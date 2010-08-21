#include <string>
namespace config_file_parser 
{
	using std::string;
	extern int line_no;
	extern int no_errors;

	extern string NCURSES_INCLUDE_DIR,
	       NCURSES_LIB_DIR,
	       NCURSES_LINK_LIBRARY_NAME,
	       PLATFORM;
}
