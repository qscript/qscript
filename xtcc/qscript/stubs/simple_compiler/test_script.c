#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "stmt.h"
#include "xtcc_set.h"
#include "stub_pair.h"
#include "symtab.h"
#include "debug_mem.h"
fstream debug_log_file("xtcc_debug.log", ios_base::out|ios_base::trunc);
using namespace std;
void read_data(const char * prompt);
extern vector<int> data;
vector <question*> question_list;
vector<mem_addr_tab>  mem_addr;
	noun_list_type noun_list[]= {
			{	"void"	, VOID_TYPE},
			{	"int8_t" ,INT8_TYPE},
			{	"int16_t" ,INT16_TYPE},
			{	"int32_t" ,INT32_TYPE},
			{	"float", FLOAT_TYPE},
			{	"double", DOUBLE_TYPE}
		};

int main(){
vector <stub_pair> age;

age.push_back( stub_pair("15 to 21", 1));
age.push_back( stub_pair("22 to 30", 2));
age.push_back( stub_pair("31 to 40", 3));
age.push_back( stub_pair("41 to 59", 4));
xtcc_set xs_0;
xs_0.indiv.insert(1);
xs_0.indiv.insert(2);
range_question * q1 = new range_question(QUESTION_TYPE, 5,string(" q1"),string(" Q1. This is question 1"),spn,0,INT32_TYPE,xs_0);
question_list.push_back(q1);
xtcc_set xs_1;
xs_1.indiv.insert(1);
xs_1.indiv.insert(2);
xs_1.range.push_back(pair<int,int>(5,8));
range_question * q2 = new range_question(QUESTION_TYPE, 10,string(" q2"),string(" Q2. This is question 2"),mpn,5,INT32_TYPE,xs_1);
question_list.push_back(q2);
// named_stub_question::generate_code() : to be implemented
named_stub_question * q3 = new named_stub_question(QUESTION_TYPE, 11,string(" q3"),string(" Q3. Respondents age"),spn,5,INT32_TYPE,&age);
question_list.push_back(q3);

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
	struct temp_0{
		const int size_ran_indiv;
		const int size_start_end;
		vector<int> ran_indiv;
		vector< pair<int,int> > ran_start_end;
		temp_0(): size_ran_indiv(2), size_start_end(0),
			ran_indiv(size_ran_indiv), ran_start_end(size_start_end){
			ran_indiv[0]=1;
			ran_indiv[1]=2;
		}
		bool exists(int key){
			for(int i=0; i<size_start_end; ++i){
				if(key >=ran_start_end[i].first && key <=ran_start_end[i].second){
					return true;
				}
			}
			for(int i=0; i< size_ran_indiv; ++i){
				if(key==ran_indiv[i]){
					return true;
				}
			}
			return false;
		}
	} temp_1;
bool temp_2 = temp_1.exists(q1);
if (temp_2 ){
		q2->eval();
		q3->eval();
}

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
