#include <sys/types.h>
#include <string>
#include "qtm_data_file.h"

namespace qtm_datafile_conf_parser_ns {
	extern int32_t ser_start, ser_end;
	extern int32_t crd_start, crd_end;

	extern int32_t line_no;
	extern int32_t no_errors;

	extern int32_t load_config_file(std::string jno);
	extern bool auto_determine_data_start_col;
	extern int32_t data_start_col;
	extern int32_t data_end_col;
	extern qtm_data_file_ns::QtmFileMode qtm_file_mode;
}
