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
#include "symtab.h"
using std::vector;
using std::pair;
using std::set;

//! XtccSet is the implementation of sets customised for the qscript and xtcc compilers
/*!
   The set can consist of individual elements or ranges of 
   elements as demonstrated below
	{ 1, 2-5, 10, 21-40} 
*/
struct XtccSet {
	vector < pair<int,int> > range;
	set<int> indiv;
	XtccSet(DataType dt, string name, XtccSet& xs1);
	XtccSet(XtccSet& xs1);
	XtccSet& operator=(const XtccSet& xs1);
	XtccSet();
	void reset();
	void add_range(int n1, int n2);
	void add_indiv(int n1);
	bool exists(int key);

};

#endif /* xtcc_set_h */
