#include "log_mesg.h"
#include <sstream>

using std::string;

string log_message(int line, string file, string func_name, string mesg)
{
	std::stringstream s;
	s 	<< "line: " << line 
		<< ", file: " << file 
		<< ", func: " << func_name << mesg;
	return s.str();
}
