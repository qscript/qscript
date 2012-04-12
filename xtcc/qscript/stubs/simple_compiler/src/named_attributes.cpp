#include <sys/types.h>
#include <iostream>
#include "named_attributes.h"
using std::cout;
using std::endl;

named_attribute_list::named_attribute_list(DataType dt, int32_t lline_no
					   , string l_name
					   , vector<string> l_attr)
	: AbstractStatement(dt, lline_no, 0, 0)
	, name(l_name), attribute(l_attr), symp(0)
{ }
void print_stmt_lst(FILE * & fptr)
{
	cout << "named_attribute_list: not yet implemented" << endl;
}
