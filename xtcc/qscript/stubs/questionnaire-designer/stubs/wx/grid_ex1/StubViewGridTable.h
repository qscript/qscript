#ifndef StubViewGridTableData_h
#define StubViewGridTableData_h


#include <string>
#include <vector>

//using namespace std;


struct StubViewGridTableData {
	std::string stub_text;
	int stub_code;
	bool mutex;
	std::string translation;
	StubViewGridTableData (std::string p_stub_text,
			int p_stub_code,
			bool p_mutex);

};

#include <wx/wx.h>
#include <wx/grid.h>


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

class StubViewGridTable : public wxGridTableBase
{
public:

	enum Columns
	{
		Col_StubText,
		Col_StubCode,
		Col_Mutex
	};
	std::vector <std::string> headers_;
	std::vector <StubViewGridTableData> the_data_;
	StubViewGridTable()
	{
		headers_.push_back("Stub Text");
		headers_.push_back("Stub Code");
		headers_.push_back("Mutex");
		headers_.push_back("Translation(Arabic)");
		the_data_.push_back (StubViewGridTableData("Strongly Agree", 1, false));
		the_data_.push_back (StubViewGridTableData("Agree", 2, false));
		the_data_.push_back (StubViewGridTableData("Neutral", 3, false));
		the_data_.push_back (StubViewGridTableData("Disagree", 4, false));
		the_data_.push_back (StubViewGridTableData("Strongly Disagree", 5, false));
	};
	virtual int GetNumberRows();
	virtual int GetNumberCols();
	virtual bool IsEmptyCell (int row, int col);
	virtual wxString GetValue (int row, int col);
	virtual void SetValue( int row, int col, const wxString& value );
	virtual wxString GetColLabelValue( int col );

	//virtual wxString GetTypeName( int row, int col );
	virtual wxString GetTypeName(int WXUNUSED(row), StubViewGridTable::Columns col);
	//virtual bool CanGetValueAs( int row, int col, const wxString& typeName );

	virtual bool CanGetValueAs(int WXUNUSED(row),
				     //StubViewGridTable::Columns col,
				     int col,

				     const wxString& typeName);
	virtual bool CanSetValueAs( int row, int col, const wxString& typeName );

	virtual long GetValueAsLong( int row, int col );
	virtual bool GetValueAsBool( int row, int col );

	virtual void SetValueAsLong( int row, int col, long value );
	virtual void SetValueAsBool( int row, int col, bool value );
	virtual bool InsertRows(size_t pos = 0, size_t numRows = 1);
};


#endif /* StubViewGridTableData */
