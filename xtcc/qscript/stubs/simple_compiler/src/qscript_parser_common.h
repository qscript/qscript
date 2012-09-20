#ifndef QSCRIPT_PARSER_COMMON_H
#define QSCRIPT_PARSER_COMMON_H
#include <sys/types.h>
#include <map>
#include <string>
#include "TempNameGenerator.h"

namespace qscript_parser {
	extern int32_t line_no;
	extern int32_t no_errors;
	extern int32_t no_warnings;
	extern std::map<std::pair<int, int>, std::string > maintainer_messages;
	extern TempNameGenerator temp_set_name_generator;
	extern TempNameGenerator temp_name_generator;
}

#endif /* QSCRIPT_PARSER_COMMON_H */
