%{

//#include "common.h"
#include "tree.h"
#include "symtab.h"
#include "stmt.h"
#include "expr.h"
#include "named_attributes.h"
#include "named_range.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
	scope* active_scope;
	vector <scope*> active_scope_list;
	int nest_lev=0;
	int flag_cmpd_stmt_is_a_func_body=-1;
	bool flag_next_stmt_start_of_block=false;
	vector<bool> blk_start_flag;
	vector <stmt*> blk_heads;



	fstream debug_log_file("xtcc_debug.log", ios_base::out|ios_base::trunc);
	using std::string;
	void print_err(compiler_err_category cmp_err, 
		string err_msg, int line_no, 
		int compiler_line_no, string compiler_file_name);
	extern int line_no;
	extern noun_list_type noun_list[];

	/*
	noun_list_type noun_list[]= {
			{	"void"	, VOID_TYPE},
			{	"int8_t" ,INT8_TYPE},
			{	"int16_t" ,INT16_TYPE},
			{	"int32_t" ,INT32_TYPE},
			{	"float", FLOAT_TYPE},
			{	"double", DOUBLE_TYPE}
		};
	*/	


	question_type q_type;
#include "const_defs.h"
#include "xtcc_set.h"
	int no_mpn=0;
	xtcc_set xs;
	int yylex();
	void yyerror(const char * s);
	int no_errors;

	struct stmt* tree_root=0;
#include <vector>
	vector <question*> question_list;
	void generate_code();
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);
	const bool XTCC_DEBUG_MEM_USAGE=true;
	bool skip_func_type_check(const char * fname);
	vector<mem_addr_tab>  mem_addr;
	vector <func_info*> func_info_table;
	int check_parameters(struct expr* e, struct var_list* v);

        vector <string> attribute_list;
	vector <named_range*> named_stubs_list;
	vector <named_attribute_list> named_attributes_list;
        vector <stub_pair> stub_list;
	extern int if_line_no;



%}


%union {
	int ival;
	double dval;
	char name[MY_STR_MAX];
	char text_buf[MY_STR_MAX];
	datatype dt;
	struct stmt * stmt;
	struct expr * expr;
	//class question* ques;
	struct cmpd_stmt * c_stmt;

};

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

%token IF ELSE

%token STUBS_LIST


%type <expr> expression
%type <expr> expr_list


%%


prog: stmt_list {
		cerr << "prog: finished parse" << endl;
		tree_root=$1;
		while(tree_root->prev) 
			tree_root=tree_root->prev;
	}
	;

stmt_list: stmt {
		$$=$1;
		if(flag_next_stmt_start_of_block){
			blk_heads.push_back($1);
			//cout << "blk_heads.size(): " << blk_heads.size() << endl;
			//start_of_blk=$1;
			flag_next_stmt_start_of_block=false;
			blk_start_flag.pop_back();
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

decl_stmt: datatype NAME ';' {
		$$ = active_scope->insert($2, $1/*, line_no*/);
		//free($2);
		// -- why am i not freeing this?
	}
	| datatype NAME '=' expression ';'{
		$$ = active_scope->insert($2, $1, $4);
		// -- why am i not freeing this?
	}
	| datatype NAME '[' expression ']' ';'{
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		datatype dt=datatype(INT8_ARR_TYPE+($1-INT8_TYPE));
		$$ = active_scope->insert($2, dt, $4/*, line_no*/);
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
			//void *ptr=$$;
			//mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			//mem_addr.push_back(m1);
		}
		flag_next_stmt_start_of_block=true;
		blk_start_flag.push_back(flag_next_stmt_start_of_block);
		active_scope_list.push_back($$->sc);
		active_scope = $$->sc;
	}
	;



if_stmt:  IF '(' expression ')' stmt {
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
	;

	
expr_stmt:	expression ';' 
	{
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
		string name($1);
		string q_text($2);
		datatype dt=$4;
		range_question * q= new range_question(QUESTION_TYPE, line_no, 
			name, q_text, q_type, no_mpn, dt, xs);
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
		string name=$1;
		string q_txt=$2;
		datatype dt=$4;
		string attribute_list_name=$5;
		bool found=false;
		struct named_range* nr_ptr = 0;
		for(int i=0; i<named_stubs_list.size(); ++i){
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
	}
	;



expression: expression '+' expression {
		$$=new bin_expr($1, $3, oper_plus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '-' expression {
		$$=new bin_expr($1, $3, oper_minus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '*' expression {
		$$=new bin_expr($1, $3, oper_mult);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '/' expression {
		$$=new bin_expr($1, $3, oper_div);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '%' expression {
		$$=new bin_expr($1, $3, oper_mod);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	'-' expression %prec UMINUS {
		$$ = new un_expr($2, oper_umin);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '<' expression {
		$$=new bin_expr($1, $3, oper_lt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '>' expression {
		$$=new bin_expr($1, $3, oper_gt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression LEQ expression {
		$$=new bin_expr($1, $3, oper_le);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression GEQ expression {
		$$=new bin_expr($1, $3, oper_ge);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression ISEQ expression {
		$$=new bin_expr($1, $3, oper_iseq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression NOEQ expression {
		$$=new bin_expr($1, $3, oper_isneq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| expression LOGOR expression {
		$$=new bin_expr($1, $3, oper_or);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| expression LOGAND expression {
		cout << "LOGAND expr: " << endl;
		$$=new bin_expr($1, $3, oper_and);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		cout << "after LOGAND expr : " << endl;
	}
	| expression '=' expression {
		$$ = new bin_expr($1, $3, oper_assgn);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	NOT expression {
		$$ = new un_expr($2, oper_not);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	INUMBER	{
		$$ = new un2_expr($1);
		//cout << "got INUMBER: " << $1 << " type : " << $$->type << endl;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	FNUMBER {
		$$ = new un2_expr($1);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	NAME	{
		$$ = new un2_expr($1, oper_name );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| 	NAME '[' expression ']' %prec FUNC_CALL {
		$$ = new un2_expr(oper_arrderef, /*nametype,  se,*/ $1,$3);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($1);
	}
	| NAME '[' expression ',' expression ']'  %prec FUNC_CALL {
		$$ = new un2_expr(oper_blk_arr_assgn, $1,$3,$5);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($1);
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
		$$ = new un2_expr(strdup($1), oper_text_expr);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| 	'(' expression ')' %prec UMINUS{ 
		$$ = new un_expr($2, oper_parexp );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| expression IN range_allowed_values {
		$$ = new bin2_expr($1, xs, oper_in);
		xs.reset();
	}

	/*
	| NAME IN NAME {
		$$ = new bin2_expr($1, $3, oper_in);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	*/
	;


expr_list: expression { $$=$1; }
	| expr_list ',' expression {
		$$=link_chain($1,$3);
	}
	;

qtype: SP { q_type = spn; }
	| MP '(' INUMBER ')' { q_type = mpn; no_mpn = $3; }
	;

range_allowed_values:  '(' range_list ')' { }
	;


range_list: range
	| range_list ',' range
	;

range: 	INUMBER '-' INUMBER {
		if($3<=$1){
			print_err(compiler_sem_err, "2nd number in range <= 1st number",
					line_no, __LINE__, __FILE__  );

		} else {
			xs.range.push_back( pair<int,int>($1,$3));
		}
	}
	|	INUMBER {
		xs.indiv.insert($1);
	}
	;

stubs:     STUBS_LIST NAME {
		stub_list.resize(0);
	}'=' stub_list ';'{
		//cout <<"got attribute_list size: " << attribute_list.size() << endl;
		string stub_name=$2;
		struct named_range* nr_ptr= new named_range(NAMED_RANGE, line_no, stub_name,stub_list);
		named_stubs_list.push_back(nr_ptr);
		//$$=0;
		$$ = nr_ptr;
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

#include <unistd.h>
#include <string>
extern void yyrestart ( FILE *input_file );

void data_entry_loop();

using std::string;
int main(int argc, char* argv[]){
	int opterr=1, c;
	string fname;
	int fname_flag=0;
	
	while( (c=getopt(argc, argv, "f:"))!=-1 ){
		char ch=optopt;
		switch(c){
		case 'f':
			fname=optarg;
			fname_flag=1;
			break;
		case '?': 
			if(optopt == 'f' ) 
				cerr << " option -'" << optopt << "' requires an argument" << endl;
			else if (isprint(optopt)){
				cerr << " unknown option : '-" << optopt << "'" << endl;
			} else 	
				cerr << " unknown character " << optopt << endl;
			exit(1);
			break;
		default:
			cerr << "usage: " << endl
				<< argv[0] << " -f <input-file>\n" <<   endl ;
			exit(0);
		}
		if(fname_flag==1){
			break;
		}
	}
	if(!fname_flag){
		cout << "usage: " 
			<< endl
			<< argv[0] << " -f <input-file> "  << endl << endl;
		exit(0);
	}
	active_scope=new scope();
	active_scope_list.push_back(active_scope);

	FILE * yyin = fopen(fname.c_str(), "r");
	if(!yyin){
		cerr << " Unable to open: " << fname << " for read ... exiting" << endl;
		exit(1);
	}
	yyrestart(yyin);
	if( !yyparse() && !no_errors){
		cout << "Input parsed sucessfully: generating code" << endl;
		//data_entry_loop();
		generate_code();
	} else {
		cerr << "There were : " << no_errors << " errors in parse" << endl;
	}
	return no_errors;
}

#include <string>
using std::string;
#if 0
void print_err(compiler_err_category cmp_err, string err_msg, 
	int line_no, int compiler_line_no, string compiler_file_name){
	++no_errors;
	cerr << "xtcc " ;
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
#endif /* 0 */

#include <sstream>
/*
void data_entry_loop(){
	int ser_no;
	cout << "Enter Serial No (0) to exit: " << flush;
	cin >> ser_no;
	string jno="j_1001";
	while(ser_no!=0){
		stringstream fname_str;
		fname_str << jno << "_" << ser_no << ".dat";
		FILE * fptr = fopen(fname_str.str().c_str(), "w+b");
		tree_root->eval();
		cout << "Enter Serial No (0) to exit: " << flush;
		cin >> ser_no;
		for (int i=0; i<question_list.size(); ++i){
			fprintf(fptr, "%s: ", question_list[i]->name.c_str());
			for( set<int>::iterator iter=question_list[i]->input_data.begin();
					iter!=question_list[i]->input_data.end(); ++iter){
				fprintf(fptr, "%d ", *iter);
			}
			fprintf(fptr, "\n");
		}
		fclose(fptr);
	} 
}
*/

void print_header(FILE* script);
void print_close(FILE* script, ostringstream & program_code);
void generate_code(){
	string script_name("test_script.c");
	FILE * script = fopen(script_name.c_str(), "w");
	if(!script){
		cerr << "unable to open output file to dump script data: " << script_name << endl;
		exit(1);
	}
	ostringstream quest_defns, program_code;
	print_header(script);
	tree_root->generate_code(quest_defns, program_code);
	fprintf(script, "%s\n", quest_defns.str().c_str());
	print_close(script, program_code);
}

void print_header(FILE* script){
	fprintf(script, "#include <iostream>\n");
	fprintf(script, "#include <vector>\n");
	fprintf(script, "#include <string>\n");
	fprintf(script, "#include <sstream>\n");
	fprintf(script, "#include <fstream>\n");
	fprintf(script, "#include \"stmt.h\"\n");
	fprintf(script, "#include \"xtcc_set.h\"\n");
	fprintf(script, "#include \"stub_pair.h\"\n");
	fprintf(script, "#include \"symtab.h\"\n");
	fprintf(script, "#include \"debug_mem.h\"\n");
	fprintf(script, "fstream debug_log_file(\"xtcc_debug.log\", ios_base::out|ios_base::trunc);\n");

	fprintf(script, "using namespace std;\n");
	fprintf(script, "void read_data(const char * prompt);\n");
	fprintf(script, "extern vector<int> data;\n");
	fprintf(script, "vector <question*> question_list;\n");
	fprintf(script, "vector<mem_addr_tab>  mem_addr;\n");


	fprintf(script, "\tnoun_list_type noun_list[]= {\n");
	fprintf(script, "\t\t\t{\t\"void\"\t, VOID_TYPE},\n");
	fprintf(script, "\t\t\t{\t\"int8_t\" ,INT8_TYPE},\n");
	fprintf(script, "\t\t\t{\t\"int16_t\" ,INT16_TYPE},\n");
	fprintf(script, "\t\t\t{\t\"int32_t\" ,INT32_TYPE},\n");
	fprintf(script, "\t\t\t{\t\"float\", FLOAT_TYPE},\n");
	fprintf(script, "\t\t\t{\t\"double\", DOUBLE_TYPE}\n");
	fprintf(script, "\t\t};\n");
	fprintf(script, "\n");


	fprintf(script, "int main(){\n");

}

void print_close(FILE* script, ostringstream & program_code){

	fprintf(script, "\tint ser_no;\n");
	fprintf(script, "\t\tcout << \"Enter Serial No (0) to exit: \" << flush;\n");
	fprintf(script, "\t\tcin >> ser_no;\n");
	fprintf(script, "\t\tstring jno=\"j_1001\";\n");
	fprintf(script, "\t\twhile(ser_no!=0){\n");
	fprintf(script, "%s\n", program_code.str().c_str());
	fprintf(script, "\t\t\tstringstream fname_str;\n");
	fprintf(script, "\t\t\tfname_str << jno << \"_\" << ser_no << \".dat\";\n");
	fprintf(script, "\t\t\tFILE * fptr = fopen(fname_str.str().c_str(), \"w+b\");\n");
	fprintf(script,	"cout << \"Enter Serial No (0) to exit: \" << flush;\n");
	fprintf(script, "cin >> ser_no;\n");
	fprintf(script, "\tfor (int i=0; i<question_list.size(); ++i){\n");
	fprintf(script, "\t\tfprintf(fptr, \"%%s: \", question_list[i]->name.c_str());\n");
	fprintf(script, "\t\tfor( set<int>::iterator iter=question_list[i]->input_data.begin();\n");
	fprintf(script, "\t\t\t\titer!=question_list[i]->input_data.end(); ++iter){\n");
	fprintf(script, "\t\t\tfprintf(fptr, \"%%d \", *iter);\n");
	fprintf(script, "\t\t}\n");
	fprintf(script, "\t\tfprintf(fptr, \"\\n\");\n");
	fprintf(script, "\t\tquestion_list[i]->input_data.clear();\n");
	fprintf(script, "\t}\n");
	fprintf(script, "\tfclose(fptr);\n");
	fprintf(script, "\n");
	fprintf(script, "\n\t} /* close while */\n");
	fprintf(script, "\n} /* close main */\n");
}


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

	bool skip_func_type_check(const char * fname){
		const char * skip_func_type_check_list[] = {"printf" };
		for (unsigned int i=0; i<sizeof(skip_func_type_check_list)/sizeof(skip_func_type_check_list[0]); ++i){
			if(!strcmp(fname, skip_func_type_check_list[i])){
				return true;
			}
		}
		return false;
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

