#include <wx/wx.h>
#include <wx/mediactrl.h>

class MainApp : public wxApp {
    public:
        virtual bool OnInit();
};

bool MainApp::OnInit() {
    wxFrame *main = new wxFrame(NULL, wxID_ANY, wxT("My first video player"));
    wxMediaCtrl *media = new wxMediaCtrl(main, wxID_ANY, wxT("capture-11.avi"));
    media->ShowPlayerControls(wxMEDIACTRLPLAYERCONTROLS_DEFAULT);
    main->Show(true); // show it
    return true;
}

IMPLEMENT_APP(MainApp)
