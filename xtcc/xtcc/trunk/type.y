/*
 * The main grammar for the xtcc parser
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
#include "const_defs.h"
#include "symtab.h"
#include "tree.h"
#include "stmt.h"
#include "Tab.h"
#include <cstring>
#include <iostream>
#include <vector>
#include "scope.h"
#include <map>
#include <sys/types.h>
#include <limits.h>

	using namespace std;

//	struct symtab symtab;
	using namespace std;
	int no_errors=0;
	int no_warn=0;
	int yylex();
	void yyerror(char * s);
	extern int line_no;
	extern char * yytext;
	bool check_type_compat(datatype typ1, datatype typ2);
	vector <func_info*> func_info_table;
	int check_parameters(struct expr* e, struct var_list* v);
	vector <scope*> active_scope_list;
	scope* active_scope;
	map<string, symtab_ent*>::iterator find_in_symtab(string id);
	//struct stmt * load_func_into_symbol_table( char * & name,  struct var_list* & v_list, datatype int_type);
	bool skip_func_type_check(const char * fname);
	void	add_func_params_to_cmpd_sc(struct scope * & sc, struct var_list * & v_list, string & fname);
	int search_for_func(string& search_for);
	int check_func_decl_with_func_defn(struct var_list*& v_list, int & index, string func_name);
	struct stmt* make_func_defn_stmt( struct scope *& sc,
		struct var_list * & v_list,
		struct stmt* & func_body,
		string search_for,
		datatype return_type
		);
	struct stmt * tree_root=NULL;
	bool 	void_check( datatype & type1, datatype & type2, datatype& result_type);
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);

	int flag_cmpd_stmt_is_a_func_body=-1;
//	scope * tmp_storage=NULL;
//int	load_func_param_into_scope(tmp_storage, v_list);
	int lookup_func(string func_name_index);
	//extern vector<table*>	table_list;
	//extern map <string, ax*> ax_map;
	vector<table*>	table_list;
	map <string, ax*> ax_map;

	int no_count_ax_elems=0;
	int no_tot_ax_elems=0;
	int in_a_loop=0;
	int nest_lev=0;
	int rec_len;


	noun_list_type noun_list[]= {
			{	"void"	, VOID_TYPE},
			{	"u_int8_t" ,U_INT8_TYPE},
			{	"int8_t" ,INT8_TYPE},
			{	"u_int16_t",U_INT16_TYPE},
			{	"int16_t" ,INT16_TYPE},
			{	"u_int32_t",U_INT32_TYPE},
			{	"int32_t" ,INT32_TYPE},
			{	"float", FLOAT_TYPE},
			{	"double", DOUBLE_TYPE}
		};

%}

%union {
	double dval;
	int ival ;
	struct symtab *symp;
	char * name;
	struct expr * expr;
	struct stmt * stmt;
	struct cmpd_stmt * c_stmt;
	int column_no;
	int code_list;
	char text_buf[MY_STR_MAX];
	struct var_list * v_list;
	datatype dt;
	struct ax * ax;
	struct table * tbl;
	class basic_ax_stmt * basic_ax_stmt;
};

%token	TOT AX ';' CNT '{' '}' TTL
%type <dt> xtcc_type
%type <tbl> tab_list
%type <tbl> tab_defn
%type <v_list> var_decl
%type <v_list> decl_comma_list
%type <expr> expression
%type <expr> expr_list
%type <stmt> top_level_item_list
%type <stmt> prog
%type <stmt> statement
%type <stmt> statement_list
%type <stmt> list_stmt
// %type <stmt> decl_list
%type <stmt> decl
%type <stmt> func_decl	
%type <c_stmt> compound_stmt	
%type <c_stmt> open_curly	
%type <stmt> top_level_item 
%type <stmt> func_defn 
%type <stmt> if_stmt 
%token  FOR
%token <text_buf> TEXT
%token <name> NAME
%token <dval> FNUMBER
%token <ival> INUMBER
//%token <column_no> SCOLUMN
%token <code_list> CODELIST
%token ';'
%token LISTA
%token IF
%token ELSE
%token '['
%token ']'
%token '{' 
%token '}'
%token '('
%token ')'
%token '!'
 /*%token <dt> INT*/
 /*%token <dt> CHAR*/
%token <dt> VOID_T
%token <dt> U_INT8_T
%token <dt> INT8_T
%token <dt> U_INT16_T
%token <dt> INT16_T
%token <dt> U_INT32_T
%token <dt> INT32_T
%token <dt> FLOAT_T
%token <dt> DOUBLE_T

%token AXSTART
%token TABSTART
%token ED_START
%token DATA_STRUCT
%token REC_LEN
%token ED_END
%token TAB
%token COND_START
%type <ax>	ax_list
%type <ax>	ax_defn
%type <basic_ax_stmt> ax_stmt_list
%type <basic_ax_stmt> ax_stmt

%token CONTINUE BREAK


%left ','
%right '='
%left LOGOR
%left LOGAND
%left ISEQ NOEQ 
%left LEQ GEQ '<' '>' 
%left '-' '+'
%left '*' '/' '%'
%nonassoc NOT
%nonassoc UMINUS
%nonassoc FUNC_CALL

%%

prog: DATA_STRUCT ';' REC_LEN '=' INUMBER ';' {	char * c_arr="c";  rec_len=$5; active_scope->insert(c_arr, INT8_ARR_TYPE, rec_len, 0);} ED_START top_level_item_list ED_END {


	//while ( st_ptr->next) st_ptr=st_ptr->next;
	//while ( $1->next) $1=$1->next;
	tree_root = trav_chain($9);
	return 0;
}
	| AXSTART '{' ax_list 	'}'	{
#if DEBUG_GRAM
		cout << "got axes\n";
#endif /* DEBUG_GRAM */
		return 0;
	}
	| TABSTART '{' tab_list '}' {
#if DEBUG_GRAM
		printf("got TABSTART\n");
#endif /* DEBUG_GRAM */
		return 0;
	}
	;

top_level_item_list: top_level_item {
		$$=$1;
	}
	| top_level_item_list top_level_item {
		$$=link_chain($1,$2);
	}
	;

top_level_item: decl
	| func_defn
	;

xtcc_type: VOID_T
	|U_INT8_T
	|INT8_T
	|U_INT16_T
	|INT16_T
	|U_INT32_T
	|INT32_T  	
	|FLOAT_T
	|DOUBLE_T
	;


func_defn:	xtcc_type NAME '(' decl_comma_list ')' {
			string func_name_index($2);
			flag_cmpd_stmt_is_a_func_body=lookup_func(func_name_index);
			if(flag_cmpd_stmt_is_a_func_body==-1){
				++ no_errors;
				cerr << "Function name not found in list of declared functions: "
					<< "You will see another error on this same function name: " << func_name_index
					<< "line_no: " << line_no ;
			}
		} compound_stmt {
		cout << "parsed to INT function defn" << endl;
		//struct cmpd_stmt* c_stmt=dynamic_cast <struct cmpd_stmt*> ($7);
		struct cmpd_stmt* c_stmt= $7;
		struct scope *sc=c_stmt->sc;
		struct var_list * v_list=trav_chain($4);
		struct stmt* func_body=$7;
		string search_for=$2;
		datatype return_type=$1;
		$$=new func_stmt(func_defn, line_no, sc, v_list, func_body, search_for, return_type);
	}
	;


decl:	xtcc_type NAME ';'{
		//cout << "creating simple var of type: " << $1 << endl;
		$$ = active_scope->insert($2, $1, line_no);
	} 
	|	xtcc_type NAME '[' INUMBER ']' ';' {
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		//cout << "creating arr var of type: " << $1 << endl;
		datatype dt=datatype(U_INT8_ARR_TYPE+($1-U_INT8_TYPE));
		$$ = active_scope->insert($2, dt, $4, line_no);
	}
	/*
	NxD I only want to allow references in function parameter lists 
	|	xtcc_type '&' NAME {
		cout << "creating ref var of type: " << $1 << endl;
		datatype dt=datatype(U_INT8_REF_TYPE+($1-U_INT8_TYPE));
		$$ = active_scope->insert($3, dt, line_no);
	}
	*/
	| func_decl	{
		$$=$1;
	}
	;


func_decl:	xtcc_type NAME '(' decl_comma_list ')' ';'{
		char *name=strdup($2);
		struct var_list* tmp=$4;
		while(tmp ) {
			//cout << "func_decl: traversing param list: " << tmp->var_name << endl;
			tmp=tmp->next;
		}
		struct var_list* v_list=trav_chain($4);
		tmp=v_list;
		while(tmp ) {
			//cout << "func_decl after reversing chain: traversing param list: " << tmp->var_name << endl;
			tmp=tmp->prev;
		}
		datatype return_type=$1;
		$$=new func_decl_stmt( func_type, line_no, name,  v_list, return_type);
	}
	;


decl_comma_list: var_decl	{
		 $$=$1;
		 cout << "got decl_comma_list : " << endl;
	}
	| decl_comma_list ',' var_decl {
		$$=link_chain($1,$3);
		//cout << "chaining var_decl : " << endl;
	}
	;


var_decl:	xtcc_type NAME 	{
		//cout << "creating simple var of type: " << $1 << endl;
		$$=new var_list($1, $2);
	}
	| xtcc_type NAME '[' INUMBER ']'  {
		/* Neil - I need to fix this */
		//cout << "creating arr var of type: " << $1 << endl;
		datatype dt=datatype(U_INT8_ARR_TYPE+($1-U_INT8_TYPE));
		$$=new var_list(dt, $2, $4);
	}
	|	xtcc_type '&' NAME {
		//cout << "creating ref var of type: " << $1 << endl;
		datatype dt=datatype(U_INT8_REF_TYPE+($1-U_INT8_TYPE));
		$$=new var_list(dt, $3);
	}
	|	/* empty */
		{
		//$$=new var_list(uninit, "empty");
		$$=0;
		}
	;

statement_list: statement {$$=$1; }
	|	statement_list statement {
		$$=link_chain($1,$2);
	}
	;

statement: FOR '(' expression ';' expression ';' expression ')' { ++in_a_loop;} statement {
		   $$ = new struct for_stmt(for_stmt, line_no, $3, $5, $7, $10);
		   cout << "finished parsing FOR" << endl;
		   --in_a_loop;
	   }
	| if_stmt
	| expression ';'{ 
		if($1->isvalid()){
			$$ = new expr_stmt(texpr_stmt, line_no, $1);
		} else {
			$$ = new expr_stmt(error_type, line_no, $1);
		}
		//printf("= %g\n", $1); 
	}
	| NAME '=' NAME '[' expression ',' expression ']' ';' {
		struct symtab_ent* lse=NULL;
		struct symtab_ent* se=NULL;
		map<string,symtab_ent*>::iterator sym_it1 = find_in_symtab($1);
		map<string,symtab_ent*>::iterator sym_it2 = find_in_symtab($3);
		if( sym_it1==active_scope->sym_tab.end()) {
			cerr << "Not able to find :" << $1 << " in symbol table: line_no" 
				<< line_no
				<< endl;
			++no_errors;
		} else {
			lse=sym_it1->second;
		}
		if( sym_it2==active_scope->sym_tab.end()) {
			cerr << "Not able to find :" << $3 << " in symbol table: line_no:" 
				<< line_no
				<< endl;
			++no_errors;
		} else {
			se=sym_it2->second;
		}
		if( !(se&&lse)){
			cerr << "Error: could not find " <<endl;
			if(!se){
				cerr << "RHS: " << $3 ;
				++no_errors;
			}
			if(!lse ){
				cerr << "LHS: " << $1;
				++no_errors;
			}
			if (!(se&&lse)) 
				cerr << "  in symbol table: lineno: " << line_no << endl;
			$$=new struct err_stmt(line_no);
		} else if(!(lse->get_type()==INT32_TYPE || lse->get_type()==FLOAT_TYPE)){
			cerr << "ERROR: LHS:  " << $1 << ":line_no:" << line_no 
				<< " should be of type float or int"
				<< endl;
			cerr << "lse type: " << lse->get_type() << endl;
			++no_errors;
			$$=new struct err_stmt(line_no);
		} else {
			
			datatype e_type1=$5->get_type();
			datatype e_type2=$7->get_type();
			if( (e_type1>=U_INT8_TYPE && e_type1 <=INT32_TYPE) && 
					(e_type2>=U_INT8_TYPE && e_type2<=INT32_TYPE)){
				datatype d1=arr_deref_type(se->get_type());
				if(d1==INT8_TYPE){
					$$ = new blk_arr_assgn_stmt(assgn_stmt, line_no, lse, se,$5,$7);
				} else {
					$$=new struct err_stmt(line_no);
					cerr << "Type Error:  x: lineno: " << line_no << "\n";
					++no_errors;
				}
			} else {
				$$=new struct err_stmt(line_no);
				cerr << "ERROR: NAME  =NAME[EXPR, EXPR] EXPR should be of type int or char: lineno: " 
					<< line_no << "\n";
				++no_errors;
			}
		}
	}
	|	compound_stmt {
		$$=$1;
	}
	|	decl {
		$$=$1;
	}
	|	list_stmt
	|	BREAK ';'{
		$$=new struct break_stmt(break_stmt, line_no);
		if (!in_a_loop){
			cerr << "break statement outside a loop: line_no: " << line_no<< endl;
			++no_errors;
		}
	}
	| 	CONTINUE ';' {
		$$=new struct continue_stmt(continue_stmt, line_no);
		if (!in_a_loop){
			cerr << "continue statement outside a loop: line_no: " << line_no<< endl;
			++no_errors;
		}
	}
	|	error ';' {
		cerr << "statement missing ';' around line_no: " << line_no << endl;
		++no_errors;
		$$ = new struct err_stmt(line_no);
		yyerrok;
	}
	;

list_stmt:	 LISTA NAME TEXT ';'{
		map<string,symtab_ent*>::iterator sym_it = find_in_symtab($2);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << $2 << " not found in symbol table" << endl;
			++no_errors;
			$$=new err_stmt(line_no);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->get_type();
			if( !(name_type>=INT8_TYPE&&name_type<=DOUBLE_TYPE)){
				cerr << "NAME: "<< $2 
					<< " should be of basic type: " << line_no << endl;
				++no_errors;
				$$=new struct err_stmt(line_no);
			} else {
				$$=new list_stmt(lista_basic_type_stmt, line_no, se);
			}
		}
	}
	| LISTA NAME '[' INUMBER ']' TEXT ';'{
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab($2);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << $2 << " not found in symbol table" << endl;
			++no_errors;
			$$=new err_stmt(line_no);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->get_type();
			if( !(name_type>=INT8_ARR_TYPE&&name_type<=DOUBLE_ARR_TYPE)){
				cerr << "NAME: "<< $2 
					<< " is not of array type: line_no:" << line_no << endl;
				++no_errors;
				$$=new err_stmt(line_no);
			} else {
				$$=new list_stmt( lista_basic_arrtype_stmt_1index, line_no, se, $4, -1, string($6));
			}
		}
	}
	| LISTA NAME '[' INUMBER ',' INUMBER ']' TEXT ';'{
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab($2);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << $2 << " not found in symbol table" << endl;
			++no_errors;
			$$=new err_stmt(line_no);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->get_type();
			if( !(name_type==INT8_ARR_TYPE||name_type==U_INT8_TYPE)){
				cerr << "NAME: "<< $2 
					<< " is not of char array type: line_no:" << line_no << endl;
				++no_errors;
			} else {
				$$=new list_stmt( lista_basic_arrtype_stmt_2index, line_no, se, $4, $6, string($8));
			}
		}
	}
	;

if_stmt: IF '(' expression ')' statement{
		$$=new if_stmt(ife_stmt,line_no,$3,$5,0);
	}
	| IF '(' expression ')' statement ELSE statement{
		$$=new if_stmt(ife_stmt, line_no,$3,$5,$7);
	}
	;


compound_stmt: open_curly statement_list '}'	{
		cout << "popping scope: " <<
			active_scope_list[active_scope_list.size()-1] << endl;
		active_scope_list.pop_back();
		int tmp=active_scope_list.size()-1;
		if(tmp==-1) { 
			active_scope = NULL;
			cerr << "Error: active_scope = NULL: should not happen: line_no:" << line_no
				<< endl;
			++no_errors;
			$$=new struct cmpd_stmt(error_type, line_no);
		} else { active_scope = active_scope_list[tmp]; }
		$1->cmpd_bdy = trav_chain($2);
		$$=$1;
	}
	;

open_curly:	'{' {
		++nest_lev;
		$$ = new struct cmpd_stmt(cmpd_stmt, line_no);
		if(flag_cmpd_stmt_is_a_func_body>=0){
			$$->sc=func_info_table[flag_cmpd_stmt_is_a_func_body]->func_scope;
			// reset the flag
			flag_cmpd_stmt_is_a_func_body=-1;
		} else {
			$$->sc= new scope();
		}
		//cout << "open_curly: cmpd_stmt: " << $$ << endl;
		//cout << "pushed active_scope: " << active_scope << endl;
		//active_scope_list.push_back(active_scope);
		active_scope_list.push_back($$->sc);
		active_scope = $$->sc;
		//cout << "active_scope: " << active_scope << endl;
	}
	;


expr_list: expression { $$=$1; }
	| expr_list ',' expression {
		$$=link_chain($1,$3);
	}
	;

expression: expression '+' expression {
		$$=new expr($1, $3, oper_plus);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression '-' expression {
		$$=new expr($1, $3, oper_minus);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression '*' expression { 
		$$=new expr($1, $3, oper_mult);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression '/' expression {
		$$=new expr($1, $3, oper_div);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression '%' expression {
		if(!(($1->get_type() >= INT8_TYPE && $1->get_type()<=U_INT32_TYPE)
				&&
			($3->get_type()>=INT8_TYPE && $3->get_type()<=U_INT32_TYPE))){
				cerr << " operands of % should be of type int or char only" << endl;
				++no_errors;
		}
		$$=new expr($1, $3, oper_mod);
		void_check($1->type, $3->type, $$->type);
	}
	|	'-' expression %prec UMINUS {
		$$ = new_expr();
		$$->l_op = $2;
		$$->type = $2->get_type();
		$$->e_operator = oper_umin;
		if($2->type==VOID_TYPE){
			cerr << "line_no: " << line_no << " expression of void type: check if you are calling a void function on either side" << endl;
			$$->type=error_type;
			++no_errors;
		}
	}
	|	expression '<' expression {
		$$=new expr($1, $3, oper_lt);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression '>' expression {
		$$=new expr($1, $3, oper_gt);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression LEQ expression {
		$$=new expr($1, $3, oper_le);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression GEQ expression {
		$$=new expr($1, $3, oper_ge);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression ISEQ expression {
		$$=new expr($1, $3, oper_iseq);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression NOEQ expression {
		$$=new expr($1, $3, oper_isneq);
		void_check($1->type, $3->type, $$->type);
	}	
	| expression LOGOR expression {
		$$=new expr($1, $3, oper_or);
		void_check($1->type, $3->type, $$->type);
	}	
	| expression LOGAND expression {
		$$=new expr($1, $3, oper_and);
		void_check($1->type, $3->type, $$->type);
	}
	|	NOT expression {
		$$ = new_expr();
		$$->l_op = $2;
		$$->type = $2->get_type();
		$$->e_operator = oper_not;
		if($2->type==VOID_TYPE){
			cerr << "line_no: " << line_no << " expression of void type: applying operator ! to void expr" << endl;
			$$->type=error_type;
			++no_errors;
		}
	}
	|	INUMBER	{
		$$ = new_expr();
		$$->l_op = NULL;
		$$->isem_value = $1;
		if( $1 > SCHAR_MIN && $1<SCHAR_MAX){
			$$->type=INT8_TYPE;
		} else if ($1> SHRT_MIN && $1 < SHRT_MAX){
			$$->type=INT16_TYPE;
		} else if ($1> INT_MIN && $1 < INT_MAX){
			$$->type=INT32_TYPE;
		} else {
			++no_errors;
			cerr << "very  integer unhandleable type most probably";
			$$->type = error_type;
		}
		$$->e_operator = oper_num;
	}
	|	FNUMBER {
		$$ = new_expr();
		$$->l_op = NULL;
		$$->dsem_value = $1;
		$$->type = FLOAT_TYPE;
		$$->e_operator = oper_float;
	}
	|	NAME	{
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab($1);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "Error: could not find:" << $1<<"  in symbol table: lineno: " << line_no << "\n";
			++no_errors;
			$$ = new_expr();
			$$->type=error_type;
			$$->e_operator = oper_name;
		} else {
			$$ = new_expr();
			$$->symp=sym_it->second;
			$$->type = sym_it->second->get_type();
			$$->e_operator = oper_name;
		}
	}
	| 	NAME '[' expression ']' %prec FUNC_CALL {
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab($1);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "Error: could not find:" << $1<<"  in symbol table: lineno: " << line_no << "\n";
			++no_errors;
			$$ = new_expr();
			$$->type=error_type;
			//$$->type='R';
			$$->e_operator = oper_arrderef;
		} else {
			struct symtab_ent* se=sym_it->second;
			$$ = new_expr();
			$$->symp=se;
			$$->l_op=$3;
			cout << "$1: name : " << $1 << " $1:type " << se->get_type() << endl;
			datatype name_type=se->get_type();
			if( !(name_type>=INT8_ARR_TYPE&&name_type<=DOUBLE_ARR_TYPE)){
				cerr << "NAME: "<< $1 
					<< " is not of array type: line_no:" << line_no << endl;
				++no_errors;
			}
			datatype e_type=$3->get_type();
			cout << "NAME [expression ]:e_type:" << e_type << endl;
			if(e_type>=U_INT8_TYPE && e_type <=INT32_TYPE){
				$$->type =arr_deref_type(se->get_type());
				if($$->type==error_type) {
					cerr << "ERROR: Variable being indexed not of Array Type : Error: lineno: " << line_no << "\n";
					++no_errors;
				}
			} else {
				$$->type=error_type;
				cerr << "ERROR: Array index not of Type Int : Error: lineno: " << line_no << "\n";
				++no_errors;
			}
			$$->e_operator = oper_arrderef;
		}
	}
	| NAME '(' expr_list ')' %prec FUNC_CALL{
		cout << "parsing Function call: name: " << $1 << endl;
		string search_for=$1;
		bool found=false;
		int index=search_for_func(search_for);
		if(index!=-1) found=true;
		bool skip_type_check=skip_func_type_check(search_for.c_str());
		if( skip_type_check==false  && found==false ) {
			cerr << "ERROR: function call Error on line_no: " << line_no << endl;
			cerr << "function : " << search_for << " used without decl" << endl;
			++ no_errors;
			$$=new_expr();
			$$->type=error_type;
		} else {
			datatype my_type=func_info_table[index]->return_type;
			struct expr* e_ptr=trav_chain($3);
			struct var_list* fparam=func_info_table[index]->param_list;
			bool match=false;
			if(skip_type_check==false){
				match=check_parameters(e_ptr, fparam);
			}
			if(match || skip_type_check){
				$$=new_expr();
				$$->type=my_type;
				$$->e_operator=oper_func_call;
				$$->func_index_in_table=index;
				$$->l_op = $3;
			} else {
				$$=new_expr();
				$$->type=error_type;
				$$->e_operator=oper_func_call;
				$$->func_index_in_table=index;
			}
		}
	}
	|	TEXT {
		$$=new_expr();
		$$->type=INT8_ARR_TYPE;
		$$->text=strdup($1);
		$$->e_operator=oper_text_expr;
	}
	| NAME '=' expression  {
		cout << "BEGIN parse oper_assgn: line_no: "<<  line_no << endl;
		map<string,symtab_ent*>::iterator sym_it = find_in_symtab($1);
		$$ = new_expr();
		struct symtab_ent* se= NULL;
		cout << "CAME HERE1 parse oper_assgn: line_no: "<<  line_no << endl;
		if( sym_it==active_scope->sym_tab.end()) {
			cerr << "Error: could not find name in symbol table NAME:" << $1 << endl;
			++no_errors;
			$$->type=error_type;
		} else if( $3->isvalid()){
			cout << "CAME HERE2 parse oper_assgn: line_no: "<<  line_no << endl;
			se= sym_it->second;
			$$->symp=se;
			$$->type = uninit;
			$$->e_operator=oper_assgn;
			$$->r_op= $3;
			datatype typ1=se->get_type();
			datatype typ2=$3->type;
			bool b1=check_type_compat(typ1, typ2);
			if(!b1) {
				cerr << "Error : assigning incompatible types line_no" << line_no << endl;
				++no_errors;
			}
			cout << "parsed oper_assgn: line_no: "<<  line_no << endl;
			//Finish the test HERE
		} else {
			$$->symp=se;
			$$->type=error_type;
			$$->r_op=$3;
			++no_errors;
			cerr << "Propagating type error to oper_assgn: line_no: " << line_no << endl;
		}
	}
	| 	'(' expression ')' %prec UMINUS{ 
		$$ = new_expr();
		$$->l_op = $2;
		$$->type = $2->type;
		$$->e_operator = oper_parexp;
	}
	;

tab_list: tab_defn	{ 
#ifdef DEBUG_GRAM
	printf("got table defn\n"); 
#endif
	}
	| tab_list tab_defn { 
#ifdef DEBUG_GRAM
		printf("recursive tab_defn\n"); 
#endif
	}
	;

tab_defn:
	TAB NAME NAME';'	{
		//printf("got table defn: no filter\n");
		$$=new table($2,$3, line_no);
		// default value for constructor tbl_ptr->filter=NULL;
		table_list.push_back($$);
	}
	| TAB NAME NAME';'COND_START expression';'{
		//printf("got table defn: with filter\n");
		$$=new table($2,$3, line_no, $6);
		table_list.push_back($$);
	}
	| error ';' {
		cerr << "Error in tab section line: " <<
			line_no << endl;
		++ line_no;
		++no_errors;
	}
	;

ax_list:	ax_defn	{
		//$$ = $1;
	}	
	|	ax_list ax_defn	{
		//$2->next_ax = $1;
		//$1->prev_ax = $2;
		//$$ = $2;
	}
	;

ax_defn:	AX NAME ';' ax_stmt_list {
		basic_ax_stmt* bptr= trav_chain($4);
		$$ = new ax(bptr,no_count_ax_elems, no_tot_ax_elems, NULL);
		
		//$$->ax_stmt_start = $4;
		//$$->ax_name = $2;
		ax_map[$2]=$$;
#ifdef DEBUG_GRAM
		printf("NAME: $2: %s\n", $2);
#endif
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
	}
	|	AX NAME ';'COND_START expression ';' ax_stmt_list {
		basic_ax_stmt* bptr= trav_chain($7);
		$$ = new ax(bptr,no_count_ax_elems, no_tot_ax_elems, $5);
		//$$->filter = $5;
		//$$->ax_stmt_start = $7;
		//$$->ax_name = $2;
		ax_map[$2]=$$;
#ifdef DEBUG_GRAM
		printf("NAME: $2: %s\n", $2);
#endif
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
	}
	| error ';'	{
		cerr << "Error in axis section line: " <<
			line_no << endl;
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		++no_errors;
	}
	;


ax_stmt_list: 	
	ax_stmt	{
		$$ = $1;
	}
	|	ax_stmt_list ax_stmt	{
		//$2->next = $1;
		//$1->prev = $2;
		//$$ = $2;
		$$=link_chain($1, $2);
	}
	;

ax_stmt:	TOT ';' TEXT ';' {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		$$ = new tot_ax_stmt (tot_axstmt,$3, NULL);
		if ($$ == NULL){
			cout << "Failed to allocate memory\n";
			exit(1);
		}
	}
	| TOT ';' TEXT ';' COND_START expression ';'	{
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		$$ = new tot_ax_stmt (tot_axstmt,$3, $6);
		if ($$ == NULL){
			cout << "Failed to allocate memory\n";
			exit(1);
		}
	}
	|	CNT ';'	TEXT ';' COND_START expression ';' 	{
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		$$ = new count_ax_stmt (cnt_axstmt,$3, $6);
		if ($$ == NULL){
			cout << "Failed to allocate memory\n";
			exit(1);
		}
	}
	| 	TTL ';' TEXT ';'	{
		$$ = new ttl_ax_stmt (txt_axstmt,$3);
		++no_tot_ax_elems;
	}
	;

%%

//void print_stmt_lst( struct stmt * &st);
void print_expr(FILE* edit_out, struct expr * e);
//void print_if_stmt(FILE* edit_out, struct if_stmt * if_stmt);

int	compile();
int	run(char * data_file_name, int rec_len);
void print_table_code(FILE * op, FILE *tab_drv_func, FILE * tab_summ_func);
void print_axis_code(FILE * op, FILE * axes_drv_func);

extern void yyrestart ( FILE *input_file );
	int main(int argc, char* argv[], char* envp[]){
		if(argc!=3) {
			cout << "Usage: " << argv[0] << " <prog-name> <data-file> " << endl;
			exit(0);
		}
		cout << "SOME DEBUGGING INFO: U_INT8_TYPE:" << U_INT8_TYPE 
			<< " U_INT8_ARR_TYPE:" << U_INT8_ARR_TYPE
			<< " U_INT8_REF_TYPE:" << U_INT8_REF_TYPE 
			<< endl;
			
			
		active_scope=new scope();
		active_scope_list.push_back(active_scope);
		cout << "tree_root: " << tree_root << endl;
		
		char * printf_name="printf";
		struct var_list* v_list=NULL;
		datatype myreturn_type=INT8_TYPE;
		struct func_info* fi=new func_info(printf_name, v_list, myreturn_type);
		func_info_table.push_back(fi);
		
		char *c_arr="c";
		

		FILE * yyin=fopen(argv[1],"r");
		yyrestart(yyin);
		if(yyparse()){
			cout << "Errors in parsing edit: " << no_errors << endl;
			exit(1);
		} else 
			cout << "yyparse finished : now going to print tree: no_errors: "    
			<< " should be 0 or we have a bug in the compiler"<< endl;
		//print_stmt_lst(tree_root);
		if(!no_errors){
			FILE * global_vars=fopen("xtcc_work/global.C", "wb");
			fprintf(global_vars, "#ifndef __NxD_GLOB_VARS_H\n#define __NxD_GLOB_VARS_H\n");
			fprintf(global_vars, "#include <sys/types.h>\n");
			fprintf(global_vars, "#include <map>\n using namespace std;\n");
			fprintf(global_vars, "void print_list_counts();\n");
			fprintf(global_vars, "void tab_compute();\n");
			fprintf(global_vars, "void tab_summ();\n");
			fprintf(global_vars, "void ax_compute();\n");
			fclose(global_vars);
			FILE * print_list_counts=fopen("xtcc_work/print_list_counts.C", "wb");
			fprintf(print_list_counts, "template <class T>\nvoid print_list_summ(map<T,int> &m);\n");
			fprintf(print_list_counts, "void print_list_counts(){\n");
			fclose(print_list_counts);
			FILE * edit_out= fopen("xtcc_work/edit_out.c", "w+b");
			fprintf(edit_out, "#include <cstdio>\n#include <iostream>\nusing namespace std;\n" );
			fprintf(edit_out, "#include <sys/types.h>\n" );
			fprintf(edit_out, "int8_t c[%d];\n", rec_len );
			fprintf(edit_out, "#include \"global.C\"\n" );
			if(edit_out==NULL){
				printf("could not open edit_out.c for writing\n");
				exit(1);
			}
			tree_root->print_stmt_lst(edit_out);
			fclose(edit_out);
			global_vars=fopen("xtcc_work/global.C", "a+");
			fprintf(global_vars, "#endif /* __NxD_GLOB_VARS_H*/\n");
			fclose(global_vars);
			if(!global_vars){
				cerr << "cannot open global.C for writing" << endl;
				exit(1);
			}
			print_list_counts=fopen("xtcc_work/print_list_counts.C", "a+");
			fprintf(print_list_counts, "}\n");
			fclose(print_list_counts);
		} else {
			cerr << "Errors in Parse:  Total errors: " << no_errors << endl;
		}
		FILE * table_op=fopen("xtcc_work/my_table.C", "w");	
		FILE * tab_drv_func=fopen("xtcc_work/my_tab_drv_func.C", "w");	
		FILE * tab_summ_func=fopen("xtcc_work/my_tab_summ.C", "w");	
		if(!(table_op&&tab_drv_func&&tab_summ_func)){
			cerr << "Unable to open file for output of table classes" << endl;
			exit(1);
		}
		if(yyparse()){
			cerr << "parsing tables section failed:" << endl;
			exit(1);
		}
		FILE * axes_op=fopen("xtcc_work/my_axes.C", "w");	
		FILE * axes_drv_func=fopen("xtcc_work/my_axes_drv_func.C", "w");	
		if(!(axes_op&&axes_drv_func)){
			cerr << "Unable to open file for output of axes classes" << endl;
			exit(1);
		}
		if(yyparse()){
			cerr << "parsing axes section failed:" << endl;
			exit(1);
		} else {
			cout <<  "successfully parsed axes section: " << endl;
		}
		print_table_code(table_op, tab_drv_func, tab_summ_func);
		print_axis_code(axes_op, axes_drv_func);
		fclose(table_op);fclose(tab_drv_func);
		fclose(axes_op); fclose(axes_drv_func);
		bool my_compile_flag=true;
		if(my_compile_flag&&!compile()){
			char * endptr=NULL;
			int convert_to_base=10;
			//int rec_len=strtol(argv[3],&endptr, convert_to_base);
			return run(argv[2], rec_len);
		}
		return no_errors;
	}

#include <cstdlib>
#include <cstdio>


void print_expr(FILE* edit_out, struct expr * e){
	if(e) {
		switch(e->e_operator){
			char oper_buf[3];

			case oper_plus:{
				fprintf(edit_out, "/* oper_plus */");	       
				sprintf(oper_buf, "%s" , "+");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_minus:{
				sprintf(oper_buf, "%s" , "-");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_mult:{
				sprintf(oper_buf, "%s" , "*");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_div:{
				sprintf(oper_buf, "%s" , "/");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_mod:{
				sprintf(oper_buf, "%s" , "%");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	      
			case oper_lt:{
				sprintf(oper_buf, "%s" , "<");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_gt:{
				sprintf(oper_buf, "%s" , ">");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_le:{
				sprintf(oper_buf, "%s" , "<=");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_ge:{
				sprintf(oper_buf, "%s" , ">=");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_iseq:{
				sprintf(oper_buf, "%s" , "==");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_isneq: {
				sprintf(oper_buf, "%s" , "!=");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			

			case oper_parexp:{
				fprintf(edit_out, "(");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, ")");
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;

			case oper_num:{
				fprintf(edit_out, "%d ", e->isem_value);
				//fprintf(edit_out, "/* %d */\n", e->type);
				      }
			break;
			case oper_float:{
				fprintf(edit_out, "%f ", e->dsem_value);
				//fprintf(edit_out, "/* %d */\n", e->type);
				      }
			break;

			case oper_name:{
				fprintf(edit_out, "%s ", e->symp->name);
				//fprintf(edit_out, "/* %d */\n", e->type);
				       }
			break;

			case oper_umin:{
				fprintf(edit_out, "- ");
				print_expr(edit_out, e->l_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				       }
			break;

			case oper_arrderef:{
				fprintf(edit_out, "%s[", e->symp->name);
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, "]");
				//fprintf(edit_out, "/* %d */\n", e->type);
					   }
			break;
			case oper_arr2deref:{
				fprintf(edit_out, "%s[", e->symp->name);
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, ",");
				print_expr(edit_out, e->r_op);
				fprintf(edit_out, "]");
				//fprintf(edit_out, "/* %d */\n", e->type);
				// Note : flag runtime error if r_op-l_op>=3
					    }
			break;
			case oper_func_call:{
				//cout << "func_index_in_table: " << e->func_index_in_table << endl;
				cout << "func_index_in_table: " << func_info_table[e->func_index_in_table]->fname << endl;
				fprintf(edit_out, "%s(", func_info_table[e->func_index_in_table]->fname.c_str());
				struct expr* e_ptr=e->l_op;
				fprintf(edit_out,  "/*print_expr: oper_func_call:  %s*/", func_info_table[e->func_index_in_table]->fname.c_str() );
				while(e_ptr){
					print_expr(edit_out, e_ptr);
					if(e_ptr->prev){
						fprintf(edit_out, ", ");
					} 
					e_ptr=e_ptr->prev;
				}
				fprintf(edit_out, ")");
			}
			break;
			case oper_text_expr:{
				fprintf(edit_out, "%s", e->text);
			}
			break;
			case oper_assgn:{
				fprintf(edit_out, "/*oper_assgn*/ %s =", e->symp->name);
				print_expr(edit_out, e->r_op);
			}
			break;
			case oper_not:{
				fprintf(edit_out, "! ");
				print_expr(edit_out, e->l_op);
			}
			break;
					


			default:
				fprintf(edit_out, "Unhandled expression type: %c\n", 
					e->type);
		}
	}
}



bool check_type_compat(datatype typ1, datatype typ2){
	cout << "check_type_compat: line_no: I have to convert the below code into a function"  << line_no << endl;
	datatype td1=typ1;
	datatype td2=typ2;
	if(td1>=U_INT8_REF_TYPE && td1<=DOUBLE_REF_TYPE) td1=datatype(U_INT8_TYPE + typ1-U_INT8_REF_TYPE);
	if(td2>=U_INT8_REF_TYPE && td2<=DOUBLE_REF_TYPE) td2=datatype(U_INT8_TYPE + typ2-U_INT8_REF_TYPE);
	if((td1>=U_INT8_TYPE&&td1<=DOUBLE_TYPE) &&
			td2>=U_INT8_TYPE&&td2<=DOUBLE_TYPE){
		if(td1>=td2){
			return true;
		}
	}
	cerr << "ERROR: Assigning unhandle_able Type to var:  line_no" << line_no 
		<< " LHS type: " << typ1 
		<< " RHS type: " << typ2 
		<< endl;
	++no_errors;
	return false;
}



int check_parameters(struct expr* e, struct var_list* v){
	cout << "check_parameters: called" << endl;
	struct expr* e_ptr=e;
	struct var_list* fparam=v;
	bool match=true;
	int count=0;
	struct expr* tmp_e=e;
	// No need to reverse chain any more: start here NxD: 22-jun-2007
	while (tmp_e) { 
		//e_ptr->print();
		count=count+1; 
		//cout << "count: " << count << endl;
		if(tmp_e->prev) tmp_e=tmp_e->prev; 
		else break;
	}
	int pcount=0;
	struct var_list* tmp_v=fparam ;
	while (tmp_v) { 
		//cout << "fparam->var_name: " << fparam->var_name << " ";
		pcount=pcount+1; 
		//cout << "pcount: " << pcount << endl;
		if(tmp_v->prev) tmp_v=tmp_v->prev; 
		else break;
	}
	if(count!=pcount) {
		cerr << "Number of parameters used in func call: " << count 
			<< " does not match number of parameters in function: = " << pcount 
			<< " line_no: " << line_no
			<< endl;
		++no_errors;
		match=false;
	}
	/* Important point to note: I am not allowing references in ordinary variable decl
	   Only in function parameter list - the object is to allow modifying of variables
	   in a function as in C++
	   */

	int chk_param_counter=1;
	while (e_ptr && fparam) {
		//e_ptr->print();
		datatype etype=e_ptr->type, fptype=fparam->var_type; 
		if((etype>=U_INT8_TYPE && etype<=DOUBLE_TYPE) && 
			((fptype>=U_INT8_TYPE && fptype<=DOUBLE_TYPE)||
			 (fptype>=U_INT8_REF_TYPE && fptype<=DOUBLE_REF_TYPE))){
			datatype tdt=fptype;
				/* the code below makes a U_INT8_REF_TYPE -> U_INT8_TYPE
				   			a INT8_REF_TYPE -> INT8_TYPE
				 thats because we dont care much about references -> C++
				 does all the hard work. For checking types they are equivalent to us
				*/			
			if(tdt>U_INT8_REF_TYPE) tdt=datatype(U_INT8_TYPE+tdt-U_INT8_REF_TYPE);
			if(etype <= tdt) {
				cout << "varname: "<< fparam->var_name << " chk_param_counter: " 
				<< chk_param_counter << " passed " << endl;
			}
		} else if ((etype>=U_INT8_ARR_TYPE&&etype<=DOUBLE_ARR_TYPE)&&
				(fptype>=U_INT8_ARR_TYPE&&fptype<=DOUBLE_ARR_TYPE)&&
				(etype==fptype)){
			cout << "varname: "<< fparam->var_name << " chk_param_counter: " 
					<< chk_param_counter << " passed " << endl;
		}else {
			match=false;
			cerr << "Parameter type mismatch name: " << endl;
			cerr << fparam->var_name << " expected type is " << fparam->var_type
				<< " passed type is " << e_ptr->type 
				<< " line_no: " << line_no << " or currently allowed promotion to: " << e_ptr->type+U_INT8_REF_TYPE
				<< endl;
			++no_errors;
		}
		e_ptr=e_ptr->prev;
		fparam=fparam->prev;
		chk_param_counter=chk_param_counter+1;
	}
	if(match==true){
		if(e_ptr==NULL&& fparam==NULL){
			match=true;
			//cout << "e_ptr && fparam are both NULL" << endl;
		}
		else 
			match=false;
	}
	if(match) {
		cout << "function passed parameter type check: n_params:" << chk_param_counter << endl;
	} else {
		cerr << "function parameter type check FAILURE: line_no " << line_no << endl;
	}
	return match;
}

map<string, symtab_ent*>::iterator find_in_symtab(string id){
	bool found=false;
	int i=active_scope_list.size()-1;
	cout << "START: find_in_symtab: i=" << i <<endl;

	map<string,symtab_ent*>::iterator sym_it ; 
	for(;i>-1;--i){
		sym_it = active_scope_list[i]->sym_tab.find(id);
		if (sym_it == active_scope_list[i]->sym_tab.end() ){
		} else {
			found = true;
			cout << "found" << endl;
			break;
		}
	}
	if(found==false){
		cout << "ID:" << id <<
			": not found in any scope\n";
		int j=active_scope_list.size()-1;
		map<string,symtab_ent*>::iterator it;
		for(; j>-1; --j){
			cout <<"searching in: " << 
				active_scope_list[j];
			cout << "j=" << j << endl;
			for(it=active_scope_list[j]->sym_tab.begin();
				it!=active_scope_list[j]->sym_tab.end();
				++it){
				cout << it->first << ",";
			}
		}
		return active_scope->sym_tab.end();
	} else {
		cout << "ID:" << id <<
			": found at scope level:" <<
			i << endl;
		return sym_it;
	}
}

/* NxD: I need to write a detailed note about this function's responisibilities
   */
   

	bool skip_func_type_check(const char * fname){
		cout << "skip_func_type_check: BEGIN" << endl;
		char * skip_func_type_check_list[] = {"printf" };
		for (unsigned int i=0; i<sizeof(skip_func_type_check_list)/sizeof(skip_func_type_check_list[0]); ++i){
			if(!strcmp(fname, skip_func_type_check_list[i])){
				cout << "skip_func_type_check: returned true: fname: " << fname << endl;
				return true;
			}
		}
		cout << "skip_func_type_check: returned false: fname: " << fname << endl;
		return false;
	}

		

void	add_func_params_to_cmpd_sc(struct scope * & sc, struct var_list * & v_list, string & fname){
	cout << "add_func_params_to_cmpd_sc: ENTER: sc=" << sc << " v_list:" << v_list << endl;
	struct var_list * v_ptr = v_list;
	while (v_ptr){
		cout << "v_ptr->var_name: " << v_ptr->var_name << endl;
		if(sc->sym_tab.find(v_ptr->var_name)==sc->sym_tab.end()){
			cout << "about to insert : " << v_ptr->var_name << " into cmpd_stmt symbol table" << endl;
			struct symtab_ent* se=new struct symtab_ent;
			se->name=strdup( v_ptr->var_name.c_str());
			se->type=v_ptr->var_type;
			sc->sym_tab[fname] = se;
			cout << "Added name: " << fname << " to symbol table" << endl;
		} else {
			cerr << "function parameter: " << v_ptr->var_name << " declared in the "
				<< "body of compound function" << endl;
			cerr << "line: " << line_no << endl;
		}
		//v_ptr=v_ptr->next;
		v_ptr=v_ptr->prev;
	}
}


int search_for_func(string& search_for){
	cout << "Entered search_for_func: " << endl;
	unsigned int i=0;
	
	for (i=0;i<func_info_table.size();++i){
		if(search_for==func_info_table[i]->fname){
			cout << "search_for_func(): found: " << search_for 
				<< " index: " << i
				<< endl;
			return i;
		}
	}
	cout << "search_for_func():not found function: " <<search_for  << endl;
	return -1;
}

int check_func_decl_with_func_defn(struct var_list* & v_list, int & index, string func_name){
	//cout << "Entered check_func_decl_with_func_defn: " << func_name << endl;
		
	struct var_list* defn_ptr=v_list;
	struct var_list* decl_ptr=func_info_table[index]->param_list;
	cout << "check_func_decl_with_func_defn: after func_info_table[index]->param_list" << endl;
		
	while(defn_ptr&&decl_ptr){
		// I may put a check on the length of the array - but it is not necessary for now I think
		if((defn_ptr->var_type==decl_ptr->var_type)&&
			(defn_ptr->var_name==decl_ptr->var_name)){
			cout << "checking : defn_ptr->var_name: " << defn_ptr->var_name << endl;
		} else {
			cerr << "check_func_decl_with_func_defn: return failure" << endl;
			++no_errors;
			return 0;
		}
		defn_ptr=defn_ptr->prev;
		decl_ptr=decl_ptr->prev;
	}
	if(defn_ptr==decl_ptr && decl_ptr==NULL){
		cout << "check_func_decl_with_func_defn: return success" << endl;
		return 1;
	}else{
		cout << "check_func_decl_with_func_defn: return failure" << endl;
		return 0;
	}
}

bool 	void_check( datatype & type1, datatype & type2, datatype& result_type){
	if(type1==VOID_TYPE|| type2==VOID_TYPE){
		cerr << "line_no: " << line_no << " either left or rhs of operator - is of void type: check if you are calling a void function on either side" << endl;
		result_type=error_type;
		++no_errors;
		return false;
	} else {
		return true;
	}
}

template<class T> T* link_chain(T* &elem1, T* &elem2){
	elem2->next=elem1;
	elem1->prev=elem2;
	return elem2;
}

template<class T> T* trav_chain(T* & elem1){
	if(elem1){
		while (elem1->next) elem1=elem1->next;
		return elem1;
	} else return 0;
}

#include <cstdlib>
int compile(){
	int rval;
	system("rm xtcc_work/temp.C");
	string cmd1="cat xtcc_work/edit_out.c xtcc_work/my_axes_drv_func.C xtcc_work/my_tab_drv_func.C stubs/main_loop.C > xtcc_work/temp.C";
	rval=system(cmd1.c_str());
	if(rval){
		cerr << "unable to cat files" << endl;
		return rval;
	}
	string cmd2="g++ xtcc_work/temp.C -o xtcc_work/myedit.exe";
	rval=system(cmd2.c_str());

	return rval;
}

#include <sstream>
int run(char * data_file_name, int rec_len){
	int rval;
	ostringstream cmd1;
	
	cmd1 << "xtcc_work/myedit.exe " << data_file_name  << " " << rec_len;
	rval=system(cmd1.str().c_str());
	return rval;
}

int lookup_func(string func_name_index){
	for(register unsigned int i=0; i<func_info_table.size(); ++i){
		if(func_name_index==func_info_table[i]->fname){
			return i;
		}
	}
	return -1;
}

void print_table_code(FILE * op, FILE * tab_drv_func, FILE * tab_summ_func){
	fprintf(op, "#include <iostream>\n");
	fprintf(op, "#include <vector>\nusing namespace std;\n");
	fprintf(tab_drv_func, "#include \"my_table.C\"\n");
	fprintf(tab_drv_func, "void tab_compute(){\n");
	for(int i=0; i<table_list.size(); i++){
		CMAPITER map_iter_s= ax_map.find(table_list[i]->side);
		CMAPITER map_iter_b= ax_map.find(table_list[i]->banner);
		if(map_iter_s==ax_map.end()||map_iter_b==ax_map.end()){
			cerr << "Error: axis name " 
				<< table_list[i]->side << " or " 
				<< table_list[i]->banner << "not pres in axes defn"
				<< " line_no: " << line_no 
				<< endl;
			++ no_errors;
		} else {
			//construct_internal_table(ax_map, table_list);
			//cout << "constructing table: " <<
			expr* f= table_list[i]->filter;
			cout << "table: " <<
				map_iter_b->first << " by " <<
				map_iter_s->first << endl;
			if ( f ){
				cout << " Filter: " ;
			}
				/*
			internal_table * itbl_ptr = 
				new internal_table(map_iter_s, map_iter_b, f, i);
			itbl_vec.push_back(itbl_ptr);
			*/
			fprintf(op, "struct table_%s_%s {\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str ());
			fprintf(op, "const int rows, cols;\n");
			fprintf(op, "vector <int> counter;\n");
			fprintf(op, "table_%s_%s():rows(%d), cols(%d),counter(%d*%d){for (int i=0;i<counter.size();++i) counter[i]=0; }\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str (),
					map_iter_s->second->no_count_ax_elems,
					map_iter_b->second->no_count_ax_elems,
					map_iter_s->second->no_count_ax_elems,
					map_iter_b->second->no_count_ax_elems
					);
			fprintf(op, "void compute(){\n");
			fprintf(op, "\tfor(int i=0; i<rows; ++i){\n");
			fprintf(op, "\t\tfor(int j=0; j<cols; ++j){\n");
			fprintf(op, "\t\t\tif(ax_%s.flag[i] && ax_%s.flag[j]){\n", 
				map_iter_s->first.c_str(), map_iter_b->first.c_str());
			fprintf(op, "\t\t\t\t++counter[i*cols+j];\n");
			fprintf(op, "\t\t\t} \n");
			fprintf(op, "\t\t} \n");
			fprintf(op, "\t}\n");
			fprintf(op, "\t} /* compute()*/\n");
			fprintf(op, "\tvoid print(){\n\t\tint rci=0, cci=0; /* row counter index , col ... */\n");
			fprintf(op, "\tcout << \"rows: \" << rows << \"cols: \" << cols << endl;");
			fprintf(op, "\t\tfor(int i=0; i<ax_%s.stmt_text.size(); ++i){\n",
					map_iter_s->first.c_str());
			fprintf(op, "\t\t\tcci=0;\n");
			fprintf(op, "\t\t\tcout << ax_%s.stmt_text[i] << \",\";\n", map_iter_s->first.c_str()); 
			fprintf(op, "\t\t\tif(ax_%s.is_a_count_text[i]){\n", map_iter_s->first.c_str());
			fprintf(op, "\t\t\t\tfor(int j=0; j<ax_%s.stmt_text.size(); ++j){\n",
					map_iter_b->first.c_str());
			fprintf(op, "\t\t\t\t\tif(ax_%s.is_a_count_text[j]){\n", map_iter_b->first.c_str());
			fprintf(op, "\t\t\t\t\t\t//cout << \"rci:\" << rci << \"cci:\" << cci << endl;\n");
			fprintf(op, "\t\t\t\t\t\tcout << counter[cci+rci*cols]<<\",\";\n");
			fprintf(op, "\t\t\t\t\t\t++cci;\n");
			fprintf(op, "\t\t\t\t\t}\n");
			fprintf(op, "\t\t\t\t}\n");
			fprintf(op, "\t\t\t\t++rci;\n");
			fprintf(op, "\t\t\t}\n");
			fprintf(op, "\t\tcout << endl;\n");
			fprintf(op, "\t\t}\n");
			fprintf(op, "\t}\n");
			fprintf(op, "} tab_%s_%s;\n",
				map_iter_s->first.c_str(), map_iter_b->first.c_str()
				);
			fprintf(tab_drv_func, "\ttab_%s_%s.compute();\n",
				map_iter_s->first.c_str(), map_iter_b->first.c_str()
				);
		}
	}

	fprintf(tab_drv_func, "}\n");

	fprintf(tab_drv_func, "void tab_summ(){\n");
	for(int i=0; i<table_list.size(); i++){
		CMAPITER map_iter_s= ax_map.find(table_list[i]->side);
		CMAPITER map_iter_b= ax_map.find(table_list[i]->banner);
		if(map_iter_s==ax_map.end()||map_iter_b==ax_map.end()){
			cerr << "Error: axis name " 
				<< table_list[i]->side << " or " 
				<< table_list[i]->banner << "not pres in axes defn"
				<< " line_no: " << line_no 
				<< endl;
			++ no_errors;
		} else {
			fprintf(tab_drv_func, "\ttab_%s_%s.print();\n",
			map_iter_s->first.c_str(), map_iter_b->first.c_str()
			);
		}
	}
	fprintf(tab_drv_func, "}\n");

}

void print_axis_code(FILE * op, FILE * axes_drv_func){

	fprintf(op, "#include <bitset>\n" );
	fprintf(op, "#include <string>\n" );
	fprintf(op, "#include <vector>\n" );
	fprintf(op, "using namespace std;\n" );
	fprintf(axes_drv_func, "#include \"my_axes.C\"\n");
	fprintf(axes_drv_func, "void ax_compute(){\n");
	for(CMAPITER it=ax_map.begin(); it!=ax_map.end(); ++it){
		fprintf(op, "struct axis_%s{\n", it->first.c_str() );
		fprintf(op, "\tbitset<%d> flag;\n", it->second->no_count_ax_elems );
		fprintf(op, "\tvector<string> stmt_text;\n");
		fprintf(op, "\tbitset<%d> is_a_count_text;\n", it->second->no_tot_ax_elems);
		fprintf(op, "\taxis_%s():stmt_text(%d){\n", it->first.c_str(), it->second->no_tot_ax_elems);
		int my_counter=0;
		for(basic_ax_stmt* ax_stmt_iter=it->second->ax_stmt_start; ax_stmt_iter; ax_stmt_iter=ax_stmt_iter->prev,
				++my_counter){
			fprintf(op, "\tstmt_text[%d]=%s;\n", my_counter, ax_stmt_iter->ax_text().c_str());
			if(ax_stmt_iter->axtype<=txt_axstmt){
				fprintf(op, "\tis_a_count_text[%d]=false;\n", my_counter);
			} else {
				fprintf(op, "\tis_a_count_text[%d]=true;\n", my_counter);
			}
		}
		fprintf(op, "}\n");
		fprintf(op, "\tvoid compute(){\n\tflag.reset();\n");
		basic_ax_stmt* iter=it->second->ax_stmt_start;
		int counter=0;
		while(iter){
			if(iter->axtype>=tot_axstmt){
				basic_count_ax_stmt * bc=dynamic_cast<basic_count_ax_stmt *> (iter);
					
				if(bc->condn){
					fprintf(op, "\tif (");
					print_expr(op, bc->condn);
					fprintf(op, " ){\n");
					fprintf(op, "\t\tflag[%d]=true;\n", counter);
					fprintf(op, "\t}\n");
				} else {
					fprintf(op, "\tflag[%d]=true;\n", counter);
				}
				++counter;
			}
			iter=iter->prev;
		}
		fprintf(op, "\t} /* close compute func */\n");
		fprintf(op, "} ax_%s;\n", it->first.c_str()) ;
		fprintf(axes_drv_func, "\tax_%s.compute();\n",it->first.c_str());
	}
	fprintf(axes_drv_func, "}\n");
}

