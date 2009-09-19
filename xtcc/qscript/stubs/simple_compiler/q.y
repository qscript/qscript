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
#include <cstdlib>

//#include "tree.h"
#include "debug_mem.h"
#include "symtab.h"
#include "scope.h"
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
	using std::cout;
	using std::cerr;
	using std::endl;
%}


%union {
	type_qualifier type_qual;
	int ival;
	double dval;
	char name[MY_STR_MAX];
	char text_buf[MY_STR_MAX];
	DataType dt;
	struct AbstractStatement * stmt;
	struct AbstractExpression * expr;
	//class AbstractQuestion* ques;
	struct CompoundStatement * c_stmt;

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
%type <stmt> stub_manip_stmts	

%token IF ELSE

%token STUBS_LIST
%token SETDEL
%token SETADD
%token UNSET
%token SETALL


%type <expr> expression
%type <expr> expr_list


%%


prog: cmpd_stmt {
	qscript_parser::tree_root=$1;
		while(qscript_parser::tree_root->prev_) {
			cerr << "This should never appear: climbing up the tree" << endl;
			qscript_parser::tree_root=qscript_parser::tree_root->prev_;
		}
	}
	;

stmt_list: stmt {
		$$=$1;
		if(qscript_parser::flag_next_stmt_start_of_block){
			qscript_parser::blk_heads.push_back($1);
			qscript_parser::flag_next_stmt_start_of_block=false;
			qscript_parser::blk_start_flag.pop_back();
		}

	}
	| stmt_list stmt{
		$1->next_=$2;
		$2->prev_=$1;
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
		DataType dt=DataType(INT8_ARR_TYPE+($1-INT8_TYPE));
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
	| stub_manip_stmts
	;

for_loop_stmt: 
	FOR '(' expression ';' expression ';' expression ')' {
		++qscript_parser::flagIsAForBody_;
		qscript_parser::for_loop_max_counter_stack.push_back($5);
	} cmpd_stmt {
		using qscript_parser::line_no;
		$$ = new ForStatement(FOR_STMT, line_no, $3, $5, $7, $10);

		--qscript_parser::flagIsAForBody_;
		qscript_parser::for_loop_max_counter_stack.pop_back();
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	;

cmpd_stmt: open_curly stmt_list '}' {
		$$ = qscript_parser::ProcessCompoundStatement($1, $2);
	}
	;

open_curly:	'{' {
		CompoundStatement * cmpdStmt = qscript_parser::ProcessOpenCurly();
		$$=cmpdStmt;
	}
	;



if_stmt:  IF '(' expression ')' stmt {
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		using qscript_parser::XTCC_DEBUG_MEM_USAGE;
		$$=new IfStatement(IFE_STMT,if_line_no,$3,$5,0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| IF '(' expression ')' stmt ELSE stmt {
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new IfStatement(IFE_STMT,qscript_parser::if_line_no,$3,$5,$7);
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
		if($1->IsValid()){
			$$ = new ExpressionStatement(TEXPR_STMT, line_no, $1);
			if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
				mem_log($$, __LINE__, __FILE__, line_no);
			}
		} else {
			$$ = new ExpressionStatement(ERROR_TYPE, line_no, $1);
			if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
				mem_log($$, __LINE__, __FILE__, line_no);
			}
		}
	}
	;


question: NAME TEXT qtype datatype range_allowed_values ';' {
		$$ = qscript_parser::ProcessRangeQuestion($1, $2, $4);
		cout << "parsed range question : " << $1 << endl;
	}
	| NAME TEXT qtype datatype NAME ';' {
		$$ = qscript_parser::ProcessNamedQuestion($1, $2, $4, $5);
		cout << "parsed named question : " << $1 << endl;
	}
	;



expression: expression '+' expression {
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		using qscript_parser::mem_addr;
		$$=new BinaryExpression($1, $3, oper_plus);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '-' expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new BinaryExpression($1, $3, oper_minus);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '*' expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new BinaryExpression($1, $3, oper_mult);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '/' expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new BinaryExpression($1, $3, oper_div);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '%' expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new BinaryExpression($1, $3, oper_mod);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	'-' expression %prec UMINUS {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$ = new UnaryExpression($2, oper_umin);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '<' expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new BinaryExpression($1, $3, oper_lt);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '>' expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new BinaryExpression($1, $3, oper_gt);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression LEQ expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new BinaryExpression($1, $3, oper_le);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression GEQ expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new BinaryExpression($1, $3, oper_ge);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression ISEQ expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new BinaryExpression($1, $3, oper_iseq);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression NOEQ expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new BinaryExpression($1, $3, oper_isneq);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| expression LOGOR expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$=new BinaryExpression($1, $3, oper_or);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| expression LOGAND expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		cout << "LOGAND expr: " << endl;
		$$=new BinaryExpression($1, $3, oper_and);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		cout << "after LOGAND expr : " << endl;
	}
	| expression '=' expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$ = new BinaryExpression($1, $3, oper_assgn);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	NOT expression {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$ = new UnaryExpression($2, oper_not);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	INUMBER	{
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		$$ = new Unary2Expression($1);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	FNUMBER {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		$$ = new Unary2Expression($1);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	NAME	{
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		$$ = new Unary2Expression($1, oper_name );
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| 	NAME '[' expression ']' %prec FUNC_CALL {
		using qscript_parser::line_no;
		using qscript_parser::mem_addr;
		$$ = new Unary2Expression(oper_arrderef, /*nametype,  se,*/ $1,$3);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($1);
	}
	| NAME '[' expression ',' expression ']'  %prec FUNC_CALL {
		using qscript_parser::line_no;
		using qscript_parser::mem_addr;
		$$ = new Unary2Expression(oper_blk_arr_assgn, $1,$3,$5);
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
			cerr << "ERROR: function call Error on line_no: " 
				<< line_no << endl;
			cerr << "function : " << search_for 
				<< " used without decl" << endl;
			++ no_errors;
			$$=new Unary2Expression(ERROR_TYPE);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		} else {
			DataType my_type=func_info_table[index]->returnType_;
			AbstractExpression* e_ptr=trav_chain($3);
			VariableList* fparam=
				func_info_table[index]->parameterList_;
			bool match=false;
			if(skip_type_check==false){
				match=check_parameters(e_ptr, fparam);
			}
			if(match || skip_type_check){
				//$$=new Unary2Expression(oper_func_call, my_type, $3, index, line_no);
				//$$=new Unary2Expression(oper_func_call, my_type, e_ptr, index, line_no);
				$$=new Unary2Expression(oper_func_call, my_type, e_ptr, index);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);
			} else {
				$$=new Unary2Expression(ERROR_TYPE);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);
			}
		}
		free($1);
	}
	|	TEXT {
		using qscript_parser::line_no;
		$$ = new Unary2Expression(strdup($1), oper_text_expr);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| 	'(' expression ')' %prec UMINUS{ 
		using qscript_parser::line_no;
		$$ = new UnaryExpression($2, oper_parexp );
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| expression IN range_allowed_values {
		using qscript_parser::xs;
		using qscript_parser::line_no;
		$$ = new Binary2Expression($1, xs, oper_in);
		xs.reset();
	}

	/*
	| NAME IN NAME {
		$$ = new Binary2Expression($1, $3, oper_in);
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
	| MP '(' INUMBER ')' { qscript_parser::q_type = mpn; 
		qscript_parser::no_mpn = $3; 
	}
	;

range_allowed_values:  '(' range_list ')' { }
	;


range_list: range
	| range_list ',' range
	;

range: 	INUMBER '-' INUMBER {
		using qscript_parser::line_no;
		if($3<=$1){
			print_err(compiler_sem_err
					, "2nd number in range <= 1st number",
					line_no, __LINE__, __FILE__  );

		} else {
			qscript_parser::
				xs.range.push_back( pair<int,int>($1,$3));
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
		struct named_range* nr_ptr= new named_range(NAMED_RANGE
				, line_no, stub_name,stub_list);
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

stub_manip_stmts: 
	  SETDEL '(' NAME ',' NAME ')' ';' {
		$$ = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_DEL
				, $3, $5);
	}
	| SETADD '(' NAME ',' NAME ')' ';' {
		$$ = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, $3, $5);
	}
	| UNSET '(' NAME ')' ';' {
		$$ = qscript_parser::setup_stub_manip_stmt_set_unset( STUB_MANIP_UNSET_ALL, $3);
	}
	| SETALL '(' NAME ')' ';' {
		$$ = qscript_parser::setup_stub_manip_stmt_set_unset( STUB_MANIP_SET_ALL, $3);
	}
	;
	



%%


#include "utils.h"
#include <unistd.h>
#include <string>

namespace qscript_parser {

template<class T> T* link_chain(T* &elem1, T* &elem2){
	if(elem1 && elem2){
		elem2->prev_=elem1;
		elem1->next_=elem2;
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
		while (elem1->prev_) elem1=elem1->prev_;
		return elem1;
	} else return 0;
}

//! The array size of a question inside a for loop
//! is determined by the nesting level of the question inside the
//! for loop and the maximum bound of the loop index - it is a multiplication
//! of all the maximum counters in the enclosing for loops
AbstractExpression * recurse_for_index(int stack_index){
	//cerr << "entered: recurse_for_index: stack_index: " << stack_index << endl;
	if(stack_index==0){
		BinaryExpression * test_expr = 
			dynamic_cast<BinaryExpression*>(
					for_loop_max_counter_stack[0]);
		if(test_expr==0){
			print_err(compiler_sem_err, 
				" test expr should be a binary expression ",
				qscript_parser::line_no, __LINE__, __FILE__);
			return 0;
		} else if(test_expr->rightOperand_->IsIntegralExpression() 
				&& test_expr->rightOperand_->IsConst()) {
			return test_expr->rightOperand_;
		} else {
			print_err(compiler_sem_err, 
				" test expr not integer and const",
				qscript_parser::line_no, __LINE__, __FILE__);
			return test_expr->rightOperand_;
		}
	} else {
		BinaryExpression * test_expr = 
			dynamic_cast<BinaryExpression*>(
				for_loop_max_counter_stack[stack_index]);
		if(test_expr==0){
			print_err(compiler_sem_err, 
				" test expr should be a binary expression ",
				qscript_parser::line_no, __LINE__, __FILE__);
			return 0;
		} else if(test_expr->rightOperand_->IsIntegralExpression() 
				&& test_expr->rightOperand_->IsConst()) {
			return new BinaryExpression(test_expr->rightOperand_,
				recurse_for_index(stack_index-1), oper_mult);
		} else {
			print_err(compiler_sem_err, 
				" test expr not integer and const",
				qscript_parser::line_no, __LINE__, __FILE__);
			return test_expr->rightOperand_;
		}
	}
}

CompoundStatement* ProcessOpenCurly()
{
	++nest_lev;
	CompoundStatement * cmpdStmt= new CompoundStatement(CMPD_STMT, 
			line_no, flagIsAFunctionBody_,
			flagIsAForBody_);
	stack_cmpd_stmt.push_back(cmpdStmt);
	void *ptr=cmpdStmt;
	mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
	mem_addr.push_back(m1);
	if(flagIsAFunctionBody_>=0){
		cmpdStmt->scope_=func_info_table[
			qscript_parser::flagIsAFunctionBody_]->functionScope_;
		// reset the flag
		qscript_parser::flagIsAFunctionBody_=-1;
	} else {
		cmpdStmt->scope_= new Scope();
	}
	flag_next_stmt_start_of_block=true;
	blk_start_flag.push_back(flag_next_stmt_start_of_block);
	active_scope_list.push_back(cmpdStmt->scope_);
	active_scope = cmpdStmt->scope_;
	return cmpdStmt;
}

CompoundStatement* ProcessCompoundStatement(CompoundStatement* cmpdStmt,
		AbstractStatement *stmt)
{

	active_scope_list.pop_back();
	int tmp=active_scope_list.size()-1;
	if(tmp==-1) { 
		active_scope = 0;
		print_err(compiler_internal_error
			, "Error: active_scope == 0 in ProcessCompoundStatement"
			": should never happen :... exiting",
				line_no, __LINE__, __FILE__  );
		exit(1);
	} else { 
		active_scope = active_scope_list[tmp]; 
	}
	struct AbstractStatement* head_of_this_chain=blk_heads.back();
	if(blk_start_flag.size() > 0){
		flag_next_stmt_start_of_block = blk_start_flag[blk_start_flag.size()-1];
	}
	if(  head_of_this_chain==0){
		//cerr << "Error in compiler : compoundBody_:  " << __FILE__ << __LINE__ << endl;
		//++no_errors;
		print_err(compiler_internal_error
			, "Error: head_of_this_chain == 0 in "
			"ProcessCompoundStatement : should never happen :"
			"... exiting"
			, line_no, __LINE__, __FILE__  );
		exit(1);
	} else {
		cmpdStmt->compoundBody_ = head_of_this_chain;
		blk_heads.pop_back();
	}

	//! update the counter of enlosing CompoundStatement with 
	//! the number of questions in this CompoundStatement being popped of
	//! right now
	if(stack_cmpd_stmt.size()>1){
		CompoundStatement * popped_off_cmpd_stmt_ptr=stack_cmpd_stmt.back();
		stack_cmpd_stmt.pop_back();
		CompoundStatement * current  = stack_cmpd_stmt.back();
		current->counterContainsQuestions_+= 
			(popped_off_cmpd_stmt_ptr->counterContainsQuestions_);
	} 
	//$$=$1;
	return cmpdStmt;
}

AbstractStatement * ProcessRangeQuestion(const string &name
		, const string & q_text, const DataType& dt )
{

	vector<string> active_push_vars;
	vector<string> active_pop_vars;
	for(unsigned int i=0; i< active_scope_list.size(); ++i){
		Scope* sc_ptr= active_scope_list[i];
		sc_ptr->print_scope(active_push_vars, active_pop_vars);
	}
	string q_push_name = name + "_push";
	string q_pop_name = name + "_pop";
	map_of_active_vars_for_questions[q_push_name] = active_push_vars;
	map_of_active_vars_for_questions[q_pop_name] = active_pop_vars;
	
	AbstractExpression * arr_sz=0;
	RangeQuestion * q=0;
	if(qscript_parser::flagIsAForBody_){
		cout << "flagIsAForBody_: " 
			<< qscript_parser::flagIsAForBody_ << endl;
		arr_sz = qscript_parser::recurse_for_index(
			qscript_parser::for_loop_max_counter_stack.size()-1);
		q= new RangeQuestion(QUESTION_TYPE, line_no, 
			name, q_text, q_type, no_mpn, dt, xs
			//, arr_sz
			,qscript_parser::for_loop_max_counter_stack
			);
		//ostringstream s1, s2;
		//arr_sz->print_expr(s1, s2);
		//cerr << "s1: " << s1.str() << ", s2: " << s2.str() << endl;
	} else {
		q= new RangeQuestion(QUESTION_TYPE, line_no, 
			name, q_text, q_type, no_mpn, dt, xs);
	}
	if(stack_cmpd_stmt.size()==0){
		print_err(compiler_internal_error
			, "compound statement stack is 0 when parsing"
			"a question... exiting",
				line_no, __LINE__, __FILE__  );
		exit(1);
	}
	CompoundStatement * cmpd_stmt_ptr=stack_cmpd_stmt.back();
	++(cmpd_stmt_ptr->counterContainsQuestions_);
	//$$=q;

	question_list.push_back(q);
	cout << "question_list: questions are " << endl;
	for(int i=0; i<question_list.size(); ++i){
		cout << question_list[i]->questionName_ << endl;
	}
	xs.reset();
	// questions always get pushed in Scope level 0 as they
	// are global variables - no matter what the level of nesting
	active_scope_list[0]->insert(name.c_str(), QUESTION_TYPE);
	// I need to modify the insert in Scope to
	// take a 3rd parameter which is a AbstractQuestion *
	// and store that into the symbol table
	// I should be able to retrieve that 
	// AbstractQuestion* pointer later 
	return q;
}

AbstractStatement * ProcessNamedQuestion(const string &name
			, const string & q_txt , const DataType& dt 
			, const string & attribute_list_name )
{

	// This is preparatory work
	// for jumping between questions
	// store
	vector<string> active_push_vars;
	vector<string> active_pop_vars;
	for(unsigned int i=0; i< active_scope_list.size(); ++i){
		Scope* sc_ptr= active_scope_list[i];
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
	
	AbstractExpression * arr_sz=0;
	NamedStubQuestion* q=0;
	if(qscript_parser::flagIsAForBody_){
		cout << "flagIsAForBody_: " 
			<< qscript_parser::flagIsAForBody_ << endl;
		arr_sz = qscript_parser::recurse_for_index(
			qscript_parser::for_loop_max_counter_stack.size()-1);
		q=new NamedStubQuestion(QUESTION_TYPE, line_no
				, name, q_txt, q_type, no_mpn, dt , nr_ptr
				,qscript_parser::for_loop_max_counter_stack);
	} else {
		q=new NamedStubQuestion(QUESTION_TYPE, 
			line_no, name, q_txt, q_type, no_mpn, dt, nr_ptr);
	}
	question_list.push_back(q);
	//$$=q;
	active_scope_list[0]->insert(name.c_str(), QUESTION_TYPE);
	if(stack_cmpd_stmt.size()==0){
		print_err(compiler_internal_error, "compound statement stack "
			"is 0 when parsing a AbstractQuestion... exiting"
			, line_no, __LINE__, __FILE__  );
		exit(1);
	}
	CompoundStatement * cmpd_stmt_ptr=stack_cmpd_stmt.back();
	++(cmpd_stmt_ptr->counterContainsQuestions_);
	return q;
}

// Close namespace
}
