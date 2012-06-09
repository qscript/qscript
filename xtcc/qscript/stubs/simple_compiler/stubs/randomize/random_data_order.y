/* Copyright : Neil Xavier D'Souza, 2012
*/

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
	void merge_randomization_order (NamedRangeGroup * grp1, NamedRangeGroup * grp2);
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
	//FILE * yyin = fopen("randomized_data_output_test.input", "rb");
	FILE * yyin = fopen("randomized_data_output_test2.input", "rb");
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
			ng->Vectorize(ng, ng->stub_grp_vec);
			ng->Print();
			ng->TransferRandomizationOrder(ng->randomized_order);
			cout << "randomized_order.size: " << ng->randomized_order.size() << endl;
			for (int i=0; i<ng->randomized_order.size(); ++i) {
				cout << i << ": " << ng->randomized_order[i] << endl;
			}
		}
	}
	{	
		NamedRangeGroup grp_1("grp_1", 7);
		grp_1.AddStub( " Kalyanam (Ratia Marg, Snagam Vihar, New Delhi)", 7, 1);
		grp_1.AddStub( " CASP Plan Project (Neem Chowk, Sangam Vihar, New Delhi)", 8, 2);
		grp_1.AddStub( " EFRAH (Aali Vihar, nr. Aali Village, New Delhi)", 9, 3);
		grp_1.AddStub( " Nav Srishti (Village neb Sarai, New Delhi)", 10, 4);
		cout << "grp_1.groupPtr_->SimplePrint =============== " << endl;
		grp_1.groupPtr_->SimplePrint();
		cout << "END SimplePrint =============== " << endl;

		NamedRangeGroup grp_21("grp_21", 1);
		grp_21.AddStub( " Shape India (R/o block 5c, Sarai Kale Khan, DDA flat)", 13, 1);
		grp_21.AddStub( " Jai Jawan Jai Kisan trust (Cenquin) (Centre for community and child development, Jamia Milia Islamia)", 14, 2);

		NamedRangeGroup grp_22("grp_22", 2);
		grp_22.AddStub( " Adarshila (Greater Kailash 2, New Delhi)", 15, 1);
		grp_22.AddStub( " Katha (A/3 Sarvodaya Enclave, New Delhi)", 16, 2);

		NamedRangeGroup grp_2("grp_2", 10);
		cout << "before: grp_2.AddGroup(grp_21);" << endl;
		grp_2.AddGroup(grp_21, grp_21.index_in_group);
		cout << "before: grp_2.AddGroup(grp_22);" << endl;
		grp_2.AddGroup(grp_22, grp_22.index_in_group);
		cout << "grp_2.groupPtr_->SimplePrint =============== " << endl;
		grp_2.groupPtr_->SimplePrint();
		cout << "END SimplePrint =============== " << endl;

		NamedRangeGroup suvidha_kendra("suvidha_kendra", 1);
		suvidha_kendra.AddStub( " CASP (JJ Colony, Madanpur Khadar, New Delhi)", 1, 1);
		suvidha_kendra.AddStub( " Prayatn (Basti Vikas Kendra, Jeevan Jyoti Rajiv Camp, D Block, Okhla PII", 2, 2);
		suvidha_kendra.AddStub( " Jal Shankar Memorial Centre (Jasloa Village, New Delhi) Jal", 3, 3);
		suvidha_kendra.AddStub( " Sakaar Outreach (Tanki Road, Meethapur Badarpur, New Delhi)", 4, 4);
		suvidha_kendra.AddStub( " Mamta health Institute for Mother and Child (JJ Camp, Tigri, New Delhi)", 5, 5);
		suvidha_kendra.AddStub( " New opportunities for Women (NOW) (Nr Shalimar Conema, New park)", 6, 6);
		suvidha_kendra.AddGroup(grp_1, grp_1.index_in_group);
		suvidha_kendra.AddStub( " Navjyoti Development Society (Tekhand village, Okhla phase I, New Del)", 11, 8);
		suvidha_kendra.AddStub( " Sakaar Outreach (Madangir Ambedkar Nagar, New Delhi)", 12, 9);
		suvidha_kendra.AddGroup(grp_2, grp_2.index_in_group);
		suvidha_kendra.AddStub( " Kalyanam (41/1407 DDA flats, Madangir, New Delhi)", 17, 11);

		suvidha_kendra.Vectorize(&suvidha_kendra, suvidha_kendra.stub_grp_vec);


		AbstractNamedRange * nr_ptr = dynamic_cast <AbstractNamedRange*> (root);
		NamedRangeGroup * ng = dynamic_cast <NamedRangeGroup*> (nr_ptr);

		merge_randomization_order(&suvidha_kendra, ng);

	}
}

void merge_randomization_order (NamedRangeGroup * grp1, NamedRangeGroup * grp2)
{
	if (grp1->stub_grp_vec.size() != grp2->stub_grp_vec.size()) {
		cout << "randomization order sizes do not match from disk and compiler generated" << endl;
	} else {
		cout << "ALL OK SO FAR. randomization order sizes from disk and compiler generated MATCH " << endl;
		//grp1->randomized_order.resize(stub_grp_vec.size());
		//for (int i=0; i< grp1->stub_grp_vec.size(); ++i) {
		//}
	}
}
