//! Active variable information 
#ifndef active_var_info_h
#define active_var_info_h

#include "datatype.h"
#include <string>

	//! Structure to store active variable information at a given point in compilation
	struct ActiveVariableInfo 
	{
		std::string name_;
		DataType type_;
		ActiveVariableInfo(std::string l_name, DataType l_type)
			: name_(l_name), type_(l_type)
		{}
	};

#endif /* active_var_info_h */
