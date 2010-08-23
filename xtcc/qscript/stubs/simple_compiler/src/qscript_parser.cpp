#include "qscript_parser.h"
#include "config_parser.h"

#include <cstdlib>
#include <sstream>
#include <iostream>
#include "compiled_code.h"
extern int qscript_confparse();
extern void qscript_confrestart ( FILE *input_file );
namespace qscript_parser {
	using std::cerr;
	using std::cout;
	using std::endl;
	using std::stringstream;
	vector<AbstractExpression*> for_loop_max_counter_stack;
	vector<CompoundStatement*> compound_body_stack;
	Scope* active_scope;
	vector <Scope*> active_scope_list;
	int nest_lev=0;
	int flagIsAFunctionBody_=-1;
	int flagIsAForBody_=0;
	bool flag_next_stmt_start_of_block=false;
	vector<bool> blk_start_flag;
	vector <AbstractStatement*> blk_heads;
	//const int DEFAULT_STACK_SIZE=20;
	vector<CompoundStatement*> stack_cmpd_stmt;
	vector<string> stack_of_active_push_vars;
	map<string, vector<string> > map_of_active_vars_for_questions;

	AbstractExpression * recurse_for_index(int stack_index);


	ofstream debug_log_file("qscript_debug.log", std::ios_base::out|std::ios_base::trunc);
	using std::string;
	//void print_err(compiler_err_category cmp_err, 
	//	string err_msg, int line_no, 
	//	int compiler_line_no, string compiler_file_name);
	int line_no;
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


	QuestionType q_type;
#include "const_defs.h"
#include "xtcc_set.h"
	int no_mpn=0;
	XtccSet xs;
	int yylex();
	void yyerror(const char * s);
	int no_errors;

	struct AbstractStatement* tree_root=0;
	vector <AbstractQuestion*> question_list;
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);
	const bool XTCC_DEBUG_MEM_USAGE=true;
	bool skip_func_type_check(const char * fname);
	vector<mem_addr_tab>  mem_addr;
	vector <FunctionInformation*> func_info_table;
	int check_parameters(struct AbstractExpression* e, struct VariableList* v);

        vector <string> attribute_list;
	vector <named_range*> named_stubs_list;
	vector <named_attribute_list> named_attributes_list;
        vector <stub_pair> stub_list;
	int if_line_no=-1;
	
	int yywrap();

	string project_name;

}

namespace qscript_parser{

using std::string;

#include <sstream>

void print_header(FILE* script, bool ncurses_flag);
void print_array_question_class(FILE* script);
void print_close(FILE* script, ostringstream & program_code, bool  ncurses_flag);
void print_navigation_support_functions(FILE * script);
void print_reset_questionnaire(FILE * script);
void PrintDisplayActiveQuestions(FILE *script);
void PrintGetUserResponse(FILE *script);
void PrintSetupNCurses(FILE * script);
void PrintSignalHandler(FILE * script);
void PrintSetupSignalHandler(FILE * script);

string ExtractBaseFileName(const string & fname)
{
	string output_file_name = fname;
	int dot_pos = fname.find_last_of('.');
	if(!(dot_pos==string::npos)){
		output_file_name = fname.substr(0, dot_pos);
	}
	return output_file_name;
}

void GenerateCode(const string & src_file_name, bool ncurses_flag)
{
	cerr << "ENTER qscript_parser::GenerateCode" << endl;
	string output_file_name = ExtractBaseFileName(src_file_name);
	output_file_name += ".C";
	//string script_name("test_script.C");
	FILE * script = fopen(output_file_name.c_str(), "w");
	if(!script){
		cerr << "unable to open output file : " << output_file_name << endl;
		exit(1);
	}
	//ostringstream quest_defns, program_code;
	StatementCompiledCode code;

	print_header(script, ncurses_flag);
	tree_root->GenerateConsolidatedForLoopIndexes();
	tree_root->GenerateCode(code);
	fprintf(script, "%s\n", code.quest_defns.str().c_str());
	fprintf(script, "%s\n", code.array_quest_init_area.str().c_str());
	print_close(script, code.program_code, ncurses_flag);
	fflush(script);
	cerr << "EXIT qscript_parser::GenerateCode" << endl;
}

void print_header(FILE* script, bool ncurses_flag){
	fprintf(script, "#include <iostream>\n");
	fprintf(script, "#include <vector>\n");
	fprintf(script, "#include <string>\n");
	fprintf(script, "#include <sstream>\n");
	fprintf(script, "#include <fstream>\n");
	fprintf(script, "#include <map>\n");
	fprintf(script, "#include <cstdlib>\n");
	if(ncurses_flag)
		fprintf(script, "#include <curses.h>\n");
	fprintf(script, "#include <signal.h>\n");
	fprintf(script, "#include \"stmt.h\"\n");
	fprintf(script, "#include \"xtcc_set.h\"\n");
	fprintf(script, "#include \"stub_pair.h\"\n");
	fprintf(script, "#include \"symtab.h\"\n");
	fprintf(script, "#include \"qscript_lib.h\"\n");
	fprintf(script, "#include \"question_disk_data.h\"\n");
	fprintf(script, "#include \"question.h\"\n");
	fprintf(script, "#include \"user_navigation.h\"\n");


	fprintf(script, "string qscript_stdout_fname(\"qscript_stdout.log\");\n");
	fprintf(script, "FILE * qscript_stdout=0;\n");
	fprintf(script, "#include \"debug_mem.h\"\n");
	fprintf(script, "fstream debug_log_file(\"qscript_debug.log\", ios_base::out|ios_base::trunc);\n");

	fprintf(script, "using namespace std;\n");
	fprintf(script, "void read_data(const char * prompt);\n");
	fprintf(script, "extern vector<int> data;\n");
	fprintf(script, "extern UserNavigation user_navigation;\n");
	fprintf(script, "vector <AbstractQuestion*> question_list;\n");
	fprintf(script, "vector<mem_addr_tab>  mem_addr;\n");
	fprintf(script, "extern vector<question_disk_data*>  qdd_list;\n");
	fprintf(script, "void merge_disk_data_into_questions(FILE * qscript_stdout);\n");
	fprintf(script, "bool stopAtNextQuestion;\n");
	fprintf(script, "string jumpToQuestion;\n");
	fprintf(script, "int jumpToIndex;\n");


	//fprintf(script, "\tnoun_list_type noun_list[]= {\n");
	//fprintf(script, "\t\t\t{\t\"void\"\t, VOID_TYPE},\n");
	//fprintf(script, "\t\t\t{\t\"int8_t\" ,INT8_TYPE},\n");
	//fprintf(script, "\t\t\t{\t\"int16_t\" ,INT16_TYPE},\n");
	//fprintf(script, "\t\t\t{\t\"int32_t\" ,INT32_TYPE},\n");
	//fprintf(script, "\t\t\t{\t\"float\", FLOAT_TYPE},\n");
	//fprintf(script, "\t\t\t{\t\"double\", DOUBLE_TYPE}\n");
	//fprintf(script, "\t\t};\n");
	fprintf(script, "\n");
	fprintf(script, "int check_if_reg_file_exists(string jno, int ser_no);\n");
	fprintf(script, "map<string, vector<string> > map_of_active_vars_for_questions;\n");
	fprintf(script, "vector <int8_t> vector_int8_t;\n");
	fprintf(script, "vector <int16_t> vector_int16_t;\n");
	fprintf(script, "vector <int32_t> vector_int32_t;\n");
	fprintf(script, "vector <float> vector_float_t;\n");
	fprintf(script, "vector <double> vector_double_t;\n");
	fprintf(script, "bool back_jump=false;// no need for this but state the intent\n");
	fprintf(script, "void write_data_to_disk(const vector<AbstractQuestion*>& q_vec, string jno, int ser_no);\n");
	fprintf(script, "AbstractQuestion * ComputePreviousQuestion(AbstractQuestion * q);\n");
	fprintf(script, "WINDOW *create_newwin(int height, int width, int starty, int startx);\n");
	fprintf(script, "void SetupNCurses(WINDOW * &  question_window,\n");
	fprintf(script, "			WINDOW * &  stub_list_window,\n");
	fprintf(script, "			WINDOW * & data_entry_window);\n");
	fprintf(script, "void SetupSignalHandler();\n");
	fprintf(script, "static void sig_usr(int signo);\n");
	fprintf(script, "int ComputeJumpToIndex(AbstractQuestion * q);\n");
	fprintf(script, "void reset_questionnaire();\n");
	fprintf(script, "void DisplayActiveQuestions();\n");
	fprintf(script, "void GetUserResponse(string& qno, int &qindex);\n");
	print_array_question_class(script);


	fprintf(script, "int main(){\n");
	fprintf(script, "bool using_ncurses=%s;\n", (ncurses_flag ) ?  "true": "false");
	fprintf(script, "AbstractQuestion * last_question_answered=0;\n");
	fprintf(script, "qscript_stdout=fopen(qscript_stdout_fname.c_str(), \"w\");\n");
	if (ncurses_flag)
		fprintf(script, "	initscr();\n");
	fprintf(script, "	using namespace std;\n");
	fprintf(script, "	WINDOW 	* question_window=0,\n");
	fprintf(script, "		* stub_list_window=0,\n");
	fprintf(script, "		* data_entry_window=0;\n");
	if (ncurses_flag)
		fprintf(script, "	SetupNCurses(question_window, stub_list_window, data_entry_window);\n");
	if (ncurses_flag) {
		fprintf(script, "	if(question_window==0 || stub_list_window==0 || data_entry_window==0){\n");
		fprintf(script, "		cerr << \"Unable to create windows ... exiting\" << endl;\n");
		fprintf(script, "		return 1;\n");
		fprintf(script, "	}\n");
	}
	fprintf(script, "	SetupSignalHandler();\n");

	/*
	map<string, vector<string> > ::iterator iter;
	for(iter=map_of_active_push_vars_for_questions.begin();
		iter!=map_of_active_push_vars_for_questions.end();
		++iter){
		//fprintf("\t");
		string q_name = iter->first;
		fprintf(script, "vector <string> active_push_vars_%s;\n",
			q_name.c_str());
		vector<string>& v=iter->second;
		for(unsigned int i=0; i<v.size(); ++i){
			fprintf(script, "active_push_vars_%s.push_back(%s);\n",
				q_name.c_str(), v[i].c_str());
		}
		fprintf(script, "map_of_active_push_vars_for_questions[%s] = active_push_vars_%s;\n",
			q_name.c_str(), q_name.c_str());
	}
	*/

}

const char * file_exists_check_code();
const char * write_data_to_disk_code();

void print_close(FILE* script, ostringstream & program_code, bool ncurses_flag)
{
	//fprintf(script, "\treset_questionnaire();\n");
	fprintf(script, "\tint ser_no;\n");
	if(ncurses_flag) {
		fprintf(script, "\tint n_printed = mvwprintw(data_entry_window, 1, 1, \"Enter Serial No (0) to exit: \");\n");
		fprintf(script, "\tmvwscanw(data_entry_window, 1, 40, \"%%d\", & ser_no);\n");
	} else	{
		fprintf(script, "\tcout << \"Enter Serial No (0) to exit: \" << flush;\n");
		fprintf(script, "\tchar  newl; cin >> ser_no;cin.get(newl);\n");
	}
	//fprintf(script, "\treset_questionnaire();\n");

	//fprintf(script, "\twgetch(data_entry_window);\n");
	fprintf(script, "\tstring jno=\"%s\";\n", project_name.c_str());
	fprintf(script, "\twhile(ser_no!=0){\n");
	fprintf(script, "%s\n", file_exists_check_code());
	fprintf(script, "\tstart_of_questions:\n");

	fprintf(script, "\tif(back_jump==true){\n");
	//fprintf(script, "\tcout << \"have reached start_of_questions with back_jump\" << endl;\n");
	fprintf(script, "\tfprintf(qscript_stdout, \"have reached start_of_questions with back_jump\");\n");
	fprintf(script, "\t}\n");
	fprintf(script, "%s\n", program_code.str().c_str());
	/*
	fprintf(script, "\t\t\tstringstream fname_str;\n");
	fprintf(script, "\t\t\tfname_str << jno << \"_\" << ser_no << \".dat\";\n");
	fprintf(script, "\t\t\tFILE * fptr = fopen(fname_str.str().c_str(), \"w+b\");\n");
	fprintf(script, "\tfor (int i=0; i<question_list.size(); ++i){\n");
	fprintf(script, "\t\tfprintf(fptr, \"%%s: \", question_list[i]->name_.c_str());\n");
	fprintf(script, "\t\tfor( set<int>::iterator iter=question_list[i]->input_data.begin();\n");
	fprintf(script, "\t\t\t\titer!=question_list[i]->input_data.end(); ++iter){\n");
	fprintf(script, "\t\t\tfprintf(fptr, \"%%d \", *iter);\n");
	fprintf(script, "\t\t}\n");
	fprintf(script, "\t\tfprintf(fptr, \"\\n\");\n");
	fprintf(script, "\t\tquestion_list[i]->input_data.clear();\n");
	fprintf(script, "\t}\n");
	fprintf(script, "\tfclose(fptr);\n");
	fprintf(script, "\n");
	*/
	fprintf(script, "\tchar end_of_question_navigation;\n");
	if(ncurses_flag) {
		fprintf(script, "\twclear(data_entry_window);\n");
		fprintf(script, "\tmvwprintw(data_entry_window, 1, 1,\"End of Questionnaire: ((s)ave, (p)revious question, question (j)ump list)\" ); \n");
		fprintf(script, "\tmvwscanw(data_entry_window, 1, 75, \"%%c\", & end_of_question_navigation);\n");
	} else {
		fprintf(script, "\tcout << \"End of Questionnaire: (s to save, p = previous question, j = question jump list)\" << endl;\n"); 
		fprintf(script, "\tcin >> end_of_question_navigation;\n");
	}
	fprintf(script, "\tif(end_of_question_navigation=='s'){\n");
	fprintf(script, "\t\twrite_data_to_disk(question_list, jno, ser_no);\n");
	fprintf(script, "\t\treset_questionnaire();\n");
	fprintf(script, "\t} else if (end_of_question_navigation=='p'){\n");
	fprintf(script, "\t\tAbstractQuestion * target_question = ComputePreviousQuestion(last_question_answered);\n" );
	fprintf(script,	"\t\tjumpToQuestion = target_question->questionName_;\n");
	fprintf(script, "\t\tcout << \"target question: \" << jumpToQuestion;\n");
	fprintf(script, "\t\tback_jump=true;\n");
	fprintf(script, "\t\tuser_navigation=NOT_SET;\n");
	fprintf(script, "\t\tgoto start_of_questions;\n");
	fprintf(script, "\t}\n");

	//fprintf(script,	"\tcout << \"Enter Serial No (0) to exit: \" << flush;\n");
	if( ncurses_flag) {
		fprintf(script, "\twclear(data_entry_window);\n");
		fprintf(script, "\tmvwprintw(data_entry_window, 1, 1, \"Enter Serial No (0) to exit: \"); \n");
		fprintf(script, "\tmvwscanw(data_entry_window, 1, 40, \"%%d\", & ser_no);\n");
	} else {
		fprintf(script,	"\tcout <<  \"Enter Serial No (0) to exit: \";cout.flush();\n");
		fprintf(script, "\tcin >> ser_no;cin.get(newl);\n");
	}
	fprintf(script, "\n\t} /* close while */\n");
	if(ncurses_flag)
		fprintf(script, "\tendwin();\n");
	fprintf(script, "\n} /* close main */\n");
	fprintf(script, "%s\n", write_data_to_disk_code());
	print_navigation_support_functions(script);
	print_reset_questionnaire(script);
	PrintDisplayActiveQuestions(script);
	PrintGetUserResponse(script);
	if(ncurses_flag)
		PrintSetupNCurses(script);
	PrintSignalHandler(script);
	PrintSetupSignalHandler(script);
}

void print_navigation_support_functions(FILE * script)
{
	fprintf(script, "// The first question before this question that is answered\n");
	fprintf(script, "AbstractQuestion * ComputePreviousQuestion(AbstractQuestion * q)\n");
	fprintf(script, "{\n");
	fprintf(script, "	int current_question_index=-1;\n");
	fprintf(script, "	for(int i=0; i<question_list.size(); ++i){\n");
	fprintf(script, "		if(question_list[i]==q){\n");
	fprintf(script, "			current_question_index=i;\n");
	fprintf(script, "			break;\n");
	fprintf(script, "		}\n");
	fprintf(script, "	}\n");
	fprintf(script, "	if(current_question_index==-1){\n");
	fprintf(script, "		cerr << \"internal compiler error at runtime ... filename: \" \n");
	fprintf(script, "			<< __FILE__ \n");
	fprintf(script, "			<< \"line no: \" << __LINE__\n");
	fprintf(script, "			<< endl;\n");
	fprintf(script, "	}\n");
	fprintf(script, "	for(int i=current_question_index-1; i>=0; --i){\n");
	fprintf(script, "		if(question_list[i]->isAnswered_){\n");
	fprintf(script, "			return question_list[i];\n");
	fprintf(script, "		}\n");
	fprintf(script, "	}\n");
	fprintf(script, "	return 0;\n");
	fprintf(script, "}\n");

	fprintf(script,"int ComputeJumpToIndex(AbstractQuestion * q)\n");
	fprintf(script,"{\n");
	fprintf(script,"	cout << \"ENTER ComputeJumpToIndex: index:  \";\n");
	fprintf(script,"	for(int i=0; i<q->loop_index_values.size(); ++i){\n");
	fprintf(script,"		cout << q->loop_index_values[i] << \" \";\n");
	fprintf(script,"	}\n");
	fprintf(script,"	cout << endl;\n");
	fprintf(script,"	int index=0;\n");
	fprintf(script,"	for(int i=0; i<q->loop_index_values.size(); ++i){\n");
	fprintf(script,"		int tmp1=q->loop_index_values[i];\n");
	fprintf(script,"		for(int j=i+1; j<q->dummyArrayQuestion_->array_bounds.size(); ++j){\n");
	fprintf(script,"			tmp1 *=q->dummyArrayQuestion_->array_bounds[j];\n");
	fprintf(script,"		}\n");
	fprintf(script,"		index+=tmp1;\n");
	fprintf(script,"	}\n");
	fprintf(script,"	cout << \"EXIT ComputeJumpToIndex: returning : \" << index << endl;\n");
	fprintf(script,"	return index;\n");
	fprintf(script,"}\n");
}

void print_reset_questionnaire(FILE * script)
{
	fprintf(script, "void reset_questionnaire(){\n");
	fprintf(script, "for(int i=0; i< question_list.size(); ++i){\n");
	fprintf(script, "\tquestion_list[i]->isAnswered_=false;\n");
	fprintf(script, "\t}\n");
	fprintf(script, "}\n");

}

void PrintSetupNCurses(FILE * script)
{
	fprintf(script, "void SetupNCurses(WINDOW * &  question_window,\n");
	fprintf(script, "			WINDOW * &  stub_list_window,\n");
	fprintf(script, "			WINDOW * & data_entry_window)\n");
	fprintf(script, "{\n");
	fprintf(script, "	if(has_colors() == FALSE)\n");
	fprintf(script, "	{	endwin();\n");
	fprintf(script, "		printf(\"Your terminal does not support color\\n\");\n");
	fprintf(script, "		exit(1);\n");
	fprintf(script, "	}\n");
	fprintf(script, "	start_color();\n");
	fprintf(script, "	chtype space=' ';");
	fprintf(script, "	init_pair(1, COLOR_RED, COLOR_WHITE);\n");
	fprintf(script, "	init_pair(2, COLOR_GREEN, COLOR_WHITE);\n");
	fprintf(script, "	init_pair(3, COLOR_BLUE, COLOR_WHITE);\n");
	fprintf(script, "	init_pair(4, COLOR_MAGENTA, COLOR_CYAN);\n");






	fprintf(script, "	int maxX, maxY;\n");
	fprintf(script, "	getmaxyx(stdscr, maxY, maxX);\n");
	fprintf(script, "\n");
	fprintf(script, "\n");
	fprintf(script, "	int DATA_ENTRY_WINDOW_HEIGHT=4, DATA_ENTRY_WINDOW_WIDTH=maxX;\n");
	fprintf(script, "\n");
	fprintf(script, "       int starty = maxY-4;\n");
	fprintf(script, "       int startx = 0;\n");
	fprintf(script, "	data_entry_window = create_newwin(DATA_ENTRY_WINDOW_HEIGHT\n");
	fprintf(script, "			, DATA_ENTRY_WINDOW_WIDTH, starty, startx);\n");
	fprintf(script, "	wcolor_set(data_entry_window, COLOR_PAIR(1), 0);\n");
	fprintf(script, "	wattron(data_entry_window, COLOR_PAIR(1));\n");
	fprintf(script, "	wbkgd(data_entry_window, space | COLOR_PAIR(1));\n");
	fprintf(script, "	wattrset(data_entry_window, COLOR_PAIR(1));\n");

	fprintf(script, "       wrefresh(data_entry_window);\n");
	//fprintf(script, "	mvwprintw(data_entry_window, 1, 1, "data_entry_window: height: %d, width, %d"\n");
	//fprintf(script, "			, DATA_ENTRY_WINDOW_HEIGHT , DATA_ENTRY_WINDOW_WIDTH);\n");
	fprintf(script, "        keypad(data_entry_window, TRUE);\n");
	fprintf(script, "	// Divide the rest of the screen between the question window\n");
	fprintf(script, "	//  and the stub window in the ration 1:2\n");
	fprintf(script, "	int height_left = maxY - DATA_ENTRY_WINDOW_HEIGHT;\n");
	fprintf(script, "	int STUB_LIST_WINDOW_HEIGHT= (height_left / 3)*2, STUB_LIST_WINDOW_WIDTH=maxX;\n");
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
	fprintf(script, "	wrefresh(stub_list_window);\n");
	fprintf(script, "\n");
	fprintf(script, "\n");
	fprintf(script, "	int QUESTION_WINDOW_HEIGHT=(height_left%%3) + (height_left/3), QUESTION_WINDOW_WIDTH=maxX;\n");
	fprintf(script, "	starty=0;\n");
	fprintf(script, "	question_window = create_newwin(QUESTION_WINDOW_HEIGHT\n");
	fprintf(script, "			, QUESTION_WINDOW_WIDTH, starty, startx);\n");
	fprintf(script, "	wbkgd(question_window, space | COLOR_PAIR(3));\n");
	fprintf(script, "	wcolor_set(question_window, 3, 0);\n");
	fprintf(script, "	wattron(question_window, COLOR_PAIR(3));\n");
	//fprintf(script, "	mvwprintw(question_window, 1, 1, "question_window: height: %d, width, %d"\n");
	//fprintf(script, "			, QUESTION_WINDOW_HEIGHT , QUESTION_WINDOW_WIDTH);\n");
	fprintf(script, "	wrefresh(question_window);\n");
	fprintf(script, "\n");
	fprintf(script, "       cbreak();\n");
	fprintf(script, "	wmove(data_entry_window, 1,1);\n");
	//fprintf(script, "	wgetch(data_entry_window);\n");
	fprintf(script, "}\n");
	fprintf(script, "\n");
	fprintf(script, "\n");
	fprintf(script, "\n");
	fprintf(script, "WINDOW *create_newwin(int height, int width, int starty, int startx)\n");
	fprintf(script, "{       WINDOW *local_win;\n");
	fprintf(script, "\n");
	fprintf(script, "        local_win = newwin(height, width, starty, startx);\n");
	fprintf(script, "        box(local_win, 0 , 0);          /* 0, 0 gives default characters \n");
	fprintf(script, "                                         * for the vertical and horizontal\n");
	fprintf(script, "                                         * lines                        */\n");
	fprintf(script, "        wrefresh(local_win);            /* Show that box                */\n");
	fprintf(script, "\n");
	fprintf(script, "        return local_win;\n");
	fprintf(script, "}\n");
	fprintf(script, "\n");
}

void PrintDisplayActiveQuestions(FILE *script)
{
	fprintf(script, "void DisplayActiveQuestions()\n{\n\
			\tfor(int i=0; i<question_list.size(); ++i){\n\
			\t\tif(question_list[i]->isAnswered_)\n\
			\t\t\tcout << question_list[i]->questionName_ << \" \";\n\
			\t}\
			\tcout << endl;\n\
			\n}\n");
}

void PrintGetUserResponse(FILE *script)
{
	fprintf(script, "void GetUserResponse(string & qno, int & qindex)\n{\n\
			cin >> qno;\nqindex=0;\n}\n");
}

	bool skip_func_type_check(const char * fname){
		const char * skip_func_type_check_list[] = {"printf" };
		for (unsigned int i=0; i<sizeof(skip_func_type_check_list)/sizeof(skip_func_type_check_list[0]); ++i){
			if(!strcmp(fname, skip_func_type_check_list[i])){
				return true;
			}
		}
		return false;
	}

int check_parameters(AbstractExpression* e, VariableList* v){
	debug_log_file << "check_parameters: called" << endl;
	AbstractExpression* e_ptr=e;
	VariableList* fparam=v;
	bool match=true;
	/* Important point to note: I am not allowing references in ordinary variable decl
	   Only in function parameter list - the object is to allow modifying of variables
	   in a function as in C++
	   */

	int chk_param_counter=1;
	while (e_ptr && fparam) {
		//e_ptr->print();
		DataType etype=e_ptr->type_, fptype=fparam->variableType_; 
		if((etype>=INT8_TYPE && etype<=DOUBLE_TYPE) && 
			((fptype>=INT8_TYPE && fptype<=DOUBLE_TYPE)||
			 (fptype>=INT8_REF_TYPE && fptype<=DOUBLE_REF_TYPE))){
			DataType tdt=fptype;
				/* the code below makes a INT8_REF_TYPE -> INT8_TYPE
				   			a INT8_REF_TYPE -> INT8_TYPE
				 thats because we dont care much about references -> C++
				 does all the hard work. For checking types they are equivalent to us
				*/			
			if(tdt>=INT8_REF_TYPE) tdt=DataType(INT8_TYPE+tdt-INT8_REF_TYPE);
			if(etype <= tdt) {
				debug_log_file << "varname: "<< fparam->variableName_ << " chk_param_counter: " 
					<< chk_param_counter << " passed " << endl;
			}
		} else if ((etype>=INT8_ARR_TYPE&&etype<=DOUBLE_ARR_TYPE)&&
				(fptype>=INT8_ARR_TYPE&&fptype<=DOUBLE_ARR_TYPE)&&
				(etype==fptype)){
			debug_log_file << "varname: "<< fparam->variableName_ << " chk_param_counter: " 
					<< chk_param_counter << " passed " << endl;
		}else {
			match=false;
			cerr << "Parameter type mismatch name: " << endl;
			cerr << fparam->variableName_ << " expected type is " << fparam->variableType_
				<< " passed type is " << e_ptr->type_ 
				<< " line_no: " << line_no << " or currently allowed promotion to: " 
				<< e_ptr->type_+INT8_REF_TYPE
				<< endl;
			++no_errors;
		}
		e_ptr=e_ptr->next_;
		fparam=fparam->next_;
		chk_param_counter=chk_param_counter+1;
	}
	if(match==true){
		if(e_ptr==0&& fparam==0){
			match=true;
		} else {
			match=false;
			++no_errors;
			cerr << "NOTMATCHED: No of parameters in function call not matching with no of paramters in AbstractExpression: line_no"
				<< line_no << endl;
		}
	}
	if(!match) {
		cerr << "function parameter type check FAILURE: line_no " << line_no << endl;
	}
	return match;
}


const char * file_exists_check_code()
{
	const char * file_check_code =  
	"\tint exists=check_if_reg_file_exists(jno, ser_no);\n"
	"\tif(exists==1){\n"
	"\t	load_data(jno,ser_no);\n"
	"\t	merge_disk_data_into_questions(qscript_stdout);\n"
	/*
	"\t	for(unsigned int i=0; i< qdd_list.size(); ++i){\n"
	"\t		cout << qdd_list[i]->qno << endl;\n"
	"\t		cout  << \":\" << qdd_list[i]->data.size() << endl;\n"
	"\t		for(int j=0; j<qdd_list[i]->data.size(); ++j){\n"
	"\t			cout << qdd_list[i]->data[j] << \" \";\n"
	"\t		}\n"
	"\t		cout << endl;\n"
	"\t	}\n"
	*/
	"\t}\n";
	cerr << "fix me : add code for `if file is invalid` case "
		<< __func__ << "FILE: " << __FILE__ 
		<< ", line: " << __LINE__ << endl;

	return file_check_code;
}


AbstractStatement* setup_stub_manip_stmt(DataType dt
		, char* stub_list_name , char * question_name
	){
	int index=-1;
	for(int i=0; i<named_stubs_list.size(); ++i){
		named_range * nr_ptr = named_stubs_list[i];
		if(nr_ptr->name==stub_list_name){
			index=i;
			break;
		}
	}
	if(index==-1){
		stringstream err_text;
		err_text << "named stub list does not exist: " << stub_list_name;
		print_err(compiler_sem_err, err_text.str(),
			line_no, __LINE__, __FILE__  );
	} 
	int index_question=-1;
	for(int i=0; i<question_list.size(); ++i){
		if(question_list[i]->questionName_ == question_name){
			index_question=i;
			break;
		}
	}
	if(index_question==-1){
		stringstream err_text;
		err_text << "AbstractQuestion does not exist: " << question_name;
		print_err(compiler_sem_err, err_text.str(),
			line_no, __LINE__, __FILE__  );
	} else {
		if(index_question>=0 && index>=0){
			NamedStubQuestion * q_ptr= 
				dynamic_cast<NamedStubQuestion*> (question_list[index_question]);
			if(q_ptr){
				if(! (q_ptr->nr_ptr->name == stub_list_name) ){
					stringstream err_text;
					err_text << "AbstractQuestion: " << question_name
						<< " named range: " << q_ptr->nr_ptr->name 
						<< " and named stub is : " << stub_list_name 
						<< endl;

					print_err(compiler_sem_err, err_text.str(),
						line_no, __LINE__, __FILE__  );
				}
			} else {
				stringstream err_text;
				err_text << "AbstractQuestion : " << question_name <<
					"is not a named range AbstractQuestion" ;
				print_err(compiler_sem_err, err_text.str(),
					line_no, __LINE__, __FILE__  );
			}
		}
	}
	struct AbstractStatement* st_ptr = new StubManipStatement(dt,
		line_no, stub_list_name, question_name);
	
	return st_ptr;
}


AbstractStatement* setup_stub_manip_stmt_set_unset(DataType dt
		, char* stub_list_name)
{
	int index=-1;
	for(int i=0; i<named_stubs_list.size(); ++i){
		named_range * nr_ptr = named_stubs_list[i];
		if(nr_ptr->name==stub_list_name){
			index=i;
			break;
		}
	}
	if(index==-1){
		stringstream err_text;
		err_text << "named stub list does not exist: " << stub_list_name;
		print_err(compiler_sem_err, err_text.str(),
			line_no, __LINE__, __FILE__  );
	} 
	struct AbstractStatement* st_ptr = new StubManipStatement(dt,
		line_no, stub_list_name);
	
	return st_ptr;
}

const char * write_data_to_disk_code()
{
	const char * write_data_disk_code = 
	"\tvoid write_data_to_disk(const vector<AbstractQuestion*>& q_vec\n"
	"\t	, string jno\n"
	"\t	, int ser_no) {\n"
	"\t	stringstream fname_str;\n"
	"\t	fname_str << jno << \"_\" << ser_no << \".dat\";\n"
	"\t	//FILE * fptr = fopen(fname_str.str().c_str(), \"w+b\");\n"
	"\t\n"
	"\t\n"
	"\t	std::ofstream data_file;\n"
	"\t	data_file.exceptions(std::ios::failbit | std::ios::badbit);\n"
	"\t	data_file.open(fname_str.str().c_str(), ios_base::ate);\n"
	"\t\n"
	"\t	for (int i=0; i<question_list.size(); ++i){\n"
	"\t		question_list[i]->WriteDataToDisk(data_file);\n"
	"\t		/*\n"
	"\t		fprintf(fptr, \"%s: \", question_list[i]->name.c_str());\n"
	"\t		for( set<int>::iterator iter=question_list[i]->input_data.begin();\n"
	"\t				iter!=question_list[i]->input_data.end(); ++iter){\n"
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
	fprintf(script, "\tvector<int> arrayBounds;\n");
	fprintf(script, "\tArrayQuestion(vector<int>& l_arrayBounds): arrayBounds(l_arrayBounds)\n");
	fprintf(script, "\t{\n");
	fprintf(script, "\t\tint bounds = 1;\n");
	fprintf(script, "\t\tfor(int i=0; i<arrayBounds.size(); ++i){\n");
	fprintf(script, "\t\t\tbounds*=arrayBounds[i];\n");
	fprintf(script, "\t\t}\n");
	fprintf(script, "\t\tquestionList.reserve(bounds);\n");
	fprintf(script, "\t}\n");
	fprintf(script, "};\n\n");

}

void PrintActiveVariablesAtScope( vector <Scope*> & active_scope_list,
		vector <ActiveVariableInfo*> & output_info)
{
	for(unsigned int i=0; i< active_scope_list.size(); ++i){
		Scope* sc_ptr= active_scope_list[i];
		sc_ptr->print_scope(output_info);
		//sc_ptr->print_scope(name, active_push_vars, active_pop_vars);
	}
}

void PrintSignalHandler(FILE * script)
{
	fprintf(script, "static void sig_usr(int signo)\n");
	fprintf(script, "{\n");
	fprintf(script, "	if(signo==SIGSEGV){\n");
	fprintf(script, "		printf(\"received SIGSEGV\\n\");\n");
	fprintf(script, "	} else if (signo==SIGILL){\n");
	fprintf(script, "		printf(\"received SIGILL\\n\");\n");
	fprintf(script, "	} else {\n");
	fprintf(script, "		fprintf(stderr, \"received signal : %%d\\n\", signo);\n");
	fprintf(script, "	}\n");
	fprintf(script, "	fflush(qscript_stdout);\n");
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
int ReadQScriptConfig()
{
	//cerr << "Enter qscript_parser::ReadQScriptConfig" << endl;
	using namespace std;
	string QSCRIPT_HOME = getenv("QSCRIPT_HOME");
	string QSCRIPT_CONFIG = QSCRIPT_HOME + "/config/qscript.config";
	FILE * qscript_confin = fopen (QSCRIPT_CONFIG.c_str(), "rb");
	qscript_confrestart(qscript_confin);
	if(!qscript_confin){
		//cout << "unable to open " <<  QSCRIPT_CONFIG <<" for reading ... exiting\n";
		return 0;
	}
	//cerr << "opened : " << QSCRIPT_CONFIG << endl;
	
	if(!qscript_confparse()){
		//cout << "Successfully parsed " << QSCRIPT_CONFIG << endl;
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
	return 1;
}

void CompileGeneratedCode(const string & src_file_name )
{
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
	cout << "executable_file_name: " << executable_file_name << endl;
	string intermediate_file_name = executable_file_name + ".C";
	executable_file_name += ".exe";
	string QSCRIPT_HOME = getenv("QSCRIPT_HOME");
	cout << "QSCRIPT_HOME: " << QSCRIPT_HOME << endl;
	string QSCRIPT_RUNTIME = QSCRIPT_HOME + "/lib";
	cout << "QSCRIPT_RUNTIME: " << QSCRIPT_RUNTIME << endl;
		
	string QSCRIPT_INCLUDE_DIR = QSCRIPT_HOME + "/include";
	string cpp_compile_command = string ("g++ -g -o ")  
				+ executable_file_name +  string(" -L") + QSCRIPT_RUNTIME
					+ string(" -I") + QSCRIPT_INCLUDE_DIR
					+ string(" ") + intermediate_file_name
					+ string(" -lqscript_runtime -lncurses ");
	cout << "cpp_compile_command: " << cpp_compile_command << endl;
	//int ret_val=0;
	int ret_val = system(cpp_compile_command.c_str());
	if(ret_val!=0){
		cerr << "Failed in compiling generated code : test_script.C ";
	} else {
		cout << "Generated executable. You can run it by\n shell_prompt> LD_LIBRARY_PATH=$QSCRIPT_HOME/lib ./"
			 <<  executable_file_name
			<< endl;
	}
}

void CompileGeneratedCodeStatic(const string & src_file_name )
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
	cout << "executable_file_name: " << executable_file_name << endl;
	string intermediate_file_name = executable_file_name + ".C";
	executable_file_name += ".exe";
	string QSCRIPT_HOME = getenv("QSCRIPT_HOME");
	cout << "QSCRIPT_HOME: " << QSCRIPT_HOME << endl;
	string QSCRIPT_RUNTIME = QSCRIPT_HOME + "/lib";
	cout << "QSCRIPT_RUNTIME: " << QSCRIPT_RUNTIME << endl;
	string QSCRIPT_CURSES_INCLUDE_DIR = "c:/usr/include ";
	cout << "QSCRIPT_CURSES_INCLUDE_DIR: " << QSCRIPT_CURSES_INCLUDE_DIR << endl;
	string QSCRIPT_CURSES_LIB_DIR = "c:/usr/lib ";
	cout << "QSCRIPT_CURSES_LIB_DIR: " << QSCRIPT_CURSES_LIB_DIR << endl;
		
	string QSCRIPT_INCLUDE_DIR = QSCRIPT_HOME + "/include";
	string cpp_compile_command = string ("c:\\MinGW\\bin\\g++ -static -g -o ")  
				+ executable_file_name 
				+ string(" -L") + QSCRIPT_RUNTIME
				+ string(" -L") + QSCRIPT_CURSES_LIB_DIR
				+ string(" -I") + QSCRIPT_INCLUDE_DIR
				+ string(" -I") + QSCRIPT_CURSES_INCLUDE_DIR
				+ string(" ") + intermediate_file_name
				+ string(" -lqscript_runtime -lpdcurses ");
	cout << "cpp_compile_command: " << cpp_compile_command << endl;
	//int ret_val=0;
	int ret_val = system(cpp_compile_command.c_str());
	if(ret_val!=0){
		cerr << "Failed in compiling generated code : test_script.C ";
	} else {
		cout << "Generated executable. You can run it by\n shell_prompt> LD_LIBRARY_PATH=$QSCRIPT_HOME/lib ./"
			 <<  executable_file_name
			<< endl;
	}
}



/* end of namespace */
}
