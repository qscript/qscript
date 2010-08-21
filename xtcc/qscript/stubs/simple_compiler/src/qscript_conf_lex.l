
%{
#include "const_defs.h"
#include "qscript_conf.hpp"
#include "config_parser.h"
%}

%option prefix="qscript_conf"

%x comment

%%

#.*		; // ingore comment - single line
"/*"         BEGIN(comment);
<comment>[^*\n]*        /* eat anything that's not a '*' */
<comment>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<comment>\n             ++config_file_parser::line_no;
<comment>"*"+"/"        BEGIN(INITIAL);
\/\/.*	{
	// ignore Comment
}

[ \t]+	; /* ignore */
\n	{ ++config_file_parser::line_no; }

NCURSES_INCLUDE_DIR	{ return NCURSES_INCLUDE_DIR; }
NCURSES_LIB_DIR	{ return NCURSES_LIB_DIR; }
NCURSES_LINK_LIBRARY_NAME  { return NCURSES_LINK_LIBRARY_NAME; }
PLATFORM { return PLATFORM; }

[0-9]+	{
	qscript_conflval.ival = atoi(yytext);
	return INUMBER;
}

\"[^\"]*\"      {
	int len_text=strlen(yytext);
	qscript_conftext[len_text-1]='\0';
	if(yyleng < MY_STR_MAX-1) {
		strcpy(qscript_conflval.text_buf, qscript_conftext+1);
	} else {
		printf("TEXT TOKEN too long... exiting lexer\n");
		exit(1);
	}
	return TEXT;
}

.	return qscript_conftext[0];

%%

#include <cstdio>
void qscript_conferror(const char * s)
{
	++config_file_parser::no_errors;
	 	printf("%s: line: %d: qscript_conftext: %s\n", s
				, config_file_parser::line_no
				, qscript_conftext  );
		printf("no_errors: %d\n", config_file_parser::no_errors);
}

int qscript_confwrap()
{
	return 1;
}
