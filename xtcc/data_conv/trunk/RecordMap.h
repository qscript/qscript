//Grzegorz Prusak
#pragma once

#include "Format.h"
#include "Type.h"
#include <string>
#include <vector>

//loops
#define REP(i,n) for(int i=0; i<(n); ++i)

class RecordMap
{
	public:
		RecordMap(AbstractFormat &F) : format(F) {}
	
		void add_field(const std::string &name, AbstractType *type)
		{
			fields.push_back(Field(name,type,byte_length()));
		}
	
		void parse(const std::string &name, const std::string &value, void *buffer)
		{
			REP(i,fields.size()) if(fields[i].name==name)
				fields[i].type->parse(value,(char*)buffer+fields[i].byte_pos,format);
		}
	
		int byte_length()
		{
			int fs = fields.size();
			return fs ? fields[fs-1].byte_pos + fields[fs-1].type->size() : 0;
		}
	
		AbstractFormat &format;
	
	private:
	
		struct Field
		{
			Field(const std::string &n, AbstractType *t, int p) : name(n), type(t), byte_pos(p) {}
			std::string name; AbstractType *type; int byte_pos;
		};
	
		std::vector<Field> fields;
};

