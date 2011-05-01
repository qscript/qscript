%{
#include <vector>
#include <iostream>
	
#include "AbstractStatement.h"
#include "named_range.h"
#include "const_defs.h"

	using std::vector;
	using std::endl;
	using std::cout;
	using std::cerr;

        vector <stub_pair> stub_list;
	vector <named_range*> named_stubs_list;
	int32_t line_no = 1;
	int32_t no_errors = 0;
	void yyerror(const char * s);
	int32_t yylex();
%}


%union {
	//type_qualifier type_qual;
	int32_t ival;
	//double dval;
	char name[MY_STR_MAX];
	char text_buf[MY_STR_MAX];
	//DataType dt;
	struct AbstractStatement * stmt;
}


%token STUBS_LIST
%token RANDOMIZE
%token MUTEX
%token STUB_GROUP
%token <name> NAME
%token <ival> INUMBER
%token <text_buf> TEXT

%type <stmt> stubs
%type <stmt> stmt
%type <stmt> stmt_list
%type <stmt> randomize_stub_statement

%%

stmt_list: stmt {
		$$=$1;
	}
	| stmt_list stmt{
		$1->next_=$2;
		$2->prev_=$1;
		$$=$2;
	}
	;

stmt: 		stubs
	| randomize_stub_statement ';'
	;

stubs:	STUBS_LIST NAME {
		stub_list.resize(0);
	} '=' stub_list ';' {
		string stub_name=$2;
		struct named_range* nr_ptr= new named_range(NAMED_RANGE
				, line_no, stub_name,stub_list);
		named_stubs_list.push_back(nr_ptr);
		$$ = nr_ptr;
	}
	;


stub_list: stub
	| stub_list stub
	;

stub:	TEXT INUMBER {
		string s1=$1;
		int32_t code=$2;
		struct stub_pair pair1(s1,code);
		stub_list.push_back(pair1);
	}
	| TEXT INUMBER MUTEX {
		string s1=$1;
		int32_t code=$2;
		struct stub_pair pair1(s1,code, true);
		stub_list.push_back(pair1);
	}
	| STUB_GROUP NAME '{'
	|	'}'
	;

randomize_stub_statement: RANDOMIZE STUBS_LIST NAME {
		$$ = 0;
	}
	;

%%
#include <cstdio>

void yyrestart(FILE *input_file);
int32_t yyparse();
int main()
{
	FILE * yyin = fopen("random_test.input", "rb");
	if (!yyin){
		cerr << " Unable to open: random_test.input "  << " for read ... exiting" << endl;
		exit(1);
	}
	yyrestart(yyin);
	if (!yyparse() && !no_errors) {
		cout << "sucessfully parsed" << endl;
	}
}
