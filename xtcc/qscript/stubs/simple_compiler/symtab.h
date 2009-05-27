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
	//! datatype enum: This enum is used to mark the type of a statement, the type of a variable and the type of an expression
	enum datatype {
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
	//! question_type enum: A question can be single code,
	//! multicoded or numeric (which I havent yet added to the
	//! grammar)
	enum question_type { spn, mpn };
	//! This helper function will evaluate 2 types for  compatibility. 
	//!For example an INT8_TYPE and a INT8_ARR_TYPE are not compatible.
	//! This is used to determine if a type promotion in an expression is
	//! possible or the compiler should signal a type error
	bool check_type_compat(datatype typ1, datatype typ2);

	bool is_of_int_type(datatype dt);
	bool is_of_noun_type(datatype dt);
	bool is_of_noun_ref_type(datatype dt);
	bool is_of_arr_type(datatype dt);
	bool is_of_int_arr_type(datatype dt);
	bool is_of_int32_arr_type(datatype dt);
	datatype convert_ref_type(datatype dt);
	bool 	void_check( datatype & type1, datatype & type2, datatype& result_type);
#include <string>
using	std::string ;
	//! useful when debugging
	string human_readable_type(datatype dt);


	struct noun_list_type {
		const char * sym;
		enum datatype dt;
	};

struct expr;
struct xtcc_set;
//! \class symtab_ent: a Symbol table entry
/*!
  All variable declarations/definitions are objects of this class.
*/
struct symtab_ent {
	char *name;
	char *text;
	union {
		double dval;
		int ival;
	};
	datatype type;
	int n_elms;
	bool created_by_me;
	//! if the variable declaration is initialised with a value - the expression for that value is held here
	expr * e;
	//! if the variable is a "set" and initialised then the values are held here
	xtcc_set * xs;
	type_qualifier type_qual;
	//! constructor for variable declaration without initialisation
	symtab_ent(const char * lname, datatype ldt):
		name(strdup(lname)), text(0), dval(0), type(ldt), n_elms(-1), created_by_me(true), e(0), xs(0)
		, type_qual(NO_QUAL)

	{ }
	//! constructor for variable declaration and initialisation with an expression
	symtab_ent(const char * lname, datatype ldt, expr* le):
		name(strdup(lname)), text(0), dval(0), type(ldt), n_elms(-1), created_by_me(true), e(le), xs(0)
		, type_qual(NO_QUAL)
		
	{ }
	//! constructor for const qualified variable declaration and initialisation with an expression
	symtab_ent(const char * lname, datatype ldt, expr* le, type_qualifier l_tq):
		name(strdup(lname)), text(0), dval(0), type(ldt), n_elms(-1), created_by_me(true), e(le), xs(0),
		type_qual(l_tq)
	{ }
	//! constructor for a variable which is a named set
	symtab_ent(const char * lname, datatype ldt, xtcc_set * xs);
	inline datatype get_type(){
		return type;
	}
	~symtab_ent();
	void print_push_stack(string & str);
	void print_pop_stack(string & str);
	private:
		symtab_ent& operator=(const symtab_ent&);
		symtab_ent (const symtab_ent&);
};


#endif /* XTCC_SYMTAB_H */
