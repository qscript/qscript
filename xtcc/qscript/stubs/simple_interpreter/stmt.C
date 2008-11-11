#include "stmt.h"
#include <string>
#include <iostream>

using std::cout;
using std::endl;

q_stmt::q_stmt(int l_no, string l_name, string l_text, question_type l_q_type, int l_no_mpn, datatype l_dt,
	xtcc_set& l_r_data): 
	stmt(l_no), name(l_name), text(l_text), q_type(l_q_type) , 
	no_mpn(l_no_mpn),
	dt(l_dt)
{
	r_data = new xtcc_set(l_r_data);
}


#include <sstream>
void q_stmt::eval(){
	cout << name << "." << text << endl << endl;
	for(	set<int>::iterator it=r_data->indiv.begin(); it!=r_data->indiv.end(); ++it){
		cout << *it << endl;
	}
	for(int i=0; i<r_data->range.size(); ++i){
		cout << r_data->range[i].first << ", " << r_data->range[i].second << endl; 
	}
	if(next){
		next->eval();
	}
}
