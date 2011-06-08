/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/xtcc_set.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#include <sstream>
#include <iostream>
#include <sys/types.h>
#include "xtcc_set.h"
#include "qscript_parser.h"

XtccSet::XtccSet(): range(0), indiv()
{ }

XtccSet::XtccSet(DataType dt, string name, XtccSet& xs)
	: range(xs.range), indiv(xs.indiv)
{ }

XtccSet::XtccSet(const XtccSet& xs1)
	: range(xs1.range), indiv(xs1.indiv)
{ }

XtccSet::XtccSet(XtccSet & xs1)
	: range(xs1.range), indiv(xs1.indiv)
{ }

XtccSet& XtccSet::operator= (const XtccSet& xs1)
{
	range = xs1.range;
	indiv = xs1.indiv;
	return *this;
}

void XtccSet::reset()
{
	using std::endl;
	using std::cerr;
	//cerr << "XtccSet::reset() called" << endl;
	range.clear();
	indiv.clear();
}

void XtccSet::add_range(int n1, int n2)
{
	using std::endl;
	using std::stringstream;
	using std::cerr;
	//cerr << "XtccSet::add_range: n1=" << n1 << ", n2=" << n2 << endl;
	//cerr << "range.size(): " << range.size() << endl;

	for(set<int>::iterator it = indiv.begin(); it != indiv.end(); ++it){
		int v = *it;
		if(v >= n1 && v <= n2){
			stringstream err_msg;
			err_msg << "range given: " << n1 << " - " << n2
				<< " makes the individual entry: "  << v << " redundant";
			print_err(compiler_sem_err, err_msg.str().c_str()
					, qscript_parser::line_no
					, __LINE__, __FILE__);
		}
	}

	if(range.size() == 0){
		//cerr << "range.size()==0 pushing back: "  << n1 << "-" << n2 << endl;
		range.push_back(pair<int,int>(n1, n2));
		return;
	}

	for(int i = 0; i < range.size(); ++i){
		if(n1 <= range[i].first && n2 >= range[i].second){
			stringstream err_msg;
			err_msg << "range given: " << n1 << " - " << n2
				<< " completely contains an earlier range:"
				<< range[i].first << " - " << range[i].second
				<< " and makes it redundant."
				<< endl;

			print_err(compiler_sem_err, err_msg.str().c_str()
					, qscript_parser::line_no
					, __LINE__, __FILE__);
		} else if ( n1 >= range[i].first && n2 <= range[i].second){
			stringstream err_msg;
			err_msg << "range given: " << n1 << " - " << n2
				<< " is completely contained in an earlier range:"
				<< range[i].first << " - " << range[i].second << endl;
			print_err(compiler_sem_err, err_msg.str().c_str()
					, qscript_parser::line_no
					, __LINE__, __FILE__);
		} else if (n1 <= range[i].first
			   && n2 >= range[i].first && n2 <= range[i].second) {
			stringstream err_msg;
			err_msg << "range given: " << n1 << " - " << n2
				<< " is partially contained in an earlier range:"
				<< range[i].first << " - " << range[i].second << endl;
			print_err(compiler_sem_err, err_msg.str().c_str()
					, qscript_parser::line_no
					, __LINE__, __FILE__);
		} else if (n2 > range[i].second
			   && n1 >= range[i].first && n1 <= range[i].second) {
			stringstream err_msg;
			err_msg << "range given: " << n1 << " - " << n2
				<< " is partially contained in an earlier range:"
				<< range[i].first << " - " << range[i].second << endl;
			print_err(compiler_sem_err, err_msg.str().c_str()
					, qscript_parser::line_no
					, __LINE__, __FILE__);
		} else if ( (n1 < range[i].first && n2 < range[i].first)
			    ||	(n1 > range[i].second && n2 > range[i].second)){
			// this is the allowed case
		} else {
			stringstream err_msg;
			err_msg << "internal compiler programming error. Contact maintainer";
			print_err(compiler_internal_error, err_msg.str().c_str()
					, qscript_parser::line_no
					, __LINE__, __FILE__);
		}
	}

	range.push_back(pair<int,int>(n1, n2));
}

void XtccSet::add_indiv(int n1)
{
	using std::stringstream;
	using std::cerr;
	using std::endl;
	//cerr << "XtccSet::add_indiv" << endl;
	if(exists(n1)){
		stringstream err_msg;
		err_msg << "individual element : " << n1 << " is already contained in range and is redundant: ";
		//	<< range[i].first << " - " << range[i].second;
		print_err(compiler_sem_err, err_msg.str().c_str()
				, qscript_parser::line_no
				, __LINE__, __FILE__);
	} else {
		indiv.insert(n1);
	}
}


bool XtccSet::exists(int key)
{
	for (unsigned int i = 0; i < range.size(); ++i) {
		if (key >= range[i].first && key <= range[i].second) {
			return true;
		}
	}
	/*
	for(	set<int>::iterator it = indiv.begin(); it!=indiv.end(); ++it){
		if (key == *it) {
			return true;
		}
	}
	*/
	set<int>::iterator it = indiv.find(key);
	if(it != indiv.end()){
		return true;
	}
	return false;
}

bool XtccSet::contains_subset(std::set<int32_t> & set_data)
{
	bool val_exists = false;

	if (set_data.begin() == set_data.end()) {
		//empty question - could be blank -
		// if it wasnt for this we return true - a bug
		return false;
	}
	for(set<int32_t>::iterator it = set_data.begin();
			it != set_data.end(); ++it) {
		val_exists = exists(*it);
		if (!val_exists) {
			return false;
		}
	}
	return true;

}

string XtccSet::print_replicate_code(string set_name)
{
	using std::endl;
	using std::stringstream;
	stringstream code;
	//code << "XtccSet " << set_name << ";" << endl;;
	for(	set<int32_t>::iterator it = indiv.begin();
			it != indiv.end(); ++it){
		code << set_name << ".indiv.insert(" << *it
			<< ");" << endl;
	}
	for(uint32_t i = 0; i < range.size(); ++i){
		code 	<< set_name
			<< ".range.push_back(pair<int32_t,int32_t>("
			<< range[i].first << ","
			<< range[i].second
			<< "));" << endl;
	}
	return code.str();

}

int32_t XtccSet::GetMax()
{
	// assume no negative codes are allowed
	// if this ever changes - this breaks
	int32_t max_code = 0; 
	for(	set<int32_t>::iterator it = indiv.begin();
			it != indiv.end(); ++it) {
		if (max_code < *it) {
			max_code = *it;
		}
	}
	for(uint32_t i = 0; i < range.size(); ++i) {
		if (max_code < range[i].second) {
			max_code = range[i].second;
		}
	}
	return max_code;

}
