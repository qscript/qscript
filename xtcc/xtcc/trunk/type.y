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
#include "expr.h"
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
	//void	add_func_params_to_cmpd_sc(struct scope * & sc, struct var_list * & v_list, string & fname);
	int search_for_func(string& search_for);
	int check_func_decl_with_func_defn(struct var_list*& v_list, int & index, string func_name);
	struct stmt* make_func_defn_stmt( struct scope *& sc,
		struct var_list * & v_list,
		struct stmt* & func_body,
		string search_for,
		datatype return_type
		);
	struct stmt * tree_root=0;
	bool 	void_check( datatype & type1, datatype & type2, datatype& result_type);
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);

	int flag_cmpd_stmt_is_a_func_body=-1;
	int lookup_func(string func_name_index);
	vector<table*>	table_list;
	map <string, ax*> ax_map;

	int no_count_ax_elems=0;
	int no_tot_ax_elems=0;
	int in_a_loop=0;
	int nest_lev=0;
	int rec_len;
	bool flag_next_stmt_start_of_block=false;
	//struct stmt* start_of_blk=0;
	vector <stmt*> blk_heads;

	noun_list_type noun_list[]= {
			{	"void"	, VOID_TYPE},
			{	"int8_t" ,INT8_TYPE},
			{	"int16_t" ,INT16_TYPE},
			{	"int32_t" ,INT32_TYPE},
			{	"float", FLOAT_TYPE},
			{	"double", DOUBLE_TYPE}
		};
	vector<mem_addr_tab>  mem_addr;

	void flex_finish();

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

%token CONVERT
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
%type <stmt> fld_stmt 
%token  FOR
%token FLD
%token <text_buf> TEXT
%token <name> NAME
%token <dval> FNUMBER
%token <ival> INUMBER
//%token <column_no> SCOLUMN
%token <code_list> CODELIST
%token LISTA
%token IF
%token ELSE
%token '['
%token ']'
%token '('
%token ')'
%token '='
 /*%token <dt> INT*/
 /*%token <dt> CHAR*/
%token <dt> VOID_T
%token <dt> INT8_T
%token <dt> INT16_T
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

prog: DATA_STRUCT ';' REC_LEN '=' INUMBER ';' 
	{	char * c_arr="c";  
		rec_len=$5; 
		active_scope->insert(c_arr, INT8_ARR_TYPE, rec_len, 0);
	} 
	ED_START top_level_item_list ED_END {
		tree_root = trav_chain($9);
		if(tree_root==0){
			cerr << "tree_root =0 : core dump expected" << endl;
		}
		return 0;
	}
	| AXSTART '{' ax_list 	'}'	{
		return 0;
	}
	| TABSTART '{' tab_list '}' {
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

top_level_item: decl{
			$$=$1;
	}
	| func_defn	{
		$$=$1;
	}
	;

xtcc_type: VOID_T
	|INT8_T
	|INT16_T
	|INT32_T  	
	|FLOAT_T
	|DOUBLE_T
	;


func_defn:	
	xtcc_type NAME '(' decl_comma_list ')' {
		string func_name_index($2);
		flag_cmpd_stmt_is_a_func_body=lookup_func(func_name_index);
		if(flag_cmpd_stmt_is_a_func_body==-1){
			++ no_errors;
			cerr << "Function name not found in list of declared functions: "
				<< "You will see another error on this same function name: " << func_name_index
				<< "line_no: " << line_no  << endl;
		}
	} compound_stmt {
		struct cmpd_stmt* c_stmt= $7;
		if(c_stmt==0){
			cout << "c_stmt==0" << endl;
		} else {
			cout << "func_body: is valid " << endl;
		}
		struct scope *sc=c_stmt->sc;
		struct var_list * v_list=trav_chain($4);
		struct stmt* func_body=$7;
		string search_for=$2;
		datatype return_type=$1;
		/*$$=new func_stmt(FUNC_DEFN, line_no, sc, v_list, cmpd_stmt, search_for, return_type);
			// This gives an error - we have to fool the compiler*/
		$$=new func_stmt(FUNC_DEFN, line_no, sc, v_list, func_body, search_for, return_type);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		// Note that the declaration already has a parameter list
		// the constructor uses the parameter list - name and type to verify everything
		// but doesnt need the parameter list any more - so we should delete it 
		// - took me a while to figure out this memory leak
		delete v_list;
		free($2);
	}
	;


decl:	xtcc_type NAME ';' {
		//cout << "creating simple var of type: " << $1 << endl;
		$$ = active_scope->insert($2, $1, line_no);
		free($2);
	} 
	|	xtcc_type NAME '[' INUMBER ']' ';' {
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		//cout << "creating arr var of type: " << $1 << endl;
		datatype dt=datatype(INT8_ARR_TYPE+($1-INT8_TYPE));
		$$ = active_scope->insert($2, dt, $4, line_no);
		free($2);
	}
	/*
	NxD I only want to allow references in function parameter lists 
	|	xtcc_type '&' NAME {
		cout << "creating ref var of type: " << $1 << endl;
		datatype dt=datatype(INT8_REF_TYPE+($1-INT8_TYPE));
		$$ = active_scope->insert($3, dt, line_no);
	}
	*/
	| func_decl	{
		$$=$1;
	}
	;


func_decl:	xtcc_type NAME '(' decl_comma_list ')' ';'{
		char *name=$2;
		//char *name=strdup($2);
		struct var_list* v_list=trav_chain($4);
		datatype return_type=$1;
		$$=new func_decl_stmt( FUNC_TYPE, line_no, name,  v_list, return_type);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		//free(name);
	}
	;


decl_comma_list: var_decl	{
		 $$=$1;
		 //cout << "got decl_comma_list : " << endl;
	}
	| decl_comma_list ',' var_decl {
		$$=link_chain($1,$3);
		//cout << "chaining var_decl : " << endl;
	}
	;


var_decl:	xtcc_type NAME 	{
		//cout << "creating simple var of type: " << $1 << endl;
		$$=new var_list($1, $2);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		free($2);
	}
	| xtcc_type NAME '[' INUMBER ']'  {
		/* Neil - I need to fix this */
		//cout << "creating arr var of type: " << $1 << endl;
		datatype dt=datatype(INT8_ARR_TYPE+($1-INT8_TYPE));
		$$=new var_list(dt, $2, $4);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		free($2);
	}
	|	xtcc_type '&' NAME {
		//cout << "creating ref var of type: " << $1 << endl;
		datatype dt=datatype(INT8_REF_TYPE+($1-INT8_TYPE));
		$$=new var_list(dt, $3);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		free($3);
	}
	|	/* empty */
		{
		//$$=new var_list(uninit, "empty");
		$$=0;
		}
	;

statement_list: statement {
		$$=$1; 
		if(flag_next_stmt_start_of_block){
			blk_heads.push_back($1);
			//start_of_blk=$1;
			flag_next_stmt_start_of_block=false;
		}
	}
	|	statement_list statement {
		$$=link_chain($1,$2);
	}
	;

statement: FOR '(' expression ';' expression ';' expression ')' { ++in_a_loop;} statement {
		   if($3->type==VOID_TYPE||$5->type==VOID_TYPE||$7->type==VOID_TYPE 
			){
			   cerr << "For condition has VOID_TYPE or ERROR_TYPE" << endl;
			   ++ no_errors;
			   $$=new struct err_stmt(line_no);
			   void *ptr=$$;
			   mem_addr_tab m1(ptr, line_no);
			   mem_addr.push_back(m1);
		   } else{
			   $$ = new struct for_stmt(FOR_STMT, line_no, $3, $5, $7, $10);
			   void *ptr=$$;
			   mem_addr_tab m1(ptr, line_no);
			   mem_addr.push_back(m1);
		   }
		   --in_a_loop;
	}
	| if_stmt
	| expression ';' { 
		if($1->isvalid()){
			$$ = new expr_stmt(TEXPR_STMT, line_no, $1);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			$$ = new expr_stmt(ERROR_TYPE, line_no, $1);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		}
		//printf("= %g\n", $1); 
	}
	|	compound_stmt {
		$$=$1;
	}
	|	decl {
		$$=$1;
	}
	|	list_stmt
	|	BREAK ';'{
		$$=new struct break_stmt(BREAK_STMT, line_no);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if (!in_a_loop){
			cerr << "break statement outside a loop: line_no: " << line_no<< endl;
			++no_errors;
		}
	}
	| 	CONTINUE ';' {
		$$=new struct continue_stmt(CONTINUE_STMT, line_no);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if (!in_a_loop){
			cerr << "continue statement outside a loop: line_no: " << line_no<< endl;
			++no_errors;
		}
	}
	|	fld_stmt
	|	error ';' {
		cerr << "statement missing ';' around line_no: " << line_no << endl;
		++no_errors;
		$$ = new struct err_stmt(line_no);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		yyerrok;
	}
	;

list_stmt:	 LISTA NAME TEXT ';'{
		map<string,symtab_ent*>::iterator sym_it = find_in_symtab($2);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << $2 << " not found in symbol table" << endl;
			++no_errors;
			$$=new err_stmt(line_no);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->type;
			if( !(name_type>=INT8_TYPE&&name_type<=DOUBLE_TYPE)){
				cerr << "NAME: "<< $2 
					<< " should be of basic type: " << line_no << endl;
				++no_errors;
				$$=new struct err_stmt(line_no);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			} else {
				$$=new list_stmt(LISTA_BASIC_TYPE_STMT, line_no, se);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
		free($2);
	}
	| LISTA NAME '[' INUMBER ']' TEXT ';'{
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab($2);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << $2 << " not found in symbol table" << endl;
			++no_errors;
			$$=new err_stmt(line_no);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->type;
			if( !(name_type>=INT8_ARR_TYPE&&name_type<=DOUBLE_ARR_TYPE)){
				cerr << "NAME: "<< $2 
					<< " is not of array type: line_no:" << line_no << endl;
				++no_errors;
				$$=new err_stmt(line_no);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			} else {
				$$=new list_stmt( LISTA_BASIC_ARRTYPE_STMT_1INDEX, line_no, se, $4, -1, string($6));
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
		free($2);
	}
	| LISTA NAME '[' INUMBER ',' INUMBER ']' TEXT ';'{
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab($2);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << $2 << " not found in symbol table" << endl;
			++no_errors;
			$$=new err_stmt(line_no);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->type;
			if( !(name_type==INT8_ARR_TYPE||name_type==INT8_TYPE)){
				cerr << "NAME: "<< $2 
					<< " is not of char array type: line_no:" << line_no << endl;
				++no_errors;
			} else {
				$$=new list_stmt( LISTA_BASIC_ARRTYPE_STMT_2INDEX, line_no, se, $4, $6, string($8));
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
		free($2);	
	}
	;

if_stmt: IF '(' expression ')' statement{
		if($3->type==VOID_TYPE || $3->type==ERROR_TYPE){
			++no_errors;
			$$=new err_stmt(line_no);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
			cerr << "Error: If condition has void or Error type:" << line_no << endl;
		} else {
			$$=new if_stmt(IFE_STMT,line_no,$3,$5,0);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		}
	}
	| IF '(' expression ')' statement ELSE statement{
		if($3->type==VOID_TYPE || $3->type==ERROR_TYPE){
			++no_errors;
			$$=new err_stmt(line_no);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
			cerr << "Error: If condition has void or Error type:" << line_no << endl;
		} else {
			$$=new if_stmt(IFE_STMT, line_no,$3,$5,$7);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		}
	}
	;

fld_stmt:	FLD NAME '=' NAME '(' expression ',' expression ')' ':' INUMBER ';'{
		expr* start_col=$6;
		expr* end_col=$8;
		int width=$11;
		map<string,symtab_ent*>::iterator sym_it1 = find_in_symtab($2);
		map<string,symtab_ent*>::iterator sym_it2 = find_in_symtab($4);
		if(!(	(start_col->type>=INT8_TYPE && start_col->type<=INT32_TYPE)&&
			(end_col->type>=INT8_TYPE && end_col->type<=INT32_TYPE)) ){
			cerr << "start_col, end_col expressions must be of integer type line_no:" 
				<< line_no << endl;
			++no_errors;
			$$=new err_stmt(line_no);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else if(sym_it1==active_scope->sym_tab.end()){
			cerr << "Error: could not find:" << $2<<"  in symbol table: lineno: " << line_no << "\n";
			++no_errors;
			$$=new err_stmt(line_no);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else if (sym_it2==active_scope->sym_tab.end()){
			cerr << "Error: could not find:" << $4
				<< " in symbol table: lineno: " << line_no << "\n";
			++no_errors;
			$$=new err_stmt(line_no);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			// first some validation checks
			//datatype type1 = sym_it1->type;
			if( !( 
				(sym_it1->second->type == INT8_ARR_TYPE) &&
				(sym_it2->second->type >= INT8_ARR_TYPE) &&
				(sym_it2->second->type <= INT32_ARR_TYPE)) ) {
				/* add code here */
				++no_errors;
				$$ = new err_stmt(line_no);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			} else if (!(width==sizeof(INT8_TYPE) || width==sizeof(INT16_TYPE)
					||width==sizeof(INT32_TYPE))	){
				cerr << "width of field can only be : " 
					<< sizeof(INT8_TYPE) << " or " << sizeof(INT16_TYPE) << " or "
					<< sizeof(INT32_TYPE) << endl;
				++no_errors;
				$$ = new err_stmt(line_no);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			} else {
				//everything is ok
				// since start_col and end_col can be exprs
				// we have to move some checks to runtime environment
				$$ = new fld_stmt(sym_it1->second, sym_it2->second, 
					start_col, end_col, width);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
	}
	;


compound_stmt: open_curly statement_list '}'	{
		active_scope_list.pop_back();
		int tmp=active_scope_list.size()-1;
		if(tmp==-1) { 
			active_scope = 0;
			cerr << "Error: active_scope = NULL: should not happen: line_no:" << line_no
				<< endl;
			++no_errors;
			$$=new struct cmpd_stmt(ERROR_TYPE, line_no, 0);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else { active_scope = active_scope_list[tmp]; }
		struct stmt* head_of_this_chain=blk_heads.back();
		if(  head_of_this_chain==0){
			cerr << "Error in compiler : cmpd_bdy:  " << __FILE__ << __LINE__ << endl;
			++no_errors;
		} else {
			$1->cmpd_bdy = head_of_this_chain;
			blk_heads.pop_back();
		}
		
		$$=$1;
	}
	;
	/* Very important point to note
	 * The scope for a function is created at the time of declaration
	 * and all the variables are dumped into it. This is loaded here if we are a function scope
	 * - otherwise if we are the scope of a for / while / if/else stmt - we create a new one
	 */

open_curly:	'{' {
			cout << "In open_curly: " << endl;
		++nest_lev;
		$$ = new cmpd_stmt(CMPD_STMT, line_no, flag_cmpd_stmt_is_a_func_body);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if(flag_cmpd_stmt_is_a_func_body>=0){
			$$->sc=func_info_table[flag_cmpd_stmt_is_a_func_body]->func_scope;
			// reset the flag
			flag_cmpd_stmt_is_a_func_body=-1;
		} else {
			$$->sc= new scope();
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		}
		flag_next_stmt_start_of_block=true;
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
		$$=new bin_expr($1, $3, oper_plus);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression '-' expression {
		$$=new bin_expr($1, $3, oper_minus);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression '*' expression { 
		$$=new bin_expr($1, $3, oper_mult);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression '/' expression {
		$$=new bin_expr($1, $3, oper_div);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression '%' expression {
		$$=new bin_expr($1, $3, oper_mod);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if(!(($1->type >= INT8_TYPE && $1->type<=INT32_TYPE)
				&&
			($3->type>=INT8_TYPE && $3->type<=INT32_TYPE))){
				cerr << " operands of % should be of type int or char only" << endl;
				++no_errors;
				$$->type=ERROR_TYPE;
		}
		void_check($1->type, $3->type, $$->type);
	}
	|	'-' expression %prec UMINUS {
		$$ = new un_expr($2, oper_umin);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if($2->type==VOID_TYPE){
			cerr << "line_no: " << line_no << " expression of void type: check if you are calling a void function on either side" << endl;
			$$->type=ERROR_TYPE;
			++no_errors;
		}
	}
	|	expression '<' expression {
		$$=new bin_expr($1, $3, oper_lt);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression '>' expression {
		$$=new bin_expr($1, $3, oper_gt);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression LEQ expression {
		$$=new bin_expr($1, $3, oper_le);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression GEQ expression {
		$$=new bin_expr($1, $3, oper_ge);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression ISEQ expression {
		$$=new bin_expr($1, $3, oper_iseq);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check($1->type, $3->type, $$->type);
	}
	|	expression NOEQ expression {
		$$=new bin_expr($1, $3, oper_isneq);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check($1->type, $3->type, $$->type);
	}	
	| expression LOGOR expression {
		$$=new bin_expr($1, $3, oper_or);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check($1->type, $3->type, $$->type);
	}	
	| expression LOGAND expression {
		$$=new bin_expr($1, $3, oper_and);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check($1->type, $3->type, $$->type);
	}
	| expression '=' expression {
		datatype typ1=$1->type;
		datatype typ2=$3->type;
		cout << " oper_assgn: LHS type" << typ1 << " RHS type: " << typ2 << endl;
		bool b1=check_type_compat(typ1, typ2)&& $1->is_lvalue();
		if($1->is_lvalue()){
			$$ = new bin_expr($1, $3, oper_assgn);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			$$ = new un2_expr(ERROR_TYPE);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
			++no_errors;
			cerr << "oper_assgn error on line: " << line_no<< endl;
		}
	}
	|	NOT expression {
		$$ = new un_expr($2, oper_not);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if($2->type==VOID_TYPE){
			cerr << "line_no: " << line_no << " expression of void type: applying operator ! to void expr" << endl;
			$$->type=ERROR_TYPE;
			++no_errors;
		}
	}
	|	INUMBER	{
		$$ = new un2_expr($1);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		//cerr << "type.y: parsed integer: type" << $$->type << endl;
	}
	|	FNUMBER {
		$$ = new un2_expr($1);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
	}
	|	NAME	{
		map<string,symtab_ent*>::iterator sym_it = find_in_symtab($1);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "Error: could not find:" << $1<<"  in symbol table: lineno: " << line_no << "\n";
			++no_errors;
			$$ = new un2_expr(ERROR_TYPE);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			$$ = new un2_expr(sym_it->second );
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		}
		free($1);
	}
	| 	NAME '[' expression ']' %prec FUNC_CALL {
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab($1);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "Error: Array indexing expr could not find:" << $1<<"  in symbol table: lineno: " << line_no << "\n";
			++no_errors;
			$$ = new un2_expr(ERROR_TYPE);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			symtab_ent* se=sym_it->second;

			datatype e_type=$3->type;
			if(e_type>=INT8_TYPE && e_type <=INT32_TYPE){
				datatype nametype =arr_deref_type(se->type);
				if(nametype==ERROR_TYPE) {
					cerr << "ERROR: Variable being indexed not of Array Type : Error: lineno: " << line_no << "\n";
					++no_errors;
					$$ = new un2_expr(ERROR_TYPE);
					void *ptr=$$;
					mem_addr_tab m1(ptr, line_no);
					mem_addr.push_back(m1);
				} else {
					$$ = new un2_expr(oper_arrderef, nametype,  se, $3);
					void *ptr=$$;
					mem_addr_tab m1(ptr, line_no);
					mem_addr.push_back(m1);
				}
			} else {
				cerr << "ERROR: Array index not of Type Int : Error: lineno: " << line_no << "\n";
				++no_errors;
				$$ = new un2_expr(ERROR_TYPE);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
		free($1);
	}
	| NAME '[' expression ',' expression ']'  %prec FUNC_CALL {
		symtab_ent* se=0;
		map<string,symtab_ent*>::iterator sym_it1 = find_in_symtab($1);
		if( sym_it1==active_scope->sym_tab.end()) {
			cerr << "Not able to find :" << $1 << " in symbol table: line_no" 
				<< line_no
				<< endl;
			++no_errors;
		} else {
			se=sym_it1->second;
		}
		if( !(se)){
			cerr << "Error: could not find name " << $1 << "  in expr " 
				<< "oper_blk_arr_assgn: " << " line_no: " << line_no;
				++no_errors;
			$$ = new un2_expr(ERROR_TYPE);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} /*else if(!(lse->type==INT32_TYPE || lse->type==FLOAT_TYPE)){
			cerr << "ERROR: LHS:  " << $1 << ":line_no:" << line_no 
				<< " should be of type float or int"
				<< endl;
			cerr << "lse type: " << lse->type << endl;
			++no_errors;
			$$=new struct err_stmt(line_no);
		}*/ else {
			datatype e_type1=$3->type;
			datatype e_type2=$5->type;
			if( (e_type1>=INT8_TYPE && e_type1 <=INT32_TYPE) && 
					(e_type2>=INT8_TYPE && e_type2<=INT32_TYPE)){
				datatype d1=arr_deref_type(se->type);
				if(d1==ERROR_TYPE){
					$$ = new un2_expr(ERROR_TYPE);
					void *ptr=$$;
					mem_addr_tab m1(ptr, line_no);
					mem_addr.push_back(m1);
					cerr << "Type Error:  x: lineno: " << line_no << "\n";
					++no_errors;
				} else {
					$$ = new un2_expr(oper_blk_arr_assgn, d1, se,$3,$5);
					void *ptr=$$;
					mem_addr_tab m1(ptr, line_no);
					mem_addr.push_back(m1);
				}
			} else {
				$$ = new un2_expr(ERROR_TYPE);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
				cerr << "ERROR: NAME  =NAME[EXPR, EXPR] EXPR should be of type int or char: lineno: " 
					<< line_no << "\n";
				++no_errors;
			}
		}
		//free($1);
	}
	| NAME '(' expr_list ')' %prec FUNC_CALL{
		//cout << "parsing Function call: name: " << $1 << endl;
		string search_for=$1;
		bool found=false;
		int index=search_for_func(search_for);
		if(index!=-1) found=true;
		bool skip_type_check=skip_func_type_check(search_for.c_str());
		if( skip_type_check==false  && found==false ) {
			cerr << "ERROR: function call Error on line_no: " << line_no << endl;
			cerr << "function : " << search_for << " used without decl" << endl;
			++ no_errors;
			$$=new un2_expr(ERROR_TYPE);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			datatype my_type=func_info_table[index]->return_type;
			expr* e_ptr=trav_chain($3);
			var_list* fparam=func_info_table[index]->param_list;
			bool match=false;
			if(skip_type_check==false){
				match=check_parameters(e_ptr, fparam);
			}
			if(match || skip_type_check){
				//$$=new un2_expr(oper_func_call, my_type, $3, index, line_no);
				$$=new un2_expr(oper_func_call, my_type, e_ptr, index, line_no);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);

			} else {
				$$=new un2_expr(ERROR_TYPE);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
		free($1);
	}
	|	TEXT {
		$$ = new un2_expr(strdup($1));
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
	}
	| 	'(' expression ')' %prec UMINUS{ 
		$$ = new un_expr($2, oper_parexp );
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
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
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		// default value for constructor tbl_ptr->filter=NULL;
		table_list.push_back($$);
		//free($2); free($3);
	}
	| TAB NAME NAME';'COND_START expression';'{
		//printf("got table defn: with filter\n");
		$$=new table($2,$3, line_no, $6);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		table_list.push_back($$);
		//free($2); free($3);
	}
	| error ';' {
		cerr << "Error in tab section line: " <<
			line_no << endl;
		++ line_no;
		++no_errors;
	}
	;

ax_list:	ax_defn	{
	}	
	|	ax_list ax_defn	{
	}
	;

ax_defn:	AX NAME ';' ax_stmt_list {
		basic_ax_stmt* bptr= trav_chain($4);
		$$ = new ax(bptr,no_count_ax_elems, no_tot_ax_elems, 0);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		
		ax_map[$2]=$$;
#ifdef DEBUG_GRAM
		printf("NAME: $2: %s\n", $2);
#endif
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		free($2);
	}
	|	AX NAME ';'COND_START expression ';' ax_stmt_list {
		basic_ax_stmt* bptr= trav_chain($7);
		$$ = new ax(bptr,no_count_ax_elems, no_tot_ax_elems, $5);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		ax_map[$2]=$$;
#ifdef DEBUG_GRAM
		printf("NAME: $2: %s\n", $2);
#endif
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		free($2);
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
		$$=link_chain($1, $2);
	}
	;

ax_stmt:	TOT ';' TEXT ';' {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		$$ = new tot_ax_stmt (tot_axstmt,$3, 0);
	}
	| TOT ';' TEXT ';' COND_START expression ';'	{
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		$$ = new tot_ax_stmt (tot_axstmt,$3, $6);
	}
	|	CNT ';'	TEXT ';' COND_START expression ';' 	{
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		$$ = new count_ax_stmt (cnt_axstmt,$3, $6);
	}
	| 	TTL ';' TEXT ';'	{
		$$ = new ttl_ax_stmt (txt_axstmt,$3);
		++no_tot_ax_elems;
	}
	;

%%

void print_expr(FILE* edit_out, expr * e);

int	compile();
int	run(char * data_file_name, int rec_len);
void print_table_code(FILE * op, FILE *tab_drv_func, FILE * tab_summ_func);
void print_axis_code(FILE * op, FILE * axes_drv_func);
void clean_up();

void	generate_edit_section_code();

extern void yyrestart ( FILE *input_file );

void	print_memory_leaks();
void reset_files();
int main(int argc, char* argv[], char* envp[]){
	if(argc!=3) {
		cout << "Usage: " << argv[0] << " <prog-name> <data-file> " << endl;
		exit(0);
	}
	cout << "SOME DEBUGGING INFO: INT8_TYPE:" << INT8_TYPE 
		<< " INT8_ARR_TYPE:" << INT8_ARR_TYPE
		<< " INT8_REF_TYPE:" << INT8_REF_TYPE 
		<< endl;
	reset_files();
		
		
	active_scope=new scope();
	active_scope_list.push_back(active_scope);
	cout << "tree_root: " << tree_root << endl;
	
	/*
	 * Hand install printf -> something like a library functions
	 */

	char * printf_name="printf";
	var_list* v_list=0;
	datatype myreturn_type=INT8_TYPE;
	func_info* fi=new func_info(printf_name, v_list, myreturn_type);
	func_info_table.push_back(fi);
	
	char *c_arr="c";

	FILE * yyin=fopen(argv[1],"r");
	yyrestart(yyin);
	if(yyparse()){
		cout << "Errors in parsing edit: " << no_errors << endl;
		exit(1);
	} else 
		cout << "edit section parse finished." << endl;

	//yyterminate();
	//print_stmt_lst(tree_root);
	if(!no_errors){
		generate_edit_section_code();
	} else {
		cerr << "Errors in Parse:  Total errors: " << no_errors << endl;
		exit(1);
	}
	FILE * table_op=fopen("xtcc_work/my_table.C", "w");
	FILE * tab_drv_func=fopen("xtcc_work/my_tab_drv_func.C", "w");	
	FILE * tab_summ_func=fopen("xtcc_work/my_tab_summ.C", "w");	
	if(!(table_op&&tab_drv_func&&tab_summ_func)){
		cerr << "Unable to open file for output of table classes" << endl;
		exit(1);
	}
	if(int rval=yyparse()){
		cerr << "parsing tables section failed:" << endl;
		exit(rval);
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
	flex_finish();
	print_table_code(table_op, tab_drv_func, tab_summ_func);
	print_axis_code(axes_op, axes_drv_func);
	fclose(yyin); yyin=0;
	fclose(table_op);
	fclose(tab_drv_func);
	fclose(axes_op); 
	fclose(axes_drv_func);
	fclose(tab_summ_func);
	bool my_compile_flag=true;
	if(my_compile_flag&&!compile()){
		char * endptr=0;
		int convert_to_base=10;
		//int rec_len=strtol(argv[3],&endptr, convert_to_base);
		int rval= run(argv[2], rec_len);
		if(tree_root) {
			delete tree_root;
			tree_root=0;
		}
		clean_up();
		// fi was allocated by us - the "hand installed printf function"
		delete fi;
		print_memory_leaks();
		return rval;
	}
	cout << "returning from main with errors"<< endl;
	return no_errors;
}


void	print_memory_leaks(){
	for(int i=0; i< mem_addr.size(); ++i ){
		cout << "addr: " << mem_addr[i].mem_ptr << " line: " << mem_addr[i].line_number << endl;
	}
}

#include <cstdlib>
#include <cstdio>


void clean_up(){
	cout << "Entered function clean_up()" << endl;
	typedef map<string, ax*>::iterator ax_map_iter;
	for(ax_map_iter it=ax_map.begin(); it!=ax_map.end(); ++it){
		delete it->second; it->second=0;
	}
	// we should only delete the 0 index scope as this was manually created by us
	if (active_scope_list[0]) {
		delete active_scope_list[0]; active_scope_list[0]=0;
	}

	for(int i=0; i<table_list.size(); ++i){
		delete table_list[i];
	}
	cout << "Exited function clean_up()" << endl;
			
}


bool check_type_compat(datatype typ1, datatype typ2){
	cout << "check_type_compat: line_no: I have to convert the below code into a function:"  << line_no << endl;
	datatype td1=typ1;
	datatype td2=typ2;
	if(td1>=INT8_REF_TYPE && td1<=DOUBLE_REF_TYPE) td1=datatype(INT8_TYPE + typ1-INT8_REF_TYPE);
	if(td2>=INT8_REF_TYPE && td2<=DOUBLE_REF_TYPE) td2=datatype(INT8_TYPE + typ2-INT8_REF_TYPE);
	if((td1>=INT8_TYPE&&td1<=DOUBLE_TYPE) &&
			td2>=INT8_TYPE&&td2<=DOUBLE_TYPE){
		if(td1>=td2){
			return true;
		}
	} else {
		cerr << "ERROR: Assigning unhandle_able Type to var:  line_no:" << line_no 
			<< " LHS type: " << typ1 << " after converting LHS: " << td1
			<< " RHS type: " << typ2 << " after converting RHS: " << td2
			<< endl;
		++no_errors;
		return false;
	}
}



int check_parameters(expr* e, var_list* v){
	cout << "check_parameters: called" << endl;
	expr* e_ptr=e;
	var_list* fparam=v;
	bool match=true;
	/* Important point to note: I am not allowing references in ordinary variable decl
	   Only in function parameter list - the object is to allow modifying of variables
	   in a function as in C++
	   */

	int chk_param_counter=1;
	while (e_ptr && fparam) {
		//e_ptr->print();
		datatype etype=e_ptr->type, fptype=fparam->var_type; 
		if((etype>=INT8_TYPE && etype<=DOUBLE_TYPE) && 
			((fptype>=INT8_TYPE && fptype<=DOUBLE_TYPE)||
			 (fptype>=INT8_REF_TYPE && fptype<=DOUBLE_REF_TYPE))){
			datatype tdt=fptype;
				/* the code below makes a INT8_REF_TYPE -> INT8_TYPE
				   			a INT8_REF_TYPE -> INT8_TYPE
				 thats because we dont care much about references -> C++
				 does all the hard work. For checking types they are equivalent to us
				*/			
			if(tdt>=INT8_REF_TYPE) tdt=datatype(INT8_TYPE+tdt-INT8_REF_TYPE);
			if(etype <= tdt) {
				cout << "varname: "<< fparam->var_name << " chk_param_counter: " 
				<< chk_param_counter << " passed " << endl;
			}
		} else if ((etype>=INT8_ARR_TYPE&&etype<=DOUBLE_ARR_TYPE)&&
				(fptype>=INT8_ARR_TYPE&&fptype<=DOUBLE_ARR_TYPE)&&
				(etype==fptype)){
			cout << "varname: "<< fparam->var_name << " chk_param_counter: " 
					<< chk_param_counter << " passed " << endl;
		}else {
			match=false;
			cerr << "Parameter type mismatch name: " << endl;
			cerr << fparam->var_name << " expected type is " << fparam->var_type
				<< " passed type is " << e_ptr->type 
				<< " line_no: " << line_no << " or currently allowed promotion to: " 
				<< e_ptr->type+INT8_REF_TYPE
				<< endl;
			++no_errors;
		}
		e_ptr=e_ptr->prev;
		fparam=fparam->prev;
		chk_param_counter=chk_param_counter+1;
	}
	if(match==true){
		if(e_ptr==0&& fparam==0){
			cout << "MATCHED" << endl;
			match=true;
		} else {
			match=false;
			++no_errors;
			cerr << "NOTMATCHED: No of parameters in function call not matching with no of paramters in expr: line_no"
				<< line_no << endl;
		}
	}
	if(!match) {
		cerr << "function parameter type check FAILURE: line_no " << line_no << endl;
	}
	return match;
}

map<string, symtab_ent*>::iterator find_in_symtab(string id){
	bool found=false;
	int i=active_scope_list.size()-1;
	//cout << "START: find_in_symtab: i=" << i <<endl;

	map<string,symtab_ent*>::iterator sym_it ; 
	for(;i>-1;--i){
		sym_it = active_scope_list[i]->sym_tab.find(id);
		if (sym_it == active_scope_list[i]->sym_tab.end() ){
		} else {
			found = true;
			//cout << "found" << endl;
			break;
		}
	}
	if(found==false){
		return active_scope->sym_tab.end();
	} else {
		return sym_it;
	}
}

/* NxD: I need to write a detailed note about this function's responsibilities
   */
   

	bool skip_func_type_check(const char * fname){
		//cout << "skip_func_type_check: BEGIN" << endl;
		char * skip_func_type_check_list[] = {"printf" };
		for (unsigned int i=0; i<sizeof(skip_func_type_check_list)/sizeof(skip_func_type_check_list[0]); ++i){
			if(!strcmp(fname, skip_func_type_check_list[i])){
				//cout << "skip_func_type_check: returned true: fname: " << fname << endl;
				return true;
			}
		}
		//cout << "skip_func_type_check: returned false: fname: " << fname << endl;
		return false;
	}

		

/*
void	add_func_params_to_cmpd_sc(scope * & sc, var_list * & v_list, string & fname){
	cout << "add_func_params_to_cmpd_sc: ENTER: sc=" << sc << " v_list:" << v_list << endl;
	var_list * v_ptr = v_list;
	while (v_ptr){
		cout << "v_ptr->var_name: " << v_ptr->var_name << endl;
		if(sc->sym_tab.find(v_ptr->var_name)==sc->sym_tab.end()){
			cout << "about to insert : " << v_ptr->var_name << " into cmpd_stmt symbol table" << endl;
			symtab_ent* se=new symtab_ent;
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
*/


int search_for_func(string& search_for){
	//cout << "Entered search_for_func: " << endl;
	unsigned int i=0;
	
	for (i=0;i<func_info_table.size();++i){
		if(search_for==func_info_table[i]->fname){
			//cout << "search_for_func(): found: " << search_for << " index: " << i << endl;
			return i;
		}
	}
	cout << "search_for_func():not found function: " <<search_for  << endl;
	return -1;
}

int check_func_decl_with_func_defn(var_list* & v_list, int & index, string func_name){
	//cout << "Entered check_func_decl_with_func_defn: " << func_name << endl;
		
	var_list* defn_ptr=v_list;
	var_list* decl_ptr=func_info_table[index]->param_list;
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
	if(defn_ptr==decl_ptr && decl_ptr==0){
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
		result_type=ERROR_TYPE;
		++no_errors;
		return false;
	} else {
		result_type=type1 > type2? type1: type2;
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
		/*
		while (elem1->exists_next()){
			
		}
		*/
	} else return 0;
}

#include <cstdlib>
int compile(){
	int rval;
#if !defined(__WIN32__) && !defined(MAC_TCL) /* GNU/UNIX */
	system("rm xtcc_work/temp.C");
	string cmd1="cat xtcc_work/edit_out.c xtcc_work/my_axes_drv_func.C xtcc_work/my_tab_drv_func.C stubs/main_loop.C > xtcc_work/temp.C";
#endif /* GNU/UNIX */
#if __WIN32__
	system("del xtcc_work\\temp.C");
	string cmd1="type xtcc_work\\edit_out.c xtcc_work\\my_axes_drv_func.C xtcc_work\\my_tab_drv_func.C stubs\\main_loop.C > xtcc_work\\temp.C";
#endif /* __WIN32__ */

	rval=system(cmd1.c_str());
	if(rval){
		cerr << "unable to cat files" << endl;
		return rval;
	}
#if !defined(__WIN32__) && !defined(MAC_TCL) /* GNU/UNIX */
	string cmd2="g++ xtcc_work/temp.C -o xtcc_work/myedit.exe";
#endif /* GNU/UNIX */	
#if __WIN32__
	string cmd2="\\Borland\\BCC55\\Bin\\bcc32 -P -I\\Borland\\BCC55\\Include -L\\Borland\\BCC55\\LIB -extcc_work\\myedit.exe xtcc_work\\temp.C ";
#endif /* __WIN32__ */	

	rval=system(cmd2.c_str());

	return rval;
}

#include <sstream>
int run(char * data_file_name, int rec_len){
	int rval;
	ostringstream cmd1;
#if	__WIN32__
	cmd1 << "xtcc_work\\myedit.exe " << data_file_name  << " " << rec_len;
#endif /* __WIN32__ */
#if !defined(__WIN32__) && !defined(MAC_TCL) /* GNU/UNIX */
	cmd1 << "xtcc_work/myedit.exe " << data_file_name  << " " << rec_len;
#endif /* UNIX */
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
	fprintf(op, "#include <fstream>\n");
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
			expr* f= table_list[i]->filter;
			cout << "table: " <<
				map_iter_b->first << " by " <<
				map_iter_s->first << endl;
			if ( f ){
				cout << " Filter: " ;
			}
			fprintf(op, "struct table_%s_%s {\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str ());
			fprintf(op, "const int rows, cols;\n");
			fprintf(op, "vector <int> counter;\n");
			fprintf(op, "table_%s_%s():rows(%d), cols(%d),counter(%d*%d){\nfor (int i=0;i<counter.size();++i) counter[i]=0; }\n",
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
			fprintf(op, "\t\tofstream tab_op(\"tab_.csv\", ios_base::out|ios_base::app);\n");
			fprintf(op, "\t\ttab_op << \"rows: \" << rows << \"cols: \" << cols << endl;\n");
			fprintf(op, "\t\ttab_op << ax_%s.stmt_text[0] << \" x \" << ax_%s.stmt_text[0] << endl;\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str()
					);
			fprintf(op, "\t\ttab_op << \",\";\n");
			fprintf(op, "\t\tfor(int j=0; j<ax_%s.stmt_text.size(); ++j){\n", map_iter_b->first.c_str());
			fprintf(op, "\t\t\tif(ax_%s.is_a_count_text[j]){\n", map_iter_b->first.c_str());
			fprintf(op, "\t\t\t\t tab_op << ax_%s.stmt_text[j] << \",\" ;\n", map_iter_b->first.c_str()); 
			fprintf(op, "\t\t\t}\n");
			fprintf(op, "\t\t}\n");
			fprintf(op, "\t\ttab_op << endl;\n");
			fprintf(op, "\t\t\tfor(int i=1; i<ax_%s.stmt_text.size(); ++i){\n",
					map_iter_s->first.c_str());
			fprintf(op, "\t\t\t\tcci=0;\n");
			fprintf(op, "\t\t\t\ttab_op << ax_%s.stmt_text[i] << \",\";\n", map_iter_s->first.c_str()); 
			fprintf(op, "\t\t\t\tif(ax_%s.is_a_count_text[i]){\n", map_iter_s->first.c_str());
			fprintf(op, "\t\t\t\t\tfor(int j=0; j<ax_%s.stmt_text.size(); ++j){\n",
					map_iter_b->first.c_str());
			fprintf(op, "\t\t\t\t\tif(ax_%s.is_a_count_text[j]){\n", map_iter_b->first.c_str());
			fprintf(op, "\t\t\t\t\t\t//tab_op << \"rci:\" << rci << \"cci:\" << cci << endl;\n");
			fprintf(op, "\t\t\t\t\t\ttab_op << counter[cci+rci*cols]<<\",\";\n");
			fprintf(op, "\t\t\t\t\t\t++cci;\n");
			fprintf(op, "\t\t\t\t\t}\n");
			fprintf(op, "\t\t\t\t}\n");
			fprintf(op, "\t\t\t\t++rci;\n");
			fprintf(op, "\t\t\t}\n");
			fprintf(op, "\t\ttab_op << endl;\n");
			fprintf(op, "\t\t}\n");
			fprintf(op, "\ttab_op.close();\n");
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
					bc->condn->print_expr(op);
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

void	generate_edit_section_code(){
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
	if(edit_out==0){
		printf("could not open edit_out.c for writing\n");
		exit(1);
	}
#if __WIN32__
	fprintf(edit_out, "#include \"stubs/iso_types.h\"\n" );
#endif /* __WIN32__ */
	fprintf(edit_out, "#include <cstdio>\n#include <iostream>\nusing namespace std;\n" );
	fprintf(edit_out, "#include <sys/types.h>\n" );
	fprintf(edit_out, "int8_t c[%d];\n", rec_len );
	fprintf(edit_out, "#include \"global.C\"\n" );
	cout << "printing edit:" << endl;
	tree_root->print_stmt_lst(edit_out);
	fclose(edit_out);
	global_vars=fopen("xtcc_work/global.C", "a+");
	if(!global_vars){
		cerr << "cannot open global.C for writing" << endl;
		exit(1);
	}
	fprintf(global_vars, "#endif /* __NxD_GLOB_VARS_H*/\n");
	fclose(global_vars);
	print_list_counts=fopen("xtcc_work/print_list_counts.C", "a+");
	fprintf(print_list_counts, "}\n");
	fclose(print_list_counts);

}

#include <fstream>
void reset_files(){
	ofstream lst_op("lst_.csv", ios_base::out|ios_base::trunc);
	lst_op << endl;
	lst_op.close();
	ofstream tab_op("tab_.csv", ios_base::out|ios_base::trunc);
	tab_op << endl;
	tab_op.close();
}
