#include <sys/types.h>
#include <string>
namespace config_file_parser
{
	using std::string;
	int32_t line_no;
	int32_t no_errors;

	string NCURSES_INCLUDE_DIR,
	       NCURSES_LIB_DIR,
	       NCURSES_LINK_LIBRARY_NAME,
	       PLATFORM;
}
