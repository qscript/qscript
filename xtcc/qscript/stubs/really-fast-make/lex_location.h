#ifndef LEX_LOCATION_H
#define LEX_LOCATION_H
#include <string>
#include <sstream>
// remove after debugging
#include <iostream>

struct LexLocation
{
	std::string fileName_;
	int columnNo_;
	int lineNo_;
	std::stringstream currentLine_;
	LexLocation( int p_columnNo_=1, int p_lineNo_=1)
		: fileName_(), columnNo_(p_columnNo_), lineNo_(p_lineNo_)
		  , currentLine_()
	{ }
	// defining the function here will inline it - which is what we want
	void IncrementLine(int p_nLines) { lineNo_+= p_nLines; }
	void IncrementColumn(int p_nColumns) { columnNo_ += p_nColumns; }
	void ResetColumn()	{ columnNo_ = 1; }
	void ResetLine()	{ lineNo_  = 1; }
	void SetFileName(std::string & p_fname)
	{
		fileName_ = p_fname;
	}
	void AddToCurrentDisplayLine(char *s)
	{
		currentLine_ << s;
	}
	void ResetCurrentDisplayLine()
	{
		currentLine_.str("");
	}
};

#endif /* LEX_LOCATION_H */
