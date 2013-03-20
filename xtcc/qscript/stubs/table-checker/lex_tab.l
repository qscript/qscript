%{

#include <map>
#include <string>
#include <cstring>
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


    YYSTYPE qtm_table_output_lval;

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
	int qtm_line_no;
	int count_at_least_n_matches ( regmatch_t p_match[5]);
	void qtm_table_output_error(const char * s);
	string stub_text;


%}


%option prefix="qtm_table_output_"
%option never-interactive
    /*%option nounistd
    %option outfile="lex_tab.c" header-file="lex_tab.h" */

DIGIT    [0-9]
        /*ID       [a-z][a-z0-9]*/

%%

[\t]+	{
    /* ignore */
}

[ \r\t]+	{ /* ignore */
}


,\"\" {
	cout << "RETURNING  EMPTY_LINE_1_COLS" << endl;
	return EMPTY_LINE_1_COLS;
}

,\"Total\"	{
	cout << "RETURNING  BAN_TOTAL" << endl;
	return BAN_TOTAL;
}

\"Total\",{DIGIT}+	{
	string side_total_str(yytext + 8);
	int side_total = atoi (side_total_str.c_str());
	cout << "RETURNING  SIDE_TOTAL:"
		<< "side_total_str:" << side_total_str << ", "
		<< "side_total: " <<side_total << endl;
	qtm_table_output_lval.ival = side_total;
	return SIDE_TOTAL;
}

\"\",\"\"	{
	cout << "RETURNING EMPTY_LINE_2_COLS" << endl;
	return EMPTY_LINE_2_COLS;
}

	/*\"\",{DIGIT}+\.{DIGIT}+      */
\"\",{DIGIT}+.{DIGIT}+ {
	char * pos_2nd_dbl_quote = strrchr (yytext, '"');
	if (pos_2nd_dbl_quote) {
		string no (pos_2nd_dbl_quote + 2);
		double perc = atof (no.c_str());
		cout << "PERC: " << perc << endl;
		qtm_table_output_lval.dval = perc;
	} else {
		cerr << __LINE__
			<< ", "
			<< __FILE__
			<< ", "
			<< __PRETTY_FUNCTION__
			<< "Impossible ! lex condition is that there should be 2 quotes"
			<< endl;
	}
        cout << "got STUB_PERC " << yytext << endl;
	return STUB_PERC;
}

\"Mean\",{DIGIT}+.{DIGIT}+  {
	string mean_str(yytext + 7);
	double mean = atof (mean_str.c_str());
	cout	<< "RETURNING  MEAN:"
		<< "mean_str:" << mean_str << ", "
		<< "mean: " << mean << endl;
	qtm_table_output_lval.dval = mean;
	return STUB_MEAN;
}

\"Std.Dev\",{DIGIT}+.{DIGIT}+  {
	string stddev_str(yytext + 10);
	double stddev = atof (stddev_str.c_str());
	cout	<< "RETURNING  MEAN:"
		<< "stddev_str:" << stddev_str << ", "
		<< "stddev: " << stddev << endl;
	qtm_table_output_lval.dval = stddev;
	return STUB_STD_DEV;
}

\"[^\"]*\",{DIGIT}+	{
	char * pos_2nd_dbl_quote = strrchr (yytext, '"');
	string no (pos_2nd_dbl_quote + 2);
	if (pos_2nd_dbl_quote) {
		string tmp = yytext;
		int pos_2nd_dbl_quote_int = tmp.rfind ('"');
		stub_text = tmp.substr (1, pos_2nd_dbl_quote_int-1);
		no = (pos_2nd_dbl_quote + 2);
	} else {
		cerr << __LINE__
			<< ", "
			<< __FILE__
			<< ", "
			<< __PRETTY_FUNCTION__
			<< "Impossible ! lex condition is that there should be 2 quotes"
			<< endl;
			exit(1);
	}
	//cout << "got STUB_FREQ: " << yytext << endl;
	if (strstr (yytext, "Sigma")) {
		double sigma = atof (no.c_str());
		qtm_table_output_lval.dval = sigma;
		cout << "SIGMA: " << "stub_text: "<< stub_text << " | " << sigma << endl;
		return SIGMA;
	} else {
		int freq = atoi (no.c_str());
		qtm_table_output_lval.ival = freq;
		cout << "STUB_FREQ: " << "stub_text: "<< stub_text << " | " << freq << endl;
		return STUB_FREQ;
	}
}


","   {
    //cout << "got COMMA" << endl;
    return COMMA;
}

\n  {
    ++qtm_line_no;
	//cout << "got a NEWL: qtm_line_no: "  << qtm_line_no << endl;
	return NEWL;
}

([0-9]*\.[0-9]+([eE][-+]?[0-9]+)?)	{
		qtm_table_output_lval.dval = atof(yytext);
		cout << "got FNUMBER " << qtm_table_output_lval.dval << endl;
		return FNUMBER;
	}

{DIGIT}+	{
		qtm_table_output_lval.ival = atoi(yytext);
		cout << "got INUMBER " << qtm_table_output_lval.ival << endl;
		return INUMBER;
	}


\"[A-Za-z_][A-Za-z0-9_]*,[a-zA-Z_][a-zA-Z0-9_]*,[0-9]+\" {
		int len_text = qtm_table_output_leng;
		yytext[len_text-1]='\0'; // clobber double quote
		if(qtm_table_output_leng < MY_STR_MAX-1) {
			strcpy(qtm_table_output_lval.text_buf, yytext+1);
		} else {
			printf("TEXT TOKEN too long... exiting lexer\n");
			exit(1);
		}
        cout << "RETURNING TABLE_INFO" << endl;
    return TABLE_INFO;
    }

\"[A-Za-z_][A-Za-z0-9_]*,[a-zA-Z_][a-zA-Z0-9_]*,[0-9]+,[A-Za-z_][A-Za-z0-9_]*\" {
		int len_text = qtm_table_output_leng;
		yytext[len_text-1]='\0'; // clobber double quote
		if(qtm_table_output_leng < MY_STR_MAX-1) {
			strcpy(qtm_table_output_lval.text_buf, yytext+1);
		} else {
			printf("TEXT TOKEN too long... exiting lexer\n");
			exit(1);
		}
        cout << "RETURNING TABLE_INFO" << endl;
    return TABLE_INFO2;
    }

\"[^\"]*\"      {
		//int len_text=strlen(yytext);
		int len_text = qtm_table_output_leng;
		yytext[len_text-1]='\0'; // clobber double quote
		if(qtm_table_output_leng < MY_STR_MAX-1) {
			strcpy(qtm_table_output_lval.text_buf, yytext+1);
		} else {
			printf("TEXT TOKEN too long... exiting lexer\n");
			exit(1);
		}
		string text(qtm_table_output_lval.text_buf);
		if (strstr(text.c_str(), "#page")) {
			//cout << "RETURNING PAGE" << endl;
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
            /*
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
            */
			return TEXT;
		}
	}

[_A-Za-z][A-Za-z0-9_]*	{
		if(qtm_table_output_leng < MY_STR_MAX) {
			strncpy(qtm_table_output_lval.name,yytext+1, qtm_table_output_leng-1);
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


	//void yyerror(const char * s)
	void qtm_table_output_error(const char * s)
	{
		//fprintf(stderr, "reached here: %s\n", __PRETTY_FUNCTION__);
		//using qscript_parser::no_errors;
		//using qscript_parser::qtm_line_no;
		//++no_errors;
	 	printf("%s: line: %d: yytext: %s\n", s, qtm_line_no, yytext);
	 	printf("line: %d: \n", qtm_line_no);
		//printf ("lexical error: line: %d, column: %d\n"
		//	, lex_location.lineNo_
		//	, lex_location.columnNo_);
		//printf ("%s\n", lex_location.currentLine_.str().c_str());
		//printf ("%*s\n%*s\ntoken: %s\n", lex_location.columnNo_, "^"
		//		    , lex_location.columnNo_, s, yytext);
	}


//int yywrap()
int qtm_table_output_wrap()
{
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

