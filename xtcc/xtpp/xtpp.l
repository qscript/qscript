%{
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include "my_defines.h"
	int lineno;
#include "xtpp.tab.h"
#include <map>
#include <string>
#include <iostream>
	using namespace std;
	const int MAX_INCL_DEPTH=15;
	YY_BUFFER_STATE include_stack[MAX_INCL_DEPTH];
	int incl_stk_ptr=0;

	int pre_proc_err=0;
	extern map < string,string > pre_sym_tab;
	void pre_proc_open_file(char * const fname);
%}
%option noyywrap 

%x	INCLUDE SUBST_ONE SUBST_TWO

%%

\n	{
	++lineno;
	ECHO;
}

"#define"	{
	BEGIN SUBST_ONE;
	//cout << "returning M_DEFINE\n";

	return M_DEFINE;
}

"#include"	{
	BEGIN INCLUDE;
	//cout << "returning INCLUDE\n";
	return INCL;
}

\$[A-Za-z_][A-Za-z0-9_]+;	{
	char buff[MAX_BUF];
	strcpy(buff,yytext+1);
	buff[yyleng-2]='\0';
	//cout << "yytext: " <<yytext << endl;
	//cout << "buff: " <<buff << endl;
	string s = pre_sym_tab[buff];
	//cout << s << endl;
	cout 	//<< "|" 
		<< s 
		//<< "|" 
		;
}

.	{ 
	//cout << "."; 
	ECHO; 
	}

<INCLUDE>[ \t]+	{
	//cout << "ign ' ' and TAB in INCLUDE mode\n";
}

<INCLUDE>\n	{
	cerr << "#include directive without FILENAME\n";
	++pre_proc_err;
	BEGIN 0;
	//printf("back to normal \n");
}

<INCLUDE>[A-Za-z0-9._-]+	{
	//cout << "lexer: FILENAME\n";
	if(yyleng < MAX_BUF){
		strcpy(yylval.file_name, yytext);
	} else {
		cout << "Filename too long: " << yytext << endl;;
		++pre_proc_err;
	}
	return FILENAME;
}


<INCLUDE>;	{
	BEGIN SUBST_ONE;
	return SEMI_COLON;
}

<SUBST_ONE>\n	{
	BEGIN 0;
	ECHO;
	return NEWL;
}

<SUBST_ONE>[A-Za-z0-9_]+	{
	BEGIN SUBST_TWO;
	//cout << "lexer: SUBST_ID\n";
	if( yyleng < MAX_BUF ){
		strcpy(yylval.subst_id, yytext);
	} else {
		cerr << "id name too long: " << yytext << endl;
		++pre_proc_err;
		exit(1);
	}
	return SUBST_ID;
}

<SUBST_TWO>[ \t]	{}

<SUBST_TWO>=		{
	return EQUALS;
}

	/*<SUBST_TWO>"\""[^"\n]*"\""	*/
<SUBST_TWO>"\""[^"\n]*"\""	{
	//cout << "lexer: SUBST_TEXT\n";
	//cout << "|" << yytext << "|" << endl;
	if(yyleng < MAX_BUF){
		strncpy(yylval.subst_txt, yytext+1, yyleng-2);
		yylval.subst_txt[yyleng-2]='\0';

		string s (yylval.subst_txt);
		//cout << "subst text(xtpp.l): " <<  "|" << s  << "|" << endl;
	} else {
		cout << "id name too long\n";
		exit(1);
	}
	return SUBST_TEXT;
}

<SUBST_TWO>;	{
	BEGIN SUBST_ONE;
	return SEMI_COLON;
}

<SUBST_TWO>\n	{
	BEGIN 0;
	return NEWL;
}

<<EOF>> {
	if(--incl_stk_ptr <0){
		yyterminate();
	} else {
		yy_delete_buffer(YY_CURRENT_BUFFER);
		yy_switch_to_buffer(include_stack[incl_stk_ptr]);
	}
}

%%

void pre_proc_open_file(char * const fname){
	if( incl_stk_ptr >= MAX_INCL_DEPTH ){
		printf("includes nested too deep\n");
		exit(1);
	}
	include_stack[incl_stk_ptr++]=YY_CURRENT_BUFFER;
	yyin=fopen(fname, "r");
	if(!yyin){
		printf("failed to open include file: %s\n", fname);
	}
	yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE) );
	
}

