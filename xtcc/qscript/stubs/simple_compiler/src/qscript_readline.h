#ifndef QSCRIPT_READLINE_H
#define QSCRIPT_READLINE_H
#include <curses.h>
#include <string>
char * qscript_readline(WINDOW * data_entry_window, const char * prompt
	, bool clear_buffer_flag, std::string & re_arranged_buffer, int & pos_1st_invalid_data);
void read_data( const char * prompt);
void read_data_from_window(WINDOW * data_entry_window, const char * prompt
	, bool clear_buffer_flag, std::string & re_arranged_buffer, int & pos_1st_invalid_data);
#endif /* QSCRIPT_READLINE_H */
