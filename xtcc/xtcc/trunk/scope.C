/*
 * Scope.C  
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
 * the Free Software Foundation; either version 2
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

#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "scope.h"
#include "stmt.h"
//#include "tree.h"
#include "debug_mem.h"

using namespace std;

extern int line_no;
extern int no_errors;
extern ofstream debug_log_file;
extern vector<mem_addr_tab> mem_addr;
extern Scope* active_scope;


Statement::AbstractStatement* Scope::insert(const char * name, DataType dt)
{
	// we have to handle a case here where symbol is a function name: - this is not allowed
	Statement::DeclarationStatement * st_ptr=new Statement::DeclarationStatement(dt, line_no);
	if(st_ptr){
	} else {
		cerr << "Memory allocation failed : line_no" << line_no << endl;
		exit(1);
	}
	if ( sym_tab.find(name) == sym_tab.end() ){
		SymbolTableEntry* se=new SymbolTableEntry(name, dt);
		//se->name = strdup(name.c_str());
		//se->type_=dt;
		string s(name);
		sym_tab[s] = se;
		st_ptr->type_=dt;
		st_ptr->symbolTableEntry_=se;
	} else {
		cerr << "ERROR: " << name 
			<< " already present in symbol table" << endl;
		st_ptr->type_=ERROR_TYPE;
		++no_errors;
	}
	return st_ptr;
}


Statement::AbstractStatement* Scope::insert(const char * name, DataType dt, int arr_size)
{
	// we have to handle a case here where symbol is a function name: - this is not allowed
	Statement::DeclarationStatement * st_ptr=new Statement::DeclarationStatement(dt, line_no);
	if(st_ptr){
	} else {
		cerr << "Memory allocation failed : line_no" << line_no << endl;
		exit(1);
	}
	if ( sym_tab.find(name) == sym_tab.end() ){
		SymbolTableEntry* se=new SymbolTableEntry(name, dt);
		se->n_elms=arr_size;
		string s(name);
		sym_tab[s] = se;
		st_ptr->type_=dt;
		st_ptr->symbolTableEntry_=se;
	} else {
		cerr << " array NAME failed:" << line_no << endl;
		cerr << name << " already present in symbol table" << endl;
		st_ptr->type_=ERROR_TYPE;
		++no_errors;
	}
	return st_ptr;
}

Statement::AbstractStatement* Scope::insert(const char * name, DataType dt
		, Expression::AbstractExpression *e)
{
	// we have to handle a case here where symbol is a function name: - this is not allowed
	Statement::DeclarationStatement * st_ptr=new Statement::DeclarationStatement(dt, line_no);
	if(st_ptr){
	} else {
		cerr << "Memory allocation failed : line_no" << line_no << endl;
		exit(1);
	}
	if ( sym_tab.find(name) == sym_tab.end() ){
		SymbolTableEntry* se=new SymbolTableEntry(name, dt, e);
		if(is_of_noun_type(e->type_)){
			if (check_type_compat(dt,e->type_)){
				string s(name);
				sym_tab[s] = se;
				st_ptr->type_=dt;
				st_ptr->symbolTableEntry_=se;
			} else {
				stringstream s;
				s << "Type of variable: " << name << "=" 
					<< human_readable_type(dt)
					<< " in decl cannot handle type of expression on rhs of variable: " 
					<< human_readable_type(e->type_) << endl;
				print_err(compiler_sem_err, s.str(), line_no
						, __LINE__, __FILE__);
				st_ptr->type_=ERROR_TYPE;
			}
		} else {
			stringstream s;
			s << "Error in expression on rhs of variable :" 
				<< name << endl;
			print_err(compiler_sem_err, s.str(), line_no
					, __LINE__, __FILE__);
			st_ptr->type_=ERROR_TYPE;
		}
	} else {
		stringstream s;
		s << "variable " << name 
			<< " already present in symbol table" << endl;
		print_err(compiler_sem_err, s.str(), line_no
				, __LINE__, __FILE__);
		st_ptr->type_=ERROR_TYPE;
	}
	return st_ptr;
}

Statement::AbstractStatement* Scope::insert(const char * name, DataType dt
		, int arr_size,  char *text_)
{
	// we have to handle a case here where symbol is a function name: - this is not allowed
	if(dt!=INT8_ARR_TYPE){
		stringstream s;
		s << "only INT8_ARR_TYPE: can be assigned a string expression" 
			<< endl;
		print_err(compiler_sem_err, s.str(), line_no
				, __LINE__, __FILE__);

	}
	int text_len=0;
	if(text_){
		text_len=strlen(text_);
	}
	if(arr_size<text_len-1) {
		cerr << "length of TEXT < array size line_no:" 
			<< line_no << endl;
		++no_errors;
	}
	Statement::DeclarationStatement * st_ptr=new Statement::DeclarationStatement(dt, line_no);
	if(st_ptr){
	} else {
		cerr << "Memory allocation failed : line_no" << line_no << endl;
		exit(1);
	}
	if ( sym_tab.find(name) == sym_tab.end() ){
		SymbolTableEntry* se=new SymbolTableEntry(name, dt);
		se->n_elms=arr_size;
		if(text_)
			se->text_=strdup(text_);
		string s(name);
		sym_tab[s] = se;
		st_ptr->type_=dt;
		st_ptr->symbolTableEntry_=se;
	} else {
		stringstream s;
		s << " IDENTIFIER: " << name 
			<< "  already present in symbol table" << endl;
		print_err(compiler_sem_err, s.str()
				, line_no, __LINE__, __FILE__);
		st_ptr->type_=ERROR_TYPE;
		++no_errors;
	}
	return st_ptr;
}

Statement::AbstractStatement* Scope::insert(const char * name, DataType dt, XtccSet *lxs)
{
	Statement::DeclarationStatement * st_ptr=new Statement::DeclarationStatement(dt, line_no);
	if(st_ptr){
	} else {
		cerr << "Memory allocation failed : line_no" << line_no << endl;
		exit(1);
	}
	if ( sym_tab.find(name) == sym_tab.end() ){
		XtccSet * xs=new XtccSet(*lxs);
		SymbolTableEntry* se=new SymbolTableEntry(name, dt, xs);
		string s(name);
		sym_tab[s] = se;
		st_ptr->type_=dt;
		st_ptr->symbolTableEntry_=se;
	} else {
		stringstream s;
		s << " IDENTIFIER: " << name 
			<< "  already present in symbol table" << endl;
		print_err(compiler_sem_err, s.str(), line_no
				, __LINE__, __FILE__);
		st_ptr->type_=ERROR_TYPE;
	}
	return st_ptr;
}

Scope::~Scope() 
{
	debug_log_file <<"deleting Scope" << endl;
	typedef map<string,SymbolTableEntry*>::iterator it;
	for(it p=sym_tab.begin(); p!=sym_tab.end(); ++p){
		delete p->second;
		p->second=0;
	}
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "Scope::~Scope setting mem_addr: " 
				<< this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "end deleting Scope" << endl;
}
