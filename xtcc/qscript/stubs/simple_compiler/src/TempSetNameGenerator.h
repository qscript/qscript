#ifndef TempSetNameGenerator_h
#define TempSetNameGenerator_h

#include <string>

struct TempSetNameGenerator 
{
	int count;
	TempSetNameGenerator();
	
	std::string GetNewTempXtccSetName();
	std::string GetCurrentTempXtccSetName();
};

#endif /* TempSetNameGenerator_h */
