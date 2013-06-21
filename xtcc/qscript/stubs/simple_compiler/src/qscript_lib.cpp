#include <sys/types.h>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include "qscript_lib.h"
#include "qscript_debug.h"



// check_if_reg_file_exists: concats jno and ser_no separated by _
// and checks if this exists as a regular file
// if regular file -> returns 1
// 		returns -1 if stat operation failed
//		returns 0 if not a regular file
int32_t check_if_reg_file_exists(string jno, int32_t ser_no)
{
	stringstream s;
	s << jno << "_" << ser_no << ".dat";
	struct stat file_info;
	int32_t stat_res = stat(s.str().c_str(), &file_info);
	if (stat_res == -1){
		return -1;
	} else if (stat_res == 0) {
		if (S_ISREG(file_info.st_mode)){
			return 1;
		} else
			return 0;
	} else {
		fprintf(stderr, "Undocumented return value of stat function : should be -1 or 0 only\
				... exiting: line: %d, file: %s\n", __LINE__, __FILE__);
		exit(1);
	}
}

#include <vector>
#include <map>
#include "question_disk_data.h"
int32_t read_disk_dataparse();
int32_t read_disk_datalex();
extern FILE* read_disk_datain;
void read_disk_data_init();
extern QuestionDiskDataMap question_disk_data_map;

extern map <string, question_disk_data*> qdd_map;
//extern WINDOW * data_entry_window;

void clear_previous_data()
{
	for (map<string, question_disk_data *>::iterator it =
			qdd_map.begin(); it != qdd_map.end(); ++it) {
		delete it->second;
		it->second = 0;
	}
	qdd_map.erase(qdd_map.begin(), qdd_map.end());
}

int32_t load_data(string jno, int32_t ser_no)
{
	stringstream s;
	clear_previous_data();
	s << jno << "_" << ser_no << ".dat";
	read_disk_datain = fopen(s.str().c_str(), "rb");
	read_disk_data_init();
	if (read_disk_datain) {
		fflush(read_disk_datain);
		if (!read_disk_dataparse()) {
			//return 1;
		} else {
			cerr << "input datafile found had errors" << endl;
			return 0;
		}
	}
	fclose (read_disk_datain);
	//cerr << "finished loading data - here is the summary" << endl;
	//for(int32_t i = 0; i<qdd_list.size(); ++i){
	//	cerr << qdd_list[i]->qno;
	//	for(int32_t j = 0; j<qdd_list[i]->data.size(); ++j){
	//		cerr << " " << qdd_list[i]->data[j];
	//	}
	//	cerr << endl;
	//}
	return 1;
}

#include "question.h"
extern vector <AbstractQuestion*> question_list;
void merge_disk_data_into_questions2(FILE * qscript_stdout, AbstractQuestion * & p_last_question_answered,
		AbstractQuestion * & p_last_question_visited)
{
	if (qscript_debug::DEBUG_LoadData) {
		cout << "ENTER: "
			<< __PRETTY_FUNCTION__
			<< __FILE__ << ", " << __LINE__ << ", "
			<< endl;
	}
	for (int32_t i = 0; i< question_list.size(); ++i) {
		AbstractQuestion* q= question_list[i];


		if (qscript_debug::DEBUG_LoadData) {
			fprintf(qscript_stdout, "searching for %s \n", q->questionDiskName_.c_str());
		}
		map<string,question_disk_data*>::iterator it=  qdd_map.find (q->questionDiskName_);
		if (  it != qdd_map.end()) {
			question_disk_data * q_disk = it->second;
			if (q->input_data.begin() != q->input_data.end()) {
				q->input_data.erase(q->input_data.begin(), q->input_data.end());
			}
			if (q_disk->data.size() > 0) {
				for (int32_t k = 0; k<q_disk->data.size(); ++k) {
					if (qscript_debug::DEBUG_LoadData) {
						//cout << "inserting q_disk->data[k]: " << q_disk->data[k] << endl;
						fprintf(qscript_stdout, "inserting into %s %d\n", q->questionDiskName_.c_str(), q_disk->data[k]);
					}
					q->input_data.insert(q_disk->data[k]);
				}
				q->isAnswered_ = true;
				//last_question_answered = q;
				p_last_question_answered = q;
				p_last_question_visited = q;
			}
		}
	}
}


#include <fstream>
#include "qtm_data_file.h"

qtm_data_file_ns::QtmDataDiskMap* GetQuestionMapEntry(vector <qtm_data_file_ns::QtmDataDiskMap*> & qtm_datafile_question_disk_map,
string name)
{
	for (int i=0; i < qtm_datafile_question_disk_map.size(); ++i)
	{
		if (qtm_datafile_question_disk_map[i]->q->questionName_ == name)
		{
			return qtm_datafile_question_disk_map[i];
		}
	}
	return 0;
}


vector <qtm_data_file_ns::QtmDataDiskMap*> GetQuestionMapEntryArrayQ
(vector <qtm_data_file_ns::QtmDataDiskMap*> & qtm_datafile_question_disk_map,
string name)
{
	string dummy_output_filename (string("dummy.output"));
	fstream dummy_output_file(dummy_output_filename.c_str(), ios_base::out|ios_base::app);
	dummy_output_file << "searching for : " << name << endl;
	vector <qtm_data_file_ns::QtmDataDiskMap*> result ;
	for (int i=0; i < qtm_datafile_question_disk_map.size(); ++i)
	{
		string s1 = qtm_datafile_question_disk_map[i]->q->questionName_ ;
		dummy_output_file << "questionName_: " << s1 << endl;
		string s3 = "";
		if (s1.length() > name.length())
		{
			s3 = s1.substr(0, name.length());
		}
		dummy_output_file << s3 << endl;
		if (qtm_datafile_question_disk_map[i]->q->questionName_ == name)
		{
			result.push_back(qtm_datafile_question_disk_map[i]);
			dummy_output_file << "added to result" << endl;
		}
	}
	return result;
}

#include "named_range.h"

void print_brand_rank_recode_edit_and_qax (string jno, string driver_brand_question, string driver_brand_rank_question
		, vector <string> recode_questions_list
		, vector <qtm_data_file_ns::QtmDataDiskMap*> qtm_datafile_question_disk_map
		, int n_ranks
		)
{
	using std::fstream;
	string variable_defns_fname (string("setup-") + jno + string("/") + string("variable1"));
	fstream variable_file (variable_defns_fname.c_str(), ios_base::out|ios_base::ate);




	string edit_file_name (string("setup-") + jno + string("/") + jno + string("-brand-rank-recode-edit.qin"));
	fstream edit_file (edit_file_name.c_str(), ios_base::out|ios_base::ate);

	vector<qtm_data_file_ns::QtmDataDiskMap *> q13_brd_map_entry_vec =
		GetQuestionMapEntryArrayQ (qtm_datafile_question_disk_map, driver_brand_question);
	for (int i=0;  i < q13_brd_map_entry_vec.size(); ++i) {
		edit_file
			<< driver_brand_question << "_cols(" << i + 1 << ")"
			<< " = " << q13_brd_map_entry_vec[i]->startPosition_ + 1
			<< endl;
	}
	edit_file << endl;
	edit_file << endl;
	vector<qtm_data_file_ns::QtmDataDiskMap *> q13_brd_rnk_map_entry_vec =
		GetQuestionMapEntryArrayQ (qtm_datafile_question_disk_map, driver_brand_rank_question);
	for (int i=0;  i < q13_brd_rnk_map_entry_vec.size(); ++i) {
		edit_file
			<< driver_brand_rank_question  << "_cols(" << i + 1 << ")"
			<< " = "
			<< q13_brd_rnk_map_entry_vec[i]->startPosition_ + 1
			<< endl;
	}
#if 0
	for (int i=0, j=0;  i < q13_brd_map_entry_vec.size(); ++i) {
		if (driver_brand_rank_question == qtm_datafile_question_disk_map[i]->q->questionName_) {
			++j;
			if (j == 1) {
				q13_brd_map_entry = qtm_datafile_question_disk_map[i];
			}
			edit_file
				<< driver_brand_rank_question  << "_cols(" << j << ")"
				<< " = "
				<< qtm_datafile_question_disk_map[i]->startPosition_ + 1
				<< endl;
		}
	}
#endif /* 0 */
	//NamedStubQuestion * nq = dynamic_cast <NamedStubQuestion*> (q13_brd_list.questionList[0]);
	NamedStubQuestion * nq = dynamic_cast <NamedStubQuestion*>
		(
		 q13_brd_map_entry_vec[0]->q
		 );

	if (!variable_file) {
		cerr << "unable to open file: variable for writing" << endl;
		exit(1);
	}

	variable_file
			<< "int rnk_col 1" << endl
			<< "int brd_col 1" << endl
			<< "int output_col_no 1" << endl
			<< "int input_col_no 1" << endl
			<< "int " << driver_brand_question
				<< "_cols " << nq->dummyArrayQuestion_->array_bounds[0]
				<< "s"
				<< endl
			<< "int " << driver_brand_rank_question
				<< "_cols " << nq->dummyArrayQuestion_->array_bounds[0]
				<< "s"
				<< endl
			<< endl;
	cerr << "output sent to variable_file" << endl;



	edit_file << endl << endl;
	qtm_data_file_ns::QtmDataDiskMap * q13_brd_map_entry = q13_brd_map_entry_vec[0];
	for (int i=0;  i < nq->nr_ptr->stubs.size(); ++i) {
		edit_file
			<< "clear "
			<< driver_brand_question
			<< "_"
			<< nq->nr_ptr->stubs[i].stub_text_as_var_name()
			<< " (1, "
			<< q13_brd_map_entry->totalLength_ << ")"    << endl;
		variable_file
			<< "data "
			<< driver_brand_question
			<< "_"
			<< nq->nr_ptr->stubs[i].stub_text_as_var_name()
			<< " "
			<< q13_brd_map_entry->totalLength_ << "s"    << endl;
	}
	variable_file  << endl;
	edit_file
		<< endl
		<< "do 10 t1=1,10,1" << endl
		<< "	rnk_col = " << driver_brand_rank_question << "_cols(t1)" << endl
		<< "	brd_col = " << driver_brand_question << "_cols(t1)" << endl;

	edit_file << endl << endl;
	for (int i=0;  i < nq->nr_ptr->stubs.size(); ++i) {
		edit_file
			<< "	if (c(brd_col, brd_col+1).eq."
			<< nq->nr_ptr->stubs[i].code << ")\t\t"
			<< driver_brand_question
			<< "_" << nq->nr_ptr->stubs[i].stub_text_as_var_name()
			<< "(1, " << q13_brd_map_entry->totalLength_ << ")" << " = c(rnk_col, rnk_col+1)\n";
	}
	edit_file << "10 continue" << endl;

	edit_file << endl << endl;
	string recode_edit_qax_file_name (string("setup-") + jno + string("/") +jno + string("-brand-rank-recode-edit.qax"));
	fstream recode_edit_qax_file (recode_edit_qax_file_name.c_str(), ios_base::out|ios_base::ate);
	{
		vector<qtm_data_file_ns::QtmDataDiskMap *> q15_map_entry_vec =
			GetQuestionMapEntryArrayQ (qtm_datafile_question_disk_map, recode_questions_list[0]);
		//NamedStubQuestion * rnq = dynamic_cast <NamedStubQuestion*> (q15_list.questionList[0]);
		NamedStubQuestion * rnq = dynamic_cast <NamedStubQuestion*> (q15_map_entry_vec[0]->q);
		for (int i=0;  i < nq->nr_ptr->stubs.size(); ++i) {
			edit_file
				<< "clear "
				<< recode_questions_list[0]
				<< "_"
				<< nq->nr_ptr->stubs[i].stub_text_as_var_name()
				<< " (1, "
				<< q15_map_entry_vec.size()
				<< ")"
				<< endl;
			variable_file
				<< "data "
				<< recode_questions_list[0]
				<< "_"
				<< nq->nr_ptr->stubs[i].stub_text_as_var_name()
				<< " "
				<< rnq->dummyArrayQuestion_->array_bounds[0] << "s"    << endl;
		}
		edit_file << endl << endl;
		edit_file << "do 9 output_col_no=1," << q15_map_entry_vec.size() << endl;
		for (int i=0;  i < nq->nr_ptr->stubs.size(); ++i) {
			edit_file
				<< "	if (" << nq->questionName_
				<< "_" << nq->nr_ptr->stubs[i].stub_text_as_var_name()
				<< " (1, " << q13_brd_map_entry->totalLength_
				<< ") .in. (1: " << n_ranks << "))"
				<< "	"
				<< recode_questions_list[0]
				<< "_"
				<< nq->nr_ptr->stubs[i].stub_text_as_var_name()
				<< " (output_col_no  "
				<< ") = 0\n";
		}
		edit_file << "9 continue;\n" << endl;
		edit_file << "output_col_no = 1\n";
		edit_file << "do 120 input_col_no = (";
		for (int i=0;  i < q15_map_entry_vec.size(); ++i) {
			edit_file << q15_map_entry_vec[i]->startPosition_+1 << " ";
			if (i < q15_map_entry_vec.size()-1) edit_file << ", ";
		}
		edit_file  << ")" << endl;
		edit_file << "	t3 = 1;" << endl;
		edit_file << "	do 25 'punch' = (";
		for (int i=1;  i <= 12; ++i) {
			edit_file << "'" << i % 10 << "' "; if (i < 12) edit_file << ", ";
		}
		edit_file << "	)" << endl;
#if 0
#endif /*  0 */
		for (int i=0;  i < nq->nr_ptr->stubs.size(); ++i) {
			edit_file
				<< "		if (c(input_col_no)'punch' .and.  " << driver_brand_question
				<< "_"  << nq->nr_ptr->stubs[i].stub_text_as_var_name()
				<< " (1, "
				<< q13_brd_map_entry->totalLength_
				<< ").eq.t3)		"
				<< recode_questions_list[0]
				<< "_"
				<< nq->nr_ptr->stubs[i].stub_text_as_var_name()
				<< " (output_col_no)=1 "
				<< endl;
		}
		edit_file << "	t3=t3+1;" << endl;
		edit_file << "	25 continue" << endl;
		edit_file << "120 continue" << endl;


		for (int j=0; j < q15_map_entry_vec.size(); ++j) {
			recode_edit_qax_file
				<< "*include " << rnq->questionName_ << "_fix.qax"
				<< ";col_no=" << j + 1
				<< ";qlno=" << j+1
				<< ";q1att=&at0t;att1t=0;q2att=;att2t=/*;"
				<< endl;
		}
		string q15_qax_file_name  =
			string("setup-") + jno + string("/")
			+rnq->questionName_  + string("_fix.qax");
		fstream q15_qax_file (q15_qax_file_name.c_str(), ios_base::out|ios_base::ate);
		q15_qax_file << "l " << rnq->questionName_ << "_fix_&qlno" << endl
			<< "*include qttl.qin;qt1it="
			<< rnq->AxPrepareQuestionTitle()
			<< "+qt2it=;act2t=/*;\n+qt3it=;act3t=/*;\n+qt4it=;act4t=/*;\n"
			<< "*include base.qin;btxt=All Respondents\n"
			<< "#include " << rnq->questionName_ << "_fix.qin" << endl
			<< endl;

		string q15_qin_file_name  =
				string("setup-") + jno + string("/")
				+ rnq->questionName_  + string("_fix.qin");
		fstream q15_qin_file (q15_qin_file_name.c_str(), ios_base::out|ios_base::ate);
		for (int i=0;  i < nq->nr_ptr->stubs.size(); ++i) {
			q15_qin_file << "n01"
				<< nq->nr_ptr->stubs[i].stub_text
				<< ";\t\t\t\tc="
				<< rnq->questionName_ << "_"
				<< nq->nr_ptr->stubs[i].stub_text_as_var_name()
				<< "(&col_no)=$1$"
				<< endl;
		}
	}

	string q13_brd_qin_fname (string("setup-") + jno + string("/br-")
			+ nq->questionName_ + string(".qin"));
	fstream q13_brd_qin_file (q13_brd_qin_fname.c_str(), ios_base::out|ios_base::ate);
	for (int i=0;  i < nq->nr_ptr->stubs.size(); ++i) {
		q13_brd_qin_file
			<< "n01"
			<< nq->nr_ptr->stubs[i].stub_text_as_var_name()
			<< ";c="
			<< nq->questionName_ << "_"
			<< nq->nr_ptr->stubs[i].stub_text_as_var_name()
			<< "(1, "
			<< q13_brd_map_entry->totalLength_
			<< ").in.(&rnk)"
			<< endl;

	}


	recode_edit_qax_file  << "l " << driver_brand_question << "_rnk_1"
		<< endl
		<< "ttl " << nq->AxPrepareQuestionTitle()
		<< "Rank 1"
		<< endl
		<< "n10Total" << endl
		<< "#include br-" << nq->questionName_ << ".qin;rnk=1;"
		<< endl
		<< endl;

	recode_edit_qax_file  << "l " << driver_brand_question << "_rnk_12"
		<< endl
		<< "ttl " << nq->AxPrepareQuestionTitle()  << ": Rank 1 and 2" << endl
		<< "n10Total" << endl
		<< "#include br-" << nq->questionName_ << ".qin;rnk=1:2;"
		<< endl
		<< endl;

	recode_edit_qax_file  << "l " << driver_brand_question << "_rnk_123"
		<< endl
		<< "ttl " << nq->AxPrepareQuestionTitle()  << ": Rank 1, 2, 3" << endl
		<< "n10Total" << endl
		<< "#include br-" << nq->questionName_ << ".qin;rnk=1:3;"
		<< endl
		<< endl;

	/*

	recode_edit_qax_file  << "l " << driver_brand_question << "_rnk_10"
		<< endl
		<< "ttl Rank 10" << endl
		<< "n10Total" << endl
		<< "#include br-" << nq->questionName_ << ".qin;rnk=10;"
		<< endl
		<< endl;

	recode_edit_qax_file  << "l " << driver_brand_question << "_rnk_910"
		<< endl
		<< "ttl Rank 9, 10" << endl
		<< "n10Total" << endl
		<< "#include br-" << nq->questionName_ << ".qin;rnk=9:10;"
		<< endl
		<< endl;

	recode_edit_qax_file  << "l " << driver_brand_question << "_rnk_810"
		<< endl
		<< "ttl Rank 8, 9 and 10" << endl
		<< "n10Total" << endl
		<< "#include br-" << nq->questionName_ << ".qin;rnk=8:10;"
		<< endl
		<< endl;
	*/

}

void print_process_edit_and_qax (string jno
		, vector <string> driver_question_list
		, vector <string> recode_questions_list
		, vector <qtm_data_file_ns::QtmDataDiskMap*> qtm_datafile_question_disk_map
		)
{
	if (driver_question_list.size() == 0) {
		return;
	}
	qtm_data_file_ns::QtmDataDiskMap * pd_rot1_map_entry =
		GetQuestionMapEntry (qtm_datafile_question_disk_map, driver_question_list[0]);

	NamedStubQuestion * driver_question = dynamic_cast <NamedStubQuestion*> ( pd_rot1_map_entry->q);

	using std::fstream;
	string variable_defns_fname (string("setup-") + jno + string("/") + string("variable-prc"));
	fstream variable_file (variable_defns_fname.c_str(), ios_base::out|ios_base::ate);
	variable_file << driver_question->questionName_ << endl;
	string process_axes_file_name (string("setup-") + jno + string("/") + jno + string("-process-axes2.qax"));
	fstream process_axes_file (process_axes_file_name.c_str(), ios_base::out|ios_base::ate);
	int no_loops_in_qnre =  driver_question_list.size();

	// string recode_edit_qax_file_name (string(\"setup-") + jno + string("/") +jno + string(\"-recode-edit2.qax"));
	// fstream recode_edit_qax_file (recode_edit_qax_file_name.c_str(), ios_base::out|ios_base::ate);
	string process_edit_file_name (string("setup-") + jno + string("/") + jno + string("-process-edit2.qin"));
	fstream process_edit_file (process_edit_file_name.c_str(), ios_base::out|ios_base::ate);


	process_edit_file
		<< "serial = c(101,108)" << endl
		<< "proc = 0"
		<< endl;
	for (int j2=0; j2 < driver_question_list.size(); ++j2) {
		string driver_question_name = driver_question_list[j2];
		qtm_data_file_ns::QtmDataDiskMap * driver_question_map_entry =
			GetQuestionMapEntry (qtm_datafile_question_disk_map, driver_question_name);
		process_edit_file
			<< "/* ===== Slot : " << j2+1 << "  ===== */" << endl
			<< "clear driver_code" << endl
			<< "driver_code = c("
			<< driver_question_map_entry -> startPosition_ + 1
			<< ","
			<< driver_question_map_entry -> startPosition_ + driver_question_map_entry->totalLength_
			<< ")" << endl;
		for (int j1 = 0; j1 < recode_questions_list.size(); j1 += no_loops_in_qnre) {
			string rec_question_name = recode_questions_list[j2 + j1];
			string leader_rec_question_name = recode_questions_list[j1];
				//recode_edit.program_code << "{" << endl;
				//recode_edit.program_code
					//<< "\t\t\tqtm_data_file_ns::QtmDataDiskMap * "
					//<< driver_question_name
					//<< "_map_entry =\n"
					//<< "\t\t\t\tGetQuestionMapEntry (qtm_datafile_question_disk_map, "
					//<< driver_question_name << "->questionName_);" << endl
			qtm_data_file_ns::QtmDataDiskMap * rec_question_name_map_entry =
				GetQuestionMapEntry (qtm_datafile_question_disk_map, rec_question_name);
				if (j2 == 0) {
					variable_file
						<< "data proc_" << rec_question_name
						<< rec_question_name_map_entry->totalLength_  << "s"
						<< endl;

					process_axes_file
						<< "l p_" << rec_question_name
						<< ";c= proc .gt. 0" << endl
						<< "ttl P." << rec_question_name
						<< endl;
				}

				process_edit_file
					<< "clear proc_"
					<< leader_rec_question_name
					<< "(1, "
					<< rec_question_name_map_entry->totalLength_
					<< " );" << endl
					<< "proc_" << leader_rec_question_name
					<< "(1,"
					<< rec_question_name_map_entry->totalLength_ << ")= "
					<< "c(" << rec_question_name_map_entry->startPosition_ + 1
					<< ", "
					<< rec_question_name_map_entry->startPosition_ +
						rec_question_name_map_entry->totalLength_
					<< ") ;"
					<< endl;
				//recode_edit.program_code << "}" << endl;
		}
		process_edit_file
			<< endl << endl
			<< "proc =  " << j2+1 << endl
			<< "process "<< endl << endl;
	}
	process_edit_file
		<< "proc =  0"
		<< endl;

}
