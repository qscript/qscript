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
	named_range * sub_group_ptr;
	named_range * next_ptr;
	bool stubs_come_first;
	//named_range(): name(""), stubs(){}
	void GenerateCode(StatementCompiledCode & code);
	named_range()
		: AbstractStatement(NAMED_RANGE, 0)
		  , name(), stubs()
		  , sub_group_ptr(0) , next_ptr(0)
		  , stubs_come_first(false)
	{ }

	named_range(DataType l_type, int32_t l_line_number
		    , std::string l_name)
		: AbstractStatement(l_type, l_line_number)
		, name(l_name)
		  , sub_group_ptr(0) , next_ptr(0)
		  , stubs_come_first(false)
	{ }

	named_range(DataType l_type, int32_t l_line_number
		    , std::string l_name, std::vector <stub_pair>& l_stubs )
		: AbstractStatement(l_type, l_line_number)
		, name(l_name), stubs(l_stubs)
		  , sub_group_ptr(0) , next_ptr(0)
		  , stubs_come_first(false)
	{ }

	void set_range_data(string l_name, std::vector<stub_pair> & l_stubs)
	{
		stubs = l_stubs;
		name = l_name;
	}
	void set_stubs(std::vector<stub_pair> & l_stubs)
	{
		stubs = l_stubs;
	}
	~named_range();
	named_range(named_range & nr);
};

#endif /* xtcc_named_range_h */
