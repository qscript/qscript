#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include "stmt.h"
#include "xtcc_set.h"
#include "stub_pair.h"
#include "symtab.h"
#include "qscript_lib.h"
#include "question_disk_data.h"
#include "debug_mem.h"
fstream debug_log_file("xtcc_debug.log", ios_base::out|ios_base::trunc);
using namespace std;
void read_data(const char * prompt);
extern vector<int> data;
vector <question*> question_list;
vector<mem_addr_tab>  mem_addr;
extern vector<question_disk_data*>  qdd_list;
void merge_disk_data_into_questions();

int check_if_reg_file_exists(string jno, int ser_no);
map<string, vector<string> > map_of_active_vars_for_questions;
vector <int8_t> vector_int8_t;
vector <int16_t> vector_int16_t;
vector <int32_t> vector_int32_t;
vector <float> vector_float_t;
vector <double> vector_double_t;
bool back_jump=false;// no need for this but state the intent
int main(){
vector <stub_pair> age;

age.push_back( stub_pair("15 to 21", 1));
age.push_back( stub_pair("22 to 30", 2));
age.push_back( stub_pair("31 to 40", 3));
age.push_back( stub_pair("41 to 59", 4));
xtcc_set xs_0;
xs_0.indiv.insert(1);
xs_0.indiv.insert(2);
xs_0.indiv.insert(3);
xs_0.indiv.insert(4);
range_question * q1 = new range_question(QUESTION_TYPE, 6,string( "q1"),string(" Q1. This is question 1"),spn,0,INT32_TYPE,xs_0);
question_list.push_back(q1);
xtcc_set xs_1;
xs_1.indiv.insert(1);
xs_1.indiv.insert(2);
xs_1.range.push_back(pair<int,int>(5,8));
range_question * q2 = new range_question(QUESTION_TYPE, 13,string( "q2"),string(" Q2. This is question 2"),mpn,5,INT32_TYPE,xs_1);
question_list.push_back(q2);
xtcc_set xs_2;
xs_2.indiv.insert(99);
xs_2.range.push_back(pair<int,int>(1,15));
range_question * q4 = new range_question(QUESTION_TYPE, 34,string( "q4"),string(" q4"),mpn,5,INT32_TYPE,xs_2);
question_list.push_back(q4);
xtcc_set xs_3;
xs_3.indiv.insert(99);
xs_3.range.push_back(pair<int,int>(1,15));
range_question * q7 = new range_question(QUESTION_TYPE, 35,string( "q7"),string(" q7"),mpn,5,INT32_TYPE,xs_3);
question_list.push_back(q7);

	int ser_no;
	cout << "Enter Serial No (0) to exit: " << flush;
	cin >> ser_no;
	string jno="j_1001";
	while(ser_no!=0){
	int exists=check_if_reg_file_exists(jno, ser_no);
	if(exists){
		load_data(jno,ser_no);
		merge_disk_data_into_questions();
		for(unsigned int i=0; i< qdd_list.size(); ++i){
			cout << qdd_list[i]->qno << endl;
			cout  << ":" << qdd_list[i]->data.size() << endl;
			for(int j=0; j<qdd_list[i]->data.size(); ++j){
				cout << qdd_list[i]->data[j] << " ";
			}
			cout << endl;
		}
	}

{
lab_q1:
if ( back_jump==true ) {
}
		q1->eval();
 // decl_stmt::generate_code 
int8_t var1=5*12;
 // decl_stmt::generate_code 
int8_t var2=7*var1;
 // decl_stmt::generate_code 
int32_t my_32int=600*700;
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
		bool contains_subset(set<int> & set_data){
			bool val_exists = false;
			for(	set<int>::iterator it=set_data.begin();
				it!=set_data.end(); ++it){
					val_exists=exists(*it);
				if(!val_exists){
					return false;
				}
			}
			if(!val_exists){
				return false;
			}
		}
	} temp_1;
bool temp_2 = temp_1.contains_subset(q1->input_data);
if (temp_2 ){
int32_t temp_3=5;
if ( q1->is_valid(temp_3)) {
q1->input_data.clear();
q1->input_data.insert(temp_3) ; 
} else {cerr << "runtime error - value assigned to question: " << "q1" << " is not in allowed range: " <<temp_3 << endl; 
}
;
lab_q2:
// QUESTION_TYPE - will think of this later 

vector_int32_t.push_back(my_32int);

vector_int8_t.push_back(var1);

vector_int8_t.push_back(var2);

if ( back_jump==true ) {
var2=vector_int8_t.back();
vector_int8_t.pop_back();

var1=vector_int8_t.back();
vector_int8_t.pop_back();

my_32int=vector_int32_t.back();
vector_int32_t.pop_back();

// QUESTION_TYPE - will think of this later 

}
		q2->eval();
}
 // decl_stmt::generate_code 
int32_t i=0;
 // decl_stmt::generate_code 
int32_t j=0;
 // decl_stmt::generate_code 
int32_t k=0;
 // decl_stmt::generate_code 
int32_t var=10;
lab_q4:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

vector_int32_t.push_back(i);

vector_int32_t.push_back(j);

vector_int32_t.push_back(k);

vector_int32_t.push_back(my_32int);

vector_int32_t.push_back(var);

vector_int8_t.push_back(var1);

vector_int8_t.push_back(var2);

if ( back_jump==true ) {
var2=vector_int8_t.back();
vector_int8_t.pop_back();

var1=vector_int8_t.back();
vector_int8_t.pop_back();

var=vector_int32_t.back();
vector_int32_t.pop_back();

my_32int=vector_int32_t.back();
vector_int32_t.pop_back();

k=vector_int32_t.back();
vector_int32_t.pop_back();

j=vector_int32_t.back();
vector_int32_t.pop_back();

i=vector_int32_t.back();
vector_int32_t.pop_back();

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q4->eval();
lab_q7:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

vector_int32_t.push_back(i);

vector_int32_t.push_back(j);

vector_int32_t.push_back(k);

vector_int32_t.push_back(my_32int);

vector_int32_t.push_back(var);

vector_int8_t.push_back(var1);

vector_int8_t.push_back(var2);

if ( back_jump==true ) {
var2=vector_int8_t.back();
vector_int8_t.pop_back();

var1=vector_int8_t.back();
vector_int8_t.pop_back();

var=vector_int32_t.back();
vector_int32_t.pop_back();

my_32int=vector_int32_t.back();
vector_int32_t.pop_back();

k=vector_int32_t.back();
vector_int32_t.pop_back();

j=vector_int32_t.back();
vector_int32_t.pop_back();

i=vector_int32_t.back();
vector_int32_t.pop_back();

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q7->eval();
}

			stringstream fname_str;
			fname_str << jno << "_" << ser_no << ".dat";
			FILE * fptr = fopen(fname_str.str().c_str(), "w+b");
	for (int i=0; i<question_list.size(); ++i){
		fprintf(fptr, "%s: ", question_list[i]->name.c_str());
		for( set<int>::iterator iter=question_list[i]->input_data.begin();
				iter!=question_list[i]->input_data.end(); ++iter){
			fprintf(fptr, "%d ", *iter);
		}
		fprintf(fptr, "\n");
		question_list[i]->input_data.clear();
	}
	fclose(fptr);

	cout << "Enter Serial No (0) to exit: " << flush;
	cin >> ser_no;

	} /* close while */

} /* close main */
