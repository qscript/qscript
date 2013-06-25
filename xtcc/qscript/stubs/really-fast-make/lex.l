%{
#include <cstdio>
#include "const_defs.h"
#include "lex_location.h"
#include "gram.h"

	namespace make_parser {
		bool show_lex_error_context = true;
		LexLocation lex_location;
		int no_errors  = 0;
		int line_no  = 0;
	}
%}

%%


[\t]+	{
		if (make_parser::show_lex_error_context)
			make_parser::lex_location.AddToCurrentDisplayLine(yytext);
		make_parser::lex_location.IncrementColumn(8*yyleng);
		printf ("skipped over TAB\n");
	}

[ \r]+	{ /* ignore */
		if (make_parser::show_lex_error_context)
			make_parser::lex_location.AddToCurrentDisplayLine(yytext);
			
		make_parser::lex_location.IncrementColumn(yyleng);
		printf ("skipped over space and carriage return\n");
	}

\n	{
		if (make_parser::show_lex_error_context)
			make_parser::lex_location.ResetCurrentDisplayLine();
		++make_parser::line_no;
		make_parser::lex_location.IncrementLine(1);
		make_parser::lex_location.ResetColumn();
	} 


";"	{
		if (make_parser::show_lex_error_context)
			make_parser::lex_location.AddToCurrentDisplayLine(yytext);
		make_parser::lex_location.IncrementColumn(yyleng);
		printf("got SEMICOLON\n");
		return ';';
	}

":"	{
		if (make_parser::show_lex_error_context)
			make_parser::lex_location.AddToCurrentDisplayLine(yytext);
		make_parser::lex_location.IncrementColumn(yyleng);
		printf("got COLON\n");
		return ':';
	}

dep 	{
	return DEP;
}

[_A-Za-z][A-Za-z0-9_.]* {
		if (make_parser::show_lex_error_context)
			make_parser::lex_location.AddToCurrentDisplayLine(yytext);
		make_parser::lex_location.IncrementColumn(yyleng);
		if(yyleng < MY_STR_MAX) {
			strcpy(yylval.name,yytext);
			printf("got NAME\n");
			return FILENAME;
		} else {
			printf("TEXT TOKEN too long... exiting lexer\n");
			exit(1);
		}
	}

%%

/*
YYSTYPE yylval;
int main()
{
	yyin = stdin;
	while ( yylex()) {
	};
}
*/


	void yyerror(const char * s);
	void yyerror(const char * s)
	{
		//fprintf(stderr, "reached here: %s\n", __PRETTY_FUNCTION__);
		using make_parser::no_errors;
		using make_parser::line_no;
		using make_parser::lex_location;
		++no_errors;
	 	//printf("%s: line: %d: yytext: %s\n", s, line_no, yytext);
	 	printf("line: %d: \n", line_no);
		printf ("lexical error: line: %d, column: %d\n"
			, lex_location.lineNo_
			, lex_location.columnNo_);
		printf ("|%s|\n", lex_location.currentLine_.str().c_str());
		printf ("|%*s|\n%*s\ntoken: %s\n", lex_location.columnNo_, "^"
				    , lex_location.columnNo_, s, yytext);
	}
