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
#include "utils.h"

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
		code.quest_defns_init_code 
			<< qscript_parser::temp_name_generator.GetCurrentName() 
			<< ".push_back( stub_pair(\"" << stubs[i].stub_text
			<< "\", " << stubs[i].code << "));"
			<< endl;
	}
	code.quest_defns << "named_range " << name << ";" << endl;
	//code.quest_defns_init_code << "named_range " << name 
	//	<< "(NAMED_RANGE, " << lineNo_
	//	<< ", " << "\"" << name << "\""
	//	<< ", " << qscript_parser::temp_name_generator.GetCurrentName()
	//	<< ");" << endl;
	code.quest_defns_init_code << name << ".set_range_data(\""
		<< name << "\", " << qscript_parser::temp_name_generator.GetCurrentName()
		<< ");" << endl;
	stringstream mesg;
	mesg << "Review source of this file: check we are not allowing duplicate codes in the stubs ";
	LOG_MAINTAINER_MESSAGE(mesg.str());

	if(next_){
		next_->GenerateCode(code);
	}
}

named_range::named_range(named_range & nr)
	: AbstractStatement(nr.type_, nr.lineNo_, 0, 0),
	name (nr.name),  stubs (nr.stubs)
{
}


named_range::named_range(DataType l_type, int32_t l_line_number
		    , std::string l_name, std::vector <stub_pair>& l_stubs )
		: AbstractStatement(l_type, l_line_number, 0, 0)
		, name(l_name), stubs(l_stubs), minCode_(-1), maxCode_ (-1)
	{
		//cout << "named_range: constructor" << endl;
		for (int i = 0; i < l_stubs.size(); ++i) {
			if (i == 0) {
				minCode_ = l_stubs[i].code;
				maxCode_ = l_stubs[i].code;
			} else {
				if (minCode_ > l_stubs[i].code) {
					minCode_ = l_stubs[i].code;
				}
				if (maxCode_ < l_stubs[i].code) {
					maxCode_ = l_stubs[i].code;
				}
			}
		}
		//cout << "minCode_: " << minCode_ 
		//	<< "maxCode_: " << maxCode_ 
		//	<< endl;
	}
