
%{
#include <vector>
	using std::vector;
	vector<int> data;
#include <iostream>
using namespace std;
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
