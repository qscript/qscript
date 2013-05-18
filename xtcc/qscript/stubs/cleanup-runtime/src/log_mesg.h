#ifndef QSCRIPT_LOG_MESG_H
#define QSCRIPT_LOG_MESG_H
#include <string>

std::string log_message (int line, std::string file,
			std::string func_name, std::string mesg);
#define LOG_MESSAGE(mesg)	log_message(__LINE__, __FILE__, __PRETTY_FUNCTION__, mesg)

#endif /* QSCRIPT_LOG_MESG_H */
