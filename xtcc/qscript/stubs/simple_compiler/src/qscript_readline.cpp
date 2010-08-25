#include "qscript_readline.h"
#include <cctype>
#include <cstring>
#include <string>

using std::string;

/*
char * qscript_readline(WINDOW * data_entry_window, const char * prompt
	, bool clear_buffer_flag, string & re_arranged_buffer, int &pos_1st_invalid_data)
{
	const int MAX_BUFF=1023;
	static char buffer[MAX_BUFF];
	static int insertionPoint=0;
	static int lastBufPointer=0;
	//char * buffer= new char [MAX_BUFF]; // we will die if this fails - I keep putting code like : ptr = new .. ; if(!ptr)
	// and should stop this habit as it does not work like this in the new c++ std
	wmove(data_entry_window, 1, 1); 
	if(clear_buffer_flag) {
		memset(buffer, 0, MAX_BUFF);
		insertionPoint=0;
		lastBufPointer=0;
	} else {
		strcpy(buffer, re_arranged_buffer.c_str());
		insertionPoint = pos_1st_invalid_data;
		lastBufPointer = re_arranged_buffer.length()-1;
		mvwprintw(data_entry_window,1,1, "%s", buffer);
	}
	mvwprintw(data_entry_window, 2,1, "buffer: %s\n", buffer);
	mvwprintw(data_entry_window, 3, 41, "insertionPoint: %d, lastBufPointer: %d\n"
			, insertionPoint, lastBufPointer);
	mvwprintw(data_entry_window, 3,1, "%s" , prompt);
	wmove(data_entry_window, 1, lastBufPointer);
	wrefresh(data_entry_window);
	int curX, curY;
	while(1){
		//c=mvwgetch(data_entry_window,1,1);
		int c=wgetch(data_entry_window);
		//mvprintw(0,0, "got char: %d\n", c);
		getyx(data_entry_window, curY, curX);

		if(isprint(c)){
			char ch=static_cast<char>(c);
			if(insertionPoint==lastBufPointer){
				buffer[lastBufPointer++]=ch; insertionPoint++;
			} else {
				for(int i=lastBufPointer; i>=insertionPoint; --i){
					buffer[i]=buffer[i-1];
				}
				++lastBufPointer;
				buffer[insertionPoint++]=ch;
			}

			//mvprintw(0,0, "buffer: %s\n", buffer);
			//waddch(data_entry_window, ch);
			//addch(ch);
		} else switch(c) {
			case 10:
			case 13:
			case KEY_ENTER:
				return buffer;
			case KEY_LEFT:
				if(insertionPoint>0){
					--insertionPoint;
				}
			break;
			case KEY_RIGHT:
				if(insertionPoint<lastBufPointer){
					++insertionPoint;
				}
			break;
			case KEY_HOME:
				insertionPoint=0;
			break;
			case KEY_END:
				insertionPoint=lastBufPointer;
			break;
			case KEY_BACKSPACE:
				if(insertionPoint>=1){
					for(int i=insertionPoint; i<=lastBufPointer; ++i){
						buffer[i-1]=buffer[i];
					}
					buffer[--lastBufPointer]=0; 
					--insertionPoint;
					if(insertionPoint>lastBufPointer)
						insertionPoint=lastBufPointer;
				}
			break;
			case KEY_DC:
				//mvprintw(0,0, "buffer: got KEY_DC\n" );

			break;
				
			case KEY_SLEFT:
				do_shiftleft();
			break;
			default:
				//mvprintw(0,0, "unknown key: %d\n", c );
			break;
		}
		mvwprintw(data_entry_window, 2,1, "buffer: %s\n", buffer);
		mvwprintw(data_entry_window, 3,1, "insertionPoint: %d, lastBufPointer: %d\n"
				, insertionPoint, lastBufPointer);
		for(int i=lastBufPointer-1; i<lastBufPointer+10; ++i){
			mvwaddch(data_entry_window, curY, i,  ' ');
		}
		wclear(data_entry_window);
		box(data_entry_window, 0, 0);
		mvwprintw(data_entry_window,1,1, "%s", buffer);
		wmove(data_entry_window, curY, insertionPoint+1);
		wrefresh(data_entry_window);
	}
}
*/

NCursesReadline::NCursesReadline(WINDOW * l_data_entry_window)
	: MAX_BUFF(1023), buffer_(new char[MAX_BUFF])
	 , insertionPoint_(0) , lastBufPointer_(0)
	 , dataEntryWindow_(l_data_entry_window)
{ }

char * NCursesReadline::ReadLine()
{
	wmove(dataEntryWindow_, 1, 1); 
	mvwprintw(dataEntryWindow_,1,1, "%s", buffer_);
	//mvwprintw(dataEntryWindow_, 2,1, "buffer_: %s\n", buffer);
	mvwprintw(dataEntryWindow_, 3, 41, "insertionPoint_: %d, lastBufPointer_: %d\n"
			, insertionPoint_, lastBufPointer_);
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
			if(insertionPoint_==lastBufPointer_){
				buffer_[lastBufPointer_++]=ch; insertionPoint_++;
			} else {
				for(int i=lastBufPointer_; i>=insertionPoint_; --i){
					buffer_[i]=buffer_[i-1];
				}
				++lastBufPointer_;
				buffer_[insertionPoint_++]=ch;
			}

			//mvprintw(0,0, "buffer_: %s\n", buffer);
			//waddch(dataEntryWindow_, ch);
			//addch(ch);
		} else switch(c) {
			case 10:
			case 13:
			case KEY_ENTER:
				return buffer_;
			case KEY_LEFT:
				mvwprintw(dataEntryWindow_,2,50, "got KEY_LEFT" );
				if(insertionPoint_>0){
					--insertionPoint_;
				}
			break;
			case KEY_RIGHT:
				if(insertionPoint_<lastBufPointer_){
					++insertionPoint_;
				}
			break;
			case KEY_HOME:
				insertionPoint_=0;
			break;
			case KEY_END:
				insertionPoint_=lastBufPointer_;
			break;
			case KEY_BACKSPACE:
			/*
				if(insertionPoint_>=1){
					for(int i=insertionPoint_; i<=lastBufPointer_; ++i){
						buffer_[i-1]=buffer_[i];
					}
					buffer_[--lastBufPointer_]=0; 
					--insertionPoint_;
					if(insertionPoint_>lastBufPointer_)
						insertionPoint_=lastBufPointer_;
				}
			*/
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
				, insertionPoint_, lastBufPointer_);
		for(int i=lastBufPointer_-1; i<lastBufPointer_+10; ++i){
			mvwaddch(dataEntryWindow_, curY, i,  ' ');
		}
		//wclear(dataEntryWindow_);
		box(dataEntryWindow_, 0, 0);
		mvwprintw(dataEntryWindow_,1,1, "%s", buffer_);
		mvwprintw(dataEntryWindow_,2,50, "got KEY %d", c );
		wmove(dataEntryWindow_, curY, 1+insertionPoint_);// since our X origin is at 1
		wrefresh(dataEntryWindow_);
	}
}

// returns 1 on success 0 on failure
// are throwing exceptions a better option?
int NCursesReadline::SetBuffer(const string & re_arranged_buffer
		, int l_new_insertionPoint)
{
	if(re_arranged_buffer.length() >= MAX_BUFF-1)
	{
		//cerr << " re_arranged_buffer too large for internal buffer"
		return 0;
	}
	strcpy(buffer_, re_arranged_buffer.c_str());
	if(l_new_insertionPoint < re_arranged_buffer.length()){
		insertionPoint_ = l_new_insertionPoint;
	} else { insertionPoint_ =0; }
	lastBufPointer_ = re_arranged_buffer.length();
}

void NCursesReadline::Reset()
{
	insertionPoint_=0; lastBufPointer_=0;
	memset(buffer_, 0, MAX_BUFF);
}

void NCursesReadline::DoDelete()
{

	if(insertionPoint_==lastBufPointer_) {
		// nothing to do
	} else if(insertionPoint_>=1){
		for(int i=insertionPoint_; i<=lastBufPointer_; ++i){
			buffer_[i]=buffer_[i+1];
		}
		buffer_[--lastBufPointer_]=0; 
		if(lastBufPointer_<insertionPoint_)
			lastBufPointer_=insertionPoint_;
	}
}

void NCursesReadline::DoBackSpace()
{
	if(insertionPoint_>=1){
		for(int i=insertionPoint_; i<=lastBufPointer_; ++i){
			buffer_[i-1]=buffer_[i];
		}
		buffer_[--lastBufPointer_]=0; 
		--insertionPoint_;
		if(insertionPoint_>lastBufPointer_)
			insertionPoint_=lastBufPointer_;
	}
}
