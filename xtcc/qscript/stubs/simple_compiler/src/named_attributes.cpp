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


void named_attribute_list::GenerateCode(StatementCompiledCode & code)
{
	code.program_code << "/* "
		<< __PRETTY_FUNCTION__ << ", " << __FILE__ << ", " << __LINE__ 
		<< "*/" << endl;
	if (next_){
		next_->GenerateCode(code);
	}
}
