#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <errno.h>
#include <curses.h>
#include <panel.h>
#include <signal.h>
#include <dirent.h>
#include <cctype>
#include <unistd.h>
#include "stub_pair.h"
#include "AbstractStatement.h"
#include "named_range.h"
#include "xtcc_set.h"
#include "datatype.h"
#include "qscript_lib.h"
#include "question_disk_data.h"
#include "question.h"
#include "user_navigation.h"
#include "qtm_data_file.h"
#include "qtm_datafile_conf_parser.h"
#include "ArrayQuestion.h"
#include "AsciiFlatFileQuestionDiskMap.h"
#include "XtccDataFile.h"
#include "base_text.h"
#include "QuestionAttributes.h"
int ser_no = 0;
using namespace std;
string qscript_stdout_fname("qscript_stdout.log");
FILE * qscript_stdout = 0;
#include "debug_mem.h"
fstream debug_log_file("qscript_debug.log", ios_base::out|ios_base::trunc);
fstream flat_file;
fstream xtcc_datafile;
fstream qtm_disk_file;
extern set<string> qtm_include_files;
using namespace std;
void read_data(const char * prompt);
//extern vector<int32_t> data;
namespace program_options_ns { bool flag_nice_map = true; }
extern UserNavigation user_navigation;
vector <AbstractQuestion*> question_list;
vector<mem_addr_tab>  mem_addr;
extern vector<question_disk_data*>  qdd_list;
void merge_disk_data_into_questions(FILE * qscript_stdout,
		AbstractQuestion * & p_last_question_answered,
		AbstractQuestion * & p_last_question_visited);
void merge_disk_data_into_questions2(FILE * qscript_stdout, AbstractQuestion * & p_last_question_answered, AbstractQuestion * & p_last_question_visited);
bool stopAtNextQuestion;
string jumpToQuestion;
int32_t jumpToIndex;
bool write_data_file_flag;
bool write_qtm_data_file_flag;
bool write_xtcc_data_file_flag;
bool card_start_flag;
bool card_end_flag;
int card_start;
int card_end;
int32_t check_if_reg_file_exists(string jno, int32_t ser_no);
void print_map_header(fstream & map_file);
map<string, vector<string> > map_of_active_vars_for_questions;
map<string, map<int, int> > freq_count;
bool back_jump = false;// no need for this but state the intent
void write_data_to_disk(const vector<AbstractQuestion*>& q_vec, string jno, int32_t ser_no);
AbstractQuestion * ComputePreviousQuestion(AbstractQuestion * q);
WINDOW *create_newwin(int32_t height, int32_t width, int32_t starty, int32_t startx);
void SetupNCurses(WINDOW * &  question_window,
			WINDOW * &  stub_list_window,
			WINDOW * & data_entry_window,
			WINDOW * & error_msg_window,
			WINDOW * & help_window,
			PANEL * &  question_panel,
			PANEL * &  stub_list_panel,
			PANEL * & data_entry_panel,
			PANEL * & error_msg_panel,
			PANEL * & help_panel);
void define_some_pd_curses_keys();
void SetupSignalHandler();
static void sig_usr(int32_t signo);
int32_t ComputeJumpToIndex(AbstractQuestion * q);
void reset_questionnaire();
void DisplayActiveQuestions();
string output_data_file_name;
string output_qtm_data_file_name;
string output_xtcc_data_file_name;
void GetUserResponse(string& qno, int32_t &qindex);
string jno = "test_fix_and_recode";
char * flat_file_output_buffer = 0;
char * xtcc_datafile_output_buffer = 0;
int32_t len_flat_file_output_buffer  = 0;
int32_t len_xtcc_datafile_output_buffer  = 0;
vector <AsciiFlatFileQuestionDiskMap*> ascii_flatfile_question_disk_map;
vector <XtccDataFileDiskMap*> xtcc_question_disk_map;
vector <qtm_data_file_ns::QtmDataDiskMap*> qtm_datafile_question_disk_map;
qtm_data_file_ns::QtmDataFile qtm_data_file;
void Compute_FlatFileQuestionDiskDataMap(vector<AbstractQuestion*> p_question_list);

qtm_data_file_ns::QtmDataDiskMap* GetQuestionMapEntry(vector <qtm_data_file_ns::QtmDataDiskMap*> & qtm_datafile_question_disk_map,
			string name);

int process_options(int argc, char * argv[]);
	WINDOW 	* question_window = 0,
		* stub_list_window = 0,
		* data_entry_window = 0,
		* error_msg_window = 0,
		* help_window = 0;
	PANEL 	* question_panel = 0,
		* stub_list_panel = 0,
		* data_entry_panel = 0,
		* error_msg_panel = 0,
		* help_panel = 0;
	DIR * directory_ptr = 0;
AbstractQuestion * last_question_answered = 0;
AbstractQuestion * last_question_visited = 0;
struct TheQuestionnaire
{
int32_t questions_start_from_here_index;
int ser_no_pos;
vector <BaseText> base_text_vec;
//CompoundStatement::GenerateCode()
// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 8, flagIsAForBody_: 0, source lineNo_: 1
vector <stub_pair> qscript_temp_25;

named_range brand_list;
NamedStubQuestion * q1;
NamedStubQuestion * q2;
XtccSet xs_0;
RangeQuestion * q3;
XtccSet xs_1;
RangeQuestion * q4;
//CompoundStatement::GenerateCode()
// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 1, flagIsAForBody_: 1, source lineNo_: 34
vector<int32_t> list_q5_array_bounds;
ArrayQuestion q5_list;
DummyArrayQuestion* dum_q5;
XtccSet xs_2;
//CompoundStatement::GenerateCode()
// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 1, flagIsAForBody_: 1, source lineNo_: 41
vector<int32_t> list_q6_array_bounds;
ArrayQuestion q6_list;
DummyArrayQuestion* dum_q6;
XtccSet xs_3;
XtccSet xs_4;
RangeQuestion * q7;
XtccSet xs_5;
RangeQuestion * q8;

TheQuestionnaire() 
: list_q5_array_bounds(1),list_q6_array_bounds(1)
{
qscript_temp_25.push_back( stub_pair("brand 1", 1));
qscript_temp_25.push_back( stub_pair("brand 2", 2));
qscript_temp_25.push_back( stub_pair("brand 3", 3));
qscript_temp_25.push_back( stub_pair("brand 4", 4));
qscript_temp_25.push_back( stub_pair("brand 5", 5));
qscript_temp_25.push_back( stub_pair("brand 6", 6));
qscript_temp_25.push_back( stub_pair("brand 7", 7));
qscript_temp_25.push_back( stub_pair("brand 8", 8));
qscript_temp_25.push_back( stub_pair("brand 9", 9));
qscript_temp_25.push_back( stub_pair("brand 10", 10));
qscript_temp_25.push_back( stub_pair("brand 11", 11));
brand_list.set_range_data("brand_list", qscript_temp_25);
q1 = new NamedStubQuestion(QUESTION_TYPE, 19,string( "q1"),string(" Primary Brand"),spn,1,INT32_TYPE,&brand_list, QuestionAttributes(false , false), true);
q2 = new NamedStubQuestion(QUESTION_TYPE, 24,string( "q2"),string(" Secondary Brand"),spn,1,INT32_TYPE,&brand_list, QuestionAttributes(false , false), false);
xs_0.range.push_back(pair<int32_t,int32_t>(1,5));
q3 = new RangeQuestion(QUESTION_TYPE, 27,string( "q3"),string(" Rate your primary brand"),spn,1,INT32_TYPE,xs_0, QuestionAttributes(false , false), false);
xs_1.range.push_back(pair<int32_t,int32_t>(1,5));
q4 = new RangeQuestion(QUESTION_TYPE, 30,string( "q4"),string(" Rate your Secondary brand"),spn,1,INT32_TYPE,xs_1, QuestionAttributes(false , false), false);
list_q5_array_bounds[0] = 10;
q5_list.SetArrayBounds(list_q5_array_bounds);
dum_q5= new DummyArrayQuestion("q5",list_q5_array_bounds);
question_list.push_back( dum_q5);
xs_2.range.push_back(pair<int32_t,int32_t>(1,5));
list_q6_array_bounds[0] = 10;
q6_list.SetArrayBounds(list_q6_array_bounds);
dum_q6= new DummyArrayQuestion("q6",list_q6_array_bounds);
question_list.push_back( dum_q6);
xs_3.range.push_back(pair<int32_t,int32_t>(1,5));
xs_4.range.push_back(pair<int32_t,int32_t>(1,5));
q7 = new RangeQuestion(QUESTION_TYPE, 49,string( "q7"),string(" Recommend your primary brand"),spn,1,INT32_TYPE,xs_4, QuestionAttributes(false , false), true);
xs_5.range.push_back(pair<int32_t,int32_t>(1,5));
q8 = new RangeQuestion(QUESTION_TYPE, 52,string( "q8"),string(" Recommend your Secondary brand"),spn,1,INT32_TYPE,xs_5, QuestionAttributes(false , false), false);

questions_start_from_here_index = question_list.size();
question_list.push_back(q1);
question_list.push_back(q2);
question_list.push_back(q3);
question_list.push_back(q4);
for (int32_t i1 = 0;i1<10; ++i1) {
vector<int32_t> stack_of_loop_indices;
stack_of_loop_indices.push_back(i1);
RangeQuestion * q5 = new RangeQuestion(QUESTION_ARR_TYPE, 37,string( "q5"),string(" Attribute battery: Primary brand"),spn,1,INT32_TYPE,xs_2, stack_of_loop_indices , dum_q5, QuestionAttributes(false , false), true);
question_list.push_back(q5);
q5_list.questionList.push_back(q5);
	stack_of_loop_indices.pop_back();
}
for (int32_t i1 = 0;i1<10; ++i1) {
vector<int32_t> stack_of_loop_indices;
stack_of_loop_indices.push_back(i1);
RangeQuestion * q6 = new RangeQuestion(QUESTION_ARR_TYPE, 44,string( "q6"),string(" Attribute battery: Secondary brand"),spn,1,INT32_TYPE,xs_3, stack_of_loop_indices , dum_q6, QuestionAttributes(false , false), true);
question_list.push_back(q6);
q6_list.questionList.push_back(q6);
	stack_of_loop_indices.pop_back();
}
question_list.push_back(q7);
question_list.push_back(q8);

}

void print_summary_axis (vector<qtm_data_file_ns::QtmDataDiskMap*> & v, fstream & qtm_qax_file) 
{
	AbstractQuestion * q = v[0]->q;
	if (q->q_type == spn) {
		int n_digits = 0;
		int rat_scale = 0;
		if (NamedStubQuestion * n_q = dynamic_cast<NamedStubQuestion*>(q)) {
			if (n_q->nr_ptr) {
				string & stub_name = n_q->nr_ptr->name;
				int multiplier = 1;
				for (int i=stub_name.length()-1; i>0; --i) {
					if ( isdigit(stub_name[i]) ) {
						int c = stub_name[i] - '0';
						++n_digits;
						rat_scale = rat_scale + c * multiplier;
						multiplier *= 10;
					} else {
						break;
					}
				}
			}
		}
		if (n_digits > 0) {
			string include_file_name;
			string mean_score_include_file;
			if (v[0]->width_ == 1) {
				include_file_name = "rat1c.qin";
				mean_score_include_file = "mn1c.qin";
			} else if (v[0]->width_ == 2) {
				include_file_name = "rat2c.qin";
				mean_score_include_file = "mn2c.qin";
			} else if (v[0]->width_ == 3) {
				include_file_name = "rat3c.qin";
				mean_score_include_file = "mn3c.qin";
			} else {
				include_file_name = "unhandled width syntax error";
				mean_score_include_file = "unhandled width syntax error";
			}

			if (rat_scale == 5) {

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_top" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 5 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_top2" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 5 << ", " << 4 << ")"
						<< endl;
				}


				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_bot" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 1 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_bot2" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 1 << ", " << 2 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_mn" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << mean_score_include_file
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 1 << ":" << 5 << ")"
						<< endl;
				}

			}
			else if (rat_scale == 7) {

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_top" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 7 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_top2" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 7 << ", " << 6 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_top3" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 5 << ":" << 7 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_bot" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 1 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_bot2" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 1 << ", " << 2 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_mn" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << mean_score_include_file
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 1 << ":" << 7 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_bot3" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 1 << ":" << 3 << ")"
						<< endl;
				}

			}
			else if (rat_scale == 10) {

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_top" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 10 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_top2" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 10 << ", " << 9 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_top3" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 8 << ":" << 10 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_bot" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 1 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_bot2" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 1 << ", " << 2 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_mn" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << mean_score_include_file
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 1 << ":" << 10 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_bot3" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i) {
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 
						<< ";myrange=(" << 1 << ":" << 3 << ")"
						<< endl;
				}

			}
		} else {
			qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
			qtm_qax_file << "/*l " << q->questionName_ << "_sum" << endl;
			qtm_qax_file << "/*ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
			for (int i=0; i<v.size(); ++i) {
				qtm_qax_file << "/**include summ.qin;qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 << endl;
			}
		}
	}
	cout << endl;
}
void compute_flat_file_map_and_init()
{
if (write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)
{
	int current_map_pos = 0;
	int current_xtcc_map_pos = 0;
	if (write_qtm_data_file_flag) {
		qtm_datafile_conf_parser_ns::load_config_file(jno);
		qtm_data_file.Initialize();
	}
	if (write_data_file_flag) {
		stringstream asc_datafile_conf_str;
		asc_datafile_conf_str << jno 
			<< ".asc_data.conf";
		fstream asc_datafile_conf(asc_datafile_conf_str.str().c_str(), ios_base::in);
		if (!asc_datafile_conf) {
			cerr << " could not open : " << asc_datafile_conf_str.str() 
				<< " for reading" << endl;
			exit(1);
		}
		string ser_no_token; string equal_token; ser_no_pos=-1; string semi_colon_token;
		asc_datafile_conf >> ser_no_token;
		if ( ser_no_token != string("SER_NO_COLS")) {
			cerr << "expected token SER_NO_COLS" << endl;
			exit(1);
		}
		asc_datafile_conf >> equal_token;
		if (equal_token != string("=") ) {
			cerr << "expected token =" << endl;
			exit(1);
		}
		asc_datafile_conf >> ser_no_pos;
		if (ser_no_pos == -1) {
			cerr << "invalid no of positions reserved for serial no: ";
			exit(1);
		}
		current_map_pos += ser_no_pos;
	}
	if (write_xtcc_data_file_flag) {
		current_xtcc_map_pos += 4; // serial no is 4 bytes fixed
	}
{
	AsciiFlatFileQuestionDiskMap * qscript_temp_1 = new AsciiFlatFileQuestionDiskMap(q1, current_map_pos);
	current_map_pos += qscript_temp_1->GetTotalLength();
	ascii_flatfile_question_disk_map.push_back(qscript_temp_1);
	if (write_xtcc_data_file_flag) {
	 XtccDataFileDiskMap * qscript_temp_2 = new XtccDataFileDiskMap(q1, current_xtcc_map_pos);
	 current_xtcc_map_pos += qscript_temp_2->GetTotalLength();
	 xtcc_question_disk_map.push_back(qscript_temp_2);
	}
	if (write_qtm_data_file_flag) {
		qtm_data_file_ns::QtmDataDiskMap * qscript_temp_3 = new qtm_data_file_ns::QtmDataDiskMap(q1, qtm_data_file, base_text_vec.back());
	 qtm_datafile_question_disk_map.push_back(qscript_temp_3);
	}
	AsciiFlatFileQuestionDiskMap * qscript_temp_4 = new AsciiFlatFileQuestionDiskMap(q2, current_map_pos);
	current_map_pos += qscript_temp_4->GetTotalLength();
	ascii_flatfile_question_disk_map.push_back(qscript_temp_4);
	if (write_xtcc_data_file_flag) {
	 XtccDataFileDiskMap * qscript_temp_5 = new XtccDataFileDiskMap(q2, current_xtcc_map_pos);
	 current_xtcc_map_pos += qscript_temp_5->GetTotalLength();
	 xtcc_question_disk_map.push_back(qscript_temp_5);
	}
	if (write_qtm_data_file_flag) {
		qtm_data_file_ns::QtmDataDiskMap * qscript_temp_6 = new qtm_data_file_ns::QtmDataDiskMap(q2, qtm_data_file, base_text_vec.back());
	 qtm_datafile_question_disk_map.push_back(qscript_temp_6);
	}
	AsciiFlatFileQuestionDiskMap * qscript_temp_7 = new AsciiFlatFileQuestionDiskMap(q3, current_map_pos);
	current_map_pos += qscript_temp_7->GetTotalLength();
	ascii_flatfile_question_disk_map.push_back(qscript_temp_7);
	if (write_xtcc_data_file_flag) {
	 XtccDataFileDiskMap * qscript_temp_8 = new XtccDataFileDiskMap(q3, current_xtcc_map_pos);
	 current_xtcc_map_pos += qscript_temp_8->GetTotalLength();
	 xtcc_question_disk_map.push_back(qscript_temp_8);
	}
	if (write_qtm_data_file_flag) {
		qtm_data_file_ns::QtmDataDiskMap * qscript_temp_9 = new qtm_data_file_ns::QtmDataDiskMap(q3, qtm_data_file, base_text_vec.back());
	 qtm_datafile_question_disk_map.push_back(qscript_temp_9);
	}
	AsciiFlatFileQuestionDiskMap * qscript_temp_10 = new AsciiFlatFileQuestionDiskMap(q4, current_map_pos);
	current_map_pos += qscript_temp_10->GetTotalLength();
	ascii_flatfile_question_disk_map.push_back(qscript_temp_10);
	if (write_xtcc_data_file_flag) {
	 XtccDataFileDiskMap * qscript_temp_11 = new XtccDataFileDiskMap(q4, current_xtcc_map_pos);
	 current_xtcc_map_pos += qscript_temp_11->GetTotalLength();
	 xtcc_question_disk_map.push_back(qscript_temp_11);
	}
	if (write_qtm_data_file_flag) {
		qtm_data_file_ns::QtmDataDiskMap * qscript_temp_12 = new qtm_data_file_ns::QtmDataDiskMap(q4, qtm_data_file, base_text_vec.back());
	 qtm_datafile_question_disk_map.push_back(qscript_temp_12);
	}
for (int32_t i1 = 0;i1<10; ++i1) {
vector<int32_t> stack_of_loop_indices;
stack_of_loop_indices.push_back(i1);
{
int32_t consolidated_for_loop_index_1 = i1;
	AsciiFlatFileQuestionDiskMap * qscript_temp_13 = new AsciiFlatFileQuestionDiskMap(q5_list.questionList[i1], current_map_pos);
	current_map_pos += qscript_temp_13->GetTotalLength();
	ascii_flatfile_question_disk_map.push_back(qscript_temp_13);
	if (write_xtcc_data_file_flag) {
	 XtccDataFileDiskMap * qscript_temp_14 = new XtccDataFileDiskMap(q5_list.questionList[i1], current_xtcc_map_pos);
	 current_xtcc_map_pos += qscript_temp_14->GetTotalLength();
	 xtcc_question_disk_map.push_back(qscript_temp_14);
	}
	if (write_qtm_data_file_flag) {
	qtm_data_file_ns::QtmDataDiskMap * qscript_temp_15 = new qtm_data_file_ns::QtmDataDiskMap(q5_list.questionList[i1], qtm_data_file, base_text_vec.back());
	 qtm_datafile_question_disk_map.push_back(qscript_temp_15);
	}
}
	stack_of_loop_indices.pop_back();
}
for (int32_t i1 = 0;i1<10; ++i1) {
vector<int32_t> stack_of_loop_indices;
stack_of_loop_indices.push_back(i1);
{
int32_t consolidated_for_loop_index_2 = i1;
	AsciiFlatFileQuestionDiskMap * qscript_temp_16 = new AsciiFlatFileQuestionDiskMap(q6_list.questionList[i1], current_map_pos);
	current_map_pos += qscript_temp_16->GetTotalLength();
	ascii_flatfile_question_disk_map.push_back(qscript_temp_16);
	if (write_xtcc_data_file_flag) {
	 XtccDataFileDiskMap * qscript_temp_17 = new XtccDataFileDiskMap(q6_list.questionList[i1], current_xtcc_map_pos);
	 current_xtcc_map_pos += qscript_temp_17->GetTotalLength();
	 xtcc_question_disk_map.push_back(qscript_temp_17);
	}
	if (write_qtm_data_file_flag) {
	qtm_data_file_ns::QtmDataDiskMap * qscript_temp_18 = new qtm_data_file_ns::QtmDataDiskMap(q6_list.questionList[i1], qtm_data_file, base_text_vec.back());
	 qtm_datafile_question_disk_map.push_back(qscript_temp_18);
	}
}
	stack_of_loop_indices.pop_back();
}
	AsciiFlatFileQuestionDiskMap * qscript_temp_19 = new AsciiFlatFileQuestionDiskMap(q7, current_map_pos);
	current_map_pos += qscript_temp_19->GetTotalLength();
	ascii_flatfile_question_disk_map.push_back(qscript_temp_19);
	if (write_xtcc_data_file_flag) {
	 XtccDataFileDiskMap * qscript_temp_20 = new XtccDataFileDiskMap(q7, current_xtcc_map_pos);
	 current_xtcc_map_pos += qscript_temp_20->GetTotalLength();
	 xtcc_question_disk_map.push_back(qscript_temp_20);
	}
	if (write_qtm_data_file_flag) {
		qtm_data_file_ns::QtmDataDiskMap * qscript_temp_21 = new qtm_data_file_ns::QtmDataDiskMap(q7, qtm_data_file, base_text_vec.back());
	 qtm_datafile_question_disk_map.push_back(qscript_temp_21);
	}
	AsciiFlatFileQuestionDiskMap * qscript_temp_22 = new AsciiFlatFileQuestionDiskMap(q8, current_map_pos);
	current_map_pos += qscript_temp_22->GetTotalLength();
	ascii_flatfile_question_disk_map.push_back(qscript_temp_22);
	if (write_xtcc_data_file_flag) {
	 XtccDataFileDiskMap * qscript_temp_23 = new XtccDataFileDiskMap(q8, current_xtcc_map_pos);
	 current_xtcc_map_pos += qscript_temp_23->GetTotalLength();
	 xtcc_question_disk_map.push_back(qscript_temp_23);
	}
	if (write_qtm_data_file_flag) {
		qtm_data_file_ns::QtmDataDiskMap * qscript_temp_24 = new qtm_data_file_ns::QtmDataDiskMap(q8, qtm_data_file, base_text_vec.back());
	 qtm_datafile_question_disk_map.push_back(qscript_temp_24);
	}
}
	string map_file_name(jno + string(".map"));
	fstream map_file(map_file_name.c_str(), ios_base::out|ios_base::ate);
	 print_map_header(map_file);
	for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {
		ascii_flatfile_question_disk_map[i]->print_map(map_file);
	}
	string spss_syn_file_name(jno + string("-flat-ascii.sps"));
	fstream spss_syn_file(spss_syn_file_name.c_str(), ios_base::out|ios_base::ate);
	 spss_syn_file << "DATA LIST FILE='" <<  jno << ".dat'\n"<< endl << "/RESPID			1-6\n";
	for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {
		ascii_flatfile_question_disk_map[i]->write_spss_pull_data(spss_syn_file);
	}
	 spss_syn_file << ".\n";

 spss_syn_file << "exe.\n";
	for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {
		ascii_flatfile_question_disk_map[i]->write_spss_variable_labels(spss_syn_file);
	}

 spss_syn_file << "exe.\n";
	for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {
		ascii_flatfile_question_disk_map[i]->write_spss_value_labels(spss_syn_file);
	}

 spss_syn_file << "exe.\n";

 spss_syn_file << "save outfile=\"" << jno << ".sav\"\n";
	string xtcc_map_file_name(jno + string(".xmap"));
	fstream xtcc_map_file(xtcc_map_file_name.c_str(), ios_base::out|ios_base::ate);
	print_map_header(xtcc_map_file);
	for (int i=0; i<xtcc_question_disk_map.size(); ++i) {
		xtcc_question_disk_map[i]->print_map(xtcc_map_file);
	}
	len_flat_file_output_buffer = current_map_pos+1;
	len_xtcc_datafile_output_buffer = current_xtcc_map_pos+1;
	flat_file_output_buffer = new char[len_flat_file_output_buffer];
	xtcc_datafile_output_buffer = new char[len_xtcc_datafile_output_buffer];
	memset(flat_file_output_buffer, ' ', len_flat_file_output_buffer-1);
	memset(xtcc_datafile_output_buffer, '\0', len_xtcc_datafile_output_buffer-1);
	flat_file_output_buffer[len_flat_file_output_buffer-1] = 0;
	xtcc_datafile_output_buffer[len_xtcc_datafile_output_buffer-1] = 0;
	string flat_file_name(jno + string(".dat"));
	flat_file.open(flat_file_name.c_str(), ios_base::out | ios_base::trunc);
	string xtcc_datafile_name(jno + string(".xdat"));
	xtcc_datafile.open(xtcc_datafile_name.c_str(), ios_base::out | ios_base::trunc | ios_base::binary);
		{struct stat dir_exists; stringstream s1;
			s1 << "setup-" << jno;
			if (stat(s1.str().c_str(), &dir_exists) <0) {
				if (errno == ENOENT)
					if (mkdir(s1.str().c_str()) <0) {
						perror("unable to create directory for setup files");
					} else
						perror("stating directory failed");
			}
		}
	if (write_qtm_data_file_flag) {
		string qtm_map_file_name(string("setup-") + jno + string("/") + jno + string(".qmap"));
		fstream qtm_map_file(qtm_map_file_name.c_str(), ios_base::out|ios_base::ate);
		print_map_header(qtm_map_file);
		for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {
			qtm_datafile_question_disk_map[i]->print_map(qtm_map_file);
		}
		string variable_defns_fname (string("variable"));
		fstream variable_file (variable_defns_fname.c_str(), ios_base::out|ios_base::ate);
		string edit_file_name (string("edit.qin"));
		fstream edit_file (edit_file_name.c_str(), ios_base::out|ios_base::ate);

		// if (q1_map_entry) {
		// 	edit_file << " found q1 in map, startPosition_"
		// 		<< q1_map_entry->startPosition_ + 1
		// 		<< endl;
		// }
		for (int i=0; i < q1->nr_ptr->stubs.size(); ++i) {
			variable_file << "q3" << "_" << q1->nr_ptr->stubs[i].stub_text << endl;
			qtm_data_file_ns::QtmDataDiskMap * q1_map_entry =
				GetQuestionMapEntry (qtm_datafile_question_disk_map, q1->questionName_);
			qtm_data_file_ns::QtmDataDiskMap * q3_map_entry =
				GetQuestionMapEntry (qtm_datafile_question_disk_map, q3->questionName_);
			if (q1_map_entry && q3_map_entry) {
				edit_file << "/* " << q1->questionName_ 
					<< " column: c(" << q1_map_entry->startPosition_ + 1
					<< ", " << q1_map_entry->startPosition_ + q1_map_entry->totalLength_
					<< ")"
					<< endl;
				edit_file << "	if ( "
					<< "c(" 
					<< q1_map_entry->startPosition_ + 1
					<< ", "
					<< q1_map_entry->startPosition_ + q1_map_entry->totalLength_ << ")"
					<< " .eq. " << q1->nr_ptr->stubs[i].code
					<< ")\n"
					<< "++\t" <<  "q3_"
					<< q1->nr_ptr->stubs[i].stub_text 
					<< "="
					<< "c(" 
					<< q3_map_entry->startPosition_ + 1
					<< ", "
					<< q3_map_entry->startPosition_ + q3_map_entry->totalLength_ << ")"
					<< endl;
			} else {
			}
		}
		for (int i=0; i < q2->nr_ptr->stubs.size(); ++i) {
			 variable_file << "q4" << "_" << q2->nr_ptr->stubs[i].stub_text << endl;
			 edit_file << "	if (" << q2->questionName_ << " .eq. " << q2->nr_ptr->stubs[i].code << ")\n"
			 << "++\t" <<  "q4=q4"
			<< endl;
		}
		for (int i=0; i < q1->nr_ptr->stubs.size(); ++i) {
			 variable_file << "q6" << "_" << q1->nr_ptr->stubs[i].stub_text << endl;
			 edit_file << "	if (" << q1->questionName_ << " .eq. " << q1->nr_ptr->stubs[i].code << ")\n"
			 << "++\t" <<  "q6=q6"
			<< endl;
		}
		for (int i=0; i < q2->nr_ptr->stubs.size(); ++i) {
			 variable_file << "q7" << "_" << q2->nr_ptr->stubs[i].stub_text << endl;
			 edit_file << "	if (" << q2->questionName_ << " .eq. " << q2->nr_ptr->stubs[i].code << ")\n"
			 << "++\t" <<  "q7=q7"
			<< endl;
		}
		string qtm_qax_file_name( string("setup-")+jno+string("/") + jno + string(".qax"));
		fstream qtm_qax_file(qtm_qax_file_name.c_str(), ios_base::out|ios_base::ate);
		map <string, vector<qtm_data_file_ns::QtmDataDiskMap*> > summary_tables;
		for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {
			qtm_datafile_question_disk_map[i]->print_qax(qtm_qax_file, string("setup-")+jno);
			string questionName = qtm_datafile_question_disk_map[i]->q->questionName_;
			if (qtm_datafile_question_disk_map[i]->q->loop_index_values.size() > 0) {
				summary_tables[questionName].push_back(qtm_datafile_question_disk_map[i]);
			}
		}
		for ( map <string, vector<qtm_data_file_ns::QtmDataDiskMap*> >::iterator it= summary_tables.begin();
				it != summary_tables.end(); ++it) {
			print_summary_axis(it->second, qtm_qax_file);
		}
		qtm_datafile_question_disk_map[0]->print_run(jno);
		string tab_file_name(string("setup-")+ jno + string("/") + jno + string(".tab"));
		fstream tab_file(tab_file_name.c_str(), ios_base::out|ios_base::ate);
		for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {
			string questionName = qtm_datafile_question_disk_map[i]->q->questionName_;
			AbstractQuestion * q = qtm_datafile_question_disk_map[i]->q;
			tab_file << "tab " << q->questionName_;
			for(int j=0; j<q->loop_index_values.size(); ++j) {
				tab_file << "_" << q->loop_index_values[j];
			}
			tab_file << " &ban" << endl;
		}
		qtm_datafile_question_disk_map[0]->qtmDataFile_.AllocateCards();
		qtm_datafile_question_disk_map[0]->qtmDataFile_.Reset();
		string qtm_disk_file_name(jno + string(".qdat"));
		qtm_disk_file.open(qtm_disk_file_name.c_str(), ios_base::out | ios_base::trunc);
	}
	if (write_xtcc_data_file_flag) {
		string xtcc_ax_file_name(string("setup-")+jno+string("/") + jno + string(".xtcc"));
		fstream xtcc_ax_file(xtcc_ax_file_name.c_str(), ios_base::out | ios_base::ate);
		xtcc_ax_file << "data_struct;rec_len=" << len_xtcc_datafile_output_buffer << ";\n";
		xtcc_ax_file << "ed_start\n";
		 xtcc_ax_file << "	int32_t edit_data();\n";
		 xtcc_ax_file << "	int32_t all;\n";
		 xtcc_ax_file << "	int32_t ser_no;\n";
		for (int i=0; i<xtcc_question_disk_map.size(); ++i) {
			xtcc_question_disk_map[i]->print_edit_var_defns(xtcc_ax_file, string("setup-")+jno+string("/"));
		}
		 xtcc_ax_file << "	int32_t edit_data()\n{\n";
		 xtcc_ax_file << "	all = 1;\n";
		 xtcc_ax_file << "	ser_no = c[0,3];\n";
		for (int i=0; i<xtcc_question_disk_map.size(); ++i) {
			xtcc_question_disk_map[i]->print_xtcc_edit_load(xtcc_ax_file, string("setup-")+jno+string("/"));
		}
		 xtcc_ax_file << "	}\n";
		xtcc_ax_file << "ed_end\n";
		xtcc_ax_file << "tabstart {\n";
		for (int i=0; i<xtcc_question_disk_map.size(); ++i) {
			xtcc_question_disk_map[i]->print_xtcc_tab(xtcc_ax_file, string("setup-")+jno+string("/"));
		}
		xtcc_ax_file << "}\n";
		xtcc_ax_file << "axstart {\n";
		xtcc_ax_file << "ax tot_ax;\n";
		xtcc_ax_file << "ttl; \"Total\";\n";
		xtcc_ax_file << "cnt; \"All\"; c= all==1;\n";
		for (int i=0; i<xtcc_question_disk_map.size(); ++i) {
			xtcc_question_disk_map[i]->print_xtcc_ax(xtcc_ax_file, string("setup-")+jno+string("/"));
		}
		xtcc_ax_file << "}\n";
	}
}
}

void eval()
{
	if (!(write_data_file_flag|| write_qtm_data_file_flag||write_xtcc_data_file_flag)) {
		int n_printed = mvwprintw(data_entry_window, 1, 1, "Enter Serial No (0) to exit: ");
		mvwscanw(data_entry_window, 1, 40, "%d", & ser_no);
	}
	while(ser_no != 0 || (write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)){
	if (write_data_file_flag||write_qtm_data_file_flag||write_xtcc_data_file_flag) {
		ser_no = read_a_serial_no();
		if (ser_no == 0) {
			break;
		} 
	} else {
		int exists = check_if_reg_file_exists(jno, ser_no);
		if(exists == 1){
			load_data(jno,ser_no);
			//merge_disk_data_into_questions(qscript_stdout, last_question_answered, last_question_visited);
			merge_disk_data_into_questions2(qscript_stdout, last_question_answered, last_question_visited);
		}
	}

	start_of_questions:
	if(back_jump == true){
	fprintf(qscript_stdout, "have reached start_of_questions with back_jump: jumpToQuestion: %s, jumpToIndex: %d\n", jumpToQuestion.c_str(), jumpToIndex);
	}
{
/* compound statement on line no: 1 questionsInBlock_, size:8 q1, q2, q3, q4, q5, q6, q7, q8,  */
/*StubManipStatement::GenerateCode() BEGIN :brand_list*/
{
for(int32_t qscript_temp_26 = 0; qscript_temp_26 < brand_list.stubs.size(); ++qscript_temp_26){
brand_list.stubs[qscript_temp_26].mask = true; 
}

}
/*StubManipStatement::GenerateCode() END :brand_list*/
/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
lab_q1:
if( back_jump == true  && q1->isAnswered_ == true ) {
if( jumpToQuestion == "q1")
{ back_jump = false;
}
}
/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
if ( (q1->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
(q1->isAnswered_ && !q1->VerifyQuestionIntegrity())||
stopAtNextQuestion ||
jumpToQuestion == "q1" || 
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q1->question_attributes.isAllowBlank()) && q1->isAnswered_ == false )) {
if(stopAtNextQuestion && q1->question_attributes.hidden_ == false ) {
	stopAtNextQuestion = false;  fprintf (qscript_stdout, " at question:  q1 disarming stopAtNextQuestion = false \n");

}
label_eval_q1:
		if ( q1->question_attributes.hidden_==false) {
		 stopAtNextQuestion = false;
q1->eval(question_window, stub_list_window, data_entry_window, error_msg_window);
	}
if(user_navigation == NAVIGATE_PREVIOUS){
		AbstractQuestion * target_question = ComputePreviousQuestion(q1);
		if(target_question == 0)
		goto label_eval_q1;
		else {
		jumpToQuestion = target_question->questionName_;
		if(target_question->type_ == QUESTION_ARR_TYPE){
			jumpToIndex = ComputeJumpToIndex(target_question);
		}
		if (data_entry_window==0) cout << "target question: " << jumpToQuestion;
		if (data_entry_window==0) cout << "target question Index: " << jumpToIndex;
		back_jump = true;
		user_navigation = NOT_SET;
		goto start_of_questions;
}
}
else if (user_navigation == NAVIGATE_NEXT){
	if (q1->isAnswered_==false && q1->question_attributes.isAllowBlank()==false ) {
		goto label_eval_q1;
	}
	stopAtNextQuestion = true;
		user_navigation = NOT_SET;
		}
else if (user_navigation == JUMP_TO_QUESTION){
		DisplayActiveQuestions();
		GetUserResponse(jumpToQuestion, jumpToIndex);
		user_navigation = NOT_SET;
		goto start_of_questions;
		}
else if (user_navigation == SAVE_DATA){
	write_data_to_disk(question_list, jno, ser_no);
		if (data_entry_window) mvwprintw(data_entry_window,2,50, "saved partial data");
 else 	cout << "saved partial data\n";
		if (q1->isAnswered_==false) {
			goto label_eval_q1;
		}
	} else { 
last_question_answered = q1;
}
}
/*StubManipStatement::GenerateCode() BEGIN q1:brand_list*/
{
set<int32_t>::iterator set_iter = q1->input_data.begin();
for( ; set_iter!= q1->input_data.end(); ++set_iter){
	for (int32_t qscript_temp_27 = 0; qscript_temp_27 < brand_list.stubs.size(); ++qscript_temp_27) {
		if (brand_list.stubs[qscript_temp_27].code == *set_iter) {
			brand_list.stubs[qscript_temp_27].mask = false; 
		}
	}
}

}
/*StubManipStatement::GenerateCode() END q1:brand_list*/
/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
lab_q2:
if( back_jump == true  && q2->isAnswered_ == true ) {
if( jumpToQuestion == "q2")
{ back_jump = false;
}
}
/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
if ( (q2->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
(q2->isAnswered_ && !q2->VerifyQuestionIntegrity())||
stopAtNextQuestion ||
jumpToQuestion == "q2" || 
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q2->question_attributes.isAllowBlank()) && q2->isAnswered_ == false )) {
if(stopAtNextQuestion && q2->question_attributes.hidden_ == false ) {
	stopAtNextQuestion = false;  fprintf (qscript_stdout, " at question:  q2 disarming stopAtNextQuestion = false \n");

}
label_eval_q2:
		if ( q2->question_attributes.hidden_==false) {
		 stopAtNextQuestion = false;
q2->eval(question_window, stub_list_window, data_entry_window, error_msg_window);
	}
if(user_navigation == NAVIGATE_PREVIOUS){
		AbstractQuestion * target_question = ComputePreviousQuestion(q2);
		if(target_question == 0)
		goto label_eval_q2;
		else {
		jumpToQuestion = target_question->questionName_;
		if(target_question->type_ == QUESTION_ARR_TYPE){
			jumpToIndex = ComputeJumpToIndex(target_question);
		}
		if (data_entry_window==0) cout << "target question: " << jumpToQuestion;
		if (data_entry_window==0) cout << "target question Index: " << jumpToIndex;
		back_jump = true;
		user_navigation = NOT_SET;
		goto start_of_questions;
}
}
else if (user_navigation == NAVIGATE_NEXT){
	if (q2->isAnswered_==false && q2->question_attributes.isAllowBlank()==false ) {
		goto label_eval_q2;
	}
	stopAtNextQuestion = true;
		user_navigation = NOT_SET;
		}
else if (user_navigation == JUMP_TO_QUESTION){
		DisplayActiveQuestions();
		GetUserResponse(jumpToQuestion, jumpToIndex);
		user_navigation = NOT_SET;
		goto start_of_questions;
		}
else if (user_navigation == SAVE_DATA){
	write_data_to_disk(question_list, jno, ser_no);
		if (data_entry_window) mvwprintw(data_entry_window,2,50, "saved partial data");
 else 	cout << "saved partial data\n";
		if (q2->isAnswered_==false) {
			goto label_eval_q2;
		}
	} else { 
last_question_answered = q2;
}
}
/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
lab_q3:
if( back_jump == true  && q3->isAnswered_ == true ) {
if( jumpToQuestion == "q3")
{ back_jump = false;
}
}
/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
if ( (q3->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
(q3->isAnswered_ && !q3->VerifyQuestionIntegrity())||
stopAtNextQuestion ||
jumpToQuestion == "q3" || 
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q3->question_attributes.isAllowBlank()) && q3->isAnswered_ == false )) {
if(stopAtNextQuestion && q3->question_attributes.hidden_ == false ) {
	stopAtNextQuestion = false;  fprintf (qscript_stdout, " at question:  q3 disarming stopAtNextQuestion = false \n");

}
label_eval_q3:
		if ( q3->question_attributes.hidden_==false) {
		 stopAtNextQuestion = false;
q3->eval(question_window, stub_list_window, data_entry_window, error_msg_window);
	}
if(user_navigation == NAVIGATE_PREVIOUS){
		AbstractQuestion * target_question = ComputePreviousQuestion(q3);
		if(target_question == 0)
		goto label_eval_q3;
		else {
		jumpToQuestion = target_question->questionName_;
		if(target_question->type_ == QUESTION_ARR_TYPE){
			jumpToIndex = ComputeJumpToIndex(target_question);
		}
		if (data_entry_window==0) cout << "target question: " << jumpToQuestion;
		if (data_entry_window==0) cout << "target question Index: " << jumpToIndex;
		back_jump = true;
		user_navigation = NOT_SET;
		goto start_of_questions;
}
}
else if (user_navigation == NAVIGATE_NEXT){
	if (q3->isAnswered_==false && q3->question_attributes.isAllowBlank()==false ) {
		goto label_eval_q3;
	}
	stopAtNextQuestion = true;
		user_navigation = NOT_SET;
		}
else if (user_navigation == JUMP_TO_QUESTION){
		DisplayActiveQuestions();
		GetUserResponse(jumpToQuestion, jumpToIndex);
		user_navigation = NOT_SET;
		goto start_of_questions;
		}
else if (user_navigation == SAVE_DATA){
	write_data_to_disk(question_list, jno, ser_no);
		if (data_entry_window) mvwprintw(data_entry_window,2,50, "saved partial data");
 else 	cout << "saved partial data\n";
		if (q3->isAnswered_==false) {
			goto label_eval_q3;
		}
	} else { 
last_question_answered = q3;
}
}
/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
lab_q4:
if( back_jump == true  && q4->isAnswered_ == true ) {
if( jumpToQuestion == "q4")
{ back_jump = false;
}
}
/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
if ( (q4->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
(q4->isAnswered_ && !q4->VerifyQuestionIntegrity())||
stopAtNextQuestion ||
jumpToQuestion == "q4" || 
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q4->question_attributes.isAllowBlank()) && q4->isAnswered_ == false )) {
if(stopAtNextQuestion && q4->question_attributes.hidden_ == false ) {
	stopAtNextQuestion = false;  fprintf (qscript_stdout, " at question:  q4 disarming stopAtNextQuestion = false \n");

}
label_eval_q4:
		if ( q4->question_attributes.hidden_==false) {
		 stopAtNextQuestion = false;
q4->eval(question_window, stub_list_window, data_entry_window, error_msg_window);
	}
if(user_navigation == NAVIGATE_PREVIOUS){
		AbstractQuestion * target_question = ComputePreviousQuestion(q4);
		if(target_question == 0)
		goto label_eval_q4;
		else {
		jumpToQuestion = target_question->questionName_;
		if(target_question->type_ == QUESTION_ARR_TYPE){
			jumpToIndex = ComputeJumpToIndex(target_question);
		}
		if (data_entry_window==0) cout << "target question: " << jumpToQuestion;
		if (data_entry_window==0) cout << "target question Index: " << jumpToIndex;
		back_jump = true;
		user_navigation = NOT_SET;
		goto start_of_questions;
}
}
else if (user_navigation == NAVIGATE_NEXT){
	if (q4->isAnswered_==false && q4->question_attributes.isAllowBlank()==false ) {
		goto label_eval_q4;
	}
	stopAtNextQuestion = true;
		user_navigation = NOT_SET;
		}
else if (user_navigation == JUMP_TO_QUESTION){
		DisplayActiveQuestions();
		GetUserResponse(jumpToQuestion, jumpToIndex);
		user_navigation = NOT_SET;
		goto start_of_questions;
		}
else if (user_navigation == SAVE_DATA){
	write_data_to_disk(question_list, jno, ser_no);
		if (data_entry_window) mvwprintw(data_entry_window,2,50, "saved partial data");
 else 	cout << "saved partial data\n";
		if (q4->isAnswered_==false) {
			goto label_eval_q4;
		}
	} else { 
last_question_answered = q4;
}
}
int32_t i1 = 0;
for (i1 = 0;i1<10;i1 = i1+1){
int32_t consolidated_for_loop_index_1 = i1;
/* compound statement on line no: 34 questionsInBlock_, size:1 q5,  */
/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():1 */
lab_q5:
if( back_jump == true  && q5_list.questionList[consolidated_for_loop_index_1]->isAnswered_ == true ) {
}
/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
 if (data_entry_window == 0) {
	cout << "jumpToQuestion = " << jumpToQuestion << endl;	cout << "jumpToIndex = " << jumpToIndex << endl;}

if ( (q5_list.questionList[i1]->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)) ||
(q5_list.questionList[i1]->isAnswered_ && !q5_list.questionList[i1]->VerifyQuestionIntegrity()) || 
stopAtNextQuestion||
(jumpToQuestion == "q5" && jumpToIndex ==  consolidated_for_loop_index_1) ||
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag) 
  && !(q5_list.questionList[i1]->question_attributes.isAllowBlank()) &&q5_list.questionList[i1]->isAnswered_ == false )) {
label_eval_q5:
if( jumpToQuestion == "q5" && jumpToIndex == consolidated_for_loop_index_1){
back_jump = false;
jumpToIndex = -1;
}
if ( q5_list.questionList[i1]->question_attributes.hidden_==false) {
fprintf( qscript_stdout, " reached : q5  because" );
if (q5_list.questionList[i1]->isAnswered_ == false) {fprintf(qscript_stdout, " isAnswered_ == false \n" );
}
if (q5_list.questionList[i1]->isAnswered_ == true && !q5_list.questionList[i1]->VerifyQuestionIntegrity()) {fprintf(qscript_stdout, " failed VerifyQuestionIntegrity \n");
}
		 stopAtNextQuestion = false;
		q5_list.questionList[i1]->eval(question_window, stub_list_window, data_entry_window, error_msg_window);
	}
if(user_navigation == NAVIGATE_PREVIOUS){
		AbstractQuestion * target_question = ComputePreviousQuestion(q5_list.questionList[consolidated_for_loop_index_1]);
		if(target_question == 0)
		goto label_eval_q5;
		else {
		jumpToQuestion = target_question->questionName_;
		if(target_question->type_ == QUESTION_ARR_TYPE){
			jumpToIndex = ComputeJumpToIndex(target_question);
		}
		if (data_entry_window==0) cout << "target question: " << jumpToQuestion;
		if (data_entry_window==0) cout << "target question Index: " << jumpToIndex;
		back_jump = true;
		user_navigation = NOT_SET;
		goto start_of_questions;
}
}
else if (user_navigation == NAVIGATE_NEXT){
		stopAtNextQuestion = true;
		user_navigation = NOT_SET;
}
else if (user_navigation == JUMP_TO_QUESTION){
		DisplayActiveQuestions();
		GetUserResponse(jumpToQuestion, jumpToIndex);
		user_navigation = NOT_SET;
		goto start_of_questions;
		}
else if (user_navigation == SAVE_DATA){
	write_data_to_disk(question_list, jno, ser_no);
	cout << "saved partial data\n";
		if (data_entry_window) mvwprintw(data_entry_window,2,50, "saved partial data");
 else 	cout << "saved partial data\n";
		if (q5_list.questionList[consolidated_for_loop_index_1]->isAnswered_==false) {
		cout << "question has not been answered ... jumping back\n";
			goto label_eval_q5;
		}
}
 else { 
last_question_answered = q5_list.questionList[consolidated_for_loop_index_1];
}
}
}
for (i1 = 0;i1<10;i1 = i1+1){
int32_t consolidated_for_loop_index_2 = i1;
/* compound statement on line no: 41 questionsInBlock_, size:1 q6,  */
/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():1 */
lab_q6:
if( back_jump == true  && q6_list.questionList[consolidated_for_loop_index_2]->isAnswered_ == true ) {
}
/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
 if (data_entry_window == 0) {
	cout << "jumpToQuestion = " << jumpToQuestion << endl;	cout << "jumpToIndex = " << jumpToIndex << endl;}

if ( (q6_list.questionList[i1]->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)) ||
(q6_list.questionList[i1]->isAnswered_ && !q6_list.questionList[i1]->VerifyQuestionIntegrity()) || 
stopAtNextQuestion||
(jumpToQuestion == "q6" && jumpToIndex ==  consolidated_for_loop_index_2) ||
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag) 
  && !(q6_list.questionList[i1]->question_attributes.isAllowBlank()) &&q6_list.questionList[i1]->isAnswered_ == false )) {
label_eval_q6:
if( jumpToQuestion == "q6" && jumpToIndex == consolidated_for_loop_index_2){
back_jump = false;
jumpToIndex = -1;
}
if ( q6_list.questionList[i1]->question_attributes.hidden_==false) {
fprintf( qscript_stdout, " reached : q6  because" );
if (q6_list.questionList[i1]->isAnswered_ == false) {fprintf(qscript_stdout, " isAnswered_ == false \n" );
}
if (q6_list.questionList[i1]->isAnswered_ == true && !q6_list.questionList[i1]->VerifyQuestionIntegrity()) {fprintf(qscript_stdout, " failed VerifyQuestionIntegrity \n");
}
		 stopAtNextQuestion = false;
		q6_list.questionList[i1]->eval(question_window, stub_list_window, data_entry_window, error_msg_window);
	}
if(user_navigation == NAVIGATE_PREVIOUS){
		AbstractQuestion * target_question = ComputePreviousQuestion(q6_list.questionList[consolidated_for_loop_index_2]);
		if(target_question == 0)
		goto label_eval_q6;
		else {
		jumpToQuestion = target_question->questionName_;
		if(target_question->type_ == QUESTION_ARR_TYPE){
			jumpToIndex = ComputeJumpToIndex(target_question);
		}
		if (data_entry_window==0) cout << "target question: " << jumpToQuestion;
		if (data_entry_window==0) cout << "target question Index: " << jumpToIndex;
		back_jump = true;
		user_navigation = NOT_SET;
		goto start_of_questions;
}
}
else if (user_navigation == NAVIGATE_NEXT){
		stopAtNextQuestion = true;
		user_navigation = NOT_SET;
}
else if (user_navigation == JUMP_TO_QUESTION){
		DisplayActiveQuestions();
		GetUserResponse(jumpToQuestion, jumpToIndex);
		user_navigation = NOT_SET;
		goto start_of_questions;
		}
else if (user_navigation == SAVE_DATA){
	write_data_to_disk(question_list, jno, ser_no);
	cout << "saved partial data\n";
		if (data_entry_window) mvwprintw(data_entry_window,2,50, "saved partial data");
 else 	cout << "saved partial data\n";
		if (q6_list.questionList[consolidated_for_loop_index_2]->isAnswered_==false) {
		cout << "question has not been answered ... jumping back\n";
			goto label_eval_q6;
		}
}
 else { 
last_question_answered = q6_list.questionList[consolidated_for_loop_index_2];
}
}
}
/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
lab_q7:
if( back_jump == true  && q7->isAnswered_ == true ) {
if( jumpToQuestion == "q7")
{ back_jump = false;
}
}
/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
if ( (q7->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
(q7->isAnswered_ && !q7->VerifyQuestionIntegrity())||
stopAtNextQuestion ||
jumpToQuestion == "q7" || 
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q7->question_attributes.isAllowBlank()) && q7->isAnswered_ == false )) {
if(stopAtNextQuestion && q7->question_attributes.hidden_ == false ) {
	stopAtNextQuestion = false;  fprintf (qscript_stdout, " at question:  q7 disarming stopAtNextQuestion = false \n");

}
label_eval_q7:
		if ( q7->question_attributes.hidden_==false) {
		 stopAtNextQuestion = false;
q7->eval(question_window, stub_list_window, data_entry_window, error_msg_window);
	}
if(user_navigation == NAVIGATE_PREVIOUS){
		AbstractQuestion * target_question = ComputePreviousQuestion(q7);
		if(target_question == 0)
		goto label_eval_q7;
		else {
		jumpToQuestion = target_question->questionName_;
		if(target_question->type_ == QUESTION_ARR_TYPE){
			jumpToIndex = ComputeJumpToIndex(target_question);
		}
		if (data_entry_window==0) cout << "target question: " << jumpToQuestion;
		if (data_entry_window==0) cout << "target question Index: " << jumpToIndex;
		back_jump = true;
		user_navigation = NOT_SET;
		goto start_of_questions;
}
}
else if (user_navigation == NAVIGATE_NEXT){
	if (q7->isAnswered_==false && q7->question_attributes.isAllowBlank()==false ) {
		goto label_eval_q7;
	}
	stopAtNextQuestion = true;
		user_navigation = NOT_SET;
		}
else if (user_navigation == JUMP_TO_QUESTION){
		DisplayActiveQuestions();
		GetUserResponse(jumpToQuestion, jumpToIndex);
		user_navigation = NOT_SET;
		goto start_of_questions;
		}
else if (user_navigation == SAVE_DATA){
	write_data_to_disk(question_list, jno, ser_no);
		if (data_entry_window) mvwprintw(data_entry_window,2,50, "saved partial data");
 else 	cout << "saved partial data\n";
		if (q7->isAnswered_==false) {
			goto label_eval_q7;
		}
	} else { 
last_question_answered = q7;
}
}
/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
lab_q8:
if( back_jump == true  && q8->isAnswered_ == true ) {
if( jumpToQuestion == "q8")
{ back_jump = false;
}
}
/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
if ( (q8->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
(q8->isAnswered_ && !q8->VerifyQuestionIntegrity())||
stopAtNextQuestion ||
jumpToQuestion == "q8" || 
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q8->question_attributes.isAllowBlank()) && q8->isAnswered_ == false )) {
if(stopAtNextQuestion && q8->question_attributes.hidden_ == false ) {
	stopAtNextQuestion = false;  fprintf (qscript_stdout, " at question:  q8 disarming stopAtNextQuestion = false \n");

}
label_eval_q8:
		if ( q8->question_attributes.hidden_==false) {
		 stopAtNextQuestion = false;
q8->eval(question_window, stub_list_window, data_entry_window, error_msg_window);
	}
if(user_navigation == NAVIGATE_PREVIOUS){
		AbstractQuestion * target_question = ComputePreviousQuestion(q8);
		if(target_question == 0)
		goto label_eval_q8;
		else {
		jumpToQuestion = target_question->questionName_;
		if(target_question->type_ == QUESTION_ARR_TYPE){
			jumpToIndex = ComputeJumpToIndex(target_question);
		}
		if (data_entry_window==0) cout << "target question: " << jumpToQuestion;
		if (data_entry_window==0) cout << "target question Index: " << jumpToIndex;
		back_jump = true;
		user_navigation = NOT_SET;
		goto start_of_questions;
}
}
else if (user_navigation == NAVIGATE_NEXT){
	if (q8->isAnswered_==false && q8->question_attributes.isAllowBlank()==false ) {
		goto label_eval_q8;
	}
	stopAtNextQuestion = true;
		user_navigation = NOT_SET;
		}
else if (user_navigation == JUMP_TO_QUESTION){
		DisplayActiveQuestions();
		GetUserResponse(jumpToQuestion, jumpToIndex);
		user_navigation = NOT_SET;
		goto start_of_questions;
		}
else if (user_navigation == SAVE_DATA){
	write_data_to_disk(question_list, jno, ser_no);
		if (data_entry_window) mvwprintw(data_entry_window,2,50, "saved partial data");
 else 	cout << "saved partial data\n";
		if (q8->isAnswered_==false) {
			goto label_eval_q8;
		}
	} else { 
last_question_answered = q8;
}
}
}

	if (write_data_file_flag) {

		 cout << "write_data_file_flag is set\n";
		write_ascii_data_to_disk();
	} else if (write_qtm_data_file_flag) {
		 cout << "write_qtm_data_file_flag is set\n";
		write_qtm_data_to_disk();
	} else if (write_xtcc_data_file_flag) {
		 cout << "write_xtcc_data_file_flag is set\n";
		 write_xtcc_data_to_disk();
	} else {
	char end_of_question_navigation;
label_end_of_qnre_navigation:
	wclear(data_entry_window);
	mvwprintw(data_entry_window, 1, 1,"End of Questionnaire: ((s)ave, (p)revious question, question (j)ump list)"); 
	mvwscanw(data_entry_window, 1, 75, "%c", & end_of_question_navigation);
	if(end_of_question_navigation == 's'){
		write_data_to_disk(question_list, jno, ser_no);
	} else if (end_of_question_navigation == 'p'){
		AbstractQuestion * target_question = ComputePreviousQuestion(last_question_answered);
		if(target_question->type_ == QUESTION_ARR_TYPE)
			{
				jumpToIndex = ComputeJumpToIndex(target_question);
			}
		jumpToQuestion = target_question->questionName_;
		if (data_entry_window == 0) cout << "target question: " << jumpToQuestion;
		back_jump = true;
		user_navigation = NOT_SET;
		goto start_of_questions;
	}	else if (end_of_question_navigation == 'j') {
		DisplayActiveQuestions();
		GetUserResponse(jumpToQuestion, jumpToIndex);
		user_navigation = NOT_SET;
		goto start_of_questions;
}	else if (end_of_question_navigation == 'q') {
		reset_questionnaire();
} else {
		goto label_end_of_qnre_navigation;
	}
	wclear(data_entry_window);
	mvwprintw(data_entry_window, 1, 1, "Enter Serial No (0) to exit: "); 
	mvwscanw(data_entry_window, 1, 40, "%d", & ser_no);
	}
	reset_questionnaire();

	} /* close while */
	endwin();
    if (write_qtm_data_file_flag||write_data_file_flag || write_xtcc_data_file_flag) {

           string freq_count_file_name(jno + string(".freq_count.csv"));
           fstream freq_count_file(freq_count_file_name.c_str(), ios_base::out | ios_base::trunc);

           // for (map<string, map<int, int> >::iterator it = freq_count.begin();
           //              it != freq_count.end(); ++ it) ;
       for (int32_t i=0; i<question_list.size(); ++i)
       {
                   AbstractQuestion *q = question_list[i];
                   //freq_count_file << it->first << endl;
                   freq_count_file << q->questionName_ ;
			stringstream question_name_str;
			question_name_str << q->questionName_;
		    if (q->loop_index_values.size()) {
				for (int j=0; j<q->loop_index_values.size(); ++j) {
					freq_count_file << "." << q->loop_index_values[j];
					question_name_str << "." << q->loop_index_values[j];
				}
		    }
		    freq_count_file << endl;
			if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q)) {
				freq_count_file << "stubs, code, frequency" << endl;
				map<int32_t, int32_t>  q_freq_count = freq_count[question_name_str.str()];
				vector<stub_pair> & vec= (nq->nr_ptr->stubs);
				for (map<int32_t, int32_t>::const_iterator it2 = q_freq_count.begin();
					it2 != q_freq_count.end(); ++ it2)
				{
					for (int i=0; i<vec.size(); ++i) {
						if (vec[i].code == it2->first) {
							freq_count_file << "\"" << vec[i].stub_text
								<< "\"" << ",";
						}
					}
					freq_count_file << it2->first << ", "
						<< it2->second << endl;
				}
			} else {
				freq_count_file << ", code, frequency" << endl;
				map<int32_t, int32_t>  q_freq_count = freq_count[question_name_str.str()];
				for (map<int32_t, int32_t>::const_iterator it2 = q_freq_count.begin();
					it2 != q_freq_count.end(); ++ it2)
				{
					freq_count_file << ", " << it2->first << ", "
						<< it2->second << endl;
				}
			}
           }
           freq_count_file << endl;
	for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {
		delete qtm_datafile_question_disk_map[i];
		qtm_datafile_question_disk_map[i] = 0;
	}
	for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {
		delete ascii_flatfile_question_disk_map[i];
		ascii_flatfile_question_disk_map[i] = 0;
	}
    }

} /* close eval */
	void write_data_to_disk(const vector<AbstractQuestion*>& q_vec
		, string jno
		, int32_t ser_no) {
		stringstream fname_str;
		fname_str << jno << "_" << ser_no << ".dat";
		//FILE * fptr = fopen(fname_str.str().c_str(), "w+b");
	
	
		std::ofstream data_file;
		data_file.exceptions(std::ios::failbit | std::ios::badbit);
		data_file.open(fname_str.str().c_str(), ios_base::ate);
	
		for(int32_t i = 0; i < question_list.size(); ++i){
			question_list[i]->WriteDataToDisk(data_file);
			/*
			fprintf(fptr, "%s: ", question_list[i]->name.c_str());
			for( set<int32_t>::iterator iter = question_list[i]->input_data.begin();
					iter != question_list[i]->input_data.end(); ++iter){
				fprintf(fptr, "%d ", *iter);
			}
			fprintf(fptr, "
");
			question_list[i]->input_data.clear();
			*/
		}
		data_file.flush();
		data_file.close();
		//fclose(fptr);
	}


// The first question before this question that is answered
AbstractQuestion * ComputePreviousQuestion(AbstractQuestion * q)
{
	int32_t current_question_index = -1;
	for (int32_t i = questions_start_from_here_index; i < question_list.size(); ++i) {
		if (question_list[i] == q) {
			current_question_index = i;
			break;
		}
	}
	if (current_question_index == -1) {
		cerr << "internal compiler error at runtime ... filename: " 
			<< __FILE__ 
			<< "line no: " << __LINE__
			<< endl;
	}
	for (int32_t i = current_question_index-1; i >= 0; --i) {
		if (question_list[i]->isAnswered_ && !question_list[i]->question_attributes.hidden_) {
			return question_list[i];
		}
	}
// If we reach here just return the 1st question and hope for the best
// This will not work if there is a condition on the 1st question - because of which it should never have been taken
	return question_list[questions_start_from_here_index];
}
int32_t ComputeJumpToIndex(AbstractQuestion * q)
{
	//cout << "ENTER ComputeJumpToIndex: index:  ";
	//for (int32_t i = 0; i < q->loop_index_values.size(); ++i) {
	//	cout << q->loop_index_values[i] << " ";
	//}
	//cout << endl;
	int32_t index = 0;
	for (int32_t i = 0; i < q->loop_index_values.size(); ++i) {
		int32_t tmp1=q->loop_index_values[i];
		for (int32_t j = i+1; j < q->dummyArrayQuestion_->array_bounds.size(); ++j) {
			tmp1 *=q->dummyArrayQuestion_->array_bounds[j];
		}
		index+=tmp1;
	}
	//cout << "EXIT ComputeJumpToIndex: returning : " << index << endl;
	return index;
}
void reset_questionnaire(){
for(int32_t i = 0; i< question_list.size(); ++i){
	question_list[i]->isAnswered_ = false;
	question_list[i]->input_data.clear();
	}
}

    int read_a_serial_no()
    {
	//cout << "ENTER: "  << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
restart:
	struct dirent *directory_entry = readdir(directory_ptr);
	if (directory_entry == NULL) {
	    // we have read upto the last record in the directory
	    cout << "finished reading all data files ... exiting"
		<< endl;
	    return 0;
	}
	string dir_entry_name(directory_entry->d_name);
	int len_entry = dir_entry_name.length();
	if (len_entry > 4 &&
	    dir_entry_name[len_entry - 1] == 't' &&
	    dir_entry_name[len_entry - 2] == 'a' &&
	    dir_entry_name[len_entry - 3] == 'd' &&
	    dir_entry_name[len_entry - 4] == '.') {
	    if (dir_entry_name.length() < jno.length() + 6
		/* "_1.dat" is the shortest possible datafile name for our study */
		) {
		// cannot be our data file
		goto restart;
	    }
	    bool not_our_file = false;
	    for (int i = 0; i < jno.length(); ++i) {
		if (!(jno[i] == dir_entry_name[i])) {
		    // cannot be our data file
		    not_our_file = true;
		    break;
		}
	    }
	    if (not_our_file) {
		//continue;
		goto restart;
	    }
	    // all our data files are expected
	    // to have a ".dat" ending and '_' after job number
	    // find the "."
	    cout << dir_entry_name << endl;
	    if (dir_entry_name[jno.length()] != '_') {
		not_our_file = true;
		//continue;
		goto restart;
	    }
	    stringstream file_ser_no_str;
	    for (int i = jno.length() + 1;
		 i < dir_entry_name.length(); ++i) {
		if (isdigit(dir_entry_name[i])) {
		    file_ser_no_str << dir_entry_name[i];
		} else {
		    if ((i + 4 == dir_entry_name.length())
			&& dir_entry_name[i] == '.'
			&& dir_entry_name[i + 1] == 'd'
			&& dir_entry_name[i + 2] == 'a'
			&& dir_entry_name[i + 3] == 't') {
			//its most probably our file 
			// need to check leading digit is not 0
			break;
		    } else {
			// it's not our file 
			not_our_file = true;
			goto restart;
		    }
		}
	    }
	    if (not_our_file) {
		    goto restart;
	    }
	    if ((file_ser_no_str.str())[0] == '0') {
		// the leading digit of our data file
		// can never be zero - so its not our file
		goto restart;
	    }
	    cout << "got a data file: " << dir_entry_name << endl;
	    int file_ser_no = atoi(file_ser_no_str.str().c_str());
	    load_data(jno, file_ser_no);
	    merge_disk_data_into_questions2(qscript_stdout, last_question_answered, last_question_visited);
	    return file_ser_no;
	} else {
	    // not our data file
	    goto restart;
	}
    }

void DisplayActiveQuestions()
{
				for(int32_t i = 0; i<question_list.size(); ++i){
					if(question_list[i]->isAnswered_)
						cout << question_list[i]->questionName_ << " ";
				}				cout << endl;
			
}
void GetUserResponse(string & qno, int32_t & qindex)
{
			char newl;
			cin >> qno;cin.get(newl);
qindex = 0;
			cout << "User input qno:" << qno 
				<< ", newl: " << newl << endl;
			}
void write_qtm_data_to_disk()
 {
	using qtm_data_file_ns::qtm_data_file_writer_log;
	qtm_data_file_writer_log << "writing serial no: " << ser_no << " to disk \n";
	for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {
		qtm_datafile_question_disk_map[i]->write_data ();
	}
	qtm_datafile_question_disk_map[0]->qtmDataFile_.write_record_to_disk(qtm_disk_file, ser_no);
	qtm_datafile_question_disk_map[0]->qtmDataFile_.Reset();
	//qtm_datafile_question_disk_map[0]->Reset();
	for (int32_t i = 0; i < qtm_datafile_question_disk_map.size(); ++i) {
		qtm_datafile_question_disk_map[i]->Reset();
	}
	do_freq_counts();
}
void write_ascii_data_to_disk()
{
	stringstream temp_ser_no_str;
	temp_ser_no_str << ser_no;
	if (temp_ser_no_str.str().length() > ser_no_pos) {
		cerr << "space reserved to hold serial no: " 
			<< ser_no_pos << " is not enough"
			<< " to hold this serial no: " 
			<< ser_no << endl;
		exit(1);
	} else {
		//char * ptr = flat_file_output_buffer;
		for (int i=0; i<temp_ser_no_str.str().length(); ++i) {
			flat_file_output_buffer[i] = temp_ser_no_str.str()[i];
		//cout << "writing digit " << temp_ser_no_str[i] << " to flat_file_output_buffer" << endl;
		}
	}

	for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {
		ascii_flatfile_question_disk_map[i]->write_data (flat_file_output_buffer);
	}
	// cout << "output_buffer: " << flat_file_output_buffer;
	flat_file << flat_file_output_buffer << endl;
	memset(flat_file_output_buffer, ' ', len_flat_file_output_buffer-1);
	do_freq_counts();
}
	void prompt_user_for_serial_no()
	{
		wclear(data_entry_window);
		mvwprintw(data_entry_window, 1, 1, "Enter Serial No (0) to exit: ");
		mvwscanw(data_entry_window, 1, 40, "%d", & ser_no);
	}

void write_xtcc_data_to_disk()
 {
	void * void_ptr = &ser_no;
	char * char_ptr = static_cast<char*>(void_ptr);
	char * my_data_ptr = xtcc_datafile_output_buffer;
	for (int i=0; i<sizeof(int); ++i) {
		*my_data_ptr++ = *char_ptr++;
	}

	for (int i=0; i<xtcc_question_disk_map.size(); ++i) {
		xtcc_question_disk_map[i]->write_data (xtcc_datafile_output_buffer);
	}
	//cout << "output_buffer: " << xtcc_datafile_output_buffer;
	xtcc_datafile . write(xtcc_datafile_output_buffer, len_xtcc_datafile_output_buffer);
	memset(xtcc_datafile_output_buffer, 0, len_xtcc_datafile_output_buffer-1);
	do_freq_counts();
	cout << "len_xtcc_datafile_output_buffer: " << len_xtcc_datafile_output_buffer << endl;
}
void do_freq_counts()
{
	for (int32_t i = 0; i < question_list.size(); ++i) {
		AbstractQuestion * q = question_list[i];
		stringstream question_name_str;
		question_name_str << q->questionName_;
		if (q->loop_index_values.size()) {
			for (int j=0; j<q->loop_index_values.size(); ++j) {
				question_name_str << "." << q->loop_index_values[j];
			}
		}
		map<int , int> q_freq_map = freq_count[question_name_str.str()];
		for (set<int32_t>::iterator it = q->input_data.begin();
			it != q->input_data.end(); ++it) {
				q_freq_map[*it] ++;
		}
		freq_count[question_name_str.str()] = q_freq_map;
	}
}
};
int32_t main(int argc, char * argv[]){
	process_options(argc, argv);
	if (write_data_file_flag||write_qtm_data_file_flag||write_xtcc_data_file_flag) {
		qtm_data_file_ns::init();
		qtm_data_file_ns::init_exceptions();
		directory_ptr = opendir(".");
		if (! directory_ptr) {
			cout << " unable to open . (current directory) for reading\n";
			exit(1);
		}
	}
bool using_ncurses = true;
qscript_stdout = fopen(qscript_stdout_fname.c_str(), "w");
	using namespace std;
	SetupNCurses(question_window, stub_list_window, data_entry_window, error_msg_window, help_window, question_panel, stub_list_panel, data_entry_panel, error_msg_panel, help_panel);
	if(question_window == 0 || stub_list_window == 0 || data_entry_window == 0
		 /* || help_window == 0 */
		 ){
		cerr << "Unable to create windows ... exiting" << endl;
		return 1;
	}
	SetupSignalHandler();
TheQuestionnaire theQuestionnaire;
theQuestionnaire.base_text_vec.push_back(BaseText("All Respondents"));
theQuestionnaire.compute_flat_file_map_and_init();
theQuestionnaire.eval();
	for (int i=0; i<question_list.size(); ++i) {
		delete question_list[i];
		question_list[i] = 0;
	}
clear_previous_data();

} /* close main */
void SetupNCurses(WINDOW * &  question_window,
			WINDOW * &  stub_list_window,
			WINDOW * & data_entry_window,
			WINDOW * & error_msg_window,
			WINDOW * & help_window,
			PANEL * &  question_panel,
			PANEL * &  stub_list_panel,
			PANEL * & data_entry_panel,
			PANEL * & error_msg_panel,
			PANEL * & help_panel)
{
	initscr();
       cbreak();
       nonl();
       intrflush(stdscr, FALSE);
	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	chtype space = ' ';	init_pair(1, COLOR_RED, COLOR_WHITE);
	init_pair(2, COLOR_GREEN, COLOR_WHITE);
	init_pair(3, COLOR_BLUE, COLOR_WHITE);
	init_pair(4, COLOR_MAGENTA, COLOR_CYAN);
	init_pair(5, COLOR_WHITE, COLOR_RED);
	int32_t maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);


	int32_t DATA_ENTRY_WINDOW_HEIGHT=5, DATA_ENTRY_WINDOW_WIDTH=maxX;

       int32_t starty = maxY-DATA_ENTRY_WINDOW_HEIGHT;
       int32_t startx = 0;
	data_entry_window = create_newwin(DATA_ENTRY_WINDOW_HEIGHT
			, DATA_ENTRY_WINDOW_WIDTH, starty, startx);
	wcolor_set(data_entry_window, COLOR_PAIR(1), 0);
	wattron(data_entry_window, COLOR_PAIR(1));
	wbkgd(data_entry_window, space | COLOR_PAIR(1));
	wattrset(data_entry_window, COLOR_PAIR(1));
	wmove(data_entry_window, 1, 1);
       keypad(data_entry_window, TRUE);
	// Divide the rest of the screen between the question window
	//  and the stub window in the ration 1:2
	int32_t height_left = maxY - DATA_ENTRY_WINDOW_HEIGHT;
	int32_t STUB_LIST_WINDOW_HEIGHT=(height_left / 3)*2, STUB_LIST_WINDOW_WIDTH=maxX;
	starty = maxY - DATA_ENTRY_WINDOW_HEIGHT - STUB_LIST_WINDOW_HEIGHT;
	stub_list_window = create_newwin(STUB_LIST_WINDOW_HEIGHT
			, STUB_LIST_WINDOW_WIDTH, starty, startx);
	wcolor_set(stub_list_window, 2, 0);
	wbkgd(stub_list_window, space | COLOR_PAIR(2));
	wattron(stub_list_window, COLOR_PAIR(2));



	int32_t ERROR_WINDOW_HEIGHT= (height_left/6), ERROR_WINDOW_WIDTH=maxX;
	starty = maxY - DATA_ENTRY_WINDOW_HEIGHT - STUB_LIST_WINDOW_HEIGHT - ERROR_WINDOW_HEIGHT;
	error_msg_window = create_newwin(ERROR_WINDOW_HEIGHT
			, ERROR_WINDOW_WIDTH, starty, startx);
	wbkgd(error_msg_window, space | COLOR_PAIR(5));
	wcolor_set(error_msg_window, 3, 0);
	wattron(error_msg_window, COLOR_PAIR(5));
 	height_left -= ERROR_WINDOW_HEIGHT;
	int32_t QUESTION_WINDOW_HEIGHT=maxY - DATA_ENTRY_WINDOW_HEIGHT - STUB_LIST_WINDOW_HEIGHT - ERROR_WINDOW_HEIGHT, QUESTION_WINDOW_WIDTH=maxX;
	starty = 0;
	question_window = create_newwin(QUESTION_WINDOW_HEIGHT
			, QUESTION_WINDOW_WIDTH, starty, startx);
	wbkgd(question_window, space | COLOR_PAIR(3));
	wcolor_set(question_window, 3, 0);
	wattron(question_window, COLOR_PAIR(3));

	int32_t HELP_WINDOW_HEIGHT=(int)((float)(2/3)*maxY), HELP_WINDOW_WIDTH=maxX/2;

       starty = 5;
       startx = 5;
	//help_window = create_newwin(HELP_WINDOW_HEIGHT, HELP_WINDOW_WIDTH, starty, startx);
	question_panel = new_panel(question_window);
	stub_list_panel = new_panel(stub_list_window);
	data_entry_panel = new_panel(data_entry_window);
	//help_panel = new_panel(help_window);
	error_msg_panel = new_panel(error_msg_window);
	update_panels();
	doupdate();
}



WINDOW *create_newwin(int32_t height, int32_t width, int32_t starty, int32_t startx)
{       WINDOW *local_win;

        local_win = newwin(height, width, starty, startx);
        box(local_win, 0 , 0);          /* 0, 0 gives default characters 
                                         * for the vertical and horizontal
                                         * lines                        */

        return local_win;
}

static void sig_usr(int32_t signo)
{
	if(signo == SIGSEGV){
		printf("received SIGSEGV\n");
	} else if(signo == SIGILL){
		printf("received SIGILL\n");
	} else {
		fprintf(stderr, "received signal : %d\n", signo);
	}
	fflush(qscript_stdout);
	 endwin();
	exit(1);
}
void SetupSignalHandler()
{
	if(signal(SIGSEGV, sig_usr) == SIG_ERR){
		fprintf(stderr, "cannot catch SIGSEGV\n");
		exit(1);
	}  else if(signal(SIGILL, sig_usr) == SIG_ERR){
		fprintf(stderr, "cannot catch SIGILL\n");
		exit(1);
	}
}

int process_options(int argc, char * argv[])
{
	//int32_t opterr=1, c;
	extern int32_t optind, opterr, optopt;
	extern char * optarg;
	int c;
	while ( (c = getopt(argc, argv, "x::w::q::")) != -1) {
		char ch = optopt;
		switch (c) {
		case 'w': {
			  write_data_file_flag = true;
			  if (optarg) {
				  output_data_file_name = optarg;
			  } else {
				  output_data_file_name = "datafile.dat";
			  }
		}
		break;
		case 'x': {
			  write_xtcc_data_file_flag = true;
			  if (optarg) {
				  output_xtcc_data_file_name = optarg;
			  } else {
				  output_xtcc_data_file_name = "xtcc_datafile.dat";
			  }
		}
		break;
		case 'q': {
			  write_qtm_data_file_flag = true;
			  if (optarg) {
				  output_qtm_data_file_name = optarg;
			  } else {
				  output_qtm_data_file_name = "qtm_datafile.dat";
			  }
		}
		break;
		case '?' : {
				   cout << " invalid option, optopt:" << optopt << endl;
				   exit(1);
			   }
			  break;
		default:
			  cerr << "invalid options: ch: " << ch << ", c: " << c << endl;
		}
	}
	cout << "output_data_file_name: " << output_data_file_name << endl;
	cout << "write_data_file_flag: " << write_data_file_flag << endl;
	cout << "output_qtm_data_file_name: " << output_qtm_data_file_name << endl;
	cout << "write_qtm_data_file_flag: " << write_qtm_data_file_flag << endl;
	//exit(1);
}
	void print_map_header(fstream & map_file )
{
map_file << "Question No			,width,	no responses,	start position,	end position\n";
}

qtm_data_file_ns::QtmDataDiskMap* GetQuestionMapEntry(vector <qtm_data_file_ns::QtmDataDiskMap*> & qtm_datafile_question_disk_map,
			string name)
{
	for (int i=0; i < qtm_datafile_question_disk_map.size(); ++i) {
		if (qtm_datafile_question_disk_map[i]->q->questionName_ == name) {
			return qtm_datafile_question_disk_map[i];
		}
	}
	return 0;
}
