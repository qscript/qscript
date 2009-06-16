/*
 * The parse tree construction function of the xtcc grammar
 * Copyright (C) 2003,2004, 2005,2006,2007  Neil Xavier D'Souza <nxd_in@yahoo.com>
 * Postal MAil address
 * Neil Xavier D'Souza
 * 502, Premier Park
 * 1st Tank Lane,
 * Orlem, Malad(W),
 * Mumbai India. 400064.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2, 
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * The Free Software Foundation, 
 * 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include "symtab.h"
#include "tree.h"
#include "stmt.h"
#include <iostream>
extern int line_no, no_errors;
#include <fstream>
using std::ofstream;
extern ofstream debug_log_file;


/*
struct expr * new_expr(){	
	struct expr * e = ((struct expr * ) malloc (sizeof(struct expr)));
	e->l_op = NULL;
	e->r_op = NULL;
	e->symp = NULL;
	e->next_=e->prev_=NULL;
	e->text=NULL;
	return e;
}
*/



DataType lcm_type(DataType d1, DataType d2){
	//cout << "lcm_type: line_no: I have to convert the below code into a function"  << line_no << endl;
	DataType td1=d1, td2=d2;
	//if(td1>=INT8_REF_TYPE && td1<=DOUBLE_REF_TYPE) td1=DataType(INT8_TYPE + d1-INT8_REF_TYPE);
	//if(td2>=INT8_REF_TYPE && td2<=DOUBLE_REF_TYPE) td2=DataType(INT8_TYPE + d2-INT8_REF_TYPE);
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

DataType arr_deref_type(DataType d1){
	/*
	if(d1==int_arr_type) return int_type;
	if(d1==char_arr_type) return char_type;
	*/
	if(d1>=INT8_ARR_TYPE && d1<=DOUBLE_ARR_TYPE){
		return DataType(INT8_TYPE+d1-INT8_ARR_TYPE);
	} else if(d1==STRING_ARR_TYPE){
		return STRING_TYPE;
	}
	cerr << "Type Error: lineno: trying to access array with non-integer index" << line_no << "\n";
	++no_errors;
	return ERROR_TYPE;
}
/*
func_info::func_info(string name, struct FunctionParameter* elist, DataType myreturn_type): 
	fname(name), param_list(elist), return_type(myreturn_type), func_body(0), func_scope(0){
	func_scope=new scope();
	struct FunctionParameter* decl_list=elist;
	while(decl_list){
		//cout << " constructing func_info decl list names are: " << decl_list->var_name << endl;
		struct symtab_ent* se=new struct symtab_ent;
		se->name = strdup(decl_list->var_name.c_str());
		se->type=decl_list->var_type;
		func_scope->sym_tab[decl_list->var_name] = se;
		decl_list=decl_list->next_;
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

*/

#include <vector>
using std::vector;
extern vector <mem_addr_tab> mem_addr;
void mem_log(void * ptr, int compiler_src_line_no, const char* compiler_src_fname,
                int input_prog_line_no){
        mem_addr_tab m1(ptr, compiler_src_line_no, compiler_src_fname, input_prog_line_no);
        mem_addr.push_back(m1);
}

#include <sstream>
FunctionParameter::FunctionParameter(DataType type, char * name): 
	var_type(type), var_name(name), arr_len(-1), prev_(NULL), next_(NULL){
	if (!( (type>=INT8_TYPE&& type<=DOUBLE_TYPE) ||
		(type>=INT8_REF_TYPE&& type<=DOUBLE_REF_TYPE))){
		stringstream s;
		s << "SEMANTIC error: only INT8_TYPE ... DOUBLE_TYPE is allowed in decl: "  << var_name<< endl;
		print_err(compiler_sem_err, s.str() , line_no, __LINE__, __FILE__);
		cerr << "NEED TO LINK  BACK TO ERROR: FIX ME" << endl;
	}
	//cout << "constructing FunctionParameter: " << var_name << endl;
}
FunctionParameter::~FunctionParameter(){
	debug_log_file << "deleting ~FunctionParameter: var_name:" << var_name << endl;
	if (next_) { delete next_; next_=0; }
	debug_log_file << "end deleting ~FunctionParameter " << endl;
}


void FunctionParameter::print(FILE * edit_out){
	struct FunctionParameter * vl_ptr=this;
	while(vl_ptr){
		if(vl_ptr->var_type>=INT8_TYPE && vl_ptr->var_type<=DOUBLE_TYPE){
			fprintf(edit_out, "%s %s", noun_list[vl_ptr->var_type].sym,vl_ptr->var_name.c_str());
		} else if (vl_ptr->var_type>=INT8_ARR_TYPE&&vl_ptr->var_type<=DOUBLE_ARR_TYPE){
			DataType tdt=DataType(INT8_TYPE + vl_ptr->var_type-INT8_ARR_TYPE);
			fprintf(edit_out, "%s %s[%d]/* vartype: %d */", noun_list[tdt].sym, vl_ptr->var_name.c_str(), arr_len, vl_ptr->var_type);
		} else if (vl_ptr->var_type>=INT8_REF_TYPE&&vl_ptr->var_type<=DOUBLE_REF_TYPE){
			DataType tdt=DataType(INT8_TYPE + vl_ptr->var_type-INT8_REF_TYPE);
			fprintf(edit_out, "%s & %s", noun_list[tdt].sym, vl_ptr->var_name.c_str());
		} else {
			fprintf(edit_out, "INTERNAL ERROR:Unknown data type: file: %s, line: %d\n", __FILE__, __LINE__);
		}
		vl_ptr=vl_ptr->next_;
		if(vl_ptr) {
			fprintf(edit_out, ",");
		}
	}
}

FunctionParameter::FunctionParameter(DataType type, char * name, int len): var_type(type), var_name(name), arr_len(len), prev_(NULL), next_(NULL){
	if(!is_of_arr_type(type)){
		cerr << "SEMANTIC error: only INT8_ARR_TYPE ... DOUBLE_ARR_TYPE array Types are allowed in decl: " << var_name << endl;
		cerr << "NEED TO LINK  BACK TO ERROR: FIX ME" << endl;
	}
	cout << "constructing FunctionParameter: " << var_name << endl;
}
