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
#include "user_navigation.h"
#include "debug_mem.h"
fstream debug_log_file("xtcc_debug.log", ios_base::out|ios_base::trunc);
using namespace std;
void read_data(const char * prompt);
extern vector<int> data;
extern UserNavigation user_navigation;
vector <AbstractQuestion*> question_list;
vector<mem_addr_tab>  mem_addr;
extern vector<question_disk_data*>  qdd_list;
void merge_disk_data_into_questions();
bool stopAtNextQuestion;
string jumpToQuestion;

int check_if_reg_file_exists(string jno, int ser_no);
map<string, vector<string> > map_of_active_vars_for_questions;
vector <int8_t> vector_int8_t;
vector <int16_t> vector_int16_t;
vector <int32_t> vector_int32_t;
vector <float> vector_float_t;
vector <double> vector_double_t;
bool back_jump=false;// no need for this but state the intent
void write_data_to_disk(const vector<AbstractQuestion*>& q_vec, string jno, int ser_no);
AbstractQuestion * ComputePreviousQuestion(AbstractQuestion * q);
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
vector <int8_t> q1_stack_int8_t;
vector <int16_t> q1_stack_int16_t;
vector <int32_t> q1_stack_int32_t;
vector <float> q1_stack_float_t;
vector <double> q1_stack_double_t;
XtccSet xs_0;
xs_0.indiv.insert(1);
xs_0.indiv.insert(2);
xs_0.indiv.insert(3);
xs_0.indiv.insert(4);
RangeQuestion * q1 = new RangeQuestion(QUESTION_TYPE, 4,string( "q1"),string(" Q1"),spn,0,INT32_TYPE,xs_0/* 0*/);
question_list.push_back(q1);
vector <int8_t> q2_stack_int8_t;
vector <int16_t> q2_stack_int16_t;
vector <int32_t> q2_stack_int32_t;
vector <float> q2_stack_float_t;
vector <double> q2_stack_double_t;
XtccSet xs_1;
xs_1.indiv.insert(1);
xs_1.indiv.insert(2);
xs_1.indiv.insert(3);
xs_1.indiv.insert(4);
RangeQuestion * q2 = new RangeQuestion(QUESTION_TYPE, 11,string( "q2"),string(" Q2"),spn,0,INT32_TYPE,xs_1/* 0*/);
question_list.push_back(q2);
vector <int8_t> q3_stack_int8_t;
vector <int16_t> q3_stack_int16_t;
vector <int32_t> q3_stack_int32_t;
vector <float> q3_stack_float_t;
vector <double> q3_stack_double_t;
XtccSet xs_2;
xs_2.indiv.insert(5);
xs_2.indiv.insert(6);
RangeQuestion * q3 = new RangeQuestion(QUESTION_TYPE, 13,string( "q3"),string(" Q3"),spn,0,INT32_TYPE,xs_2/* 0*/);
question_list.push_back(q3);

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

	start_of_questions:
{
 // DeclarationStatement::GenerateCode 
int32_t i1=1;
 // DeclarationStatement::GenerateCode 
int32_t i2=2;
lab_q1:
if ( back_jump==true ) {
i2=q1_stack_int32_t.back();
q1_stack_int32_t.pop_back();

i1=q1_stack_int32_t.back();
q1_stack_int32_t.pop_back();

}
q1_stack_int32_t.push_back(i1);

q1_stack_int32_t.push_back(i2);

if (!q1->isAnswered_ ||
stopAtNextQuestion ||
jumpToQuestion == "q1" ){ 
label_eval_q1:
		q1->eval();
if (user_navigation==NAVIGATE_PREVIOUS){
			AbstractQuestion * target_question = ComputePreviousQuestion(q1);
			if(target_question==0)
			goto label_eval_q1;
			else {
			jumpToQuestion = target_question->questionName_;
			user_navigation=NOT_SET;
			goto start_of_questions;
}
}
else if (user_navigation==NAVIGATE_NEXT){
			jumpToQuestion = "q4";
			user_navigation=NOT_SET;
			goto start_of_questions;
}
}
	struct temp_0{
		const int size_ran_indiv;
		const int size_start_end;
		vector<int> ran_indiv;
		vector< pair<int,int> > ran_start_end;
		temp_0(): size_ran_indiv(1), size_start_end(0),
			ran_indiv(size_ran_indiv), ran_start_end(size_start_end){
			ran_indiv[0]=1;
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
	} temp_1;
bool temp_2 = temp_1.contains_subset(q1->input_data);
if (temp_2 ) {{
i1  = 10;
}
// ifStatementStack.size(): 0
 }
 else {
{
i1  = 20;
}
// end of ifBody_->GetQuestionNames 
 // elseIfStatement DOES NOT exists 
/* question_list_if_body.size(): 0 */ 
// **************** 
}
 /* finished generating code IfStatement */ 
lab_q2:
if ( back_jump==true ) {
i2=q2_stack_int32_t.back();
q2_stack_int32_t.pop_back();

i1=q2_stack_int32_t.back();
q2_stack_int32_t.pop_back();

// QUESTION_TYPE - will think of this later 

}
// QUESTION_TYPE - will think of this later 

q2_stack_int32_t.push_back(i1);

q2_stack_int32_t.push_back(i2);

if (!q2->isAnswered_ ||
stopAtNextQuestion ||
jumpToQuestion == "q2" ){ 
label_eval_q2:
		q2->eval();
if (user_navigation==NAVIGATE_PREVIOUS){
			AbstractQuestion * target_question = ComputePreviousQuestion(q2);
			if(target_question==0)
			goto label_eval_q2;
			else {
			jumpToQuestion = target_question->questionName_;
			user_navigation=NOT_SET;
			goto start_of_questions;
}
}
else if (user_navigation==NAVIGATE_NEXT){
			jumpToQuestion = "q4";
			user_navigation=NOT_SET;
			goto start_of_questions;
}
}
lab_q3:
if ( back_jump==true ) {
i2=q3_stack_int32_t.back();
q3_stack_int32_t.pop_back();

i1=q3_stack_int32_t.back();
q3_stack_int32_t.pop_back();

// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

}
// QUESTION_TYPE - will think of this later 

// QUESTION_TYPE - will think of this later 

q3_stack_int32_t.push_back(i1);

q3_stack_int32_t.push_back(i2);

if (!q3->isAnswered_ ||
stopAtNextQuestion ||
jumpToQuestion == "q3" ){ 
label_eval_q3:
		q3->eval();
if (user_navigation==NAVIGATE_PREVIOUS){
			AbstractQuestion * target_question = ComputePreviousQuestion(q3);
			if(target_question==0)
			goto label_eval_q3;
			else {
			jumpToQuestion = target_question->questionName_;
			user_navigation=NOT_SET;
			goto start_of_questions;
}
}
else if (user_navigation==NAVIGATE_NEXT){
			jumpToQuestion = "q4";
			user_navigation=NOT_SET;
			goto start_of_questions;
}
}
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


// The first question before this question that is answered
AbstractQuestion * ComputePreviousQuestion(AbstractQuestion * q)
{
	int current_question_index=-1;
	for(int i=0; i<question_list.size(); ++i){
		if(question_list[i]==q){
			current_question_index=i;
			break;
		}
	}
	if(current_question_index==-1){
		cerr << "internal compiler error at runtime ... filename: " 
			<< __FILE__ 
			<< "line no: " << __LINE__
			<< endl;
	}
	for(int i=current_question_index-1; i>=0; --i){
		if(question_list[i]->isAnswered_){
			return question_list[i];
		}
	}
	return 0;
}
