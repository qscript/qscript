#include <sys/types.h>
#include <iostream>
#include "named_attributes.h"
using std::cout;
using std::endl;

named_attribute_list::named_attribute_list(DataType dt, int32_t lline_no
					   , string l_name
					   , vector<string> l_attr)
	: AbstractStatement(dt, lline_no)
	, name(l_name), attribute(l_attr), symbolTableEntry_(0)
{ }

named_attribute_list::named_attribute_list()
	: AbstractStatement(NAMED_ATTRIBUTE_TYPE, 0)
	, name(), attribute(), symbolTableEntry_(0)
{ }

named_attribute_list::~named_attribute_list()
{ }

void named_attribute_list::GenerateCode(StatementCompiledCode & code)
{
	code.program_code << "/* "
		<< __PRETTY_FUNCTION__ << ", " << __FILE__ << ", " << __LINE__ 
		<< "*/" << endl;
	code.quest_defns << "named_attribute_list " 
		<<  name << ";\n";
	code.quest_defns_init_code
		<< name << ".name = \"" << name << "\";\n";
	for (int i=0; i<attribute.size(); ++i) {
		code.quest_defns_init_code 
			<<  name << ".attribute.push_back (string(\"" << attribute[i]
				<< "\"));\n";
	}
	if (next_) {
		next_->GenerateCode(code);
	}
}
