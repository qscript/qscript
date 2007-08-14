#include "tree.h"
#include <vector>
using namespace std;

extern vector<func_info> func_info_table;

	datatype expr::get_type(){
		/*
		if(type==oper_func_call){
			return func_info_table[index].return_type;
		}
		*/
		return type;
	}

	int expr::isvalid(){
		if (type==error_type){
			return 0;
		} else return 1;
	}
