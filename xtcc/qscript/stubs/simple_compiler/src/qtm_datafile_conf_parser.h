#include <sys/types.h>
#include <string>

namespace qtm_datafile_conf_parser_ns {
	extern int32_t ser_start, ser_end;
	extern int32_t crd_start, crd_end;

	extern int32_t line_no;
	extern int32_t no_errors;

	int32_t load_config_file(std::string jno);
}
