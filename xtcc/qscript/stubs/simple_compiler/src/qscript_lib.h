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
#endif /* qscript_lib_h */
