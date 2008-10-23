#ifndef xtcc_set_h
#define xtcc_set_h

#include <vector>
#include <set>
using namespace std;

struct xtcc_set {
	vector < pair<int,int> > range;
	set<int> indiv;
	//xtcc_set(datatype dt, string name, xtcc_set& xs1);
	xtcc_set(xtcc_set& xs1);
	xtcc_set& operator=(const xtcc_set& xs1);
	xtcc_set();
	void reset();
	void add_range(int n1, int n2);
	void add_indiv(int n1);
};

#endif /* xtcc_set_h */
