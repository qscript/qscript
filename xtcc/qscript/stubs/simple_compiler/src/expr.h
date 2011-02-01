/*!\file
   \brief The classes for the expressions allowed in the qscript grammar
   are contained in this file
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
//#include "tree.h"
#include <sys/types.h>
#include <iosfwd>
#include "symtab.h"
#include "compiled_code.h"
//#include <sstream>
using std::ostringstream;


//! every expression has an operator type - which is one of those below
/*! the user of this enum ExpressionOperatorType should not depend on the order in which
    the elements are defined
*/
enum ExpressionOperatorType
{ 	oper_plus, oper_minus, oper_mult, oper_div
	, oper_and, oper_or, oper_lt, oper_gt
	, oper_le, oper_ge, oper_isneq, oper_iseq, oper_parexp
	, oper_umin, oper_num,  oper_name, oper_arrderef
	, oper_arr2deref, oper_func_call, oper_text_expr
	, oper_float, oper_assgn , oper_not, oper_mod
	, oper_blk_arr_assgn, oper_in, oper_q_expr_in
	, oper_q_expr_arr_in, oper_to_string, oper_err
	};

//! helper function when debugging
using std::string;
string human_readable_expr_type( ExpressionOperatorType e_type);

//!AbstractExpression  Pure virtual base class - all expression classes inherit from this class
/*!
 */
struct AbstractExpression
{
	ExpressionOperatorType exprOperatorType_;
	DataType type_;
	struct AbstractExpression * next_, *prev_;
	AbstractExpression(ExpressionOperatorType le_type);
	AbstractExpression(ExpressionOperatorType le_type, DataType ldt);
	//virtual void PrintExpressionCode(FILE * edit_out)=0;
	//! Pure virtual function. Generates the code for a particular expression.
//	virtual void PrintExpressionCode(ostringstream& code_bef_expr
//			, ostringstream & code_expr)=0;
	virtual void PrintExpressionCode(ExpressionCompiledCode & code)=0;

	virtual int32_t IsValid();
	//! pure virtual function will tell us if an AbstractExpression can appear on the
	//! left side of the assignment operator
	//! of the
	virtual bool IsLValue()=0;
	// ! determines if an expression is a constant value
	virtual bool IsConst()=0;
	// ! determines if an expression is an integral value
	virtual bool IsIntegralExpression()=0;
	virtual ~AbstractExpression();
	private:
		AbstractExpression& operator=(const AbstractExpression&);
		AbstractExpression (const AbstractExpression&);
};


//! holds Unary expressions of the form '-' expression, ! expression,  and '(' expression ')'.
/*! Note that these are expressions constructed
    out of an operator and another expression - there is no additional
    data involved which is what differentiates these from the Unary2Expression
    expressions
*/
struct UnaryExpression : public AbstractExpression
{
	protected:
	AbstractExpression* operand_;
	public:
	UnaryExpression( AbstractExpression * l_operand=0
			, ExpressionOperatorType le_type=oper_err);
	bool IsLValue(){ return false; }
//	virtual void PrintExpressionCode(ostringstream& code_bef_expr
//			, ostringstream & code_expr);
	virtual void PrintExpressionCode(ExpressionCompiledCode & code);
	virtual ~UnaryExpression();
	virtual bool IsConst();
	virtual bool IsIntegralExpression();
	private:
		UnaryExpression& operator=(const UnaryExpression&);
		UnaryExpression (const UnaryExpression&);
};

//extern vector <func_info*> func_info_table;

#include <vector>
#include <set>
//using namespace std;

#include "xtcc_set.h"
struct Unary2Expression;
class AbstractQuestion;

//! holds expressions of the form  a in (1,2,4) - where a can be a varible or an integral expression and the right hand side of operator "in" is a set
struct Binary2Expression: public AbstractExpression
{
	protected:
	Unary2Expression * leftOperand_;
	AbstractExpression * leftOperand2_;
	XtccSet *xs;
	AbstractQuestion * rhsQuestion_;
	public:
	Binary2Expression(AbstractExpression* llop
			  , XtccSet& l_rd, ExpressionOperatorType letype);

	Binary2Expression(AbstractExpression* llop
					     , string name
					     , ExpressionOperatorType letype);
	bool IsLValue(){ return false; }
	virtual bool IsConst();
	virtual bool IsIntegralExpression();
//	virtual void PrintExpressionCode(ostringstream& code_bef_expr
//			, ostringstream & code_expr);
	virtual void PrintExpressionCode(ExpressionCompiledCode & code);
	~Binary2Expression();

	private:
		Binary2Expression& operator=(const Binary2Expression&);
		Binary2Expression (const Binary2Expression&);
		void PrintTemporaryStruct(ExpressionCompiledCode &code);
};

//! BinaryExpression holds expressions operated on by binary operators. For example a +b , a-b etc
struct BinaryExpression: public AbstractExpression
{
	public:
	AbstractExpression *leftOperand_, *rightOperand_;
	public:
	BinaryExpression(AbstractExpression* llop, AbstractExpression* lrop
			 , ExpressionOperatorType letype);
	bool IsLValue(){ return false; }
	void print_oper_assgn(ExpressionCompiledCode &code);
//	virtual void PrintExpressionCode(ostringstream& code_bef_expr
//			, ostringstream & code_expr);
	virtual void PrintExpressionCode(ExpressionCompiledCode & code);
	virtual bool IsConst();
	virtual bool IsIntegralExpression();
	~BinaryExpression();
	private:
		BinaryExpression& operator=(const BinaryExpression&);
		BinaryExpression (const BinaryExpression&);
};

//! Unary2Expression are single operands which have some data attached with them
/*
 Some examples are INUMBER, FNUMBER, NAME, NAME[], NAME[,]
 NAME ( expr_list ) function call, TEXT

*/
struct Unary2Expression : public AbstractExpression
{
	protected:
	public:
	struct SymbolTableEntry * symbolTableEntry_;
	int32_t intSemanticValue_;
	double doubleSemanticValue_;
	int32_t func_index_in_table;
	char * text;
	int32_t column_no;
	AbstractExpression* operand_;
	AbstractExpression* operand2_;
	// This is a hack - I have to fix this by putting line number in the base class
	bool IsLValue();
	virtual bool IsConst();
	virtual bool IsIntegralExpression();
	Unary2Expression(ExpressionOperatorType le_type, DataType ldt
			, AbstractExpression* e_list, int32_t lfunc_index_in_table);
	const SymbolTableEntry* get_symp_ptr()
	{
		return (const SymbolTableEntry*) symbolTableEntry_;
	}

	Unary2Expression(int32_t l_isem_value);

	Unary2Expression(double l_dsem_value);

	Unary2Expression( struct SymbolTableEntry * lsymp);
	Unary2Expression(DataType d);
	Unary2Expression(ExpressionOperatorType le_type,  string name
			, AbstractExpression* arr_index);
	Unary2Expression(ExpressionOperatorType le_type,  string name
			, AbstractExpression* arr_index
			, AbstractExpression* arr_index2);
	Unary2Expression(char* ltxt, ExpressionOperatorType le_type);
	~Unary2Expression();
	friend void BinaryExpression::print_oper_assgn(ExpressionCompiledCode & code);
//	virtual void PrintExpressionCode(ostringstream& code_bef_expr
//			, ostringstream & code_expr);
	virtual void PrintExpressionCode(ExpressionCompiledCode & code);
	private:
		Unary2Expression& operator=(const Unary2Expression&);
		Unary2Expression (const Unary2Expression&);
};


#endif /* xtcc_expr_h */
