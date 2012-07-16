/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#include "TreeViewExample.h"


#include <iostream>
#include <boost/lexical_cast.hpp>
#include <cstdlib>
#include <cstdio>
#include <sstream>

#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WEnvironment>
#include <Wt/WPanel>
#include <Wt/WPushButton>
#include <Wt/WStandardItem>
#include <Wt/WStandardItemModel>
#include <Wt/WText>
#include <Wt/WTreeView>
#include <Wt/WHBoxLayout>
#include <Wt/Http/Response>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>
#include "expr.h"
//#include "tree.h"
#include "debug_mem.h"
#include "stmt.h"
#include "Tab.h"
#include "code_output_files.h"
#include "generate_code.hpp"

extern map <string, Table::ax*> ax_map;
using namespace Wt;
int	compile( char * const XTCC_HOME, char * const work_dir);
int	run(char * data_file_name, int rec_len);
extern char * XTCC_HOME;
extern char * data_file ;
extern int rec_len;
extern char * work_dir;

static const char *weatherIcons[] = {
  "sun01.png",
  "cloudy01.png",
  "w_cloud.png",
  "rain.png",
  "storm.png",
  "snow.png"
};

TreeViewExample::TreeViewExample (WStandardItemModel *model,
			 	  WStandardItemModel *side_model,
			 	  WStandardItemModel *top_model,
				  /* const WString& titleText */
				WObject * parent)
  : main_axes_model (model), main_axes_tree (0), 
	side_axes_model (side_model), side_axes_tree (0),
	top_axes_model (top_model), top_axes_tree (0)
{
#if 0
	WStandardItemModel *main_axes_model = new WStandardItemModel(0, 1, parent);
	main_axes_model->setHeaderData(0, Horizontal, std::string("Axes"));
	for (Table::CMAPITER it = ax_map.begin(); it != ax_map.end(); ++it) {
		//gtk_tree_store_append (store, &iter_child, &iter_parent);
		WStandardItem * data = new WStandardItem(it->first);
		data->setColumnCount(1);
		main_axes_model -> appendRow (data);
	}
#endif /* 0 */

  //belgium_ = main_axes_model->item(0, 0)->child(0, 0);

  //new WText(titleText, this);

  /*
   * Now create the view
   */
  WPanel *panel1 = new WPanel(this);
  panel1->resize(150, 300);
  panel1->setCentralWidget(main_axes_tree = new WTreeView());

  WPanel *panel2 = new WPanel(this);
  panel2->resize(150, 300);
  panel2->setCentralWidget(side_axes_tree = new WTreeView());
  side_axes_tree->setModel(side_axes_model);
  side_axes_tree->setSelectionMode (ExtendedSelection);

  WPanel *panel3 = new WPanel(this);
  panel3->resize(150, 300);
  panel3->setCentralWidget(top_axes_tree = new WTreeView());
  top_axes_tree->setModel(top_axes_model);
  top_axes_tree->setSelectionMode (ExtendedSelection);

  WContainerWidget  * w  = new WContainerWidget(this);
  WHBoxLayout * hbl = new WHBoxLayout ();
  hbl->addWidget (panel1 );
  hbl->addWidget (panel2);
  hbl->addWidget (panel3);
  w->setLayout (hbl, AlignTop | AlignJustify);

  if (!WApplication::instance()->environment().ajax()) {
    main_axes_tree->resize(WLength::Auto, 90);
    side_axes_tree->resize(WLength::Auto, 90);
  }
  //main_axes_tree->setSelectionBehaviour (SelectRows);
  main_axes_tree->setSelectionMode (ExtendedSelection);
  main_axes_tree->setAlternatingRowColors(true);
  main_axes_tree->setRowHeight(25);
  main_axes_tree->setModel(main_axes_model);

  main_axes_tree->setColumnWidth(1, WLength(40));
  main_axes_tree->setColumnAlignment(1, AlignCenter);
  //main_axes_tree->setColumnWidth(3, WLength(100));
  //main_axes_tree->setColumnAlignment(3, AlignCenter);

  /*
   * Expand the first (and single) top level node
   */
  main_axes_tree->setExpanded(main_axes_model->index(0, 0), true);
  //main_axes_tree->setExpanded(main_axes_model->index(0, 0, main_axes_model->index(0, 0)), true);

  /*
   * Setup some buttons to manipulate the view and the model.
   */
#if 1
  WContainerWidget *wc = new WContainerWidget();
  hbl->addWidget (wc);
  WPushButton *b;
  
  b = new WPushButton("Side =>", wc);
  b->clicked().connect(this, &TreeViewExample::add_axes);
  //b->setToolTip("Toggles row height between 31px and 25px");
  b = new WPushButton("Top =>", wc);
  b->clicked().connect(this, &TreeViewExample::add_axes_to_top);
  b->setToolTip("Toggle alternating row colors");
  
  b = new WPushButton("Run", wc);
  b->clicked().connect(this, &TreeViewExample::run_tables);
  b->setToolTip("Toggles root item between all and the first continent.");

#if 0 
  b = new WPushButton("Add rows", wc);
  b->clicked().connect(this, &TreeViewExample::addRows);
  b->setToolTip("Adds some cities to Belgium");
#endif /*  0 */
#endif /*  0 */
}

#if 1
WStandardItemModel *TreeViewExample::create_main_axes_model(bool useInternalPath,
						 WObject *parent)
{
  WStandardItemModel *result = new WStandardItemModel(0, 1, parent);
  result->setHeaderData(0, Horizontal, std::string("Axes"));
  /*
   * ... and data
   */
	for (Table::CMAPITER it = ax_map.begin(); it != ax_map.end(); ++it) {
		//gtk_tree_store_append (store, &iter_child, &iter_parent);
		WStandardItem * data = new WStandardItem(it->first);
		data->setColumnCount(1);
		result -> appendRow (data);
		//gtk_tree_store_append (main_axes_store, &iter_parent, NULL);
		//gtk_tree_store_set (main_axes_store, &iter_parent, 
		//			AXIS_COLUMN, it->first.c_str(),
		//			-1);
	}
  return result;
}
#endif /* 0 */

WStandardItemModel *TreeViewExample::create_side_axes_model(bool useInternalPath,
						 WObject *parent)
{
	WStandardItemModel *result = new WStandardItemModel(0, 1, parent);
	result->setHeaderData(0, Horizontal, std::string("Side Axes"));
	return result;
}

WStandardItem *TreeViewExample::continentItem(const std::string& continent)
{
  WStandardItem *result = new WStandardItem(continent);
  result->setColumnCount(4);
  return result;
}

WStandardItem *TreeViewExample::countryItem(const std::string& country,
					    const std::string& code)
{
  WStandardItem *result = new WStandardItem(WString::fromUTF8(country));
  result->setIcon("icons/flag_" + code + ".png");
  
  return result;
}

std::vector<WStandardItem *>
TreeViewExample::cityItems(const std::string& city,
			   WeatherIcon weather,
			   const std::string& drink,
			   bool useInternalPath, bool visited)
{
  std::vector<WStandardItem *> result;
  WStandardItem *item;
  
  // column 0: country
  item = new WStandardItem(WString::fromUTF8(city));
  result.push_back(item);
  
  // column 1: weather
  item = new WStandardItem();
  item->setIcon(std::string("icons/") + weatherIcons[weather]);
  result.push_back(item);
  
  // column 2: drink
  item = new WStandardItem(drink);
  if (useInternalPath)
    item->setInternalPath("/drinks/" + drink);
  result.push_back(item);
  
  // column 3: visited
  item = new WStandardItem();
  item->setCheckable(true);
  item->setChecked(visited);
  result.push_back(item);
  
  return result;
}

void TreeViewExample::toggleRowHeight()
{
  if (main_axes_tree->rowHeight() == WLength(31))
    main_axes_tree->setRowHeight(25);
  else
    main_axes_tree->setRowHeight(31);
}

void TreeViewExample::add_axes()
{
	WModelIndexSet sel_indx = main_axes_tree->selectedIndexes();
	int n_axes = 0;
	for (set<WModelIndex>::iterator it = sel_indx.begin();
			it != sel_indx.end(); ++it) {
		WStandardItem *data = main_axes_model->itemFromIndex(*it);
		std::cout << data->text() << std::endl;
		WStandardItem * data2 = new WStandardItem (data->text());
		side_axes_model -> appendRow ( data2) ;
		++ n_axes;
	}
	std::cout << "selectedIndexes: " << n_axes << std::endl;
}


void TreeViewExample::add_axes_to_top()
{
	WModelIndexSet sel_indx = main_axes_tree->selectedIndexes();
	int n_axes = 0;
	for (set<WModelIndex>::iterator it = sel_indx.begin();
			it != sel_indx.end(); ++it) {
		WStandardItem *data = main_axes_model->itemFromIndex(*it);
		std::cout << data->text() << std::endl;
		WStandardItem * data2 = new WStandardItem (data->text());
		top_axes_model -> appendRow ( data2) ;
		++ n_axes;
	}
	std::cout << "selectedIndexes: " << n_axes << std::endl;
}
void TreeViewExample::toggleStripes()
{
  main_axes_tree->setAlternatingRowColors(!main_axes_tree->alternatingRowColors());
}

void TreeViewExample::toggleRoot()
{
  if (main_axes_tree->rootIndex() == WModelIndex())
    main_axes_tree->setRootIndex(main_axes_model->index(0, 0));
  else
    main_axes_tree->setRootIndex(WModelIndex());
}

void TreeViewExample::addRows()
{
#if 0
  static int COUNT = 10;

  for (int i = 0; i < COUNT; ++i) {
    std::string cityName = "City "
      + boost::lexical_cast<std::string>(belgium_->rowCount() + 1);
    
    bool useInternalPath = false;
    belgium_->appendRow(cityItems(cityName, Storm, "Juice", useInternalPath,
				  false));
  }

  main_axes_tree->scrollTo(belgium_->child(belgium_->rowCount() -COUNT )->index(),
		      WAbstractItemView::PositionAtTop);
#endif /*  0  */
}


void TreeViewExample:: run_tables ()
{
	using std::cout;
	using std::endl;
	using std::cerr;
	cout << "side row count: " << side_axes_model->rowCount()
		<< endl;
	cout << "top row count: " << top_axes_model->rowCount()
		<< endl;
	vector <string> side_axes;
	for (int i=0; i < side_axes_model->rowCount(); ++i) {
		WStandardItem * item = side_axes_model->item (i);
		side_axes.push_back (item->text().toUTF8());
	}
	vector <string> ban_axes;
	for (int i=0; i < top_axes_model->rowCount(); ++i) {
		WStandardItem * item = top_axes_model->item (i);
		ban_axes.push_back (item->text().toUTF8());
	}
#if 0
	GtkTreeIter iter;
	/* Get the first iter in the list */
	GtkTreeModel * model = gtk_tree_view_get_model (side_axes_tree); 
	gboolean valid = gtk_tree_model_get_iter_first (model, &iter);
	vector <string> side_axes;
	gint row_count = 0;
	while (valid) {
		/* Walk through the list, reading each row */
		gchar *str_data;
		/* Make sure you terminate calls to gtk_tree_model_get()
		* with a '-1' value
		*/
		gtk_tree_model_get (model, &iter,
				  AXIS_COLUMN, &str_data,
				  -1);
		/* Do something with the data */
		//g_print ("Row %d: |%s|\n", row_count, str_data);
		side_axes.push_back (str_data);
		g_free (str_data);
		row_count ++;
		valid = gtk_tree_model_iter_next (model, &iter);
	}
	/* Get the first iter in the list */
	model = gtk_tree_view_get_model (top_axes_tree); 
	valid = gtk_tree_model_get_iter_first (model, &iter);
	vector <string> ban_axes;
	row_count = 0;
	while (valid) {
		/* Walk through the list, reading each row */
		gchar *str_data;
		/* Make sure you terminate calls to gtk_tree_model_get()
		* with a '-1' value
		*/
		gtk_tree_model_get (model, &iter,
				  AXIS_COLUMN, &str_data,
				  -1);
		/* Do something with the data */
		//g_print ("Row %d: |%s|\n", row_count, str_data);
		ban_axes.push_back (str_data);
		g_free (str_data);
		row_count ++;
		valid = gtk_tree_model_iter_next (model, &iter);
	}
#endif /* 0 */
	if (side_axes.size() == 0) {
		cout << "No axes in side: \n";
	} else if (ban_axes.size() == 0) {
		cout << "No axes in banner: \n";
	} else {
		cout <<  "Ok to tabulate: \n";
		vector<Table::table*>	table_list;
		for (int i=0; i < side_axes.size(); ++i) {
			for (int j=0; j < ban_axes.size(); ++j) {
				Table::table * tbl = new Table::table (side_axes[i], ban_axes[j], 0);
				table_list.push_back (tbl);
			}
		}
		cout <<  "work_dir: %s\n"  << work_dir << endl;
		string fname = string(work_dir) + string("/my_table.C");
		FILE * table_op=fopen( fname.c_str(), "w");
		fname = string(work_dir) + string("/my_tab_drv_func.C");
		FILE * tab_drv_func=fopen(fname.c_str(), "w");	
		fname = string(work_dir) + string("/my_tab_summ.C");
		FILE * tab_summ_func=fopen(fname.c_str(), "w");	
		if(!(table_op&&tab_drv_func&&tab_summ_func)){
			std::cerr << "Unable to open file for output of table classes" << std::endl;
			exit(1);
		}
		print_table_code (table_op, tab_drv_func, tab_summ_func, table_list);
		fclose(table_op);
		fclose(tab_drv_func);
		fclose(tab_summ_func);
		if (!compile(XTCC_HOME, work_dir)) {
			using namespace std;
			int rval = run(data_file, rec_len);
			cout << "xtcc run complete" << endl;

			//Wt::Http::Response resp;
			//resp.addHeader ("Content-Type", "binary/octet-stream");
			//ostringstream  size_str ;
		}
		for (int i=0; i < table_list.size(); ++i) {
			delete table_list[i];
		}
#if 0
#endif /*  0 */
	}
}
