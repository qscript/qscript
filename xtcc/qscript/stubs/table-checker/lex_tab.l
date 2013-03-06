%{

#include <map>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include <regex.h>
#include "const_defs.h"
#include "table_csv.h"
/*
typedef union YYSTYPE
{


	int ival;
	double dval;
	char name[4095];
	char text_buf[4095];



} YYSTYPE;


YYSTYPE yylval;

enum {
	TABLE=1,
	PAGE,
	TOTAL,
	SIGMA,
	MEAN,
	STUB_FREQ,
	STUB_PERC
};
*/


	extern int yylex();
	extern void yyerror(const char * s);
	using std::cout;
	using std::cerr;
	using std::endl;
	using std::string;
	int line_no;
	int count_at_least_n_matches ( regmatch_t p_match[5]);

%}


DIGIT    [0-9]
        /*ID       [a-z][a-z0-9]*/

%%

[\t]+	{
    /* ignore */
}

[ \r\t]+	{ /* ignore */
}


,\"\"	{
	cout << "RETURNING  EMPTY_LINE_1_COLS" << endl;
	return EMPTY_LINE_1_COLS;
}

,\"Total\"	{
	cout << "RETURNING  BAN_TOTAL" << endl;
	return BAN_TOTAL;
}

\"Total\",{DIGIT}+	{
	cout << "RETURNING  SIDE_TOTAL" << endl;
	return SIDE_TOTAL;
}

\"\",\"\"	{
	cout << "RETURNING EMPTY_LINE_2_COLS" << endl;
	return EMPTY_LINE_2_COLS;
}

	/*\"\",{DIGIT}+\.{DIGIT}+      */
\"\",{DIGIT}+ 	{
        cout << "got STUB_PERC " << endl;
	return STUB_PERC;
}


\"[^\"]*\",{DIGIT}+	{
        cout << "got STUB_FREQ " << endl;
	return STUB_FREQ;
}


","   {
    cout << "got COMMA" << endl;
    return COMMA;
}

\n  {
    ++line_no;
    cout << "got a NEWL: line_no: "  << line_no << endl;
	return NEWL;
}

{DIGIT}+	{
		yylval.ival = atoi(yytext);
        	cout << "got INUMBER " << yylval.ival << endl;
		return INUMBER;
	}

([0-9]*\.[0-9]+([eE][-+]?[0-9]+)?)	{
		yylval.dval = atof(yytext);
        	cout << "got FNUMBER " << yylval.dval << endl;
		return FNUMBER;
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
		string text(yylval.text_buf);
		if (strstr(text.c_str(), "#page")) {
			cout << "RETURNING PAGE" << endl;
			return PAGE;
		} else if (strstr(text.c_str(),"Table ")) {
			cout << "RETURNING TABLE" << endl;
			return TABLE;
		} else if (strstr(text.c_str(),"Total")) {
			cout << "RETURNING TOTAL" << endl;
			return TOTAL;
		} else if (strstr(text.c_str(),"Mean")) {
			cout << "RETURNING MEAN" << endl;
			return MEAN;
		} else if (strstr(text.c_str(),"Sigma")) {
			cout << "RETURNING SIGMA" << endl;
			return SIGMA;
		} else if (strstr(text.c_str(),"Base:")) {
			cout << "RETURNING BASE_TEXT" << endl;
			return BASE_TEXT;
		} else {
			regex_t a_regex;
			regcomp (&a_regex, "^[a-zA-Z_][a-zA-Z0-9_]*$", 0);
			regmatch_t p_match[5];
			int n_match=5;
			int regex_result = regexec (&a_regex, text.c_str(), n_match, p_match, 0);
			if (regex_result == 0) {
				// we got a match
				int how_many_matches = count_at_least_n_matches (p_match);
				if (how_many_matches == 1) {
				// this is the start of a new table 
					cout << "RETURNING NAME: " << text << endl;
					return NAME;
				} else {
					cout << "RETURNING TEXT" << text << endl;
					return TEXT;
				}
			} else {
				cout << "RETURNING TEXT" << text << endl;
				return TEXT;
			}
		}
	}

[_A-Za-z][A-Za-z0-9_]*	{
		if(yyleng < MY_STR_MAX) {
			strcpy(yylval.name,yytext);
            //cout << "got NAME:" << yytext << endl;
			return NAME;
		} else {
			printf("TEXT TOKEN too long... exiting lexer\n");
			exit(1);
		}
	}


\.     {
    //cout << "got DOT" << endl;
    //return DOT;
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

// 
int count_at_least_n_matches ( regmatch_t p_match[5])
{
	int n_matches = 0;
	for (int i= 0; i< 5; ++i) {
		if (p_match[i].rm_so != -1) {
			++ n_matches;
		}
	}
	return n_matches;
}

	/*
	int main ()
	{
		std::string fname ("T.CSV");
		FILE * yyin = fopen(fname.c_str(), "rb");
		yyrestart(yyin);
		int n_loops = 0;
		while (yylex()) {
			++ n_loops;
		}
		cout << "EXIT: " << n_loops << endl;
	}
	*/

