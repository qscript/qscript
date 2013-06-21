#ifndef qscript_lib_h
#define qscript_lib_h

//#include <sstream>
//#include <iosfwd>
#include <string>
#include <vector>
#include <sys/stat.h>
#include "qtm_data_file.h"
#include "base_text.h"
using namespace std;
int32_t check_if_reg_file_exists(string jno, int32_t ser_no);
int32_t load_data(string jno, int32_t ser_no);
void merge_disk_data_into_questions(FILE * qscript_stdout);
void clear_previous_data();

void print_brand_rank_recode_edit_and_qax (string jno, string driver_brand_question, string driver_brand_rank_question
		, vector <string> recode_questions_list
		, vector <qtm_data_file_ns::QtmDataDiskMap*> qtm_datafile_question_disk_map
		, int n_ranks
		);

void print_process_edit_and_qax (string jno
		, vector <string> driver_question_list
		, vector <string> recode_questions_list
		, vector <qtm_data_file_ns::QtmDataDiskMap*> qtm_datafile_question_disk_map
		);

qtm_data_file_ns::QtmDataDiskMap*
GetQuestionMapEntry(vector <qtm_data_file_ns::QtmDataDiskMap*> & qtm_datafile_question_disk_map,
	string name);
vector <qtm_data_file_ns::QtmDataDiskMap*> GetQuestionMapEntryArrayQ
	(vector <qtm_data_file_ns::QtmDataDiskMap*> & qtm_datafile_question_disk_map,
	string name);
#endif /* qscript_lib_h */
