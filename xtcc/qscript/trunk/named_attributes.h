#ifndef xtcc_named_attributes_h
#define xtcc_named_attributes_h


#include <string>
#include <vector>
#include "../xtcc/trunk/stmt.h"
using std::string;
using std::vector;
struct named_attribute_list: public stmt{
	string name;
	vector<string> attribute;
	struct symtab_ent* symp;

	named_attribute_list(datatype dt, int lline_no,  string l_name, vector<string> l_attr):  stmt(dt, lline_no),
		name(l_name), attribute(l_attr), symp(0)
	{}
	void print_stmt_lst(FILE * & fptr){
		cout << "named_attribute_list: not yet implemented" << endl;
	}
};

#endif /* xtcc_named_attributes_h */
