
%{
#include "const_defs.h"
#include "common.h"
#include "q.tab.h"
	void yyerror(const char * s);
	int line_no;
	extern int no_errors;

%}

%%

[ \t]+	; /* ignore */

\n	{ ++line_no; } 

";"	{
	return ';';
}

"("	{ return '('; }
")"	{ return ')'; }

void		{ yylval.dt=VOID_TYPE; return VOID_T; }
int8_t		{ yylval.dt=INT8_TYPE; return INT8_T; }
int16_t		{ yylval.dt=INT16_TYPE;	return INT16_T; }
int32_t		{ yylval.dt=INT32_TYPE;	return INT32_T; }
float		{ yylval.dt=FLOAT_TYPE; return FLOAT_T; }
double 		{ yylval.dt=DOUBLE_TYPE; return DOUBLE_T; }
string 		{ yylval.dt=STRING_TYPE; return STRING_T; }
sp 	{return SP;}
mp 	{ return MP;}

[0-9]+	{
	yylval.ival = atoi(yytext);
	return INUMBER;
}

[_A-Za-z][A-Za-z0-9_]*	{
	if(yyleng < MY_STR_MAX) {
		strcpy(yylval.name,yytext);
		return NAME;
	} else {
		printf("TEXT TOKEN too long... exiting lexer\n");
		exit(1);
	}

}

\"[^\"]*\"      {
	int len_text=strlen(yytext);
	if(yyleng < MY_STR_MAX-1) {
		strcpy(yylval.text_buf, yytext);
	} else {
		printf("TEXT TOKEN too long... exiting lexer\n");
		exit(1);
	}
	return TEXT;
}

.	return yytext[0];


%%

	void yyerror(const char * s){
		++no_errors;
	 	printf("%s: line: %d: yytext: %s\n", s, line_no, yytext  );
		printf("no_errors: %d\n", no_errors);
	}

int yywrap(){
	return 1;
}
