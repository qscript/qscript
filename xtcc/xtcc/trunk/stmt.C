#include "symtab.h"
#include "stmt.h"
#include "tree.h"
extern vector<mem_addr_tab> mem_addr;
extern vector <func_info*> func_info_table;
extern ofstream debug_log_file;
extern int if_line_no;
#include <fstream>
#include <iostream>

extern char * work_dir;
stmt::~stmt(){ 
	if (next /*
		    && !((type==FUNC_DEFN)||(type==FUNC_TYPE))*/ ) {
		delete next; next=0;
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
	//if(next) delete next;
	//delete se;
}

#include <sstream>
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
		stringstream s;
		s << "Function  Name : " << name << " already present in symbol table." << endl;
		print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		type=ERROR_TYPE;
		free(name);
	}
}

void func_decl_stmt::print_stmt_lst(FILE * & fptr){
	fflush(fptr);
	if(fptr){
		f_ptr->print(fptr);
		if(next) next->print_stmt_lst(fptr);
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
			stringstream s;
			s << "func defn, decl parameter return_types did not match: function name: " << func_name;
			print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
			type=ERROR_TYPE;
		}
	} else {
		stringstream s;
		s << "func defn, decl parameter return_types did not match: function name: " << func_name;
		print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
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
		if(next) next->print_stmt_lst(fptr);
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
	//if(next) { delete next; }
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
	//if (next) delete next;
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
	//if(next ) delete next;
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
				if(/*dt>=INT8_TYPE && dt<=DOUBLE_TYPE*/
					is_of_noun_type(dt) || is_of_noun_ref_type(dt)){
					fprintf(global_vars, "map<%s,int> list%d;\n", 
							noun_list[dt].sym, counter_number);
					fprintf(fptr, "list%d [%s]++;\n", counter_number, se->name);
					fprintf(print_list_counts, "print_list_summ(list%d, string(\"%s\"), string(%s) );\n", 
						counter_number, se->name, list_text.c_str());
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
					fprintf(global_vars, "map<%s,int> list1_%d;\n", 
							noun_list[dt].sym, counter_number);
					fprintf(fptr, "list1_%d [%s[", counter_number, se->name);
					arr_start->print_expr(fptr);
					fprintf(fptr, "]]++;\n");
					fprintf(print_list_counts, "print_list_summ(list1_%d, string(\"%s\"), string(%s) );\n", 
						counter_number, se->name, list_text.c_str());
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
					/*fprintf(fptr, "list2_%d [%s[%d]]++;\n", counter_number, se->name,
							arr_start);
					fprintf(print_list_counts, "print_list_summ(list2_%d );\n", counter_number);
					*/
					fprintf(print_list_counts, "printf(\"LISTA_BASIC_ARRTYPE_STMT_2INDEX: to be implemented\");\\n\n");

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
		if(next) next->print_stmt_lst(fptr);

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
	//if(next) delete next;
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

if_stmt::if_stmt( datatype dtype, int lline_number, 
		struct  expr * lcondition, struct  stmt * lif_body, struct stmt * lelse_body): 
		stmt(dtype, lline_number),
		condition(lcondition), if_body(lif_body), else_body(lelse_body)
{
	if(lcondition->type==VOID_TYPE || lcondition->type==ERROR_TYPE){
		print_err(compiler_sem_err, "If condition expression has Void or Error Type", if_line_no, __LINE__, __FILE__);
	} else {
	}
}


for_stmt::for_stmt(datatype dtype, int lline_number, expr* l_init, expr* l_test, expr* l_incr, stmt * lfor_body):
	stmt(dtype, lline_number), init(l_init), test(l_test), incr(l_incr),  for_body(lfor_body)
{
	if(init->type==VOID_TYPE||test->type==VOID_TYPE||incr->type==VOID_TYPE ){
		print_err(compiler_sem_err, "For condition expression has Void or Error Type", line_no, __LINE__, __FILE__);
		type=ERROR_TYPE;
	} 
}


list_stmt::list_stmt( datatype dtype, string name,
		string llist_text,
		expr*  l_arr_start, 
		expr* l_arr_end
		):
		stmt(dtype, line_no), 
		se(0), list_text(llist_text), arr_start(l_arr_start), arr_end(l_arr_end)
{
		map<string,symtab_ent*>::iterator sym_it = find_in_symtab(name);
		if(sym_it==active_scope->sym_tab.end() ){
			stringstream s;
			s << "list_stmt:  statement symbol: " << name << " not found in symbol table" << endl;
			print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		} else {
			se=sym_it->second;
			datatype name_type=se->type;
			if( !(is_of_noun_type(name_type)|| is_of_noun_ref_type(name_type))
				/*!(name_type>=INT8_TYPE&&name_type<=DOUBLE_TYPE)*/){
				stringstream s;
				s << "list_stmt NAME: "<< name 
					<< " should be of basic type or basic reference types: " << line_no << endl;
				print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
				type = ERROR_TYPE;
			} 
		}
		if(arr_start){
			if(! is_of_int_type( arr_start->type) ){
				type=ERROR_TYPE;
				stringstream s;
				s << "list_stmt NAME: "<< name 
					<< " array index should be of INT type: " << line_no << endl;
				print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);

			}
		} 
		if(arr_end){
			if(! is_of_int_type( arr_end->type) ){
				type=ERROR_TYPE;
				stringstream s;
				s << "list_stmt NAME: "<< name 
					<< " array index 2 should be of INT type: " << line_no << endl;
				print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
			}
		}
	}

fld_stmt::fld_stmt(string lhs_name, string rhs_name, expr* l_s, expr* l_e, int l_w):
	lsymp(0), rsymp(0), start_col(l_s), end_col(l_e), width(l_w)
{
	map<string,symtab_ent*>::iterator sym_it1 = find_in_symtab(lhs_name);
	map<string,symtab_ent*>::iterator sym_it2 = find_in_symtab(rhs_name);
	if(!(is_of_int_type(start_col->type)/*	(start_col->type>=INT8_TYPE && start_col->type<=INT32_TYPE)*/&&
		is_of_int_type(end_col->type) /* (end_col->type>=INT8_TYPE && end_col->type<=INT32_TYPE)*/) ){
		print_err(compiler_sem_err, "fld_stmt: start col and end col expressions must be of integer type", 
				line_no, __LINE__, __FILE__);
	} else if(sym_it1==active_scope->sym_tab.end()){
		stringstream s;
		s <<  "Error: could not find:" << lhs_name <<"  in symbol table: lineno: " << line_no << "\n";
		print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
	} else if (sym_it2==active_scope->sym_tab.end()){
		stringstream s;
		s <<  "Error: could not find:" << rhs_name <<"  in symbol table: lineno: " << line_no << "\n";
		print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
	} else {
		lsymp = sym_it1->second;
		rsymp = sym_it2->second;
		// first some validation checks
		//datatype type1 = sym_it1->type;
		if( !( 
			(sym_it1->second->type == INT32_ARR_TYPE) &&
			(sym_it2->second->type >= INT8_ARR_TYPE) &&
			(sym_it2->second->type <= INT32_ARR_TYPE)) ) {
			stringstream s;
			s << " lhs name should be an array of type int32_t and rhs name should be an integer array ";
			print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);

		} else if (!(width==sizeof(INT8_TYPE) || width==sizeof(INT16_TYPE)
				||width==sizeof(INT32_TYPE))	){
			stringstream s;
			s << "fld_stmt width error: width of field can only be : " 
				<< sizeof(int8_t) << " or " << sizeof(int16_t) << " or "
				<< sizeof(int32_t) << endl;
			print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		} else {
			//everything is ok
		}
	}
}

func_info::func_info(string name, struct var_list* elist, datatype myreturn_type): 
	fname(name), param_list(elist), return_type(myreturn_type), func_body(0), func_scope(0){
	func_scope=new scope();
	struct var_list* decl_list=elist;
	while(decl_list){
		//cout << " constructing func_info decl list names are: " << decl_list->var_name << endl;
		struct symtab_ent* se=new struct symtab_ent;
		se->name = strdup(decl_list->var_name.c_str());
		se->type=decl_list->var_type;
		func_scope->sym_tab[decl_list->var_name] = se;
		decl_list=decl_list->next;
	}
}

void func_info::print(FILE * fptr){
	if(return_type >=VOID_TYPE && return_type <=DOUBLE_TYPE){
		fprintf(fptr, "%s ", noun_list[return_type].sym );
	} else {
		fprintf(fptr, "Unexpected return type for function\n");
	}
	fprintf(fptr, "%s(", fname.c_str());
	if (param_list) param_list->print(fptr);
	fprintf(fptr, ");\n" );
}

func_info::~func_info(){
	if(param_list) { delete param_list; param_list=0; }
	//if(func_body) { delete func_body; func_body=0; }
	// func_scope was created by in the constructor - so we delete it
	if(func_scope) { delete func_scope; func_scope=0; }
}

