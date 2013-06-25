%{

#include "const_defs.h"
	extern int yylex();
	extern void yyerror(const char * s);

%}

%union {
	char name[MY_STR_MAX];
	char text_buf[MY_STR_MAX];
}

%token DEP
%token<name> FILENAME
%type<text_buf> rule
%type<text_buf> dependency_rule
%type<text_buf> command_list
%type<text_buf> filename_list

%%

rule_list: rule 
	 | rule_list rule 
	 ;

rule: dependency_rule ';' command_list
	{
	}
	;

dependency_rule: DEP FILENAME ':' filename_list
	{
	}
	;

filename_list:	FILENAME {
	}
	|	filename_list FILENAME
	{
	}
	;

command_list: {
	};

%%

int main()
{
	yyparse();
}
