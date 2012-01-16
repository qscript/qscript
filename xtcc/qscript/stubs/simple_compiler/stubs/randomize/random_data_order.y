%{
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <sys/types.h>
	
#include "const_defs.h"
#include "AbstractStatement.h"
#include "new_named_range.h"

	using std::vector;
	using std::stringstream;
	using std::string;
	using std::endl;
	using std::cout;
	using std::cerr;

        vector <stub_pair> stub_list;
	int32_t line_no = 1;
	int32_t no_errors = 0;
	void yyerror(const char * s);
	int32_t yylex();

	vector <AbstractNamedRange*> vec_abs_nr;
	vector <int> no_vec;
	vector <int> stub_number;
	AbstractStatement * root;
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

%token <name> NAME
%token <ival> INUMBER
%token <text_buf> TEXT

%type <stmt> prog
%type <stmt> stmt
%type <stmt> stmt_list

%type <nr_ptr> randomized_data_order
%type <nr_ptr> randomized_data_list
%type <nr_ptr> randomized_data
%type <nr_ptr> simple_number_list

%%

prog: stmt_list {
		root = $1;
	}
	;

stmt_list: stmt {
	 	//$$ = $1;
	}
	| stmt_list stmt {
		//$1->next_=$2;
		//$2->prev_=$1;
		//$$=$2;
	}
	;

stmt: randomized_data_order {
	$$ = $1;
	cout << "parsed randomized_data_order" << endl;
	}
	;

randomized_data_order: '{' NAME ':' { ++stub_number[stub_number.size()-1]; stub_number.push_back(0); } randomized_data_list '}' {
		AbstractNamedRange * nr_ptr = $5;
		//cout << "climbing up the chain" << endl;
		while (nr_ptr->prev_nr) {
			//cout << "." ;
			nr_ptr = nr_ptr->prev_nr;
		}
		//cout << endl;
		string grp_name = $2;
		NamedRangeGroup * nrg = new NamedRangeGroup (grp_name, stub_number[stub_number.size()-2]);
		nrg->groupPtr_ = nr_ptr;
		$$ = nrg;
		cout << "NamedRangeGroup: " << grp_name << endl;
		stub_number.pop_back();
	}
	;

randomized_data_list: randomized_data {
			    $$ = $1;
		}
		| randomized_data_list randomized_data {
			$1->next_nr = $2;
			$2->prev_nr = $1;
			AbstractNamedRange * nr = $2;
			NamedRangeGroup * nrg = dynamic_cast<NamedRangeGroup*> (nr);
			if (nrg) {
				cout << "chaining: " << nrg->groupName_ << endl;
			}
			$$ = $2;
		}
		;


randomized_data:    simple_number_list ';' {
			NamedRangeList * nrl = new NamedRangeList();
			nrl->stubs = stub_list;
			stub_list.clear();
			$$ = nrl;
		    }
		    | randomized_data_order   {
			$$ = $1;
			cout << " got nested randomized_data_order: " << endl;
		    }
		    ;

simple_number_list: INUMBER {
			//no_vec.push_back ($1);
			string s1 = "dummy";
			int32_t code=$1;
			++stub_number[stub_number.size()-1];
			struct stub_pair pair1 (s1, code, stub_number.back());
			stub_list.push_back (pair1);
		  }
		  | simple_number_list INUMBER {
			//no_vec.push_back ($2);
			string s1 = "dummy";
			int32_t code=$2;
			++stub_number[stub_number.size()-1];
			struct stub_pair pair1 (s1, code, stub_number.back());
			stub_list.push_back (pair1);
		  }
		  ;


%%

#include <cstdio>
#include <vector>
#include <sys/types.h>

#include "const_defs.h"

void yyrestart(FILE *input_file);
int32_t yyparse();
int main()
{
	FILE * yyin = fopen("randomized_data_output_test.input", "rb");
	if (!yyin) {
		cerr << " Unable to open:  randomized_data_output_test.input"  << " for read ... exiting" << endl;
		exit(1);
	}
	yyrestart(yyin);
	stub_number.push_back(0);
	if (!yyparse() && !no_errors) {
		cout << "sucessfully parsed" << endl;
		AbstractNamedRange * nr_ptr = dynamic_cast <AbstractNamedRange*> (root);
		if (NamedRangeGroup * ng = dynamic_cast <NamedRangeGroup*> (nr_ptr)) {
			ng->Print();
		}
	}
}


