#ifndef xtcc_utils_h
#define xtcc_utils_h

#include "symtab.h"
#include <map>
#include <string>
using std::map;
using std::string;
enum compiler_err_category{compiler_syntax_err, compiler_sem_err, compiler_internal_error};
map<string, symtab_ent*>::iterator find_in_symtab(string id);
#endif // xtcc_utils_h
