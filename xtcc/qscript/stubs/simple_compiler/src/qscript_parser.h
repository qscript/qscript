/*!  \file
	\brief Global variables used by the parser
 */
#ifndef qscript_parser_h
#define qscript_parser_h

#include <inttypes.h>
#include <sys/types.h>
#include <fstream>
#include <vector>
#include <map>
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
#include "lex_location.h"
#include "TempNameGenerator.h"

using std::ofstream;
using std::vector;
namespace qscript_parser
{

	extern vector<AbstractExpression*> for_loop_max_counter_stack;
	//extern vector<CompoundStatement*> compound_body_stack;
	//! This is a pointer to the most active Scope on the active_scope_list stack
	extern Scope* active_scope;
	//! maintains the Scope levels in the files being parsed. The active_scope_list is treated like a stack
	extern vector <Scope*> active_scope_list;
	extern int32_t nest_lev;
	extern int32_t flagIsAFunctionBody_;
	extern int32_t flagIsAForBody_;
	extern int32_t page_nest_lev;
	// NxD: 11-aug-2013 Since pages cannot nest inside each other
	// I am hoping a global variable for the active page name
	// should be enough
	extern std::string globalActivePageName_;
	extern bool flag_first_question_in_page;
	extern bool flag_next_stmt_start_of_block;
	extern bool flag_next_question_start_of_block;
	extern bool flag_dynamic_base_text;
	extern AbstractQuestion * dynamic_base_text_question;
	extern vector<bool> blk_start_flag;
	extern vector<bool> blk_question_start_flag;
	extern vector <AbstractStatement*> blk_heads;
	//const int32_t DEFAULT_STACK_SIZE=20;
	extern vector<CompoundStatement*> stack_cmpd_stmt;
	extern vector<string> stack_of_active_push_vars;
	extern map<string, vector<string> > map_of_active_vars_for_questions;
	extern vector<AbstractStatement*> delete_manually_in_cleanup;


	AbstractExpression * recurse_for_index(int32_t stack_index);

	extern ofstream debug_log_file;
	using std::string;
	//void print_err(compiler_err_category cmp_err,
	//	string err_msg, int32_t line_no,
	//	int32_t compiler_line_no, string compiler_file_name);
	extern int32_t line_no;
	extern noun_list_type noun_list[];

	extern QuestionType q_type;
	extern int32_t no_mpn;
	extern XtccSet xs;
	extern XtccSet mutex_range_set;
	extern bool has_mutex_range;
	extern map<std::pair<int, int>, string > maintainer_messages;
	extern int32_t yylex();
	extern void yyerror(const char * s);
	extern int32_t no_errors;

	extern struct AbstractStatement* tree_root;
	extern string project_name;
	extern vector <AbstractQuestion*> question_list;
	extern void GenerateCode(const string & src_file_name, bool ncurses_flag);
	extern int32_t ReadQScriptConfig();
	extern void CompileGeneratedCode(const string & src_file_name);
	extern void CompileGeneratedCodeEmscripten(const string & src_file_name);
	extern void CompileGeneratedCodeStatic(const string & src_file_name );
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);
	extern const bool XTCC_DEBUG_MEM_USAGE;
	extern bool skip_func_type_check(const char * fname);
	extern vector<mem_addr_tab>  mem_addr;
	extern vector <FunctionInformation*> func_info_table;
	extern int32_t check_parameters(struct AbstractExpression* e, struct VariableList* v);

        extern vector <string> attribute_list;
	extern vector <named_range*> named_stubs_list;
	extern vector <named_attribute_list> named_attributes_list;
        extern vector <stub_pair> stub_list;
	extern int32_t if_line_no;
	extern int32_t yywrap();

	extern AbstractStatement* setup_stub_manip_stmt(DataType dt
			, char* stub_list_name, char * question_name, AbstractExpression * l_arr_index=0);

	extern AbstractStatement* setup_stub_manip_stmt(DataType dt
			 , char* stub_list_name , XtccSet & l_xs);
	extern AbstractStatement* setup_stub_manip_stmt_set_unset(DataType dt
			, char* stub_list_name);

	CompoundStatement* ProcessOpenCurly();
	CompoundStatement* ProcessCompoundStatement(CompoundStatement* cmpdStmt,
			AbstractStatement *stmt);
	AbstractStatement * ProcessRangeQuestion(const string &name
						 , const string & q_text
						 , const DataType& dt );
	AbstractStatement * ProcessNamedQuestion(
		const string &name, const string & q_txt
		, const DataType& dt, const string & named_stub_list );


	void PrintActiveVariablesAtScope( vector <Scope*> & active_scope_list,
		vector <ActiveVariableInfo*> & output_info);


	extern bool show_lex_error_context ;
	extern string fname;
	extern struct LexLocation lex_location;

	extern TempNameGenerator temp_set_name_generator;
	extern TempNameGenerator temp_name_generator;
	string ExtractBaseFileName(const string & fname);

	extern vector<TextExpression*> text_expr_vec;

}

#endif /* qscript_parser_h */
