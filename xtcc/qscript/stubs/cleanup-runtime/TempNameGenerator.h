#ifndef TempNameGenerator_h
#define TempNameGenerator_h

#include <string>

struct TempNameGenerator 
{
	int count;
	std::string prefix_;
	TempNameGenerator(std::string p_prefix);
	
	std::string GetNewName();
	std::string GetCurrentName();
};

#endif /* TempNameGenerator_h */
