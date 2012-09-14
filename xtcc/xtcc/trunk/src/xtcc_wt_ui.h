// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef XTCC_WT_UI
#define XTCC_WT_UI

#include <Wt/WContainerWidget>
#include <Wt/WString>
#include <Wt/WVBoxLayout>
#include <Wt/WStandardItemModel>
#include <Wt/WHBoxLayout>
#include <Wt/Chart/WCartesianChart>
#include <Wt/WTable>
#include <Wt/WTableView>
#include <Wt/WTabWidget>
#include <Wt/WApplication>
#include <string>
#include <vector>
#include <set>
#include <Wt/WSortFilterProxyModel>
#include <Wt/WLineEdit>


using std::string;
using std::vector;
using std::set;


namespace Wt {
  class WStandardItem;
  class WStandardItemModel;
  class WTreeView;
  class WText;
}

class XtccWtUI : public Wt::WContainerWidget
{
public:
	XtccWtUI (Wt::WStandardItemModel * & model,
			 Wt::WStandardItemModel * & side_model,
			 Wt::WStandardItemModel * & top_model,
			 std::set<string> & p_side_axes_set,
			 std::set<string> & p_top_axes_set
			 //, Wt::WApplication * parent
			 );

  Wt::WTreeView *treeView() const { return main_axes_tree; }

  static Wt::WStandardItemModel *create_main_axes_model(bool useInternalPath ,
		  				//Wt::WStandardItemModel * & model, 
						WObject *parent );
//  Wt::WStandardItemModel *create_main_axes_model(bool useInternalPath ,
//		  				Wt::WStandardItemModel * & model 
//					      , WObject *parent );
  static Wt::WStandardItemModel *create_side_axes_model(bool useInternalPath
		  				 , WObject *parent, std::string text);

private:
	Wt::WSortFilterProxyModel *filteredAxes;
	Wt::WLineEdit *regexpFilter;

	// =========

	Wt::WTabWidget  * tab_widget;
	//Wt::WContainerWidget  * w  ;
	//Wt::WVBoxLayout  * vbl1  ;
	//Wt::WHBoxLayout * hbl ;
	//Wt::WHBoxLayout * hbl2 ;
	Wt::WStandardItemModel *main_axes_model;
	Wt::WTreeView          *main_axes_tree;
	Wt::WStandardItemModel *side_axes_model;
	Wt::WTreeView          *side_axes_tree;
	Wt::WStandardItemModel *top_axes_model;
	Wt::WTreeView          *top_axes_tree;
	std::set<string> & side_axes_set;
	std::set<string> & top_axes_set;
	Wt::WContainerWidget * messages_container;
	Wt::WVBoxLayout * mesg_cont_layout;
	Wt::WContainerWidget * wt_tbl_cont;
	Wt::WTable *wt_tbl ;
	int wt_tbl_element_count;
	Wt::WSelectionBox * selected_axes_view ;
	vector <Wt::Chart::WCartesianChart*> charts;
	vector <Wt::WTableView*> tables;
	vector <Wt::WContainerWidget*> containers;
	//Wt::WApplication * app_;
	//Wt::Ext::Panel * messages_container ;

	// ===============
	Wt::WContainerWidget  * topLevel_  ;
	Wt::WContainerWidget  * console_  ;
	Wt::WVBoxLayout  * threeStoreyedBuilding_  ;
	Wt::WHBoxLayout * thirdFloor_ ;
	Wt::WHBoxLayout * secondFloor_ ;
	Wt::WHBoxLayout * firstFloor_ ;

	static Wt::WStandardItem *continentItem(const std::string& continent);

	void add_axes();
	void remove_axes_from_side();
	void remove_axes_from_top();
	void add_axes_to_top();
	void run_tables ();

	void toggleRowHeight();
	void toggleStripes();
	void toggleRoot();
	void changeRegexp() {
		filteredAxes->setFilterRegExp(regexpFilter->text());
		//filteredSortedCocktails->setFilterRegExp(regexpFilter->text());
	}

	XtccWtUI& operator = (XtccWtUI &);
	XtccWtUI (XtccWtUI &);

};

#endif
