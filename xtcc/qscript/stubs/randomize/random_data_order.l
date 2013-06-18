/* random_data_order.l
 *
 * simple tokenizer for reading randomized stubs order
 */

%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include "const_defs.h"
#include "random_data_order.tab.h"
#include "lex_location.h"

	//void yyerror(const char * s);
	extern int line_no;
	extern int no_errors;
	struct LexLocation lex_location;
	bool show_lex_error_context = true ;
	void yyerror(const char * s);
	
%}

%option never-interactive
%x comment

%%


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

":" 	{
		if (show_lex_error_context)
			lex_location.AddToCurrentDisplayLine(yytext);
		lex_location.IncrementColumn(yyleng);
		return ':';
	}

";" 	{
		if (show_lex_error_context)
			lex_location.AddToCurrentDisplayLine(yytext);
		lex_location.IncrementColumn(yyleng);
		return ';';
	}

[0-9]+	{
		if (show_lex_error_context)
			lex_location.AddToCurrentDisplayLine(yytext);
		lex_location.IncrementColumn(yyleng);
		yylval.ival = atoi(yytext);
		return INUMBER;
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


%%


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


int yywrap(){
	return 1;
}
