#include "TempNameGenerator.h"
#include <sstream>
#include <string>

using std::stringstream;
using std::string;

TempNameGenerator::TempNameGenerator(string p_prefix)
	: prefix_(p_prefix), count(0)
{ }


std::string TempNameGenerator::GetNewName()
{
	++count;
	stringstream s1;
	//s1 << "temp_xtcc_set_" << count;
	s1 << prefix_ << count;
	return s1.str();
}

std::string TempNameGenerator::GetCurrentName()
{
	stringstream s1;
	//s1 << "temp_xtcc_set_" << count;
	s1 << prefix_ << count;
	return s1.str();
}
