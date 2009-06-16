/* tree.h
 *
 * grammar parse tree construction functions
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
 * the Free Software Foundation; version 2
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

#ifndef __NxD_TREE_H
#define __NxD_TREE_H

#include <cstdlib>

#include "utils.h"

#include "symtab.h"
bool is_of_int_type(DataType dt);
#include <string>
using std::string;
void print_err(compiler_err_category cmp_err, 
		string err_msg, int line_no, int compiler_line_no, string compiler_file_name);

extern noun_list_type noun_list[];
DataType lcm_type(DataType d1, DataType d2);



struct FunctionArgument {
	struct expr* e;
	char * text;
	struct FunctionArgument * prev_;
	struct FunctionArgument * next_;
};

DataType arr_deref_type(DataType d1);

//struct expr * new_expr();

#include <string>
struct FunctionParameter {
	DataType var_type;
	string var_name;
	int arr_len;
	struct FunctionParameter * prev_, *next_;
	FunctionParameter(DataType type, char * name);
	FunctionParameter(DataType type, char * name, int len); 

	void print(FILE * edit_out);

	~FunctionParameter();
	private:
		FunctionParameter& operator=(const FunctionParameter&);
		FunctionParameter(const FunctionParameter&);
	
};

#include <cstdlib>

#include "scope.h"




struct mem_addr_tab{
	void * mem_ptr;
	int line_number;
	string src_file;
	int src_file_line_no;
	mem_addr_tab(void * ptr, int line): mem_ptr(ptr), line_number(line), src_file(""), src_file_line_no(-1){}
	mem_addr_tab(void * ptr, int line, string l_src_file, int l_src_file_line_no): mem_ptr(ptr), line_number(line), src_file(l_src_file), src_file_line_no(l_src_file_line_no){}
};
void mem_log(void * ptr, int compiler_src_line_no, const char* compiler_src_fname,
                int input_prog_line_no);

//extern struct stmt * tree_root;

bool 	void_check( DataType & type1, DataType & type2, DataType& result_type);



#endif /* __NxD_TREE_H */
