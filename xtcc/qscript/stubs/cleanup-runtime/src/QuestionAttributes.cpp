
#include <sstream>
#include <string>
#include "QuestionAttributes.h"

using std::string;
using std::stringstream;


void QuestionAttributes::Reset()
{ hidden_ = false; allowBlank_ = false; }

QuestionAttributes::QuestionAttributes()
	: hidden_(false), allowBlank_(false)
{ }

QuestionAttributes::QuestionAttributes(bool p_Hidden, bool p_allowBlank)
	: hidden_(p_Hidden), allowBlank_(p_allowBlank)
{ }

string QuestionAttributes::Print()
{
	stringstream s;
	s << " QuestionAttributes(";
	if (hidden_ == false) {
		s << "false ";
	} else {
		s << "true ";
	}
	s << ", ";
	if (allowBlank_ == false) {
		s << "false";
	} else {
		s << "true";
	}
	s << ")";
	return s.str();
}

void QuestionAttributes::setHidden() { hidden_ = true; }

void QuestionAttributes::setAllowBlank() { allowBlank_ = true; }


bool QuestionAttributes::isAllowBlank() { return allowBlank_; }
 
bool QuestionAttributes::isHidden() { return hidden_; }
