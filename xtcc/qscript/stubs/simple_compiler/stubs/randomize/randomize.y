%{
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
	
#include "AbstractStatement.h"
//#include "named_range.h"
#include "new_named_range.h"
#include "const_defs.h"

	using std::vector;
	using std::stringstream;
	using std::string;
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
		 
		cout << "stub_number.size(): "  << stub_number.size()
			<< endl;
		stub_number.pop_back(); 
		cout << "highest_stub_number_in_group: " 
			<< $2 << ": " 
			<< highest_stub_number_in_group
			<< endl;
		if (stub_number.size() != 0) {
			cerr << "Error in parsing assumptions: stub_number.size should be 0 at this point"
				<< endl;
		}
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
#include <vector>

void yyrestart(FILE *input_file);
int32_t yyparse();
void PrintNamedRange (AbstractNamedRange * nr, vector <string> & group_str, vector <string> & group_list, stringstream & final_answer);
bool compare_structure (AbstractNamedRange * nr1, AbstractNamedRange * nr2);
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
			vector <string> group_str;
			vector <string> group_list;
			stringstream final_answer;

			if (NamedRangeGroup * ng = dynamic_cast <NamedRangeGroup*> (nr_ptr)) {
				//group_list.push_back ("NamedRangeGroup " + ng->groupName_ + ";\n");
				//group_str.push_back (ng->groupName_);
				PrintNamedRange (nr_ptr, group_str, group_list, final_answer);
			}
			cout 	<< "final_answer: " << endl
				<< "========================" << endl
				<< final_answer.str()
				<< "========================" << endl
				<< endl;
		} else {
			cout << "not a AbstractNamedRange" << endl;
		}
		if (nr_ptr) {
			if (NamedRangeGroup * ng = dynamic_cast <NamedRangeGroup*> (nr_ptr)) {
				cout << "SimplePrint =============== " << endl;
				ng->groupPtr_->SimplePrint();
				cout << "END SimplePrint =============== " << endl;
			}
		}
	}
	{
		// test area
		//=======
		NamedRangeGroup grp_1("grp_1");
		grp_1.AddStub( " Kalyanam (Ratia Marg, Snagam Vihar, New Delhi)", 7, 1);
		grp_1.AddStub( " CASP Plan Project (Neem Chowk, Sangam Vihar, New Delhi)", 8, 2);
		grp_1.AddStub( " EFRAH (Aali Vihar, nr. Aali Village, New Delhi)", 9, 3);
		grp_1.AddStub( " Nav Srishti (Village neb Sarai, New Delhi)", 10, 4);
		cout << "grp_1.groupPtr_->SimplePrint =============== " << endl;
		grp_1.groupPtr_->SimplePrint();
		cout << "END SimplePrint =============== " << endl;

		NamedRangeGroup grp_21("grp_21");
		grp_21.AddStub( " Shape India (R/o block 5c, Sarai Kale Khan, DDA flat)", 13, 1);
		grp_21.AddStub( " Jai Jawan Jai Kisan trust (Cenquin) (Centre for community and child development, Jamia Milia Islamia)", 14, 2);

		NamedRangeGroup grp_22("grp_22");
		grp_22.AddStub( " Adarshila (Greater Kailash 2, New Delhi)", 15, 1);
		grp_22.AddStub( " Katha (A/3 Sarvodaya Enclave, New Delhi)", 16, 2);

		NamedRangeGroup grp_2("grp_2");
		cout << "before: grp_2.AddGroup(grp_21);" << endl;
		grp_2.AddGroup(grp_21);
		cout << "before: grp_2.AddGroup(grp_22);" << endl;
		grp_2.AddGroup(grp_22);
		cout << "grp_2.groupPtr_->SimplePrint =============== " << endl;
		grp_2.groupPtr_->SimplePrint();
		cout << "END SimplePrint =============== " << endl;

		NamedRangeGroup suvidha_kendra("suvidha_kendra");
		suvidha_kendra.AddStub( " CASP (JJ Colony, Madanpur Khadar, New Delhi)", 1, 1);
		suvidha_kendra.AddStub( " Prayatn (Basti Vikas Kendra, Jeevan Jyoti Rajiv Camp, D Block, Okhla PII", 2, 2);
		suvidha_kendra.AddStub( " Jal Shankar Memorial Centre (Jasloa Village, New Delhi) Jal", 3, 3);
		suvidha_kendra.AddStub( " Sakaar Outreach (Tanki Road, Meethapur Badarpur, New Delhi)", 4, 4);
		suvidha_kendra.AddStub( " Mamta health Institute for Mother and Child (JJ Camp, Tigri, New Delhi)", 5, 5);
		suvidha_kendra.AddStub( " New opportunities for Women (NOW) (Nr Shalimar Conema, New park)", 6, 6);
		suvidha_kendra.AddGroup(grp_1);
		suvidha_kendra.AddStub( " Navjyoti Development Society (Tekhand village, Okhla phase I, New Del)", 11, 8);
		suvidha_kendra.AddStub( " Sakaar Outreach (Madangir Ambedkar Nagar, New Delhi)", 12, 9);
		suvidha_kendra.AddGroup(grp_2);
		suvidha_kendra.AddStub( " Kalyanam (41/1407 DDA flats, Madangir, New Delhi)", 17, 11);

		cout << "SimplePrint suvidha_kendra.groupPtr_ =============== " << endl;
		suvidha_kendra.groupPtr_->SimplePrint();
		cout << "END SimplePrint =============== " << endl;
		//cout << "SimplePrint =============== " << endl;
		//suvidha_kendra.SimplePrint();
		//cout << "END SimplePrint =============== " << endl;
		AbstractNamedRange * nr_ptr = dynamic_cast <AbstractNamedRange*> (root);
		if (NamedRangeGroup * ng = dynamic_cast <NamedRangeGroup*> (nr_ptr)) {
			bool compare_result = compare_structure (&suvidha_kendra, ng);
			cout << " compare_result: " << compare_result << endl;
		}

		//=======
		vector <string> group_str;
		vector <string> group_list;
		stringstream final_answer;
		//group_str.push_back("suvidha_kendra");
		//group_list.push_back("suvidha_kendra");

		// uncommenting this one and the PrintNamedRange below should both give the same
		// printed output
		//PrintNamedRange (&suvidha_kendra, group_str, group_list, final_answer);
		NamedRangeGroup * ng = dynamic_cast <NamedRangeGroup*> (nr_ptr);
		PrintNamedRange (ng, group_str, group_list, final_answer);
		cout << "final_answer: "
			<< "=======================" << endl
			<< final_answer.str()
			<< "=======================" << endl
			<< "group_str.size(): " << group_str.size() << endl
			<< "group_list.size(): " << group_list.size() << endl
			<< endl;

		cout << "=========== ng->Print(); ============ " << endl;
		ng->Print();
		ng->Vectorize(ng, ng->stub_grp_vec);
		//cout << "ng->stub_grp_vec.size(): " << ng->stub_grp_vec.size() << endl;
		ng->VectorizePrint(ng);

	}

}

void PrintNamedRange (AbstractNamedRange * nr, vector <string> & group_str, vector <string> & group_list, stringstream & final_answer)
{
	//cout << "Enter: " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
	//cout << "group_str.size(): " << group_str.size() << endl;
	//cout << "group_list.size(): " << group_list.size() << endl;
	bool added_to_stack = false;
	if (nr) {
		if (NamedRangeGroup * ng = dynamic_cast<NamedRangeGroup*> (nr)) {
			string s (ng->groupName_);
			group_list.push_back ( s);

			cout << "Adding group: " << s 
				<< " onto the stack" << endl;
			if (group_str.size() > 0) {
				//cout << "inside if clause" << __LINE__
				//	<< ": group_str.size(): "
				//	<< group_str.size() << endl;
				//cout << "inside if clause" << __LINE__
				//	<< ": group_list.size(): "
				//	<< group_list.size() << endl;
				group_str[group_str.size() - 1] 
					+=  group_list[group_list.size()-2]
						+ ".AddGroup(" 
						+ s
						+ ");\n";
			}
			//s += " : ";
			group_str.push_back("NamedRangeGroup " + s + "(\"" + s + "\")" +";\n");
			//if (ng->groupPtr_)
			//cout << " before call to PrintNamedRange: " << __LINE__ << endl;
			PrintNamedRange (ng->groupPtr_, group_str, group_list, final_answer);
			added_to_stack = true;
		} else if (NamedRangeList * nl = dynamic_cast<NamedRangeList*> (nr)) {
			//group_str[group_str.size() -1 ] += string("|");
			for (int i = 0; i < nl->stubs.size(); ++i) {
				//group_str[group_str.size() - 1] += string("|") + nl->stubs[i].stub_text;
				stringstream s1;
				s1 << group_list[group_list.size()-1]
					<< string(".AddStub( \"") << nl->stubs[i].stub_text
					<< string("\", ")
					<< nl->stubs[i].code
					<< string(", ") << nl->stubs[i].index_in_group 
					<< string(");\n");
				group_str[group_str.size() - 1] 
					+= s1.str();
			}
		}
		//nr = nr->next_nr;
	}
	//if (group_str.size() > 0) 
	if (added_to_stack) {
		final_answer << group_str.back() << endl;
		group_str.pop_back();
		group_list.pop_back();
	}
	//cout << "before next recursive call nr: " << nr << endl;
	if (nr->next_nr) {
			PrintNamedRange (nr->next_nr, group_str, group_list, final_answer);
	}
}

bool compare_structure (AbstractNamedRange * nr1, AbstractNamedRange * nr2)
{
	NamedRangeList * nl1 = dynamic_cast<NamedRangeList*> (nr1);
	NamedRangeGroup * ng1 = dynamic_cast<NamedRangeGroup*> (nr1);
	NamedRangeList * nl2 = dynamic_cast<NamedRangeList*> (nr2);
	NamedRangeGroup * ng2 = dynamic_cast<NamedRangeGroup*> (nr2);

	if (ng1 && ng1->groupName_ == "grp_21") {
		cout << "ng1 == grp_21" << endl;
		cout << "ng1->groupPtr_: "
			<< ng1->groupPtr_ << endl;
		if (dynamic_cast<NamedRangeGroup*> (ng1->groupPtr_)) {
			cout << "ng1->groupPtr_"
				<< " is a NamedRangeGroup"
				<< endl;
		}
		if (dynamic_cast<NamedRangeList*> (ng1->groupPtr_)) {
			cout << "ng1->groupPtr_"
				<< " is a NamedRangeList"
				<< endl;
		}
		cout << "=============" << endl;
	}
	if (ng2 && ng2->groupName_ == "grp_21") {
		cout << "ng2 == grp_21" << endl;
		cout << "ng2->groupPtr_: "
			<< ng2->groupPtr_ << endl;
		if (dynamic_cast<NamedRangeGroup*> (ng2->groupPtr_)) {
			cout << "ng2->groupPtr_"
				<< " is a NamedRangeGroup"
				<< endl;
		}
		if (dynamic_cast<NamedRangeList*> (ng2->groupPtr_)) {
			cout << "ng2->groupPtr_"
				<< " is a NamedRangeList"
				<< endl;
		}
		cout << "-------------" << endl;
	}

	cout << __PRETTY_FUNCTION__ << endl;

	if (nl1 && nl2) {
		cout <<  "both are lists" << endl;
		if (nl1->stubs.size() != nl2->stubs.size()) {
			cout << "nl1 and nl2 are both lists but stub sizes are different" << endl;
			return false;
		} else {
			for (int i=0; i < nl1->stubs.size(); ++i) {
				if (nl1->stubs[i].stub_text != nl2->stubs[i].stub_text) {
					cout << "nl1 and nl2 differ at i= " << i;
					cout << nl1->stubs[i].stub_text << endl
						 << nl2->stubs[i].stub_text << endl;
				}
			}
			if (nl1->next_nr && nl2->next_nr) {
				return compare_structure (nl1->next_nr, nl2->next_nr);
			} else {
				return true;
			}
		}
	} else if (ng1 && ng2) {
		cout <<  "both are named groups: " 
			<< ng1->groupName_ << ", " 
			<< ng2->groupName_ 
			<< endl;
		if (ng1->groupName_ == ng2->groupName_) {
			
			bool result = compare_structure (ng1->groupPtr_, ng2->groupPtr_);
			if (!result) {
				cout << "group names match but structure doesnt: "
					<< ng1->groupName_
					<< endl;
				return false;
			} else if (ng1->next_nr && ng2->next_nr) {
				return compare_structure (ng1->next_nr, ng2->next_nr);
			} else if (ng1->next_nr == 0 && ng2->next_nr == 0) {
				return true;
			} else {
				cout << "one of the groups does not have a next_nr pointer" << endl;
				if (ng1->next_nr) {
					cout << "ng1->next: " << ng1->next_nr << endl;
				} else {
					cout << "ng1->next == 0" << endl;
				}
				if (ng2->next_nr) {
					cout << "ng2->next: " << ng2->next_nr << endl;
				} else {
					cout << "ng2->next == 0" << endl;
				}
				return false;
			}
		} else {
			cout << "ng1 and ng2 have different names"
				<< endl;
			return false;
		}
	} else {
		cout << "the inputs are of different types" 
			<< endl;
		return false;
	}
}
