
%{

#include <inttypes.h>
#include <sys/types.h>
#include <limits.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "const_defs.h"


	extern int yylex();
	extern void yyerror(const char * s);
	using std::cout;
	using std::endl;
	using std::cerr;

%}

%union {
	int ival;
	double dval;
	char name[4095];
	char text_buf[4095];
}

%token STUBS
%token CODE
%token FREQUENCY

%token <ival> INUMBER
%token <dval> FNUMBER
%token <name> NAME
%token <text_buf> TEXT
%token NEWL
%token COMMA
%token DOT


%%

axis_freq_count_list: axis_freq_count {
		cout << "parsed axis_freq_count to axis_freq_count_list"
			<< endl;
	}
	| axis_freq_count_list axis_freq_count {
		cout << "chaining axis_freq_count with axis_freq_count_list"
			<< endl;
	}
	;

axis_freq_count: name stub_header_line stub_frequency_list NEWL {
	       cout << "got an named stub axis_freq_count" << endl;
	}
	| name code_header_line code_freq_list NEWL{
	       cout << "got an range stub axis_freq_count" << endl;
	}
	;

stub_header_line: STUBS COMMA CODE COMMA FREQUENCY NEWL {
	cout << "got stubs_header_line" << endl;
	}

code_header_line: COMMA CODE COMMA FREQUENCY NEWL {
	cout << "got code_header_line" << endl;
	}

name: NAME NEWL {
	cout << "Got NAME: " << $1 << endl;
	}
	| NAME DOT INUMBER NEWL {
	cout << "Got array NAME: " << $1 << endl;
	}

stub_frequency_list: stub_freq
	| stub_frequency_list stub_freq
	;

code_freq_list: code_freq
	| code_freq_list code_freq
	;

stub_freq: TEXT COMMA INUMBER COMMA INUMBER NEWL {
	cout << "Got stub_freq:"  << TEXT << endl;
}

code_freq: COMMA INUMBER COMMA INUMBER NEWL {
	cout	<< "Got code_freq code:"  << $2
		<< ", freq: " << $4
		<< endl;
	 }

%%
	extern void yyrestart(FILE *input_file);
	extern int32_t yyparse();

#include "const_defs.h"
int main()
{
	std::string fname ("cmb_decision_maker.freq_count.csv");
	FILE * yyin = fopen(fname.c_str(), "rb");
	if (!yyin){
		cerr << " Unable to open: " << fname << " for read ... exiting" << endl;
		exit(1);
	}
	yyrestart(yyin);
	if (!yyparse()) {
		cout << "Input parsed successfully" << endl;
	}
	
}
