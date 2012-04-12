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
	//named_range(): name(""), stubs(){}
	void GenerateCode(StatementCompiledCode & code);
	named_range()
		: AbstractStatement(NAMED_RANGE, 0, 0, 0)
		  , name(), stubs()
	{ }
	named_range(DataType l_type, int32_t l_line_number
		    , std::string l_name, std::vector <stub_pair>& l_stubs )
		: AbstractStatement(l_type, l_line_number, 0, 0)
		, name(l_name), stubs(l_stubs)
	{
		//cout << "named_range: constructor" << endl;
	}
	void set_range_data(string l_name, std::vector<stub_pair> & l_stubs)
	{
		stubs = l_stubs;
		name = l_name;
	}
	~named_range();
	named_range(named_range & nr);
};

#endif /* xtcc_named_range_h */
