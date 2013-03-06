
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
#include "lex_tab.h"


	//extern int yylex();
	//extern void yyerror(const char * s);
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
	void qtm_table_output_error(const char * s);

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
%token <text_buf> BASE_TEXT
%token <text_buf> STUB_FREQ
%token <text_buf> STUB_PERC
%token <text_buf> STUB_MEAN
%token <text_buf> STUB_STD_DEV
%token <ival> INUMBER
%token <dval> FNUMBER
%token <name> NAME
%token <text_buf> TEXT
%token NEWL
%token COMMA
%token DOT
%token EMPTY_LINE_2_COLS
%token EMPTY_LINE_1_COLS
%token BAN_TOTAL
%token SIDE_TOTAL

%name-prefix "qtm_table_output_"

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

axis_freq_count: PAGE NEWL TABLE NEWL TEXT NEWL NAME NEWL text_chain BASE_TEXT NEWL EMPTY_LINE_2_COLS NEWL EMPTY_LINE_1_COLS NEWL BAN_TOTAL NEWL EMPTY_LINE_1_COLS NEWL SIDE_TOTAL NEWL freq_chain {
		cout << "got axis_freq_count" << endl;
	}

text_chain: TEXT NEWL
	  | text_chain TEXT NEWL
	  ;

freq_chain: a_freq
	  | freq_chain a_freq
	  ;

a_freq: 	STUB_FREQ NEWL
      	|	STUB_PERC NEWL
        |   STUB_MEAN NEWL
        |   STUB_STD_DEV NEWL
	;


%%

	//extern void qtm_table_output_restart(FILE *input_file);
	extern int yyparse();
	void qtm_table_output_error(const char * s);

#include "const_defs.h"
int main()
{
	std::string fname ("T.CSV");
	FILE * yyin = fopen(fname.c_str(), "rb");
	if (!yyin) {
		cerr << " Unable to open: " << fname << " for read ... exiting" << endl;
		exit(1);
	}
	qtm_table_output_restart(yyin);
	//if (!yyparse()) 
	if (!qtm_table_output_parse()) {
		cout << "Input parsed successfully" << endl;
	}
	
}

