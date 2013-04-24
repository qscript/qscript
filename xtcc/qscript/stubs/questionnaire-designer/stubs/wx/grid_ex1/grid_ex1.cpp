
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
#include <vector>

#include "StubViewGridTable.h"


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

	int gridW , gridH ;



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
	wxTextCtrl * no_of_rows_tc;
	//wxListBox * stub_lbox;
	//wxListBox * code_lbox;
	wxGrid * stub_view_grid_;
	wxSizer *sizer_stub_view_;
	wxTextCtrl     *log_tc;
	wxLogTextCtrl  *logger_ltc;
	wxLog *m_logOld;




	wxSizer *CreateSizerWithText(wxControl *control,
                                          wxWindowID id,
                                          wxTextCtrl **ppText);

	void AddtoSizer_LabelAndText(
					wxSizer * sizer,
					const wxString& label_str,
					wxWindowID id,
					wxTextCtrl **ppText);
	void AddToSizer_Button(
				wxSizer * sizer,
				const wxString& label_str,
				wxWindowID id);

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
	void NewCreateContent2();
	void CreateRadio();

	void SelectRows( wxCommandEvent& WXUNUSED(ev) );

	void InsertRow( wxCommandEvent& WXUNUSED(ev) );

	void OnLabelLeftClick( wxGridEvent& ev );

	void OnEditorHidden( wxGridEvent& ev );
	void OnEditorShown( wxGridEvent& ev );

	void OnColSize( wxGridSizeEvent& ev );
	void OnRowSize( wxGridSizeEvent& ev );
	void OnSelectCell( wxGridEvent& );


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
	CodeLB_ID,
	CreateGridButton_ID,
	NoOfRowsTC_ID,
	AddRowButton_ID,
	InsertRowButton_ID,
	DeleteRowButton_ID,
	StubGrid_ID
};

enum
{
    RadioDir_Default,
    RadioDir_LtoR,
    RadioDir_TtoB
};



BEGIN_EVENT_TABLE(wxQuestionnaireDesignerGUI, wxFrame)
	EVT_BUTTON(InsertRowButton_ID, wxQuestionnaireDesignerGUI::InsertRow )
	EVT_GRID_LABEL_LEFT_CLICK( wxQuestionnaireDesignerGUI::OnLabelLeftClick )
	EVT_GRID_SELECT_CELL( wxQuestionnaireDesignerGUI::OnSelectCell )
	EVT_GRID_EDITOR_SHOWN( wxQuestionnaireDesignerGUI::OnEditorShown )
	EVT_GRID_EDITOR_HIDDEN( wxQuestionnaireDesignerGUI::OnEditorHidden )
END_EVENT_TABLE()


wxQuestionnaireDesignerGUI::wxQuestionnaireDesignerGUI (const wxString & title)
	: wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(800, 600)),
	  the_question (0), the_stubs(0), the_data_entry_line(0),
	  m_radio(0), m_sizerRadio(0)
{
	NewCreateContent2();
}



IMPLEMENT_APP(wxQuestionnaireApplication)





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


void wxQuestionnaireDesignerGUI::AddToSizer_Button(
			wxSizer * sizer,
			const wxString& label_str,
			wxWindowID id)
{
	sizer->Add (0, 10, 0, wxGROW); // spacer
	sizer->Add(new wxButton(this, id, label_str), 0);
	sizer->Add (0, 10, 0, wxGROW); // spacer
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

void wxQuestionnaireDesignerGUI::NewCreateContent2()
{
	stub_box_ = question_box_ = named_attribute_box_ = 0;
	stub_name_tc_ = 0;
	stub_box_ = new wxStaticBox (this, StubBox_ID, _T("Use this interface to create your Stub List"),
			wxDefaultPosition,
			wxSize(800,600)
			);
	stub_box_container_sizer_ = new wxStaticBoxSizer (stub_box_, wxVERTICAL);
	wxSizer * stub_name_row_sizer_ = new wxBoxSizer (wxHORIZONTAL);
	AddtoSizer_LabelAndText (stub_name_row_sizer_, _T("&Stub Name:"), StubNameTC_ID, &stub_name_tc_);


	wxSizer * stub_data_entry_row_sizer = new wxBoxSizer (wxHORIZONTAL);
	AddtoSizer_LabelAndText (stub_data_entry_row_sizer, _T("&No of Rows:"), StubTextTC_ID, &no_of_rows_tc);
	AddToSizer_Button (stub_data_entry_row_sizer, _T("CreateGrid"), CreateGridButton_ID);

	wxSizer * button_row_sizer = new wxBoxSizer (wxHORIZONTAL);
	AddToSizer_Button (button_row_sizer, _T("&Add Row"), AddRowButton_ID);
	AddToSizer_Button (button_row_sizer, _T("&Insert Row"), InsertRowButton_ID);
	AddToSizer_Button (button_row_sizer, _T("&Delete Row"), DeleteRowButton_ID);

	stub_box_container_sizer_->Add (stub_name_row_sizer_);
	stub_box_container_sizer_->Add (0, 10, 0, wxGROW); // spacer
	stub_box_container_sizer_->Add (stub_data_entry_row_sizer);
	stub_box_container_sizer_->Add (0, 10, 0, wxGROW); // spacer
	stub_box_container_sizer_->Add (button_row_sizer);


	sizer_stub_view_ = new wxBoxSizer (wxHORIZONTAL);

	gridW = 600, gridH = 300;
	stub_view_grid_ = new wxGrid (this, wxID_ANY, wxDefaultPosition,
				//wxDefaultSize
				wxSize (gridW,gridH)
				);
	//wxGridTableBase * table = new BugsGridTable();
	wxGridTableBase * table = new StubViewGridTable();
	table -> SetAttrProvider (new MyGridCellAttrProvider);
	//stub_view_grid_->SetTable (table, true);
	stub_view_grid_->SetTable (table, false);
	//stub_view_grid_->CreateGrid (2,3);
	sizer_stub_view_->Add (stub_view_grid_);
	stub_box_container_sizer_->Add (0, 10, 0, wxGROW); // spacer
	stub_box_container_sizer_->Add (sizer_stub_view_);

	int logW = gridW, logH = 100;


	log_tc = new wxTextCtrl( this,
			wxID_ANY,
			wxEmptyString,
			wxPoint( 0, gridH + 20 ),
			wxSize( logW, logH ),
			wxTE_MULTILINE );
	logger_ltc = new wxLogTextCtrl( log_tc );
	m_logOld = wxLog::SetActiveTarget( logger_ltc );
	//wxLog::SetTimestamp( NULL );


	stub_box_container_sizer_->Add (log_tc);
	//sizerTop->Add (log_tc, 0, wxEXPAND );

	wxSizer *sizerTop = new wxBoxSizer(wxHORIZONTAL);
	sizerTop -> Add (stub_box_container_sizer_, 0, wxGROW , 10);


	SetSizer (sizerTop);

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


static const int TEST_BUTTON = 1;




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

void wxQuestionnaireDesignerGUI::InsertRow(
		//wxCommandEvent& WXUNUSED(ev)
		wxCommandEvent& ev
		)
{
	cout << "sel row:" << stub_view_grid_->GetGridCursorRow()
		<< endl;
	stub_view_grid_->InsertRows( stub_view_grid_->GetGridCursorRow(), 1 );
	wxGridTableBase * table = stub_view_grid_->GetTable();
	table->GetNumberRows();
	//table->InsertRows( stub_view_grid_->GetGridCursorRow(), 1 );
	//stub_view_grid_->SetTable (table, false);
	//
	//

	//sizer_stub_view_->Detach( stub_view_grid_ );
        //m_sizerRadio->
	stub_box_container_sizer_->Detach (sizer_stub_view_);
	stub_box_container_sizer_->Detach (log_tc);
	delete stub_view_grid_;
	//delete sizer_stub_view_;
	stub_view_grid_ = new wxGrid (this, wxID_ANY, wxDefaultPosition,
				//wxDefaultSize
				wxSize (gridW,gridH)
				);
	stub_view_grid_->SetTable(table, false);
	wxSizer *sizer_stub_view_ = new wxBoxSizer (wxHORIZONTAL);
	sizer_stub_view_->Add (stub_view_grid_);
	stub_box_container_sizer_->Add (sizer_stub_view_);
	stub_box_container_sizer_->Add (log_tc);
	stub_box_container_sizer_->Layout();

	cout << "Insert row called" << endl;
	ev.Skip();
}

bool StubViewGridTable :: InsertRows(size_t pos , size_t numRows )
{
	cout << __PRETTY_FUNCTION__
		<< "numRows: " << numRows
		<< endl;
	the_data_.push_back (StubViewGridTableData("New", 51, false));
	return true;
}

void wxQuestionnaireDesignerGUI::SelectRows( wxCommandEvent& WXUNUSED(ev) )
{
    stub_view_grid_->SetSelectionMode( wxGrid::wxGridSelectRows );
}

void wxQuestionnaireDesignerGUI::OnSelectCell( wxGridEvent& ev )
{
    wxString logBuf;
    if ( ev.Selecting() )
        logBuf << _T("Selected ");
    else
        logBuf << _T("Deselected ");
    logBuf << _T("cell at row ") << ev.GetRow()
           << _T(" col ") << ev.GetCol()
           << _T(" ( ControlDown: ")<< (ev.ControlDown() ? 'T':'F')
           << _T(", ShiftDown: ")<< (ev.ShiftDown() ? 'T':'F')
           << _T(", AltDown: ")<< (ev.AltDown() ? 'T':'F')
           << _T(", MetaDown: ")<< (ev.MetaDown() ? 'T':'F') << _T(" )");

    //Indicate whether this column was moved
    if ( ((wxGrid *)ev.GetEventObject())->GetColPos( ev.GetCol() ) != ev.GetCol() )
        logBuf << _T(" *** Column moved, current position: ") << ((wxGrid *)ev.GetEventObject())->GetColPos( ev.GetCol() );

    wxLogMessage( wxT("%s"), logBuf.c_str() );

    // you must call Skip() if you want the default processing
    // to occur in wxGrid
    ev.Skip();
}

void wxQuestionnaireDesignerGUI::OnLabelLeftClick( wxGridEvent& ev )
{
    wxString logBuf;
    if ( ev.GetRow() != -1 )
    {
        logBuf << _T("Left click on row label ") << ev.GetRow();
    }
    else if ( ev.GetCol() != -1 )
    {
        logBuf << _T("Left click on col label ") << ev.GetCol();
    }
    else
    {
        logBuf << _T("Left click on corner label");
    }

    if ( ev.ShiftDown() )
        logBuf << _T(" (shift down)");
    if ( ev.ControlDown() )
        logBuf << _T(" (control down)");
    wxLogMessage( wxT("%s"), logBuf.c_str() );

    // you must call event skip if you want default grid processing
    //
    ev.Skip();
}

void wxQuestionnaireDesignerGUI::OnEditorShown( wxGridEvent& ev )
{

    if ( (ev.GetCol() == 4) &&
         (ev.GetRow() == 0) &&
     (wxMessageBox(_T("Are you sure you wish to edit this cell"),
                   _T("Checking"),wxYES_NO) == wxNO ) ) {

     ev.Veto();
     return;
    }

    wxLogMessage( wxT("Cell editor shown.") );

    ev.Skip();
}

void wxQuestionnaireDesignerGUI::OnEditorHidden( wxGridEvent& ev )
{

    if ( (ev.GetCol() == 4) &&
         (ev.GetRow() == 0) &&
     (wxMessageBox(_T("Are you sure you wish to finish editing this cell"),
                   _T("Checking"),wxYES_NO) == wxNO ) ) {

        ev.Veto();
        return;
    }

    wxLogMessage( wxT("Cell editor hidden.") );

    ev.Skip();
}

void wxQuestionnaireDesignerGUI::OnRowSize( wxGridSizeEvent& ev )
{
    wxLogMessage(_T("Resized row %d"), ev.GetRowOrCol());

    ev.Skip();
}


void wxQuestionnaireDesignerGUI::OnColSize( wxGridSizeEvent& ev )
{
    wxLogMessage(_T("Resized col %d"), ev.GetRowOrCol());

    ev.Skip();
}
