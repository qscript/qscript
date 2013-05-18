

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

//void RangeQuestion::eval()
#if 0
void RangeQuestion::eval(/*qs_ncurses::*/WINDOW * question_window
			 , /*qs_ncurses::*/WINDOW* stub_list_window
			 , /*qs_ncurses::*/WINDOW* data_entry_window)
{
	if (displayData_.begin() == displayData_.end()) {
#if 0
		for(	set<int32_t>::iterator it = r_data->indiv.begin();
				it != r_data->indiv.end(); ++it){
			//displayData_.insert(*it);
			displayData_.push_back(display_data::DisplayDataUnit(*it));
		}
		for(int32_t i = 0; i < r_data->range.size(); ++i){
			/*
			for(int32_t j = r_data->range[i].first; j <= r_data->range[i].second
					;++j){
				displayData_.insert(j);
			}
			*/
			displayData_.push_back(display_data::DisplayDataUnit(r_data->range[i].first, r_data->range[i].second));
		}
		std::sort(displayData_.begin(), displayData_.end(), display_data::DisplayDataUnitOrder());
#endif /*  0 */
		MakeDisplaySummaryDataRanges();
	}
	if(question_window ==0 || stub_list_window  == 0 || data_entry_window  == 0 ){
		cout << questionName_ << ".";
		if(loop_index_values.size()>0){
			for(uint32_t i=0; i<loop_index_values.size(); ++i){
				cout << loop_index_values[i]+1 << ".";
			}
		}
		//cout << questionText_ << endl << endl;
		cout << textExprVec_[0]->text_ << endl << endl;
		//for(	set<int32_t>::iterator it = displayData_.begin();
		//		it != displayData_.end(); ++it)
		for(	vector<display_data::DisplayDataUnit>::iterator it = displayData_.begin();
				it != displayData_.end(); ++it)
		{
			//cout << *it << endl;
			if ( (*it).displayDataType_ == display_data::single_element) {
				cout << (*it).startOfRangeOrSingle_ << ", ";
			} else if ( (*it).displayDataType_ == display_data::range_element) {
				cout << (*it).startOfRangeOrSingle_ << " - " << (*it).endOfRange_ << endl;
			}
		}

		if(input_data.begin() != input_data.end()){
			cout << "Current data values: ";

			for(set<int32_t>::iterator iter = input_data.begin();
				iter != input_data.end(); ++iter){
				cout << *iter << " ";
			}
			cout << endl;
		}

		//AbstractRuntimeQuestion::GetDataFromUser(data_entry_window);
	} else {
		wclear(question_window);
		box(question_window, 0, 0);
		wclear(stub_list_window);
		box(stub_list_window, 0, 0);
		wclear(data_entry_window);
		box(data_entry_window, 0, 0);
		mvwprintw(question_window, 1, 1, "%s.", questionName_.c_str());
		int len_qno = questionName_.length()+2;
		if(loop_index_values.size()>0){
			for(uint32_t i=0; i<loop_index_values.size(); ++i){
				//cout << loop_index_values[i]+1 << ".";
				mvwprintw(question_window, 1, len_qno, "%d.", loop_index_values[i]+1);
				if (loop_index_values[i]+1<10) {
					len_qno += 1;
				} else if (loop_index_values[i]+1<100) {
					len_qno += 2;
				} else if (loop_index_values[i]+1<1000) {
					len_qno += 3;
				} else if (loop_index_values[i]+1<10000) {
					len_qno += 4;
				}
				len_qno += 1; // for the "."
			}
		}
		//mvwprintw(question_window, 1, len_qno+1, " %s", questionText_.c_str() );
		mvwprintw(question_window, 1, len_qno+1, " %s", textExprVec_[0]->text_.c_str() );
		for (int i=1; i<textExprVec_.size(); ++i) {
			mvwprintw(question_window, 2+i, 1, " %s", textExprVec_[i]->text_.c_str() );
		}
		//wrefresh(question_window);
		update_panels();
		doupdate();

		int32_t maxWinX, maxWinY;
		getmaxyx(data_entry_window, maxWinY, maxWinX);
		int32_t currXpos = 1, currYpos = 1;
#if 0
		for(	set<int32_t>::iterator it = displayData_.begin();
				it != displayData_.end(); ++it){
			stringstream s;
			s << *it;
			int32_t len = s.str().length();
			set<int32_t>::iterator found= input_data.find(*it);
			if(found != input_data.end()){
				// is an input value
				//YELLOW
					wattroff(stub_list_window, COLOR_PAIR(2));
					wattron(stub_list_window, COLOR_PAIR(4));
					mvwprintw(stub_list_window, currYpos, currXpos, "%s ", s.str().c_str());
					wattroff(stub_list_window, COLOR_PAIR(4));
					wattron(stub_list_window, COLOR_PAIR(2));
			} else {
				mvwprintw(stub_list_window, currYpos, currXpos, "%s ", s.str().c_str());
			}
			if(currXpos+len +1 /* 1 for the trailing space below */ >= maxWinX){
				currXpos = 1, ++currYpos;
			} else {
				currXpos+= len + 1;
			}
		}
#endif /* 0 */
		/*
		for (vector<display_data::DisplayDataUnit>::iterator it = displayData_.begin();
				it != displayData_.end(); ++it)
		{
			//cout << *it << endl;
			stringstream s;

			if ( (*it).displayDataType_ == display_data::single_element) {
				s << (*it).startOfRangeOrSingle_ << ",";
			} else if ( (*it).displayDataType_ == display_data::range_element) {
				s << (*it).startOfRangeOrSingle_ << " - " << (*it).endOfRange_ << endl;
			}
			if (currXpos + s.str().length() > maxWinX) {
				currXpos =1, ++currYpos;
			}
			mvwprintw(stub_list_window, currYpos, currXpos, "%s", s.str().c_str());
			currXpos += s.str().length() + 1;
		}
		*/
		Print_DisplayDataUnitVector (stub_list_window,
				displayData_, currXpos, currYpos, maxWinX);
		// mvwprintw(data_entry_window, 2, 1, "just before exit eval");

		//wrefresh(stub_list_window);
		update_panels();
		doupdate();
		//AbstractRuntimeQuestion::GetDataFromUser(data_entry_window);
	}

	user_response::UserResponseType user_resp = AbstractRuntimeQuestion::GetDataFromUser(question_window, stub_list_window, data_entry_window);

/*
get_data_again:
	user_response::UserResponseType user_resp = AbstractRuntimeQuestion::GetDataFromUser(data_entry_window);
	stringstream mesg; mesg << "user_resp: " << user_resp;
	cout << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
		<< mesg.str() << endl;
	if (user_resp == user_response::UserClearedData && question_attributes.isAllowBlank()) {
		// valid response if blanks are allowed but dont do isAnswered_ = true
		// because otherwise when visiting the questionnaire it will skip this
		// question and data entry will have an off by 1 error everytime they
		// are reviewing this question - since blank is a valid answer
	} else if (user_resp == user_response::UserEnteredData) {
	} else if (user_resp == user_response::UserEnteredNavigation
			&& user_navigation == NAVIGATE_PREVIOUS) {
	} else {
		goto get_data_again;
	}
	*/

}
#endif /* 0 */



//void NamedStubQuestion::eval()
#if 0
void NamedStubQuestion::eval(/*qs_ncurses::*/WINDOW * question_window
			     , /*qs_ncurses::*/WINDOW* stub_list_window
			     , /*qs_ncurses::*/WINDOW* data_entry_window)
{
	if (displayData_.begin() == displayData_.end()) {
		MakeDisplaySummaryDataRanges();
#if 0
		vector<stub_pair> & vec= (nr_ptr->stubs);
		if (vec.size() == 0) {
			cerr << "runtime error: Impossible !!! stubs with no codes: "
				<< __LINE__ << ", " << __FILE__ << __PRETTY_FUNCTION__
				<< " question name: " << questionName_ << endl;
			exit(1);
		}
		int start_code = vec[0].code;
		int previous_code = start_code;
		int current_code = start_code;
		for (int32_t i=0; i<vec.size(); ++i) {
			current_code = vec[i].code;
			if (current_code - previous_code > 1) {
				if (start_code < previous_code) {
					displayData_.push_back(display_data::DisplayDataUnit(start_code, previous_code));
					start_code = current_code;
					previous_code = current_code;
				} else {
					displayData_.push_back(display_data::DisplayDataUnit(start_code));
					start_code = current_code;
					previous_code = current_code;
				}
			}
			if (i>0) {
				previous_code = current_code;
			}
			//displayData_.push_back(display_data::DisplayDataUnit(vec[i].code));
		}
		if (start_code < previous_code) {
			displayData_.push_back(display_data::DisplayDataUnit(start_code, previous_code));
			start_code = current_code;
			previous_code = current_code;
		} else {
			displayData_.push_back(display_data::DisplayDataUnit(start_code));
			start_code = current_code;
			previous_code = current_code;
		}
#endif /*  0 */
	}
	if (question_window  == 0 || stub_list_window  == 0 || data_entry_window  == 0) {
		cout << questionName_ << ".";
		if (loop_index_values.size()>0) {
			for(uint32_t i=0; i<loop_index_values.size(); ++i){
				cout << loop_index_values[i]+1 << ".";
			}
		}
		//cout << questionText_ << endl << endl;
		cout << textExprVec_[0]->text_ << endl << endl;

		//cout << questionName_ << "." << questionText_ << endl << endl;
		//vector<stub_pair> vec= *stub_ptr;
		vector<stub_pair> & vec= (nr_ptr->stubs);
		for (uint32_t i = 0; i< vec.size(); ++i) {
			if( vec[i].mask)
				cout << vec[i].stub_text << ": " << vec[i].code << endl;
		}

		if (input_data.begin() != input_data.end()) {
			cout << "Current data values: ";

			for(set<int32_t>::iterator iter = input_data.begin();
				iter != input_data.end(); ++iter){
				cout << *iter << " ";
			}
			cout << endl;
		}

		//user_response::UserResponseType user_resp = AbstractRuntimeQuestion::GetDataFromUser(data_entry_window);

	} else {
		wclear(question_window);
		box(question_window, 0, 0);
		wclear(stub_list_window);
		box(stub_list_window, 0, 0);
		wclear(data_entry_window);
		box(data_entry_window, 0, 0);
		mvwprintw(question_window, 1, 1, "%s.", questionName_.c_str());
		int len_qno = questionName_.length()+2;
		if(loop_index_values.size()>0){
			for(uint32_t i=0; i<loop_index_values.size(); ++i){
				//cout << loop_index_values[i]+1 << ".";
				mvwprintw(question_window, 1, len_qno, "%d.", loop_index_values[i]+1);
				if (loop_index_values[i]+1<10) {
					len_qno += 1;
				} else if (loop_index_values[i]+1<100) {
					len_qno += 2;
				} else if (loop_index_values[i]+1<1000) {
					len_qno += 3;
				} else if (loop_index_values[i]+1<10000) {
					len_qno += 4;
				}
				len_qno += 1; // for the "."
			}
		}
		//mvwprintw(question_window,1,1, "%s. %s", questionName_.c_str(), questionText_.c_str() );
		//wrefresh(question_window);
		//mvwprintw(question_window, 1, len_qno+1, " %s", questionText_.c_str() );
		mvwprintw(question_window, 1, len_qno+1, " %s", textExprVec_[0]->text_.c_str() );
		for (int i=1; i<textExprVec_.size(); ++i) {
			mvwprintw(question_window, 2+i, 1, " %s", textExprVec_[i]->text_.c_str() );
		}
		update_panels();
		doupdate();
		int32_t maxWinX, maxWinY;
		getmaxyx(data_entry_window, maxWinY, maxWinX);
		int32_t currXpos = 1, currYpos = 1;
		Print_DisplayDataUnitVector (stub_list_window, displayData_, currXpos, currYpos, maxWinX);
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
		// AbstractRuntimeQuestion::GetDataFromUser(data_entry_window);
	}
	user_response::UserResponseType user_resp = AbstractRuntimeQuestion::GetDataFromUser(question_window, stub_list_window, data_entry_window);

	/*
get_data_again:
	user_response::UserResponseType user_resp = AbstractRuntimeQuestion::GetDataFromUser(data_entry_window);
	stringstream mesg; mesg << "user_resp: " << user_resp;
	cout << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
		<< mesg.str() << endl;
	if (user_resp == user_response::UserClearedData && question_attributes.isAllowBlank()) {
		// valid response if blanks are allowed but dont do isAnswered_ = true
		// because otherwise when visiting the questionnaire it will skip this
		// question and data entry will have an off by 1 error everytime they
		// are reviewing this question - since blank is a valid answer
	} else if (user_resp == user_response::UserEnteredData) {
	} else if (user_resp == user_response::UserEnteredNavigation
		&& user_navigation == NAVIGATE_PREVIOUS) {
	} else {
		goto get_data_again;
	}
	*/

}
#endif /* 0 */

