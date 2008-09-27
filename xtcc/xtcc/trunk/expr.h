/* expr.h
 *
 * expression for xtcc grammar
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

#ifndef xtcc_expr_h
#define xtcc_expr_h
#include "tree.h"

enum e_operator_type { oper_plus, oper_minus, oper_mult, oper_div, oper_and, oper_or, oper_lt, oper_gt,
		oper_le, oper_ge, oper_isneq, oper_iseq, oper_parexp, oper_umin, oper_num,  oper_name, oper_arrderef,
		oper_arr2deref, oper_func_call, oper_text_expr, oper_float, oper_assgn , oper_not, oper_mod,
		oper_blk_arr_assgn, oper_in, oper_q_expr_in, oper_q_expr_arr_in,
		oper_err
	};

struct expr {
	e_operator_type e_type;
	datatype type;
	struct expr * next, *prev;
	expr(e_operator_type le_type):e_type(le_type), type(ERROR_TYPE), next(0), prev(0) { }
	expr(e_operator_type le_type, datatype ldt):e_type(le_type), type(ldt), next(0), prev(0) 
	{}
	virtual void print_expr(FILE * edit_out)=0;
	virtual int isvalid();
	virtual bool is_lvalue()=0;
	virtual ~expr();
};

extern int no_errors;
extern int line_no;

struct un_expr : public expr{
	protected:
	expr* operand;
	public:
	un_expr( expr * l_operand=0, e_operator_type le_type=oper_err);
	bool is_lvalue(){ return false; }
	void print_expr(FILE * edit_out);
	virtual ~un_expr();
};

//extern vector <func_info*> func_info_table;

struct bin2_expr: public expr{
	protected:
	symtab_ent *l_symp, *r_symp;
	public:
	bin2_expr(string lname , string rname ,e_operator_type letype);
	bool is_lvalue(){ return false; }
	//void print_oper_assgn(FILE * edit_out);
	void print_expr(FILE * edit_out);
	~bin2_expr();
};

struct bin_expr: public expr{
	protected:
	expr *l_op, *r_op;
	public:
	bin_expr(expr* llop, expr* lrop,e_operator_type letype);
	bool is_lvalue(){ return false; }
	void print_oper_assgn(FILE * edit_out);
	void print_expr(FILE * edit_out);
	~bin_expr();
};


struct un2_expr : public expr{
	protected:
	struct symtab_ent * symp;
	int isem_value;
	double dsem_value;
	int func_index_in_table;
	char * text;
	int column_no;
	expr* operand;
	expr* operand2;
	public:
	// This is a hack - I have to fix this by putting line number in the base class
	int line_no;
	bool is_lvalue();
	un2_expr(e_operator_type le_type, datatype ldt, expr* e_list, int lfunc_index_in_table, int lline_no);

	un2_expr(int l_isem_value);

	un2_expr(double l_dsem_value);

	un2_expr( struct symtab_ent * lsymp); 
	un2_expr(datatype d);
	un2_expr(e_operator_type le_type, /*datatype dt, struct symtab_ent * lsymp,*/ string name, expr* arr_index);
	un2_expr(e_operator_type le_type, /*datatype dt, struct symtab_ent * lsymp, */ string name,  expr* arr_index, expr* arr_index2);
	un2_expr(char* ltxt, e_operator_type le_type); 
	~un2_expr();
	friend void bin_expr::print_oper_assgn(FILE* edit_out);
	void print_expr(FILE * edit_out);
};


#include <vector>
#include <set>

struct xtcc_set {
	vector < pair<int,int> > range;
	set<int> indiv;
	xtcc_set(datatype dt, string name, xtcc_set& xs1);
	xtcc_set(xtcc_set& xs1);
	xtcc_set& operator=(const xtcc_set& xs1);
	xtcc_set();
};

#endif /* xtcc_expr_h */
