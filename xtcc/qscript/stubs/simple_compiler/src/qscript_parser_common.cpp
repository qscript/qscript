#include "qscript_parser_common.h"
#include <map>

namespace qscript_parser {
	int32_t line_no;
	int32_t no_errors;
	std::map<std::pair<int, int>, std::string > maintainer_messages;
}
