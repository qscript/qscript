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
#include <cstdlib>

#include "question_stdout_runtime.h"
#include "named_range.h"
#include "question_disk_data.h"
#include "qscript_data.hpp"

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

int32_t prompt_user_for_serial_no(int (* p_return_ser_no) (int))
{

	cout << "Enter a serial no, 0 to exit" << endl;
	int serial_no;
	cin >> serial_no;

	if (serial_no == 0) {
		cout << "exiting ..." << endl;
		exit(0);
	} else {
		p_return_ser_no (serial_no);
	}
	// unreachable code 
	return serial_no;
}

void setup_ui (int argc, char * argv[] )
{
	cout 	<< "Welcome to the simplest possible qscript runtime"
		<< endl;

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

void DisplayQuestionTextView (const vector <string> & qno_and_qtxt)
{
	if (qno_and_qtxt.size() > 1) {
		cout << qno_and_qtxt[0] << "." << qno_and_qtxt[1];
		for (int i = 2; i < qno_and_qtxt.size(); ++i) {
			cout <<  qno_and_qtxt[i].c_str();
		}
	}
	cout << endl;
}


void ClearPreviousView ()
{
	cout << __PRETTY_FUNCTION__ << endl;
}

void PrepareStubs (AbstractQuestion *q)
{

}

void DisplayStubs (AbstractQuestion *q)
{
	if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*> (q) ) {
		vector<stub_pair> & vec= (nq->nr_ptr->stubs);
		for (int i=0; i<vec.size(); ++i) {
			cout 	<< vec[i].code << ":" << vec[i].stub_text 
				<< endl;
		}
	} else if (RangeQuestion * rq = dynamic_cast<RangeQuestion*> (q) ) {
		rq->MakeDisplaySummaryDataRanges();
		for(	vector<display_data::DisplayDataUnit>::iterator it = rq->displayData_.begin();
				it != rq->displayData_.end(); ++it) {
			//cout << *it << endl;
			if ( (*it).displayDataType_ == display_data::single_element) {
				cout << (*it).startOfRangeOrSingle_ << ", ";
			} else if ( (*it).displayDataType_ == display_data::range_element) {
				cout << (*it).startOfRangeOrSingle_ << " - " << (*it).endOfRange_ << endl;
			}
		}
	} else {
		cerr << "Unhandled exception" << endl;
		exit(1);
	}
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

void GetUserInput ( 
	void (*callback_ui_input) (UserInput p_user_input, AbstractQuestion * q,
		struct TheQuestionnaire * theQuestionnaire), 
		AbstractQuestion *q, struct TheQuestionnaire * theQuestionnaire)
{
	string current_response;
	getline(cin, current_response);
	UserInput user_input;
	if (current_response.size() > 0) {
		if (current_response[0] == 'P') {
			user_input.userNavigation_ = NAVIGATE_PREVIOUS;
			user_input.theUserResponse_ = user_response::UserEnteredNavigation;
			callback_ui_input (user_input, q, theQuestionnaire);
		} else if (current_response[0] == 'N') {
			user_input.userNavigation_ = NAVIGATE_NEXT;
			user_input.theUserResponse_ = user_response::UserEnteredNavigation;
			callback_ui_input (user_input, q, theQuestionnaire);
		} else  {
			user_input.theUserResponse_ = user_response::UserEnteredData;
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
#if 0

			vector <int> answers;
			//str2int (answers, current_response.c_str());
			str2int (answers, current_response);
			cout << "Entered data: " ;
			print_vec(answers);
			cout << endl;
			bool is_valid = VerifyQuestionIntegrity(answers, next_q->valid_codes);
			if (is_valid) {
				next_q->is_answered = true;
				question_eval_loop (NORMAL_FLOW, NAVIGATE_NEXT, 
						next_q, 0, qnre);
			} else {
				cout << "Invalid Entry" << endl;
				question_eval_loop (NORMAL_FLOW, NAVIGATE_NEXT, 
						last_question_visited, 0, qnre);
			}
#endif /* 0 */
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
		GetUserInput (callback_ui_input, q, theQuestionnaire);
	}
}

void stdout_eval (AbstractQuestion * q, struct TheQuestionnaire * theQuestionnaire,
	void (*callback_ui_input) (UserInput p_user_input, AbstractQuestion * q, struct TheQuestionnaire * theQuestionnaire))
{
	cout << __PRETTY_FUNCTION__ << endl;
	ClearPreviousView ();
	vector <string> qno_and_qtxt = PrepareQuestionText (q);
	DisplayQuestionTextView (qno_and_qtxt);
	PrepareStubs (q);
	DisplayStubs (q);
	GetUserInput (callback_ui_input, q, theQuestionnaire);
	exit(1);
}
