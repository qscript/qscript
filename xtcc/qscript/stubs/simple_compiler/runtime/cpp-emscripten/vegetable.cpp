#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <cctype>
#include <unistd.h>
#include "AbstractQuestionnaire.h"
#include "question_stdout_runtime.h"
#include "stub_pair.h"
//#include "AbstractStatement.h"
#include "named_range.h"
#include "xtcc_set.h"
#include "datatype.h"
#include "qscript_lib.h"
#include "question_disk_data.h"
#include "question.h"
#include "user_navigation.h"
//#include "qtm_data_file.h"
//#include "qtm_datafile_conf_parser.h"
#include "ArrayQuestion.h"
//#include "AsciiFlatFileQuestionDiskMap.h"
//#include "XtccDataFile.h"
#include "base_text.h"
#include "named_attributes.h"
#include "QuestionAttributes.h"
#include "UserResponse.h"
#include "dom_manip_funcs.h"
using namespace std;
//string qscript_stdout_fname("qscript_stdout.log");
//FILE * qscript_stdout = 0;
#include "debug_mem.h"


//fstream debug_log_file("qscript_debug.log", ios_base::out|ios_base::trunc);
extern fstream flat_file;
extern fstream xtcc_datafile;
extern fstream qtm_disk_file;
extern set<string> qtm_include_files;
using namespace std;
//extern vector<int32_t> data;
namespace program_options_ns { bool flag_nice_map = true; }
extern UserNavigation user_navigation;
vector<mem_addr_tab>  mem_addr;
//extern vector<question_disk_data*>  qdd_list;
bool write_messages_flag;

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
void write_data_to_disk(const vector<AbstractRuntimeQuestion*>& q_vec, string jno, int32_t ser_no);
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
//vector <AsciiFlatFileQuestionDiskMap*> ascii_flatfile_question_disk_map;
//vector <XtccDataFileDiskMap*> xtcc_question_disk_map;
//vector <qtm_data_file_ns::QtmDataDiskMap*> qtm_datafile_question_disk_map;
//qtm_data_file_ns::QtmDataFile qtm_data_file;
void Compute_FlatFileQuestionDiskDataMap(vector<AbstractRuntimeQuestion*> p_question_list);
void load_languages_available(vector<string> & vec_language);

//int process_options(int argc, char * argv[]);
	DIR * directory_ptr = 0;
vector <string> vec_language;
struct TheQuestionnaire: public AbstractQuestionnaire
{
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

TheQuestionnaire (string p_jno): AbstractQuestionnaire(p_jno)
 /* length(): 48 */,list_q5_array_bounds(1),list_q6_array_bounds(1)
{
if (write_messages_flag) {
	messages.open ("vegetable.xml", ios_base::out|ios_base::trunc);
	if(!messages) { cerr << "unable to open file for output of messages... exiting\n"; exit(1); }
	messages << "<?xml version=\"1.0\" encoding=\"UTF8\"?>\n";
	messages << "<messages>\n";	messages << "  <message id=\"thank_you\">The Survey is now complete. Thank You for your time.</message>\n";}
qscript_temp_19.push_back( stub_pair("Yes", 1));
qscript_temp_19.push_back( stub_pair("No", 2));
	if (write_messages_flag) {
	for (int i=0; i<qscript_temp_19.size(); ++i) {
	messages << "<message id=\"" << "yn" << "_" << i << "\">" << qscript_temp_19[i].stub_text << "</message>\n" << endl;
	}
}
yn.set_range_data("yn", qscript_temp_19);
{
vector<TextExpression *> text_expr_vec;
text_expr_vec.push_back(new TextExpression(string("Do you eat vegetables?")));
q1 = new NamedStubQuestion(QUESTION_TYPE, 7,string( "q1"), text_expr_vec,spn,1,INT32_TYPE,&yn, QuestionAttributes(false , false), true);
print_question_messages(q1);
}
qscript_temp_20.push_back( stub_pair("Agree strongly", 5));
qscript_temp_20.push_back( stub_pair("Agree somewhat", 4));
qscript_temp_20.push_back( stub_pair("Neutral", 3));
qscript_temp_20.push_back( stub_pair("Disagree ", 2));
qscript_temp_20.push_back( stub_pair("Disagree strongly", 1));
	if (write_messages_flag) {
	for (int i=0; i<qscript_temp_20.size(); ++i) {
	messages << "<message id=\"" << "agree_5" << "_" << i << "\">" << qscript_temp_20[i].stub_text << "</message>\n" << endl;
	}
}
agree_5.set_range_data("agree_5", qscript_temp_20);
qscript_temp_21.push_back( stub_pair("Tomates", 1));
qscript_temp_21.push_back( stub_pair("Potatoes", 2));
qscript_temp_21.push_back( stub_pair("Capsicum", 3));
qscript_temp_21.push_back( stub_pair("Brinjal/Egg plant", 4));
qscript_temp_21.push_back( stub_pair("Okra/Lady Finger", 5));
	if (write_messages_flag) {
	for (int i=0; i<qscript_temp_21.size(); ++i) {
	messages << "<message id=\"" << "veg" << "_" << i << "\">" << qscript_temp_21[i].stub_text << "</message>\n" << endl;
	}
}
veg.set_range_data("veg", qscript_temp_21);
veg_seg_att.name = "veg_seg_att";
veg_seg_att.attribute.push_back (string(" Vegetables are good for health"));
veg_seg_att.attribute.push_back (string(" I buy fresh vegetables often"));
veg_seg_att.attribute.push_back (string(" Greens are good source of dietary fibre"));
veg_seg_att.attribute.push_back (string(" I would like to be vegetarian some day"));
	if (write_messages_flag) {
	for (int i=0; i<veg_seg_att.attribute.size(); ++i) {
	messages << "<message id=\"" << "veg_seg_att" << "_" << i << "\">" << veg_seg_att.attribute[i] << "</message>\n" << endl;
	}
}
{
vector<TextExpression *> text_expr_vec;
text_expr_vec.push_back(new TextExpression(string("Which of these vegetables are you aware of?")));
q2 = new NamedStubQuestion(QUESTION_TYPE, 35,string( "q2"), text_expr_vec,mpn,5,INT32_TYPE,&veg, QuestionAttributes(false , false), true);
print_question_messages(q2);
}
{
vector<TextExpression *> text_expr_vec;
text_expr_vec.push_back(new TextExpression(string("And, Which of these vegetables do you regularly eat?")));
q3 = new NamedStubQuestion(QUESTION_TYPE, 40,string( "q3"), text_expr_vec,mpn,5,INT32_TYPE,&veg, QuestionAttributes(false , false), false);
print_question_messages(q3);
}
{
vector<TextExpression *> text_expr_vec;
text_expr_vec.push_back(new TextExpression(string("And, Could you tell us which of these is your favourite vegetable?")));
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
for (int32_t i1 = 0;i1<5; ++i1) {
vector<int32_t> stack_of_loop_indices;
stack_of_loop_indices.push_back(i1);
{
vector<TextExpression *> text_expr_vec;
text_expr_vec.push_back(new TextExpression(string("In a week what perc of your veggies are : ")));
text_expr_vec.push_back( new TextExpression(q3, i1) ); /*  -NxD- */
RangeQuestion * q5 = new RangeQuestion(QUESTION_ARR_TYPE, 56,string( "q5"), text_expr_vec,spn,1,INT32_TYPE,xs_0, stack_of_loop_indices , dum_q5, QuestionAttributes(false , false), true);
question_list.push_back(q5);
print_question_messages(q5);
q5_list.questionList.push_back(q5);
}
	stack_of_loop_indices.pop_back();
}
for (int32_t i1 = 0;i1<4; ++i1) {
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

	//compute_flat_file_map_and_init();
	if (write_messages_flag) {
	messages << "</messages>\n";
	messages.flush() ;
	}
}
#if 0
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
		current_map_pos += (ser_no_pos-1);
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
base_text_vec.push_back(BaseText("All who have answered question q1 Equals 1"));
{
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
for (int32_t i1 = 0;i1<5; ++i1) {
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
for (int32_t i1 = 0;i1<4; ++i1) {
vector<int32_t> stack_of_loop_indices;
stack_of_loop_indices.push_back(i1);
{
int32_t consolidated_for_loop_index_7 = i1;
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
	xtcc_datafile.open(xtcc_datafile_name.c_str(), ios_base::out | ios_base::trunc);
		{struct stat dir_exists; stringstream s1;
		s1 << "setup-" << jno;
		if (stat(s1.str().c_str(), &dir_exists) <0) {
			if (errno == ENOENT)
				if (mkdir(s1.str().c_str(), S_IRUSR | S_IWUSR | S_IXUSR) <0) {
					perror("unable to create directory for setup files");
}
			else
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
			AbstractRuntimeQuestion * q = qtm_datafile_question_disk_map[i]->q;
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
#endif /* 0 */

AbstractRuntimeQuestion * eval2 ( /*AbstractRuntimeQuestion * p_last_question_answered,
		 AbstractRuntimeQuestion * p_last_question_visited,*/
		 UserNavigation p_navigation_mode, AbstractRuntimeQuestion * p_last_question_visited, AbstractRuntimeQuestion * p_jump_to_index)
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
			//merge_disk_data_into_questions2 (qscript_stdout, last_question_answered, last_question_visited, this->question_list, &qdd_map);
		}
	}

	*/
	start_of_questions:
	if(back_jump == true){
	//fprintf(qscript_stdout, "have reached start_of_questions with back_jump: jumpToQuestion: %s, jumpToIndex: %d\n", jumpToQuestion.c_str(), jumpToIndex);
	}
{
/* compound statement on line no: 1 questionsInBlock_, size:6 q1, q2, q3, q4, q5, q6,  */
int32_t i1;
/* ENTER: AbstractRuntimeQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
lab_q1:
if( back_jump == true  && q1->isAnswered_ == true ) {
if( jumpToQuestion == "q1")
{ back_jump = false;
}
}
/* EXIT: AbstractRuntimeQuestion::PrintSetupBackJump()  */
/*  void AbstractRuntimeQuestion::PrintEvalAndNavigateCode(std::ostringstream&)*/

if ( /* nxd */(q1->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
(q1->isAnswered_ && !q1->VerifyQuestionIntegrity())||
( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == 0) || (p_navigation_mode == NAVIGATE_NEXT && q1->questionNoIndex_ >  last_question_visited-> questionNoIndex_ )) ||
( p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractRuntimeQuestion*>(q1) == p_jump_to_index)) ||
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q1->question_attributes.isAllowBlank()) && q1->isAnswered_ == false )) {
label_eval_q1:
		if (q1->question_attributes.hidden_==false) {
	// q1->eval(question_window, stub_list_window, data_entry_window);
	last_question_visited = q1;
	//fprintf(qscript_stdout, "last_question_visited: q1\n");
	return q1;
	}
}
/* virtual void named_attribute_list::GenerateCode(StatementCompiledCode&), src/named_attributes.cpp, 25*/
/* if_nest_level: 1 */
/*if (!q1->isAnswered_) {
cerr << "runtime error using unanswered question in expression: " << "q1" << endl;
}*/
int32_t qscript_temp_22 = *q1->input_data.begin();
if (qscript_temp_22==1) {// ifStatementStack.size(): 0
// question_list_else_body :
{
/* compound statement on line no: 30 questionsInBlock_, size:4 q2, q3, q4, q5,  */
/*StubManipStatement::GenerateCode() BEGIN :veg*/
{
for(int32_t qscript_temp_23 = 0; qscript_temp_23 < veg.stubs.size(); ++qscript_temp_23){
veg.stubs[qscript_temp_23].mask = true;
}

}
/*StubManipStatement::GenerateCode() END :veg*/
/* ENTER: AbstractRuntimeQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
lab_q2:
if( back_jump == true  && q2->isAnswered_ == true ) {
if( jumpToQuestion == "q2")
{ back_jump = false;
}
}
/* EXIT: AbstractRuntimeQuestion::PrintSetupBackJump()  */
/*  void AbstractRuntimeQuestion::PrintEvalAndNavigateCode(std::ostringstream&)*/

if ( /* nxd */(q2->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
(q2->isAnswered_ && !q2->VerifyQuestionIntegrity())||
( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == 0) || (p_navigation_mode == NAVIGATE_NEXT && q2->questionNoIndex_ >  last_question_visited-> questionNoIndex_ )) ||
( p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractRuntimeQuestion*>(q2) == p_jump_to_index)) ||
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q2->question_attributes.isAllowBlank()) && q2->isAnswered_ == false )) {
label_eval_q2:
		if (q2->question_attributes.hidden_==false) {
	// q2->eval(question_window, stub_list_window, data_entry_window);
	last_question_visited = q2;
	//fprintf(qscript_stdout, "last_question_visited: q2\n");
	return q2;
	}
}
/*StubManipStatement::GenerateCode() BEGIN :veg*/
{
for(int32_t qscript_temp_24 = 0; qscript_temp_24 < veg.stubs.size(); ++qscript_temp_24){
veg.stubs[qscript_temp_24].mask = false;
}

}
/*StubManipStatement::GenerateCode() END :veg*/
/*StubManipStatement::GenerateCode() BEGIN q2:veg*/
{
set<int32_t>::iterator set_iter = q2->input_data.begin();
for( ; set_iter!= q2->input_data.end(); ++set_iter){
	for (int32_t qscript_temp_25 = 0; qscript_temp_25 < veg.stubs.size(); ++qscript_temp_25) {
		if (veg.stubs[qscript_temp_25].code == *set_iter) {
			veg.stubs[qscript_temp_25].mask = true;
		}
	}
}

}
/*StubManipStatement::GenerateCode() END q2:veg*/
/* ENTER: AbstractRuntimeQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
lab_q3:
if( back_jump == true  && q3->isAnswered_ == true ) {
if( jumpToQuestion == "q3")
{ back_jump = false;
}
}
/* EXIT: AbstractRuntimeQuestion::PrintSetupBackJump()  */
/*  void AbstractRuntimeQuestion::PrintEvalAndNavigateCode(std::ostringstream&)*/

if ( /* nxd */(q3->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
(q3->isAnswered_ && !q3->VerifyQuestionIntegrity())||
( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == 0) || (p_navigation_mode == NAVIGATE_NEXT && q3->questionNoIndex_ >  last_question_visited-> questionNoIndex_ )) ||
( p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractRuntimeQuestion*>(q3) == p_jump_to_index)) ||
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q3->question_attributes.isAllowBlank()) && q3->isAnswered_ == false )) {
label_eval_q3:
		if (q3->question_attributes.hidden_==false) {
	// q3->eval(question_window, stub_list_window, data_entry_window);
	last_question_visited = q3;
	//fprintf(qscript_stdout, "last_question_visited: q3\n");
	return q3;
	}
}
/*StubManipStatement::GenerateCode() BEGIN :veg*/
{
for(int32_t qscript_temp_26 = 0; qscript_temp_26 < veg.stubs.size(); ++qscript_temp_26){
veg.stubs[qscript_temp_26].mask = false;
}

}
/*StubManipStatement::GenerateCode() END :veg*/
/*StubManipStatement::GenerateCode() BEGIN q3:veg*/
{
set<int32_t>::iterator set_iter = q3->input_data.begin();
for( ; set_iter!= q3->input_data.end(); ++set_iter){
	for (int32_t qscript_temp_27 = 0; qscript_temp_27 < veg.stubs.size(); ++qscript_temp_27) {
		if (veg.stubs[qscript_temp_27].code == *set_iter) {
			veg.stubs[qscript_temp_27].mask = true;
		}
	}
}

}
/*StubManipStatement::GenerateCode() END q3:veg*/
/* ENTER: AbstractRuntimeQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
lab_q4:
if( back_jump == true  && q4->isAnswered_ == true ) {
if( jumpToQuestion == "q4")
{ back_jump = false;
}
}
/* EXIT: AbstractRuntimeQuestion::PrintSetupBackJump()  */
/*  void AbstractRuntimeQuestion::PrintEvalAndNavigateCode(std::ostringstream&)*/

if ( /* nxd */(q4->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
(q4->isAnswered_ && !q4->VerifyQuestionIntegrity())||
( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == 0) || (p_navigation_mode == NAVIGATE_NEXT && q4->questionNoIndex_ >  last_question_visited-> questionNoIndex_ )) ||
( p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractRuntimeQuestion*>(q4) == p_jump_to_index)) ||
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q4->question_attributes.isAllowBlank()) && q4->isAnswered_ == false )) {
label_eval_q4:
		if (q4->question_attributes.hidden_==false) {
	// q4->eval(question_window, stub_list_window, data_entry_window);
	last_question_visited = q4;
	//fprintf(qscript_stdout, "last_question_visited: q4\n");
	return q4;
	}
}
int32_t sum = 0;
int32_t iter_no = 0;
for (i1 = 0;i1<5;i1 = i1+1){
int32_t consolidated_for_loop_index_2 = i1;
/* compound statement on line no: 50 questionsInBlock_, size:1 q5,  */
int32_t code = i1+1;
/* if_nest_level: 2 */
if (/* virtual void Binary2Expression::PrintExpressionCode(ExpressionCompiledCode&), 1676, src/expr.cpp    */
q3->input_data.find(code) != q3->input_data.end()) {// ifStatementStack.size(): 0
// question_list_else_body :
{
/* compound statement on line no: 53 questionsInBlock_, size:1 q5,  */
/* ENTER: AbstractRuntimeQuestion::PrintSetupBackJump() : for_bounds_stack.size():1 */
lab_q5:
if( back_jump == true  && q5_list.questionList[consolidated_for_loop_index_2]->isAnswered_ == true ) {
}
/* EXIT: AbstractRuntimeQuestion::PrintSetupBackJump()  */
// if (data_entry_window == 0) {
	//cout << "jumpToQuestion = " << jumpToQuestion << endl;//	cout << "jumpToIndex = " << jumpToIndex << endl;//}

if ((q5_list.questionList[i1]->isAnswered_ == false  && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
 stopAtNextQuestion ||
( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == 0) ||   (p_navigation_mode == NAVIGATE_NEXT && q5_list.questionList[i1]->questionNoIndex_ > last_question_visited->questionNoIndex_)) ||
( p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractRuntimeQuestion*>(q5_list.questionList[i1]) == p_jump_to_index)) ||
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q5_list.questionList[i1]->question_attributes.isAllowBlank()) && q5_list.questionList[i1]->isAnswered_ == false )) {
label_eval_q5:
if( jumpToQuestion == "q5" && jumpToIndex == consolidated_for_loop_index_2){
back_jump = false;
jumpToIndex = -1;
}
if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q5_list.questionList[i1] &&  q5_list.questionList[i1]->isAnswered_ == true) {
 stopAtNextQuestion = true;
 //fprintf (qscript_stdout, " at question:  q5 arming stopAtNextQuestion = true \n");
} else if ( q5_list.questionList[i1] ->question_attributes.hidden_==false) {
		//q5_list.questionList[i1]->eval(question_window, stub_list_window, data_entry_window);
		last_question_visited = q5_list.questionList[i1];
stopAtNextQuestion = false;
		return q5_list.questionList[i1];
	}
}
/* ENTER ExpressionStatement::GenerateCode */
if (!q5_list.questionList[i1]->isAnswered_) {
cerr << "runtime error using unanswered question in expression: " << "q5" << endl;
}
sum = sum+*(q5_list.questionList[i1]->input_data.begin());
/* EXIT ExpressionStatement::GenerateCode */
/* ENTER ExpressionStatement::GenerateCode */
iter_no = i1;
}
 }
 else {
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
if (sum!=100) {// ifStatementStack.size(): 0
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
 else {
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
for (i1 = 0;i1<4;i1 = i1+1){
int32_t consolidated_for_loop_index_7 = i1;
/* compound statement on line no: 74 questionsInBlock_, size:1 q6,  */
/* ENTER: AbstractRuntimeQuestion::PrintSetupBackJump() : for_bounds_stack.size():1 */
lab_q6:
if( back_jump == true  && q6_list.questionList[consolidated_for_loop_index_7]->isAnswered_ == true ) {
}
/* EXIT: AbstractRuntimeQuestion::PrintSetupBackJump()  */
// if (data_entry_window == 0) {
	//cout << "jumpToQuestion = " << jumpToQuestion << endl;//	cout << "jumpToIndex = " << jumpToIndex << endl;//}

if ((q6_list.questionList[i1]->isAnswered_ == false  && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
 stopAtNextQuestion ||
( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == 0) ||   (p_navigation_mode == NAVIGATE_NEXT && q6_list.questionList[i1]->questionNoIndex_ > last_question_visited->questionNoIndex_)) ||
( p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractRuntimeQuestion*>(q6_list.questionList[i1]) == p_jump_to_index)) ||
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q6_list.questionList[i1]->question_attributes.isAllowBlank()) && q6_list.questionList[i1]->isAnswered_ == false )) {
label_eval_q6:
if( jumpToQuestion == "q6" && jumpToIndex == consolidated_for_loop_index_7){
back_jump = false;
jumpToIndex = -1;
}
if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == q6_list.questionList[i1] &&  q6_list.questionList[i1]->isAnswered_ == true) {
 stopAtNextQuestion = true;
// fprintf (qscript_stdout, " at question:  q6 arming stopAtNextQuestion = true \n");
} else if ( q6_list.questionList[i1] ->question_attributes.hidden_==false) {
		//q6_list.questionList[i1]->eval(question_window, stub_list_window, data_entry_window);
		last_question_visited = q6_list.questionList[i1];
stopAtNextQuestion = false;
		return q6_list.questionList[i1];
	}
}
}
}

	return 0;
} /* close eval */
};
struct TheQuestionnaire * make_questionnaire ()
{
	TheQuestionnaire * theQuestionnaire = new TheQuestionnaire (jno);
	theQuestionnaire->base_text_vec.push_back(BaseText("All Respondents"));
	return theQuestionnaire;
}
void question_eval_loop2 (
	UserInput p_user_input,
	AbstractRuntimeQuestion * last_question_visited,
	AbstractRuntimeQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire, int nest_level);

int callback_get_ser_no_from_ui (int p_ser_no, int nest_level, char * survey_data)
{
	// now its not :-) // nxd: this is a global variable - has to be eliminated at some point
	TheQuestionnaire * theQuestionnaire = new TheQuestionnaire (jno);
	cout << "received serial no : " << p_ser_no << "from ui";

	theQuestionnaire->ser_no = p_ser_no;
	theQuestionnaire->base_text_vec.push_back(BaseText("All Respondents"));
	//theQuestionnaire->compute_flat_file_map_and_init();
	UserNavigation qnre_navigation_mode = NAVIGATE_NEXT;

	AbstractRuntimeQuestion * last_question_visited = 0;
	AbstractRuntimeQuestion * jump_to_question = 0;

	string str_survey_data(survey_data);
	if (str_survey_data.length() > 0) {
		map <string, question_disk_data*>  qdd_map;
		int r_val =  load_data_from_string (str_survey_data.c_str(), &qdd_map);
		printf ("after load_data_from_string r_val: %d\n", r_val);
		merge_disk_data_into_questions2 (/*qscript_stdout*/ 0,
			theQuestionnaire->last_question_answered,
			theQuestionnaire->last_question_visited,
			theQuestionnaire->question_list, &qdd_map);
	}
	EvalMode qnre_mode = NORMAL_FLOW;
	//question_eval_loop (qnre_mode,
	//			qnre_navigation_mode, last_question_visited,
	//			jump_to_question, theQuestionnaire);
	UserInput l_user_input;
	question_eval_loop2 (
				l_user_input, /* last_question_visited */ 0,
				/* jump_to_question */ 0, theQuestionnaire, nest_level+1);
	cout << "finished qnre: exiting ..." << endl;
	cout << "commented out prompt_user_for_serial_no" << endl;
	//prompt_user_for_serial_no (callback_get_ser_no_from_ui, nest_level + 1);
	return 0;
}


void parse_input_data(vector<int> * data_ptr, int & success);
void callback_ui_input (UserInput p_user_input, AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire, int nest_level);
void eval_single_question_logic_with_input (UserInput p_user_input, AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire, int nest_level);


void callback_ui_input (UserInput p_user_input, AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire, int nest_level)
{
	//cout << __PRETTY_FUNCTION__ << endl;
	printf("%s\n", __PRETTY_FUNCTION__);
	// this will be called by the UI - it is the UI's responsibility to
	// get valid data for us
	//bool valid_input = q->VerifyResponse (p_user_input.theUserResponse_, p_user_input.userNavigation_);
	if (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {
		question_eval_loop2 (
				p_user_input,
				/* last_question_visited */ q,
				/*  jump_to_question */ 0, theQuestionnaire, nest_level + 1);
	} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {
		cout << "mode: user_response::UserEnteredData" << endl;
		eval_single_question_logic_with_input (p_user_input, q, theQuestionnaire, nest_level + 1);
	} else if (p_user_input.theUserResponse_ == user_response::UserSavedData) {
		cout << "under stdout either the user can enter data or navigation" << endl
			<< "but under ncurses or other guis - it's possible to enter data" << endl
			<< " AND ask to save by pressing f4, in which case we should save the data "
			<< " and then try to validate the user input - just like we would in a normal case"
			<< endl;
		// nxd: this function needs to be cleaned up
		//      we can easily downcast to an AbstractQuestionnaire and then there is no need for this
		//      function to be present here
		theQuestionnaire->write_data_to_disk (theQuestionnaire->question_list, theQuestionnaire->jno, theQuestionnaire->ser_no);
	} else {
		cerr << __PRETTY_FUNCTION__ << " unhandled case theUserResponse_" << endl;
	}
	printf("EXIT: %s\n", __PRETTY_FUNCTION__);
}

void question_eval_loop2 (
	UserInput p_user_input,
	AbstractRuntimeQuestion * last_question_visited,
	AbstractRuntimeQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire, int nest_level)
{
	printf ("Enter: %s\n", __PRETTY_FUNCTION__);
	//cout << endl << "Enter: " << __PRETTY_FUNCTION__ << endl;
	cout << "arg values: " << endl;
	if (p_user_input.userNavigation_ == NAVIGATE_NEXT) {
		cout << "p_user_input.userNavigation_ == NAVIGATE_NEXT" << endl;
	} else if (p_user_input.userNavigation_ == NAVIGATE_PREVIOUS) {
		cout << "p_user_input.userNavigation_ == NAVIGATE_PREVIOUS" << endl;
	} else {
		cout << "FIXME: p_user_input.userNavigation_ == Unhandled value " << endl;
	}
	if 	  (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {
		cout << "p_user_input.theUserResponse_ == UserEnteredNavigation" << endl;
	} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {
		cout << "p_user_input.theUserResponse_ == UserEnteredData" << endl;
	} else if (p_user_input.theUserResponse_ == user_response::UserClearedData) {
		cout << "p_user_input.theUserResponse_ == UserClearedData" << endl;
	} else if (p_user_input.theUserResponse_ == user_response::UserSavedData) {
		cout << "p_user_input.theUserResponse_ == UserSavedData" << endl;
	} else if (p_user_input.theUserResponse_ == user_response::NotSet) {
		cout << "p_user_input.theUserResponse_ == NotSet" << endl;
	} else {
		cout << "FIXME: p_user_input.theUserResponse_ == Unhandled value " << endl;
	}


	cout
		<< "p_user_input.questionResponseData_:"
		<< p_user_input.questionResponseData_ << endl;

	if (last_question_visited) {
		//cout << "last_question_visited->questionName_:"
		//	<<  last_question_visited->questionName_
		//	<< endl;
		printf ("last_question_visited->questionName_:%s\n", last_question_visited->questionName_.c_str());
	} else {
		//cout << "last_question_visited->questionName_: is NULL"  << endl;
		printf ("last_question_visited->questionName_ is NULL\n");
	}

	if (last_question_visited) {
		if (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {
			if (p_user_input.userNavigation_ == NAVIGATE_PREVIOUS) {
				//fprintf(qscript_stdout, "user_navigation == NAVIGATE_PREVIOUS\n");
				AbstractRuntimeQuestion *target_question =
					theQuestionnaire->ComputePreviousQuestion(last_question_visited);
				if (target_question == 0) {
					stdout_eval (last_question_visited, theQuestionnaire, callback_ui_input, nest_level + 1);
				} else {
					stdout_eval (target_question, theQuestionnaire, callback_ui_input, nest_level + 1);
				}
			} else if (p_user_input.userNavigation_ == NAVIGATE_NEXT) {
				// do nothing
				// once we exit this major block == last_question_visited
				// the bottom of this function will handle it
			} else {
				cout << "Unhandled case userNavigation_ ... exiting" << endl
					<< __FILE__ << ","
					<< __LINE__ << ","
					<< __PRETTY_FUNCTION__ << ","
					<< endl;
				exit(1);
			}
		} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {
			// the management of correctly accepting data is handled
			// by : callback_ui_input
			// if we have reached back again here - it means it's
			// time to get the next question

		} else {
			cout << "Unhandled case userNavigation_ ... exiting" << endl;
			exit(1);
		}
	} // else {
	// should reach here - end of :
		AbstractRuntimeQuestion * q =
			theQuestionnaire->eval2 (
			NAVIGATE_NEXT, last_question_visited, jump_to_question);
		if (!q) {
			printf(" eval2 has returned NULL => End of qnre();\n");
			show_end_of_qnre_page();
		} else {
			printf(" eval2 has returned q: %s\n", q->questionName_.c_str());
			//cout << __PRETTY_FUNCTION__ << "," << __LINE__ <<  ", eval2 return q = "
			//	<< q->questionName_ << endl;
			//string qnre_data = theQuestionnaire->write_data_to_disk (theQuestionnaire->question_list, theQuestionnaire->jno, theQuestionnaire->ser_no);
			const int MAX_DATAFILE_SIZE = 100000;
			char buffer[MAX_DATAFILE_SIZE]; int n_left = MAX_DATAFILE_SIZE;
			char * buffer_start_ptr = buffer;
			//string qnre_data = theQuestionnaire->write_data_to_disk (theQuestionnaire->question_list, theQuestionnaire->jno, theQuestionnaire->ser_no);

			int n_written = theQuestionnaire->
				write_data_to_buffer
					(
						theQuestionnaire->question_list,
						theQuestionnaire->jno,
						theQuestionnaire->ser_no,
						buffer_start_ptr,
						n_left);
			//save_qnre_data (buffer);
			stdout_eval (q, theQuestionnaire, callback_ui_input, nest_level + 1);
		}
	//}
}

void set_last_visited (struct TheQuestionnaire * qnre, AbstractRuntimeQuestion * last_question_visited)
{
	qnre->last_question_visited = last_question_visited;
}

extern "C" {

void callback_return_serial (int serial_no, char * survey_data)
{
	printf ("Got a serial no from the DOM: %d, survey_data: %s\n", serial_no, survey_data);
	//TheQuestionnaire * l_qnre_ptr = dynamic_cast<TheQuestionnaire*> (AbstractQuestionnaire::qnre_ptr);
	callback_get_ser_no_from_ui (serial_no, 1, survey_data);
}

void called_from_the_dom (char * data)
{
	//emscripten_pause_main_loop();
	//emscripten_resume_main_loop();
	//printf ("data from the browser dom callback: %s\n", data);
	printf ("hello called_from_the_dom\n");
	printf ("data: %s\n", data);
	printf ("last_question_visited: %s\n",
		AbstractQuestionnaire::qnre_ptr->last_question_visited->questionName_.c_str());
	AbstractRuntimeQuestion * q = AbstractQuestionnaire::qnre_ptr->last_question_visited;
	// hard code the answers - Proof of concept testing
	// Can we really load the next question on the interface using this callback system?
	//q->isAnswered_ = true;
	//q->input_data.insert (2);
	//UserInput user_input;
	//user_input.theUserResponse_ = user_response::UserEnteredData;
	//user_input.questionResponseData_ = "1";
	UserInput user_input;
	user_input.theUserResponse_ = user_response::UserEnteredData;
	user_input.questionResponseData_ = data;
	string err_mesg;
	bool valid_input = q->VerifyResponse(user_input.theUserResponse_, user_input.userNavigation_, err_mesg);
	TheQuestionnaire * l_qnre_ptr = dynamic_cast<TheQuestionnaire*> (AbstractQuestionnaire::qnre_ptr);

	if (valid_input) {
		if (user_input.theUserResponse_ == user_response::UserSavedData) {
			cerr  << "NOT YET DONE"
				<< __FILE__ << "," << __LINE__ << "," << __PRETTY_FUNCTION__
				<< endl
				<< "invoking callback_ui_input with UserSavedData" << endl;
			// this call will return really fast
			//  (if you consider io fast)
			//  but what I mean is we wont add much to the call stack
			//callback_ui_input (user_input, q, theQuestionnaire_, 1);
			//GetUserInput (callback_ui_input, q, theQuestionnaire);
			//cout << "callback_ui_input has returned after UserSavedData" << endl;
		} else {
			cout << "reached here: "
				<< __PRETTY_FUNCTION__ << endl;
			callback_ui_input (user_input, q, l_qnre_ptr, 1);
			cout << "callback_ui_input has returned"
				<< __PRETTY_FUNCTION__ << endl;
		}
		// move all this into callback_ui_input
		// case UserEnteredData

	}
	//void question_eval_loop2 (
	//	UserInput p_user_input,
	//	AbstractRuntimeQuestion * last_question_visited,
	//	AbstractRuntimeQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire, int nest_level );
	//question_eval_loop2 (user_input, q, 0, l_qnre_ptr, /*nest_level + */ 1);
	printf ("EXIT: %s\n", __PRETTY_FUNCTION__);
}

}
