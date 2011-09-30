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

#include "new_named_range.h"

void NamedRangeGroup::AddStub (string p_text, int p_code, int p_index_in_group)
{
	if (groupPtr_) {
		AbstractNamedRange * ptr_AbstractNamedRange = groupPtr_;
		while (ptr_AbstractNamedRange->next_nr) {
			ptr_AbstractNamedRange = ptr_AbstractNamedRange->next_nr;
		}
		if (NamedRangeGroup * ng = dynamic_cast<NamedRangeGroup*> (ptr_AbstractNamedRange)) {
			NamedRangeList * nl = new NamedRangeList();
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
		NamedRangeList * nl = new NamedRangeList();
		struct stub_pair pair1 (p_text, p_code, true, p_index_in_group);
		nl->stubs.push_back (pair1);
		//next_nr  = nl;
		groupPtr_ = nl;
		cout << "adding stub: " << p_text << " to group: " << groupName_ << endl;
	}
}

void NamedRangeGroup::AddGroup (NamedRangeGroup & p_group)
{
	cout << __PRETTY_FUNCTION__ << "groupName_: " 
		<< groupName_
		<< ", p_group: " 
		<< p_group.groupName_
		<< endl;
	if (next_nr== 0 && groupPtr_==0) {
		//groupPtr_ = & p_group;
		NamedRangeGroup * nrg = new NamedRangeGroup(p_group.groupName_);
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
		NamedRangeGroup * nrg = new NamedRangeGroup(p_group.groupName_);
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
			NamedRangeList * nl = new NamedRangeList();
			struct stub_pair pair1 (p_text, p_code, true, p_index_in_group);
			nl->stubs.push_back (pair1);
			ptr_AbstractNamedRange->next_nr = nl;
		}
	} else {
		struct stub_pair pair1 (p_text, p_code, true, p_index_in_group);
		stubs.push_back (pair1);
	}
}

void NamedRangeList::AddGroup (NamedRangeGroup & p_group)
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
