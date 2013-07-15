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
#include "lex_location.h"

namespace qscript_parser {
	//void yyerror(const char * s);
	extern int line_no;
	extern int no_errors;
	extern int if_line_no;
	//using namespace std;
	//using qscript_parser::lex_location;
	extern struct LexLocation lex_location;
	extern bool show_lex_error_context ;

}

%}
%option never-interactive
%option nounput
%x comment



%%


"/*"		{
			qscript_parser::lex_location.IncrementColumn(yyleng);
			BEGIN(comment);
		}

<comment>[^*\n]*	{
				qscript_parser::lex_location.IncrementColumn(yyleng);
			}

<comment>"*"+[^*/\n]*   {
				qscript_parser::lex_location.IncrementColumn(yyleng);
			}

<comment>\n	{ 
		++qscript_parser::line_no;
		qscript_parser::lex_location.IncrementLine(1);
		qscript_parser::lex_location.ResetColumn();
	}

<comment>"*"+"/" { 
			qscript_parser::lex_location.IncrementColumn(yyleng);
			BEGIN(INITIAL);
		}

\/\/.*	{
	// ignore Comment
}

[\t]+	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(8*yyleng);
	}

[ \r]+	{ /* ignore */
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
			
		qscript_parser::lex_location.IncrementColumn(yyleng);
	}

\n	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.ResetCurrentDisplayLine();
		++qscript_parser::line_no;
		qscript_parser::lex_location.IncrementLine(1);
		qscript_parser::lex_location.ResetColumn();
	} 

";"	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return ';';
	}

"("	{ 
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return '('; 
	}

")"	{	
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return ')'; 
	}

"<="	{ 
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return LEQ; 
	}

">="	{	
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return GEQ;
	}

"=="	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);

		qscript_parser::lex_location.IncrementColumn(yyleng);
		return ISEQ;
	}

"!="	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return NOEQ;
	}

"&&" 	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return LOGAND;
	}

"||"	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return LOGOR;
	}

"!"	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return NOT;
	}

"{"	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return '{';
	}

"}"	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return '}';
	}

":"	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return ':';
}

goto	{
		return GOTO;
	}




if	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		qscript_parser::if_line_no = qscript_parser::line_no;
		return IF;
	}

else 	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return ELSE; 
	}

in 	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return IN;
	}

for	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return FOR;
	}


stubs	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return STUBS_LIST;
	}

named_attribute {
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return NAMED_ATTRIBUTES;
	}

void	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		yylval.dt=VOID_TYPE; return VOID_T; 
	}

int8_t	{ 
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		yylval.dt=INT8_TYPE; return INT8_T; 
	}

int16_t	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		yylval.dt=INT16_TYPE;	return INT16_T; 
	}

int32_t		{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		yylval.dt=INT32_TYPE;	return INT32_T;
	}

float		{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		yylval.dt=FLOAT_TYPE; return FLOAT_T;
	}

double 		{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		yylval.dt=DOUBLE_TYPE; return DOUBLE_T;
	}

string 		{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		yylval.dt=STRING_TYPE; return STRING_T;
	}

sp 		{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return SINGLE_CODED;
	}

mp 		{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return MP;
	}

video		{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return VIDEO;
	}

const 		{
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return CONST;
	}

setdel		{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return SETDEL;
	}

setadd		{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return SETADD;
	}

unset		{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return UNSET;
	}

setall		{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return SETALL;
	}

to_string	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return TOSTRING;
	}

hide 	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return HIDDEN;
}

allow_blank	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return ALLOW_BLANK;
}

mutex	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return MUTEX;

}

clear	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return CLEAR;
}

column	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		return COLUMN;
}

isanswered	{
		return ISANSWERED;
	}

count		{
		return COUNT;
	}

newcard		{
		return NEWCARD;
	}


[0-9]+	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		yylval.ival = atoi(yytext);
		return INUMBER;
	}

([0-9]*\.[0-9]+([eE][-+]?[0-9]+)?)	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		yylval.dval = atof(yytext);
		return FNUMBER;
	}

[_A-Za-z][A-Za-z0-9_]*	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
		if(yyleng < MY_STR_MAX) {
			strcpy(yylval.name,yytext);
			return NAME;
		} else {
			printf("TEXT TOKEN too long... exiting lexer\n");
			exit(1);
		}
	}

\"[^\"]*\"      {
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		qscript_parser::lex_location.IncrementColumn(yyleng);
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

.	{
		if (qscript_parser::show_lex_error_context)
			qscript_parser::lex_location.AddToCurrentDisplayLine(yytext);
		return yytext[0];
		qscript_parser::lex_location.IncrementColumn(yyleng);
	}


%%
	using qscript_parser::lex_location;

	void yyerror(const char * s);
	void yyerror(const char * s)
	{
		//fprintf(stderr, "reached here: %s\n", __PRETTY_FUNCTION__);
		using qscript_parser::no_errors;
		using qscript_parser::line_no;
		++no_errors;
	 	//printf("%s: line: %d: yytext: %s\n", s, line_no, yytext);
	 	printf("line: %d: \n", line_no);
		printf ("lexical error: line: %d, column: %d\n"
			, lex_location.lineNo_
			, lex_location.columnNo_);
		printf ("%s\n", lex_location.currentLine_.str().c_str());
		printf ("%*s\n%*s\ntoken: %s\n", lex_location.columnNo_, "^"
				    , lex_location.columnNo_, s, yytext);
	}

	void clean_lex()
	{
		yy_delete_buffer(YY_CURRENT_BUFFER);
	}


int yywrap(){
	return 1;
}


