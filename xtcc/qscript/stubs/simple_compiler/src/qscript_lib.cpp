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
	if (read_disk_datain){
		fflush(read_disk_datain);
		if (!read_disk_dataparse()){
			//return 1;
		} else {
			cerr << "input datafile found had errors" << endl;
			return 0;
		}
	}
	fclose(read_disk_datain);
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


		fprintf(qscript_stdout, "searching for %s \n", q->questionDiskName_.c_str());
		map<string,question_disk_data*>::iterator it=  qdd_map.find (q->questionDiskName_);
		if (  it != qdd_map.end()) {
			question_disk_data * q_disk = it->second;
			if (q->input_data.begin() != q->input_data.end()) {
				q->input_data.erase(q->input_data.begin(), q->input_data.end());
			}
			if (q_disk->data.size() > 0) {
				for (int32_t k = 0; k<q_disk->data.size(); ++k) {
					if (qscript_debug::DEBUG_LoadData) {
						cout << "inserting q_disk->data[k]: " << q_disk->data[k] << endl;
					}
					fprintf(qscript_stdout, "inserting into %s %d\n", q->questionDiskName_.c_str(), q_disk->data[k]);
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


// this is inefficient and will later be replaced
// but right now i want to see this working
// ideally we should be storing the questions in a map
// with the AbstractQuestion no as a key and the index as the value
// and looking up the vector that way
//extern AbstractQuestion * last_question_answered;
#if 0
void merge_disk_data_into_questions(FILE * qscript_stdout, AbstractQuestion * & p_last_question_answered,
		AbstractQuestion * & p_last_question_visited)
{
	//cout << "merge_disk_data_into_questions: " << endl;
	if (qscript_debug::DEBUG_LoadData) {
		cout << "ENTER: " 
			<< __PRETTY_FUNCTION__ 
			<< __FILE__ << ", " << __LINE__ << ", " 
			<< endl;
	}
	for (int32_t i = 0; i< question_list.size(); ++i) {
		if (question_list[i]->loop_index_values.size() > 0) {
			if (qscript_debug::DEBUG_LoadData) {
				cout << "have reached the 1st array question - exiting the " << __PRETTY_FUNCTION__
					<< endl;
			}
			break;
		}
		bool found = false;
		AbstractQuestion* q= question_list[i];
		question_disk_data * q_disk = 0;
		if (qscript_debug::DEBUG_LoadData) {
			cout << "searching for : |" << q->questionName_  << "|" << endl;
			cout << "qdd_list:" ;
		}
		fprintf(qscript_stdout, "searching for : |%s|, text: |%s|\n", q->questionName_.c_str(), q->questionText_.c_str());
		fflush(qscript_stdout);
		for (int32_t j = 0; j< qdd_list.size(); ++j) {
			if (qscript_debug::DEBUG_LoadData) {
				cout << "|" <<qdd_list[j]->qno << "|" << " ";
			}
			fprintf(qscript_stdout, "|%s| ", qdd_list[j]->qno.c_str() );
			fflush(qscript_stdout);
			if (q->questionName_ == qdd_list[j]->qno) {
				if (qscript_debug::DEBUG_LoadData) {
					cout << "found in qdd_list[" << j << "]" << qdd_list[j]->qno << endl;
				}
				fprintf(qscript_stdout, "found in qdd_list[%d]:%s\n",  j,  qdd_list[j]->qno.c_str());
				fflush(qscript_stdout);
				q_disk = qdd_list[j];
				found = true;
				break;
			}
		}
		if (found) {
			DummyArrayQuestion * dum_q = dynamic_cast<DummyArrayQuestion*>(q);
			if (dum_q) {
				if (qscript_debug::DEBUG_LoadData) {
					cout << q->questionName_ << " is a DummyArrayQuestion: Text: " 
						<< q->questionText_
						<< endl;
				}
				int32_t max_bound =1;
				if (qscript_debug::DEBUG_LoadData) {
					cout << "array bounds are: " ;
				}
				for (int32_t k=0; k< dum_q->array_bounds.size(); ++k) {
					if (qscript_debug::DEBUG_LoadData) {
						cout << dum_q->array_bounds[k] << " ";
					}
					max_bound *=  dum_q->array_bounds[k];
				}
				if (qscript_debug::DEBUG_LoadData) {
					cout << "max_bound: " << max_bound << endl;
				}
				map<int, vector<int32_t> > & array_question_data = question_disk_data_map.array_question_map[q->questionName_];
				if (qscript_debug::DEBUG_LoadData) {
					cout << "disk data map for " << q->questionName_ << " looks like this: " << endl;
					for (map<int, vector<int32_t> >::iterator it1 = array_question_data.begin();
							it1 != array_question_data.end(); ++it1) {
						cout << "iter: " << it1->first << "|" ;
						vector<int32_t> v = it1->second;
						for (int i1 =0; i1<v.size(); ++i1) {
							cout << v[i1] << " ";
						}
						cout << endl;
					}
				}
				int array_start_point = -1;
				for(int k=i+1; k<question_list.size(); ++k) {
					if (question_list[k]->questionName_ == q->questionName_) {
						array_start_point = k;
						break;
					}
				}
				if (qscript_debug::DEBUG_LoadData) {
					cout << question_list[array_start_point]->questionName_
						<< ", array_start_point: " << array_start_point 
						<< endl;
				}
				if (array_start_point == -1) {
					cout << "this can never be: " << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
					cout << "exiting";
					exit(1);
				}
				for (int k=0; k<max_bound; ++k) {
					if (array_question_data.find(k) != array_question_data.end()) {

						//AbstractQuestion * q1=question_list[array_start_point+k];
						AbstractQuestion *q1 =0;
						// this is a really bad, slow method of loading the array question
						// with data
						//cout << "starting at " << array_start_point
						//	<< question_list[l]->questionName_ << ", "
						//	<< q->questionName_
						//	<< endl;
						
						if (qscript_debug::DEBUG_LoadData) {
							cout << " we are doing iteration no: " << k
								<< " of the array question: " << q->questionName_ 
								<< endl;
						}
						int array_quest_loc=array_start_point;
						/*
						for (int l=0; l<=k; ++l) {
							cout << ".";
							if ( (array_start_point+l) < question_list.size() 
								&& question_list[array_start_point+l]->questionName_ == q->questionName_ 
								&& l == k) {
								if (qscript_debug::DEBUG_LoadData) {
									cout << "breaking out: " 
										<< "k: " << k << ", "
										<< "l: " << l << ", "
										<< question_list[array_start_point+l]->questionName_
										<< ", " 
										<< q->questionName_ 
										<< endl;
								}
								array_quest_loc = array_start_point+l;
								break;
							}
						}
						*/
						
						int arr_idx=0; 
						while (array_quest_loc<question_list.size()) {
							if (question_list[array_quest_loc]->questionName_
									== q->questionName_) {
								if (arr_idx<k)
									++arr_idx;
								else {
									break;
								}
							}
							++array_quest_loc;
						}
						//cout << endl;
						
						if (qscript_debug::DEBUG_LoadData) {
							cout << "array_start_point: " << array_start_point
								<< ", array_quest_loc: " << array_quest_loc
								<< endl;
						}
						q1 = question_list[array_quest_loc];


						//for (int l=array_start_point; l<question_list.size(); ++l) {
						//	if (question_list[l]->questionName_ == q->questionName_) {
						//		q1 = question_list[array_start_point+l];
						//		break;
						//	}
						//}
						if (q1 == 0) {
							continue;
						}
					
						if (qscript_debug::DEBUG_LoadData) {
							cout << "Loading data for question: q1=" << q1->questionName_
								<< ", q=" << q->questionName_;
								;
						}
						//for (int l=0; l<q1->loop_index_values.size(); ++l) {
						// 	cout << "$" << q1->loop_index_values[l];
						//}

						if (qscript_debug::DEBUG_LoadData) {
							cout << ", k=" << k << endl;
						}

						vector<int32_t> q_data = array_question_data[k];
						q1->input_data.erase(q1->input_data.begin(), q1->input_data.end());
						if (q_data.size() > 0) {
							for (int32_t l = 0; l<q_data.size(); ++l) {
								if (qscript_debug::DEBUG_LoadData) {
									cout << "inserting " << q_data[l] << " into " 
										<< q1->questionName_;
									for(int l1 = 0; l1<q1->loop_index_values.size(); ++l1) {
										cout << q1->loop_index_values[l1] << ".";
									}
									cout << endl;
								}
								q1->input_data.insert(q_data[l]);
							}
							q1->isAnswered_ = true;
							p_last_question_answered = q1;
							p_last_question_visited = q1;
						}
					}
				}
			} else {
				if (qscript_debug::DEBUG_LoadData) {
					cout << "loading data for non-array question: " << q->questionName_ << endl;
				}
				q->input_data.erase(q->input_data.begin(), q->input_data.end());
				if (q_disk->data.size() > 0) {
					for (int32_t k = 0; k<q_disk->data.size(); ++k) {
						if (qscript_debug::DEBUG_LoadData) {
							cout << "inserting q_disk->data[k]: " << q_disk->data[k] << endl;
						}
						q->input_data.insert(q_disk->data[k]);
					}
					q->isAnswered_ = true;
					//last_question_answered = q;
					p_last_question_answered = q;
					p_last_question_visited = q;
				}
			}
			found = false;
		}
	}

	int actual_questions_start_index = 0;
	while (actual_questions_start_index < question_list.size()  && question_list[actual_questions_start_index]->loop_index_values.size() ==0) {
			// keep skipping over dummy array questions which were loaded earlier
		++ actual_questions_start_index;
	}
	for (int32_t i = actual_questions_start_index; i< question_list.size(); ++i) {
		// as per the new layout in memory we have
		// DUMMY ARRAY QUESTIONS
		// QUESTIONS in qnre order - a mix of array and non array questions
		// we have now reached the actual questions
		bool found = false;

		AbstractQuestion* q= question_list[i];
		question_disk_data * q_disk = 0;
		if (q->loop_index_values.size() == 0) {
			for (int32_t j = 0; j< qdd_list.size(); ++j) {
				if (qscript_debug::DEBUG_LoadData) {
					cout << "|" <<qdd_list[j]->qno << "|" << " ";
				}
				fprintf(qscript_stdout, "|%s| ", qdd_list[j]->qno.c_str() );
				fflush(qscript_stdout);
				if (q->questionName_ == qdd_list[j]->qno) {
					if (qscript_debug::DEBUG_LoadData) {
						cout << "found in qdd_list[" << j << "]" << qdd_list[j]->qno << endl;
					}
					fprintf(qscript_stdout, "found in qdd_list[%d]:%s\n",  j,  qdd_list[j]->qno.c_str());
					fflush(qscript_stdout);
					q_disk = qdd_list[j];
					found = true;
					break;
				}
			}
		}
		if (found) {
			if (qscript_debug::DEBUG_LoadData) {
				cout << "loading data for non-array question: " << q->questionName_ << endl;
			}
			q->input_data.erase(q->input_data.begin(), q->input_data.end());
			if (q_disk->data.size() > 0) {
				for (int32_t k = 0; k<q_disk->data.size(); ++k) {
					if (qscript_debug::DEBUG_LoadData) {
						cout << "inserting q_disk->data[k]: " << q_disk->data[k] << endl;
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
#endif  /* 0 */

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
