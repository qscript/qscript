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

%left ','
%right '='
%left LOGOR
%left LOGAND
%left ISEQ NOEQ 
%left LE GE '<' '>' 
%left '-' '+'
%left '*' '/' '%'
%nonassoc NOT
%nonassoc UMINUS
%nonassoc IN COUNT
%nonassoc FUNC_CALL


%%

prog:stmt_list
	;

stmt_list: stmt
	| stmt_list stmt
	;
	
stmt: ques
	| expr ';'
	| IF '(' expr ')' stmt 
	| IF '(' expr ')' stmt ELSE stmt
	| cmpd_stmt
	;

cmpd_stmt: '{' stmt_list '}'
	;
ques: NAME TEXT qtype datatype range_allowed_values';'

qtype: SP
	| MP '(' INUMBER ')'
	;

datatype: INT8_T
	|INT16_T
	|INT32_T  	
	|FLOAT_T
	|DOUBLE_T
	;

range_allowed_values: NAME
	| '(' number_range_list ')'
	;

number_range_list: number_range
	| number_range_list ',' number_range
	;

number_range: INUMBER '-' INUMBER
	| INUMBER 
	;

expr	: 	expr '>' expr
	|	expr '<' expr
	|	expr LE expr
	|	expr GE expr
	|	expr ISEQ expr
	|	expr NOEQ expr
	|	expr LOGAND expr
	|	expr LOGOR expr
	|	NOT expr
	|	INUMBER
	|	FNUMBER
	|	NAME
	|	q_expr
	;

q_expr: 	NAME IN range_allowed_values
	| 	COUNT '(' NAME ')'
	;


%%

int main(){
	return yyparse(); 
}
