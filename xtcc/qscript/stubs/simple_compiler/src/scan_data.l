/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/try1.l
 *
 * tokenizer for the data entry command line - this file should be named better
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
%{
#include <string>
#include <iostream>
#include <vector>
#include "data_entry.hpp"
#include "user_navigation.h"
//#include <readline/readline.h>
#include "qscript_readline.h"

	using namespace std;

	//enum read_data_token { NUMBER, HYPHEN, INVALID, END_OF_DATA };
	int scan_datalex (YYSTYPE * yylval_param, yyscan_t yyscanner);
	int scan_dataparse(yyscan_t yyscanner, vector<int>* data_ptr);
%}

%option never-interactive
%option noyywrap
%option prefix="scan_data"
%option reentrant 
%option bison-bridge

%%
[ \t]+	;

[0-9]+	{
	yylval_param->ival = atoi(yytext);
	//scan_datalval.ival = atoi(yytext);
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
		/*
		if(yytext[0] == 'n'){
			return NAVIGATE_NEXT_TOK;
		} else if (yytext[0] == 'p'){
			return NAVIGATE_PREVIOUS_TOK;
		} else if (yytext[0] == 'j'){
			return JUMP_TO_QUESTION_TOK;
		} else if (yytext[0] == 's') {
			return SAVE_DATA_TOK;
		} else if (yytext[0] == 'c') {
			return CLEAR_DATA;
		} else  {
			// cerr << "ERROR: running ECHO rule" << endl;
			//ECHO;
			return yytext[0];
		}*/
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
	//vector<int> data;

int main(){
	string s="1 2 4-8 12-15 5";
	yyscan_t scanner;
	yylex_init(&scanner);
	//YY_BUFFER_STATE s_data =  yy_scan_string(s.c_str());
	YY_BUFFER_STATE s_data =  scan_data_scan_string(s.c_str(), scanner);

	//read_question_data();
	vector <int> data;
	scan_dataparse(scanner, &data);
	cout << endl;
	yy_delete_buffer(s_data, scanner);

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
	//extern vector<int> data;
	extern UserNavigation user_navigation;
	extern user_response::UserResponseType the_user_response;
	void scan_dataerror(char *s);

user_response::UserResponseType read_data( const char * prompt, vector<int> * data_ptr)
{
	yyscan_t scanner;
	yylex_init(&scanner);
	vector <int> & data = *data_ptr;
	data.clear();
	user_navigation = NOT_SET;
top:
	string buffer;
	cout << prompt << "> ";
	cout.flush();
	getline(cin, buffer);
	if(buffer.length()==0){
		cout << "Empty line ... re-enter" << endl;
		goto top;
	}
	cout << "buffer: " << buffer << endl;
	YY_BUFFER_STATE s_data =  scan_data_scan_string(buffer.c_str(), scanner);
	if(scan_dataparse(scanner, &data)){
		cout << "there was an error in parsing the data" << endl;
		yy_delete_buffer(s_data, scanner);
		data.clear();
		goto top;
	}
	cout << endl;
	yy_delete_buffer(s_data, scanner);
	return the_user_response;
}

user_response::UserResponseType read_data_from_window(
		WINDOW * question_window, 
		WINDOW * stub_list_window,
		WINDOW * data_entry_window,
		const char * prompt, bool clear_buffer_flag, string & re_arranged_buffer,
		int & pos_1st_invalid_data, AbstractQuestion * q, vector<int> * data_ptr)
{
	static NCursesReadline ncurses_readline(question_window, stub_list_window, data_entry_window);
	vector <int> & data = *data_ptr;
	data.clear();
	if (clear_buffer_flag) {
		ncurses_readline.Reset();
	} else {
		ncurses_readline.SetBuffer(re_arranged_buffer
				, pos_1st_invalid_data );
	}
	wattroff(data_entry_window, COLOR_PAIR(1));
	wattron(data_entry_window, COLOR_PAIR(5));
	mvwprintw(data_entry_window, 3, 1, prompt);
	wattroff(data_entry_window, COLOR_PAIR(5));
	wattron(data_entry_window, COLOR_PAIR(1));

top:
	//cerr << "clear_buffer_flag: " << clear_buffer_flag;
	// NOTE: so long as the ncurses_readline is static the pointer
	// returned will be valid
	const char * line=ncurses_readline.ReadLine(q);
	// cout << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
	// 	<< ", " << line << endl;

	string s(line);
	if (s.length()==0) {
		if ( (user_navigation == NAVIGATE_NEXT || user_navigation == NAVIGATE_PREVIOUS)
				&& the_user_response==user_response::UserEnteredNavigation) {
		//cout << "Empty line ... re-enter" << endl;
			return the_user_response;
		} else if (user_navigation == NOT_SET) {
			user_navigation = NAVIGATE_NEXT; // treat as if visit next question
			the_user_response = user_response::UserEnteredNavigation;
			return the_user_response;
		} else if (user_navigation == SAVE_DATA &&
				the_user_response == user_response::UserSavedData) {
			return the_user_response;
		} else {
			goto top;
		}
	}
	yyscan_t scanner;
	yylex_init(&scanner);
	YY_BUFFER_STATE s_data =  scan_data_scan_string(line, scanner);
	if (scan_dataparse(scanner, &data)) {
		//cout << "there was an error in parsing the data" << endl;
		data.clear();
		yy_delete_buffer(s_data, scanner);
		//delete[] line;
		clear_buffer_flag=false;
		//cerr << "reset clear_buffer_flag: " << clear_buffer_flag;
		wattroff(data_entry_window, COLOR_PAIR(1));
		wattron(data_entry_window, COLOR_PAIR(5));
		mvwprintw(data_entry_window, 3, 1, "invalid text, re-enter");
		wattroff(data_entry_window, COLOR_PAIR(5));
		wattron(data_entry_window, COLOR_PAIR(1));
		goto top;
	}
	//for(int i=0; i<data.size(); ++i){
	//	cout << data[i] << "," ;
	//}
	yy_delete_buffer(s_data, scanner);
	// user_response::UserResponseType resp = (user_navigation == NOT_SET) 
	// 	? user_response::UserEnteredData:user_response::UserEnteredNavigation;
	// return resp;
	return the_user_response;
}

	
bool verify_web_data (string p_question_data, 
		UserNavigation p_user_navigation,
		user_response::UserResponseType p_the_user_response,
		vector<int> * data_ptr)
{
	cout << __PRETTY_FUNCTION__ << ", p_question_data: " << p_question_data << endl;
	user_response::UserResponseType l_user_response = user_response::NotSet; 
	if (p_question_data.length()==0) {
		return l_user_response;
	}
	yyscan_t scanner;
	yylex_init(&scanner);
	YY_BUFFER_STATE s_data =  scan_data_scan_string(p_question_data.c_str(), scanner);
	vector <int> & data = * data_ptr;
	if (scan_dataparse(scanner, &data)) {
		cout << "there was an error in parsing the data" << endl;
		yy_delete_buffer(s_data, scanner);
		data.clear();
		return false;
	} else {
		return true;
	}
	cout << endl;
	yy_delete_buffer(s_data, scanner);
	return true;
}
