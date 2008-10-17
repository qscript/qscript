%{
#define MY_STR_MAX 50

#include "symtab.h"
#include "expr.tab.h"
	extern int no_errors;
	void yyerror(char * s);
	int line_no=1;


%}


%%

[ \t]+	; /* ignore */
\n	{ ++line_no; } 
"("	return '(';
")"	return ')';
";"	return ';' ;
","	return ',' ;
"&&"	return LOGAND ;



in	return IN;

[0-9]+	{
	yylval.ival = atoi(yytext);
	return INUMBER;
}

[A-Za-z_][A-Za-z0-9_]*	{
	if(yyleng < MY_STR_MAX) {
		strcpy(yylval.name,yytext);
		return NAME;
	} else {
		printf("TEXT TOKEN too long... exiting lexer\n");
		exit(1);
	}
}


%%

void yyerror(char * s){
	++no_errors;
	printf("%s: line: %d: yytext: %s\n", s, line_no, yytext  );
	printf("no_errors: %d\n", no_errors);
}

int yywrap(){
	return 1;
}

