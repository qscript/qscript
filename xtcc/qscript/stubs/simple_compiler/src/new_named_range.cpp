/*
 * =====================================================================================
 *
 *       Filename:  new_named_range.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 30 September 2011 09:55:22  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Neil Xavier D'Souza
 *
 * =====================================================================================
 */

#include <algorithm>
#include <functional>
#include <fstream>
#include "new_named_range.h"

//ptrdiff_t (*p_myrandom)(ptrdiff_t) = myrandom;
//ptrdiff_t myrandom (ptrdiff_t i) 
//{
//	int random_seed = time (0);
//	return rand()%i;
//}

/*
struct MyRNG
{
	int random_seed;
	MyRNG(): 	random_seed (time(0))
	{ }
	int MyRNG(ptrdiff_t i)
	{
		return rand_r(&random_seed) % i;
	}
};
*/

void NamedRangeGroup::AddStub (string p_text, int p_code, int p_index_in_group)
{
	if (groupPtr_) {
		AbstractNamedRange * ptr_AbstractNamedRange = groupPtr_;
		while (ptr_AbstractNamedRange->next_nr) {
			ptr_AbstractNamedRange = ptr_AbstractNamedRange->next_nr;
		}
		if (NamedRangeGroup * ng = dynamic_cast<NamedRangeGroup*> (ptr_AbstractNamedRange)) {
			NamedRangeList * nl = new NamedRangeList(0);
			struct stub_pair pair1 (p_text, p_code, true, p_index_in_group);
			nl->stubs.push_back (pair1);
			ptr_AbstractNamedRange->next_nr  = nl;
			cout << "adding stub: " << p_text << " to group: " << groupName_ << endl;
		} else if (NamedRangeList * nl = dynamic_cast<NamedRangeList*> (ptr_AbstractNamedRange)) {
			struct stub_pair pair1 (p_text, p_code, true, p_index_in_group);
			nl->stubs.push_back (pair1);
			cout << "adding stub: " << p_text << " to group: " << groupName_ << endl;
		}
	} else {
		NamedRangeList * nl = new NamedRangeList (0);
		struct stub_pair pair1 (p_text, p_code, true, p_index_in_group);
		nl->stubs.push_back (pair1);
		//next_nr  = nl;
		groupPtr_ = nl;
		cout << "adding stub: " << p_text << " to group: " << groupName_ << endl;
	}
}

void NamedRangeGroup::AddGroup (NamedRangeGroup & p_group, int p_index_in_group)
{
	cout << __PRETTY_FUNCTION__ << "groupName_: " 
		<< groupName_
		<< ", p_group: " 
		<< p_group.groupName_
		<< endl;
	if (next_nr== 0 && groupPtr_==0) {
		//groupPtr_ = & p_group;
		NamedRangeGroup * nrg = new NamedRangeGroup (p_group.lineNo_, p_group.groupName_, p_index_in_group);
		nrg->groupPtr_ = p_group.groupPtr_;
		//groupPtr_ = p_group.groupPtr_;
		groupPtr_ = nrg;
		//groupName_ = p_group.groupName_;
		//groupPtr_ = p_group.groupPtr_;
	} else {
		AbstractNamedRange * ptr_AbstractNamedRange = groupPtr_;
		while (ptr_AbstractNamedRange->next_nr) {
			ptr_AbstractNamedRange = ptr_AbstractNamedRange->next_nr;
		}
		//ptr_AbstractNamedRange->next_nr = & p_group;
		NamedRangeGroup * nrg = new NamedRangeGroup (p_group.lineNo_, p_group.groupName_, p_index_in_group);
		nrg->groupPtr_ = p_group.groupPtr_;
		ptr_AbstractNamedRange->next_nr = nrg;
	}
}

void NamedRangeList::AddStub (string p_text, int p_code, int p_index_in_group)
{
	if (next_nr) {
		AbstractNamedRange * ptr_AbstractNamedRange = next_nr;
		while (ptr_AbstractNamedRange->next_nr) {
			ptr_AbstractNamedRange = ptr_AbstractNamedRange->next_nr;
		}
		if (NamedRangeGroup * ng = dynamic_cast<NamedRangeGroup*> (next_nr)) {
			NamedRangeList * nl = new NamedRangeList (0);
			struct stub_pair pair1 (p_text, p_code, true, p_index_in_group);
			nl->stubs.push_back (pair1);
			ptr_AbstractNamedRange->next_nr = nl;
		}
	} else {
		struct stub_pair pair1 (p_text, p_code, true, p_index_in_group);
		stubs.push_back (pair1);
	}
}

void NamedRangeList::AddGroup (NamedRangeGroup & p_group, int p_index_in_group)
{
	cout << __PRETTY_FUNCTION__ << endl;
	if (next_nr == NULL) {
		next_nr = & p_group;
	} else {
		AbstractNamedRange * ptr_AbstractNamedRange = next_nr;
		while (ptr_AbstractNamedRange->next_nr) {
			ptr_AbstractNamedRange = ptr_AbstractNamedRange->next_nr;
		}
		ptr_AbstractNamedRange->next_nr = & p_group;
	}
}


void NamedRangeList::Vectorize (AbstractNamedRange * invoker, vector <AbstractNamedRange*> & p_stub_grp_vec)
{
	for (int i=0; i<stubs.size(); ++i) {
		p_stub_grp_vec.push_back (new NamedRangeStub (0, stubs[i].stub_text, stubs[i].code));
	}
	if (next_nr) {
		next_nr -> Vectorize (invoker, p_stub_grp_vec);
	}
}


void NamedRangeGroup::Vectorize (AbstractNamedRange * invoker, vector <AbstractNamedRange*> & p_stub_grp_vec)
{
	if (this != invoker)
		p_stub_grp_vec.push_back (this);
	if (groupPtr_) {
		groupPtr_->Vectorize (invoker, stub_grp_vec);
		//p_stub_grp_vec.push_back (groupPtr_);
	}
	if (next_nr) {
		next_nr->Vectorize (invoker, p_stub_grp_vec);
	}
}

// Warning : this function should only be called
// after calling Vectorize on the group
void NamedRangeGroup::Randomize()
{
	randomized_order.resize (stub_grp_vec.size());	
	for (int i=0; i < randomized_order.size(); ++i) {
		randomized_order[i] = i;
		NamedRangeGroup * nrg = dynamic_cast<NamedRangeGroup*> (stub_grp_vec[i]);
		if (nrg) {
			nrg->Randomize();
		}
	}

	MyRNG my_rng;
	random_shuffle ( randomized_order.begin(), randomized_order.end(), my_rng);
}


int MyRNG::operator () (ptrdiff_t i)
{
	return rand_r(&random_seed) % i;
}


void NamedRangeGroup::SaveRandomizedOrderToDisk()
{
	cout << "{ " << groupName_ << ": ";
	bool last_item_was_nrg = true; // I am the last Item and I am an NRG
	//{ grp_2: { grp_23:  2 0 1; }  { grp_21:  1 0; }  { grp_22:  1 0; }   }
	// other wise the output would be like this
	//{ grp_2: ; { grp_23:  2 0 1; }  { grp_21:  1 0; }  { grp_22:  1 0; }   }
	//         ^
	//         | ---- this is wrong
	for (int i=0; i<randomized_order.size(); ++i) {
		NamedRangeGroup * nrg = dynamic_cast<NamedRangeGroup*> (stub_grp_vec[randomized_order[i]]);
		if (nrg) {
			if (last_item_was_nrg) {
			} else {
				cout << "; ";
			}
			nrg->SaveRandomizedOrderToDisk();
			last_item_was_nrg = true;
		} else {
			cout << " " << randomized_order[i];
			last_item_was_nrg = false;
		}
	}
	if (last_item_was_nrg) {
		cout << " }  ";
	} else {
		cout << "; }  ";
	}
}

string NamedRangeGroup::GetRandomizedOrder()
{
	stringstream randomized_order_str;
	randomized_order_str << "{ " << groupName_ << ": ";
	bool last_item_was_nrg = true; // I am the last Item and I am an NRG
	//{ grp_2: { grp_23:  2 0 1; }  { grp_21:  1 0; }  { grp_22:  1 0; }   }
	// other wise the output would be like this
	//{ grp_2: ; { grp_23:  2 0 1; }  { grp_21:  1 0; }  { grp_22:  1 0; }   }
	//         ^
	//         | ---- this is wrong
	for (int i=0; i<randomized_order.size(); ++i) {
		NamedRangeGroup * nrg = dynamic_cast<NamedRangeGroup*> (stub_grp_vec[randomized_order[i]]);
		if (nrg) {
			if (last_item_was_nrg) {
			} else {
				randomized_order_str << "; ";
			}
			string s1 = nrg->GetRandomizedOrder();
			randomized_order_str << s1;
			last_item_was_nrg = true;
		} else {
			randomized_order_str << " " << randomized_order[i];
			last_item_was_nrg = false;
		}
	}
	if (last_item_was_nrg) {
		randomized_order_str << " }  ";
	} else {
		randomized_order_str << "; }  ";
	}

	return randomized_order_str.str();
}

/*  This function has been badly hacked together to get the :
 *  declaration of the NamedRangeGroup into the class definition area
 *  and out of the constructor in the last case when the stack is unwinding
 *  */
void PrintNamedRange (AbstractNamedRange * nr, vector <string> & group_str,
		vector <string> & group_list,
		vector <string> & defns,
		stringstream & final_answer)
{
	//cerr << "Enter: " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
	//cerr << "group_str.size(): " << group_str.size() << endl;
	//cerr << "group_list.size(): " << group_list.size() << endl;
	bool added_to_stack = false;
	if (nr) {
		if (NamedRangeGroup * ng = dynamic_cast<NamedRangeGroup*> (nr)) {
			string s (ng->groupName_);
			group_list.push_back ( s);

			//cout << "Adding group: " << s 
			//	<< " onto the stack" << endl;
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
						+ s + ", 0 /*  this should be the line number of the group, but get it to compile for now */"
						+ ");\n";
				//defns[defns.size() - 1] 
				//	+=  group_list[group_list.size()-2]
				//		+ ".AddGroup(" 
				//		+ s
				//		+ ");\n";
			}
			
			stringstream tmp1;
			tmp1 << "NamedRangeGroup " << s << "(" 
				<< ng->lineNo_ 
				<< ", \"" << s << "\", "
				<< ng->index_in_group
				<< ")" << "; // " 
				<< "group_str.size(): " << group_str.size()  
				<< "group_list.size(): " << group_list.size()  
				<< "final_answer.str().length() : " << final_answer.str().length()
				<< endl;
			//group_str.push_back (tmp1.str());
			//group_str.push_back("NamedRangeGroup " + s + "(\"" + s + "\")" +";\n");
			if (group_str.size() == 0 && group_list.size()==1 && final_answer.str().length() == 0) {
				//cerr << "group_str.size() = 0, NamedRangeGroup: " << s << endl;
			} else {
				group_str.push_back (tmp1.str());
			}
			defns.push_back("NamedRangeGroup " + s + "(\"" + s + "\")" +";\n");
			//if (ng->groupPtr_)
			//cout << " before call to PrintNamedRange: " << __LINE__ << endl;
			PrintNamedRange (ng->groupPtr_, group_str, group_list, defns, final_answer);
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
				//group_str[group_str.size() - 1] 
				//	+= s1.str();
				//cerr << "defns.size(): " << defns.size() << endl;
				//if (defns.size() == 1) {
				//	cout << "defns[0]: "  << defns[0] << endl;
				//}
				// ----------
				// This is a real hack and should be cleaned up
				// at some point. It just about works for now
				// but I would prefer If I came up with a more
				// elegant solution
				if (group_str.size() > 0) {
					group_str[group_str.size() - 1] 
						+= s1.str();
				} else {
					if (defns.size() == 1) {
						group_str.push_back (s1.str());
					}
				}
				// ---------------
				//cerr << "reached here: " << endl;
			}
		}
		//nr = nr->next_nr;
	}
	//if (group_str.size() > 0) 
	if (added_to_stack) {
		//cerr << "reached here: " << endl;
		if (group_str.size() > 0)
			final_answer << group_str.back() << endl;
		if (group_str.size() != 0)
			group_str.pop_back();
		group_list.pop_back();
		defns.pop_back();
	}
	//cout << "before next recursive call nr: " << nr << endl;
	if (nr->next_nr) {
		PrintNamedRange (nr->next_nr, group_str, group_list, defns, final_answer);
	}
}


void NamedRangeGroup::GenerateCode(StatementCompiledCode & code)
{
	code.quest_defns << "// invoked: " << __PRETTY_FUNCTION__ << endl;
	vector <string> group_str;
	vector <string> group_list;
	vector <string> defns;
	stringstream final_answer;
	PrintNamedRange (this, group_str, group_list, defns, final_answer);
	code.quest_defns << "NamedRangeGroup " << groupName_ << ";" << endl;
	code.quest_defns_init_code << final_answer.str() << endl;
	if (code.quest_defns_constructor.str().length() > 0) {
		code.quest_defns_constructor <<  "," 
			<< groupName_
			<< "(" << lineNo_ << ", " 
			<<  "\"" << groupName_ << "\"" << ", 0" << ")";
	} else {
		//code.quest_defns_constructor <<  ":" << groupName_ << "(\"" << groupName_ << "\")";
		code.quest_defns_constructor <<  ":" 
			<< groupName_
			<< "(" << lineNo_ << ", " 
			<<  "\"" << groupName_ << "\"" << ", 0" << ")";
	}

	if (next_) {
		next_->GenerateCode(code);
	}
}

//extern fstream new_named_range_debug_out;

void NamedRangeGroup::CreateDisplayStubs (AbstractNamedRange * invoker
			, vector<stub_pair> & display_result)
{
	//{
	//	new_named_range_debug_out << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
	//	new_named_range_debug_out << " randomized_order.size: " << randomized_order.size() << endl;
	//	new_named_range_debug_out << " stub_grp_vec.size: " << stub_grp_vec.size() << endl;
	//	new_named_range_debug_out << "display_result.size: " << display_result.size() << endl;
	//}
	if (randomized_order.size() == 0) {
		for (int i=0; i < stub_grp_vec.size(); ++i) {
			stub_grp_vec[i]->CreateDisplayStubs (invoker,
					display_result);
		}
	} else {
		for (int i=0; i < randomized_order.size(); ++i) {
			stub_grp_vec[randomized_order[i]] ->
				CreateDisplayStubs(invoker,
						display_result);
		}
	}
}

