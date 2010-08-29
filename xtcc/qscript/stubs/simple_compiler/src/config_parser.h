#include <sys/types.h>
#include <string>
namespace config_file_parser 
{
	using std::string;
	extern int32_t line_no;
	extern int32_t no_errors;

	extern string NCURSES_INCLUDE_DIR,
	       NCURSES_LIB_DIR,
	       NCURSES_LINK_LIBRARY_NAME,
	       PLATFORM;
}
