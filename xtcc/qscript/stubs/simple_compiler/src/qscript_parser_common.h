#ifndef QSCRIPT_PARSER_COMMON_H
#define QSCRIPT_PARSER_COMMON_H
#include <sys/types.h>
#include <map>
#include <string>

namespace qscript_parser {
	extern int32_t line_no;
	extern int32_t no_errors;
	extern std::map<std::pair<int, int>, std::string > maintainer_messages;
}

#endif /* QSCRIPT_PARSER_COMMON_H */
