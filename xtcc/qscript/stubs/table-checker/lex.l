
%{

#include <map>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "../const_defs.h"
#include "freq_file.h"


	extern int yylex();
	extern void yyerror(const char * s);
	using std::cout;
	using std::cerr;
	using std::endl;
    int line_no;

%}


%%

[\t]+	{
    /* ignore */
}

","   {
    //cout << "got COMMA" << endl;
    return COMMA;
}

[ \r\t]+	{ /* ignore */
}

\n  {
    ++line_no;
    //cout << "got a NEWL: line_no: "  << line_no << endl;
	return NEWL;
}

[0-9]+	{
		yylval.ival = atoi(yytext);
        //cout << "got INUMBER " << yylval.ival << endl;
		return INUMBER;
	}

([0-9]+\.[0-9]+([eE][-+]?[0-9]+)?)	{
		yylval.dval = atof(yytext);
		return FNUMBER;
	}


code {
    //cout << "got CODE" << endl;
    return CODE;
}

frequency {
    //cout << "got FREQUENCY" << endl;
    return FREQUENCY;
}

stubs {
    //cout << "got STUBS" << endl;
    return STUBS;
}


\"[^\"]*\"      {
		//int len_text=strlen(yytext);
		int len_text = yyleng;
		yytext[len_text-1]='\0'; // clobber double quote
		if(yyleng < MY_STR_MAX-1) {
			strcpy(yylval.text_buf, yytext+1);
		} else {
			printf("TEXT TOKEN too long... exiting lexer\n");
			exit(1);
		}
        return TEXT;
	}

[_A-Za-z][A-Za-z0-9_]*	{
		if(yyleng < MY_STR_MAX) {
			strcpy(yylval.name,yytext);
            cout << "got NAME:" << yytext << endl;
			return NAME;
		} else {
			printf("TEXT TOKEN too long... exiting lexer\n");
			exit(1);
		}
	}


\.     {
    cout << "got DOT" << endl;
    return DOT;
}

.    {
    cout << "unhandled inputs: |" << yytext[0] << "|"
        << endl;
    return yytext[0];
}

%%


	void yyerror(const char * s)
	{
		//fprintf(stderr, "reached here: %s\n", __PRETTY_FUNCTION__);
		//using qscript_parser::no_errors;
		//using qscript_parser::line_no;
		//++no_errors;
	 	printf("%s: line: %d: yytext: %s\n", s, line_no, yytext);
	 	printf("line: %d: \n", line_no);
		//printf ("lexical error: line: %d, column: %d\n"
		//	, lex_location.lineNo_
		//	, lex_location.columnNo_);
		//printf ("%s\n", lex_location.currentLine_.str().c_str());
		//printf ("%*s\n%*s\ntoken: %s\n", lex_location.columnNo_, "^"
		//		    , lex_location.columnNo_, s, yytext);
	}


int yywrap(){
	return 1;
}
