//Grzegorz Prusak

/*	
	structure of the text config file:

	[output machine type name]
	[output (binary) filename]
	[data files directory]
	[number of questions (qc)]
	
	[question name] [answer type] [stub tag - optional; up to the '\n']
	[question name] [answer type] [stub tag]
	[question name] [answer type] [stub tag]
	...	(qc times)
	[stubinfo section - up to the eof]
*/

#include "RecordMap.h"
#include "Format.h"
#include "Type.h"
#include <iostream>
#include <fstream>
#include <boost/filesystem/operations.hpp>

//debug mode
#define DEBUG_MODE 1
#define DEBUG(i) if((1<<i)&DEBUG_MODE)

//loops
#define REP(i,n) for(int i=0; i<(n); ++i)

//flags
#define exc_flags std::ios::failbit | std::ios::badbit

int main(int argc, char **argv)
{
	//check for config file
	if(argc<2){ std::cout << "usage: " << argv[0] << " config_file\n"; return 1; }
	
	try
	{
		//open config file
		std::ifstream conf; conf.exceptions(exc_flags); conf.open(argv[1]);
		std::string format_name,out_name,dir_name; int qc;
		conf >> format_name >> out_name >> dir_name >> qc;
		
		DEBUG(0) std::cout << "format_name='" << format_name << "'; out_name='" << out_name 
					<< "; dir_name='" << dir_name << "'; qc=" << qc << "\n"; 
		
		RecordMap rec_map(*AbstractFormat::get(format_name));
		
		//read questions' configauration
		REP(i,qc)
		{
			std::string name,type,tag; conf >> name >> type; std::getline(conf,tag);
			rec_map.add_field(name,AbstractType::get(type),tag);
		}
		
		//read raw stubinfo
		std::getline(conf,rec_map.stubinfo,'\0');
		
		//gather aswers from the data files and save answer to the output file
		std::ofstream of; of.exceptions(exc_flags); of.open(out_name.c_str());
		rec_map.write_header(of); rec_map.write_stubinfo(of); rec_map.write_filemap(of);
		for(boost::filesystem::directory_iterator it(dir_name),end; it!=end; ++it)
		{
			DEBUG(0) std::cout << "it->string()='" << it->string() << "'\n";
			std::ifstream df; df.open(it->string().c_str()); char buffer[rec_map.byte_length()];
			for(std::string name,value; df>>std::ws, std::getline(df,name,':'), df>>value;)
			{
				DEBUG(0) std::cout << "name='" << name << "' value='" << value << "'\n";
				rec_map.parse(name,value,buffer);
			}
			of.write(buffer,rec_map.byte_length());
		}
	}
	catch(std::ios::failure e){ std::cout << "IO error: " << e.what() << "\n"; }
	catch(const std::string &s){ std::cout << "error: " << s << "\n"; }
	catch(boost::filesystem::filesystem_error e){ std::cout << e.what() << "\n"; }
		
	return 0;
}

