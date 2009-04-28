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
#include "debug_mem.h"
#include "symtab.h"
#include "tree.h"
#include "stmt.h"
#include <iostream>
//extern int line_no, no_errors;
#include <fstream>
#include "qscript_parser.h"
//extern ofstream debug_log_file;
using qscript_parser::debug_log_file;
using qscript_parser::mem_addr;
using qscript_parser::line_no;
using qscript_parser::no_errors;
using qscript_parser::map_of_active_vars_for_questions;





/*
datatype lcm_type(datatype d1, datatype d2){
	//cout << "lcm_type: line_no: I have to convert the below code into a function"  << line_no << endl;
	datatype td1=d1, td2=d2;
	//if(td1>=INT8_REF_TYPE && td1<=DOUBLE_REF_TYPE) td1=datatype(INT8_TYPE + d1-INT8_REF_TYPE);
	//if(td2>=INT8_REF_TYPE && td2<=DOUBLE_REF_TYPE) td2=datatype(INT8_TYPE + d2-INT8_REF_TYPE);
	if(d1==STRING_TYPE && d2==STRING_TYPE){
		return STRING_TYPE;
	}
	if(d1==BOOL_TYPE && d2==BOOL_TYPE){
		return BOOL_TYPE;
	}
	td1=convert_ref_type(td1);
	td2=convert_ref_type(td2);
	if( is_of_noun_type(td1)&&
		 is_of_noun_type(td2)){
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
*/

/*
datatype arr_deref_type(datatype d1){
	if(d1>=INT8_ARR_TYPE && d1<=DOUBLE_ARR_TYPE){
		return datatype(INT8_TYPE+d1-INT8_ARR_TYPE);
	} else if(d1==STRING_ARR_TYPE){
		return STRING_TYPE;
	}
	cerr << "Type Error: lineno: trying to access array with non-integer index" << line_no << "\n";
	++no_errors;
	return ERROR_TYPE;
}
*/

/*#include <vector>
using std::vector;
extern vector <mem_addr_tab> mem_addr;
void mem_log(void * ptr, int compiler_src_line_no, const char* compiler_src_fname,
                int input_prog_line_no){
        mem_addr_tab m1(ptr, compiler_src_line_no, compiler_src_fname, input_prog_line_no);
        mem_addr.push_back(m1);
}
*/

#include <sstream>
