// Neil Xavier DSouza
// really simple program to check how to use customized labels in a wxGrid
#include <wx/wx.h>
#include <wx/grid.h>
#include <iostream>

using namespace std;

class GridFrame : public wxFrame
{
	public:
	wxGrid         *grid;
	wxTextCtrl     *logWin;
	wxLogTextCtrl  *logger;
	wxLog *m_logOld;
	GridFrame();

};

class CustomColumnHeaderRenderer : public wxGridColumnHeaderRenderer
{
public:
    CustomColumnHeaderRenderer(const wxColour& colFg, const wxColour& colBg)
        : m_colFg(colFg),
          m_colBg(colBg)
    {
    }

    virtual void DrawLabel(const wxGrid& WXUNUSED(grid),
                           wxDC& dc,
                           const wxString& value,
                           const wxRect& rect,
                           int horizAlign,
                           int vertAlign,
                           int WXUNUSED(textOrientation)) const
    {
	//    cout << __PRETTY_FUNCTION__ << endl;
        dc.SetTextForeground(m_colFg);
        dc.SetFont(wxITALIC_FONT->Bold());
	wxString a_label = wxString::Format(_("NxD:%i"), m_active_col_no);
        //dc.DrawLabel(value, rect, horizAlign | vertAlign);
        dc.DrawLabel(a_label, rect, horizAlign | vertAlign);
    }

    virtual void DrawBorder(const wxGrid& WXUNUSED(grid),
                            wxDC& dc,
                            wxRect& rect) const
    {
        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.SetBrush(wxBrush(m_colBg));
        dc.DrawRectangle(rect);
    }

    void SetColumnNumber(int col_no)
    {
	    m_active_col_no = col_no;
    }

private:
    const wxColour m_colFg, m_colBg;
    int m_active_col_no;

    wxDECLARE_NO_COPY_CLASS(CustomColumnHeaderRenderer);
};


class CustomColumnHeadersProvider : public wxGridCellAttrProvider
{
public:
    // by default custom column renderer is not used, call
    // UseCustomColHeaders() to enable it
    CustomColumnHeadersProvider()
        : m_customOddRenderer(*wxYELLOW, *wxBLUE),
          m_customEvenRenderer(*wxWHITE, *wxBLACK),
          m_useCustom(false)
    {
    }

    // enable or disable the use of custom renderer for column headers
    void UseCustomColHeaders(bool use = true) { m_useCustom = use; }

protected:
    virtual const wxGridColumnHeaderRenderer& GetColumnHeaderRenderer(int col)
    {
        // if enabled, use custom renderers
        if ( m_useCustom )
        {
            // and use different ones for odd and even columns -- just to show
            // that we can
	    m_customEvenRenderer.SetColumnNumber(col);
	    m_customOddRenderer.SetColumnNumber(col);
		//cout << __PRETTY_FUNCTION__ << endl;
            return col % 2 ? m_customOddRenderer : m_customEvenRenderer;
        }

        return wxGridCellAttrProvider::GetColumnHeaderRenderer(col);
    }

private:
    CustomColumnHeaderRenderer m_customOddRenderer,
                               m_customEvenRenderer;

    bool m_useCustom;

    wxDECLARE_NO_COPY_CLASS(CustomColumnHeadersProvider);
};




GridFrame::GridFrame()
        : wxFrame( (wxFrame *)NULL, wxID_ANY, wxT("wxWidgets grid class demo"),
                   wxDefaultPosition,
                   wxDefaultSize )
{


    grid = new wxGrid( this,
                       wxID_ANY,
                       wxPoint( 0, 0 ),
                       wxSize( 400, 300 ) );

    int gridW = 600, gridH = 300;
    int logW = gridW, logH = 100;
    logWin = new wxTextCtrl( this,
                             wxID_ANY,
                             wxEmptyString,
                             wxPoint( 0, gridH + 20 ),
                             wxSize( logW, logH ),
                             wxTE_MULTILINE );
    logger = new wxLogTextCtrl( logWin );
    m_logOld = wxLog::SetActiveTarget( logger );
    wxLog::DisableTimestamp();

    grid->CreateGrid( 0, 0 );

    grid->GetTable()->SetAttrProvider(new CustomColumnHeadersProvider());
    CustomColumnHeadersProvider* provider =
        static_cast<CustomColumnHeadersProvider*>(grid->GetTable()->GetAttrProvider());
    provider->UseCustomColHeaders(true);
    grid->SetUseNativeColLabels(false);


    grid->AppendRows(100);
    grid->AppendCols(100);

    int ir = grid->GetNumberRows();
    grid->DeleteRows(0, ir);
    grid->AppendRows(ir);


}


// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// GridApp
// ----------------------------------------------------------------------------

class GridApp : public wxApp
{
public:
    bool OnInit();
};

bool GridApp::OnInit()
{
    GridFrame *frame = new GridFrame;
    frame->Show(true);

    return true;
}

IMPLEMENT_APP( GridApp )
