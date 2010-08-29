/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/try1.l
 *
 * tokenizer for the data entry command line - this file should be named better 
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
%{
#include <string>
#include <iostream>
#include "data_entry.hpp"
#include "user_navigation.h"
//#include <readline/readline.h>
#include "qscript_readline.h"

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
		if(yytext[0] == 'n'){
			return NAVIGATE_NEXT_TOK;
		} else if (yytext[0]=='p'){
			return NAVIGATE_PREVIOUS_TOK;
		} else if (yytext[0]=='j'){
			return JUMP_TO_QUESTION_TOK;
		} else if (yytext[0] =='s') {
			return SAVE_DATA_TOK;
		} else  {
			cerr << "ERROR: running ECHO rule" << endl;
			ECHO;
			return yytext[0];
		}
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
	extern  UserNavigation user_navigation;
	void scan_dataerror(char *s);

	void read_data( const char * prompt)
	{
		data.clear();
top:
		//char * line=readline(prompt);
		//const int BUF_MAX=1023;
		//char buffer[BUF_MAX];
		string buffer;
		//fgets(buffer, BUF_MAX, stdin);
		cout.flush();
		getline(cin, buffer);
		if(buffer.length()==0){
			goto top;
		}
		//printf("readline: %s\n", line);
		cout << "buffer: " << buffer << endl;
		YY_BUFFER_STATE s_data =  scan_data_scan_string(buffer.c_str());
		if(scan_dataparse()){
			cout << "there was an error in parsing the data" << endl;
			yy_delete_buffer(s_data);
			data.clear();
			goto top;
		}
		//cout << "read: " << endl;
		//for(int i=0; i<data.size(); ++i){
		//	cout << data[i] << "," ;
		//}
		cout << endl;
		yy_delete_buffer(s_data);
	}

	void read_data_from_window(WINDOW * data_entry_window, const char * prompt
		, bool clear_buffer_flag, string & re_arranged_buffer, int & pos_1st_invalid_data)
	{
		/*
		data.clear();
top:
		//cerr << "clear_buffer_flag: " << clear_buffer_flag;
		char * line=qscript_readline(data_entry_window, prompt
			, clear_buffer_flag, re_arranged_buffer, pos_1st_invalid_data);
		YY_BUFFER_STATE s_data =  scan_data_scan_string(line);
		if(scan_dataparse()){
			//cout << "there was an error in parsing the data" << endl;
			data.clear();
			yy_delete_buffer(s_data);
			//delete[] line;
			clear_buffer_flag=false;
			//cerr << "reset clear_buffer_flag: " << clear_buffer_flag;
			goto top;
		}
		//for(int i=0; i<data.size(); ++i){
		//	cout << data[i] << "," ;
		//}
		yy_delete_buffer(s_data);
		//delete[] line;
		*/

		static NCursesReadline ncurses_readline(data_entry_window);
		data.clear();
		if(clear_buffer_flag)
		{
			ncurses_readline.Reset();
		} else {
			ncurses_readline.SetBuffer(re_arranged_buffer
					, pos_1st_invalid_data );
		}

top:
		//cerr << "clear_buffer_flag: " << clear_buffer_flag;
		// NOTE: so long as the ncurses_readline is static the pointer 
		// returned will be valid
		const char * line=ncurses_readline.ReadLine();
		YY_BUFFER_STATE s_data =  scan_data_scan_string(line);
		if(scan_dataparse()){
			//cout << "there was an error in parsing the data" << endl;
			data.clear();
			yy_delete_buffer(s_data);
			//delete[] line;
			clear_buffer_flag=false;
			//cerr << "reset clear_buffer_flag: " << clear_buffer_flag;
			goto top;
		}
		//for(int i=0; i<data.size(); ++i){
		//	cout << data[i] << "," ;
		//}
		yy_delete_buffer(s_data);
	}

