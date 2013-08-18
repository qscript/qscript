#include <sys/types.h>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include "qscript_lib.h"
#include "qscript_debug.h"
#include "qscript_data.hpp"



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
#include "read_disk_data_flex_prototypes.h"
//int32_t read_disk_dataparse();
//int32_t read_disk_datalex();
//extern FILE* read_disk_datain;

	typedef void * yyscan_t;
int read_disk_dataparse(yyscan_t yyscanner,
	std::map <string, question_disk_data*>* qdd_map_ptr,
	std::vector<int>* data_ptr,
	vector<int>* array_index_list_ptr);
int read_disk_datalex (YYSTYPE * yylval_param, yyscan_t yyscanner);

void read_disk_data_init();
//extern QuestionDiskDataMap question_disk_data_map;

//extern WINDOW * data_entry_window;

/*
extern map <string, question_disk_data*> qdd_map;
void clear_previous_data()
{
	for (map<string, question_disk_data *>::iterator it =
			qdd_map.begin(); it != qdd_map.end(); ++it) {
		delete it->second;
		it->second = 0;
	}
	qdd_map.erase(qdd_map.begin(), qdd_map.end());
}
*/

int32_t load_data_from_string(const char * survey_data,
		map <string, question_disk_data*> * qdd_map_ptr)
{
	printf ("Enter: %s\n", __PRETTY_FUNCTION__);
	yyscan_t scanner;
	read_disk_datalex_init(&scanner);
	YY_BUFFER_STATE s_data = read_disk_data_scan_string  (survey_data, scanner);
	vector <int> data;
	vector <int> array_index_list;
	// warning this is the same code as the next function - need
	// to extract it out
	if (! read_disk_dataparse (scanner, qdd_map_ptr, &data, &array_index_list)) {
		//return 1;
		map <string, question_disk_data*> & qdd_map = * qdd_map_ptr;
		for (map<string, question_disk_data*>:: iterator it
				= qdd_map.begin();
				it != qdd_map.end();
				++it) {
			cout << "loaded data for question: "
				<< it->first;
			question_disk_data * qdd = it->second;
			for (int i=0; i<qdd->array_bounds.size(); ++i) {
				cout << "$" << qdd->array_bounds[i];
			}
			cout << ": " ;
			for (int i=0; i<qdd->data.size(); ++i) {
				cout << " " << qdd->data[i];
			}
			cout << endl;
		}
		read_disk_data_delete_buffer(s_data, scanner);
		read_disk_datalex_destroy(scanner);
		printf ("Exit success: %s\n", __PRETTY_FUNCTION__);
		return 1;
	}  else {
		cerr << "input datafile found had errors" << endl;
		read_disk_datalex_destroy(scanner);
		printf ("Exit failure: %s\n", __PRETTY_FUNCTION__);
		return 0;
	}
}

int32_t load_data(string jno, int32_t ser_no,
		map <string, question_disk_data*> * qdd_map_ptr)
{
	yyscan_t scanner;
	//yylex_init(&scanner);
	stringstream s;
	//clear_previous_data();
	s << jno << "_" << ser_no << ".dat";
	//FILE* read_disk_datain;
	FILE * read_disk_datain = fopen (s.str().c_str(), "rb");
	//read_disk_data_init();
	if (read_disk_datain) {
		read_disk_datalex_init(&scanner);
		fflush (read_disk_datain);
		read_disk_dataset_in (read_disk_datain, scanner);
		vector <int> data;
		vector <int> array_index_list;
		if (! read_disk_dataparse (scanner, qdd_map_ptr, &data, &array_index_list)) {
			//return 1;
			map <string, question_disk_data*> & qdd_map = * qdd_map_ptr;
			for (map<string, question_disk_data*>:: iterator it
					= qdd_map.begin();
					it != qdd_map.end();
					++it) {
				cout << "loaded data for question: "
					<< it->first;
				question_disk_data * qdd = it->second;
				for (int i=0; i<qdd->array_bounds.size(); ++i) {
					cout << "$" << qdd->array_bounds[i];
				}
				cout << ": " ;
				for (int i=0; i<qdd->data.size(); ++i) {
					cout << " " << qdd->data[i];
				}
				cout << endl;
			}
			read_disk_datalex_destroy(scanner);
			fclose (read_disk_datain);
			return 1;
		} else {
			cerr << "input datafile found had errors" << endl;
			read_disk_datalex_destroy(scanner);
			fclose (read_disk_datain);
			return 0;
		}
		fclose (read_disk_datain);
	}

	//cerr << "finished loading data - here is the summary" << endl;
	//for(int32_t i = 0; i<qdd_list.size(); ++i){
	//	cerr << qdd_list[i]->qno;
	//	for(int32_t j = 0; j<qdd_list[i]->data.size(); ++j){
	//		cerr << " " << qdd_list[i]->data[j];
	//	}
	//	cerr << endl;
	//}
	// case : unable to open data file for read
	return 0;
}

#include "question.h"

//extern vector <AbstractRuntimeQuestion*> question_list;
void merge_disk_data_into_questions2(FILE * qscript_stdout, AbstractRuntimeQuestion * & p_last_question_answered,
		vector<AbstractRuntimeQuestion *> & p_last_question_visited, const vector <AbstractRuntimeQuestion*> question_list,
		map <string, question_disk_data*> * qdd_map_ptr)

{
	map <string, question_disk_data*> & qdd_map =  * qdd_map_ptr;
	if (qscript_debug::DEBUG_LoadData) {
		cout << "ENTER: "
			<< __PRETTY_FUNCTION__
			<< __FILE__ << ", " << __LINE__ << ", "
			<< endl;
	}
	for (int32_t i = 0; i< question_list.size(); ++i) {
		AbstractRuntimeQuestion* q= question_list[i];


		//fprintf(qscript_stdout, "searching for %s \n", q->questionDiskName_.c_str());
		cout << "searching for " << q->questionDiskName_ << "\n";

		map<string,question_disk_data*>::iterator it=  qdd_map.find (q->questionDiskName_);
		if (  it != qdd_map.end()) {
			cout << "found " << q->questionDiskName_ << "\n";
			question_disk_data * q_disk = it->second;
			q->input_data.erase(q->input_data.begin(), q->input_data.end());
			if (q_disk->data.size() > 0) {
				for (int32_t k = 0; k<q_disk->data.size(); ++k) {
					if (qscript_debug::DEBUG_LoadData) {
						cout << "inserting q_disk->data[k]: " << q_disk->data[k] << endl;
					}
					//fprintf(qscript_stdout, "inserting into %s %d\n", q->questionDiskName_.c_str(), q_disk->data[k]);
					q->input_data.insert(q_disk->data[k]);
				}
				q->isAnswered_ = true;
				//last_question_answered = q;
				p_last_question_answered = q;
				p_last_question_visited.push_back(q);
			}
		}
	}
}

enum EvalMode { USER_NAVIGATION, NORMAL_FLOW };
#include "user_navigation.h"


