/*!  \file
	\brief Global variables used by the parser
 */
#ifndef qscript_parser_h
#define qscript_parser_h

#include <fstream>
#include <vector>
#include <cstdlib>
#include "debug_mem.h"
#include "datatype.h"
#include "symtab.h"
#include "stmt.h"
#include "expr.h"
#include "named_attributes.h"
#include "named_range.h"
#include "const_defs.h"
#include "xtcc_set.h"
#include "utils.h"
#include "question.h"
#include "active_var_info.h"

using std::ofstream;
using std::vector;
namespace qscript_parser {
	//! This is a pointer to the most active Scope on the active_scope_list stack
	extern vector<AbstractExpression*> for_loop_max_counter_stack;
	//extern vector<CompoundStatement*> compound_body_stack;
	extern Scope* active_scope;
	//! maintains the Scope levels in the files being parsed. The active_scope_list is treated like a stack
	extern vector <Scope*> active_scope_list;
	extern int nest_lev;
	extern int flagIsAFunctionBody_;
	extern int flagIsAForBody_;
	extern bool flag_next_stmt_start_of_block;
	extern vector<bool> blk_start_flag;
	extern vector <AbstractStatement*> blk_heads;
	//const int DEFAULT_STACK_SIZE=20;
	extern vector<CompoundStatement*> stack_cmpd_stmt;
	extern vector<string> stack_of_active_push_vars;
	extern map<string, vector<string> > map_of_active_vars_for_questions;


	AbstractExpression * recurse_for_index(int stack_index);

	extern ofstream debug_log_file;
	using std::string;
	//void print_err(compiler_err_category cmp_err, 
	//	string err_msg, int line_no, 
	//	int compiler_line_no, string compiler_file_name);
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


	extern QuestionType q_type;
	extern int no_mpn;
	extern XtccSet xs;
	extern int yylex();
	extern void yyerror(const char * s);
	extern int no_errors;

	extern struct AbstractStatement* tree_root;
	extern string project_name;
	extern vector <AbstractQuestion*> question_list;
	extern void GenerateCode(const string & src_file_name, bool ncurses_flag);
	extern void CompileGeneratedCode(const string & src_file_name);
	extern int ReadQScriptConfig();
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);
	extern const bool XTCC_DEBUG_MEM_USAGE;
	extern bool skip_func_type_check(const char * fname);
	extern vector<mem_addr_tab>  mem_addr;
	extern vector <FunctionInformation*> func_info_table;
	extern int check_parameters(struct AbstractExpression* e, struct VariableList* v);

        extern vector <string> attribute_list;
	extern vector <named_range*> named_stubs_list;
	extern vector <named_attribute_list> named_attributes_list;
        extern vector <stub_pair> stub_list;
	extern int if_line_no;
	extern int yywrap();

	extern AbstractStatement* setup_stub_manip_stmt(DataType dt
			, char* stub_list_name, char * question_name);
	extern AbstractStatement* setup_stub_manip_stmt_set_unset(DataType dt
			, char* stub_list_name);

	CompoundStatement* ProcessOpenCurly();
	CompoundStatement* ProcessCompoundStatement(CompoundStatement* cmpdStmt,
			AbstractStatement *stmt);
	AbstractStatement * ProcessRangeQuestion(const string &name
			, const string & q_text , const DataType& dt );
	AbstractStatement * ProcessNamedQuestion(const string &name
			, const string & q_txt , const DataType& dt 
			, const string & named_stub_list );


	void PrintActiveVariablesAtScope( vector <Scope*> & active_scope_list,
		vector <ActiveVariableInfo*> & output_info);
}

#endif /* qscript_parser_h */
