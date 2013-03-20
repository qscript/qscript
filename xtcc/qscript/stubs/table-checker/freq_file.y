/*
	Copyright : Neil Xavier D'Souza, 2013
	License: GNU GPL2
*/

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
    int n_codes;
    int n_stubs;

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
		//cout << "parsed axis_freq_count to axis_freq_count_list"
		//	<< endl;
	}
	| axis_freq_count_list axis_freq_count {
		//cout << "chaining axis_freq_count with axis_freq_count_list"
		//	<< endl;
	}
	;

axis_freq_count: name stub_header_line stub_frequency_list NEWL {
		//cout << "got an named stub axis_freq_count" << endl;
		freq_count_map_nq_name_stub_freq[axis_name] = temp_freq_count_map_nq_stub_codefreq;
		freq_count_map_nq_name_code_freq[axis_name] = temp_freq_count_map_nq_code_codefreq;
		freq_count_map_nq_name_stub_code[axis_name] = temp_freq_count_map_nq_stub_code;
		temp_freq_count_map_nq_stub_codefreq.clear();
		temp_freq_count_map_nq_code_codefreq.clear();
		temp_freq_count_map_nq_stub_code.clear();
		cout << "got Named Question axis_freq_count: " << axis_name << endl;
		cout << "got axis_freq_count: " << axis_name
            << ", n_stubs: " << n_stubs
            << ", n_codes: " << n_codes
            << endl;
        n_stubs = 0;
        n_codes = 0;
	}
	| name code_header_line NEWL {
        // do nothing - this question had no data
    }
	| name stub_header_line NEWL {
        // do nothing - this question had no data
    }
	| name code_header_line code_freq_list NEWL{
		//cout << "got an range stub axis_freq_count" << endl;
		freq_count_map_rq[axis_name] = temp_freq_count_map_rq;
		temp_freq_count_map_rq.clear();
		cout << "got Range Question axis_freq_count: " << axis_name
            << ", n_stubs: " << n_stubs
            << ", n_codes: " << n_codes
            << endl;
        n_stubs = 0;
        n_codes = 0;
	}
	;

stub_header_line: STUBS COMMA CODE COMMA FREQUENCY NEWL {
	//cout << "got stubs_header_line" << endl;
	}

code_header_line: COMMA CODE COMMA FREQUENCY NEWL {
	//cout << "got code_header_line" << endl;
	}

name: NAME NEWL {
	//cout << "Got NAME: " << $1 << endl;
	axis_name = $1;
	}
	| NAME DOT INUMBER NEWL {
		cout << "Got array NAME: " << $1 << endl;
		stringstream s1;
		s1 << $1 << "_" << $3;
		axis_name = s1.str();
	}

stub_frequency_list: stub_freq
	| stub_frequency_list stub_freq
	;

code_freq_list: code_freq
	| code_freq_list code_freq
	;

stub_freq: TEXT COMMA INUMBER COMMA INUMBER NEWL {
	temp_freq_count_map_nq_stub_codefreq[$1]=$5;
	temp_freq_count_map_nq_code_codefreq[$3]=$5;
	temp_freq_count_map_nq_stub_code[$1]=$3;
	cout << "Got stub: |"  << $1 << "|"
        << ", code " << $3
        << ", freq " << $5
        << endl;
	nq_axis = true;
    ++n_stubs;
}

code_freq: COMMA INUMBER COMMA INUMBER NEWL {
	//cout	<< "Got code_freq code:"  << $2
	//	<< ", freq: " << $4
	//	<< endl;
		temp_freq_count_map_rq[$2] = $4;
		nq_axis = false;
        ++n_codes;
	 }

%%
	extern void yyrestart(FILE *input_file);
	extern int32_t yyparse();

#include "const_defs.h"
/*
// Enable main if you want to test separately

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
*/
