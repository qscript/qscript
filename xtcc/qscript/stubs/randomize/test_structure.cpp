#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstdio>

#include "AbstractStatement.h"
//#include "named_range.h"
#include "new_named_range-v2.h"
#include "const_defs.h"
#include "utils.h"

	void yyrestart(FILE *input_file);
	int yyparse();
	extern AbstractStatement * root;
	extern int no_errors;
	void simple_compile(string group_name, stringstream & named_group_creation_order);
int main()
{
	cout << "Enter:" << __PRETTY_FUNCTION__ << endl;

	FILE * yyin = fopen("random_test4.input", "rb");
	if (!yyin){
		cerr << " Unable to open: random_test.input "  << " for read ... exiting" << endl;
		exit(1);
	}
	yyrestart(yyin);
	if (!yyparse() && !no_errors) {
		cout << "Parsed:" << endl;
		AbstractNamedRange * nr_ptr = dynamic_cast <AbstractNamedRange*> (root);
		if (NamedRangeGroup * ng = dynamic_cast <NamedRangeGroup*> (nr_ptr)) {
			vector<stub_pair> flat_display_nr;
			vector <string> group_str;
			vector <NamedRangeGroup*> group_list;
			stringstream final_answer;
			PrintNamedRange2 (nr_ptr, group_str, group_list, final_answer, flat_display_nr);
			cout 	<< "final_answer: " << endl
				<< "========================" << endl
				<< final_answer.str()
				<< "========================" << endl
				<< endl;
			cout << "=========== ng->VectorizePrint(); ============ " << endl;
			ng->Vectorize(ng, ng->stub_grp_vec);
			ng->Randomize();
			vector<stub_pair> flat_display_nr_after_rnd;
			cout << "VectorizePrint 1 === " << endl;
			ng->VectorizePrint(1, ng, flat_display_nr_after_rnd);
			display_flat_named_range ("flat_display_nr_after_rnd", flat_display_nr_after_rnd);
			ng->SaveRandomizedOrderToDisk(1);
			simple_compile (ng->groupName_ , final_answer);
		}
	}
	{
		NamedRangeGroup sub_group_1_lev_1("sub_group_1_lev_1",6);
		sub_group_1_lev_1.AddStub( "sub_group_1_lev_1 5", 5, 1);
		sub_group_1_lev_1.AddStub( "sub_group_1_lev_1 6", 6, 2);
		sub_group_1_lev_1.AddStub( "sub_group_1_lev_1 7", 7, 3);
		sub_group_1_lev_1.AddStub( "sub_group_1_lev_1 8", 8, 4);

		NamedRangeGroup sub_group_3_lev_2("sub_group_3_lev_2",1);
		sub_group_3_lev_2.AddStub( "sub_group_3_lev_2 9", 9, 1);
		sub_group_3_lev_2.AddStub( "sub_group_3_lev_2 10", 10, 2);
		sub_group_3_lev_2.AddStub( "sub_group_3_lev_2 11", 11, 3);

		NamedRangeGroup sub_group_4_lev_2("sub_group_4_lev_2",2);
		sub_group_4_lev_2.AddStub( "sub_group_4_lev_2 12", 12, 1);
		sub_group_4_lev_2.AddStub( "sub_group_4_lev_2 13", 13, 2);
		sub_group_4_lev_2.AddStub( "sub_group_4_lev_2 14", 14, 3);
		sub_group_4_lev_2.AddStub( "sub_group_4_lev_2 15", 15, 4);

		NamedRangeGroup sub_group_5_lev_2("sub_group_5_lev_2",3);
		sub_group_5_lev_2.AddStub( "sub_group_5_lev_2 16", 16, 1);
		sub_group_5_lev_2.AddStub( "sub_group_5_lev_2 17", 17, 2);
		sub_group_5_lev_2.AddStub( "sub_group_5_lev_2 18", 18, 3);
		sub_group_5_lev_2.AddStub( "sub_group_5_lev_2 19", 19, 4);

		NamedRangeGroup sub_group_2_lev_1("sub_group_2_lev_1",7);
		sub_group_2_lev_1.AddGroup(sub_group_3_lev_2,sub_group_3_lev_2.index_in_group);
		sub_group_2_lev_1.AddGroup(sub_group_4_lev_2,sub_group_4_lev_2.index_in_group);
		sub_group_2_lev_1.AddGroup(sub_group_5_lev_2,sub_group_5_lev_2.index_in_group);

		NamedRangeGroup sub_group_6_lev_1("sub_group_6_lev_1",13);
		sub_group_6_lev_1.AddStub( "sub_group_6_lev_1 25", 25, 1);
		sub_group_6_lev_1.AddStub( "sub_group_6_lev_1 26", 26, 2);
		sub_group_6_lev_1.AddStub( "sub_group_6_lev_1 27", 27, 3);
		sub_group_6_lev_1.AddStub( "sub_group_6_lev_1 28", 28, 4);

		NamedRangeGroup top_lev_group("top_lev_group",13);
		top_lev_group.AddStub( "top_lev_group 0", 0, 1);
		top_lev_group.AddStub( "top_lev_group 1", 1, 2);
		top_lev_group.AddStub( "top_lev_group 2", 2, 3);
		top_lev_group.AddStub( "top_lev_group 3", 3, 4);
		top_lev_group.AddStub( "top_lev_group 4", 4, 5);
		top_lev_group.AddGroup(sub_group_1_lev_1,sub_group_1_lev_1.index_in_group);
		top_lev_group.AddGroup(sub_group_2_lev_1,sub_group_2_lev_1.index_in_group);
		top_lev_group.AddStub( "top_lev_group 20", 20, 8);
		top_lev_group.AddStub( "top_lev_group 21", 21, 9);
		top_lev_group.AddStub( "top_lev_group 22", 22, 10);
		top_lev_group.AddStub( "top_lev_group 23", 23, 11);
		top_lev_group.AddStub( "top_lev_group 24", 24, 12);
		top_lev_group.AddGroup(sub_group_6_lev_1,sub_group_6_lev_1.index_in_group);

		top_lev_group.Vectorize(&top_lev_group, top_lev_group.stub_grp_vec);
		top_lev_group.Randomize();
		vector<stub_pair> flat_display_nr_after_rnd;
		cout << "VectorizePrint 2 === " << endl;
		top_lev_group.VectorizePrint(1, &top_lev_group, flat_display_nr_after_rnd);
		display_flat_named_range ("flat_display_nr_after_rnd", flat_display_nr_after_rnd);

		AbstractNamedRange * nr_ptr = dynamic_cast <AbstractNamedRange*> (root);
		cout
			<< endl
			<< "===========  recursive_compare_structure: ============== "
			<< endl;
		bool result = recursive_compare_structure (nr_ptr, &top_lev_group, 1);
		if (result ) {
			cout << "the structures are similar" << endl;
		} else {
			cout << "the structures are not similar" << endl;
		}
	}
	cout << "Exit:" << __PRETTY_FUNCTION__ << endl;
}

// 1. create a program which will contain re-create the group as
// input by the program - using c++ statements
// 2. Call randomize on the group
// 3. save the randomized order to disk
// 4. When the program is re-invoked,
// 	if it is running the second time
// 	open the file and load the randomization order from disk
// 5. Display the stubs again in randomized order that was loaded
// 	from the disk
void simple_compile(string group_name, stringstream & named_group_creation_order)
{
	FILE * test_randomization_cpp = fopen ("test_randomization.cpp", "wb");

	fprintf (test_randomization_cpp, "#include \"new_named_range-v2.h\"\n");
	fprintf (test_randomization_cpp, "#include \"utils.h\"\n");
	fprintf (test_randomization_cpp, "int main()\n{\n");
	fprintf (test_randomization_cpp, "%s\n", named_group_creation_order.str().c_str());
	fprintf (test_randomization_cpp, "%s.Vectorize(&%s, %s.stub_grp_vec);\n",
		group_name.c_str(), group_name.c_str(), group_name.c_str());
	fprintf (test_randomization_cpp, "%s.Randomize();\n", group_name.c_str());
	fprintf (test_randomization_cpp,  "vector<stub_pair> flat_display_nr_after_rnd;\n");
	fprintf (test_randomization_cpp, "%s.VectorizePrint(1, &%s, flat_display_nr_after_rnd);\n",
			group_name.c_str(), group_name.c_str());
	fprintf (test_randomization_cpp, "display_flat_named_range (\"flat_display_nr_after_rnd\", flat_display_nr_after_rnd);\n");
	fprintf (test_randomization_cpp, "}\n");
}
