//Grzegorz Prusak
#pragma once

#include <string>
#include <vector>

//loops
#define REP(i,n) for(int i=0; i<(n); ++i)

class AbstractFormat
{
	friend int main(int,char**);

	public:
		AbstractFormat(const std::string &n) : name(n) { list.push_back(this); }
		virtual ~AbstractFormat(){}
		
		virtual char   operator()(char)   = 0;
		virtual short  operator()(short)  = 0;
		virtual long   operator()(long)   = 0;
		virtual float  operator()(float)  = 0;
		virtual double operator()(double) = 0;
		
		const std::string name;
		
		static AbstractFormat * get(std::string &s)
		{
			REP(i,list.size()) if(list[i]->name==s) return list[i];
			throw "unsupported format: " + s;
		}
		
	private:
		static std::vector<AbstractFormat*> list;
};

