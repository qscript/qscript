/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/data_entry.y
 *
 *  Parser for the data entry command line
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

%{
#include <limits.h>
#include <vector>
using namespace std;
	vector<int> data;
#include <iostream>
//#define yylex scan_datalex
	int scan_datalex();
	void scan_dataerror(char *s);
%}

%union {
	int ival;
}

%token <ival> NUMBER
%token HYPHEN
 //%token END_OF_DATA



%%

prog:	datalist /*END_OF_DATA*/ {
		cout << "GOT END_OF_DATA" << endl;
	}
	;

datalist: data
	| datalist data
	;

data: NUMBER	{
	      data.push_back($1);
	}
	| NUMBER HYPHEN NUMBER {
		data.push_back($1);
		for(int i=data[data.size()-1]+1; i<=$3; ++i){
			data.push_back(i);
		}
	}
	;
%%

	void scan_dataerror(char *s){
		cout << "error in input: " << s << endl;
	}
