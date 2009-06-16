#ifndef xtcc_utils_h
#define xtcc_utils_h

#include "symtab.h"
#include <map>
#include <string>
using std::map;
using std::string;
enum compiler_err_category{compiler_syntax_err, compiler_sem_err
	, compiler_internal_error};
void print_err(compiler_err_category cmp_err
		, string err_msg, int line_no, int compiler_line_no
		, string compiler_file_name);

map<string, SymbolTableEntry*>::iterator find_in_symtab(string id);
int search_for_func(string& search_for);
#endif // xtcc_utils_h
