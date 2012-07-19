/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include <stdlib.h>
#include <boost/tokenizer.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>

#include <Wt/WAbstractItemModel>
#include <Wt/WString>

#include "CsvUtil.h"

using namespace std;

void readFromCsv(std::istream& f, //Wt::WAbstractItemModel *model,
		 int numRows, bool firstLineIsHeaders)
{
  int csvRow = 0;
  enum { Hunt, GetRowAndColumnCount, GetTitles, GetBannerTitles, GetColumnTotals, Skip2Lines, GetTableData};

  int myCurrentState = Hunt, myPreviousState = Hunt;
  int nRows = 0, nCols = 0;
read_another_line:
  while (f) {
    std::string line;
    getline(f, line);

    myPreviousState = myCurrentState;
    cout << "nCols: " << nCols << endl;

    if (f) {
      typedef boost::tokenizer<boost::escaped_list_separator<char> >
	CsvTokenizer;
      CsvTokenizer tok(line);

      int col = 0;
      for (CsvTokenizer::iterator i = tok.begin();
	   i != tok.end(); ++i, ++col) {

#if 0
	if (col >= model->columnCount())
	  model->insertColumns(model->columnCount(),
			       col + 1 - model->columnCount());
#endif /* 0 */

	//if (firstLineIsHeaders && csvRow == 0) {
top_of_state_change_marker:
	if (myCurrentState == Hunt) {
		//model->setHeaderData(col, boost::any(Wt::WString::fromUTF8(*i)));
		Wt::WString ws(Wt::WString::fromUTF8(*i));
		cout << "header: " << ws;
		if (ws == "rows") {
			myCurrentState = GetRowAndColumnCount;
			cout << "this marks the start of a new table: " << endl;
			goto top_of_state_change_marker;

		}
	} 
	if (myCurrentState == GetRowAndColumnCount) {
		++i;
		Wt::WString rows_str(Wt::WString::fromUTF8(*i));
		nRows = atoi (rows_str.toUTF8().c_str()) ;
		cout << "nRows: " << nRows << endl;
		++i; ++i;
		Wt::WString cols_str(Wt::WString::fromUTF8(*i));
		nCols = atoi (cols_str.toUTF8().c_str()) ;
		cout << "nCols: " << nCols << endl;
		cout << " Got GetRowAndColumnCount changing state" << endl;
		myPreviousState = myCurrentState;
		myCurrentState = GetTitles;
		goto read_another_line;
	}
	if (myCurrentState == GetTitles) {
		Wt::WString side_ttl(Wt::WString::fromUTF8(*i));
		cout << side_ttl << endl;
		++i;
		Wt::WString ban_ttl(Wt::WString::fromUTF8(*i));
		cout << ban_ttl << endl;
		myCurrentState = GetBannerTitles;
		goto read_another_line;
	}
	if (myCurrentState == GetBannerTitles) {
		vector <Wt::WString> col_titles;
		cout << "reached here" << endl;
		if (i == tok.end()) {
			cout << "i == tok.end()" << endl; 
		}
			cout << "nCols: " << nCols << endl;
		++i; ++i;
		for (int c=0; c < nCols && i != tok.end(); ++c, ++i) {
			Wt::WString col_ttl(Wt::WString::fromUTF8(*i));
			cout << col_ttl << endl;
			col_titles.push_back (col_ttl);
		}
		myCurrentState = GetColumnTotals;
		goto read_another_line;
	}
#if 0
		else {
	  int dataRow = firstLineIsHeaders ? csvRow - 1 : csvRow;

	  if (numRows != -1 && dataRow >= numRows)
	    return;

#if 0
	  if (dataRow >= model->rowCount())
	    model->insertRows(model->rowCount(),
			      dataRow + 1 - model->rowCount());

#endif /* 0 */

	  boost::any data;
	  std::string s = *i;
	  cout << "data: " << s << ",";

	  char *endptr;

	  if (s.empty())
	    data = boost::any();
	  else {
	    double d = strtod(s.c_str(), &endptr);
	    if (*endptr == 0)
	      data = boost::any(d);
	    else
	      data = boost::any(Wt::WString::fromUTF8(s));
	  }
#if 0
	  model->setData(dataRow, col, data);
#endif /*  0 */
	}
#endif /*  0  */
      }
    }

    ++csvRow;
  }
}

int main ()
{
	std::ifstream f ("tab_UTC_Y-M-D_H-M-S_2012-07-19_11-32-18.csv");
	readFromCsv (f, true);

}
