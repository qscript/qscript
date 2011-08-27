/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/named_attributes.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

#ifndef xtcc_named_attributes_h
#define xtcc_named_attributes_h


#include <sys/types.h>
#include <string>
#include <vector>
#include <iostream>
#include "stmt.h"

using std::string;
using std::vector;
struct named_attribute_list: public AbstractStatement 
{
	string name;
	vector<string> attribute;
	struct SymbolTableEntry* symbolTableEntry_;

	named_attribute_list(DataType dt, int32_t lline_no,  string l_name, vector<string> l_attr);
	named_attribute_list();
	virtual ~named_attribute_list();
	virtual void GenerateCode(StatementCompiledCode & code);
	private:
		named_attribute_list& operator=(const named_attribute_list&);
		named_attribute_list (const named_attribute_list&);

};

#endif /* xtcc_named_attributes_h */
