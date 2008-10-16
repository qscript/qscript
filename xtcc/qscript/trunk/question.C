#include <question.h>
#include "named_range.h"
#include <vector>

	extern vector<named_range>  named_stubs_list;

using namespace std;
#include <iostream>
void question::print_stmt_lst(FILE * & fptr){
	cout << "question:: print_stmt_lst not yet implemented" << endl;
}

void range_question::print_stmt_lst(FILE *& fptr){
	cout << "range_question::  print_stmt_lst not yet implemented" << endl;
}


named_stub_question::named_stub_question(int line_number, datatype this_stmt_type, 
		string l_name, string l_q_text,
		question_type l_q_type, int l_no_mpn, datatype l_dt,
		string & list_name): question(line_number, this_stmt_type, l_name, l_q_text,
					l_q_type, l_no_mpn, l_dt), named_list(list_name)
	{ 
		bool found=false;
		for(int i=0; i<named_stubs_list.size(); ++i){
			if( named_stubs_list[i].name == named_list){
				found=true;
			}
		}
		if(!found){
			cout << "found named list in named_stubs_list" << endl;
		}
	}

void named_stub_question::print_stmt_lst(FILE *& fptr){
	cout << "named_stub_question ::  print_stmt_lst not yet implemented" << endl;
}
