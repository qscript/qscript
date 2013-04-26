
// Neil Xavier D'Souza
//
#include <wx/wx.h>
#include "wx/filepicker.h"

#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;


class QScriptCompilerUI : public wxFrame
{
public:
	QScriptCompilerUI(const wxString& title);
	wxTextCtrl *compileFileName_ ;
	wxFilePickerCtrl * filePicker_;
	//wxFileCtrl * filePicker_;
	wxCheckListBox * compilerOptionsCBox_;
	wxPanel *panel_ ;
	wxButton * showCmdLineBtn_;
	wxButton * showRunCmdBtn_;
	void OnFileChange(wxFileDirPickerEvent& event);
	void OnCheckBox(wxCommandEvent &event);
	void CreateCheckListbox(long flags = 0);
	void OnCheckboxToggle(wxCommandEvent& event);
	void RunCompiler(wxCommandEvent& event);
	void SetCompilerHomeDir();
	//set<int32_t> cbData_;
	wxStatusBar * statusBar_;
	string compile_file_and_path_;
	string cwd_;
	string exe_home_;
	string qscript_home;

private:
	DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------
// event tables
// ----------------------------------------------------------------------------

enum {
	FileNameControlID = wxID_HIGHEST,
	FPControlID,
	CBControlID,
	BtnCmdLineID,
	BtnRunCmdID
};

BEGIN_EVENT_TABLE(QScriptCompilerUI, wxFrame)
	EVT_FILEPICKER_CHANGED(FPControlID, QScriptCompilerUI::OnFileChange)
	EVT_CHECKBOX(wxID_ANY, QScriptCompilerUI::OnCheckBox)
	EVT_CHECKLISTBOX(CBControlID, QScriptCompilerUI::OnCheckboxToggle)
	EVT_BUTTON(BtnRunCmdID, QScriptCompilerUI::RunCompiler)
END_EVENT_TABLE()

/*
//    EVT_RADIOBOX(wxID_ANY, QScriptCompilerUI::OnCheckBox)
*/

//#include "flexgridsizer.h"

QScriptCompilerUI::QScriptCompilerUI(const wxString& title)
       : wxFrame(NULL, -1, title, wxPoint(-1, -1)
		       , wxSize(640, 480)
		       //, wxDefaultSize
		       )
{
	const int widths[] = { -1, 200 };
	statusBar_ = CreateStatusBar(2);
	SetStatusWidths(2, widths);


	panel_ = new wxPanel(this, -1);

	//wxBoxSizer *vtUIContainer_ = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *vtUIContainer_ = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hzUIFileSelectionContainer_ = new wxBoxSizer(wxHORIZONTAL);

	//wxFlexGridSizer *fgs = new wxFlexGridSizer(2, 3, 9, 25);



	filePicker_ = new wxFilePickerCtrl(panel_, FPControlID,
					wxEmptyString,
					wxT("Please choose a file ... "), wxT("*.qscript"),
					wxDefaultPosition, wxDefaultSize,
					wxFLP_DEFAULT_STYLE | wxFLP_CHANGE_DIR
					//, GetPickerStyle()
					);

	//filePicker_ = new wxFileCtrl(panel_, FPControlID,
	//				wxEmptyString,
	//				wxEmptyString, wxT("*.qscript")
	//		);
	//				//,
	//				//wxDefaultPosition, wxDefaultSize
	//				////, GetPickerStyle()
	//				//);

	wxStaticText *thetitle = new wxStaticText(panel_, -1, wxT("Choose a File to Compile"));
	//wxStaticText *author = new wxStaticText(panel_, -1, wxT("Author"));
	//wxStaticText *review = new wxStaticText(panel_, -1, wxT("Review"));

	compileFileName_ = new wxTextCtrl(panel_, -1);
	//wxTextCtrl *tc2 = new wxTextCtrl(panel_, -1);
	//wxTextCtrl *tc3 = new wxTextCtrl(panel_, -1, wxT(""),
	//wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE);

	//fgs->Add(thetitle);
	//fgs->Add(compileFileName_, 1, wxEXPAND);
	//fgs->Add(filePicker_, 1, wxEXPAND);
	hzUIFileSelectionContainer_->Add(thetitle, wxSizerFlags(1).Align(0).Expand().Border(wxALL, 10)
			);
	hzUIFileSelectionContainer_->Add(compileFileName_, wxSizerFlags(1).Align(0).Expand().Border(wxALL, 10));
	hzUIFileSelectionContainer_->Add(filePicker_, wxSizerFlags(1).Align(0).Expand().Border(wxALL, 10));
	// hzUIFileSelectionContainer_->Add(fgs, 1, wxALL | wxEXPAND, 15);
	//fgs->Add(author);
	//fgs->Add(tc2, 1, wxEXPAND);
	//fgs->Add(review, 1, wxEXPAND);
	//fgs->Add(tc3, 1, wxEXPAND);
	wxBoxSizer *hzUICompilerOptionsContainer_ = new wxBoxSizer(wxHORIZONTAL);
	CreateCheckListbox();
	hzUICompilerOptionsContainer_->Add(compilerOptionsCBox_, wxSizerFlags(1).Align(0).Expand().Border(wxALL, 10));
	//fgs->Add(compilerOptionsCBox_, 1, wxEXPAND);
	//fgs->AddGrowableRow(1, 1);
	//fgs->AddGrowableCol(1, 1);
	//
	//
	 wxButton *showCmdLineBtn_ = new wxButton(panel_, BtnCmdLineID,
		wxT("Show Command Line Output"), wxPoint(20, 20));
	 wxButton *showRunCmdBtn_ = new wxButton(panel_, BtnRunCmdID,
		wxT("Run Compile Command"), wxPoint(20, 20));
	wxBoxSizer *hzUIButtonsContainer_ = new wxBoxSizer(wxHORIZONTAL);
	hzUIButtonsContainer_->Add(showCmdLineBtn_);
	hzUIButtonsContainer_->Add(showRunCmdBtn_);

	//hzUIContainer_->Add(fgs, 1, wxALL | wxEXPAND, 15);
	vtUIContainer_->Add(hzUIFileSelectionContainer_);
	vtUIContainer_->Add(hzUIButtonsContainer_);
	vtUIContainer_->Add(hzUICompilerOptionsContainer_);
	panel_->SetSizer(vtUIContainer_);
	Centre();
	exe_home_ = wxGetCwd().utf8_str();
}

void QScriptCompilerUI::OnFileChange(wxFileDirPickerEvent& event)
{
    //wxLogMessage(wxT("The file changed to '%s' ! The current working directory is '%s'"),
    //             event.GetPath().c_str(), wxGetCwd().c_str());
	cout	<< "The file changed to '"
		<< event.GetPath().utf8_str()
		<< "' ! The current working directory is '"
		<< wxGetCwd().utf8_str()
		<< endl;
	compile_file_and_path_ = event.GetPath().utf8_str();
	cwd_ = wxGetCwd().utf8_str();
}

void QScriptCompilerUI::OnCheckBox(wxCommandEvent &event)
{
}



class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};


//#include "main.h"
//#include "flexgridsizer.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{

	QScriptCompilerUI * ui = new QScriptCompilerUI(wxT("QScriptCompilerUI"));
	ui->Show(true);

	return true;
}


void QScriptCompilerUI::CreateCheckListbox(long flags)
{
	// check list box
	static const wxChar *aszChoices[] =
		{
		 _T("-o Optimize Generated Code Size")
		,_T("-m Nice Data Map for Quantum")
		,_T("-n NCurses User Interface")
		,_T("-s Static Compile - This must be passed for Windows")
		};

	wxString *astrChoices = new wxString[WXSIZEOF(aszChoices)];
	for (unsigned int ui = 0; ui < WXSIZEOF(aszChoices); ui++ ) {
		astrChoices[ui] = aszChoices[ui];
	}
	compilerOptionsCBox_ = new wxCheckListBox
				(
				 panel_,               // parent
				 CBControlID,       // control id
				 wxDefaultPosition, wxDefaultSize,
				 //wxPoint(10, 10),       // listbox poistion
				 //wxSize(400, 100),      // listbox size
				 WXSIZEOF(aszChoices),  // number of strings
				 astrChoices,           // array of strings
				 flags
				);

	delete [] astrChoices;

	// set grey background for every second entry
	//for ( ui = 0; ui < WXSIZEOF(aszChoices); ui += 2 ) {
	//    AdjustColour(ui);
	//}
	//m_pListBox->Check(2);
	//m_pListBox->Select(3);
}

void QScriptCompilerUI::OnCheckboxToggle(wxCommandEvent& event)
{
	unsigned int nItem = event.GetInt();

	wxLogStatus(this, wxT("item %d was %schecked"), nItem,
		      compilerOptionsCBox_->IsChecked(nItem) ? wxT("") : wxT("un"));
	// int code = rbQnreCodeMap_[nItem];
	// if (compilerOptionsCBox_->IsChecked(nItem)) {
	// 	cbData_.insert (code);
	// } else {
	// 	cbData_.erase (code);
	// }
	// cout << "selected values are: " << endl;
	// for (set<int32_t>::iterator it = cbData_.begin(); it != cbData_.end(); ++it) {
	// 	cout << " " << *it;
	// }
	cout << endl;

}

void QScriptCompilerUI::SetCompilerHomeDir()
{

	{
		string home = getenv("QSCRIPT_HOME");
		cout << "QSCRIPT_HOME: is " << home << endl;
	}
	qscript_home =  exe_home_ + "/../simple_compiler";
	string qscript_home_env = "QSCRIPT_HOME=" + qscript_home;
	char * s (strdup(qscript_home_env.c_str()));
	putenv (s);
	{
		string home = getenv("QSCRIPT_HOME");
		cout << "QSCRIPT_HOME: now is " << home << endl;
	}
	// memory leak

}

void QScriptCompilerUI::RunCompiler(wxCommandEvent& event)
{
	cout << __PRETTY_FUNCTION__ << endl;

	for (int i=0; i<4; ++i) {
		if (compilerOptionsCBox_->IsChecked(i)) {
			cout << "item " << i << "is Checked" << endl;
		} else {
			cout << "item " << i << "is UnChecked" << endl;
		}
	}
	enum CompilerFlags {
		OptimizeFlag,
		NiceMapFlag,
		NCursesUIFlag,
		StaticCompileFlag
	};

	stringstream compiler_options;
	if (compilerOptionsCBox_->IsChecked(OptimizeFlag)) {
		compiler_options << " -o ";
	}
	if (compilerOptionsCBox_->IsChecked(NiceMapFlag)) {
		compiler_options << " -m ";
	}
	if (compilerOptionsCBox_->IsChecked(NCursesUIFlag)) {
		compiler_options << " -n ";
	}
	if (compilerOptionsCBox_->IsChecked(StaticCompileFlag)) {
		compiler_options << " -s ";
	}
	cout << "compiler_options: " << compiler_options.str() << endl;
	if (compile_file_and_path_.length() == 0) {
		cout << "please choose a file using the FilePicker" << endl;
		return;
	}

	static bool has_set_home_dir_flag = false;
	if (!has_set_home_dir_flag) {
		SetCompilerHomeDir();
		has_set_home_dir_flag = true;
	}

	stringstream cmd;
	size_t pos = compile_file_and_path_.find_last_of('/');
	string proj_dir = compile_file_and_path_.substr(0, pos);
	string file_name = compile_file_and_path_.substr(pos + 1, compile_file_and_path_.length()-(pos + 1));
	wxString wxProjDir (proj_dir.c_str(), wxConvUTF8);
	//filePicker_->SetDirectory (wxProjDir);
	wxSetWorkingDirectory (wxProjDir);
	cout << "proj_dir: " << proj_dir << endl;
	cout << "file_name: " << file_name << endl;
	cmd << qscript_home << "/bin/qscript " << compiler_options.str()
		<< " -f " <<  file_name
		;
	cout << "cmd: " << cmd.str() << endl;
	int rval = system(cmd.str().c_str());

}
