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
#include <string>
using namespace std;

extern int line_no;

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
