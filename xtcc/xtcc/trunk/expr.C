/*
 * expr.C  
 * expressions in the grammar  
 * Copyright (C) 2003,2004, 2005,2006,2007  Neil Xavier D'Souza <nxd_in@yahoo.com>
 * Postal MAil address:
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

#include "tree.h"
#include <vector>
using namespace std;

extern vector<func_info> func_info_table;

	datatype expr::get_type(){
		/*
		if(type==oper_func_call){
			return func_info_table[index].return_type;
		}
		*/
		return type;
	}

	int expr::isvalid(){
		cout << "isvalid called" << endl;
		if (type==error_type){
			return 0;
		} else return 1;
	}
