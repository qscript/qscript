#include "qscript_lib.h"

// check_if_reg_file_exists: concats jno and ser_no separated by _
// and checks if this exists as a regular file 
// if regular file -> returns 1 
// 		returns -1 if stat operation failed
//		returns 0 if not a regular file
int check_if_reg_file_exists(string jno, int ser_no){
	stringstream s;
	s << jno << "_" << ser_no << ".dat";
	struct stat file_info;
	int stat_res=stat(s.str().c_str(), &file_info);
	if(stat_res==-1){
		return -1;
	} else if (stat_res==0) {
		if( S_ISREG( file_info.st_mode) ){
			return 1;
		} else 
			return 0;
	}
}

#include <vector>
#include "question_disk_data.h"
int read_disk_dataparse();
int read_disk_datalex();
extern FILE* read_disk_datain;
void read_disk_data_init();
extern vector <question_disk_data*> qdd_list;
int load_data(string jno, int ser_no){
	stringstream s;
	s << jno << "_" << ser_no << ".dat";
	read_disk_datain = fopen(s.str().c_str(), "rb");
	read_disk_data_init();
	if(read_disk_datain){
		if(!read_disk_dataparse()){
			return 1;
		} else {
			return 0;
		}
	}
}
