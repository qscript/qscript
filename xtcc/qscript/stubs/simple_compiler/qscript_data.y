
%{
#include <iostream>
	using namespace std;
#include "const_defs.h"
#include "question_disk_data.h"
#include <vector>

	
	static vector<int> data;
	static vector<int> array_index_list;
	vector <question_disk_data*> qdd_list;
	int read_disk_datalex();
	int no_errors;
	void read_disk_dataerror(const char * s);
%}


%union {
	int ival;
	double dval;
	char name[MY_STR_MAX];
}
%token <name> NAME
%token COLON DOLLAR BOUNDS
%token <ival> INUMBER
%token  NEWL


%%

program: question_list{
	cout << "got question_list: parsed to program: " << endl;
	return no_errors;
	}
	;

question_list: question
	| question_list question
	;

question: NAME COLON numberlist NEWL {
		//cout << "data<int>[]: ";
		for(int i=0; i<data.size(); ++i){
			cout << data[i] << " ";
		}
		cout << "data.capacity(): " << data.capacity() << endl;
		cout <<endl;
		//cout << "got question" << endl;
		string qno($1);
		question_disk_data * qdd = new question_disk_data(qno, data);
		qdd_list.push_back(qdd);
		data.clear();
	}
	| NAME COLON NEWL {
		//cout << "got empty question" << endl;
		string qno($1);
		question_disk_data * qdd = new question_disk_data(qno);
		qdd_list.push_back(qdd);
		data.clear();
	}
	| NAME array_index_list COLON numberlist NEWL {
		string qno($1);
		QuestionExists q_eq(qno);
		vector<question_disk_data*> ::iterator it = find_if(qdd_list.begin(),
				qdd_list.end(), q_eq);
		if(it!=qdd_list.end()){
			question_disk_data * qdd = *it;
			qdd->set_array_data(array_index_list, data);
		} else {
			//question_disk_data * qdd = new question_disk_data(qno, array_index_list, data);
			//qdd_list.push_back(qdd);
			cout << "Array question found but bounds not set in data file - this is an error in the data file" 
				<< endl;
		}
		array_index_list.clear();
		data.clear();
		cout << " Got array question: " << qno << endl;
	}
	| NAME BOUNDS numberlist NEWL{
		string qno($1);
		question_disk_data * qdd = new question_disk_data(qno, data, data);
		qdd_list.push_back(qdd);
		data.clear();
		cout << " Got bounds for: " << qno << endl;
	}
	;

numberlist: INUMBER {
		    data.push_back($1);
	}
	|	numberlist INUMBER {
		    data.push_back($2);
	}
	;

array_index_list: DOLLAR INUMBER {
		array_index_list.push_back($2);
	}
	| array_index_list DOLLAR INUMBER {
		array_index_list.push_back($3);
	}
	;

%%

/*
int main(){
	data.reserve(50);
	qdd_list.reserve(100);
	if(!read_disk_dataparse()&& !no_errors){
		for(int i=0; i< qdd_list.size(); ++i){
			cout << qdd_list[i]->qno << endl;
			cout  << ":" << qdd_list[i]->data.size() << endl;
			for(int j=0; j<qdd_list[i]->data.size(); ++j){
				cout << qdd_list[i]->data[j] << " ";
			}
			cout << endl;
		}
	}  else {
		cout << "errors in parse: " << no_errors;
		return 1;
	}
}
*/

void read_disk_data_init(){
	data.reserve(50);
	qdd_list.reserve(100);
}
