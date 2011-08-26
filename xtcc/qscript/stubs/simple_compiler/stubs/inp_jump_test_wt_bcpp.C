#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <errno.h>
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <microhttpd.h>
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
#include "UserResponse.h"


#include "a_few_pd_curses_keys.h"



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
void write_data_to_disk(const vector<AbstractQuestion*>& q_vec, string jno, int32_t ser_no);
void SetupSignalHandler();
static void sig_usr(int32_t signo);
string output_data_file_name;
string output_qtm_data_file_name;
string output_xtcc_data_file_name;
void GetUserResponse(string& qno, int32_t &qindex);
string jno = "inp_jump_test";
char * flat_file_output_buffer = 0;
char * xtcc_datafile_output_buffer = 0;
int32_t len_flat_file_output_buffer  = 0;
int32_t len_xtcc_datafile_output_buffer  = 0;
vector <AsciiFlatFileQuestionDiskMap*> ascii_flatfile_question_disk_map;
vector <XtccDataFileDiskMap*> xtcc_question_disk_map;
vector <qtm_data_file_ns::QtmDataDiskMap*> qtm_datafile_question_disk_map;
qtm_data_file_ns::QtmDataFile qtm_data_file;
void Compute_FlatFileQuestionDiskDataMap(vector<AbstractQuestion*> p_question_list);

int process_options(int argc, char * argv[]);
WINDOW  * question_window = 0,
* stub_list_window = 0,
* data_entry_window = 0,
* help_window = 0;
PANEL   * question_panel = 0,
* stub_list_panel = 0,
* data_entry_panel = 0,
* help_panel = 0;
DIR * directory_ptr = 0;
struct TheQuestionnaire
{
	AbstractQuestion * last_question_answered;
	AbstractQuestion * last_question_visited;
	bool back_jump;
	string jno;
	int ser_no;
	bool stopAtNextQuestion;
	int32_t questions_start_from_here_index;
	int ser_no_pos;
	vector <BaseText> base_text_vec;
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 3, flagIsAForBody_: 0, source lineNo_: 0
	XtccSet xs_0;
	RangeQuestion * q1;
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 0, flagIsAForBody_: 0, source lineNo_: 8
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 0, flagIsAForBody_: 0, source lineNo_: 10
	XtccSet xs_1;
	RangeQuestion * q2;
	XtccSet xs_2;
	RangeQuestion * q3;

	TheQuestionnaire()
		/* length(): 0 */: last_question_answered(0), last_question_visited(0), back_jump(false), stopAtNextQuestion(false)
		, jno ("inp_jump_test"), ser_no(0)
	{
		xs_0.indiv.insert(11);
		xs_0.indiv.insert(16);
		xs_0.range.push_back(pair<int32_t,int32_t>(5,8));
		xs_0.range.push_back(pair<int32_t,int32_t>(1,2));
		xs_0.range.push_back(pair<int32_t,int32_t>(9,10));
		q1 = new RangeQuestion(QUESTION_TYPE, 7,string( "q1"),string(" Q1. "),spn,1,INT32_TYPE,xs_0, QuestionAttributes(false , false), true);
		xs_1.indiv.insert(1);
		xs_1.indiv.insert(2);
		xs_1.indiv.insert(3);
		xs_1.indiv.insert(4);
		q2 = new RangeQuestion(QUESTION_TYPE, 15,string( "q2"),string(" Q2. "),spn,1,INT32_TYPE,xs_1, QuestionAttributes(false , false), false);
		xs_2.indiv.insert(5);
		xs_2.indiv.insert(6);
		q3 = new RangeQuestion(QUESTION_TYPE, 19,string( "q3"),string(" Q3. "),spn,1,INT32_TYPE,xs_2, QuestionAttributes(false , false), false);

		questions_start_from_here_index = question_list.size();
		question_list.push_back(q1);
		question_list.push_back(q2);
		question_list.push_back(q3);

		compute_flat_file_map_and_init();
	}
	void print_summary_axis (vector<qtm_data_file_ns::QtmDataDiskMap*> & v, fstream & qtm_qax_file)
	{
		AbstractQuestion * q = v[0]->q;
		if (q->q_type == spn)
		{
			int n_digits = 0;
			int rat_scale = 0;
			if (NamedStubQuestion * n_q = dynamic_cast<NamedStubQuestion*>(q))
			{
				if (n_q->nr_ptr)
				{
					string & stub_name = n_q->nr_ptr->name;
					int multiplier = 1;
					for (int i=stub_name.length()-1; i>0; --i)
					{
						if ( isdigit(stub_name[i]) )
						{
							int c = stub_name[i] - '0';
							++n_digits;
							rat_scale = rat_scale + c * multiplier;
							multiplier *= 10;
						}
						else
						{
							break;
						}
					}
				}
			}
			if (n_digits > 0)
			{
				string include_file_name;
				string mean_score_include_file;
				if (v[0]->width_ == 1)
				{
					include_file_name = "rat1c.qin";
					mean_score_include_file = "mn1c.qin";
				}
				else if (v[0]->width_ == 2)
				{
					include_file_name = "rat2c.qin";
					mean_score_include_file = "mn2c.qin";
				}
				else if (v[0]->width_ == 3)
				{
					include_file_name = "rat3c.qin";
					mean_score_include_file = "mn3c.qin";
				}
				else
				{
					include_file_name = "unhandled width syntax error";
					mean_score_include_file = "unhandled width syntax error";
				}

				if (rat_scale == 5)
				{

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_top" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 5 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_top2" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 5 << ", " << 4 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_bot" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_bot2" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ", " << 2 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_mn" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << mean_score_include_file
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ":" << 5 << ")"
							<< endl;
					}

				}
				else if (rat_scale == 7)
				{

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_top" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 7 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_top2" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 7 << ", " << 6 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_top3" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 5 << ":" << 7 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_bot" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_bot2" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ", " << 2 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_mn" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << mean_score_include_file
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ":" << 7 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_bot3" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ":" << 3 << ")"
							<< endl;
					}

				}
				else if (rat_scale == 10)
				{

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_top" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 10 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_top2" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 10 << ", " << 9 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_top3" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 8 << ":" << 10 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_bot" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_bot2" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ", " << 2 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_mn" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << mean_score_include_file
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ":" << 10 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_bot3" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ":" << 3 << ")"
							<< endl;
					}

				}
			}
			else
			{
				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "/*l " << q->questionName_ << "_sum" << endl;
				qtm_qax_file << "/*ttl" << q->questionName_ << "." << v[0]->q->questionText_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
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
			if (write_qtm_data_file_flag)
			{
				qtm_datafile_conf_parser_ns::load_config_file(jno);
				qtm_data_file.Initialize();
			}
			if (write_data_file_flag)
			{
				stringstream asc_datafile_conf_str;
				asc_datafile_conf_str << jno
					<< ".asc_data.conf";
				fstream asc_datafile_conf(asc_datafile_conf_str.str().c_str(), ios_base::in);
				if (!asc_datafile_conf)
				{
					cerr << " could not open : " << asc_datafile_conf_str.str()
						<< " for reading" << endl;
					exit(1);
				}
				string ser_no_token; string equal_token; ser_no_pos=-1; string semi_colon_token;
				asc_datafile_conf >> ser_no_token;
				if ( ser_no_token != string("SER_NO_COLS"))
				{
					cerr << "expected token SER_NO_COLS" << endl;
					exit(1);
				}
				asc_datafile_conf >> equal_token;
				if (equal_token != string("=") )
				{
					cerr << "expected token =" << endl;
					exit(1);
				}
				asc_datafile_conf >> ser_no_pos;
				if (ser_no_pos == -1)
				{
					cerr << "invalid no of positions reserved for serial no: ";
					exit(1);
				}
				current_map_pos += (ser_no_pos-1);
			}
			if (write_xtcc_data_file_flag)
			{
								 // serial no is 4 bytes fixed
				current_xtcc_map_pos += 4;
			}
			{
				AsciiFlatFileQuestionDiskMap * qscript_temp_1 = new AsciiFlatFileQuestionDiskMap(q1, current_map_pos);
				current_map_pos += qscript_temp_1->GetTotalLength();
				ascii_flatfile_question_disk_map.push_back(qscript_temp_1);
				if (write_xtcc_data_file_flag)
				{
					XtccDataFileDiskMap * qscript_temp_2 = new XtccDataFileDiskMap(q1, current_xtcc_map_pos);
					current_xtcc_map_pos += qscript_temp_2->GetTotalLength();
					xtcc_question_disk_map.push_back(qscript_temp_2);
				}
				if (write_qtm_data_file_flag)
				{
					qtm_data_file_ns::QtmDataDiskMap * qscript_temp_3 = new qtm_data_file_ns::QtmDataDiskMap(q1, qtm_data_file, base_text_vec.back());
					qtm_datafile_question_disk_map.push_back(qscript_temp_3);
				}
				base_text_vec.push_back(BaseText("All those respondents who have selected:  certain values in rq"));
				{
				}
				base_text_vec.pop_back();
				base_text_vec.push_back(BaseText("Not All those respondents who have selected:  certain values in rq"));
				{
				}
				base_text_vec.pop_back();
				AsciiFlatFileQuestionDiskMap * qscript_temp_4 = new AsciiFlatFileQuestionDiskMap(q2, current_map_pos);
				current_map_pos += qscript_temp_4->GetTotalLength();
				ascii_flatfile_question_disk_map.push_back(qscript_temp_4);
				if (write_xtcc_data_file_flag)
				{
					XtccDataFileDiskMap * qscript_temp_5 = new XtccDataFileDiskMap(q2, current_xtcc_map_pos);
					current_xtcc_map_pos += qscript_temp_5->GetTotalLength();
					xtcc_question_disk_map.push_back(qscript_temp_5);
				}
				if (write_qtm_data_file_flag)
				{
					qtm_data_file_ns::QtmDataDiskMap * qscript_temp_6 = new qtm_data_file_ns::QtmDataDiskMap(q2, qtm_data_file, base_text_vec.back());
					qtm_datafile_question_disk_map.push_back(qscript_temp_6);
				}
				AsciiFlatFileQuestionDiskMap * qscript_temp_7 = new AsciiFlatFileQuestionDiskMap(q3, current_map_pos);
				current_map_pos += qscript_temp_7->GetTotalLength();
				ascii_flatfile_question_disk_map.push_back(qscript_temp_7);
				if (write_xtcc_data_file_flag)
				{
					XtccDataFileDiskMap * qscript_temp_8 = new XtccDataFileDiskMap(q3, current_xtcc_map_pos);
					current_xtcc_map_pos += qscript_temp_8->GetTotalLength();
					xtcc_question_disk_map.push_back(qscript_temp_8);
				}
				if (write_qtm_data_file_flag)
				{
					qtm_data_file_ns::QtmDataDiskMap * qscript_temp_9 = new qtm_data_file_ns::QtmDataDiskMap(q3, qtm_data_file, base_text_vec.back());
					qtm_datafile_question_disk_map.push_back(qscript_temp_9);
				}
			}
			string map_file_name(jno + string(".map"));
			fstream map_file(map_file_name.c_str(), ios_base::out|ios_base::ate);
			print_map_header(map_file);
			for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i)
			{
				ascii_flatfile_question_disk_map[i]->print_map(map_file);
			}
			string spss_syn_file_name(jno + string("-flat-ascii.sps"));
			fstream spss_syn_file(spss_syn_file_name.c_str(), ios_base::out|ios_base::ate);
			spss_syn_file << "DATA LIST FILE='" <<  jno << ".dat'\n"<< endl << "/RESPID			1-6\n";
			for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i)
			{
				ascii_flatfile_question_disk_map[i]->write_spss_pull_data(spss_syn_file);
			}
			spss_syn_file << ".\n";

			spss_syn_file << "exe.\n";
			for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i)
			{
				ascii_flatfile_question_disk_map[i]->write_spss_variable_labels(spss_syn_file);
			}

			spss_syn_file << "exe.\n";
			for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i)
			{
				ascii_flatfile_question_disk_map[i]->write_spss_value_labels(spss_syn_file);
			}

			spss_syn_file << "exe.\n";

			spss_syn_file << "save outfile=\"" << jno << ".sav\"\n";
			string xtcc_map_file_name(jno + string(".xmap"));
			fstream xtcc_map_file(xtcc_map_file_name.c_str(), ios_base::out|ios_base::ate);
			print_map_header(xtcc_map_file);
			for (int i=0; i<xtcc_question_disk_map.size(); ++i)
			{
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
			xtcc_datafile.open(xtcc_datafile_name.c_str(), ios_base::out | ios_base::trunc);
			{
				struct stat dir_exists; stringstream s1;
				s1 << "setup-" << jno;
				if (stat(s1.str().c_str(), &dir_exists) <0)
				{
					if (errno == ENOENT)
						if (mkdir(s1.str().c_str(), S_IRUSR | S_IWUSR | S_IXUSR) <0)
					{
						perror("unable to create directory for setup files");
					}
					else
						perror("stating directory failed");
				}
			}
			if (write_qtm_data_file_flag)
			{
				string qtm_map_file_name(string("setup-") + jno + string("/") + jno + string(".qmap"));
				fstream qtm_map_file(qtm_map_file_name.c_str(), ios_base::out|ios_base::ate);
				print_map_header(qtm_map_file);
				for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i)
				{
					qtm_datafile_question_disk_map[i]->print_map(qtm_map_file);
				}
				string qtm_qax_file_name( string("setup-")+jno+string("/") + jno + string(".qax"));
				fstream qtm_qax_file(qtm_qax_file_name.c_str(), ios_base::out|ios_base::ate);
				map <string, vector<qtm_data_file_ns::QtmDataDiskMap*> > summary_tables;
				for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i)
				{
					qtm_datafile_question_disk_map[i]->print_qax(qtm_qax_file, string("setup-")+jno);
					string questionName = qtm_datafile_question_disk_map[i]->q->questionName_;
					if (qtm_datafile_question_disk_map[i]->q->loop_index_values.size() > 0)
					{
						summary_tables[questionName].push_back(qtm_datafile_question_disk_map[i]);
					}
				}
				for ( map <string, vector<qtm_data_file_ns::QtmDataDiskMap*> >::iterator it= summary_tables.begin();
					it != summary_tables.end(); ++it)
				{
					print_summary_axis(it->second, qtm_qax_file);
				}
				qtm_datafile_question_disk_map[0]->print_run(jno);
				string tab_file_name(string("setup-")+ jno + string("/") + jno + string(".tab"));
				fstream tab_file(tab_file_name.c_str(), ios_base::out|ios_base::ate);
				for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i)
				{
					string questionName = qtm_datafile_question_disk_map[i]->q->questionName_;
					AbstractQuestion * q = qtm_datafile_question_disk_map[i]->q;
					tab_file << "tab " << q->questionName_;
					for(int j=0; j<q->loop_index_values.size(); ++j)
					{
						tab_file << "_" << q->loop_index_values[j];
					}
					tab_file << " &ban" << endl;
				}
				qtm_datafile_question_disk_map[0]->qtmDataFile_.AllocateCards();
				qtm_datafile_question_disk_map[0]->qtmDataFile_.Reset();
				string qtm_disk_file_name(jno + string(".qdat"));
				qtm_disk_file.open(qtm_disk_file_name.c_str(), ios_base::out | ios_base::trunc);
			}
			if (write_xtcc_data_file_flag)
			{
				string xtcc_ax_file_name(string("setup-")+jno+string("/") + jno + string(".xtcc"));
				fstream xtcc_ax_file(xtcc_ax_file_name.c_str(), ios_base::out | ios_base::ate);
				xtcc_ax_file << "data_struct;rec_len=" << len_xtcc_datafile_output_buffer << ";\n";
				xtcc_ax_file << "ed_start\n";
				xtcc_ax_file << "	int32_t edit_data();\n";
				xtcc_ax_file << "	int32_t all;\n";
				xtcc_ax_file << "	int32_t ser_no;\n";
				for (int i=0; i<xtcc_question_disk_map.size(); ++i)
				{
					xtcc_question_disk_map[i]->print_edit_var_defns(xtcc_ax_file, string("setup-")+jno+string("/"));
				}
				xtcc_ax_file << "	int32_t edit_data()\n{\n";
				xtcc_ax_file << "	all = 1;\n";
				xtcc_ax_file << "	ser_no = c[0,3];\n";
				for (int i=0; i<xtcc_question_disk_map.size(); ++i)
				{
					xtcc_question_disk_map[i]->print_xtcc_edit_load(xtcc_ax_file, string("setup-")+jno+string("/"));
				}
				xtcc_ax_file << "	}\n";
				xtcc_ax_file << "ed_end\n";
				xtcc_ax_file << "tabstart {\n";
				for (int i=0; i<xtcc_question_disk_map.size(); ++i)
				{
					xtcc_question_disk_map[i]->print_xtcc_tab(xtcc_ax_file, string("setup-")+jno+string("/"));
				}
				xtcc_ax_file << "}\n";
				xtcc_ax_file << "axstart {\n";
				xtcc_ax_file << "ax tot_ax;\n";
				xtcc_ax_file << "ttl; \"Total\";\n";
				xtcc_ax_file << "cnt; \"All\"; c= all==1;\n";
				for (int i=0; i<xtcc_question_disk_map.size(); ++i)
				{
					xtcc_question_disk_map[i]->print_xtcc_ax(xtcc_ax_file, string("setup-")+jno+string("/"));
				}
				xtcc_ax_file << "}\n";
			}
		}
	}

	AbstractQuestion * eval2 (
	/*AbstractQuestion * p_last_question_answered,
			 AbstractQuestion * p_last_question_visited,*/
		UserNavigation p_navigation_mode)
	{
		if (last_question_visited)
			fprintf (qscript_stdout, "entered eval2: last_question_visited: %s, stopAtNextQuestion: %d\n", last_question_visited->questionName_.c_str(), stopAtNextQuestion);
		/*
		if (write_data_file_flag||write_qtm_data_file_flag||write_xtcc_data_file_flag) {
			ser_no = read_a_serial_no();
			if (ser_no == 0) {
				exit(1);
			}
		} else {
			int exists = check_if_reg_file_exists(jno, ser_no);
			if(exists == 1){
				load_data(jno,ser_no);
				//merge_disk_data_into_questions(qscript_stdout, last_question_answered, last_question_visited);
				merge_disk_data_into_questions2(qscript_stdout, last_question_answered, last_question_visited);
			}
		}

		*/
		start_of_questions:
		if(back_jump == true)
		{
			fprintf(qscript_stdout, "have reached start_of_questions with back_jump: jumpToQuestion: %s, jumpToIndex: %d\n", jumpToQuestion.c_str(), jumpToIndex);
		}
		{
			/* compound statement on line no: 0 questionsInBlock_, size:3 q1, q2, q3,  */
			int32_t i1 = 1;
			int32_t i2 = 2;
			int32_t i3;
			/* ENTER ExpressionStatement::GenerateCode */
			i3 = 10;
			/* EXIT ExpressionStatement::GenerateCode */
			/* ENTER ExpressionStatement::GenerateCode */
			fprintf(qscript_stdout,"before q1 i1:%d , i2:%d, i3:%d\n", i1, i2, i3);fflush(qscript_stdout);
			/* EXIT ExpressionStatement::GenerateCode */
			/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
			lab_q1:
			if( back_jump == true  && q1->isAnswered_ == true )
			{
				if( jumpToQuestion == "q1")
				{
					back_jump = false;
				}
			}
			/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
			if ( (q1->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
				(q1->isAnswered_ && !q1->VerifyQuestionIntegrity())||
				stopAtNextQuestion ||
				jumpToQuestion == "q1" ||
				((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q1->question_attributes.isAllowBlank()) && q1->isAnswered_ == false ))
			{
				if(stopAtNextQuestion && q1->question_attributes.hidden_ == false )
				{
					stopAtNextQuestion = false;  fprintf (qscript_stdout, " at question:  q1 disarming stopAtNextQuestion = false \n");

				}
				if (jumpToQuestion == "q1")
				{
					jumpToQuestion = "";
				}
				label_eval_q1:
				if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q1)
				{
					stopAtNextQuestion = true;
					fprintf (qscript_stdout, " at question:  q1 arming stopAtNextQuestion = true \n");
				}
				else if (q1->question_attributes.hidden_==false)
				{
					// q1->eval(question_window, stub_list_window, data_entry_window);
					last_question_visited = q1;
					fprintf(qscript_stdout, "last_question_visited: q1\n");
					return q1;
				}
			}
			/* if_nest_level: 1 */
			XtccSet qscript_temp_xtcc_set_1;
			qscript_temp_xtcc_set_1.add_indiv(1);
			bool qscript_temp_10 = qscript_temp_xtcc_set_1.contains_subset(q1->input_data);
			if (qscript_temp_10 )// ifStatementStack.size(): 0
			{
				// question_list_else_body :
				{
					/* compound statement on line no: 8 questionsInBlock_, size:0  */
					/* ENTER ExpressionStatement::GenerateCode */
					i1 = 10;
				}
			}
			else
			{
				// end of ifBody_->GetQuestionNames
				// elseIfStatement DOES NOT exists
				/* question_list_if_body.size(): 0 */
				// ****************
				{
					/* compound statement on line no: 10 questionsInBlock_, size:0  */
					/* ENTER ExpressionStatement::GenerateCode */
					i1 = 20;
				}
			}
			/* ENTER ExpressionStatement::GenerateCode */
			fprintf(qscript_stdout,"after q1 i1:%d , i2:%d, i3:%d\n", i1, i2, i3);fflush(qscript_stdout);
			/* EXIT ExpressionStatement::GenerateCode */
			/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
			lab_q2:
			if( back_jump == true  && q2->isAnswered_ == true )
			{
				if( jumpToQuestion == "q2")
				{
					back_jump = false;
				}
			}
			/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
			if ( (q2->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
				(q2->isAnswered_ && !q2->VerifyQuestionIntegrity())||
				stopAtNextQuestion ||
				jumpToQuestion == "q2" ||
				((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q2->question_attributes.isAllowBlank()) && q2->isAnswered_ == false ))
			{
				if(stopAtNextQuestion && q2->question_attributes.hidden_ == false )
				{
					stopAtNextQuestion = false;  fprintf (qscript_stdout, " at question:  q2 disarming stopAtNextQuestion = false \n");

				}
				if (jumpToQuestion == "q2")
				{
					jumpToQuestion = "";
				}
				label_eval_q2:
				if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q2)
				{
					stopAtNextQuestion = true;
					fprintf (qscript_stdout, " at question:  q2 arming stopAtNextQuestion = true \n");
				}
				else if (q2->question_attributes.hidden_==false)
				{
					// q2->eval(question_window, stub_list_window, data_entry_window);
					last_question_visited = q2;
					fprintf(qscript_stdout, "last_question_visited: q2\n");
					return q2;
				}
			}
			/* ENTER ExpressionStatement::GenerateCode */
			i1 = 1001;
			/* EXIT ExpressionStatement::GenerateCode */
			/* ENTER ExpressionStatement::GenerateCode */
			i2 = 1002;
			/* EXIT ExpressionStatement::GenerateCode */
			/* ENTER ExpressionStatement::GenerateCode */
			i3 = 1003;
			/* EXIT ExpressionStatement::GenerateCode */
			/* ENTER ExpressionStatement::GenerateCode */
			fprintf(qscript_stdout,"after q2: i1:%d , i2:%d, i3:%d\n", i1, i2, i3);fflush(qscript_stdout);
			/* EXIT ExpressionStatement::GenerateCode */
			/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
			lab_q3:
			if( back_jump == true  && q3->isAnswered_ == true )
			{
				if( jumpToQuestion == "q3")
				{
					back_jump = false;
				}
			}
			/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
			if ( (q3->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
				(q3->isAnswered_ && !q3->VerifyQuestionIntegrity())||
				stopAtNextQuestion ||
				jumpToQuestion == "q3" ||
				((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q3->question_attributes.isAllowBlank()) && q3->isAnswered_ == false ))
			{
				if(stopAtNextQuestion && q3->question_attributes.hidden_ == false )
				{
					stopAtNextQuestion = false;  fprintf (qscript_stdout, " at question:  q3 disarming stopAtNextQuestion = false \n");

				}
				if (jumpToQuestion == "q3")
				{
					jumpToQuestion = "";
				}
				label_eval_q3:
				if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q3)
				{
					stopAtNextQuestion = true;
					fprintf (qscript_stdout, " at question:  q3 arming stopAtNextQuestion = true \n");
				}
				else if (q3->question_attributes.hidden_==false)
				{
					// q3->eval(question_window, stub_list_window, data_entry_window);
					last_question_visited = q3;
					fprintf(qscript_stdout, "last_question_visited: q3\n");
					return q3;
				}
			}
			/* ENTER ExpressionStatement::GenerateCode */
			i1 = 2001;
			/* EXIT ExpressionStatement::GenerateCode */
			/* ENTER ExpressionStatement::GenerateCode */
			i2 = 2002;
			/* EXIT ExpressionStatement::GenerateCode */
			/* ENTER ExpressionStatement::GenerateCode */
			i3 = 2003;
			/* EXIT ExpressionStatement::GenerateCode */
			/* ENTER ExpressionStatement::GenerateCode */
			fprintf(qscript_stdout,"after q3: i1:%d , i2:%d, i3:%d\n", i1, i2, i3);fflush(qscript_stdout);
		}

		/*
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
		cout << "End of Questionnaire: (s to save, p = previous question, j = question jump list, q = quit without saving - all newly entered data will be lost)" << endl;
		cin >> end_of_question_navigation;
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
		}
		*/
		reset_questionnaire();
		return 0;
		if (write_qtm_data_file_flag||write_data_file_flag || write_xtcc_data_file_flag)
		{

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
				if (q->loop_index_values.size())
				{
					for (int j=0; j<q->loop_index_values.size(); ++j)
					{
						freq_count_file << "." << q->loop_index_values[j];
						question_name_str << "." << q->loop_index_values[j];
					}
				}
				freq_count_file << endl;
				if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q))
				{
					freq_count_file << "stubs, code, frequency" << endl;
					map<int32_t, int32_t>  q_freq_count = freq_count[question_name_str.str()];
					vector<stub_pair> & vec= (nq->nr_ptr->stubs);
					for (map<int32_t, int32_t>::const_iterator it2 = q_freq_count.begin();
						it2 != q_freq_count.end(); ++ it2)
					{
						for (int i=0; i<vec.size(); ++i)
						{
							if (vec[i].code == it2->first)
							{
								freq_count_file << "\"" << vec[i].stub_text
									<< "\"" << ",";
							}
						}
						freq_count_file << it2->first << ", "
							<< it2->second << endl;
					}
				}
				else
				{
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
			for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i)
			{
				delete qtm_datafile_question_disk_map[i];
				qtm_datafile_question_disk_map[i] = 0;
			}
			for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i)
			{
				delete ascii_flatfile_question_disk_map[i];
				ascii_flatfile_question_disk_map[i] = 0;
			}
		}

	}							 /* close eval */
	void write_data_to_disk(const vector<AbstractQuestion*>& q_vec
		, string jno
		, int32_t ser_no)
	{
		stringstream fname_str;
		fname_str << jno << "_" << ser_no << ".dat";
		//FILE * fptr = fopen(fname_str.str().c_str(), "w+b");

		std::ofstream data_file;
		data_file.exceptions(std::ios::failbit | std::ios::badbit);
		data_file.open(fname_str.str().c_str(), ios_base::ate);

		for(int32_t i = 0; i < question_list.size(); ++i)
		{
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
		for (int32_t i = questions_start_from_here_index; i < question_list.size(); ++i)
		{
			if (question_list[i] == q)
			{
				current_question_index = i;
				break;
			}
		}
		if (current_question_index == -1)
		{
			cerr << "internal compiler error at runtime ... filename: "
				<< __FILE__
				<< "line no: " << __LINE__
				<< endl;
		}
		for (int32_t i = current_question_index-1; i >= 0; --i)
		{
			if (question_list[i]->isAnswered_)
			{
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
		for (int32_t i = 0; i < q->loop_index_values.size(); ++i)
		{
			int32_t tmp1=q->loop_index_values[i];
			for (int32_t j = i+1; j < q->dummyArrayQuestion_->array_bounds.size(); ++j)
			{
				tmp1 *=q->dummyArrayQuestion_->array_bounds[j];
			}
			index+=tmp1;
		}
		//cout << "EXIT ComputeJumpToIndex: returning : " << index << endl;
		return index;
	}
	void reset_questionnaire()
	{
		for(int32_t i = 0; i< question_list.size(); ++i)
		{
			question_list[i]->isAnswered_ = false;
			question_list[i]->input_data.clear();
		}
	}

	int read_a_serial_no()
	{
		//cout << "ENTER: "  << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
		restart:
		struct dirent *directory_entry = readdir(directory_ptr);
		if (directory_entry == NULL)
		{
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
			dir_entry_name[len_entry - 4] == '.')
		{
			if (dir_entry_name.length() < jno.length() + 6
				/* "_1.dat" is the shortest possible datafile name for our study */
				)
			{
				// cannot be our data file
				goto restart;
			}
			bool not_our_file = false;
			for (int i = 0; i < jno.length(); ++i)
			{
				if (!(jno[i] == dir_entry_name[i]))
				{
					// cannot be our data file
					not_our_file = true;
					break;
				}
			}
			if (not_our_file)
			{
				//continue;
				goto restart;
			}
			// all our data files are expected
			// to have a ".dat" ending and '_' after job number
			// find the "."
			cout << dir_entry_name << endl;
			if (dir_entry_name[jno.length()] != '_')
			{
				not_our_file = true;
				//continue;
				goto restart;
			}
			stringstream file_ser_no_str;
			for (int i = jno.length() + 1;
				i < dir_entry_name.length(); ++i)
			{
				if (isdigit(dir_entry_name[i]))
				{
					file_ser_no_str << dir_entry_name[i];
				}
				else
				{
					if ((i + 4 == dir_entry_name.length())
						&& dir_entry_name[i] == '.'
						&& dir_entry_name[i + 1] == 'd'
						&& dir_entry_name[i + 2] == 'a'
						&& dir_entry_name[i + 3] == 't')
					{
						//its most probably our file
						// need to check leading digit is not 0
						break;
					}
					else
					{
						// it's not our file
						not_our_file = true;
						goto restart;
					}
				}
			}
			if (not_our_file)
			{
				goto restart;
			}
			if ((file_ser_no_str.str())[0] == '0')
			{
				// the leading digit of our data file
				// can never be zero - so its not our file
				goto restart;
			}
			cout << "got a data file: " << dir_entry_name << endl;
			int file_ser_no = atoi(file_ser_no_str.str().c_str());
			load_data(jno, file_ser_no);
			merge_disk_data_into_questions2(qscript_stdout, last_question_answered, last_question_visited);
			return file_ser_no;
		}
		else
		{
			// not our data file
			goto restart;
		}
	}

	void DisplayActiveQuestions()
	{
		for(int32_t i = 0; i<question_list.size(); ++i)
		{
			if(question_list[i]->isAnswered_)
				cout << question_list[i]->questionName_ << " ";
		}               cout << endl;

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
		for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i)
		{
			qtm_datafile_question_disk_map[i]->write_data ();
		}
		qtm_datafile_question_disk_map[0]->qtmDataFile_.write_record_to_disk(qtm_disk_file, ser_no);
		qtm_datafile_question_disk_map[0]->qtmDataFile_.Reset();
		//qtm_datafile_question_disk_map[0]->Reset();
		for (int32_t i = 0; i < qtm_datafile_question_disk_map.size(); ++i)
		{
			qtm_datafile_question_disk_map[i]->Reset();
		}
		do_freq_counts();
	}
	void write_ascii_data_to_disk()
	{
		stringstream temp_ser_no_str;
		temp_ser_no_str << ser_no;
		if (temp_ser_no_str.str().length() > ser_no_pos)
		{
			cerr << "space reserved to hold serial no: "
				<< ser_no_pos << " is not enough"
				<< " to hold this serial no: "
				<< ser_no << endl;
			exit(1);
		}
		else
		{
			//char * ptr = flat_file_output_buffer;
			for (int i=0; i<temp_ser_no_str.str().length(); ++i)
			{
				flat_file_output_buffer[i] = temp_ser_no_str.str()[i];
				//cout << "writing digit " << temp_ser_no_str[i] << " to flat_file_output_buffer" << endl;
			}
		}

		for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i)
		{
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
		for (int i=0; i<sizeof(int); ++i)
		{
			*my_data_ptr++ = *char_ptr++;
		}

		for (int i=0; i<xtcc_question_disk_map.size(); ++i)
		{
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
		for (int32_t i = 0; i < question_list.size(); ++i)
		{
			AbstractQuestion * q = question_list[i];
			stringstream question_name_str;
			question_name_str << q->questionName_;
			if (q->loop_index_values.size())
			{
				for (int j=0; j<q->loop_index_values.size(); ++j)
				{
					question_name_str << "." << q->loop_index_values[j];
				}
			}
			map<int , int> q_freq_map = freq_count[question_name_str.str()];
			for (set<int32_t>::iterator it = q->input_data.begin();
				it != q->input_data.end(); ++it)
			{
				q_freq_map[*it] ++;
			}
			freq_count[question_name_str.str()] = q_freq_map;
		}
	}
};
/**
 * Invalid method page.
 */
#define METHOD_ERROR "<html><head><title>Illegal request</title></head><body>Go away.</body></html>"

/**
 * Invalid URL page.
 */
#define NOT_FOUND_ERROR "<html><head><title>Not found</title></head><body>Go away.</body></html>"

/**
 * Last page.
 */
#define LAST_PAGE "<html><head><title>Thank you</title></head><body>Thank you.</body></html>"

#define COOKIE_NAME "session"

struct Request
{
	/**
	 * Associated session.
	 */
	struct Session *session;
	/**
	 * Post processor handling form data (IF this is
	 * a POST request).
	 */
	struct MHD_PostProcessor *pp;
	/**
	 * URL to serve in response to this POST (if this request
	 * was a 'POST')
	 */
	const char *post_url;
};

struct Session
{
	/**
	 * We keep all sessions in a linked list.
	 */
	struct Session *next;
	/**
	 * Unique ID for this session.
	 */
	char sid[33];
	/**
	 * Reference counter giving the number of connections
	 * currently using this session.
	 */
	unsigned int rc;
	/**
	 * Time when this session was last active.
	 */
	time_t start;

	struct TheQuestionnaire * questionnaire;
	char last_question_answered[200];
	char last_question_visited[200];
	char question_response[200];
	char user_navigation[200];
	AbstractQuestion * last_question_served;
	AbstractQuestion * ptr_last_question_answered;
	AbstractQuestion * ptr_last_question_visited;
	Session()
		: start(time(NULL)),
		questionnaire(new TheQuestionnaire()),
		rc(1), last_question_served(0),
		ptr_last_question_answered(0),
		ptr_last_question_visited(0)
	{
		snprintf (sid,
			sizeof (sid),
			"%X%X%X%X",
			(unsigned int) random (),
			(unsigned int) random (),
			(unsigned int) random (),
			(unsigned int) random ());
		memset(last_question_answered, 0, sizeof(last_question_answered));
		memset(last_question_visited, 0, sizeof(last_question_visited));
	}
};

static struct Session *sessions;
vector <Session*> wt_sessions;

static int
post_iterator (void *cls,
enum MHD_ValueKind kind,
const char *key,
const char *filename,
const char *content_type,
const char *transfer_encoding,
const char *data, uint64_t off, size_t size);

int setup_and_run_MHD_daemon();

static struct Session *
get_session (struct MHD_Connection *connection);
static void
request_completed_callback (void *cls,
struct MHD_Connection *connection,
void **con_cls,
enum MHD_RequestTerminationCode toe);

static int
create_response (void *cls,
struct MHD_Connection *connection,
const char *url,
const char *method,
const char *version,
const char *upload_data,
size_t *upload_data_size,
void **ptr);

typedef int (*PageHandler)(const void *cls,
const char *mime,
struct Session *session,
struct MHD_Connection *connection);
struct Page
{
	/**
	 * Acceptable URL for this page.
	 */
	const char *url;

	/**
	 * Mime type to set for the page.
	 */
	const char *mime;

	/**
	 * Handler to call to generate response.
	 */
	PageHandler handler;

	/**
	 * Extra argument to handler.
	 */
	const void *handler_cls;
};
static void
add_session_cookie (struct Session *session,
struct MHD_Response *response);

static int
not_found_page (const void *cls,
const char *mime,
struct Session *session,
struct MHD_Connection *connection);

static int serve_question(struct Session *session,
struct MHD_Connection *connection
);

using namespace Wt;

class QuestionnaireApplication: public WApplication
{
public: 
	QuestionnaireApplication(const WEnvironment &env);
private:
	WText * wt_debug_;
	WText * wt_questionText_;
	WLineEdit * le_data_;
	WText * wt_lastQuestionVisited_;

	WContainerWidget viewPort_;
	WWidget * currentForm_;
	WContainerWidget * formContainer_;

	void display();
	void DoQuestionnaire() ;
	void setCentralWidget(WWidget * new_question_form);
};
bool verify_web_data (std::string p_question_data, 
		UserNavigation p_user_navigation,
		user_response::UserResponseType p_the_user_response,
		std::vector<int> * data_ptr);


void QuestionnaireApplication::DoQuestionnaire()
{
	//if (!wt_questionText_) {
	//	wt_questionText_ = new WText(root());
	//}
	static int counter = 0;
	stringstream s;
	s << "reached DoQuestionnaire: " << counter++;
	wt_debug_->setText(s.str());
	UserNavigation qnre_navigation_mode = NAVIGATE_NEXT;
	string sess_id = sessionId();
	string display_text = string("This is the survey:") + sess_id;
	wt_questionText_->setText(display_text);
	int found_index = -1;
	for (int i=0; i<wt_sessions.size(); ++i) {
		// boy is the below inefficient and should be fixed
		if (sess_id == string(wt_sessions[i]->sid) ) {
			found_index = i;
			break;
		}
	}
	Session * this_users_session = 0;
	if (found_index != -1) {
		s << "found session at index: " << found_index;
		this_users_session = wt_sessions[found_index];
	} else {
		this_users_session = new Session();
		strcpy(this_users_session->sid, sess_id.c_str());
		wt_sessions.push_back(this_users_session);
	}
	// put this code later
	string err_mesg, re_arranged_buffer;
	int32_t pos_1st_invalid_data;
	string last_question_visited_str = wt_lastQuestionVisited_->text().narrow();
	string current_question_response = le_data_->text().narrow();
	s << "last_question_served: " << this_users_session->last_question_served;
	wt_debug_->setText(s.str());
	if (this_users_session->last_question_served) {
		if (last_question_visited_str != "" && current_question_response != "")
		{
			UserNavigation user_nav=NOT_SET;
			user_response::UserResponseType user_resp=user_response::NotSet;
			vector<int32_t> data;
			bool parse_success = verify_web_data (current_question_response, user_nav, user_resp, &data);
			if (parse_success)
			{
				cout << "successfully parsed data = ";
				for (int i=0; i<data.size(); ++i)
				{
					cout << data[i] << ", ";
				}
				cout << endl;
			}
			AbstractQuestion * last_question_served = this_users_session->last_question_served;
			// the call below will be required at some later stage
			//bool valid_input = AbstractQuestion::VerifyResponse(user_resp);
			// right now we go along with the happy path
			bool invalid_code = last_question_served->VerifyData(err_mesg, re_arranged_buffer, pos_1st_invalid_data,
				&data);
			if (invalid_code == false)
			{
				last_question_served->input_data.erase
					(last_question_served->input_data.begin(),
					last_question_served->input_data.end());
				for(uint32_t i = 0; i < data.size(); ++i)
				{
					last_question_served->input_data.insert(data[i]);
					//cout << "storing: " << data[i]
					//	<< " into input_data" << endl;
				}
				last_question_served->isAnswered_ = true;
				data.clear();
			}
		}
	}
	AbstractQuestion * q =
		this_users_session->questionnaire->eval2(
		qnre_navigation_mode);
	this_users_session->last_question_served = q;
	WContainerWidget * new_form = 0;
	if (q) {
		new_form = new WContainerWidget();
		wt_questionText_ = new WText();
		wt_questionText_->setText(q->questionText_);
		new_form->addWidget(wt_questionText_);

		le_data_ = new WLineEdit();
		new_form->addWidget(le_data_);

		wt_lastQuestionVisited_ = new WText();
		if (this_users_session->last_question_answered)
			wt_lastQuestionVisited_->setText(q->questionName_);
		new_form->addWidget(wt_lastQuestionVisited_);

		WPushButton *b = new WPushButton("Next"); // create a button
		b->clicked().connect(this, &QuestionnaireApplication::DoQuestionnaire);
		new_form->addWidget(b);

		setCentralWidget(new_form);
	}


}

void QuestionnaireApplication::setCentralWidget(WWidget * new_question_form)
{
	if (currentForm_)
		delete currentForm_;
	currentForm_ = new_question_form;
	formContainer_->addWidget(currentForm_);
}

#if 0
int32_t main(int argc, char * argv[])
{
	process_options(argc, argv);
	if (write_data_file_flag||write_qtm_data_file_flag)
	{
		qtm_data_file_ns::init_exceptions();
		directory_ptr = opendir(".");
		if (! directory_ptr)
		{
			cout << " unable to open . (current directory) for reading\n";
			exit(1);
		}
	}
	bool using_ncurses = true;
	qscript_stdout = fopen(qscript_stdout_fname.c_str(), "w");
	using namespace std;
	SetupSignalHandler();
	setup_and_run_MHD_daemon();
}
#endif /* 0 */

QuestionnaireApplication::QuestionnaireApplication(const WEnvironment &env)
	: WApplication(env), wt_questionText_(0), currentForm_(0)
{
	WContainerWidget * canvas = new WContainerWidget(0);
	setTitle("QuestionnaireApplication");
	/*
	WPushButton *b = new WPushButton("Click to start survey", root()); // create a button
	b->setMargin(5, Left);                                 // add 5 pixels margin

	root()->addWidget(new WBreak());                       // insert a line break

	wt_questionText_ = new WText(root());                         // empty text

	b->clicked().connect(this, &QuestionnaireApplication::DoQuestionnaire);
	*/
	WPushButton *b = new WPushButton("Click to start survey", canvas); // create a button
	b->setMargin(5, Left);                                 // add 5 pixels margin
	canvas->addWidget(new WBreak());                       // insert a line break
	b->clicked().connect(this, &QuestionnaireApplication::DoQuestionnaire);
	wt_questionText_ = new WText(canvas);                         // empty text
	wt_questionText_->setText("question text will be updated");
	wt_lastQuestionVisited_ = new WText(canvas);
	le_data_ = new WLineEdit(canvas);

	wt_debug_ = new WText(canvas);
	formContainer_ = new WContainerWidget(root());
	formContainer_->addWidget(canvas);
}

WApplication * createApplication(const WEnvironment &env)
{
	return new QuestionnaireApplication (env);
}

int main(int argc, char ** argv)
{
	//process_options(argc, argv);
	if (write_data_file_flag||write_qtm_data_file_flag)
	{
		qtm_data_file_ns::init_exceptions();
		directory_ptr = opendir(".");
		if (! directory_ptr)
		{
			cout << " unable to open . (current directory) for reading\n";
			exit(1);
		}
	}
	bool using_ncurses = true;
	qscript_stdout = fopen(qscript_stdout_fname.c_str(), "w");

	return WRun (argc, argv, &createApplication);
}



#define MHD_PORT_NUMBER     8888
//struct MHD_Daemon * setup_and_run_MHD_daemon()
int setup_and_run_MHD_daemon()
{
	struct MHD_Daemon *d;
	struct timeval tv;
	struct timeval *tvp;
	fd_set rs;
	fd_set ws;
	fd_set es;
	int max;
	unsigned MHD_LONG_LONG mhd_timeout;

	/* initialize PRNG */
	srandom ((unsigned int) time (NULL));
	d = MHD_start_daemon (MHD_USE_DEBUG,
		MHD_PORT_NUMBER,
		NULL, NULL,
		&create_response, NULL,
		MHD_OPTION_CONNECTION_TIMEOUT, (unsigned int) 15,
		MHD_OPTION_NOTIFY_COMPLETED, &request_completed_callback, NULL,
		MHD_OPTION_END);
	if (NULL == d)
		return 1;
	while (1)
	{
		//expire_sessions ();
		max = 0;
		FD_ZERO (&rs);
		FD_ZERO (&ws);
		FD_ZERO (&es);
		if (MHD_YES != MHD_get_fdset (d, &rs, &ws, &es, &max))
			break;				 /* fatal internal error */
		if (MHD_get_timeout (d, &mhd_timeout) == MHD_YES)
		{
			tv.tv_sec = mhd_timeout / 1000;
			tv.tv_usec = (mhd_timeout - (tv.tv_sec * 1000)) * 1000;
			tvp = &tv;
		}
		else
			tvp = NULL;
		select (max + 1, &rs, &ws, &es, tvp);
		MHD_run (d);
	}
	MHD_stop_daemon (d);
	return 0;
}


static void
request_completed_callback (void *cls,
struct MHD_Connection *connection,
void **con_cls,
enum MHD_RequestTerminationCode toe)
{
	struct Request *request = (struct Request *) *con_cls;

	if (NULL == request)
		return;
	if (NULL != request->session)
		request->session->rc--;
	if (NULL != request->pp)
		MHD_destroy_post_processor (request->pp);
	free (request);
}


static int
create_response (void *cls,
struct MHD_Connection *connection,
const char *url,
const char *method,
const char *version,
const char *upload_data,
size_t *upload_data_size,
void **ptr)
{
	struct MHD_Response *response;
	struct Request *request;
	struct Session *session;
	int ret;
	unsigned int i;

	printf("ENTER: %s\n", __PRETTY_FUNCTION__);

	request = (struct Request*) *ptr;
	if (NULL == request)
	{
		printf("func: %s, called the first time creating MHD_create_post_processor\n", __PRETTY_FUNCTION__);
		request = (struct Request *) calloc (1, sizeof (struct Request));
		if (NULL == request)
		{
			fprintf (stderr, "calloc error: %s\n", strerror (errno));
			return MHD_NO;
		}
		*ptr = request;
		if (0 == strcmp (method, MHD_HTTP_METHOD_POST))
		{
			request->pp = MHD_create_post_processor (connection, 1024,
				&post_iterator, request);
			if (NULL == request->pp)
			{
				fprintf (stderr, "Failed to setup post processor for `%s'\n",
					url);
				return MHD_NO;	 /* internal error */
			}
		}
		printf("func: %s, called the first time successfully created a MHD_create_post_processor\n", __PRETTY_FUNCTION__);
		return MHD_YES;
	}
	else
	{
		printf("func: %s post processor already created continuing to handle request\n", __PRETTY_FUNCTION__);
	}
	if (NULL == request->session)
	{
		printf("func: %s, creating a session\n", __PRETTY_FUNCTION__);
		request->session = get_session (connection);
		if (NULL == request->session)
		{
			fprintf (stderr, "Failed to setup session for `%s'\n",
				url);
			return MHD_NO;		 /* internal error */
		}
	}
	session = request->session;
	session->start = time (NULL);
	if (0 == strcmp (method, MHD_HTTP_METHOD_POST))
	{
		/* evaluate POST data */
		printf("func: %s, MHD_HTTP_METHOD_POST\n", __PRETTY_FUNCTION__);
		MHD_post_process (request->pp,
			upload_data,
			*upload_data_size);
		if (0 != *upload_data_size)
		{
			*upload_data_size = 0;
			return MHD_YES;
		}
		/* done with POST data, serve response */
		MHD_destroy_post_processor (request->pp);
		request->pp = NULL;
								 /* fake 'GET' */
		method = MHD_HTTP_METHOD_GET;
		if (NULL != request->post_url)
			url = request->post_url;

		printf("func: %s, done with post processor : requested url is: %s\n"
			, __PRETTY_FUNCTION__, url);
	}

	if ( (0 == strcmp (method, MHD_HTTP_METHOD_GET)) ||
		(0 == strcmp (method, MHD_HTTP_METHOD_HEAD)) )
	{
		/* find out which page to serve */
		/*
		printf("func: %s, url %s\n", __PRETTY_FUNCTION__, url);
		i=0;
		while ( (pages[i].url != NULL) &&
		  (0 != strcmp (pages[i].url, url)) )
		i++;

		printf("i == %d\n", i);
		ret = pages[i].handler (pages[i].handler_cls,
				  pages[i].mime,
				  session, connection);
		*/
		ret = serve_question(session, connection);
		if (ret != MHD_YES)
			fprintf (stderr, "Failed to create page for `%s'\n",
				url);
		return ret;
	}
	/* unsupported HTTP method */
	response = MHD_create_response_from_buffer (strlen (METHOD_ERROR),
		(void *) METHOD_ERROR,
		MHD_RESPMEM_PERSISTENT);
	ret = MHD_queue_response (connection,
		MHD_HTTP_METHOD_NOT_ACCEPTABLE,
		response);
	MHD_destroy_response (response);
	return ret;
}


static int
post_iterator (void *cls,
enum MHD_ValueKind kind,
const char *key,
const char *filename,
const char *content_type,
const char *transfer_encoding,
const char *data, uint64_t off, size_t size)
{
	struct Request *request = (struct Request *) cls;
	struct Session *session = request->session;

	printf("func: %s, key: %s, filename: %s, content_type: %s, transfer_encoding: %s, offset: %ld, size of data avlbl: %ld\n",
		__PRETTY_FUNCTION__, key, filename, content_type, transfer_encoding, off, size);

	if (0 == strcmp ("last_question_answered", key))
	{
		if (size + off > sizeof(session->last_question_answered))
			size = sizeof (session->last_question_answered) - off;
		memcpy (&session->last_question_answered[off],
			data,
			size);
		if (size + off < sizeof (session->last_question_answered))
			session->last_question_answered[size+off] = '\0';
		cout << "post_iterator finished" << endl;
		return MHD_YES;
	}

	if (0 == strcmp ("question_response", key))
	{
		if (size + off > sizeof(session->question_response))
			size = sizeof (session->question_response) - off;
		memcpy (&session->question_response[off],
			data,
			size);
		if (size + off < sizeof (session->question_response))
			session->question_response[size+off] = '\0';
		cout << "question_response : " << session->question_response << endl;
		cout << "post_iterator finished" << endl;
		return MHD_YES;
	}

	if (0 == strcmp ("user_navigation", key))
	{
		if (size + off > sizeof(session->user_navigation))
			size = sizeof (session->user_navigation) - off;
		memcpy (&session->user_navigation[off],
			data,
			size);
		if (size + off < sizeof (session->user_navigation))
			session->user_navigation[size+off] = '\0';
		cout << "user_navigation : " << session->user_navigation << endl;
		cout << "post_iterator finished" << endl;
		return MHD_YES;
	}

	/*
	if (0 == strcmp ("last_question_visited", key))
	{
	if (size + off > sizeof(session->last_question_visited))
	size = sizeof (session->last_question_visited) - off;
	memcpy (&session->last_question_visited[off],
		  data,
		  size);
	if (size + off < sizeof (session->last_question_visited))
	session->last_question_visited[size+off] = '\0';
	return MHD_YES;
	}
	*/

	/* copy current_question to last_question_visited */
	if (0 == strcmp ("current_question", key))
	{
		if (size + off > sizeof(session->last_question_visited))
			size = sizeof (session->last_question_visited) - off;
		memcpy (&session->last_question_visited[off],
			data,
			size);
		if (size + off < sizeof (session->last_question_visited))
			session->last_question_visited[size+off] = '\0';
		cout << "post_iterator finished" << endl;
		return MHD_YES;
	}

	fprintf (stderr, "Unsupported form value `%s'\n", key);
	return MHD_YES;
}


static struct Session *
get_session (struct MHD_Connection *connection)
{
	struct Session *ret;
	const char *cookie;

	cookie = MHD_lookup_connection_value (connection,
		MHD_COOKIE_KIND,
		COOKIE_NAME);
	if (cookie != NULL)
	{
		/* find existing session */
		ret = sessions;
		while (NULL != ret)
		{
			if (0 == strcmp (cookie, ret->sid))
				break;
			ret = ret->next;
		}
		if (NULL != ret)
		{
			ret->rc++;
			return ret;
		}
	}
	/* create fresh session */

	/*
	ret = (struct Session *) calloc (1, sizeof (struct Session));
	ret->questionnaire = new TheQuestionnaire();
	if (NULL == ret)
	  {
		fprintf (stderr, "calloc error: %s\n", strerror (errno));
		return NULL;
	  }
	snprintf (ret->sid,
		  sizeof (ret->sid),
		  "%X%X%X%X",
		  (unsigned int) random (),
		  (unsigned int) random (),
		  (unsigned int) random (),
		  (unsigned int) random ());
	ret->rc++;
	ret->start = time (NULL);
	*/
	ret = new Session();
	ret->next = sessions;
	sessions = ret;
	return ret;
}


static void
add_session_cookie (struct Session *session,
struct MHD_Response *response)
{
	char cstr[256];
	snprintf (cstr,
		sizeof (cstr),
		"%s=%s",
		COOKIE_NAME,
		session->sid);
	if (MHD_NO ==
		MHD_add_response_header (response,
		MHD_HTTP_HEADER_SET_COOKIE,
		cstr))
	{
		fprintf (stderr,
			"Failed to set session cookie header!\n");
	}
}


/*
static int
serve_simple_form (const void *cls,
		   const char *mime,
		   struct Session *session,
		   struct MHD_Connection *connection)
{
  int ret;
  const char *form = (const char *) cls;
  struct MHD_Response *response;

  //  return static form
  response = MHD_create_response_from_buffer (strlen (form),
						  (void *) form,
						  MHD_RESPMEM_PERSISTENT);
  add_session_cookie (session, response);
  MHD_add_response_header (response,
			   MHD_HTTP_HEADER_CONTENT_ENCODING,
			   mime);
  ret = MHD_queue_response (connection,
				MHD_HTTP_OK,
				response);
  MHD_destroy_response (response);
  return ret;
}
*/

static int
not_found_page (const void *cls,
const char *mime,
struct Session *session,
struct MHD_Connection *connection)
{
	int ret;
	struct MHD_Response *response;

	/* unsupported HTTP method */
	response = MHD_create_response_from_buffer (strlen (NOT_FOUND_ERROR),
		(void *) NOT_FOUND_ERROR,
		MHD_RESPMEM_PERSISTENT);
	ret = MHD_queue_response (connection,
		MHD_HTTP_NOT_FOUND,
		response);
	MHD_add_response_header (response,
		MHD_HTTP_HEADER_CONTENT_ENCODING,
		mime);
	MHD_destroy_response (response);
	return ret;
}


#include "qscript_readline.h"

static int serve_question(struct Session *session,
struct MHD_Connection *connection
)
{
	cout << "ENTER: " << __PRETTY_FUNCTION__ << endl;
	UserNavigation qnre_navigation_mode = NAVIGATE_NEXT;
	/*
	if (session->last_question_served == 0) {
		// this is the 1st question we are going to serve
		AbstractQuestion * q =
				session->questionnaire->eval2(last_question_answered, last_question_visited,
								qnre_navigation_mode);
		session->last_question_served = q;
	} else
	*/
	// first check that the response to the previous question is valid

	string err_mesg, re_arranged_buffer;
	int32_t pos_1st_invalid_data;
	string last_question_visited_str = session->last_question_visited;
	string current_question_response = session->question_response;
	if (session->last_question_served)
	{
		if (last_question_visited_str != "" && current_question_response != "")
		{
			UserNavigation user_nav=NOT_SET;
			user_response::UserResponseType user_resp=user_response::NotSet;
			vector<int32_t> data;
			bool parse_success = verify_web_data (current_question_response, user_nav, user_resp, &data);
			if (parse_success)
			{
				cout << "successfully parsed data = ";
				for (int i=0; i<data.size(); ++i)
				{
					cout << data[i] << ", ";
				}
				cout << endl;
			}
			AbstractQuestion * last_question_served = session->last_question_served;
			// the call below will be required at some later stage
			//bool valid_input = AbstractQuestion::VerifyResponse(user_resp);
			// right now we go along with the happy path
			bool invalid_code = last_question_served->VerifyData(err_mesg, re_arranged_buffer, pos_1st_invalid_data,
				&data);
			if (invalid_code == false)
			{
				last_question_served->input_data.erase
					(last_question_served->input_data.begin(),
					last_question_served->input_data.end());
				for(uint32_t i = 0; i < data.size(); ++i)
				{
					last_question_served->input_data.insert(data[i]);
					//cout << "storing: " << data[i]
					//	<< " into input_data" << endl;
				}
				last_question_served->isAnswered_ = true;
				data.clear();
			}
		}
	}
	AbstractQuestion * q =
								 /*session->ptr_last_question_answered, session->ptr_last_question_visited,*/
		session->questionnaire->eval2(
		qnre_navigation_mode);
	session->last_question_served = q;
	label_ask_again:
	stringstream question_form;

	cout << "last_question_visited == " << last_question_visited_str << endl;
	cout << "current_question_response == " << current_question_response << endl;

	question_form << "<html><head><title>"
		<< "Questionnaire: " << session->questionnaire->jno
		<< "</title>\n";
	//question_form << "<script type=\"text/javascript\" src=\"event_util.js\" ></script>\n";
	fstream event_js_file("event_util.js", ios_base::in);
	string event_js_file_contents;
	stringstream event_js_file_contents_str;
	cout << "reading file: event_js_file" << endl;
	while (getline (event_js_file, event_js_file_contents) )
	{
		// cout << "contents: " << event_js_file_contents << endl;
		event_js_file_contents_str << event_js_file_contents << endl;
	}

	question_form << "<script type=\"text/javascript\" >\n";
	question_form << event_js_file_contents_str.str().c_str() << endl;
	question_form << "</script>\n";

	question_form << "</head>\n<body>\n";
	question_form << "\t<form action=\"" << q->questionName_
		<< "\" method=\"post\">\n"
		<< q->questionName_ << ".";
	for(int32_t i = 0; i< q->loop_index_values.size(); ++i)
	{
		question_form << "." << q->loop_index_values[i];
	}

	question_form << q->questionText_
		<< endl;
	question_form
		<< "\t\t<input type=\"text\" name=\"question_response\""
		<< "value=\""
	// put the value here later
		<< "\" />\n";

	question_form << "<p>";

	question_form
	// << "\t\t<input type=\"hidden\" name=\"last_question_answered\" ";
		<< "\t\t last_question_answered: <input type=\"text\" name=\"last_question_answered\" ";
	/*
	if (session->last_question_answered) {
		question_form
			<< " value=\""
			<< last_question_answered->questionName_
			<< "\"";
	} else {
		question_form
			<< " value=\""
			<< "\"";
	}
	*/
	question_form << "value =\"" << session->last_question_answered
		<< "\""
		<< " />\n";

	question_form
		<< "\t\t last_question_visited: <input type=\"text\" name=\"last_question_visited\" ";
	/*
	if (session->last_question_visited) {
		question_form
			<< " value=\""
			<< last_question_visited->questionName_
			<< "\"";
	} else {
		question_form
			<< " value=\""
			<< "\"";
	}
	*/
	question_form << "value =\"" << session->last_question_visited
		<< "\""
		<< " />\n";

	question_form
		<< "\t\t current_question: <input type=\"text\" name=\"current_question\" ";
	question_form << "value =\"" << q->questionName_;

	for (int i=0; i<q->loop_index_values.size(); ++i)
	{
		question_form << "$" << q->loop_index_values[i];
	}
	question_form
		<< "\""
		<< " />\n";

	question_form << "		user_navigation: <input type=\"text\" name=\"user_navigation\" value =\"\" /> " << endl;
	question_form << "		<input type=\"button\" value=\"Previous\" name=\"prev_button\" id=\"prev_button\" /> " << endl;
	question_form << "		<input type=\"button\" value=\"Next\" name=\"next_button\" id=\"next_button\" /> " << endl;
	question_form << "		<input type=\"button\" id=\"form_button\" value=\"button\" />" << endl;

	question_form << "	<script type=\"text/javascript\">\n";
	question_form << "	var form = document.forms[0];\n";
	question_form << "	var form_button = form.elements[\"form_button\"];\n";
	question_form << "	//var form_button = document.getElementById(\"form_button\");\n";
	question_form << "	//alert ('form_button' +  form_button);\n";
	question_form << "	var handler = function () {\n";
	question_form << "		//alert(\"handler executed on click\");\n";
	question_form << "		var user_navigation = form.elements[\"user_navigation\"];\n";
	question_form << "		user_navigation.value = \"previous\";\n";
	question_form << "	}\n";
	question_form << "	EventUtil.addHandler(form_button, \"click\", handler);\n";
	question_form << "	//alert(\"added handler to button\");\n";
	question_form << "	// the real stuff I want to do goes here\n";
	question_form << "	// 1. when user clicks button previous \n";
	question_form << "	//    set user_navigation to previous\n";
	question_form << "	//    and submit the form\n";
	question_form << "	var prev_button = form.elements[\"prev_button\"]\n";
	question_form << "	var handle_prev = function() {\n";
	question_form << "		var user_navigation = form.elements[\"user_navigation\"];\n";
	question_form << "		user_navigation.value = \"previous\";\n";
	question_form << "		prev_button.disabled = true;\n";
	question_form << "		next_button.disabled = true;\n";
	question_form << "		form.submit();\n";
	question_form << "	}\n";
	question_form << "	EventUtil.addHandler(prev_button, \"click\", handle_prev);\n";
	question_form << "\n";
	question_form << "	// 2. when user clicks button next\n";
	question_form << "	//    set user_navigation to next\n";
	question_form << "	//    and submit the form\n";
	question_form << "	var next_button = form.elements[\"next_button\"]\n";
	question_form << "	var handle_next = function(event) {\n";
	question_form << "		var user_navigation = form.elements[\"user_navigation\"];\n";
	question_form << "		user_navigation.value = \"next\";\n";
	question_form << "		prev_button.disabled = true;\n";
	question_form << "		next_button.disabled = true;\n";
	question_form << "		//event = EventUtil.getEvent(event);\n";
	question_form << "		//EventUtil.preventDefault(event);\n";
	question_form << "		form.submit();\n";
	question_form << "	}\n";
	question_form << "	EventUtil.addHandler(next_button, \"click\", handle_next);\n";
	question_form << "	</script>\n";
	question_form << "\n";

	question_form << "\n</body></html>\n";
	struct MHD_Response * response  = MHD_create_response_from_buffer(question_form.str().length(),
		(void *) question_form.str().c_str(),
		MHD_RESPMEM_MUST_COPY);
	add_session_cookie (session, response);
	const char * mime = "text/html";
	MHD_add_response_header (response,
		MHD_HTTP_HEADER_CONTENT_ENCODING,
		mime);
	int ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
	MHD_destroy_response (response);

	cout << "EXIT: " << __PRETTY_FUNCTION__ << endl;
	return ret;
}


static void sig_usr(int32_t signo)
{
	if(signo == SIGSEGV)
	{
		printf("received SIGSEGV\n");
	}
	else if(signo == SIGILL)
	{
		printf("received SIGILL\n");
	}
	else
	{
		fprintf(stderr, "received signal : %d\n", signo);
	}
	fflush(qscript_stdout);
	exit(1);
}


void SetupSignalHandler()
{
	if(signal(SIGSEGV, sig_usr) == SIG_ERR)
	{
		fprintf(stderr, "cannot catch SIGSEGV\n");
		exit(1);
	}
	else if(signal(SIGILL, sig_usr) == SIG_ERR)
	{
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
	while ( (c = getopt(argc, argv, "x::w::q::")) != -1)
	{
		char ch = optopt;
		switch (c)
		{
			case 'w':
			{
				write_data_file_flag = true;
				if (optarg)
				{
					output_data_file_name = optarg;
				}
				else
				{
					output_data_file_name = "datafile.dat";
				}
			}
			break;
			case 'x':
			{
				write_xtcc_data_file_flag = true;
				if (optarg)
				{
					output_xtcc_data_file_name = optarg;
				}
				else
				{
					output_xtcc_data_file_name = "xtcc_datafile.dat";
				}
			}
			break;
			case 'q':
			{
				write_qtm_data_file_flag = true;
				if (optarg)
				{
					output_qtm_data_file_name = optarg;
				}
				else
				{
					output_qtm_data_file_name = "qtm_datafile.dat";
				}
			}
			break;
			case '?' :
			{
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
