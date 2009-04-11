/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/try1.l
 *
 * tokenizer for the data entry command line - this file should be named better 
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
%{
#include <string>
#include <iostream>
#include "data_entry.tab.h"
#include <readline/readline.h>
	using namespace std;

	//enum read_data_token { NUMBER, HYPHEN, INVALID, END_OF_DATA };
	int scan_datalex();
	int scan_dataparse();
%}

%option never-interactive
%option noyywrap
%option prefix="scan_data"

%%
[ \t]+	;

[0-9]+	{
	scan_datalval.ival = atoi(yytext);
	return NUMBER;
}

-	{
	return HYPHEN;
}

	/*<<EOF>>	{
		cout << "finished parse returning END_OF_DATA" << endl;
		return END_OF_DATA;
	}*/

. 	{
	cerr << "ERROR: running ECHO rule" << endl;
	ECHO;
	return yytext[0];
	}
	

%%

/*
#include <string>
#include <iostream>
#include <vector>
	using std::string;
	using std::cout;
	using std::cerr;
	using std::endl;
	using std::vector;
	void read_question_data();
	vector<int> data;

int main(){
	string s="1 2 4-8 12-15 5";
	YY_BUFFER_STATE s_data =  yy_scan_string(s.c_str());

	//read_question_data();
	scan_dataparse();
	cout << endl;
	yy_delete_buffer(s_data);

	cout << endl;
	for(int i=0; i<data.size(); ++i){
		cout << data[i] << ' ';
	}
	cout << endl;
	return 0;
}
*/

/*
void read_question_data(){
	int tok;
	bool is_range=false;
	while((tok=scan_datalex())!=END_OF_DATA){
		int first_num, second_num;
		switch(tok){
		case NUMBER:
			first_num = atoi(yytext);
			break;
		case HYPHEN:
			is_range=true;
			tok=scan_datalex();
			switch (tok){
				case NUMBER:
				second_num=atoi(yytext);
				break;
				default:
				cerr << "syntax error in data" << endl;
			}
			break;
		default:
			cerr << "syntax error in data" << endl;
		}
		if(is_range){
			for(int i=first_num; i<=second_num; ++i){
				data.push_back(i);
			}
		} else {
			data.push_back(first_num);
		}

	}
}
*/

#include <vector>
	using std::vector;
	extern  vector<int> data;
	void scan_dataerror(char *s);

	void read_data( const char * prompt);
		void read_data( const char * prompt){
		char * line=readline(prompt);
		//printf("readline: %s\n", line);
		cout << "readline: " << line << endl;
		YY_BUFFER_STATE s_data =  scan_data_scan_string(line);
		scan_dataparse();
		cout << "read: " << endl;
		for(int i=0; i<data.size(); ++i){
			cout << data[i] << "," ;
		}
		cout << endl;
		yy_delete_buffer(s_data);
		free(line);
		line=0;
	}

