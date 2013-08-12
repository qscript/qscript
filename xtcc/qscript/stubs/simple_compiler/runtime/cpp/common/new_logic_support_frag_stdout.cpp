/* ============= new_logic_support_frag stdout =========*/
//void question_eval_loop2 (
//	UserInput p_user_input,
//	const vector<AbstractRuntimeQuestion *> & last_question_visited,
//	AbstractRuntimeQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire, int nest_level);

int callback_get_ser_no_from_ui (int p_ser_no, int nest_level)
{
	// now its not :-) // nxd: this is a global variable - has to be eliminated at some point
	TheQuestionnaire * theQuestionnaire = new TheQuestionnaire (jno);
	cout << "received serial no : " << p_ser_no << "from ui";

	theQuestionnaire->ser_no = p_ser_no;
	theQuestionnaire->base_text_vec.push_back(BaseText("All Respondents"));
	//theQuestionnaire->compute_flat_file_map_and_init();
	UserNavigation qnre_navigation_mode = NAVIGATE_NEXT;

	AbstractRuntimeQuestion * last_question_visited = 0;
	AbstractRuntimeQuestion * jump_to_question = 0;
	EvalMode qnre_mode = NORMAL_FLOW;
	//question_eval_loop (qnre_mode,
	//			qnre_navigation_mode, last_question_visited,
	//			jump_to_question, theQuestionnaire);
	UserInput l_user_input;
	vector <AbstractRuntimeQuestion*> empty_vec;
	question_eval_loop2 (
				l_user_input, /* last_question_visited */ empty_vec,
				/* jump_to_question */ 0, theQuestionnaire, nest_level + 1);
	cout << "finished qnre: exiting ..." << endl;
	prompt_user_for_serial_no (callback_get_ser_no_from_ui, nest_level + 1);
	return 0;
}


void parse_input_data(vector<int> * data_ptr, int & success);
//void callback_ui_input (UserInput p_user_input,
//		const vector<AbstractRuntimeQuestion *> & q_vec,
//		struct TheQuestionnaire * theQuestionnaire, int nest_level);
void eval_single_question_logic_with_input (UserInput p_user_input,
		const vector<AbstractRuntimeQuestion *> & q_vec,
		struct TheQuestionnaire * theQuestionnaire, int nest_level);

void callback_ui_input (UserInput p_user_input,
		const vector<AbstractRuntimeQuestion *> & q_vec,
		struct TheQuestionnaire * theQuestionnaire, int nest_level)
{
	cout << __PRETTY_FUNCTION__ << endl;
	// this will be called by the UI - it is the UI's responsibility to
	// get valid data for us
	//bool valid_input = q->VerifyResponse (p_user_input.theUserResponse_, p_user_input.userNavigation_);
	if (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {
		question_eval_loop2 (
				p_user_input,
				/* last_question_visited */ q_vec,
				/*  jump_to_question */ 0, theQuestionnaire, nest_level + 1);
	} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {
		eval_single_question_logic_with_input (p_user_input, q_vec, theQuestionnaire, nest_level + 1);
	} else if (p_user_input.theUserResponse_ == user_response::UserSavedData) {
		cout << "under stdout either the user can enter data or navigation" << endl
			<< "but under ncurses or other guis - it's possible to enter data" << endl
			<< " AND ask to save by pressing f4, in which case we should save the data "
			<< " and then try to validate the user input - just like we would in a normal case"
			<< endl;
		// nxd: this function needs to be cleaned up
		//      we can easily downcast to an AbstractQuestionnaire and then there is no need for this
		//      function to be present here
		theQuestionnaire->write_data_to_disk (theQuestionnaire->question_list, theQuestionnaire->jno, theQuestionnaire->ser_no);
	} else {
		cerr << __PRETTY_FUNCTION__ << " unhandled case theUserResponse_" << endl;
	}
}

void question_eval_loop2 (
	UserInput p_user_input,
	const vector<AbstractRuntimeQuestion *> & last_question_visited,
	AbstractRuntimeQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire, int nest_level)
{
	cout << endl << "Enter: " << __PRETTY_FUNCTION__
		<< endl
		<< "nest_level: " << nest_level
		<< endl;
	cout << "arg values: " << endl;
	if (p_user_input.userNavigation_ == NAVIGATE_NEXT) {
		cout << "p_user_input.userNavigation_ == NAVIGATE_NEXT" << endl;
	} else if (p_user_input.userNavigation_ == NAVIGATE_PREVIOUS) {
		cout << "p_user_input.userNavigation_ == NAVIGATE_PREVIOUS" << endl;
	} else {
		cout << "FIXME: p_user_input.userNavigation_ == Unhandled value " << endl;
	}
	if 	  (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {
		cout << "p_user_input.theUserResponse_ == UserEnteredNavigation" << endl;
	} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {
		cout << "p_user_input.theUserResponse_ == UserEnteredData" << endl;
	} else if (p_user_input.theUserResponse_ == user_response::UserClearedData) {
		cout << "p_user_input.theUserResponse_ == UserClearedData" << endl;
	} else if (p_user_input.theUserResponse_ == user_response::UserSavedData) {
		cout << "p_user_input.theUserResponse_ == UserSavedData" << endl;
	} else if (p_user_input.theUserResponse_ == user_response::NotSet) {
		cout << "p_user_input.theUserResponse_ == NotSet" << endl;
	} else {
		cout << "FIXME: p_user_input.theUserResponse_ == Unhandled value " << endl;
	}


	cout
		<< "p_user_input.questionResponseData_:"
		<< p_user_input.questionResponseData_ << endl;

	if (last_question_visited.size() > 0) {
		cout << "last_question_visited->questionName_:"
			<<  last_question_visited[0]->questionName_
			<< endl;
	} else {
		cout << "last_question_visited->questionName_: is NULL"  << endl;
	}

	if (last_question_visited.size() > 0) {
		if (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {
			if (p_user_input.userNavigation_ == NAVIGATE_PREVIOUS) {
				fprintf(qscript_stdout,
					"user_navigation == NAVIGATE_PREVIOUS\n");
				cout << "Previous Button in MULITPLE QUESTIONS PER PAGE UNHANDLED"
					<< endl;
#if 0
				AbstractRuntimeQuestion *target_question =
					theQuestionnaire->ComputePreviousQuestion(last_question_visited);
				// this line seems unncessary - but it is necessary
				// - DO NOT DELETE AS REDUNDANT
				vector<AbstractRuntimeQuestion> * q =
					theQuestionnaire->eval2 (
					NAVIGATE_PREVIOUS, last_question_visited, target_question);
				if (target_question == 0) {
					stdout_eval (last_question_visited, theQuestionnaire, callback_ui_input, nest_level+1);
				} else {
					stdout_eval (target_question, theQuestionnaire, callback_ui_input, nest_level+1);
				}
#endif /* 0 */
			} else if (p_user_input.userNavigation_ == NAVIGATE_NEXT) {
				// do nothing
				// once we exit this major block == last_question_visited
				// the bottom of this function will handle it
			} else {
				cout << "Unhandled case userNavigation_ ... exiting" << endl
					<< __FILE__ << ","
					<< __LINE__ << ","
					<< __PRETTY_FUNCTION__ << ","
					<< endl;
				exit(1);
			}
		} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {
			// the management of correctly accepting data is handled
			// by : callback_ui_input
			// if we have reached back again here - it means it's
			// time to get the next question

		} else {
			cout << "Unhandled case userNavigation_ ... exiting" << endl;
			exit(1);
		}
	} // else {
	// should reach here - end of :
		vector<AbstractRuntimeQuestion *> q_vec =
			theQuestionnaire->eval2 (
				NAVIGATE_NEXT, last_question_visited, jump_to_question);
		if (q_vec.size() == 0) {
			cout << "End of qnre();" << endl << ">";
		} else {
			cout << __PRETTY_FUNCTION__ << "," << __LINE__ <<  ", eval2 return first q in vec = "
				<< q_vec[0]->questionName_ << endl;
			stdout_eval (q_vec, theQuestionnaire, callback_ui_input, nest_level + 1);
		}
	//}
}

/* ============= END new_logic_support_frag stdout =========*/
