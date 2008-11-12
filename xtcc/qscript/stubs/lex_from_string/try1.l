%{
#include <string>
#include <iostream>
	using std::string;
	using std::cout;
	using std::cerr;
	using std::endl;

	enum read_data_token { NUMBER, HYPHEN, INVALID, END_OF_DATA };
	int scan_datalex();
%}

%option noyywrap
%option prefix="scan_data"

%%
[ \t]+	;

[0-9]+	{
	return NUMBER;
}

-	{
	return HYPHEN;
}

<<EOF>>	{
	cout << "finished parse" << endl;
	return END_OF_DATA;
}

. 	{
	cerr << "ERROR: running ECHO rule" ;
	ECHO;
	}

%%

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
	string s="1 2 4-8";
	YY_BUFFER_STATE s_data =  yy_scan_string(s.c_str());

	read_question_data();
	cout << endl;
	yy_delete_buffer(s_data);

	cout << endl;
	for(int i=0; i<data.size(); ++i){
		cout << data[i] << ' ';
	}
	cout << endl;
	return 0;
}


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
