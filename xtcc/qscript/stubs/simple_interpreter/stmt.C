#include "stmt.h"
#include <string>
#include <iostream>

using std::cout;
using std::endl;
void read_data();

q_stmt::q_stmt(int l_no, string l_name, string l_text, question_type l_q_type, int l_no_mpn, datatype l_dt,
	xtcc_set& l_r_data): 
	stmt(l_no), name(l_name), text(l_text), q_type(l_q_type) , 
	no_mpn(l_no_mpn),
	dt(l_dt)
{
	r_data = new xtcc_set(l_r_data);
}


#include <sstream>
int scan_datalex();
int scan_dataparse();
extern vector<int> data;
void q_stmt::eval(){
	cout << name << "." << text << endl << endl;
	for(	set<int>::iterator it=r_data->indiv.begin(); it!=r_data->indiv.end(); ++it){
		cout << *it << endl;
	}
	for(int i=0; i<r_data->range.size(); ++i){
		for(int j=r_data->range[i].first; j<=r_data->range[i].second;++j){  
			cout << j << endl; 
		}
	}
	read_data();

	if(next){
		next->eval();
	}
}
