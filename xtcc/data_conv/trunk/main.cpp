//Grzegorz Prusak

/*	
 structure of the text config file:
 
 	[output machine type name]
 	[output (binary) filename] 
 	[number of questions (qc)] [number of data files (fc)]
 	
 	[question name] [answer type]
 	[question name] [answer type]
 	[question name] [answer type] 
 	...	(qc times)
 	
 	[data file name]
	[data file name]
	[data file name]
	... (fc times)
*/

#include "RecordMap.h"
#include "Format.h"
#include "Type.h"
#include <iostream>
#include <fstream>

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
	if(argc<2){ std::cout << "usage: conv config_file\n"; return 1; }
	
	try
	{
		//open config file
		std::ifstream conf; conf.exceptions(exc_flags); conf.open(argv[1]);
		std::string format_name,out_name; int qc,fc; conf >> format_name >> out_name >> qc >> fc;
		
		DEBUG(0) std::cout << "format_name='" << format_name << "'; out_name='" << out_name 
					<< "'; qc=" << qc << "; fc=" << fc << "\n"; 
		
		RecordMap rec_map(*AbstractFormat::get(format_name));
		
		//read questions' configauration
		REP(i,qc)
		{
			std::string name,type; conf >> name >> type;
			rec_map.add_field(name+':',AbstractType::get(type));
		}
		
		//gather aswers from the data files and save answer to the output file
		std::ofstream of; of.exceptions(exc_flags); of.open(out_name.c_str());
		REP(i,fc)
		{
			std::string df_name; conf >> df_name;
			std::ifstream df; df.open(df_name.c_str()); 
		
			char buffer[rec_map.byte_length()];
			for(std::string name,value; df >> name >> value;) rec_map.parse(name,value,buffer);
			of.write(buffer,rec_map.byte_length());
		}
	}
	catch(std::ios::failure e)
	{
		std::cout << "IO error: " << e.what() << "\n";
	}
	catch(const std::string &s)
	{
		std::cout << "error: " << s << "\n";
	}
		
	return 0;
}

