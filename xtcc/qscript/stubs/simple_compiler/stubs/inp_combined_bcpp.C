#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <cstdlib>
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
#include "QuestionAttributes.h"
#include "UserResponse.h"
int ser_no = 0;
using namespace std;
string qscript_stdout_fname("qscript_stdout.log");
FILE * qscript_stdout = 0;
#include "debug_mem.h"
fstream debug_log_file("qscript_debug.log", ios_base::out|ios_base::trunc);
fstream flat_file;
fstream qtm_disk_file;
extern set<string> qtm_include_files;
using namespace std;
//extern vector<int32_t> data;
extern UserNavigation user_navigation;
vector <AbstractQuestion*> question_list;
vector<mem_addr_tab>  mem_addr;
extern vector<question_disk_data*>  qdd_list;
void merge_disk_data_into_questions(FILE * qscript_stdout,
AbstractQuestion * & p_last_question_answered,
AbstractQuestion * & p_last_question_visited);
bool stopAtNextQuestion;
string jumpToQuestion;
int32_t jumpToIndex;
bool write_data_file_flag;
bool write_qtm_data_file_flag;
int32_t check_if_reg_file_exists(string jno, int32_t ser_no);
void print_map_header(fstream & map_file);
void write_data_to_disk(const vector<AbstractQuestion*>& q_vec, string jno, int32_t ser_no);
void SetupSignalHandler();
static void sig_usr(int32_t signo);
string output_data_file_name;
string output_qtm_data_file_name;
void GetUserResponse(string& qno, int32_t &qindex);
char * flat_file_output_buffer = 0;
int32_t len_flat_file_output_buffer  = 0;
vector <AsciiFlatFileQuestionDiskMap*> ascii_flatfile_question_disk_map;
vector <qtm_data_file_ns::QtmDataDiskMap*> qtm_datafile_question_disk_map;
qtm_data_file_ns::QtmDataFile qtm_data_file;

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
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 6, flagIsAForBody_: 0, source lineNo_: 2
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 2, flagIsAForBody_: 1, source lineNo_: 8
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 1, flagIsAForBody_: 1, source lineNo_: 11
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 1, flagIsAForBody_: 2, source lineNo_: 12
	map <string,int8_t> q1_scope_int8_t;
	map <string,int16_t> q1_scope_int16_t;
	map <string,int32_t> q1_scope_int32_t;
	map <string,float> q1_scope_float_t;
	map <string,double> q1_scope_double_t;
	map <string,set<int32_t> > q1_scope_question_t;
	vector<int32_t> list_q1_array_bounds;
	ArrayQuestion q1_list;
	DummyArrayQuestion* dum_q1;
	XtccSet xs_0;
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 1, flagIsAForBody_: 2, source lineNo_: 16
	map <string,int8_t> q2_scope_int8_t;
	map <string,int16_t> q2_scope_int16_t;
	map <string,int32_t> q2_scope_int32_t;
	map <string,float> q2_scope_float_t;
	map <string,double> q2_scope_double_t;
	map <string,set<int32_t> > q2_scope_question_t;
	vector<int32_t> list_q2_array_bounds;
	ArrayQuestion q2_list;
	DummyArrayQuestion* dum_q2;
	XtccSet xs_1;
	map <string,int8_t> q3_1_scope_int8_t;
	map <string,int16_t> q3_1_scope_int16_t;
	map <string,int32_t> q3_1_scope_int32_t;
	map <string,float> q3_1_scope_float_t;
	map <string,double> q3_1_scope_double_t;
	map <string,set<int32_t> > q3_1_scope_question_t;
	XtccSet xs_2;
	RangeQuestion * q3_1;
	map <string,int8_t> q3_2_scope_int8_t;
	map <string,int16_t> q3_2_scope_int16_t;
	map <string,int32_t> q3_2_scope_int32_t;
	map <string,float> q3_2_scope_float_t;
	map <string,double> q3_2_scope_double_t;
	map <string,set<int32_t> > q3_2_scope_question_t;
	XtccSet xs_3;
	RangeQuestion * q3_2;
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 2, flagIsAForBody_: 1, source lineNo_: 25
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 1, flagIsAForBody_: 1, source lineNo_: 28
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 1, flagIsAForBody_: 2, source lineNo_: 29
	map <string,int8_t> q4_scope_int8_t;
	map <string,int16_t> q4_scope_int16_t;
	map <string,int32_t> q4_scope_int32_t;
	map <string,float> q4_scope_float_t;
	map <string,double> q4_scope_double_t;
	map <string,set<int32_t> > q4_scope_question_t;
	vector<int32_t> list_q4_array_bounds;
	ArrayQuestion q4_list;
	DummyArrayQuestion* dum_q4;
	XtccSet xs_4;
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 1, flagIsAForBody_: 2, source lineNo_: 33
	map <string,int8_t> q5_scope_int8_t;
	map <string,int16_t> q5_scope_int16_t;
	map <string,int32_t> q5_scope_int32_t;
	map <string,float> q5_scope_float_t;
	map <string,double> q5_scope_double_t;
	map <string,set<int32_t> > q5_scope_question_t;
	vector<int32_t> list_q5_array_bounds;
	ArrayQuestion q5_list;
	DummyArrayQuestion* dum_q5;
	XtccSet xs_5;

	TheQuestionnaire()
		: list_q1_array_bounds(2),list_q2_array_bounds(2),list_q4_array_bounds(2),list_q5_array_bounds(2)
		, last_question_answered(0), last_question_visited(0), back_jump(false)
		, jno ("inp_combined")
	{
		list_q1_array_bounds[0] = 5;
		list_q1_array_bounds[1] = 2;
		q1_list.SetArrayBounds(list_q1_array_bounds);
		dum_q1= new DummyArrayQuestion("q1",list_q1_array_bounds);
		question_list.push_back( dum_q1);
		xs_0.indiv.insert(1);
		xs_0.indiv.insert(2);
		xs_0.indiv.insert(3);
		xs_0.indiv.insert(4);
		list_q2_array_bounds[0] = 5;
		list_q2_array_bounds[1] = 3;
		q2_list.SetArrayBounds(list_q2_array_bounds);
		dum_q2= new DummyArrayQuestion("q2",list_q2_array_bounds);
		question_list.push_back( dum_q2);
		xs_1.indiv.insert(1);
		xs_1.indiv.insert(2);
		xs_1.indiv.insert(3);
		xs_1.indiv.insert(4);
		xs_2.range.push_back(pair<int32_t,int32_t>(1,99));
		q3_1 = new RangeQuestion(QUESTION_TYPE, 21,string( "q3_1"),string(" q3.1 "),mpn,5,INT32_TYPE,xs_2, QuestionAttributes(false , false));
		question_list.push_back(q3_1);
		xs_3.range.push_back(pair<int32_t,int32_t>(1,99));
		q3_2 = new RangeQuestion(QUESTION_TYPE, 22,string( "q3_2"),string(" q3.2 "),mpn,5,INT32_TYPE,xs_3, QuestionAttributes(false , false));
		question_list.push_back(q3_2);
		list_q4_array_bounds[0] = 5;
		list_q4_array_bounds[1] = 2;
		q4_list.SetArrayBounds(list_q4_array_bounds);
		dum_q4= new DummyArrayQuestion("q4",list_q4_array_bounds);
		question_list.push_back( dum_q4);
		xs_4.range.push_back(pair<int32_t,int32_t>(1,200));
		list_q5_array_bounds[0] = 5;
		list_q5_array_bounds[1] = 3;
		q5_list.SetArrayBounds(list_q5_array_bounds);
		dum_q5= new DummyArrayQuestion("q5",list_q5_array_bounds);
		question_list.push_back( dum_q5);
		xs_5.range.push_back(pair<int32_t,int32_t>(1,300));

		for (int32_t i1 = 0;i1<5; ++i1)
		{
			vector<int32_t> stack_of_loop_indices;
			stack_of_loop_indices.push_back(i1);
			for (int32_t i2 = 0;i2<2; ++i2)
			{
				stack_of_loop_indices.push_back(i2);
				RangeQuestion * q1 = new RangeQuestion(QUESTION_ARR_TYPE, 13,string( "q1"),string(" Q1. This is question 1"),spn,1,INT32_TYPE,xs_0, stack_of_loop_indices , dum_q1, QuestionAttributes(false , false));
				question_list.push_back(q1);
				q1_list.questionList.push_back(q1);
				stack_of_loop_indices.pop_back();
			}
			for (int32_t i2 = 0;i2<3; ++i2)
			{
				stack_of_loop_indices.push_back(i2);
				RangeQuestion * q2 = new RangeQuestion(QUESTION_ARR_TYPE, 17,string( "q2"),string(" Q2. This is question 2"),spn,1,INT32_TYPE,xs_1, stack_of_loop_indices , dum_q2, QuestionAttributes(false , false));
				question_list.push_back(q2);
				q2_list.questionList.push_back(q2);
				stack_of_loop_indices.pop_back();
			}
			stack_of_loop_indices.pop_back();
		}
		for (int32_t i1 = 0;i1<5; ++i1)
		{
			vector<int32_t> stack_of_loop_indices;
			stack_of_loop_indices.push_back(i1);
			for (int32_t i2 = 0;i2<2; ++i2)
			{
				stack_of_loop_indices.push_back(i2);
				RangeQuestion * q4 = new RangeQuestion(QUESTION_ARR_TYPE, 30,string( "q4"),string(" Q1. "),mpn,10,INT32_TYPE,xs_4, stack_of_loop_indices , dum_q4, QuestionAttributes(false , false));
				question_list.push_back(q4);
				q4_list.questionList.push_back(q4);
				stack_of_loop_indices.pop_back();
			}
			for (int32_t i2 = 0;i2<3; ++i2)
			{
				stack_of_loop_indices.push_back(i2);
				RangeQuestion * q5 = new RangeQuestion(QUESTION_ARR_TYPE, 34,string( "q5"),string(" Q5. "),mpn,10,INT32_TYPE,xs_5, stack_of_loop_indices , dum_q5, QuestionAttributes(false , false));
				question_list.push_back(q5);
				q5_list.questionList.push_back(q5);
				stack_of_loop_indices.pop_back();
			}
			stack_of_loop_indices.pop_back();
		}
		compute_flat_file_map_and_init();
	}
	void compute_flat_file_map_and_init()
	{
		if (write_data_file_flag || write_qtm_data_file_flag)
		{
			int current_map_pos = 0;
			if (write_qtm_data_file_flag)
			{
				qtm_datafile_conf_parser_ns::load_config_file(jno);
				qtm_data_file.Initialize();
			}
			{
				for (int32_t i1 = 0;i1<5; ++i1)
				{
					vector<int32_t> stack_of_loop_indices;
					stack_of_loop_indices.push_back(i1);
					{
						int32_t consolidated_for_loop_index_1 = i1;
						{
							for (int32_t i2 = 0;i2<2; ++i2)
							{
								stack_of_loop_indices.push_back(i2);
								{
									int32_t consolidated_for_loop_index_3 = i1*2+i2;
									AsciiFlatFileQuestionDiskMap * qscript_temp_1 = new AsciiFlatFileQuestionDiskMap(q1_list.questionList[i1*2+i2], current_map_pos);
									current_map_pos += qscript_temp_1->GetTotalLength();
									ascii_flatfile_question_disk_map.push_back(qscript_temp_1);
									if (write_qtm_data_file_flag)
									{
										qtm_data_file_ns::QtmDataDiskMap * qscript_temp_2 = new qtm_data_file_ns::QtmDataDiskMap(q1_list.questionList[i1*2+i2], qtm_data_file);
										qtm_datafile_question_disk_map.push_back(qscript_temp_2);
									}
								}
								stack_of_loop_indices.pop_back();
							}
						}
						for (int32_t i2 = 0;i2<3; ++i2)
						{
							stack_of_loop_indices.push_back(i2);
							{
								int32_t consolidated_for_loop_index_4 = i1*3+i2;
								AsciiFlatFileQuestionDiskMap * qscript_temp_3 = new AsciiFlatFileQuestionDiskMap(q2_list.questionList[i1*3+i2], current_map_pos);
								current_map_pos += qscript_temp_3->GetTotalLength();
								ascii_flatfile_question_disk_map.push_back(qscript_temp_3);
								if (write_qtm_data_file_flag)
								{
									qtm_data_file_ns::QtmDataDiskMap * qscript_temp_4 = new qtm_data_file_ns::QtmDataDiskMap(q2_list.questionList[i1*3+i2], qtm_data_file);
									qtm_datafile_question_disk_map.push_back(qscript_temp_4);
								}
							}
							stack_of_loop_indices.pop_back();
						}
					}
					stack_of_loop_indices.pop_back();
				}
				AsciiFlatFileQuestionDiskMap * qscript_temp_5 = new AsciiFlatFileQuestionDiskMap(q3_1, current_map_pos);
				current_map_pos += qscript_temp_5->GetTotalLength();
				ascii_flatfile_question_disk_map.push_back(qscript_temp_5);
				if (write_qtm_data_file_flag)
				{
					qtm_data_file_ns::QtmDataDiskMap * qscript_temp_6 = new qtm_data_file_ns::QtmDataDiskMap(q3_1, qtm_data_file);
					qtm_datafile_question_disk_map.push_back(qscript_temp_6);
				}
				AsciiFlatFileQuestionDiskMap * qscript_temp_7 = new AsciiFlatFileQuestionDiskMap(q3_2, current_map_pos);
				current_map_pos += qscript_temp_7->GetTotalLength();
				ascii_flatfile_question_disk_map.push_back(qscript_temp_7);
				if (write_qtm_data_file_flag)
				{
					qtm_data_file_ns::QtmDataDiskMap * qscript_temp_8 = new qtm_data_file_ns::QtmDataDiskMap(q3_2, qtm_data_file);
					qtm_datafile_question_disk_map.push_back(qscript_temp_8);
				}
				for (int32_t i1 = 0;i1<5; ++i1)
				{
					vector<int32_t> stack_of_loop_indices;
					stack_of_loop_indices.push_back(i1);
					{
						int32_t consolidated_for_loop_index_5 = i1;
						{
							for (int32_t i2 = 0;i2<2; ++i2)
							{
								stack_of_loop_indices.push_back(i2);
								{
									int32_t consolidated_for_loop_index_7 = i1*2+i2;
									AsciiFlatFileQuestionDiskMap * qscript_temp_9 = new AsciiFlatFileQuestionDiskMap(q4_list.questionList[i1*2+i2], current_map_pos);
									current_map_pos += qscript_temp_9->GetTotalLength();
									ascii_flatfile_question_disk_map.push_back(qscript_temp_9);
									if (write_qtm_data_file_flag)
									{
										qtm_data_file_ns::QtmDataDiskMap * qscript_temp_10 = new qtm_data_file_ns::QtmDataDiskMap(q4_list.questionList[i1*2+i2], qtm_data_file);
										qtm_datafile_question_disk_map.push_back(qscript_temp_10);
									}
								}
								stack_of_loop_indices.pop_back();
							}
						}
						for (int32_t i2 = 0;i2<3; ++i2)
						{
							stack_of_loop_indices.push_back(i2);
							{
								int32_t consolidated_for_loop_index_8 = i1*3+i2;
								AsciiFlatFileQuestionDiskMap * qscript_temp_11 = new AsciiFlatFileQuestionDiskMap(q5_list.questionList[i1*3+i2], current_map_pos);
								current_map_pos += qscript_temp_11->GetTotalLength();
								ascii_flatfile_question_disk_map.push_back(qscript_temp_11);
								if (write_qtm_data_file_flag)
								{
									qtm_data_file_ns::QtmDataDiskMap * qscript_temp_12 = new qtm_data_file_ns::QtmDataDiskMap(q5_list.questionList[i1*3+i2], qtm_data_file);
									qtm_datafile_question_disk_map.push_back(qscript_temp_12);
								}
							}
							stack_of_loop_indices.pop_back();
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
			len_flat_file_output_buffer = current_map_pos+1;
			flat_file_output_buffer = new char[len_flat_file_output_buffer];
			memset(flat_file_output_buffer, ' ', len_flat_file_output_buffer-1);
			flat_file_output_buffer[len_flat_file_output_buffer-1] = 0;
			string flat_file_name(jno + string(".dat"));
			flat_file.open(flat_file_name.c_str(), ios_base::out | ios_base::trunc);
			if (write_qtm_data_file_flag)
			{
				string qtm_map_file_name(jno + string(".qmap"));
				fstream qtm_map_file(qtm_map_file_name.c_str(), ios_base::out|ios_base::ate);
				print_map_header(qtm_map_file);
				for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i)
				{
					qtm_datafile_question_disk_map[i]->print_map(qtm_map_file);
				}
				string qtm_qax_file_name(jno + string(".qax"));
				fstream qtm_qax_file(qtm_qax_file_name.c_str(), ios_base::out|ios_base::ate);
				for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i)
				{
					qtm_datafile_question_disk_map[i]->print_qax(qtm_qax_file);
				}
				qtm_datafile_question_disk_map[0]->qtmDataFile_.AllocateCards();
				qtm_datafile_question_disk_map[0]->qtmDataFile_.Reset();
				string qtm_disk_file_name(jno + string(".qdat"));
				qtm_disk_file.open(qtm_disk_file_name.c_str(), ios_base::out | ios_base::trunc);
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
		if (write_data_file_flag||write_qtm_data_file_flag)
		{
			ser_no = read_a_serial_no();
			if (ser_no == 0)
			{
				exit(1);
			}
		}
		else
		{
			int exists = check_if_reg_file_exists(jno, ser_no);
			if(exists == 1)
			{
				load_data(jno,ser_no);
				merge_disk_data_into_questions(qscript_stdout, last_question_answered, last_question_visited);
			}
		}

		start_of_questions:
		if(back_jump == true)
		{
			fprintf(qscript_stdout, "have reached start_of_questions with back_jump");
		}
		{
			/* compound statement on line no: 2 questionsInBlock_, size:6 q1, q2, q3_1, q3_2, q4, q5,  */
			int32_t i1 = 0;
			int32_t i2 = 0;
			int32_t i3 = 0;
			for (i1 = 0;i1<5;i1 = i1+1)
			{
				int32_t consolidated_for_loop_index_1 = i1;
				/* compound statement on line no: 8 questionsInBlock_, size:2 q1, q2,  */
				if (i1>2)		 // ifStatementStack.size(): 0
				{
					{
						/* compound statement on line no: 11 questionsInBlock_, size:1 q1,  */
						for (i2 = 0;i2<2;i2 = i2+1)
						{
							int32_t consolidated_for_loop_index_3 = i1*2+i2;
							/* compound statement on line no: 12 questionsInBlock_, size:1 q1,  */
							/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():2 */
							lab_q1:
							if( back_jump == true  && q1_list.questionList[consolidated_for_loop_index_3]->isAnswered_ == true )
							{
								/* ENTER AbstractQuestion::SetupArrayQuestionRestore */
								/* ENTER:AbstractQuestion::PrintRestoreMyPreviousIterationsData */
								for(int32_t xtcc_i = 0; xtcc_i < consolidated_for_loop_index_3-1;++xtcc_i)
								{
									ostringstream temp_map_key;
									temp_map_key << "q1" << "_" << xtcc_i << "$" << consolidated_for_loop_index_3;

									q1_list.questionList[xtcc_i]->input_data = q1_scope_question_t[ temp_map_key.str()];
								}
								/* EXIT:AbstractQuestion::PrintRestoreMyPreviousIterationsData */
								ostringstream map_key_0;
								map_key_0<< "i1" << "_" << consolidated_for_loop_index_3;
								i1 = q1_scope_int32_t[map_key_0.str()];
								map_key_0<< "i2" << "_" << consolidated_for_loop_index_3;
								i2 = q1_scope_int32_t[map_key_0.str()];
								map_key_0<< "i3" << "_" << consolidated_for_loop_index_3;
								i3 = q1_scope_int32_t[map_key_0.str()];
								/* ENTER AbstractQuestion::RestoreQuestionsInMyBlockThatAreAfterMe */
								/* questions in my block (q1):q1,q2,*/
								/*q1 and q2 :belong to different blocks */
								for(int32_t xtcc_i = 0; xtcc_i < 5*3;++xtcc_i)
								{
									ostringstream map_key;
									map_key << "q1" << "_" << xtcc_i << "$" << consolidated_for_loop_index_3;
									q2_list.questionList[xtcc_i]->input_data = q2_scope_question_t[map_key.str()]  ;

								}
								/* EXIT AbstractQuestion::RestoreQuestionsInMyBlockThatAreAfterMe */
								/* EXIT AbstractQuestion::SetupArrayQuestionRestore */
							}
							/* ENTER AbstractQuestion::SetupArrayQuestionSave */
							/* ENTER:AbstractQuestion::PrintSaveMyPreviousIterationsData */
							for(int32_t xtcc_i = 0; xtcc_i < consolidated_for_loop_index_3-1;++xtcc_i)
							{
								ostringstream temp_map_key;
								temp_map_key << "q1" << "_" << xtcc_i << "$" << consolidated_for_loop_index_3;

								q1_scope_question_t[ temp_map_key.str()] = q1_list.questionList[xtcc_i]->input_data;
							}
							/* EXIT:AbstractQuestion::PrintSaveMyPreviousIterationsData */
							ostringstream map_key_1;
							map_key_1<< "i1" << "_" << consolidated_for_loop_index_3;
							q1_scope_int32_t[map_key_1.str()] = i1;
							map_key_1<< "i2" << "_" << consolidated_for_loop_index_3;
							q1_scope_int32_t[map_key_1.str()] = i2;
							map_key_1<< "i3" << "_" << consolidated_for_loop_index_3;
							q1_scope_int32_t[map_key_1.str()] = i3;
							/* ENTER AbstractQuestion::SaveQuestionsInMyBlockThatAreAfterMe */
							/* questions in my block (q1):q1,q2,*/
							/*q1 and q2 :belong to different blocks */
							for(int32_t xtcc_i = 0; xtcc_i < 5*3;++xtcc_i)
							{
								ostringstream map_key;
								map_key << "q1" << "_" << xtcc_i << "$" << consolidated_for_loop_index_3;
								q2_scope_question_t[map_key.str()] = q2_list.questionList[xtcc_i]->input_data;

							}
							/* EXIT AbstractQuestion::SaveQuestionsInMyBlockThatAreAfterMe */
							/* EXIT AbstractQuestion::SetupArrayQuestionSave */
							/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
							if (data_entry_window == 0)
							{
								cout << "jumpToQuestion = " << jumpToQuestion << endl;  cout << "jumpToIndex = " << jumpToIndex << endl;
							}

							if(!q1_list.questionList[i1*2+i2]->isAnswered_||stopAtNextQuestion||
								(p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q1_list.questionList[i1*2+i2]) ||
								(jumpToQuestion == "q1" && jumpToIndex ==  consolidated_for_loop_index_3) )
							{
								label_eval_q1:
								if( jumpToQuestion == "q1" && jumpToIndex == consolidated_for_loop_index_3)
								{
									back_jump = false;
									jumpToIndex = -1;
								}
								if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q1_list.questionList[i1*2+i2] &&  q1_list.questionList[i1*2+i2]->isAnswered_ == true)
								{
									stopAtNextQuestion = true;
									fprintf (qscript_stdout, " at question:  q1 arming stopAtNextQuestion = true \n");
								}
								else if ( q1_list.questionList[i1*2+i2] ->question_attributes.hidden_==false)
								{
									//q1_list.questionList[i1*2+i2]->eval(question_window, stub_list_window, data_entry_window);
									last_question_visited = q1_list.questionList[i1*2+i2];
									stopAtNextQuestion = false;
									return q1_list.questionList[i1*2+i2];
								}
								if(user_navigation == NAVIGATE_PREVIOUS)
								{
									AbstractQuestion * target_question = ComputePreviousQuestion(q1_list.questionList[consolidated_for_loop_index_3]);
									if(target_question == 0)
										goto label_eval_q1;
									else
									{
										jumpToQuestion = target_question->questionName_;
										if(target_question->type_ == QUESTION_ARR_TYPE)
										{
											jumpToIndex = ComputeJumpToIndex(target_question);
										}
										if (data_entry_window==0) cout << "target question: " << jumpToQuestion;
										if (data_entry_window==0) cout << "target question Index: " << jumpToIndex;
										back_jump = true;
										user_navigation = NOT_SET;
										goto start_of_questions;
									}
								}
								else if (user_navigation == NAVIGATE_NEXT)
								{
									stopAtNextQuestion = true;
									user_navigation = NOT_SET;
								}
								else if (user_navigation == JUMP_TO_QUESTION)
								{
									DisplayActiveQuestions();
									GetUserResponse(jumpToQuestion, jumpToIndex);
									user_navigation = NOT_SET;
									goto start_of_questions;
								}
								else if (user_navigation == SAVE_DATA)
								{
									write_data_to_disk(question_list, jno, ser_no);
									cout << "saved partial data\n";
									if (data_entry_window) mvwprintw(data_entry_window,2,50, "saved partial data");
									else   cout << "saved partial data\n";
									if (q1_list.questionList[consolidated_for_loop_index_3]->isAnswered_==false)
									{
										cout << "question has not been answered ... jumping back\n";
										goto label_eval_q1;
									}
								}
								else
								{
									last_question_answered = q1_list.questionList[consolidated_for_loop_index_3];
								}
							}
						}
					}
				}
				for (i2 = 0;i2<3;i2 = i2+1)
				{
					int32_t consolidated_for_loop_index_4 = i1*3+i2;
					/* compound statement on line no: 16 questionsInBlock_, size:1 q2,  */
					/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():2 */
					lab_q2:
					if( back_jump == true  && q2_list.questionList[consolidated_for_loop_index_4]->isAnswered_ == true )
					{
						/* ENTER AbstractQuestion::SetupArrayQuestionRestore */
						/* ENTER:AbstractQuestion::PrintRestoreMyPreviousIterationsData */
						for(int32_t xtcc_i = 0; xtcc_i < consolidated_for_loop_index_4-1;++xtcc_i)
						{
							ostringstream temp_map_key;
							temp_map_key << "q2" << "_" << xtcc_i << "$" << consolidated_for_loop_index_4;

							q2_list.questionList[xtcc_i]->input_data = q2_scope_question_t[ temp_map_key.str()];
						}
						/* EXIT:AbstractQuestion::PrintRestoreMyPreviousIterationsData */
						ostringstream map_key_2;
						/* ENTER AbstractQuestion::PrintRestoreArrayQuestion q1 at location: q2 */
						/* questionsInBlock_: q2  */
						/*q2 and q1 :belong to different blocks */
						for(int32_t xtcc_i = 0; xtcc_i < 5*2;++xtcc_i)
						{
							ostringstream map_key;
							map_key << "q2" << "_" << xtcc_i << "$" << consolidated_for_loop_index_4;
							q1_list.questionList[xtcc_i]->input_data = q1_scope_question_t[map_key.str()];

						}
						/* EXIT AbstractQuestion::PrintRestoreArrayQuestion */
						map_key_2<< "i1" << "_" << consolidated_for_loop_index_4;
						i1 = q2_scope_int32_t[map_key_2.str()];
						map_key_2<< "i2" << "_" << consolidated_for_loop_index_4;
						i2 = q2_scope_int32_t[map_key_2.str()];
						map_key_2<< "i3" << "_" << consolidated_for_loop_index_4;
						i3 = q2_scope_int32_t[map_key_2.str()];
						/* ENTER AbstractQuestion::RestoreQuestionsInMyBlockThatAreAfterMe */
						/* questions in my block (q2):q1,q2,*/
						/* I = q2 is the last question in in block  nothing to do */
						/* EXIT AbstractQuestion::RestoreQuestionsInMyBlockThatAreAfterMe */
						/* EXIT AbstractQuestion::SetupArrayQuestionRestore */
					}
					/* ENTER AbstractQuestion::SetupArrayQuestionSave */
					/* ENTER:AbstractQuestion::PrintSaveMyPreviousIterationsData */
					for(int32_t xtcc_i = 0; xtcc_i < consolidated_for_loop_index_4-1;++xtcc_i)
					{
						ostringstream temp_map_key;
						temp_map_key << "q2" << "_" << xtcc_i << "$" << consolidated_for_loop_index_4;

						q2_scope_question_t[ temp_map_key.str()] = q2_list.questionList[xtcc_i]->input_data;
					}
					/* EXIT:AbstractQuestion::PrintSaveMyPreviousIterationsData */
					ostringstream map_key_3;
					/* ENTER PrintSaveArrayQuestion q1 at location: q2*/
					/* questionsInBlock_: q2  */
					/*q2 and q1 :belong to different blocks */
					for(int32_t xtcc_i = 0; xtcc_i < 5*2;++xtcc_i)
					{
						ostringstream map_key;
						map_key << "q2" << "_" << xtcc_i << "$" << consolidated_for_loop_index_4;
						q1_scope_question_t[map_key.str()] = q1_list.questionList[xtcc_i]->input_data;

					}
					/* EXIT PrintSaveArrayQuestion */
					map_key_3<< "i1" << "_" << consolidated_for_loop_index_4;
					q2_scope_int32_t[map_key_3.str()] = i1;
					map_key_3<< "i2" << "_" << consolidated_for_loop_index_4;
					q2_scope_int32_t[map_key_3.str()] = i2;
					map_key_3<< "i3" << "_" << consolidated_for_loop_index_4;
					q2_scope_int32_t[map_key_3.str()] = i3;
					/* ENTER AbstractQuestion::SaveQuestionsInMyBlockThatAreAfterMe */
					/* questions in my block (q2):q1,q2,*/
					/* I = q2 is the last question in in block  nothing to do */
					/* EXIT AbstractQuestion::SaveQuestionsInMyBlockThatAreAfterMe */
					/* EXIT AbstractQuestion::SetupArrayQuestionSave */
					/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
					if (data_entry_window == 0)
					{
						cout << "jumpToQuestion = " << jumpToQuestion << endl;  cout << "jumpToIndex = " << jumpToIndex << endl;
					}

					if(!q2_list.questionList[i1*3+i2]->isAnswered_||stopAtNextQuestion||
						(p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q2_list.questionList[i1*3+i2]) ||
						(jumpToQuestion == "q2" && jumpToIndex ==  consolidated_for_loop_index_4) )
					{
						label_eval_q2:
						if( jumpToQuestion == "q2" && jumpToIndex == consolidated_for_loop_index_4)
						{
							back_jump = false;
							jumpToIndex = -1;
						}
						if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q2_list.questionList[i1*3+i2] &&  q2_list.questionList[i1*3+i2]->isAnswered_ == true)
						{
							stopAtNextQuestion = true;
							fprintf (qscript_stdout, " at question:  q2 arming stopAtNextQuestion = true \n");
						}
						else if ( q2_list.questionList[i1*3+i2] ->question_attributes.hidden_==false)
						{
							//q2_list.questionList[i1*3+i2]->eval(question_window, stub_list_window, data_entry_window);
							last_question_visited = q2_list.questionList[i1*3+i2];
							stopAtNextQuestion = false;
							return q2_list.questionList[i1*3+i2];
						}
						if(user_navigation == NAVIGATE_PREVIOUS)
						{
							AbstractQuestion * target_question = ComputePreviousQuestion(q2_list.questionList[consolidated_for_loop_index_4]);
							if(target_question == 0)
								goto label_eval_q2;
							else
							{
								jumpToQuestion = target_question->questionName_;
								if(target_question->type_ == QUESTION_ARR_TYPE)
								{
									jumpToIndex = ComputeJumpToIndex(target_question);
								}
								if (data_entry_window==0) cout << "target question: " << jumpToQuestion;
								if (data_entry_window==0) cout << "target question Index: " << jumpToIndex;
								back_jump = true;
								user_navigation = NOT_SET;
								goto start_of_questions;
							}
						}
						else if (user_navigation == NAVIGATE_NEXT)
						{
							stopAtNextQuestion = true;
							user_navigation = NOT_SET;
						}
						else if (user_navigation == JUMP_TO_QUESTION)
						{
							DisplayActiveQuestions();
							GetUserResponse(jumpToQuestion, jumpToIndex);
							user_navigation = NOT_SET;
							goto start_of_questions;
						}
						else if (user_navigation == SAVE_DATA)
						{
							write_data_to_disk(question_list, jno, ser_no);
							cout << "saved partial data\n";
							if (data_entry_window) mvwprintw(data_entry_window,2,50, "saved partial data");
							else   cout << "saved partial data\n";
							if (q2_list.questionList[consolidated_for_loop_index_4]->isAnswered_==false)
							{
								cout << "question has not been answered ... jumping back\n";
								goto label_eval_q2;
							}
						}
						else
						{
							last_question_answered = q2_list.questionList[consolidated_for_loop_index_4];
						}
					}
				}
			}
			/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
			lab_q3_1:
			if( back_jump == true  && q3_1->isAnswered_ == true )
			{
				/* AbstractQuestion::SetupSimpleQuestionRestore */
				/* ENTER AbstractQuestion::PrintRestoreArrayQuestion q1 at location: q3_1 */
				/* questionsInBlock_: q1 q2 q3_1 q3_2 q4 q5  */
				/*q3_1 is at a higher nest level than q1*/
				/* treat as if the question is outside our block */
				/*q3_1 and q1 :belong to different blocks */
				for(int32_t xtcc_i = 0; xtcc_i < 5*2;++xtcc_i)
				{
					ostringstream map_key;
					map_key << "q3_1" << "_" << xtcc_i ;
					q1_list.questionList[xtcc_i]->input_data = q1_scope_question_t[map_key.str()];

				}
				/* EXIT AbstractQuestion::PrintRestoreArrayQuestion */
				/* ENTER AbstractQuestion::PrintRestoreArrayQuestion q2 at location: q3_1 */
				/* questionsInBlock_: q1 q2 q3_1 q3_2 q4 q5  */
				/*q3_1 is at a higher nest level than q2*/
				/* treat as if the question is outside our block */
				/*q3_1 and q2 :belong to different blocks */
				for(int32_t xtcc_i = 0; xtcc_i < 5*3;++xtcc_i)
				{
					ostringstream map_key;
					map_key << "q3_1" << "_" << xtcc_i ;
					q2_list.questionList[xtcc_i]->input_data = q2_scope_question_t[map_key.str()];

				}
				/* EXIT AbstractQuestion::PrintRestoreArrayQuestion */
				i1 = q3_1_scope_int32_t["i1"];
				i2 = q3_1_scope_int32_t["i2"];
				i3 = q3_1_scope_int32_t["i3"];
				if( jumpToQuestion == "q3_1")
				{
					back_jump = false;
				}
			}
			/* AbstractQuestion::SetupSimpleQuestionSave */
			/* ENTER PrintSaveArrayQuestion q1 at location: q3_1*/
			/* questionsInBlock_: q1 q2 q3_1 q3_2 q4 q5  */
			/*q3_1 is at a higher nest level than q1*/
			/* treat as if the question is outside our block */
			/*q3_1 and q1 :belong to different blocks */
			for(int32_t xtcc_i = 0; xtcc_i < 5*2;++xtcc_i)
			{
				ostringstream map_key;
				map_key << "q3_1" << "_" << xtcc_i ;
				q1_scope_question_t[map_key.str()] = q1_list.questionList[xtcc_i]->input_data;

			}
			/* EXIT PrintSaveArrayQuestion */
			/* ENTER PrintSaveArrayQuestion q2 at location: q3_1*/
			/* questionsInBlock_: q1 q2 q3_1 q3_2 q4 q5  */
			/*q3_1 is at a higher nest level than q2*/
			/* treat as if the question is outside our block */
			/*q3_1 and q2 :belong to different blocks */
			for(int32_t xtcc_i = 0; xtcc_i < 5*3;++xtcc_i)
			{
				ostringstream map_key;
				map_key << "q3_1" << "_" << xtcc_i ;
				q2_scope_question_t[map_key.str()] = q2_list.questionList[xtcc_i]->input_data;

			}
			/* EXIT PrintSaveArrayQuestion */
			q3_1_scope_int32_t["i1"] = i1;
			q3_1_scope_int32_t["i2"] = i2;
			q3_1_scope_int32_t["i3"] = i3;
			/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
			if(!q3_1->isAnswered_ ||
				stopAtNextQuestion ||
				(p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q3_1) || jumpToQuestion == "q3_1" )
			{
				if(stopAtNextQuestion && q3_1->question_attributes.hidden_ == false )
				{
					stopAtNextQuestion = false;  fprintf (qscript_stdout, " at question:  q3_1 disarming stopAtNextQuestion = false \n");

				}
				if (jumpToQuestion == "q3_1")
				{
					jumpToQuestion = "";
				}
				label_eval_q3_1:
				if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q3_1)
				{
					stopAtNextQuestion = true;
					fprintf (qscript_stdout, " at question:  q3_1 arming stopAtNextQuestion = true \n");
				}
				else if (q3_1->question_attributes.hidden_==false)
				{
					// q3_1->eval(question_window, stub_list_window, data_entry_window);
					last_question_visited = q3_1;
					fprintf(qscript_stdout, "last_question_visited: q3_1\n");
					return q3_1;
				}
			}
			/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
			lab_q3_2:
			if( back_jump == true  && q3_2->isAnswered_ == true )
			{
				/* AbstractQuestion::SetupSimpleQuestionRestore */
				/* ENTER AbstractQuestion::PrintRestoreArrayQuestion q1 at location: q3_2 */
				/* questionsInBlock_: q1 q2 q3_1 q3_2 q4 q5  */
				/*q3_2 is at a higher nest level than q1*/
				/* treat as if the question is outside our block */
				/*q3_2 and q1 :belong to different blocks */
				for(int32_t xtcc_i = 0; xtcc_i < 5*2;++xtcc_i)
				{
					ostringstream map_key;
					map_key << "q3_2" << "_" << xtcc_i ;
					q1_list.questionList[xtcc_i]->input_data = q1_scope_question_t[map_key.str()];

				}
				/* EXIT AbstractQuestion::PrintRestoreArrayQuestion */
				/* ENTER AbstractQuestion::PrintRestoreArrayQuestion q2 at location: q3_2 */
				/* questionsInBlock_: q1 q2 q3_1 q3_2 q4 q5  */
				/*q3_2 is at a higher nest level than q2*/
				/* treat as if the question is outside our block */
				/*q3_2 and q2 :belong to different blocks */
				for(int32_t xtcc_i = 0; xtcc_i < 5*3;++xtcc_i)
				{
					ostringstream map_key;
					map_key << "q3_2" << "_" << xtcc_i ;
					q2_list.questionList[xtcc_i]->input_data = q2_scope_question_t[map_key.str()];

				}
				/* EXIT AbstractQuestion::PrintRestoreArrayQuestion */
				q3_1->input_data = q3_1_scope_question_t["q3_2"];
				i1 = q3_2_scope_int32_t["i1"];
				i2 = q3_2_scope_int32_t["i2"];
				i3 = q3_2_scope_int32_t["i3"];
				if( jumpToQuestion == "q3_2")
				{
					back_jump = false;
				}
			}
			/* AbstractQuestion::SetupSimpleQuestionSave */
			/* ENTER PrintSaveArrayQuestion q1 at location: q3_2*/
			/* questionsInBlock_: q1 q2 q3_1 q3_2 q4 q5  */
			/*q3_2 is at a higher nest level than q1*/
			/* treat as if the question is outside our block */
			/*q3_2 and q1 :belong to different blocks */
			for(int32_t xtcc_i = 0; xtcc_i < 5*2;++xtcc_i)
			{
				ostringstream map_key;
				map_key << "q3_2" << "_" << xtcc_i ;
				q1_scope_question_t[map_key.str()] = q1_list.questionList[xtcc_i]->input_data;

			}
			/* EXIT PrintSaveArrayQuestion */
			/* ENTER PrintSaveArrayQuestion q2 at location: q3_2*/
			/* questionsInBlock_: q1 q2 q3_1 q3_2 q4 q5  */
			/*q3_2 is at a higher nest level than q2*/
			/* treat as if the question is outside our block */
			/*q3_2 and q2 :belong to different blocks */
			for(int32_t xtcc_i = 0; xtcc_i < 5*3;++xtcc_i)
			{
				ostringstream map_key;
				map_key << "q3_2" << "_" << xtcc_i ;
				q2_scope_question_t[map_key.str()] = q2_list.questionList[xtcc_i]->input_data;

			}
			/* EXIT PrintSaveArrayQuestion */
			q3_1_scope_question_t["q3_2"] = q3_1->input_data;
			q3_2_scope_int32_t["i1"] = i1;
			q3_2_scope_int32_t["i2"] = i2;
			q3_2_scope_int32_t["i3"] = i3;
			/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
			if(!q3_2->isAnswered_ ||
				stopAtNextQuestion ||
				(p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q3_2) || jumpToQuestion == "q3_2" )
			{
				if(stopAtNextQuestion && q3_2->question_attributes.hidden_ == false )
				{
					stopAtNextQuestion = false;  fprintf (qscript_stdout, " at question:  q3_2 disarming stopAtNextQuestion = false \n");

				}
				if (jumpToQuestion == "q3_2")
				{
					jumpToQuestion = "";
				}
				label_eval_q3_2:
				if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q3_2)
				{
					stopAtNextQuestion = true;
					fprintf (qscript_stdout, " at question:  q3_2 arming stopAtNextQuestion = true \n");
				}
				else if (q3_2->question_attributes.hidden_==false)
				{
					// q3_2->eval(question_window, stub_list_window, data_entry_window);
					last_question_visited = q3_2;
					fprintf(qscript_stdout, "last_question_visited: q3_2\n");
					return q3_2;
				}
			}
			for (i1 = 0;i1<5;i1 = i1+1)
			{
				int32_t consolidated_for_loop_index_5 = i1;
				/* compound statement on line no: 25 questionsInBlock_, size:2 q4, q5,  */
				if (i1>2)		 // ifStatementStack.size(): 0
				{
					{
						/* compound statement on line no: 28 questionsInBlock_, size:1 q4,  */
						for (i2 = 0;i2<2;i2 = i2+1)
						{
							int32_t consolidated_for_loop_index_7 = i1*2+i2;
							/* compound statement on line no: 29 questionsInBlock_, size:1 q4,  */
							/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():2 */
							lab_q4:
							if( back_jump == true  && q4_list.questionList[consolidated_for_loop_index_7]->isAnswered_ == true )
							{
								/* ENTER AbstractQuestion::SetupArrayQuestionRestore */
								/* ENTER:AbstractQuestion::PrintRestoreMyPreviousIterationsData */
								for(int32_t xtcc_i = 0; xtcc_i < consolidated_for_loop_index_7-1;++xtcc_i)
								{
									ostringstream temp_map_key;
									temp_map_key << "q4" << "_" << xtcc_i << "$" << consolidated_for_loop_index_7;

									q4_list.questionList[xtcc_i]->input_data = q4_scope_question_t[ temp_map_key.str()];
								}
								/* EXIT:AbstractQuestion::PrintRestoreMyPreviousIterationsData */
								ostringstream map_key_4;
								/* ENTER AbstractQuestion::PrintRestoreArrayQuestion q1 at location: q4 */
								/* questionsInBlock_: q4  */
								/*q4 and q1 :belong to different blocks */
								for(int32_t xtcc_i = 0; xtcc_i < 5*2;++xtcc_i)
								{
									ostringstream map_key;
									map_key << "q4" << "_" << xtcc_i << "$" << consolidated_for_loop_index_7;
									q1_list.questionList[xtcc_i]->input_data = q1_scope_question_t[map_key.str()];

								}
								/* EXIT AbstractQuestion::PrintRestoreArrayQuestion */
								/* ENTER AbstractQuestion::PrintRestoreArrayQuestion q2 at location: q4 */
								/* questionsInBlock_: q4  */
								/*q4 and q2 :belong to different blocks */
								for(int32_t xtcc_i = 0; xtcc_i < 5*3;++xtcc_i)
								{
									ostringstream map_key;
									map_key << "q4" << "_" << xtcc_i << "$" << consolidated_for_loop_index_7;
									q2_list.questionList[xtcc_i]->input_data = q2_scope_question_t[map_key.str()];

								}
								/* EXIT AbstractQuestion::PrintRestoreArrayQuestion */
								map_key_4<< "q3_1" << "_" << consolidated_for_loop_index_7;
								q3_1->input_data = q3_1_scope_question_t[map_key_4.str()];
								map_key_4<< "q3_2" << "_" << consolidated_for_loop_index_7;
								q3_2->input_data = q3_2_scope_question_t[map_key_4.str()];
								map_key_4<< "i1" << "_" << consolidated_for_loop_index_7;
								i1 = q4_scope_int32_t[map_key_4.str()];
								map_key_4<< "i2" << "_" << consolidated_for_loop_index_7;
								i2 = q4_scope_int32_t[map_key_4.str()];
								map_key_4<< "i3" << "_" << consolidated_for_loop_index_7;
								i3 = q4_scope_int32_t[map_key_4.str()];
								/* ENTER AbstractQuestion::RestoreQuestionsInMyBlockThatAreAfterMe */
								/* questions in my block (q4):q4,q5,*/
								/*q4 and q5 :belong to different blocks */
								for(int32_t xtcc_i = 0; xtcc_i < 5*3;++xtcc_i)
								{
									ostringstream map_key;
									map_key << "q4" << "_" << xtcc_i << "$" << consolidated_for_loop_index_7;
									q5_list.questionList[xtcc_i]->input_data = q5_scope_question_t[map_key.str()]  ;

								}
								/* EXIT AbstractQuestion::RestoreQuestionsInMyBlockThatAreAfterMe */
								/* EXIT AbstractQuestion::SetupArrayQuestionRestore */
							}
							/* ENTER AbstractQuestion::SetupArrayQuestionSave */
							/* ENTER:AbstractQuestion::PrintSaveMyPreviousIterationsData */
							for(int32_t xtcc_i = 0; xtcc_i < consolidated_for_loop_index_7-1;++xtcc_i)
							{
								ostringstream temp_map_key;
								temp_map_key << "q4" << "_" << xtcc_i << "$" << consolidated_for_loop_index_7;

								q4_scope_question_t[ temp_map_key.str()] = q4_list.questionList[xtcc_i]->input_data;
							}
							/* EXIT:AbstractQuestion::PrintSaveMyPreviousIterationsData */
							ostringstream map_key_5;
							/* ENTER PrintSaveArrayQuestion q1 at location: q4*/
							/* questionsInBlock_: q4  */
							/*q4 and q1 :belong to different blocks */
							for(int32_t xtcc_i = 0; xtcc_i < 5*2;++xtcc_i)
							{
								ostringstream map_key;
								map_key << "q4" << "_" << xtcc_i << "$" << consolidated_for_loop_index_7;
								q1_scope_question_t[map_key.str()] = q1_list.questionList[xtcc_i]->input_data;

							}
							/* EXIT PrintSaveArrayQuestion */
							/* ENTER PrintSaveArrayQuestion q2 at location: q4*/
							/* questionsInBlock_: q4  */
							/*q4 and q2 :belong to different blocks */
							for(int32_t xtcc_i = 0; xtcc_i < 5*3;++xtcc_i)
							{
								ostringstream map_key;
								map_key << "q4" << "_" << xtcc_i << "$" << consolidated_for_loop_index_7;
								q2_scope_question_t[map_key.str()] = q2_list.questionList[xtcc_i]->input_data;

							}
							/* EXIT PrintSaveArrayQuestion */
							map_key_5<< "q3_1" << "_" << consolidated_for_loop_index_7;
							q3_1_scope_question_t[map_key_5.str()] = q3_1->input_data;
							map_key_5<< "q3_2" << "_" << consolidated_for_loop_index_7;
							q3_2_scope_question_t[map_key_5.str()] = q3_2->input_data;
							map_key_5<< "i1" << "_" << consolidated_for_loop_index_7;
							q4_scope_int32_t[map_key_5.str()] = i1;
							map_key_5<< "i2" << "_" << consolidated_for_loop_index_7;
							q4_scope_int32_t[map_key_5.str()] = i2;
							map_key_5<< "i3" << "_" << consolidated_for_loop_index_7;
							q4_scope_int32_t[map_key_5.str()] = i3;
							/* ENTER AbstractQuestion::SaveQuestionsInMyBlockThatAreAfterMe */
							/* questions in my block (q4):q4,q5,*/
							/*q4 and q5 :belong to different blocks */
							for(int32_t xtcc_i = 0; xtcc_i < 5*3;++xtcc_i)
							{
								ostringstream map_key;
								map_key << "q4" << "_" << xtcc_i << "$" << consolidated_for_loop_index_7;
								q5_scope_question_t[map_key.str()] = q5_list.questionList[xtcc_i]->input_data;

							}
							/* EXIT AbstractQuestion::SaveQuestionsInMyBlockThatAreAfterMe */
							/* EXIT AbstractQuestion::SetupArrayQuestionSave */
							/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
							if (data_entry_window == 0)
							{
								cout << "jumpToQuestion = " << jumpToQuestion << endl;  cout << "jumpToIndex = " << jumpToIndex << endl;
							}

							if(!q4_list.questionList[i1*2+i2]->isAnswered_||stopAtNextQuestion||
								(p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q4_list.questionList[i1*2+i2]) ||
								(jumpToQuestion == "q4" && jumpToIndex ==  consolidated_for_loop_index_7) )
							{
								label_eval_q4:
								if( jumpToQuestion == "q4" && jumpToIndex == consolidated_for_loop_index_7)
								{
									back_jump = false;
									jumpToIndex = -1;
								}
								if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q4_list.questionList[i1*2+i2] &&  q4_list.questionList[i1*2+i2]->isAnswered_ == true)
								{
									stopAtNextQuestion = true;
									fprintf (qscript_stdout, " at question:  q4 arming stopAtNextQuestion = true \n");
								}
								else if ( q4_list.questionList[i1*2+i2] ->question_attributes.hidden_==false)
								{
									//q4_list.questionList[i1*2+i2]->eval(question_window, stub_list_window, data_entry_window);
									last_question_visited = q4_list.questionList[i1*2+i2];
									stopAtNextQuestion = false;
									return q4_list.questionList[i1*2+i2];
								}
								if(user_navigation == NAVIGATE_PREVIOUS)
								{
									AbstractQuestion * target_question = ComputePreviousQuestion(q4_list.questionList[consolidated_for_loop_index_7]);
									if(target_question == 0)
										goto label_eval_q4;
									else
									{
										jumpToQuestion = target_question->questionName_;
										if(target_question->type_ == QUESTION_ARR_TYPE)
										{
											jumpToIndex = ComputeJumpToIndex(target_question);
										}
										if (data_entry_window==0) cout << "target question: " << jumpToQuestion;
										if (data_entry_window==0) cout << "target question Index: " << jumpToIndex;
										back_jump = true;
										user_navigation = NOT_SET;
										goto start_of_questions;
									}
								}
								else if (user_navigation == NAVIGATE_NEXT)
								{
									stopAtNextQuestion = true;
									user_navigation = NOT_SET;
								}
								else if (user_navigation == JUMP_TO_QUESTION)
								{
									DisplayActiveQuestions();
									GetUserResponse(jumpToQuestion, jumpToIndex);
									user_navigation = NOT_SET;
									goto start_of_questions;
								}
								else if (user_navigation == SAVE_DATA)
								{
									write_data_to_disk(question_list, jno, ser_no);
									cout << "saved partial data\n";
									if (data_entry_window) mvwprintw(data_entry_window,2,50, "saved partial data");
									else   cout << "saved partial data\n";
									if (q4_list.questionList[consolidated_for_loop_index_7]->isAnswered_==false)
									{
										cout << "question has not been answered ... jumping back\n";
										goto label_eval_q4;
									}
								}
								else
								{
									last_question_answered = q4_list.questionList[consolidated_for_loop_index_7];
								}
							}
						}
					}
				}
				for (i2 = 0;i2<3;i2 = i2+1)
				{
					int32_t consolidated_for_loop_index_8 = i1*3+i2;
					/* compound statement on line no: 33 questionsInBlock_, size:1 q5,  */
					/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():2 */
					lab_q5:
					if( back_jump == true  && q5_list.questionList[consolidated_for_loop_index_8]->isAnswered_ == true )
					{
						/* ENTER AbstractQuestion::SetupArrayQuestionRestore */
						/* ENTER:AbstractQuestion::PrintRestoreMyPreviousIterationsData */
						for(int32_t xtcc_i = 0; xtcc_i < consolidated_for_loop_index_8-1;++xtcc_i)
						{
							ostringstream temp_map_key;
							temp_map_key << "q5" << "_" << xtcc_i << "$" << consolidated_for_loop_index_8;

							q5_list.questionList[xtcc_i]->input_data = q5_scope_question_t[ temp_map_key.str()];
						}
						/* EXIT:AbstractQuestion::PrintRestoreMyPreviousIterationsData */
						ostringstream map_key_6;
						/* ENTER AbstractQuestion::PrintRestoreArrayQuestion q1 at location: q5 */
						/* questionsInBlock_: q5  */
						/*q5 and q1 :belong to different blocks */
						for(int32_t xtcc_i = 0; xtcc_i < 5*2;++xtcc_i)
						{
							ostringstream map_key;
							map_key << "q5" << "_" << xtcc_i << "$" << consolidated_for_loop_index_8;
							q1_list.questionList[xtcc_i]->input_data = q1_scope_question_t[map_key.str()];

						}
						/* EXIT AbstractQuestion::PrintRestoreArrayQuestion */
						/* ENTER AbstractQuestion::PrintRestoreArrayQuestion q2 at location: q5 */
						/* questionsInBlock_: q5  */
						/*q5 and q2 :belong to different blocks */
						for(int32_t xtcc_i = 0; xtcc_i < 5*3;++xtcc_i)
						{
							ostringstream map_key;
							map_key << "q5" << "_" << xtcc_i << "$" << consolidated_for_loop_index_8;
							q2_list.questionList[xtcc_i]->input_data = q2_scope_question_t[map_key.str()];

						}
						/* EXIT AbstractQuestion::PrintRestoreArrayQuestion */
						map_key_6<< "q3_1" << "_" << consolidated_for_loop_index_8;
						q3_1->input_data = q3_1_scope_question_t[map_key_6.str()];
						map_key_6<< "q3_2" << "_" << consolidated_for_loop_index_8;
						q3_2->input_data = q3_2_scope_question_t[map_key_6.str()];
						/* ENTER AbstractQuestion::PrintRestoreArrayQuestion q4 at location: q5 */
						/* questionsInBlock_: q5  */
						/*q5 and q4 :belong to different blocks */
						for(int32_t xtcc_i = 0; xtcc_i < 5*2;++xtcc_i)
						{
							ostringstream map_key;
							map_key << "q5" << "_" << xtcc_i << "$" << consolidated_for_loop_index_8;
							q4_list.questionList[xtcc_i]->input_data = q4_scope_question_t[map_key.str()];

						}
						/* EXIT AbstractQuestion::PrintRestoreArrayQuestion */
						map_key_6<< "i1" << "_" << consolidated_for_loop_index_8;
						i1 = q5_scope_int32_t[map_key_6.str()];
						map_key_6<< "i2" << "_" << consolidated_for_loop_index_8;
						i2 = q5_scope_int32_t[map_key_6.str()];
						map_key_6<< "i3" << "_" << consolidated_for_loop_index_8;
						i3 = q5_scope_int32_t[map_key_6.str()];
						/* ENTER AbstractQuestion::RestoreQuestionsInMyBlockThatAreAfterMe */
						/* questions in my block (q5):q4,q5,*/
						/* I = q5 is the last question in in block  nothing to do */
						/* EXIT AbstractQuestion::RestoreQuestionsInMyBlockThatAreAfterMe */
						/* EXIT AbstractQuestion::SetupArrayQuestionRestore */
					}
					/* ENTER AbstractQuestion::SetupArrayQuestionSave */
					/* ENTER:AbstractQuestion::PrintSaveMyPreviousIterationsData */
					for(int32_t xtcc_i = 0; xtcc_i < consolidated_for_loop_index_8-1;++xtcc_i)
					{
						ostringstream temp_map_key;
						temp_map_key << "q5" << "_" << xtcc_i << "$" << consolidated_for_loop_index_8;

						q5_scope_question_t[ temp_map_key.str()] = q5_list.questionList[xtcc_i]->input_data;
					}
					/* EXIT:AbstractQuestion::PrintSaveMyPreviousIterationsData */
					ostringstream map_key_7;
					/* ENTER PrintSaveArrayQuestion q1 at location: q5*/
					/* questionsInBlock_: q5  */
					/*q5 and q1 :belong to different blocks */
					for(int32_t xtcc_i = 0; xtcc_i < 5*2;++xtcc_i)
					{
						ostringstream map_key;
						map_key << "q5" << "_" << xtcc_i << "$" << consolidated_for_loop_index_8;
						q1_scope_question_t[map_key.str()] = q1_list.questionList[xtcc_i]->input_data;

					}
					/* EXIT PrintSaveArrayQuestion */
					/* ENTER PrintSaveArrayQuestion q2 at location: q5*/
					/* questionsInBlock_: q5  */
					/*q5 and q2 :belong to different blocks */
					for(int32_t xtcc_i = 0; xtcc_i < 5*3;++xtcc_i)
					{
						ostringstream map_key;
						map_key << "q5" << "_" << xtcc_i << "$" << consolidated_for_loop_index_8;
						q2_scope_question_t[map_key.str()] = q2_list.questionList[xtcc_i]->input_data;

					}
					/* EXIT PrintSaveArrayQuestion */
					map_key_7<< "q3_1" << "_" << consolidated_for_loop_index_8;
					q3_1_scope_question_t[map_key_7.str()] = q3_1->input_data;
					map_key_7<< "q3_2" << "_" << consolidated_for_loop_index_8;
					q3_2_scope_question_t[map_key_7.str()] = q3_2->input_data;
					/* ENTER PrintSaveArrayQuestion q4 at location: q5*/
					/* questionsInBlock_: q5  */
					/*q5 and q4 :belong to different blocks */
					for(int32_t xtcc_i = 0; xtcc_i < 5*2;++xtcc_i)
					{
						ostringstream map_key;
						map_key << "q5" << "_" << xtcc_i << "$" << consolidated_for_loop_index_8;
						q4_scope_question_t[map_key.str()] = q4_list.questionList[xtcc_i]->input_data;

					}
					/* EXIT PrintSaveArrayQuestion */
					map_key_7<< "i1" << "_" << consolidated_for_loop_index_8;
					q5_scope_int32_t[map_key_7.str()] = i1;
					map_key_7<< "i2" << "_" << consolidated_for_loop_index_8;
					q5_scope_int32_t[map_key_7.str()] = i2;
					map_key_7<< "i3" << "_" << consolidated_for_loop_index_8;
					q5_scope_int32_t[map_key_7.str()] = i3;
					/* ENTER AbstractQuestion::SaveQuestionsInMyBlockThatAreAfterMe */
					/* questions in my block (q5):q4,q5,*/
					/* I = q5 is the last question in in block  nothing to do */
					/* EXIT AbstractQuestion::SaveQuestionsInMyBlockThatAreAfterMe */
					/* EXIT AbstractQuestion::SetupArrayQuestionSave */
					/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
					if (data_entry_window == 0)
					{
						cout << "jumpToQuestion = " << jumpToQuestion << endl;  cout << "jumpToIndex = " << jumpToIndex << endl;
					}

					if(!q5_list.questionList[i1*3+i2]->isAnswered_||stopAtNextQuestion||
						(p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q5_list.questionList[i1*3+i2]) ||
						(jumpToQuestion == "q5" && jumpToIndex ==  consolidated_for_loop_index_8) )
					{
						label_eval_q5:
						if( jumpToQuestion == "q5" && jumpToIndex == consolidated_for_loop_index_8)
						{
							back_jump = false;
							jumpToIndex = -1;
						}
						if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q5_list.questionList[i1*3+i2] &&  q5_list.questionList[i1*3+i2]->isAnswered_ == true)
						{
							stopAtNextQuestion = true;
							fprintf (qscript_stdout, " at question:  q5 arming stopAtNextQuestion = true \n");
						}
						else if ( q5_list.questionList[i1*3+i2] ->question_attributes.hidden_==false)
						{
							//q5_list.questionList[i1*3+i2]->eval(question_window, stub_list_window, data_entry_window);
							last_question_visited = q5_list.questionList[i1*3+i2];
							stopAtNextQuestion = false;
							return q5_list.questionList[i1*3+i2];
						}
						if(user_navigation == NAVIGATE_PREVIOUS)
						{
							AbstractQuestion * target_question = ComputePreviousQuestion(q5_list.questionList[consolidated_for_loop_index_8]);
							if(target_question == 0)
								goto label_eval_q5;
							else
							{
								jumpToQuestion = target_question->questionName_;
								if(target_question->type_ == QUESTION_ARR_TYPE)
								{
									jumpToIndex = ComputeJumpToIndex(target_question);
								}
								if (data_entry_window==0) cout << "target question: " << jumpToQuestion;
								if (data_entry_window==0) cout << "target question Index: " << jumpToIndex;
								back_jump = true;
								user_navigation = NOT_SET;
								goto start_of_questions;
							}
						}
						else if (user_navigation == NAVIGATE_NEXT)
						{
							stopAtNextQuestion = true;
							user_navigation = NOT_SET;
						}
						else if (user_navigation == JUMP_TO_QUESTION)
						{
							DisplayActiveQuestions();
							GetUserResponse(jumpToQuestion, jumpToIndex);
							user_navigation = NOT_SET;
							goto start_of_questions;
						}
						else if (user_navigation == SAVE_DATA)
						{
							write_data_to_disk(question_list, jno, ser_no);
							cout << "saved partial data\n";
							if (data_entry_window) mvwprintw(data_entry_window,2,50, "saved partial data");
							else   cout << "saved partial data\n";
							if (q5_list.questionList[consolidated_for_loop_index_8]->isAnswered_==false)
							{
								cout << "question has not been answered ... jumping back\n";
								goto label_eval_q5;
							}
						}
						else
						{
							last_question_answered = q5_list.questionList[consolidated_for_loop_index_8];
						}
					}
				}
			}
		}

		if (write_data_file_flag)
		{

			for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i)
			{
				ascii_flatfile_question_disk_map[i]->write_data (flat_file_output_buffer);
			}
			cout << "output_buffer: " << flat_file_output_buffer;
			flat_file << flat_file_output_buffer << endl;
			memset(flat_file_output_buffer, ' ', len_flat_file_output_buffer-1);
		}
		else if (write_qtm_data_file_flag)
		{
			for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i)
			{
				qtm_datafile_question_disk_map[i]->write_data ();
			}
			qtm_datafile_question_disk_map[0]->qtmDataFile_.write_record_to_disk(qtm_disk_file, ser_no);
			qtm_datafile_question_disk_map[0]->qtmDataFile_.Reset();
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
				write_data_to_disk(question_list, jno, ser_no);
			}
			else if (end_of_question_navigation == 'p')
			{
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
			}
			else if (end_of_question_navigation == 'j')
			{
				DisplayActiveQuestions();
				GetUserResponse(jumpToQuestion, jumpToIndex);
				user_navigation = NOT_SET;
				goto start_of_questions;
			}
			else if (end_of_question_navigation == 'q')
			{
				reset_questionnaire();
			}
			else
			{
				goto label_end_of_qnre_navigation;
			}
			wclear(data_entry_window);
			mvwprintw(data_entry_window, 1, 1, "Enter Serial No (0) to exit: ");
			mvwscanw(data_entry_window, 1, 40, "%d", & ser_no);
		}
		reset_questionnaire();
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
		for(int32_t i = 0; i < question_list.size(); ++i)
		{
			if(question_list[i] == q)
			{
				current_question_index = i;
				break;
			}
		}
		if(current_question_index == -1)
		{
			cerr << "internal compiler error at runtime ... filename: "
				<< __FILE__
				<< "line no: " << __LINE__
				<< endl;
		}
		for(int32_t i = current_question_index-1; i >= 0; --i)
		{
			if(question_list[i]->isAnswered_)
			{
				return question_list[i];
			}
		}
		// If we reach here just return the 1st question and hope for the best
		// This will not work if there is a condition on the 1st question - because of which it should never have been taken
		return question_list[0];
	}
	int32_t ComputeJumpToIndex(AbstractQuestion * q)
	{
		cout << "ENTER ComputeJumpToIndex: index:  ";
		for(int32_t i = 0; i < q->loop_index_values.size(); ++i)
		{
			cout << q->loop_index_values[i] << " ";
		}
		cout << endl;
		int32_t index = 0;
		for(int32_t i = 0; i < q->loop_index_values.size(); ++i)
		{
			int32_t tmp1=q->loop_index_values[i];
			for(int32_t j = i+1; j < q->dummyArrayQuestion_->array_bounds.size(); ++j)
			{
				tmp1 *=q->dummyArrayQuestion_->array_bounds[j];
			}
			index+=tmp1;
		}
		cout << "EXIT ComputeJumpToIndex: returning : " << index << endl;
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

	int read_a_serial_no()
	{
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
					if ((i + 3 == dir_entry_name.length())
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
			merge_disk_data_into_questions(qscript_stdout, last_question_answered, last_question_visited);
			return file_ser_no;
		}
		else
		{
			// not our data file
			goto restart;
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


#define MHD_PORT_NUMBER		8888
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
			return MHD_NO; /* internal error */
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
		method = MHD_HTTP_METHOD_GET; /* fake 'GET' */
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
bool verify_web_data (string p_question_data,
UserNavigation p_user_navigation,
user_response::UserResponseType p_the_user_response);

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
		/* continue from here - add functionality
		   for navigate previous.
		   pull the navigation direction from the input form field
		 */
		/*
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
				jumpToQuestion = target_question->questionName_;
				if (target_question->type_ == QUESTION_ARR_TYPE)
				{
					jumpToIndex =
						theQuestionnaire.
						ComputeJumpToIndex(target_question);
				}
				theQuestionnaire.back_jump = true;
				user_navigation = NOT_SET;
				//goto start_of_questions;
				goto re_eval_from_start;
			}
		}
		*/

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
		session->questionnaire->eval2(/*session->ptr_last_question_answered, session->ptr_last_question_visited,*/
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
	endwin();
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
	while ( (c = getopt(argc, argv, "w::q::")) != -1)
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
