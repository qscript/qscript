%{
#include "my_defines.h"
#include <map>
#include <string>
#include <iostream>
#include <cstring>

#define YY_USE_PROTOS
#ifdef YY_USE_PROTOS
#define YY_PROTO(proto) proto
#else
#define YY_PROTO(proto) ()
#endif
	using namespace std;
	extern int lineno;
	extern char *  yytext;
	int yyparse();
	extern int yylex();
	extern void pre_proc_open_file(char * const fname);
	//extern const int MAX_INCL_DEPTH=15;
	//extern int incl_stk_ptr;
	//extern YY_BUFFER_STATE include_stack[MAX_INCL_DEPTH];
	map <string, string> pre_sym_tab;
	void yyerror(char *s);
%}

%union	{
	char file_name[MAX_BUF];
	char subst_txt[MAX_BUF];
	char subst_id[MAX_BUF];
}

%token	SEMI_COLON
%token	<file_name> FILENAME
%token 	<subst_id> SUBST_ID
%token <subst_txt> SUBST_TEXT
%token	EQUALS
%token NEWL
%token INCL
%token M_DEFINE

%%

pre_proc_gram: /* empty */ {
		//cout << "parsed as an empty string" << endl;
	}
	|pre_proc_directives
	;

pre_proc_directives: pre_proc_directive
	| pre_proc_directives pre_proc_directive
	;
	

pre_proc_directive:	include_directive
	| 	define_directive
	;

/*
include_directives: include_directive
	|	include_directives include_directive
	;
	*/

include_directive:	INCL 	FILENAME SEMI_COLON subst_list NEWL{
		//printf("passing filename: %s: to pre_proc_open_file\n", $2);
		char fname[MAX_BUF];
		strcpy(fname, $2);
		pre_proc_open_file(fname);
	}
	;

/*
define_directives: define_directive
	| define_directives define_directive
	;
*/	

define_directive: M_DEFINE subst_list NEWL {
//define_directive: M_DEFINE NEWL{
		// the "subst_list" rule transfers the text into the symbol table
		//cout << "got define directive\n";
	}
	;

subst_list:	subst
	| subst_list subst
	;

subst:	SUBST_ID EQUALS SUBST_TEXT SEMI_COLON {
     		//cout << "storing : " << $1 << "=" << $3 << endl;
		pre_sym_tab[$1]=$3;
	}
	;


%%

int main(){
	return	yyparse();
}

void yyerror(char *s){
	cout << "Error: lineno " << lineno+1  << ":yytext: " << yytext <<
		":Errmsg:" << s << endl;
}
