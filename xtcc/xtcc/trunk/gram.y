/*
 * The main grammar for the xtcc parser
 * Copyright (C) 2003,2004, 2005,2006,2007  Neil Xavier D'Souza <nxd_in@yahoo.com>
 * 502, Premier Park
 * 1st Tank Lane,
 * Orlem, Malad(W),
 * Mumbai 400064.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
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
#include "symtab.h"
#include <string.h>
#include <cstdlib>
#include "tree.h"
%}

%union {
	double dval;
	int ival;
	struct symtab *symp;
	struct expr * expr;
	struct stmt * stmt;
	int column_no;
	int code_list;
};

%token <symp> NAME
%token <dval> NUMBER
%token <column_no> SCOLUMN
%token <code_list> CODELIST
%token ';'
%token IF
%token ELSE
%token C
%token '['
%token ']'
%token '{' 
%token '}'
%token '('
%token ')'
%token '!'
%token INT
%token FLOAT


%right '='
%left LOGOR
%left LOGAND
%left ISEQ NOEQ 
%left LEQ GEQ '<' '>' 
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS

%type <expr> expression
%type <expr> mr_expr
%type <stmt> statement
%type <stmt> statement_list
%type <stmt> decl_statement


%%

start:	'{' statement_list '}'	{
	tree_root = $2;
	}

statement_list: statement  { printf(" got a statement\n"); 
		// later on reverse the chain
		$$ = $1;
	}
	| statement_list statement {
		$2->next_stmt = $1;
		$1->prev_stmt = $2;
		$$ = $2;
	}
	;

statement: NAME '=' expression ';' {
		//$1->value = $3; printf("%g\n", $3); 
		$$ = new_stmt();
		$$->symp = $1;
		$$->expr = $3;
		$$->type = 'A';
	}
	| expression ';' { 
		$$ = new_stmt();
		$$->expr = $1;
		$$->type = 'E';
		//printf("= %g\n", $1); 
	}
	| IF '(' expression ')'  statement 	{
		$$ = new_stmt();
		$$->if_stmt = new_if_stmt();
		$$->if_stmt->condition = $3;
		$$->if_stmt->if_body = $5;
		printf("constructing if_body: %x\n", $5);
		$$->if_stmt->else_body = NULL;
		$$->type = 'I';
	}
	| IF '(' expression ')'  statement ELSE  statement 	{
		$$ = new_stmt();
		$$->if_stmt = new_if_stmt();
		$$->if_stmt->condition = $3;
		$$->if_stmt->if_body = $5;
		$$->if_stmt->else_body = $7;
		$$->type = 'I';
	}
	|	'{' statement_list '}'	{ 
		$$ = new_stmt();
		$$ ->type = 'C';
		$$ ->c_stmt = $2;
	}
	|	decl_statement	{
		$$=$1;
	}
	;

decl_statement: INT NAME	';'	{
		$$=new_stmt();
		$$->type = 'D';
		$$->symp = $2;
		printf("got an int defn\n");
	}
	|	FLOAT NAME	';'	{
		$$=new_stmt();
		$$->type = 'F';
		$$->symp = $2;
		printf("got an float defn\n");
	}
	;

expression: expression '+' expression {
		$$ = new_expr();
		$$->l_op=$1 ; $$->r_op=$3; 
		$$->type = '+';
		printf("got an '+' expr\n"); 
	}
	|	expression '-' expression {
		$$ = new_expr();
		$$->l_op= $1;
		$$->r_op= $3; 
		$$->type='-';
	}
	|	expression '*' expression { 
		$$ = new_expr();
		$$->l_op = $1;
		$$->r_op = $3;
		$$->type = '*';
	}
	|	expression '/' expression {
			$$ = new_expr();
			$$->l_op = $1;
			$$->r_op = $3;
			$$->type = '/';
	}
	|	'-' expression %prec UMINUS {
			$$ = new_expr();
			$$->l_op = $2;
			$$->type = 'U';
	}
	| 	'(' expression ')'	{ 
		$$ = $2;
		$$ = new_expr();
		$$->l_op = $2;
		$$->type = 'P';
	}
	|	expression '<' expression {
			$$ = new_expr();
			$$->l_op = $1;
			$$->r_op = $3;
			$$->type = '<';
	}
	|	expression '>' expression {
			$$ = new_expr();
			$$->l_op = $1;
			$$->r_op = $3;
			$$->type = '>';
	}
	|	expression LEQ expression {
			$$ = new_expr();
			$$->l_op = $1;
			$$->r_op = $3;
			$$->type = LEQ;
	}
	|	expression GEQ expression {
			$$ = new_expr();
			$$->l_op = $1;
			$$->r_op = $3;
			$$->type = GEQ;
	}
	|	expression ISEQ expression {
			$$ = new_expr();
			$$->l_op = $1;
			$$->r_op = $3;
			$$->type = ISEQ;
	}
	|	expression NOEQ expression {
			$$ = new_expr();
			$$->l_op = $1;
			$$->r_op = $3;
			$$->type = ISEQ;
	}	
	| expression LOGOR expression {
			$$ = new_expr();
			$$->l_op = $1;
			$$->r_op = $3;
			$$->type = LOGOR;
	}	
	| expression LOGAND expression {
			$$ = new_expr();
			$$->l_op = $1;
			$$->r_op = $3;
			$$->type = LOGAND;
	}
	|	NUMBER	{
			$$ = new_expr();
			$$->l_op = NULL;
			$$->type = 'L';
			$$->sem_value = $1;
	}
	|	NAME		{
			$$ = new_expr();
			$$->symp = $1; 
			$$->type = 'I';
	}
	|	mr_expr
	;

mr_expr:	SCOLUMN	{
		$$ = new_expr();
		$$->column_no = $1; /* column_no */
		$$->type = 'M';
		$$->mr_type = 0;
	}
	|	SCOLUMN CODELIST {
		$$ = new_expr();
		$$->column_no = $1;
		$$->code_list = $2;
		$$->type = 'M';
		$$->mr_type = 1;
	}
	|	C '[' NUMBER ',' NUMBER ']' {
		$$ = new_expr();
		$$->column_no = $3;
		$$->column_no_2 = $5;
		$$->mr_type = 2;
		$$->type = 'M';
	}
	;


%%

	struct stmt * tree_root;

	struct symtab_ent * symlook( char * s){
		struct symtab_ent *sp;
		printf("entered func: symlook\n");
		for (sp = symtab.sym_entry[0]; sp < symtab.sym_counter; ++sp){
			if (sp->name && !strcmp(sp->name, s))
				return sp;
			
		}
		if( sym_counter==NSYMS-1){
			cerr << "Symbol table full\n";
			return NULL;
		}
		if (!sp->name){
			sp->name = strdup(s);
			return sp;
		}
		yyerror("Too many symbols");
		exit(1);
	}

	int yyerror(char * s){
	 	return printf("%s\n", s);
	}
#include <stdio.h>
void print_stmt_lst( struct stmt * st);
void print_expr(FILE* edit_out, struct expr * e);
void print_if_stmt(FILE* edit_out, struct if_stmt * if_stmt);

	int main(){
		tree_root = NULL;
		yyparse();
		printf("%x\n", tree_root);
		print_stmt_lst(tree_root);
		return 0;
	}
#include <stdlib.h>
#include <stdio.h>

void print_stmt_lst(struct stmt * st){
	/* I may have to parametrize this later */
	static FILE * edit_out=NULL;
	struct stmt* st_ptr=st;

	if(edit_out==NULL){
		edit_out=fopen("edit_out.ndg", "w+b");
		if(edit_out==NULL){
			printf("could not open edit_out.ndg for writing\n");
			exit(1);
		}
	}

	if ( st == NULL ){
		fprintf(edit_out,"/*print_stmt_lst: empty stmt ... returning*/\n");
		return;
	}
#if DEBUG
	fprintf(edit_out,"/* print_stmt_lst: printing type '%c'*/\n", st->type);
#endif /* DEBUG */
	/* New in version 0.2
	   */
	while ( st_ptr->next_stmt) st_ptr=st_ptr->next_stmt;
	while( st_ptr){
		switch(st_ptr->type){
		case 'C':
			fprintf(edit_out,"{\n");
#if DEBUG
			fprintf(edit_out,"/*printing compound statement*/\n");
#endif /* DEBUG */
			print_stmt_lst(st_ptr->c_stmt);
			fprintf(edit_out,"}\n");
			break;
		case 'E':
#if DEBUG
			fprintf(edit_out,"/*printing expr statement*/\n");
#endif /* DEBUG */
			print_expr(edit_out, st_ptr->expr);
#if 0
			do {
				print_expr(edit_out, st_ptr->expr);
				fprintf(edit_out,";\n");
				st_ptr=st_ptr->next_stmt;
			} while (st_ptr);
#endif /* 0 */
			fprintf(edit_out,";\n");
			break;
		case 'I':
			print_if_stmt(edit_out, st_ptr->if_stmt);
			break;
		case 'A':
#if DEBUG
			fprintf(edit_out,"/*assignment stmt */\n");
#endif /* DEBUG */
			fprintf(edit_out,"%s=", st_ptr->symp->name);
			print_expr(edit_out, st_ptr->expr);
			fprintf(edit_out,";\n");
			break;
		case 'D':
#if DEBUG
			fprintf(edit_out,"int %s;\n", st_ptr->symp->name);
#endif /* DEBUG */
		break;
		case 'F':
			fprintf(edit_out,"float %s;\n", st_ptr->symp->name);
		break;
		default:
			fprintf(edit_out,"/*Unhandled statement type: Report bug to NxD_in@yahoo.com*/\n");
		}
		if(st_ptr)
			st_ptr=st_ptr->prev_stmt;
#if DEBUG
		fprintf(edit_out,"/*stmt printed*/\n");
#endif /* DEBUG */
	}
}

void print_expr(FILE* edit_out, struct expr * e){
	if(e) {
		switch(e->type){

			case '+':
			case '-':
			case '*':
			case '/':
			case '<':
			case '>':
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %c ", e->type);
				print_expr(edit_out, e->r_op);
			break;
			// fprintf(edit_out, "EXPR: Type: %c: line: %d\n", 
			// e->type, e->line_number);

			case LEQ:
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " <= ", e->type);
				print_expr(edit_out, e->r_op);
			break;

			case GEQ:
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " >= ", e->type);
				print_expr(edit_out, e->r_op);
			break;

			case ISEQ:
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " == ", e->type);
				print_expr(edit_out, e->r_op);
			break;

			case 'P':
				fprintf(edit_out, "(");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, ")");
			break;

			case 'L':
				fprintf(edit_out, "%d ", e->sem_value);
			break;

			case 'I':
				fprintf(edit_out, "%s ", e->symp->name);
			break;

			case 'U':
				fprintf(edit_out, "- ");
				print_expr(edit_out, e->l_op);
			break;

			case 'M':
#if DEBUG
				fprintf(edit_out, "/* MR expr */\n");
#endif /* DEBUG */
				switch(e->mr_type){

				case 0:
					//fprintf(edit_out, "c%d ", e->column_no);
					fprintf(edit_out, "c[%d] ", e->column_no);
				break;

				case 1:{
					//fprintf(edit_out, "c%d '%x'", e->column_no,
					//	e->code_list);
					int t = e->code_list;
					fprintf(edit_out, "(");
					for(;t%10;){
						if(t>10) {
							fprintf(edit_out, "c[%d] & %d||",
							e->column_no,
							t%10);
						} else {
							fprintf(edit_out, "c[%d] & %d",
							e->column_no,
							t);
						}
						t=t/10;
					}
					fprintf(edit_out, ")");
				}
				break;

				case 2:
					//fprintf(edit_out, "c[%d,%d]", e->column_no,
					//	e->column_no_2);
					fprintf(edit_out, "strntol(&c[%d], %d, %d)",
						e->column_no, 
						e->column_no_2 - e->column_no,
						10);
				break;

				default:
					fprintf(edit_out, "Unhandled MR expression\n");
				}
			break;

			default:
				fprintf(edit_out, "Unhandled expression type: %c\n", 
					e->type);
		}
	}
}

#if 1
void print_if_stmt(FILE* edit_out, struct if_stmt * if_stmt){
#if DEBUG
	fprintf(edit_out, "/*printing if_stmt: */\n");
#endif /* DEBUG */
	fprintf(edit_out, " if ( ");
	print_expr(edit_out, if_stmt->condition);
	fprintf(edit_out, " ) ");
//#if DEBUG
	fprintf(edit_out, "/* if_body: %x */\n", if_stmt->if_body);
//#endif /* DEBUG */
	//fprintf(edit_out, "{\n");
	print_stmt_lst(if_stmt->if_body);
	//fprintf(edit_out, "}\n");
	if (if_stmt->else_body ){
		fprintf(edit_out, " else ");
#if DEBUG
		fprintf(edit_out, "/* else_body type: '%c'*/\n", if_stmt->else_body->type);
#endif /* DEBUG */
		print_stmt_lst(if_stmt->else_body);
		//fprintf(edit_out, "}\n");
	}
}
#endif /* 0 */
