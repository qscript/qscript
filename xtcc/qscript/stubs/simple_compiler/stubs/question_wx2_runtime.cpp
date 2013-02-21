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
	
	void get_serial_no (wxCommandEvent& event);

private:
    DECLARE_EVENT_TABLE()


};


enum MyWidgetID {
	ID_BUTTON_SERIAL_NO = 101
};


BEGIN_EVENT_TABLE(wxQuestionnaireGUI, wxFrame)
    EVT_BUTTON(ID_BUTTON_SERIAL_NO,  wxQuestionnaireGUI::get_serial_no)
END_EVENT_TABLE()

void wxQuestionnaireGUI::get_serial_no(wxCommandEvent& WXUNUSED(event))
{
	cout << __PRETTY_FUNCTION__ << " was invoked" << endl;
	cout << (txt_ctrl_ser_no->GetValue()).utf8_str() << endl;
	txt_ctrl_ser_no->GetValue();
	//wxTextEntryDialog * sr_no = new wxTextEntryDialog(this, wxT("Please enter a serial no"), wxT("Serial No"));
	//if (sr_no->ShowModal() == wxID_OK) {
	//	cout << (sr_no->GetValue()).utf8_str() << endl;
	//} else {
	//}

}

IMPLEMENT_APP(wxQuestionnaireApplication)




bool wxQuestionnaireApplication::OnInit()
{

    wxQuestionnaireGUI *wxGUI = new wxQuestionnaireGUI(wxT("wx QScript Questionnaire UI"));
    wxGUI->Show(true);

    return true;
}

wxQuestionnaireGUI::wxQuestionnaireGUI (const wxString & title)
    : wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(800, 600))
{
	wxPanel *panel = new wxPanel(this, -1);


	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

#if 1
	wxFlexGridSizer *fgs = new wxFlexGridSizer(4, 1, 9, 25);

	wxStaticText *the_question = new wxStaticText(panel, -1, wxT("Question No and Question Text"));
	wxStaticText *the_stubs = new wxStaticText(panel, -1, wxT("Stubs for the question"));
	wxStaticText *the_data_entry_line = new wxStaticText(panel, -1, wxT("Data entry - line"));

	// Serial line related stuff
	wxStaticText *enter_serial_no_label = new wxStaticText(panel, -1, wxT("Enter the Serial: "));
	txt_ctrl_ser_no = new wxTextCtrl(panel, -1);
	wxBoxSizer *serial_row_sizer = new wxBoxSizer(wxHORIZONTAL);
	serial_row_sizer->Add (enter_serial_no_label);
	serial_row_sizer->Add (txt_ctrl_ser_no);

	wxButton *button = new wxButton(panel, ID_BUTTON_SERIAL_NO, wxT("Start") /* , wxPoint(20, 20) */);
	serial_row_sizer->Add (button);

	fgs->Add (the_question,  wxEXPAND);
	fgs->Add (the_stubs,  wxEXPAND);
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
