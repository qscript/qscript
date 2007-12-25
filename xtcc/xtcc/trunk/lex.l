/* tree.h
 *
 * grammar parse tree construction functions
 * Copyright (C) 2003,2004, 2005,2006,2007  Neil Xavier D'Souza <nxd_in@yahoo.com>
 * Postal MAil address
 * Neil Xavier D'Souza
 * 502, Premier Park
 * 1st Tank Lane,
 * Orlem, Malad(W),
 * Mumbai India. 400064.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * The Free Software Foundation, 
 * 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

%{
#define YY_NEVER_INTERACTIVE 1
#include <iostream>
#include "symtab.h"
#include "const_defs.h"
//#include "y.tab.h"
#include "type.h"
#include <math.h>
#include <string.h>
	void yyerror(char * s);
//	char * yytext;
	int line_no=1;
	extern int no_errors;
	using namespace std;
%}

%x comment
%option never-interactive

%%


	/* NxD: I shamelessly copied this out of flex's man page */	
"/*"         BEGIN(comment);

<comment>[^*\n]*        /* eat anything that's not a '*' */
<comment>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<comment>\n             ++line_no;
<comment>"*"+"/"        BEGIN(INITIAL);


\/\/.*	{
	// ignore Comment
}

void 	{
	yylval.dt=VOID_TYPE;
	return VOID_T;
}

int8_t		{ yylval.dt=INT8_TYPE;	       return INT8_T; }
int16_t		{ yylval.dt=INT16_TYPE;	       return INT16_T; }
int32_t		{ yylval.dt=INT32_TYPE;	       return INT32_T; }
float	{ yylval.dt=FLOAT_TYPE; return FLOAT_T; }
double { yylval.dt=DOUBLE_TYPE; return DOUBLE_T; }

for 	{
	return FOR;
}

fld 	{ return FLD;}

lista 	{
	return LISTA;
}

axstart {
	cout << "got token AXSTART" << endl;
	return AXSTART;
}
tab {
	return TAB;
}

tabstart {
	return TABSTART;
}

data_struct {
	return DATA_STRUCT;
}
rec_len {
	return REC_LEN;
}

ed_start {
	return ED_START;
}
ed_end {
	return ED_END;
}


ax	{
	//printf("\nreturned AX\n");
	return AX;
}

tot 	{
	//printf("lex: tot\n");
	return TOT;
}

cnt	{
	return CNT;
}

ttl	{
	return TTL;
}

c=	{
	//printf("Got COND_START\n");
	return COND_START;
}

"!"	{
	return NOT;
}

continue	{
	return CONTINUE;
}

break	{
	return BREAK;
}


"==" 	{
	return ISEQ;
}

"<="	{
	return LEQ;
}

">=" 	{
	return GEQ;
}

"!="	{
	return NOEQ;
}

")"	{
	return ')';
}

"("	{
	return '(';
}

"{"	{
	return '{';
}

"}"	{
	return '}';
}

";"	{
	return ';';
}

\"[^\"]*\"	{
		int len_text=strlen(yytext);
		if(len_text < MY_STR_MAX-1) {
			strcpy(yylval.text_buf, yytext);
		} else {
			printf("TEXT TOKEN too long... exiting lexer\n"); 
			exit(1);
		}
		return TEXT;
	}

'[1-8]+'	{
		unsigned int i; int tmp=0;
		for(i = 1; i < strlen(yytext)-1; i++){
			printf("%d=%c,", i, yytext[i]);
			tmp |= (1<<(yytext[i]-'0'-1));
		}
		printf("\n");
		yylval.code_list = tmp;
		printf("got a code_list: %s, tmp=%d\n", yytext, tmp);
		return CODELIST;
	}

[0-9]+	{
	yylval.ival = atoi(yytext);
	return INUMBER;
}

([0-9]*\.[0-9]+([eE][-+]?[0-9]+)?)	{
	yylval.dval = atof(yytext);
	printf("returned %g\n", yylval.dval);
	return FNUMBER;
	}

if	{
		return IF;
	}

else 	{
		return ELSE;
	}

conv	{ return CONVERT ; }

	/*
	c[0-9]+	{
			yylval.column_no = atoi(yytext+1);
			return SCOLUMN;
		}

	c	{
			return C;
		}
	*/

[ \t]+	; // eat whitespace

[\n]	{
	++line_no;
}

[A-Za-z_][A-Za-z0-9_]*	{
	yylval.name=strdup(yytext);
	return NAME;
	}

"$"	{ return 0;}


.	return yytext[0];

%%


	void yyerror(char * s){
		++no_errors;
	 	printf("%s: line: %d: yytext: %s\n", s, line_no, yytext  );
		printf("no_errors: %d\n", no_errors);
	}

	int yywrap(){
		return 1;
	}

	void flex_finish(){
		yy_delete_buffer(YY_CURRENT_BUFFER);
	}
