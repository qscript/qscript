/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/utils.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#ifndef xtcc_utils_h
#define xtcc_utils_h

#include "symtab.h"
#include <map>
#include <string>
using std::map;
using std::string;

struct FunctionParameter;
enum compiler_err_category
{	compiler_syntax_err
	, compiler_sem_err
	, compiler_internal_error
	, compiler_code_generation_error
};

void print_err(compiler_err_category cmp_err
		, string err_msg
		, int line_no
		, int compiler_line_no
		, string compiler_file_name);
map<string, SymbolTableEntry*>::iterator find_in_symtab(string id);
int search_for_func(string& search_for);
DataType arr_deref_type(DataType d1);
bool is_of_int_type(DataType dt);
int check_func_decl_with_func_defn(FunctionParameter* & v_list
		, int & index, string func_name);
bool 	void_check( DataType & type1, DataType & type2, DataType& result_type);
DataType lcm_type(DataType d1, DataType d2);
int check_parameters(AbstractExpression* e, FunctionParameter* v);
bool skip_func_type_check(const char * fname);
bool check_type_compat(DataType typ1, DataType typ2);
int lookup_func(string func_name_index);


extern noun_list_type noun_list[];
#endif // xtcc_utils_h
