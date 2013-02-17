#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <errno.h>
#include <unistd.h>
#include <curses.h>
#include <panel.h>
#include <signal.h>
#include <dirent.h>
#include <cctype>
#include <unistd.h>
#include "AbstractQuestionnaire.h"
#include "question_stdout_runtime.h"
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
#include "eval_mode.h"

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

int process_options(int argc, char * argv[]);
DIR * directory_ptr = 0;
vector <string> vec_language;
struct TheQuestionnaire: public AbstractQuestionnaire
{
	//CompoundStatement::GenerateCode()
	// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 5, flagIsAForBody_: 0, source lineNo_: 0
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
	vector <stub_pair> qscript_temp_17;

	named_range test1;
	NamedStubQuestion * q4;
	vector <stub_pair> qscript_temp_18;

	named_range test2;
	NamedStubQuestion * q5;

	TheQuestionnaire (string p_jno): AbstractQuestionnaire(p_jno)
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
			text_expr_vec.push_back(new TextExpression(string("Q1. ")));
			text_expr_vec.push_back(new TextExpression(string(" Part 2")));
			q1 = new RangeQuestion(QUESTION_TYPE, 7,string( "q1"), text_expr_vec,spn,1,INT32_TYPE,xs_0, QuestionAttributes(false , false), true);
			print_question_messages(q1);
		}
		xs_1.indiv.insert(1);
		xs_1.indiv.insert(2);
		xs_1.indiv.insert(3);
		xs_1.indiv.insert(4);
		{
			vector<TextExpression *> text_expr_vec;
			text_expr_vec.push_back(new TextExpression(string("Q2. ")));
			q2 = new RangeQuestion(QUESTION_TYPE, 15,string( "q2"), text_expr_vec,spn,1,INT32_TYPE,xs_1, QuestionAttributes(false , false), false);
			print_question_messages(q2);
		}
		xs_2.indiv.insert(5);
		xs_2.indiv.insert(6);
		{
			vector<TextExpression *> text_expr_vec;
			text_expr_vec.push_back(new TextExpression(string("Q3. ")));
			q3 = new RangeQuestion(QUESTION_TYPE, 19,string( "q3"), text_expr_vec,spn,1,INT32_TYPE,xs_2, QuestionAttributes(false , false), false);
			print_question_messages(q3);
		}
		qscript_temp_17.push_back( stub_pair("Strongly Agree", 5));
		qscript_temp_17.push_back( stub_pair("Agree", 4));
		qscript_temp_17.push_back( stub_pair("Neither Agree or Disagree", 3));
		qscript_temp_17.push_back( stub_pair("Disagree", 2));
		qscript_temp_17.push_back( stub_pair("Strongly Disagree", 1));
		if (write_messages_flag)
		{
			for (int i=0; i<qscript_temp_17.size(); ++i)
			{
				messages << "<message id=\"" << "test1" << "_" << i << "\">" << qscript_temp_17[i].stub_text << "</message>\n" << endl;
			}
		}
		test1.set_range_data("test1", qscript_temp_17);
		{
			vector<TextExpression *> text_expr_vec;
			text_expr_vec.push_back(new TextExpression(string("q4. Named stubs")));
			q4 = new NamedStubQuestion(QUESTION_TYPE, 34,string( "q4"), text_expr_vec,spn,1,INT32_TYPE,&test1, QuestionAttributes(false , false), false);
			print_question_messages(q4);
		}
		qscript_temp_18.push_back( stub_pair("Other 1", 1));
		qscript_temp_18.push_back( stub_pair("Other 2", 2));
		qscript_temp_18.push_back( stub_pair("Other 3", 3));
		qscript_temp_18.push_back( stub_pair("Other 4", 4));
		qscript_temp_18.push_back( stub_pair("Other 5", 5));
		qscript_temp_18.push_back( stub_pair("Other 6", 6));
		qscript_temp_18.push_back( stub_pair("Other 7", 7));
		qscript_temp_18.push_back( stub_pair("Other 8", 8));
		qscript_temp_18.push_back( stub_pair("Other 9", 9));
		qscript_temp_18.push_back( stub_pair("Other 10", 10));
		qscript_temp_18.push_back( stub_pair("Other 11", 11));
		qscript_temp_18.push_back( stub_pair("Other 12", 12));
		qscript_temp_18.push_back( stub_pair("Other 13", 13));
		qscript_temp_18.push_back( stub_pair("Other 14", 14));
		qscript_temp_18.push_back( stub_pair("Other 15", 15));
		qscript_temp_18.push_back( stub_pair("Other 16", 16));
		qscript_temp_18.push_back( stub_pair("Other 17", 17));
		qscript_temp_18.push_back( stub_pair("Other 18", 18));
		qscript_temp_18.push_back( stub_pair("Other 19", 19));
		qscript_temp_18.push_back( stub_pair("Other 20", 20));
		qscript_temp_18.push_back( stub_pair("Other 21", 21));
		qscript_temp_18.push_back( stub_pair("Other 22", 22));
		qscript_temp_18.push_back( stub_pair("Other 23", 23));
		qscript_temp_18.push_back( stub_pair("Other 24", 24));
		qscript_temp_18.push_back( stub_pair("Other 25", 25));
		qscript_temp_18.push_back( stub_pair("Other 26", 26));
		qscript_temp_18.push_back( stub_pair("Other 27", 27));
		qscript_temp_18.push_back( stub_pair("Other 28", 28));
		qscript_temp_18.push_back( stub_pair("Other 29", 29));
		qscript_temp_18.push_back( stub_pair("Other 30", 30));
		qscript_temp_18.push_back( stub_pair("Other 31", 31));
		qscript_temp_18.push_back( stub_pair("Other 32", 32));
		qscript_temp_18.push_back( stub_pair("Other 33", 33));
		qscript_temp_18.push_back( stub_pair("Other 34", 34));
		qscript_temp_18.push_back( stub_pair("Other 35", 35));
		qscript_temp_18.push_back( stub_pair("Other 36", 36));
		qscript_temp_18.push_back( stub_pair("Other 37", 37));
		qscript_temp_18.push_back( stub_pair("Other 38", 38));
		qscript_temp_18.push_back( stub_pair("Other 39", 39));
		qscript_temp_18.push_back( stub_pair("Other 40", 40));
		qscript_temp_18.push_back( stub_pair("Other 41", 41));
		qscript_temp_18.push_back( stub_pair("Other 42", 42));
		qscript_temp_18.push_back( stub_pair("Other 43", 43));
		qscript_temp_18.push_back( stub_pair("Other 44", 44));
		qscript_temp_18.push_back( stub_pair("Other 45", 45));
		qscript_temp_18.push_back( stub_pair("Other 46", 46));
		qscript_temp_18.push_back( stub_pair("Other 47", 47));
		qscript_temp_18.push_back( stub_pair("Other 48", 48));
		qscript_temp_18.push_back( stub_pair("Other 49", 49));
		qscript_temp_18.push_back( stub_pair("Other 50", 50));
		qscript_temp_18.push_back( stub_pair("Other 51", 51));
		qscript_temp_18.push_back( stub_pair("Other 52", 52));
		qscript_temp_18.push_back( stub_pair("Other 53", 53));
		qscript_temp_18.push_back( stub_pair("Other 54", 54));
		qscript_temp_18.push_back( stub_pair("Other 55", 55));
		qscript_temp_18.push_back( stub_pair("Other 56", 56));
		qscript_temp_18.push_back( stub_pair("Other 57", 57));
		qscript_temp_18.push_back( stub_pair("Other 58", 58));
		qscript_temp_18.push_back( stub_pair("Other 59", 59));
		qscript_temp_18.push_back( stub_pair("Other 60", 60));
		qscript_temp_18.push_back( stub_pair("Other 61", 61));
		qscript_temp_18.push_back( stub_pair("Other 62", 62));
		qscript_temp_18.push_back( stub_pair("Other 63", 63));
		qscript_temp_18.push_back( stub_pair("Other 64", 64));
		qscript_temp_18.push_back( stub_pair("Other 65", 65));
		qscript_temp_18.push_back( stub_pair("Other 66", 66));
		if (write_messages_flag)
		{
			for (int i=0; i<qscript_temp_18.size(); ++i)
			{
				messages << "<message id=\"" << "test2" << "_" << i << "\">" << qscript_temp_18[i].stub_text << "</message>\n" << endl;
			}
		}
		test2.set_range_data("test2", qscript_temp_18);
		{
			vector<TextExpression *> text_expr_vec;
			text_expr_vec.push_back(new TextExpression(string("q5. Named stubs")));
			q5 = new NamedStubQuestion(QUESTION_TYPE, 107,string( "q5"), text_expr_vec,spn,1,INT32_TYPE,&test2, QuestionAttributes(false , false), false);
			print_question_messages(q5);
		}

		questions_start_from_here_index = question_list.size();
		question_list.push_back(q1);
		print_question_messages(q1);
		question_list.push_back(q2);
		print_question_messages(q2);
		question_list.push_back(q3);
		print_question_messages(q3);
		question_list.push_back(q4);
		print_question_messages(q4);
		question_list.push_back(q5);
		print_question_messages(q5);

		compute_flat_file_map_and_init();
		if (write_messages_flag)
		{
			messages << "</messages>\n";
			messages.flush() ;
		}
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
				AsciiFlatFileQuestionDiskMap * qscript_temp_13 = new AsciiFlatFileQuestionDiskMap(q5, current_map_pos);
				current_map_pos += qscript_temp_13->GetTotalLength();
				ascii_flatfile_question_disk_map.push_back(qscript_temp_13);
				if (write_xtcc_data_file_flag)
				{
					XtccDataFileDiskMap * qscript_temp_14 = new XtccDataFileDiskMap(q5, current_xtcc_map_pos);
					current_xtcc_map_pos += qscript_temp_14->GetTotalLength();
					xtcc_question_disk_map.push_back(qscript_temp_14);
				}
				if (write_qtm_data_file_flag)
				{
					qtm_data_file_ns::QtmDataDiskMap * qscript_temp_15 = new qtm_data_file_ns::QtmDataDiskMap(q5, qtm_data_file, base_text_vec.back());
					qtm_datafile_question_disk_map.push_back(qscript_temp_15);
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
		UserNavigation p_navigation_mode, AbstractQuestion * p_last_question_visited, AbstractQuestion * p_jump_to_index)
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
			/* compound statement on line no: 0 questionsInBlock_, size:5 q1, q2, q3, q4, q5,  */
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
			/*  void AbstractQuestion::PrintEvalAndNavigateCode(std::ostringstream&)*/

			if ( /* nxd */(q1->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
				(q1->isAnswered_ && !q1->VerifyQuestionIntegrity())||
				( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == 0) || (p_navigation_mode == NAVIGATE_NEXT && q1->questionNoIndex_ >  last_question_visited-> questionNoIndex_ )) ||
				( p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractQuestion*>(q1) == p_jump_to_index)) ||
				((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q1->question_attributes.isAllowBlank()) && q1->isAnswered_ == false ))
			{
				label_eval_q1:
				if (q1->question_attributes.hidden_==false)
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
			bool qscript_temp_16 = qscript_temp_xtcc_set_1.contains_subset(q1->input_data);
			if (qscript_temp_16 )// ifStatementStack.size(): 0
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
			/*  void AbstractQuestion::PrintEvalAndNavigateCode(std::ostringstream&)*/

			if ( /* nxd */(q2->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
				(q2->isAnswered_ && !q2->VerifyQuestionIntegrity())||
				( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == 0) || (p_navigation_mode == NAVIGATE_NEXT && q2->questionNoIndex_ >  last_question_visited-> questionNoIndex_ )) ||
				( p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractQuestion*>(q2) == p_jump_to_index)) ||
				((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q2->question_attributes.isAllowBlank()) && q2->isAnswered_ == false ))
			{
				label_eval_q2:
				if (q2->question_attributes.hidden_==false)
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
			/*  void AbstractQuestion::PrintEvalAndNavigateCode(std::ostringstream&)*/

			if ( /* nxd */(q3->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
				(q3->isAnswered_ && !q3->VerifyQuestionIntegrity())||
				( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == 0) || (p_navigation_mode == NAVIGATE_NEXT && q3->questionNoIndex_ >  last_question_visited-> questionNoIndex_ )) ||
				( p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractQuestion*>(q3) == p_jump_to_index)) ||
				((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q3->question_attributes.isAllowBlank()) && q3->isAnswered_ == false ))
			{
				label_eval_q3:
				if (q3->question_attributes.hidden_==false)
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
			/* EXIT ExpressionStatement::GenerateCode */
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
			/*  void AbstractQuestion::PrintEvalAndNavigateCode(std::ostringstream&)*/

			if ( /* nxd */(q4->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
				(q4->isAnswered_ && !q4->VerifyQuestionIntegrity())||
				( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == 0) || (p_navigation_mode == NAVIGATE_NEXT && q4->questionNoIndex_ >  last_question_visited-> questionNoIndex_ )) ||
				( p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractQuestion*>(q4) == p_jump_to_index)) ||
				((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q4->question_attributes.isAllowBlank()) && q4->isAnswered_ == false ))
			{
				label_eval_q4:
				if (q4->question_attributes.hidden_==false)
				{
					// q4->eval(question_window, stub_list_window, data_entry_window);
					last_question_visited = q4;
					fprintf(qscript_stdout, "last_question_visited: q4\n");
					return q4;
				}
			}
			/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
			lab_q5:
			if( back_jump == true  && q5->isAnswered_ == true )
			{
				if( jumpToQuestion == "q5")
				{
					back_jump = false;
				}
			}
			/* EXIT: AbstractQuestion::PrintSetupBackJump()  */
			/*  void AbstractQuestion::PrintEvalAndNavigateCode(std::ostringstream&)*/

			if ( /* nxd */(q5->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
				(q5->isAnswered_ && !q5->VerifyQuestionIntegrity())||
				( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == 0) || (p_navigation_mode == NAVIGATE_NEXT && q5->questionNoIndex_ >  last_question_visited-> questionNoIndex_ )) ||
				( p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractQuestion*>(q5) == p_jump_to_index)) ||
				((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q5->question_attributes.isAllowBlank()) && q5->isAnswered_ == false ))
			{
				label_eval_q5:
				if (q5->question_attributes.hidden_==false)
				{
					// q5->eval(question_window, stub_list_window, data_entry_window);
					last_question_visited = q5;
					fprintf(qscript_stdout, "last_question_visited: q5\n");
					return q5;
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
};

void outer_question_eval_loop (EvalMode qnre_mode, UserNavigation navg, AbstractQuestion * last_question_visited, AbstractQuestion* jump_to_question, TheQuestionnaire * qnre);
void question_eval_loop (EvalMode qnre_mode,
	UserNavigation qnre_navigation_mode, AbstractQuestion * last_question_visited,
	AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire);

void question_eval_loop2 (
	UserInput p_user_input,
	AbstractQuestion * last_question_visited,
	AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire);

// nxd: this is a global variable - has to be eliminated at some point
TheQuestionnaire * theQuestionnaire = new TheQuestionnaire (jno);
int callback_get_ser_no_from_ui (int p_ser_no)
{
	cout << "received serial no : " << p_ser_no << "from ui";

	theQuestionnaire->ser_no = p_ser_no;
	theQuestionnaire->base_text_vec.push_back(BaseText("All Respondents"));
	theQuestionnaire->compute_flat_file_map_and_init();
	UserNavigation qnre_navigation_mode = NAVIGATE_NEXT;

	AbstractQuestion * last_question_visited = 0;
	AbstractQuestion * jump_to_question = 0;
	EvalMode qnre_mode = NORMAL_FLOW;
	//question_eval_loop (qnre_mode,
	//			qnre_navigation_mode, last_question_visited,
	//			jump_to_question, theQuestionnaire);
	UserInput l_user_input;
	question_eval_loop2 (
				l_user_input, /* last_question_visited */ 0,
				/* jump_to_question */ 0, theQuestionnaire);
	cout << "finished qnre: exiting ..." << endl;
	return 0;
}

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
	SetupSignalHandler();
	setup_ui (argc, argv);
	prompt_user_for_serial_no (callback_get_ser_no_from_ui);

	// nxd: TheQuestionnaire * theQuestionnaire = new TheQuestionnaire (jno);
	// nxd: theQuestionnaire->base_text_vec.push_back(BaseText("All Respondents"));
	// nxd: theQuestionnaire->compute_flat_file_map_and_init();
	// nxd: UserNavigation qnre_navigation_mode = NAVIGATE_NEXT;

	// nxd: AbstractQuestion * last_question_visited = 0;
	// nxd: AbstractQuestion * jump_to_question = 0;
	// nxd: EvalMode qnre_mode = NORMAL_FLOW;

	// nxd: //outer_question_eval_loop (qnre_mode, qnre_navigation_mode, last_question_visited, jump_to_question, theQuestionnaire);
	// nxd: endwin();

}								 /* close main */

void callback_ui_input (UserInput p_user_input, AbstractQuestion * q, struct TheQuestionnaire * theQuestionnaire)
{
	cout << __PRETTY_FUNCTION__ << endl;
	bool valid_input = q->VerifyResponse (p_user_input.theUserResponse_);
	if (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {
		question_eval_loop2 (
				p_user_input,
				/* last_question_visited */ q,
				/*  jump_to_question */ 0, theQuestionnaire);
#if 0
		switch (p_user_input.userNavigation_) {
		case NAVIGATE_PREVIOUS:
			question_eval_loop2 (USER_NAVIGATION,
					p_user_input,
					/* last_question_visited */ q,
					/*  jump_to_question */ 0, theQuestionnaire);
		break;
		default:
			cout << "unhandled navigation in " << __PRETTY_FUNCTION__
				<< endl;
		}
#endif /*  0 */
	} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {

	}
}

void question_eval_loop2 (
	UserInput p_user_input,
	AbstractQuestion * last_question_visited,
	AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire)
{
	if (last_question_visited) {
		if (p_user_input.userNavigation_ == NAVIGATE_PREVIOUS) {
			fprintf(qscript_stdout,
				"user_navigation == NAVIGATE_PREVIOUS\n");
			AbstractQuestion *target_question =
				theQuestionnaire->ComputePreviousQuestion(last_question_visited);
			if (target_question == 0)
			{
				//goto re_eval;
				//void question_eval_loop (EvalMode qnre_mode,
				//UserNavigation qnre_navigation_mode, AbstractQuestion * last_question_visited,
				//AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire)
				//question_eval_loop2 (
				//	NAVIGATE_PREVIOUS, /* last_question_visited */ last_question_visited,
				//	/*  jump_to_question */ last_question_visited, theQuestionnaire);
				stdout_eval (last_question_visited, theQuestionnaire, callback_ui_input);
			}
			else
			{
				//theQuestionnaire->jumpToQuestion = target_question->questionName_;
				//if (target_question->type_ == QUESTION_ARR_TYPE)
				//{
				//	theQuestionnaire->jumpToIndex =
				//		theQuestionnaire->
				//		ComputeJumpToIndex(target_question);
				//}
				// if (data_entry_window == 0)
				//     cout << "target question: " << jumpToQuestion;
				// if (data_entry_window == 0)
				//     cout << "target question Index: " << theQuestionnaire.jumpToIndex;
				//theQuestionnaire->back_jump = true;
				//user_navigation = NOT_SET;
				//goto start_of_questions;
				//question_eval_loop (USER_NAVIGATION,
				//	NAVIGATE_PREVIOUS, /* last_question_visited */ last_question_visited,
				//	/*  jump_to_question */ target_question, theQuestionnaire);
				//goto re_eval_from_start;
				stdout_eval (target_question, theQuestionnaire, callback_ui_input);
			}
		}
	} else {
		AbstractQuestion * q =
			theQuestionnaire->eval2 (
			NAVIGATE_NEXT, last_question_visited, jump_to_question);
		if (!q) {
			cout << "End of qnre();" << endl << ">";
			int ch = getchar();
		} else {
			stdout_eval (q, theQuestionnaire, callback_ui_input);
		}
	}
}

void question_eval_loop (EvalMode qnre_mode,
	UserNavigation qnre_navigation_mode, AbstractQuestion * last_question_visited,
	AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire)
{

	//while(theQuestionnaire->ser_no != 0 || (write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag))
	//{
	cout << "__PRETTY_FUNCTION__" << endl;
	re_eval_from_start:
	AbstractQuestion * q =
		theQuestionnaire->eval2 (
		qnre_navigation_mode, last_question_visited, jump_to_question);
	// Currently lets not worry about the data writing path
	// hence if we are in data writing mode - just exit with a message
	if (!q)
	{
		if (write_data_file_flag)
		{
			theQuestionnaire->write_ascii_data_to_disk();
			cerr << "Not considering data writing path at the moment" << endl;
			exit(1);
		}
		else if (write_qtm_data_file_flag)
		{
			theQuestionnaire->write_qtm_data_to_disk();
			cerr << "Not considering data writing path at the moment" << endl;
			exit(1);
		}
		else
		{
			//cerr << "Not considering What happens when we reach end of qnre at the moment - just lets exit" << endl;
			//exit(1);
			// thanks to the exit above - the code that follow is redundant in this block
			char end_of_question_navigation = get_end_of_question_response();
			if(end_of_question_navigation == 's')
			{
				theQuestionnaire->write_data_to_disk(theQuestionnaire->question_list, theQuestionnaire->jno, theQuestionnaire->ser_no);
				return;
			}
			else if (end_of_question_navigation == 'p')
			{
				AbstractQuestion * target_question = theQuestionnaire->ComputePreviousQuestion(theQuestionnaire->last_question_answered);
				//if(target_question->type_ == QUESTION_ARR_TYPE)
				//{
				//	theQuestionnaire->jumpToIndex = theQuestionnaire->ComputeJumpToIndex(target_question);
				//}
				//theQuestionnaire->jumpToQuestion = target_question->questionName_;
				////if (data_entry_window == 0) cout << "target question: " << jumpToQuestion;
				//theQuestionnaire->back_jump = true;
				//user_navigation = NOT_SET;
				//goto start_of_questions;
				//goto re_eval_from_start;
				question_eval_loop (USER_NAVIGATION,
					NAVIGATE_PREVIOUS, /* last_question_visited */ q,
					/*  jump_to_question */ target_question, theQuestionnaire);
			}
			else if (end_of_question_navigation == 'j')
			{
				theQuestionnaire->DisplayActiveQuestions();
				GetUserResponse(theQuestionnaire->jumpToQuestion, theQuestionnaire->jumpToIndex);
				user_navigation = NOT_SET;
				//goto start_of_questions;
				//goto re_eval_from_start;
			}
			else if (end_of_question_navigation == 'q')
			{
				//change to break again when we remove the exit from above
				//break;
				//endwin();
				//exit(1);
				return;
			}
			else
			{
				//goto label_end_of_qnre_navigation;
			}
			// wclear(data_entry_window);
			// mvwprintw(data_entry_window, 1, 1, "Enter Serial No (0) to exit: ");
			// mvwscanw(data_entry_window, 1, 40, "%d", & ser_no);
			//theQuestionnaire.prompt_user_for_serial_no();
			//if (theQuestionnaire.ser_no ==0) break;
			//change to break again when we remove the exit from above
			//actually this should be un-reachable code
			//break;
			//
			exit(1);
		}
	}
	else
	{
		fprintf(qscript_stdout, "eval2 returned %s\n",
			q->questionName_.c_str());
		re_eval:
		//q->eval(question_window, stub_list_window, data_entry_window);
		stdout_eval (q, theQuestionnaire, callback_ui_input);

		if (user_navigation == NAVIGATE_PREVIOUS)
		{
			fprintf(qscript_stdout,
				"user_navigation == NAVIGATE_PREVIOUS\n");
			AbstractQuestion *target_question =
				theQuestionnaire->ComputePreviousQuestion(q);
			if (target_question == 0)
			{
				//goto re_eval;
				//void question_eval_loop (EvalMode qnre_mode,
				//UserNavigation qnre_navigation_mode, AbstractQuestion * last_question_visited,
				//AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire)
				question_eval_loop (USER_NAVIGATION,
					NAVIGATE_PREVIOUS, /* last_question_visited */ q,
					/*  jump_to_question */ q, theQuestionnaire);
			}
			else
			{
				//theQuestionnaire->jumpToQuestion = target_question->questionName_;
				//if (target_question->type_ == QUESTION_ARR_TYPE)
				//{
				//	theQuestionnaire->jumpToIndex =
				//		theQuestionnaire->
				//		ComputeJumpToIndex(target_question);
				//}
				// if (data_entry_window == 0)
				//     cout << "target question: " << jumpToQuestion;
				// if (data_entry_window == 0)
				//     cout << "target question Index: " << theQuestionnaire.jumpToIndex;
				theQuestionnaire->back_jump = true;
				//user_navigation = NOT_SET;
				//goto start_of_questions;
				question_eval_loop (USER_NAVIGATION,
					NAVIGATE_PREVIOUS, /* last_question_visited */ q,
					/*  jump_to_question */ target_question, theQuestionnaire);
				//goto re_eval_from_start;
			}
		}
		else if (user_navigation == NAVIGATE_NEXT)
		{
			//fprintf(qscript_stdout, "user_navigation == NAVIGATE_NEXT\n");
			//if (q->isAnswered_ == false
			//	&& q->question_attributes.isAllowBlank() == false)
			//{
			//	fprintf(qscript_stdout,
			//		"questionName_ %s: going back to re_eval\n",
			//		q->questionName_.c_str());
			//	goto re_eval;
			//}
			//qnre_navigation_mode = NAVIGATE_NEXT;
			// stopAtNextQuestion = true;
			//user_navigation = NOT_SET;
			question_eval_loop (USER_NAVIGATION,
				NAVIGATE_NEXT, /* last_question_visited */ q,
				/*  jump_to_question */ 0, theQuestionnaire);
		}
		else if (user_navigation == JUMP_TO_QUESTION)
		{
			theQuestionnaire->DisplayActiveQuestions();
			GetUserResponse(theQuestionnaire->jumpToQuestion, theQuestionnaire->jumpToIndex);
			user_navigation = NOT_SET;
			//goto start_of_questions;
			goto re_eval_from_start;
		}
		else if (user_navigation == SAVE_DATA)
		{
			theQuestionnaire->write_data_to_disk(theQuestionnaire->question_list, theQuestionnaire->jno,
				theQuestionnaire->ser_no);
			print_save_partial_data_message_success ();
			//if (q->isAnswered_ == false)
			//{
			//	//goto label_eval_q2;
			//	goto re_eval;
			//}
			question_eval_loop (NORMAL_FLOW,
				NAVIGATE_NEXT, /* last_question_visited */ q,
				/*  jump_to_question */ jump_to_question, theQuestionnaire);
		}
		else
		{
			theQuestionnaire->last_question_answered = q;
			question_eval_loop (NORMAL_FLOW,
				NAVIGATE_NEXT, /* last_question_visited */ q,
				/*  jump_to_question */ 0, theQuestionnaire);
		}
	}
	//}						 /* close while */

}


#if 0
void outer_question_eval_loop (EvalMode qnre_mode,
UserNavigation qnre_navigation_mode, AbstractQuestion * last_question_visited,
AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire)
{
	do
	{
		theQuestionnaire->reset_questionnaire();
		if (write_data_file_flag||write_qtm_data_file_flag)
		{
			theQuestionnaire->ser_no =
				read_a_serial_no (directory_ptr, jno, theQuestionnaire);
			if (theQuestionnaire->ser_no == 0)
			{
				exit(1);
			}
		}
		else
		{
			theQuestionnaire->ser_no = prompt_user_for_serial_no();
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

		question_eval_loop (qnre_mode,
			qnre_navigation_mode, last_question_visited,
			jump_to_question, theQuestionnaire);

								 /* close do */
	} while(theQuestionnaire->ser_no != 0);
	endwin();

}
#endif /*  0 */


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
	std::cout << __PRETTY_FUNCTION__ << std::endl;
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
