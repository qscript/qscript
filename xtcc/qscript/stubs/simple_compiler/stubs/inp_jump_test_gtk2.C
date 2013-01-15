#include <locale.h>
#include <libintl.h>
#include <gtk/gtk.h>
#ifdef _WIN32
#define random rand
#define srandom srand
#endif							 /*  _WIN32*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <errno.h>
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
#include "named_attributes.h"
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
//vector <AbstractQuestion*> question_list;
vector<mem_addr_tab>  mem_addr;
//extern vector<question_disk_data*>  qdd_list;
bool write_data_file_flag;
bool write_qtm_data_file_flag;
bool write_messages_flag;
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
void load_languages_available(vector<string> & vec_language);
//int SetupGTK (int argc, char * argv[]);
string GenerateSessionId();

int process_options(int argc, char * argv[]);
DIR * directory_ptr = 0;
vector <string> vec_language;
enum UI_Mode { NCurses_Mode, Microhttpd_Mode, Wt_Mode, Gtk_Mode};
struct TheQuestionnaire
{
	AbstractQuestion * last_question_answered;
	AbstractQuestion * last_question_visited;
	vector <AbstractQuestion*> question_list;
	fstream messages;
	bool back_jump;
	string jno;
	int ser_no;
	bool stopAtNextQuestion;
	int32_t questions_start_from_here_index;
	int ser_no_pos;
	string jumpToQuestion;
	int32_t jumpToIndex;
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
		if (write_messages_flag)
		{
			messages.open ("inp_jump_test.xml", ios_base::out|ios_base::trunc);
			if(!messages) { cerr << "unable to open file for output of messages... exiting\n"; exit(1); }
			messages << "<?xml version=\"1.0\" encoding=\"UTF8\"?>\n";
			messages << "<messages>\n"; messages << "  <message id=\"thank_you\">The Survey is now complete. Thank You for your time.</message>\n";
		}
		xs_0.indiv.insert(11);
		xs_0.indiv.insert(16);
		xs_0.range.push_back(pair<int32_t,int32_t>(5,8));
		xs_0.range.push_back(pair<int32_t,int32_t>(1,2));
		xs_0.range.push_back(pair<int32_t,int32_t>(9,10));
		{
			vector<TextExpression *> text_expr_vec;
			text_expr_vec.push_back(new TextExpression(string(gettext("Q1. "))));
			text_expr_vec.push_back(new TextExpression(string(gettext(" Part 2"))));
			q1 = new RangeQuestion(QUESTION_TYPE, 7,string( "q1"), text_expr_vec,spn,1,INT32_TYPE,xs_0, QuestionAttributes(false , false), true);
			print_question_messages(q1);
		}
		xs_1.indiv.insert(1);
		xs_1.indiv.insert(2);
		xs_1.indiv.insert(3);
		xs_1.indiv.insert(4);
		{
			vector<TextExpression *> text_expr_vec;
			text_expr_vec.push_back(new TextExpression(string(gettext("Q2. "))));
			q2 = new RangeQuestion(QUESTION_TYPE, 15,string( "q2"), text_expr_vec,spn,1,INT32_TYPE,xs_1, QuestionAttributes(false , false), false);
			print_question_messages(q2);
		}
		xs_2.indiv.insert(5);
		xs_2.indiv.insert(6);
		{
			vector<TextExpression *> text_expr_vec;
			text_expr_vec.push_back(new TextExpression(string(gettext("Q3. "))));
			q3 = new RangeQuestion(QUESTION_TYPE, 19,string( "q3"), text_expr_vec,spn,1,INT32_TYPE,xs_2, QuestionAttributes(false , false), false);
			print_question_messages(q3);
		}

		questions_start_from_here_index = question_list.size();
		question_list.push_back(q1);
		print_question_messages(q1);
		question_list.push_back(q2);
		print_question_messages(q2);
		question_list.push_back(q3);
		print_question_messages(q3);

		compute_flat_file_map_and_init();
		if (write_messages_flag)
		{
			messages << "</messages>\n";
		}
	}

	void print_question_messages(AbstractQuestion * q)
	{
		stringstream question_name;
		question_name << q->questionName_;
		for (int i=0; i< q->loop_index_values.size(); ++i)
		{
			question_name << "_" << q->loop_index_values[i];
		}
		for (int i=0; i< q->textExprVec_.size(); ++i)
		{
			messages << "<message id=\"" << question_name.str()
				<< "_" << i << "\">"
				<< q->textExprVec_[i]->text_
				<< "</message>\n" << endl;
		}
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
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 5 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_top2" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 5 << ", " << 4 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_bot" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_bot2" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ", " << 2 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_mn" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
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
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 7 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_top2" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 7 << ", " << 6 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_top3" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 5 << ":" << 7 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_bot" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_bot2" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ", " << 2 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_mn" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << mean_score_include_file
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ":" << 7 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_bot3" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
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
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 10 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_top2" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 10 << ", " << 9 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_top3" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 8 << ":" << 10 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_bot" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_bot2" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << include_file_name
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ", " << 2 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_mn" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
					for (int i=0; i<v.size(); ++i)
					{
						qtm_qax_file << "*include " << mean_score_include_file
							<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
							<< ";myrange=(" << 1 << ":" << 10 << ")"
							<< endl;
					}

					qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
					qtm_qax_file << "l " << q->questionName_ << "_bot3" << endl;
					qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
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
				qtm_qax_file << "/*ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
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
		//if (last_question_visited)
		//fprintf (qscript_stdout, "entered eval2: last_question_visited: %s, stopAtNextQuestion: %d\n", last_question_visited->questionName_.c_str(), stopAtNextQuestion);
		/*
		if (write_data_file_flag||write_qtm_data_file_flag||write_xtcc_data_file_flag) {
			ser_no = read_a_serial_no();
			if (ser_no == 0) {
				exit(1);
			}
		} else {
			int exists = check_if_reg_file_exists(jno, ser_no);
			if (exists == 1) {
				map <string, question_disk_data*>  qdd_map;
				load_data (jno, ser_no, &qdd_map);
				//merge_disk_data_into_questions(qscript_stdout, last_question_answered, last_question_visited);
				merge_disk_data_into_questions2 (qscript_stdout, last_question_answered, last_question_visited, this->question_list, &qdd_map);
			}
		}

		*/
		start_of_questions:
		if(back_jump == true)
		{
			//fprintf(qscript_stdout, "have reached start_of_questions with back_jump: jumpToQuestion: %s, jumpToIndex: %d\n", jumpToQuestion.c_str(), jumpToIndex);
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
			//if (data_entry_window == 0) cout << "target question: " << jumpToQuestion;
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
		//reset_questionnaire();
		return 0;
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
			map <string, question_disk_data*>  qdd_map;
			load_data(jno, file_ser_no, &qdd_map);
			merge_disk_data_into_questions2(qscript_stdout, last_question_answered, last_question_visited, this->question_list, &qdd_map);
			for (map<string, question_disk_data*>:: iterator it
				= qdd_map.begin();
				it != qdd_map.end();
				++it)
			{
				delete it->second;
			}
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
struct Session
{
	/**
	 * We keep all sessions in a linked list.
	 */
	struct Session *next;
	/**
	 * Unique ID for this session.
	 */
	char sid[50];
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
	~Session()
	{
		delete questionnaire;
		questionnaire = 0;
	}
};

static struct Session *sessions;
vector <Session*> wt_sessions;
class GtkQuestionnaireApplication;

struct GtkRadioButtonData
{
	int selectedCode_;
	GtkQuestionnaireApplication * qApp_;
	GtkRadioButtonData (int data, GtkQuestionnaireApplication * p_qapp)
		: selectedCode_ (data), qApp_ (p_qapp)
		{ }
};

class GtkQuestionnaireApplication
{
	public:
		GtkWidget * window , * top_half , * bottom_half ;
		GtkQuestionnaireApplication (int argc, char * argv[]);
		void setupGTK (int argc, char * argv[]);
		int rb_selected_code;
	private:
		GtkWidget * wt_debug_;
		GtkWidget * wt_questionText_;
		GtkWidget * le_data_;
		GtkWidget * wt_lastQuestionVisited_;
		GtkWidget * wt_cb_rb_container_;
		GtkWidget * wt_rb_container_;

		GtkWidget * questionTextLabel_;

		vector<GtkWidget*> vec_rb;
		vector<GtkRadioButtonData*> rbData_;
		vector<GtkWidget*> vec_cb;
		std::map<int, int> map_cb_code_index;
		std::vector<GtkWidget *> languageSelects_;

		GtkWidget *vbox , *hbox ;
		GtkWidget * entry ;
		//GtkWidget * button ;
		GtkWidget * check ;
		GtkWidget * rb ;
		GtkWidget * next_button ;

		GtkWidget * viewPort_;
		GtkWidget * currentForm_;
		GtkWidget * formContainer_;
		GSList * gtkRadioButtonGroup_;

		GtkWidget * bottomHalfVBox_, * bottomHalfNavigationBox_;

		int ser_no;
		GtkWidget * serialPage_;
		bool flagSerialPageRemoved_;
		Session * this_users_session;
		string sess_id ;

		void display();
		void changeLanguage();
		void setLanguage(const std::string lang);
		void ConstructQuestionForm(
			AbstractQuestion *q, Session * this_users_session);
		void ConstructThankYouPage();
		const char * software_info();
		void CreateBottomHalf();
		void DestroyPreviousWidgets ();
	public:
		void DoQuestionnaire() ;
		void ValidateSerialNo();
		//virtual ~GtkQuestionnaireApplication();
		void get_serial_no_gtk ();
};

void GtkQuestionnaireApplication::DestroyPreviousWidgets ()
{
	cout << __PRETTY_FUNCTION__ << endl;
	if (questionTextLabel_)
	{
		gtk_widget_destroy (questionTextLabel_) ;
		questionTextLabel_ = 0;
	}
	if (vec_rb.size() > 0)
	{
		// put clear / destroy previous widget code here
		for (int i=0; i<vec_rb.size(); ++i)
		{
			gtk_widget_destroy (vec_rb[i]);
		}
		vec_rb.clear();
	}
	if (vec_cb.size() > 0)
	{
		// put clear / destroy previous widget code here
		for (int i=0; i<vec_cb.size(); ++i)
		{
			gtk_widget_destroy (vec_cb[i]);
		}
		vec_cb.clear();
	}
	if (next_button)
	{
		gtk_widget_destroy (next_button);
		next_button = 0;
	}
	if (le_data_)
	{
		gtk_widget_destroy (le_data_);
		le_data_ = 0;
	}
}


gint delete_event (GtkWidget *widget, GdkEvent *event, gpointer data)
{
	/*
	 *
	 *
	 *
	 *
	If you return FALSE in the "delete_event" signal handler,
	GTK will emit the "destroy" signal. Returning TRUE means
	you dont want the window to be destroyed.
	This is useful for popping up are you sure you want to quit?
	type dialogs. */
	g_print ("delete event occurred\n");
	/* Change TRUE to FALSE and the main window will be destroyed with
	 * a "delete_event". */
	return FALSE;
}


/* Anothe callback */
void destroy( GtkWidget *widget, gpointer data )
{
	gtk_main_quit ();
}


GtkWidget * CreateTopHalf()
{
	GtkWidget * scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
		GTK_POLICY_AUTOMATIC,
		GTK_POLICY_AUTOMATIC);
	return scrolled_window;
}


void GtkQuestionnaireApplication::CreateBottomHalf()
{
	//GtkWidget *scrolled_window;
	//GtkWidget *view;
	//GtkTextBuffer *buffer;
	//view = gtk_text_view_new ();
	//buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
	bottom_half = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (bottom_half),
		GTK_POLICY_AUTOMATIC,
		GTK_POLICY_AUTOMATIC);
	//gtk_container_add (GTK_CONTAINER (scrolled_window), view);
	bottomHalfVBox_ = gtk_vbox_new (FALSE, 0);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (bottom_half), bottomHalfVBox_);
	gtk_widget_show (bottomHalfVBox_);
	//insert_text (buffer);
	gtk_widget_show_all (bottom_half);
	//return scrolled_window;
	bottomHalfNavigationBox_ = gtk_vbox_new (FALSE, 0);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (bottom_half), bottomHalfNavigationBox_);
	gtk_widget_show (bottomHalfNavigationBox_);
}


GtkQuestionnaireApplication::GtkQuestionnaireApplication (int argc, char * argv[])
{
	setupGTK (argc, argv);
}


void GtkQuestionnaireApplication::setupGTK (int argc, char * argv[])
{
	questionTextLabel_ = 0;
	next_button = 0;
	le_data_ = 0;
	gtk_init (&argc, &argv);
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Paned Windows");
	/* Sets the border width of the window. */
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	gtk_widget_set_size_request (GTK_WIDGET (window), 800, 600);
	g_signal_connect (G_OBJECT (window), "delete_event",
		G_CALLBACK (delete_event), NULL);
	/* Here we connect the "destroy" event to a signal handler.
	 * This event occurs when we call gtk_widget_destroy() on the window,
	 * or if we return FALSE in the "delete_event" callback. */
	g_signal_connect (G_OBJECT (window), "destroy",
		G_CALLBACK (destroy), NULL);
	// ============================
	/* create a vpaned widget and add it to our toplevel window */
	GtkWidget * vpaned = gtk_vpaned_new ();
	gtk_container_add (GTK_CONTAINER (window), vpaned);
	gtk_widget_show (vpaned);
	/* Now create the contents of the two halves of the window */
	/* GtkWidget *  */ top_half = CreateTopHalf ();
	gtk_paned_add1 (GTK_PANED (vpaned), top_half);
	gtk_widget_show (top_half);
	/*  GtkWidget *   bottom_half =*/ CreateBottomHalf ();
	gtk_paned_add2 (GTK_PANED (vpaned), bottom_half);
	gtk_widget_show (bottom_half);
	gtk_widget_show (window);
	// ============================
	get_serial_no_gtk();

	// Setup the session
	string sess_id = GenerateSessionId();
	this_users_session = new Session();
	strcpy (this_users_session->sid, sess_id.c_str());
	wt_sessions.push_back(this_users_session);
}


void enter_callback (GtkWidget *widget, GtkQuestionnaireApplication * qapp)
{
	const gchar *entry_text;
	entry_text = gtk_entry_get_text (GTK_ENTRY (widget));
	printf("Entry contents: %s\n", entry_text);

	qapp->ValidateSerialNo ();
	//theQuestionnaire.eval();
}


void line_edit_callback (GtkWidget *widget, GtkQuestionnaireApplication * qapp)
{
	const gchar *entry_text;
	entry_text = gtk_entry_get_text (GTK_ENTRY (widget));
	printf("Entry contents: %s\n", entry_text);

	//theQuestionnaire.eval();
}


void GtkQuestionnaireApplication::get_serial_no_gtk ()
{
	printf ("called: %s\n", __PRETTY_FUNCTION__);
	gint tmp_pos;

	vbox = gtk_vbox_new (FALSE, 0);
	//gtk_container_add (GTK_CONTAINER (top_half), vbox);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (top_half), vbox);
	gtk_widget_show (vbox);

	entry = gtk_entry_new ();
	gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
	g_signal_connect (G_OBJECT (entry), "activate",
		G_CALLBACK (enter_callback),
		(gpointer) this);
	gtk_entry_set_text (GTK_ENTRY (entry), "hello");
	tmp_pos = GTK_ENTRY (entry)-> text_length;
	gtk_editable_insert_text (GTK_EDITABLE (entry), " world", -1, &tmp_pos);
	gtk_editable_select_region (GTK_EDITABLE (entry),
		0, GTK_ENTRY (entry)-> text_length);
	gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
	gtk_widget_show (entry);

}


void GtkQuestionnaireApplication::ValidateSerialNo()
{
	int l_ser_no = -1;
	const gchar * entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
	string narrow_text (entry_text);
	if (narrow_text.length() == 0 || narrow_text.length() > 7)
	{
		//le_data_->setText("You have entered a very long serial number");
	}
	else
	{
		l_ser_no = strtol (narrow_text.c_str(), 0, 10);
		if (l_ser_no > 0)
		{
			ser_no = l_ser_no;
			this_users_session->questionnaire->ser_no = l_ser_no;
			int exists = check_if_reg_file_exists (jno, ser_no);
			cout << "checking if serial no : " << ser_no
				<< ", jno: " << jno << " exists: " << exists << endl;

			if(exists == 1)
			{
				map <string, question_disk_data*>  qdd_map;
				load_data(jno, ser_no, &qdd_map);
				merge_disk_data_into_questions2(qscript_stdout,
					this_users_session->questionnaire->last_question_answered,
					this_users_session->questionnaire->last_question_visited,
					this_users_session->questionnaire->question_list,
					&qdd_map);
				for (map<string, question_disk_data*>:: iterator it
					= qdd_map.begin();
					it != qdd_map.end();
					++it)
				{
					delete it->second;
				}
			}
			DoQuestionnaire();
		}
		else
		{
			//le_data_->setText("You have entered a  negative number");
		}
	}
}


string GenerateSessionId()
{
	srand(time(0));
	char buffer[50];
	sprintf (buffer, "%010d%010d%010d%010d", rand(), rand(), rand(), rand());
	return string(buffer);
}


bool verify_web_data (std::string p_question_data,
UserNavigation p_user_navigation,
user_response::UserResponseType p_the_user_response,
std::vector<int> * data_ptr);
void GtkQuestionnaireApplication::DoQuestionnaire()
{
	//if (!wt_questionText_) {
	//	wt_questionText_ = new WText(root());
	//}
	cout << "Data for ser_no: " << ser_no << endl;
	for(int32_t i = 0; i < this_users_session->questionnaire->question_list.size(); ++i)
	{
		cout << this_users_session->questionnaire->question_list[i]->questionName_;
		for( set<int32_t>::iterator iter = this_users_session->questionnaire->question_list[i]->input_data.begin();
			iter != this_users_session->questionnaire->question_list[i]->input_data.end(); ++iter)
		{
			cout << " " << *iter;
		}
		cout << "\n";
	}
	static int counter = 0;
	stringstream s;
	s << "reached DoQuestionnaire: " << counter++;
	//wt_debug_->setText(s.str());
	UserNavigation qnre_navigation_mode = NAVIGATE_NEXT;
	//string display_text = string("Session Id:") + sess_id;
	//wt_questionText_->setText(display_text);
	// put this code later
	string err_mesg, re_arranged_buffer;
	int32_t pos_1st_invalid_data;
	if (this_users_session->last_question_served)
		s << "last_question_served: " << this_users_session->last_question_served->questionName_ ;
	cout << s.str() << endl;
	//wt_debug_->setText(s.str());
	if (this_users_session->last_question_served)
	{
		if (NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion *>(this_users_session->last_question_served))
		{
			AbstractQuestion * last_question_served = this_users_session->last_question_served;
			vector<int32_t> data;
			bool isAnswered = false;
			cout << "returned back data from question: " << nq->questionName_ << endl;
			if (last_question_served->no_mpn == 1)
			{
				if (rb_selected_code != -1)
				{
					isAnswered = true;
					//int code = wt_rb_container_->checkedId();
					cout << "no_mpn == 1, code: " << rb_selected_code << endl;
					data.push_back(rb_selected_code);
				}
				else
				{
					isAnswered = false;
				}
			}
			else
			{
				cout << " vec_cb.size(): " << vec_cb.size() << "no_mpn > 1" << endl;
				for (int i = 0; i < vec_cb.size(); ++i)
				{
					//if (vec_cb[i]->checkState() == Wt::Checked)
					//{
					//	int code = map_cb_code_index[i];
					//	data.push_back(code);
					//	cout << "vec_cb[" << i << "] is checked,   code: " << code << endl;
					//	isAnswered = true;
					//}
					if (gtk_toggle_button_get_active ((GtkToggleButton *) vec_cb[i]) )
					{
						int code = map_cb_code_index[i];
						data.push_back(code);
						isAnswered = true;
						cout << "button is toggled: " << code << endl;
					}
				}
			}
			if (isAnswered)
			{
				bool invalid_code = last_question_served->VerifyData(err_mesg, re_arranged_buffer, pos_1st_invalid_data,
					&data);
				if (invalid_code == false)
				{
					//last_question_served->input_data.erase
					//	(last_question_served->input_data.begin(),
					//	last_question_served->input_data.end());
					last_question_served->input_data.clear();
					for(uint32_t i = 0; i < data.size(); ++i)
					{
						last_question_served->input_data.insert(data[i]);
						cout << "storing: " << data[i]
							<< " into input_data" << endl;
					}
					last_question_served->isAnswered_ = true;
					data.clear();
				}
			}
			// do something with isAnswered_ == false here and resend the
			// qnre to the respondent
		}
		else
		{

			const gchar *entry_text = gtk_entry_get_text (GTK_ENTRY (le_data_));
			string last_question_served_response (entry_text);
			AbstractQuestion * last_question_served = this_users_session->last_question_served;
			if (/* last_question_visited_str != "" &&  */ last_question_served_response != "" && last_question_served->no_mpn==1)
			{
				UserNavigation user_nav=NOT_SET;
				user_response::UserResponseType user_resp=user_response::NotSet;
				vector<int32_t> data;
				bool parse_success = verify_web_data (last_question_served_response, user_nav, user_resp, &data);
				if (parse_success)
				{
					cout << "successfully parsed data = ";
					for (int i=0; i<data.size(); ++i)
					{
						cout << data[i] << ", ";
					}
					cout << endl;
				}
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
				else
				{
					ConstructQuestionForm(last_question_served, this_users_session);
					return;
				}
			}
			else if (/* last_question_visited_str != "" &&  */ last_question_served_response != "" && last_question_served->no_mpn > 1)
			{
				//string utf8_response = le_data_->text().toUTF8();
				if (last_question_served_response != "")
				{
					stringstream file_name_str;
					file_name_str << last_question_served->questionName_ << "."
						<< jno << "_" << ser_no << ".dat";

					fstream open_end_resp(file_name_str.str().c_str(), ios_base::out|ios_base::ate);
					open_end_resp << last_question_served_response << endl;
					last_question_served->input_data.insert(96);
					last_question_served->isAnswered_ = true;
				}
				else
				{
					ConstructQuestionForm(last_question_served, this_users_session);
					return;
				}
			}
		}
	}
	{
		TheQuestionnaire * qnre = this_users_session->questionnaire;
		qnre->write_data_to_disk(qnre->question_list, qnre->jno, qnre->ser_no);
	}
	AbstractQuestion * q =
		this_users_session->questionnaire->eval2(
		qnre_navigation_mode);
	this_users_session->last_question_served = q;
	if (q)
	{
		ConstructQuestionForm(q, this_users_session);
	}
	else
	{
		//TheQuestionnaire * qnre = this_users_session->questionnaire;
		//qnre->write_data_to_disk(qnre->question_list, qnre->jno, qnre->ser_no);
		//ConstructThankYouPage();
		cout << "End of qnre" << endl;
	}
}


void next_button_callback (GtkWidget *widget, GtkQuestionnaireApplication * qapp)
{
	//g_print ("Next button was pressed", (char *) data);
	qapp->DoQuestionnaire();
}


void toggle_rb_button_event (GtkWidget *widget, GtkRadioButtonData * rb_data)
{
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
	{
		/* If control reaches here, the toggle button is down */
		rb_data->qApp_->rb_selected_code  = rb_data -> selectedCode_;
	}
	else
	{
		/* If control reaches here, the toggle button is up */
	}
	g_print ("Toggle event occured %d",  rb_data -> selectedCode_);
}


void GtkQuestionnaireApplication::ConstructQuestionForm(
AbstractQuestion *q, Session * this_users_session)
{
	map_cb_code_index.clear();
	//WContainerWidget * new_form = new WContainerWidget();
	//vec_rb.clear();				 // memory leak introduced here? no it seems
	//vec_cb.clear();				 // memory leak introduced here? no it seems
	//map_cb_code_index.clear();

	//wt_questionText_ = new WText();
	//wt_questionText_->setText(q->textExprVec_[0]->text_);
	string question_text;
	stringstream part_mesg_id;
	//WString question_text;
	part_mesg_id << q->questionName_;
	for (int i=0; i<q->loop_index_values.size(); ++i)
	{
		part_mesg_id << "_" << q->loop_index_values[i];
	}
	//WText * wt_questionNo_ = new WText(part_mesg_id.str().c_str(), new_form);
	for (int i=0; i<q->textExprVec_.size(); ++i)
	{
		//question_text += "<p>";
		if (q->textExprVec_[i]->teType_ == TextExpression::simple_text_type)
		{
			stringstream mesg_id;
			mesg_id << part_mesg_id.str() << "_" << i;
			//question_text += string (gettext(mesg_id.str().c_str()));
			question_text += string (gettext(q->textExprVec_[0]->text_.c_str()));
		}
		else if (q->textExprVec_[i]->teType_ == TextExpression::named_attribute_type)
		{
			//stringstream named_attribute_key;
			//named_attribute_key << q->textExprVec_[i]->naPtr_->name;
			//named_attribute_key << "_" << q->textExprVec_[i]->naIndex_;
			//question_text += string(gettext(named_attribute_key.str().c_str()));
			question_text += string(" FIXME : BUG that I didnt notice. Need to create a map of <string, named_attribute_list>   to solve this problem, where the first string is the name of the named_attribute_list");
		}
		else if (q->textExprVec_[i]->teType_ == TextExpression::question_type)
		{
			if (q->textExprVec_[i]->codeIndex_ != -1)
			{
				question_text += q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers(q->textExprVec_[i]->codeIndex_);
			}
			else
			{
				question_text += q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers();
			}
		}
		//question_text += "</p>";
	}
	#if 0
	wt_questionText_->setText(question_text);

	new_form->addWidget(wt_questionText_);
	if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q))
	{
		new_form->addWidget(wt_cb_rb_container_ = new WGroupBox());
		if (q->no_mpn==1)
		{
			wt_rb_container_ = new WButtonGroup(wt_cb_rb_container_);
		}
		vector<stub_pair> & vec= (nq->nr_ptr->stubs);
		for (int i=0; i<vec.size(); ++i)
		{
			stringstream named_range_key;
			named_range_key << nq->nr_ptr->name << "_" << i;
			if (q->no_mpn==1 && vec[i].mask)
			{
				//WRadioButton * wt_rb = new WRadioButton( vec[i].stub_text, wt_cb_rb_container_);
				WRadioButton * wt_rb = new WRadioButton(WString::tr(named_range_key.str().c_str()), wt_cb_rb_container_);
				wt_rb_container_->addButton(wt_rb, vec[i].code);
				new WBreak(wt_cb_rb_container_);
				vec_rb.push_back(wt_rb);
			}
			else if (q->no_mpn>1 && vec[i].mask)
			{
				//WCheckBox * wt_cb = new WCheckBox ( vec[i].stub_text, wt_cb_rb_container_);
				WCheckBox * wt_cb = new WCheckBox (WString::tr(named_range_key.str().c_str()), wt_cb_rb_container_);
				vec_cb.push_back(wt_cb);
				cout << " adding code: " << vec[i].code << " to map_cb_code_index" ;
				map_cb_code_index[vec_cb.size()-1] = vec[i].code;
			}
		}
		new_form->addWidget(wt_cb_rb_container_);
	}
	else
	{
		le_data_ = new WLineEdit();
		new_form->addWidget(le_data_);
	}

	wt_lastQuestionVisited_ = new WText();
	if (this_users_session->last_question_answered)
		wt_lastQuestionVisited_->setText(q->questionName_);
	new_form->addWidget(wt_lastQuestionVisited_);

	// create a button
	WPushButton *b = new WPushButton("Next");
	b->clicked().connect(this, &QuestionnaireApplication::DoQuestionnaire);
	new_form->addWidget(b);

	setCentralWidget(new_form);
	#endif						 /* 0 */
	//gtk_widget_hide_all (top_half);
	gtk_widget_hide( entry);

	DestroyPreviousWidgets ();
	questionTextLabel_ = gtk_label_new (question_text.c_str());
	//gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (top_half), questionTextLabel_);
	gtk_box_pack_start (GTK_BOX (vbox), questionTextLabel_, TRUE, TRUE, 0);
	gtk_widget_show(questionTextLabel_);
	gtk_widget_show (top_half);

	if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q))
	{
		//new_form->addWidget(wt_cb_rb_container_ = new WGroupBox());
		if (q->no_mpn==1)
		{
			//wt_rb_container_ = new WButtonGroup(wt_cb_rb_container_);
			rb_selected_code = -1;
			rb = gtk_radio_button_new_with_label (NULL, "Dummy - for default unselected - should never display");
			gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), rb, TRUE, TRUE, 0);
			GtkRadioButtonData * rb_data = new GtkRadioButtonData (0, this);
			rbData_.push_back (rb_data);
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (rb), TRUE);
			gtkRadioButtonGroup_ = gtk_radio_button_get_group (GTK_RADIO_BUTTON (rb));
			//g_signal_connect (G_OBJECT (rb), "toggled",
			//	G_CALLBACK (toggle_rb_button_event), (gpointer) rb_data);
			// purposely dont do a show . Make it default selected
		}
		vector<stub_pair> & vec= (nq->nr_ptr->stubs);
		bool rb_group_was_created = false;
		for (int i=0; i<vec.size(); ++i)
		{
			stringstream named_range_key;
			named_range_key << nq->nr_ptr->name << "_" << i;
			if (q->no_mpn == 1 && vec[i].mask)
			{
				//WRadioButton * wt_rb = new WRadioButton( vec[i].stub_text, wt_cb_rb_container_);
				//WRadioButton * wt_rb = new WRadioButton(WString::tr(named_range_key.str().c_str()), wt_cb_rb_container_);
				//wt_rb_container_->addButton(wt_rb, vec[i].code);
				//new WBreak(wt_cb_rb_container_);
				//if (!rb_group_was_created) {
				rb = gtk_radio_button_new_with_label (gtkRadioButtonGroup_, vec[i].stub_text.c_str());
				gtkRadioButtonGroup_ = gtk_radio_button_get_group (GTK_RADIO_BUTTON (rb));
				gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), rb, TRUE, TRUE, 0);
				GtkRadioButtonData * rb_data = new GtkRadioButtonData (vec[i].code, this);
				rbData_.push_back (rb_data);
				g_signal_connect (G_OBJECT (rb), "toggled",
					G_CALLBACK (toggle_rb_button_event), (gpointer) rb_data);
				gtk_widget_show (rb);
				//gtkRadioButtonGroup_ = gtk_radio_button_get_group (GTK_RADIO_BUTTON (rb));
				//rb_group_was_created = true;
				//} else {
				//	rb = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON(vec_rb[vec_rb.size()-1]), vec[i].stub_text.c_str());
				//	GtkRadioButtonData * rb_data = new GtkRadioButtonData (vec[i].code, this);
				//	rbData_.push_back (rb_data);
				//	g_signal_connect (G_OBJECT (rb), "toggled",
				//		G_CALLBACK (toggle_rb_button_event), (gpointer) rb_data);
				//	gtk_widget_show (rb);
				//	gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), rb, TRUE, TRUE, 0);
				//}
				vec_rb.push_back (rb);
			}
			if (q->no_mpn>1 && vec[i].mask)
			{
				//WCheckBox * wt_cb = new WCheckBox ( vec[i].stub_text, wt_cb_rb_container_);
				//WCheckBox * wt_cb = new WCheckBox (WString::tr(named_range_key.str().c_str()), wt_cb_rb_container_);
				//vec_cb.push_back(wt_cb);
				//cout << " adding code: " << vec[i].code << " to map_cb_code_index" ;
				GtkWidget * cb = gtk_check_button_new_with_label (vec[i].stub_text.c_str());
				GtkRadioButtonData * cb_data = new GtkRadioButtonData (vec[i].code, this);
				rbData_.push_back (cb_data);
				g_signal_connect (G_OBJECT (cb), "toggled",
					G_CALLBACK (toggle_rb_button_event), (gpointer) cb_data);
				gtk_widget_show (cb);
				gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), cb, TRUE, TRUE, 0);
				//!! Warning - the 2 statements below have to be in this order
				// and are not interchangeable
				vec_cb.push_back (cb);
				map_cb_code_index[vec_cb.size()-1] = vec[i].code;
			}
		}
		//new_form->addWidget(wt_cb_rb_container_);
	}
	else
	{
		le_data_ = gtk_entry_new ();
		gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
		g_signal_connect (G_OBJECT (le_data_), "activate", G_CALLBACK (line_edit_callback), (gpointer) this);
		gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), le_data_, TRUE, TRUE, 0);
		gtk_widget_show (le_data_);
	}
	next_button = gtk_button_new_with_label ("Next");
	gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), next_button, TRUE, TRUE, 0);
	gtk_widget_show (next_button);

	/* When the button is clicked, we call the "callback" function
	 * with a pointer to "button 1" as its argument */
	g_signal_connect (G_OBJECT (next_button), "clicked",
		G_CALLBACK (next_button_callback), (gpointer) this);
}


UI_Mode ui_mode = Gtk_Mode ;
int main(int argc, char ** argv)
{
	setlocale( LC_ALL, "" );
	bindtextdomain( "inp_jump_test", "/usr/share/locale" );
	textdomain( "inp_jump_test" );
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
	load_languages_available(vec_language);
	bool using_ncurses = true;
	qscript_stdout = fopen(qscript_stdout_fname.c_str(), "w");
	SetupSignalHandler();
	GtkQuestionnaireApplication gtkQuestionnaireApplication (argc, argv);
	//TheQuestionnaire theQuestionnaire;
	//get_serial_no_gtk (theQuestionnaire);
	gtk_main ();

	//return WRun (argc, argv, &createApplication);
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
	else if(signo == SIGHUP)
	{
		printf("received, SIGHUP: ignore this signal\n");
		return;
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
	if (signal (SIGSEGV, sig_usr) == SIG_ERR)
	{
		fprintf(stderr, "cannot catch SIGSEGV\n");
		exit(1);
	}
	else if (signal (SIGHUP, SIG_IGN) == SIG_ERR)
	{
		fprintf(stderr, "cannot ignore SIGHUP\n");
		exit(1);
	}
	else if (signal (SIGILL, sig_usr) == SIG_ERR)
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
	while ( (c = getopt(argc, argv, "mx::w::q::")) != -1)
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
			case 'm':
			{
				write_messages_flag = true;
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


void load_languages_available(vector<string> & vec_language)
{
	DIR * directory_ptr = opendir(".");
	vec_language.push_back("en");
	struct dirent *directory_entry = readdir(directory_ptr);
	while (directory_entry)
	{
		string dir_entry_name(directory_entry->d_name);
		int len_entry = dir_entry_name.length();
		if (len_entry > 4 &&
			dir_entry_name[len_entry - 1] == 'l' &&
			dir_entry_name[len_entry - 2] == 'm' &&
			dir_entry_name[len_entry - 3] == 'x' &&
			dir_entry_name[len_entry - 4] == '.' )
		{
			// the names we are looking for are of the form
			// jno + "[a-z][a-z].xml"
			bool is_our_file = true;
			if (len_entry != jno.length() + 7)
			{
				is_our_file = false;
				// the above doesnt matter actually,
				// continue takes us back to the top
				goto read_another_entry;
			}
			else
			{
				// possibly what we are looking for
				//
				for (int i = 0; i < jno.length(); ++i)
				{
					if (!(jno[i] == dir_entry_name[i]))
					{
						// cannot be our data file
						is_our_file = false;
						goto read_another_entry;
					}
				}
				char first_letter = dir_entry_name[jno.length() + 1];
				if (! isalpha (first_letter))
				{
					is_our_file = false;
					goto read_another_entry;
				}
				char second_letter = dir_entry_name[jno.length() + 2];
				if (! isalpha (second_letter))
				{
					is_our_file = false;
					goto read_another_entry;
				}
				string a_language;
				a_language.push_back(first_letter);
				a_language.push_back(second_letter);
				vec_language.push_back(a_language);
				//cout << "found an language traslation file: "
				//	<< dir_entry_name << endl;
			}
		}
		read_another_entry:
		directory_entry = readdir(directory_ptr);
	}
	closedir(directory_ptr);
}
