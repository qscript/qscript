/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/utils.C
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#include "utils.h"
#include "symtab.h"
#include "scope.h"
//#include "Tab.h"
#include "expr.h"
#include "stmt.h"
#include "qscript_parser.h"

using qscript_parser::active_scope;
using qscript_parser::active_scope_list;
using qscript_parser::no_errors;
using qscript_parser::func_info_table;
using qscript_parser::line_no;
using std::cout;
using std::cerr;
using std::endl;
//extern vector<mem_addr_tab>  mem_addr;
//extern int rec_len;
//extern struct stmt * tree_root;
//void flex_finish();
//extern vector <scope*> active_scope_list;
//extern scope* active_scope;
//extern vector <func_info*> func_info_table;

#include <string>
using std::string;
void print_err(compiler_err_category cmp_err, string err_msg, 
	int line_no, int compiler_line_no, string compiler_file_name);

bool check_type_compat(datatype typ1, datatype typ2){
	//cout << "check_type_compat: line_no: I have to convert the below code into a function:"  << line_no << endl;
	datatype td1=typ1;
	datatype td2=typ2;
	if(td1==STRING_TYPE && td2==STRING_TYPE){
		return true;
	}
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
}


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
			return sym_it;
		}
	}

	return active_scope->sym_tab.end();
}


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


int check_func_decl_with_func_defn(var_list* & v_list, int & index, string func_name){
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
}


bool 	void_check( datatype & type1, datatype & type2, datatype& result_type){
	if(type1==VOID_TYPE){
		print_err(compiler_sem_err, " lhs of binary expr is of type void ", 
			line_no, __LINE__, __FILE__);
		result_type=ERROR_TYPE;
		++no_errors;
		return false;
	}  else if( type2==VOID_TYPE){
		print_err(compiler_sem_err, " rhs of binary expr is of type void ", 
			line_no, __LINE__, __FILE__);
		result_type=ERROR_TYPE;
		++no_errors;
		return false;
	}
	//if( !(type1==VOID_TYPE && type2==VOID_TYPE))
	else {
		result_type=type1 > type2? type1: type2;
		return true;
	}
	//return true;
}



int lookup_func(string func_name_index){
	for(register unsigned int i=0; i<func_info_table.size(); ++i){
		if(func_name_index==func_info_table[i]->fname){
			return i;
		}
	}
	return -1;
}


#include <string>
using std::string;
void print_err(compiler_err_category cmp_err, string err_msg, 
	int line_no, int compiler_line_no, string compiler_file_name){
	++no_errors;
	cerr << "xtcc " ;
	switch(cmp_err){
		case compiler_syntax_err: 
			cerr << "syntax error: ";
		break;
		case compiler_sem_err:
			cerr << "semantic error: ";
		break;
		case compiler_internal_error:
			cerr << "compiler internal error: " ;
		break;	
		default:
			cerr << "internal compiler error - error code category missing in switch statement: compiler file: " 
				<< __FILE__ << " compiler src code lineno: " << __LINE__ << endl;
			
	}
	cerr << " line_no: " << line_no << " "<< err_msg << ", compiler line_no: " 
		<< compiler_line_no << ", compiler_file_name: " << compiler_file_name << endl;
}
	noun_list_type noun_list[]= {
			{	"void"	, VOID_TYPE},
			{	"int8_t" ,INT8_TYPE},
			{	"int16_t" ,INT16_TYPE},
			{	"int32_t" ,INT32_TYPE},
			{	"float", FLOAT_TYPE},
			{	"double", DOUBLE_TYPE}
		};



datatype lcm_type(datatype d1, datatype d2){
	//cout << "lcm_type: line_no: I have to convert the below code into a function"  << line_no << endl;
	datatype td1=d1, td2=d2;
	//if(td1>=INT8_REF_TYPE && td1<=DOUBLE_REF_TYPE) td1=datatype(INT8_TYPE + d1-INT8_REF_TYPE);
	//if(td2>=INT8_REF_TYPE && td2<=DOUBLE_REF_TYPE) td2=datatype(INT8_TYPE + d2-INT8_REF_TYPE);
	if(d1==STRING_TYPE && d2==STRING_TYPE){
		return STRING_TYPE;
	}
	if(d1==BOOL_TYPE && d2==BOOL_TYPE){
		return BOOL_TYPE;
	}
	td1=convert_ref_type(td1);
	td2=convert_ref_type(td2);
	if(/*(td1>=INT8_TYPE && td1<=DOUBLE_TYPE)*/ is_of_noun_type(td1)&&
		/*(td2>=INT8_TYPE && td2<=DOUBLE_TYPE)*/ is_of_noun_type(td2)){
		if(td1>td2) { return td1;
		} else {
			return td2;
		}
	} else {
		cerr << "lcm_type: error: LHS type d1:" << d1 << " RHS type: d2:" << d2 << endl;
		cerr << "lcm_type: error: LHS type td1:" << td1 << " RHS type: td2:" << td2 << endl;
		++ no_errors;
		return ERROR_TYPE;
	}
}


datatype arr_deref_type(datatype d1){
	if(d1>=INT8_ARR_TYPE && d1<=DOUBLE_ARR_TYPE){
		return datatype(INT8_TYPE+d1-INT8_ARR_TYPE);
	} else if(d1==STRING_ARR_TYPE){
		return STRING_TYPE;
	}
	cerr << "Type Error: lineno: trying to access array with non-integer index" << line_no << "\n";
	++no_errors;
	return ERROR_TYPE;
}

