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

#ifndef __NxD_TREE_H
#define __NxD_TREE_H

#include <cstdlib>

//enum compiler_err_category{compiler_syntax_err, compiler_sem_err, compiler_internal_error};
#include "utils.h"
/*
enum e_operator_type { oper_plus, oper_minus, oper_mult, oper_div, oper_and, oper_or, oper_lt, oper_gt,
		oper_le, oper_ge, oper_isneq, oper_iseq, oper_parexp, oper_umin, oper_num,  oper_name, oper_arrderef,
		oper_arr2deref, oper_func_call, oper_text_expr, oper_float, oper_assgn , oper_not, oper_mod,
		oper_blk_arr_assgn,
		oper_err
	};
	*/

#include "symtab.h"
bool is_of_int_type(datatype dt);
#include <string>
using std::string;
void print_err(compiler_err_category cmp_err, 
		string err_msg, int line_no, int compiler_line_no, string compiler_file_name);

extern noun_list_type noun_list[];
datatype lcm_type(datatype d1, datatype d2);


//struct expr;
/*

struct expr{
	datatype type;
	struct expr * l_op;
	struct expr * r_op;
	e_operator_type e_operator;
	struct symtab_ent * symp;
	int line_number;
	int isem_value;
	double dsem_value;
	int column_no;
	int column_no_2;
	struct expr * next, *prev;
	int func_index_in_table;
	char * text;
	datatype get_type();
	int isvalid();
	expr( expr* left, expr* right, e_operator_type eop):
		type(uninit), 
		l_op(left), r_op(right), e_operator(eop),
		symp(0), line_number(-1), isem_value(0),dsem_value(0),column_no(-1), column_no_2(-1),
		next(0), prev(0), func_index_in_table(-1), text(0)
	{
		type=lcm_type(l_op->type, r_op->type);
	}
	private:
	expr& operator=(const expr&);	
	expr(const expr&);	
};

*/

struct param {
	struct expr* e;
	char * text;
	struct param * prev;
	struct param * next;
};

datatype arr_deref_type(datatype d1);

//struct expr * new_expr();

#include <string>
using namespace std;
struct var_list {
	datatype var_type;
	string var_name;
	int arr_len;
	struct var_list * prev, *next;
	var_list(datatype type, char * name);
	var_list(datatype type, char * name, int len); 

	void print(FILE * edit_out);

	~var_list();
	private:
		var_list& operator=(const var_list&);
		var_list(const var_list&);
	
};

#include <cstdlib>

/*
 * The func_info constructor adds the names of the function parameters into its scope.
 * When a compound statement is parsed : it checks for the flag_cmpd_stmt_is_a_func_body and
 * loads that into the active scope if set.
 * Note that flag_cmpd_stmt_is_a_func_body is initialized to -1 as the 1st function 
 * will be in index 0 of func_info_table vector.
 * Also lookup_func searches the func_info_table for the function name and returns -1 on failure
 * this is naturally compatible with the initial value of flag_cmpd_stmt_is_a_func_body
 * if the flag is not set -> we need to allocate a new scope - else we will crash
 */
#include "scope.h"
/*
struct func_info;
//#include "stmt.h"
struct stmt;
struct func_info{
	string fname;
	struct var_list * param_list;
	datatype return_type;
	struct stmt * func_body;
	struct scope * func_scope;
	func_info(string name, struct var_list* elist, datatype myreturn_type); 
	void print(FILE * fptr);
	~func_info();
private:
	func_info& operator=(const func_info&);
	func_info(const func_info&);
};*/




//extern void print_expr(struct expr * e);
//extern void print_stmt_lst(struct stmt * st);
//extern void print_inp_prog(struct stmt * st);
//void print_expr(FILE* edit_out, struct expr * e);
#include "debug_mem.h" 

//extern struct stmt * tree_root;

//bool 	void_check( datatype & type1, datatype & type2, datatype& result_type);



#endif /* __NxD_TREE_H */
