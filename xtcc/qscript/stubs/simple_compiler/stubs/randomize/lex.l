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
#include "randomize.tab.h"
#include "lex_location.h"

	//void yyerror(const char * s);
	extern int line_no;
	extern int no_errors;
	struct LexLocation lex_location;
	bool show_lex_error_context = true ;

%}
%option never-interactive
%x comment


%%


"/*"		{
			lex_location.IncrementColumn(yyleng);
			BEGIN(comment);
		}

<comment>[^*\n]*	{
				lex_location.IncrementColumn(yyleng);
			}

<comment>"*"+[^*/\n]*   {
				lex_location.IncrementColumn(yyleng);
			}

<comment>\n	{ 
		++line_no;
		lex_location.IncrementLine(1);
		lex_location.ResetColumn();
	}

<comment>"*"+"/" { 
			lex_location.IncrementColumn(yyleng);
			BEGIN(INITIAL);
		}

\/\/.*	{
	// ignore Comment
}

[\t]+	{
		if (show_lex_error_context)
			lex_location.AddToCurrentDisplayLine(yytext);
		lex_location.IncrementColumn(8*yyleng);
	}

[ \r]+	{ /* ignore */
		if (show_lex_error_context)
			lex_location.AddToCurrentDisplayLine(yytext);
			
		lex_location.IncrementColumn(yyleng);
	}

\n	{
		if (show_lex_error_context)
			lex_location.ResetCurrentDisplayLine();
		++line_no;
		lex_location.IncrementLine(1);
		lex_location.ResetColumn();
	} 

";"	{
		if (show_lex_error_context)
			lex_location.AddToCurrentDisplayLine(yytext);
		lex_location.IncrementColumn(yyleng);
		return ';';
	}

"{"	{
		if (show_lex_error_context)
			lex_location.AddToCurrentDisplayLine(yytext);
		lex_location.IncrementColumn(yyleng);
		return '{';
	}

"}"	{
		if (show_lex_error_context)
			lex_location.AddToCurrentDisplayLine(yytext);
		lex_location.IncrementColumn(yyleng);
		return '}';
	}

":"	{
		if (show_lex_error_context)
			lex_location.AddToCurrentDisplayLine(yytext);
		lex_location.IncrementColumn(yyleng);
		return ':';
}

stubs	{
		if (show_lex_error_context)
			lex_location.AddToCurrentDisplayLine(yytext);
		lex_location.IncrementColumn(yyleng);
		return STUBS_LIST;
	}

stub_group {
		if (show_lex_error_context)
			lex_location.AddToCurrentDisplayLine(yytext);
		lex_location.IncrementColumn(yyleng);
	return STUB_GROUP;
}

mutex	{
		if (show_lex_error_context)
			lex_location.AddToCurrentDisplayLine(yytext);
		lex_location.IncrementColumn(yyleng);
		return MUTEX;
}


[0-9]+	{
		if (show_lex_error_context)
			lex_location.AddToCurrentDisplayLine(yytext);
		lex_location.IncrementColumn(yyleng);
		yylval.ival = atoi(yytext);
		return INUMBER;
	}

randomize {
	return RANDOMIZE;
}

[_A-Za-z][A-Za-z0-9_]*	{
		if (show_lex_error_context)
			lex_location.AddToCurrentDisplayLine(yytext);
		lex_location.IncrementColumn(yyleng);
		if(yyleng < MY_STR_MAX) {
			strcpy(yylval.name,yytext);
			return NAME;
		} else {
			printf("TEXT TOKEN too long... exiting lexer\n");
			exit(1);
		}
	}

\"[^\"]*\"      {
		if (show_lex_error_context)
			lex_location.AddToCurrentDisplayLine(yytext);
		lex_location.IncrementColumn(yyleng);
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
		if (show_lex_error_context)
			lex_location.AddToCurrentDisplayLine(yytext);
		return yytext[0];
		lex_location.IncrementColumn(yyleng);
	}


%%

	void yyerror(const char * s);
	void yyerror(const char * s)
	{
		fprintf(stderr, "reached here: %s\n", __PRETTY_FUNCTION__);
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


