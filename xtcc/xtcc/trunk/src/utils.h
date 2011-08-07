#ifndef xtcc_utils_h
#define xtcc_utils_h

#include "symtab.h"
#include <map>
#include <string>

namespace Statement{
	struct FunctionParameter;
}

namespace Util
{

using std::map;
using std::string;
enum compiler_err_category{compiler_syntax_err, compiler_sem_err
	, compiler_internal_error};
void print_err(compiler_err_category cmp_err
		, string err_msg, int line_no, int compiler_line_no
		, string compiler_file_name);

map<string, SymbolTableEntry*>::iterator find_in_symtab(string id);
int search_for_func(string& search_for);
DataType arr_deref_type(DataType d1);
int check_func_decl_with_func_defn(Statement::FunctionParameter* & v_list
		, int & index, string func_name);
bool 	void_check( DataType & type1, DataType & type2, DataType& result_type);
DataType lcm_type(DataType d1, DataType d2);
int check_parameters(Expression::AbstractExpression* e, Statement::FunctionParameter* v);
bool skip_func_type_check(const char * fname);
map<string, SymbolTableEntry*>::iterator find_in_symtab(string id);
bool check_type_compat(DataType typ1, DataType typ2);
int lookup_func(string func_name_index);

} /* close namespace Util */


#endif // xtcc_utils_h
