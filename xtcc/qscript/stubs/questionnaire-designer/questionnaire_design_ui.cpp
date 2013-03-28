/*
 * =====================================================================================
 *
 *       Filename:  questionnaire_design_ui.cpp
 *
 *    Description: The beginnings of the Questionnaire design interface
 *
 *        Version:  1.0
 *       Revision:  none
 *
 *         Author:  Neil Xavier D'Souza
 *
 * =====================================================================================
 */


#include <wx/wx.h>
#include <wx/grid.h>
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

class MyGridCellAttrProvider : public wxGridCellAttrProvider
{
public:
    MyGridCellAttrProvider();
    virtual ~MyGridCellAttrProvider();

    virtual wxGridCellAttr *GetAttr(int row, int col,
                                    wxGridCellAttr::wxAttrKind  kind) const;

private:
    wxGridCellAttr *m_attrForOddRows;
};

// ----------------------------------------------------------------------------
// MyGridCellAttrProvider
// ----------------------------------------------------------------------------

MyGridCellAttrProvider::MyGridCellAttrProvider()
{
    m_attrForOddRows = new wxGridCellAttr;
    m_attrForOddRows->SetBackgroundColour(*wxLIGHT_GREY);
}

MyGridCellAttrProvider::~MyGridCellAttrProvider()
{
    m_attrForOddRows->DecRef();
}

wxGridCellAttr *MyGridCellAttrProvider::GetAttr(int row, int col,
                           wxGridCellAttr::wxAttrKind  kind /* = wxGridCellAttr::Any */) const
{
    wxGridCellAttr *attr = wxGridCellAttrProvider::GetAttr(row, col, kind);

    if ( row % 2 )
    {
        if ( !attr )
        {
            attr = m_attrForOddRows;
            attr->IncRef();
        }
        else
        {
            if ( !attr->HasBackgroundColour() )
            {
                wxGridCellAttr *attrNew = attr->Clone();
                attr->DecRef();
                attr = attrNew;
                attr->SetBackgroundColour(*wxLIGHT_GREY);
            }
        }
    }

    return attr;
}


class StubViewGridTable : public wxGridTableBase
{
public:
    StubViewGridTable(){};

    virtual int GetNumberRows();
    virtual int GetNumberCols();
    virtual bool IsEmptyCell( int row, int col );
    virtual wxString GetValue( int row, int col );
    virtual void SetValue( int row, int col, const wxString& value );

    virtual wxString GetColLabelValue( int col );

    virtual wxString GetTypeName( int row, int col );
    virtual bool CanGetValueAs( int row, int col, const wxString& typeName );
    virtual bool CanSetValueAs( int row, int col, const wxString& typeName );

    virtual long GetValueAsLong( int row, int col );
    virtual bool GetValueAsBool( int row, int col );

    virtual void SetValueAsLong( int row, int col, long value );
    virtual void SetValueAsBool( int row, int col, bool value );
};


struct wxQuestionnaireDesignerGUI : public wxFrame
{
public:
	wxQuestionnaireDesignerGUI(const wxString& title);
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

	// new GUI Design Widgets go here
	wxStaticBox *stub_box_ ;
	wxStaticBox *question_box_ ;
	wxStaticBox *named_attribute_box_ ;
	wxSizer *stub_box_container_sizer_;
	//wxSizer *stub_sizer_;
	wxSizer *question_sizer_;
	wxSizer *named_attribute_sizer_;
	wxTextCtrl * stub_name_tc_;
	wxTextCtrl * stub_text_tc;
	wxTextCtrl * stub_code_tc;
	//wxListBox * stub_lbox;
	//wxListBox * code_lbox;
	wxGrid * stub_view_grid_;


	wxSizer *CreateSizerWithText(wxControl *control,
                                          wxWindowID id,
                                          wxTextCtrl **ppText);

	void AddtoSizer_LabelAndText(
					wxSizer * sizer,
					const wxString& label_str,
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
	void NewCreateContent();
	void CreateRadio();

	void OnButtonRecreate(wxCommandEvent& WXUNUSED(event));
	void OnButtonSetLabel(wxCommandEvent& WXUNUSED(event));
	void OnButtonSelection(wxCommandEvent& WXUNUSED(event));
	void OnEnableItem(wxCommandEvent& event);
	void OnUpdateUIUpdate(wxUpdateUIEvent& event);
	void OnShowItem(wxCommandEvent& event);
	void OnUpdateUISelection(wxUpdateUIEvent& event);
	void OnUpdateUIReset(wxUpdateUIEvent& event);
	void OnUpdateUIShowItem(wxUpdateUIEvent& event);
	void OnUpdateUIEnableItem(wxUpdateUIEvent& event);
	void OnRadioBox(wxCommandEvent& event);
	void OnCheckOrRadioBox(wxCommandEvent& WXUNUSED(event));


private:
    DECLARE_EVENT_TABLE()


};

int wxQuestionnaireDesignerGUI::ms_defaultFlags = wxBORDER_DEFAULT;

enum MyWidgetID {
	ID_BUTTON_SERIAL_NO = wxID_HIGHEST,
	ID_STUBS_ROW ,
	RadioPage_Reset ,
	RadioPage_Update,
	RadioPage_Selection,
	RadioPage_Label,
	RadioPage_LabelBtn,
	RadioPage_EnableItem,
	RadioPage_ShowItem,
	RadioPage_Radio,
	StubBox_ID,
	QuestionBox_ID,
	NamedAttributeBox_ID,
	StubNameTC_ID,
	StubTextTC_ID,
	StubCodeTC_ID,
	StubLB_ID,
	CodeLB_ID
};

enum
{
    RadioDir_Default,
    RadioDir_LtoR,
    RadioDir_TtoB
};



BEGIN_EVENT_TABLE(wxQuestionnaireDesignerGUI, wxFrame)
    EVT_BUTTON(ID_BUTTON_SERIAL_NO,  wxQuestionnaireDesignerGUI::get_serial_no)

    EVT_BUTTON(RadioPage_LabelBtn, wxQuestionnaireDesignerGUI::OnButtonRecreate)

    EVT_BUTTON(RadioPage_Selection, wxQuestionnaireDesignerGUI::OnButtonSelection)
    EVT_BUTTON(RadioPage_Label, wxQuestionnaireDesignerGUI::OnButtonSetLabel)

    EVT_UPDATE_UI(RadioPage_Update, wxQuestionnaireDesignerGUI::OnUpdateUIUpdate)
    EVT_UPDATE_UI(RadioPage_Selection, wxQuestionnaireDesignerGUI::OnUpdateUISelection)

    EVT_RADIOBOX(RadioPage_Radio, wxQuestionnaireDesignerGUI::OnRadioBox)

    EVT_CHECKBOX(RadioPage_EnableItem, wxQuestionnaireDesignerGUI::OnEnableItem)
    EVT_CHECKBOX(RadioPage_ShowItem, wxQuestionnaireDesignerGUI::OnShowItem)

    EVT_UPDATE_UI(RadioPage_EnableItem, wxQuestionnaireDesignerGUI::OnUpdateUIEnableItem)
    EVT_UPDATE_UI(RadioPage_ShowItem, wxQuestionnaireDesignerGUI::OnUpdateUIShowItem)

    EVT_CHECKBOX(wxID_ANY, wxQuestionnaireDesignerGUI::OnCheckOrRadioBox)
    EVT_RADIOBOX(wxID_ANY, wxQuestionnaireDesignerGUI::OnCheckOrRadioBox)
END_EVENT_TABLE()


wxQuestionnaireDesignerGUI::wxQuestionnaireDesignerGUI (const wxString & title)
	: wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(800, 600)),
	  the_question (0), the_stubs(0), the_data_entry_line(0),
	  m_radio(0), m_sizerRadio(0)
{
	//CreateContent();
	NewCreateContent();
}



IMPLEMENT_APP(wxQuestionnaireApplication)


void wxQuestionnaireDesignerGUI::get_serial_no(wxCommandEvent& WXUNUSED(event))
{
	int l_ser_no = -1;
	cout << __PRETTY_FUNCTION__ << " was invoked" << endl;
	//const char * entry_text =(txt_ctrl_ser_no->GetValue()).utf8_str()  ;
	// 2-mar-2013: string narrow_text ((txt_ctrl_ser_no->GetValue()).utf8_str()  );
	// 2-mar-2013: cout << narrow_text << endl;
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


wxQuestionnaireDesignerGUI *wxGUI = 0;
bool wxQuestionnaireApplication::OnInit()
{
	wxGUI = new wxQuestionnaireDesignerGUI(wxT("wx QScript Questionnaire UI"));
	//wxQuestionnaireDesignerGUI *wxGUI = new wxQuestionnaireDesignerGUI(wxT("wx QScript Questionnaire UI"));
	wxGUI->Show(true);
	//qscript_stdout = fopen(qscript_stdout_fname.c_str(), "w");

	return true;
}




// create a sizer containing a label and a text ctrl
wxSizer *wxQuestionnaireDesignerGUI::CreateSizerWithTextAndLabel(const wxString& label,
                                                  wxWindowID id,
                                                  wxTextCtrl **ppText)
{
    return CreateSizerWithText(new wxStaticText(this, wxID_ANY, label),
        id, ppText);
}

void wxQuestionnaireDesignerGUI::AddtoSizer_LabelAndText(
						wxSizer * sizer,
						const wxString& label_str,
                                                  wxWindowID id,
                                                  wxTextCtrl **ppText)
{
	wxTextCtrl *text = new wxTextCtrl(this, id, wxEmptyString,
				wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	wxStaticText * label = new wxStaticText (this, wxID_ANY, label_str);

	sizer->Add (label, 0, wxRIGHT | wxALIGN_CENTRE_VERTICAL, 5);
	sizer->Add (0, 2, 0, wxGROW); // spacer
	sizer->Add (text, 1, wxLEFT | wxALIGN_CENTRE_VERTICAL, 5);

	if ( ppText ) {
		*ppText = text;
	}
}

// create a sizer containing a button and a text ctrl
wxSizer *wxQuestionnaireDesignerGUI::CreateSizerWithTextAndButton(wxWindowID idBtn,
                                                   const wxString& label,
                                                   wxWindowID id,
                                                   wxTextCtrl **ppText)
{
    return CreateSizerWithText(new wxButton(this, idBtn, label), id, ppText);
}

wxCheckBox *wxQuestionnaireDesignerGUI::CreateCheckBoxAndAddToSizer(wxSizer *sizer,
                                                     const wxString& label,
                                                     wxWindowID id)
{
    wxCheckBox *checkbox = new wxCheckBox(this, id, label);
    sizer->Add(checkbox, 0, wxLEFT | wxRIGHT, 5);
    sizer->Add(0, 2, 0, wxGROW); // spacer

    return checkbox;
}


wxSizer *wxQuestionnaireDesignerGUI::CreateSizerWithText(wxControl *control,
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


void wxQuestionnaireDesignerGUI::Reset()
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

void wxQuestionnaireDesignerGUI::NewCreateContent()
{
	stub_box_ = question_box_ = named_attribute_box_ = 0;
	stub_name_tc_ = 0;
	stub_box_ = new wxStaticBox (this, StubBox_ID, _T("Use this interface to create your Stub List"));
	stub_box_container_sizer_ = new wxStaticBoxSizer (stub_box_, wxVERTICAL);
	wxSizer * stub_name_row_sizer_ = new wxBoxSizer (wxHORIZONTAL);
	AddtoSizer_LabelAndText (stub_name_row_sizer_, _T("&Stub Name:"), StubNameTC_ID, &stub_name_tc_);


	wxSizer * stub_data_entry_row_sizer_ = new wxBoxSizer (wxHORIZONTAL);
	AddtoSizer_LabelAndText (stub_data_entry_row_sizer_, _T("Stub &Text:"), StubTextTC_ID, &stub_text_tc);
	AddtoSizer_LabelAndText (stub_data_entry_row_sizer_, _T("Stub &Code:"), StubCodeTC_ID, &stub_code_tc);
	stub_box_container_sizer_->Add (stub_name_row_sizer_);
	stub_box_container_sizer_->Add (stub_data_entry_row_sizer_);


	wxStaticBox *stub_view_box = new wxStaticBox(this, wxID_ANY, _T("Active Stub &View"));
	wxSizer *sizer_stub_view = new wxStaticBoxSizer(stub_view_box, wxVERTICAL);

	stub_view_grid_ = new wxGrid (this, wxID_ANY, wxDefaultPosition,
				wxDefaultSize);
	wxGridTableBase * table = new StubViewGridTable();
	table -> SetAttrProvider (new MyGridCellAttrProvider);
	stub_view_grid_->SetTable (table, true);
	//stub_view_grid_->CreateGrid (2,3);
	sizer_stub_view->Add (stub_view_grid_);


	//
	wxSizer *sizerTop = new wxBoxSizer(wxHORIZONTAL);
	//sizerTop -> Add (stub_box_container_sizer_, 0, wxGROW | (wxALL & ~wxLEFT), 10);
	sizerTop -> Add (stub_box_container_sizer_, 0, wxGROW , 10);
	sizerTop -> Add (sizer_stub_view, 1, wxGROW | wxALL, 10);


	SetSizer (sizerTop);
}

void wxQuestionnaireDesignerGUI::CreateContent()
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


void wxQuestionnaireDesignerGUI::CreateRadio()
{
	cout << __PRETTY_FUNCTION__ << endl;
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
	cout << "Should have a valid major dimension number." << endl;

        // fall back to default
        count = DEFAULT_NUM_ENTRIES;
    }

    unsigned long majorDim;
    if ( !m_textMajorDim->GetValue().ToULong(&majorDim) )
    {
        wxLogWarning(_T("Should have a valid major dimension number."));

	cout << "Should have a valid major dimension number." << endl;
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
wxCheckBox * wxQuestionnaireDesignerGUI::CreateCheckBoxAndAddToSizer(wxSizer *sizer,
                                                     const wxString& label,
                                                     wxWindowID id)
{
    wxCheckBox *checkbox = new wxCheckBox(this, id, label);
    sizer->Add(checkbox, 0, wxLEFT | wxRIGHT, 5);
    sizer->Add(0, 2, 0, wxGROW); // spacer

    return checkbox;
}
*/

void wxQuestionnaireDesignerGUI::OnButtonRecreate(wxCommandEvent& WXUNUSED(event))
{
	cout << "Reset fired" << endl;
	CreateRadio();
}

void wxQuestionnaireDesignerGUI::OnButtonSetLabel(wxCommandEvent& WXUNUSED(event))
{
    m_radio->wxControl::SetLabel(m_textLabel->GetValue());
}

void wxQuestionnaireDesignerGUI::OnButtonSelection(wxCommandEvent& WXUNUSED(event))
{
    unsigned long sel;
    if ( !m_textSel->GetValue().ToULong(&sel) ||
            (sel >= (size_t)m_radio->GetCount()) )
    {
        wxLogWarning(_T("Invalid number specified as new selection."));
    }
    else
    {
        m_radio->SetSelection(sel);
    }
}


static const int TEST_BUTTON = 1;
void wxQuestionnaireDesignerGUI::OnEnableItem(wxCommandEvent& event)
{
    m_radio->Enable(TEST_BUTTON, event.IsChecked());
}

void wxQuestionnaireDesignerGUI::OnShowItem(wxCommandEvent& event)
{
    m_radio->Show(TEST_BUTTON, event.IsChecked());
}

void wxQuestionnaireDesignerGUI::OnUpdateUIUpdate(wxUpdateUIEvent& event)
{
    unsigned long n;
    event.Enable( m_textNumBtns->GetValue().ToULong(&n) &&
                  m_textMajorDim->GetValue().ToULong(&n) );
}


//void wxQuestionnaireDesignerGUI::OnUpdateUIUpdate(wxUpdateUIEvent& event)
//{
//    unsigned long n;
//    event.Enable( m_textNumBtns->GetValue().ToULong(&n) &&
//                  m_textMajorDim->GetValue().ToULong(&n) );
//    cout << "OnUpdateUIUpdate fired" << endl;
//}
//

void wxQuestionnaireDesignerGUI::OnUpdateUISelection(wxUpdateUIEvent& event)
{
    unsigned long n;
    event.Enable( m_textSel->GetValue().ToULong(&n) &&
                   (n < (size_t)m_radio->GetCount()) );
}


void wxQuestionnaireDesignerGUI::OnUpdateUIReset(wxUpdateUIEvent& event)
{
    // only enable it if something is not set to default
    bool enable = m_chkVert->GetValue();

    if ( !enable )
    {
        unsigned long numEntries;

        enable = !m_textNumBtns->GetValue().ToULong(&numEntries) ||
                    numEntries != DEFAULT_NUM_ENTRIES;

        if ( !enable )
        {
            unsigned long majorDim;

            enable = !m_textMajorDim->GetValue().ToULong(&majorDim) ||
                        majorDim != DEFAULT_MAJOR_DIM;
        }
    }

    event.Enable(enable);
}


void wxQuestionnaireDesignerGUI::OnUpdateUIEnableItem(wxUpdateUIEvent& event)
{
    event.SetText(m_radio->IsItemEnabled(TEST_BUTTON) ? _T("Disable &2nd item")
                                                      : _T("Enable &2nd item"));
}

void wxQuestionnaireDesignerGUI::OnUpdateUIShowItem(wxUpdateUIEvent& event)
{
    event.SetText(m_radio->IsItemShown(TEST_BUTTON) ? _T("Hide 2nd &item")
                                                    : _T("Show 2nd &item"));
}


void wxQuestionnaireDesignerGUI::OnRadioBox(wxCommandEvent& event)
{
    int sel = m_radio->GetSelection();
    int event_sel = event.GetSelection();
    wxUnusedVar(event_sel);

    wxLogMessage(_T("Radiobox selection changed, now %d"), sel);

    wxASSERT_MSG( sel == event_sel,
                  _T("selection should be the same in event and radiobox") );

    m_textCurSel->SetValue(wxString::Format(_T("%d"), sel));
}


void wxQuestionnaireDesignerGUI::OnCheckOrRadioBox(wxCommandEvent& WXUNUSED(event))
{
    CreateRadio();
}

enum Columns
{
    Col_Id,
    Col_Summary,
    Col_Severity,
    Col_Priority,
    Col_Platform,
    Col_Opened,
    Col_Max
};

enum Severity
{
    Sev_Wish,
    Sev_Minor,
    Sev_Normal,
    Sev_Major,
    Sev_Critical,
    Sev_Max
};

static const wxString severities[] =
{
    _T("wishlist"),
    _T("minor"),
    _T("normal"),
    _T("major"),
    _T("critical"),
};

static struct StubViewGridData
{
    int id;
    wxChar summary[80];
    Severity severity;
    int prio;
    wxChar platform[12];
    bool opened;
} gs_dataStubViewGrid [] =
{
    { 18, _T("foo doesn't work"), Sev_Major, 1, _T("wxMSW"), true },
    { 27, _T("bar crashes"), Sev_Critical, 1, _T("all"), false },
    { 45, _T("printing is slow"), Sev_Minor, 3, _T("wxMSW"), true },
    { 68, _T("Rectangle() fails"), Sev_Normal, 1, _T("wxMSW"), false },
};

static const wxChar *headers[Col_Max] =
{
    _T("Id"),
    _T("Summary"),
    _T("Severity"),
    _T("Priority"),
    _T("Platform"),
    _T("Opened?"),
};



wxString StubViewGridTable::GetTypeName(int WXUNUSED(row), int col)
{
    switch ( col )
    {
        case Col_Id:
        case Col_Priority:
            return wxGRID_VALUE_NUMBER;;

        case Col_Severity:
            // fall thorugh (TODO should be a list)

        case Col_Summary:
            return wxString::Format(_T("%s:80"), wxGRID_VALUE_STRING);

        case Col_Platform:
            return wxString::Format(_T("%s:all,MSW,GTK,other"), wxGRID_VALUE_CHOICE);

        case Col_Opened:
            return wxGRID_VALUE_BOOL;
    }

    wxFAIL_MSG(_T("unknown column"));

    return wxEmptyString;
}

int StubViewGridTable::GetNumberRows()
{
    return WXSIZEOF(gs_dataStubViewGrid);
}

int StubViewGridTable::GetNumberCols()
{
    return Col_Max;
}

bool StubViewGridTable::IsEmptyCell( int WXUNUSED(row), int WXUNUSED(col) )
{
    return false;
}

wxString StubViewGridTable::GetValue( int row, int col )
{
    const StubViewGridData& gd = gs_dataStubViewGrid[row];

    switch ( col )
    {
        case Col_Id:
            return wxString::Format(_T("%d"), gd.id);

        case Col_Priority:
            return wxString::Format(_T("%d"), gd.prio);

        case Col_Opened:
            return gd.opened ? _T("1") : _T("0");

        case Col_Severity:
            return severities[gd.severity];

        case Col_Summary:
            return gd.summary;

        case Col_Platform:
            return gd.platform;
    }

    return wxEmptyString;
}

void StubViewGridTable::SetValue( int row, int col, const wxString& value )
{
    StubViewGridData& gd = gs_dataStubViewGrid[row];

    switch ( col )
    {
        case Col_Id:
        case Col_Priority:
        case Col_Opened:
            wxFAIL_MSG(_T("unexpected column"));
            break;

        case Col_Severity:
            {
                size_t n;
                for ( n = 0; n < WXSIZEOF(severities); n++ )
                {
                    if ( severities[n] == value )
                    {
                        gd.severity = (Severity)n;
                        break;
                    }
                }

                if ( n == WXSIZEOF(severities) )
                {
                    wxLogWarning(_T("Invalid severity value '%s'."),
                                 value.c_str());
                    gd.severity = Sev_Normal;
                }
            }
            break;

        case Col_Summary:
            wxStrncpy(gd.summary, value, WXSIZEOF(gd.summary));
            break;

        case Col_Platform:
            wxStrncpy(gd.platform, value, WXSIZEOF(gd.platform));
            break;
    }
}

bool
StubViewGridTable::CanGetValueAs(int WXUNUSED(row),
                             int col,
                             const wxString& typeName)
{
    if ( typeName == wxGRID_VALUE_STRING )
    {
        return true;
    }
    else if ( typeName == wxGRID_VALUE_BOOL )
    {
        return col == Col_Opened;
    }
    else if ( typeName == wxGRID_VALUE_NUMBER )
    {
        return col == Col_Id || col == Col_Priority || col == Col_Severity;
    }
    else
    {
        return false;
    }
}

bool StubViewGridTable::CanSetValueAs( int row, int col, const wxString& typeName )
{
    return CanGetValueAs(row, col, typeName);
}

long StubViewGridTable::GetValueAsLong( int row, int col )
{
    const StubViewGridData& gd = gs_dataStubViewGrid[row];

    switch ( col )
    {
        case Col_Id:
            return gd.id;

        case Col_Priority:
            return gd.prio;

        case Col_Severity:
            return gd.severity;

        default:
            wxFAIL_MSG(_T("unexpected column"));
            return -1;
    }
}

bool StubViewGridTable::GetValueAsBool( int row, int col )
{
    if ( col == Col_Opened )
    {
        return gs_dataStubViewGrid[row].opened;
    }
    else
    {
        wxFAIL_MSG(_T("unexpected column"));

        return false;
    }
}

void StubViewGridTable::SetValueAsLong( int row, int col, long value )
{
    StubViewGridData& gd = gs_dataStubViewGrid[row];

    switch ( col )
    {
        case Col_Priority:
            gd.prio = value;
            break;

        default:
            wxFAIL_MSG(_T("unexpected column"));
    }
}

void StubViewGridTable::SetValueAsBool( int row, int col, bool value )
{
    if ( col == Col_Opened )
    {
        gs_dataStubViewGrid[row].opened = value;
    }
    else
    {
        wxFAIL_MSG(_T("unexpected column"));
    }
}

wxString StubViewGridTable::GetColLabelValue( int col )
{
    return headers[col];
}


