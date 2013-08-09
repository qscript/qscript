/*
 * =====================================================================================
 *
 *       Filename:  wx_hello_dynamic_event.cpp
 *
 *    Description:  copied from wx docs: http://www.wxwidgets.org/docs/tutorials/hworld2.txt 
 *
 *        Version:  1.0
 *        Created:  Thursday 21 February 2013 07:27:53  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <wx/wx.h>

class MyApp : public wxApp
{
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)


class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

enum
{
    ID_Quit=1,
    ID_About
};


bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( _("Hello World"), wxPoint(50, 50),
                                  wxSize(450, 350));

    frame->Connect( ID_Quit, wxEVT_COMMAND_MENU_SELECTED,
                    (wxObjectEventFunction) &MyFrame::OnQuit );
    frame->Connect( ID_About, wxEVT_COMMAND_MENU_SELECTED,
                    (wxObjectEventFunction) &MyFrame::OnAbout );

    frame->Show(true);
    SetTopWindow(frame);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame( NULL, -1, title, pos, size )
{
    wxMenuBar *menuBar = new wxMenuBar;

    wxMenu *menuFile = new wxMenu;

    menuFile->Append( ID_About, _("&About...") );
    menuFile->AppendSeparator();
    menuFile->Append( ID_Quit, _("E&xit") );

    menuBar->Append(menuFile, _("&File") );

    SetMenuBar(menuBar);

    CreateStatusBar();
        
    SetStatusText( _("Welcome to wxWidgets!") );
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox( _("wxWidgets Hello World example."), 
                  _("About Hello World"),
                  wxOK|wxICON_INFORMATION, this );
}
