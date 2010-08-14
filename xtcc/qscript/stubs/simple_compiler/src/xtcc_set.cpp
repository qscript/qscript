/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/xtcc_set.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#include "xtcc_set.h"
#include "qscript_parser.h"
#include <sstream>

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

void XtccSet::add_range(int n1, int n2)
{
	using std::endl;
	using std::stringstream;

	for(	set<int>::iterator it=indiv.begin(); it!=indiv.end(); ++it){
		int v = *it;
		if(v>=n1 && v <= n2){
			stringstream err_msg;
			err_msg << "range given: " << n1 << " - " << n2
				<< " makes the individual entry: "  << v << " redundant";
			print_err(compiler_sem_err, err_msg.str().c_str()
					, qscript_parser::line_no
					, __LINE__, __FILE__ );
		}
	}

	for(int i=0; i<range.size(); ++i){
		if(n1 <= range[i].first && n2 >= range[i].second){
			stringstream err_msg;
			err_msg << "range given: " << n1 << " - " << n2
				<< " is completely contains in an earlier range:" 
				<< range[i].first << " - " << range[i].second << endl;
			print_err(compiler_sem_err, err_msg.str().c_str()
					, qscript_parser::line_no
					, __LINE__, __FILE__ );
		} else if ( n1 >= range[i].first && n2 <= range[i].second){ 
			stringstream err_msg;
			err_msg << "range given: " << n1 << " - " << n2
				<< " is completely contained in an earlier range:" 
				<< range[i].first << " - " << range[i].second << endl;
			print_err(compiler_sem_err, err_msg.str().c_str()
					, qscript_parser::line_no
					, __LINE__, __FILE__ );
		} else if (n1 <= range[i].first && 
				n2 >= range[i].first && n2<=range[i].second) {
			stringstream err_msg;
			err_msg << "range given: " << n1 << " - " << n2
				<< " is partially contained in an earlier range:" 
				<< range[i].first << " - " << range[i].second << endl;
			print_err(compiler_sem_err, err_msg.str().c_str()
					, qscript_parser::line_no
					, __LINE__, __FILE__ );
		} else if (n2 > range[i].second && 
				n1 >= range[i].first && n1<=range[i].second) {
			stringstream err_msg;
			err_msg << "range given: " << n1 << " - " << n2
				<< " is partially contained in an earlier range:" 
				<< range[i].first << " - " << range[i].second << endl;
			print_err(compiler_sem_err, err_msg.str().c_str()
					, qscript_parser::line_no
					, __LINE__, __FILE__ );
		} else if ( 	(n1 < range[i].first && n2 < range[i].first)
			    ||	(n1 > range[i].second && n2 > range[i].second)){
			// this is the allowed case
			range.push_back( pair<int,int>(n1, n2));
		} else {
			stringstream err_msg;
			err_msg << "internal compiler programming error contact author";
			print_err(compiler_internal_error, err_msg.str().c_str()
					, qscript_parser::line_no
					, __LINE__, __FILE__ );
		}
	}
}

void XtccSet::add_indiv(int n1)
{
	using std::endl;
	using std::stringstream;
	for(int i=0; i<range.size(); ++i){
		if(n1 >= range[i].first && n1 <= range[i].second){
			stringstream err_msg;
			err_msg << "individual element : " << n1 << " is already contained in range: " 
				<< range[i].first << " - " << range[i].second;
			print_err(compiler_sem_err, err_msg.str().c_str()
					, qscript_parser::line_no
					, __LINE__, __FILE__ );
		}
	}
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

