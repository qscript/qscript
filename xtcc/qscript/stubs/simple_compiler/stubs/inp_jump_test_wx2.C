#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <cctype>
#include <unistd.h>
#include "AbstractQuestionnaire.h"
#include "question_gtk2_runtime.h"
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

		return 0;
	}							 /* close eval */
};

#if 0
int callback_get_ser_no_from_ui (int p_ser_no);
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
	TheQuestionnaire * theQuestionnaire = new TheQuestionnaire (jno);
	setup_ui (argc, argv, theQuestionnaire);

}								 /* close main */
#endif /*  0 */

struct TheQuestionnaire * make_questionnaire ()
{
	TheQuestionnaire * theQuestionnaire = new TheQuestionnaire (jno);
	theQuestionnaire->base_text_vec.push_back(BaseText("All Respondents"));
	return theQuestionnaire;
}


void question_eval_loop2 (
UserInput p_user_input,
AbstractQuestion * last_question_visited,
AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire);

// nxd: this is a global variable - has to be eliminated at some point
//TheQuestionnaire * theQuestionnaire = new TheQuestionnaire (jno);
int callback_get_ser_no_from_ui (int p_ser_no, struct TheQuestionnaire * theQuestionnaire )
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
	//cout << "finished qnre: exiting ..." << endl;
	//prompt_user_for_serial_no (callback_get_ser_no_from_ui);
	return 0;
}


void parse_input_data(vector<int> * data_ptr, int & success);
void callback_ui_input (UserInput p_user_input, AbstractQuestion * q, struct TheQuestionnaire * theQuestionnaire);
void eval_single_question_logic_with_input (UserInput p_user_input, AbstractQuestion * q, struct TheQuestionnaire * theQuestionnaire);

void callback_ui_input (UserInput p_user_input, AbstractQuestion * q, struct TheQuestionnaire * theQuestionnaire)
{
	cout << __PRETTY_FUNCTION__ << endl;
	// this will be called by the UI - it is the UI's responsibility to
	// get valid data for us
	//bool valid_input = q->VerifyResponse (p_user_input.theUserResponse_, p_user_input.userNavigation_);
	if (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation)
	{
		question_eval_loop2 (
			p_user_input,
			/* last_question_visited */ q,
			/*  jump_to_question */ 0, theQuestionnaire);
	}
	else if (p_user_input.theUserResponse_ == user_response::UserEnteredData)
	{
		eval_single_question_logic_with_input (p_user_input, q, theQuestionnaire);
	}
	else if (p_user_input.theUserResponse_ == user_response::UserSavedData)
	{
		cout << "under stdout either the user can enter data or navigation" << endl
			<< "but under ncurses or other guis - it's possible to enter data" << endl
			<< " AND ask to save by pressing f4, in which case we should save the data "
			<< " and then try to validate the user input - just like we would in a normal case"
			<< endl;
		// nxd: this function needs to be cleaned up
		//      we can easily downcast to an AbstractQuestionnaire and then there is no need for this
		//      function to be present here
		theQuestionnaire->write_data_to_disk (theQuestionnaire->question_list, theQuestionnaire->jno, theQuestionnaire->ser_no);
	}
	else
	{
		cerr << __PRETTY_FUNCTION__ << " unhandled case theUserResponse_" << endl;
	}
}


void question_eval_loop2 (
UserInput p_user_input,
AbstractQuestion * last_question_visited,
AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire)
{
	cout << endl << "Enter: " << __PRETTY_FUNCTION__ << endl;
	cout << "arg values: " << endl;
	if (p_user_input.userNavigation_ == NAVIGATE_NEXT)
	{
		cout << "p_user_input.userNavigation_ == NAVIGATE_NEXT" << endl;
	}
	else if (p_user_input.userNavigation_ == NAVIGATE_PREVIOUS)
	{
		cout << "p_user_input.userNavigation_ == NAVIGATE_PREVIOUS" << endl;
	}
	else
	{
		cout << "FIXME: p_user_input.userNavigation_ == Unhandled value " << endl;
	}
	if    (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation)
	{
		cout << "p_user_input.theUserResponse_ == UserEnteredNavigation" << endl;
	}
	else if (p_user_input.theUserResponse_ == user_response::UserEnteredData)
	{
		cout << "p_user_input.theUserResponse_ == UserEnteredData" << endl;
	}
	else if (p_user_input.theUserResponse_ == user_response::UserClearedData)
	{
		cout << "p_user_input.theUserResponse_ == UserClearedData" << endl;
	}
	else if (p_user_input.theUserResponse_ == user_response::UserSavedData)
	{
		cout << "p_user_input.theUserResponse_ == UserSavedData" << endl;
	}
	else if (p_user_input.theUserResponse_ == user_response::NotSet)
	{
		cout << "p_user_input.theUserResponse_ == NotSet" << endl;
	}
	else
	{
		cout << "FIXME: p_user_input.theUserResponse_ == Unhandled value " << endl;
	}

	cout
		<< "p_user_input.questionResponseData_:"
		<< p_user_input.questionResponseData_ << endl;

	if (last_question_visited)
	{
		cout << "last_question_visited->questionName_:"
			<<  last_question_visited->questionName_
			<< endl;
	}
	else
	{
		cout << "last_question_visited->questionName_: is NULL"  << endl;
	}

	if (last_question_visited)
	{
		if (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation)
		{
			if (p_user_input.userNavigation_ == NAVIGATE_PREVIOUS)
			{
				fprintf(qscript_stdout,
					"user_navigation == NAVIGATE_PREVIOUS\n");
				AbstractQuestion *target_question =
					theQuestionnaire->ComputePreviousQuestion(last_question_visited);
				if (target_question == 0)
				{
					stdout_eval (last_question_visited, theQuestionnaire, callback_ui_input);
				}
				else
				{
					stdout_eval (target_question, theQuestionnaire, callback_ui_input);
				}
			}
			else if (p_user_input.userNavigation_ == NAVIGATE_NEXT)
			{
				// do nothing
				// once we exit this major block == last_question_visited
				// the bottom of this function will handle it
			}
			else
			{
				cout << "Unhandled case userNavigation_ ... exiting" << endl
					<< __FILE__ << ","
					<< __LINE__ << ","
					<< __PRETTY_FUNCTION__ << ","
					<< endl;
				exit(1);
			}
		}
		else if (p_user_input.theUserResponse_ == user_response::UserEnteredData)
		{
			// the management of correctly accepting data is handled
			// by : callback_ui_input
			// if we have reached back again here - it means it's
			// time to get the next question
#if 0
			AbstractQuestion * q =
				theQuestionnaire->eval2 (
				NAVIGATE_NEXT, last_question_visited, jump_to_question);
			if (!q)
			{
				cout << "End of qnre();" << endl << ">";
				//int ch = getchar();
			}
			else
			{
				cout << __PRETTY_FUNCTION__ << "," << __LINE__ <<  ", eval2 return q = "
					<< q->questionName_ << endl;
				stdout_eval (q, theQuestionnaire, callback_ui_input);
			}
#endif /*  0 */

		}
		else
		{
			cout << "Unhandled case userNavigation_ ... exiting" << endl;
			exit(1);
		}
	}							 // else {
	// should reach here - end of :
	AbstractQuestion * q =
		theQuestionnaire->eval2 (
		NAVIGATE_NEXT, last_question_visited, jump_to_question);
	if (!q)
	{
		cout << "End of qnre();" << endl << ">";
	}
	else
	{
		cout << __PRETTY_FUNCTION__ << "," << __LINE__ <<  ", eval2 return q = "
			<< q->questionName_ << endl;
		stdout_eval (q, theQuestionnaire, callback_ui_input);
	}
	//}
}
