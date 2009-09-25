
#ifndef xtcc_named_range_h
#define xtcc_named_range_h
#include "stub_pair.h"
#include <fstream>
#include <string>
#include <vector>
	struct named_range{
		std::string name;
		std::vector <stub_pair> stubs;
		named_range();
		named_range(std::string l_name, std::vector <stub_pair>& l_stubs );
	};

#endif /* xtcc_named_range_h */
