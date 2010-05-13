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
vector <AbstractQuestion*> question_list;
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
void write_data_to_disk(const vector<AbstractQuestion*>& q_vec, string jno, int ser_no);
class ArrayQuestion
{
public: 
	vector<AbstractQuestion*> questionList;
	vector<int> arrayBounds;
	ArrayQuestion(vector<int>& l_arrayBounds): arrayBounds(l_arrayBounds)
	{
		int bounds = 1;
		for(int i=0; i<arrayBounds.size(); ++i){
			bounds*=arrayBounds[i];
		}
		questionList.reserve(bounds);
	}
};

int main(){
XtccSet xs_0;
xs_0.indiv.insert(1);
xs_0.indiv.insert(2);
xs_0.indiv.insert(3);
xs_0.indiv.insert(4);
RangeQuestion * q1 = new RangeQuestion(QUESTION_TYPE, 4,string( "q1"),string(" Q1. "),spn,0,INT32_TYPE,xs_0/* 0*/);
question_list.push_back(q1);
XtccSet xs_1;
xs_1.indiv.insert(5);
xs_1.indiv.insert(6);
RangeQuestion * q2 = new RangeQuestion(QUESTION_TYPE, 7,string( "q2"),string(" Q2. "),spn,0,INT32_TYPE,xs_1/* 0*/);
question_list.push_back(q2);
XtccSet xs_2;
xs_2.indiv.insert(5);
xs_2.indiv.insert(6);
RangeQuestion * q3 = new RangeQuestion(QUESTION_TYPE, 9,string( "q3"),string(" Q3. "),spn,0,INT32_TYPE,xs_2/* 0*/);
question_list.push_back(q3);
XtccSet xs_3;
xs_3.indiv.insert(1);
xs_3.indiv.insert(2);
xs_3.indiv.insert(3);
xs_3.indiv.insert(4);
RangeQuestion * q4 = new RangeQuestion(QUESTION_TYPE, 11,string( "q4"),string(" Q4. "),spn,0,INT32_TYPE,xs_3/* 0*/);
question_list.push_back(q4);
XtccSet xs_4;
xs_4.indiv.insert(7);
xs_4.indiv.insert(8);
RangeQuestion * q5 = new RangeQuestion(QUESTION_TYPE, 13,string( "q5"),string(" Q5. "),spn,0,INT32_TYPE,xs_4/* 0*/);
question_list.push_back(q5);
XtccSet xs_5;
xs_5.indiv.insert(7);
xs_5.indiv.insert(8);
RangeQuestion * q6 = new RangeQuestion(QUESTION_TYPE, 14,string( "q6"),string(" Q6. "),spn,0,INT32_TYPE,xs_5/* 0*/);
question_list.push_back(q6);
XtccSet xs_6;
xs_6.indiv.insert(9);
xs_6.indiv.insert(10);
RangeQuestion * q5_1 = new RangeQuestion(QUESTION_TYPE, 16,string( "q5_1"),string(" Q5_1 "),spn,0,INT32_TYPE,xs_6/* 0*/);
question_list.push_back(q5_1);
XtccSet xs_7;
xs_7.indiv.insert(11);
xs_7.indiv.insert(12);
RangeQuestion * q5_2 = new RangeQuestion(QUESTION_TYPE, 17,string( "q5_2"),string(" Q5_2 "),spn,0,INT32_TYPE,xs_7/* 0*/);
question_list.push_back(q5_2);
XtccSet xs_8;
xs_8.indiv.insert(13);
xs_8.indiv.insert(14);
RangeQuestion * q5_3 = new RangeQuestion(QUESTION_TYPE, 19,string( "q5_3"),string(" Q5_3 "),spn,0,INT32_TYPE,xs_8/* 0*/);
question_list.push_back(q5_3);
XtccSet xs_9;
xs_9.indiv.insert(15);
xs_9.indiv.insert(16);
RangeQuestion * q5_4 = new RangeQuestion(QUESTION_TYPE, 20,string( "q5_4"),string(" Q5_4 "),spn,0,INT32_TYPE,xs_9/* 0*/);
question_list.push_back(q5_4);
XtccSet xs_10;
xs_10.indiv.insert(7);
xs_10.indiv.insert(8);
RangeQuestion * q7 = new RangeQuestion(QUESTION_TYPE, 23,string( "q7"),string(" Q7. "),spn,0,INT32_TYPE,xs_10/* 0*/);
question_list.push_back(q7);
XtccSet xs_11;
xs_11.indiv.insert(7);
xs_11.indiv.insert(8);
RangeQuestion * q8 = new RangeQuestion(QUESTION_TYPE, 24,string( "q8"),string(" Q8. "),spn,0,INT32_TYPE,xs_11/* 0*/);
question_list.push_back(q8);
XtccSet xs_12;
xs_12.indiv.insert(7);
xs_12.indiv.insert(8);
RangeQuestion * q9 = new RangeQuestion(QUESTION_TYPE, 26,string( "q9"),string(" Q9. "),spn,0,INT32_TYPE,xs_12/* 0*/);
question_list.push_back(q9);
XtccSet xs_13;
xs_13.indiv.insert(7);
xs_13.indiv.insert(8);
RangeQuestion * q10 = new RangeQuestion(QUESTION_TYPE, 27,string( "q10"),string(" Q10. "),spn,0,INT32_TYPE,xs_13/* 0*/);
question_list.push_back(q10);
XtccSet xs_14;
xs_14.indiv.insert(1);
xs_14.indiv.insert(3);
RangeQuestion * q11 = new RangeQuestion(QUESTION_TYPE, 29,string( "q11"),string(" Q11 "),spn,0,INT32_TYPE,xs_14/* 0*/);
question_list.push_back(q11);

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
<<<<<<< .mine
			/*if(!val_exists){
				return false;
			}*/
		return true;
=======
			return true;
>>>>>>> .r197
		}
	} temp_1;
bool temp_2 = temp_1.contains_subset(q1->input_data);
if (temp_2 ) {lab_q2:
// QUESTION_TYPE - will think of this later 

if ( back_jump==true ) {
// QUESTION_TYPE - will think of this later 

}
		q2->eval();
// ifStatementStack.size(): 0
// q3
 }
 else {
lab_q3:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

if ( back_jump==true ) {
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q3->eval();
// end of ifBody_->GetQuestionNames 
 // elseIfStatement DOES NOT exists 
/* question_list_if_body.size(): 1 */ 
// q2
// **************** 
}
 /* finished generating code IfStatement */ 
lab_q4:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

if ( back_jump==true ) {
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q4->eval();
	struct temp_3{
		const int size_ran_indiv;
		const int size_start_end;
		vector<int> ran_indiv;
		vector< pair<int,int> > ran_start_end;
		temp_3(): size_ran_indiv(2), size_start_end(0),
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
			/*if(!val_exists){
				return false;
			}*/
		return true;
		}
	} temp_4;
bool temp_5 = temp_4.contains_subset(q4->input_data);
if (temp_5 ) {{
lab_q5:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

if ( back_jump==true ) {
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q5->eval();
lab_q6:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

if ( back_jump==true ) {
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q6->eval();
	struct temp_6{
		const int size_ran_indiv;
		const int size_start_end;
		vector<int> ran_indiv;
		vector< pair<int,int> > ran_start_end;
		temp_6(): size_ran_indiv(1), size_start_end(0),
			ran_indiv(size_ran_indiv), ran_start_end(size_start_end){
			ran_indiv[0]=7;
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
			/*if(!val_exists){
				return false;
			}*/
		return true;
		}
	} temp_7;
bool temp_8 = temp_7.contains_subset(q5->input_data);
if (temp_8 ) {{
lab_q5_1:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

if ( back_jump==true ) {
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q5_1->eval();
lab_q5_2:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

if ( back_jump==true ) {
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q5_2->eval();
}
// ifStatementStack.size(): 0
// q5_3
// q5_4
 }
 else {
// pushing onto ifStatementStack 
// if statement at same level of nesting as previous if i.e. part of the else if clause: if_nest_level: 2
	struct temp_9{
		const int size_ran_indiv;
		const int size_start_end;
		vector<int> ran_indiv;
		vector< pair<int,int> > ran_start_end;
		temp_9(): size_ran_indiv(1), size_start_end(0),
			ran_indiv(size_ran_indiv), ran_start_end(size_start_end){
			ran_indiv[0]=8;
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
			/*if(!val_exists){
				return false;
			}*/
		return true;
		}
	} temp_10;
bool temp_11 = temp_10.contains_subset(q5->input_data);
if (temp_11 ) {{
lab_q5_3:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

if ( back_jump==true ) {
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q5_3->eval();
lab_q5_4:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

if ( back_jump==true ) {
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q5_4->eval();
}
// ifStatementStack.size(): 1
// q5_1
// q5_2
 }
 /* finished generating code IfStatement */ 
// end of ifBody_->GetQuestionNames 
 // elseIfStatement exists 
}
 /* finished generating code IfStatement */ 
}
// ifStatementStack.size(): 0
// q7
// q8
// q9
// q10
// q11
 }
 else {
// pushing onto ifStatementStack 
// if statement at same level of nesting as previous if i.e. part of the else if clause: if_nest_level: 1
	struct temp_12{
		const int size_ran_indiv;
		const int size_start_end;
		vector<int> ran_indiv;
		vector< pair<int,int> > ran_start_end;
		temp_12(): size_ran_indiv(1), size_start_end(0),
			ran_indiv(size_ran_indiv), ran_start_end(size_start_end){
			ran_indiv[0]=3;
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
			/*if(!val_exists){
				return false;
			}*/
		return true;
		}
	} temp_13;
bool temp_14 = temp_13.contains_subset(q4->input_data);
if (temp_14 ) {{
lab_q7:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

if ( back_jump==true ) {
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q7->eval();
lab_q8:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

if ( back_jump==true ) {
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q8->eval();
}
// ifStatementStack.size(): 1
// q5
// q6
// q5_1
// q5_2
// q5_3
// q5_4
// q9
// q10
// q11
 }
 else {
// pushing onto ifStatementStack 
// if statement at same level of nesting as previous if i.e. part of the else if clause: if_nest_level: 1
	struct temp_15{
		const int size_ran_indiv;
		const int size_start_end;
		vector<int> ran_indiv;
		vector< pair<int,int> > ran_start_end;
		temp_15(): size_ran_indiv(1), size_start_end(0),
			ran_indiv(size_ran_indiv), ran_start_end(size_start_end){
			ran_indiv[0]=4;
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
			/*if(!val_exists){
				return false;
			}*/
		return true;
		}
	} temp_16;
bool temp_17 = temp_16.contains_subset(q4->input_data);
if (temp_17 ) {{
lab_q9:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

if ( back_jump==true ) {
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q9->eval();
lab_q10:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

if ( back_jump==true ) {
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q10->eval();
}
// ifStatementStack.size(): 2
// q5
// q6
// q5_1
// q5_2
// q5_3
// q5_4
// q7
// q8
// q11
 }
 else {
{
lab_q11:
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

if ( back_jump==true ) {
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
		q11->eval();
}
// end of ifBody_->GetQuestionNames 
 // elseIfStatement DOES NOT exists 
/* question_list_if_body.size(): 10 */ 
// q5
// q6
// q5_1
// q5_2
// q5_3
// q5_4
// q7
// q8
// q9
// q10
// **************** 
}
 /* finished generating code IfStatement */ 
// end of ifBody_->GetQuestionNames 
 // elseIfStatement exists 
}
 /* finished generating code IfStatement */ 
// end of ifBody_->GetQuestionNames 
 // elseIfStatement exists 
}
 /* finished generating code IfStatement */ 
}

		write_data_to_disk(question_list, jno, ser_no);
	cout << "Enter Serial No (0) to exit: " << flush;
	cin >> ser_no;

	} /* close while */

} /* close main */
	void write_data_to_disk(const vector<AbstractQuestion*>& q_vec
		, string jno
		, int ser_no) {
		stringstream fname_str;
		fname_str << jno << "_" << ser_no << ".dat";
		//FILE * fptr = fopen(fname_str.str().c_str(), "w+b");
	
	
		std::ofstream data_file;
		data_file.exceptions(std::ios::failbit | std::ios::badbit);
		data_file.open(fname_str.str().c_str());
	
		for (int i=0; i<question_list.size(); ++i){
			question_list[i]->WriteDataToDisk(data_file);
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


