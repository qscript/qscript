#include <string>
namespace config_file_parser {
	using std::string;
	int line_no;
	int no_errors;

	string NCURSES_INCLUDE_DIR,
	       NCURSES_LIB_DIR,
	       NCURSES_LINK_LIBRARY_NAME,
	       PLATFORM;
}
