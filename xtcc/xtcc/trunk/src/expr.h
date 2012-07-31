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
#include <iosfwd>
#include <sstream>
#include <map>
//#include "tree.h"
#include "xtcc_set.h"

namespace Expression {

using std::ostringstream;

enum ExpressionOperatorType 
{ 	oper_plus, oper_minus, oper_mult, oper_div
	, oper_and, oper_or, oper_lt, oper_gt
	, oper_le, oper_ge, oper_isneq, oper_iseq
	, oper_parexp, oper_umin, oper_num,  oper_name, oper_arrderef
	, oper_arr2deref, oper_func_call, oper_text_expr
	, oper_float, oper_assgn , oper_not, oper_mod
	, oper_blk_arr_assgn, oper_in, oper_q_expr_in
	, oper_q_expr_arr_in, oper_err
};

struct AbstractExpression {
	ExpressionOperatorType exprOperatorType_;
	DataType type_;
	struct AbstractExpression * next_, *prev_;
	AbstractExpression(ExpressionOperatorType le_type)
		:exprOperatorType_(le_type), type_(ERROR_TYPE)
		 , next_(0), prev_(0) 
	{}
	AbstractExpression(ExpressionOperatorType le_type, DataType ldt)
		:exprOperatorType_(le_type), type_(ldt), next_(0), prev_(0) 
	{}
	virtual void PrintExpressionCode(ostringstream& code_bef_expr
			, ostringstream & code_expr)=0;

	virtual int isvalid();
	virtual bool is_lvalue()=0;
	virtual ~AbstractExpression();
	private:
	AbstractExpression& operator=(const AbstractExpression&);	
	AbstractExpression(const AbstractExpression&);	
};

//extern int no_errors;
//extern int line_no;

struct UnaryExpression : public AbstractExpression
{
	public:
	AbstractExpression* operand_;
	public:
	UnaryExpression( AbstractExpression * l_operand=0
			, ExpressionOperatorType le_type=oper_err);
	bool is_lvalue(){ return false; }
	virtual void PrintExpressionCode(ostringstream& code_bef_expr
			, ostringstream & code_expr);
	virtual ~UnaryExpression();
	private:
	UnaryExpression& operator=(const UnaryExpression&);	
	UnaryExpression(const UnaryExpression&);	
};


#include <vector>
#include <set>
using std::vector;
using std::set;
using std::pair;
//using std::cout;
//using std::cerr;
//using std::endl;
using std::string;
using std::stringstream;

//! holds expressions of the form  a in (1,2,4) - where a can be a varible or an integral expression and the right hand side of operator "in" is a set 
struct Binary2Expression: public AbstractExpression
{
	public:
	AbstractExpression * leftOperand_;
	XtccSet *xs;
	public:
	Binary2Expression(AbstractExpression* llop
			, XtccSet& l_rd, ExpressionOperatorType letype);
	bool is_lvalue(){ return false; }
	virtual void PrintExpressionCode(ostringstream& code_bef_expr
			, ostringstream & code_expr);
	~Binary2Expression();
	private:
	Binary2Expression& operator=(const Binary2Expression&);	
	Binary2Expression(const Binary2Expression&);	
};

//! BinaryExpression holds expressions operated on by binary operators. For example a +b , a-b etc
struct BinaryExpression: public AbstractExpression
{
	public:
	AbstractExpression *leftOperand_, *rightOperand_;
	public:
	BinaryExpression(AbstractExpression* llop
			, AbstractExpression* lrop
			,ExpressionOperatorType letype);
	bool is_lvalue(){ return false; }
	void print_oper_assgn(ostringstream& code_bef_expr
			, ostringstream & code_expr);
	virtual void PrintExpressionCode(ostringstream& code_bef_expr
			, ostringstream & code_expr);
	~BinaryExpression();
	private:
	BinaryExpression& operator=(const BinaryExpression&);	
	BinaryExpression(const BinaryExpression&);	
};


//! Unary2Expression are single operands which have some data attached with them
/*
 Some examples are INUMBER, FNUMBER, NAME, NAME[], NAME[,]
 NAME ( expr_list ) function call, TEXT

*/
struct Unary2Expression : public AbstractExpression
{
	public:
	struct SymbolTableEntry * symbolTableEntry_;
	int isem_value;
	double dsem_value;
	int func_index_in_table;
	char * text;
	int column_no;
	AbstractExpression* operand_;
	AbstractExpression* operand2_;
	public:
	// This is a hack - I have to fix this by putting line number in the base class
	int line_no;
	bool is_lvalue();
	Unary2Expression(ExpressionOperatorType le_type, DataType ldt
		, AbstractExpression* e_list, int lfunc_index_in_table
		, int lline_no);

	Unary2Expression(int l_isem_value);

	Unary2Expression(double l_dsem_value);

	Unary2Expression( struct SymbolTableEntry * lsymp); 
	Unary2Expression(DataType d);
	Unary2Expression(ExpressionOperatorType le_type, string name
			, AbstractExpression* arr_index);
	Unary2Expression(ExpressionOperatorType le_type, string name
			, AbstractExpression* arr_index
			, AbstractExpression* arr_index2);
	Unary2Expression(char* ltxt, ExpressionOperatorType le_type); 
	~Unary2Expression();
	friend void BinaryExpression::print_oper_assgn
		(ostringstream& code_bef_expr, ostringstream & code_expr);
	virtual void PrintExpressionCode(ostringstream& code_bef_expr
			, ostringstream & code_expr);
	private:
	Unary2Expression& operator=(const Unary2Expression&);	
	Unary2Expression(const Unary2Expression&);	
};

void hunt_for_names_in_expression (AbstractExpression *e, std::map<string, SymbolTableEntry*> & name_list );

} /* close namespace Expression */
#endif /* xtcc_expr_h */
