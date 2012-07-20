// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef CSV_UTIL_H_
#define CSV_UTIL_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace Wt {
  class WAbstractItemModel;
}

/**
 * @addtogroup chartsexample
 */
/*@{*/

/*! \brief Utility function that reads a model from a CSV file.
 */

struct TableData {
	string ban_ttl;
	string side_ttl;
	int nRows, nCols;
	vector <string> row_text;
	vector <string> column_text;

	vector <int> col_totals;
	vector <int> abs_int_data; // if there is weighting 
				   // there will be real data
	vector <double> row_pc;
	vector <double> col_pc;
	TableData():
		ban_ttl(), side_ttl(),
		nRows (0), nCols (0), row_text(), column_text(),
		col_totals (), abs_int_data (), row_pc (),
		col_pc()
	{}
	void Print()
	{
		cout << "nRows: " << nRows << ", nCols: " << nCols << endl
			<< "side_ttl: " << side_ttl << endl
			<< "ban_ttl: " << ban_ttl << endl;
		cout << "column_text.size(): " << column_text.size() << endl;
		cout << "col_totals.size(): " << col_totals.size();
		cout << "abs_int_data.size(): " << abs_int_data.size() << endl
			<< "row_pc.size(): " << row_pc.size() << endl
			<< "col_pc.size(): " << col_pc.size() << endl;
	}
	
};

extern void readFromCsv(std::istream& f, //Wt::WAbstractItemModel *model,
			//int numRows = -1, bool firstLineIsHeaders = true
			struct TableData & tbl_data
			);



/*@}*/

#endif // CSV_UTIL_H_
