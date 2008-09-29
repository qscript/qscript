#ifndef xtcc_named_attributes_h
#define xtcc_named_attributes_h


struct named_attribute_list {
	string name;
	vector<string> attribute;
	named_attribute_list(string l_name, vector<string> l_attr): 
		name(l_name), attribute(l_attr)
	{}
};

#endif /* xtcc_named_attributes_h */
