/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/common.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#ifndef common_h
#define common_h


	enum datatype {
		VOID_TYPE,
		INT8_TYPE, INT16_TYPE, INT32_TYPE, FLOAT_TYPE, DOUBLE_TYPE,
		BOOL_TYPE, STRING_TYPE,
		ERROR_TYPE
	};
	enum question_type { spn, mpn };
	enum compiler_err_category{compiler_syntax_err, compiler_sem_err, compiler_internal_error};
#endif /* common_h */
