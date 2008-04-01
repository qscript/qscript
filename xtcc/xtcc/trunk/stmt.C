#include "symtab.h"
#include "stmt.h"
#include "tree.h"
extern vector<mem_addr_tab> mem_addr;
extern ofstream debug_log_file;
#include <fstream>
#include <iostream>

extern char * work_dir;
stmt::~stmt(){ 
	if (prev /*
		    && !((type==FUNC_DEFN)||(type==FUNC_TYPE))*/ ) {
		delete prev; prev=0;
	} 
	debug_log_file << "stmt::~stmt() base destructor" << std::endl;
}

list_stmt::~list_stmt(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "list_stmt::~list_stmt setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting list_stmt" << endl;
	//if(prev) delete prev;
	//delete se;
}

func_decl_stmt::func_decl_stmt( datatype dtype, int lline_number, char * & name,  var_list* & v_list, datatype return_type)
		:
		stmt(dtype, lline_number), f_ptr(0){
	//cout << "load_func_into_symbol_table : " << "name: " << name << endl;
	if ( active_scope->sym_tab.find(name) == active_scope->sym_tab.end() ){
		//cout << "got func_decl" << endl;
		datatype myreturn_type=return_type;
		func_info* fi=new func_info(name, v_list, myreturn_type);
		func_info_table.push_back(fi);
		type=FUNC_TYPE;
		symtab_ent* se=new symtab_ent;
		if(! se) {
			cerr << "memory allocation error: I will eventually crash :-(" << endl;
		}
		se->name = name;
		string s(name);
		active_scope->sym_tab[s] = se;
		se->type=FUNC_TYPE;
		f_ptr=fi;
		//free(name);
	} else {
		cerr << "Symbol : " << name << " already present in symbol table" << endl;
		cout << "line_no: " << lline_number;
		++no_errors;
		type=ERROR_TYPE;
		free(name);
	}
}

void func_decl_stmt::print_stmt_lst(FILE * & fptr){
	fflush(fptr);
	if(fptr){
		f_ptr->print(fptr);
		if(prev) prev->print_stmt_lst(fptr);
	}
}

func_decl_stmt::~func_decl_stmt(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "func_decl_stmt::~func_decl_stmt setting mem_addr: " << this<< "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting func_decl_stmt: name: "  << f_ptr->fname << endl;
	if (f_ptr) { delete f_ptr; f_ptr=0; }
}

func_stmt:: func_stmt ( datatype dtype, int lline_number, scope * &sc,
		var_list * & v_list,
		stmt* & lfunc_body,
		string func_name,
		datatype lreturn_type
		) : stmt(dtype, lline_number), f_ptr(0), func_body(lfunc_body), return_type(lreturn_type){
	int index=search_for_func(func_name);
	if(index==-1){
		cerr << "function defn without decl: " << func_name << " lline_number: " << lline_number << endl;
		type=ERROR_TYPE;
		++no_errors;
	} else if(check_func_decl_with_func_defn(v_list, index, func_name)){
		if(return_type==func_info_table[index]->return_type){
			type=FUNC_DEFN;
			f_ptr=func_info_table[index];
		} else {
			cerr << "func defn, decl parameter return_types did not match: lline_number: " 
			<< lline_number
			<< endl;
			++no_errors;
			type=ERROR_TYPE;
		}
	} else {
		cerr << "func defn, decl parameter lists did not match: lline_number" 
			<< lline_number
			<< endl;
		++no_errors;
		type=ERROR_TYPE;
	}
}

void func_stmt::print_stmt_lst(FILE * & fptr){
	if(fptr){
		if(f_ptr->return_type >= VOID_TYPE && f_ptr->return_type<=DOUBLE_TYPE){
			fprintf(fptr,"%s ", noun_list[f_ptr->return_type].sym);
		} else {
			fprintf(fptr, "Unxpected return type for function: file: %s, line:%d\n",
					__FILE__, __LINE__ );
		}
		
		if(f_ptr->fname==string("printf")){
			fprintf(fptr, "fprintf(xtcc_stdout,");
		} else {
			fprintf(fptr, "%s/* comment */\n", f_ptr->fname.c_str());
			fprintf(fptr, "(");
		}
		var_list* v_ptr=f_ptr->param_list;
		v_ptr->print(fptr);
		fprintf(fptr, ")");
		if(func_body) func_body->print_stmt_lst(fptr);
		if(prev) prev->print_stmt_lst(fptr);
	}
}


func_stmt::~func_stmt(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "func_stmt::~func_stmt: setting mem_addr=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting func_stmt" << endl;
	if(func_body) {
		delete func_body;
		func_body=0;
	}
}

for_stmt:: ~for_stmt(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "for_stmt::~for_stmt setting mem_addr:" << this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting for_stmt" << endl;
	//if(prev) { delete prev; }
	if(init) {
		delete init;
		init =0;
	}
	if(test) {
		delete test;
		test=0;
	}
	if(incr) {
		delete incr;
		incr=0;
	}
	if(for_body) {
		delete for_body; for_body=0;
	}
}

if_stmt:: ~if_stmt(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
			if(this==mem_addr[i].mem_ptr){
				mem_addr[i].mem_ptr=0;
				debug_log_file << "if_stmt::~if_stmt setting mem_addr:" << this << "=0" << endl;
				break;
			}
		}
	debug_log_file << "deleting if_stmt" << endl;
	//if (prev) delete prev;
	delete condition;
	delete if_body;
	if (else_body) delete else_body;
}


expr_stmt::~expr_stmt() {
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "expr_stmt::~expr_stmt: setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting expr_stmt" << endl;
	//if(prev ) delete prev;
	if (expr) delete expr;
}

void list_stmt::print_stmt_lst(FILE * & fptr){
	fflush(fptr);
	string my_work_dir=string(work_dir)+string("/");

	if(fptr){
		switch(type){
		case LISTA_BASIC_TYPE_STMT:{
			static int counter_number=0;			   
			string fname= my_work_dir+ string("global.C");
			FILE * global_vars=fopen(fname.c_str(), "a+b");
			fname=my_work_dir+ string("print_list_counts.C");
			FILE * print_list_counts=fopen(fname.c_str(), "a+b");
			if(!(global_vars&&print_list_counts)){
				cerr << "Unable to open global.C or print_list_counts.C for append... exiting" << endl;
				exit(1);
			}
			if(se){
				datatype dt=se->get_type();
				if(dt>=INT8_TYPE && dt<=DOUBLE_TYPE){
					fprintf(global_vars, "map<%s,int> list%d;\n", 
							noun_list[dt].sym, counter_number);
					fprintf(fptr, "list%d [%s]++;\n", counter_number, se->name);
					fprintf(print_list_counts, "print_list_summ(list%d );\n", counter_number);
				}

				++counter_number;
			}
			fclose(global_vars);
			fclose(print_list_counts);
		}
		break;
		case LISTA_BASIC_ARRTYPE_STMT_1INDEX:{
			static int counter_number=0;			   
			//FILE * global_vars=fopen("xtcc_work/global.C", "a+b");
			//FILE * print_list_counts=fopen("xtcc_work/print_list_counts.C", "a+b");
			string fname= my_work_dir+ string("global.C");
			FILE * global_vars=fopen(fname.c_str(), "a+b");
			fname=my_work_dir+ string("print_list_counts.C");
			FILE * print_list_counts=fopen(fname.c_str(), "a+b");
			if(!global_vars){
				cerr << "Unable to open global.C for append" << endl;
			}
			if(se){
				datatype dt=se->get_type();
				if(dt>=INT8_ARR_TYPE&& dt<=DOUBLE_ARR_TYPE){
					fprintf(global_vars, "map<%s,int> list%d;\n", 
							noun_list[dt].sym, counter_number);
					fprintf(fptr, "list1_%d [%s[%d]]++;\n", counter_number, se->name,
							arr_start);
					fprintf(print_list_counts, "print_list_summ(list%d );\n", counter_number);
				}
				++counter_number;
			}
			fclose(global_vars);
			fclose(print_list_counts);
		}
		break;
		case LISTA_BASIC_ARRTYPE_STMT_2INDEX:{
			static int counter_number=0;			   
			//FILE * global_vars=fopen("xtcc_work/global.C", "a+b");
			//FILE * print_list_counts=fopen("xtcc_work/print_list_counts.C", "a+b");
			string fname= my_work_dir+ string("global.C");
			FILE * global_vars=fopen(fname.c_str(), "a+b");
			fname=my_work_dir+ string("print_list_counts.C");
			FILE * print_list_counts=fopen(fname.c_str(), "a+b");
			if(!global_vars){
				cerr << "Unable to open global.C for append" << endl;
			}
			if(se){
				datatype dt=se->get_type();
				switch(dt){
				case INT8_ARR_TYPE:	
					{
					fprintf(global_vars, "map<%s,int> list2_%d;\n", 
							noun_list[dt].sym, counter_number);
					fprintf(fptr, "list2_%d [%s[%d]]++;\n", counter_number, se->name,
							arr_start);
					fprintf(print_list_counts, "print_list_summ(list2_%d );\n", counter_number);
					}
				break;		      
				default:
					++no_errors;
				}
				++counter_number;
			}
			fclose(print_list_counts);
			fclose(global_vars);
		}
		default:
			fprintf(fptr, "Unhandled lista statement: \n");	
		}
		if(prev) prev->print_stmt_lst(fptr);

	}
}

cmpd_stmt::~cmpd_stmt() {
	debug_log_file << "deleting cmpd_stmt" << endl;
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "basic_count_ax_stmt::~basic_count_ax_stmt setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	//if(prev) delete prev;
	if(sc&&flag_cmpd_stmt_is_a_func_body<0) {
		delete sc;
		sc=0;
	}
	if(cmpd_bdy /*&& flag_cmpd_stmt_is_a_func_body<0*/){
		delete cmpd_bdy;
		cmpd_bdy=0;
	}
}

decl_stmt::~decl_stmt(){ 
	debug_log_file << "deleting decl_stmt" << endl;
	//if(symp) { delete symp; symp=0; }
}
