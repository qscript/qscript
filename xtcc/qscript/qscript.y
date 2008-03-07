%{
#include "const_defs.h"
#include "qscript_types.h"
	extern char * yytext;
	int no_errors=0;
	int no_warn=0;
	extern int line_no;
	int yylex();
	void yyerror(char * s);
%}

%union {
	double dval;
	int ival ;
	char name[MY_STR_MAX];
	char text_buf[MY_STR_MAX];
	datatype dt;
};


%token IF ELSE
%token <dval> FNUMBER
%token <ival> INUMBER
%token NAME
%token QTEXT
%token SP
%token MP
%token TEXT
%token <dt> INT8_T
%token <dt> INT16_T
%token <dt> INT32_T
%token <dt> FLOAT_T
%token <dt> DOUBLE_T


%%

prog: qlist
	;
	
qlist: ques
	| qlist ques
	;

ques: NAME TEXT qtype datatype ';'

qtype: SP
	| MP '(' INUMBER ')'
	;

datatype: INT8_T
	|INT16_T
	|INT32_T  	
	|FLOAT_T
	|DOUBLE_T
	;

%%

int main(){
	return yyparse(); 
}
