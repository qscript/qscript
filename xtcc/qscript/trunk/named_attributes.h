#ifndef xtcc_named_attributes_h
#define xtcc_named_attributes_h


#include <string>
#include <vector>
#include "stmt.h"
using std::string;
using std::vector;
struct named_attribute_list: public AbstractStatement{
	string name;
	vector<string> attribute;
	struct SymbolTableEntry* symbolTableEntry_;

	named_attribute_list(DataType dt, int lline_no,  string l_name, vector<string> l_attr):  
		AbstractStatement(dt, lline_no),
		name(l_name), attribute(l_attr), symbolTableEntry_(0)
	{}
	void GenerateCode(FILE * & fptr){
		cout << "named_attribute_list: not yet implemented" << endl;
	}
};

#endif /* xtcc_named_attributes_h */
