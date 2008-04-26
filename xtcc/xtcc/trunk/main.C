#include <cstdlib>
#include "expr.h"
#include "tree.h"
#include "stmt.h"
#include "Tab.h"
template<class T> T* link_chain(T* & elem1, T* & elem2);
template<class T> T* trav_chain(T* & elem1);
extern vector<table*>	table_list;
extern map <string, ax*> ax_map;
extern vector<mem_addr_tab>  mem_addr;
extern int rec_len;
extern struct stmt * tree_root;
void flex_finish();
extern vector <scope*> active_scope_list;
extern scope* active_scope;
extern vector <func_info*> func_info_table;

extern int errno;
void print_expr(FILE* edit_out, expr * e);

int check_parameters(struct expr* e, struct var_list* v);
bool check_type_compat(datatype typ1, datatype typ2);
int	compile( char * const XTCC_HOME, char * const work_dir);
int	run(char * data_file_name, int rec_len);
void print_table_code(FILE * op, FILE *tab_drv_func, FILE * tab_summ_func);
void print_axis_code(FILE * op, FILE * axes_drv_func);
void clean_up();

void	generate_edit_section_code();

extern void yyrestart ( FILE *input_file );
#include <sys/stat.h>
#include <sys/types.h>
#include <cctype>
#include <fcntl.h>
#include <unistd.h>

fstream debug_log_file("xtcc_debug.log", ios_base::out|ios_base::trunc);
void	print_memory_leaks();
char default_work_dir[]="xtcc_work";
char * work_dir=default_work_dir;
void reset_files();
int main(int argc, char* argv[]/*, char* envp[]*/){
	if(!debug_log_file){
		cerr << "unable to open xtcc_debug.log file for debugging info ... exiting\n";
		exit(1);
	}
	bool exit_flag=false;
	opterr=1;
	int c;
	// temp hack

	while((c=getopt(argc, argv, "w:"))!=-1){
		switch(c){
			case 'w':
				work_dir=optarg;
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
		cout << "Usage: " << argv[0] << " <prog-name> <data-file>" << endl;
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
		
		
	active_scope=new scope();
	active_scope_list.push_back(active_scope);
	//cout << "tree_root: " << tree_root << endl;
	
	/*
	 * Hand install printf -> something like a library function
	 */

	const char * printf_name="printf";
	var_list* v_list=0;
	datatype myreturn_type=INT8_TYPE;
	func_info* fi=new func_info(printf_name, v_list, myreturn_type);
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
	//print_stmt_lst(tree_root);
	struct   stat file_info;
	int xtcc_work_dir_exists=stat(work_dir, &file_info);
	if (xtcc_work_dir_exists==-1){
		cout << "attempting to create directory xtcc_work" << endl;
		// file does not exist - so create the directoryo
		int dir_success=mkdir(work_dir, S_IRUSR| S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP);
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

	fname = string(work_dir)+ ("/my_axes.C");
	FILE * axes_op=fopen(fname.c_str(), "w");	
	fname = string(work_dir) + string("/my_axes_drv_func.C");
	FILE * axes_drv_func=fopen(fname.c_str(), "w");	
	if(!(axes_op&&axes_drv_func)){
		cerr << "Unable to open file for output of axes classes" << endl;
		exit(1);
	}
	if(yyparse()){
		cerr << "parsing axes section failed:" << endl;
		exit(1);
	} else {
		cout <<  "successfully parsed axes section: " << endl;
	}
	flex_finish();
	print_table_code(table_op, tab_drv_func, tab_summ_func);
	print_axis_code(axes_op, axes_drv_func);
	fclose(yyin); yyin=0;
	fclose(table_op);
	fclose(tab_drv_func);
	fclose(axes_op); 
	fclose(axes_drv_func);
	fclose(tab_summ_func);
	bool my_compile_flag=true;
	printf("parsing over\n about to begin compiling\n");
	if(my_compile_flag&&!compile(XTCC_HOME, work_dir)){
		char * endptr=0;
		int convert_to_base=10;
		//int rec_len=strtol(argv[3],&endptr, convert_to_base);
		int rval= run(data_file, rec_len);
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
	cout << "returning from main with errors"<< endl;
	return no_errors;
}


void	print_memory_leaks(){
	fstream mem_leak_log("mem_leak.log", ios_base::out|ios_base::trunc);
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

#include <cstdlib>
#include <cstdio>


void clean_up(){
	debug_log_file << "Entered function clean_up()" << endl;
	typedef map<string, ax*>::iterator ax_map_iter;
	for(ax_map_iter it=ax_map.begin(); it!=ax_map.end(); ++it){
		delete it->second; it->second=0;
	}
	// we should only delete the 0 index scope as this was manually created by us
	if (active_scope_list[0]) {
		delete active_scope_list[0]; active_scope_list[0]=0;
	}

	for(int i=0; i<table_list.size(); ++i){
		delete table_list[i];
	}
	debug_log_file << "Exited function clean_up()" << endl;
			
}

/*
bool check_type_compat(datatype typ1, datatype typ2){
	//cout << "check_type_compat: line_no: I have to convert the below code into a function:"  << line_no << endl;
	datatype td1=typ1;
	datatype td2=typ2;
	if(td1>=INT8_REF_TYPE && td1<=DOUBLE_REF_TYPE) td1=datatype(INT8_TYPE + typ1-INT8_REF_TYPE);
	if(td2>=INT8_REF_TYPE && td2<=DOUBLE_REF_TYPE) td2=datatype(INT8_TYPE + typ2-INT8_REF_TYPE);
	if((td1>=INT8_TYPE&&td1<=DOUBLE_TYPE) &&
			td2>=INT8_TYPE&&td2<=DOUBLE_TYPE){
		if(td1>=td2){
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}*/



int check_parameters(expr* e, var_list* v){
	debug_log_file << "check_parameters: called" << endl;
	expr* e_ptr=e;
	var_list* fparam=v;
	bool match=true;
	/* Important point to note: I am not allowing references in ordinary variable decl
	   Only in function parameter list - the object is to allow modifying of variables
	   in a function as in C++
	   */

	int chk_param_counter=1;
	while (e_ptr && fparam) {
		//e_ptr->print();
		datatype etype=e_ptr->type, fptype=fparam->var_type; 
		if((etype>=INT8_TYPE && etype<=DOUBLE_TYPE) && 
			((fptype>=INT8_TYPE && fptype<=DOUBLE_TYPE)||
			 (fptype>=INT8_REF_TYPE && fptype<=DOUBLE_REF_TYPE))){
			datatype tdt=fptype;
				/* the code below makes a INT8_REF_TYPE -> INT8_TYPE
				   			a INT8_REF_TYPE -> INT8_TYPE
				 thats because we dont care much about references -> C++
				 does all the hard work. For checking types they are equivalent to us
				*/			
			if(tdt>=INT8_REF_TYPE) tdt=datatype(INT8_TYPE+tdt-INT8_REF_TYPE);
			if(etype <= tdt) {
				debug_log_file << "varname: "<< fparam->var_name << " chk_param_counter: " 
					<< chk_param_counter << " passed " << endl;
			}
		} else if ((etype>=INT8_ARR_TYPE&&etype<=DOUBLE_ARR_TYPE)&&
				(fptype>=INT8_ARR_TYPE&&fptype<=DOUBLE_ARR_TYPE)&&
				(etype==fptype)){
			debug_log_file << "varname: "<< fparam->var_name << " chk_param_counter: " 
					<< chk_param_counter << " passed " << endl;
		}else {
			match=false;
			cerr << "Parameter type mismatch name: " << endl;
			cerr << fparam->var_name << " expected type is " << fparam->var_type
				<< " passed type is " << e_ptr->type 
				<< " line_no: " << line_no << " or currently allowed promotion to: " 
				<< e_ptr->type+INT8_REF_TYPE
				<< endl;
			++no_errors;
		}
		e_ptr=e_ptr->next;
		fparam=fparam->next;
		chk_param_counter=chk_param_counter+1;
	}
	if(match==true){
		if(e_ptr==0&& fparam==0){
			match=true;
		} else {
			match=false;
			++no_errors;
			cerr << "NOTMATCHED: No of parameters in function call not matching with no of paramters in expr: line_no"
				<< line_no << endl;
		}
	}
	if(!match) {
		cerr << "function parameter type check FAILURE: line_no " << line_no << endl;
	}
	return match;
}
/*
map<string, symtab_ent*>::iterator find_in_symtab(string id){
	bool found=false;
	int i=active_scope_list.size()-1;
	map<string,symtab_ent*>::iterator sym_it ; 
	for(;i>-1;--i){
		sym_it = active_scope_list[i]->sym_tab.find(id);
		if (sym_it == active_scope_list[i]->sym_tab.end() ){
		} else {
			found = true;
			//cout << "found" << endl;
			break;
		}
	}
	if(found==false){
		return active_scope->sym_tab.end();
	} else {
		return sym_it;
	}
}*/

/* NxD: I need to write a detailed note about this function's responsibilities
   */
   

	bool skip_func_type_check(const char * fname){
		const char * skip_func_type_check_list[] = {"printf" };
		for (unsigned int i=0; i<sizeof(skip_func_type_check_list)/sizeof(skip_func_type_check_list[0]); ++i){
			if(!strcmp(fname, skip_func_type_check_list[i])){
				return true;
			}
		}
		return false;
	}

		


/*

int search_for_func(string& search_for){
	//cout << "Entered search_for_func: " << endl;
	unsigned int i=0;
	
	for (i=0;i<func_info_table.size();++i){
		if(search_for==func_info_table[i]->fname){
			//cout << "search_for_func(): found: " << search_for << " index: " << i << endl;
			return i;
		}
	}
	cout << "search_for_func():not found function: " <<search_for  << endl;
	return -1;
}
*/

/*
int check_func_decl_with_func_defn(var_list* & v_list, int & index, string func_name){
	//cout << "Entered check_func_decl_with_func_defn: " << func_name << endl;
		
	var_list* defn_ptr=v_list;
	var_list* decl_ptr=func_info_table[index]->param_list;
	
	while(defn_ptr&&decl_ptr){
		// I may put a check on the length of the array - but it is not necessary for now I think
		if((defn_ptr->var_type==decl_ptr->var_type)&&
			(defn_ptr->var_name==decl_ptr->var_name)){
		} else {
			++no_errors;
			return 0;
		}
		defn_ptr=defn_ptr->next;
		decl_ptr=decl_ptr->next;
	}
	if(defn_ptr==decl_ptr && decl_ptr==0){
		return 1;
	}else{
		return 0;
	}
}*/

/*
bool 	void_check( datatype & type1, datatype & type2, datatype& result_type){
	if(type1==VOID_TYPE){
		print_err(compiler_sem_err, " lhs of binary expr is of type void ", 
			line_no, __LINE__, __FILE__);
		result_type=ERROR_TYPE;
		++no_errors;
		return false;
	} 
	if( type2==VOID_TYPE){
		print_err(compiler_sem_err, " rhs of binary expr is of type void ", 
			line_no, __LINE__, __FILE__);
		result_type=ERROR_TYPE;
		++no_errors;
		return false;
	}
	if( !(type1==VOID_TYPE && type2==VOID_TYPE)){
		result_type=type1 > type2? type1: type2;
		return true;
	}
	//return true;
}
*/

template<class T> T* link_chain(T* &elem1, T* &elem2){
	elem2->prev=elem1;
	elem1->next=elem2;
	return elem2;
}

template<class T> T* trav_chain(T* & elem1){
	if(elem1){
		while (elem1->prev) elem1=elem1->prev;
		return elem1;
		/*
		while (elem1->exists_next()){
			
		}
		*/
	} else return 0;
}

#include <cstdlib>
int compile(char * const XTCC_HOME, char * const work_dir){
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
	string cmd2=string("g++ ") + work_dir + string("/temp.C -o ") +  work_dir + string("/myedit.exe");
#endif /* GNU/UNIX */	
#if __WIN32__
	string cmd2="\\Borland\\BCC55\\Bin\\bcc32 -P -I\\Borland\\BCC55\\Include -L\\Borland\\BCC55\\LIB -extcc_work\\myedit.exe xtcc_work\\temp.C ";
#endif /* __WIN32__ */	

	rval=system(cmd2.c_str());

	return rval;
}

#include <sstream>
int run(char * data_file_name, int rec_len){
	int rval;
	ostringstream cmd1;
#if	__WIN32__
	cmd1 << "xtcc_work\\myedit.exe " << data_file_name  << " " << rec_len;
#endif /* __WIN32__ */
#if !defined(__WIN32__) && !defined(MAC_TCL) /* GNU/UNIX */
	cmd1 <<  work_dir << "/myedit.exe " << data_file_name  << " " << rec_len;
#endif /* UNIX */
	rval=system(cmd1.str().c_str());
	return rval;
}

/*
int lookup_func(string func_name_index){
	for(register unsigned int i=0; i<func_info_table.size(); ++i){
		if(func_name_index==func_info_table[i]->fname){
			return i;
		}
	}
	return -1;
}
*/




#include <fstream>
void reset_files(){
	ofstream lst_op("lst_.csv", ios_base::out|ios_base::trunc);
	lst_op << endl;
	lst_op.close();
	ofstream tab_op("tab_.csv", ios_base::out|ios_base::trunc);
	tab_op << endl;
	tab_op.close();
}

