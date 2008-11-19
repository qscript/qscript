#include "stmt.h"
#include <string>
#include <iostream>

using std::cout;
using std::endl;
void read_data(const char * prompt);

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

	bool invalid_code=false;
	string prompt="before do: Enter Data:";
	do{
		invalid_code=false;
		read_data(prompt.c_str());
		cout << "data.size(): " << data.size() << endl;
		for(int i=0; i<data.size(); ++i){
			cout << "Testing data exists: " << data[i] << endl;
			if (!r_data->exists(data[i])){
				invalid_code=true;
				prompt = "Input contained some invalid data\nRe-enter Data\n";
				data.clear();
				break;
			}
		}
	} while (invalid_code==true);
	

	if(next){
		next->eval();
	}
}


