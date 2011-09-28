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
	AbstractStatement * root;
	vector <int> stub_number;
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
%type <nr_ptr> stub
%type <nr_ptr> stub_list
%type <stmt> stmt
%type <stmt> stmt_list
%type <stmt> randomize_stub_statement
%type <stmt> prog

%%

prog: stmt_list {
	root = $1;
	}
	;

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
		stub_number.push_back(0);
		//active_named_range = new named_range (NAMED_RANGE, line_no, $2);
	} '=' stub_list ';' {
		//string stub_name=$2;
		//struct named_range* nr_ptr= 
		//	new named_range(NAMED_RANGE, 
		//			line_no, stub_name,stub_list);
		//named_stubs_list.push_back(nr_ptr);
		//$$ = nr_ptr;
		//active_named_range->groupPtr_ = $4;
		//active_named_range = new NamedRangeGroup ($2);
		//active_named_range->groupName_ = $2;
		//active_named_range-
		//$$ = $5;
		NamedRangeGroup * nrg = new NamedRangeGroup ($2);
		AbstractNamedRange * nr_ptr = $5;
		cout << "climbing up the chain" << endl;
		while (nr_ptr->prev_nr) {
			cout << "." ;
			nr_ptr = nr_ptr->prev_nr;
		}
		cout << endl;
		nrg->groupPtr_ = nr_ptr;
		$$ = nrg;

		int highest_stub_number_in_group = stub_number.back() ;
		 
		stub_number.pop_back(); 
		cout << "highest_stub_number_in_group: " 
			<< $2 << ": " 
			<< highest_stub_number_in_group
			<< endl;
		stub_number.pop_back();
	}
	;


simple_stub_list: simple_stub
	| simple_stub_list ',' simple_stub
	;

simple_stub:	TEXT INUMBER {
		string s1=$1;
		int32_t code=$2;
		++stub_number[stub_number.size()-1];
		struct stub_pair pair1 (s1, code, stub_number.back());
		stub_list.push_back (pair1);
	}
	| TEXT INUMBER MUTEX {
		string s1=$1;
		int32_t code=$2;
		++stub_number[stub_number.size()-1];
		struct stub_pair pair1 (s1, code, true, stub_number.back());
		stub_list.push_back(pair1);
	}
	;

stub: simple_stub_list {
		NamedRangeList * nrl = new NamedRangeList();
		nrl->stubs = stub_list;
		stub_list.clear();
		$$ = nrl;
	}
	| STUB_GROUP NAME { ++stub_number[stub_number.size()-1]; stub_number.push_back(0); } '{' stub_list  '}' {
		/* continue from here:
		   treat this as a named compound statement - just like in the main qscript grammar
		   */
		/*
		if (stub_list.size() > 0) {
			active_named_range.set_stubs(stub_list);
			stub_list.resize(0);
			active_named_range.stubs_come_first = true;
		}
		++stub_group_nest_level;
		active_named_range_stack.push_back (active_named_range);
		active_named_range->sub_group_ptr = new named_range (NAMED_RANGE, line_no, $2);
		active_named_range = active_named_range->sub_group_ptr;
		*/
		AbstractNamedRange * nr_ptr = $5;
		cout << "climbing up the chain" << endl;
		while (nr_ptr->prev_nr) {
			cout << "." ;
			nr_ptr = nr_ptr->prev_nr;
		}
		cout << endl;

		NamedRangeGroup * nrg = new NamedRangeGroup ($2);
		nrg->groupPtr_ = nr_ptr;
		$$ = nrg;
		int highest_stub_number_in_group = stub_number.back() ;
		 
		stub_number.pop_back(); 
		cout << "highest_stub_number_in_group: " 
			<< $2 << ": " 
			<< highest_stub_number_in_group
			<< endl
	}
	/*
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
	*/
	;

stub_list: stub
	| stub_list stub {
		AbstractNamedRange * nr_ptr1=$1, *nr_ptr2=$2;
		NamedRangeList * nrl_ptr1 =0, *nrl_ptr2=0;
		NamedRangeGroup *nrg_ptr1 =0, *nrg_ptr2=0;
		/*
		if (	nrl_ptr1 = dynamic_cast<NamedRangeList*> (nr_ptr1) && 
			nrl_ptr2 = dynamic_cast<NamedRangeList*> (nr_ptr2) ) {
			nrl_ptr1->next_nr = nrl_ptr2;
			nrl_ptr2->prev_nr = nrl_ptr1;
			cout << "this case should never be - as the grammar would prevent it. all such cases would fold into simple_stub_list"
				<< endl;
		} else if (	nrg_ptr1 = dynamic_cast<NamedRangeGroup*> (nr_ptr1) &&
				nrl_ptr2 = dynamic_cast<NamedRangeList*> (nr_ptr2) ) {
			nrg_ptr1->groupPtr_ = nrl_ptr2;
			$$ = nrg_ptr1;
		} else if (	nrg_ptr1 = dynamic_cast<NamedRangeGroup*> (nr_ptr1) &&
				nrg_ptr2 = dynamic_cast<NamedRangeGroup*> (nr_ptr2) ) {
			nrg_ptr1->groupPtr_ = nrg_ptr2;
			$$ = nrg_ptr2;
		} else if (	nrg_ptr1 = dynamic_cast<NamedRangeGroup*> (nr_ptr1) &&
				nrl_ptr2 = dynamic_cast<NamedRangeList*>  (nr_ptr2) ) {
			nrg_ptr1->next_nr = nrg_ptr2;
			$$ = nrg_ptr2;
		}
		*/

		$1->Print();
		$2->Print();
		cout << "connecting: " << endl;
		$1->next_nr = $2;
		$2->prev_nr = $1;
		$$ = $2;
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
	FILE * yyin = fopen("random_test2.input", "rb");
	if (!yyin){
		cerr << " Unable to open: random_test.input "  << " for read ... exiting" << endl;
		exit(1);
	}
	yyrestart(yyin);
	if (!yyparse() && !no_errors) {
		cout << "sucessfully parsed" << endl;
		AbstractNamedRange * nr_ptr = dynamic_cast <AbstractNamedRange*> (root);
		if (nr_ptr) {
			nr_ptr->Print();
		} else {
			cout << "not a AbstractNamedRange" << endl;
		}
	}
}
