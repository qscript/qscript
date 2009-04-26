/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/q.y
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

%{

//#include "common.h"

#include <limits.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "tree.h"
#include "symtab.h"
#include "stmt.h"
#include "expr.h"
#include "named_attributes.h"
#include "named_range.h"

#include "qscript_parser.h"

	//using qscript_parser::yyerror;
	//using qscript_parser::yylex;
	//using qscript_parser::yywrap;
	extern int yylex();
	extern void yyerror(const char * s);
%}


%union {
	type_qualifier type_qual;
	int ival;
	double dval;
	char name[MY_STR_MAX];
	char text_buf[MY_STR_MAX];
	datatype dt;
	struct stmt * stmt;
	struct expr * expr;
	//class question* ques;
	struct cmpd_stmt * c_stmt;

}

%token <ival> INUMBER
%token <dval> FNUMBER
%token <name> NAME
%token <text_buf> TEXT
%token SP
%token MP
%token <dt> VOID_T
%token <dt> INT8_T
%token <dt> INT16_T
%token <dt> INT32_T
%token <dt> FLOAT_T
%token <dt> DOUBLE_T
%token <dt> STRING_T
%type <dt> datatype
%token IN
%token FOR


%token '['
%token ']'
%token '('
%token ')'
%token '='
%token CONST 

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
%nonassoc IN COUNT
%nonassoc FUNC_CALL

%type <type_qual> type_qual
%type <stmt> question
%type <stmt> stmt
%type <stmt> expr_stmt
%type <stmt> stmt_list
%type <stmt> decl_stmt
 /*%type <stmt> attributes	*/
%type <stmt> stubs	
%type <c_stmt> cmpd_stmt	
%type <c_stmt> open_curly	
%type <stmt> if_stmt	
%type <stmt> for_loop_stmt	

%token IF ELSE

%token STUBS_LIST


%type <expr> expression
%type <expr> expr_list


%%


	//prog: stmt_list {
prog: cmpd_stmt {
	qscript_parser::tree_root=$1;
		while(qscript_parser::tree_root->prev) {
			cerr << "climbing up the tree" << endl;
			qscript_parser::tree_root=qscript_parser::tree_root->prev;
		}
	}
	;

stmt_list: stmt {
		$$=$1;
		if(qscript_parser::flag_next_stmt_start_of_block){
			qscript_parser::blk_heads.push_back($1);
			//cout << "blk_heads.size(): " << blk_heads.size() << endl;
			//start_of_blk=$1;
			qscript_parser::flag_next_stmt_start_of_block=false;
			qscript_parser::blk_start_flag.pop_back();
		}

	}
	| stmt_list stmt{
		$1->next=$2;
		$2->prev=$1;
		$$=$2;
	}
	;


datatype: VOID_T
	| INT8_T
	|INT16_T
	|INT32_T  	
	|FLOAT_T
	|DOUBLE_T
	|STRING_T
	;

type_qual: CONST {
		   $$ = CONST_QUAL;
	}
	;

decl_stmt: datatype NAME ';' {
		$$ = qscript_parser::active_scope->insert($2, $1/*, line_no*/);
		//free($2);
		// -- why am i not freeing this?
	}
	| type_qual datatype NAME '=' expression ';' {
	}
	| datatype NAME '=' expression ';'{
		$$ = qscript_parser::active_scope->insert($2, $1, $4);
		// -- why am i not freeing this?
	}
	| datatype NAME '[' expression ']' ';'{
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		datatype dt=datatype(INT8_ARR_TYPE+($1-INT8_TYPE));
		$$ = qscript_parser::active_scope->insert($2, dt, $4/*, line_no*/);
		free($2);
	}
	;




stmt:	question
	| expr_stmt
	| decl_stmt
	| stubs 
	| cmpd_stmt  {
		$$ = $1;
	}
	| if_stmt
	| for_loop_stmt 
	;

for_loop_stmt: 
	FOR '(' expression ';' expression ';' expression ')' {
		qscript_parser::flag_cmpd_stmt_is_a_for_body=1;
	} cmpd_stmt {
		using qscript_parser::line_no;
		$$ = new for_stmt(FOR_STMT, line_no, $3, $5, $7, $10);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	;

cmpd_stmt: open_curly stmt_list '}' {
		using qscript_parser::active_scope;
		using qscript_parser::active_scope_list;
		using qscript_parser::stack_cmpd_stmt;
		using qscript_parser::blk_start_flag;
		using qscript_parser::blk_heads;
		using qscript_parser::mem_addr;
		using qscript_parser::flag_next_stmt_start_of_block;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;

		active_scope_list.pop_back();
		int tmp=active_scope_list.size()-1;
		if(tmp==-1) { 
			active_scope = 0;
			cerr << "Error: active_scope = NULL: should not happen: line_no:" << line_no
				<< endl;
			++no_errors;
			$$=new struct cmpd_stmt(ERROR_TYPE, line_no, 0, 0);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		} else { 
			active_scope = active_scope_list[tmp]; 
		}
		struct stmt* head_of_this_chain=blk_heads.back();
		if(blk_start_flag.size() > 0){
			flag_next_stmt_start_of_block = blk_start_flag[blk_start_flag.size()-1];
		}
		if(  head_of_this_chain==0){
			cerr << "Error in compiler : cmpd_bdy:  " << __FILE__ << __LINE__ << endl;
			++no_errors;
		} else {
			$1->cmpd_bdy = head_of_this_chain;
			blk_heads.pop_back();
		}

		//! update the counter of enlosing cmpd_stmt with 
		//! the number of questions in this cmpd_stmt being popped of
		//! right now
		if(stack_cmpd_stmt.size()>1){
			cmpd_stmt * popped_off_cmpd_stmt_ptr=stack_cmpd_stmt.back();
			stack_cmpd_stmt.pop_back();
			cmpd_stmt * current  = stack_cmpd_stmt.back();
			current->counter_contains_questions+= 
				(popped_off_cmpd_stmt_ptr->counter_contains_questions);
		} 
		$$=$1;
	}
	;

open_curly:	'{' {
		using qscript_parser::active_scope;
		using qscript_parser::active_scope_list;
		using qscript_parser::stack_cmpd_stmt;
		using qscript_parser::blk_start_flag;
		using qscript_parser::blk_heads;
		using qscript_parser::mem_addr;
		using qscript_parser::flag_next_stmt_start_of_block;
		using qscript_parser::flag_cmpd_stmt_is_a_func_body;
		using qscript_parser::flag_cmpd_stmt_is_a_for_body;
		using qscript_parser::func_info_table;
		using qscript_parser::nest_lev;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;

		++nest_lev;
		cmpd_stmt * cmpd_stmt_ptr= new cmpd_stmt(CMPD_STMT, 
				line_no, flag_cmpd_stmt_is_a_func_body,
				flag_cmpd_stmt_is_a_for_body);
		$$ = cmpd_stmt_ptr;
		stack_cmpd_stmt.push_back(cmpd_stmt_ptr);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
		mem_addr.push_back(m1);
		if(flag_cmpd_stmt_is_a_func_body>=0){
			$$->sc=func_info_table[qscript_parser::flag_cmpd_stmt_is_a_func_body]->func_scope;
			// reset the flag
			qscript_parser::flag_cmpd_stmt_is_a_func_body=-1;
		} else {
			$$->sc= new scope();
		}
		qscript_parser::flag_next_stmt_start_of_block=true;
		qscript_parser::blk_start_flag.push_back(flag_next_stmt_start_of_block);
		qscript_parser::active_scope_list.push_back($$->sc);
		qscript_parser::active_scope = $$->sc;
	}
	;



if_stmt:  IF '(' expression ')' stmt {
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		using qscript_parser::XTCC_DEBUG_MEM_USAGE;
		$$=new if_stmt(IFE_STMT,if_line_no,$3,$5,0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| IF '(' expression ')' stmt ELSE stmt {
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new if_stmt(IFE_STMT,qscript_parser::if_line_no,$3,$5,$7);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
	;

	
expr_stmt:	expression ';' 
	{
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		if($1->isvalid()){
			$$ = new expr_stmt(TEXPR_STMT, line_no, $1);
			if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
				mem_log($$, __LINE__, __FILE__, line_no);
			}
		} else {
			$$ = new expr_stmt(ERROR_TYPE, line_no, $1);
			if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
				mem_log($$, __LINE__, __FILE__, line_no);
			}
		}
	}
	;

	/*
	question_list: question {
		$$=$1;
	}
	| question_list question {
		$1->next=$2;
		$2->prev=$1;
		$$=$2;
	}
	;
	*/

question: NAME TEXT qtype datatype range_allowed_values ';' {
		using qscript_parser::active_scope;
		using qscript_parser::active_scope_list;
		using qscript_parser::stack_cmpd_stmt;
		using qscript_parser::mem_addr;
		using qscript_parser::map_of_active_vars_for_questions;
		using qscript_parser::question_list;
		using qscript_parser::xs;
		using qscript_parser::q_type;
		using qscript_parser::no_mpn;
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;

		string name($1);
		string q_text($2);
		datatype dt=$4;
		// This is preparatory work
		// for jumping between questions
		// store
		vector<string> active_push_vars;
		vector<string> active_pop_vars;
		for(unsigned int i=0; i< active_scope_list.size(); ++i){
			scope* sc_ptr= active_scope_list[i];
			sc_ptr->print_scope(active_push_vars, active_pop_vars);
		}
		string q_push_name = name + "_push";
		string q_pop_name = name + "_pop";
		map_of_active_vars_for_questions[q_push_name] = active_push_vars;
		map_of_active_vars_for_questions[q_pop_name] = active_pop_vars;
		range_question * q= new range_question(QUESTION_TYPE, line_no, 
			name, q_text, q_type, no_mpn, dt, xs);
		if(stack_cmpd_stmt.size()==0){
			print_err(compiler_internal_error, "compound statement stack is 0 when parsing a question"
					"... exiting",
					line_no, __LINE__, __FILE__  );
			exit(1);
		}
		cmpd_stmt * cmpd_stmt_ptr=stack_cmpd_stmt.back();
		++(cmpd_stmt_ptr->counter_contains_questions);
		$$=q;
		question_list.push_back(q);
		xs.reset();
		// questions always get pushed in scope level 0 as they
		// are global variables - no matter what the level of nesting
		active_scope_list[0]->insert($1, QUESTION_TYPE);
		// I need to modify the insert in scope to
		// take a 3rd parameter which is a question *
		// and store that into the symbol table
		// I should be able to retrieve that 
		// question* pointer later 
	}
	| NAME TEXT qtype datatype NAME ';' {
		using qscript_parser::active_scope;
		using qscript_parser::active_scope_list;
		using qscript_parser::stack_cmpd_stmt;
		using qscript_parser::mem_addr;
		using qscript_parser::map_of_active_vars_for_questions;
		using qscript_parser::named_stubs_list;
		using qscript_parser::question_list;
		using qscript_parser::q_type;
		using qscript_parser::no_mpn;
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		string name=$1;
		string q_txt=$2;
		datatype dt=$4;
		string attribute_list_name=$5;

		// This is preparatory work
		// for jumping between questions
		// store
		vector<string> active_push_vars;
		vector<string> active_pop_vars;
		for(unsigned int i=0; i< active_scope_list.size(); ++i){
			scope* sc_ptr= active_scope_list[i];
			sc_ptr->print_scope(active_push_vars, active_pop_vars);
		}
		string q_push_name = name + "_push";
		string q_pop_name = name + "_pop";
		map_of_active_vars_for_questions[q_push_name] = active_push_vars;
		map_of_active_vars_for_questions[q_pop_name] = active_pop_vars;

		bool found=false;
		struct named_range* nr_ptr = 0;
		for(unsigned int i=0; i<named_stubs_list.size(); ++i){
			nr_ptr = named_stubs_list[i];
			if(nr_ptr->name==attribute_list_name){
				found=true; break;
			}
		}
		if(!found){
			print_err(compiler_sem_err, string("named_stubs_list ") 
				+ attribute_list_name + string(" not found \n"), line_no,
				__LINE__, __FILE__);
		}
		named_stub_question* q=new named_stub_question(QUESTION_TYPE, 
				line_no, name, q_txt, 
				q_type, no_mpn, dt, 
				//attribute_list_name);
				nr_ptr);
		question_list.push_back(q);
		$$=q;
		active_scope_list[0]->insert($1, QUESTION_TYPE);
		if(stack_cmpd_stmt.size()==0){
			print_err(compiler_internal_error, "compound statement stack is 0 when parsing a question"
					"... exiting",
					line_no, __LINE__, __FILE__  );
			exit(1);
		}
		cmpd_stmt * cmpd_stmt_ptr=stack_cmpd_stmt.back();
		++(cmpd_stmt_ptr->counter_contains_questions);
	}
	;



expression: expression '+' expression {
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		using qscript_parser::mem_addr;
		$$=new bin_expr($1, $3, oper_plus);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '-' expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new bin_expr($1, $3, oper_minus);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '*' expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new bin_expr($1, $3, oper_mult);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '/' expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new bin_expr($1, $3, oper_div);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '%' expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new bin_expr($1, $3, oper_mod);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	'-' expression %prec UMINUS {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$ = new un_expr($2, oper_umin);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '<' expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new bin_expr($1, $3, oper_lt);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '>' expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new bin_expr($1, $3, oper_gt);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression LEQ expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new bin_expr($1, $3, oper_le);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression GEQ expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new bin_expr($1, $3, oper_ge);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression ISEQ expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new bin_expr($1, $3, oper_iseq);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression NOEQ expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new bin_expr($1, $3, oper_isneq);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| expression LOGOR expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new bin_expr($1, $3, oper_or);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| expression LOGAND expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		cout << "LOGAND expr: " << endl;
		$$=new bin_expr($1, $3, oper_and);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		cout << "after LOGAND expr : " << endl;
	}
	| expression '=' expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$ = new bin_expr($1, $3, oper_assgn);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	NOT expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$ = new un_expr($2, oper_not);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	INUMBER	{
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$ = new un2_expr($1);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	FNUMBER {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		$$ = new un2_expr($1);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	NAME	{
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		$$ = new un2_expr($1, oper_name );
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| 	NAME '[' expression ']' %prec FUNC_CALL {
		using qscript_parser::line_no;
		using qscript_parser::mem_addr;
		$$ = new un2_expr(oper_arrderef, /*nametype,  se,*/ $1,$3);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($1);
	}
	| NAME '[' expression ',' expression ']'  %prec FUNC_CALL {
		using qscript_parser::line_no;
		using qscript_parser::mem_addr;
		$$ = new un2_expr(oper_blk_arr_assgn, $1,$3,$5);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($1);
	}
	| NAME '(' expr_list ')' %prec FUNC_CALL{
		using qscript_parser::mem_addr;
		using qscript_parser::named_stubs_list;
		using qscript_parser::func_info_table;
		using qscript_parser::xs;
		using qscript_parser::q_type;
		using qscript_parser::no_mpn;
		using qscript_parser::trav_chain;
		using qscript_parser::skip_func_type_check;
		using qscript_parser::check_parameters;
		using qscript_parser::link_chain;
		using qscript_parser::stub_list;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
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
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
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
				//$$=new un2_expr(oper_func_call, my_type, e_ptr, index, line_no);
				$$=new un2_expr(oper_func_call, my_type, e_ptr, index);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);
			} else {
				$$=new un2_expr(ERROR_TYPE);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);
			}
		}
		free($1);
	}
	|	TEXT {
		using qscript_parser::line_no;
		$$ = new un2_expr(strdup($1), oper_text_expr);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| 	'(' expression ')' %prec UMINUS{ 
		using qscript_parser::line_no;
		$$ = new un_expr($2, oper_parexp );
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| expression IN range_allowed_values {
		using qscript_parser::xs;
		using qscript_parser::line_no;
		$$ = new bin2_expr($1, xs, oper_in);
		xs.reset();
	}

	/*
	| NAME IN NAME {
		$$ = new bin2_expr($1, $3, oper_in);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	*/
	;


expr_list: expression { $$=$1; }
	| expr_list ',' expression {
		$$=qscript_parser::link_chain($1,$3);
	}
	;

qtype: SP { qscript_parser::q_type = spn; }
	| MP '(' INUMBER ')' { qscript_parser::q_type = mpn; qscript_parser::no_mpn = $3; }
	;

range_allowed_values:  '(' range_list ')' { }
	;


range_list: range
	| range_list ',' range
	;

range: 	INUMBER '-' INUMBER {
		using qscript_parser::line_no;
		if($3<=$1){
			print_err(compiler_sem_err, "2nd number in range <= 1st number",
					line_no, __LINE__, __FILE__  );

		} else {
			qscript_parser::xs.range.push_back( pair<int,int>($1,$3));
		}
	}
	|	INUMBER {
		qscript_parser::xs.indiv.insert($1);
	}
	;

stubs:     STUBS_LIST NAME {
		using qscript_parser:: stub_list;
		using qscript_parser:: named_stubs_list;
		stub_list.resize(0);
	}'=' stub_list ';'{
		using qscript_parser::line_no;
		using qscript_parser:: stub_list;
		using qscript_parser:: named_stubs_list;
		//cout <<"got attribute_list size: " << attribute_list.size() << endl;
		string stub_name=$2;
		struct named_range* nr_ptr= new named_range(NAMED_RANGE, line_no, stub_name,stub_list);
		named_stubs_list.push_back(nr_ptr);
		//$$=0;
		$$ = nr_ptr;
	}
	;


stub_list:	TEXT INUMBER {
		using qscript_parser::stub_list;
		string s1=$1;
		int code=$2;
		struct stub_pair pair1(s1,code);
		stub_list.push_back(pair1);
	}
	| stub_list TEXT INUMBER {
		using qscript_parser::stub_list;
		string s1=$2;
		int code=$3;
		struct stub_pair pair1(s1,code);
		stub_list.push_back(pair1);
		//cout << "chaining stublist" << endl;
	}
	;



%%

#include <unistd.h>
#include <string>

namespace qscript_parser {

template<class T> T* link_chain(T* &elem1, T* &elem2){
	if(elem1 && elem2){
		elem2->prev=elem1;
		elem1->next=elem2;
		return elem2;
	}
	else if(elem1){
		return elem1;
	} else {
		return elem2;
	}
}


template<class T> T* trav_chain(T* & elem1){
	if(elem1){
		while (elem1->prev) elem1=elem1->prev;
		return elem1;
	} else return 0;
}

}
