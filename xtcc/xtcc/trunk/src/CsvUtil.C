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
		 //int numRows, bool firstLineIsHeaders
		 struct TableData & tbl_data
		 )
{
	int csvRow = 0;
	enum { Hunt, GetRowAndColumnCount, GetTitles, GetBannerTitles, GetColumnTotals, Skip2Lines, GetTableData};
	int myCurrentState = Hunt, myPreviousState = Hunt;
	//int nRows = 0, nCols = 0;
	int r = 0;
	//vector <string> table_row_text;
	int skip_2_lines_count = 0;
	enum { Absolutes, RowPercentages, ColumnPercentages };
	int table_data_capture_state = Absolutes;

read_another_line:
	while (f) {
		std::string line;
		getline(f, line);

		myPreviousState = myCurrentState;
		//cout << "nCols: " << nCols << endl;

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
					tbl_data.nRows = atoi (rows_str.toUTF8().c_str()) ;
					cout << "nRows: " << tbl_data.nRows << endl;
					++i; ++i;
					Wt::WString cols_str(Wt::WString::fromUTF8(*i));
					tbl_data.nCols = atoi (cols_str.toUTF8().c_str()) ;
					cout << "nCols: " << tbl_data.nCols << endl;
					cout << " Got GetRowAndColumnCount changing state" << endl;
					myPreviousState = myCurrentState;
					myCurrentState = GetTitles;
					//tbl_data.row_text.resize (nRows);
					//tbl_data.column_text.resize (nCols);
					goto read_another_line;
				}
				if (myCurrentState == GetTitles) {
					//Wt::WString side_ttl(Wt::WString::fromUTF8(*i));
					tbl_data.side_ttl = *i;
					cout << tbl_data.side_ttl << endl;
					++i;
					//Wt::WString ban_ttl(Wt::WString::fromUTF8(*i));
					tbl_data.ban_ttl = *i;
					cout << tbl_data.ban_ttl << endl;
					myCurrentState = GetBannerTitles;
					goto read_another_line;
				}
				if (myCurrentState == GetBannerTitles) {
					//vector <Wt::WString> col_titles;
					cout << "reached here" << endl;
					if (i == tok.end()) {
						cout << "i == tok.end()" << endl; 
					}
					cout << "nCols: " << tbl_data.nCols << endl;
					++i; ++i;
					for (int c=0; c < tbl_data.nCols && i != tok.end(); ++c, ++i) {
						Wt::WString col_ttl (Wt::WString::fromUTF8(*i));
						cout << col_ttl << endl;
						//col_titles.push_back (col_ttl);
						tbl_data.column_text.push_back (*i);
					}
					myCurrentState = GetColumnTotals;
					goto read_another_line;
				}
				if (myCurrentState == GetColumnTotals) {
					//vector <int> col_totals;
					++i; ++i;
					for (int c = 0; c < tbl_data.nCols && i != tok.end(); ++c, ++i) {
						int n = atoi ((*i).c_str());
						tbl_data.col_totals .push_back (n);
						cout << " col total: " << n << ",";
					}
					cout << endl;
					myCurrentState = Skip2Lines;
					goto read_another_line;
				}
				if (myCurrentState == Skip2Lines) {
					if (skip_2_lines_count == 0) {
						cout << "reached skip_2_lines_count == 0" << endl;
						++ skip_2_lines_count;
						myCurrentState = Skip2Lines;
						goto read_another_line;
					}
					if (skip_2_lines_count == 1) {
						cout << "reached skip_2_lines_count == 1" << endl;
						skip_2_lines_count = 0;
						myCurrentState = GetTableData;
						goto read_another_line;
					}
				}
				if (myCurrentState == GetTableData) {
					if (table_data_capture_state == Absolutes) {
						++i; // skip 1st comma
						//cout << "table_data_capture_state: " << table_data_capture_state << endl;
						for (; r < tbl_data.nRows-1; ++r) {
							//cout << "table_row_text: " << *i ;
							tbl_data.row_text.push_back (*i); 
							++i; /*  capture the row stub text and incr pointer */
							cout << "r: " << r << endl;
							for (int c = 0; c < tbl_data.nCols && i != tok.end(); ++c, ++i) {
								int n = atoi ( (*i).c_str());
								cout << " Abs n: " << n;
								tbl_data.abs_int_data.push_back (n);
							}
							cout << endl;
							myCurrentState = GetTableData;
							table_data_capture_state = RowPercentages;
							goto read_another_line;
						}
					}
					if (table_data_capture_state == RowPercentages) {
						//cout << "reached here : RowPercentages" << endl;
						++i; // skip 1st comma
						++i; // 2nd comma also blank
						cout << "RowPC r: " << r << endl;
						for (; r < tbl_data.nRows-1; ) {
							for (int c = 0; c < tbl_data.nCols && i != tok.end(); ++c, ++i) {
								double d = atof ( (*i).c_str());
								cout << " RowPC d: " << d;
								tbl_data.row_pc.push_back (d);
							}
							cout << endl;
							myCurrentState = GetTableData;
							table_data_capture_state = ColumnPercentages;
							goto read_another_line;
						}
					}
					if (table_data_capture_state == ColumnPercentages) {
						++i; // skip 1st comma
						if (i != tok.end() ) {
							++i; // 2nd comma also blank
							cout << "ColPC r: " << r << endl;
							for (; r < tbl_data.nRows-1; ) {
								for (int c = 0; c < tbl_data.nCols && i != tok.end(); ++c, ++i) {
									double d = atof ( (*i).c_str());
									cout << " ColPC d: " << d;
									tbl_data.col_pc.push_back (d);
								}
								cout << endl;
								myCurrentState = GetTableData;
								table_data_capture_state = Absolutes;
								++r;
								if (r >= tbl_data.nRows-1) {
									getline(f, line);
									cout << "returning" << endl;
									return;
								} else {
									goto read_another_line;
								}

							}
						} else {
								++r;
								if (r >= tbl_data.nRows-1) {
									getline(f, line);
									cout << "returning" << endl;
									return;
								} else {
									goto read_another_line;
								}
						}
					}
					if (r >= tbl_data.nRows-2) {
						myCurrentState = Hunt;
						//goto read_another_line;
						//getline(f, line);
						cout << "returning" << endl;
						return;
					} else {
						cout << "should never reach here\n";
						goto read_another_line;
					}
				}
#if 0
					else {
				  int dataRow = firstLineIsHeaders ? csvRow - 1 : csvRow;

				  if (numRows != -1 && dataRow >= numRows)
				    return;

				  if (dataRow >= model->rowCount())
				    model->insertRows(model->rowCount(),
						      dataRow + 1 - model->rowCount());


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
				  model->setData(dataRow, col, data);
				}
#endif /*  0  */
			}
		}
		++csvRow;
	}
}

#if 0
int main ()
{
	std::ifstream f ("tab_UTC_Y-M-D_H-M-S_2012-07-19_11-32-18.csv");
	struct TableData tbl_data;
	readFromCsv (f,
			//, true
			tbl_data);
	tbl_data.Print();

}
#endif /* 0 */
