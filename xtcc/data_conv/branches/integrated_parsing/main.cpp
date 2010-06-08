//Grzegorz Prusak

/*
	data type size:
	
	char   : 1B
	short  : 2B
	long   : 4B
	float  : 4B
	double : 8B
*/

/*
	<string>		= *char
	<digit>			= ['0'-'9']
	<number>		= *<digit>
	
	<signature>		= "xtcc"
	<version> 		= "0.0.0.0"
	<char sample> 	= "xtcc"
	<short sample> 	= [short 0x4142]
	<long sample> 	= [long 0x43444546]
	<float sample> 	= [float 3297809.75]
	<double sample> = [double 7.10524632318153195520e20]
	<header>		= <signature> '\n' <version> '\n' <char sample> '\n' <short sample> '\n' <long sample> '\n'
					  <float sample> '\n' <double sample> '\n'
	
	<range value>	= ' ' <number> " \"" <string> '\"'
	<range name>	= <string>
	<range>			= <range name> " =" *<range value> '\n'
	<stubinfo>		= "STUBINFORMATION\n" *<range> "ENDSTUBINFORMATION\n"
	
	<type>			= "INT8" | "INT16" | "INT32" | "FLOAT" | "DOUBLE"
	<question name> = <string>
	<first byte>	= <number>
	<last byte>		= <number>
	<question>		= <question name> ' ' <type> ' ' <first byte> ' ' <last byte> '\n'
	<record map>	= *<question> '\0'
	
	<record>		= [size of record]*char
	<data>			= *<record>
	
	<output>		= <header> <stubinfo> <record map> <data> EOF
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
	if(argc<5){ std::cout << "usage: " << argv[0] << " machine_format script_file data_directory output_file\n"; return 1; }
	
	try
	{
		RecordMap rec_map(*AbstractFormat::get(argv[1]),argv[2]);
		
		//gather aswers from the data files and save answer to the output file
		std::ofstream of; of.exceptions(exc_flags); of.open(argv[4]);
		rec_map.write_header(of); rec_map.write_stubinfo(of); rec_map.write_filemap(of);
		for(boost::filesystem::directory_iterator it(argv[3]),end; it!=end; ++it)
		{
			DEBUG(0) std::cout << "it->string()='" << it->string() << "'\n";
			std::ifstream df; df.open(it->string().c_str()); char buffer[rec_map.byte_length()];
			for(std::string name,value; df>>std::ws, std::getline(df,name,':'), std::getline(df,value,'\n'), df;)
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

