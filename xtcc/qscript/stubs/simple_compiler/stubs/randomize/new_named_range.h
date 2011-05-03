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

struct AbstractNamedRange: public AbstractStatement
{
	struct AbstractNamedRange *next_nr, *prev_nr;
	AbstractNamedRange():
		AbstractStatement (NAMED_RANGE, 0),
		next_nr(0), prev_nr(0)
	{ }
	void GenerateCode(StatementCompiledCode & code)
	{ }
	virtual void Print()=0;
};


struct NamedRangeList: public AbstractNamedRange
{
	std::vector <stub_pair> stubs;
	NamedRangeList():
		AbstractNamedRange()
	{ }
	void Print() {
		for (int i=0; i<stubs.size(); ++i) {
			cout << stubs[i].stub_text << ", " << stubs[i].code << endl;
		}
		if (next_nr) {
			next_nr->Print();
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
};

#endif /* xtcc_named_range_h */
