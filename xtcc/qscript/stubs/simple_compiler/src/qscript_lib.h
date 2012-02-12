#ifndef qscript_lib_h
#define qscript_lib_h

//#include <sstream>
//#include <iosfwd>
#include <string>
#include <sys/stat.h>
#include <vector>
#include <map>
#include <string>
#include "question_disk_data.h"
#include "new_named_range.h"

struct AbstractQuestion;
//using namespace std;
int32_t check_if_reg_file_exists(std::string jno, int32_t ser_no);
int32_t load_data(string jno, int32_t ser_no, 
		map <string, question_disk_data*> * qdd_map_ptr,
		vector <NamedRangeGroup*> * vec_nrg_ptr);
//void merge_disk_data_into_questions(FILE * qscript_stdout);
//void clear_previous_data();
//void merge_disk_data_into_questions2(FILE * qscript_stdout, AbstractQuestion * & p_last_question_answered,
//		AbstractQuestion * & p_last_question_visited, const vector <AbstractQuestion*> question_list);
void merge_disk_data_into_questions2(FILE * qscript_stdout,
		AbstractQuestion * & p_last_question_answered,
		AbstractQuestion * & p_last_question_visited,
		const std::vector <AbstractQuestion*> question_list,
		std::map <string, question_disk_data*> * qdd_map_ptr);

#endif /* qscript_lib_h */
