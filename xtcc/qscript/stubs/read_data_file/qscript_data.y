
%{
#include <iostream>
	using namespace std;
#include "const_defs.h"
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

question_list: question
	| question_list question
	;

question: NAME COLON numberlist NEWL {
	cout << "got question" << endl;
	}
	| NAME COLON NEWL {
	cout << "got empty question" << endl;
	}
	;

numberlist: INUMBER {
	}
	|	numberlist INUMBER
	;


%%

int main(){
	return yyparse();
}
