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
#include <string>
#include <vector>
#include <set>

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
			 std::set<string> & p_top_axes_set,
			 WObject * parent);

  Wt::WTreeView *treeView() const { return main_axes_tree; }

  static Wt::WStandardItemModel *create_main_axes_model(bool useInternalPath ,
		  				//Wt::WStandardItemModel * & model, 
						WObject *parent );
//  Wt::WStandardItemModel *create_main_axes_model(bool useInternalPath ,
//		  				Wt::WStandardItemModel * & model 
//					      , WObject *parent );
  static Wt::WStandardItemModel *create_side_axes_model(bool useInternalPath
		  				 , WObject *parent );

private:
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
	//Wt::Ext::Panel * messages_container ;

	static Wt::WStandardItem *continentItem(const std::string& continent);

	void add_axes();
	void remove_axes_from_side();
	void remove_axes_from_top();
	void add_axes_to_top();
	void run_tables ();

	void toggleRowHeight();
	void toggleStripes();
	void toggleRoot();
};

#endif
