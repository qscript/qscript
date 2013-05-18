/*
 *  Copyright (C)  2011
 *	Neil Xavier D'Souza
 */

#ifndef QuestionAttributes_h
#define QuestionAttributes_h
#include <string>

struct QuestionAttributes
{
	bool hidden_;
	bool allowBlank_;
	void Reset();
	QuestionAttributes();
	QuestionAttributes(bool p_Hidden, bool p_allowBlank);
	void setHidden();
	void setAllowBlank();
	bool isAllowBlank();
	bool isHidden();
	std::string Print();
};

#endif /* QuestionAttributes_h */
