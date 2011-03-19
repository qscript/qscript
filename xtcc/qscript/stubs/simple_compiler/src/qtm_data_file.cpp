#include <sstream>
#include <cstdlib>
#include <algorithm>
#include "qtm_data_file.h"
#include "log_mesg.h"


namespace qtm_data_file_ns {

using std::stringstream;
using std::cout;
using std::cerr;
using std::endl;
using std::fstream;
using std::pair;

void QtmDataDiskMap::write_data (QtmDataFile & p_qtm_data_file)
{

	for (set<int>::iterator it = q->input_data.begin();
	it != q->input_data.end(); ++it) {
		int code = *it;
		int bucket_no = code / 10;
		codeBucketVec_[bucket_no].codeVec_.push_back(code);

		stringstream code_str;
		code_str << code;
		cout << "putting code: " << code << " into bucket no: " << bucket_no << "\n";
	}

	for (int i=0; i<codeBucketVec_.size(); ++i) {
#if 0	
		if (codeBucketVec_[i].codeVec_.size() == 0) {
			// no data 
		} else if (codeBucketVec_[i].codeVec_.size() == 1) {
			// single coded column
		} else /* if (codeBucketVec_[i].codeVec_.size() > 1 */ {
			// multi coded data
		}
#endif /* 0 */
		if (codeBucketVec_[i].codeVec_.size() == 0) {
		} else {
			qtmDataFile_.write_data (startPosition_ + i, codeBucketVec_[i].codeVec_);
		}
		
	}

}


QtmDataDiskMap::QtmDataDiskMap(AbstractQuestion * p_q,
		QtmDataFile & p_qtm_data_file )
	:
	q(p_q), qtmDataFile_(p_qtm_data_file)
{
	int max_code = q->GetMaxCode();
	if (q->no_mpn == 1) {
		if (max_code < 10) {
			width_ = 1;
		}
		else if (max_code < 100) {
			width_ = 2;
		}
		else if (max_code < 1000) {
			width_ = 3;
		}
		else if (max_code < 10000) {
			width_ = 4;
		}
		else if (max_code < 100000) {
			width_ = 5;
		}
		else if (max_code < 1000000) {
			width_ = 6;
		}
		else if (max_code < 10000000) {
			width_ = 7;
		}
		else if (max_code < 100000000) {
			width_ = 8;
		}
		else {
			cout	<< " max_code " << max_code << " for question: " 
				<< q->questionName_ << " exceeds max length = 8 we are programmed to handled ... exiting " 
				<< __FILE__ << ","  << __LINE__ << ","  << __PRETTY_FUNCTION__ << endl;
			exit(1);
		}
	} else if (q->no_mpn > 1) {
		width_ = max_code % 10 == 0 ? (max_code / 10) : ( (max_code / 10) + 1); 
			// acn puts code 10 in the same column as code '0', 
				// nop (now gfk) puts it in the next column as code '0'
				// if this program is used by both companies
				// then will need to add a flag - nop/acn to create accordingly
	} else {
		cerr << "Internal compiler error - detected at runtime. q->no_mpn should be >= 1 ... "
			<< "q->questionName_: " << q->questionName_ 
			<< ", q->no_mpn: " << q->no_mpn 
			<< __FILE__ << ", " << __LINE__ 
			<< endl;
		cerr << " ... exiting\n";
		exit(1);
	}
	totalLength_ = width_;
		
	/*
	startPosition_ = file_xcha.GetCurrentColumnPosition();
	if ( (qtmFileMode_ != READ_EQ_0) && 
		(startPosition_ + width_) >= file_xcha.cardWrapAroundAt_) {
		if (dontBreakQuestionsAtBoundary_) {
			file_xcha.NextCard();
			startPosition_ = file_xcha.cardStartAt_;
		} else {
			cerr << " dontBreakQuestionsAtBoundary_ == false is unhandled case by algorithm " 
				<< __FILE__ << ","  << __LINE__ << ","  << __PRETTY_FUNCTION__ << endl;
			cerr << "exiting ...\n";
			exit(1);
		}
	}
	*/
	startPosition_ = qtmDataFile_.fileXcha_.UpdateCurrentColumn(width_);
	int noBuckets = width_;
	for (int i=0; i< noBuckets; ++i) {
		codeBucketVec_.push_back(CodeBucket());	
	}
}

int QtmFileCharacteristics::UpdateCurrentColumn(int width_)
{
	if (qtmFileMode_ != READ_EQ_0) {
		if (width_ > (cardWrapAroundAt_ - cardStartAt_)) {
			cerr << " the questions width_ exceeds the width_ that can fit in a single card ... "
				<< __FILE__ << ","  << __LINE__ << ","  << __PRETTY_FUNCTION__ << endl;
			cerr << "exiting ...\n";
			exit(1);
		}
	
		if (currentColumn_ + width_ >= cardWrapAroundAt_)  {
			NextCard();
		}
	}
	int question_pos = GetCurrentColumnPosition();
	currentColumn_ += width_;
	return question_pos;
}


void QtmDataDiskMap::print_map(fstream & map_file)
{
	map_file << q->questionName_;
	if (q->loop_index_values.size()) {
		for (int i=0; i< q->loop_index_values.size(); ++i) {
			map_file << "." << q->loop_index_values[i];
		}
	}
	map_file << ",			";
	map_file << width_ << ",	";
	map_file << q->no_mpn << ",	";
	map_file << startPosition_+1 << ",	";
	map_file << startPosition_ + totalLength_  << "\n";
}



QtmFileCharacteristics::QtmFileCharacteristics(int p_cardStartAt_, int p_cardWrapAroundAt,
		bool p_dontBreakQuestionsAtBoundary, QtmFileMode p_qtmFileMode)
	: cardStartAt_(p_cardStartAt_), cardWrapAroundAt_(p_cardWrapAroundAt),
	  dontBreakQuestionsAtBoundary_(p_dontBreakQuestionsAtBoundary),
	  qtmFileMode_(p_qtmFileMode)
{
	/*
	int cardWrapAroundAt_;
	int cardStartAt_;
	bool dontBreakQuestionsAtBoundary_;
	QtmFileMode qtmFileMode_;
	int currentCard_;
	int currentColumn_;
	int multiplier_;
	*/
	if (qtmFileMode_ == READ_EQ_0) {
		multiplier_ = 1;
	} else if (qtmFileMode_ == READ_EQ_1) {
		multiplier_ = 1000;
	} else if (qtmFileMode_ == READ_EQ_2) {
		multiplier_ = 100;
	} else {
		cerr << "error in setting qtmFileMode_ in " << __PRETTY_FUNCTION__ << ", " << __FILE__ << ", " << __LINE__ << endl;
		cerr << "exiting ...\n";
		exit(1);
	}
	if (qtmFileMode_ == READ_EQ_0) {
		// we dont care about cardWrapAroundAt_ or cardStartAt_ 
	} else if (qtmFileMode_ == READ_EQ_1) {
		if (cardWrapAroundAt_ > 999) {
			cerr << " cardWrapAroundAt_ = " << cardWrapAroundAt_ << " which is an invalid value for READ_EQ_1 ... exiting" << endl;
			exit(1);
		}
	} else if (qtmFileMode_ == READ_EQ_2) {
		if (cardWrapAroundAt_ > 99) {
			cerr << " cardWrapAroundAt_ = " << cardWrapAroundAt_ << " which is an invalid value for READ_EQ_2 ... exiting" << endl;
			exit(1);
		}
	} else {
		cerr << " impossible - the earlier line of code should have terminated the program" << endl;
		cerr  << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
		exit (1);
	}
	if (cardStartAt_ < 1) {
		cerr	<< " invalid value for cardStartAt_: " << cardStartAt_ 
			<< ", " <<  __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
		exit(1);
	}
	currentColumn_ = cardStartAt_;
	currentCard_ = 1;
}

void QtmFileCharacteristics::NextCard()
{
	if (qtmFileMode_ == READ_EQ_0) {
		cerr << " this function should never be called when qtmFileMode_ == READ_EQ_0"
			<< __FILE__ << ","  << __LINE__ << ","  << __PRETTY_FUNCTION__ << endl;
		cerr << "exiting ...\n";
		exit(1);
	}
	++currentCard_;
	currentColumn_ = cardStartAt_;
}

int QtmFileCharacteristics::GetCurrentColumnPosition()
{
	return currentCard_ * multiplier_
			+ currentColumn_;
}

QtmDataFile::QtmDataFile()
	: fileXcha_(11, 80, true, READ_EQ_2)
{ }

// This function cannot be used to write codes '-', '&'
void QtmDataFile::write_data (int column, vector<int> & data)
{
	bool valid_col_ref = CheckForValidColumnRef (column);
	if (!valid_col_ref) {
		stringstream s;
		s << " invalid col reference ... exiting " << endl;
		LOG_MESSAGE(s.str());
		exit(1);
	}
	if (data.size() == 0) {
		stringstream warn_str;
		warn_str << "RUNTIME WARNING we should not be invoked when data.size() == 0 " << endl;
		cerr << warn_str.str();
	} else if (data.size() == 1) {
		pair<int,int> cc = ConvertToCardColumn (column);
		cardVec_[cc.first].data_[cc.second] == data[data.size()-1] % 10;
	} else /* if (data.size() > 1 */ {
		pair<int,int> cc = ConvertToCardColumn (column);
		cardVec_[cc.first].data_[cc.second] == '*'; // multi punch data
	}
}

pair<int, int> QtmDataFile::ConvertToCardColumn (int column) 
{
	if (fileXcha_.qtmFileMode_ == READ_EQ_0) {
		// flat file - single card - column is the actual position
		return pair<int, int> (0, column);
	} else if (fileXcha_.qtmFileMode_ == READ_EQ_1) {
		return pair<int, int> (column/1000, column%1000);
	} else if (fileXcha_.qtmFileMode_ == READ_EQ_2) {
		return pair<int, int> (column/100, column%100);
	} else {
		stringstream error_str;
		error_str << " fileXcha_.qtmFileMode_ has an unknown value " 
			<< endl;
		cerr << LOG_MESSAGE(error_str.str());
		exit(1);
	}
}

bool QtmDataFile::CheckForValidColumnRef (int column)
{
	if (fileXcha_.qtmFileMode_ == READ_EQ_0) {
		// no need to check column references
	} else if (fileXcha_.qtmFileMode_ == READ_EQ_1) {
		if (column < 1000) {
			stringstream error_str;
			error_str << "RUNTIME ERROR we should not be invoked when data.size() == 0 " << endl;
			LOG_MESSAGE(error_str.str());
			exit(1);
			return false;
		}
	} else if (fileXcha_.qtmFileMode_ == READ_EQ_2) {
		if (column < 100) {
			stringstream error_str;
			error_str << "RUNTIME ERROR we should not be invoked when data.size() == 0 " << endl;
			LOG_MESSAGE(error_str.str());
			exit(1);
			return false;
		}
	}
	return true;
}

void QtmDataFile::write_record_to_disk(std::fstream & disk_file)
{
	for (int i=0; i<cardVec_.size(); ++i) {
		char end_of_data_marker = '';
		char * the_single_coded_data = new char [cardVec_[i].data_.size()+1];
		using std::copy;
		copy (cardVec_[i].data_.begin(), cardVec_[i].data_.end(), the_single_coded_data);
		disk_file << the_single_coded_data
			<<  end_of_data_marker ; //<< cardVec_[i].multiPunchData_ << endl;
	}
}

}
