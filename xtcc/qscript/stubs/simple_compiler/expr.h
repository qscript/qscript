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


// the user of this enum e_operator_type should not depend on the order in which 
// the elements are defined
enum e_operator_type { oper_plus, oper_minus, oper_mult, oper_div, oper_and, oper_or, oper_lt, oper_gt,
		oper_le, oper_ge, oper_isneq, oper_iseq, oper_parexp, oper_umin, oper_num,  oper_name, oper_arrderef,
		oper_arr2deref, oper_func_call, oper_text_expr, oper_float, oper_assgn , oper_not, oper_mod,
		oper_blk_arr_assgn, oper_in, oper_q_expr_in, oper_q_expr_arr_in,
		oper_err
	};

string human_readable_expr_type( e_operator_type e_type);

struct expr {
	e_operator_type e_type;
	datatype type;
	struct expr * next, *prev;
	expr(e_operator_type le_type):e_type(le_type), type(ERROR_TYPE), next(0), prev(0) { }
	expr(e_operator_type le_type, datatype ldt):e_type(le_type), type(ldt), next(0), prev(0) 
	{}
	//virtual void print_expr(FILE * edit_out)=0;
	virtual void print_expr(ostringstream& code_bef_expr, ostringstream & code_expr)=0;

	virtual int isvalid();
	virtual bool is_lvalue()=0;
	virtual bool is_const()=0;
	virtual bool is_integral_expr()=0;
	virtual ~expr();
	private:
		expr& operator=(const expr&);
		expr (const expr&);
};

extern int no_errors;
extern int line_no;

struct un_expr : public expr{
	protected:
	expr* operand;
	public:
	un_expr( expr * l_operand=0, e_operator_type le_type=oper_err);
	bool is_lvalue(){ return false; }
	//void print_expr(FILE * edit_out);
	virtual void print_expr(ostringstream& code_bef_expr, ostringstream & code_expr);
	virtual ~un_expr();
	virtual bool is_const();
	virtual bool is_integral_expr();
	private:
		un_expr& operator=(const un_expr&);
		un_expr (const un_expr&);
};

//extern vector <func_info*> func_info_table;

#include <vector>
#include <set>
using namespace std;
/*
struct xtcc_set {
	vector < pair<int,int> > range;
	set<int> indiv;
	xtcc_set(datatype dt, string name, xtcc_set& xs1);
	xtcc_set(xtcc_set& xs1);
	xtcc_set& operator=(const xtcc_set& xs1);
	xtcc_set();
	void reset();
	void add_range(int n1, int n2);
	void add_indiv(int n1);
};
*/

#include "xtcc_set.h"
struct un2_expr;
struct bin2_expr: public expr{
	protected:
	//symtab_ent *l_symp, *r_symp;
	//expr * l_op;
	un2_expr * l_op;	
	xtcc_set *xs;
	public:
	//bin2_expr(string lname , string rname ,e_operator_type letype);
	bin2_expr(expr* llop, xtcc_set& l_rd, e_operator_type letype);
	bool is_lvalue(){ return false; }
	virtual bool is_const();
	virtual bool is_integral_expr();
	//void print_oper_assgn(FILE * edit_out);
	//void print_expr(FILE * edit_out);
	virtual void print_expr(ostringstream& code_bef_expr, ostringstream & code_expr);
	~bin2_expr();
	private:
		bin2_expr& operator=(const bin2_expr&);
		bin2_expr (const bin2_expr&);
};

struct bin_expr: public expr{
	public:
	expr *l_op, *r_op;
	public:
	bin_expr(expr* llop, expr* lrop,e_operator_type letype);
	bool is_lvalue(){ return false; }
	//void print_oper_assgn(FILE * edit_out);
	void print_oper_assgn(ostringstream& code_bef_expr, ostringstream & code_expr);
	//void print_expr(FILE * edit_out);
	virtual void print_expr(ostringstream& code_bef_expr, ostringstream & code_expr);
	virtual bool is_const();
	virtual bool is_integral_expr();
	~bin_expr();
	private:
		bin_expr& operator=(const bin_expr&);
		bin_expr (const bin_expr&);
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
	//int line_no;
	bool is_lvalue();
	virtual bool is_const();
	virtual bool is_integral_expr();
	//un2_expr(e_operator_type le_type, datatype ldt, expr* e_list, int lfunc_index_in_table, int lline_no);
	un2_expr(e_operator_type le_type, datatype ldt, expr* e_list, int lfunc_index_in_table);
	const symtab_ent* get_symp_ptr(){
		return (const symtab_ent*) symp;
	}

	un2_expr(int l_isem_value);

	un2_expr(double l_dsem_value);

	un2_expr( struct symtab_ent * lsymp); 
	un2_expr(datatype d);
	un2_expr(e_operator_type le_type, /*datatype dt, struct symtab_ent * lsymp,*/ string name, expr* arr_index);
	un2_expr(e_operator_type le_type, /*datatype dt, struct symtab_ent * lsymp, */ string name,  expr* arr_index, expr* arr_index2);
	un2_expr(char* ltxt, e_operator_type le_type); 
	~un2_expr();
	//friend void bin_expr::print_oper_assgn(FILE* edit_out);
	friend void bin_expr::print_oper_assgn(ostringstream& code_bef_expr, ostringstream & code_expr);
	//void print_expr(FILE * edit_out);
	virtual void print_expr(ostringstream& code_bef_expr, ostringstream & code_expr);
	private:
		un2_expr& operator=(const un2_expr&);
		un2_expr (const un2_expr&);
};


#endif /* xtcc_expr_h */
