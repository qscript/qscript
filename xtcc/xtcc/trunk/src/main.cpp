#include <cstdlib>
#include <cstdio>
#include <fstream>
#include "expr.h"
//#include "tree.h"
#include "debug_mem.h"
#include "stmt.h"
#include "Tab.h"
#include "code_output_files.h"

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
void print_table_code(FILE * op, FILE *tab_drv_func, FILE * tab_summ_func);
void print_axis_code(FILE * op, FILE * axes_drv_func);
void clean_up();

void	generate_edit_section_code();
void 	generate_make_file();

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
int main(int argc, char* argv[]/*, char* envp[]*/){
	using std::cout;
	using std::endl;
	using std::cerr;

	if(!debug_log_file){
		cerr << "unable to open xtcc_debug.log file for debugging info ... exiting\n";
		exit(1);
	}
	bool exit_flag=false;
	opterr=1;
	int c;
	// temp hack

	while((c=getopt(argc, argv, "lcw:"))!=-1){
		switch(c){
			case 'w':
				work_dir=optarg;
			break;
			case 'c':
				flag_compile_only = true;
			break;
			case 'l':
				flag_use_clang = true;
			break;
			case '?':
				if (optopt == 'w')
					fprintf (stderr, "Option -%c requires an argument.\n", 
						optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n", 
						optopt);
				exit(1);
			break;	
			default:
				exit(1);
		}
	}
	//printf("work dir set to %s\n", work_dir);


	if(argc-optind<2) {
		cout << "Usage: " << argv[0] << " <prog-name> <data-file>" << endl << endl;
		exit_flag=true;
	}
	char * inp_file = argv[optind++];
	char * data_file = argv[optind];
	cerr << "inp_file: " << inp_file << ", data_file: " << data_file << endl;
	char * XTCC_HOME=getenv("XTCC_HOME");
	if(!XTCC_HOME){
		cout << "Please set environment variable XTCC_HOME." << endl 
			<< "If xtcc was installed in /home/unixuser/xtcc/ In UNIX - bash " << endl
			<< "you would do this as (assume $ as shell prompt):" << endl 
			<< "$export XTCC_HOME=/home/unixuser/xtcc" << endl;
		exit_flag=true;
	}
	if(exit_flag){
		exit(1);
	}
	
	reset_files();
		
		
	active_scope=new Scope();
	active_scope_list.push_back(active_scope);
	//cout << "tree_root: " << tree_root << endl;
	
	/*
	 * Hand install printf -> something like a library function
	 */

	const char * printf_name="printf";
	Statement::FunctionParameter* v_list=0;
	DataType myreturn_type=INT8_TYPE;
	Statement::FunctionInformation* fi=new Statement::FunctionInformation(printf_name, v_list, myreturn_type);
	func_info_table.push_back(fi);
	
	const char *c_arr="c";

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
	print_table_code(table_op, tab_drv_func, tab_summ_func);
	print_axis_code(axes_op, axes_drv_func);
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
	if(flag_compile_only==false && !compile(XTCC_HOME, work_dir)){
		char * endptr=0;
		int convert_to_base=10;
		//int rec_len=strtol(argv[3],&endptr, convert_to_base);
		//bool run_flag=true;
		int rval=0;
		//if(run_flag){
		//if(!flag_compile_only){
			rval= run(data_file, rec_len);
		//}
		if(tree_root) {
			delete tree_root;
			tree_root=0;
		}

		clean_up();
		// fi was allocated by us - the "hand installed printf function"
		delete fi;
		print_memory_leaks();
		cout << "xtcc run complete" << endl;
		return rval;
	}
	cout << "returning from main with errors: "  << no_errors << endl;
	return no_errors;
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
	string cmd1=string("type xtcc_work\\edit_out.c xtcc_work\\my_axes_drv_func.C xtcc_work\\my_tab_drv_func.C ") + string(XTCC_HOME)+ string("\\stubs\\main_loop.C > xtcc_work\\temp.C");
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

