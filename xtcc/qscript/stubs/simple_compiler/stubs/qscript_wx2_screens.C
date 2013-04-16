// Neil Xavier D'Souza
// 2013
// GPL V2
//
// This file is for my GUI screens, without the other distractions.
//
// Objectives:
//    1. Function to create screen to capture serial no
//    2. Function to clear screen after capturing serial no
//    3. Function to display End of Qnre screen
//    4. Mock up function to Display Question screen : because they are already implemented in the runtime
//    5. Mock up function to Clear Question screen   :
#include <wx/wx.h>
#include <iostream>
#include <string>
#include <cstdlib>

using std::cout;
using std::endl;
using std::cerr;
using std::string;

class ScreenApp: public wxApp
{
public:
    bool OnInit();
};

class ScreenUI : public wxFrame
{
public:
	ScreenUI(wxFrame *frame, const wxChar *title);
	wxPanel *panel;
	wxBoxSizer *panel_sizer;
	wxStatusBar * statusBar_;
	// related to serial no:
	wxTextCtrl * txt_ctrl_ser_no;
	wxBoxSizer *serial_row_sizer;
	// related to testing the various pages
	wxButton * show_serial_page  ;
	wxButton * clear_serial_page ;
	wxButton * show_end_page     ;
	wxButton * clear_end_page    ;

	void ShowSerialNoScreen(wxCommandEvent& WXUNUSED(event));
	void ClearSerialNoScreen();
	void ShowEndOfQnreScreen();
	void ClearEndOfQnreScreen();

	void get_serial_no (wxCommandEvent& event);
private:
    DECLARE_EVENT_TABLE()
};


enum MyWidgetID {
	ID_BUTTON_SERIAL_NO = wxID_HIGHEST,
	ID_STUBS_ROW,
	ID_NEXT_BUTTON,
	SingleAnswerRadioBox,
	MultiAnswerCheckListBox,
	ID_SHOW_SERIAL_PAGE_BUTTON,
	ID_CLEAR_PAGE_BUTTON,
	ID_SHOW_END_PAGE_BUTTON,
	ID_CLEAR_END_PAGE_BUTTON
};

BEGIN_EVENT_TABLE(ScreenUI, wxFrame)
	EVT_BUTTON(ID_BUTTON_SERIAL_NO,  ScreenUI::get_serial_no)
	//EVT_BUTTON(ID_NEXT_BUTTON,  wxQuestionnaireGUI::handleDataInput)
	//EVT_RADIOBOX(SingleAnswerRadioBox, wxQuestionnaireGUI::OnRadioBox)
	//EVT_CHECKLISTBOX(MultiAnswerCheckListBox, wxQuestionnaireGUI::OnCheckboxToggle)
	//
	EVT_BUTTON(ID_SHOW_SERIAL_PAGE_BUTTON, ScreenUI::ShowSerialNoScreen)
	//EVT_BUTTON(ID_CLEAR_PAGE_BUTTON, );
	//EVT_BUTTON(ID_SHOW_END_PAGE_BUTTON,  );
	//EVT_BUTTON(ID_CLEAR_END_PAGE_BUTTON,  );
END_EVENT_TABLE()


ScreenUI::ScreenUI(wxFrame *frame,
				const wxChar *title)
        : wxFrame(frame, wxID_ANY, title,
			wxDefaultPosition, wxSize(640,480))
{
	const int widths[] = { -1, 200 };
	statusBar_ = CreateStatusBar(2);
	SetStatusWidths(2, widths);
	panel = new wxPanel(this, -1);

	wxBoxSizer * button_sizer = new wxBoxSizer (wxHORIZONTAL);
	{
		wxSizerFlags flagsNoExpand(0);
		flagsNoExpand.Border(wxALL,10);
		show_serial_page  = new wxButton(panel, ID_SHOW_SERIAL_PAGE_BUTTON, wxT("Show Serial No Page") );
		clear_serial_page = new wxButton(panel, ID_CLEAR_PAGE_BUTTON, wxT("Clear Serial No Page") );
		show_end_page     = new wxButton(panel, ID_SHOW_END_PAGE_BUTTON, wxT("Show End Page") );
		clear_end_page    = new wxButton(panel, ID_CLEAR_END_PAGE_BUTTON, wxT("Clear End Page") );
		button_sizer->Add (show_serial_page, flagsNoExpand);
		button_sizer->Add (clear_serial_page, flagsNoExpand);
		button_sizer->Add (show_end_page, flagsNoExpand);
		button_sizer->Add (clear_end_page, flagsNoExpand);
		button_sizer->AddStretchSpacer();
		button_sizer->ComputeFittingClientSize(this);
	}
	wxBoxSizer * test_sizer = new wxBoxSizer (wxVERTICAL);
	test_sizer->Add (button_sizer);


	panel_sizer = new wxBoxSizer(wxVERTICAL);
	panel_sizer->Add (test_sizer);
	panel->SetSizer(panel_sizer);
	panel_sizer->ComputeFittingClientSize(this);
	//panel_sizer->Fit(this);
	//ShowSerialNoScreen(wxCommandEvent& WXUNUSED(event));
	Show(true);
}

// init our app: create windows
bool ScreenApp::OnInit(void)
{
	ScreenUI *pFrame = new ScreenUI
				    (
				     NULL,
				     _T("wxWidgets Screens for QScript")
				    );
	SetTopWindow(pFrame);

	return true;
}

void ScreenUI::ShowSerialNoScreen(wxCommandEvent& WXUNUSED(event))
{
	wxSizerFlags flagsNoExpand(0);
	flagsNoExpand.Border(wxALL,10);
	wxStaticText *enter_serial_no_label = new wxStaticText(panel, -1, wxT("Enter the Serial No: "));
	txt_ctrl_ser_no = new wxTextCtrl(panel, -1);
	wxBoxSizer *serial_row_sizer = new wxBoxSizer(wxHORIZONTAL);
	serial_row_sizer->Add (enter_serial_no_label, flagsNoExpand);
	serial_row_sizer->Add (txt_ctrl_ser_no, flagsNoExpand);
	wxButton *button = new wxButton(panel, ID_BUTTON_SERIAL_NO, wxT("Start") /* , wxPoint(20, 20) */);
	serial_row_sizer->Add (button, flagsNoExpand);
	panel_sizer->Add (serial_row_sizer);
	panel_sizer->Layout();
}


void ScreenUI::get_serial_no(wxCommandEvent& WXUNUSED(event))
{
	int l_ser_no = -1;
	cout << __PRETTY_FUNCTION__ << " was invoked" << endl;
	//const char * entry_text =(txt_ctrl_ser_no->GetValue()).utf8_str()  ;
	wxString wx_ser_no = (txt_ctrl_ser_no->GetValue());
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
			//callback_get_ser_no_from_ui (l_ser_no, theQuestionnaire_);
			wxString serial_status_info = wxString(wxT("Serial No: ")) + wx_ser_no;
			statusBar_->SetStatusText (serial_status_info, 1);
		} else {
			cout << "strtol failed: l_ser_no: " << l_ser_no << endl;
		}
	}

}


IMPLEMENT_APP(ScreenApp)

