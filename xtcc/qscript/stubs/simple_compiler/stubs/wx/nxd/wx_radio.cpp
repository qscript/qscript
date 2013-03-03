/*
 * =====================================================================================
 *
 *       Filename:  wx_radio.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 22 February 2013 09:42:34  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
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


using namespace std;

static const unsigned int DEFAULT_NUM_ENTRIES = 12;
static const unsigned int DEFAULT_MAJOR_DIM = 3;


class wxQuestionnaireApplication : public wxApp
{
public:
	virtual bool OnInit();

};

struct wxQuestionnaireGUI : public wxFrame
{
public:
	wxQuestionnaireGUI(const wxString& title);
	//void (*callback_ui_input) (UserInput p_user_input, AbstractQuestion * q, struct TheQuestionnaire * theQuestionnaire);
	//int (*return_ser_no) (int, struct TheQuestionnaire *);
	wxTextCtrl *txt_ctrl_ser_no;
	wxBoxSizer *stubs_row_sizer ;
	wxPanel *panel;
	wxFlexGridSizer *fgs ;
	static int ms_defaultFlags;


	
	void get_serial_no (wxCommandEvent& event);

	//struct TheQuestionnaire * theQuestionnaire_;
	//void ConstructQuestionForm( AbstractQuestion *q );
	//void DisplayQuestionTextView (const vector <string> & qno_and_qtxt);

	//void PrepareSingleCodedStubDisplay (NamedStubQuestion * nq);
	//void PrepareMultiCodedStubDisplay (NamedStubQuestion * nq);
	//void DisplayStubs (AbstractQuestion * q);


	wxStaticText *the_question ;
	wxStaticText *the_stubs ;
	wxStaticText *the_data_entry_line ;
	wxRadioBox *m_radio;
	wxSizer *m_sizerRadio;
	void OnUpdateUIUpdate(wxUpdateUIEvent& event);

	wxTextCtrl 	*m_textNumBtns,
			*m_textMajorDim,
			*m_textCurSel,
			*m_textSel,
			*m_textLabel,
			*m_textLabelBtns;

	wxCheckBox *m_chkVert;
	wxCheckBox *m_chkEnableItem;
	wxCheckBox *m_chkShowItem;
	wxRadioBox *m_radioDir;

	wxSizer *CreateSizerWithText(wxControl *control,
                                          wxWindowID id,
                                          wxTextCtrl **ppText);

	wxCheckBox * CreateCheckBoxAndAddToSizer(wxSizer *sizer,
                                                     const wxString& label,
                                                     wxWindowID id = wxID_ANY);
	wxSizer *CreateSizerWithTextAndButton(wxWindowID idBtn,
                                                   const wxString& label,
                                                   wxWindowID id,
                                                   wxTextCtrl **ppText);
	wxSizer *CreateSizerWithTextAndLabel(const wxString& label,
                                                  wxWindowID id,
                                                  wxTextCtrl **ppText);
	void Reset();
	void CreateContent();
	void CreateRadio();
	void old_create_ui();
private:
    DECLARE_EVENT_TABLE()


};

int wxQuestionnaireGUI::ms_defaultFlags = wxBORDER_DEFAULT;

enum MyWidgetID {
	ID_BUTTON_SERIAL_NO = wxID_HIGHEST,
	ID_STUBS_ROW ,
	RadioPage_Reset = wxID_HIGHEST,
	RadioPage_Update,
	RadioPage_Selection,
	RadioPage_Label,
	RadioPage_LabelBtn,
	RadioPage_EnableItem,
	RadioPage_ShowItem,
	RadioPage_Radio
};

enum
{
    RadioDir_Default,
    RadioDir_LtoR,
    RadioDir_TtoB
};



BEGIN_EVENT_TABLE(wxQuestionnaireGUI, wxFrame)
    EVT_BUTTON(ID_BUTTON_SERIAL_NO,  wxQuestionnaireGUI::get_serial_no)
    EVT_UPDATE_UI(RadioPage_Update, wxQuestionnaireGUI::OnUpdateUIUpdate)
END_EVENT_TABLE()


wxQuestionnaireGUI::wxQuestionnaireGUI (const wxString & title)
	: wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(800, 600)),
	  the_question (0), the_stubs(0), the_data_entry_line(0),
	  m_radio(0), m_sizerRadio(0)
{
	CreateContent();
}

void wxQuestionnaireGUI::old_create_ui()
{

	panel = new wxPanel(this, -1);



	unsigned long count = 12;
	//static const unsigned int DEFAULT_MAJOR_DIM = 2;
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
	int flags = false ? wxRA_VERTICAL
				      : wxRA_HORIZONTAL;
	//flags |= ms_defaultFlags;

	m_radio = new wxRadioBox (this, panel->GetId(),
				wxT("Radio Box Label"),
				wxDefaultPosition, wxDefaultSize,
				count, items,
				majorDim,
				flags);

	//wxSizer *sizerRight = new wxBoxSizer(wxHORIZONTAL);
	//sizerRight->SetMinSize(150, 0);
	//m_sizerRadio = sizerRight; // save it to modify it later
	//m_sizerRadio->Add(m_radio, 1, wxGROW);
	//m_sizerRadio->Layout();
	//the_stubs->SetLabel(wxT("New Stubs Text - should be visible now"));

	fgs = new wxFlexGridSizer(4, 1, 9, 25);

	wxSizer *sizerRow;
	sizerRow = CreateSizerWithTextAndLabel(_T("&Major dimension:"),
					   wxID_ANY,
					   &m_textMajorDim);
	fgs->Add (sizerRow, wxEXPAND);
	//sizerLeft->Add(sizerRow, 0, wxGROW | wxALL, 5);

	sizerRow = CreateSizerWithTextAndLabel(_T("&Number of buttons:"),
					   wxID_ANY,
					   &m_textNumBtns);
	fgs->Add (sizerRow, wxEXPAND);
	//sizerLeft->Add(sizerRow, 0, wxGROW | wxALL, 5);

	wxButton *btn = new wxButton(this, RadioPage_Update, _T("&Update"));
	fgs->Add (btn, wxEXPAND);
	//hbox->Add(btn, 0, wxALIGN_CENTRE_HORIZONTAL | wxALL, 5);
	//hbox->Add(m_radio, 1, wxGROW);
	fgs->Add (m_radio, wxEXPAND);

	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	hbox->Add(fgs, 1, wxALL | wxEXPAND, 15);

	hbox->Layout();



	panel->SetSizer(hbox);
	Centre();


}

IMPLEMENT_APP(wxQuestionnaireApplication)


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
#if 0
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
#endif /*  0 */

}


wxQuestionnaireGUI *wxGUI = 0;
bool wxQuestionnaireApplication::OnInit()
{
	wxGUI = new wxQuestionnaireGUI(wxT("wx QScript Questionnaire UI"));
	//wxQuestionnaireGUI *wxGUI = new wxQuestionnaireGUI(wxT("wx QScript Questionnaire UI"));
	wxGUI->Show(true);
	//qscript_stdout = fopen(qscript_stdout_fname.c_str(), "w");

	return true;
}


void wxQuestionnaireGUI::OnUpdateUIUpdate(wxUpdateUIEvent& event)
{
    unsigned long n;
    event.Enable( m_textNumBtns->GetValue().ToULong(&n) &&
                  m_textMajorDim->GetValue().ToULong(&n) );
    cout << "OnUpdateUIUpdate fired" << endl;
}



// create a sizer containing a label and a text ctrl
wxSizer *wxQuestionnaireGUI::CreateSizerWithTextAndLabel(const wxString& label,
                                                  wxWindowID id,
                                                  wxTextCtrl **ppText)
{
    return CreateSizerWithText(new wxStaticText(this, wxID_ANY, label),
        id, ppText);
}

// create a sizer containing a button and a text ctrl
wxSizer *wxQuestionnaireGUI::CreateSizerWithTextAndButton(wxWindowID idBtn,
                                                   const wxString& label,
                                                   wxWindowID id,
                                                   wxTextCtrl **ppText)
{
    return CreateSizerWithText(new wxButton(this, idBtn, label), id, ppText);
}

wxCheckBox *wxQuestionnaireGUI::CreateCheckBoxAndAddToSizer(wxSizer *sizer,
                                                     const wxString& label,
                                                     wxWindowID id)
{
    wxCheckBox *checkbox = new wxCheckBox(this, id, label);
    sizer->Add(checkbox, 0, wxLEFT | wxRIGHT, 5);
    sizer->Add(0, 2, 0, wxGROW); // spacer

    return checkbox;
}


wxSizer *wxQuestionnaireGUI::CreateSizerWithText(wxControl *control,
                                          wxWindowID id,
                                          wxTextCtrl **ppText)
{
    wxSizer *sizerRow = new wxBoxSizer(wxHORIZONTAL);
    wxTextCtrl *text = new wxTextCtrl(this, id, wxEmptyString,
        wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

    sizerRow->Add(control, 0, wxRIGHT | wxALIGN_CENTRE_VERTICAL, 5);
    sizerRow->Add(text, 1, wxLEFT | wxALIGN_CENTRE_VERTICAL, 5);

    if ( ppText )
        *ppText = text;

    return sizerRow;
}


void wxQuestionnaireGUI::Reset()
{
    m_textMajorDim->SetValue(wxString::Format(_T("%u"), DEFAULT_MAJOR_DIM));
    m_textNumBtns->SetValue(wxString::Format(_T("%u"), DEFAULT_NUM_ENTRIES));
    m_textLabel->SetValue(_T("I'm a radiobox"));
    m_textLabelBtns->SetValue(_T("item"));

    //m_chkVert->SetValue(false);
    //m_chkEnableItem->SetValue(true);
    //m_chkShowItem->SetValue(true);
    //m_radioDir->SetSelection(RadioDir_Default);
}


void wxQuestionnaireGUI::CreateContent()
{
    wxSizer *sizerTop = new wxBoxSizer(wxHORIZONTAL);

    // left pane
    wxStaticBox *box = new wxStaticBox(this, wxID_ANY, _T("&Set style"));

    wxSizer *sizerLeft = new wxStaticBoxSizer(box, wxVERTICAL);

    m_chkVert = CreateCheckBoxAndAddToSizer(sizerLeft, _T("&Vertical layout"));

    static const wxString layoutDir[] =
    {
        _T("default"),
        _T("left to right"),
        _T("top to bottom")
    };

    m_radioDir = new wxRadioBox(this, wxID_ANY, _T("Numbering:"),
                                wxDefaultPosition, wxDefaultSize,
                                WXSIZEOF(layoutDir), layoutDir,
                                1, wxRA_SPECIFY_COLS);
    sizerLeft->Add(m_radioDir, 0, wxGROW | wxALL, 5);

    // if it's not defined, we can't change the radiobox direction
#ifndef wxRA_LEFTTORIGHT
    m_radioDir->Disable();
#endif // wxRA_LEFTTORIGHT

    wxSizer *sizerRow;
    sizerRow = CreateSizerWithTextAndLabel(_T("&Major dimension:"),
                                           wxID_ANY,
                                           &m_textMajorDim);
    sizerLeft->Add(sizerRow, 0, wxGROW | wxALL, 5);

    sizerRow = CreateSizerWithTextAndLabel(_T("&Number of buttons:"),
                                           wxID_ANY,
                                           &m_textNumBtns);
    sizerLeft->Add(sizerRow, 0, wxGROW | wxALL, 5);

    wxButton *btn;
    btn = new wxButton(this, RadioPage_Update, _T("&Update"));
    sizerLeft->Add(btn, 0, wxALIGN_CENTRE_HORIZONTAL | wxALL, 5);

    sizerLeft->Add(5, 5, 0, wxGROW | wxALL, 5); // spacer

    btn = new wxButton(this, RadioPage_Reset, _T("&Reset"));
    sizerLeft->Add(btn, 0, wxALIGN_CENTRE_HORIZONTAL | wxALL, 15);

    // middle pane
    wxStaticBox *box2 = new wxStaticBox(this, wxID_ANY, _T("&Change parameters"));
    wxSizer *sizerMiddle = new wxStaticBoxSizer(box2, wxVERTICAL);

    sizerRow = CreateSizerWithTextAndLabel(_T("Current selection:"),
                                           wxID_ANY,
                                           &m_textCurSel);
    sizerMiddle->Add(sizerRow, 0, wxGROW | wxALL, 5);

    sizerRow = CreateSizerWithTextAndButton(RadioPage_Selection,
                                            _T("&Change selection:"),
                                           wxID_ANY,
                                           &m_textSel);
    sizerMiddle->Add(sizerRow, 0, wxGROW | wxALL, 5);

    sizerRow = CreateSizerWithTextAndButton(RadioPage_Label,
                                            _T("&Label for box:"),
                                            wxID_ANY,
                                            &m_textLabel);
    sizerMiddle->Add(sizerRow, 0, wxGROW | wxALL, 5);

    sizerRow = CreateSizerWithTextAndButton(RadioPage_LabelBtn,
                                            _T("&Label for buttons:"),
                                            wxID_ANY,
                                            &m_textLabelBtns);
    sizerMiddle->Add(sizerRow, 0, wxGROW | wxALL, 5);

    m_chkEnableItem = CreateCheckBoxAndAddToSizer(sizerMiddle,
                                                  _T("Disable &2nd item"),
                                                  RadioPage_EnableItem);
    m_chkShowItem = CreateCheckBoxAndAddToSizer(sizerMiddle,
                                                _T("Hide 2nd &item"),
                                                RadioPage_ShowItem);

    // right pane
    wxSizer *sizerRight = new wxBoxSizer(wxHORIZONTAL);
    sizerRight->SetMinSize(150, 0);
    m_sizerRadio = sizerRight; // save it to modify it later

    Reset();
    CreateRadio();

    // the 3 panes panes compose the window
    sizerTop->Add(sizerLeft, 0, wxGROW | (wxALL & ~wxLEFT), 10);
    sizerTop->Add(sizerMiddle, 1, wxGROW | wxALL, 10);
    sizerTop->Add(sizerRight, 0, wxGROW | (wxALL & ~wxRIGHT), 10);

    // final initializations
    SetSizer(sizerTop);
}


void wxQuestionnaireGUI::CreateRadio()
{
    int sel;
    if ( m_radio )
    {
        sel = m_radio->GetSelection();

        m_sizerRadio->Detach( m_radio );

        delete m_radio;
    }
    else // first time creation, no old selection to preserve
    {
        sel = -1;
    }

    unsigned long count;
    if ( !m_textNumBtns->GetValue().ToULong(&count) )
    {
        wxLogWarning(_T("Should have a valid number for number of items."));

        // fall back to default
        count = DEFAULT_NUM_ENTRIES;
    }

    unsigned long majorDim;
    if ( !m_textMajorDim->GetValue().ToULong(&majorDim) )
    {
        wxLogWarning(_T("Should have a valid major dimension number."));

        // fall back to default
        majorDim = DEFAULT_MAJOR_DIM;
    }

    wxString *items = new wxString[count];

    wxString labelBtn = m_textLabelBtns->GetValue();
    for ( size_t n = 0; n < count; n++ )
    {
        items[n] = wxString::Format(_T("%s %lu"),
                                    labelBtn.c_str(), (unsigned long)n + 1);
    }

    int flags = m_chkVert->GetValue() ? wxRA_VERTICAL
                                      : wxRA_HORIZONTAL;

    flags |= ms_defaultFlags;

#ifdef wxRA_LEFTTORIGHT
    switch ( m_radioDir->GetSelection() )
    {
        default:
            wxFAIL_MSG( _T("unexpected wxRadioBox layout direction") );
            // fall through

        case RadioDir_Default:
            break;

        case RadioDir_LtoR:
            flags |= wxRA_LEFTTORIGHT;
            break;

        case RadioDir_TtoB:
            flags |= wxRA_TOPTOBOTTOM;
            break;
    }
#endif // wxRA_LEFTTORIGHT

    m_radio = new wxRadioBox(this, RadioPage_Radio,
                             m_textLabel->GetValue(),
                             wxDefaultPosition, wxDefaultSize,
                             count, items,
                             majorDim,
                             flags);

    delete [] items;

    if ( sel >= 0 && (size_t)sel < count )
    {
        m_radio->SetSelection(sel);
    }

    m_sizerRadio->Add(m_radio, 1, wxGROW);
    m_sizerRadio->Layout();

    m_chkEnableItem->SetValue(true);
    m_chkEnableItem->SetValue(true);
}



/* 
wxCheckBox * wxQuestionnaireGUI::CreateCheckBoxAndAddToSizer(wxSizer *sizer,
                                                     const wxString& label,
                                                     wxWindowID id)
{
    wxCheckBox *checkbox = new wxCheckBox(this, id, label);
    sizer->Add(checkbox, 0, wxLEFT | wxRIGHT, 5);
    sizer->Add(0, 2, 0, wxGROW); // spacer

    return checkbox;
}
*/
