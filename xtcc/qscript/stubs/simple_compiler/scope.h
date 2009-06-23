/*!\file
   \brief Class implementing the scoping level features of the qscript language


 * scope.h
 *  
 * implementation of scoping rules
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

#ifndef __SCOPE_H
#define __SCOPE_H

#include <map>
#include <string>

//#include "defs.h"
//#include <sstream>
#include <vector>

struct AbstractStatement;
struct AbstractExpression;
using std::vector;
using std::string;
using std::map;

	struct Scope;

#include "symtab.h"

struct Scope
{
	map<string,SymbolTableEntry*> SymbolTable;
	Scope()	{ }
	AbstractStatement* insert(const char * name, DataType dt/*, int line_no*/);
	AbstractStatement* insert(const char * name, DataType dt, AbstractExpression *e);
	AbstractStatement* insert(const char * name, DataType dt, AbstractExpression *e, type_qualifier tq);
	AbstractStatement* insert(const char * name, DataType dt, int arr_size /*, int line_no*/);
	AbstractStatement* insert(const char * name, DataType dt, int arr_size, /*int line_no,*/ char *text);
	AbstractStatement* insert(const char * name, DataType dt, XtccSet *lxs);
	void print_scope(vector<string> &push_stack, vector<string>& pop_stack);
	~Scope();
};

#endif /* __SCOPE_H */
