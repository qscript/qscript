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
using namespace std;


/*
struct expr * new_expr(){	
	struct expr * e = ((struct expr * ) malloc (sizeof(struct expr)));
	e->l_op = NULL;
	e->r_op = NULL;
	e->symp = NULL;
	e->prev=e->next=NULL;
	e->text=NULL;
	return e;
}
*/



datatype lcm_type(datatype d1, datatype d2){
	cout << "lcm_type: line_no: I have to convert the below code into a function"  << line_no << endl;
	datatype td1=d1, td2=d2;
	if(td1>=U_INT8_REF_TYPE && td1<=DOUBLE_REF_TYPE) td1=datatype(U_INT8_TYPE + d1-U_INT8_REF_TYPE);
	if(td2>=U_INT8_REF_TYPE && td2<=DOUBLE_REF_TYPE) td2=datatype(U_INT8_TYPE + d2-U_INT8_REF_TYPE);

	if((td1>=U_INT8_TYPE && td1<=DOUBLE_TYPE)&&
		(td2>=U_INT8_TYPE && td2<=DOUBLE_TYPE)){
		if(td1>td2) { return td1;
		} else {
			return td2;
		}
	} else {
		cerr << "lcm_type: error" << endl;
		++ no_errors;
		return ERROR_TYPE;
	}



}

datatype arr_deref_type(datatype d1){
	/*
	if(d1==int_arr_type) return int_type;
	if(d1==char_arr_type) return char_type;
	*/
	if(d1>=U_INT8_ARR_TYPE && d1<=DOUBLE_ARR_TYPE){
		return datatype(U_INT8_TYPE+d1-U_INT8_ARR_TYPE);
	}
	cerr << "Type Error: lineno: trying to access array with non-integer index" << line_no << "\n";
	++no_errors;
	return ERROR_TYPE;
}

