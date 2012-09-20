/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/named_range.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

#ifndef xtcc_named_range_h
#define xtcc_named_range_h
#include <sys/types.h>
//#include <fstream>
#include <vector>
#include <string>
#include "stub_pair.h"
//#include "stmt.h"
#include "AbstractStatement.h"


struct named_range: public AbstractStatement
{
	std::string name;
	std::vector <stub_pair> stubs;
	int minCode_;
	int maxCode_;
	//named_range(): name(""), stubs(){}
	void GenerateCode(StatementCompiledCode & code);
	named_range()
		: AbstractStatement(NAMED_RANGE, 0, 0, 0)
		  , name(), stubs(), minCode_(-1), maxCode_ (-1)
	{ }

	named_range(DataType l_type, int32_t l_line_number
		    , std::string l_name, std::vector <stub_pair>& l_stubs );
		/*
		: AbstractStatement(l_type, l_line_number, 0, 0)
		, name(l_name), stubs(l_stubs), minCode_(-1), maxCode_ (-1)
	{
		//cout << "named_range: constructor" << endl;
		for (int i = 0; i < l_stubs.size(); ++i) {
			if (i == 0) {
				minCode_ = l_stubs[i].code;
				maxCode_ = l_stubs[i].code;
			} else {
				if (minCode_ < l_stubs[i].code) {
					minCode_ = l_stubs[i].code;
				}
				if (maxCode_ > l_stubs[i].code) {
					maxCode_ = l_stubs[i].code;
				}
			}
		}
		cout << "minCode_: " << minCode_ 
			<< "maxCode_: " << maxCode_ 
			<< endl;
	}
	*/

	void set_range_data(string l_name, std::vector<stub_pair> & l_stubs)
	{
		stubs = l_stubs;
		name = l_name;
	}
	~named_range();
	named_range(named_range & nr);
};

#endif /* xtcc_named_range_h */
