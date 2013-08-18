/*
 * =====================================================================================
 *
 *       Filename:  question_stdout_runtime.C
 *
 *    Description:  Simplest possible runtime
 *    			and I should have built this first
 *    			but I thought that I was too smart
 *
 *        Version:  1.0
 *        Created:  Sunday 17 February 2013 11:42:54  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Neil Xavier D'Souza
 *        Company:
 *
 * =====================================================================================
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <dirent.h>

#include "question_stdout_runtime.h"
#include "named_range.h"
#include "question_disk_data.h"
#include "qscript_data.hpp"
//#include "qtm_data_file.h"

void parse_input_data(vector<int> * data_ptr, int & success);

using namespace std;


char get_end_of_question_response()
{
	return 'Z'; // an invalid character
}

void print_save_partial_data_message_success ()
{
	cout << "saved partial data " << endl;
}

int32_t prompt_user_for_serial_no(int (* p_return_ser_no) (int, int), int nest_level)
{

	cout << "Enter a serial no, 0 to exit" << endl;
	int serial_no;
	cin >> serial_no;

	if (serial_no == 0) {
		cout << "exiting ..." << endl;
		exit(0);
	} else {
		p_return_ser_no (serial_no, nest_level);
	}
	// unreachable code
	return serial_no;
}

void setup_ui (int argc, char * argv[] )
{
	cout 	<< "Welcome to the simplest possible qscript runtime"
		<< endl;

}


vector<string> PrepareQuestionText (AbstractRuntimeQuestion *q)
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
	//question_text << q->textExprVec_[0]->text_;
	//result.push_back (question_text.str());
	//for (int i=1; i<q->textExprVec_.size(); ++i) {
	//	//mvwprintw(question_window, 2+i, 1, " %s", textExprVec_[i]->text_.c_str() );
	//	result.push_back (q->textExprVec_[i]->text_);
	//}
	for (int i=0; i<q->textExprVec_.size(); ++i)
        {
        	question_text << "<p>";
        	if (q->textExprVec_[i]->teType_ == TextExpression::simple_text_type)
        	{
        		//stringstream mesg_id;
        		//mesg_id << part_mesg_id.str() << "_" << i;
        		//question_text += WString::tr(mesg_id.str().c_str());
			question_text << q->textExprVec_[i]->text_;
        	}
        	else if (q->textExprVec_[i]->teType_ == TextExpression::named_attribute_type)
        	{
        		//stringstream named_attribute_key;
        		//named_attribute_key << q->textExprVec_[i]->naPtr_->name;
        		//named_attribute_key << "_" << q->textExprVec_[i]->naIndex_;
        		//question_text += WString::tr(named_attribute_key.str().c_str());
			question_text << q->textExprVec_[i]->naPtr_->attribute[q->textExprVec_[i]->naIndex_];
        	}
        	else if (q->textExprVec_[i]->teType_ == TextExpression::question_type)
        	{
        		if (q->textExprVec_[i]->codeIndex_ != -1) {
        			question_text << q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers(q->textExprVec_[i]->codeIndex_);
        		} else {
        			question_text << q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers();
        		}
			//question_text << "pipedQuestion_" << endl;
        	}
        	question_text << "</p>";
        }

	result.push_back (question_text.str());
	return result;

}

void DisplayQuestionTextView (const vector <string> & qno_and_qtxt)
{
	string start_marker("===================== QUESTION TEXT =============================");
	string end_marker  ("================= END OF QUESTION TEXT ==========================");
	if (qno_and_qtxt.size() > 1) {
		cout << start_marker << endl;
		cout << qno_and_qtxt[0] << "." << qno_and_qtxt[1];
		for (int i = 2; i < qno_and_qtxt.size(); ++i) {
			cout <<  qno_and_qtxt[i].c_str();
		}
		cout << endl;

		cout << end_marker << endl;
	}
	cout << endl;
}


void ClearPreviousView ()
{
	cout << __PRETTY_FUNCTION__ << endl;
}

void PrepareStubs (AbstractRuntimeQuestion *q)
{

}

void DisplayStubs (AbstractRuntimeQuestion *q)
{
	string marker_start ("------------------------------- STUBS ------------------------------------");
	string marker_end   ("----------------------------- STUBS END ----------------------------------");
	cout << marker_start << endl;
	if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*> (q) ) {
		vector<stub_pair> & vec= (nq->nr_ptr->stubs);
		for (int i=0; i<vec.size(); ++i) {
			if( vec[i].mask) {
				cout 	<< vec[i].code << " : " << vec[i].stub_text
					<< endl;
			}
		}
	} else if (RangeQuestion * rq = dynamic_cast<RangeQuestion*> (q) ) {
		rq->MakeDisplaySummaryDataRanges();
		for(	vector<display_data::DisplayDataUnit>::iterator it = rq->displayData_.begin();
				it != rq->displayData_.end(); ++it) {
			//cout << *it << endl;
			if ( (*it).displayDataType_ == display_data::single_element) {
				cout << "  " << (*it).startOfRangeOrSingle_ << " ";
			} else if ( (*it).displayDataType_ == display_data::range_element) {
				cout << "  " << (*it).startOfRangeOrSingle_ << " - " << (*it).endOfRange_;
			}
		}
		cout << endl;
	} else {
		cerr << "Unhandled exception" << endl;
		exit(1);
	}
	cout << marker_end << endl;
}

/*
typedef void (*callback_get_user_input_t) (callback_ui_input_t callback_ui_input,
			callback_get_user_input_t callback_get_user_input);

struct UserInputParams
{
void (*callback_ui_input) (UserInput * p_user_input);
}; */


/*
void GetUserInput (void (*callback_ui_input) (UserInput * p_user_input),
		void (*get_user_input) (
			void (*callback_ui_input) (UserInput * p_user_input),
			void (*get_user_input) (
				void (*callback_ui_input) (UserInput * p_user_input),
				)
		)
	)
 */
typedef void (*callback_ui_input_t) (UserInput * p_user_input);

// this functions job is to take any user input from the interface
// and pass it to the control flow logic decider.
// Any control flow logic that appears here is a mistake in my programming
// and needs to be fixed
void GetUserInput (
	void (*callback_ui_input) (UserInput p_user_input,
		const vector<AbstractRuntimeQuestion *> & q_vec,
		struct TheQuestionnaire * theQuestionnaire, int nest_level),
	const vector<AbstractRuntimeQuestion *> & q_vec,
	struct TheQuestionnaire * theQuestionnaire, int nest_level)
{
	cerr << "FIXME: add conditions for all questions in input vector, right now we are checking only 1st question "
		<< __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
		<< endl;
	AbstractRuntimeQuestion * q = q_vec[0];
	cout << __PRETTY_FUNCTION__ << endl;
	if (q->no_mpn == 1) {
		cout << " Question is single answer, please enter only 1 response." << endl;
	} else {
		cout << " Question accepts multiple answers." << endl;
	}
	string current_response;
	cout << "Enter Data>" << endl;
	getline(cin, current_response);
	UserInput user_input;
	if (current_response.size() > 0) {
		if (current_response[0] == 'P') {
			user_input.userNavigation_ = NAVIGATE_PREVIOUS;
			user_input.theUserResponse_ = user_response::UserEnteredNavigation;
		} else if (current_response[0] == 'N') {
			user_input.userNavigation_ = NAVIGATE_NEXT;
			user_input.theUserResponse_ = user_response::UserEnteredNavigation;
		} else if (current_response[0] == 'S') {
			user_input.userNavigation_ = SAVE_DATA;
			user_input.theUserResponse_ = user_response::UserSavedData;
			cout << "Got SAVE_DATA from user" << endl;
		} else  {
			user_input.theUserResponse_ = user_response::UserEnteredData;
			user_input.questionResponseDataVec_.push_back( current_response);
		}

		cout << "reached here" << endl;
		string err_mesg;
		bool valid_input = q->VerifyResponse(user_input.theUserResponse_, user_input.userNavigation_, err_mesg);
		// if VerifyResponse fails it is the UI's job to get valid input from the user
		// It is not the UI's job to parse the data and validate the answer against the question

		/* moved to VerifyResponse - but seems redundant - it was already there
		if (q->isAnswered_ == false && user_input.userNavigation_ == NAVIGATE_PREVIOUS
				&& user_input.theUserResponse_ == user_response::UserEnteredNavigation) {
			// allow this behaviour - they can go back to the
			// previous question without answering anything -
			// no harm done
			callback_ui_input (user_input, q, theQuestionnaire);
		} else */
		/* moved this into VerifyResponse - final else clause
		 * where all error messages can be reported
		if (q->isAnswered_ == false && user_input.userNavigation_ == NAVIGATE_NEXT
				&& user_input.theUserResponse_ == user_response::UserEnteredNavigation
				&& q->question_attributes.isAllowBlank() == false) {
			// nxd: 18-feb-2013 - note this error message should be passed
			// back as a parameter  - so it can be reported
			err_mesg = "cannot navigate to next question unless this is answered";
			valid_input = false;
		}
		*/

		cout << "reached here: valid_input :" << valid_input <<  endl;

		if (valid_input) {

			if (user_input.theUserResponse_ == user_response::UserSavedData) {
				cout << "invoking callback_ui_input with UserSavedData" << endl;
				// this call will return really fast
				//  (if you consider io fast)
				//  but what I mean is we wont add much to the call stack
				callback_ui_input (user_input, q_vec, theQuestionnaire, nest_level);
				GetUserInput (callback_ui_input, q_vec, theQuestionnaire, nest_level);
				cout << "callback_ui_input has returned after UserSavedData" << endl;
			} else {
				cout << "reached here: "
					<< __PRETTY_FUNCTION__ << endl;
				callback_ui_input (user_input, q_vec, theQuestionnaire, nest_level);
				cout << "callback_ui_input has returned"
					<< __PRETTY_FUNCTION__ << endl;
			}
			// move all this into callback_ui_input
			// case UserEnteredData
#if 0

			int success;
			vector <int> input_data;
			parse_input_data (current_response, &input_data, success);
			if (success == 0) {
				GetUserInput (callback_ui_input, q, theQuestionnaire);
			} else {
				// default direction - chosen by us
				user_input.userNavigation_ = NAVIGATE_NEXT;
				user_input.inputData_ = input_data;
				callback_ui_input (user_input, q, theQuestionnaire);
			}
#endif /*  0 */
		} else {
			// we should be passing an error message too
			GetUserInput (callback_ui_input, q_vec, theQuestionnaire, nest_level);
		}
		/*
		else {
			// invalid entries
			cout << "invalid input" << endl;
			question_eval_loop (NORMAL_FLOW, NAVIGATE_NEXT,
					last_question_visited, 0, qnre);
			//goto ask_again;
		} */
	} else {
		// nxd: 19-feb-2013
		// I have to change this
		GetUserInput (callback_ui_input, q_vec, theQuestionnaire, nest_level);
	}
}

void DisplayCurrentAnswers (AbstractRuntimeQuestion * q)
{
	if (q->input_data.begin() != q->input_data.end()) {
		cout << "Current Answers values: ";

		for (set<int32_t>::iterator iter = q->input_data.begin();
			iter != q->input_data.end(); ++iter){
			cout << *iter << " ";
		}
		cout << endl;
	}
	string end_marker("----------------- END OF ANSWERS -----------------------");
	cout << end_marker << endl;
}

void stdout_eval (const vector<AbstractRuntimeQuestion *> & q_vec,
		struct TheQuestionnaire * theQuestionnaire,
	void (*callback_ui_input)
		(UserInput p_user_input, const vector<AbstractRuntimeQuestion *> & q_vec,
		 struct TheQuestionnaire * theQuestionnaire,
		 int nest_level),
	int nest_level
	)
{
	cout << __PRETTY_FUNCTION__ << " nest_level : " << nest_level << endl;
	ClearPreviousView ();
	// 11-aug-2013
	// begin testing by using just the first question
	// in the returned array
	// this way we can change the functions signatures slowly
	// 1st Assumption - we are called by question_eval_loop2
	// it already checks if the vector size is 0 and returns end of qnre
	// hence we safely pull out the first question from the vector
	// assuming that we are never 0 size
	AbstractRuntimeQuestion * q= q_vec[0];
	vector <string> qno_and_qtxt = PrepareQuestionText (q);
	DisplayQuestionTextView (qno_and_qtxt);
	PrepareStubs (q);
	DisplayStubs (q);
	DisplayCurrentAnswers (q);
	GetUserInput (callback_ui_input, q_vec, theQuestionnaire, nest_level);
}

int process_options(int argc, char * argv[]);

extern bool write_data_file_flag;
extern bool write_qtm_data_file_flag;
extern bool write_messages_flag;
extern bool write_xtcc_data_file_flag;
extern bool card_start_flag;
extern bool card_end_flag;
extern int card_start;
extern int card_end;
extern string qscript_stdout_fname;

int callback_get_ser_no_from_ui (int p_ser_no, int nest_level);
void SetupSignalHandler();
extern FILE * qscript_stdout ;
extern DIR * directory_ptr ;
int32_t main(int argc, char * argv[])
{
	process_options(argc, argv);
	if (write_data_file_flag||write_qtm_data_file_flag||write_xtcc_data_file_flag)
	{
		//qtm_data_file_ns::init();
		//qtm_data_file_ns::init_exceptions();
		directory_ptr = opendir(".");
		if (! directory_ptr)
		{
			cout << " unable to open . (current directory) for reading\n";
			exit(1);
		}
	}
	bool using_ncurses = true;
	qscript_stdout = fopen(qscript_stdout_fname.c_str(), "w");
	using namespace std;
	SetupSignalHandler();
	setup_ui (argc, argv);
	prompt_user_for_serial_no (callback_get_ser_no_from_ui, 1);
} /* close main */
