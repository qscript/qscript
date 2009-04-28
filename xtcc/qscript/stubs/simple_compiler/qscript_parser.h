/*!  \file
	\brief Global variables used by the parser
 */
#ifndef qscript_parser_h
#define qscript_parser_h

#include <fstream>
#include <vector>
#include "debug_mem.h"
#include "symtab.h"
#include "stmt.h"
#include "expr.h"
#include "named_attributes.h"
#include "named_range.h"
#include "const_defs.h"
#include "xtcc_set.h"
#include "utils.h"

using std::ofstream;
using std::vector;
namespace qscript_parser {
	//! This is a pointer to the most active scope on the active_scope_list stack
	extern scope* active_scope;
	//! maintains the scope levels in the files being parsed. The active_scope_list is treated like a stack
	extern vector <scope*> active_scope_list;
	extern int nest_lev;
	extern int flag_cmpd_stmt_is_a_func_body;
	extern int flag_cmpd_stmt_is_a_for_body;
	extern bool flag_next_stmt_start_of_block;
	extern vector<bool> blk_start_flag;
	extern vector <stmt*> blk_heads;
	//const int DEFAULT_STACK_SIZE=20;
	extern vector<cmpd_stmt*> stack_cmpd_stmt;
	extern vector<string> stack_of_active_push_vars;
	extern map<string, vector<string> > map_of_active_vars_for_questions;



	extern ofstream debug_log_file;
	using std::string;
	void print_err(compiler_err_category cmp_err, 
		string err_msg, int line_no, 
		int compiler_line_no, string compiler_file_name);
	extern int line_no;
	extern noun_list_type noun_list[];

	/*
	noun_list_type noun_list[]= {
			{	"void"	, VOID_TYPE},
			{	"int8_t" ,INT8_TYPE},
			{	"int16_t" ,INT16_TYPE},
			{	"int32_t" ,INT32_TYPE},
			{	"float", FLOAT_TYPE},
			{	"double", DOUBLE_TYPE}
		};
	*/	


	extern question_type q_type;
	extern int no_mpn;
	extern xtcc_set xs;
	extern int yylex();
	extern void yyerror(const char * s);
	extern int no_errors;

	extern struct stmt* tree_root;
	extern vector <question*> question_list;
	extern void generate_code();
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);
	extern const bool XTCC_DEBUG_MEM_USAGE;
	extern bool skip_func_type_check(const char * fname);
	extern vector<mem_addr_tab>  mem_addr;
	extern vector <func_info*> func_info_table;
	extern int check_parameters(struct expr* e, struct var_list* v);

        extern vector <string> attribute_list;
	extern vector <named_range*> named_stubs_list;
	extern vector <named_attribute_list> named_attributes_list;
        extern vector <stub_pair> stub_list;
	extern int if_line_no;
	extern int yywrap();


}

#endif /* qscript_parser_h */
