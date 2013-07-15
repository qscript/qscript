/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/common.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */


/*! \file
    \brief Symbol table entries - supporting class
*/

#ifndef XTCC_SYMTAB_H
#define XTCC_SYMTAB_H
//#include <iostream>
#include <sys/types.h>
#include <limits.h>
#include <cstring>
#include "datatype.h"
#include "active_var_info.h"
//#include <sstream>

//using std::stringstream;
	/*!  type_qualifier enum: used to add qualifiers to the definition of a variable. For example: const int32_t BUFSIZE=1024; // Here const is a qualifier
	 */
	enum type_qualifier {
		NO_QUAL, // used to mark that nothing was specified
		CONST_QUAL
	};
	//! QuestionType enum: A question can be single code,
	//! multicoded or numeric (which I havent yet added to the
	//! grammar)
	enum QuestionType { spn, mpn, video };
	//! This helper function will evaluate 2 types for  compatibility.
	//!For example an INT8_TYPE and a INT8_ARR_TYPE are not compatible.
	//! This is used to determine if a type promotion in an expression is
	//! possible or the compiler should signal a type error
	bool check_type_compat(DataType typ1, DataType typ2);

	bool is_of_int_type(DataType dt);
	bool is_of_noun_type(DataType dt);
	bool is_of_noun_ref_type(DataType dt);
	bool is_of_arr_type(DataType dt);
	bool is_of_int_arr_type(DataType dt);
	bool is_of_int32_arr_type(DataType dt);
	DataType convert_ref_type(DataType dt);
	bool 	void_check( DataType & type1, DataType & type2, DataType& result_type);
#include <string>
using	std::string ;
	//! useful when debugging
	string human_readable_type(DataType dt);


	struct noun_list_type {
		const char * sym;
		enum DataType dt;
	};

struct AbstractQuestion;
struct AbstractExpression;
struct XtccSet;
struct named_attribute_list;
//! \class SymbolTableEntry: a Symbol table entry
/*!
  All variable declarations/definitions are objects of this class.
*/
struct SymbolTableEntry {
	char *name_;
	char *text_;
	//union {
		double dval;
		int32_t ival;
	//}; finally got fed up of the warnings i got from the compiler
	DataType type_;
	int32_t n_elms;
	bool created_by_me;
	//! if the variable declaration is initialised with a value - the expression for that value is held here
	AbstractExpression * e;
	//! if the variable is a "set" and initialised then the values are held here
	XtccSet * xs;
	type_qualifier type_qual;
	AbstractQuestion * question_;
	named_attribute_list * namedAttributes_;

	//! constructor for variable declaration without initialisation
	SymbolTableEntry(const char * lname, DataType ldt):
		name_(strdup(lname)), text_(0), dval(0), ival(0)
		, type_(ldt), n_elms(-1), created_by_me(true), e(0), xs(0)
		, type_qual(NO_QUAL), question_(0), namedAttributes_(0)
	{ }
	//! constructor for variable declaration and initialisation with an expression
	SymbolTableEntry(const char * lname, DataType ldt, AbstractExpression* le):
		name_(strdup(lname)), text_(0), dval(0), ival(0)
		, type_(ldt), n_elms(-1), created_by_me(true), e(le), xs(0)
		, type_qual(NO_QUAL), question_(0), namedAttributes_(0)
	{ }
	//! constructor for const qualified variable declaration and initialisation with an expression
	SymbolTableEntry(const char * lname, DataType ldt, AbstractExpression* le, type_qualifier l_tq):
		name_(strdup(lname)), text_(0), dval(0), ival(0)
		, type_(ldt), n_elms(-1), created_by_me(true), e(le), xs(0),
		type_qual(l_tq), question_(0), namedAttributes_(0)
	{ }

	SymbolTableEntry(const char * lname, DataType ldt, int32_t arr_sz, char * text):
		name_(strdup(lname)), text_(strdup(text)), dval(0), ival(0)
		, type_(ldt) , n_elms(arr_sz), created_by_me(true)
		, e(0), xs(0), type_qual(NO_QUAL)
		, question_(0), namedAttributes_(0)
	{ }
	//! constructor for a variable which is a named set
	SymbolTableEntry(const char * lname, DataType ldt, XtccSet * xs);
	//! constructor for question SymbolTableEntry
	SymbolTableEntry(const char * lname, DataType ldt, AbstractQuestion * l_q):
		name_(strdup(lname)), text_(0), dval(0), ival(0)
		, type_(ldt), n_elms(-1), created_by_me(true), e(0), xs(0)
		, type_qual(NO_QUAL), question_(l_q), namedAttributes_(0)
	{ }

	SymbolTableEntry (const char * lname, DataType ldt, named_attribute_list * l_na):
		name_(strdup(lname)), text_(0), dval(0), ival(0)
		, type_(ldt), n_elms(-1), created_by_me(true), e(0), xs(0)
		, type_qual(NO_QUAL), question_(0), namedAttributes_(l_na)
	{ }
	inline DataType get_type()
	{
		return type_;
	}
	~SymbolTableEntry();
	void print_push_stack(const string & stack_name, string & str);
	void print_pop_stack(const string & stack_name, string & str);
	ActiveVariableInfo * GetVarInfo();
	private:
		SymbolTableEntry& operator=(const SymbolTableEntry&);
		SymbolTableEntry (const SymbolTableEntry&);
};


#endif /* XTCC_SYMTAB_H */
