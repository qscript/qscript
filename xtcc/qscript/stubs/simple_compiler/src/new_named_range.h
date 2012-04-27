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
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "stub_pair.h"
//#include "stmt.h"
#include "AbstractStatement.h"

using namespace std;
struct NamedRangeList;
struct NamedRangeGroup;
struct NamedRangeStub;

struct MyRNG
{
	unsigned int random_seed;
	MyRNG() : random_seed (time(0))
	{ }
	int operator () (ptrdiff_t i);

};

struct AbstractNamedRange: public AbstractStatement
{
	struct AbstractNamedRange *next_nr, *prev_nr;
	AbstractNamedRange (int p_line_no):
		AbstractStatement (NAMED_RANGE, p_line_no),
		next_nr(0), prev_nr(0)
	{ }
	virtual void GenerateCode(StatementCompiledCode & code)=0;
	virtual void Print ()=0;
	virtual void SimplePrint ()=0;
	virtual void AddStub (string p_text, int p_code, int p_index_in_group)=0;
	virtual void AddGroup (NamedRangeGroup & p_group, int p_index_in_group)=0;
	virtual void Vectorize (AbstractNamedRange * invoker, vector <AbstractNamedRange*> & p_stub_grp_vec) = 0;
	virtual void VectorizePrint (AbstractNamedRange * invoker) = 0;
	virtual void CreateDisplayStubs (AbstractNamedRange * invoker, vector<stub_pair> & display_result) = 0;
	private:
		AbstractNamedRange& operator=(const AbstractNamedRange&);
		AbstractNamedRange (const AbstractNamedRange&);

};


struct NamedRangeList: public AbstractNamedRange
{
	std::vector <stub_pair> stubs;
	NamedRangeList (int p_line_no):
		AbstractNamedRange (p_line_no),
		stubs ()
	{ }
	void GenerateCode(StatementCompiledCode & code)
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

	//void Vectorize (vector <AbstractNamedRange*> & p_stub_grp_vec);
	void Vectorize (AbstractNamedRange * invoker, vector <AbstractNamedRange*> & p_stub_grp_vec) ;

	void AddStub (string p_text, int p_code, int p_index_in_group);
	void AddGroup (NamedRangeGroup & p_group, int p_index_in_group);
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
	void VectorizePrint (AbstractNamedRange * invoker) 
	{
		for (int i=0; i<stubs.size(); ++i) {
			cout << stubs[i].stub_text << ", " << stubs[i].code 
				<< ", index_in_group: " << stubs[i].index_in_group
				<< endl;
		}
	}
	void CreateDisplayStubs (AbstractNamedRange * invoker, vector<stub_pair> & display_result);

};

struct NamedRangeGroup: public AbstractNamedRange
{
	string groupName_;
	AbstractNamedRange * groupPtr_;
	vector <AbstractNamedRange *> stub_grp_vec;
	vector <int> randomized_order;
	int index_in_group;
	NamedRangeGroup (int p_line_no, string p_groupName, int p_index_in_group):
		AbstractNamedRange (p_line_no),
		groupName_(p_groupName), groupPtr_(0),
		stub_grp_vec(), randomized_order(),
		index_in_group (p_index_in_group)
	{ }
	void GenerateCode(StatementCompiledCode & code);
	void Print()
	{
		cout << groupName_
			<< ", index_in_group: " << index_in_group
			<< endl;
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
	void AddGroup (NamedRangeGroup & p_group, int p_index_in_group);

	//void Vectorize (vector <AbstractNamedRange*> & p_stub_grp_vec);
	void Vectorize (AbstractNamedRange * invoker, vector <AbstractNamedRange*> & p_stub_grp_vec) ;
	void VectorizePrint (AbstractNamedRange * invoker)
	{
		cout << groupName_ ;
		cout << ", stub_grp_vec.size(): " << stub_grp_vec.size() << endl;
		//if (invoker == this) {
			if (randomized_order.size() == 0) {
				for (int i=0; i < stub_grp_vec.size(); ++i) {
					stub_grp_vec[i]->VectorizePrint(invoker);
				}
			} else {
				for (int i=0; i < randomized_order.size(); ++i) {
					stub_grp_vec[randomized_order[i]]->VectorizePrint(invoker);
				}
			}
		//}
	}
	void CreateDisplayStubs (AbstractNamedRange * invoker
			, vector<stub_pair> & display_result);
	// Warning : this function should only be called
	// after calling Vectorize on the group
	void Randomize();
	void SaveRandomizedOrderToDisk();
	private:
		NamedRangeGroup& operator=(const NamedRangeGroup&);
		NamedRangeGroup (const NamedRangeGroup&);
};

struct NamedRangeStub : public AbstractNamedRange
{
	stub_pair stub;
	void Print()
	{
		cout << stub.code << ": " <<  stub.stub_text << endl;
	}
	void SimplePrint ()
	{
		Print();
	}
	void AddStub(string p_text, int p_code, int p_index_in_group)
	{
		stub.stub_text = p_text;
		stub.code = p_code;
	}
	NamedRangeStub (int p_line_no, string p_text, int p_code):
		AbstractNamedRange (p_line_no),
		stub(p_text, p_code)
	{}
	void AddGroup (NamedRangeGroup & p_group, int p_index_in_group)
	{
	}
	void Vectorize (AbstractNamedRange * invoker, vector <AbstractNamedRange*> & p_stub_grp_vec)
	{
	}
	void VectorizePrint (AbstractNamedRange * invoker)
	{
		Print();
	}
	void GenerateCode(StatementCompiledCode & code)
	{ }

	void CreateDisplayStubs (AbstractNamedRange * invoker, vector<stub_pair> & display_result);

};

#endif /* xtcc_named_range_h */
