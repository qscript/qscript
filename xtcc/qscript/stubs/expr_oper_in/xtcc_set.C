#include "xtcc_set.h"

xtcc_set::xtcc_set(): range(0) { 
}

/*
xtcc_set::xtcc_set(datatype dt, string name, xtcc_set& xs): 
	range(xs.range), indiv(xs.indiv){
}
*/

xtcc_set::xtcc_set(xtcc_set& xs1): 
	range(xs1.range), indiv(xs1.indiv){
	}

xtcc_set& xtcc_set::operator= (const xtcc_set& xs1){
	range=xs1.range;
	indiv = xs1.indiv;
	return *this;
}

void xtcc_set::reset(){
	range.clear();
	indiv.clear();
}

void xtcc_set::add_range(int n1, int n2){
	range.push_back( pair<int,int>(n1, n2));
}

void xtcc_set::add_indiv(int n1){
	indiv.insert(n1);
}
