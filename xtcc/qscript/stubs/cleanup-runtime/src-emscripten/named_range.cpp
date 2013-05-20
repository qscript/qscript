/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/named_range.C
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

#include <sys/types.h>
#include <iostream>
#include <sstream>
#include "named_range.h"
#include "utils.h"
//#include "TempNameGenerator.h"

using std::cout;
using std::endl;
using std::stringstream;
using std::string;

named_range::~named_range()
{ }

//namespace qscript_parser {
//	extern TempNameGenerator temp_name_generator;
//}

#if 0
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

	code.quest_defns_init_code
		<< "\tif (write_messages_flag) {\n"
		<< "\tfor (int i=0; i<"
		<< qscript_parser::temp_name_generator.GetCurrentName()<< ".size(); ++i) {\n"
		<< "\tmessages << \"<message id=\\\"\" << \"" << name  << "\" << \"_\" << i << \"\\\">\""
		<<	" << "
		<< qscript_parser::temp_name_generator.GetCurrentName()
		<< "[i].stub_text << \"</message>\\n\" << endl;\n"
		<< "\t}\n"
		<< "}\n";
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
#endif /* 0 */

named_range::named_range(named_range & nr)
	: //AbstractStatement(nr.type_, nr.lineNo_),
	name (nr.name),  stubs (nr.stubs)
{
}

#if 0
// this code works in normal c++ , doesnt in emscripten
template <typename Writer>
void named_range::Serialize(Writer& writer) const
{

	using namespace rapidjson;
	writer.String("name");
	writer.String(name.c_str(), (SizeType) name.length());
	writer.StartArray();
	for (std::vector<stub_pair>::const_iterator stub_pair_itr = stubs.begin();
			stub_pair_itr != stubs.end(); ++ stub_pair_itr
		) {
		stub_pair_itr->Serialize(writer);
	}
	writer.EndArray();

}
#endif

void named_range::toString (stringstream & s) const
{
	using std::endl;
	s << "{" << endl;
	s << "\"name\"" << ":" << "\""<< name << "\"";
	s << "{" << endl;
	int i = 0;
	for (std::vector<stub_pair>::const_iterator stub_pair_itr = stubs.begin();
			stub_pair_itr != stubs.end(); ++ stub_pair_itr, ++i
		) {
		if (i==0) {

		} else {
			s << ",";
		}
		stub_pair_itr->toString(s);
	}
	s << "}" << endl;
	s << "}" << endl;
}
