#include <iostream>

#include "StubViewGridTable.h"

using namespace std;


StubViewGridTableData::StubViewGridTableData (std::string p_stub_text,
			int p_stub_code,
			bool p_mutex)
		: stub_text (p_stub_text),
		  stub_code (p_stub_code),
		  mutex (p_mutex),
		  translation()
	{ }

wxString StubViewGridTable::GetTypeName(int WXUNUSED(row), StubViewGridTable::Columns col)
{
	/*
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
    */
	switch (col) {
		case  StubViewGridTable::Col_StubText:
		    return wxString::Format(_T("%s:500"), wxGRID_VALUE_STRING);

	}

    wxFAIL_MSG(_T("unknown column"));

    return wxEmptyString;
}


bool
StubViewGridTable::CanGetValueAs(int WXUNUSED(row),
                             //StubViewGridTable::Columns col,
			     int col,
                             const wxString& typeName)
{
    if ( typeName == wxGRID_VALUE_STRING )
    {
        return true;
    }
    else if ( typeName == wxGRID_VALUE_BOOL )
    {
        return col == Col_Mutex;
    }
    else if ( typeName == wxGRID_VALUE_NUMBER )
    {
        return col == Col_StubCode ;
    }
    else
    {
        return false;
    }
}


int StubViewGridTable::GetNumberRows()
{
	//return WXSIZEOF(gs_dataStubViewGrid);
	cout << __PRETTY_FUNCTION__ << "called: "
		<< the_data_.size()
		<< endl;
	return the_data_.size();
}


int StubViewGridTable::GetNumberCols()
{
	// yup it's hardcoded
	return 4;
}


bool StubViewGridTable::IsEmptyCell( int WXUNUSED(row), int WXUNUSED(col) )
{
    return false;
}


wxString StubViewGridTable::GetValue( int row, int col )
{
    //const StubViewGridData& gd = gs_dataStubViewGrid[row];
    const StubViewGridTableData &gd = the_data_[row];

    /*
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
    */
	switch ( col ) {
	case StubViewGridTable::Col_StubText: {
		wxString mystring(gd.stub_text.c_str(), wxConvUTF8);
		return mystring;
		}

	case StubViewGridTable::Col_StubCode:
		return wxString::Format(_T("%d"), gd.stub_code);

	case StubViewGridTable::Col_Mutex:
		return gd.mutex ? _T("1") : _T("0");
	}

	return wxEmptyString;
}


void StubViewGridTable::SetValue( int row, int col, const wxString& value )
{
	//StubViewGridData& gd = gs_dataStubViewGrid[row];
	StubViewGridTableData &gd = the_data_[row];

	/*
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
	*/


	switch ( col ) {
	case StubViewGridTable::Col_StubText:
		//wxStrncpy(gd.summary, value, WXSIZEOF(gd.summary));
		gd.stub_text =  std::string(value.mb_str());
		break;

	}
}


bool StubViewGridTable::CanSetValueAs( int row, int col, const wxString& typeName )
{
    return CanGetValueAs(row, col, typeName);
}


long StubViewGridTable::GetValueAsLong( int row, int col )
{
	//const StubViewGridData& gd = gs_dataStubViewGrid[row];
	const StubViewGridTableData & gd = the_data_[row];

	/*
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
	*/

	switch ( col ) {
	case StubViewGridTable::Col_StubCode:
		return gd.stub_code;
	default:
		wxFAIL_MSG(_T("unexpected column"));
		return -1;
	}
}


bool StubViewGridTable::GetValueAsBool( int row, int col )
{
	/*
    if ( col == Col_Opened )
    {
        return gs_dataStubViewGrid[row].opened;
    }
    else
    {
        wxFAIL_MSG(_T("unexpected column"));

        return false;
    }
    */
	if (col == StubViewGridTable::Col_Mutex) {
		return the_data_[row].mutex;
	} else {
		wxFAIL_MSG(_T("unexpected column"));
		return false;
	}
}


void StubViewGridTable::SetValueAsLong( int row, int col, long value )
{
	//StubViewGridData& gd = gs_dataStubViewGrid[row];
	StubViewGridTableData &gd = the_data_[row];

	switch ( StubViewGridTable::Col_StubCode )
	{
	case Col_Priority:
	    gd.mutex = value;
	    break;

	default:
	    wxFAIL_MSG(_T("unexpected column"));
	}
}

void StubViewGridTable::SetValueAsBool( int row, int col, bool value )
{
	if ( col == StubViewGridTable::Col_Mutex ) {
		the_data_[row].mutex = value;
	} else {
		wxFAIL_MSG(_T("unexpected column"));
	}
}


wxString StubViewGridTable::GetColLabelValue( int col )
{
	if (col < 4) {
		wxString mystring(headers_[col].c_str(), wxConvUTF8);
		return mystring;
	} else {
		return wxEmptyString;
	}
}


