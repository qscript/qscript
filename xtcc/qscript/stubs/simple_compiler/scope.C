/*
 * scope.C  
 * The main grammar for the xtcc parser
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
 * the Free Software Foundation version 2 
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

#include <sstream>
#include "stmt.h"
#include "expr.h"
#include "scope.h"
#include "tree.h"
#include <string>
//#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include "qscript_parser.h"
using namespace std;

//extern int line_no;
//extern int no_errors;
//extern ofstream debug_log_file;
//extern vector<mem_addr_tab> mem_addr;
using qscript_parser::line_no;
using qscript_parser::no_errors;
using qscript_parser::debug_log_file;
using qscript_parser::mem_addr;


stmt* scope::insert(const char * name, datatype dt/*, int line_no*/){
	// we have to handle a case here where symbol is a function name: - this is not allowed
	decl_stmt * st_ptr=new decl_stmt(dt, line_no);
	if(st_ptr){
	} else {
		cerr << "Memory allocation failed : line_no" << line_no << endl;
		exit(1);
	}
	if ( sym_tab.find(name) == sym_tab.end() ){
		symtab_ent* se=new symtab_ent(name, dt);
		//se->name = strdup(name.c_str());
		//se->type=dt;
		string s(name);
		sym_tab[s] = se;
		st_ptr->type=dt;
		st_ptr->symp=se;
	} else {
		cerr << "ERROR: " << name << " already present in symbol table" << endl;
		st_ptr->type=ERROR_TYPE;
		++no_errors;
	}
	return st_ptr;
}


stmt* scope::insert(const char * name, datatype dt, int arr_size/*, int line_no*/){
	// we have to handle a case here where symbol is a function name: - this is not allowed
	decl_stmt * st_ptr=new decl_stmt(dt, line_no);
	if(st_ptr){
	} else {
		cerr << "Memory allocation failed : line_no" << line_no << endl;
		exit(1);
	}
	if ( sym_tab.find(name) == sym_tab.end() ){
		symtab_ent* se=new symtab_ent(name, dt);
		se->n_elms=arr_size;
		string s(name);
		sym_tab[s] = se;
		st_ptr->type=dt;
		st_ptr->symp=se;
	} else {
		cerr << " array NAME failed:" << line_no << endl;
		cerr << name << " already present in symbol table" << endl;
		st_ptr->type=ERROR_TYPE;
		++no_errors;
	}
	return st_ptr;
}

stmt* scope::insert(const char * name, datatype dt, expr *e){
	// we have to handle a case here where symbol is a function name: - this is not allowed
	decl_stmt * st_ptr=new decl_stmt(dt, line_no);
	if(st_ptr){
	} else {
		cerr << "Memory allocation failed : line_no" << line_no << endl;
		exit(1);
	}
	if ( sym_tab.find(name) == sym_tab.end() ){
		symtab_ent* se=new symtab_ent(name, dt, e);
		if(is_of_noun_type(e->type)){
			if (check_type_compat(dt,e->type)){
				string s(name);
				sym_tab[s] = se;
				st_ptr->type=dt;
				st_ptr->symp=se;
			} else {
				stringstream s;
				s << "Type of variable: " << name << "=" 
					<< human_readable_type(dt)
					<< " in decl cannot handle type of expression on rhs of variable: " 
					<< human_readable_type(e->type) << endl;
				print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
				st_ptr->type=ERROR_TYPE;
			}
		} else {
			stringstream s;
			s << "Error in expression on rhs of variable :" << name << endl;
			print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
			st_ptr->type=ERROR_TYPE;
		}
	} else {
		stringstream s;
		s << "variable " << name << " already present in symbol table" << endl;
		print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		st_ptr->type=ERROR_TYPE;
	}
	return st_ptr;
}


stmt* scope::insert(const char * name, datatype dt, expr *e, type_qualifier tq){
	// we have to handle a case here where symbol is a function name: - this is not allowed
	decl_stmt * st_ptr=new decl_stmt(dt, line_no);
	if(st_ptr){
	} else {
		cerr << "Memory allocation failed : line_no" << line_no << endl;
		exit(1);
	}
	if ( sym_tab.find(name) == sym_tab.end() ){
		symtab_ent* se=new symtab_ent(name, dt, e, tq);
		if(is_of_noun_type(e->type)){
			if (check_type_compat(dt,e->type)){
				string s(name);
				sym_tab[s] = se;
				st_ptr->type=dt;
				st_ptr->symp=se;
			} else {
				stringstream s;
				s << "Type of variable: " << name << "=" 
					<< human_readable_type(dt)
					<< " in decl cannot handle type of expression on rhs of variable: " 
					<< human_readable_type(e->type) << endl;
				print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
				st_ptr->type=ERROR_TYPE;
			}
		} else {
			stringstream s;
			s << "Error in expression on rhs of variable :" << name << endl;
			print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
			st_ptr->type=ERROR_TYPE;
		}
	} else {
		stringstream s;
		s << "variable " << name << " already present in symbol table" << endl;
		print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		st_ptr->type=ERROR_TYPE;
	}
	return st_ptr;
}

stmt* scope::insert(const char * name, datatype dt, int arr_size, /*int line_no, */ char *text){
	// we have to handle a case here where symbol is a function name: - this is not allowed
	if(dt!=INT8_ARR_TYPE){
		stringstream s;
		s << "only INT8_ARR_TYPE: can be assigned a string expression" << endl;
		print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);

	}
	int text_len=0;
	if(text){
		text_len=std::strlen(text);
	}
	if(arr_size<text_len-1) {
		cerr << "length of TEXT < array size line_no:" << line_no << endl;
		++no_errors;
	}
	decl_stmt * st_ptr=new decl_stmt(dt, line_no);
	if(st_ptr){
	} else {
		cerr << "Memory allocation failed : line_no" << line_no << endl;
		exit(1);
	}
	if ( sym_tab.find(name) == sym_tab.end() ){
		symtab_ent* se=new symtab_ent(name, dt);
		se->n_elms=arr_size;
		if(text)
			se->text=strdup(text);
		string s(name);
		sym_tab[s] = se;
		st_ptr->type=dt;
		st_ptr->symp=se;
	} else {
		stringstream s;
		s << " IDENTIFIER: " << name << "  already present in symbol table" << endl;
		print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		st_ptr->type=ERROR_TYPE;
		++no_errors;
	}
	return st_ptr;
}

stmt* scope::insert(const char * name, datatype dt, xtcc_set *lxs){
	decl_stmt * st_ptr=new decl_stmt(dt, line_no);
	if(st_ptr){
	} else {
		cerr << "Memory allocation failed : line_no" << line_no << endl;
		exit(1);
	}
	if ( sym_tab.find(name) == sym_tab.end() ){
		xtcc_set * xs=new xtcc_set(*lxs);
		symtab_ent* se=new symtab_ent(name, dt, xs);
		string s(name);
		sym_tab[s] = se;
		st_ptr->type=dt;
		st_ptr->symp=se;
	} else {
		stringstream s;
		s << " IDENTIFIER: " << name << "  already present in symbol table" << endl;
		print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		st_ptr->type=ERROR_TYPE;
	}
	return st_ptr;
}

scope::~scope() {
	debug_log_file <<"deleting scope" << endl;
	typedef map<string,symtab_ent*>::iterator it;
	for(it p=sym_tab.begin(); p!=sym_tab.end(); ++p){
		delete p->second;
		p->second=0;
	}
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "scope::~scope setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "end deleting scope" << endl;
}

string human_readable_type(datatype dt);
void scope::print_scope(vector<string> &push_stack, vector<string>& pop_stack){
	map<string,symtab_ent*>::iterator it;
	for(it=sym_tab.begin(); it!=sym_tab.end(); ++it){
		symtab_ent * sym_ptr=  it->second;
		/*
		string s = sym_ptr-> name;
		s += " " + human_readable_type(sym_ptr->type);
		*/
		string s("NONE");
		sym_ptr->print_push_stack(s);
		push_stack.push_back(s);
		sym_ptr->print_pop_stack(s);
		pop_stack.push_back(s);
	}
}
