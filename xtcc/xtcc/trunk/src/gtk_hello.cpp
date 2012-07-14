/*
 * =====================================================================================
 *
 *       Filename:  gtk_hello.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 13 July 2012 10:01:19  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include "expr.h"
//#include "tree.h"
#include "debug_mem.h"
#include "stmt.h"
#include "Tab.h"
#include "code_output_files.h"
#include "generate_code.hpp"

template<class T> T* link_chain(T* & elem1, T* & elem2);
template<class T> T* trav_chain(T* & elem1);
extern vector<Table::table*>	table_list;
extern map <string, Table::ax*> ax_map;
extern vector<mem_addr_tab>  mem_addr;
extern int rec_len;
extern struct Statement::AbstractStatement * tree_root;
void flex_finish();
extern vector <Scope*> active_scope_list;
extern Scope* active_scope;
extern vector <Statement::FunctionInformation*> func_info_table;

extern int errno;
bool flag_compile_only;
//void print_expr(FILE* edit_out, AbstractExpression * e);

int check_parameters(struct AbstractExpression* e, struct FunctionParameter* v);
bool check_type_compat(DataType typ1, DataType typ2);
int	compile( char * const XTCC_HOME, char * const work_dir);
int	run(char * data_file_name, int rec_len);
//void print_table_code(FILE * op, FILE *tab_drv_func, FILE * tab_summ_func);
void print_weighting_code();
//void print_axis_code(FILE * op, FILE * axes_drv_func);
void clean_up();

void	generate_edit_section_code();
void 	generate_make_file();

extern	vector <Table::weight_axis_group> wt_axis_group_vec;
extern	vector <Table::weight_axis> wt_axis_vec;

extern void yyrestart ( FILE *input_file );
extern int yyparse();
#include <sys/stat.h>
#include <sys/types.h>
#include <cctype>
#include <fcntl.h>
#include <unistd.h>

std::fstream debug_log_file("xtcc_debug.log", std::ios_base::out|std::ios_base::trunc);
void	print_memory_leaks();
char default_work_dir[]="xtcc_work";
char * work_dir=default_work_dir;
void reset_files();

bool flag_use_clang = false;
CodeOutputFiles code_output_files;


extern int no_errors;
extern int line_no;




#include <gtk/gtk.h>
#include <iostream>
#include <cstdlib>
	using std::cout;
	using std::endl;
	using std::cerr;
/* This is a callback function. The data arguments are ignored
* in this example. More on callbacks below. */
GtkWidget * setup_tree_view(GtkTreeStore  *& store, GtkTreeSelection * & selection);
void hello( GtkWidget *widget, gpointer data )
{
	g_print ("Hello World\n");
}
gint delete_event( GtkWidget *widget,
	GdkEvent *event, gpointer data) 
{
	/*
	*
	*
	*
	*
	If you return FALSE in the "delete_event" signal handler,
	GTK will emit the "destroy" signal. Returning TRUE means
	you don’t want the window to be destroyed.
	This is useful for popping up ’are you sure you want to quit?’
	type dialogs. */
	g_print ("delete event occurred\n");
	/* Change TRUE to FALSE and the main window will be destroyed with
	* a "delete_event". */
	//return TRUE
	return FALSE;
}
/* Another callback */
void destroy (GtkWidget *widget, gpointer data)
{
	gtk_main_quit ();
}

	void setup_gui();
int main (int argc, char *argv[])
{
	/* GtkWidget is the storage type for widgets */
	GtkWidget *button;
	/* This is called in all GTK applications. Arguments are parsed
	* from the command line and are returned to the application. */
	gtk_init (&argc, &argv);
	if (argc < 2) {
		cout << "Usage: " << argv[0] << " <prog-name> <data-file>" << endl << endl;
		exit(1);
	} else {
		cout << "Program name: " << argv[1] << ", Data file: " << argv[2] << endl;
	}

	char * inp_file = argv[1];
	char * data_file = argv[2];
	char * XTCC_HOME=getenv("XTCC_HOME");
	active_scope=new Scope();
	active_scope_list.push_back(active_scope);

	const char * printf_name="printf";
	Statement::FunctionParameter* v_list=0;
	DataType myreturn_type=INT8_TYPE;
	Statement::FunctionInformation* fi=new Statement::FunctionInformation(printf_name, v_list, myreturn_type);
	func_info_table.push_back(fi);


	FILE * yyin=fopen(inp_file,"r");
	if(!yyin) {
		cerr << "Unable to open file: " << argv[1] << " for read ...exiting" << endl; exit(1);
	}
	yyrestart(yyin);
	if(yyparse()){
		cout << "Errors in parsing edit: " << no_errors << endl;
		exit(1);
	} 

	//yyterminate();
	//GenerateCode(tree_root);
	struct   stat file_info;
	int xtcc_work_dir_exists=stat(work_dir, &file_info);
	if (xtcc_work_dir_exists==-1){
		cout << "attempting to create directory xtcc_work" << endl;
		// file does not exist - so create the directoryo
#ifndef _WIN32
		int dir_success=mkdir (work_dir, S_IRUSR| S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP);
#else
		int dir_success=mkdir (work_dir /*, S_IRUSR| S_IWUSR | S_IXUSR*/);
#endif
		if(dir_success==-1){
			cerr << "Unable to create temp work directory " <<work_dir <<  " : ... exiting" << endl;
			exit(1);
		} else if (dir_success==0){
		} else {
			cerr << "Some error on creating directory " << work_dir << "  ... exiting" << endl;
			exit(1);
		}
	} else if (S_ISDIR(file_info.st_mode)) {
	} else {
		cerr << "file " << work_dir << " exists but is not a directory." << endl 
			<< "xtcc uses this directory to create its temporary files - please rename." << endl;
		exit(1);
	}
	
	if(!no_errors){
		generate_edit_section_code();
	} else {
		cerr << "Errors in Parse:  Total errors: " << no_errors << endl;
		exit(1);
	}

	string fname = string(work_dir) + string("/my_table.C");
	FILE * table_op=fopen( fname.c_str(), "w");

	fname = string(work_dir) + string("/my_tab_drv_func.C");
	FILE * tab_drv_func=fopen(fname.c_str(), "w");	
	fname = string(work_dir) + string("/my_tab_summ.C");
	FILE * tab_summ_func=fopen(fname.c_str(), "w");	
	if(!(table_op&&tab_drv_func&&tab_summ_func)){
		cerr << "Unable to open file for output of table classes" << endl;
		exit(1);
	}
	if(int rval=yyparse()){
		cerr << "parsing tables section failed:" << endl;
		exit(rval);
	}
	if(no_errors >0 ){
		cerr << "Error(s) in the tabulation section: " << no_errors << endl;
		exit(1);
	} else {
		cout << "Successfully parsed tabulation section" << endl;
	}

	fname = string(work_dir)+ ("/my_axes.C");
	FILE * axes_op=fopen(fname.c_str(), "w");	
	fname = string(work_dir) + string("/my_axes_drv_func.C");
	FILE * axes_drv_func=fopen(fname.c_str(), "w");	
	if(!(axes_op&&axes_drv_func)){
		cerr << "Unable to open file for output of axes classes" << endl;
		exit(1);
	}
	if(int rval=yyparse()){
		cerr << "parsing axes section failed:" << endl;
		exit(rval);
	} 

	if(no_errors >0 ){
		cerr << "Errors in axes section: " << no_errors << endl;
		exit(1);
	} else {
		cout << "Successfully parsed axes section" << endl;
	}
	
	flex_finish();
	extern vector<Table::table*>	table_list;
	print_table_code(table_op, tab_drv_func, tab_summ_func, table_list);
	print_axis_code(axes_op, axes_drv_func);
	print_weighting_code();
	generate_make_file();
	fclose(yyin); yyin=0;
	fclose(table_op);
	fclose(tab_drv_func);
	fclose(axes_op); 
	fclose(axes_drv_func);
	fclose(tab_summ_func);
	//bool my_compile_flag=true;
	//bool my_compile_flag=false;
	printf("parsing over\n about to begin compiling\n");
	//if(my_compile_flag&&!compile(XTCC_HOME, work_dir))


	/* create a new window */
	setup_gui();

	/* All GTK applications must have a gtk_main(). Control ends here
	* and waits for an event to occur (like a key press or
	* mouse event). */
	gtk_main ();
	return 0;
}

void	print_memory_leaks(){
	using std::cout;
	using std::endl;
	using std::cerr;
	std::fstream mem_leak_log("mem_leak.log", std::ios_base::out|std::ios_base::trunc);
	if(!mem_leak_log){
		cerr << "Unable to open mem_leak.log for memory leak info output" << endl;
		exit(1);
	}
	for(int i=0; i< mem_addr.size(); ++i ){
		if(mem_addr[i].mem_ptr ){
			mem_leak_log << "addr: " << mem_addr[i].mem_ptr 
				<< " line: " << mem_addr[i].line_number 
				<< "src file: " << mem_addr[i].src_file 
				<< "src line_no: " << mem_addr[i].src_file_line_no
				<< endl;
		}
	}
}



void clean_up(){
	using std::cout;
	using std::endl;
	using std::cerr;
	debug_log_file << "Entered function clean_up()" << endl;
	typedef map<string, Table::ax*>::iterator ax_map_iter;
	for(ax_map_iter it=ax_map.begin(); it!=ax_map.end(); ++it){
		delete it->second; it->second=0;
	}
	// we should only delete the 0 index Scope as this was manually created by us
	if (active_scope_list[0]) {
		delete active_scope_list[0]; active_scope_list[0]=0;
	}

	for(int i=0; i<table_list.size(); ++i){
		delete table_list[i];
	}
	debug_log_file << "Exited function clean_up()" << endl;
			
}



		





template<class T> T* link_chain(T* &elem1, T* &elem2){
	elem2->prev_=elem1;
	elem1->next_=elem2;
	return elem2;
}

template<class T> T* trav_chain(T* & elem1){
	if(elem1){
		while (elem1->prev_) elem1=elem1->prev_;
		return elem1;
		/*
		while (elem1->exists_next()){
			
		}
		*/
	} else return 0;
}

#include <cstdlib>
int compile(char * const XTCC_HOME, char * const work_dir)
{
	using std::cout;
	using std::endl;
	using std::cerr;
	int rval;
	string my_work_dir=string(work_dir)+string("/");
	string MY_XTCC_HOME=string(XTCC_HOME)+string("/");
#if !defined(__WIN32__) && !defined(MAC_TCL) /* GNU/UNIX */
	string cmd=string("rm ") + string(work_dir) + string("/temp.C");
	//system("rm xtcc_work/temp.C");
	cout << "XTCC_HOME is = " << XTCC_HOME << endl;
	const char * file_list[]={
		"edit_out.c", "my_axes_drv_func.C", "/stubs/main_loop.C", 
		"my_tab_drv_func.C", "temp.C" 
	};
	const char * copy_file_list[] = {"/stubs/ax_stmt_type.h",
					"/stubs/mean_stddev_struct.h"
	};

	for(int i=0; i<(sizeof(copy_file_list)/sizeof(copy_file_list[0])); ++i) {
		string cmd0="cp "; 
		cmd0 += MY_XTCC_HOME +  copy_file_list[i] + " " + my_work_dir;
		// cout << "executing command : " << cmd0 << endl;
		rval=system(cmd0.c_str());
		if (rval) {
			cerr << "unable to cp include file: "  << copy_file_list[i] << " to " << my_work_dir << endl;
			return rval;
		}
	}
	string cmd1="cat "; 
	const int main_loop_file_index=2;
	const int temp_file_index=4;

	for(int i=0; i<(sizeof(file_list)/sizeof(file_list[0]))-1; ++i){
		if (i==main_loop_file_index){
			cmd1 += MY_XTCC_HOME + string(file_list[i])+ string(" ");
		} else {
			cmd1 += my_work_dir + string(file_list[i])+string(" ");
		}
	}
	cmd1 += string (" > ") + my_work_dir + string(file_list[temp_file_index]);
	string cmd3=string("; echo \"#include <" ) + string (XTCC_HOME) + string("/stubs/list_summ_template.C>\" >> ") + my_work_dir + string("/temp.C");
	cmd1 += cmd3;

#endif /* GNU/UNIX */
#if __WIN32__
	/* this code has to be updated as above*/
	system("del xtcc_work\\temp.C");
	const char * copy_file_list[] = {"/stubs/ax_stmt_type.h",
					"/stubs/mean_stddev_struct.h"
	};
	for(int i=0; i<(sizeof(copy_file_list)/sizeof(copy_file_list[0])); ++i) {
		string cmd0="copy "; 
		cmd0 += MY_XTCC_HOME +  copy_file_list[i] + " " + my_work_dir;
		// cout << "executing command : " << cmd0 << endl;
		rval=system(cmd0.c_str());
		if (rval) {
			cerr << "unable to copy include file: "  << copy_file_list[i] << " to " << my_work_dir << endl;
			return rval;
		}
	}
	//string cmd1=string("type xtcc_work\\edit_out.c xtcc_work\\my_axes_drv_func.C xtcc_work\\my_tab_drv_func.C ") + string(XTCC_HOME)+ string("\\stubs\\main_loop.C > xtcc_work\\temp.C");
	string cmd1=string("type ");
	const char * file_list[]={
		"edit_out.c", "my_axes_drv_func.C", "/stubs/main_loop.C", 
		"my_tab_drv_func.C", "temp.C" 
	};
	for(int i=0; i<(sizeof(file_list)/sizeof(file_list[0]))-1; ++i){
		if (i==main_loop_file_index){
			cmd1 += MY_XTCC_HOME + string(file_list[i])+ string(" ");
		} else {
			cmd1 += my_work_dir + string(file_list[i])+string(" ");
		}
	}
	cmd1 += string (" > ") + my_work_dir + string(file_list[temp_file_index]);
	string cmd3=string("; echo \"#include <" ) + string (XTCC_HOME) + string("/stubs/list_summ_template.C>\" >> ") + my_work_dir + string("/temp.C");
	//cmd1 += cmd3;
#endif /* __WIN32__ */

	cout << cmd1.c_str() << endl;
	rval=system(cmd1.c_str());
	if(rval){
		cerr << "unable to cat files" << endl;
		return rval;
	}
#if !defined(__WIN32__) && !defined(MAC_TCL) /* GNU/UNIX */
	string cmd2;
	if (flag_use_clang == false)
		cmd2=string("g++ -g ") + work_dir + string("/temp.C -o ") +  work_dir + string("/myedit.exe");
	else
		cmd2=string("clang -g ") + work_dir + string("/temp.C -o ") +  work_dir + string("/myedit.exe /usr/lib/libstlport_gcc.so.4.6");
#endif /* GNU/UNIX */	
#if __WIN32__
	string cmd2="\\Borland\\BCC55\\Bin\\bcc32 -P -I\\Borland\\BCC55\\Include -L\\Borland\\BCC55\\LIB -extcc_work\\myedit.exe xtcc_work\\temp.C ";
#endif /* __WIN32__ */	

	cout << "compile command: " << endl
		<< cmd2 << endl;
	rval=system(cmd2.c_str());

	return rval;
}

#include <sstream>
int run(char * data_file_name, int rec_len){
	int rval;
	std::ostringstream cmd1;
#if	__WIN32__
	cmd1 << "xtcc_work\\myedit.exe " << data_file_name  << " " << rec_len;
#endif /* __WIN32__ */
#if !defined(__WIN32__) && !defined(MAC_TCL) /* GNU/UNIX */
	string cmd0 = "date +hour:%l:minute:%M:second:%S:nanosecond:%N";
	rval=system(cmd0.c_str());

	cmd1 <<  "echo \"executing exe\"; time " << work_dir << "/myedit.exe " << data_file_name  << " " << rec_len;
#endif /* UNIX */
	std::cout << "executing : " 
		<< cmd1.str() << std::endl;
	rval=system(cmd1.str().c_str());
	if (!rval) {
		string cmd0 = "date +hour:%l:minute:%M:second:%S:nanosecond:%N";
		rval=system(cmd0.c_str());
	}
	return rval;
}





#include <fstream>
void reset_files(){
	using std::cout;
	using std::endl;
	using std::cerr;
	std::ofstream lst_op("lst_.csv", std::ios_base::out|std::ios_base::trunc);
	lst_op << endl;
	lst_op.close();
	std::ofstream tab_op("tab_.csv", std::ios_base::out|std::ios_base::trunc);
	tab_op << endl;
	tab_op.close();
	std::ofstream tab_tex("tab_.tex", std::ios_base::out|std::ios_base::trunc);
	tab_tex << endl;
	tab_tex.close();
}

void print_weighting_code()
{
	using namespace std;
	cout << "wt_axis_group_vec.size(): " << wt_axis_group_vec.size() << endl;
	if (wt_axis_group_vec.size() > 0) {
		for (int i=0; i < wt_axis_group_vec.size(); ++i) {
			vector <Table::weight_axis> & wt_axis_vec = wt_axis_group_vec[i].weight_axis_vec;
			vector <Table::ax * > wt_ax_ptr_vec (wt_axis_vec.size());
			for (int j=0; j < wt_axis_vec.size(); ++j) {
				Table::ax * ax_ptr = ax_map[wt_axis_vec[j].name];			
				wt_ax_ptr_vec.push_back (ax_ptr);
			}
		}
	} else {
		return;
	}
}
/*  ================ GUI ==================== */

enum { AXIS_COLUMN, N_COLUMNS };
// Bad !!! global variables, I hope I can get away with this
//

struct GUIAxData {
	GtkTreeStore * axes_store;
	GtkTreeSelection * axes_selection;
};

GtkTreeStore * main_axes_store;
GtkTreeStore * side_axes_store;
GtkTreeStore * top_axes_store;
GtkTreeSelection * main_axes_selection;
GtkTreeSelection * side_axes_selection;
GtkTreeSelection * top_axes_selection;

void add_axes( GtkWidget *widget, gpointer data)
{
        GtkTreeIter iter;
        GtkTreeModel *model;
        gchar *ax_name;
	/* 
        if (gtk_tree_selection_get_selected (main_axes_selection, &model, &iter))
        {
                gtk_tree_model_get (model, &iter, AXIS_COLUMN, &ax_name, -1);
                g_print ("You selected axis: %s\n", ax_name);
                g_free (ax_name);
        } */
	GtkTreeSelection * selection = main_axes_selection;
	GtkTreeStore * store = (GtkTreeStore *) data; 
	if (gtk_tree_selection_count_selected_rows (selection) ) {
		GList * selected_tree_path = gtk_tree_selection_get_selected_rows (selection, &model);
		for (GList * gl = selected_tree_path; gl; gl=gl->next) {
			//GtkTreeRowReference * row_ref = gtk_tree_row_reference_new (model, GtkTreePath (gl->data));
			int arr_sz = 0;
			gint * indices = gtk_tree_path_get_indices_with_depth ( (GtkTreePath *) gl->data, &arr_sz);
			//cout << "arr_sz:" << arr_sz << endl;
			//for (int i=0; i < arr_sz; ++i) {
			//	cout << "Path: " << indices[i] << endl;
			//}
			if (gtk_tree_model_get_iter (model, &iter, (GtkTreePath *) gl->data)) {
				gtk_tree_model_get (model, &iter, AXIS_COLUMN, &ax_name, -1);
				g_print ("You selected axis: %s\n", ax_name);

				GtkTreeIter iter_parent;
				//gtk_tree_store_append (side_axes_store, &iter_parent, NULL);
				gtk_tree_store_append (store, &iter_parent, NULL);
				//gtk_tree_store_set (side_axes_store, &iter_parent, 
				//			AXIS_COLUMN, ax_name,
				//			-1);
				gtk_tree_store_set (store, &iter_parent, 
							AXIS_COLUMN, ax_name,
							-1);
			}
		}
	}

}

void remove_axes_side( GtkWidget *widget, gpointer data )
{
	//g_print ("Hello World\n");
        GtkTreeIter iter;
        GtkTreeModel *model;
        gchar *ax_name;
	GtkTreeSelection * selection = side_axes_selection;
	//GtkTreeStore * store = (GtkTreeStore *) data; 
	GtkTreeStore * store = side_axes_store; 
	vector <GtkTreePath*> path_vec;
	if (gtk_tree_selection_count_selected_rows (selection) ) {
		GList * selected_tree_path = gtk_tree_selection_get_selected_rows (selection, &model);
		for (GList * gl = selected_tree_path; gl; gl=gl->next) {
			//GtkTreeRowReference * row_ref = gtk_tree_row_reference_new (model, GtkTreePath (gl->data));
			int arr_sz = 0;
			gint * indices = gtk_tree_path_get_indices_with_depth ( (GtkTreePath *) gl->data, &arr_sz);
			cout << "arr_sz:" << arr_sz << endl;
			for (int i=0; i < arr_sz; ++i) {
				cout << "Path: " << indices[i] << endl;
			}
			//if (gtk_tree_model_get_iter (model, &iter, (GtkTreePath *) gl->data)) {
			//	gtk_tree_model_get (model, &iter, AXIS_COLUMN, &ax_name, -1);
			//	// works correctly, doesnt seem to print the right value on screen though
			//	g_print ("You removed axis: %s\n", ax_name);
			//	gtk_tree_store_remove (store, &iter);
			//}
			path_vec.push_back ( (GtkTreePath*) gl->data);
		}
		// delete in reverse order, or we invalidate the iterators
		for (int i=path_vec.size()-1 ; i>=0; --i) {
			if (gtk_tree_model_get_iter (model, &iter,  path_vec[i])) {
				gtk_tree_model_get (model, &iter, AXIS_COLUMN, &ax_name, -1);
				// works correctly, doesnt seem to print the right value on screen though
				g_print ("You removed axis: %s\n", ax_name);
				gtk_tree_store_remove (store, &iter);
			}
		}
	}
}

void remove_axes_top( GtkWidget *widget, gpointer data )
{
	//g_print ("Hello World\n");
        GtkTreeIter iter;
        GtkTreeModel *model;
        gchar *ax_name;
	GtkTreeSelection * selection = top_axes_selection;
	//GtkTreeStore * store = (GtkTreeStore *) data; 
	GtkTreeStore * store = top_axes_store; 
	vector <GtkTreePath*> path_vec;
	if (gtk_tree_selection_count_selected_rows (selection) ) {
		GList * selected_tree_path = gtk_tree_selection_get_selected_rows (selection, &model);
		for (GList * gl = selected_tree_path; gl; gl=gl->next) {
			//GtkTreeRowReference * row_ref = gtk_tree_row_reference_new (model, GtkTreePath (gl->data));
			int arr_sz = 0;
			gint * indices = gtk_tree_path_get_indices_with_depth ( (GtkTreePath *) gl->data, &arr_sz);
			cout << "arr_sz:" << arr_sz << endl;
			for (int i=0; i < arr_sz; ++i) {
				cout << "Path: " << indices[i] << endl;
			}
			//if (gtk_tree_model_get_iter (model, &iter, (GtkTreePath *) gl->data)) {
			//	gtk_tree_model_get (model, &iter, AXIS_COLUMN, &ax_name, -1);
			//	// works correctly, doesnt seem to print the right value on screen though
			//	g_print ("You removed axis: %s\n", ax_name);
			//	gtk_tree_store_remove (store, &iter);
			//}
			path_vec.push_back ( (GtkTreePath*) gl->data);
		}
		// delete in reverse order, or we invalidate the iterators
		for (int i=path_vec.size()-1 ; i>=0; --i) {
			if (gtk_tree_model_get_iter (model, &iter,  path_vec[i])) {
				gtk_tree_model_get (model, &iter, AXIS_COLUMN, &ax_name, -1);
				// works correctly, doesnt seem to print the right value on screen though
				g_print ("You removed axis: %s\n", ax_name);
				gtk_tree_store_remove (store, &iter);
			}
		}
	}
}


void setup_gui()
{
	GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size ( (GtkWindow *) window, 460, 620);
	GtkWidget *scr_window = gtk_scrolled_window_new (NULL, NULL);


	GtkWidget* table = gtk_table_new (6, 6, TRUE);
	/* When the window is given the "delete_event" signal (this is given
	* by the window manager, usually by the "close" option, or on the
	* titlebar), we ask it to call the delete_event () function
	* as defined above. The data passed to the callback
	* function is NULL and is ignored in the callback function. */
	g_signal_connect (G_OBJECT (window), "delete_event",
				G_CALLBACK (delete_event), NULL);
	/* Here we connect the "destroy" event to a signal handler.
	* This event occurs when we call gtk_widget_destroy() on the window,
	* or if we return FALSE in the "delete_event" callback. */
	g_signal_connect (G_OBJECT (window), "destroy",
				G_CALLBACK (destroy), NULL);
	/* Sets the border width of the window. */
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	/* Creates a new button with the label "Hello World". */
	//button = gtk_button_new_with_label ("Hello World");
	GtkWidget * main_axes_tree = setup_tree_view (main_axes_store, main_axes_selection);
	GtkWidget * side_axes_tree = setup_tree_view (side_axes_store, side_axes_selection);
	GtkWidget * top_axes_tree = setup_tree_view (top_axes_store, top_axes_selection);

	/* Load the main axes store */
	GtkTreeIter iter_parent, iter_child;
	for (Table::CMAPITER it = ax_map.begin(); it != ax_map.end(); ++it) {
		//gtk_tree_store_append (store, &iter_child, &iter_parent);
		gtk_tree_store_append (main_axes_store, &iter_parent, NULL);
		gtk_tree_store_set (main_axes_store, &iter_parent, 
					AXIS_COLUMN, it->first.c_str(),
					-1);
	}

	/* When the button receives the "clicked" signal, it will call the
	* function hello() passing it NULL as its argument. The hello()
	* function is defined above. */
	//g_signal_connect (G_OBJECT (button), "clicked",
	//			G_CALLBACK (hello), NULL);
	/* This will cause the window to be destroyed by calling
	* gtk_widget_destroy(window) when "clicked". Again, the destroy
	* signal could come from here, or the window manager. */
	//g_signal_connect_swapped (G_OBJECT (button), "clicked",
	//	G_CALLBACK (gtk_widget_destroy),
	//	G_OBJECT (window));
	/* This packs the button into the window (a gtk container). */
	gtk_container_add (GTK_CONTAINER (window), scr_window);
	gtk_container_add (GTK_CONTAINER (scr_window), table);


	gtk_table_attach_defaults (GTK_TABLE (table), main_axes_tree, 0, 1, 1, 5);

	GtkWidget * add_to_side_tab_button = gtk_button_new_with_label ("Side =>");
	g_signal_connect (G_OBJECT (add_to_side_tab_button), "clicked",
				G_CALLBACK (add_axes), (gpointer) side_axes_store);
	gtk_table_attach_defaults (GTK_TABLE (table), add_to_side_tab_button, 1, 2, 1, 2);
	gtk_widget_show (add_to_side_tab_button);
	GtkWidget * remove_from_side_tab_button = gtk_button_new_with_label ("Side <=");
	gtk_table_attach_defaults (GTK_TABLE (table), remove_from_side_tab_button, 1, 2, 2, 3);
	g_signal_connect (G_OBJECT (remove_from_side_tab_button), "clicked",
				G_CALLBACK (remove_axes_side), (gpointer) side_axes_store);
	gtk_widget_show (remove_from_side_tab_button);

	GtkWidget * add_to_top_tab_button = gtk_button_new_with_label ("Top =>");
	g_signal_connect (G_OBJECT (add_to_top_tab_button), "clicked",
				G_CALLBACK (add_axes), (gpointer) top_axes_store);
	gtk_table_attach_defaults (GTK_TABLE (table), add_to_top_tab_button, 1, 2, 3, 4);
	gtk_widget_show (add_to_top_tab_button);
	GtkWidget * remove_from_top_tab_button = gtk_button_new_with_label ("Top <=");
	gtk_table_attach_defaults (GTK_TABLE (table), remove_from_top_tab_button, 1, 2, 4, 5);
	g_signal_connect (G_OBJECT (remove_from_top_tab_button), "clicked",
				G_CALLBACK (remove_axes_top), (gpointer) NULL);
	gtk_widget_show (remove_from_top_tab_button);

	gtk_table_attach_defaults (GTK_TABLE (table), side_axes_tree, 2, 3, 1, 5);
	gtk_table_attach_defaults (GTK_TABLE (table), top_axes_tree,  3, 4, 1, 5);

	//gtk_container_add (GTK_CONTAINER (scr_window), table);
	//gtk_container_add (GTK_CONTAINER (window), button);
	/* The final step is to display this newly created widget. */
	//gtk_widget_show (button);
	gtk_widget_show (main_axes_tree);
	gtk_widget_show (side_axes_tree);
	gtk_widget_show (top_axes_tree);
	/* and the window */
	gtk_widget_show (scr_window);
	gtk_widget_show (window);
	gtk_widget_show (table);

}


#include "Tab.h"
static void tree_selection_changed_cb (GtkTreeSelection *selection, gpointer data);
GtkWidget * setup_tree_view(GtkTreeStore  *& store, GtkTreeSelection * & selection)
{
	store = gtk_tree_store_new (N_COLUMNS, G_TYPE_STRING);

	GtkTreeIter iter_parent, iter_child;


	/* 
	extern map <string, Table::ax*> ax_map;
	Table::CMAPITER it = ax_map.begin();
	if (it != ax_map.end()) {
		gtk_tree_store_append (store, &iter_parent, NULL);
		gtk_tree_store_set (store, &iter_parent, 
					AXIS_COLUMN, it->first.c_str(),
					-1);
	}
	*/

	/*
	for (Table::CMAPITER it = ax_map.begin(); it != ax_map.end(); ++it) {
		//gtk_tree_store_append (store, &iter_child, &iter_parent);
		gtk_tree_store_append (store, &iter_parent, NULL);
		gtk_tree_store_set (store, &iter_parent, 
					AXIS_COLUMN, it->first.c_str(),
					-1);
	}
	*/
	GtkWidget * tree = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));

	GtkCellRenderer *renderer = gtk_cell_renderer_text_new ();
	GtkTreeViewColumn * column = gtk_tree_view_column_new_with_attributes ("Axis",
					renderer, "text", AXIS_COLUMN, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);


	/*  setup the callback selection handlers */


/* Prototype for selection handler callback */

/* Setup the selection handler */
	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (tree));
	//gtk_tree_selection_set_mode (main_axes_selection, GTK_SELECTION_SINGLE);
	gtk_tree_selection_set_mode (selection, GTK_SELECTION_MULTIPLE);
	g_signal_connect (G_OBJECT (selection), "changed",
			  G_CALLBACK (tree_selection_changed_cb),
			  NULL);

	gtk_widget_show (tree);
	return tree;
}

static void tree_selection_changed_cb (GtkTreeSelection *selection, gpointer data)
{
        GtkTreeIter iter;
        GtkTreeModel *model;
        gchar *ax_name;

	/* 
        if (gtk_tree_selection_get_selected (selection, &model, &iter)) {
                gtk_tree_model_get (model, &iter, AXIS_COLUMN, &ax_name, -1);
                g_print ("You selected axis: %s\n", ax_name);
                g_free (ax_name);
        }

	if (gtk_tree_selection_count_selected_rows (selection) ) {
		GList * selected_tree_path = gtk_tree_selection_get_selected_rows (selection, &model);
		for (GList * gl = selected_tree_path; gl; gl=gl->next) {
			//GtkTreeRowReference * row_ref = gtk_tree_row_reference_new (model, GtkTreePath (gl->data));
			int arr_sz = 0;
			gint * indices = gtk_tree_path_get_indices_with_depth ( (GtkTreePath *) gl->data, &arr_sz);
			cout << "arr_sz:" << arr_sz << endl;
			for (int i=0; i < arr_sz; ++i) {
				cout << "Path: " << indices[i] << endl;
			}
			if (gtk_tree_model_get_iter (model, &iter, (GtkTreePath *) gl->data)) {
				gtk_tree_model_get (model, &iter, AXIS_COLUMN, &ax_name, -1);
				g_print ("You selected axis: %s\n", ax_name);
			}
		}
	}
	*/

}

