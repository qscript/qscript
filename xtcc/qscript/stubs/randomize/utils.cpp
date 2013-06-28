#include "new_named_range-v2.h"

bool recursive_compare_structure (NamedRangeGroup * g1, NamedRangeGroup * g2, int nest_level)
{

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


