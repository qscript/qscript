/*
 *  Copyright (C) 2011 Neil Xavier D'Souza
 */

#ifndef xtcc_named_range_h
#define xtcc_named_range_h
#include <sys/types.h>
//#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include "stub_pair.h"
//#include "stmt.h"
#include "AbstractStatement.h"

using namespace std;
struct NamedRangeList;
struct NamedRangeGroup;

struct AbstractNamedRange: public AbstractStatement
{
	struct AbstractNamedRange *next_nr, *prev_nr;
	AbstractNamedRange():
		AbstractStatement (NAMED_RANGE, 0),
		next_nr(0), prev_nr(0)
	{ }
	void GenerateCode(StatementCompiledCode & code)
	{ }
	virtual void Print ()=0;
	virtual void SimplePrint ()=0;
	virtual void AddStub (string p_text, int p_code, int p_index_in_group)=0;
	virtual void AddGroup (NamedRangeGroup & p_group)=0;
};


struct NamedRangeList: public AbstractNamedRange
{
	std::vector <stub_pair> stubs;
	NamedRangeList():
		AbstractNamedRange()
	{ }
	void Print() {
		for (int i=0; i<stubs.size(); ++i) {
			cout << stubs[i].stub_text << ", " << stubs[i].code 
				<< ", index_in_group: " << stubs[i].index_in_group
				<< endl;
		}
		if (next_nr) {
			next_nr->Print();
		}
	}
	void AddStub (string p_text, int p_code, int p_index_in_group);
	void AddGroup (NamedRangeGroup & p_group);
	void SimplePrint()
	{
		for (int i=0; i<stubs.size(); ++i) {
			cout << stubs[i].stub_text << ", " << stubs[i].code 
				<< ", index_in_group: " << stubs[i].index_in_group
				<< endl;
		}
		if (next_nr) {
			next_nr->SimplePrint();
		}
	}
};

struct NamedRangeGroup: public AbstractNamedRange
{
	string groupName_;
	AbstractNamedRange * groupPtr_;
	NamedRangeGroup(string p_groupName):
		AbstractNamedRange(),
		groupName_(p_groupName), groupPtr_(0)
	{ }
	void Print() {
		cout << groupName_ << endl;
		if (groupPtr_) {
			groupPtr_->Print();
		}
		cout << "======" << endl;
		if (next_nr) {
			next_nr->Print();
		}
	}

	void SimplePrint()
	{
		cout << groupName_ << endl;
		if (next_nr) {
			next_nr->SimplePrint();
		}
	}
	void AddStub (string p_text, int p_code, int p_index_in_group);
	void AddGroup (NamedRangeGroup & p_group);
};

#endif /* xtcc_named_range_h */
