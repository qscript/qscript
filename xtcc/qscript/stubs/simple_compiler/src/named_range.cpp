/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/named_range.C
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

#include <sys/types.h>
#include <iostream>
#include <sstream>
#include "named_range.h"
#include "qscript_parser.h"

using std::cout;
using std::endl;
using std::stringstream;
using std::string;

named_range::~named_range()
{ }

void named_range::GenerateCode(StatementCompiledCode & code)
{
	code.quest_defns << "vector <stub_pair> " 
		<< qscript_parser::temp_name_generator.GetNewName()
		//<< "(" << stubs.size() << ");"
		<< ";" << endl << endl;

	for(int32_t i = 0; i<stubs.size(); ++i){
		code.quest_defns 
			<< qscript_parser::temp_name_generator.GetCurrentName() 
			<< ".push_back( stub_pair(\"" << stubs[i].stub_text
			<< "\", " << stubs[i].code << "));"
			<< endl;
	}
	code.quest_defns << "named_range " << name 
		<< "(NAMED_RANGE, " << lineNo_
		<< ", " << "\"" << name << "\""
		<< ", " << qscript_parser::temp_name_generator.GetCurrentName()
		<< ");" << endl;

	if(next_){
		next_->GenerateCode(code);
	}
}

named_range::named_range(named_range & nr)
	: AbstractStatement(nr.type_, nr.lineNo_),
	name (nr.name),  stubs (nr.stubs)
{
}
