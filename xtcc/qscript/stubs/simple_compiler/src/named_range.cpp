/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/named_range.C
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

#include "named_range.h"
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::stringstream;
using std::string;

named_range::~named_range()
{ }

void named_range::GenerateCode (StatementCompiledCode & code)
{
	code.quest_defns << "vector <stub_pair> " << name 
		//<< "(" << stubs.size() << ");"  
		<< ";" << endl << endl;

	for(int i=0; i<stubs.size(); ++i){
		code.quest_defns << name << ".push_back( stub_pair(\"" << stubs[i].stub_text 
			<< "\", " << stubs[i].code << "));" 
			<< endl;
	}
	if(next_){
		next_->GenerateCode(code);
	}
}

