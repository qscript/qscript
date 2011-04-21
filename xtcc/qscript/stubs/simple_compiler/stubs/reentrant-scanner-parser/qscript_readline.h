#ifndef QSCRIPT_READLINE_H
#define QSCRIPT_READLINE_H
#include <sys/types.h>
#include <curses.h>
#include <string>
#include "UserResponse.h"

class NCursesReadline
{
	//const int32_t MAX_BUFF;
	//char * buffer_;
	std::string buffer_;
	int32_t insertionPoint_;
		//, lastBufPointer_;
	WINDOW * dataEntryWindow_;
	public:
	// We expect an already allocated window to be passed to us
	NCursesReadline(WINDOW * l_data_entry_window);
	const char * ReadLine();
	void SetBuffer(const std::string & re_arranged_buffer
		       , int32_t l_new_insertionPoint);
	void DoDelete();
	void DoBackSpace();
	void DoDeleteWordForward();
	void DoDeleteWordBackWard();
	void Reset();
	void EraseLine(int32_t line_no);
	void DoShiftLeft();
	void DoShiftRight();
	private:
		NCursesReadline& operator=(const NCursesReadline&);
		NCursesReadline (const NCursesReadline&);
};


//void read_data( const char * prompt);
///void read_data_from_window(WINDOW * data_entry_window, const char * prompt
///			   , bool clear_buffer_flag
///			   , std::string & re_arranged_buffer
///			   , int32_t & pos_1st_invalid_data);

user_response::UserResponseType read_data( const char * prompt);
user_response::UserResponseType read_data_from_window(WINDOW * data_entry_window,
		const char * prompt, bool clear_buffer_flag, std::string & re_arranged_buffer,
		int & pos_1st_invalid_data);
/*
char * qscript_readline(WINDOW * data_entry_window, const char * prompt
	, bool clear_buffer_flag, std::string & re_arranged_buffer, int32_t & pos_1st_invalid_data);
*/
#endif /* QSCRIPT_READLINE_H */
