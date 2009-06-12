/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/xtcc_set.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#include "xtcc_set.h"

XtccSet::XtccSet(): range(0){ 
}

XtccSet::XtccSet(DataType dt, string name, XtccSet& xs): 
	range(xs.range), indiv(xs.indiv){
}

XtccSet::XtccSet(XtccSet& xs1): range(xs1.range), indiv(xs1.indiv){
}

XtccSet& XtccSet::operator= (const XtccSet& xs1){
	range=xs1.range;
	indiv = xs1.indiv;
	return *this;
}

void XtccSet::reset(){
	range.clear();
	indiv.clear();
}

void XtccSet::add_range(int n1, int n2){
	range.push_back( pair<int,int>(n1, n2));
}

void XtccSet::add_indiv(int n1){
	indiv.insert(n1);
}


bool XtccSet::exists(int key)
{
	for (unsigned int i = 0; i < range.size(); ++i) {
		if (key >= range[i].first && key <= range[i].second) {
			return true;
		}
	}
	for(	set<int>::iterator it=indiv.begin(); it!=indiv.end(); ++it){
		if (key == *it) {
			return true;
		}
	}
	return false;
}

