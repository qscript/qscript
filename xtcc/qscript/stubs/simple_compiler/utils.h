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
enum compiler_err_category{compiler_syntax_err, compiler_sem_err, compiler_internal_error,
		compiler_code_generation_error};
void print_err(compiler_err_category cmp_err, 
		string err_msg, int line_no, int compiler_line_no, string compiler_file_name);
map<string, symtab_ent*>::iterator find_in_symtab(string id);
int search_for_func(string& search_for);
bool is_of_int_type(datatype dt);

extern noun_list_type noun_list[];
datatype lcm_type(datatype d1, datatype d2);
datatype arr_deref_type(datatype d1);


#endif // xtcc_utils_h
