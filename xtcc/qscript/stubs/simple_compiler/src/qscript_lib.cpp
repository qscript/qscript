#include <sys/types.h>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include "qscript_lib.h"


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
void merge_disk_data_into_questions(FILE * qscript_stdout)
{
	//cout << "merge_disk_data_into_questions: " << endl;
	for (int32_t i = 0; i< question_list.size(); ++i){
		bool found = false;
		AbstractQuestion* q= question_list[i];
		question_disk_data * q_disk = 0;
		//cout << "searching for : |" << q->questionName_  << "|" << endl;
		//cout << "qdd_list:" ;
		fprintf(qscript_stdout, "searching for : |%s|\n", q->questionName_.c_str());
		fflush(qscript_stdout);
		for(int32_t j = 0; j< qdd_list.size(); ++j){
			//cout << "|" <<qdd_list[j]->qno << "|" << " ";
			fprintf(qscript_stdout, "|%s| ", qdd_list[j]->qno.c_str() );
			fflush(qscript_stdout);
			if (q->questionName_ == qdd_list[j]->qno) {
				//cout << "found in qdd_list[" << j << "]" << qdd_list[j]->qno << endl;
				fprintf(qscript_stdout, "found in qdd_list[%d]:%s\n",  j,  qdd_list[j]->qno.c_str());
				fflush(qscript_stdout);
				q_disk = qdd_list[j];
				found = true;
				break;
			}
		}
		if (found){
			q->input_data.erase(q->input_data.begin(), q->input_data.end());
			if (q_disk->data.size() > 0) {
				for(int32_t k = 0; k<q_disk->data.size(); ++k){
					//cout << "inserting q_disk->data[k]: " << q_disk->data[k] << endl;
					q->input_data.insert(q_disk->data[k]);
				}
				q->isAnswered_ = true;
			}
			found = false;
		}
	}
}
