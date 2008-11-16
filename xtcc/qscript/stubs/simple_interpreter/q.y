%{

#include "common.h"	
#include "stmt.h"	
#include <string>
#include <iostream>
	using std::string;
	void print_err(compiler_err_category cmp_err, 
		string err_msg, int line_no, int compiler_line_no, string compiler_file_name);
	extern int line_no;

	question_type q_type;
#include "const_defs.h"
#include "xtcc_set.h"
	int no_mpn=0;
	xtcc_set xs;
	int yylex();
	void yyerror(const char * s);
	int no_errors;

	struct stmt* tree_root=0;

%}


%union {
	int ival;
	char name[MY_STR_MAX];
	char text_buf[MY_STR_MAX];
	datatype dt;
	struct stmt * stmt;
	//class question* ques;
};

%token <ival> INUMBER
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
%type <stmt> question
%type <stmt> question_list



%%


prog: question_list {
		tree_root=$1;
		while(tree_root->prev) 
			tree_root=tree_root->prev;
	}
	;

question_list: question {
		$$=$1;
	}
	| question_list question {
		$1->next=$2;
		$2->prev=$1;
		$$=$2;
	}
	;

question: NAME TEXT qtype datatype range_allowed_values ';' {
		  string name($1);
		  string q_text($2);
		  datatype dt=$4;
		  $$ = new q_stmt(line_no, name, q_text, q_type, no_mpn, dt, xs);
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
	|STRING_T
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


%%

#include <unistd.h>
#include <string>
extern void yyrestart ( FILE *input_file );

using std::string;
int main(int argc, char* argv[]){
	int opterr=1, c;
	string fname;
	int fname_flag=0;
	
	while( (c=getopt(argc, argv, "f:"))!=-1 ){
		char ch=optopt;
		cout << "ch: " << ch << endl;
		switch(c){
		case 'f':
			fname=optarg;
			fname_flag=1;
			cout << " got fname: " << fname << endl;
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
			cerr << "def usage: " << endl
				<< argv[0] << " -f <input-file>\n" <<   endl << "hello\t" << endl;
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
	FILE * yyin = fopen(fname.c_str(), "r");
	if(!yyin){
		cerr << " Unable to open: " << fname << " for read ... exiting" << endl;
		exit(1);
	}
	yyrestart(yyin);
	if( !yyparse()){
		cout << "Input parsed sucessfully: starting interpreter" << endl;
		tree_root->eval();
	} else {
		cerr << "There were : " << no_errors << " in parse" << endl;
	}
	return no_errors;
}

#include <string>
using std::string;
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
