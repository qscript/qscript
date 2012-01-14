%{
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <sys/types.h>
	
#include "const_defs.h"
#include "AbstractStatement.h"
#include "new_named_range.h"

	using std::vector;
	using std::stringstream;
	using std::string;
	using std::endl;
	using std::cout;
	using std::cerr;

        vector <stub_pair> stub_list;
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
	struct AbstractNamedRange * nr_ptr;
}

%token <name> NAME
%token <ival> INUMBER
%token <text_buf> TEXT

%type <stmt> prog
%type <stmt> stmt
%type <stmt> stmt_list

%type <stmt> randomized_data_order
%type <stmt> randomized_data_list
%type <stmt> randomized_data
%type <stmt> simple_number_list

%%

prog: stmt_list {
		$$ = $1;
	}
	;

stmt_list: stmt {
	 	//$$ = $1;
	}
	| stmt_list stmt {
		//$1->next_=$2;
		//$2->prev_=$1;
		//$$=$2;
	}
	;

stmt: randomized_data_order
	;

randomized_data_order: '{' NAME ':' randomized_data_list '}' {
		     }
		     ;

randomized_data_list: randomized_data
		    | randomized_data_list randomized_data
		    ;


randomized_data:    simple_number_list ';' {
		    }
		    | randomized_data_order   {
		    }
		    ;

simple_number_list: INUMBER {
		  }
		  | simple_number_list INUMBER {
		  }
		  ;


%%

#include <cstdio>
#include <vector>
#include <sys/types.h>

#include "const_defs.h"

void yyrestart(FILE *input_file);
int32_t yyparse();
int main()
{
	FILE * yyin = fopen("randomized_data_output_test.input", "rb");
	if (!yyin) {
		cerr << " Unable to open:  randomized_data_output_test.input"  << " for read ... exiting" << endl;
		exit(1);
	}
	yyrestart(yyin);
	if (!yyparse() && !no_errors) {
		cout << "sucessfully parsed" << endl;
	}
}


