/*
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

#ifndef __SCOPE_H
#define __SCOPE_H

#include <map>
#include <string>

//#include "defs.h"
#include <iostream>
#include <vector>

struct stmt;
using namespace std;

	struct scope;
	//extern vector<scope*> active_scope_list;

#include "symtab.h"

	struct scope{
		map<string,symtab_ent*> sym_tab;
		scope()	{
			//cout << " constructing scope(): this: " << this << endl;
		}
		stmt* insert(string name, datatype dt, int line_no);
		stmt* insert(string name, datatype dt, int arr_size, int line_no);
		stmt* insert(string name, datatype dt, int arr_size, int line_no, char *text);
	};

#endif /* __SCOPE_H */
