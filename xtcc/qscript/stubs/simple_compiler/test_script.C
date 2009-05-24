#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <cstdlib>
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
void write_data_to_disk(const vector<question*>& q_vec, string jno, int ser_no);
int main(){
vector <stub_pair> age;

age.push_back( stub_pair("15 to 21", 1));
age.push_back( stub_pair("22 to 30", 2));
age.push_back( stub_pair("31 to 40", 3));
age.push_back( stub_pair("41 to 59", 4));
vector <stub_pair> csd_brand_list;

csd_brand_list.push_back( stub_pair("Goqe", 1));
csd_brand_list.push_back( stub_pair("Bebzi", 2));
csd_brand_list.push_back( stub_pair("Oogla", 3));
csd_brand_list.push_back( stub_pair("Zingmoo", 4));
csd_brand_list.push_back( stub_pair("Thunder", 5));
csd_brand_list.push_back( stub_pair("Zoinks", 6));
xtcc_set xs_0;
xs_0.indiv.insert(1);
xs_0.indiv.insert(2);
xs_0.indiv.insert(3);
xs_0.indiv.insert(4);
range_question * q1 = new range_question(QUESTION_TYPE, 16,string( "q1"),string(" Q1. This is question 1"),spn,0,INT32_TYPE,xs_0/* 0*/);
question_list.push_back(q1);
xtcc_set xs_1;
xs_1.indiv.insert(1);
xs_1.indiv.insert(2);
xs_1.range.push_back(pair<int,int>(5,8));
range_question * q2 = new range_question(QUESTION_TYPE, 23,string( "q2"),string(" Q2. This is question 2"),mpn,5,INT32_TYPE,xs_1/* 0*/);
question_list.push_back(q2);
// named_stub_question::generate_code() : to be implemented
named_stub_question * q3 = new named_stub_question(QUESTION_TYPE, 24,string( "q3"),string(" Q3. Respondents age"),spn,5,INT32_TYPE,&age/* 0*/);
question_list.push_back(q3);
// named_stub_question::generate_code() : to be implemented
named_stub_question * q4 = new named_stub_question(QUESTION_TYPE, 29,string( "q4"),string(" Q4. When you think of Soft Drinks and CSDs in particular, which CSD's come to mind first?"),spn,5,INT32_TYPE,&csd_brand_list/* 0*/);
question_list.push_back(q4);
// named_stub_question::generate_code() : to be implemented
named_stub_question * q4_2 = new named_stub_question(QUESTION_TYPE, 33,string( "q4_2"),string(" Q4.2 Which other brands come to mind ?"),spn,5,INT32_TYPE,&csd_brand_list/* 0*/);
question_list.push_back(q4_2);
vector <question*> q17_list;
for(int i=0;i<2; ++i){
vector<int> stack_of_loop_indices; 
stack_of_loop_indices.push_back(i);
for(int j=0;j<3; ++j){
stack_of_loop_indices.push_back(j);
for(int k=0;k<4; ++k){
stack_of_loop_indices.push_back(k);
// named_stub_question::generate_code() : to be implemented
named_stub_question * q17 = new named_stub_question(QUESTION_TYPE, 46,string( "q17"),string(" Q17. Respondents age"),spn,5,INT32_TYPE,&age, stack_of_loop_indices /* 3*/);
question_list.push_back(q17);
q17_list.push_back(q17);
stack_of_loop_indices.pop_back();
}
stack_of_loop_indices.pop_back();
}
stack_of_loop_indices.pop_back();
}
vector <question*> q15_list;
for(int i=0;i<5; ++i){
vector<int> stack_of_loop_indices;
stack_of_loop_indices.push_back(i);
xtcc_set xs_2;
xs_2.indiv.insert(99);
xs_2.range.push_back(pair<int,int>(1,15));
range_question * q15 = new range_question(QUESTION_TYPE, 52,string( "q15"),string(" q15"),mpn,5,INT32_TYPE,xs_2, stack_of_loop_indices /* 1*/);
question_list.push_back(q15);
q15_list.push_back(q15);
stack_of_loop_indices.pop_back();
}

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
lab_q3:
// QUESTION_TYPE - will think of this later 

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

// QUESTION_TYPE - will think of this later 

}
		q3->eval();
}
lab_q4:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

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

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q4->eval();
/*stub_manip::generate_code()q4:csd_brand_list*/
{
set<int>::iterator set_iter = q4->input_data.begin();
for( ; set_iter!= q4->input_data.end(); ++set_iter){
for(int i=0; i< csd_brand_list.size(); ++i){
if(csd_brand_list[i].code==*set_iter ) {
csd_brand_list[i].mask=false; 
}
}

}
for(int i=0; i< csd_brand_list.size(); ++i){
cout << csd_brand_list[i].stub_text << ":" <<
csd_brand_list[i].mask << ":" <<
csd_brand_list[i].code  << endl;

}
}
lab_q4_2:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

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

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q4_2->eval();
/*stub_manip::generate_code()q4_2:csd_brand_list*/
{
set<int>::iterator set_iter = q4_2->input_data.begin();
for( ; set_iter!= q4_2->input_data.end(); ++set_iter){
for(int i=0; i< csd_brand_list.size(); ++i){
if(csd_brand_list[i].code==*set_iter ) {
csd_brand_list[i].mask=false; 
}
}

}
for(int i=0; i< csd_brand_list.size(); ++i){
cout << csd_brand_list[i].stub_text << ":" <<
csd_brand_list[i].mask << ":" <<
csd_brand_list[i].code  << endl;

}
}
 // decl_stmt::generate_code 
int32_t i=0;
 // decl_stmt::generate_code 
int32_t j=0;
 // decl_stmt::generate_code 
int32_t k=0;
 // decl_stmt::generate_code 
int32_t var=10;
for (i  = 0;i<2;i  = i+1){
for (j  = 0;j<3;j  = j+1){
for (k  = 0;k<4;k  = k+1){
lab_q17:
// QUESTION_TYPE - will think of this later 

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

// QUESTION_TYPE - will think of this later 

}
		q17_list[i*3*4+j*4+k]->eval();
}
}
}
for (i  = 0;i<5;i  = i+1){
lab_q15:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

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

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q15_list[i]->eval();
}
}

		write_data_to_disk(question_list, jno, ser_no);
	cout << "Enter Serial No (0) to exit: " << flush;
	cin >> ser_no;

	} /* close while */

} /* close main */
	void write_data_to_disk(const vector<question*>& q_vec
		, string jno
		, int ser_no) {
		stringstream fname_str;
		fname_str << jno << "_" << ser_no << ".dat";
		//FILE * fptr = fopen(fname_str.str().c_str(), "w+b");
	
	
		std::ofstream data_file;
		data_file.exceptions(std::ios::failbit | std::ios::badbit);
		data_file.open(fname_str.str().c_str());
	
		for (int i=0; i<question_list.size(); ++i){
			question_list[i]->write_data_to_disk(data_file);
			/*
			fprintf(fptr, "%s: ", question_list[i]->name.c_str());
			for( set<int>::iterator iter=question_list[i]->input_data.begin();
					iter!=question_list[i]->input_data.end(); ++iter){
				fprintf(fptr, "%d ", *iter);
			}
			fprintf(fptr, "
");
			question_list[i]->input_data.clear();
			*/
		}
		//fclose(fptr);
	}


