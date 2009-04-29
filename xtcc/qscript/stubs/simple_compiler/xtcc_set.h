/*! \file 
    \brief Implementation of sets specific to the qscript/xtcc programming langauge

 *  xtcc/xtcc/qscript/stubs/simple_compiler/xtcc_set.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#ifndef xtcc_set_h
#define xtcc_set_h

#include <vector>
#include <set>
#include <string>
//#include "common.h"
#include "symtab.h"
//using namespace std;
using std::vector;
using std::pair;
using std::set;

//! xtcc_set is the implementation of sets customised for the qscript and xtcc compilers
/*!
   The set can consist of individual elements or ranges of 
   elements as demonstrated below
	{ 1, 2-5, 10, 21-40} 
*/
struct xtcc_set {
	vector < pair<int,int> > range;
	set<int> indiv;
	xtcc_set(datatype dt, string name, xtcc_set& xs1);
	xtcc_set(xtcc_set& xs1);
	xtcc_set& operator=(const xtcc_set& xs1);
	xtcc_set();
	void reset();
	void add_range(int n1, int n2);
	void add_indiv(int n1);
	bool exists(int key);

};

#endif /* xtcc_set_h */
