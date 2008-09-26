/*
 * The main grammar for the qscript parser
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
#include <iostream>
#include "const_defs.h"
//#include "qscript_types.h"
#include "../xtcc/trunk/symtab.h"
#include "../xtcc/trunk/expr.h" 
#include "q_expr.h" 
#include "range_set.h"
#include "stub_pair.h"
#include "named_range.h"
#include "question.h"

	question_type q_type;
	int no_mpn=0;
	using std::cout;
	using std::endl;
	vector <scope*> active_scope_list;
	scope* active_scope;
	extern char * yytext;
	int no_errors=0;
	int no_warn=0;
	extern int line_no;
	int yylex();
	void yyerror(char * s);
	const bool XTCC_DEBUG_MEM_USAGE=1;
	bool skip_func_type_check(const char * fname);
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);
	int check_parameters(struct expr* e, struct var_list* v);
	extern int if_line_no;
	int nest_lev=0;
	int flag_cmpd_stmt_is_a_func_body=-1;
	bool flag_next_stmt_start_of_block=false;
	vector<bool> blk_start_flag;
	vector <stmt*> blk_heads;

	char default_work_dir[]="xtcc_work";
	char * work_dir=default_work_dir;
        range_data r_data;
        vector <string> attribute_list;
	vector <named_range> named_stubs_list;
        vector <stub_pair> stub_list;


	noun_list_type noun_list[]= {
			{	"void"	, VOID_TYPE},
			{	"int8_t" ,INT8_TYPE},
			{	"int16_t" ,INT16_TYPE},
			{	"int32_t" ,INT32_TYPE},
			{	"float", FLOAT_TYPE},
			{	"double", DOUBLE_TYPE}
		};
	vector<mem_addr_tab>  mem_addr;
#include <vector>
	using std::vector;
#include <fstream>
#include <map>
	fstream debug_log_file("xtcc_debug.log", ios_base::out|ios_base::trunc);
	map<string, symtab_ent*>::iterator find_in_symtab(string id);
	void print_err(compiler_err_category cmp_err, string err_msg, 
		int line_no, int compiler_line_no, string compiler_file_name);
#include "../xtcc/trunk/stmt.h"
	vector <func_info*> func_info_table;
%}

%union {
	double dval;
	int ival ;
	char name[MY_STR_MAX];
	char text_buf[MY_STR_MAX];
	datatype dt;
	struct expr * expr;
	struct stmt * stmt;
	struct cmpd_stmt * c_stmt;
	class question* ques;
};


%token IF ELSE
%token <dval> FNUMBER
%token <ival> INUMBER
%token <name> NAME
%token QTEXT
%token SP
%token MP
%token <dt> VOID_T
%token <dt> INT8_T
%token <dt> INT16_T
%token <dt> INT32_T
%token <dt> FLOAT_T
%token <dt> DOUBLE_T
%type <dt> datatype

%token '['
%token ']'
%token '('
%token ')'
%token '='

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

%type <expr> expression
%type <expr> expr_list
%type <expr> q_expr
%token CONTINUE BREAK
%token <text_buf> TEXT

%type <stmt> decl_stmt
%type <stmt> stmt
%type <stmt> stmt_list
%type <c_stmt> cmpd_stmt	
%type <c_stmt> open_curly	
%type <stmt> ques	
%type <stmt> stubs	
%type <stmt> attributes	
%token ATTRIBUTE_LIST
%token STUBS_LIST

%%

prog:stmt_list
	;

stmt_list: stmt { 
		   cerr << "chain 1:"  << $1 << endl; $$=$1; 
		   cerr << "after $$=$1;" << endl;
		if(flag_next_stmt_start_of_block){
			blk_heads.push_back($1);
			//cout << "blk_heads.size(): " << blk_heads.size() << endl;
			//start_of_blk=$1;
			flag_next_stmt_start_of_block=false;
			blk_start_flag.pop_back();
		}
	}
	| stmt_list stmt {
		$$=link_chain($1, $2);
	}
	;
	
stmt: ques
	| expression ';' { 
		if($1->isvalid()){
			$$ = new expr_stmt(TEXPR_STMT, line_no, $1);
			if(XTCC_DEBUG_MEM_USAGE){
				mem_log($$, __LINE__, __FILE__, line_no);
			}
		} else {
			$$ = new expr_stmt(ERROR_TYPE, line_no, $1);
			if(XTCC_DEBUG_MEM_USAGE){
				mem_log($$, __LINE__, __FILE__, line_no);
			}
		}
	}
	| IF '(' expression ')' stmt {
		$$=new if_stmt(IFE_STMT,if_line_no,$3,$5,0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| IF '(' expression ')' stmt ELSE stmt {
		$$=new if_stmt(IFE_STMT,if_line_no,$3,$5,$7);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| cmpd_stmt { 
		$$=$1;
	}
	| decl_stmt {
		$$=$1;
	}
	| stubs {
		$$=0;
	}
	| attributes{
		$$=0;
	}
	;

decl_stmt: datatype NAME ';' {
		$$ = active_scope->insert($2, $1/*, line_no*/);
		free($2);
	   }
	| datatype NAME '=' expression ';'{
		$$ = active_scope->insert($2, $1, $4);

	}
	| datatype NAME '[' expression ']' ';'{
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		datatype dt=datatype(INT8_ARR_TYPE+($1-INT8_TYPE));
		$$ = active_scope->insert($2, dt, $4/*, line_no*/);
		free($2);
	}
	;

cmpd_stmt: open_curly stmt_list '}' {
		active_scope_list.pop_back();
		int tmp=active_scope_list.size()-1;
		if(tmp==-1) { 
			active_scope = 0;
			cerr << "Error: active_scope = NULL: should not happen: line_no:" << line_no
				<< endl;
			++no_errors;
			$$=new struct cmpd_stmt(ERROR_TYPE, line_no, 0);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		} else { active_scope = active_scope_list[tmp]; }
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
		
		$$=$1;
	}
	;


open_curly:	'{' {
		++nest_lev;
		$$ = new cmpd_stmt(CMPD_STMT, line_no, flag_cmpd_stmt_is_a_func_body);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
		mem_addr.push_back(m1);
		if(flag_cmpd_stmt_is_a_func_body>=0){
			$$->sc=func_info_table[flag_cmpd_stmt_is_a_func_body]->func_scope;
			// reset the flag
			flag_cmpd_stmt_is_a_func_body=-1;
		} else {
			$$->sc= new scope();
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		}
		flag_next_stmt_start_of_block=true;
		blk_start_flag.push_back(flag_next_stmt_start_of_block);
		active_scope_list.push_back($$->sc);
		active_scope = $$->sc;
	}
	;

ques: NAME TEXT qtype datatype range_allowed_values';' {
	      cout << " got question " << endl;
	      string name=$1;
	      string q_txt=$2;
	      $$=new range_question(line_no, QUESTION_TYPE, name, q_txt, q_type, no_mpn, $4, r_data);
	      r_data.reset();
	}
	| NAME TEXT qtype datatype NAME ';' {
		cout << " got named stublist type question" << endl;
	      string name=$1;
	      string q_txt=$2;
	      string attribute_list_name=$5;
	      $$=new named_stub_question(line_no, QUESTION_TYPE, name, q_txt, q_type, no_mpn, $4, attribute_list_name);
		
	}
	;


qtype: SP { q_type = spn; }
	| MP '(' INUMBER ')' { q_type = mpn; no_mpn = $3; }
	;

datatype: INT8_T
	|INT16_T
	|INT32_T  	
	|FLOAT_T
	|DOUBLE_T
	;

range_allowed_values:  '(' number_range_list ')' { }
	;

number_range_list: number_range
	| number_range_list ',' number_range
	;

number_range: INUMBER '-' INUMBER {
                if( $3 <=$1 ) {
                        cout << "error on lineno: " << line_no
                                << "2nd number in range <= 1st number"
                                << endl;
                } else {
			if(r_data.rcount<MAX_RANGE_ELEMENTS/2){
				r_data.ran_start_end[r_data.rcount*2  ]=$1;
				r_data.ran_start_end[r_data.rcount*2+1]=$3;
				++r_data.rcount;
			} else {
				cerr << "range_list: ran_start_end rcount : buffer overflow:\n";
				cerr << " I should use vector and get rid of this restriction\n";
			}
			
                }
        }
	| INUMBER {
                if(r_data.icount<MAX_RANGE_ELEMENTS){
                        r_data.ran_indiv[r_data.icount]=$1;
			++r_data.icount;
		} else {
                        cerr << "range_list: ran_indiv : buffer overflow:\n";
				cerr << " I should use vector and get rid of this restriction\n";
                }
        }
	;

include(`../xtcc/trunk/expr.y.inc')

expression: q_expr {
		$$=$1;
	}

q_expr: 	NAME IN range_allowed_values {
			cout << " got NAME IN range_allowed_values " << endl;
			$$=new q_expr($1, r_data, oper_q_expr_in);
			r_data.reset();
		}
	|	NAME '[' expression ']' IN range_allowed_values {
		cout << "NAME '[' expression ']' IN range_allowed_values " << endl;
			$$=new q_expr($1, r_data, oper_q_expr_arr_in);
			r_data.reset();
	}
	| 	COUNT '(' NAME ')' {
		cout << "COUNT '(' NAME ')' " << endl;
		$$=0;
	}
	;

expr_list: expression { /*$$=$1;*/ }
	| expr_list ',' expression {
		//$$=link_chain($1,$3);
	}
	;

text_list:      TEXT ';' {
                        string s1=$1;
                        attribute_list.push_back(s1);
                }
        | text_list TEXT ';' {
                        string s1=$2;
                        attribute_list.push_back(s1);
        }
        ;


attributes:     ATTRIBUTE_LIST NAME '=' {
		attribute_list.resize(0);
		//cout << "resize attribute_list to 0\n";
	} text_list ';' {
		//cout <<"got attribute_list size: " << attribute_list.size() << endl;
		$$=0;
	}
        ;


stubs:     STUBS_LIST NAME {
		stub_list.resize(0);
		//cout << "resize attribute_list to 0\n";
	}'=' stub_list ';'{
		//cout <<"got attribute_list size: " << attribute_list.size() << endl;
		string stub_name=$2;
		struct named_range nr1(stub_name,stub_list);
		named_stubs_list.push_back(nr1);
		$$=0;
	}
	;


stub_list:	TEXT INUMBER {
                        string s1=$1;
			int code=$2;
			struct stub_pair pair1(s1,code);
			stub_list.push_back(pair1);
	}
	| stub_list TEXT INUMBER {
                        string s1=$2;
			int code=$3;
			struct stub_pair pair1(s1,code);
			stub_list.push_back(pair1);
			//cout << "chaining stublist" << endl;
	}
	;

%%

int main(){
	active_scope=new scope();
	active_scope_list.push_back(active_scope);
	return yyparse(); 
}

#include <string>
#if 0
using std::string;
void print_err(compiler_err_category cmp_err, string err_msg, 
	int line_no, int compiler_line_no, string compiler_file_name){
	++no_errors;
	cerr << "qscript " ;
	switch(cmp_err){
		case compiler_syntax_err: 
			cerr << "syntax error: ";
		break;
		case compiler_sem_err:
			cerr << "semantic error: ";
		break;
		case compiler_internal_error:
			cerr << "compiler internal error: " ;
		break;	
		default:
			cerr << "internal compiler error - error code category missing in switch statement: compiler file: " 
				<< __FILE__ << " compiler src code lineno: " << __LINE__ << endl;
			
	}
	cerr << " line_no: " << line_no << " "<< err_msg << ", compiler line_no: " 
		<< compiler_line_no << ", compiler_file_name: " << compiler_file_name << endl;
}
#endif // 0


#if 0
map<string, symtab_ent*>::iterator find_in_symtab(string id){
	bool found=false;
	int i=active_scope_list.size()-1;

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


bool check_type_compat(datatype typ1, datatype typ2){
	//cout << "check_type_compat: line_no: I have to convert the below code into a function:"  << line_no << endl;
	datatype td1=typ1;
	datatype td2=typ2;
	if(td1>=INT8_REF_TYPE && td1<=DOUBLE_REF_TYPE) td1=datatype(INT8_TYPE + typ1-INT8_REF_TYPE);
	if(td2>=INT8_REF_TYPE && td2<=DOUBLE_REF_TYPE) td2=datatype(INT8_TYPE + typ2-INT8_REF_TYPE);
	if((td1>=INT8_TYPE&&td1<=DOUBLE_TYPE) &&
			td2>=INT8_TYPE&&td2<=DOUBLE_TYPE){
		if(td1>=td2){
			return true;
		} else {
			/*
			cerr << "ERROR: td1< td2 Assigning unhandle_able Type to var:  line_no:" << line_no 
				<< " LHS type: " << typ1 << " after converting LHS: " << td1
				<< " RHS type: " << typ2 << " after converting RHS: " << td2
				<< endl;
			*/	
			return false;
		}
	} else {
		/*
		cerr << "ERROR: Assigning unhandle_able Type to var:  line_no:" << line_no 
			<< " LHS type: " << typ1 << " after converting LHS: " << td1
			<< " RHS type: " << typ2 << " after converting RHS: " << td2
			<< endl;
		*/	
		return false;
	}
}

bool 	void_check( datatype & type1, datatype & type2, datatype& result_type){
	if(type1==VOID_TYPE){
		print_err(compiler_sem_err, " lhs of binary expr is of type void ", 
			line_no, __LINE__, __FILE__);
		result_type=ERROR_TYPE;
		++no_errors;
		return false;
	} 
	if( type2==VOID_TYPE){
		print_err(compiler_sem_err, " rhs of binary expr is of type void ", 
			line_no, __LINE__, __FILE__);
		result_type=ERROR_TYPE;
		++no_errors;
		return false;
	}
	if( !(type1==VOID_TYPE && type2==VOID_TYPE)){
		result_type=type1 > type2? type1: type2;
		return true;
	}
	//return true;
}
#endif //0

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

int check_parameters(expr* e, var_list* v){
	debug_log_file << "check_parameters: called" << endl;
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
				debug_log_file << "varname: "<< fparam->var_name << " chk_param_counter: " 
					<< chk_param_counter << " passed " << endl;
			}
		} else if ((etype>=INT8_ARR_TYPE&&etype<=DOUBLE_ARR_TYPE)&&
				(fptype>=INT8_ARR_TYPE&&fptype<=DOUBLE_ARR_TYPE)&&
				(etype==fptype)){
			debug_log_file << "varname: "<< fparam->var_name << " chk_param_counter: " 
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
		e_ptr=e_ptr->next;
		fparam=fparam->next;
		chk_param_counter=chk_param_counter+1;
	}
	if(match==true){
		if(e_ptr==0&& fparam==0){
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


	bool skip_func_type_check(const char * fname){
		const char * skip_func_type_check_list[] = {"printf" };
		for (unsigned int i=0; i<sizeof(skip_func_type_check_list)/sizeof(skip_func_type_check_list[0]); ++i){
			if(!strcmp(fname, skip_func_type_check_list[i])){
				return true;
			}
		}
		return false;
	}
