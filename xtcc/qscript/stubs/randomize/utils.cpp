#include <cstdio>
#include "new_named_range-v2.h"
#include "utils.h"

void display_flat_named_range(const string & name, const vector<stub_pair>  nr_vec)
{
	cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
	cout	<< "NamedRange info: "
		<< name
		<< ", size: " << nr_vec.size()
		<< endl;
	for (int i=0; i < nr_vec.size(); ++i) {
		cout
			<< "code: " << nr_vec[i].code
			<< ", stub_text: " << nr_vec[i].stub_text
			<< endl;
	}
	cout << " ===== END NamedRange Info" << name << "=======" << endl;
	cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
}

bool recursive_compare_structure (AbstractNamedRange * nr1, AbstractNamedRange * nr2, int nest_level)
{
	//cout
	//	<< __PRETTY_FUNCTION__
	//	<< ": nest_level: " << nest_level
	//	<< endl;
	printf("%*d|%s\n", nest_level, nest_level, __PRETTY_FUNCTION__);
	NamedRangeList * nl1 = dynamic_cast<NamedRangeList*> (nr1);
	NamedRangeGroup * ng1 = dynamic_cast<NamedRangeGroup*> (nr1);
	NamedRangeList * nl2 = dynamic_cast<NamedRangeList*> (nr2);
	NamedRangeGroup * ng2 = dynamic_cast<NamedRangeGroup*> (nr2);
	if (ng1 && ng2) {
		cout << "comparing: "
			<< ng1->groupName_ << " vs "
			<< ng2->groupName_
			<< endl;
		if (ng1->groupName_ != ng2->groupName_) {
			cout
				<< "name mismatch: "
				<< ng1->groupName_ << "!=" << ng2->groupName_
				<< ", nest_level: " << nest_level
				<< endl;
			return false;
		}
		if (ng1->groupPtr_ && ng2->groupPtr_) {
			bool res =  recursive_compare_structure (ng1->groupPtr_, ng2->groupPtr_, nest_level+1);
			if (ng1->next_nr && ng2->next_nr) {
				return res && recursive_compare_structure (ng1->next_nr, ng2->next_nr, nest_level+1);
			} else if (ng1->next_nr == 0 && ng2->next_nr == 0) {
				return res;
			} else {
				cout
					<< "one of the groups has a next_nr and the other doesnt: "
					<< ng1->groupName_ << ": next_nr == " << ng1->next_nr
					<< ng2->groupName_ << ": next_nr == " << ng2->next_nr
					<< ", nest_level: " << nest_level
					<< endl;
				return false;
			}
		} else if (ng1->groupPtr_ == 0 && ng2->groupPtr_ == 0) {
			if (ng1->next_nr && ng2->next_nr) {
				return recursive_compare_structure (ng1->next_nr, ng2->next_nr, nest_level+1);
			} else {
				return true;
			}
		} else {
			cout
				<< "one of the groupPtr_ s is 0"
				<< "ng1->groupPtr_ " << ng1->groupPtr_
				<< ", "
				<< "ng2->groupPtr_ " << ng2->groupPtr_
				<< ", nest_level: " << nest_level
				<< endl;
			return false;
		}
	} else if (nl1 && nl2) {
		cout <<  "both are lists" << endl;
		if (nl1->stubs.size() != nl2->stubs.size()) {
			cout << "nl1 and nl2 are both lists but stub sizes are different" << endl;
			return false;
		} else {
			for (int i=0; i < nl1->stubs.size(); ++i) {
				cout << "comparing: "
					<< nl1->stubs[i].stub_text << " vs "
					<< nl2->stubs[i].stub_text
					<< endl;
				if (nl1->stubs[i].stub_text != nl2->stubs[i].stub_text) {
					cout << "nl1 and nl2 differ at i= " << i << endl;
					cout << nl1->stubs[i].stub_text << endl
						 << nl2->stubs[i].stub_text << endl;
					cout << "nest_level: " << nest_level << endl;
					return false;
				}
			}
			if (nl1->next_nr && nl2->next_nr) {
				return recursive_compare_structure (nl1->next_nr, nl2->next_nr, nest_level+1);
			} else {
				return true;
			}
		}
	} else {
		cout << __PRETTY_FUNCTION__
			<< "nl1: " << nl1
			<< "nl2: " << nl2
			<< "ng1: " << ng1
			<< "ng2: " << ng2
			<< ": nest_level: "
			<< endl
			<< " not similar - nl1 and nl2 are /ng1 ng2 one of them is null and one isnt"
			<< endl;
		return false;
	}

	cout << "Impossible: unreachable code" << endl;
}


void PrintNamedRange2 (AbstractNamedRange * nr, vector <string> & group_str,
	vector <NamedRangeGroup*> & group_list, stringstream & final_answer,
	vector<stub_pair> & flat_display_nr
	)
{
	cout << "Enter: " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
	cout << "group_str.size(): " << group_str.size() << endl;
	cout << "group_list.size(): " << group_list.size() << endl;
	bool added_to_stack = false;
	if (nr) {
		if (NamedRangeGroup * ng = dynamic_cast<NamedRangeGroup*> (nr)) {
			string s (ng->groupName_);
			//group_list.push_back ( s);
			group_list.push_back (ng);

			cout << "Adding group: " << s
				<< " onto the stack" << endl;
			if (group_str.size() > 0) {
				//cout << "inside if clause" << __LINE__
				//	<< ": group_str.size(): "
				//	<< group_str.size() << endl;
				//cout << "inside if clause" << __LINE__
				//	<< ": group_list.size(): "
				//	<< group_list.size() << endl;
				stringstream s1;
				s1 <<
					group_list[group_list.size()-2]->groupName_
					<<  ".AddGroup("
					<<  s
					<< ","
					//<< group_list[group_list.size()-2]->index_in_group
					<<  s << ".index_in_group"
					<<  ");\n";
				group_str[group_str.size() - 1]
					+=
					//group_list[group_list.size()-2]->groupName_
					//	+ ".AddGroup("
					//	+ s
					//	+ ");\n";
					s1.str();
			}
			//s += " : ";
			stringstream s2;
			s2
				<< "NamedRangeGroup "
				<< s
				<< "(\""
				<<  s
				<< "\""
				<< ","
				<< group_list[group_list.size()-1]->index_in_group
				<< ")"
				<<  ";\n";
			group_str.push_back(
				//"NamedRangeGroup "
				//+ s + "(\""
				//+ s
				//+ "\")" +";\n"
				s2.str()
				);
			//if (ng->groupPtr_)
			//cout << " before call to PrintNamedRange: " << __LINE__ << endl;
			PrintNamedRange2 (ng->groupPtr_, group_str, group_list, final_answer, flat_display_nr);
			added_to_stack = true;
			//flat_display_nr.push_back (stub_pair(string("Group:") + ng->groupName_,
			//				flat_display_nr.size()));
		} else if (NamedRangeList * nl = dynamic_cast<NamedRangeList*> (nr)) {
			//group_str[group_str.size() -1 ] += string("|");
			for (int i = 0; i < nl->stubs.size(); ++i) {
				//group_str[group_str.size() - 1] += string("|") + nl->stubs[i].stub_text;
				stringstream s1;
				s1 << group_list[group_list.size()-1]->groupName_
					<< string(".AddStub( \"") << nl->stubs[i].stub_text
					<< string("\", ")
					<< nl->stubs[i].code
					<< string(", ") << nl->stubs[i].index_in_group
					<< string(");\n");
				group_str[group_str.size() - 1]
					+= s1.str();
				flat_display_nr.push_back (stub_pair(nl->stubs[i].stub_text, flat_display_nr.size()));
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
		PrintNamedRange2 (nr->next_nr, group_str, group_list, final_answer,
			flat_display_nr);
	}
}



void PrintNamedRange (AbstractNamedRange * nr, vector <string> & group_str,
	vector <string> & group_list, stringstream & final_answer,
	vector<stub_pair> & flat_display_nr
	)
{
	cout << "Enter: " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
	cout << "group_str.size(): " << group_str.size() << endl;
	cout << "group_list.size(): " << group_list.size() << endl;
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
			group_str.push_back("NamedRangeGroup "
				+ s + "(\""
				+ s
				+ "\")" +";\n");
			//if (ng->groupPtr_)
			//cout << " before call to PrintNamedRange: " << __LINE__ << endl;
			PrintNamedRange (ng->groupPtr_, group_str, group_list, final_answer, flat_display_nr);
			added_to_stack = true;
			//flat_display_nr.push_back (stub_pair(string("Group:") + ng->groupName_,
			//				flat_display_nr.size()));
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
				flat_display_nr.push_back (stub_pair(nl->stubs[i].stub_text, flat_display_nr.size()));
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
		PrintNamedRange (nr->next_nr, group_str, group_list, final_answer,
			flat_display_nr);
	}
}


/*
bool compare_structure (AbstractNamedRange * nr1, AbstractNamedRange * nr2, int nest_level)
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
*/
