#include <sys/types.h>
#include <cctype>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include <panel.h>
#include "qscript_readline.h"
#include "user_navigation.h"
#include "UserResponse.h"
#include "question.h"
#include "named_range.h"

#define CTL_LEFT 	0x1bb
#define CTL_RIGHT 	0x1bc
#define CTL_DEL 	0x20f
#define ALT_DEL 	0x1de
#define SHF_DC 		0x21a

using std::string;
extern user_response::UserResponseType the_user_response;
extern UserNavigation user_navigation;

void do_pageup(WINDOW * questionWindow_, WINDOW * stubListWindow_, WINDOW * dataEntryWindow_, WINDOW * errorMessageWindow_, NamedStubQuestion * nq);
void do_pagedown(WINDOW * questionWindow_, WINDOW * stubListWindow_, WINDOW * dataEntryWindow_, WINDOW * errorMessageWindow_, NamedStubQuestion * nq);

NCursesReadline::NCursesReadline(WINDOW * l_question_window,
		WINDOW * l_stub_list_window,
		WINDOW * l_data_entry_window,
		WINDOW * l_error_msg_window)
	: buffer_(), insertionPoint_(0),
	  questionWindow_(l_question_window),
	  stubListWindow_(l_stub_list_window),
	  dataEntryWindow_(l_data_entry_window),
	  errorMessageWindow_(l_error_msg_window)
{ buffer_.reserve(4095); }

const char * NCursesReadline::ReadLine (AbstractQuestion * q)
{
	wmove(dataEntryWindow_, 1, 1);
	mvwprintw(dataEntryWindow_,1,1, "%s", buffer_.c_str());
	//mvwprintw(dataEntryWindow_, 2,1, "buffer_: %s\n", buffer);
	//mvwprintw(dataEntryWindow_, 3, 41, "insertionPoint_: %d, lastBufPointer_: %d\n"
	//		, insertionPoint_, buffer_.length());
	//mvwprintw(dataEntryWindow_, 3,1, "%s" , prompt);
	wmove(dataEntryWindow_, 1, insertionPoint_);
	//wrefresh(dataEntryWindow_);
	update_panels();
	doupdate();
	int32_t curX, curY;
	while(1) {
		//c = mvwgetch(dataEntryWindow_,1,1);
		int32_t c = wgetch(dataEntryWindow_);
		//mvprintw(0,0, "got char: %d\n", c);
		getyx(dataEntryWindow_, curY, curX);

		if(isascii(c) && isprint(c)){
			char ch = static_cast<char>(c);
			if(insertionPoint_ == buffer_.length()){
				buffer_.append(1, ch);
				++insertionPoint_;
			} else {
				buffer_.insert(insertionPoint_++, 1, ch);
			}
			mvwprintw(dataEntryWindow_,2,75, "got PRINTABLE CHAR %d", c);

		} else switch (c) {
			case 24:
				endwin();
				std::cout << "exited without saving changes.\n";
				exit(1);
			case 10:
			case 13:
			case 459: /* numeric keypad enter on WINDOWS PDCURSES */
			case KEY_ENTER:
				return buffer_.c_str();
			case 16: /* Ctrl P */
				the_user_response = user_response::UserEnteredNavigation;
				user_navigation = NAVIGATE_PREVIOUS;
				return buffer_.c_str();
			case 14: /* Ctrl N */
				the_user_response = user_response::UserEnteredNavigation;
				user_navigation = NAVIGATE_NEXT;
				return buffer_.c_str();
			case KEY_F(4):
				user_navigation = SAVE_DATA;
				the_user_response = user_response::UserSavedData;
				mvwprintw(dataEntryWindow_,2,50, "Save data requested");
				return buffer_.c_str();
			case 11:
				the_user_response = user_response::UserClearedData;
				user_navigation = NOT_SET;
				buffer_.clear();
				insertionPoint_ = 0;
				// return buffer_.c_str();
				break;
			case KEY_LEFT:
				mvwprintw(dataEntryWindow_,2,50, "got KEY_LEFT");
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
				insertionPoint_ = 0;
				break;
			case KEY_END:
				insertionPoint_ = buffer_.length();
				break;
			case 8: // ctrl-H (which is backspace) in pdcurses
			case SHF_DC:
			case KEY_BACKSPACE:
				DoBackSpace();
				break;
			case KEY_DC:
				mvwprintw(dataEntryWindow_,2,50, "got KEY_DC");
				DoDelete();
				break;
			case CTL_DEL:
				DoDeleteWordForward();
				break;
			case ALT_DEL:
				DoDeleteWordBackWard();
				break;
			case CTL_LEFT:
			case KEY_SLEFT:
				DoShiftLeft();
				break;
			case CTL_RIGHT:
			case KEY_SRIGHT:
				DoShiftRight();
				break;
			case 457:
			case KEY_NPAGE:
				mvwprintw(dataEntryWindow_,2,50, "got KEY_NPAGE");
				if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q)) {
					do_pagedown(questionWindow_, stubListWindow_, dataEntryWindow_, errorMessageWindow_, nq);
				}
				break;
			case 451:
			case KEY_PPAGE:
				mvwprintw(dataEntryWindow_,2,50, "got KEY_PPAGE");
				if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q)) {
					do_pageup(questionWindow_, stubListWindow_, dataEntryWindow_, errorMessageWindow_, nq);
				}
				break;
			case 0x1d1:
				mvwprintw(dataEntryWindow_,2,50, "got PADPLUS");
				if(insertionPoint_ == buffer_.length()){
					buffer_.append(1, ' ');
					++insertionPoint_;
				} else {
					buffer_.insert(insertionPoint_++, 1, ' ');
				}
				break;
			default:
				//mvprintw(0,0, "unknown key: %d\n", c);
				mvwprintw(dataEntryWindow_,2,50, "got KEY %d", c);
				break;
			}
		//mvwprintw(dataEntryWindow_, 2,1, "buffer_: %s\n", buffer_);
		//mvwprintw(dataEntryWindow_, 3,1, "insertionPoint_: %d, lastBufPointer_: %d\n"
		//		, insertionPoint_, buffer_.length());
		//for(int32_t i = lastBufPointer_-1; i < lastBufPointer_+10; ++i){
		//	mvwaddch(dataEntryWindow_, curY, i,  ' ');
		//}
		//wclear(dataEntryWindow_);
		EraseLine(curY);
		box(dataEntryWindow_, 0, 0);
		mvwprintw(dataEntryWindow_,1,1, "%s", buffer_.c_str());
		//mvwprintw(dataEntryWindow_,2,50, "got KEY %d", c);
		wmove(dataEntryWindow_, curY, 1+insertionPoint_);// since our X origin is at 1
		//wrefresh(dataEntryWindow_);
		update_panels();
		doupdate();
	}
}

void NCursesReadline::EraseLine(int32_t line_no)
{
	int32_t maxX, maxY;
	getmaxyx(dataEntryWindow_, maxY,maxX);
	if(line_no  >= 0 && line_no  <=  maxY){
		for(int32_t i = 0; i < /*buffer_.length()+10*/ maxX ; ++i){
			mvwaddch(dataEntryWindow_, line_no, i,  ' ');
		}
	}
}

void NCursesReadline::SetBuffer(const string & re_arranged_buffer
				, int32_t l_new_insertionPoint)
{
	buffer_ = re_arranged_buffer;

	if(l_new_insertionPoint < re_arranged_buffer.length()){
		insertionPoint_ = l_new_insertionPoint;
	} else { insertionPoint_ =0; }
}

void NCursesReadline::Reset()
{
	insertionPoint_ = 0;
	buffer_.clear();
}

void NCursesReadline::DoDelete()
{

	if(insertionPoint_ == buffer_.length()) {
		// nothing to do
	} else if (insertionPoint_ >= 0){
		buffer_.erase(insertionPoint_, 1);
	}
}

void NCursesReadline::DoBackSpace()
{
	if(insertionPoint_ >= 1){
		buffer_.erase(insertionPoint_-1, 1);
		--insertionPoint_;
	}
}

void NCursesReadline::DoShiftLeft()
{
	if(insertionPoint_>0){
		//string::size_type found;
		//do {
		//	found = buffer_.rfind(' ', insertionPoint_);
		//} while (found == insertionPoint_);
		int32_t i1 = insertionPoint_-1;
		int32_t idx = 0;
		int32_t count_blank_spaces = 0;
		while(buffer_[i1] == ' ' && i1>0){
			mvwprintw(dataEntryWindow_,2,90+idx, ".");
			count_blank_spaces++;
			--i1;
		}
		if(count_blank_spaces>1){
			insertionPoint_ = i1;
			return;
		}
		string::size_type found = buffer_.rfind(' ', i1);
		if(found != string::npos){
			insertionPoint_ = found;
		}
	}
}

void NCursesReadline::DoShiftRight()
{
	if(insertionPoint_<buffer_.length()){
		//string::size_type found;
		//do {
		//	found = buffer_.rfind(' ', insertionPoint_);
		//} while (found == insertionPoint_);
		int32_t i1 = insertionPoint_+1;
		int32_t idx = 0;
		int32_t count_blank_spaces = 0;
		while(buffer_[i1] == ' ' && i1>0){
			mvwprintw(dataEntryWindow_,2,90+idx, ".");
			count_blank_spaces++;
			++i1;
		}
		if(count_blank_spaces>1){
			insertionPoint_ = i1;
			return;
		}
		string::size_type found = buffer_.find(' ', i1);
		if(found != string::npos){
			insertionPoint_ = found;
		}
	}
}

void NCursesReadline::DoDeleteWordBackWard()
{
	if(insertionPoint_>0){
		//string::size_type found;
		//do {
		//	found = buffer_.rfind(' ', insertionPoint_);
		//} while (found == insertionPoint_);
		int32_t i1 = insertionPoint_-1;
		int32_t idx = 0;
		int32_t count_blank_spaces = 0;
		int32_t end_mark = insertionPoint_;
		while(buffer_[i1] == ' ' && i1>0){
			mvwprintw(dataEntryWindow_,2,90+idx, ".");
			count_blank_spaces++;
			--i1;
		}
		if(count_blank_spaces>1){
			int32_t start_mark = i1+1;
			int32_t length = end_mark - start_mark;
			buffer_.erase(start_mark, length);
			insertionPoint_ = i1;
			return;
		}
		string::size_type found = buffer_.rfind(' ', i1);
		if(found != string::npos){
			insertionPoint_ = found;
			int32_t start_mark = found;
			int32_t length = end_mark - start_mark;
			buffer_.erase(start_mark, length);
			return;
		} else {
			int32_t start_mark = 0;
			int32_t length = end_mark - start_mark;
			buffer_.erase(start_mark, length);
			insertionPoint_ = 0;
			return;
		}
	}
}

void NCursesReadline::DoDeleteWordForward()
{
	if(insertionPoint_<buffer_.length()){
		//string::size_type found;
		//do {
		//	found = buffer_.rfind(' ', insertionPoint_);
		//} while (found == insertionPoint_);
		int32_t i1 = insertionPoint_+1;
		int32_t idx = 0;
		int32_t count_blank_spaces = 0;
		int32_t start_mark = insertionPoint_;
		while(buffer_[i1] == ' ' && i1>0){
			mvwprintw(dataEntryWindow_,2,90+idx, ".");
			count_blank_spaces++;
			++i1;
		}
		if(count_blank_spaces>1){
			int32_t end_mark = i1;
			int32_t length = end_mark - start_mark;
			buffer_.erase(start_mark, length);
			// no need to updated insertionPoint_ - it remains as it was
			return;
		}
		string::size_type found = buffer_.find(' ', i1);
		if(found != string::npos){
			int32_t end_mark = found;
			int32_t length = end_mark - start_mark;
			buffer_.erase(start_mark, length);
			// no need to updated insertionPoint_ - it remains as it was
			return;
		} else {
			int32_t end_mark = buffer_.length();
			int32_t length = end_mark - start_mark;
			buffer_.erase(start_mark, length);
			// no need to updated insertionPoint_ - it remains as it was
			return;
		}
	}
}


void do_pagedown(WINDOW * questionWindow_, WINDOW * stubListWindow_, WINDOW * dataEntryWindow_, WINDOW * errorMessageWindow_, NamedStubQuestion * nq)
{
	int32_t maxWinX, maxWinY;
	getmaxyx(stubListWindow_, maxWinY, maxWinX);

#if OLD_PAGE_ALGORITHM
	int page_size = maxWinY - 3;
	if (page_size>0) {


		//vector<stub_pair> & vec= *stub_ptr;
		vector<stub_pair> & vec= (nq->nr_ptr->stubs);
		int total_pages = (vec.size() / page_size) + 1;
		int32_t currXpos = 1, currYpos = 2;
		if (total_pages > 1 && page_size < vec.size() && nq->currentPage_ < total_pages) {
			wclear(stubListWindow_);
			box(stubListWindow_, 0 , 0);
			int max_index = (nq->currentPage_+1) * page_size < vec.size() ? (nq->currentPage_+1) * page_size : vec.size();
			for(uint32_t i = (nq->currentPage_) * page_size; i< max_index; ++i) {
				if (vec[i].mask) {
					//cout << vec[i].stub_text << ": " << vec[i].code << endl;
					//mvwprintw(stub_list_window, currYpos, currXpos, "%s: %d ", vec[i].stub_text.c_str(), vec[i].code);
					mvwprintw(stubListWindow_, currYpos, currXpos, "%s: ", vec[i].stub_text.c_str());
					set<int32_t>::iterator found= nq->input_data.find(vec[i].code);
					if (found != nq->input_data.end() ){
						wattroff(stubListWindow_, COLOR_PAIR(2));
						wattron(stubListWindow_, COLOR_PAIR(4));
						mvwprintw(stubListWindow_, currYpos, currXpos + vec[i].stub_text.length() + 3, "%d ", vec[i].code);
						wattroff(stubListWindow_, COLOR_PAIR(4));
						wattron(stubListWindow_, COLOR_PAIR(2));
					} else {
						mvwprintw(stubListWindow_, currYpos, currXpos + vec[i].stub_text.length() + 3, "%d ", vec[i].code);
					}
					++currYpos;
				}
			}
			++nq->currentPage_;
		}
	}
#endif /*  OLD_PAGE_ALGORITHM */

	int page_size = maxWinY - nq->stubStartYIndex_;
	int start_y = nq->stubStartYIndex_;
	if (nq->currentPage_ + 1 < nq->pageIndices_.size()) {
		++ nq->currentPage_;
		nq->DisplayStubsPage (questionWindow_, stubListWindow_, dataEntryWindow_, errorMessageWindow_);
	}




}


void do_pageup(WINDOW * questionWindow_, WINDOW * stubListWindow_, WINDOW * dataEntryWindow_, WINDOW * errorMessageWindow_, NamedStubQuestion * nq)
{
	int32_t maxWinX, maxWinY;
	getmaxyx(stubListWindow_, maxWinY, maxWinX);
#if OLD_PAGE_ALGORITHM
	int page_size = maxWinY - 4;
	if (page_size>0) {
		//vector<stub_pair> & vec= *stub_ptr;
		vector<stub_pair> & vec= (nq->nr_ptr->stubs);
		int total_pages = (vec.size() / page_size) + 1;
		int32_t currXpos = 1, currYpos = 2;
		if (total_pages > 1 && page_size < vec.size() && nq->currentPage_ > 0) {
			wclear(stubListWindow_);
			box(stubListWindow_, 0 , 0);
			int max_index = nq->currentPage_ * page_size < vec.size() ? nq->currentPage_ * page_size : vec.size();
			for(uint32_t i = (nq->currentPage_-1) * page_size; i< max_index; ++i) {
				if( vec[i].mask) {
					//cout << vec[i].stub_text << ": " << vec[i].code << endl;
					//mvwprintw(stub_list_window, currYpos, currXpos, "%s: %d ", vec[i].stub_text.c_str(), vec[i].code);
					mvwprintw(stubListWindow_, currYpos, currXpos, "%s: ", vec[i].stub_text.c_str());
					set<int32_t>::iterator found= nq->input_data.find(vec[i].code);
					if (found != nq->input_data.end() ){
						wattroff(stubListWindow_, COLOR_PAIR(2));
						wattron(stubListWindow_, COLOR_PAIR(4));
						mvwprintw(stubListWindow_, currYpos, currXpos + vec[i].stub_text.length() + 3, "%d ", vec[i].code);
						wattroff(stubListWindow_, COLOR_PAIR(4));
						wattron(stubListWindow_, COLOR_PAIR(2));
					} else {
						mvwprintw(stubListWindow_, currYpos, currXpos + vec[i].stub_text.length() + 3, "%d ", vec[i].code);
					}
					++currYpos;
				}
			}
			--nq->currentPage_;
		}
	}
#endif /* OLD_PAGE_ALGORITHM  */

	int page_size = maxWinY - nq->stubStartYIndex_;
	int start_y = nq->stubStartYIndex_;
	if (nq->currentPage_ - 1 >= 0) {
		-- nq->currentPage_;
		nq->DisplayStubsPage (questionWindow_, stubListWindow_, dataEntryWindow_, errorMessageWindow_);
	}
}
