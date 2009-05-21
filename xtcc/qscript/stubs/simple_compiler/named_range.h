/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/named_range.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

#ifndef xtcc_named_range_h
#define xtcc_named_range_h
#include <fstream>
#include "stub_pair.h"
#include "stmt.h"

struct named_range: public stmt{
	string name;
	vector <stub_pair> stubs;
	//named_range(): name(""), stubs(){}
	void generate_code(ostringstream & quest_defns, ostringstream& program_code);
	named_range(datatype l_type, int l_line_number, 
		string l_name, vector <stub_pair>& l_stubs ):
		stmt(l_type, l_line_number),
		name(l_name), stubs(l_stubs)
	{
		//cout << "named_range: constructor" << endl;
		}
		~named_range();
};

#endif /* xtcc_named_range_h */
