/*
 * =====================================================================================
 *
 *       Filename:  question_ncurses_runtime.C
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 08 February 2013 08:14:53  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Neil Xavier D'Souza
 *        Company:  
 *
 * =====================================================================================
 */

#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "question_ncurses_runtime.h"
#include "question.h"
#include "named_range.h"
#include "user_navigation.h"


using std::vector;

WINDOW  * question_window = 0,
	* stub_list_window = 0,
	* data_entry_window = 0,
	* error_msg_window = 0,
	* help_window = 0;
PANEL   * question_panel = 0,
	* stub_list_panel = 0,
	* data_entry_panel = 0,
	* help_panel = 0,
	* error_msg_panel = 0;

void ClearPreviousView (WINDOW * question_window, WINDOW * stub_list_window, WINDOW * data_entry_window);
vector<string> PrepareQuestionText (AbstractQuestion *q);
void DisplayQuestionTextView (const vector <string> & qno_and_qtxt);

void DisplayStubs (AbstractQuestion *q);
void PrepareStubs (AbstractQuestion *q);

WINDOW *create_newwin(int32_t height, int32_t width, int32_t starty, int32_t startx);
/* 
void SetupNCurses(WINDOW * &  question_window,
			WINDOW * &  stub_list_window,
			WINDOW * & data_entry_window,
			WINDOW * & help_window,
			PANEL * &  question_panel,
			PANEL * &  stub_list_panel,
			PANEL * & data_entry_panel,
			PANEL * & help_panel)
{
	initscr();
	cbreak();
	nonl();
	intrflush(stdscr, FALSE);
	if(has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	chtype space = ' '; init_pair(1, COLOR_RED, COLOR_WHITE);
	init_pair(2, COLOR_GREEN, COLOR_WHITE);
	init_pair(3, COLOR_BLUE, COLOR_WHITE);
	init_pair(4, COLOR_MAGENTA, COLOR_CYAN);
	init_pair(5, COLOR_WHITE, COLOR_RED);
	int32_t maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);

	int32_t DATA_ENTRY_WINDOW_HEIGHT=5, DATA_ENTRY_WINDOW_WIDTH=maxX;

	int32_t starty = maxY-DATA_ENTRY_WINDOW_HEIGHT;
	int32_t startx = 0;
	data_entry_window = create_newwin(DATA_ENTRY_WINDOW_HEIGHT
		, DATA_ENTRY_WINDOW_WIDTH, starty, startx);
	wcolor_set(data_entry_window, COLOR_PAIR(1), 0);
	wattron(data_entry_window, COLOR_PAIR(1));
	wbkgd(data_entry_window, space | COLOR_PAIR(1));
	wattrset(data_entry_window, COLOR_PAIR(1));
	keypad(data_entry_window, TRUE);
	// Divide the rest of the screen between the question window
	//  and the stub window in the ration 1:2
	int32_t height_left = maxY - DATA_ENTRY_WINDOW_HEIGHT;
	int32_t STUB_LIST_WINDOW_HEIGHT=(height_left / 3)*2, STUB_LIST_WINDOW_WIDTH=maxX;
	starty = maxY - DATA_ENTRY_WINDOW_HEIGHT - STUB_LIST_WINDOW_HEIGHT;
	stub_list_window = create_newwin(STUB_LIST_WINDOW_HEIGHT
		, STUB_LIST_WINDOW_WIDTH, starty, startx);
	wcolor_set(stub_list_window, 2, 0);
	wbkgd(stub_list_window, space | COLOR_PAIR(2));
	wattron(stub_list_window, COLOR_PAIR(2));

	int32_t QUESTION_WINDOW_HEIGHT=(height_left%3) + (height_left/3), QUESTION_WINDOW_WIDTH=maxX;
	starty = 0;
	question_window = create_newwin(QUESTION_WINDOW_HEIGHT
		, QUESTION_WINDOW_WIDTH, starty, startx);
	wbkgd(question_window, space | COLOR_PAIR(3));
	wcolor_set(question_window, 3, 0);
	wattron(question_window, COLOR_PAIR(3));

	wmove(data_entry_window, 1,1);
	define_some_pd_curses_keys();
	int32_t HELP_WINDOW_HEIGHT=(int)((float)(2/3)*maxY), HELP_WINDOW_WIDTH=maxX/2;

	starty = 5;
	startx = 5;
	//help_window = create_newwin(HELP_WINDOW_HEIGHT, HELP_WINDOW_WIDTH, starty, startx);
	question_panel = new_panel(question_window);
	stub_list_panel = new_panel(stub_list_window);
	data_entry_panel = new_panel(data_entry_window);
	//help_panel = new_panel(help_window);
	update_panels();
	doupdate();
}
*/


void SetupNCurses( 	WINDOW * &  question_window,
			WINDOW * &  stub_list_window,
			WINDOW * & data_entry_window,
			WINDOW * & error_msg_window,
			WINDOW * & help_window,
			PANEL * &  question_panel,
			PANEL * &  stub_list_panel,
			PANEL * & data_entry_panel,
			PANEL * & error_msg_panel,
			PANEL * & help_panel)
{
	initscr();
	cbreak();
	nonl();
	intrflush(stdscr, FALSE);
	if(has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	chtype space = ' '; init_pair(1, COLOR_RED, COLOR_WHITE);
	init_pair(2, COLOR_GREEN, COLOR_WHITE);
	init_pair(3, COLOR_BLUE, COLOR_WHITE);
	init_pair(4, COLOR_MAGENTA, COLOR_CYAN);
	init_pair(5, COLOR_WHITE, COLOR_RED);
	int32_t maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);

	int32_t DATA_ENTRY_WINDOW_HEIGHT=5, DATA_ENTRY_WINDOW_WIDTH=maxX;

	int32_t starty = maxY-DATA_ENTRY_WINDOW_HEIGHT;
	int32_t startx = 0;
	data_entry_window = create_newwin(DATA_ENTRY_WINDOW_HEIGHT
		, DATA_ENTRY_WINDOW_WIDTH, starty, startx);
	wcolor_set(data_entry_window, COLOR_PAIR(1), 0);
	wattron(data_entry_window, COLOR_PAIR(1));
	wbkgd(data_entry_window, space | COLOR_PAIR(1));
	wattrset(data_entry_window, COLOR_PAIR(1));
	wmove(data_entry_window, 1, 1);
	keypad(data_entry_window, TRUE);
	// Divide the rest of the screen between the question window
	//  and the stub window in the ration 1:2
	int32_t height_left = maxY - DATA_ENTRY_WINDOW_HEIGHT;
	int32_t STUB_LIST_WINDOW_HEIGHT=(height_left / 3)*2, STUB_LIST_WINDOW_WIDTH=maxX;
	starty = maxY - DATA_ENTRY_WINDOW_HEIGHT - STUB_LIST_WINDOW_HEIGHT;
	stub_list_window = create_newwin(STUB_LIST_WINDOW_HEIGHT
		, STUB_LIST_WINDOW_WIDTH, starty, startx);
	wcolor_set(stub_list_window, 2, 0);
	wbkgd(stub_list_window, space | COLOR_PAIR(2));
	wattron(stub_list_window, COLOR_PAIR(2));

	int32_t ERROR_WINDOW_HEIGHT= (height_left/6), ERROR_WINDOW_WIDTH=maxX;
	starty = maxY - DATA_ENTRY_WINDOW_HEIGHT - STUB_LIST_WINDOW_HEIGHT - ERROR_WINDOW_HEIGHT;
	error_msg_window = create_newwin(ERROR_WINDOW_HEIGHT
		, ERROR_WINDOW_WIDTH, starty, startx);
	wbkgd(error_msg_window, space | COLOR_PAIR(5));
	wcolor_set(error_msg_window, 3, 0);
	wattron(error_msg_window, COLOR_PAIR(5));
	height_left -= ERROR_WINDOW_HEIGHT;
	int32_t QUESTION_WINDOW_HEIGHT=maxY - DATA_ENTRY_WINDOW_HEIGHT - STUB_LIST_WINDOW_HEIGHT - ERROR_WINDOW_HEIGHT, QUESTION_WINDOW_WIDTH=maxX;
	starty = 0;
	question_window = create_newwin(QUESTION_WINDOW_HEIGHT
		, QUESTION_WINDOW_WIDTH, starty, startx);
	wbkgd(question_window, space | COLOR_PAIR(3));
	wcolor_set(question_window, 3, 0);
	wattron(question_window, COLOR_PAIR(3));

	define_some_pd_curses_keys();
	int32_t HELP_WINDOW_HEIGHT=(int)((float)(2/3)*maxY), HELP_WINDOW_WIDTH=maxX/2;

	starty = 5;
	startx = 5;
	//help_window = create_newwin(HELP_WINDOW_HEIGHT, HELP_WINDOW_WIDTH, starty, startx);
	question_panel = new_panel(question_window);
	stub_list_panel = new_panel(stub_list_window);
	data_entry_panel = new_panel(data_entry_window);
	//help_panel = new_panel(help_window);
	error_msg_panel = new_panel(error_msg_window);
	update_panels();
	doupdate();
}



WINDOW *create_newwin(int32_t height, int32_t width, int32_t starty, int32_t startx)
{
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);
	/* 0, 0 gives default characters
	 * for the vertical and horizontal
	 * lines                        */

	return local_win;
}


void define_some_pd_curses_keys()
{
	using std::string;
	string ctrl_left_arrow;
	ctrl_left_arrow.append(1, 27);
	ctrl_left_arrow.append(1, 91);
	ctrl_left_arrow.append(1, 49);
	ctrl_left_arrow.append(1, 59);
	ctrl_left_arrow.append(1, 53);
	ctrl_left_arrow.append(1, 68);

	string ctrl_right_arrow;
	ctrl_right_arrow.append(1, 27);
	ctrl_right_arrow.append(1, 91);
	ctrl_right_arrow.append(1, 49);
	ctrl_right_arrow.append(1, 59);
	ctrl_right_arrow.append(1, 53);
	ctrl_right_arrow.append(1, 67);
	string ctl_del;
	ctl_del.append(1, 27);
	ctl_del.append(1, 91);
	ctl_del.append(1, 51);
	ctl_del.append(1, 59);
	ctl_del.append(1, 53);
	ctl_del.append(1, 126);
	string alt_del;
	alt_del.append(1, 27);
	alt_del.append(1, 91);
	alt_del.append(1, 51);
	alt_del.append(1, 59);
	alt_del.append(1, 51);
	alt_del.append(1, 126);

	string shift_del;
	shift_del.append(1, 27);
	shift_del.append(1, 91);
	shift_del.append(1, 51);
	shift_del.append(1, 59);
	shift_del.append(1, 50);
	shift_del.append(1, 126);
	define_key(ctrl_left_arrow.c_str(), CTL_LEFT);
	define_key(ctrl_right_arrow.c_str(), CTL_RIGHT);
	define_key(ctl_del.c_str(), CTL_DEL);
	define_key(alt_del.c_str(), ALT_DEL);
	define_key(shift_del.c_str(), SHF_DC);
}

void GetDataFromUser (AbstractQuestion * q)
{
	//user_response::UserResponseType user_resp = AbstractQuestion::GetDataFromUser(question_window, stub_list_window, data_entry_window);
	user_response::UserResponseType user_resp = q->GetDataFromUser(question_window, stub_list_window, data_entry_window);
}

void ncurses_eval (AbstractQuestion * q)
{
	//q->eval(question_window, stub_list_window, data_entry_window);
	ClearPreviousView (question_window, stub_list_window, data_entry_window);

	vector <string> qno_and_qtxt = PrepareQuestionText (q);

	DisplayQuestionTextView (qno_and_qtxt);
	PrepareStubs (q);
	DisplayStubs (q);
	wmove (data_entry_window, 1, 1);
	//wrefresh (data_entry_window);
	update_panels();
	doupdate();

	GetDataFromUser (q);

}


void ClearPreviousView (WINDOW * question_window, WINDOW * stub_list_window, WINDOW * data_entry_window)
{
	wclear(question_window);
	box(question_window, 0, 0);
	wclear(stub_list_window);
	box(stub_list_window, 0, 0);
	wclear(data_entry_window);
	box(data_entry_window, 0, 0);
}

vector<string> PrepareQuestionText (AbstractQuestion *q)
{
	using std::string;
	using std::stringstream;
	vector <string> result;
	stringstream question_no;
	//mvwprintw(question_window, 1, 1, "%s.", questionName_.c_str());
	question_no << q->questionName_;
	//int len_qno = questionName_.length()+2;
	if (q->loop_index_values.size() > 0) {
		for (uint32_t i = 0; i < q->loop_index_values.size(); ++i) {
			//cout << loop_index_values[i]+1 << ".";
			//mvwprintw(question_window, 1, len_qno, "%d.", loop_index_values[i]+1);
			//if (loop_index_values[i]+1<10) {
			//	len_qno += 1;
			//} else if (loop_index_values[i]+1<100) {
			//	len_qno += 2;
			//} else if (loop_index_values[i]+1<1000) {
			//	len_qno += 3;
			//} else if (loop_index_values[i]+1<10000) {
			//	len_qno += 4;
			//}
			//len_qno += 1; // for the "."
			question_no << q->loop_index_values[i] << ".";
		}
	}
	result.push_back (question_no.str());
		//mvwprintw(question_window,1,1, "%s. %s", questionName_.c_str(), questionText_.c_str() );
		//wrefresh(question_window);
		//mvwprintw(question_window, 1, len_qno+1, " %s", questionText_.c_str() );
	//mvwprintw(question_window, 1, len_qno+1, " %s", textExprVec_[0]->text_.c_str() );
	stringstream question_text;
	question_text << q->textExprVec_[0]->text_;
	result.push_back (question_text.str());
	for (int i=1; i<q->textExprVec_.size(); ++i) {
		//mvwprintw(question_window, 2+i, 1, " %s", textExprVec_[i]->text_.c_str() );
		result.push_back (q->textExprVec_[i]->text_);
	}
	return result;
	
}

// assumption
// 0 -> question no
// 1 -> question text
// 2 -> other question texts (could be created by chaining for example) ":"
void DisplayQuestionTextView (const vector <string> & qno_and_qtxt)
{
	if (qno_and_qtxt.size() > 1) {
		mvwprintw (question_window, 1, 1, "%s.%s", (qno_and_qtxt[0]).c_str(), (qno_and_qtxt[1]).c_str());
		for (int i = 2; i < qno_and_qtxt.size(); ++i) {
			mvwprintw (question_window, 2+i, 1, "%s", qno_and_qtxt[i].c_str());
		}
	}
	update_panels();
	doupdate();
}

void PrepareStubs (AbstractQuestion *q)
{
	NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*> (q) ;
	RangeQuestion * rq = dynamic_cast<RangeQuestion*> (q) ;
	if (nq) {
		if (nq->displayData_.begin() == nq->displayData_.end()) {
			nq->MakeDisplaySummaryDataRanges();
		}
	} else {
		rq->MakeDisplaySummaryDataRanges();
	}
}

void DisplayStubs (AbstractQuestion *q)
{
	int32_t maxWinX, maxWinY;
	getmaxyx(data_entry_window, maxWinY, maxWinX);
	int32_t currXpos = 1, currYpos = 1;

	NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*> (q) ;
	RangeQuestion * rq = dynamic_cast<RangeQuestion*> (q) ;
	if (nq) {
		Print_DisplayDataUnitVector (stub_list_window, nq->displayData_, currXpos, currYpos, maxWinX);
		++currYpos; currXpos = 1;

		vector<stub_pair> & vec= (nq->nr_ptr->stubs);
		nq->stubStartYIndex_ = currYpos;
		nq->ComputeVisiblePages (question_window, stub_list_window,
					data_entry_window, error_msg_window);
		nq->DisplayStubsPage( question_window
			     ,  stub_list_window
			     ,  data_entry_window
			     ,  error_msg_window);


	} else {
		Print_DisplayDataUnitVector (stub_list_window, rq->displayData_, currXpos, currYpos, maxWinX);
	}
	/* 
	if (NamedS
	++currYpos; currXpos = 1;

		//vector<stub_pair> & vec= *stub_ptr;
		vector<stub_pair> & vec= (nr_ptr->stubs);
		for(uint32_t i = 0; i< vec.size(); ++i){
			if( vec[i].mask) {
				//cout << vec[i].stub_text << ": " << vec[i].code << endl;
				//mvwprintw(stub_list_window, currYpos, currXpos, "%s: %d ", vec[i].stub_text.c_str(), vec[i].code);
				mvwprintw(stub_list_window, currYpos, currXpos, "%s: ", vec[i].stub_text.c_str());
				set<int32_t>::iterator found= input_data.find(vec[i].code);
				if (found != input_data.end() ){
					wattroff(stub_list_window, COLOR_PAIR(2));
					wattron(stub_list_window, COLOR_PAIR(4));
					mvwprintw(stub_list_window, currYpos, currXpos + vec[i].stub_text.length() + 3, "%d ", vec[i].code);
					wattroff(stub_list_window, COLOR_PAIR(4));
					wattron(stub_list_window, COLOR_PAIR(2));
				} else {
					mvwprintw(stub_list_window, currYpos, currXpos + vec[i].stub_text.length() + 3, "%d ", vec[i].code);
				}
				++currYpos;
			}
		}

		//wrefresh(stub_list_window);
		update_panels();
		doupdate();
		*/


	update_panels();
	doupdate();
}

void setup_ui ()
{
	SetupNCurses ( 	question_window, stub_list_window,
			data_entry_window, error_msg_window,
			help_window, 
			question_panel, stub_list_panel,
			data_entry_panel, error_msg_panel,
			help_panel);
	if(question_window == 0 || stub_list_window == 0 || data_entry_window == 0
		/* || help_window == 0 */
		)
	{
		using std::cerr;
		using std::endl;
		cerr << "Unable to create windows ... exiting" << endl;
		exit(1);
	}
}

int32_t prompt_user_for_serial_no()
{
	wclear(data_entry_window);
	mvwprintw(data_entry_window, 1, 1, "Enter Serial No (0) to exit: ");
	int32_t ser_no = -1;
	mvwscanw(data_entry_window, 1, 40, "%d", & ser_no);
	return ser_no;
}

char get_end_of_question_response()
{
	char end_of_question_navigation;
	label_end_of_qnre_navigation:
	wclear(data_entry_window);
	mvwprintw(data_entry_window, 1, 1,"End of Questionnaire: ((s)ave, (p)revious question, question (j)ump list)");
	mvwscanw(data_entry_window, 1, 75, "%c", & end_of_question_navigation);
	return end_of_question_navigation;
}

void print_save_partial_data_message_success ()
{
	if (data_entry_window)
		mvwprintw(data_entry_window, 2, 50, "saved partial data");
}
