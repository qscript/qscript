//Grzegorz Prusak
#pragma once

#include "Format.h"
#include <string>
#include <vector>
#include <sstream>

//loops
#define REP(i,n) for(int i=0; i<(n); ++i)

class AbstractType
{
	public:
		AbstractType(const std::string &t) : token(t) {}
		virtual ~AbstractType(){}
		virtual int size() = 0;
		virtual void parse(const std::string &s, void *buffer, AbstractFormat &F) = 0;
		const std::string token;
};

extern AbstractType &INT8,&INT16,&INT32,&FLOAT,&DOUBLE;

