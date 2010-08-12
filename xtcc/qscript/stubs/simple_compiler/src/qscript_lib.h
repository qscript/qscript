#ifndef qscript_lib_h
#define qscript_lib_h

//#include <sstream>
//#include <iosfwd>
#include <string>
#include <sys/stat.h>
using namespace std;
int check_if_reg_file_exists(string jno, int ser_no);
int load_data(string jno, int ser_no);
void merge_disk_data_into_questions(FILE * qscript_stdout);
#endif /* qscript_lib_h */
