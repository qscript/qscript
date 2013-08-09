#include <wx/wx.h>
#include <wx/mediactrl.h>

class MainFrame : public wxFrame {
    public:
        MainFrame();
};

MainFrame::MainFrame() :
	wxFrame(NULL, wxID_ANY, wxT("My first video player"), wxDefaultPosition, wxDefaultSize)
{
    wxMediaCtrl *media = new wxMediaCtrl(this, wxID_ANY, wxT("path\file.avi"));
    media->ShowPlayerControls();
}

class MainApp : public wxApp {
    public:
        virtual bool OnInit();
};

bool MainApp::OnInit() {
    MainFrame *main = new MainFrame();

    main->Show(true); // show it

    return true;
}

IMPLEMENT_APP(MainApp)
