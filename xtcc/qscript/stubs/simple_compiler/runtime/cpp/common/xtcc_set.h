/*! \file
    \brief Implementation of sets specific to the qscript/xtcc programming langauge

 *  xtcc/xtcc/qscript/stubs/simple_compiler/xtcc_set.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#ifndef xtcc_set_h
#define xtcc_set_h

#include <sys/types.h>
#include <vector>
#include <set>
#include <string>
//#include "symtab.h"
#include "datatype.h"
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
	vector < pair<int32_t,int32_t> > range;
	set<int32_t> indiv;
	XtccSet(DataType dt, std::string name, XtccSet& xs1);
	XtccSet(const XtccSet& xs1);
	XtccSet(XtccSet & xs1);
	XtccSet& operator=(const XtccSet& xs1);
	XtccSet();
	void reset();
	void add_range(int32_t n1, int32_t n2);
	void add_indiv(int32_t n1);
	bool exists(int32_t key);
	bool contains_subset(std::set<int32_t> & set_data);
	bool contains_value(int v);
	std::string print_replicate_code(std::string set_name);
	int32_t GetMax();
	bool isEmpty();
};

#endif /* xtcc_set_h */
