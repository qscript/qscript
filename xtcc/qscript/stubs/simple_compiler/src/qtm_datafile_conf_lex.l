%{
#include "qtm_datafile_conf_parser.h"
#include "qtm_datafile_conf.hpp"
%}

%option prefix="qtm_datafile_conf_"
%option noyywrap
%option never-interactive

%x comment

%%


#.*		; // ingore comment - single line
"/*"         BEGIN(comment);
<comment>[^*\n]*        /* eat anything that's not a '*' */
<comment>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<comment>\n             ++qtm_datafile_conf_parser_ns::line_no;
<comment>"*"+"/"        BEGIN(INITIAL);

\/\/.*	{
	// ignore Comment
}

[ \t\r]+	; /* ignore */
\n	{ ++qtm_datafile_conf_parser_ns::line_no; }

[1-9][0-9]*	{
	qtm_datafile_conf_lval.ival = atoi(yytext);
	return INUMBER;
}

CARD_NO_COLS {
	return CARD_NO_COLS;
}

SER_NO_COLS {
	return SER_NO_COLS;
}

AUTO	{
	return AUTO;
}

DATA_START_COL_NO {
	return DATA_START_COL_NO;
}

DATA_END_COL_NO {
	return DATA_END_COL_NO;
}

READ_EQ 	{
	return READ_EQ;
}

.	{ //std::cerr << "returning " << qscript_conftext[0] << std::endl; 
	return qtm_datafile_conf_text[0]; 
}

%%



void qtm_datafile_conf_error(const char * s)
{
	++qtm_datafile_conf_parser_ns::no_errors;
	printf("%s: line: %d: qtm_datafile_conf_text: %s\n", s
			, qtm_datafile_conf_parser_ns::line_no
			, qtm_datafile_conf_text);
	printf("no_errors: %d\n", qtm_datafile_conf_parser_ns::no_errors);
}
