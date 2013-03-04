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
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <locale.h>
#include <libintl.h>
#include <map>

#include "question_gtk2_runtime.h"
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
	void (*callback_ui_input) (UserInput p_user_input, AbstractQuestion * q, struct TheQuestionnaire * theQuestionnaire);
	int (*return_ser_no) (int, struct TheQuestionnaire *);
	wxTextCtrl *txt_ctrl_ser_no;
	wxBoxSizer *stubs_row_sizer ;
	wxPanel *panel;
	wxFlexGridSizer *fgs ;
	wxBoxSizer *hbox ;
	
	void get_serial_no (wxCommandEvent& event);
	struct TheQuestionnaire * theQuestionnaire_;
	void ConstructQuestionForm( AbstractQuestion *q );
	void DisplayQuestionTextView (const vector <string> & qno_and_qtxt);

	void PrepareSingleCodedStubDisplay (NamedStubQuestion * nq);
	void PrepareMultiCodedStubDisplay (NamedStubQuestion * nq);
	void DisplayStubs (AbstractQuestion * q);


	wxStaticText *the_question ;
	wxStaticText *the_stubs ;
	wxStaticText *the_data_entry_line ;
	wxTextCtrl * txt_data_entry_line;
	wxRadioBox *m_radio;
	wxSizer *m_sizerRadio;

private:
    DECLARE_EVENT_TABLE()


};


enum MyWidgetID {
	ID_BUTTON_SERIAL_NO = wxID_HIGHEST,
	ID_STUBS_ROW = 102,
	SingleAnswerRadioBox
};


BEGIN_EVENT_TABLE(wxQuestionnaireGUI, wxFrame)
    EVT_BUTTON(ID_BUTTON_SERIAL_NO,  wxQuestionnaireGUI::get_serial_no)
END_EVENT_TABLE()

void wxQuestionnaireGUI::get_serial_no(wxCommandEvent& WXUNUSED(event))
{
	int l_ser_no = -1;
	cout << __PRETTY_FUNCTION__ << " was invoked" << endl;
	//const char * entry_text =(txt_ctrl_ser_no->GetValue()).utf8_str()  ;
	string narrow_text ((txt_ctrl_ser_no->GetValue()).utf8_str()  );
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
			theQuestionnaire_ = make_questionnaire();
			callback_get_ser_no_from_ui (l_ser_no, theQuestionnaire_);
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
	wxGUI = new wxQuestionnaireGUI(wxT("wx QScript Questionnaire UI"));
	//wxQuestionnaireGUI *wxGUI = new wxQuestionnaireGUI(wxT("wx QScript Questionnaire UI"));
	wxGUI->Show(true);
	qscript_stdout = fopen(qscript_stdout_fname.c_str(), "w");

	return true;
}

wxQuestionnaireGUI::wxQuestionnaireGUI (const wxString & title)
	: wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(800, 600)),
	  the_question (0), the_stubs(0), the_data_entry_line(0),
	  m_radio(0), m_sizerRadio(0), hbox(0)
{
	panel = new wxPanel(this, -1);


	hbox = new wxBoxSizer(wxHORIZONTAL);

#if 1
	fgs = new wxFlexGridSizer(4, 1, 9, 25);

	the_question = new wxStaticText(panel, -1, wxT("Question No and Question Text"));
	the_stubs = new wxStaticText(panel, -1, wxT("Stubs for the question"));
	stubs_row_sizer = new wxBoxSizer(wxHORIZONTAL|wxVERTICAL);
	stubs_row_sizer->Add(the_stubs);

	// ============ RADIO BOX CODE : TEST TO SEE IF IT APPEARS ===============
	unsigned long count = 12;
	static const unsigned int DEFAULT_MAJOR_DIM = 2;
	unsigned long majorDim = DEFAULT_MAJOR_DIM;

	wxString *items = new wxString[count];
	//wxString labelBtn = m_textLabelBtns->GetValue();
	wxString labelBtn = wxT("Radio Button Label") ;
	for ( size_t n = 0; n < count; n++ )
	{
		//items[n] = wxString::Format(_T("Radio Button Label %lu"),
		//			    //labelBtn.c_str(), (unsigned long)n + 1);
		//			     (unsigned long)n + 1);

		items[n] = wxT("Radio Button Label ")
						     ;
	}

	//int flags = m_chkVert->GetValue() ? wxRA_VERTICAL
	int flags = true ? wxRA_VERTICAL
				      : wxRA_HORIZONTAL;


	m_radio = new wxRadioBox (panel, SingleAnswerRadioBox,
				wxT("Radio Box Label"),
				wxDefaultPosition, wxDefaultSize,
				count, items,
				majorDim,
				flags);
	// ======== RADIO BOX CODE: END =============


	the_data_entry_line = new wxStaticText(panel, -1, wxT("Data entry - line"));
	txt_data_entry_line = new wxTextCtrl(panel, -1);
	stubs_row_sizer->Add (txt_data_entry_line);
	stubs_row_sizer->Add (m_radio);

	// Serial line related stuff
	wxStaticText *enter_serial_no_label = new wxStaticText(panel, -1, wxT("Enter the Serial: "));
	txt_ctrl_ser_no = new wxTextCtrl(panel, -1);
	wxBoxSizer *serial_row_sizer = new wxBoxSizer(wxHORIZONTAL);
	serial_row_sizer->Add (enter_serial_no_label);
	serial_row_sizer->Add (txt_ctrl_ser_no);

	wxButton *button = new wxButton(panel, ID_BUTTON_SERIAL_NO, wxT("Start") /* , wxPoint(20, 20) */);
	serial_row_sizer->Add (button);

	fgs->Add (the_question,  wxEXPAND);
	fgs->Add (stubs_row_sizer,  wxEXPAND);
	fgs->Add (the_data_entry_line,  wxEXPAND);
	fgs->Add (serial_row_sizer,  wxEXPAND);




	fgs->AddGrowableRow (1, 1);
	fgs->AddGrowableCol (0, 1);
	hbox->Add(fgs, 1, wxALL | wxEXPAND, 15);
#endif /*  0 */

#if 0
wxFlexGridSizer *fgs = new wxFlexGridSizer(3, 2, 9, 25);

  wxStaticText *thetitle = new wxStaticText(panel, -1, wxT("Title"));
  wxStaticText *author = new wxStaticText(panel, -1, wxT("Author"));
  wxStaticText *review = new wxStaticText(panel, -1, wxT("Review"));

  wxTextCtrl *tc1 = new wxTextCtrl(panel, -1);
  wxTextCtrl *tc2 = new wxTextCtrl(panel, -1);
  wxTextCtrl *tc3 = new wxTextCtrl(panel, -1, wxT(""),
      wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE);

  fgs->Add(thetitle);
  fgs->Add(tc1, 1, wxEXPAND);
  fgs->Add(author);
  fgs->Add(tc2, 1, wxEXPAND);
  fgs->Add(review, 1, wxEXPAND);
  fgs->Add(tc3, 1, wxEXPAND);

  fgs->AddGrowableRow(2, 1);
  fgs->AddGrowableCol(1, 1);

  hbox->Add(fgs, 1, wxALL | wxEXPAND, 15);
#endif /*  0 */
	panel->SetSizer(hbox);
	Centre();

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
	void (*callback_ui_input) (UserInput p_user_input, AbstractQuestion * q,
		struct TheQuestionnaire * theQuestionnaire),
		AbstractQuestion *q, struct TheQuestionnaire * theQuestionnaire)
{
	static int count = 0;
	cout << __PRETTY_FUNCTION__ << ++count << endl;
	if (q->no_mpn == 1) {
		cout << " Question is single answer, please enter only 1 response." << endl;
	} else {
		cout << " Question accepts multiple answers." << endl;
	}
	string current_response;
	cout << "Enter Data>" << endl;
	if (count < 4) {
		getline(cin, current_response);
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
				callback_ui_input (user_input, q, theQuestionnaire);
				GetUserInput (callback_ui_input, q, theQuestionnaire);
				cout << "callback_ui_input has returned after UserSavedData" << endl;
			} else {
				cout << "reached here: "
					<< __PRETTY_FUNCTION__ << endl;
				callback_ui_input (user_input, q, theQuestionnaire);
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
			GetUserInput (callback_ui_input, q, theQuestionnaire);
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
		GetUserInput (callback_ui_input, q, theQuestionnaire);
	}
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

void PrepareStubs (AbstractQuestion *q)
{

}

void DisplayStubs (AbstractQuestion *q)
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


void DisplayCurrentAnswers (AbstractQuestion * q)
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



void stdout_eval (AbstractQuestion * q, struct TheQuestionnaire * theQuestionnaire,
	void (*callback_ui_input) (UserInput p_user_input, AbstractQuestion * q, struct TheQuestionnaire * theQuestionnaire))
{
	cout << __PRETTY_FUNCTION__ << endl;
	ClearPreviousView ();
	vector <string> qno_and_qtxt = PrepareQuestionText (q);
	DisplayQuestionTextView (qno_and_qtxt);
	PrepareStubs (q);
	DisplayStubs (q);
	DisplayCurrentAnswers (q);
	//GetUserInput (callback_ui_input, q, theQuestionnaire);

	//gtkQuestionnaireApplication->set_callback_ui_input (callback_ui_input);
	//gtkQuestionnaireApplication->ConstructQuestionForm (q
	//		//, gtkQuestionnaireApplication->this_users_session
	//		);

	wxGUI->ConstructQuestionForm( q );
	GetUserInput (callback_ui_input, q, theQuestionnaire);
}

void wxQuestionnaireGUI::ConstructQuestionForm( AbstractQuestion *q )
{

	vector <string> question_text_vec = PrepareQuestionText (q);
	//the_question = new wxStaticText(panel, -1, wxT("Question No and Question Text"));
	DisplayQuestionTextView (question_text_vec);		
	// Hack to Display Radio Buttons
	DisplayStubs (q);

}

void wxQuestionnaireGUI::DisplayQuestionTextView (const vector <string> & qno_and_qtxt)
{
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
	cout << "EXIT: " << __PRETTY_FUNCTION__;
}

void wxQuestionnaireGUI::DisplayStubs (AbstractQuestion * q)
{
	cout << __PRETTY_FUNCTION__ << endl;
	if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q))
	{
		if (q->no_mpn==1)
		{
			PrepareSingleCodedStubDisplay(nq);
		} else {
			PrepareMultiCodedStubDisplay (nq);
		}
	} else {
		cout << "Implement Display Range Question" << endl;
	}
}

void wxQuestionnaireGUI::PrepareMultiCodedStubDisplay (NamedStubQuestion * nq)
{
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
}

void wxQuestionnaireGUI::PrepareSingleCodedStubDisplay (NamedStubQuestion * nq)
{
	cout << __PRETTY_FUNCTION__ << endl;
	int sel = -1;
	if ( m_radio )
	{
		sel = m_radio->GetSelection();
		//m_sizerRadio->Detach( m_radio );
		stubs_row_sizer->Detach (m_radio);
		delete m_radio;
		m_radio = 0;
	}
	else // first time creation, no old selection to preserve
	{
		sel = -1;
	}
	// no of radio buttons
#if 1
	unsigned long count = 12;
	static const unsigned int DEFAULT_MAJOR_DIM = 2;
	unsigned long majorDim = DEFAULT_MAJOR_DIM;

	wxString *items = new wxString[count];
	//wxString labelBtn = m_textLabelBtns->GetValue();
	wxString labelBtn = wxT("Radio Button Label") ;
	for ( size_t n = 0; n < count; n++ )
	{
		//items[n] = wxString::Format(_T("Radio Button Label %lu"),
		//			    //labelBtn.c_str(), (unsigned long)n + 1);
		//			     (unsigned long)n + 1);

		items[n] = wxT("Radio Button Label Changed nxd ")
						     ;
	}

	//int flags = m_chkVert->GetValue() ? wxRA_VERTICAL
	int flags = true ? wxRA_VERTICAL
				      : wxRA_HORIZONTAL;

	//flags |= ms_defaultFlags;

	m_radio = new wxRadioBox (panel, SingleAnswerRadioBox,
				wxT("Radio Box Label nxd"),
				wxDefaultPosition, wxDefaultSize,
				count, items,
				majorDim,
				flags);

	//wxSizer *sizerRight = new wxBoxSizer(wxHORIZONTAL);
	//sizerRight->SetMinSize(150, 0);
	//m_sizerRadio = sizerRight; // save it to modify it later
	//m_sizerRadio->Add(m_radio, 1, wxGROW);
	//m_sizerRadio->Layout();
	the_stubs->SetLabel(wxT("New Stubs Text - should be visible now"));
	cout << "Updated New stubs text" << endl;
	stubs_row_sizer->Add(m_radio, 1, wxGROW);
	m_radio->Show(true);
	stubs_row_sizer->Show(false);
	stubs_row_sizer->Show(true);
	this->Fit();
#endif /*  0 */
	stubs_row_sizer->Layout();
	fgs->Layout();
	hbox->Layout();
}

