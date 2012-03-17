#include <cstdlib>
#include <sstream>
#include <iostream>
#include <utility>
#include "compiled_code.h"
#include "qscript_parser.h"
#include "config_parser.h"
#include "qscript_debug.h"
#include "TempNameGenerator.h"
#include "utils.h"
#include "scope.h"


namespace program_options_ns {
	extern bool ncurses_flag;
	extern bool static_binary_flag;
	extern bool web_server_flag;
	extern bool compile_to_cpp_only_flag;
	extern int32_t fname_flag;
	extern bool flag_nice_map;
	extern char * QSCRIPT_HOME;
}

extern int32_t qscript_confparse();
extern void qscript_confrestart(FILE *input_file);
namespace qscript_parser
{
	using std::cerr;
	using std::cout;
	using std::endl;
	using std::stringstream;
	vector<AbstractExpression*> for_loop_max_counter_stack;
	vector<CompoundStatement*> compound_body_stack;
	Scope* active_scope;
	vector <Scope*> active_scope_list;
	int32_t nest_lev = 0;
	int32_t flagIsAFunctionBody_ = -1;
	int32_t flagIsAForBody_ = 0;
	bool flag_next_stmt_start_of_block = false;

	bool flag_dynamic_base_text = false;
	AbstractQuestion * dynamic_base_text_question = 0;
	bool flag_next_question_start_of_block = false;

	vector<bool> blk_start_flag;
	vector<bool> blk_question_start_flag;
	vector <AbstractStatement*> blk_heads;
	//const int32_t DEFAULT_STACK_SIZE=20;
	vector<CompoundStatement*> stack_cmpd_stmt;
	vector<string> stack_of_active_push_vars;
	map<string, vector<string> > map_of_active_vars_for_questions;
	// map<std::pair<int, int>, string > maintainer_messages;

	AbstractExpression * recurse_for_index(int32_t stack_index);
	vector<AbstractStatement*> delete_manually_in_cleanup;


	ofstream debug_log_file("qscript_debug.log", std::ios_base::out|std::ios_base::trunc);
	using std::string;
	//void print_err(compiler_err_category cmp_err,
	//	string err_msg, int32_t line_no,
	//	int32_t compiler_line_no, string compiler_file_name);
	// int32_t line_no;
	extern noun_list_type noun_list[];

	QuestionType q_type;
#include "const_defs.h"
#include "xtcc_set.h"
	int32_t no_mpn = 0;
	XtccSet xs;
	XtccSet mutex_range_set;
	bool has_mutex_range = false;
	int32_t yylex();
	void yyerror(const char * s);
	//int32_t no_errors;

	struct AbstractStatement* tree_root = 0;
	vector <AbstractQuestion*> question_list;
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);
	const bool XTCC_DEBUG_MEM_USAGE = true;
	bool skip_func_type_check(const char * fname);
	vector<mem_addr_tab>  mem_addr;
	vector <FunctionInformation*> func_info_table;
	int32_t check_parameters(struct AbstractExpression* e, struct VariableList* v);

        vector <string> attribute_list;
	vector <named_range*> named_stubs_list;
	vector <named_attribute_list> named_attributes_list;
        vector <stub_pair> stub_list;
	int32_t if_line_no = -1;

	int32_t yywrap();

	string project_name;
	bool show_lex_error_context = true;
	string fname;
	struct LexLocation lex_location;
	//TempNameGenerator temp_set_name_generator("qscript_temp_xtcc_set_");
	//TempNameGenerator temp_name_generator("qscript_temp_");
	vector < FixAndRecodeStatement* > recode_driver_vec;
	vector < Create_1_0_DataEditStatement* > create_1_0_edit_vec;

}

namespace qscript_parser{

using std::string;

#include <sstream>

void print_header(FILE* script, bool ncurses_flag);
void print_array_question_class(FILE* script);
//void print_flat_ascii_data_class(FILE *script);
//void print_qtm_data_class(FILE *script);
void print_close(FILE* script, ostringstream & program_code, bool  ncurses_flag);
void print_navigation_support_functions(FILE * script);
void print_reset_questionnaire(FILE * script);
void print_read_a_serial_no (FILE * script);
void PrintDisplayActiveQuestions(FILE *script);
void PrintGetUserResponse(FILE *script);
void PrintSetupNCurses(FILE * script);
void PrintSignalHandler(FILE * script, bool ncurses_flag);
void PrintSetupSignalHandler(FILE * script);

void PrintPrintMapHeader(FILE * script);
void PrintDefineSomePDCursesKeys(FILE * script);
void PrintPDCursesKeysHeader(FILE * script);
void PrintProcessOptions(FILE * script);
void PrintNCursesMain(FILE * script, bool ncurses_flag);
void PrintComputeFlatFileMap(StatementCompiledCode & compute_flat_map_code);
void PrintRecodeEdit(StatementCompiledCode & recode_edit);
void PrintCreate_1_0_DataEdit(StatementCompiledCode & create_1_0_data_edit);
void print_eval_questionnaire (FILE* script, ostringstream & program_code, bool ncurses_flag);
void print_write_qtm_data_to_disk(FILE *script);
void print_write_ascii_data_to_disk(FILE *script);
void print_write_spss_file_for_ascii_data_to_disk(/*FILE *script*/StatementCompiledCode & compute_flat_map_code);
void print_do_freq_counts(FILE *script);
void print_write_xtcc_data_to_disk(FILE *script);
const char * file_exists_check_code();
const char * write_data_to_disk_code();
void print_summary_axis(FILE * script);
void print_prompt_user_for_serial_no(FILE * script);
void print_ncurses_include_files (FILE * script);
void print_ncurses_func_prototypes (FILE * script);
void print_GetQuestionMapEntry(FILE * script);
void print_GetQuestionMapEntryArrayQ (FILE * script);
void print_recode_edit_qax (FILE * script);


string ExtractBaseFileName(const string & fname)
{
	string output_file_name = fname;
	int32_t dot_pos = fname.find_last_of('.');
	if(!(dot_pos == string::npos)){
		output_file_name = fname.substr(0, dot_pos);
	}
	return output_file_name;
}

void GenerateCode(const string & src_file_name, bool ncurses_flag)
{
	if(qscript_debug::DEBUG_qscript_parser)
		cerr << "ENTER qscript_parser::GenerateCode" << endl;
	string output_file_name = ExtractBaseFileName(src_file_name);
	output_file_name += ".C";
	FILE * script = fopen(output_file_name.c_str(), "w");
	if(!script){
		cerr << "unable to open output file : " << output_file_name << endl;
		exit(1);
	}

	print_header(script, ncurses_flag);
	tree_root->GenerateConsolidatedForLoopIndexes();
	StatementCompiledCode compute_flat_map_code;
	PrintComputeFlatFileMap(compute_flat_map_code);
	StatementCompiledCode code;
	tree_root->GenerateCode(code);

	fprintf(script, "struct TheQuestionnaire\n{\n");
	//fprintf(script, "AbstractQuestion * last_question_answered;\n");
	fprintf(script, "int32_t questions_start_from_here_index;\n" );
	fprintf(script, "int ser_no_pos;\n");
	fprintf(script, "vector <BaseText> base_text_vec;\n");
	fprintf(script, "%s\n", code.quest_defns.str().c_str());
	fprintf(script, "TheQuestionnaire() \n");
	fprintf(script, "%s\n", code.quest_defns_constructor.str().c_str());
	fprintf(script, "{\n");
	//fprintf(script, "last_question_answered = 0;\n");
	fprintf(script, "%s\n", code.quest_defns_init_code.str().c_str());
	fprintf(script, "questions_start_from_here_index = question_list.size();\n");

	fprintf(script, "%s\n", code.array_quest_init_area.str().c_str());
	fprintf(script, "}\n\n");
	print_summary_axis(script);
	// 5-apr-2011 , 0:12 (am)
	// continue from here - put the compute_flat_map_code into
	// a write data function - commiting this 
	// - generated code wont compile
	fprintf(script, "%s\n", compute_flat_map_code.program_code.str().c_str());
	print_eval_questionnaire(script, code.program_code, ncurses_flag);
	fprintf(script, "%s\n", write_data_to_disk_code());
	print_navigation_support_functions(script);
	print_reset_questionnaire(script);
	print_read_a_serial_no (script);
	PrintDisplayActiveQuestions(script);
	PrintGetUserResponse(script);
	print_write_qtm_data_to_disk(script);
	print_write_ascii_data_to_disk(script);
	print_prompt_user_for_serial_no(script);
	//print_write_spss_file_for_ascii_data_to_disk(script);
	print_write_xtcc_data_to_disk(script);
	print_do_freq_counts(script);
	//print_close(script, code.program_code, ncurses_flag);
	//fflush(script);
	fprintf(script, "};\n");
	print_GetQuestionMapEntry(script);
	print_GetQuestionMapEntryArrayQ(script);

	print_recode_edit_qax (script);

	//print_close(script, code.program_code, ncurses_flag);

	if (program_options_ns::ncurses_flag)
		PrintNCursesMain(script, ncurses_flag);
	print_close(script, code.program_code, ncurses_flag);
	fflush(script);
	if(qscript_debug::DEBUG_qscript_parser)
		cerr << "EXIT qscript_parser::GenerateCode" << endl;
}

void print_header(FILE* script, bool ncurses_flag)
{
	fprintf(script, "#include <iostream>\n");
	fprintf(script, "#include <vector>\n");
	fprintf(script, "#include <string>\n");
	fprintf(script, "#include <sstream>\n");
	fprintf(script, "#include <fstream>\n");
	fprintf(script, "#include <map>\n");
	fprintf(script, "#include <cstdlib>\n");
	fprintf(script, "#include <errno.h>\n");
	if (program_options_ns::ncurses_flag) {
		print_ncurses_include_files(script);
	}
	fprintf(script, "#include <signal.h>\n");
	fprintf(script, "#include <dirent.h>\n");
	fprintf(script, "#include <cctype>\n");
	fprintf(script, "#include <unistd.h>\n");
	fprintf(script, "#include <time.h>\n");
	//fprintf(script, "#include \"stmt.h\"\n");
	fprintf(script, "#include \"stub_pair.h\"\n");
	fprintf(script, "#include \"AbstractStatement.h\"\n");
	fprintf(script, "#include \"named_range.h\"\n");
	fprintf(script, "#include \"xtcc_set.h\"\n");
	fprintf(script, "#include \"datatype.h\"\n");
	fprintf(script, "#include \"qscript_lib.h\"\n");
	fprintf(script, "#include \"question_disk_data.h\"\n");
	fprintf(script, "#include \"question.h\"\n");
	fprintf(script, "#include \"user_navigation.h\"\n");
	fprintf(script, "#include \"qtm_data_file.h\"\n");
	fprintf(script, "#include \"qtm_datafile_conf_parser.h\"\n");
	fprintf(script, "#include \"ArrayQuestion.h\"\n");
	fprintf(script, "#include \"AsciiFlatFileQuestionDiskMap.h\"\n");
	fprintf(script, "#include \"XtccDataFile.h\"\n");
	fprintf(script, "#include \"base_text.h\"\n");

	{
		//stringstream mesg;
		//mesg << "do we need to #include \"TempNameGenerator.h\" in generated code? I have commented it out";
		// LOG_MAINTAINER_MESSAGE(mesg.str());
		// no we dont
		//fprintf(script, "#include \"TempNameGenerator.h\"\n");
	}
	fprintf(script, "#include \"QuestionAttributes.h\"\n");
	if(config_file_parser::PLATFORM == "LINUX"){
		FILE * simple_pd_curses_keys_h = fopen("a_few_pd_curses_keys.h", "wb");
		if(!simple_pd_curses_keys_h){
			fprintf(stderr, "unable to open file a_few_pd_curses_keys.h for writing ...\
					exiting \n");
			exit(1);
		}
		PrintPDCursesKeysHeader(simple_pd_curses_keys_h);
		fclose(simple_pd_curses_keys_h);
		fprintf(script, "#include \"a_few_pd_curses_keys.h\"\n");
	}


	fprintf(script, "int ser_no = 0;\n");
	fprintf(script, "using namespace std;\n");
	fprintf(script, "string qscript_stdout_fname(\"qscript_stdout.log\");\n");
	fprintf(script, "FILE * qscript_stdout = 0;\n");
	fprintf(script, "#include \"debug_mem.h\"\n");
	fprintf(script, "fstream debug_log_file(\"qscript_debug.log\", ios_base::out|ios_base::trunc);\n");
	fprintf(script, "fstream flat_file;\n");
	fprintf(script, "fstream xtcc_datafile;\n");
	fprintf(script, "fstream qtm_disk_file;\n");
	fprintf(script, "extern set<string> qtm_include_files;\n");

	fprintf(script, "using namespace std;\n");
	fprintf(script, "void read_data(const char * prompt);\n");
	fprintf(script, "//extern vector<int32_t> data;\n");

	if ( program_options_ns::flag_nice_map ) {
		fprintf(script, "namespace program_options_ns { bool flag_nice_map = true; }\n");
	} else {
		fprintf(script, "namespace program_options_ns { bool flag_nice_map = false; }\n");
	}
	
	fprintf(script, "extern UserNavigation user_navigation;\n");
	fprintf(script, "vector <AbstractQuestion*> question_list;\n");
	fprintf(script, "vector<mem_addr_tab>  mem_addr;\n");
	fprintf(script, "extern vector<question_disk_data*>  qdd_list;\n");
	fprintf(script, "void merge_disk_data_into_questions(FILE * qscript_stdout,\n"
			"\t\tAbstractQuestion * & p_last_question_answered,\n"
			"\t\tAbstractQuestion * & p_last_question_visited);\n");
	fprintf(script, "void merge_disk_data_into_questions2(FILE * qscript_stdout, AbstractQuestion * & p_last_question_answered, AbstractQuestion * & p_last_question_visited);\n");
	fprintf(script, "bool stopAtNextQuestion;\n");
	fprintf(script, "string jumpToQuestion;\n");
	fprintf(script, "int32_t jumpToIndex;\n");
	fprintf(script, "bool write_data_file_flag;\n");
	fprintf(script, "bool write_qtm_data_file_flag;\n");
	fprintf(script, "bool write_xtcc_data_file_flag;\n");
	fprintf(script, "bool card_start_flag;\n");
	fprintf(script, "bool card_end_flag;\n");
	fprintf(script, "int card_start;\n");
	fprintf(script, "int card_end;\n");

	fprintf(script, "int32_t check_if_reg_file_exists(string jno, int32_t ser_no);\n");
	fprintf(script, "void print_map_header(fstream & map_file);\n");
	fprintf(script, "map<string, vector<string> > map_of_active_vars_for_questions;\n");
	fprintf(script, "map<string, map<int, int> > freq_count;\n");
	fprintf(script, "bool back_jump = false;// no need for this but state the intent\n");
	fprintf(script, "void write_data_to_disk(const vector<AbstractQuestion*>& q_vec, string jno, int32_t ser_no);\n");
	fprintf(script, "AbstractQuestion * ComputePreviousQuestion(AbstractQuestion * q);\n");
	if (program_options_ns::ncurses_flag) {
		print_ncurses_func_prototypes(script);
	}
	fprintf(script, "void SetupSignalHandler();\n");
	fprintf(script, "static void sig_usr(int32_t signo);\n");
	fprintf(script, "int32_t ComputeJumpToIndex(AbstractQuestion * q);\n");
	fprintf(script, "void reset_questionnaire();\n");
	fprintf(script, "void DisplayActiveQuestions();\n");
	fprintf(script, "string output_data_file_name;\n");
	fprintf(script, "string output_qtm_data_file_name;\n");
	fprintf(script, "string output_xtcc_data_file_name;\n");
	fprintf(script, "void GetUserResponse(string& qno, int32_t &qindex);\n");
	// print_array_question_class(script);
	fprintf(script, "string jno = \"%s\";\n", project_name.c_str());
	fprintf(script, "char * flat_file_output_buffer = 0;\n");
	fprintf(script, "char * xtcc_datafile_output_buffer = 0;\n");
	fprintf(script, "int32_t len_flat_file_output_buffer  = 0;\n");
	fprintf(script, "int32_t len_xtcc_datafile_output_buffer  = 0;\n");
	//print_flat_ascii_data_class(script);
	//print_qtm_data_class(script);
	fprintf(script, "vector <AsciiFlatFileQuestionDiskMap*> ascii_flatfile_question_disk_map;\n");
	fprintf(script, "vector <XtccDataFileDiskMap*> xtcc_question_disk_map;\n");
	fprintf(script, "vector <qtm_data_file_ns::QtmDataDiskMap*> qtm_datafile_question_disk_map;\n");
	fprintf(script, "qtm_data_file_ns::QtmDataFile qtm_data_file;\n");
	fprintf(script, "void Compute_FlatFileQuestionDiskDataMap(vector<AbstractQuestion*> p_question_list);\n");
	fprintf(script, "\n");
	fprintf(script, "int process_options(int argc, char * argv[]);\n");
	fprintf(script, "qtm_data_file_ns::QtmDataDiskMap* GetQuestionMapEntry(vector <qtm_data_file_ns::QtmDataDiskMap*> & qtm_datafile_question_disk_map,\n");
	fprintf(script, "		string name);\n");
	fprintf(script, "vector<qtm_data_file_ns::QtmDataDiskMap*> GetQuestionMapEntryArrayQ(vector <qtm_data_file_ns::QtmDataDiskMap*> & qtm_datafile_question_disk_map,\n");
	fprintf(script, "		string name);\n");
	fprintf(script, "	WINDOW 	* question_window = 0,\n"
			"		* stub_list_window = 0,\n"
			"		* data_entry_window = 0,\n"
			"		* error_msg_window = 0,\n"
			"		* help_window = 0;\n"
			);
	fprintf(script, "	PANEL 	* question_panel = 0,\n"
			"		* stub_list_panel = 0,\n"
			"		* data_entry_panel = 0,\n"
			"		* error_msg_panel = 0,\n"
			"		* help_panel = 0;\n");
	fprintf(script, "\tDIR * directory_ptr = 0;\n");
	fprintf(script, "AbstractQuestion * last_question_answered = 0;\n");
	fprintf(script, "AbstractQuestion * last_question_visited = 0;\n");

	// fprintf(script, "struct TheQuestionnaire\n{\n");
	// fprintf(script, "AbstractQuestion * last_question_answered = 0;\n");
	/* main was here */


}


void print_close(FILE* script, ostringstream & program_code, bool ncurses_flag)
{

	//print_eval_questionnaire(script, program_code, ncurses_flag);
	// fprintf(script, "%s\n", write_data_to_disk_code());
	// print_navigation_support_functions(script);
	// print_reset_questionnaire(script);
	// PrintDisplayActiveQuestions(script);
	// PrintGetUserResponse(script);
	if(ncurses_flag){
		PrintSetupNCurses(script);
		if(config_file_parser::PLATFORM == "LINUX"){
			PrintDefineSomePDCursesKeys(script);
		}
	}
	PrintSignalHandler(script, ncurses_flag);
	PrintSetupSignalHandler(script);
	PrintProcessOptions(script);
	PrintPrintMapHeader(script);
}

void print_navigation_support_functions(FILE * script)
{
	fprintf(script, "// The first question before this question that is answered\n");
	fprintf(script, "AbstractQuestion * ComputePreviousQuestion(AbstractQuestion * q)\n");
	fprintf(script, "{\n");
	fprintf(script, "	int32_t current_question_index = -1;\n");
	//fprintf(script, "	for(int32_t i = 0; i < question_list.size(); ++i)\n");
	fprintf(script, "	for (int32_t i = questions_start_from_here_index; i < question_list.size(); ++i) {\n");
	fprintf(script, "		if (question_list[i] == q) {\n");
	fprintf(script, "			current_question_index = i;\n");
	fprintf(script, "			break;\n");
	fprintf(script, "		}\n");
	fprintf(script, "	}\n");
	fprintf(script, "	if (current_question_index == -1) {\n");
	fprintf(script, "		cerr << \"internal compiler error at runtime ... filename: \" \n");
	fprintf(script, "			<< __FILE__ \n");
	fprintf(script, "			<< \"line no: \" << __LINE__\n");
	fprintf(script, "			<< endl;\n");
	fprintf(script, "	}\n");
	fprintf(script, "	for (int32_t i = current_question_index-1; i >= 0; --i) {\n");
	fprintf(script, "		if (question_list[i]->isAnswered_ && !question_list[i]->question_attributes.hidden_) {\n");
	fprintf(script, "			return question_list[i];\n");
	fprintf(script, "		}\n");
	fprintf(script, "	}\n");
	fprintf(script, "// If we reach here just return the 1st question and hope for the best\n");
	fprintf(script, "// This will not work if there is a condition on the 1st question - because of which it should never have been taken\n");
	fprintf(script, "	return question_list[questions_start_from_here_index];\n");
	fprintf(script, "}\n");

	fprintf(script,"int32_t ComputeJumpToIndex(AbstractQuestion * q)\n");
	fprintf(script,"{\n");
	fprintf(script,"	//cout << \"ENTER ComputeJumpToIndex: index:  \";\n");
	fprintf(script,"	//for (int32_t i = 0; i < q->loop_index_values.size(); ++i) {\n");
	fprintf(script,"	//	cout << q->loop_index_values[i] << \" \";\n");
	fprintf(script,"	//}\n");
	fprintf(script,"	//cout << endl;\n");
	fprintf(script,"	int32_t index = 0;\n");
	fprintf(script,"	for (int32_t i = 0; i < q->loop_index_values.size(); ++i) {\n");
	fprintf(script,"		int32_t tmp1=q->loop_index_values[i];\n");
	fprintf(script,"		for (int32_t j = i+1; j < q->dummyArrayQuestion_->array_bounds.size(); ++j) {\n");
	fprintf(script,"			tmp1 *=q->dummyArrayQuestion_->array_bounds[j];\n");
	fprintf(script,"		}\n");
	fprintf(script,"		index+=tmp1;\n");
	fprintf(script,"	}\n");
	fprintf(script,"	//cout << \"EXIT ComputeJumpToIndex: returning : \" << index << endl;\n");
	fprintf(script,"	return index;\n");
	fprintf(script,"}\n");
}

void print_reset_questionnaire(FILE * script)
{
	fprintf(script, "void reset_questionnaire(){\n");
	fprintf(script, "for(int32_t i = 0; i< question_list.size(); ++i){\n");
	fprintf(script, "\tquestion_list[i]->isAnswered_ = false;\n");
	fprintf(script, "\tquestion_list[i]->input_data.clear();\n");
	fprintf(script, "\t}\n");
	fprintf(script, "}\n");

}

void PrintSetupNCurses(FILE * script)
{
	//fprintf(script, "void SetupNCurses(WINDOW * &  question_window,\n");
	//fprintf(script, "			WINDOW * &  stub_list_window,\n");
	//fprintf(script, "			WINDOW * & data_entry_window)\n");

	fprintf(script, "void SetupNCurses(WINDOW * &  question_window,\n"
			"			WINDOW * &  stub_list_window,\n"
			"			WINDOW * & data_entry_window,\n"
			"			WINDOW * & error_msg_window,\n"
			"			WINDOW * & help_window,\n"
			"			PANEL * &  question_panel,\n"
			"			PANEL * &  stub_list_panel,\n"
			"			PANEL * & data_entry_panel,\n"
			"			PANEL * & error_msg_panel,\n"
			"			PANEL * & help_panel)\n");
	fprintf(script, "{\n");
	fprintf(script, "	initscr();\n");
	fprintf(script, "       cbreak();\n");
	//fprintf(script, "       noecho();\n");
	fprintf(script, "       nonl();\n");
	fprintf(script, "       intrflush(stdscr, FALSE);\n");
	fprintf(script, "	if(has_colors() == FALSE)\n");
	fprintf(script, "	{	endwin();\n");
	fprintf(script, "		printf(\"Your terminal does not support color\\n\");\n");
	fprintf(script, "		exit(1);\n");
	fprintf(script, "	}\n");
	fprintf(script, "	start_color();\n");
	fprintf(script, "	chtype space = ' ';");
	fprintf(script, "	init_pair(1, COLOR_RED, COLOR_WHITE);\n");
	fprintf(script, "	init_pair(2, COLOR_GREEN, COLOR_WHITE);\n");
	fprintf(script, "	init_pair(3, COLOR_BLUE, COLOR_WHITE);\n");
	fprintf(script, "	init_pair(4, COLOR_MAGENTA, COLOR_CYAN);\n");
	fprintf(script, "	init_pair(5, COLOR_WHITE, COLOR_RED);\n");






	fprintf(script, "	int32_t maxX, maxY;\n");
	fprintf(script, "	getmaxyx(stdscr, maxY, maxX);\n");
	fprintf(script, "\n");
	fprintf(script, "\n");
	fprintf(script, "	int32_t DATA_ENTRY_WINDOW_HEIGHT=5, DATA_ENTRY_WINDOW_WIDTH=maxX;\n");
	fprintf(script, "\n");
	fprintf(script, "       int32_t starty = maxY-DATA_ENTRY_WINDOW_HEIGHT;\n");
	fprintf(script, "       int32_t startx = 0;\n");
	fprintf(script, "	data_entry_window = create_newwin(DATA_ENTRY_WINDOW_HEIGHT\n");
	fprintf(script, "			, DATA_ENTRY_WINDOW_WIDTH, starty, startx);\n");
	fprintf(script, "	wcolor_set(data_entry_window, COLOR_PAIR(1), 0);\n");
	fprintf(script, "	wattron(data_entry_window, COLOR_PAIR(1));\n");
	fprintf(script, "	wbkgd(data_entry_window, space | COLOR_PAIR(1));\n");
	fprintf(script, "	wattrset(data_entry_window, COLOR_PAIR(1));\n");
	fprintf(script, "	wmove(data_entry_window, 1, 1);\n");
	//fprintf(script, "       wrefresh(data_entry_window);\n");
	//fprintf(script, "	mvwprintw(data_entry_window, 1, 1, "data_entry_window: height: %d, width, %d"\n");
	//fprintf(script, "			, DATA_ENTRY_WINDOW_HEIGHT , DATA_ENTRY_WINDOW_WIDTH);\n");
	fprintf(script, "       keypad(data_entry_window, TRUE);\n");

	fprintf(script, "	// Divide the rest of the screen between the question window\n");
	fprintf(script, "	//  and the stub window in the ration 1:2\n");
	fprintf(script, "	int32_t height_left = maxY - DATA_ENTRY_WINDOW_HEIGHT;\n");
	fprintf(script, "	int32_t STUB_LIST_WINDOW_HEIGHT=(height_left / 3)*2, STUB_LIST_WINDOW_WIDTH=maxX;\n");
	//fprintf(script, "	mvwprintw(data_entry_window, 2, 1, "stub_list_window: height: %d, width, %d"\n");
	//fprintf(script, "			, STUB_LIST_WINDOW_HEIGHT , STUB_LIST_WINDOW_WIDTH);\n");
	fprintf(script, "	starty = maxY - DATA_ENTRY_WINDOW_HEIGHT - STUB_LIST_WINDOW_HEIGHT;\n");
	fprintf(script, "	stub_list_window = create_newwin(STUB_LIST_WINDOW_HEIGHT\n");
	fprintf(script, "			, STUB_LIST_WINDOW_WIDTH, starty, startx);\n");
	fprintf(script, "	wcolor_set(stub_list_window, 2, 0);\n");
	fprintf(script, "	wbkgd(stub_list_window, space | COLOR_PAIR(2));\n");
	fprintf(script, "	wattron(stub_list_window, COLOR_PAIR(2));\n");
	fprintf(script, "\n");
	//fprintf(script, "	mvwprintw(stub_list_window, 2, 1, "stub_list_window: height: %d, width, %d"\n");
	//fprintf(script, "			, STUB_LIST_WINDOW_HEIGHT , STUB_LIST_WINDOW_WIDTH);\n");
	//fprintf(script, "	wrefresh(stub_list_window);\n");
	fprintf(script, "\n");
	fprintf(script, "\n");

	fprintf(script, "	int32_t ERROR_WINDOW_HEIGHT= (height_left/6), ERROR_WINDOW_WIDTH=maxX;\n");
	fprintf(script, "	starty = maxY - DATA_ENTRY_WINDOW_HEIGHT - STUB_LIST_WINDOW_HEIGHT - ERROR_WINDOW_HEIGHT;\n");
	fprintf(script, "	error_msg_window = create_newwin(ERROR_WINDOW_HEIGHT\n");
	fprintf(script, "			, ERROR_WINDOW_WIDTH, starty, startx);\n");
	fprintf(script, "	wbkgd(error_msg_window, space | COLOR_PAIR(5));\n");
	fprintf(script, "	wcolor_set(error_msg_window, 3, 0);\n");
	fprintf(script, "	wattron(error_msg_window, COLOR_PAIR(5));\n");

	fprintf(script, " 	height_left -= ERROR_WINDOW_HEIGHT;\n");

	fprintf(script, "	int32_t QUESTION_WINDOW_HEIGHT=maxY - DATA_ENTRY_WINDOW_HEIGHT - STUB_LIST_WINDOW_HEIGHT - ERROR_WINDOW_HEIGHT, QUESTION_WINDOW_WIDTH=maxX;\n");
	fprintf(script, "	starty = 0;\n");
	fprintf(script, "	question_window = create_newwin(QUESTION_WINDOW_HEIGHT\n");
	fprintf(script, "			, QUESTION_WINDOW_WIDTH, starty, startx);\n");
	fprintf(script, "	wbkgd(question_window, space | COLOR_PAIR(3));\n");
	fprintf(script, "	wcolor_set(question_window, 3, 0);\n");
	fprintf(script, "	wattron(question_window, COLOR_PAIR(3));\n");

	//fprintf(script, "	mvwprintw(question_window, 1, 1, "question_window: height: %d, width, %d"\n");
	//fprintf(script, "			, QUESTION_WINDOW_HEIGHT , QUESTION_WINDOW_WIDTH);\n");
	//fprintf(script, "	wrefresh(question_window);\n");
	fprintf(script, "\n");
	//fprintf(script, "	wgetch(data_entry_window);\n");
	if(config_file_parser::PLATFORM == "LINUX"|| config_file_parser::PLATFORM == "UNIX"){
		fprintf(script, "	define_some_pd_curses_keys();\n");
	}
	fprintf(script, "	int32_t HELP_WINDOW_HEIGHT=(int)((float)(2/3)*maxY), HELP_WINDOW_WIDTH=maxX/2;\n");
	fprintf(script, "\n");
	fprintf(script, "       starty = 5;\n");
	fprintf(script, "       startx = 5;\n");
	fprintf(script, "	//help_window = create_newwin(HELP_WINDOW_HEIGHT, HELP_WINDOW_WIDTH, starty, startx);\n");

	fprintf(script, "	question_panel = new_panel(question_window);\n"
			"	stub_list_panel = new_panel(stub_list_window);\n"
			"	data_entry_panel = new_panel(data_entry_window);\n"
			"	//help_panel = new_panel(help_window);\n"
			"	error_msg_panel = new_panel(error_msg_window);\n"
			);
	fprintf(script, "	update_panels();\n"
			"	doupdate();\n");
	fprintf(script, "}\n");
	fprintf(script, "\n");
	fprintf(script, "\n");
	fprintf(script, "\n");
	fprintf(script, "WINDOW *create_newwin(int32_t height, int32_t width, int32_t starty, int32_t startx)\n");
	fprintf(script, "{       WINDOW *local_win;\n");
	fprintf(script, "\n");
	fprintf(script, "        local_win = newwin(height, width, starty, startx);\n");
	fprintf(script, "        box(local_win, 0 , 0);          /* 0, 0 gives default characters \n");
	fprintf(script, "                                         * for the vertical and horizontal\n");
	fprintf(script, "                                         * lines                        */\n");
	// no need for this once we are using panels
	//fprintf(script, "        wrefresh(local_win);            /* Show that box                */\n");
	fprintf(script, "\n");
	fprintf(script, "        return local_win;\n");
	fprintf(script, "}\n");
	fprintf(script, "\n");
}

void PrintDisplayActiveQuestions(FILE *script)
{
	fprintf(script, "void DisplayActiveQuestions()\n{\n\
			\tfor(int32_t i = 0; i<question_list.size(); ++i){\n\
			\t\tif(question_list[i]->isAnswered_)\n\
			\t\t\tcout << question_list[i]->questionName_ << \" \";\n\
			\t}\
			\tcout << endl;\n\
			\n}\n");
}

void PrintGetUserResponse(FILE *script)
{
	fprintf(script, "void GetUserResponse(string & qno, int32_t & qindex)\n{\n\
			char newl;\n\
			cin >> qno;cin.get(newl);\nqindex = 0;\n\
			cout << \"User input qno:\" << qno \n\
				<< \", newl: \" << newl << endl;\n\
			}\n");
}

bool skip_func_type_check(const char * fname)
{
	const char * skip_func_type_check_list[] = {"printf" };
	for(uint32_t i = 0; i < sizeof(skip_func_type_check_list)/sizeof(skip_func_type_check_list[0]); ++i){
		if(!strcmp(fname, skip_func_type_check_list[i])){
			return true;
		}
	}
	return false;
}

int32_t check_parameters(AbstractExpression* e, VariableList* v)
{
	debug_log_file << "check_parameters: called" << endl;
	AbstractExpression* e_ptr = e;
	VariableList* fparam = v;
	bool match = true;
	/* Important point to note: I am not allowing references in ordinary variable decl
	   Only in function parameter list - the object is to allow modifying of variables
	   in a function as in C++
	   */
	cerr << "Fix this function DOES NOT REPORT ERRORS using print_err"
	     << ", line: " << __LINE__
	     << ", file: " << __FILE__
	     << ", function: " << __PRETTY_FUNCTION__ << endl;
	int32_t chk_param_counter = 1;
	while(e_ptr && fparam) {
		//e_ptr->print();
		DataType etype = e_ptr->type_, fptype = fparam->variableType_;
		if((etype >= INT8_TYPE && etype <= DOUBLE_TYPE)
		   && ((fptype >= INT8_TYPE && fptype <= DOUBLE_TYPE)
		       || (fptype >= INT8_REF_TYPE && fptype <= DOUBLE_REF_TYPE))){
			DataType tdt = fptype;
				/* the code below makes a INT8_REF_TYPE -> INT8_TYPE
				   			a INT8_REF_TYPE -> INT8_TYPE
				 thats because we dont care much about references -> C++
				 does all the hard work. For checking types they are equivalent to us
				*/
			if(tdt >= INT8_REF_TYPE) tdt = DataType(INT8_TYPE+tdt-INT8_REF_TYPE);
			if(etype <= tdt) {
				debug_log_file << "varname: "<< fparam->variableName_ << " chk_param_counter: "
					<< chk_param_counter << " passed " << endl;
			}
		} else if ((etype >= INT8_ARR_TYPE&&etype <= DOUBLE_ARR_TYPE)
			   && (fptype >= INT8_ARR_TYPE&&fptype <= DOUBLE_ARR_TYPE)
			   && (etype == fptype)){
			debug_log_file << "varname: "<< fparam->variableName_ << " chk_param_counter: "
					<< chk_param_counter << " passed " << endl;
		} else {
			match = false;
			cerr << "Parameter type mismatch name: " << endl;
			cerr << fparam->variableName_ << " expected type is " << fparam->variableType_
				<< " passed type is " << e_ptr->type_
				<< " line_no: " << line_no << " or currently allowed promotion to: "
				<< e_ptr->type_+INT8_REF_TYPE
				<< endl;
			++no_errors;
		}
		e_ptr = e_ptr->next_;
		fparam = fparam->next_;
		chk_param_counter = chk_param_counter+1;
	}
	if(match == true){
		if(e_ptr == 0 && fparam == 0){
			match = true;
		} else {
			match = false;
			++no_errors;
			cerr << "NOTMATCHED: No of parameters in function call not matching with no of paramters in AbstractExpression: line_no"
				<< line_no << endl;
		}
	}
	if(!match){
		cerr << "function parameter type check FAILURE: line_no " << line_no << endl;
	}
	return match;
}


const char * file_exists_check_code()
{
	const char * file_check_code =
	"\tif (write_data_file_flag||write_qtm_data_file_flag||write_xtcc_data_file_flag) {\n"
	"\t	ser_no = read_a_serial_no();\n"
	"\t	if (ser_no == 0) {\n"
	"\t		break;\n"
	"\t	} \n"
	"\t} else {\n"
	"\t\tint exists = check_if_reg_file_exists(jno, ser_no);\n"
	"\t\tif(exists == 1){\n"
	"\t\t	load_data(jno,ser_no);\n"
	"\t\t	//merge_disk_data_into_questions(qscript_stdout, last_question_answered, last_question_visited);\n"
	"\t\t	merge_disk_data_into_questions2(qscript_stdout, last_question_answered, last_question_visited);\n"
	"\t\t}\n\t}\n";
	if (qscript_debug::MAINTAINER_MESSAGES){
		cerr << "fix me : add code for `if file is invalid` case "
			<< __func__ << "FILE: " << __FILE__
			<< ", line: " << __LINE__ << endl;
	}

	return file_check_code;
}


AbstractStatement* setup_stub_manip_stmt(DataType dt
					 , char* stub_list_name
					 , char * question_name
					 , AbstractExpression * l_arr_index /* =0 */)
{
	int32_t index = -1;
	bool question_stub = false, range_stub=false;
	NamedStubQuestion * lhs_question = 0, * rhs_question=0;
	named_range * lhs_stub = 0;
	for(int32_t i = 0; i < named_stubs_list.size(); ++i){
		named_range * nr_ptr = named_stubs_list[i];
		if(nr_ptr->name == stub_list_name){
			index = i;
			range_stub = true;
			lhs_stub = nr_ptr;
			break;
		}
	}
	// at this point lhs_stub is valid
	for(int32_t i = 0; i < question_list.size(); ++i){
		if(question_list[i]->questionName_  ==  stub_list_name){
			index = i;
			question_stub = true;
			lhs_question = dynamic_cast<NamedStubQuestion*>(question_list[i]);
			if (!lhs_question) {
				stringstream err_text;
				err_text << "Question : " << stub_list_name <<
					"is not a named stub Question";
				print_err(compiler_sem_err, err_text.str(),
					line_no, __LINE__, __FILE__);
				return new ErrorStatement(line_no);
			}
			break;
		}
	}

	if(index == -1){
		stringstream err_text;
		err_text << "named stub list does not exist: " << stub_list_name;
		print_err(compiler_sem_err, err_text.str(),
				line_no, __LINE__, __FILE__);
		return new ErrorStatement(line_no);
	}
	// at this point
	// 	1. if lhs_question is not null it is valid and
	// 	2. we need not do any more checks on the 1st argument


	int32_t index_question = -1;
	for(int32_t i = 0; i < question_list.size(); ++i){
		if(question_list[i]->questionName_  ==  question_name){
			index_question = i;
			rhs_question = dynamic_cast<NamedStubQuestion*>(question_list[i]);
			if (!rhs_question) {
				stringstream err_text;
				err_text << "Question : " << question_name <<
					"is not a named stub Question";
				print_err(compiler_sem_err, err_text.str(),
					line_no, __LINE__, __FILE__);
				return new ErrorStatement(line_no);
			}
			break;
		}
	}
	// 	At this point if rhs_question is not null it is a named stub question
	if(index_question == -1){
		stringstream err_text;
		err_text << "Question does not exist: " << question_name;
		print_err(compiler_sem_err, err_text.str(),
			line_no, __LINE__, __FILE__);
		return new ErrorStatement(line_no);
	} 
	// At this point 2nd argument  is valid

	if (range_stub == true) {
		if(!(rhs_question->nr_ptr->name == stub_list_name) ){
			stringstream err_text;
			err_text << "Question: " << question_name
				<< " named range: " << rhs_question->nr_ptr->name
				<< " and named stub is : " << stub_list_name
				<< " do not match"
				<< endl;
			print_err(compiler_sem_err, err_text.str(),
				line_no, __LINE__, __FILE__);
			return new ErrorStatement(line_no);
		}
		if (l_arr_index==0) {
			struct AbstractStatement* st_ptr = new StubManipStatement(dt,
				line_no, lhs_stub, rhs_question);
			return st_ptr;
		} else {
			struct AbstractStatement* st_ptr = new StubManipStatement(dt,
				line_no, lhs_stub, rhs_question, l_arr_index);
			return st_ptr;
		}
	} else if (question_stub == true) {
		if(!(rhs_question->nr_ptr->name == lhs_question->nr_ptr->name) ){
			stringstream err_text;
			err_text << "1st arg Question: " << lhs_question->questionName_
				<< " named range: " << lhs_question->nr_ptr->name
				<< " and : " 
				<< " 2nd arg Question: " << rhs_question->questionName_
				<< " named range: " << rhs_question->nr_ptr->name
				<< " do not match" << endl;
			print_err(compiler_sem_err, err_text.str(),
				line_no, __LINE__, __FILE__);
			return new ErrorStatement(line_no);
		}
		if (l_arr_index==0) {
			struct AbstractStatement* st_ptr = new StubManipStatement(dt,
				line_no, lhs_question, rhs_question);
			return st_ptr;
		} else {
			struct AbstractStatement* st_ptr = new StubManipStatement(dt,
				line_no, lhs_question, rhs_question, l_arr_index);
			return st_ptr;
		}

	}
	return new ErrorStatement(line_no);
}


AbstractStatement* setup_stub_manip_stmt_set_unset(DataType dt
						   , char* stub_list_name)
{
	int32_t index = -1;
	for(int32_t i = 0; i < named_stubs_list.size(); ++i){
		named_range * nr_ptr = named_stubs_list[i];
		if(nr_ptr->name == stub_list_name){
			index = i;
			break;
		}
	}
	if(index == -1){
		stringstream err_text;
		err_text << "named stub list does not exist: " << stub_list_name;
		print_err(compiler_sem_err, err_text.str(),
			line_no, __LINE__, __FILE__);
	}
	struct AbstractStatement* st_ptr = new StubManipStatement(dt,
		line_no, stub_list_name);

	return st_ptr;
}

AbstractStatement* setup_stub_manip_stmt(DataType dt
					 , char* stub_list_name
					 , XtccSet & l_xs)
{
	stringstream warn_mesg;
	warn_mesg << " The code below is common in the setup_stub_manip_stmt functions and should be factored out";
	//cerr << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
	//	<< warn_mesg.str() << endl;

	LOG_MAINTAINER_MESSAGE(warn_mesg.str());
	int32_t index = -1;
	bool question_stub = false, range_stub=false;
	NamedStubQuestion * lhs_question = 0;
	named_range * lhs_stub = 0;
	for (int32_t i = 0; i < named_stubs_list.size(); ++i) {
		named_range * nr_ptr = named_stubs_list[i];
		if(nr_ptr->name == stub_list_name){
			index = i;
			range_stub = true;
			lhs_stub = nr_ptr;
			break;
		}
	}
	// at this point lhs_stub is valid
	for (int32_t i = 0; i < question_list.size(); ++i) {
		if(question_list[i]->questionName_  ==  stub_list_name){
			index = i;
			question_stub = true;
			lhs_question = dynamic_cast<NamedStubQuestion*>(question_list[i]);
			if (!lhs_question) {
				stringstream err_text;
				err_text << "Question : " << stub_list_name <<
					"is not a named stub Question";
				print_err(compiler_sem_err, err_text.str(),
					line_no, __LINE__, __FILE__);
				return new ErrorStatement(line_no);
			}
			break;
		}
	}

	if(index == -1){
		stringstream err_text;
		err_text << "named stub list does not exist: " << stub_list_name;
		print_err(compiler_sem_err, err_text.str(),
				line_no, __LINE__, __FILE__);
		return new ErrorStatement(line_no);
	}
	// at this point
	// 	1. if lhs_question is not null it is valid and
	// 	2. we need not do any more checks on the 1st argument
	if (range_stub == true) {
		struct AbstractStatement* st_ptr = new StubManipStatement(dt,
						line_no, lhs_stub, l_xs);
		return st_ptr;
	} else if (question_stub == true) {
		struct AbstractStatement* st_ptr = new StubManipStatement(dt,
						line_no, lhs_question, l_xs);
		return st_ptr;
	}
	return new ErrorStatement(line_no);
}

const char * write_data_to_disk_code()
{
	const char * write_data_disk_code =
	"\tvoid write_data_to_disk(const vector<AbstractQuestion*>& q_vec\n"
	"\t	, string jno\n"
	"\t	, int32_t ser_no) {\n"
	"\t	stringstream fname_str;\n"
	"\t	fname_str << jno << \"_\" << ser_no << \".dat\";\n"
	"\t	//FILE * fptr = fopen(fname_str.str().c_str(), \"w+b\");\n"
	"\t\n"
	"\t\n"
	"\t	std::ofstream data_file;\n"
	"\t	data_file.exceptions(std::ios::failbit | std::ios::badbit);\n"
	"\t	data_file.open(fname_str.str().c_str(), ios_base::ate);\n"
	"\tchar outstr[500];\n"
	"\tmemset (outstr, 0, 500);\n"
	"\ttime_t t = time(NULL);\n"
	"\tstruct tm *tmp = localtime(&t);\n"
	"\tif (tmp == NULL) {\n"
	"\tperror(\"localtime\");\n"
	"\texit(EXIT_FAILURE);\n"
	"\t}\n"
                                                           
	"\tif (strftime(outstr, sizeof(outstr), \"%Y%m%d_%H%M%S\", tmp) == 0) {\n"
	"\tfprintf(stderr, \"strftime returned 0\");\n"
	"\texit(EXIT_FAILURE);\n"
	"\t}\n"


	"\t\n"
	"\t	for(int32_t i = 0; i < question_list.size(); ++i){\n"
	"\t		question_list[i]->WriteDataToDisk(data_file, string(outstr), jno, ser_no);\n"
	"\t		/*\n"
	"\t		fprintf(fptr, \"%s: \", question_list[i]->name.c_str());\n"
	"\t		for( set<int32_t>::iterator iter = question_list[i]->input_data.begin();\n"
	"\t				iter != question_list[i]->input_data.end(); ++iter){\n"
	"\t			fprintf(fptr, \"%d \", *iter);\n"
	"\t		}\n"
	"\t		fprintf(fptr, \"\n\");\n"
	"\t		question_list[i]->input_data.clear();\n"
	"\t		*/\n"
	"\t	}\n"
	"\t	data_file.flush();\n"
	"\t	data_file.close();\n"
	"\t	//fclose(fptr);\n"
	"\t}\n"
	"\n";
	return write_data_disk_code;
}


void print_array_question_class(FILE* script)
{
	fprintf(script, "class ArrayQuestion\n");
	fprintf(script, "{\n");
	fprintf(script, "public: \n");
	fprintf(script, "\tvector<AbstractQuestion*> questionList;\n");
	fprintf(script, "\tvector<int32_t> arrayBounds;\n");
	fprintf(script, "\tArrayQuestion(vector<int32_t>& l_arrayBounds): arrayBounds(l_arrayBounds)\n");
	fprintf(script, "\t{\n");
	fprintf(script, "\t\tint bounds = 1;\n");
	fprintf(script, "\t\tfor(int32_t i = 0; i<arrayBounds.size(); ++i){\n");
	fprintf(script, "\t\t\tbounds*=arrayBounds[i];\n");
	fprintf(script, "\t\t}\n");
	fprintf(script, "\t\tquestionList.reserve(bounds);\n");
	fprintf(script, "\t}\n");
	fprintf(script, "};\n\n");

}



void PrintActiveVariablesAtScope(vector <Scope*> & active_scope_list
				 , vector <ActiveVariableInfo*> & output_info)
{
	for(uint32_t i = 0; i< active_scope_list.size(); ++i){
		Scope* sc_ptr= active_scope_list[i];
		sc_ptr->print_scope(output_info);
		//sc_ptr->print_scope(name, active_push_vars, active_pop_vars);
	}
}

void PrintSignalHandler(FILE * script, bool ncurses_flag)
{
	fprintf(script, "static void sig_usr(int32_t signo)\n");
	fprintf(script, "{\n");
	fprintf(script, "	if(signo == SIGSEGV){\n");
	fprintf(script, "		printf(\"received SIGSEGV\\n\");\n");
	fprintf(script, "	} else if(signo == SIGILL){\n");
	fprintf(script, "		printf(\"received SIGILL\\n\");\n");
	fprintf(script, "	} else {\n");
	fprintf(script, "		fprintf(stderr, \"received signal : %%d\\n\", signo);\n");
	fprintf(script, "	}\n");
	fprintf(script, "	fflush(qscript_stdout);\n");
	if (ncurses_flag) {
		fprintf(script, "	 endwin();\n");
	}
	fprintf(script, "	exit(1);\n");
	fprintf(script, "}\n");
}

void PrintSetupSignalHandler(FILE * script)
{
	fprintf(script, "void SetupSignalHandler()\n{\n");
	fprintf(script, "	if(signal(SIGSEGV, sig_usr) == SIG_ERR){\n");
	fprintf(script, "		fprintf(stderr, \"cannot catch SIGSEGV\\n\");\n");
	fprintf(script, "		exit(1);\n");
	fprintf(script, "	}  else if(signal(SIGILL, sig_usr) == SIG_ERR){\n");
	fprintf(script, "		fprintf(stderr, \"cannot catch SIGILL\\n\");\n");
	fprintf(script, "		exit(1);\n");
	fprintf(script, "	}\n");
	fprintf(script, "}\n\n");
}

// Returns 0 on failure, 1 on success
int32_t ReadQScriptConfig()
{
	cerr << "Enter qscript_parser::ReadQScriptConfig" << endl;
	using namespace std;
	//string QSCRIPT_HOME = getenv("QSCRIPT_HOME");
	string QSCRIPT_HOME = program_options_ns::QSCRIPT_HOME;
	string::size_type contains_space = QSCRIPT_HOME.find_last_of(" ");
	if (contains_space != string::npos) {
		QSCRIPT_HOME.erase(contains_space);
	}
	string QSCRIPT_CONFIG = QSCRIPT_HOME + "/config/qscript.config";
	FILE * qscript_confin = fopen(QSCRIPT_CONFIG.c_str(), "rb");
	qscript_confrestart(qscript_confin);
	if(!qscript_confin){
		cout << "unable to open " <<  QSCRIPT_CONFIG <<" for reading ... exiting\n";
		return 0;
	}
	cerr << "opened : " << QSCRIPT_CONFIG << endl;

	if(!qscript_confparse()){
		cout << "Successfully parsed " << QSCRIPT_CONFIG << endl;
	} else {
		cerr << "there were errors in parsing configuration file" << QSCRIPT_CONFIG << endl;
		return 0;
	}
	cout << "qscript.config: values are : " << endl
		<< "NCURSES_INCLUDE_DIR: " << config_file_parser::NCURSES_INCLUDE_DIR << endl
		<< "NCURSES_LIB_DIR: " << config_file_parser::NCURSES_LIB_DIR << endl
		<< "NCURSES_LINK_LIBRARY_NAME: " << config_file_parser::NCURSES_LINK_LIBRARY_NAME << endl
		<< "PLATFORM: " << config_file_parser::PLATFORM << endl
		<< endl;
	if(config_file_parser::PLATFORM == "WINDOWS"
	   || config_file_parser::PLATFORM == "LINUX"
	   || config_file_parser::PLATFORM == "UNIX"
		){
	} else {
		cerr << "Unknown platform ... please set it to one of\
			LINUX, UNIX, WINDOWS ... exiting\n";
		exit(1);
	}

	return 1;
}

// ReadQScriptConfig would have already been called
// before this function is invoked - we work on that assumuption
void CompileGeneratedCode(const string & src_file_name)
{
	if(qscript_debug::DEBUG_qscript_parser)
		cerr << "ENTER qscript_parser::CompileGeneratedCode" << endl;

	/*
# You will need to modify the variable below
#QSCRIPT_HOME=/media/sda3/home/nxd/xtcc_sourceforge_copy/xtcc/xtcc/qscript/stubs/simple_compiler
# if you have setup everything under ../INSTALL_CUSTOM.readme the you will not need to change
#the variables below
# when running the generated exe you will need to use
# LD_LIBRARY_PATH=$(QSCRIPT_RUNTIME) ./test_script

QSCRIPT_RUNTIME=$(QSCRIPT_HOME)/lib
QSCRIPT_INCLUDE_DIR=$(QSCRIPT_HOME)/include

test_script: test_script.o
	$(CXX) -g -o $@ -L$(QSCRIPT_RUNTIME) test_script.o -lqscript_runtime -lreadline

test_script.o: test_script.C
	$(CXX) -I$(QSCRIPT_INCLUDE_DIR) -g -c $<
	*/
	string executable_file_name = ExtractBaseFileName(src_file_name);
	string intermediate_file_name = executable_file_name + ".C";
	executable_file_name += ".exe";
	string QSCRIPT_HOME = getenv("QSCRIPT_HOME");
	cout << "QSCRIPT_HOME: " << QSCRIPT_HOME << endl;
	string QSCRIPT_RUNTIME = QSCRIPT_HOME + "/lib";
	cout << "QSCRIPT_RUNTIME: " << QSCRIPT_RUNTIME << endl;

	string QSCRIPT_INCLUDE_DIR = QSCRIPT_HOME + "/include";
	string cpp_compile_command ;
	if (program_options_ns::ncurses_flag) {
		cpp_compile_command = string("g++ -g -o ")
			+ executable_file_name + string(" -L") + QSCRIPT_RUNTIME
			+ string(" -I") + QSCRIPT_INCLUDE_DIR
			+ string(" -I") + config_file_parser::NCURSES_INCLUDE_DIR
			+ string(" -L") + config_file_parser::NCURSES_LIB_DIR
			+ string(" ") + intermediate_file_name
			+ string(" -lqscript_runtime -lpanel ")
			+ string(" -l") + config_file_parser::NCURSES_LINK_LIBRARY_NAME;
	} else if (program_options_ns::web_server_flag) {
		cpp_compile_command = string("g++ -g -o ")
			+ executable_file_name + string(" -L") + QSCRIPT_RUNTIME
			+ string(" -I") + QSCRIPT_INCLUDE_DIR
			+ string(" -I") + config_file_parser::NCURSES_INCLUDE_DIR
			+ string(" -L") + config_file_parser::NCURSES_LIB_DIR
			+ string(" ") + intermediate_file_name
			+ string(" -lmicrohttpd -lpanel -lncurses -lqscript_runtime");
	}
	cout << "cpp_compile_command: " << cpp_compile_command << endl;
	//int32_t ret_val = 0;
	int32_t ret_val = system(cpp_compile_command.c_str());
	if(ret_val != 0){
		cerr << "Failed in compiling generated code : test_script.C ";
	} else {
		cout 	<< endl
			<< "Generated executable. You can run it by\n shell_prompt> LD_LIBRARY_PATH=$QSCRIPT_HOME/lib ./"
			<<  executable_file_name
			<< endl
			<< endl;
	}
}

void CompileGeneratedCodeStatic(const string & src_file_name)
{
	cerr << "ENTER qscript_parser::CompileGeneratedCodeStatic" << endl;

	/*
# You will need to modify the variable below
#QSCRIPT_HOME=/media/sda3/home/nxd/xtcc_sourceforge_copy/xtcc/xtcc/qscript/stubs/simple_compiler
# if you have setup everything under ../INSTALL_CUSTOM.readme the you will not need to change
#the variables below
# when running the generated exe you will need to use
# LD_LIBRARY_PATH=$(QSCRIPT_RUNTIME) ./test_script

QSCRIPT_RUNTIME=$(QSCRIPT_HOME)/lib
QSCRIPT_INCLUDE_DIR=$(QSCRIPT_HOME)/include

test_script: test_script.o
	$(CXX) -g -o $@ -L$(QSCRIPT_RUNTIME) test_script.o -lqscript_runtime -lreadline

test_script.o: test_script.C
	$(CXX) -I$(QSCRIPT_INCLUDE_DIR) -g -c $<
	*/
	string executable_file_name = ExtractBaseFileName(src_file_name);
	string intermediate_file_name = executable_file_name + ".C";
	executable_file_name += ".exe";
	string QSCRIPT_HOME = getenv("QSCRIPT_HOME");
	string::size_type contains_space = QSCRIPT_HOME.find_last_of(" ");
	if (contains_space != string::npos) {
		QSCRIPT_HOME.erase(contains_space);
	}
	cout << "QSCRIPT_HOME: " << QSCRIPT_HOME << endl;
	string QSCRIPT_RUNTIME = QSCRIPT_HOME + "/lib";
	cout << "QSCRIPT_RUNTIME: " << QSCRIPT_RUNTIME << endl;
	/*
	string QSCRIPT_INCLUDE_DIR = QSCRIPT_HOME + "/include";
	string cpp_compile_command = string("c:\\MinGW\\bin\\g++ -static -g -o ")
				+ executable_file_name
				+ string(" -L") + QSCRIPT_RUNTIME
				+ string(" -L") + QSCRIPT_CURSES_LIB_DIR
				+ string(" -I") + QSCRIPT_INCLUDE_DIR
				+ string(" -I") + QSCRIPT_CURSES_INCLUDE_DIR
				+ string(" ") + intermediate_file_name
				+ string(" -lqscript_runtime -lpdcurses ");
	*/

	string QSCRIPT_INCLUDE_DIR = QSCRIPT_HOME + "/include";
	string cpp_compile_command = string("g++ -static -g -o ")
			+ executable_file_name + string(" -L") + QSCRIPT_RUNTIME
			+ string(" -I") + QSCRIPT_INCLUDE_DIR
			+ string(" -I") + config_file_parser::NCURSES_INCLUDE_DIR
			+ string(" -L") + config_file_parser::NCURSES_LIB_DIR
			+ string(" ") + intermediate_file_name
			+ string(" -lqscript_runtime ")
			+ string(" -l") + config_file_parser::NCURSES_LINK_LIBRARY_NAME;

	cout << "cpp_compile_command: " << cpp_compile_command << endl;
	//int32_t ret_val = 0;
	int32_t ret_val = system(cpp_compile_command.c_str());
	if(ret_val != 0){
		cerr << "Failed in compiling generated code : test_script.C ";
	} else {
		cout << "Generated executable. You can run it by\n shell_prompt> LD_LIBRARY_PATH=$QSCRIPT_HOME/lib ./"
			 <<  executable_file_name
			<< endl;
	}
}

void PrintDefineSomePDCursesKeys(FILE * script)
{
	fprintf(script, "void define_some_pd_curses_keys()\n");
	fprintf(script, "{\n\
			string ctrl_left_arrow;\n\
			ctrl_left_arrow.append(1, 27);\n\
			ctrl_left_arrow.append(1, 91);\n\
			ctrl_left_arrow.append(1, 49);\n\
			ctrl_left_arrow.append(1, 59);\n\
			ctrl_left_arrow.append(1, 53);\n\
			ctrl_left_arrow.append(1, 68);\n\
			\n\
			string ctrl_right_arrow;\n\
			ctrl_right_arrow.append(1, 27);\n\
			ctrl_right_arrow.append(1, 91);\n\
			ctrl_right_arrow.append(1, 49);\n\
			ctrl_right_arrow.append(1, 59);\n\
			ctrl_right_arrow.append(1, 53);\n\
			ctrl_right_arrow.append(1, 67);\n\
			string ctl_del;\n\
			ctl_del.append(1, 27);\n\
			ctl_del.append(1, 91);\n\
			ctl_del.append(1, 51);\n\
			ctl_del.append(1, 59);\n\
			ctl_del.append(1, 53);\n\
			ctl_del.append(1, 126);\n\
			string alt_del;\n\
			alt_del.append(1, 27);\n\
			alt_del.append(1, 91);\n\
			alt_del.append(1, 51);\n\
			alt_del.append(1, 59);\n\
			alt_del.append(1, 51);\n\
			alt_del.append(1, 126);\n\
			\n\
			string shift_del;\n\
			shift_del.append(1, 27);\n\
			shift_del.append(1, 91);\n\
			shift_del.append(1, 51);\n\
			shift_del.append(1, 59);\n\
			shift_del.append(1, 50);\n\
			shift_del.append(1, 126);\n\
			define_key(ctrl_left_arrow.c_str(), CTL_LEFT);\n\
			define_key(ctrl_right_arrow.c_str(), CTL_RIGHT);\n\
			define_key(ctl_del.c_str(), CTL_DEL);\n\
			define_key(alt_del.c_str(), ALT_DEL);\n\
			define_key(shift_del.c_str(), SHF_DC);\n\
		}\n");
}

void PrintPDCursesKeysHeader(FILE * script)
{
	fprintf(script, "\
			#ifndef a_few_pd_curses_keys_h\n\
			#define a_few_pd_curses_keys_h\n\
			#define CTL_LEFT 	0x1bb\n\
			#define CTL_RIGHT 	0x1bc\n\
			#define CTL_DEL 	0x20f\n\
			#define ALT_DEL 	0x1de\n\
			#undef KEY_SDC /* redefined as per PD curses below */\n\
			#define SHF_DC 		0x21a\n\
			#endif /* a_few_pd_curses_keys_h */\n\
			");
}

void PrintProcessOptions(FILE * script)
{
	fprintf(script, "int process_options(int argc, char * argv[])\n");
	fprintf(script, "{\n");
	fprintf(script, "	//int32_t opterr=1, c;\n");
	fprintf(script, "	extern int32_t optind, opterr, optopt;\n");
	fprintf(script, "	extern char * optarg;\n");
	fprintf(script, "	int c;\n");
	fprintf(script, "	while ( (c = getopt(argc, argv, \"x::w::q::\")) != -1) {\n");
	fprintf(script, "		char ch = optopt;\n");
	fprintf(script, "		switch (c) {\n");

	fprintf(script, "		case 'w': {\n");
	fprintf(script, "			  write_data_file_flag = true;\n");
	fprintf(script, "			  if (optarg) {\n");
	fprintf(script, "				  output_data_file_name = optarg;\n");
	fprintf(script, "			  } else {\n");
	fprintf(script, "				  output_data_file_name = \"datafile.dat\";\n");
	fprintf(script, "			  }\n");
	fprintf(script, "		}\n");
	fprintf(script, "		break;\n");


	fprintf(script, "		case 'x': {\n");
	fprintf(script, "			  write_xtcc_data_file_flag = true;\n");
	fprintf(script, "			  if (optarg) {\n");
	fprintf(script, "				  output_xtcc_data_file_name = optarg;\n");
	fprintf(script, "			  } else {\n");
	fprintf(script, "				  output_xtcc_data_file_name = \"xtcc_datafile.dat\";\n");
	fprintf(script, "			  }\n");
	fprintf(script, "		}\n");
	fprintf(script, "		break;\n");

	fprintf(script, "		case 'q': {\n");
	fprintf(script, "			  write_qtm_data_file_flag = true;\n");
	fprintf(script, "			  if (optarg) {\n");
	fprintf(script, "				  output_qtm_data_file_name = optarg;\n");
	fprintf(script, "			  } else {\n");
	fprintf(script, "				  output_qtm_data_file_name = \"qtm_datafile.dat\";\n");
	fprintf(script, "			  }\n");
	fprintf(script, "		}\n");
	fprintf(script, "		break;\n");
	fprintf(script, "		case '?' : {\n");
	fprintf(script, "				   cout << \" invalid option, optopt:\" << optopt << endl;\n");
	fprintf(script, "				   exit(1);\n");
	fprintf(script, "			   }\n");
	fprintf(script, "			  break;\n");
	fprintf(script, "		default:\n");
	fprintf(script, "			  cerr << \"invalid options: ch: \" << ch << \", c: \" << c << endl;\n");
	fprintf(script, "		}\n");
	fprintf(script, "	}\n");
	fprintf(script, "	cout << \"output_data_file_name: \" << output_data_file_name << endl;\n");
	fprintf(script, "	cout << \"write_data_file_flag: \" << write_data_file_flag << endl;\n");
	fprintf(script, "	cout << \"output_qtm_data_file_name: \" << output_qtm_data_file_name << endl;\n");
	fprintf(script, "	cout << \"write_qtm_data_file_flag: \" << write_qtm_data_file_flag << endl;\n");
	fprintf(script, "	//exit(1);\n");
	fprintf(script, "}\n");
}

void PrintPrintMapHeader(FILE * script)
{
	fprintf(script, "\tvoid print_map_header(fstream & map_file )\n{\n");
	fprintf(script, "map_file << \"Question No\t\t\t,width,\tno responses,\tstart position,\tend position\\n\";\n");
	fprintf(script, "}\n");
}

void PrintNCursesMain (FILE * script, bool ncurses_flag)
{
	fprintf(script, "int32_t main(int argc, char * argv[]){\n");
	fprintf(script, "\tprocess_options(argc, argv);\n");
	//fprintf(script, "\tDIR * directory_ptr = 0;\n");
	fprintf(script, "\tif (write_data_file_flag||write_qtm_data_file_flag||write_xtcc_data_file_flag) {\n");
	fprintf(script, "\t	qtm_data_file_ns::init();\n");
	fprintf(script, "\t	qtm_data_file_ns::init_exceptions();\n");
	fprintf(script, "\t	directory_ptr = opendir(\".\");\n");
	fprintf(script, "\t	if (! directory_ptr) {\n");
	fprintf(script, "\t		cout << \" unable to open . (current directory) for reading\\n\";\n");
	fprintf(script, "\t		exit(1);\n");
	fprintf(script, "\t	}\n");
	fprintf(script, "\t}\n");
	fprintf(script, "bool using_ncurses = %s;\n", (ncurses_flag) ?  "true": "false");
	fprintf(script, "qscript_stdout = fopen(qscript_stdout_fname.c_str(), \"w\");\n");
	fprintf(script, "	using namespace std;\n");

	/*
	fprintf(script, "	WINDOW 	* question_window = 0,\n"
			"		* stub_list_window = 0,\n"
			"		* data_entry_window = 0,\n"
			"		* help_window = 0;\n"
			);
	fprintf(script, "	PANEL 	* question_panel = 0,\n"
			"		* stub_list_panel = 0,\n"
			"		* data_entry_panel = 0,\n"
			"		* help_panel = 0;\n");
	*/

	if(ncurses_flag) {
		fprintf(script, "	SetupNCurses(question_window, stub_list_window, data_entry_window, error_msg_window, help_window, question_panel, stub_list_panel, data_entry_panel, error_msg_panel, help_panel);\n");
		fprintf(script, "	if(question_window == 0 || stub_list_window == 0 || data_entry_window == 0\n\t\t /* || help_window == 0 */\n\t\t ){\n");
		fprintf(script, "		cerr << \"Unable to create windows ... exiting\" << endl;\n");
		fprintf(script, "		return 1;\n");
		fprintf(script, "	}\n");
	}
	fprintf(script, "	SetupSignalHandler();\n");
	fprintf(script, "TheQuestionnaire theQuestionnaire;\n"
			"theQuestionnaire.base_text_vec.push_back(BaseText(\"All Respondents\"));\n"
			"theQuestionnaire.compute_flat_file_map_and_init();\n"
			"theQuestionnaire.eval();\n");
	fprintf(script, "	for (int i=0; i<question_list.size(); ++i) {\n");
	fprintf(script, "		delete question_list[i];\n");
	fprintf(script, "		question_list[i] = 0;\n");
	fprintf(script, "	}\n");
	fprintf(script, "clear_previous_data();\n");

	fprintf(script, "\n} /* close main */\n");
}

void PrintComputeFlatFileMap(StatementCompiledCode & compute_flat_map_code)
{
	compute_flat_map_code.program_code << "void compute_flat_file_map_and_init()\n{\n";
	compute_flat_map_code.program_code 
		<< "if (write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)\n"
		<< "{\n"
		<< "\tint current_map_pos = 0;\n"
		<< "\tint current_xtcc_map_pos = 0;\n";
	compute_flat_map_code.program_code << "\tif (write_qtm_data_file_flag) {\n"
		<< "\t\tqtm_datafile_conf_parser_ns::load_config_file(jno);\n"
		<< "\t\tqtm_data_file.Initialize();\n"
		<< "\t}\n";

	compute_flat_map_code.program_code << "\tif (write_data_file_flag) {\n";
	compute_flat_map_code.program_code << "		stringstream asc_datafile_conf_str;\n";
	compute_flat_map_code.program_code << "		asc_datafile_conf_str << jno \n";
	compute_flat_map_code.program_code << "			<< \".asc_data.conf\";\n";
	compute_flat_map_code.program_code << "		fstream asc_datafile_conf(asc_datafile_conf_str.str().c_str(), ios_base::in);\n";
	compute_flat_map_code.program_code << "		if (!asc_datafile_conf) {\n";
	compute_flat_map_code.program_code << "			cerr << \" could not open : \" << asc_datafile_conf_str.str() \n";
	compute_flat_map_code.program_code << "				<< \" for reading\" << endl;\n";
	compute_flat_map_code.program_code << "			exit(1);\n";
	compute_flat_map_code.program_code << "		}\n";
	compute_flat_map_code.program_code << "		string ser_no_token; string equal_token; ser_no_pos=-1; string semi_colon_token;\n";
	compute_flat_map_code.program_code << "		asc_datafile_conf >> ser_no_token;\n";
	compute_flat_map_code.program_code << "		if ( ser_no_token != string(\"SER_NO_COLS\")) {\n";
	compute_flat_map_code.program_code << "			cerr << \"expected token SER_NO_COLS\" << endl;\n";
	compute_flat_map_code.program_code << "			exit(1);\n";
	compute_flat_map_code.program_code << "		}\n";
	compute_flat_map_code.program_code << "		asc_datafile_conf >> equal_token;\n";

	compute_flat_map_code.program_code << "		if (equal_token != string(\"=\") ) {\n";
	compute_flat_map_code.program_code << "			cerr << \"expected token =\" << endl;\n";
	compute_flat_map_code.program_code << "			exit(1);\n";
	compute_flat_map_code.program_code << "		}\n";
	compute_flat_map_code.program_code << "		asc_datafile_conf >> ser_no_pos;\n";
	compute_flat_map_code.program_code << "		if (ser_no_pos == -1) {\n";
	compute_flat_map_code.program_code << "			cerr << \"invalid no of positions reserved for serial no: \";\n";
	compute_flat_map_code.program_code << "			exit(1);\n";
	compute_flat_map_code.program_code << "		}\n";
	compute_flat_map_code.program_code << "		current_map_pos += ser_no_pos;\n";
	compute_flat_map_code.program_code << "	}\n";

	compute_flat_map_code.program_code << "\tif (write_xtcc_data_file_flag) {\n";
	compute_flat_map_code.program_code << "\t\tcurrent_xtcc_map_pos += 4; // serial no is 4 bytes fixed\n";
	compute_flat_map_code.program_code << "\t}\n";


	tree_root->Generate_ComputeFlatFileMap(compute_flat_map_code);

	compute_flat_map_code.program_code << "\tstring map_file_name(jno + string(\".map\"));\n";
	compute_flat_map_code.program_code << "\tfstream map_file(map_file_name.c_str(), ios_base::out|ios_base::ate);\n";
	compute_flat_map_code.program_code << "\t print_map_header(map_file);\n";
	compute_flat_map_code.program_code << "\tfor (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {\n"
		<< "\t\tascii_flatfile_question_disk_map[i]->print_map(map_file);\n"
		<< "\t}\n";
	print_write_spss_file_for_ascii_data_to_disk(compute_flat_map_code);
	compute_flat_map_code.program_code << "\tstring xtcc_map_file_name(jno + string(\".xmap\"));\n";
	compute_flat_map_code.program_code << "\tfstream xtcc_map_file(xtcc_map_file_name.c_str(), ios_base::out|ios_base::ate);\n";
	compute_flat_map_code.program_code << "\tprint_map_header(xtcc_map_file);\n";
	compute_flat_map_code.program_code 
		<< "\tfor (int i=0; i<xtcc_question_disk_map.size(); ++i) {\n"
		<< "\t\txtcc_question_disk_map[i]->print_map(xtcc_map_file);\n"
		<< "\t}\n";

	compute_flat_map_code.program_code << "\tlen_flat_file_output_buffer = current_map_pos+1;\n";
	compute_flat_map_code.program_code << "\tlen_xtcc_datafile_output_buffer = current_xtcc_map_pos+1;\n";
	compute_flat_map_code.program_code << "\tflat_file_output_buffer = new char[len_flat_file_output_buffer];\n";
	compute_flat_map_code.program_code << "\txtcc_datafile_output_buffer = new char[len_xtcc_datafile_output_buffer];\n";
	compute_flat_map_code.program_code << "\tmemset(flat_file_output_buffer, ' ', len_flat_file_output_buffer-1);\n";
	compute_flat_map_code.program_code << "\tmemset(xtcc_datafile_output_buffer, '\\0', len_xtcc_datafile_output_buffer-1);\n";
	compute_flat_map_code.program_code << "\tflat_file_output_buffer[len_flat_file_output_buffer-1] = 0;\n";
	compute_flat_map_code.program_code << "\txtcc_datafile_output_buffer[len_xtcc_datafile_output_buffer-1] = 0;\n";
	compute_flat_map_code.program_code << "\tstring flat_file_name(jno + string(\".dat\"));\n";
	compute_flat_map_code.program_code << "\tflat_file.open(flat_file_name.c_str(), ios_base::out | ios_base::trunc);\n";
	compute_flat_map_code.program_code << "\tstring xtcc_datafile_name(jno + string(\".xdat\"));\n";
	compute_flat_map_code.program_code << "\txtcc_datafile.open(xtcc_datafile_name.c_str(), ios_base::out | ios_base::trunc | ios_base::binary);\n";

	if (config_file_parser::PLATFORM != "WINDOWS") {
		compute_flat_map_code.program_code 
			<< "\t\t{struct stat dir_exists; stringstream s1;\n"
			<< "\t\ts1 << \"setup-\" << jno;\n"
			<< "\t\tif (stat(s1.str().c_str(), &dir_exists) <0) {\n"
			<< "\t\t\tif (errno == ENOENT)\n"
			<< "\t\t\t\tif (mkdir(s1.str().c_str(), S_IRUSR | S_IWUSR | S_IXUSR) <0) {\n"
			<< "\t\t\t\t\tperror(\"unable to create directory for setup files\");\n}\n"
			<< "\t\t\telse\n"
			<< "\t\t\t\tperror(\"stating directory failed\");\n"
			<< "\t\t\t}\t\t\n}\n"
			;
	} else {
		compute_flat_map_code.program_code 
			<< "\t\t{struct stat dir_exists; stringstream s1;\n"
			<< "\t\t\ts1 << \"setup-\" << jno;\n"
			<< "\t\t\tif (stat(s1.str().c_str(), &dir_exists) <0) {\n"
			<< "\t\t\t\tif (errno == ENOENT)\n"
			<< "\t\t\t\t\tif (mkdir(s1.str().c_str()) <0) {\n"
			<< "\t\t\t\t\t\tperror(\"unable to create directory for setup files\");\n"
			<< "\t\t\t\t\t} else\n"
			<< "\t\t\t\t\t\tperror(\"stating directory failed\");\n"
			<< "\t\t\t}\n\t\t}\n"
			;
	}

	compute_flat_map_code.program_code << "\tif (write_qtm_data_file_flag) {\n";


	compute_flat_map_code.program_code << "\t\tstring qtm_map_file_name(string(\"setup-\") + jno + string(\"/\") + jno + string(\".qmap\"));\n";
	compute_flat_map_code.program_code << "\t\tfstream qtm_map_file(qtm_map_file_name.c_str(), ios_base::out|ios_base::ate);\n";
	compute_flat_map_code.program_code << "\t\tprint_map_header(qtm_map_file);\n";
	compute_flat_map_code.program_code << "\t\tfor (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {\n"
		<< "\t\t\tqtm_datafile_question_disk_map[i]->print_map(qtm_map_file);\n"
		<< "\t\t}\n";

	StatementCompiledCode recode_edit;
	PrintRecodeEdit (recode_edit);
	compute_flat_map_code.program_code << "{" <<recode_edit.program_code.str() << "}"  << endl;

	StatementCompiledCode create_1_0_data_edit;
	PrintCreate_1_0_DataEdit(create_1_0_data_edit);
	compute_flat_map_code.program_code << "{" << create_1_0_data_edit.program_code.str() << "}" << endl;

	compute_flat_map_code.program_code << "\t\tstring qtm_qax_file_name( string(\"setup-\")+jno+string(\"/\") + jno + string(\".qax\"));\n";
	compute_flat_map_code.program_code << "\t\tfstream qtm_qax_file(qtm_qax_file_name.c_str(), ios_base::out|ios_base::ate);\n"
		"\t\tmap <string, vector<qtm_data_file_ns::QtmDataDiskMap*> > summary_tables;\n";
	compute_flat_map_code.program_code << "\t\tfor (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {\n"
		<< "\t\t\tqtm_datafile_question_disk_map[i]->print_qax(qtm_qax_file, string(\"setup-\")+jno);\n"
		<< "\t\t\tstring questionName = qtm_datafile_question_disk_map[i]->q->questionName_;\n"
		<< "\t\t\tif (qtm_datafile_question_disk_map[i]->q->loop_index_values.size() > 0) {\n"
		<< "\t\t\t\tsummary_tables[questionName].push_back(qtm_datafile_question_disk_map[i]);\n"
		<< "\t\t\t}\n"
		<< "\t\t}\n"
		<< "\t\tfor ( map <string, vector<qtm_data_file_ns::QtmDataDiskMap*> >::iterator it= summary_tables.begin();\n"
		<< "\t\t		it != summary_tables.end(); ++it) {\n"
		<< "\t\t	print_summary_axis(it->second, qtm_qax_file);\n"
		<< "\t\t}\n";
	compute_flat_map_code.program_code 
		<< "\t\tqtm_datafile_question_disk_map[0]->print_run(jno);"
		<< endl;
	compute_flat_map_code.program_code << "\t\tstring tab_file_name(string(\"setup-\")+ jno + string(\"/\") + jno + string(\".tab\"));\n";
	compute_flat_map_code.program_code << "\t\tfstream tab_file(tab_file_name.c_str(), ios_base::out|ios_base::ate);\n";
	compute_flat_map_code.program_code << "\t\tfor (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {\n"
		<< "\t\t\tstring questionName = qtm_datafile_question_disk_map[i]->q->questionName_;\n"
		<< "\t\t\tAbstractQuestion * q = qtm_datafile_question_disk_map[i]->q;\n"
		<< "\t\t\ttab_file << \"tab \" << q->questionName_;\n"
		<< "\t\t\tfor(int j=0; j<q->loop_index_values.size(); ++j) {\n"
		<< "\t\t\t\ttab_file << \"_\" << q->loop_index_values[j];\n"
		<< "\t\t\t}\n"
		<< "\t\t\ttab_file << \" &ban\" << endl;\n"
		<< "\t\t}\n";


	compute_flat_map_code.program_code << "\t\tqtm_datafile_question_disk_map[0]->qtmDataFile_.AllocateCards();\n"
		<< "\t\tqtm_datafile_question_disk_map[0]->qtmDataFile_.Reset();\n";
	compute_flat_map_code.program_code << "\t\tstring qtm_disk_file_name(jno + string(\".qdat\"));\n";
	compute_flat_map_code.program_code << "\t\tqtm_disk_file.open(qtm_disk_file_name.c_str(), ios_base::out | ios_base::trunc);\n";
	compute_flat_map_code.program_code << "\t}\n";

	compute_flat_map_code.program_code 
		<< "\tif (write_xtcc_data_file_flag) {\n"
		<< "\t\tstring xtcc_ax_file_name(string(\"setup-\")+jno+string(\"/\") + jno + string(\".xtcc\"));\n"
		<< "\t\tfstream xtcc_ax_file(xtcc_ax_file_name.c_str(), ios_base::out | ios_base::ate);\n"
		<< "\t\txtcc_ax_file << \"data_struct;rec_len=\" << len_xtcc_datafile_output_buffer << \";\\n\";\n" 
		<< "\t\txtcc_ax_file << \"ed_start\\n\";\n"
		<< "\t\t xtcc_ax_file << \"\tint32_t edit_data();\\n\";\n"
		<< "\t\t xtcc_ax_file << \"\tint32_t all;\\n\";\n"
		<< "\t\t xtcc_ax_file << \"\tint32_t ser_no;\\n\";\n"
		<< "\t\tfor (int i=0; i<xtcc_question_disk_map.size(); ++i) {\n"
		<< "\t\t\txtcc_question_disk_map[i]->print_edit_var_defns(xtcc_ax_file, string(\"setup-\")+jno+string(\"/\"));\n"
		<< "\t\t}\n"
		<< "\t\t xtcc_ax_file << \"\tint32_t edit_data()\\n{\\n\";\n"
		<< "\t\t xtcc_ax_file << \"\tall = 1;\\n\";\n"
		<< "\t\t xtcc_ax_file << \"\tser_no = c[0,3];\\n\";\n"
		<< "\t\tfor (int i=0; i<xtcc_question_disk_map.size(); ++i) {\n"
		<< "\t\t\txtcc_question_disk_map[i]->print_xtcc_edit_load(xtcc_ax_file, string(\"setup-\")+jno+string(\"/\"));\n"
		<< "\t\t}\n"
		<< "\t\t xtcc_ax_file << \"\t}\\n\";\n"
		<< "\t\txtcc_ax_file << \"ed_end\\n\";\n"
		<< "\t\txtcc_ax_file << \"tabstart {\\n\";\n"
		<< "\t\tfor (int i=0; i<xtcc_question_disk_map.size(); ++i) {\n"
		<< "\t\t\txtcc_question_disk_map[i]->print_xtcc_tab(xtcc_ax_file, string(\"setup-\")+jno+string(\"/\"));\n"
		<< "\t\t}\n"
		<< "\t\txtcc_ax_file << \"}\\n\";\n"
		<< "\t\txtcc_ax_file << \"axstart {\\n\";\n"

		<< "\t\txtcc_ax_file << \"ax tot_ax;\\n\";\n"
		<< "\t\txtcc_ax_file << \"ttl; \\\"Total\\\";\\n\";\n"
		<< "\t\txtcc_ax_file << \"cnt; \\\"All\\\"; c= all==1;\\n\";\n"

		<< "\t\tfor (int i=0; i<xtcc_question_disk_map.size(); ++i) {\n"
		<< "\t\t\txtcc_question_disk_map[i]->print_xtcc_ax(xtcc_ax_file, string(\"setup-\")+jno+string(\"/\"));\n"
		<< "\t\t}\n"
		<< "\t\txtcc_ax_file << \"}\\n\";\n"
		<< "\t}\n";	

	compute_flat_map_code.program_code << "}\n";

	compute_flat_map_code.program_code << "}\n";
}


void PrintRecodeEdit(StatementCompiledCode & recode_edit)
{
	recode_edit.program_code 
		<< "\t\tstring variable_defns_fname (string(\"setup-\") + jno + string(\"/\") + string(\"variable\"));\n"
		<< "\t\tfstream variable_file (variable_defns_fname.c_str(), ios_base::out|ios_base::ate);\n"
		<< "\t\tstring edit_file_name (string(\"setup-\") + jno + string(\"/\") + jno + string(\"-recode-edit.qin\"));\n"
		<< "\t\tfstream edit_file (edit_file_name.c_str(), ios_base::out|ios_base::ate);\n"
		<< "\t\tstring recode_edit_qax_file_name (string(\"setup-\") + jno + string(\"/\") +jno + string(\"-recode-edit.qax\"));\n"
		<< "\t\tfstream recode_edit_qax_file (recode_edit_qax_file_name.c_str(), ios_base::out|ios_base::ate);\n"
		<< endl;

		;
	
	for (int i=0; i<recode_driver_vec.size(); ++i) {
		// WARNING!!! if driver_vec is zero size this will dump core
		// our grammar parser should ensure this is never the case

		vector <string> & recode_vec = recode_driver_vec[i]->recode_vec,
				& driver_vec = recode_driver_vec[i]->driver_vec;
		int no_loops_in_qnre =  driver_vec.size();
		for (int j1 = 0; j1 < recode_vec.size(); j1 += no_loops_in_qnre) {
			for (int j2=0; j2 < driver_vec.size(); ++j2) {
				string driver_question_name = driver_vec[j2];
				string rec_question_name = recode_vec[j2 + j1];
				string leader_rec_question_name = recode_vec[j1];
				SymbolTableEntry * se = active_scope_list[0]->find (rec_question_name);
				if (se) {
					recode_edit.program_code << "/* "
						<< "found : " << rec_question_name
						<< " in symbol table: " ;
					if (se->type_ == QUESTION_TYPE) {
						/* If you need more than 3 levels of indentation
						   you're screwed and need to re-think your function
						   - Linux Kernel Documentation, indentation rules
						   ....
						   so I definitely need to refactor this into a function later
						   */
						recode_edit.program_code 
							<< " normal question" << endl;
						recode_edit.program_code << "*/" << endl;

						recode_edit.program_code
							<< "\t\tfor (int i=0; i < " << driver_question_name 
							<< "->nr_ptr->stubs.size(); ++i) {\n"

							<< "\t\t\tqtm_data_file_ns::QtmDataDiskMap * "
							<< driver_question_name
							<< "_map_entry =\n"
							<< "\t\t\t\tGetQuestionMapEntry (qtm_datafile_question_disk_map, "
							<< driver_question_name << "->questionName_);" << endl
							<< "\t\t\tqtm_data_file_ns::QtmDataDiskMap * "
							<< rec_question_name
							<< "_map_entry =\n"
							<< "\t\t\t\tGetQuestionMapEntry (qtm_datafile_question_disk_map, "
							<< rec_question_name << "->questionName_);" << endl;

						if (j2 == 0) {
							recode_edit.program_code
								<< "\t\t\t variable_file << " 
								<< "\"data " << rec_question_name << "\"" << " << " << "\"_\""
								<< " << " << driver_question_name 
								<< "->nr_ptr->stubs[i].stub_text_as_var_name() << \" \" << "
								<< rec_question_name << "_map_entry->totalLength_ " << " << \"s\""
								<< "<< endl;\n"
								<< "\t\t\t\t\trecode_edit_qax_file\n"
								<< "\t\t\t\t\t\t	<< print_recode_edit_qax (" 
								<< driver_question_name << "_map_entry, "
								<< rec_question_name << "_map_entry, i);\n" << endl;

							recode_edit.program_code 
								<< "edit_file << \"clear "
								<< leader_rec_question_name << "_\"" << endl
								<< "\t\t\t\t\t<< "
								<< driver_question_name
								<< "->nr_ptr->stubs[i].stub_text_as_var_name() << \"(1, \" << " << endl
								<< rec_question_name 
								<< "_map_entry->totalLength_"
								<< " << \");\\n\";\n";
						}

							//<< "\t\t\tvariable_file << \""
							//<< rec_question_name
							//<< "\" << \"_\" << "
							//<< driver_question_name
							//<< "->nr_ptr->stubs[i].stub_text_as_var_name() << endl;" 
							//<< ""
							//<< endl


						recode_edit.program_code 
							<< "\t\t\tif (" << driver_question_name << "_map_entry"
							<< " && " << rec_question_name << "_map_entry) {\n"
							<< "\t\t\t\tedit_file << \"/* \" << "
							<< driver_question_name
							<< "->questionName_ \n"
							<< "\t\t\t\t\t<< \" column: c(\" << "
							<< driver_question_name << "_map_entry->startPosition_ + 1\n"
							<< "\t\t\t\t\t<< \", \" << "
							<< driver_question_name << "_map_entry->startPosition_ + "
							<< driver_question_name << "_map_entry->totalLength_\n"
							<< "\t\t\t\t\t<< \")\"" << endl
							<< "\t\t\t\t\t<< endl;" << endl
							<< "\t\t\t\tedit_file << \"	if ( \"" << endl
							<< "\t\t\t\t\t<< \"c(\" " << endl
							<< "\t\t\t\t\t<< " << driver_question_name
							<< "_map_entry->startPosition_ + 1" << endl
							<< "\t\t\t\t\t<< \", \"" << endl
							<< "\t\t\t\t\t<< " 
							<< driver_question_name << "_map_entry->startPosition_ + "
							<< driver_question_name 
							<< "_map_entry->totalLength_ << \")\"" << endl
							<< "\t\t\t\t\t<< \" .eq. \" << "
							<< driver_question_name
							<< "->nr_ptr->stubs[i].code" << endl
							<< "\t\t\t\t\t<< \")\\n\"" << endl
							<< "\t\t\t\t\t<< \"+\\t\" <<  \""
							<< leader_rec_question_name << "_\"" << endl
							<< "\t\t\t\t\t<< "
							<< driver_question_name
							<< "->nr_ptr->stubs[i].stub_text_as_var_name() << \"(1, \" << " << endl
							<< rec_question_name 
							<< "_map_entry->totalLength_"
							<< " << \")\" "
							<< "\t\t\t\t\t<< \"=\"" << endl
							<< "\t\t\t\t\t<< \"c(\" " << endl
							<< "\t\t\t\t\t<< "
							<< rec_question_name
							<< "_map_entry->startPosition_ + 1" << endl
							<< "\t\t\t\t\t<< \", \"" << endl
							<< "\t\t\t\t\t<< " << rec_question_name << "_map_entry->startPosition_ + "
							<< rec_question_name << "_map_entry->totalLength_ << \")\"" << endl
							<< "\t\t\t\t\t<< endl;" << endl 

							<< "\t\t\t}\n"
							<< "\t\t}\n";
					} else if (se->type_ == QUESTION_ARR_TYPE) {
						recode_edit.program_code 
							<< " array question" << endl;
						recode_edit.program_code << "*/" << endl;

						recode_edit.program_code
							<< "\t\tfor (int i=0; i < " << driver_question_name 
							<< "->nr_ptr->stubs.size(); ++i) {\n"

							<< "\t\t\tqtm_data_file_ns::QtmDataDiskMap * "
							<< driver_question_name
							<< "_map_entry =\n"
							<< "\t\t\t\tGetQuestionMapEntry (qtm_datafile_question_disk_map, "
							<< driver_question_name << "->questionName_);" << endl
							<< "\t\t\tvector<qtm_data_file_ns::QtmDataDiskMap *> "
							<< rec_question_name
							<< "_map_entry =\n"
							<< "\t\t\t\tGetQuestionMapEntryArrayQ (qtm_datafile_question_disk_map, \""
							<< rec_question_name << "\");" << endl
							//<< "\t\t\t variable_file << " 
							//<< "\"" << rec_question_name << "\"" << " << " << "\"_\""
							//<< " << " << driver_question_name 
							//<< "->nr_ptr->stubs[i].stub_text_as_var_name() << endl;\n"

							<< "\t\t\t\tfor (int i1=0; i1<" << rec_question_name 
							<< "_map_entry.size(); ++i1) {" << endl;

						if (j2 == 0) {
						recode_edit.program_code 
							<< "\t\t\tvariable_file << \"data "
							<< rec_question_name << "\";\n" << endl
							<< "\t\t\t\t\tfor (int i2=0; i2 < "
							<< rec_question_name << "_map_entry[i1]->"
							<< "q->loop_index_values.size(); ++i2) {\n"
							<< "\t\t\t\t\t\t variable_file << \"_\" << "
							<< rec_question_name << "_map_entry[i1]->q->"
							<< "loop_index_values[i2];\n"
							<< "\t\t\t\t\t}\n"
							
							<< "\t\t\t\t\tvariable_file << \"_\" << "
							<< driver_question_name
							<< "->nr_ptr->stubs[i].stub_text_as_var_name() << \" \" << " 
							<< rec_question_name << "_map_entry[i1]->totalLength_ " << " << \"s\\n\";\n"
							<< "\t\t\t\t\trecode_edit_qax_file\n"
							<< "\t\t\t\t\t\t	<< print_recode_edit_qax (" 
							<< driver_question_name << "_map_entry, "
							<< rec_question_name << "_map_entry[i1], i);\n" << endl;

						recode_edit.program_code 
							<< "edit_file << \"clear " << leader_rec_question_name << "\";" << endl;
						recode_edit.program_code 
							<< "\t\t\t\t\tfor (int i2=0; i2 < "
							<< rec_question_name << "_map_entry[i1]->"
							<< "q->loop_index_values.size(); ++i2) {\n"
							<< "\t\t\t\t\t\tedit_file << \"_\" << "
							<< rec_question_name << "_map_entry[i1]->q->"
							<< "loop_index_values[i2];\n"
							<< "\t\t\t\t\t}\n";
						recode_edit.program_code
							<< "\t\t\t\t\tedit_file << \"_\" << "
							<< driver_question_name
							<< "->nr_ptr->stubs[i].stub_text_as_var_name() << \"(1, \" << " << endl
							<< rec_question_name 
							<< "_map_entry[i1]->totalLength_"
							<< " << \");\\n\";\n";

						}

						recode_edit.program_code 
							<< "\t\t\t\t\tif (" << driver_question_name << "_map_entry"
							<< " && " << rec_question_name << "_map_entry.size() > 0) {\n"
							<< "\t\t\t\t\tedit_file << \"/* \" << "
							<< driver_question_name
							<< "->questionName_ \n"
							<< "\t\t\t\t\t<< \" column: c(\" << "
							<< driver_question_name << "_map_entry->startPosition_ + 1\n"
							<< "\t\t\t\t\t<< \", \" << "
							<< driver_question_name << "_map_entry->startPosition_ + "
							<< driver_question_name << "_map_entry->totalLength_\n"
							<< "\t\t\t\t\t<< \")\"" << endl
							<< "\t\t\t\t\t<< endl;" << endl
							<< "\t\t\t\t\tedit_file << \"	if ( \"" << endl
							<< "\t\t\t\t\t<< \"c(\" " << endl
							<< "\t\t\t\t\t<< " << driver_question_name
							<< "_map_entry->startPosition_ + 1" << endl
							<< "\t\t\t\t\t<< \", \"" << endl
							<< "\t\t\t\t\t<< " 
							<< driver_question_name << "_map_entry->startPosition_ + "
							<< driver_question_name 
							<< "_map_entry->totalLength_ << \")\"" << endl
							<< "\t\t\t\t\t<< \" .eq. \" << "
							<< driver_question_name
							<< "->nr_ptr->stubs[i].code" << endl
							<< "\t\t\t\t\t<< \")\\n\"" << endl
							<< "\t\t\t\t\t<< \"+\\t\" <<  \""
							<< leader_rec_question_name << "\";" << endl;
						recode_edit.program_code 
							<< "\t\t\t\t\tfor (int i2=0; i2 < "
							<< rec_question_name << "_map_entry[i1]->"
							<< "q->loop_index_values.size(); ++i2) {\n"
							<< "\t\t\t\t\t\tedit_file << \"_\" << "
							<< rec_question_name << "_map_entry[i1]->q->"
							<< "loop_index_values[i2];\n"
							<< "\t\t\t\t\t}\n";
						recode_edit.program_code
							<< "\t\t\t\t\tedit_file << \"_\" << "
							<< driver_question_name
							<< "->nr_ptr->stubs[i].stub_text_as_var_name() << \"(1, \" << " << endl
							<< rec_question_name 
							<< "_map_entry[i1]->totalLength_"
							<< " << \")\" "
							<< "\t\t\t\t\t<< \"=\"" << endl
							<< "\t\t\t\t\t<< \"c(\" " << endl
							<< "\t\t\t\t\t<< "
							<< rec_question_name
							<< "_map_entry[i1]->startPosition_ + 1" << endl
							<< "\t\t\t\t\t<< \", \"" << endl
							<< "\t\t\t\t\t<< " << rec_question_name << "_map_entry[i1]->startPosition_ + "
							<< rec_question_name << "_map_entry[i1]->totalLength_ << \")\"" << endl
							<< "\t\t\t\t\t<< endl;" << endl 
							<< "\t\t\t\t}" << endl
							<< "\t\t\t}" << endl
							<< "\t\t}\n";
					} else {
						recode_edit.program_code 
							<< " not a  question" << endl;
						recode_edit.program_code << "*/" << endl;
					}
				} else {
					recode_edit.program_code << "/* "
						<< "NOT found : " << rec_question_name
						<< " in symbol table: " 
						<< "*/"
						<< endl ;
				}

				cout << __PRETTY_FUNCTION__ << endl
					<< "rec_question_name: " << rec_question_name
					<< endl;

			}
		}
	}
}



void PrintCreate_1_0_DataEdit(StatementCompiledCode & create_1_0_data_edit)
{
	create_1_0_data_edit.program_code 
		<< "\t\tstring variable_defns_fname (string(\"setup-\") + jno + string(\"/\") + string(\"variable\"));\n"
		<< "\t\tfstream variable_file (variable_defns_fname.c_str(), ios_base::out|ios_base::ate);\n"
		<< "\t\tstring edit_file_name (string(\"setup-\") + jno + string(\"/\") + jno + string(\"-1_0-edit.qin\"));\n"
		<< "\t\tfstream edit_file (edit_file_name.c_str(), ios_base::out|ios_base::ate);\n"
		<< "\t\tstring recode_edit_qax_file_name (string(\"setup-\") + jno + string(\"/\") +jno + string(\"-1_0-edit.qax\"));\n"
		<< "\t\tfstream recode_edit_qax_file (recode_edit_qax_file_name.c_str(), ios_base::out|ios_base::ate);\n"
		<< endl;
	for (int i = 0; i < create_1_0_edit_vec.size(); ++i) {
		string rec_question_name = create_1_0_edit_vec[i]->questionName_;
		SymbolTableEntry * se = active_scope_list[0]->find (rec_question_name);
		if (se) {
			NamedStubQuestion * nq = dynamic_cast <NamedStubQuestion*>(se->question_);
			if (!nq) {
				cerr << "question: " << rec_question_name << " is not a NamedStubQuestion, this recode will not work ... exiting\n";
				exit(1); 
			}
			if (se->type_ == QUESTION_ARR_TYPE) {
				create_1_0_data_edit.program_code
					<< "if (" << rec_question_name << "_list.arrayBounds.size() > 1) {\n"
					<< "\t cerr << \" this edit will not work for QUESTION_ARR_TYPE having dimensions > 1\" << endl;\n"
					<< "\t exit(1);\n"
					<< "}\n";
				create_1_0_data_edit.program_code
					<< "NamedStubQuestion * " << rec_question_name 
					<<  "= dynamic_cast<NamedStubQuestion*> ("
					<< rec_question_name 
					<< "_list.questionList[0]);\n";

				create_1_0_data_edit.program_code
					<< "\t\t\tvector<qtm_data_file_ns::QtmDataDiskMap *> "
					<< rec_question_name
					<< "_map_entry =\n"
					<< "\t\t\t\tGetQuestionMapEntryArrayQ (qtm_datafile_question_disk_map, \""
					<< rec_question_name << "\");" << endl;


				create_1_0_data_edit.program_code
					<< "\t\tfor (int i=0; i < " << rec_question_name 
					<< "->nr_ptr->stubs.size(); ++i) {\n"
					<< "variable_file << \"data \" <<  \"" 
					<< rec_question_name 
					<< "\" << \"_\" << "
					<< rec_question_name
					<< "->nr_ptr->stubs[i].stub_text_as_var_name() "
					<< "<< \" \" << " << rec_question_name << "_list.arrayBounds[0]"
					<< "<< endl;" << endl
					<< "edit_file << \"clear \" <<  \"" 
					<< rec_question_name 
					<< "\" << \"_\" << "
					<< rec_question_name
					<< "->nr_ptr->stubs[i].stub_text_as_var_name() "
					<< "<< \" (1, \" << " << rec_question_name << "_list.arrayBounds[0]"
					<< "<< \")\""
					<< "<< endl;"
					<< "}\n";
				create_1_0_data_edit.program_code
					<< "edit_file << \"do 9 t1=1,\" << " 
					<< rec_question_name << "_list.arrayBounds[0] << \",1\" << endl"
					<< ";";

				create_1_0_data_edit.program_code
					<< "\t\tfor (int i=0; i < " << rec_question_name 
					<< "->nr_ptr->stubs.size(); ++i) {\n"
					<< "edit_file << \"\t\" <<  \"" 
					<< rec_question_name 
					<< "\" << \"_\" << "
					<< rec_question_name
					<< "->nr_ptr->stubs[i].stub_text_as_var_name() "
					<< "<< \" (t1)=$0$ \""
					<< "<< endl;"
					<< "}\n";

				create_1_0_data_edit.program_code
					<< "edit_file << \"9 continue;\" << endl;";

				create_1_0_data_edit.program_code
					<< "edit_file << \"output_col = 1\" << endl;"
					<< "edit_file << \"do 10 input_col=\";";
				create_1_0_data_edit.program_code
					<< "\t\t\t\tfor (int i1=0; i1<" << rec_question_name 
					<< "_map_entry.size(); ++i1) {" << endl;
				//create_1_0_data_edit.program_code 
				//	<< "\t\t\t\t\tfor (int i2=0; i2 < "
				//	<< rec_question_name << "_map_entry[i1]->"
				//	<< "q->loop_index_values.size(); ++i2) {\n"
				//	<< "\t\t\t\t\t\tedit_file << \"_\" << "
				//	<< rec_question_name << "_map_entry[i1]->q->"
				//	<< "loop_index_values[i2];\n"
				//	<< "\t\t\t\t\t}\n";
				create_1_0_data_edit.program_code
					<< "edit_file << "
					<< rec_question_name 
					<< "_map_entry[i1]->startPosition_ + 1;\n";
				create_1_0_data_edit.program_code
					<< "if (i1+1 < " << rec_question_name	
					//<< "_map_entry.size() ) edit_file << \":\"<< i1 << \",\";\n";
					<<   "_map_entry.size() ) edit_file               << \",\";\n";

				create_1_0_data_edit.program_code 
					<< "}\n";
				create_1_0_data_edit.program_code
					<< "edit_file << endl;";
				create_1_0_data_edit.program_code
					<< "\t\tfor (int i=0; i < " << rec_question_name 
					<< "->nr_ptr->stubs.size(); ++i) {\n"
					<< "edit_file << "
					<< " \"\tif c(input_col+\" << "
					<< rec_question_name
					<< "->nr_ptr->stubs[i].code/10"
					<< " << \")'\" << "
					<< rec_question_name
					<< "->nr_ptr->stubs[i].code%10"
					<< "<< \"' \""
					<< "<< \"" 
					<< rec_question_name 
					<< "\" << \"_\" << "
					<< rec_question_name
					<< "->nr_ptr->stubs[i].stub_text_as_var_name()"
					<< "<< \"(output_col)=$1$\""
					<< "<< endl;"
					<< "}\n";


				create_1_0_data_edit.program_code
					<< "edit_file << \"\toutput_col = output_col+1;\" << endl;\n"
					<< "edit_file << \"10 continue;\" << endl;\n";

				create_1_0_data_edit.program_code
					<< "int max_card  =  qtm_datafile_question_disk_map[0]->qtmDataFile_.fileXcha_.currentCard_ + 1 ;\n"
					<< "int recode_start_card  =  max_card + 10 + 10-max_card%10 ;\n"
					<< "edit_file << \"/*Max card: \" << max_card << \"*/\"<< endl;\n"
					<< "edit_file << \"spss array write start card: \" << recode_start_card << \"*/\" << endl;\n" ;

				create_1_0_data_edit.program_code
					<< "int n_stmts = " << rec_question_name << "_list.arrayBounds[0];\n"
					<< "int blk_size = n_stmts +10 + 10-n_stmts%10;\n"
					<< "int n_brands = " << rec_question_name << "->nr_ptr->stubs.size();\n"
					<< "edit_file "
					<< " << \"n_stmts: \" << n_stmts << endl\n"
					<< " << \"blk_size: \" << blk_size << endl\n"
					<< " << \"n_brands: \" << n_brands << endl\n"
					<< " << \"r b c(\" << recode_start_card*100\n"
					<< " << \", \" <<  recode_start_card*100 + (n_brands+1) * blk_size"
					<< " << \") $ cards used for SPSS edit data xfer$\\n\";\n"
					<< "\t\tfor (int i=0; i < " << rec_question_name 
					<< "->nr_ptr->stubs.size(); ++i) {\n"
					<< "\t edit_file << " 
					<< " \"c(\""
					<< " << recode_start_card*100 + (i+1) * blk_size"
					<< " << \", \""
					<< " << recode_start_card*100 + (i+1) * blk_size+n_stmts"
					<< " << \") = \""
					<< " << \"" 
					<< rec_question_name 
					<< "\" << \"_\" << "
					<< rec_question_name 
					<< "->nr_ptr->stubs[i].stub_text_as_var_name()  "
					<< " << \"(1, \" << n_stmts << \")\" << endl;"
					<< "}\n"
					<< "edit_file << \"filedef " << qscript_parser::project_name << "_\"" << "<< \"" << rec_question_name << "\" << \".dat data len=\" << ((n_brands+1) * blk_size) << endl;\n"
					<< "edit_file << \"write " << qscript_parser::project_name << "_\"" << "<< \"" << rec_question_name << "\" << \".dat c(\""

					<< " << recode_start_card*100\n"
					<< " << \", \" <<  recode_start_card*100 + (n_brands+1) * blk_size"
					<< " << \") \"<< endl;\n"
					<< endl
					;



			} else {
				cerr << "symbol: " << rec_question_name << " is not QUESTION_ARR_TYPE ... create_1_0_data_edit_stmt ... unhandled case... exiting\n";
				exit(1); 
			}

		} else {
			cerr << "symbol: " << rec_question_name << " not found in symbol table... create_1_0_data_edit_stmt ... exiting\n";
			exit(1); 
		}
	}
}

void print_eval_questionnaire (FILE* script, ostringstream & program_code, bool ncurses_flag)
{
	fprintf(script, "void eval()\n{\n");
	// fprintf(script, "\tint ser_no = 0;\n");
	if(ncurses_flag) {
		fprintf(script, "\tif (!(write_data_file_flag|| write_qtm_data_file_flag||write_xtcc_data_file_flag)) {\n");
		fprintf(script, "\t\tint n_printed = mvwprintw(data_entry_window, 1, 1, \"Enter Serial No (0) to exit: \");\n");
		fprintf(script, "\t\tmvwscanw(data_entry_window, 1, 40, \"%%d\", & ser_no);\n");
		fprintf(script, "\t}\n");
	} else	{
		fprintf(script, "\tif (!(write_data_file_flag|| write_qtm_data_file_flag||write_xtcc_data_file_flag)) {\n");
		fprintf(script, "\t\tcout << \"Enter Serial No (0) to exit: \" << flush;\n");
		fprintf(script, "\t\tchar  newl; cin >> ser_no;cin.get(newl);\n");
		fprintf(script, "\t}\n");
	}

	fprintf(script, "\twhile(ser_no != 0 || (write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)){\n");
	// code-frag/open-eval-while-loop-code-frag.cpp 

	fprintf(script, "%s\n", file_exists_check_code());

	fprintf(script, "\tstart_of_questions:\n");
	fprintf(script, "\tif(back_jump == true){\n");
	fprintf(script, "\tfprintf(qscript_stdout, \"have reached start_of_questions with back_jump: jumpToQuestion: %%s, jumpToIndex: %%d\\n\", jumpToQuestion.c_str(), jumpToIndex);\n");
	fprintf(script, "\t}\n");

	fprintf(script, "%s\n", program_code.str().c_str());
	fprintf(script, "\tif (write_data_file_flag) {\n\n");
	fprintf(script, "\t\t cout << \"write_data_file_flag is set\\n\";\n");
	fprintf(script, "\t\twrite_ascii_data_to_disk();\n");
	fprintf(script, "\t} else if (write_qtm_data_file_flag) {\n");
	fprintf(script, "\t\t cout << \"write_qtm_data_file_flag is set\\n\";\n");
	fprintf(script, "\t\twrite_qtm_data_to_disk();\n");
	fprintf(script, "\t} else if (write_xtcc_data_file_flag) {\n");
	fprintf(script, "\t\t cout << \"write_xtcc_data_file_flag is set\\n\";\n");
	fprintf(script, "\t\t write_xtcc_data_to_disk();\n");
	fprintf(script, "\t} else {\n");
	fprintf(script, "\tchar end_of_question_navigation;\n");
	fprintf(script, "label_end_of_qnre_navigation:\n");
	if(ncurses_flag) {
		fprintf(script, "\twclear(data_entry_window);\n");
		fprintf(script, "\tmvwprintw(data_entry_window, 1, 1,\"End of Questionnaire: ((s)ave, (p)revious question, question (j)ump list)\"); \n");
		fprintf(script, "\tmvwscanw(data_entry_window, 1, 75, \"%%c\", & end_of_question_navigation);\n");
	} else {
		fprintf(script, "\tcout << \"End of Questionnaire: (s to save, p = previous question, j = question jump list, q = quit without saving - all newly entered data will be lost)\" << endl;\n");
		fprintf(script, "\tcin >> end_of_question_navigation;\n");
	}
	fprintf(script, "\tif(end_of_question_navigation == 's'){\n");
	fprintf(script, "\t\twrite_data_to_disk(question_list, jno, ser_no);\n");
	fprintf(script, "\t} else if (end_of_question_navigation == 'p'){\n");
	fprintf(script, "\t\tAbstractQuestion * target_question = ComputePreviousQuestion(last_question_answered);\n");
	fprintf(script, "\t\tif(target_question->type_ == QUESTION_ARR_TYPE)\n");
	fprintf(script,	"\t\t\t{\n");
	fprintf(script, "\t\t\t\tjumpToIndex = ComputeJumpToIndex(target_question);\n");
	fprintf(script, "\t\t\t}\n");
	fprintf(script,	"\t\tjumpToQuestion = target_question->questionName_;\n");
	fprintf(script, "\t\tif (data_entry_window == 0) cout << \"target question: \" << jumpToQuestion;\n");
	fprintf(script, "\t\tback_jump = true;\n");
	fprintf(script, "\t\tuser_navigation = NOT_SET;\n");
	fprintf(script, "\t\tgoto start_of_questions;\n");
	fprintf(script, "\t}");
	fprintf(script, "\telse if (end_of_question_navigation == 'j') {\n"
			"\t\tDisplayActiveQuestions();\n"
			"\t\tGetUserResponse(jumpToQuestion, jumpToIndex);\n"
			"\t\tuser_navigation = NOT_SET;\n"
			"\t\tgoto start_of_questions;\n}");
	fprintf(script, "\telse if (end_of_question_navigation == 'q') {\n"
		 	"\t\treset_questionnaire();\n"
			"}");
	fprintf(script, " else {\n"
			"\t\tgoto label_end_of_qnre_navigation;\n"
			"\t}\n"
			);
	if( ncurses_flag) {
		fprintf(script, "\twclear(data_entry_window);\n");
		fprintf(script, "\tmvwprintw(data_entry_window, 1, 1, \"Enter Serial No (0) to exit: \"); \n");
		fprintf(script, "\tmvwscanw(data_entry_window, 1, 40, \"%%d\", & ser_no);\n");
		fprintf(script, "\t}\n");
		fprintf(script, "\treset_questionnaire();\n");
	} else {
		fprintf(script,	"\tcout <<  \"Enter Serial No (0) to exit: \";cout.flush();\n");
		fprintf(script, "\tcin >> ser_no;cin.get(newl);\n");
		fprintf(script, "\treset_questionnaire();\n");
	}
	fprintf(script, "\n\t} /* close while */\n");
	if(ncurses_flag)
		fprintf(script, "\tendwin();\n");

	fprintf(script, "    if (write_qtm_data_file_flag||write_data_file_flag || write_xtcc_data_file_flag) {\n");
	fprintf(script, "\n");
	fprintf(script, "           string freq_count_file_name(jno + string(\".freq_count.csv\"));\n");
	fprintf(script, "           fstream freq_count_file(freq_count_file_name.c_str(), ios_base::out | ios_base::trunc);\n");
	fprintf(script, "\n");
	fprintf(script, "           // for (map<string, map<int, int> >::iterator it = freq_count.begin();\n");
	fprintf(script, "           //              it != freq_count.end(); ++ it) ;\n");
	fprintf(script, "       for (int32_t i=0; i<question_list.size(); ++i)\n");
	fprintf(script, "       {\n");
	fprintf(script, "                   AbstractQuestion *q = question_list[i];\n");
	fprintf(script, "                   //freq_count_file << it->first << endl;\n");
	fprintf(script, "                   freq_count_file << q->questionName_ ;\n");
	fprintf(script, "			stringstream question_name_str;\n");
	fprintf(script, "			question_name_str << q->questionName_;\n");
	fprintf(script, "		    if (q->loop_index_values.size()) {\n");
	fprintf(script, "				for (int j=0; j<q->loop_index_values.size(); ++j) {\n");
	fprintf(script, "					freq_count_file << \".\" << q->loop_index_values[j];\n");
	fprintf(script, "					question_name_str << \".\" << q->loop_index_values[j];\n");
	fprintf(script, "				}\n");
	fprintf(script, "		    }\n");
	fprintf(script, "		    freq_count_file << endl;\n");

	fprintf(script, "			if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q)) {\n");
	fprintf(script, "				freq_count_file << \"stubs, code, frequency\" << endl;\n");
	fprintf(script, "				map<int32_t, int32_t>  q_freq_count = freq_count[question_name_str.str()];\n");
	fprintf(script, "				vector<stub_pair> & vec= (nq->nr_ptr->stubs);\n");
	fprintf(script, "				for (map<int32_t, int32_t>::const_iterator it2 = q_freq_count.begin();\n");
	fprintf(script, "					it2 != q_freq_count.end(); ++ it2)\n");
	fprintf(script, "				{\n");
	fprintf(script, "					for (int i=0; i<vec.size(); ++i) {\n");
	fprintf(script, "						if (vec[i].code == it2->first) {\n");
	fprintf(script, "							freq_count_file << \"\\\"\" << vec[i].stub_text\n");
	fprintf(script, "								<< \"\\\"\" << \",\";\n");
	fprintf(script, "						}\n");
	fprintf(script, "					}\n");
	fprintf(script, "					freq_count_file << it2->first << \", \"\n");
	fprintf(script, "						<< it2->second << endl;\n");
	fprintf(script, "				}\n");
	fprintf(script, "			} else {\n");
	fprintf(script, "				freq_count_file << \", code, frequency\" << endl;\n");
	fprintf(script, "				map<int32_t, int32_t>  q_freq_count = freq_count[question_name_str.str()];\n");
	fprintf(script, "				for (map<int32_t, int32_t>::const_iterator it2 = q_freq_count.begin();\n");
	fprintf(script, "					it2 != q_freq_count.end(); ++ it2)\n");
	fprintf(script, "				{\n");
	fprintf(script, "					freq_count_file << \", \" << it2->first << \", \"\n");
	fprintf(script, "						<< it2->second << endl;\n");
	fprintf(script, "				}\n");
	fprintf(script, "			}\n");


	// fprintf(script, "                   freq_count_file << \"code, frequency\" << endl;\n");
	// fprintf(script, "                   // map<int32_t, int32_t>  q_freq_count = it->second;\n");
	// fprintf(script, "                   map<int32_t, int32_t>  q_freq_count = freq_count[question_name_str.str()];\n");
	// fprintf(script, "                   for (map<int32_t, int32_t>::const_iterator it2 = q_freq_count.begin();\n");
	// fprintf(script, "                                   it2 != q_freq_count.end(); ++ it2) {\n");
	// fprintf(script, "                       freq_count_file << it2->first << \", \" \n");
	// fprintf(script, "                               << it2->second << endl;\n");
	// fprintf(script, "                   }\n");


	fprintf(script, "           }\n");
	fprintf(script, "           freq_count_file << endl;\n");
	fprintf(script, "	for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {\n");
	fprintf(script, "		delete qtm_datafile_question_disk_map[i];\n");
	fprintf(script, "		qtm_datafile_question_disk_map[i] = 0;\n");
	fprintf(script, "	}\n");
	fprintf(script, "	for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {\n");
	fprintf(script, "		delete ascii_flatfile_question_disk_map[i];\n");
	fprintf(script, "		ascii_flatfile_question_disk_map[i] = 0;\n");
	fprintf(script, "	}\n");

	fprintf(script, "    }\n");
	fprintf(script, "\n");

	fprintf(script, "} /* close eval */\n");
}

void print_read_a_serial_no (FILE * script)
{
	fprintf (script, "\n");
	fprintf (script, "    int read_a_serial_no()\n");
	fprintf (script, "    {\n");
	fprintf (script, "	//cout << \"ENTER: \"  << __FILE__ << \", \" << __LINE__ << \", \" << __PRETTY_FUNCTION__ << endl;\n"); 
	fprintf (script, "restart:\n");
	fprintf (script, "	struct dirent *directory_entry = readdir(directory_ptr);\n");
	fprintf (script, "	if (directory_entry == NULL) {\n");
	fprintf (script, "	    // we have read upto the last record in the directory\n");
	fprintf (script, "	    cout << \"finished reading all data files ... exiting\"\n");
	fprintf (script, "		<< endl;\n");
	fprintf (script, "	    return 0;\n");
	fprintf (script, "	}\n");
	fprintf (script, "	string dir_entry_name(directory_entry->d_name);\n");
	fprintf (script, "	int len_entry = dir_entry_name.length();\n");
	fprintf (script, "	if (len_entry > 4 &&\n");
	fprintf (script, "	    dir_entry_name[len_entry - 1] == 't' &&\n");
	fprintf (script, "	    dir_entry_name[len_entry - 2] == 'a' &&\n");
	fprintf (script, "	    dir_entry_name[len_entry - 3] == 'd' &&\n");
	fprintf (script, "	    dir_entry_name[len_entry - 4] == '.') {\n");
	fprintf (script, "	    if (dir_entry_name.length() < jno.length() + 6\n");
	fprintf (script, "		/* \"_1.dat\" is the shortest possible datafile name for our study */\n");
	fprintf (script, "		) {\n");
	fprintf (script, "		// cannot be our data file\n");
	fprintf (script, "		goto restart;\n");
	fprintf (script, "	    }\n");
	fprintf (script, "	    bool not_our_file = false;\n");
	fprintf (script, "	    for (int i = 0; i < jno.length(); ++i) {\n");
	fprintf (script, "		if (!(jno[i] == dir_entry_name[i])) {\n");
	fprintf (script, "		    // cannot be our data file\n");
	fprintf (script, "		    not_our_file = true;\n");
	fprintf (script, "		    break;\n");
	fprintf (script, "		}\n");
	fprintf (script, "	    }\n");
	fprintf (script, "	    if (not_our_file) {\n");
	fprintf (script, "		//continue;\n");
	fprintf (script, "		goto restart;\n");
	fprintf (script, "	    }\n");
	fprintf (script, "	    // all our data files are expected\n");
	fprintf (script, "	    // to have a \".dat\" ending and '_' after job number\n");
	fprintf (script, "	    // find the \".\"\n");
	fprintf (script, "	    cout << dir_entry_name << endl;\n");
	fprintf (script, "	    if (dir_entry_name[jno.length()] != '_') {\n");
	fprintf (script, "		not_our_file = true;\n");
	fprintf (script, "		//continue;\n");
	fprintf (script, "		goto restart;\n");
	fprintf (script, "	    }\n");
	fprintf (script, "	    stringstream file_ser_no_str;\n");
	fprintf (script, "	    for (int i = jno.length() + 1;\n");
	fprintf (script, "		 i < dir_entry_name.length(); ++i) {\n");
	fprintf (script, "		if (isdigit(dir_entry_name[i])) {\n");
	fprintf (script, "		    file_ser_no_str << dir_entry_name[i];\n");
	fprintf (script, "		} else {\n");
	fprintf (script, "		    if ((i + 4 == dir_entry_name.length())\n");
	fprintf (script, "			&& dir_entry_name[i] == '.'\n");
	fprintf (script, "			&& dir_entry_name[i + 1] == 'd'\n");
	fprintf (script, "			&& dir_entry_name[i + 2] == 'a'\n");
	fprintf (script, "			&& dir_entry_name[i + 3] == 't') {\n");
	fprintf (script, "			//its most probably our file \n");
	fprintf (script, "			// need to check leading digit is not 0\n");
	fprintf (script, "			break;\n");
	fprintf (script, "		    } else {\n");
	fprintf (script, "			// it's not our file \n");
	fprintf (script, "			not_our_file = true;\n");
	fprintf (script, "			goto restart;\n");
	fprintf (script, "		    }\n");
	fprintf (script, "		}\n");
	fprintf (script, "	    }\n");
	fprintf (script, "	    if (not_our_file) {\n");
	fprintf (script, "		    goto restart;\n");
	fprintf (script, "	    }\n");
	fprintf (script, "	    if ((file_ser_no_str.str())[0] == '0') {\n");
	fprintf (script, "		// the leading digit of our data file\n");
	fprintf (script, "		// can never be zero - so its not our file\n");
	fprintf (script, "		goto restart;\n");
	fprintf (script, "	    }\n");
	fprintf (script, "	    cout << \"got a data file: \" << dir_entry_name << endl;\n");
	fprintf (script, "	    int file_ser_no = atoi(file_ser_no_str.str().c_str());\n");
	fprintf (script, "	    load_data(jno, file_ser_no);\n");
	fprintf (script, "	    merge_disk_data_into_questions2(qscript_stdout, last_question_answered, last_question_visited);\n");
	fprintf (script, "	    return file_ser_no;\n");
	fprintf (script, "	} else {\n");
	fprintf (script, "	    // not our data file\n");
	fprintf (script, "	    goto restart;\n");
	fprintf (script, "	}\n");
	fprintf (script, "    }\n");
	fprintf (script, "\n");
}

void print_write_qtm_data_to_disk(FILE *script)
{
	fprintf(script, "void write_qtm_data_to_disk()\n {\n");
	fprintf(script, "	using qtm_data_file_ns::qtm_data_file_writer_log;\n");
	fprintf(script, "	qtm_data_file_writer_log << \"writing serial no: \" << ser_no << \" to disk \\n\";\n");
	fprintf(script, "	for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {\n");
	fprintf(script, "		qtm_datafile_question_disk_map[i]->write_data ();\n");
	fprintf(script, "	}\n");
	fprintf(script, "	qtm_datafile_question_disk_map[0]->qtmDataFile_.write_record_to_disk(qtm_disk_file, ser_no);\n");
	fprintf(script, "	qtm_datafile_question_disk_map[0]->qtmDataFile_.Reset();\n");
	fprintf(script, "	//qtm_datafile_question_disk_map[0]->Reset();\n");
	fprintf(script, "	for (int32_t i = 0; i < qtm_datafile_question_disk_map.size(); ++i) {\n");
	fprintf(script, "		qtm_datafile_question_disk_map[i]->Reset();\n");
	fprintf(script, "	}\n");
	fprintf(script, "	do_freq_counts();\n");
	/*
	fprintf(script, "       for (int32_t i = 0; i < question_list.size(); ++i) {\n");
	fprintf(script, "                       AbstractQuestion * q = question_list[i];\n");
	fprintf(script, "			stringstream question_name_str;\n");
	fprintf(script, "			question_name_str << q->questionName_;\n");
			
	fprintf(script, "		    if (q->loop_index_values.size()) {\n");
	fprintf(script, "				for (int j=0; j<q->loop_index_values.size(); ++j) {\n");
	fprintf(script, "					question_name_str << \".\" << q->loop_index_values[j];\n");
	fprintf(script, "				}\n");
	fprintf(script, "		    }\n");
	fprintf(script, "                       map<int , int> q_freq_map = freq_count[question_name_str.str()];\n");
	fprintf(script, "                       for (set<int32_t>::iterator it = q->input_data.begin();\n");
	fprintf(script, "                                       it != q->input_data.end(); ++it) {\n");
	fprintf(script, "                               q_freq_map[*it] ++;\n");
	fprintf(script, "                       }\n");
	fprintf(script, "                       freq_count[question_name_str.str()] = q_freq_map;\n");
	fprintf(script, "       }\n");
	*/


	fprintf(script, "}\n");
}

void print_do_freq_counts(FILE *script)
{
	fprintf(script, "void do_freq_counts()\n{\n");
	fprintf(script, "\tfor (int32_t i = 0; i < question_list.size(); ++i) {\n");
	fprintf(script, "\t\tAbstractQuestion * q = question_list[i];\n");
	fprintf(script, "\t\tstringstream question_name_str;\n");
	fprintf(script, "\t\tquestion_name_str << q->questionName_;\n");
	fprintf(script, "\t\tif (q->loop_index_values.size()) {\n");
	fprintf(script, "\t\t\tfor (int j=0; j<q->loop_index_values.size(); ++j) {\n");
	fprintf(script, "\t\t\t\tquestion_name_str << \".\" << q->loop_index_values[j];\n");
	fprintf(script, "\t\t\t}\n");
	fprintf(script, "\t\t}\n");
	fprintf(script, "\t\tmap<int , int> q_freq_map = freq_count[question_name_str.str()];\n");
	fprintf(script, "\t\tfor (set<int32_t>::iterator it = q->input_data.begin();\n");
	fprintf(script, "\t\t\tit != q->input_data.end(); ++it) {\n");
	fprintf(script, "\t\t\t\tq_freq_map[*it] ++;\n");
	fprintf(script, "\t\t}\n");
	fprintf(script, "\t\tfreq_count[question_name_str.str()] = q_freq_map;\n");
	fprintf(script, "\t}\n");
	fprintf(script, "}\n");
}

void print_write_ascii_data_to_disk(FILE *script)
{
	fprintf(script, "void write_ascii_data_to_disk()\n{\n");
	fprintf(script, "	stringstream temp_ser_no_str;\n");
	fprintf(script, "	temp_ser_no_str << ser_no;\n");
	fprintf(script, "	if (temp_ser_no_str.str().length() > ser_no_pos) {\n");
	fprintf(script, "		cerr << \"space reserved to hold serial no: \" \n");
	fprintf(script, "			<< ser_no_pos << \" is not enough\"\n");
	fprintf(script, "			<< \" to hold this serial no: \" \n");
	fprintf(script, "			<< ser_no << endl;\n");
	fprintf(script, "		exit(1);\n");
	fprintf(script, "	} else {\n");
	fprintf(script, "		//char * ptr = flat_file_output_buffer;\n");
	fprintf(script, "		for (int i=0; i<temp_ser_no_str.str().length(); ++i) {\n");
	fprintf(script, "			flat_file_output_buffer[i] = temp_ser_no_str.str()[i];\n");
	fprintf(script, "		//cout << \"writing digit \" << temp_ser_no_str[i] << \" to flat_file_output_buffer\" << endl;\n");
	fprintf(script, "		}\n");
	fprintf(script, "	}\n");
	fprintf(script, "\n");
	fprintf(script, "	for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {\n");
	fprintf(script, "		ascii_flatfile_question_disk_map[i]->write_data (flat_file_output_buffer);\n");
	fprintf(script, "	}\n");
	fprintf(script, "	// cout << \"output_buffer: \" << flat_file_output_buffer;\n");
	fprintf(script, "	flat_file << flat_file_output_buffer << endl;\n");
	fprintf(script, "	memset(flat_file_output_buffer, ' ', len_flat_file_output_buffer-1);\n");
	fprintf(script, "	do_freq_counts();\n");
	fprintf(script, "}\n");
}

void print_write_spss_file_for_ascii_data_to_disk(/*FILE *script*/StatementCompiledCode & compute_flat_map_code)
{
	compute_flat_map_code.program_code << "\tstring spss_syn_file_name(jno + string(\"-flat-ascii.sps\"));\n";
	compute_flat_map_code.program_code << "\tfstream spss_syn_file(spss_syn_file_name.c_str(), ios_base::out|ios_base::ate);\n";
	compute_flat_map_code.program_code << "\t spss_syn_file << \"DATA LIST FILE='\" << "
		<< " jno << \".dat'\\n\"<< endl << \"/RESPID\t\t\t1-6\\n\";\n";
	compute_flat_map_code.program_code << "\tfor (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {\n"
		<< "\t\tascii_flatfile_question_disk_map[i]->write_spss_pull_data(spss_syn_file);\n"
		<< "\t}\n";
	compute_flat_map_code.program_code << "\t spss_syn_file << \".\\n\";\n";
	compute_flat_map_code.program_code << "\n spss_syn_file << \"exe.\\n\";\n";
	compute_flat_map_code.program_code << "\tfor (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {\n"
		<< "\t\tascii_flatfile_question_disk_map[i]->write_spss_variable_labels(spss_syn_file);\n"
		<< "\t}\n";
	compute_flat_map_code.program_code << "\n spss_syn_file << \"exe.\\n\";\n";
	compute_flat_map_code.program_code << "\tfor (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {\n"
		<< "\t\tascii_flatfile_question_disk_map[i]->write_spss_value_labels(spss_syn_file);\n"
		<< "\t}\n";
	compute_flat_map_code.program_code << "\n spss_syn_file << \"exe.\\n\";\n";
	compute_flat_map_code.program_code << "\n spss_syn_file << \"save outfile=\\\"\" << jno << \".sav\\\"\\n\";\n";

	//compute_flat_map_code.program_code << "\t\tfor (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {\n"
	//	<< "\t\t\tqtm_datafile_question_disk_map[i]->print_qax(qtm_qax_file, string(\"setup-\")+jno);\n"
	//	<< "\t\t\tstring questionName = qtm_datafile_question_disk_map[i]->q->questionName_;\n"
	//	<< "\t\t\tif (qtm_datafile_question_disk_map[i]->q->loop_index_values.size() > 0) {\n"
	//	<< "\t\t\t\tsummary_tables[questionName].push_back(qtm_datafile_question_disk_map[i]);\n"
	//	<< "\t\t\t}\n"

}

void print_write_xtcc_data_to_disk(FILE *script)
{
	fprintf(script, "void write_xtcc_data_to_disk()\n {\n");
	// serial number goes into the 1st 4 bytes
	fprintf(script, "	void * void_ptr = &ser_no;\n");
	fprintf(script, "	char * char_ptr = static_cast<char*>(void_ptr);\n");
	fprintf(script, "	char * my_data_ptr = xtcc_datafile_output_buffer;\n");
	fprintf(script, "	for (int i=0; i<sizeof(int); ++i) {\n");
	fprintf(script, "		*my_data_ptr++ = *char_ptr++;\n");
	fprintf(script, "	}\n");
	fprintf(script, "\n");
	fprintf(script, "	for (int i=0; i<xtcc_question_disk_map.size(); ++i) {\n");
	fprintf(script, "		xtcc_question_disk_map[i]->write_data (xtcc_datafile_output_buffer);\n");
	fprintf(script, "	}\n");
	fprintf(script, "	//cout << \"output_buffer: \" << xtcc_datafile_output_buffer;\n");
	fprintf(script, "	xtcc_datafile . write(xtcc_datafile_output_buffer, len_xtcc_datafile_output_buffer);\n");
	fprintf(script, "	memset(xtcc_datafile_output_buffer, 0, len_xtcc_datafile_output_buffer-1);\n");
	fprintf(script, "	do_freq_counts();\n");
	fprintf(script, "	cout << \"len_xtcc_datafile_output_buffer: \" << len_xtcc_datafile_output_buffer << endl;\n");
	fprintf(script, "}\n");
}


void print_summary_axis(FILE * script)
{

	fprintf (script, "void print_summary_axis (vector<qtm_data_file_ns::QtmDataDiskMap*> & v, fstream & qtm_qax_file) \n");
	fprintf (script, "{\n");
	fprintf (script, "	AbstractQuestion * q = v[0]->q;\n");
	fprintf (script, "	if (q->q_type == spn) {\n");
	fprintf (script, "		int n_digits = 0;\n");
	fprintf (script, "		int rat_scale = 0;\n");
	fprintf (script, "		if (NamedStubQuestion * n_q = dynamic_cast<NamedStubQuestion*>(q)) {\n");
	fprintf (script, "			if (n_q->nr_ptr) {\n");
	fprintf (script, "				string & stub_name = n_q->nr_ptr->name;\n");
	fprintf (script, "				int multiplier = 1;\n");
	fprintf (script, "				for (int i=stub_name.length()-1; i>0; --i) {\n");
	fprintf (script, "					if ( isdigit(stub_name[i]) ) {\n");
	fprintf (script, "						int c = stub_name[i] - '0';\n");
	fprintf (script, "						++n_digits;\n");
	fprintf (script, "						rat_scale = rat_scale + c * multiplier;\n");
	fprintf (script, "						multiplier *= 10;\n");
	fprintf (script, "					} else {\n");
	fprintf (script, "						break;\n");
	fprintf (script, "					}\n");
	fprintf (script, "				}\n");
	fprintf (script, "			}\n");
	fprintf (script, "		}\n");
	fprintf (script, "		if (n_digits > 0) {\n");
	fprintf (script, "			string include_file_name;\n");
	fprintf (script, "			string mean_score_include_file;\n");
	fprintf (script, "			if (v[0]->width_ == 1) {\n");
	fprintf (script, "				include_file_name = \"rat1c.qin\";\n");
	fprintf (script, "				mean_score_include_file = \"mn1c.qin\";\n");
	fprintf (script, "			} else if (v[0]->width_ == 2) {\n");
	fprintf (script, "				include_file_name = \"rat2c.qin\";\n");
	fprintf (script, "				mean_score_include_file = \"mn2c.qin\";\n");
	fprintf (script, "			} else if (v[0]->width_ == 3) {\n");
	fprintf (script, "				include_file_name = \"rat3c.qin\";\n");
	fprintf (script, "				mean_score_include_file = \"mn3c.qin\";\n");
	fprintf (script, "			} else {\n");
	fprintf (script, "				include_file_name = \"unhandled width syntax error\";\n");
	fprintf (script, "				mean_score_include_file = \"unhandled width syntax error\";\n");
	fprintf (script, "			}\n");
	fprintf (script, "\n");

	fprintf (script, "			if (rat_scale == 5) {\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_top\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 5 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_top2\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 5 << \", \" << 4 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_bot\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_bot2\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \", \" << 2 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_mn\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << mean_score_include_file\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \":\" << 5 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "			}\n");

	fprintf (script, "			else if (rat_scale == 7) {\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_top\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 7 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_top2\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 7 << \", \" << 6 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_top3\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 5 << \":\" << 7 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_bot\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_bot2\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \", \" << 2 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_mn\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << mean_score_include_file\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \":\" << 7 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_bot3\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \":\" << 3 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "			}\n");

	fprintf (script, "			else if (rat_scale == 10) {\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_top\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 10 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_top2\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 10 << \", \" << 9 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_top3\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 8 << \":\" << 10 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_bot\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_bot2\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \", \" << 2 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_mn\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << mean_score_include_file\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \":\" << 10 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_bot3\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \":\" << 3 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "			}\n");

	fprintf (script, "		} else {\n");
	fprintf (script, "			qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "			qtm_qax_file << \"/*l \" << q->questionName_ << \"_sum\" << endl;\n");
	fprintf (script, "			qtm_qax_file << \"/*ttl\" << q->questionName_ << \".\" << v[0]->q->questionText_ << endl;\n");
	fprintf (script, "			for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "				qtm_qax_file << \"/**include summ.qin;qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 << endl;\n");
	fprintf (script, "			}\n");
	fprintf (script, "		}\n");
	fprintf (script, "	}\n");
	fprintf (script, "	cout << endl;\n");
	fprintf (script, "}\n");
}

void print_prompt_user_for_serial_no(FILE * script)
{
	fprintf(script, "	void prompt_user_for_serial_no()\n");
	fprintf(script, "	{\n");
	fprintf(script, "		wclear(data_entry_window);\n");
	fprintf(script, "		mvwprintw(data_entry_window, 1, 1, \"Enter Serial No (0) to exit: \");\n");
	fprintf(script, "		mvwscanw(data_entry_window, 1, 40, \"%%d\", & ser_no);\n");
	fprintf(script, "	}\n\n");
}

void print_ncurses_include_files (FILE * script)
{
	fprintf(script, "#include <curses.h>\n");
	fprintf(script, "#include <panel.h>\n");
}

void print_ncurses_func_prototypes (FILE * script)
{
	fprintf(script, "WINDOW *create_newwin(int32_t height, int32_t width, int32_t starty, int32_t startx);\n");
	fprintf(script, "void SetupNCurses(WINDOW * &  question_window,\n"
			"			WINDOW * &  stub_list_window,\n"
			"			WINDOW * & data_entry_window,\n"
			"			WINDOW * & error_msg_window,\n"
			"			WINDOW * & help_window,\n"
			"			PANEL * &  question_panel,\n"
			"			PANEL * &  stub_list_panel,\n"
			"			PANEL * & data_entry_panel,\n"
			"			PANEL * & error_msg_panel,\n"
			"			PANEL * & help_panel);\n");
	fprintf (script, "void define_some_pd_curses_keys();\n");
	fprintf (script, "string print_recode_edit_qax (qtm_data_file_ns::QtmDataDiskMap * driver_q, qtm_data_file_ns::QtmDataDiskMap * recode_q, int index);\n");
}

void print_GetQuestionMapEntry(FILE * script)
{

	fprintf(script, "qtm_data_file_ns::QtmDataDiskMap* GetQuestionMapEntry(vector <qtm_data_file_ns::QtmDataDiskMap*> & qtm_datafile_question_disk_map,\n");
	fprintf(script, "			string name)\n");
	fprintf(script, "{\n");
	fprintf(script, "	for (int i=0; i < qtm_datafile_question_disk_map.size(); ++i) {\n");
	fprintf(script, "		if (qtm_datafile_question_disk_map[i]->q->questionName_ == name) {\n");
	fprintf(script, "			return qtm_datafile_question_disk_map[i];\n");
	fprintf(script, "		}\n");
	fprintf(script, "	}\n");
	fprintf(script, "	return 0;\n");
	fprintf(script, "}\n");

}

void print_GetQuestionMapEntryArrayQ (FILE * script)
{
	fprintf (script, "\n");
	fprintf (script, "vector <qtm_data_file_ns::QtmDataDiskMap*> GetQuestionMapEntryArrayQ\n");
	fprintf (script, "	(vector <qtm_data_file_ns::QtmDataDiskMap*> & qtm_datafile_question_disk_map,\n");
	fprintf (script, "			string name)\n");
	fprintf (script, "{\n");
	fprintf (script, "	string dummy_output_filename (string(\"dummy.output\"));\n");
	fprintf (script, "	fstream dummy_output_file(dummy_output_filename.c_str(), ios_base::out|ios_base::app);\n");
	fprintf (script, "	dummy_output_file << \"searching for : \" << name << endl;\n");
	fprintf (script, "	vector <qtm_data_file_ns::QtmDataDiskMap*> result ;\n");
	fprintf (script, "	for (int i=0; i < qtm_datafile_question_disk_map.size(); ++i) {\n");
	fprintf (script, "		string s1 = qtm_datafile_question_disk_map[i]->q->questionName_ ;\n");
	fprintf (script, "		dummy_output_file << \"questionName_: \" << s1 << endl;\n");
	fprintf (script, "		string s3 = \"\";\n");
	fprintf (script, "		if (s1.length() > name.length()) {\n");
	fprintf (script, "			s3 = s1.substr(0, name.length());\n");
	fprintf (script, "		}\n");
	fprintf (script, "		dummy_output_file << s3 << endl;\n");
	fprintf (script, "		if (qtm_datafile_question_disk_map[i]->q->questionName_ == name) {\n");
	fprintf (script, "			result.push_back(qtm_datafile_question_disk_map[i]);\n");
	fprintf (script, "			dummy_output_file << \"added to result\" << endl;\n");
	fprintf (script, "		}\n");
	fprintf (script, "	}\n");
	fprintf (script, "	return result;\n");
	fprintf (script, "}\n");

}

void print_recode_edit_qax (FILE * script)
{
	stringstream warn_mesg;
	warn_mesg << " There is a lot of code duplication between print_recode_edit_qax and function (QtmDataDiskMap::print_qax) . This duplicated code has to be re-visited and normalized" << endl;
	LOG_MAINTAINER_MESSAGE(warn_mesg.str());

	fprintf (script, "string print_recode_edit_qax (qtm_data_file_ns::QtmDataDiskMap * driver_q, qtm_data_file_ns::QtmDataDiskMap * recode_q, int index)\n");
	fprintf (script, "{\n");
	fprintf (script, "	stringstream ax;\n");
	//fprintf (script, "	ax << \"l \";\n");
	fprintf (script, "	string setup_dir( string(\"setup-\") + jno + string (\"/\"));\n");
	fprintf (script, "	NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*> (driver_q->q);\n");
	fprintf (script, "	if (nq) {\n");
	fprintf (script, "		const int TEXT_LEN_BREAK_AT = 120;\n");
	fprintf (script, "		vector <string> smaller_ttls = qtm_data_file_ns::split_into_smaller_chunks (recode_q->q->questionText_, TEXT_LEN_BREAK_AT);\n");
	fprintf (script, "		stringstream ttl_string;\n");
	fprintf (script, "		for (int i=0; i<smaller_ttls.size(); ++i) {\n");
	fprintf (script, "			ttl_string << smaller_ttls[i];\n");
	fprintf (script, "		}\n");

	fprintf (script, "		if (recode_q->q->loop_index_values.size() > 0) {\n");
	fprintf (script, "			stringstream l_base_text;\n");
	fprintf (script, "			if (recode_q->baseText_.isDynamicBaseText_ == false) {\n");
	fprintf (script, "				l_base_text << recode_q->baseText_.baseText_ ;\n");
	fprintf (script, "			} else {\n");
	fprintf (script, "				l_base_text << qtm_data_file_ns::print_dynamic_base_text (recode_q->q, recode_q->baseText_);\n");
	fprintf (script, "			}\n");
	fprintf (script, "			l_base_text << \" who use : \" << nq->nr_ptr->stubs[index].stub_text << endl;\n");
	fprintf (script, "			if (recode_q->q->loop_index_values.size()==1) {\n");
	fprintf (script, "				ax << \"*include \" << \"r_\" << recode_q->q->questionName_ \n");
	fprintf (script, "					<<\".qax\"\n");
	fprintf (script, "					<<\";qlno=\" << recode_q->q->loop_index_values[0] << \";var_name=\" << recode_q->q->questionName_ ;\n");
	
	fprintf (script, "\t\t\t\t\tfor (int i2=0; i2 < recode_q->q->loop_index_values.size(); ++i2) {\n");

	fprintf (script, "\t\t\t\t\t\t ax << \"_\" << recode_q->q->loop_index_values[i2];\n");
	fprintf (script, "\t\t\t\t\t\t}\n");
	fprintf (script, " 				ax << \"_\" << nq->nr_ptr->stubs[index].stub_text_as_var_name()\n");
	fprintf (script, "					<<\";col(a)=\" << 1\n");
	fprintf (script, "					<<\";qat1t=&a\" << recode_q->q->loop_index_values[0] <<\"t;att1t=;qat2t=;att2t=/*;\"\n");
	fprintf (script, "					<<\"\\n+btxt=\" << l_base_text.str()\n");
	fprintf (script, "					<< endl\n");
	fprintf (script, "					<< endl;\n");
	fprintf (script, "			} else {\n");
	/* the same code using the for loop above with index variable i2 has to be used here : for double arrays this 
	   recode edit code generation has not been fixed
	   */
	fprintf (script, "				ax <<\"*include r_\" << recode_q->q->questionName_\n");
	fprintf (script, "					<<\".qax\"\n");
	fprintf (script, "					<<\";col(a)=\" << recode_q->q->loop_index_values[0] + 1\n");
	fprintf (script, "					<<\";qlno=\" << recode_q->q->loop_index_values[0] <<\"_\" << recode_q->q->loop_index_values[1] << \";var_name=\"  << recode_q->q->questionName_ << \"_\" << nq->nr_ptr->stubs[index].stub_text_as_var_name()\n");
	fprintf (script, "					<<\";qat1t=&a\" << recode_q->q->loop_index_values[0] <<\"t;att1t=\"\n");
	fprintf (script, "					<<\";qat2t=&b\" << recode_q->q->loop_index_values[0] <<\"t;att2t=\" << endl\n");
	fprintf (script, "					<<\"\\n+btxt = \" << l_base_text.str()\n");
	fprintf (script, "					<< endl\n");
	fprintf (script, "					<< endl;\n");
	fprintf (script, "			}\n");
	fprintf (script, "	\n");
	fprintf (script, "			bool is_1st_iter = true;\n");
	fprintf (script, "			for (int32_t i=0; i<recode_q->q->loop_index_values.size(); ++i) {\n");
	fprintf (script, "				if (recode_q->q->loop_index_values[i] != 0) {\n");
	fprintf (script, "					is_1st_iter = false;\n");
	fprintf (script, "					break;\n");
	fprintf (script, "				}\n");
	fprintf (script, "			}\n");
	fprintf (script, "			if (is_1st_iter == true) {\n");
	fprintf (script, "				// make questionName_ . qax file\n");
	fprintf (script, "				stringstream qax_fname;\n");
	fprintf (script, "				qax_fname << setup_dir <<\"\";\n");
	fprintf (script, "				qax_fname << \"r_\" << recode_q->q->questionName_ <<\".qax\";\n");
	fprintf (script, "				fstream ax(qax_fname.str().c_str(), std::ios_base::out | std::ios_base::trunc);\n");
	fprintf (script, "				ax <<\"l \" << recode_q->q->questionName_ <<\"_&qlno;c=&var_name(a0\";\n");
	fprintf (script, "				if (recode_q->width_>0) {\n");
	fprintf (script, "					ax <<\",a\" << recode_q->width_-1 ;\n");
	fprintf (script, "				} \n");
	fprintf (script, "				ax <<\") u $ $\" << endl;\n");
	fprintf (script, "				ax <<\"*include qttl.qin;\" \n");
	fprintf (script, "					<< ttl_string.str() << endl\n");
	fprintf (script, "					<<\"*include base.qin\" << endl;\n");
	fprintf (script, "	\n");
	fprintf (script, "				if (NamedStubQuestion * n_q = dynamic_cast<NamedStubQuestion*>(recode_q->q)) {\n");
	fprintf (script, "					recode_q->print_qin(setup_dir, \"&var_name\");\n");
	fprintf (script, "					if (n_q->nr_ptr) {\n");
	fprintf (script, "						if (n_q->no_mpn>1) {\n");
	fprintf (script, "							ax <<\"*include r_\" << n_q->nr_ptr->name <<\".min\"\n");
	fprintf (script, "							<< endl;\n");
	fprintf (script, "						} else {\n");
	fprintf (script, "							ax <<\"*include r_\" << n_q->nr_ptr->name <<\".sin\"\n");
	fprintf (script, "							<< endl;\n");
	fprintf (script, "						}\n");
	fprintf (script, "					}\n");
	fprintf (script, "				} else if (RangeQuestion * r_q = dynamic_cast<RangeQuestion*>(recode_q->q)) {\n");
	fprintf (script, "					ax <<\"*include \" << \"r_\" << recode_q->q->questionName_ <<\".qin\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "					stringstream fname;\n");
	fprintf (script, "					fname << setup_dir << \"r_\" << recode_q->q->questionName_ <<\".qin\";\n");
	fprintf (script, "					fstream qtm_include_file (fname.str().c_str(), \n");
	fprintf (script, "							std::ios_base::out | std::ios_base::trunc);\n");
	fprintf (script, "					if (recode_q->width_ == 1) {\n");
	fprintf (script, "						qtm_include_file <<\"val &var_name(a0);i;\" \n");
	fprintf (script, "							<< endl;\n");
	fprintf (script, "					} else {\n");
	fprintf (script, "						qtm_include_file <<\"val &var_name(a0\"\n");
	fprintf (script, "							<<\"\" << recode_q->width_ - 1 <<\");i;\" \n");
	fprintf (script, "							<< endl;\n");
	fprintf (script, "					}\n");
	fprintf (script, "				}\n");
	fprintf (script, "					\n");
	fprintf (script, "			}\n");
	fprintf (script, "		} else {\n");
	fprintf (script, "			ax << \"l \";\n");
	fprintf (script, "			ax << recode_q->q->questionName_ << \"_\" << nq->nr_ptr->stubs[index].stub_text_as_var_name();\n");
	fprintf (script, "			ax << \"; c=\" << recode_q->q->questionName_ << \"_\" << nq->nr_ptr->stubs[index].stub_text_as_var_name() << \"(1, \"<< recode_q->totalLength_ << \") u $ $\\n\"\n");
	fprintf (script, "				<< endl;\n");
	fprintf (script, "			ax << \"*include qttl.qin;qno=\" << recode_q->q->questionName_ << \"_\" << nq->nr_ptr->stubs[index].stub_text_as_var_name() << \";\";\n");
	fprintf (script, "	\n");
	fprintf (script, "	\n");
	fprintf (script, "			ax << ttl_string.str();\n");
	fprintf (script, "	\n");
	fprintf (script, "			ax << \"+q1att=;att1t=/*\" << endl;\n");
	fprintf (script, "			ax << \"+q2att=;att2t=/*\" << endl;\n");
	fprintf (script, "	\n");
	fprintf (script, "			if (recode_q->baseText_.isDynamicBaseText_ == false) {\n");
	fprintf (script, "				ax <<\"*include base.qin;btxt=\" << recode_q->baseText_.baseText_ << \" who use : \" << nq->nr_ptr->stubs[index].stub_text << endl;\n");
	fprintf (script, "			} else {\n");
	fprintf (script, "				ax <<\"*include base.qin;btxt= Unexpected case non-array questions should not have dynamicBaseQuestion_ : %d, %s, %s \";\n", __LINE__, __FILE__, __PRETTY_FUNCTION__);
	fprintf (script, "			}\n");
	//fprintf (script, "			ax <<\"*include base.qin;btxt= All those respondents who coded\";\n");
	//fprintf (script, "			if (recode_q->q->loop_index_values.size() == 1) {\n");
	//fprintf (script, "				ax <<\"\\\"\" << recode_q->q->loop_index_values[0] <<\"\\\" i.e.\";\n");
	//fprintf (script, "				NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*> (recode_q->baseText_.dynamicBaseQuestion_);\n");
	//fprintf (script, "				if (nq) {\n");
	//fprintf (script, "					vector<stub_pair> & vec= (nq->nr_ptr->stubs);\n");
	//fprintf (script, "					for (int i=0; i<vec.size(); ++i) {\n");
	//fprintf (script, "						if (vec[i].code == recode_q->q->loop_index_values[0]+1) {\n");
	//fprintf (script, "							ax << vec[i].stub_text;\n");
	//fprintf (script, "							break;\n");
	//fprintf (script, "						}\n");
	//fprintf (script, "					}\n");
	//fprintf (script, "				}\n");
	//fprintf (script, "				ax <<\" at\" << recode_q->baseText_.dynamicBaseQuestion_->questionName_ << endl;\n");
	//fprintf (script, "			}\n");
	fprintf (script, "	\n");
	fprintf (script, "			if (NamedStubQuestion * n_q = dynamic_cast<NamedStubQuestion*>(recode_q->q)) {\n");
	fprintf (script, "				recode_q->print_qin (setup_dir, \"&var_name\");\n");
	fprintf (script, "				if (n_q->nr_ptr) {\n");
	fprintf (script, "					if (n_q->no_mpn>1) {\n");
	fprintf (script, "						ax <<\"*include r_\" << n_q->nr_ptr->name <<\".min;\"\n");
	fprintf (script, "						<<\"col(a)=\" << 1 << \";var_name=\" << recode_q->q->questionName_ << \"_\" << nq->nr_ptr->stubs[index].stub_text_as_var_name() << \";\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "					} else {\n");
	fprintf (script, "						ax <<\"*include r_\" << n_q->nr_ptr->name <<\".sin;\"\n");
	fprintf (script, "						<<\"col(a)=\" << 1 << \";var_name=\" << recode_q->q->questionName_ << \"_\" << nq->nr_ptr->stubs[index].stub_text_as_var_name() << \";\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "					}\n");
	fprintf (script, "				}\n");
	fprintf (script, "			} else if (RangeQuestion * r_q = dynamic_cast<RangeQuestion*>(recode_q->q)) {\n");
	fprintf (script, "				ax <<\"*include r_\" << recode_q->q->questionName_ <<\".qin;\"\n");
	fprintf (script, "					<<\"col(a)=\" << 1 << \";var_name=\" << recode_q->q->questionName_ << \"_\" << nq->nr_ptr->stubs[index].stub_text_as_var_name() << \";\"\n");
	fprintf (script, "					<<\"\"\n");
	fprintf (script, "					<< endl;\n");
	fprintf (script, "				stringstream fname;\n");
	fprintf (script, "				fname << setup_dir << \"r_\" << recode_q->q->questionName_ <<\".qin;\";\n");
	fprintf (script, "				fstream qtm_include_file (fname.str().c_str(), \n");
	fprintf (script, "						std::ios_base::out | std::ios_base::trunc);\n");
	fprintf (script, "				if (recode_q->width_ == 1) {\n");
	fprintf (script, "					qtm_include_file <<\"val &var_name(a0);i;\" \n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				} else {\n");
	fprintf (script, "					qtm_include_file <<\"val &var_name(a0\"\n");
	fprintf (script, "						<<\"\" << recode_q->width_ - 1 <<\");i;\" \n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "			}\n");
	fprintf (script, "	\n");
	fprintf (script, "			ax << endl;\n");
	fprintf (script, "		}\n");



	fprintf (script, "	} else {\n");
	fprintf (script, "		ax << \" driver question does not have named stubs, this should be an input file error\" << endl;\n");
	fprintf (script, "	}\n");
	fprintf (script, "	return ax.str();\n");
	fprintf (script, "}\n");
}























/* end of namespace */
}
