/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/lex.l
 *
 * lex tokenizer for the grammar
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "const_defs.h"
//#include "common.h"
#include "symtab.h"
#include "q.hpp"

namespace qscript_parser {
	//void yyerror(const char * s);
	extern int line_no;
	extern int no_errors;
	extern int if_line_no;
	using namespace std;

}

%}
%option never-interactive
%x comment


%%


"/*"         BEGIN(comment);
<comment>[^*\n]*        /* eat anything that's not a '*' */
<comment>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<comment>\n             ++qscript_parser::line_no;
<comment>"*"+"/"        BEGIN(INITIAL);
\/\/.*	{
	// ignore Comment
}


[ \t]+	; /* ignore */

\n	{ ++qscript_parser::line_no; } 

";"	{
	return ';';
}

"("	{ return '('; }
")"	{ return ')'; }

"<=" {return LEQ;}
">=" {return GEQ;}
"==" {return ISEQ;}
"!=" {return NOEQ;}

"&&" 	{ return LOGAND; }
"||"	{ return LOGOR; }
"!"	{ return NOT; }
"{"	{ return '{'; }
"}"	{ return '}'; }



if	{
	qscript_parser::if_line_no = qscript_parser::line_no;
	return IF;
}

else 	{ return ELSE; }

in 		{ return IN; }

for		{ return FOR; }


stubs		{ return STUBS_LIST; }


void		{ yylval.dt=VOID_TYPE; return VOID_T; }
int8_t		{ yylval.dt=INT8_TYPE; return INT8_T; }
int16_t		{ yylval.dt=INT16_TYPE;	return INT16_T; }
int32_t		{ yylval.dt=INT32_TYPE;	return INT32_T; }
float		{ yylval.dt=FLOAT_TYPE; return FLOAT_T; }
double 		{ yylval.dt=DOUBLE_TYPE; return DOUBLE_T; }
string 		{ yylval.dt=STRING_TYPE; return STRING_T; }
sp 		{return SP;}
mp 		{ return MP;}
const 		{ return CONST; }
setdel		{ return SETDEL; }
setadd		{ return SETADD; }
unset		{ return UNSET; }
setall		{ return SETALL; }


[0-9]+	{
	yylval.ival = atoi(yytext);
	return INUMBER;
}

([0-9]*\.[0-9]+([eE][-+]?[0-9]+)?)	{
	yylval.dval = atof(yytext);
	return FNUMBER;
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
	yytext[len_text-1]='\0';
	if(yyleng < MY_STR_MAX-1) {
		strcpy(yylval.text_buf, yytext+1);
	} else {
		printf("TEXT TOKEN too long... exiting lexer\n");
		exit(1);
	}
	return TEXT;
}

.	return yytext[0];


%%

	void yyerror(const char * s);
	void yyerror(const char * s){
		using qscript_parser::no_errors;
		using qscript_parser::line_no;
		++no_errors;
	 	printf("%s: line: %d: yytext: %s\n", s, line_no, yytext  );
		printf("no_errors: %d\n", no_errors);
	}

int yywrap(){
	return 1;
}

