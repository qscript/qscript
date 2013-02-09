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
WINDOW *create_newwin(int32_t height, int32_t width, int32_t starty, int32_t startx);
void SetupNCurses(WINDOW * &  question_window,
WINDOW * &  stub_list_window,
WINDOW * & data_entry_window,
WINDOW * & help_window,
PANEL * &  question_panel,
PANEL * &  stub_list_panel,
PANEL * & data_entry_panel,
PANEL * & help_panel);
void define_some_pd_curses_keys();
void SetupSignalHandler();
static void sig_usr(int32_t signo);
string output_data_file_name;
string output_qtm_data_file_name;
string output_xtcc_data_file_name;
void GetUserResponse(string& qno, int32_t &qindex);
string jno = "vegetable";
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
vector <string> vec_language;
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
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 6, flagIsAForBody_: 0, source lineNo_: 1
	vector <stub_pair> qscript_temp_19;

	named_range yn;
	NamedStubQuestion * q1;
	vector <stub_pair> qscript_temp_20;

	named_range agree_5;
	vector <stub_pair> qscript_temp_21;

	named_range veg;
	named_attribute_list veg_seg_att;
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 4, flagIsAForBody_: 0, source lineNo_: 30
	NamedStubQuestion * q2;
	NamedStubQuestion * q3;
	NamedStubQuestion * q4;
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 1, flagIsAForBody_: 1, source lineNo_: 50
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 1, flagIsAForBody_: 1, source lineNo_: 53
	vector<int32_t> list_q5_array_bounds;
	ArrayQuestion q5_list;
	DummyArrayQuestion* dum_q5;
	XtccSet xs_0;
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 0, flagIsAForBody_: 1, source lineNo_: 59
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 0, flagIsAForBody_: 0, source lineNo_: 63
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 0, flagIsAForBody_: 0, source lineNo_: 69
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 1, flagIsAForBody_: 1, source lineNo_: 74
	vector<int32_t> list_q6_array_bounds;
	ArrayQuestion q6_list;
	DummyArrayQuestion* dum_q6;

	TheQuestionnaire()
		/* length(): 49 */: list_q5_array_bounds(1),list_q6_array_bounds(1)
		, last_question_answered(0), last_question_visited(0), back_jump(false), stopAtNextQuestion(false)
		, jno ("vegetable"), ser_no(0)
	{
		if (write_messages_flag)
		{
			messages.open ("vegetable.xml", ios_base::out|ios_base::trunc);
			if(!messages) { cerr << "unable to open file for output of messages... exiting\n"; exit(1); }
			messages << "<?xml version=\"1.0\" encoding=\"UTF8\"?>\n";
			messages << "<messages>\n"; messages << "  <message id=\"thank_you\">The Survey is now complete. Thank You for your time.</message>\n";
		}
		qscript_temp_19.push_back( stub_pair("Yes", 1));
		qscript_temp_19.push_back( stub_pair("No", 2));
		if (write_messages_flag)
		{
			for (int i=0; i<qscript_temp_19.size(); ++i)
			{
				messages << "<message id=\"" << "yn" << "_" << i << "\">" << qscript_temp_19[i].stub_text << "</message>\n" << endl;
			}
		}
		yn.set_range_data("yn", qscript_temp_19);
		{
			vector<TextExpression *> text_expr_vec;
			text_expr_vec.push_back(new TextExpression(string("Eat veg?")));
			q1 = new NamedStubQuestion(QUESTION_TYPE, 7,string( "q1"), text_expr_vec,spn,1,INT32_TYPE,&yn, QuestionAttributes(false , false), true);
			print_question_messages(q1);
		}
		qscript_temp_20.push_back( stub_pair("agree strongly", 5));
		qscript_temp_20.push_back( stub_pair("agree somewhat", 4));
		qscript_temp_20.push_back( stub_pair("Neutral", 3));
		qscript_temp_20.push_back( stub_pair("Disagree ", 2));
		qscript_temp_20.push_back( stub_pair("Disagree strongly", 1));
		if (write_messages_flag)
		{
			for (int i=0; i<qscript_temp_20.size(); ++i)
			{
				messages << "<message id=\"" << "agree_5" << "_" << i << "\">" << qscript_temp_20[i].stub_text << "</message>\n" << endl;
			}
		}
		agree_5.set_range_data("agree_5", qscript_temp_20);
		qscript_temp_21.push_back( stub_pair("Tomates", 1));
		qscript_temp_21.push_back( stub_pair("Potatoes", 2));
		qscript_temp_21.push_back( stub_pair("Capsicum", 3));
		qscript_temp_21.push_back( stub_pair("Brinjal/Egg plant", 4));
		qscript_temp_21.push_back( stub_pair("Okra/Lady Finger", 5));
		if (write_messages_flag)
		{
			for (int i=0; i<qscript_temp_21.size(); ++i)
			{
				messages << "<message id=\"" << "veg" << "_" << i << "\">" << qscript_temp_21[i].stub_text << "</message>\n" << endl;
			}
		}
		veg.set_range_data("veg", qscript_temp_21);
		veg_seg_att.name = "veg_seg_att";
		veg_seg_att.attribute.push_back (string(" Vegetables are good for health"));
		veg_seg_att.attribute.push_back (string(" I buy fresh vegetables often"));
		veg_seg_att.attribute.push_back (string(" Greens are good source of dietary fibre"));
		veg_seg_att.attribute.push_back (string(" I would like to be vegetarian some day"));
		if (write_messages_flag)
		{
			for (int i=0; i<veg_seg_att.attribute.size(); ++i)
			{
				messages << "<message id=\"" << "veg_seg_att" << "_" << i << "\">" << veg_seg_att.attribute[i] << "</message>\n" << endl;
			}
		}
		{
			vector<TextExpression *> text_expr_vec;
			text_expr_vec.push_back(new TextExpression(string("Which veg u r aware of?")));
			q2 = new NamedStubQuestion(QUESTION_TYPE, 35,string( "q2"), text_expr_vec,mpn,5,INT32_TYPE,&veg, QuestionAttributes(false , false), true);
			print_question_messages(q2);
		}
		{
			vector<TextExpression *> text_expr_vec;
			text_expr_vec.push_back(new TextExpression(string("Which veg dou eat?")));
			q3 = new NamedStubQuestion(QUESTION_TYPE, 40,string( "q3"), text_expr_vec,mpn,5,INT32_TYPE,&veg, QuestionAttributes(false , false), false);
			print_question_messages(q3);
		}
		{
			vector<TextExpression *> text_expr_vec;
			text_expr_vec.push_back(new TextExpression(string("Which is ur fav veg?")));
			q4 = new NamedStubQuestion(QUESTION_TYPE, 46,string( "q4"), text_expr_vec,spn,1,INT32_TYPE,&veg, QuestionAttributes(false , false), false);
			print_question_messages(q4);
		}
		list_q5_array_bounds[0] = 5;
		q5_list.SetArrayBounds(list_q5_array_bounds);
		dum_q5= new DummyArrayQuestion("q5",list_q5_array_bounds);
		question_list.push_back( dum_q5);
		xs_0.range.push_back(pair<int32_t,int32_t>(0,100));
		list_q6_array_bounds[0] = 4;
		q6_list.SetArrayBounds(list_q6_array_bounds);
		dum_q6= new DummyArrayQuestion("q6",list_q6_array_bounds);
		question_list.push_back( dum_q6);

		questions_start_from_here_index = question_list.size();
		question_list.push_back(q1);
		print_question_messages(q1);
		question_list.push_back(q2);
		print_question_messages(q2);
		question_list.push_back(q3);
		print_question_messages(q3);
		question_list.push_back(q4);
		print_question_messages(q4);
		for (int32_t i1 = 0;i1<5; ++i1)
		{
			vector<int32_t> stack_of_loop_indices;
			stack_of_loop_indices.push_back(i1);
			{
				vector<TextExpression *> text_expr_vec;
				text_expr_vec.push_back(new TextExpression(string("In a week what perc of your veggies are : ")));
								 /*  -NxD- */
				text_expr_vec.push_back( new TextExpression(q3, i1) );
				RangeQuestion * q5 = new RangeQuestion(QUESTION_ARR_TYPE, 56,string( "q5"), text_expr_vec,spn,1,INT32_TYPE,xs_0, stack_of_loop_indices , dum_q5, QuestionAttributes(false , false), true);
				question_list.push_back(q5);
				print_question_messages(q5);
				q5_list.questionList.push_back(q5);
			}
			stack_of_loop_indices.pop_back();
		}
		for (int32_t i1 = 0;i1<4; ++i1)
		{
			vector<int32_t> stack_of_loop_indices;
			stack_of_loop_indices.push_back(i1);
			{
				vector<TextExpression *> text_expr_vec;
				text_expr_vec.push_back(new TextExpression(string("Please state your agreement with these statements")));
				text_expr_vec.push_back(new TextExpression(&veg_seg_att, i1));
				NamedStubQuestion * q6 = new NamedStubQuestion(QUESTION_ARR_TYPE, 76,string( "q6"), text_expr_vec,spn,1,INT32_TYPE,&agree_5, stack_of_loop_indices , dum_q6, QuestionAttributes(false , false), true);
				question_list.push_back(q6);
				print_question_messages(q6);
				q6_list.questionList.push_back(q6);
			}
			stack_of_loop_indices.pop_back();
		}

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
				base_text_vec.push_back(BaseText("All who have answered question q1 Equals 1"));
				{
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
					AsciiFlatFileQuestionDiskMap * qscript_temp_10 = new AsciiFlatFileQuestionDiskMap(q4, current_map_pos);
					current_map_pos += qscript_temp_10->GetTotalLength();
					ascii_flatfile_question_disk_map.push_back(qscript_temp_10);
					if (write_xtcc_data_file_flag)
					{
						XtccDataFileDiskMap * qscript_temp_11 = new XtccDataFileDiskMap(q4, current_xtcc_map_pos);
						current_xtcc_map_pos += qscript_temp_11->GetTotalLength();
						xtcc_question_disk_map.push_back(qscript_temp_11);
					}
					if (write_qtm_data_file_flag)
					{
						qtm_data_file_ns::QtmDataDiskMap * qscript_temp_12 = new qtm_data_file_ns::QtmDataDiskMap(q4, qtm_data_file, base_text_vec.back());
						qtm_datafile_question_disk_map.push_back(qscript_temp_12);
					}
					for (int32_t i1 = 0;i1<5; ++i1)
					{
						vector<int32_t> stack_of_loop_indices;
						stack_of_loop_indices.push_back(i1);
						{
							int32_t consolidated_for_loop_index_2 = i1;
							BaseText btxt("q3 oper_in unhandled case leftOperand2_ is oper_name 1554, src/expr.cpp, virtual void Binary2Expression::PrintExpressionText(std::ostringstream&)", true,q3 );
							base_text_vec.push_back(btxt);
							{
								AsciiFlatFileQuestionDiskMap * qscript_temp_13 = new AsciiFlatFileQuestionDiskMap(q5_list.questionList[i1], current_map_pos);
								current_map_pos += qscript_temp_13->GetTotalLength();
								ascii_flatfile_question_disk_map.push_back(qscript_temp_13);
								if (write_xtcc_data_file_flag)
								{
									XtccDataFileDiskMap * qscript_temp_14 = new XtccDataFileDiskMap(q5_list.questionList[i1], current_xtcc_map_pos);
									current_xtcc_map_pos += qscript_temp_14->GetTotalLength();
									xtcc_question_disk_map.push_back(qscript_temp_14);
								}
								if (write_qtm_data_file_flag)
								{
									qtm_data_file_ns::QtmDataDiskMap * qscript_temp_15 = new qtm_data_file_ns::QtmDataDiskMap(q5_list.questionList[i1], qtm_data_file, base_text_vec.back());
									qtm_datafile_question_disk_map.push_back(qscript_temp_15);
								}
							}
							base_text_vec.pop_back();
							base_text_vec.push_back(BaseText("Not q3 oper_in unhandled case leftOperand2_ is oper_name 1554, src/expr.cpp, virtual void Binary2Expression::PrintExpressionText(std::ostringstream&)"));
							{
							}
							base_text_vec.pop_back();
						}
						stack_of_loop_indices.pop_back();
					}
					base_text_vec.push_back(BaseText("All respondents where internal variable sum is true is Not Equal to 100"));
					{
					}
					base_text_vec.pop_back();
					base_text_vec.push_back(BaseText("Not All respondents where internal variable sum is true is Not Equal to 100"));
					base_text_vec.pop_back();
				}
				base_text_vec.pop_back();
				base_text_vec.push_back(BaseText("Not All who have answered question q1 Equals 1"));
				{
				}
				base_text_vec.pop_back();
				for (int32_t i1 = 0;i1<4; ++i1)
				{
					vector<int32_t> stack_of_loop_indices;
					stack_of_loop_indices.push_back(i1);
					{
						int32_t consolidated_for_loop_index_7 = i1;
						AsciiFlatFileQuestionDiskMap * qscript_temp_16 = new AsciiFlatFileQuestionDiskMap(q6_list.questionList[i1], current_map_pos);
						current_map_pos += qscript_temp_16->GetTotalLength();
						ascii_flatfile_question_disk_map.push_back(qscript_temp_16);
						if (write_xtcc_data_file_flag)
						{
							XtccDataFileDiskMap * qscript_temp_17 = new XtccDataFileDiskMap(q6_list.questionList[i1], current_xtcc_map_pos);
							current_xtcc_map_pos += qscript_temp_17->GetTotalLength();
							xtcc_question_disk_map.push_back(qscript_temp_17);
						}
						if (write_qtm_data_file_flag)
						{
							qtm_data_file_ns::QtmDataDiskMap * qscript_temp_18 = new qtm_data_file_ns::QtmDataDiskMap(q6_list.questionList[i1], qtm_data_file, base_text_vec.back());
							qtm_datafile_question_disk_map.push_back(qscript_temp_18);
						}
					}
					stack_of_loop_indices.pop_back();
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
			/* compound statement on line no: 1 questionsInBlock_, size:6 q1, q2, q3, q4, q5, q6,  */
			int32_t i1;
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
			/* virtual void named_attribute_list::GenerateCode(StatementCompiledCode&), src/named_attributes.cpp, 25*/
			/* if_nest_level: 1 */
			/*if (!q1->isAnswered_) {
			cerr << "runtime error using unanswered question in expression: " << "q1" << endl;
			}*/
			int32_t qscript_temp_22 = *q1->input_data.begin();
								 // ifStatementStack.size(): 0
			if (qscript_temp_22==1)
			{
				// question_list_else_body :
				{
					/* compound statement on line no: 30 questionsInBlock_, size:4 q2, q3, q4, q5,  */
					/*StubManipStatement::GenerateCode() BEGIN :veg*/
					{
						for(int32_t qscript_temp_23 = 0; qscript_temp_23 < veg.stubs.size(); ++qscript_temp_23)
						{
							veg.stubs[qscript_temp_23].mask = true;
						}

					}
					/*StubManipStatement::GenerateCode() END :veg*/
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
					/*StubManipStatement::GenerateCode() BEGIN :veg*/
					{
						for(int32_t qscript_temp_24 = 0; qscript_temp_24 < veg.stubs.size(); ++qscript_temp_24)
						{
							veg.stubs[qscript_temp_24].mask = false;
						}

					}
					/*StubManipStatement::GenerateCode() END :veg*/
					/*StubManipStatement::GenerateCode() BEGIN q2:veg*/
					{
						set<int32_t>::iterator set_iter = q2->input_data.begin();
						for( ; set_iter!= q2->input_data.end(); ++set_iter)
						{
							for (int32_t qscript_temp_25 = 0; qscript_temp_25 < veg.stubs.size(); ++qscript_temp_25)
							{
								if (veg.stubs[qscript_temp_25].code == *set_iter)
								{
									veg.stubs[qscript_temp_25].mask = true;
								}
							}
						}

					}
					/*StubManipStatement::GenerateCode() END q2:veg*/
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
					/*StubManipStatement::GenerateCode() BEGIN :veg*/
					{
						for(int32_t qscript_temp_26 = 0; qscript_temp_26 < veg.stubs.size(); ++qscript_temp_26)
						{
							veg.stubs[qscript_temp_26].mask = false;
						}

					}
					/*StubManipStatement::GenerateCode() END :veg*/
					/*StubManipStatement::GenerateCode() BEGIN q3:veg*/
					{
						set<int32_t>::iterator set_iter = q3->input_data.begin();
						for( ; set_iter!= q3->input_data.end(); ++set_iter)
						{
							for (int32_t qscript_temp_27 = 0; qscript_temp_27 < veg.stubs.size(); ++qscript_temp_27)
							{
								if (veg.stubs[qscript_temp_27].code == *set_iter)
								{
									veg.stubs[qscript_temp_27].mask = true;
								}
							}
						}

					}
					/*StubManipStatement::GenerateCode() END q3:veg*/
					/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
					lab_q4:
					if( back_jump == true  && q4->isAnswered_ == true )
					{
						if( jumpToQuestion == "q4")
						{
							back_jump = false;
						}
					}
					/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
					if ( (q4->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
						(q4->isAnswered_ && !q4->VerifyQuestionIntegrity())||
						stopAtNextQuestion ||
						jumpToQuestion == "q4" ||
						((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q4->question_attributes.isAllowBlank()) && q4->isAnswered_ == false ))
					{
						if(stopAtNextQuestion && q4->question_attributes.hidden_ == false )
						{
							stopAtNextQuestion = false;  fprintf (qscript_stdout, " at question:  q4 disarming stopAtNextQuestion = false \n");

						}
						if (jumpToQuestion == "q4")
						{
							jumpToQuestion = "";
						}
						label_eval_q4:
						if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q4)
						{
							stopAtNextQuestion = true;
							fprintf (qscript_stdout, " at question:  q4 arming stopAtNextQuestion = true \n");
						}
						else if (q4->question_attributes.hidden_==false)
						{
							// q4->eval(question_window, stub_list_window, data_entry_window);
							last_question_visited = q4;
							fprintf(qscript_stdout, "last_question_visited: q4\n");
							return q4;
						}
					}
					int32_t sum = 0;
					int32_t iter_no = 0;
					for (i1 = 0;i1<5;i1 = i1+1)
					{
						int32_t consolidated_for_loop_index_2 = i1;
						/* compound statement on line no: 50 questionsInBlock_, size:1 q5,  */
						int32_t code = i1+1;
						/* if_nest_level: 2 */
						if (	 /* virtual void Binary2Expression::PrintExpressionCode(ExpressionCompiledCode&), 1676, src/expr.cpp    */
								 // ifStatementStack.size(): 0
							q3->input_data.find(code) != q3->input_data.end())
						{
							// question_list_else_body :
							{
								/* compound statement on line no: 53 questionsInBlock_, size:1 q5,  */
								/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():1 */
								lab_q5:
								if( back_jump == true  && q5_list.questionList[consolidated_for_loop_index_2]->isAnswered_ == true )
								{
								}
								/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
								// if (data_entry_window == 0) {
								//cout << "jumpToQuestion = " << jumpToQuestion << endl;//	cout << "jumpToIndex = " << jumpToIndex << endl;//}

								if(!q5_list.questionList[i1]->isAnswered_||stopAtNextQuestion||
									(p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q5_list.questionList[i1]) ||
									(jumpToQuestion == "q5" && jumpToIndex ==  consolidated_for_loop_index_2) )
								{
									label_eval_q5:
									if( jumpToQuestion == "q5" && jumpToIndex == consolidated_for_loop_index_2)
									{
										back_jump = false;
										jumpToIndex = -1;
									}
									if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q5_list.questionList[i1] &&  q5_list.questionList[i1]->isAnswered_ == true)
									{
										stopAtNextQuestion = true;
										fprintf (qscript_stdout, " at question:  q5 arming stopAtNextQuestion = true \n");
									}
									else if ( q5_list.questionList[i1] ->question_attributes.hidden_==false)
									{
										//q5_list.questionList[i1]->eval(question_window, stub_list_window, data_entry_window);
										last_question_visited = q5_list.questionList[i1];
										stopAtNextQuestion = false;
										return q5_list.questionList[i1];
									}
								}
								/* ENTER ExpressionStatement::GenerateCode */
								if (!q5_list.questionList[i1]->isAnswered_)
								{
									cerr << "runtime error using unanswered question in expression: " << "q5" << endl;
								}
								sum = sum+*(q5_list.questionList[i1]->input_data.begin());
								/* EXIT ExpressionStatement::GenerateCode */
								/* ENTER ExpressionStatement::GenerateCode */
								iter_no = i1;
							}
						}
						else
						{
							// end of ifBody_->GetQuestionNames
							// elseIfStatement DOES NOT exists
							/* question_list_if_body.size(): 1 */
							q5_list.questionList[consolidated_for_loop_index_2]->isAnswered_ = false;
							// ****************
							{
								/* compound statement on line no: 59 questionsInBlock_, size:0  */
								/* ENTER ExpressionStatement::GenerateCode */
								1;
							}
						}
					}
					/* if_nest_level: 2 */
					if (sum!=100)// ifStatementStack.size(): 0
					{
						// question_list_else_body :
						{
							/* compound statement on line no: 63 questionsInBlock_, size:0  */
							q5_list.questionList[iter_no]->isAnswered_ = false;
							stopAtNextQuestion = false;
							goto start_of_questions;
						}
					}
					// elseBody_ == 0 - detecting if ifBody_ has questions: yes => we flag an error
					// question_list_if_body:
				}
			}
			else
			{
				// end of ifBody_->GetQuestionNames
				// elseIfStatement DOES NOT exists
				/* question_list_if_body.size(): 3 */
				q2->isAnswered_ = false;
				q3->isAnswered_ = false;
				q4->isAnswered_ = false;
				// ****************
				{
					/* compound statement on line no: 69 questionsInBlock_, size:0  */
					/* ENTER ExpressionStatement::GenerateCode */
					1;
				}
			}
			for (i1 = 0;i1<4;i1 = i1+1)
			{
				int32_t consolidated_for_loop_index_7 = i1;
				/* compound statement on line no: 74 questionsInBlock_, size:1 q6,  */
				/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():1 */
				lab_q6:
				if( back_jump == true  && q6_list.questionList[consolidated_for_loop_index_7]->isAnswered_ == true )
				{
				}
				/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
				// if (data_entry_window == 0) {
				//cout << "jumpToQuestion = " << jumpToQuestion << endl;//	cout << "jumpToIndex = " << jumpToIndex << endl;//}

				if(!q6_list.questionList[i1]->isAnswered_||stopAtNextQuestion||
					(p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q6_list.questionList[i1]) ||
					(jumpToQuestion == "q6" && jumpToIndex ==  consolidated_for_loop_index_7) )
				{
					label_eval_q6:
					if( jumpToQuestion == "q6" && jumpToIndex == consolidated_for_loop_index_7)
					{
						back_jump = false;
						jumpToIndex = -1;
					}
					if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q6_list.questionList[i1] &&  q6_list.questionList[i1]->isAnswered_ == true)
					{
						stopAtNextQuestion = true;
						fprintf (qscript_stdout, " at question:  q6 arming stopAtNextQuestion = true \n");
					}
					else if ( q6_list.questionList[i1] ->question_attributes.hidden_==false)
					{
						//q6_list.questionList[i1]->eval(question_window, stub_list_window, data_entry_window);
						last_question_visited = q6_list.questionList[i1];
						stopAtNextQuestion = false;
						return q6_list.questionList[i1];
					}
				}
			}
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
		wclear(data_entry_window);
		mvwprintw(data_entry_window, 1, 1, "Enter Serial No (0) to exit: ");
		mvwscanw(data_entry_window, 1, 40, "%d", & ser_no);
		}
		*/
		// reset_questionnaire();
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

enum EvalMode { USER_NAVIGATION, NORMAL_FLOW };
void question_eval_loop (EvalMode qnre_mode, UserNavigation navg,
		AbstractQuestion * last_question_visited,
		AbstractQuestion * jump_to_question,
		TheQuestionnaire * qnre);

int32_t main(int argc, char * argv[])
{
	process_options(argc, argv);
	if (write_data_file_flag||write_qtm_data_file_flag||write_xtcc_data_file_flag)
	{
		qtm_data_file_ns::init();
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
	SetupNCurses(question_window, stub_list_window, data_entry_window, help_window, question_panel, stub_list_panel, data_entry_panel, help_panel);
	if(question_window == 0 || stub_list_window == 0 || data_entry_window == 0
		/* || help_window == 0 */
		)
	{
		cerr << "Unable to create windows ... exiting" << endl;
		return 1;
	}
	SetupSignalHandler();
	TheQuestionnaire * theQuestionnaire = new TheQuestionnaire();
	theQuestionnaire->base_text_vec.push_back(BaseText("All Respondents"));
	theQuestionnaire->compute_flat_file_map_and_init();
	UserNavigation qnre_navigation_mode = NAVIGATE_NEXT;
	EvalMode qnre_mode = NORMAL_FLOW;
	AbstractQuestion * last_question_visited = 0;
	AbstractQuestion * jump_to_question = 0;

	question_eval_loop (qnre_mode, qnre_navigation_mode, last_question_visited, jump_to_question, theQuestionnaire);

	// extract out into a function
	// then iteratively make it a pure function.
	// use : no_goto.cpp as the motivating example
#if 0
	do
	{
		theQuestionnaire.reset_questionnaire();
		if (write_data_file_flag||write_qtm_data_file_flag)
		{
			theQuestionnaire.ser_no = theQuestionnaire.read_a_serial_no();
			if (theQuestionnaire.ser_no == 0)
			{
				exit(1);
			}
		}
		else
		{
			theQuestionnaire.prompt_user_for_serial_no();
			if (theQuestionnaire.ser_no == 0)
			{
				break;
			}
			int exists = check_if_reg_file_exists(theQuestionnaire.jno, theQuestionnaire.ser_no);
			if(exists == 1)
			{
				map <string, question_disk_data*>  qdd_map;
				load_data (theQuestionnaire.jno, theQuestionnaire.ser_no, &qdd_map);
				merge_disk_data_into_questions2(qscript_stdout, theQuestionnaire.last_question_answered, theQuestionnaire.last_question_visited, theQuestionnaire.question_list, &qdd_map);
			}
		}

		while(theQuestionnaire.ser_no != 0 || (write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag))
		{
			fprintf(qscript_stdout, "reached top of while loop:\n");              re_eval_from_start:
			AbstractQuestion * q =
								 /*last_question_answered, last_question_visited, */
				theQuestionnaire.eval2 (
				qnre_navigation_mode);
			if (!q)
			{
				if (write_data_file_flag)
				{
					theQuestionnaire.write_ascii_data_to_disk();
				}
				else if (write_qtm_data_file_flag)
				{
					theQuestionnaire.write_qtm_data_to_disk();
				}
				else
				{
					char end_of_question_navigation;
					label_end_of_qnre_navigation:
					wclear(data_entry_window);
					mvwprintw(data_entry_window, 1, 1,"End of Questionnaire: ((s)ave, (p)revious question, question (j)ump list)");
					mvwscanw(data_entry_window, 1, 75, "%c", & end_of_question_navigation);
					if(end_of_question_navigation == 's')
					{
						theQuestionnaire.write_data_to_disk(theQuestionnaire.question_list, theQuestionnaire.jno, theQuestionnaire.ser_no);
					}
					else if (end_of_question_navigation == 'p')
					{
						AbstractQuestion * target_question = theQuestionnaire.ComputePreviousQuestion(theQuestionnaire.last_question_answered);
						if(target_question->type_ == QUESTION_ARR_TYPE)
						{
							theQuestionnaire.jumpToIndex = theQuestionnaire.ComputeJumpToIndex(target_question);
						}
						theQuestionnaire.jumpToQuestion = target_question->questionName_;
						//if (data_entry_window == 0) cout << "target question: " << jumpToQuestion;
						theQuestionnaire.back_jump = true;
						user_navigation = NOT_SET;
						//goto start_of_questions;
						goto re_eval_from_start;
					}
					else if (end_of_question_navigation == 'j')
					{
						theQuestionnaire.DisplayActiveQuestions();
						theQuestionnaire.GetUserResponse(theQuestionnaire.jumpToQuestion, theQuestionnaire.jumpToIndex);
						user_navigation = NOT_SET;
						//goto start_of_questions;
						goto re_eval_from_start;
					}
					else if (end_of_question_navigation == 'q')
					{
						//theQuestionnaire.reset_questionnaire();
						break;
					}
					else
					{
						goto label_end_of_qnre_navigation;
					}
					// wclear(data_entry_window);
					// mvwprintw(data_entry_window, 1, 1, "Enter Serial No (0) to exit: ");
					// mvwscanw(data_entry_window, 1, 40, "%d", & ser_no);
					//theQuestionnaire.prompt_user_for_serial_no();
					//if (theQuestionnaire.ser_no ==0) break;
					break;
				}
			}
			else
			{
				fprintf(qscript_stdout, "eval2 returned %s\n",
					q->questionName_.c_str());
				re_eval:
				q->eval(question_window, stub_list_window, data_entry_window);

				if (user_navigation == NAVIGATE_PREVIOUS)
				{
					fprintf(qscript_stdout,
						"user_navigation == NAVIGATE_PREVIOUS\n");
					AbstractQuestion *target_question =
						theQuestionnaire.ComputePreviousQuestion(q);
					if (target_question == 0)
						goto re_eval;
					else
					{
						theQuestionnaire.jumpToQuestion = target_question->questionName_;
						if (target_question->type_ == QUESTION_ARR_TYPE)
						{
							theQuestionnaire.jumpToIndex =
								theQuestionnaire.
								ComputeJumpToIndex(target_question);
						}
						// if (data_entry_window == 0)
						//     cout << "target question: " << jumpToQuestion;
						// if (data_entry_window == 0)
						//     cout << "target question Index: " << theQuestionnaire.jumpToIndex;
						theQuestionnaire.back_jump = true;
						user_navigation = NOT_SET;
						//goto start_of_questions;
						goto re_eval_from_start;
					}
				}
				else if (user_navigation == NAVIGATE_NEXT)
				{
					fprintf(qscript_stdout, "user_navigation == NAVIGATE_NEXT\n");
					if (q->isAnswered_ == false
						&& q->question_attributes.isAllowBlank() == false)
					{
						fprintf(qscript_stdout,
							"questionName_ %s: going back to re_eval\n",
							q->questionName_.c_str());
						goto re_eval;
					}
					qnre_navigation_mode = NAVIGATE_NEXT;
					// stopAtNextQuestion = true;
					user_navigation = NOT_SET;
				}
				else if (user_navigation == JUMP_TO_QUESTION)
				{
					theQuestionnaire.DisplayActiveQuestions();
					theQuestionnaire.GetUserResponse(theQuestionnaire.jumpToQuestion, theQuestionnaire.jumpToIndex);
					user_navigation = NOT_SET;
					//goto start_of_questions;
					goto re_eval_from_start;
				}
				else if (user_navigation == SAVE_DATA)
				{
					theQuestionnaire.write_data_to_disk(theQuestionnaire.question_list, theQuestionnaire.jno,
						theQuestionnaire.ser_no);
					if (data_entry_window)
						mvwprintw(data_entry_window, 2, 50, "saved partial data");
					else
						cout << "saved partial data\n";
					if (q->isAnswered_ == false)
					{
						//goto label_eval_q2;
						goto re_eval;
					}
				}
				else
				{
					theQuestionnaire.last_question_answered = q;
				}
			}
		}						 /* close while */
								 /* close do */
	} while(theQuestionnaire.ser_no != 0);
#endif /*  0 */
	endwin();

}								 /* close main */

void question_eval_loop (EvalMode qnre_mode, UserNavigation qnre_navigation_mode,
		AbstractQuestion * last_question_visited,
		AbstractQuestion * jump_to_question,
		TheQuestionnaire * theQuestionnaire)
{
	do
	{
		theQuestionnaire->reset_questionnaire();
		if (write_data_file_flag||write_qtm_data_file_flag)
		{
			theQuestionnaire->ser_no = 
				theQuestionnaire->read_a_serial_no();
			if (theQuestionnaire->ser_no == 0)
			{
				exit(1);
			}
		}
		else
		{
			theQuestionnaire->prompt_user_for_serial_no();
			if (theQuestionnaire->ser_no == 0)
			{
				break;
			}
			int exists = check_if_reg_file_exists(theQuestionnaire->jno, theQuestionnaire->ser_no);
			if(exists == 1)
			{
				map <string, question_disk_data*>  qdd_map;
				load_data (theQuestionnaire->jno, theQuestionnaire->ser_no, &qdd_map);
				merge_disk_data_into_questions2(qscript_stdout, theQuestionnaire->last_question_answered, theQuestionnaire->last_question_visited, theQuestionnaire->question_list, &qdd_map);
			}
		}

		while(theQuestionnaire->ser_no != 0 || (write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag))
		{
			fprintf(qscript_stdout, "reached top of while loop:\n");              re_eval_from_start:
			AbstractQuestion * q =
								 /*last_question_answered, last_question_visited, */
				theQuestionnaire->eval2 (
				qnre_navigation_mode);
			if (!q)
			{
#if 1
				if (write_data_file_flag)
				{
					theQuestionnaire->write_ascii_data_to_disk();
				}
				else if (write_qtm_data_file_flag)
				{
					theQuestionnaire->write_qtm_data_to_disk();
				}
				else
				{
					char end_of_question_navigation;
					label_end_of_qnre_navigation:
					wclear(data_entry_window);
					mvwprintw(data_entry_window, 1, 1,"End of Questionnaire: ((s)ave, (p)revious question, question (j)ump list)");
					mvwscanw(data_entry_window, 1, 75, "%c", & end_of_question_navigation);
					if(end_of_question_navigation == 's')
					{
						theQuestionnaire->write_data_to_disk(theQuestionnaire->question_list, theQuestionnaire->jno, theQuestionnaire->ser_no);
					}
					else if (end_of_question_navigation == 'p')
					{
						AbstractQuestion * target_question = theQuestionnaire->ComputePreviousQuestion(theQuestionnaire->last_question_answered);
						if(target_question->type_ == QUESTION_ARR_TYPE)
						{
							theQuestionnaire->jumpToIndex = theQuestionnaire->ComputeJumpToIndex(target_question);
						}
						theQuestionnaire->jumpToQuestion = target_question->questionName_;
						//if (data_entry_window == 0) cout << "target question: " << jumpToQuestion;
						theQuestionnaire->back_jump = true;
						user_navigation = NOT_SET;
						//goto start_of_questions;
						goto re_eval_from_start;
					}
					else if (end_of_question_navigation == 'j')
					{
						theQuestionnaire->DisplayActiveQuestions();
						theQuestionnaire->GetUserResponse(theQuestionnaire->jumpToQuestion, theQuestionnaire->jumpToIndex);
						user_navigation = NOT_SET;
						//goto start_of_questions;
						goto re_eval_from_start;
					}
					else if (end_of_question_navigation == 'q')
					{
						//theQuestionnaire.reset_questionnaire();
						break;
					}
					else
					{
						goto label_end_of_qnre_navigation;
					}
					// wclear(data_entry_window);
					// mvwprintw(data_entry_window, 1, 1, "Enter Serial No (0) to exit: ");
					// mvwscanw(data_entry_window, 1, 40, "%d", & ser_no);
					//theQuestionnaire.prompt_user_for_serial_no();
					//if (theQuestionnaire.ser_no ==0) break;
					break;
				}
#endif /*  0 */
			}
			else
			{
#if 1
				fprintf(qscript_stdout, "eval2 returned %s\n",
					q->questionName_.c_str());
				re_eval:
				q->eval(question_window, stub_list_window, data_entry_window);

				if (user_navigation == NAVIGATE_PREVIOUS)
				{
					fprintf(qscript_stdout,
						"user_navigation == NAVIGATE_PREVIOUS\n");
					AbstractQuestion *target_question =
						theQuestionnaire->ComputePreviousQuestion(q);
					if (target_question == 0)
						goto re_eval;
					else
					{
						theQuestionnaire->jumpToQuestion = target_question->questionName_;
						if (target_question->type_ == QUESTION_ARR_TYPE)
						{
							theQuestionnaire->jumpToIndex =
								theQuestionnaire->
								ComputeJumpToIndex(target_question);
						}
						// if (data_entry_window == 0)
						//     cout << "target question: " << jumpToQuestion;
						// if (data_entry_window == 0)
						//     cout << "target question Index: " << theQuestionnaire.jumpToIndex;
						theQuestionnaire->back_jump = true;
						user_navigation = NOT_SET;
						//goto start_of_questions;
						goto re_eval_from_start;
					}
				}
				else if (user_navigation == NAVIGATE_NEXT)
				{
					fprintf(qscript_stdout, "user_navigation == NAVIGATE_NEXT\n");
					if (q->isAnswered_ == false
						&& q->question_attributes.isAllowBlank() == false)
					{
						fprintf(qscript_stdout,
							"questionName_ %s: going back to re_eval\n",
							q->questionName_.c_str());
						goto re_eval;
					}
					qnre_navigation_mode = NAVIGATE_NEXT;
					// stopAtNextQuestion = true;
					user_navigation = NOT_SET;
				}
				else if (user_navigation == JUMP_TO_QUESTION)
				{
					theQuestionnaire->DisplayActiveQuestions();
					theQuestionnaire->GetUserResponse(theQuestionnaire->jumpToQuestion, theQuestionnaire->jumpToIndex);
					user_navigation = NOT_SET;
					//goto start_of_questions;
					goto re_eval_from_start;
				}
				else if (user_navigation == SAVE_DATA)
				{
					theQuestionnaire->write_data_to_disk(theQuestionnaire->question_list, theQuestionnaire->jno,
						theQuestionnaire->ser_no);
					if (data_entry_window)
						mvwprintw(data_entry_window, 2, 50, "saved partial data");
					else
						cout << "saved partial data\n";
					if (q->isAnswered_ == false)
					{
						//goto label_eval_q2;
						goto re_eval;
					}
				}
				else
				{
					theQuestionnaire->last_question_answered = q;
				}
#endif /*  0 */
			}
		}						 /* close while */
								 /* close do */
	} while(theQuestionnaire->ser_no != 0);

}

void SetupNCurses(WINDOW * &  question_window,
WINDOW * &  stub_list_window,
WINDOW * & data_entry_window,
WINDOW * & help_window,
PANEL * &  question_panel,
PANEL * &  stub_list_panel,
PANEL * & data_entry_panel,
PANEL * & help_panel)
{
	initscr();
	cbreak();
	nonl();
	intrflush(stdscr, FALSE);
	if(has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	chtype space = ' '; init_pair(1, COLOR_RED, COLOR_WHITE);
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

	int32_t QUESTION_WINDOW_HEIGHT=(height_left%3) + (height_left/3), QUESTION_WINDOW_WIDTH=maxX;
	starty = 0;
	question_window = create_newwin(QUESTION_WINDOW_HEIGHT
		, QUESTION_WINDOW_WIDTH, starty, startx);
	wbkgd(question_window, space | COLOR_PAIR(3));
	wcolor_set(question_window, 3, 0);
	wattron(question_window, COLOR_PAIR(3));

	wmove(data_entry_window, 1,1);
	define_some_pd_curses_keys();
	int32_t HELP_WINDOW_HEIGHT=(int)((float)(2/3)*maxY), HELP_WINDOW_WIDTH=maxX/2;

	starty = 5;
	startx = 5;
	//help_window = create_newwin(HELP_WINDOW_HEIGHT, HELP_WINDOW_WIDTH, starty, startx);
	question_panel = new_panel(question_window);
	stub_list_panel = new_panel(stub_list_window);
	data_entry_panel = new_panel(data_entry_window);
	//help_panel = new_panel(help_window);
	update_panels();
	doupdate();
}


WINDOW *create_newwin(int32_t height, int32_t width, int32_t starty, int32_t startx)
{
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);
	/* 0, 0 gives default characters
	 * for the vertical and horizontal
	 * lines                        */

	return local_win;
}


void define_some_pd_curses_keys()
{
	string ctrl_left_arrow;
	ctrl_left_arrow.append(1, 27);
	ctrl_left_arrow.append(1, 91);
	ctrl_left_arrow.append(1, 49);
	ctrl_left_arrow.append(1, 59);
	ctrl_left_arrow.append(1, 53);
	ctrl_left_arrow.append(1, 68);

	string ctrl_right_arrow;
	ctrl_right_arrow.append(1, 27);
	ctrl_right_arrow.append(1, 91);
	ctrl_right_arrow.append(1, 49);
	ctrl_right_arrow.append(1, 59);
	ctrl_right_arrow.append(1, 53);
	ctrl_right_arrow.append(1, 67);
	string ctl_del;
	ctl_del.append(1, 27);
	ctl_del.append(1, 91);
	ctl_del.append(1, 51);
	ctl_del.append(1, 59);
	ctl_del.append(1, 53);
	ctl_del.append(1, 126);
	string alt_del;
	alt_del.append(1, 27);
	alt_del.append(1, 91);
	alt_del.append(1, 51);
	alt_del.append(1, 59);
	alt_del.append(1, 51);
	alt_del.append(1, 126);

	string shift_del;
	shift_del.append(1, 27);
	shift_del.append(1, 91);
	shift_del.append(1, 51);
	shift_del.append(1, 59);
	shift_del.append(1, 50);
	shift_del.append(1, 126);
	define_key(ctrl_left_arrow.c_str(), CTL_LEFT);
	define_key(ctrl_right_arrow.c_str(), CTL_RIGHT);
	define_key(ctl_del.c_str(), CTL_DEL);
	define_key(alt_del.c_str(), ALT_DEL);
	define_key(shift_del.c_str(), SHF_DC);
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
	endwin();
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
