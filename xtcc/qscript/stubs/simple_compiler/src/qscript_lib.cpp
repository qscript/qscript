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
#include "question_disk_data.h"
int32_t read_disk_dataparse();
int32_t read_disk_datalex();
extern FILE* read_disk_datain;
void read_disk_data_init();
extern vector <question_disk_data*> qdd_list;
extern QuestionDiskDataMap question_disk_data_map;
//extern WINDOW * data_entry_window;

int32_t load_data(string jno, int32_t ser_no)
{
	stringstream s;
	qdd_list.clear();
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
// this is inefficient and will later be replaced
// but right now i want to see this working
// ideally we should be storing the questions in a map
// with the AbstractQuestion no as a key and the index as the value
// and looking up the vector that way
#include "question.h"
extern vector <AbstractQuestion*> question_list;
//extern AbstractQuestion * last_question_answered;
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
}
