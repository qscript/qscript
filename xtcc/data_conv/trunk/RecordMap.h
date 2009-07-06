//Grzegorz Prusak
#pragma once

#include "Format.h"
#include "Type.h"
#include <string>
#include <vector>
#include <ostream>

//loops
#define REP(i,n) for(int i=0; i<(n); ++i)

class RecordMap
{
	public:
		RecordMap(AbstractFormat &F) : format(F) {}
	
		void write_header(std::ostream &os)
		{
			const char *signature = "xtcc";
			const char *version = "0.0.0.0";
			char 	CHAR[4] = {format('x'),format('t'),format('c'),format('c')};
			short 	SHORT 	= format((short )0x4142);
			long 	LONG 	= format((long  )0x43444546);
			float 	FLOAT 	= format((float )3297809.75);
			double 	DOUBLE 	= format((double)7.10524632318153195520e20);
			
			os << signature << '\n' << version << '\n';
			os.write(CHAR, sizeof CHAR);			os << '\n';
			os.write((char*)&SHORT, sizeof SHORT );	os << '\n';
			os.write((char*)&LONG,  sizeof LONG  );	os << '\n';
			os.write((char*)&FLOAT, sizeof FLOAT );	os << '\n';
			os.write((char*)&DOUBLE,sizeof DOUBLE);	os << '\n';
		}
	
		void write_stubinfo(std::ostream &os)
		{
			os << "STUBINFORMATION\n" << stubinfo << "ENDSTUBINFORMATION\n";
		}
	
		void write_filemap(std::ostream &os)
		{
			REP(i,fields.size()) os << fields[i] << '\n';
			os.put(0);
		}
	
		void add_field(const std::string &name, AbstractType *type, const std::string &tag)
		{
			fields.push_back(Field(name,type,byte_length(),tag));
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
		std::string stubinfo;
	
	private:
	
		struct Field
		{
			Field(const std::string &n, AbstractType *t, int p, const std::string &tg) :
				name(n), type(t), byte_pos(p), tag(tg) {}
			std::string name,tag; AbstractType *type; int byte_pos;
			
			friend std::ostream & operator<<(std::ostream &os, Field &f)
			{
				os << f.name << " " << f.type->token << " " << f.byte_pos << " " << f.byte_pos+f.type->size()-1 << f.tag;
				return os;
			}
		};
	
		std::vector<Field> fields;
};

