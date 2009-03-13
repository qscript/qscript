
%{
#include <iostream>
	using namespace std;
#include "const_defs.h"
#include "question_disk_data.h"
#include <vector>

	
	vector<int> data;
	vector <question_disk_data*> qdd_list;
	int yylex();
	int no_errors;
	void yyerror(const char * s);
%}


%union {
	int ival;
	double dval;
	char name[MY_STR_MAX];
}
%token <name> NAME
%token COLON
%token <ival> INUMBER
%token  NEWL


%%

program: question_list{
	return no_errors;
	}

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
	;

numberlist: INUMBER {
		    data.push_back($1);
	}
	|	numberlist INUMBER {
		    data.push_back($2);
	}
	;


%%

int main(){
	data.reserve(50);
	qdd_list.reserve(100);
	if(!yyparse()&& !no_errors){
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
