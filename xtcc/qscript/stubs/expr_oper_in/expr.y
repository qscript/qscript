%{
#define MY_STR_MAX 50
#include "stmt.h"
#include "expr.h"
#include "range_set.h"
#include "symtab.h"
#include <iostream>
	range_data r_data;
	extern int line_no;
	int yylex();
	int no_errors=0;
	void yyerror(char * s);
	struct stmt* tree_root;
	string get_temp_name();



%}


%union {
	datatype dt;
	int ival ;
	char name[MY_STR_MAX];
	struct expr * expr;
	struct stmt * stmt;
};

%token <ival> INUMBER
%type <expr> expr
%type <stmt> stmt
%type <stmt> stmt_list
%token <name> NAME
%nonassoc IN
%left LOGAND

%type <dt> range_allowed_values

%%

prog: stmt_list {
	tree_root=$1;
		while($1->prev){
			tree_root=$1->prev;
		}
	}

stmt_list: stmt { 
		$$=$1;
	}
	| stmt_list stmt {
		$1->next = $2;
		$2->prev=$1;
		$$=$2;
	}
	;

stmt: expr ';' {
		$$ = new expr_stmt(line_no, $1);
	}
	;



expr: expr LOGAND expr {
	}
	| NAME IN range_allowed_values {
		$$=new bin2_expr($1, r_data, oper_in);
	}
	;

range_allowed_values: '(' number_range_list ')' { 
		$$=UNNAMED_RANGE;
	}
	;


number_range_list: number_range {
	}
	| number_range_list ',' number_range {
	}
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

%%


int main(){
	return yyparse();
	for(int i=0; i<1000; i++){
		cout << get_temp_name() << endl;
	}
	return 0;
}


string get_temp_name(){
	// about a billion temporaries before we run out
	const int max_temp=10;
	static int count=0;
	char buffer[max_temp];
	char op_buf[max_temp];
	int dividend=count;

	buffer[0]='0'; buffer[1]='\0';

	int j=0;
	do {
		int rem = dividend%10;
		dividend=dividend/10;
		buffer[j++]='0' + rem;
	} while(dividend>0);
	/*
	for(int i=0 ; dividend/10>0; dividend=dividend/10,++i,++j){
		//int quot = dividend/10;
		int rem = dividend%10;
		buffer[j]='0' + rem;
	}
	*/
	buffer[j]='\0';
	for(int i=j-1; i>=0; --i){
		op_buf[j-1-i]=buffer[i];
	}
	op_buf[j]='\0';
	string s(op_buf);
	++count;
	//cout << s << endl;
	string s1="temp_"+s;
	return s1;
}
