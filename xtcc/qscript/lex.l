%{
#include <math.h>
#include "const_defs.h"
#include "../xtcc/trunk/symtab.h"
#include "qscript.h"
	void yyerror(char * s);
	int line_no=1;
	extern int no_errors;
%}

%x comment
%option never-interactive

%%
	/* NxD: I shamelessly copied this out of flex's man page */	
"/*"         BEGIN(comment);
<comment>[^*\n]*        /* eat anything that's not a '*' */
<comment>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<comment>\n             ++line_no;
<comment>"*"+"/"        BEGIN(INITIAL);
\/\/.*	{
	// ignore Comment
}

[ \t]+	; /* ignore */
\n	{ ++line_no; } 

void 	{ yylval.dt=VOID_TYPE; return VOID_T; }
int8_t		{ yylval.dt=INT8_TYPE;	       return INT8_T; }
int16_t		{ yylval.dt=INT16_TYPE;	       return INT16_T; }
int32_t		{ yylval.dt=INT32_TYPE;	       return INT32_T; }
float	{ yylval.dt=FLOAT_TYPE; return FLOAT_T; }
double { yylval.dt=DOUBLE_TYPE; return DOUBLE_T; }
continue	{
	return CONTINUE;
}
break	{
	return BREAK;
}
";"	{
	return ';';
}

")"	{ return ')'; }

"("	{ return '('; }



"<=" {return LE;}
">=" {return GE;}
"==" {return ISEQ;}
"!=" {return NOEQ;}

"&&" 	{ return LOGAND; }
"||"	{ return LOGOR; }
"!"	{ return NOT; }

sp 	{return SP;}
mp 	{ return MP;}
in 	{ return IN;}
count 	{ return COUNT;}

[0-9]+	{
	yylval.ival = atoi(yytext);
	return INUMBER;
}

([0-9]*\.[0-9]+([eE][-+]?[0-9]+)?)	{
	yylval.dval = atof(yytext);
	printf("returned %g\n", yylval.dval);
	return FNUMBER;
}

if	{
	printf("got IF"); 
	return IF;
}

else 	{
	return ELSE;
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


void yyerror(char * s){
	++no_errors;
	printf("%s: line: %d: yytext: %s\n", s, line_no, yytext  );
	printf("no_errors: %d\n", no_errors);
}

int yywrap(){
	return 1;
}

