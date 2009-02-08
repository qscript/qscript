#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "stmt.h"
#include "xtcc_set.h"
using namespace std;
void read_data(const char * prompt);
extern vector<int> data;
vector <question*> question_list;
int main(){
xtcc_set xs_0;
xs_0.indiv.insert(1);
xs_0.indiv.insert(2);
question * q1 = new question(7,"q1","Q1. This is question 1",spn,0,INT32_TYPE,xs_0);
question_list.push_back(q1);
xtcc_set xs_1;
xs_1.indiv.insert(1);
xs_1.indiv.insert(2);
xs_1.range.push_back(pair<int,int>(5,8));
question * q2 = new question(11,"q2","Q2. This is question 2",mpn,5,INT32_TYPE,xs_1);
question_list.push_back(q2);
// named_stub_question::generate_code() : to be implemented

	int ser_no;
		cout << "Enter Serial No (0) to exit: " << flush;
		cin >> ser_no;
		string jno="j_1001";
		while(ser_no!=0){
		q1->eval();
 // decl_stmt::generate_code 
int8_t var1=5*12;
 // decl_stmt::generate_code 
int8_t var2=7*var1;
(12.5*13.3)-8+7*(12%7);
		q2->eval();

			stringstream fname_str;
			fname_str << jno << "_" << ser_no << ".dat";
			FILE * fptr = fopen(fname_str.str().c_str(), "w+b");
cout << "Enter Serial No (0) to exit: " << flush;
cin >> ser_no;
	for (int i=0; i<question_list.size(); ++i){
		fprintf(fptr, "%s: ", question_list[i]->name.c_str());
		for( set<int>::iterator iter=question_list[i]->input_data.begin();
				iter!=question_list[i]->input_data.end(); ++iter){
			fprintf(fptr, "%d ", *iter);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);


	} /* close while */

} /* close main */
