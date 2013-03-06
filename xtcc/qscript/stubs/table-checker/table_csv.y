
%{

#include <inttypes.h>
#include <sys/types.h>
#include <limits.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>
#include "const_defs.h"


	extern int yylex();
	extern void yyerror(const char * s);
	using std::cout;
	using std::endl;
	using std::cerr;
	using std::stringstream;
	using std::map;
	using std::string;
	// these are the global accumulators
	// yes bad bad global variables
	map<string, map <string, int> > freq_count_map_nq_name_stub_freq;
	map<string, map <int, int> > freq_count_map_nq_name_code_freq;
	map<string, map <string, int> > freq_count_map_nq_name_stub_code;
	map<string, map <int, int> > freq_count_map_rq;
	// these are used while building up the list
	//       this is for named stub questions
	map<string, int> temp_freq_count_map_nq_stub_codefreq;
	map<int, int>    temp_freq_count_map_nq_code_codefreq;
	map<string, int>    temp_freq_count_map_nq_stub_code;
	//       this is for range questions
	map<int, int> temp_freq_count_map_rq; // will always be code -> freq
	string axis_name;
	bool nq_axis;

%}

%union {
	int ival;
	double dval;
	char name[4095];
	char text_buf[4095];
}


%token TABLE
%token PAGE
%token TOTAL
%token SIGMA
%token MEAN
%token <text_buf> STUB_FREQ
%token <text_buf> STUB_PERC
%token <ival> INUMBER
%token <dval> FNUMBER
%token <name> NAME
%token <text_buf> TEXT
%token NEWL
%token COMMA
%token DOT


%%

axis_freq_count_list: axis_freq_count {
		//cout << "parsed axis_freq_count to axis_freq_count_list"
		//	<< endl;
	}
	| axis_freq_count_list axis_freq_count {
		//cout << "chaining axis_freq_count with axis_freq_count_list"
		//	<< endl;
	}
	;

axis_freq_count: PAGE NEWL TABLE NEWL TEXT NEWL NAME NEWL text_chain freq_chain {
		cout << "got axis_freq_count" << endl;
	}

text_chain: TEXT NEWL
	  | text_chain TEXT NEWL
	  ;

freq_chain: a_freq
	  | freq_chain a_freq
	  ;

a_freq: 	STUB_FREQ
      	|	STUB_PERC
	;


%%


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

void yyerror(const char * s)
{
	//fprintf(stderr, "reached here: %s\n", __PRETTY_FUNCTION__);
	//using qscript_parser::no_errors;
	//using qscript_parser::line_no;
	//++no_errors;
	printf("%s: line: %d: yytext: %s\n", s, line_no, yytext);
	printf("line: %d: \n", line_no);
	//printf ("lexical error: line: %d, column: %d\n"
	//	, lex_location.lineNo_
	//	, lex_location.columnNo_);
	//printf ("%s\n", lex_location.currentLine_.str().c_str());
	//printf ("%*s\n%*s\ntoken: %s\n", lex_location.columnNo_, "^"
	//		    , lex_location.columnNo_, s, yytext);
}


int yywrap()
{
	return 1;
}
