/* AbstractExpression.h
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
#include <iosfwd>
#include <sstream>

using std::ostringstream;

enum e_operator_type 
{ oper_plus, oper_minus, oper_mult, oper_div
	, oper_and, oper_or, oper_lt, oper_gt
	, oper_le, oper_ge, oper_isneq, oper_iseq
	, oper_parexp, oper_umin, oper_num,  oper_name, oper_arrderef
	, oper_arr2deref, oper_func_call, oper_text_expr
	, oper_float, oper_assgn , oper_not, oper_mod
	, oper_blk_arr_assgn, oper_in, oper_q_expr_in
	, oper_q_expr_arr_in, oper_err
};

struct AbstractExpression {
	e_operator_type e_type;
	DataType type;
	struct AbstractExpression * next_, *prev_;
	AbstractExpression(e_operator_type le_type):e_type(le_type), type(ERROR_TYPE), next_(0), prev_(0) { }
	AbstractExpression(e_operator_type le_type, DataType ldt):e_type(le_type), type(ldt), next_(0), prev_(0) 
	{}
	//virtual void print_expr(FILE * edit_out)=0;
	virtual void print_expr(ostringstream& code_bef_expr, ostringstream & code_expr)=0;

	virtual int isvalid();
	virtual bool is_lvalue()=0;
	virtual ~AbstractExpression();
};

extern int no_errors;
extern int line_no;

struct un_expr : public AbstractExpression{
	protected:
	AbstractExpression* operand;
	public:
	un_expr( AbstractExpression * l_operand=0, e_operator_type le_type=oper_err);
	bool is_lvalue(){ return false; }
	//void print_expr(FILE * edit_out);
	virtual void print_expr(ostringstream& code_bef_expr, ostringstream & code_expr);
	virtual ~un_expr();
};

//extern vector <func_info*> func_info_table;

#include <vector>
#include <set>
//using namespace std;
using std::vector;
using std::set;
using std::pair;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::stringstream;

struct xtcc_set {
	vector < pair<int,int> > range;
	set<int> indiv;
	xtcc_set(DataType dt, string name, xtcc_set& xs1);
	xtcc_set(xtcc_set& xs1);
	xtcc_set& operator=(const xtcc_set& xs1);
	xtcc_set();
	void reset();
	void add_range(int n1, int n2);
	void add_indiv(int n1);
};

struct bin2_expr: public AbstractExpression{
	protected:
	//SymbolTableEntry *l_symp, *r_symp;
	AbstractExpression * l_op;
	xtcc_set *xs;
	public:
	//bin2_expr(string lname , string rname ,e_operator_type letype);
	bin2_expr(AbstractExpression* llop, xtcc_set& l_rd, e_operator_type letype);
	bool is_lvalue(){ return false; }
	//void print_oper_assgn(FILE * edit_out);
	//void print_expr(FILE * edit_out);
	virtual void print_expr(ostringstream& code_bef_expr, ostringstream & code_expr);
	~bin2_expr();
};

struct bin_expr: public AbstractExpression{
	protected:
	AbstractExpression *l_op, *r_op;
	public:
	bin_expr(AbstractExpression* llop, AbstractExpression* lrop,e_operator_type letype);
	bool is_lvalue(){ return false; }
	//void print_oper_assgn(FILE * edit_out);
	void print_oper_assgn(ostringstream& code_bef_expr, ostringstream & code_expr);
	//void print_expr(FILE * edit_out);
	virtual void print_expr(ostringstream& code_bef_expr, ostringstream & code_expr);
	~bin_expr();
};


struct un2_expr : public AbstractExpression{
	protected:
	struct SymbolTableEntry * symp;
	int isem_value;
	double dsem_value;
	int func_index_in_table;
	char * text;
	int column_no;
	AbstractExpression* operand;
	AbstractExpression* operand2;
	public:
	// This is a hack - I have to fix this by putting line number in the base class
	int line_no;
	bool is_lvalue();
	un2_expr(e_operator_type le_type, DataType ldt, AbstractExpression* e_list, int lfunc_index_in_table, int lline_no);

	un2_expr(int l_isem_value);

	un2_expr(double l_dsem_value);

	un2_expr( struct SymbolTableEntry * lsymp); 
	un2_expr(DataType d);
	un2_expr(e_operator_type le_type, /*DataType dt, struct SymbolTableEntry * lsymp,*/ string name, AbstractExpression* arr_index);
	un2_expr(e_operator_type le_type, /*DataType dt, struct SymbolTableEntry * lsymp, */ string name,  AbstractExpression* arr_index, AbstractExpression* arr_index2);
	un2_expr(char* ltxt, e_operator_type le_type); 
	~un2_expr();
	//friend void bin_expr::print_oper_assgn(FILE* edit_out);
	friend void bin_expr::print_oper_assgn(ostringstream& code_bef_expr, ostringstream & code_expr);
	//void print_expr(FILE * edit_out);
	virtual void print_expr(ostringstream& code_bef_expr, ostringstream & code_expr);
};


#endif /* xtcc_expr_h */
