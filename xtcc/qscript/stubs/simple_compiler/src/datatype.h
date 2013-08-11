/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/src/datatype.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

/*! \file
    \brief Statement Datatypes in the language
*/


#ifndef datatype_h
#define datatype_h
	//! DataType enum: This enum is used to mark the type of a statement, the type of a variable and the type of an expression
	enum DataType
	{
		VOID_TYPE,
		INT8_TYPE,  INT16_TYPE,  INT32_TYPE, FLOAT_TYPE, DOUBLE_TYPE,
		INT8_ARR_TYPE, INT16_ARR_TYPE, INT32_ARR_TYPE, FLOAT_ARR_TYPE, DOUBLE_ARR_TYPE,
		INT8_REF_TYPE, INT16_REF_TYPE, INT32_REF_TYPE, FLOAT_REF_TYPE, DOUBLE_REF_TYPE,
		BOOL_TYPE,
		ERROR_TYPE,
		TEXPR_STMT, CMPD_STMT, IFE_STMT, DECL_STMT, FUNC_TYPE, FUNC_DEFN, FOR_STMT,
		PAGE_STMT,
		LISTA_BASIC_TYPE_STMT, LISTA_BASIC_ARRTYPE_STMT_1INDEX, LISTA_BASIC_ARRTYPE_STMT_2INDEX,
		BREAK_STMT, CONTINUE_STMT, RANGE_DECL_STMT,
		QUESTION_TYPE, QUESTION_ARR_TYPE,
		STRING_TYPE, STRING_ARR_TYPE, NAMED_ATTRIBUTE_TYPE, NAMED_RANGE,
		UNNAMED_RANGE, STUB_MANIP_ADD, STUB_MANIP_DEL, STUB_MANIP_UNSET_ALL,
		STUB_MANIP_SET_ALL, GOTO_STMT, CLEAR_STMT, COLUMN_STMT, NEWCARD_STMT,
		uninit
	};

#endif /* datatype_h */
