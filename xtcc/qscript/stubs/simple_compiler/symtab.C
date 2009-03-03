/*
 * symtab.C  
 * The symbol table code for the xtcc compiler
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
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
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
#include "expr.h"
#include <string>
using namespace std;

extern int line_no;
extern ofstream debug_log_file;
/*
stmt* sym_tab::insert(string name, datatype dt){
	// we have to handle a case here where symbol is a function name: - this is not allowed
	struct stmt * st_ptr=new_stmt();
	if(st_ptr){
	} else {
		cerr << "Memory allocation failed : line_no" << line_no << endl;
		exit(1);
	}
	if ( sym_tab.find(name) == sym_tab.end() ){
		cout << "char decl:start\n";
		struct symtab_ent* se=new struct symtab_ent;
		se->name = name;
		se->type=char_type;
		string s(name);
		active_scope->sym_tab[s] = se;
		st_ptr->type=char_type;
		st_ptr->symp=se;
	} else {
		cerr << " CHAR NAME failed:" << line_no << endl;
		cerr << $2 << " already present in symbol table" << endl;
		st_ptr->type=error_type;
		++no_errors;
	}
	return st_ptr;
}
*/
#include <fstream>
using std::endl;
symtab_ent::~symtab_ent(){
	debug_log_file<< "deleting symtab_ent: name: " << name << std::endl;
	if(name&& created_by_me) { free( name); name=0; }
	if(text) { delete text; text=0; }
	if(e) { delete e; e=0; }
	debug_log_file << "FINISHED deleting symtab_ent" << std::endl;
}


bool is_of_int_type(datatype dt){
	return (dt >= INT8_TYPE && dt <=INT32_TYPE);
}
bool is_of_noun_type(datatype dt){
	return (dt >= INT8_TYPE && dt <=DOUBLE_TYPE);
}
bool is_of_noun_ref_type(datatype dt){
	return (dt >= INT8_REF_TYPE && dt <=DOUBLE_REF_TYPE);
}

bool is_of_arr_type(datatype dt){
	return (dt >= INT8_ARR_TYPE && dt <=DOUBLE_ARR_TYPE);
}

datatype convert_ref_type(datatype dt){
	if(dt>=INT8_REF_TYPE && dt<=DOUBLE_REF_TYPE) 
		return datatype(INT8_TYPE + dt-INT8_REF_TYPE);
	else 
		return dt;
}

string human_readable_type(datatype dt){
	string s="UNKNOWN TYPE";
	switch(dt){
		case STRING_TYPE:
			s="STRING_TYPE";
		break;
		case VOID_TYPE:
			s= "VOID_TYPE";
		break;	
		case INT8_TYPE:
			s= "INT8_TYPE";
		break;	
		case INT16_TYPE:
			s = "INT16_TYPE";
		break;
		case INT32_TYPE:
			s = "INT32_TYPE";
		break;	
		case FLOAT_TYPE:
			s = "FLOAT_TYPE";
		break;	
		case DOUBLE_TYPE:
			s = "DOUBLE_TYPE";
		break;	
		case INT8_ARR_TYPE:
			s = "INT8_ARR_TYPE";
		break;	
		case INT16_ARR_TYPE:
			s= "INT16_ARR_TYPE";
		break;	
		case INT32_ARR_TYPE:	
			s="INT32_ARR_TYPE";
		break;	
		case FLOAT_ARR_TYPE:
			s="FLOAT_ARR_TYPE";
		break;	
		case DOUBLE_ARR_TYPE:
			s="DOUBLE_ARR_TYPE";
		break;	
		case INT8_REF_TYPE:
			s="INT8_REF_TYPE";
		break;	
		case INT16_REF_TYPE:
			s="INT16_REF_TYPE";
		break;	
		case INT32_REF_TYPE:
			s="INT32_REF_TYPE";
		break;	
		case FLOAT_REF_TYPE:
			s="FLOAT_REF_TYPE";
		break;	
		case DOUBLE_REF_TYPE:
			s="DOUBLE_REF_TYPE";
		break;	
		case QUESTION_TYPE:
			s="QUESTION_TYPE";
		default:
		;
	}
	return s;
}



symtab_ent::symtab_ent(const char * lname, datatype ldt, xtcc_set * lxs):name(strdup(lname)), dval(0), type(ldt), n_elms(-1), created_by_me(true), e(0)  { 
	xs = new xtcc_set(*lxs);
}

			
bool is_of_int_arr_type(datatype dt){
	return (dt >= INT8_ARR_TYPE && dt <=INT32_ARR_TYPE);
}

bool is_of_int32_arr_type(datatype dt){
	return (dt == INT32_ARR_TYPE);
}

