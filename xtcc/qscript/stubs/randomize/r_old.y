%{
#include <vector>
#include <iostream>
	
#include "AbstractStatement.h"
//#include "named_range.h"
#include "new_named_range.h"
#include "const_defs.h"

	using std::vector;
	using std::endl;
	using std::cout;
	using std::cerr;

        vector <stub_pair> stub_list;
	//vector <named_range*> named_stubs_list;
	int32_t line_no = 1;
	int32_t no_errors = 0;
	void yyerror(const char * s);
	int32_t yylex();
	int stub_group_nest_level = 0;
	//named_range * active_named_range = 0;
	//vector <named_range*> active_named_range_stack;
	AbstractNamedRange * active_named_range;
	vector <AbstractNamedRange*> active_named_range_stack;
%}


%union {
	//type_qualifier type_qual;
	int32_t ival;
	//double dval;
	char name[MY_STR_MAX];
	char text_buf[MY_STR_MAX];
	//DataType dt;
	struct AbstractStatement * stmt;
	struct AbstractNamedRange * nr_ptr;
}


%token STUBS_LIST
%token RANDOMIZE
%token MUTEX
%token STUB_GROUP
%token <name> NAME
%token <ival> INUMBER
%token <text_buf> TEXT

%type <stmt> stubs
%type <stmt> stmt
%type <stmt> stmt_list
%type <stmt> randomize_stub_statement
%type <nr_ptr> stubs
%type <nr_ptr> stub_list

%%

stmt_list: stmt {
		$$=$1;
	}
	| stmt_list stmt{
		$1->next_=$2;
		$2->prev_=$1;
		$$=$2;
	}
	;

stmt: 		stubs
	| randomize_stub_statement ';'
	;

stubs:	STUBS_LIST NAME {
		stub_list.resize(0);
		//active_named_range = new named_range (NAMED_RANGE, line_no, $2);
		active_named_range = new NamedRangeGroup ($2);
	} '=' stub_list ';' {
		//string stub_name=$2;
		//struct named_range* nr_ptr= 
		//	new named_range(NAMED_RANGE, 
		//			line_no, stub_name,stub_list);
		//named_stubs_list.push_back(nr_ptr);
		//$$ = nr_ptr;
		active_named_range->groupPtr_ = $4;
		$$ = active_named_range;
	}
	;


stub_list: stub
	| stub_list stub
	;

stub:	TEXT INUMBER {
		if (active_named_range == 0) {
			active_named_range = new NamedRangeList();
		}
		active_named_range->stubs.push_back( struct stub_pair(s1, code));
		//string s1=$1;
		//int32_t code=$2;
		//struct stub_pair pair1 (s1, code);
		//stub_list.push_back (pair1);
	}
	| TEXT INUMBER MUTEX {
		if (active_named_range == 0) {
			active_named_range = new NamedRangeList();
		}
		active_named_range->stubs.push_back( struct stub_pair(s1, code, true));
		//string s1=$1;
		//int32_t code=$2;
		//struct stub_pair pair1 (s1, code, true);
		//stub_list.push_back(pair1);
	}
	| STUB_GROUP NAME '{' {
		/* continue from here:
		   treat this as a named compound statement - just like in the main qscript grammar
		   */
		if (stub_list.size() > 0) {
			active_named_range.set_stubs(stub_list);
			stub_list.resize(0);
			active_named_range.stubs_come_first = true;
		}
		++stub_group_nest_level;
		active_named_range_stack.push_back (active_named_range);
		//active_named_range->sub_group_ptr = new named_range (NAMED_RANGE, line_no, $2);
		//active_named_range = active_named_range->sub_group_ptr;
		active_named_range = active_named_range->sub_group_ptr;
	}
	| '}' {
		if (stub_group_nest_level <= 0) {
			++no_errors;
			cerr << "incorrect } in stub group nesting, line_no:"
				<< line_no << endl;
		} else {
			if (stub_list.size() > 0) {
				active_named_range.set_stubs(stub_list);
				stub_list.resize(0);
				active_named_range.stubs_come_first = true;
			}
			active_named_range_stack.back()->sub_group_ptr = active_named_range;
			active_named_range = 
				active_named_range_stack.pop_back();
		}
		--stub_group_nest_level;
	}
	;

randomize_stub_statement: RANDOMIZE STUBS_LIST NAME {
		$$ = 0;
	}
	;

%%
#include <cstdio>

void yyrestart(FILE *input_file);
int32_t yyparse();
int main()
{
	FILE * yyin = fopen("random_test.input", "rb");
	if (!yyin){
		cerr << " Unable to open: random_test.input "  << " for read ... exiting" << endl;
		exit(1);
	}
	yyrestart(yyin);
	if (!yyparse() && !no_errors) {
		cout << "sucessfully parsed" << endl;
	}
}
