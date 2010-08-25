#include "qscript_readline.h"
#include <cctype>
#include <cstring>
#include <string>

using std::string;

NCursesReadline::NCursesReadline(WINDOW * l_data_entry_window)
	: insertionPoint_(0) //, lastBufPointer_(0)
	 , dataEntryWindow_(l_data_entry_window)
{ buffer_.reserve(4095); }

const char * NCursesReadline::ReadLine()
{
	wmove(dataEntryWindow_, 1, 1); 
	mvwprintw(dataEntryWindow_,1,1, "%s", buffer_.c_str());
	//mvwprintw(dataEntryWindow_, 2,1, "buffer_: %s\n", buffer);
	mvwprintw(dataEntryWindow_, 3, 41, "insertionPoint_: %d, lastBufPointer_: %d\n"
			, insertionPoint_, buffer_.length());
	//mvwprintw(dataEntryWindow_, 3,1, "%s" , prompt);
	wmove(dataEntryWindow_, 1, insertionPoint_);
	wrefresh(dataEntryWindow_);
	int curX, curY;
	while(1){
		//c=mvwgetch(dataEntryWindow_,1,1);
		int c=wgetch(dataEntryWindow_);
		//mvprintw(0,0, "got char: %d\n", c);
		getyx(dataEntryWindow_, curY, curX);

		if(isprint(c)){
			char ch=static_cast<char>(c);
			if(insertionPoint_==buffer_.length()){
				buffer_.append(1, ch);
				++insertionPoint_;
			} else {
				buffer_.insert(insertionPoint_++, 1, ch);
			}

		} else switch(c) {
			case 10:
			case 13:
			case KEY_ENTER:
				return buffer_.c_str();
			case KEY_LEFT:
				mvwprintw(dataEntryWindow_,2,50, "got KEY_LEFT" );
				if(insertionPoint_>0){
					--insertionPoint_;
				}
			break;
			case KEY_RIGHT:
				if(insertionPoint_<buffer_.length()){
					++insertionPoint_;
				}
			break;
			case KEY_HOME:
				insertionPoint_=0;
			break;
			case KEY_END:
				insertionPoint_=buffer_.length();
			break;
			case KEY_BACKSPACE:
				DoBackSpace();
			break;
			case KEY_DC:
				mvwprintw(dataEntryWindow_,2,50, "got KEY_DC" );
				DoDelete();
			break;
				
			//case KEY_SLEFT:
			//	do_shiftleft();
			//break;
			default:
				//mvprintw(0,0, "unknown key: %d\n", c );
				mvwprintw(dataEntryWindow_,2,50, "got KEY %d", c );
			break;
		}
		//mvwprintw(dataEntryWindow_, 2,1, "buffer_: %s\n", buffer_);
		mvwprintw(dataEntryWindow_, 3,1, "insertionPoint_: %d, lastBufPointer_: %d\n"
				, insertionPoint_, buffer_.length());
		//for(int i=lastBufPointer_-1; i<lastBufPointer_+10; ++i){
		//	mvwaddch(dataEntryWindow_, curY, i,  ' ');
		//}
		//wclear(dataEntryWindow_);
		EraseLine(curY);
		box(dataEntryWindow_, 0, 0);
		mvwprintw(dataEntryWindow_,1,1, "%s", buffer_.c_str());
		mvwprintw(dataEntryWindow_,2,50, "got KEY %d", c );
		wmove(dataEntryWindow_, curY, 1+insertionPoint_);// since our X origin is at 1
		wrefresh(dataEntryWindow_);
	}
}

void NCursesReadline::EraseLine(int line_no)
{
	int maxX, maxY;
	getmaxyx(dataEntryWindow_, maxY,maxX);
	if(line_no >=0 && line_no <= maxY){
		for(int i=0; i<buffer_.length()+10; ++i){
			mvwaddch(dataEntryWindow_, line_no, i,  ' ');
		}
	}
}

// returns 1 on success 0 on failure
// are throwing exceptions a better option?
int NCursesReadline::SetBuffer(const string & re_arranged_buffer
		, int l_new_insertionPoint)
{
	buffer_=re_arranged_buffer;

	if(l_new_insertionPoint < re_arranged_buffer.length()){
		insertionPoint_ = l_new_insertionPoint;
	} else { insertionPoint_ =0; }
}

void NCursesReadline::Reset()
{
	insertionPoint_=0;
	buffer_.clear();
}

void NCursesReadline::DoDelete()
{

	if(insertionPoint_==buffer_.length()) {
		// nothing to do
	} else if(insertionPoint_>=0){
		buffer_.erase(insertionPoint_, 1); 
	}
}

void NCursesReadline::DoBackSpace()
{
	if(insertionPoint_>=1){
		buffer_.erase(insertionPoint_-1, 1);
		--insertionPoint_;
	}
}
