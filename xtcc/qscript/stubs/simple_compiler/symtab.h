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
#include <limits.h>
#include <cstring>
//#include <sstream>

//using std::stringstream;
	/*!  type_qualifier enum: used to add qualifiers to the definition of a variable. For example: const int BUFSIZE=1024; // Here const is a qualifier
	 */ 
	enum type_qualifier {
		NO_QUAL, // used to mark that nothing was specified 
		CONST_QUAL
	};
	//! DataType enum: This enum is used to mark the type of a statement, the type of a variable and the type of an expression
	enum DataType {
		VOID_TYPE, 
		INT8_TYPE,  INT16_TYPE,  INT32_TYPE, FLOAT_TYPE, DOUBLE_TYPE,
		INT8_ARR_TYPE, INT16_ARR_TYPE, INT32_ARR_TYPE, FLOAT_ARR_TYPE, DOUBLE_ARR_TYPE,
		INT8_REF_TYPE, INT16_REF_TYPE, INT32_REF_TYPE, FLOAT_REF_TYPE, DOUBLE_REF_TYPE,
		BOOL_TYPE,
		ERROR_TYPE,
		TEXPR_STMT, CMPD_STMT, IFE_STMT, DECL_STMT, FUNC_TYPE, FUNC_DEFN, FOR_STMT,
		LISTA_BASIC_TYPE_STMT, LISTA_BASIC_ARRTYPE_STMT_1INDEX, LISTA_BASIC_ARRTYPE_STMT_2INDEX,
		BREAK_STMT, CONTINUE_STMT, RANGE_DECL_STMT,
		QUESTION_TYPE, QUESTION_ARR_TYPE,
		STRING_TYPE, STRING_ARR_TYPE, NAMED_ATTRIBUTE_TYPE, NAMED_RANGE,
		UNNAMED_RANGE, STUB_MANIP_ADD, STUB_MANIP_DEL, STUB_MANIP_UNSET_ALL,
		STUB_MANIP_SET_ALL,
		uninit 
	};
	//! QuestionType enum: A question can be single code,
	//! multicoded or numeric (which I havent yet added to the
	//! grammar)
	enum QuestionType { spn, mpn };
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

struct AbstractExpression;
struct XtccSet;
//! \class SymbolTableEntry: a Symbol table entry
/*!
  All variable declarations/definitions are objects of this class.
*/
struct SymbolTableEntry {
	char *name_;
	char *text_;
	union {
		double dval;
		int ival;
	};
	DataType type_;
	int n_elms;
	bool created_by_me;
	//! if the variable declaration is initialised with a value - the expression for that value is held here
	AbstractExpression * e;
	//! if the variable is a "set" and initialised then the values are held here
	XtccSet * xs;
	type_qualifier type_qual;
	//! constructor for variable declaration without initialisation
	SymbolTableEntry(const char * lname, DataType ldt):
		name_(strdup(lname)), text_(0), dval(0), type_(ldt), n_elms(-1), created_by_me(true), e(0), xs(0)
		, type_qual(NO_QUAL)

	{ }
	//! constructor for variable declaration and initialisation with an expression
	SymbolTableEntry(const char * lname, DataType ldt, AbstractExpression* le):
		name_(strdup(lname)), text_(0), dval(0), type_(ldt), n_elms(-1), created_by_me(true), e(le), xs(0)
		, type_qual(NO_QUAL)
		
	{ }
	//! constructor for const qualified variable declaration and initialisation with an expression
	SymbolTableEntry(const char * lname, DataType ldt, AbstractExpression* le, type_qualifier l_tq):
		name_(strdup(lname)), text_(0), dval(0), type_(ldt), n_elms(-1), created_by_me(true), e(le), xs(0),
		type_qual(l_tq)
	{ }
	//! constructor for a variable which is a named set
	SymbolTableEntry(const char * lname, DataType ldt, XtccSet * xs);
	inline DataType get_type(){
		return type_;
	}
	~SymbolTableEntry();
	void print_push_stack(string & str);
	void print_pop_stack(string & str);
	private:
		SymbolTableEntry& operator=(const SymbolTableEntry&);
		SymbolTableEntry (const SymbolTableEntry&);
};


#endif /* XTCC_SYMTAB_H */
