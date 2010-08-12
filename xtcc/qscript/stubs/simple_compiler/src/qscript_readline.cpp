#include "qscript_readline.h"
#include <cctype>
#include <cstring>

char * qscript_readline(WINDOW * data_entry_window, char * prompt)
{
	const int MAX_BUFF=1023;
	//char buffer[MAX_BUFF];
	char * buffer= new char [MAX_BUFF]; // we will die if this fails - I keep putting code like : ptr = new .. ; if(!ptr)
	// and should stop this habit as it does not work like this in the new c++ std
	wmove(data_entry_window, 1, 1); 
	memset(buffer, 0, MAX_BUFF);
	int curX, curY;
	int insertionPoint=0;
	int lastBufPointer=0;
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

			mvprintw(0,0, "buffer: %s\n", buffer);

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
				mvprintw(0,0, "buffer: got KEY_DC\n" );

			break;
				
			default:
				mvprintw(0,0, "unknown key: %d\n", c );
			break;
		}
		mvprintw(0,0, "buffer: %s\n", buffer);
		mvprintw(1,0, "insertionPoint: %d, lastBufPointer: %d\n"
				, insertionPoint, lastBufPointer);
		for(int i=lastBufPointer-1; i<lastBufPointer+10; ++i){
			mvwaddch(data_entry_window, curY, i,  ' ');
		}
		wclear(data_entry_window);
		mvwprintw(data_entry_window,1,1, "%s", buffer);
		wmove(data_entry_window, curY, insertionPoint+1);
		wrefresh(data_entry_window);
	}
}
