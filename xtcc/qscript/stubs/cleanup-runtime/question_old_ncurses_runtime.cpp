

void Print_DisplayDataUnitVector(WINDOW * stub_list_window,
		vector<display_data::DisplayDataUnit> & disp_vec,
		int &xPos, int &yPos, int maxWinX)
{
	using display_data::DisplayDataUnit;
	for (vector<DisplayDataUnit>::iterator it = disp_vec.begin();
				it != disp_vec.end(); ++it)
	{
		//cout << *it << endl;
		stringstream s;

		if ( (*it).displayDataType_ == display_data::single_element) {
			s << (*it).startOfRangeOrSingle_ << ",";
		} else if ( (*it).displayDataType_ == display_data::range_element) {
			s << (*it).startOfRangeOrSingle_ << " - " << (*it).endOfRange_ << endl;
		}
		if (xPos + s.str().length() > maxWinX) {
			xPos =1, ++yPos;
		}
		mvwprintw(stub_list_window, yPos, xPos, "%s", s.str().c_str());
		xPos += s.str().length() + 1;
	}
}


void NamedStubQuestion::DisplayStubsPage(/*qs_ncurses::*/WINDOW * question_window
			     , /*qs_ncurses::*/WINDOW* stub_list_window
			     , /*qs_ncurses::*/WINDOW* data_entry_window
			     , WINDOW * error_msg_window)
{
	//fstream file_display_stubs_log("file_display_stubs.log", ios_base::out|ios_base::app);

	int32_t currXpos = 1, currYpos = stubStartYIndex_;

	int32_t maxWinX, maxWinY;
	getmaxyx(data_entry_window, maxWinY, maxWinX);
	vector<stub_pair> & vec= (nr_ptr->stubs);
	//wclear(stub_list_window);
	//for (int i=stubStartYIndex_; i < maxWinY; ++i) {
	//	for (int j = 1; j < maxWinX -1; ++j) {
	//		mvwaddch(stub_list_window, currYpos, currXpos , ' ');
	//	}
	//}
	//update_panels ();
	//doupdate ();
	for (int y = currYpos; y < maxWinY; ++y) {
		for (int x=1; x < maxWinX-1; ++x) {
			//mvwprintw (stub_list_window, y, x, " ");
			//cout << "reached here\n";
			mvwaddch(stub_list_window, y, x , ' ');
		}
	}
	//wmove(data_entry_window, 1, 1);
	update_panels ();
	doupdate ();
	//file_display_stubs_log << "currentPage_: " << currentPage_ << endl;
	for (uint32_t i = pageIndices_[currentPage_].first; i <= pageIndices_[currentPage_].second; ++i) {
		if (vec[i].mask) {
			//file_display_stubs_log << vec[i].stub_text << ": " << vec[i].code << endl;
			//mvwprintw(stub_list_window, currYpos, currXpos, "%s: %d ", vec[i].stub_text.c_str(), vec[i].code);
			set<int32_t>::iterator found = input_data.find(vec[i].code);
			if (found != input_data.end()) {
				wattroff(stub_list_window, COLOR_PAIR(3));
				wattron(stub_list_window, COLOR_PAIR(5));
				mvwprintw(stub_list_window, currYpos, currXpos , "%03d :", vec[i].code);
				wattroff(stub_list_window, COLOR_PAIR(5));
				wattron(stub_list_window, COLOR_PAIR(3));
			} else {
				mvwprintw(stub_list_window, currYpos, currXpos , "%03d :", vec[i].code);
			}
			mvwprintw(stub_list_window, currYpos, currXpos + 8, "%s", vec[i].stub_text.c_str());
			++currYpos;
			// this should not be necessary - the paging algo should already have calculated this
			//if (currYpos >= maxWinY) {
			//	break;
			//}
		}
	}
	if (currYpos < maxWinY) {
		char space = ' ';
		for (int y = currYpos; y < maxWinY; ++y) {
			for (int x = 1; x < maxWinX; ++x) {
				mvwaddch (stub_list_window, y, x, ' ');
				//cout << "reached here\n";
			}
		}
	}
	update_panels ();
	doupdate ();
	wmove(data_entry_window, 1, 1);
	update_panels ();
	doupdate ();
}

