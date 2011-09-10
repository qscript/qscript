#ifndef qscript_lib_h
#define qscript_lib_h

//#include <sstream>
//#include <iosfwd>
#include <string>
#include <sys/stat.h>
#include <vector>

struct AbstractQuestion;
using namespace std;
int32_t check_if_reg_file_exists(string jno, int32_t ser_no);
int32_t load_data(string jno, int32_t ser_no);
void merge_disk_data_into_questions(FILE * qscript_stdout);
void clear_previous_data();
void merge_disk_data_into_questions2(FILE * qscript_stdout, AbstractQuestion * & p_last_question_answered,
		AbstractQuestion * & p_last_question_visited, const vector <AbstractQuestion*> question_list);
#endif /* qscript_lib_h */
