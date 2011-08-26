#ifndef BaseText_h
#define BaseText_h

#include <question.h>
#include <string>

struct BaseText 
{
	std::string baseText_;
	bool isDynamicBaseText_;
	AbstractQuestion * dynamicBaseQuestion_;
	BaseText(std::string base_text):
		baseText_(base_text), isDynamicBaseText_(false),
		dynamicBaseQuestion_(0)
	{ }
	BaseText(std::string base_text, bool l_isDynamicBaseText,
			AbstractQuestion * l_dynamicBaseQuestion):
		baseText_(base_text), isDynamicBaseText_(l_dynamicBaseQuestion),
		dynamicBaseQuestion_(l_dynamicBaseQuestion)
	{ }
};

#endif /* BaseText_h */
