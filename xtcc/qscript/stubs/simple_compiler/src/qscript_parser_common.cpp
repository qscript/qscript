#include "qscript_parser_common.h"
#include <map>

namespace qscript_parser {
	int32_t line_no = 1;
	int32_t no_errors;
	int32_t no_warnings;
	std::map<std::pair<int, int>, std::string > maintainer_messages;
	TempNameGenerator temp_set_name_generator("qscript_temp_xtcc_set_");
	TempNameGenerator temp_name_generator("qscript_temp_");
}
