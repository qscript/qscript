%{
#include "const_defs.h"
#include "simple_parser.hpp"
int yylex();
void yyerror(const char *s);
%}

%%


\"[^\"]*\"      {

		if(yyleng < MY_STR_MAX-1) {
			strcpy(yylval.text_buf, yytext);
		} else {
			printf("TEXT TOKEN too long... exiting lexer\n");
			exit(1);
		}
		return TEXT;
	}

.	{
		return yytext[0];
	}

%%

void yyerror(const char * s)
{
	printf("syntax error: %s, yytext: %s\n", s, yytext);
}

