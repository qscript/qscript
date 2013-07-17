/*
 * =====================================================================================
 *
 *       Filename:  question_wx2_runtime.cpp
 *
 *    Description:  wx Widgets GUI display for qscript runtime
 *
 *        Version:  1.0
 *        Created:  Thursday 21 February 2013 20:38:48  IST (is this a bug - it was showing 8:38)
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Neil Xavier D'Souza
 *        Company:
 *
 * =====================================================================================
 */

#include <wx/wx.h>
#include <wx/mediactrl.h>   //for wxMediaCtrl
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <locale.h>
#include <libintl.h>
#include <map>

#include "question_gtk2_runtime.h"
#include "question.h"
#include "named_range.h"
#include "question_disk_data.h"
#include "qscript_data.hpp"

using std::cout;
using std::endl;
using std::cerr;

#include "question_gtk2_runtime.h"

class wxQuestionnaireApplication : public wxApp
{
public:
	virtual bool OnInit();

};

struct wxQuestionnaireGUI : public wxFrame
{
public:
	wxQuestionnaireGUI(const wxString& title);
	void (*callback_ui_input) (UserInput p_user_input, AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire, int nest_level);
	int (*return_ser_no) (int, struct TheQuestionnaire *);
	wxTextCtrl *txt_ctrl_ser_no;
	wxBoxSizer *serial_row_sizer;
	wxBoxSizer *stubsRowSizer_ ;
	wxBoxSizer * check_box_sizer;
	wxBoxSizer * radio_box_sizer;
	wxBoxSizer * data_entry_and_navg_sizer;
	wxBoxSizer * data_entry_line_sizer;
	wxPanel *panel;
	wxPanel * media_panel_;
	wxFlexGridSizer *fgs ;
	wxBoxSizer *panel_sizer ;
	wxBoxSizer *media_panel_sizer_ ;
	wxStatusBar * statusBar_;
	// warning - need to delete this
	wxMediaCtrl * mediactrl_;

	AbstractRuntimeQuestion * last_question_visited;
	AbstractRuntimeQuestion * jump_to_question;

	void get_serial_no (wxCommandEvent& event);
	struct TheQuestionnaire * theQuestionnaire_;
	void ConstructQuestionForm( AbstractRuntimeQuestion *q );
	void DisplayQuestionTextView (const vector <string> & qno_and_qtxt);

	void PrepareSingleCodedStubDisplay (NamedStubQuestion * nq);
	void PrepareMultiCodedStubDisplay (NamedStubQuestion * nq);
	void DisplayStubs (AbstractRuntimeQuestion * q);
	void DisplayVideo (AbstractRuntimeQuestion * q);

	void OnSingleAnswerToggle(wxCommandEvent& event);

	void OnCheckboxToggle(wxCommandEvent& event);

	void ShowSerialNoScreen(wxCommandEvent& WXUNUSED(event));
	//void ShowEndOfQnreScreen(wxCommandEvent& WXUNUSED(event));
	void ShowEndOfQnreScreen();

	void ShowQuestionScreen(wxCommandEvent& WXUNUSED(event));
	void ClearQuestionScreen();

	int32_t prevRBValue_;
	int32_t rbData_;
	set<int32_t> cbData_;
	map <int32_t, int32_t> rbQnreCodeMap_;
	map <int32_t, int32_t> rbQnreReverseCodeMap_;
	void ClearRadio();
	void ClearCheckList();
	void ClearStubsArea();
	void ClearMediaArea();
	void CreateSerialNoScreen();
	void CreateEndOfQnreScreen();
	void CreateQuestionScreen();
	void ClearSerialNoScreen(wxCommandEvent& WXUNUSED(event));
	void ClearEndOfQnreScreen(wxCommandEvent& WXUNUSED(event));
	//void LostFocus(wxCommandEvent& WXUNUSED(event));

	wxStaticText *the_question ;
	wxStaticText *the_stubs ;
	wxStaticText *the_data_entry_line ;
	wxTextCtrl * txt_data_entry_line;
	//wxRadioBox *m_radio;
	wxSizer *m_sizerRadio;
	//wxScrolledWindow * rboxWindow_;


	wxCheckListBox * m_pListBox;
	wxListBox * m_rListBox;

	wxBoxSizer * end_of_qnre_sizer;


	void handleDataInput (wxCommandEvent& WXUNUSED(event));
	void handlePrevNavigation (wxCommandEvent& WXUNUSED(event));
	void handleSave(wxCommandEvent& WXUNUSED(event));

	void handleCBDataInput (int nest_level);
	void handleRBDataInput (int nest_level);

	void OnMediaLoaded(wxMediaEvent& WXUNUSED(evt));

	void set_callback_ui_input (
			void (*p_callback_ui_input) (UserInput p_user_input, AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire, int nest_level)
			);

private:
    DECLARE_EVENT_TABLE()


};


enum MyWidgetID {
	ID_BUTTON_SERIAL_NO = wxID_HIGHEST,
	ID_STUBS_ROW,
	ID_NEXT_BUTTON,
	SingleAnswerRadioBox,
	MultiAnswerCheckListBox,
	ID_BUTTON_PREVIOUS_QUESTION,
	ID_BUTTON_SAVE,
	ID_BUTTON_CLOSE_QUESTIONNAIRE_WITHOUT_SAVING,
	ID_MEDIA_PANEL,
	ID_MEDIACTRL
};


BEGIN_EVENT_TABLE(wxQuestionnaireGUI, wxFrame)
    EVT_BUTTON(ID_BUTTON_SERIAL_NO,  wxQuestionnaireGUI::get_serial_no)
    EVT_BUTTON(ID_NEXT_BUTTON,  wxQuestionnaireGUI::handleDataInput)
    EVT_BUTTON(ID_BUTTON_PREVIOUS_QUESTION,  wxQuestionnaireGUI::handlePrevNavigation)
    EVT_BUTTON(ID_BUTTON_SAVE,  wxQuestionnaireGUI::handleSave)
    EVT_LISTBOX(SingleAnswerRadioBox, wxQuestionnaireGUI::OnSingleAnswerToggle)
    EVT_CHECKLISTBOX(MultiAnswerCheckListBox, wxQuestionnaireGUI::OnCheckboxToggle)
    //EVT_KILL_FOCUS(txt_data_entry_line, wxQuestionnaireApplication::LostFocus)
    EVT_MEDIA_LOADED(ID_MEDIACTRL, wxQuestionnaireGUI::OnMediaLoaded)
END_EVENT_TABLE()

void wxQuestionnaireGUI::handleCBDataInput (int nest_level)
{
	vector<int32_t> data;
	UserInput user_input;
	//data.push_back(rbData_);
	stringstream s1;
	//s1 << rbData_;
	for (set<int32_t>::iterator it = cbData_.begin(); it != cbData_.end(); ++it) {
		//cout << " " << *it;
		data.push_back (*it);
		s1 << " " << (*it);
	}
	user_input.theUserResponse_ = user_response::UserEnteredData;
	user_input.questionResponseData_ = s1.str();
	AbstractRuntimeQuestion * q = last_question_visited;
	string err_mesg;
	bool valid_input = q->VerifyResponse(user_input.theUserResponse_, user_input.userNavigation_, err_mesg);
	if (valid_input) {
		if (user_input.theUserResponse_ == user_response::UserSavedData) {
			cerr  << "NOT YET DONE"
				<< __FILE__ << "," << __LINE__ << "," << __PRETTY_FUNCTION__
				<< endl
				<< "invoking callback_ui_input with UserSavedData" << endl;
			// this call will return really fast
			//  (if you consider io fast)
			//  but what I mean is we wont add much to the call stack
			callback_ui_input (user_input, q, theQuestionnaire_, nest_level + 1);
			//GetUserInput (callback_ui_input, q, theQuestionnaire);
			cout << "callback_ui_input has returned after UserSavedData" << endl;
		} else {
			cout << "reached here: "
				<< __PRETTY_FUNCTION__ << endl;
			callback_ui_input (user_input, q, theQuestionnaire_, nest_level + 1);
			cout << "callback_ui_input has returned"
				<< __PRETTY_FUNCTION__ << endl;
		}
		// move all this into callback_ui_input
		// case UserEnteredData
	} else {
		// we should be passing an error message too
		//GetUserInput (callback_ui_input, q, theQuestionnaire);
		// do nothing - the callback just continues to wait for data
	}


}

void wxQuestionnaireGUI::handleRBDataInput (int nest_level)
{
	//vector<int32_t> data;
	//data.push_back(rbData_);
	UserInput user_input;
	stringstream s1;
	s1 << rbData_;
	user_input.theUserResponse_ = user_response::UserEnteredData;
	user_input.questionResponseData_ = s1.str();
	AbstractRuntimeQuestion * q = last_question_visited;
	string err_mesg;
	bool valid_input = q->VerifyResponse(user_input.theUserResponse_, user_input.userNavigation_, err_mesg);
	if (valid_input) {
		if (user_input.theUserResponse_ == user_response::UserSavedData) {
			cerr  << "NOT YET DONE"
				<< __FILE__ << "," << __LINE__ << "," << __PRETTY_FUNCTION__
				<< endl
				<< "invoking callback_ui_input with UserSavedData" << endl;
			// this call will return really fast
			//  (if you consider io fast)
			//  but what I mean is we wont add much to the call stack
			callback_ui_input (user_input, q, theQuestionnaire_, nest_level + 1);
			//GetUserInput (callback_ui_input, q, theQuestionnaire);
			cout << "callback_ui_input has returned after UserSavedData" << endl;
		} else {
			cout << "reached here: "
				<< __PRETTY_FUNCTION__ << endl;
			callback_ui_input (user_input, q, theQuestionnaire_, nest_level + 1);
			cout << "callback_ui_input has returned"
				<< __PRETTY_FUNCTION__ << endl;
		}
		// move all this into callback_ui_input
		// case UserEnteredData
	} else {
		// we should be passing an error message too
		//GetUserInput (callback_ui_input, q, theQuestionnaire);
		// do nothing - the callback just continues to wait for data
	}

}

void wxQuestionnaireGUI::handlePrevNavigation(wxCommandEvent& WXUNUSED(event))
{
	cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
	UserInput user_input;
	user_input.userNavigation_ = NAVIGATE_PREVIOUS;
	user_input.theUserResponse_ = user_response::UserEnteredNavigation;
	callback_ui_input (user_input, last_question_visited, theQuestionnaire_, 1);
	cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
}

void wxQuestionnaireGUI::handleSave(wxCommandEvent& WXUNUSED(event))
{
	cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
	UserInput user_input;
	user_input.userNavigation_ = SAVE_DATA;
	user_input.theUserResponse_ = user_response::UserSavedData;
	callback_ui_input (user_input, last_question_visited, theQuestionnaire_, 1);
	cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
}

void wxQuestionnaireGUI::handleDataInput(wxCommandEvent& WXUNUSED(event))
{
	cout << "Enter: " << __PRETTY_FUNCTION__
		<< ", last_question_visited: " << last_question_visited
		<< endl;

	if (NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion *>(last_question_visited))
	{
		AbstractRuntimeQuestion * last_question_served = last_question_visited;
		vector<int32_t> data;
		bool isAnswered = false;
		cout << "returned back data from question: " << nq->questionName_ << endl;
		if (last_question_served->no_mpn == 1)
		{
			/*
			if (rbData_ != -1) {
				vector<int32_t> data;
				UserInput user_input;
				data.push_back(rbData_);
				stringstream s1;
				s1 << rbData_;
				user_input.theUserResponse_ = user_response::UserEnteredData;
				user_input.questionResponseData_ = s1.str();
				AbstractRuntimeQuestion * q = last_question_visited;
				string err_mesg;
				bool valid_input = q->VerifyResponse(user_input.theUserResponse_, user_input.userNavigation_, err_mesg);
				if (valid_input) {
					if (user_input.theUserResponse_ == user_response::UserSavedData) {
						cerr  << "NOT YET DONE"
							<< __FILE__ << "," << __LINE__ << "," << __PRETTY_FUNCTION__
							<< endl
							<< "invoking callback_ui_input with UserSavedData" << endl;
						// this call will return really fast
						//  (if you consider io fast)
						//  but what I mean is we wont add much to the call stack
						callback_ui_input (user_input, q, theQuestionnaire_);
						//GetUserInput (callback_ui_input, q, theQuestionnaire);
						cout << "callback_ui_input has returned after UserSavedData" << endl;
					} else {
						cout << "reached here: "
							<< __PRETTY_FUNCTION__ << endl;
						callback_ui_input (user_input, q, theQuestionnaire_);
						cout << "callback_ui_input has returned"
							<< __PRETTY_FUNCTION__ << endl;
					}
					// move all this into callback_ui_input
					// case UserEnteredData
				} else {
					// we should be passing an error message too
					//GetUserInput (callback_ui_input, q, theQuestionnaire);
					// do nothing - the callback just continues to wait for data
				}
			}
			*/
			handleRBDataInput(1);
		} else {
			handleCBDataInput(1);
		}
	} else if (VideoQuestion * vq = dynamic_cast<VideoQuestion *>(last_question_visited)) {
		AbstractRuntimeQuestion * last_question_served = last_question_visited;
		cout << __PRETTY_FUNCTION__ << "doing nothing : case VideoQuestion" << endl;
		UserInput user_input;
		user_input.theUserResponse_ = user_response::UserViewedVideo;
		cerr
			<< "Not call to verify - maybe we need to add a timer" << endl
			<< " to ensure user saw at least 30 secs of video etc" << endl
			<< endl;
		// we dont call verify - maybe later -
		callback_ui_input (user_input, last_question_served, theQuestionnaire_,  1);
	} else if (RangeQuestion *rq = dynamic_cast<RangeQuestion*>(last_question_visited) ) {
		cout << __PRETTY_FUNCTION__ << "Case RangeQuestion: " << endl;
		AbstractRuntimeQuestion * q = last_question_visited;
		string current_response ((txt_data_entry_line->GetValue()).utf8_str()  );
		cout << current_response << endl;
		if (current_response.size() > 0) {
			UserInput user_input;
#if 0
			if (current_response[0] == 'P') {
				user_input.userNavigation_ = NAVIGATE_PREVIOUS;
				user_input.theUserResponse_ = user_response::UserEnteredNavigation;
			} else if (current_response[0] == 'N') {
#endif /*  0 */

				// Why? - if current_response == empty then treat that as
				// UserEnteredNavigation (which should come in the else clause
				//                        of this if)
				//user_input.userNavigation_ = NAVIGATE_NEXT;
				//user_input.theUserResponse_ = user_response::UserEnteredNavigation;
				user_input.theUserResponse_ = user_response::UserEnteredData;
				user_input.questionResponseData_ = current_response;
#if 0
			} else if (current_response[0] == 'S') {
				user_input.userNavigation_ = SAVE_DATA;
				user_input.theUserResponse_ = user_response::UserSavedData;
				cout << "Got SAVE_DATA from user" << endl;
			} else  {
				user_input.theUserResponse_ = user_response::UserEnteredData;
				user_input.questionResponseData_ = current_response;
			}
#endif /*  0 */

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

			cout << "reached here: valid_input :" << valid_input
				<< "error message: " << err_mesg
				<<  endl;

			if (valid_input) {
				if (user_input.theUserResponse_ == user_response::UserSavedData) {
					cerr  << "NOT YET DONE"
						<< __FILE__ << "," << __LINE__ << "," << __PRETTY_FUNCTION__
						<< endl
						<< "invoking callback_ui_input with UserSavedData" << endl;
					// this call will return really fast
					//  (if you consider io fast)
					//  but what I mean is we wont add much to the call stack
					callback_ui_input (user_input, q, theQuestionnaire_, 1);
					//GetUserInput (callback_ui_input, q, theQuestionnaire);
					cout << "callback_ui_input has returned after UserSavedData" << endl;
				} else {
					cout << "reached here: "
						<< __PRETTY_FUNCTION__ << endl;
					callback_ui_input (user_input, q, theQuestionnaire_, 1);
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
				//GetUserInput (callback_ui_input, q, theQuestionnaire);
				// do nothing - the callback just continues to wait for data
			}

			/*
			else {
				// invalid entries
				cout << "invalid input" << endl;
				question_eval_loop (NORMAL_FLOW, NAVIGATE_NEXT,
						last_question_visited, 0, qnre);
				//goto ask_again;
			} */
		}

	}
	cout << "Exit: " << __PRETTY_FUNCTION__
		<< ", last_question_visited: " << last_question_visited
		<< endl;
	if (last_question_visited) {
		cout << "last_question_visited is not null, it is: "
			<< last_question_visited->questionName_
			<< endl;
	}
	cout << endl;
}

void wxQuestionnaireGUI::get_serial_no(wxCommandEvent& WXUNUSED(event))
{
	int l_ser_no = -1;
	cout << __PRETTY_FUNCTION__ << " was invoked" << endl;
	//const char * entry_text =(txt_ctrl_ser_no->GetValue()).utf8_str()  ;
	wxString wx_ser_no = (txt_ctrl_ser_no->GetValue());
	//string narrow_text ((txt_ctrl_ser_no->GetValue()).utf8_str()  );
	string narrow_text (wx_ser_no.utf8_str()  );
	cout << narrow_text << endl;
	//txt_ctrl_ser_no->GetValue();
	//wxTextEntryDialog * sr_no = new wxTextEntryDialog(this, wxT("Please enter a serial no"), wxT("Serial No"));
	//if (sr_no->ShowModal() == wxID_OK) {
	//	cout << (sr_no->GetValue()).utf8_str() << endl;
	//} else {
	//}

	if (narrow_text.length() == 0 || narrow_text.length() > 7)
	{
		//le_data_->setText("You have entered a very long serial number");
		cout << "You have entered a very long serial number" << endl;
	}
	else
	{
		l_ser_no = strtol (narrow_text.c_str(), 0, 10);
		if (l_ser_no > 0)
		{
			cerr << __PRETTY_FUNCTION__ << " hide serialNoEntry_ later" << endl;
			//gtk_widget_hide (serialNoEntry_);
			//qapp->return_ser_no(l_ser_no, qapp->theQuestionnaire_);
			//theQuestionnaire_ = make_questionnaire();
			wxString serial_status_info = wxString(wxT("Serial No: ")) + wx_ser_no;
			statusBar_->SetStatusText (serial_status_info, 1);
			wxCommandEvent dummy_evt;
			ClearSerialNoScreen(dummy_evt);
			//panel_sizer->Show(fgs);
			ShowQuestionScreen(dummy_evt);
			callback_get_ser_no_from_ui (l_ser_no, theQuestionnaire_, 1);
		} else {
			cout << "strtol failed: l_ser_no: " << l_ser_no << endl;
		}
	}

}

IMPLEMENT_APP(wxQuestionnaireApplication)



extern string qscript_stdout_fname;
extern FILE * qscript_stdout;

wxQuestionnaireGUI *wxGUI = 0;
bool wxQuestionnaireApplication::OnInit()
{
	wxGUI = new wxQuestionnaireGUI(wxT("QScript: Job Name"));
	//wxQuestionnaireGUI *wxGUI = new wxQuestionnaireGUI(wxT("wx QScript Questionnaire UI"));
	wxGUI->Show(true);
	qscript_stdout = fopen(qscript_stdout_fname.c_str(), "w");

	return true;
}

wxQuestionnaireGUI::wxQuestionnaireGUI (const wxString & title)
	: wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(800, 700)),
	  the_question (0), the_stubs(0), the_data_entry_line(0),
	  // m_radio(0),
	  m_sizerRadio(0),
	  panel_sizer(0), media_panel_sizer_(0),
	  rbData_(-1), prevRBValue_(-1),
	  // rboxWindow_(0),
	  m_pListBox(0),
	  mediactrl_(0)
{

	const int widths[] = { -1, 200 };
	statusBar_ = CreateStatusBar(2);
	SetStatusWidths(2, widths);
	panel = new wxPanel(this, -1);


	panel_sizer = new wxBoxSizer(wxHORIZONTAL);

	CreateQuestionScreen();
	CreateSerialNoScreen();
	CreateEndOfQnreScreen();
	panel->SetSizer(panel_sizer);

	//media_panel_sizer_ = new wxBoxSizer(wxVERTICAL);
	//media_panel_ ->SetSizer (media_panel_sizer_);
	//panel_sizer->Add (media_panel_);
	//media_panel_sizer_->Hide(media_panel_);

	Centre();
	theQuestionnaire_ = make_questionnaire();

	wxCommandEvent evt_dummy;
	ShowSerialNoScreen(evt_dummy);

}

// since main is started from the UI - this is not reqd
// instead put the functions in the OnInit function
#if 0
void setup_ui (int argc, char * argv[], /* int (* p_return_ser_no) (int), */ struct TheQuestionnaire * p_theQuestionnaire)
{

}
#endif /*  0 */


int32_t prompt_user_for_serial_no(
		int (* p_return_ser_no) (int, struct TheQuestionnaire *)
	)
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "Enter a serial no, 0 to exit" << endl;
#if 0
	int serial_no;
	cin >> serial_no;

	if (serial_no == 0) {
		cout << "exiting ..." << endl;
		exit(0);
	} else {
		p_return_ser_no (serial_no);
	}
	// unreachable code
#endif /*  0 */

	//gtkQuestionnaireApplication->get_serial_no_gtk(p_return_ser_no);
	//cerr 	<< __PRETTY_FUNCTION__ << ","
	//	<< __FILE__ << ","
	//	<< __LINE__ << ","
	//	<< " fix this return 100 - return the serial no from the UI"
	//	<< endl;

	return  100;
}

void GetUserInput (
	void (*callback_ui_input) (UserInput p_user_input, AbstractRuntimeQuestion * q,
		struct TheQuestionnaire * theQuestionnaire, int nest_level),
		AbstractRuntimeQuestion *q, struct TheQuestionnaire * theQuestionnaire, int nest_level)
{
	static int count = 0;
	cout << "Enter: " << __PRETTY_FUNCTION__ << ++count << endl;
	if (q->no_mpn == 1) {
		cout << " Question is single answer, please enter only 1 response." << endl;
	} else {
		cout << " Question accepts multiple answers." << endl;
	}
	string current_response;
	cout << "Enter Data>" << endl;
	if (count < 4) {
		//getline(cin, current_response);
	} else {
		return;
	}
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
			user_input.questionResponseData_ = current_response;
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
				callback_ui_input (user_input, q, theQuestionnaire, nest_level + 1);
				GetUserInput (callback_ui_input, q, theQuestionnaire,  nest_level + 1);
				cout << "callback_ui_input has returned after UserSavedData" << endl;
			} else {
				cout << "reached here: "
					<< __PRETTY_FUNCTION__ << endl;
				callback_ui_input (user_input, q, theQuestionnaire, nest_level + 1);
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
			GetUserInput (callback_ui_input, q, theQuestionnaire, nest_level + 1);
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
		GetUserInput (callback_ui_input, q, theQuestionnaire, nest_level + 1);
	}
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
			cout 	<< vec[i].code << " : " << vec[i].stub_text
				<< endl;
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



void stdout_eval (AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire,
	void (*callback_ui_input) (UserInput p_user_input, AbstractRuntimeQuestion * q,
		struct TheQuestionnaire * theQuestionnaire, int nest_level), int nest_level)
{
	if (q) {
		cout << __PRETTY_FUNCTION__
			<< ": nest_level: " << nest_level
			<< "questionName_: " << q->questionName_
			<< endl;
		ClearPreviousView ();
		vector <string> qno_and_qtxt = PrepareQuestionText (q);
		DisplayQuestionTextView (qno_and_qtxt);
		if (q->q_type != video) {
			PrepareStubs (q);
			DisplayStubs (q);
			DisplayCurrentAnswers (q);
		}
		//GetUserInput (callback_ui_input, q, theQuestionnaire);

		wxGUI->set_callback_ui_input (callback_ui_input);
		//gtkQuestionnaireApplication->ConstructQuestionForm (q
		//		//, gtkQuestionnaireApplication->this_users_session
		//		);

		wxGUI->ConstructQuestionForm( q );
		//GetUserInput (callback_ui_input, q, theQuestionnaire);
		//
	} else {

		wxGUI->ShowEndOfQnreScreen();
	}
}

void wxQuestionnaireGUI::ConstructQuestionForm( AbstractRuntimeQuestion *q )
{

	vector <string> question_text_vec = PrepareQuestionText (q);
	//the_question = new wxStaticText(panel, -1, wxT("Question No and Question Text"));
	DisplayQuestionTextView (question_text_vec);
	// Hack to Display Radio Buttons
	if (q->q_type == spn || q->q_type == mpn) {
		DisplayStubs (q);
	} else if (q->q_type == video) {
		DisplayVideo (q);
		//panel_sizer->Hide (end_of_qnre_sizer);
		//panel_sizer->Hide (fgs);
		//panel_sizer->Show (media_panel_);
		panel_sizer->Layout();
	}
	last_question_visited = q;

}


void wxQuestionnaireGUI::DisplayVideo (AbstractRuntimeQuestion * q)
{
	cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
	rbQnreCodeMap_.clear();
	rbQnreReverseCodeMap_.clear();
	ClearStubsArea();
	data_entry_and_navg_sizer->Hide(data_entry_line_sizer);
	VideoQuestion * vq = dynamic_cast <VideoQuestion*> (q);
	if (vq) {
		cout << " is a VideoQuestion" << endl;
#if 0
		if (mediactrl_) {
			//radio_box_sizer ->Detach (m_rListBox);
			panel_sizer ->Detach (mediactrl_);

			delete mediactrl_; mediactrl_ = 0;;
		}
#endif /* 0 */

		mediactrl_ = new wxMediaCtrl();
		bool bOK = mediactrl_->Create(panel, ID_MEDIACTRL, wxEmptyString,
						wxDefaultPosition, wxDefaultSize);
		media_panel_sizer_->Add(mediactrl_);
		//bool bOK = mediactrl_->Create(media_panel_, ID_MEDIACTRL, wxEmptyString,
		//				wxDefaultPosition, wxDefaultSize);
		mediactrl_->ShowPlayerControls(wxMEDIACTRLPLAYERCONTROLS_DEFAULT);
		//panel_sizer->Add (mediactrl_);
		//panel_sizer->Hide(fgs);
		//panel_sizer->Show(media_panel_);
		stubsRowSizer_->Show(media_panel_sizer_);
		stubsRowSizer_->Layout();

		wxString hard_coded_path =
			//wxString::FromUTF8("/home/nxd/Progs/wx/wx-media-ctrl/video-2012-04-01-13-36-59.mp4");
			//wxString::FromUTF8("/home/nxd/Progs/wx/wx-media-ctrl/video-2012-04-01-13-36-59.mp4");
			wxString::FromUTF8(vq->file_path.c_str());
		wxURI uripath(hard_coded_path);
		if( uripath.IsReference() ) {
			cout << "uripath IsReference" << endl;

			if (mediactrl_->Load (hard_coded_path)) {
				cout << "Successfully Loaded file" << endl;
			} else {
				cout << "Could not Load file" << endl;
			}
		} else {
			cout << "uripath NOT IsReference" << endl;

			if (mediactrl_->Load (uripath)) {
				cout << "Successfully Loaded file" << endl;
			} else {
				cout << "Could not Load file" << endl;
			}
		}
		panel_sizer->Layout();
	}
	cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
}

void wxQuestionnaireGUI::DisplayQuestionTextView (const vector <string> & qno_and_qtxt)
{
	cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
	std::stringstream question_text;
	for (int i=0; i < qno_and_qtxt.size(); ++i) {
		question_text << qno_and_qtxt[i];
	}
	//question_text << "dummy - to check for core dump";
	//questionTextLabel_ = gtk_label_new (question_text.str().c_str());
	////gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (top_half), questionTextLabel_);
	//cout << "topHalfVBox_: " << topHalfVBox_ << endl;
	//gtk_box_pack_start (GTK_BOX (topHalfVBox_), questionTextLabel_, TRUE, TRUE, 0);
	//gtk_widget_show (questionTextLabel_);
	//gtk_widget_show (top_half);
	the_question->SetLabel( wxString (question_text.str().c_str(), wxConvUTF8));
	cout << "EXIT: " << __PRETTY_FUNCTION__ << endl;
}

void wxQuestionnaireGUI::DisplayStubs (AbstractRuntimeQuestion * q)
{
	cout << __PRETTY_FUNCTION__ << endl;
	data_entry_and_navg_sizer->Show(data_entry_line_sizer);
	if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q))
	{
		// nxd: move both the below functions to a clear() api which we call from here
		rbData_ = -1; // clear the data basically
		cbData_.clear();
		if (q->no_mpn==1) {
			PrepareSingleCodedStubDisplay(nq);
		} else {
			PrepareMultiCodedStubDisplay (nq);
		}
	} else {
		cout << "=== Implement Display Range Question" << endl;
		//ClearPreviousView();
		ClearStubsArea();
	}
}

void wxQuestionnaireGUI::PrepareMultiCodedStubDisplay (NamedStubQuestion * nq)
{
	cout << __PRETTY_FUNCTION__
		<< " nq: " << nq->questionName_
		<< endl;
#if 0
	vector<stub_pair> & vec= (nq->nr_ptr->stubs);
	for (int i=0; i<vec.size(); ++i) {
		stringstream named_range_key;
		named_range_key << nq->nr_ptr->name << "_" << i;
		if (vec[i].mask) {
			GtkWidget * cb = gtk_check_button_new_with_label (vec[i].stub_text.c_str());
			GtkRadioButtonData * cb_data = new GtkRadioButtonData (vec[i].code, this);
			rbData_.push_back (cb_data);
			g_signal_connect (G_OBJECT (cb), "toggled",
				G_CALLBACK (toggle_rb_button_event), (gpointer) cb_data);
			gtk_widget_show (cb);
			gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), cb, TRUE, TRUE, 0);
			//!! Warning - the 2 statements below have to be in this order
			// and are not interchangeable
			vec_cb.push_back (cb);
			map_cb_code_index[vec_cb.size()-1] = vec[i].code;
		}
	}
#endif /*  0 */
    // check list box
	//ClearRadio();
	ClearStubsArea();
	/*
	static const wxChar *aszChoices[] =
    {
        _T("Zeroth"),
        _T("First"), _T("Second"), _T("Third"),
        _T("Fourth"), _T("Fifth"), _T("Sixth"),
        _T("Seventh"), _T("Eighth"), _T("Nineth")
    };
    */
	vector<stub_pair> & vec= (nq->nr_ptr->stubs);
	unsigned long count = vec.size();
	static const unsigned int DEFAULT_N_MAJOR_DIM = 2;
	unsigned long nmajorDim = DEFAULT_N_MAJOR_DIM;
	wxString *items = new wxString[count];

	//wxString *astrChoices = new wxString[WXSIZEOF(aszChoices)];
	//unsigned int ui;
	//for ( ui = 0; ui < WXSIZEOF(aszChoices); ui++ )
	//    astrChoices[ui] = aszChoices[ui];

	//rboxWindow_ = new wxScrolledWindow (panel, -1, wxDefaultPosition, wxSize(700,350));
	//rboxWindow_->SetScrollbars(20, 20, 50, 50);
	rbQnreCodeMap_.clear();
	rbQnreReverseCodeMap_.clear();
	vector <int32_t> answer_code_vec;
	vector <int32_t> answer_code_vec_pos;
	if (nq->isAnswered_) {
		for (set <int>::const_iterator cit = nq->input_data.begin(),
				END = nq->input_data.end();
				cit != END; ++cit) {
			answer_code_vec.push_back (*cit);
			cbData_.insert (*cit);
		}
	}
	cout << "answer_code_vec.size(): " << answer_code_vec.size() << endl;
	int actual_count = 0;
	for ( size_t i = 0; i < count; ++i ) {
		if (vec[i].mask) {
			stringstream s1;
			s1 << vec[i].code << ": " << vec[i].stub_text;
			//items[i] = wxString::FromUTF8(vec[i].stub_text.c_str());
			items[actual_count] = wxString::FromUTF8 (s1.str().c_str());
			rbQnreCodeMap_[actual_count] = vec[i].code;
			rbQnreReverseCodeMap_[vec[i].code] = actual_count;

			//items[i] = wxString::Format (_T("%d: %s"),
			//		vec[i].stub_text.c_str(),
			//		vec[i].code);
			++actual_count;
		}
	}

	if (nq->isAnswered_ ) {
		cout << "found answers at pos: ";
		for (int j=0; j< answer_code_vec.size(); ++j) {
			//if (vec[i].code == answer_code_vec[j]) {
			answer_code_vec_pos.push_back(rbQnreReverseCodeMap_[answer_code_vec[j]]);
			cout
				<< "| "
				<< answer_code_vec[j]
				<< " at  "
				<< answer_code_vec_pos[j];
			//}
		}
		cout << endl;
	}

	/*
	int flags = 0;
	m_pListBox = new wxCheckListBox
		(
		 rboxWindow_,               // parent
		 MultiAnswerCheckListBox,       // control id
		 wxDefaultPosition, //wxPoint(10, 10),       // listbox poistion
		 wxDefaultSize, //wxSize(400, 100),      // listbox size
		 count, // WXSIZEOF(aszChoices),  // number of strings
		 items, //astrChoices,           // array of strings
		 flags
		);
	*/

	int flags = 0;
	m_pListBox = new wxCheckListBox
		(
		 panel,               // parent
		 MultiAnswerCheckListBox,       // control id
		 wxDefaultPosition, //wxPoint(10, 10),       // listbox poistion
		 //wxDefaultSize,
		 wxSize(500, 350),      // listbox size
		 actual_count, // WXSIZEOF(aszChoices),  // number of strings
		 items, //astrChoices,           // array of strings
		 flags
		);

	cout << "answer_code_vec_pos.size(): " << answer_code_vec_pos.size() << endl;
	for (int i=0; i< answer_code_vec_pos.size(); ++i) {
		cout << " " << answer_code_vec_pos[i];
		m_pListBox -> Check (answer_code_vec_pos[i]);
	}
	cout << endl;

	delete [] items;

    // set grey background for every second entry
    //for ( ui = 0; ui < WXSIZEOF(aszChoices); ui += 2 ) {
    //    AdjustColour(ui);
    //}

	//m_pListBox->Check(2);
	//m_pListBox->Select(3);
	//check_box_sizer->Add (rboxWindow_);
	check_box_sizer->Add (m_pListBox);
	//stubsRowSizer_->Add(rboxWindow_, 1, wxGROW);
	fgs->Layout();
	panel_sizer->Layout();

}

void wxQuestionnaireGUI::ClearMediaArea()
{
	if (mediactrl_) {
		//radio_box_sizer ->Detach (m_rListBox);
		media_panel_sizer_ ->Detach (mediactrl_);
		delete mediactrl_; mediactrl_ = 0;;
	}
}

void wxQuestionnaireGUI::ClearStubsArea()
{
	txt_data_entry_line->Clear();
	ClearCheckList();
	ClearRadio();
	ClearMediaArea();
}

void wxQuestionnaireGUI::ClearCheckList()
{
	if (m_pListBox) {
		//if (rboxWindow_) {
		//	check_box_sizer->Detach (rboxWindow_);
		//}
		check_box_sizer->Detach (m_pListBox);
		delete m_pListBox; m_pListBox = 0;
	}
	//if (rboxWindow_) {
	//	delete rboxWindow_; rboxWindow_ = 0;
	//}
	// code to preserve previous values - do i really need this?
}

void wxQuestionnaireGUI::ClearRadio()
{
    // Later load prevRBValue_ from m_radio before deleting
	cout << __PRETTY_FUNCTION__ << "fix later m_radio to be changed to m_pListBox"
		<< endl;
#if 1
	int rbData_ = -1;
	if ( m_rListBox )
	{
		radio_box_sizer ->Detach (m_rListBox);
		delete m_rListBox; m_rListBox = 0;
	}
	else // first time creation, no old selection to preserve
	{
		rbData_ = -1;
		prevRBValue_ = -1;
	}

	//if (rboxWindow_) {
	//	delete rboxWindow_; rboxWindow_ = 0;
	//}
#endif /* 0 */
}

void wxQuestionnaireGUI::PrepareSingleCodedStubDisplay (NamedStubQuestion * nq)
{
	cout << __PRETTY_FUNCTION__ << endl;
	//ClearRadio();
	ClearStubsArea();



	// no of radio buttons
#if 1
	//unsigned long count = 12;
	vector<stub_pair> & vec= (nq->nr_ptr->stubs);
	unsigned long count = vec.size();
	static const unsigned int DEFAULT_N_MAJOR_DIM = 2;
	unsigned long nmajorDim = DEFAULT_N_MAJOR_DIM;

	wxString *items = new wxString[count];
	//wxString labelBtn = m_textLabelBtns->GetValue();
	//wxString labelBtn = wxT("Radio Button Label") ;
	//for ( size_t n = 0; n < count; n++ )
	//{
	//	//items[n] = wxString::Format(_T("Radio Button Label %lu"),
	//	//			    //labelBtn.c_str(), (unsigned long)n + 1);
	//	//			     (unsigned long)n + 1);

	//	items[n] = wxT("Radio Button Label Changed nxd ")
	//					     ;
	//}
	rbQnreCodeMap_.clear();
	int actual_count = 0;
	int answer_position = -1;
	int answer_code = -1 ;
	if (nq->isAnswered_) {
		answer_code = *(nq->input_data.begin());
		cout << "nq: " << nq->questionName_
			<< " currentResponse_: "
			<< answer_code
			<< endl;
		rbData_ = answer_code;
	}
	for ( size_t i = 0; i < count; ++i ) {
		if (vec[i].mask) {
			stringstream s1;
			s1 << "   " << vec[i].code << ": " << vec[i].stub_text;
			//items[i] = wxString::FromUTF8(vec[i].stub_text.c_str());
			items[actual_count] = wxString::FromUTF8 (s1.str().c_str());
			rbQnreCodeMap_[actual_count] = vec[i].code;
			if (nq->isAnswered_ &&  vec[i].code == answer_code) {
				answer_position = i;
			}
			//items[i] = wxString::Format (_T("%d: %s"),
			//		vec[i].stub_text.c_str(),
			//		vec[i].code);
			++actual_count;
		}
	}




	//int flags = m_chkVert->GetValue() ? wxRA_VERTICAL
	//int flags = true ? wxRA_VERTICAL : wxRA_HORIZONTAL;
	//int flags = wxRA_SPECIFY_COLS;
	//flags |= ms_defaultFlags;
	//
	/*
	rboxWindow_ = new wxScrolledWindow (panel, -1);
	rboxWindow_->SetScrollbars(20, 20, 50, 50);
	//rboxWindow_->EnableScrolling(true, true);

	m_radio = new wxRadioBox ( rboxWindow_, SingleAnswerRadioBox,
				wxT("Choose a single answer"),
				wxDefaultPosition, wxDefaultSize,
				count, items,
				nmajorDim,
				  wxRA_SPECIFY_COLS
				);
	*/


	int flags = wxLB_SINGLE;
	m_rListBox = new wxListBox
		(
		 panel,               // parent
		 SingleAnswerRadioBox,       // control id
		 wxDefaultPosition, //wxPoint(10, 10),       // listbox poistion
		 //wxDefaultSize,
		 wxSize(500, 350),      // listbox size
		 actual_count, // WXSIZEOF(aszChoices),  // number of strings
		 items, //astrChoices,           // array of strings
		 flags
		);
	m_rListBox -> SetSelection (answer_position);

	delete [] items;

	//wxSizer *sizerRight = new wxBoxSizer(wxHORIZONTAL);
	//sizerRight->SetMinSize(150, 0);
	//m_sizerRadio = sizerRight; // save it to modify it later
	//m_sizerRadio->Add(m_radio, 1, wxGROW);
	//m_sizerRadio->Layout();
	//the_stubs->SetLabel(wxT("New Stubs Text - should be visible now"));
	cout << "Updated New stubs text" << endl;
	//stubsRowSizer_->Add(m_radio, 1, wxGROW);
	//stubsRowSizer_->Add(rboxWindow_, 1, wxGROW);
	//radio_box_sizer->Add(rboxWindow_);
	radio_box_sizer->Add(m_rListBox, 1, wxGROW);
	//m_radio->Show(true);
	//stubsRowSizer_->Show(false);
	//stubsRowSizer_->Show(true);
	//this->Fit();
#endif /*  0 */
	//CreateSerialNoScreen();
	//CreateEndOfQnreScreen();
	//stubsRowSizer_->Layout();
	fgs->Layout();
	panel_sizer->Layout();
}


void wxQuestionnaireGUI::set_callback_ui_input (
			void (*p_callback_ui_input) (UserInput p_user_input, AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire, int nest_level)
			)
{
	callback_ui_input = p_callback_ui_input;
}


void wxQuestionnaireGUI::OnSingleAnswerToggle(wxCommandEvent& event)
{
	//int sel = m_radio->GetSelection();
	int event_sel = event.GetSelection();
	//cout << "sel = " << sel << endl;
	cout << "event_sel = " << event_sel << endl;
	cout << "selected code: " << rbQnreCodeMap_[event_sel]
	    << endl;
	prevRBValue_ = rbData_;
	rbData_ =  rbQnreCodeMap_[event_sel];
	stringstream s;
	s << rbData_;
	wxString my_wx_string(s.str().c_str(), wxConvUTF8);
	txt_data_entry_line->Clear();
	(*txt_data_entry_line) << my_wx_string;
	//wxUnusedVar(event_sel);

	//wxLogMessage(_T("Radiobox selection changed, now %d"), sel);

	//wxASSERT_MSG( sel == event_sel,
	//              _T("selection should be the same in event and radiobox") );

	//m_textCurSel->SetValue(wxString::Format(_T("%d"), sel));
}

/*
void wxQuestionnaireGUI::OnToggleSelection(wxCommandEvent& event)
{
    wxSizer *sizer = m_panel->GetSizer();
    sizer->Detach( m_pListBox );
    delete m_pListBox;
    CreateCheckListbox(event.IsChecked() ? wxLB_EXTENDED : 0);
    sizer->Insert(0, m_pListBox, 1, wxGROW | wxALL, 10);
    m_panel->Layout();
}
*/

void wxQuestionnaireGUI::OnCheckboxToggle(wxCommandEvent& event)
{
	unsigned int nItem = event.GetInt();

	wxLogStatus(this, wxT("item %d was %schecked"), nItem,
		      m_pListBox->IsChecked(nItem) ? wxT("") : wxT("un"));
	int code = rbQnreCodeMap_[nItem];
	if (m_pListBox->IsChecked(nItem)) {
		cbData_.insert (code);
	} else {
		cbData_.erase (code);
	}
	cout << "selected values are: " << endl;
	stringstream s;
	for (set<int32_t>::iterator it = cbData_.begin(); it != cbData_.end(); ++it) {
		cout << " " << *it;
		s << " " << *it;
	}
	cout << endl;
	wxString my_wx_string(s.str().c_str(), wxConvUTF8);
	txt_data_entry_line->Clear();
	(*txt_data_entry_line) << my_wx_string;

}



void wxQuestionnaireGUI::CreateSerialNoScreen()
{
	cout << __PRETTY_FUNCTION__ << endl;
	wxSizerFlags flagsNoExpand(0);
	flagsNoExpand.Border(wxALL,10);
	wxStaticText *enter_serial_no_label = new wxStaticText(panel, -1, wxT("Enter the Serial No: "));
	txt_ctrl_ser_no = new wxTextCtrl(panel, -1);
	serial_row_sizer = new wxBoxSizer(wxHORIZONTAL);
	serial_row_sizer->Add (enter_serial_no_label, flagsNoExpand);
	serial_row_sizer->Add (txt_ctrl_ser_no, flagsNoExpand);
	wxButton *button = new wxButton(panel, ID_BUTTON_SERIAL_NO, wxT("Start") /* , wxPoint(20, 20) */);
	serial_row_sizer->Add (button, flagsNoExpand);
	panel_sizer->Add (serial_row_sizer);
	panel_sizer->Hide (serial_row_sizer);
	//panel_sizer->Layout();
}


void wxQuestionnaireGUI::CreateEndOfQnreScreen()
{
	cout << __PRETTY_FUNCTION__ << endl;
	wxSizerFlags flagsNoExpand(0);
	flagsNoExpand.Border(wxALL,10);
	end_of_qnre_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton *button = new wxButton(panel, ID_BUTTON_PREVIOUS_QUESTION, wxT("Previous Question") );
	end_of_qnre_sizer->Add (button);
	button = new wxButton(panel, ID_BUTTON_SAVE, wxT("Save") );
	end_of_qnre_sizer->Add (button);
	button = new wxButton(panel, ID_BUTTON_CLOSE_QUESTIONNAIRE_WITHOUT_SAVING, wxT("Close Questionnaire without Saving") );
	end_of_qnre_sizer->Add (button);
	panel_sizer->Add (end_of_qnre_sizer);
	panel_sizer->Hide (end_of_qnre_sizer);
}


void wxQuestionnaireGUI::ClearSerialNoScreen(wxCommandEvent& WXUNUSED(event))
{
	panel_sizer->Hide(serial_row_sizer);
	panel_sizer->Layout();
}


void wxQuestionnaireGUI::ClearEndOfQnreScreen(wxCommandEvent& WXUNUSED(event))
{
	panel_sizer->Hide(end_of_qnre_sizer);
	panel_sizer->Layout();
}

void wxQuestionnaireGUI::CreateQuestionScreen()
{

	fgs = new wxFlexGridSizer(4, 1, 10, 25);
	the_question = new wxStaticText(panel, -1, wxT("Question No and Question Text"));
	the_stubs = new wxStaticText(panel, -1, wxT("Stubs for the question"));
	stubsRowSizer_ = new wxStaticBoxSizer(wxVERTICAL, panel, wxT(""));
	stubsRowSizer_->Add(the_stubs);
	check_box_sizer = new wxBoxSizer (wxHORIZONTAL);
	stubsRowSizer_->Add (check_box_sizer);
	radio_box_sizer = new wxBoxSizer (wxHORIZONTAL);
	stubsRowSizer_->Add (radio_box_sizer);
	data_entry_and_navg_sizer = new wxBoxSizer (wxVERTICAL);

	//media_panel_ = new wxPanel(panel, ID_MEDIA_PANEL);
	media_panel_sizer_ = new wxBoxSizer (wxHORIZONTAL);
	//media_panel_->SetSizer(media_panel_sizer_);
	stubsRowSizer_->Add (media_panel_sizer_);

	//wxBoxSizer * data_entry_line_sizer = new wxBoxSizer (wxVERTICAL);
	data_entry_line_sizer = new wxStaticBoxSizer (wxVERTICAL, panel, wxT("Data Entry"));
	//wxBoxSizer * navg_sizer = new wxBoxSizer (wxHORIZONTAL);
	wxBoxSizer * navg_sizer = new wxStaticBoxSizer (wxHORIZONTAL, panel, wxT("Navigation"));
	{
		//the_data_entry_line = new wxStaticText(panel, -1, wxT("Data entry (Coded Questions): "));
		//data_entry_line_sizer->Add (the_data_entry_line);

		txt_data_entry_line = new wxTextCtrl(panel, -1, wxEmptyString, wxDefaultPosition, wxSize(500, 25));
		//txt_data_entry_line = new wxTextCtrl(panel, -1, wxEmptyString, wxDefaultPosition, wx);
		data_entry_line_sizer->Add (txt_data_entry_line, 1, wxALL, 5);
		wxButton *prev = new wxButton(panel, ID_BUTTON_PREVIOUS_QUESTION, wxT("PreV") );
		wxButton *next = new wxButton(panel, ID_NEXT_BUTTON, wxT("NexT") );
		wxButton *save = new wxButton(panel, ID_BUTTON_SAVE, wxT("Save") );
		wxButton *q_no_save = new wxButton(panel, ID_BUTTON_SAVE, wxT("Quit") );
		navg_sizer->Add (prev,     1,  wxALL, 5);
		navg_sizer->Add (next,     1,  wxALL, 5);
		navg_sizer->Add (save,     1,  wxALL, 5);
		navg_sizer->Add (q_no_save,1,  wxALL, 5);
	}
	data_entry_and_navg_sizer->Add (data_entry_line_sizer, 1, wxEXPAND | wxALL, 5);
	data_entry_and_navg_sizer->Add (navg_sizer, 1, wxEXPAND | wxALL, 5);
	//stubsRowSizer_->Add (data_entry_and_navg_sizer);
	//stubsRowSizer_->Add (m_radio);

	// Serial line related stuff
	//wxStaticText *enter_serial_no_label = new wxStaticText(panel, -1, wxT("Enter the Serial: "));
	//txt_ctrl_ser_no = new wxTextCtrl(panel, -1);
	//wxBoxSizer *serial_row_sizer = new wxBoxSizer(wxHORIZONTAL);
	//serial_row_sizer->Add (enter_serial_no_label);
	//serial_row_sizer->Add (txt_ctrl_ser_no);

	//wxButton *button = new wxButton(panel, ID_BUTTON_SERIAL_NO, wxT("Start") /* , wxPoint(20, 20) */);
	//serial_row_sizer->Add (button);

	fgs->Add (the_question,  wxEXPAND);
	fgs->Add (stubsRowSizer_,  wxEXPAND, wxALL|wxGROW, 5);
	fgs->Add (data_entry_and_navg_sizer, wxEXPAND);
	//fgs->Add (serial_row_sizer,  wxEXPAND);




	fgs->AddGrowableRow (1, 1);
	fgs->AddGrowableCol (0, 1);
	panel_sizer->Add(fgs, 1, wxALL | wxEXPAND, 15);
	//fgs->Hide();
	panel_sizer->Hide(fgs);


}

void wxQuestionnaireGUI::ShowQuestionScreen(wxCommandEvent& WXUNUSED(event))
{
	panel_sizer->Show(fgs);
	panel_sizer->Layout();
}

void wxQuestionnaireGUI::ClearQuestionScreen()
{
	panel_sizer->Hide(fgs);
	panel_sizer->Layout();
}

void wxQuestionnaireGUI::ShowSerialNoScreen(wxCommandEvent& WXUNUSED(event))
{
	if (!serial_row_sizer) {
		CreateSerialNoScreen();
		panel_sizer->Add (serial_row_sizer);
	}
	panel_sizer->Show(serial_row_sizer);
	panel_sizer->Layout();
}


void wxQuestionnaireGUI::ShowEndOfQnreScreen()
{
	if (!end_of_qnre_sizer) {
		CreateSerialNoScreen();
		panel_sizer->Add (end_of_qnre_sizer);
	}
	ClearQuestionScreen();
	panel_sizer->Show(end_of_qnre_sizer);
	panel_sizer->Layout();
}


/*
void wxQuestionnaireApplication::LostFocus(wxCommandEvent& WXUNUSED(event))
{
	cout << __PRETTY_FUNCTION__ << endl;
	cout << "Textbox lost focus" << endl;
}
*/


void wxQuestionnaireGUI::OnMediaLoaded(wxMediaEvent& WXUNUSED(evt))
{
	mediactrl_->Play();
}

