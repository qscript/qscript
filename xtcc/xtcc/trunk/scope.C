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

#include "scope.h"
#include "stmt.h"
#include "tree.h"
#include <string>
#include <cstring>
using namespace std;

extern int line_no;
extern int no_errors;

stmt* scope::insert(char * name, datatype dt, int line_no){
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


stmt* scope::insert(char * name, datatype dt, int arr_size, int line_no){
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


stmt* scope::insert(char * name, datatype dt, int arr_size, int line_no, char *text){
	// we have to handle a case here where symbol is a function name: - this is not allowed
	int text_len=strlen(text);
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
		cout << "char decl:start\n";
		symtab_ent* se=new symtab_ent(name, dt);
		//se->name = strdup(name.c_str());
		//se->type=dt;
		se->n_elms=arr_size;
		se->text=strdup(text);
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
scope::~scope() {
	cout <<"deleting scope" << endl;
	typedef map<string,symtab_ent*>::iterator it;
	for(it p=sym_tab.begin(); p!=sym_tab.end(); ++p){
		//cout << "deleting name: " << p->second->name << " in scope" << endl;
		delete p->second;
		p->second=0;
	}
	cout << "end deleting scope" << endl;
}
