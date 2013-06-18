/*
 * =====================================================================================
 *
 *       Filename:  test_main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 30 September 2011 01:54:00  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <string>
#include <sstream>
#include <vector>
#include "new_named_range.h"

using namespace std;


void PrintNamedRange (AbstractNamedRange * nr, vector <string> & group_str, vector <string> & group_list, stringstream & final_answer);

int main()
{

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
	grp_2.AddGroup(grp_21);
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


	//=======
	vector <string> group_str;
	vector <string> group_list;
	stringstream final_answer;
	//group_str.push_back("suvidha_kendra");
	//group_list.push_back("suvidha_kendra");
	PrintNamedRange (&suvidha_kendra, group_str, group_list, final_answer);
	cout << "final_answer: "
		<< "=======================" << endl
		<< final_answer.str()
		<< "=======================" << endl
		<< endl;

	if (group_str.size() != 0) {
		cout << "ERROR: group_str.size() != 0" << endl;
		for (int i=0; i < group_str.size(); ++i) {
			cout << group_str[i] << endl;
		}
	}
	if (group_list.size() != 0) {
		cout << "ERROR: group_list.size() != 0" << endl;
		for (int i=0; i < group_list.size(); ++i) {
			cout << group_list[i] << endl;
		}
	}
}


void PrintNamedRange (AbstractNamedRange * nr, vector <string> & group_str, vector <string> & group_list, stringstream & final_answer)
{
	static int nest_level = 0;
	cout << __PRETTY_FUNCTION__ << ", nest_level: " 
		<< ++nest_level
		<< endl;
	bool added_to_stack = false;
	//while (nr) 
	//cout << "before if nr: " << nr << endl;
	if (nr) {
		if (NamedRangeGroup * ng = dynamic_cast<NamedRangeGroup*> (nr)) {
			string s (ng->groupName_);
			group_list.push_back ( s);

			cout << "Adding group: " << s 
				<< " onto the stack: group_str.size: " 
				<< group_str.size() 
				<< endl;
			if (group_str.size() > 0) {
				group_str[group_str.size() - 1]
					+=  group_list[group_list.size()-2]
						+ ".AddGroup("
						+ s
						+ ") /* -- */\n";
			}
			//s += " : ";
			group_str.push_back("NamedRangeGroup " + s + "(\"" + s + "\")" +";\n");
			//cout << "ng->groupPtr_: " << ng->groupPtr_ << endl;
			//if (ng->groupPtr_)
			PrintNamedRange (ng->groupPtr_, group_str, group_list, final_answer);
			added_to_stack = true;
		} else if (NamedRangeList * nl = dynamic_cast<NamedRangeList*> (nr)) {
			//group_str[group_str.size() -1 ] += string("|");
			cout << "group_list.size: " << group_list.size() 
				<< ", group_list.back(): " << group_list.back()
				<< endl;
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
				//cout << "Adding stub: " << nl->stubs[i].stub_text
				//	<< " to group " << group_list.back() << endl;
			}
		}
		//nr = nr->next_nr;
	} else {
		cout << "Should never reach here : " << __PRETTY_FUNCTION__ << ", nest_level: " << nest_level << endl;
		--nest_level;
		return;
	}
	//if (group_str.size() > 0)
	if (added_to_stack) {
		final_answer << group_str.back() << endl;
		cout << "group_list.size(): " << group_list.size()
			<< ", group_str.size(): " << group_str.size()
			<< endl << endl;
		group_str.pop_back();
		cout <<  "popping off group: " << group_list.back() << endl;
		group_list.pop_back();
		//cout << "final_answer: looks like this: "
		//	<< endl
		//	<< "::::::::::::::::::::" << endl
		//	<< final_answer.str()
		//	<< "::::::::::::::::::::" << endl
		//	<< endl;
		if (group_list.size() > 0) {
			cout << group_list.back() << endl;
		}
	}
	//cout << "before next recursive call nr: " << nr << endl;

	if (nr->next_nr) {
		PrintNamedRange (nr->next_nr, group_str, group_list, final_answer);
	}
	cout << "Exit : " << __PRETTY_FUNCTION__ << ", nest_level: " << nest_level << endl;
	--nest_level;
}
