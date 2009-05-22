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
		AbstractType(const std::string &t) : token(t) { list.push_back(this); }
		virtual ~AbstractType(){}
	
		virtual int size() = 0;
		
		virtual void parse(const std::string &s, void *buffer, AbstractFormat &F) = 0;
		
		static AbstractType * get(const std::string &s)
		{
			REP(i,list.size()) if(list[i]->token==s) return list[i];
			throw "unknown type: " + s;
		}
		
		const std::string token;
		
	private:
		static std::vector<AbstractType*> list;
};

