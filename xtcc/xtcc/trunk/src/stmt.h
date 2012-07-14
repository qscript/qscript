/*
 * AbstractStatement.h
 *  
 * implementation of statement handling routines in the xtcc grammar
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
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
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
/* !\file
   \brief The classes for the statements parsed in the input
   	language to the "xtcc" compiler are contained in this file
*/

#ifndef _xtcc_stmt_h
#define _xtcc_stmt_h
#include "scope.h"
#include "expr.h"
#include "utils.h"
#include "code_output_files.h"

#include <cstdio>
#include <cstdlib>
#include <sstream>

#include <map>
using std:: map;
map<string, SymbolTableEntry*>::iterator find_in_symtab(string id);
extern noun_list_type noun_list[];

namespace Statement {


struct FunctionArgument {
	struct expr* e;
	char * text;
	struct FunctionArgument * prev_;
	struct FunctionArgument * next_;
};

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

void PrintExpressionCode(FILE* edit_out, struct AbstractExpression * e);
int check_func_decl_with_func_defn(struct FunctionParameter*& v_list
		, int & index, string func_name);

//!AbstractStatement  Pure virtual base class - all statement classes inherit from this class except for class FunctionInformation
/*!
  All language statements classes are derived from the AbstractStatement class
  the AbstractStatement class - contains members (
  AbstractStatement * prev_, *next_ pointers to chain other statements). 
  It also contains line and filename information 
  about the statement being parsed
*/

struct AbstractStatement
{
	public:
	//! chainers to the previous and next_ statement
	AbstractStatement * prev_;
	AbstractStatement * next_;
	DataType type_;
	int lineNo_;
	virtual void GenerateCode(FILE * & fptr)=0;
	//! Constructor - statement type and line number of the statement in the source code
	AbstractStatement(DataType dtype=ERROR_TYPE, int lline_number=0)
		:prev_(0), next_(0), type_(dtype), lineNo_(lline_number)
	{}
	virtual ~AbstractStatement();
	private:
		AbstractStatement(const AbstractStatement&);
		AbstractStatement& operator=(const AbstractStatement&);
};

//! ForStatement: A parsed for statement in the language becomes an object instanstiation of this class
struct ForStatement: public AbstractStatement
{
	struct Expression::AbstractExpression * initializationExpression_
		, * testExpression_, *incrementExpression_;
	struct AbstractStatement * forBody_;
	ForStatement(DataType dtype, int lline_number
			, Expression::AbstractExpression* l_init
			, Expression::AbstractExpression* l_test
			, Expression::AbstractExpression* l_incr
			, AbstractStatement * lfor_body);
	void GenerateCode(FILE * & fptr);
	virtual ~ForStatement();
	private:
	ForStatement& operator=(const ForStatement&);	
	ForStatement(const ForStatement&);	
};

//! IfStatement if statements in the language become object instantiations of this class
struct IfStatement : public AbstractStatement
{
	protected:
	Expression::AbstractExpression * ifCondition_;
	AbstractStatement * ifBody_;
	AbstractStatement * elseBody_;
	public:
	IfStatement( DataType dtype, int lline_number
		, Expression::AbstractExpression * lcondition, AbstractStatement * lif_body
		, AbstractStatement * lelse_body=0);
	void GenerateCode(FILE * & fptr);
	virtual ~IfStatement();
	private:
	IfStatement& operator=(const IfStatement&);	
	IfStatement(const IfStatement&);	
};

//!ExpressionStatement Parsed expressions statements become object instanstiations of this class
struct ExpressionStatement: public AbstractStatement
{
	struct Expression::AbstractExpression* expression_;
	ExpressionStatement(DataType dtype, int lline_number
			, struct Expression::AbstractExpression* e)
		: AbstractStatement(dtype, lline_number), expression_(e) 
	{}
	void GenerateCode(FILE * & fptr);
	virtual ~ExpressionStatement();
	private:
	ExpressionStatement& operator=(const ExpressionStatement&);	
	ExpressionStatement(const ExpressionStatement&);	
};

struct ErrorStatement: public AbstractStatement
{
	ErrorStatement( int lline_number)
		: AbstractStatement(ERROR_TYPE, lline_number)
	{}
	void GenerateCode(FILE * & fptr);
	private:
	ErrorStatement& operator=(const ErrorStatement&);	
	ErrorStatement(const ErrorStatement&);	
};

struct CompoundStatement: public AbstractStatement
{
	AbstractStatement* compoundBody_;
	Scope * scope_;
	int flagIsFunctionBody_;
	public:
	CompoundStatement(DataType dtype, int lline_number
			, int l_flag_cmpd_stmt_is_a_func_body)
		: AbstractStatement(dtype, lline_number), compoundBody_(0)
		, scope_(0)
		, flagIsFunctionBody_(l_flag_cmpd_stmt_is_a_func_body)
	{}
	void GenerateCode(FILE * & fptr);
	virtual ~CompoundStatement();
	private:
	CompoundStatement& operator=(const CompoundStatement&);	
	CompoundStatement(const CompoundStatement&);	
};

struct FieldStatement: public AbstractStatement
{
	struct SymbolTableEntry * lhsSymbolTableEntry_, *rhsSymbolTableEntry_;
	Expression::AbstractExpression* start_col, *end_col;
	int width;
	FieldStatement(string lhs_name, string rhs_name
			, Expression::AbstractExpression* l_s, Expression::AbstractExpression* l_e
			, int l_w);
	void GenerateCode(FILE * & fptr);
	~FieldStatement()
	{}
	private:
	FieldStatement& operator=(const FieldStatement&);	
	FieldStatement(const FieldStatement&);	
};
		 

struct BlockArrayAssignmentStatement: public AbstractStatement
{
	struct SymbolTableEntry * lhsSymbolTableEntry_;
	struct SymbolTableEntry * rhsSymbolTableEntry_;
	Expression::AbstractExpression * low_indx, *high_indx;
	BlockArrayAssignmentStatement(DataType dtype, int lline_number
			, SymbolTableEntry* llsymp, SymbolTableEntry* lrsymp
			, Expression::AbstractExpression * lbd, Expression::AbstractExpression* hbd)
		: AbstractStatement(dtype, lline_number)
		  , lhsSymbolTableEntry_(llsymp), rhsSymbolTableEntry_(lrsymp)
		  , low_indx(lbd), high_indx(hbd)
	{}
	void GenerateCode(FILE * & fptr);
	~BlockArrayAssignmentStatement();
	
	private:
	BlockArrayAssignmentStatement& operator=
		(const BlockArrayAssignmentStatement&);	
	BlockArrayAssignmentStatement(const BlockArrayAssignmentStatement&);	
};

struct BreakStatement: public AbstractStatement
{
	BreakStatement(DataType dtype, int lline_number, int in_a_loop);
	void GenerateCode(FILE * & fptr);
	~BreakStatement();
	private:
	BreakStatement& operator=(const BreakStatement&);	
	BreakStatement(const BreakStatement&);	
};

struct ContinueStatement: public AbstractStatement{
	ContinueStatement(DataType dtype, int lline_number, int in_a_loop);
	void GenerateCode(FILE * & fptr);
	~ContinueStatement(){
		//cout << "deleting ContinueStatement" << endl;
		if (next_) delete next_;
	}
	private:
	ContinueStatement& operator=(const ContinueStatement&);	
	ContinueStatement(const ContinueStatement&);	
};

struct FunctionDeclarationStatement: public AbstractStatement
{
	struct FunctionInformation * funcInfo_;

	FunctionDeclarationStatement( DataType dtype
			, int lline_number, char * & name
			, FunctionParameter* & v_list, DataType returnType_);
	void GenerateCode(FILE * & fptr);
	~FunctionDeclarationStatement();
	private:
	FunctionDeclarationStatement& operator=
		(const FunctionDeclarationStatement&);	
	FunctionDeclarationStatement(const FunctionDeclarationStatement&);	
};

struct DeclarationStatement: public AbstractStatement
{
	struct SymbolTableEntry* symbolTableEntry_;
	int nestLevel_;
	DeclarationStatement (DataType dtype, int lline_number, int l_nest_level)
		: AbstractStatement (dtype, lline_number), symbolTableEntry_ (0),
		  nestLevel_ (l_nest_level)
	{}
	void GenerateCode(FILE * & fptr);
	~DeclarationStatement();
	private:
	DeclarationStatement& operator=(const DeclarationStatement&);	
	DeclarationStatement(const DeclarationStatement&);	
};


struct FunctionStatement: public AbstractStatement
{
	struct FunctionInformation * funcInfo_;
	struct AbstractStatement *funcBody_;
	DataType returnType_;

	FunctionStatement ( DataType dtype, int lline_number
			, struct Scope * &scope_
			, struct FunctionParameter * & v_list
			, struct AbstractStatement* & lfunc_body
			, string func_name
			, DataType lreturn_type
		);
	void GenerateCode(FILE * & fptr);
	~FunctionStatement();
	private:
	FunctionStatement& operator=(const FunctionStatement&);	
	FunctionStatement(const FunctionStatement&);	
};


struct ListStatement: public AbstractStatement{
	struct SymbolTableEntry * symbolTableEntry_;
	string list_text;
	Expression::AbstractExpression * arr_start;
	Expression::AbstractExpression * arr_end;
	ListStatement( DataType dtype, string name,
		string llist_text=string(""),
		Expression::AbstractExpression*  l_arr_start=0, 
		Expression::AbstractExpression* l_arr_end=0
		);
	void GenerateCode(FILE * & fptr);

	~ListStatement();

	private:
	ListStatement& operator=(const ListStatement&);	
	ListStatement(const ListStatement&);	
};



/*
 * The FunctionInformation constructor adds the names of the function parameters into its Scope.
 * When a compound statement is parsed : it checks for the flagIsFunctionBody_ and
 * loads that into the active Scope if set.
 * Note that flagIsFunctionBody_ is initialized to -1 as the 1st function 
 * will be in index 0 of func_info_table vector.
 * Also lookup_func searches the func_info_table for the function name and returns -1 on failure
 * this is naturally compatible with the initial value of flagIsFunctionBody_
 * if the flag is not set -> we need to allocate a new Scope - else we will crash
 */
//struct FunctionInformation;
struct FunctionInformation
{
	string funcName_;
	struct FunctionParameter * paramList_;
	DataType returnType_;
	struct AbstractStatement * funcBody_;
	struct Scope * funcScope_;
	FunctionInformation(string name, struct FunctionParameter* elist
			, DataType myreturn_type); 
	void print(FILE * fptr);
	~FunctionInformation();
private:
	FunctionInformation& operator=(const FunctionInformation&);
	FunctionInformation(const FunctionInformation&);
};


} /* close namespace Statement */
#endif /* _xtcc_stmt_h */
