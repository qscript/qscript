#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <fstream>
#include <set>
#include "qtm_data_file.h"
#include "log_mesg.h"
#include "qtm_datafile_conf_parser.h"
#include "named_range.h"
#include "question.h"


set<string> qtm_include_files;


namespace qtm_data_file_ns {

using std::stringstream;
using std::cout;
using std::cerr;
using std::endl;
using std::fstream;
using std::pair;
fstream qtm_data_file_writer_log;


// This function operates on the 
// assumption that all columns for
// a question are allocated in the same block
// 20-mar-2011 - split into 2 funcs
// - write_multi_coded_data
// - write_single_coded_data - below is wrong
// and assumes everything is multi_coded
void QtmDataDiskMap::write_data ()
{

	if (q->no_mpn == 1) {
		write_single_code_data();
	} else {
		write_multi_code_data();
	}

}

void QtmDataDiskMap::write_single_code_data()
{
	if (q->input_data.begin() != q->input_data.end())
		qtmDataFile_.write_single_code_data (startPosition_, width_, *q->input_data.begin(), q);
}

void QtmDataDiskMap::write_multi_code_data()
{
	stringstream message;
	message << "ENTER writing : " << q->questionName_;
	for (int32_t i=0; i<q->loop_index_values.size(); ++i) {
		message << "." << q->loop_index_values[i];
	}
	message << endl;
	qtm_data_file_writer_log << LOG_MESSAGE(message.str());
	for (set<int>::iterator it = q->input_data.begin();
		it != q->input_data.end(); ++it) {
		int code = *it;
		int qtm_code = code % 10 == 0 ? 10 : code % 10 ;
		int bucket_no = (code % 10 == 0) ? (code / 10) -1 : code / 10 ;
		codeBucketVec_[bucket_no].codeVec_.push_back(qtm_code);
		qtm_data_file_writer_log << "putting code: " << code << " into bucket no: " << bucket_no << "\n";
	}
	qtm_data_file_writer_log << "codeBucketVec_.size: " << codeBucketVec_.size() << endl;
	for (int i=0; i<codeBucketVec_.size(); ++i) {
		if (codeBucketVec_[i].codeVec_.size() == 0) {
		} else if (codeBucketVec_[i].codeVec_.size() == 1) {
			qtmDataFile_.write_single_code_data (startPosition_ + i, 1, 
					codeBucketVec_[i].codeVec_[0], q);
		} else {
			qtm_data_file_writer_log << " writing bucket " << i << " data at col position: "
				<< startPosition_ +i +1 << endl; // remember index = 0 => data file col 1
			qtmDataFile_.write_multi_code_data (startPosition_ + i, codeBucketVec_[i].codeVec_, q);
		}
	}
}

QtmDataDiskMap::QtmDataDiskMap(AbstractQuestion * p_q,
		QtmDataFile & p_qtm_data_file )
	:
	q(p_q), startPosition_(-1),
	width_(-1), totalLength_(-1),
	qtmDataFile_(p_qtm_data_file)
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
		else if (max_code < 1000000000) {
			width_ = 9;
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
		
	startPosition_ = qtmDataFile_.fileXcha_.UpdateCurrentColumn(width_);
	int noBuckets = width_;
	for (int i=0; i< noBuckets; ++i) {
		codeBucketVec_.push_back(CodeBucket());	
	}
}

int QtmFileCharacteristics::UpdateCurrentColumn(int width_)
{
	if (qtmFileMode_ != READ_EQ_0) {
		if (width_ > (cardDataWrapAroundAt_ - cardDataStartAt_)) {
			cerr << " the questions width_ exceeds the width_ that can fit in a single card ... "
				<< __FILE__ << ","  << __LINE__ << ","  << __PRETTY_FUNCTION__ << endl;
			cerr << "exiting ...\n";
			exit(1);
		}
	
		if (currentColumn_ + width_ >= cardDataWrapAroundAt_)  {
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

void QtmDataDiskMap::print_qax(fstream & qax_file)
{
	qax_file << "l " << q->questionName_ ;
	for (int i=0; i< q->loop_index_values.size(); ++i) {
		qax_file << "_" << q->loop_index_values[i];
	}
	qax_file << endl;
	qax_file << "*include qttl.qin;qno=" << q->questionName_;
	for (int i=0; i< q->loop_index_values.size(); ++i) {
		qax_file << "." << q->loop_index_values[i];
	}
	qax_file << ";qtit=" << q->questionText_ << ";" << endl;
	qax_file << "*include base.qin" << endl;
	if (NamedStubQuestion * n_q = dynamic_cast<NamedStubQuestion*>(q)) {
		if (n_q->nr_ptr) {
			qax_file << "*include " << n_q->nr_ptr->name << ".qin;"
			<< "col(a)=" << startPosition_ + 1
			<< endl;
		}
		set<string>::iterator it = qtm_include_files.find(n_q->nr_ptr->name);
		if (it == qtm_include_files.end()) {
			stringstream fname;
			fname << n_q->nr_ptr->name << ".qin";
			fstream qtm_include_file (fname.str().c_str(), 
					std::ios_base::out | std::ios_base::trunc);
			for (int i=0; i<n_q->nr_ptr->stubs.size(); ++i) {
				qtm_include_file << "n01"
					<< n_q->nr_ptr->stubs[i].stub_text
					<< "; c=c";
				int the_code = n_q->nr_ptr->stubs[i].code;
				if (n_q->no_mpn>1) {
					qtm_include_file << "a";
					int dividend = the_code/10;
					int remainder = the_code%10;
					if (remainder == 0) {
						qtm_include_file 
							<< dividend - 1 << "'"
							<< remainder << "'";
					} else {
						qtm_include_file 
							<< dividend  << "'"
							<< remainder << "'";
					}
				} else {
					if (width_==1) {
						qtm_include_file << "a0'";
						if (the_code < 10) {
							qtm_include_file << the_code
								<< "'";
						} else {
							if (the_code == 10) {
								qtm_include_file << "'0'";
							} else if (the_code == 11) {
								qtm_include_file << "'-'";
							} else if (the_code == 12) {
								qtm_include_file << "'&'";
							} else {
								stringstream error_str;
								error_str << "RUNTIME ERROR code for single coded qtm data exceeds 12... exiting " << endl;
								cerr << LOG_MESSAGE(error_str.str());
								exit(1);
							}
						}
					} else {
						qtm_include_file << "(a0,a"
							<< width_-1 << ").eq."
							<< the_code;
					}
				}
				qtm_include_file << endl;
			}
			qtm_include_files.insert(n_q->nr_ptr->name);
		}
	} else if (RangeQuestion * r_q = dynamic_cast<RangeQuestion*>(q)) {
		qax_file << "*include " << q->questionName_ << ".qin;"
			<< "col(a)=" << startPosition_ + 1
			<< ";"
			<< endl;
	}
	qax_file << endl;
}


QtmFileCharacteristics::QtmFileCharacteristics(int p_cardDataStartAt_, 
		int p_cardWrapAroundAt,
		bool p_dontBreakQuestionsAtBoundary, QtmFileMode p_qtmFileMode)
	: cardDataStartAt_(p_cardDataStartAt_), cardDataWrapAroundAt_(p_cardWrapAroundAt),
	  dontBreakQuestionsAtBoundary_(p_dontBreakQuestionsAtBoundary),
	  qtmFileMode_(p_qtmFileMode),
	  currentCard_(-1), currentColumn_(-1), multiplier_(-1),
	  maxColList_()
{
	/*
	int cardDataWrapAroundAt_;
	int cardDataStartAt_;
	bool dontBreakQuestionsAtBoundary_;
	QtmFileMode qtmFileMode_;
	int currentCard_;
	int currentColumn_;
	int multiplier_;
	*/
	/*
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
		// we dont care about cardDataWrapAroundAt_ or cardDataStartAt_ 
	} else if (qtmFileMode_ == READ_EQ_1) {
		if (cardDataWrapAroundAt_ > 999) {
			cerr << " cardDataWrapAroundAt_ = " << cardDataWrapAroundAt_ << " which is an invalid value for READ_EQ_1 ... exiting" << endl;
			exit(1);
		}
	} else if (qtmFileMode_ == READ_EQ_2) {
		if (cardDataWrapAroundAt_ > 99) {
			cerr << " cardDataWrapAroundAt_ = " << cardDataWrapAroundAt_ << " which is an invalid value for READ_EQ_2 ... exiting" << endl;
			exit(1);
		}
	} else {
		cerr << " impossible - the earlier line of code should have terminated the program" << endl;
		cerr  << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
		exit (1);
	}
	if (cardDataStartAt_ < 1) {
		cerr	<< " invalid value for cardDataStartAt_: " << cardDataStartAt_ 
			<< ", " <<  __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
		exit(1);
	}
	currentColumn_ = cardDataStartAt_;
	currentCard_ = 1;
	*/
}

void QtmFileCharacteristics::NextCard()
{
	if (qtmFileMode_ == READ_EQ_0) {
		cerr << " this function should never be called when qtmFileMode_ == READ_EQ_0"
			<< __FILE__ << ","  << __LINE__ << ","  << __PRETTY_FUNCTION__ << endl;
		cerr << "exiting ...\n";
		exit(1);
	}
	maxColList_.push_back( pair<int, int>(currentCard_, currentColumn_) );
	++currentCard_;
	currentColumn_ = cardDataStartAt_;
}

int QtmFileCharacteristics::GetCurrentColumnPosition()
{
	return currentCard_ * multiplier_
			+ currentColumn_;
}

QtmDataFile::QtmDataFile()
	: cardVec_(), fileXcha_(/*11,  */
		qtm_datafile_conf_parser_ns::crd_start,
		qtm_datafile_conf_parser_ns::crd_end, true, 
		qtm_datafile_conf_parser_ns::qtm_file_mode)
{
	cout << "qtm_datafile_conf_parser_ns::crd_start: " 
		<< qtm_datafile_conf_parser_ns::crd_start 
		<< endl;
	cout << "qtm_datafile_conf_parser_ns::crd_end: " 
		<< qtm_datafile_conf_parser_ns::crd_end 
		<< endl;
}

// This function cannot be used to write codes '-', '&'
void QtmDataFile::write_multi_code_data (int column, vector<int> & data,
		AbstractQuestion * q)
{
	bool valid_col_ref = CheckForValidColumnRef (column);
	if (!valid_col_ref) {
		stringstream s;
		s << " invalid col reference ... exiting " << endl;
		s << "question name: " << q->questionName_;
		for (int32_t i=0; i<q->loop_index_values.size(); ++i) {
			s << "." << q->loop_index_values[i];
		}
		cerr << LOG_MESSAGE(s.str());
		exit(1);
	}
	if (data.size() == 0) {
		stringstream warn_str;
		warn_str << "RUNTIME WARNING we should not be invoked when data.size() == 0 " << endl;
		cerr << warn_str.str();
	} else if (data.size() == 1) {
		pair<int,int> cc = ConvertToCardColumn (column);
		//cout << "cc.first: " << cc.first << ", cc.second: " << cc.second << endl;
		//cout 	<< "cardVec_.size(): " << cardVec_.size() << endl;
			//<< "cardVec_.data_.size(): " << cardVec_[cc.first].data_.size()
			//<< endl;
		cardVec_[cc.first].data_[cc.second] = data[data.size()-1] % 10;
	} else /* if (data.size() > 1 */ {
		char c = check_for_exceptions (data);
		pair<int,int> cc = ConvertToCardColumn (column);
		if (c) {
			cardVec_[cc.first].data_[cc.second] = c;
			qtm_data_file_writer_log << "check_for_exceptions found exception returned: " 
				<< c << endl;
			return;
		}
		cardVec_[cc.first].data_[cc.second] = '*'; // multi punch data
		char mp_data[2]  = { 64, 64 };
		for (int i=0; i<data.size(); ++i) {
			int code = data[i];
			if (code == 1) {
				mp_data[0] |= 1<<2;
			} else if (code == 2) {
				mp_data[0] |= 1<<1;
			} else if (code == 3) {
				mp_data[0] |= 1<<0;
			} else if (code == 10 /* '0' */) {
				mp_data[0] |= 1<<3;
			} else if (code == 11 /* '-' */) {
				mp_data[0] |= 1<<4;
			} else if (code == 12 /* '&' */) {
				mp_data[0] |= 1<<5;
			} else if (code == 4) {
				mp_data[1] |= 1<<5;
			} else if (code == 5) {
				mp_data[1] |= 1<<4;
			} else if (code == 6) {
				mp_data[1] |= 1<<3;
			} else if (code == 7) {
				mp_data[1] |= 1<<2;
			} else if (code == 8) {
				mp_data[1] |= 1<<1;
			} else if (code == 9) {
				mp_data[1] |= 1<<0;
			}
		}
		cardVec_[cc.first].multiPunchData_.push_back(mp_data[0]);
		cardVec_[cc.first].multiPunchData_.push_back(mp_data[1]);
	}
}

pair<int, int> QtmDataFile::ConvertToCardColumn (int column) 
{
	if (fileXcha_.qtmFileMode_ == READ_EQ_0) {
		// flat file - single card - column is the actual position
		return pair<int, int> (0, column);
	} else if (fileXcha_.qtmFileMode_ == READ_EQ_1) {
		return pair<int, int> (column/1000 -1, column%1000);
	} else if (fileXcha_.qtmFileMode_ == READ_EQ_2) {
		return pair<int, int> (column/100 - 1, column%100);
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
			cerr << LOG_MESSAGE(error_str.str());
			exit(1);
			return false;
		}
	} else if (fileXcha_.qtmFileMode_ == READ_EQ_2) {
		if (column < 100) {
			stringstream error_str;
			error_str << "RUNTIME ERROR we should not be invoked when data.size() == 0 " << endl;
			cerr << LOG_MESSAGE(error_str.str());
			exit(1);
			return false;
		}
	}
	return true;
}

void QtmDataFile::write_record_to_disk(std::fstream & disk_file, int ser_no)
{
	char end_of_data_marker = 127;
	stringstream mesg;
	mesg << " : invoked with ser_no: " << ser_no << endl;
	qtm_data_file_writer_log << LOG_MESSAGE(mesg.str());
	for (int i=0; i<cardVec_.size(); ++i) {
		char * the_single_coded_data = new char [cardVec_[i].data_.size()+1];
		the_single_coded_data[cardVec_[i].data_.size()] = '\0';
		using std::copy;
		copy (cardVec_[i].data_.begin(), cardVec_[i].data_.end(), the_single_coded_data);
		stringstream ser_no_str;
		ser_no_str << ser_no;
		if (ser_no_str.str().length() > (qtm_datafile_conf_parser_ns::ser_end
					-qtm_datafile_conf_parser_ns::ser_start+1)) {
			stringstream error_str;
			error_str << "RUNTIME ERROR when writing datafile - space reserved for ser_no is not enough\n...exiting\n";
			cerr << LOG_MESSAGE(error_str.str());
			exit(1);
		}
		qtm_data_file_writer_log << " ser_start: " << qtm_datafile_conf_parser_ns::ser_start
			<< endl;

		for (int j=0; j<ser_no_str.str().length(); ++j) {
			the_single_coded_data[j+qtm_datafile_conf_parser_ns::ser_start-1] =  ser_no_str.str()[j];
			qtm_data_file_writer_log << " output char : " << ser_no_str.str()[j] 
				<< " of serial to data file: "
				<< endl;
		}

		stringstream crd_no_str;
		crd_no_str << i+1;
		if (crd_no_str.str().length() > (qtm_datafile_conf_parser_ns::crd_end
					-qtm_datafile_conf_parser_ns::crd_start+1)) {
			stringstream error_str;
			error_str << "RUNTIME ERROR when writing datafile - space reserved for crd_no is not enough\n...exiting\n";
			cerr << LOG_MESSAGE(error_str.str());
			exit(1);
		}
		for (int j=0; j<crd_no_str.str().length(); ++j) {
			the_single_coded_data[j+qtm_datafile_conf_parser_ns::crd_start-1] =  crd_no_str.str()[j];
			qtm_data_file_writer_log << " output char : " << crd_no_str.str()[j] 
				<< " of crd no to data file: "
				<< endl;
		}
		disk_file << the_single_coded_data
			<<  end_of_data_marker;

		//<< endl ; //<< cardVec_[i].multiPunchData_ << endl;
		for (int j=0; j<cardVec_[i].multiPunchData_.size(); ++j) {
			disk_file << cardVec_[i].multiPunchData_[j];
		}
		disk_file << endl;
		delete [] the_single_coded_data;
	}
}

void QtmDataFile::AllocateCards()
{
	// last card is never added by NextCard - could be empty - add it now
	fileXcha_.maxColList_.push_back( pair<int, int>(fileXcha_.currentCard_, fileXcha_.currentColumn_) );
	cout << " allocated currentCard_: " << fileXcha_.currentCard_ 
		<< " currentColumn_: " << fileXcha_.currentColumn_ 
		<< endl;
	for (int i=0; i<fileXcha_.maxColList_.size(); ++i) {
		// pair <card, col>
		pair <int, int> card_col = fileXcha_.maxColList_[i];
		cardVec_.push_back ( Card(card_col.second) );
		bool not_the_last_card = i < fileXcha_.maxColList_.size()-1;
		if (not_the_last_card) {
			pair <int, int> next_card_col  = fileXcha_.maxColList_[i+1]; 
			// above is safe
			if (next_card_col.first - card_col.first > 1) {
				// blank cards in between 
				for (int j=card_col.first+1; j< next_card_col.first;
						++j) {
					cardVec_.push_back ( Card(0) );
				}
			}
		}
	}
}

Card::Card (int no_cols)
	: data_(no_cols, ' '), multiPunchData_()
{ }


void QtmDataFile::Reset ()
{
	for (int i=0; i<cardVec_.size(); ++i) {
		for (int j=0; j<cardVec_[i].data_.size(); j++) {
			cardVec_[i].data_[j] = ' ';
		}
		cardVec_[i].multiPunchData_.clear();
		cardVec_[i].multiPunchData_.resize(0);
	}
}

void QtmDataDiskMap::Reset()
{
	for (int i=0; i<codeBucketVec_.size(); ++i) {
		codeBucketVec_[i].codeVec_.clear();
		codeBucketVec_[i].codeVec_.resize(0);
	}
	//qtmDataFile_.Reset();
}

void QtmDataFile::write_single_code_data (int column, int width, int code, AbstractQuestion *q)
{
	stringstream s;
	if (width == 1) {
		if (code==10) {
			s << "0";
		} else if (code == 11) {
			s << "-";
		} else if (code == 12) {
			s << "&";
		}  else {
			s << code;
		}
	} else {
		s << code;
	}

	if (s.str().length() > width) {
		stringstream error_str;
		error_str << " width of single code data > width allocated ... internal compiler error - this error should have been caught at an earlier stage \n";
		error_str << "question name: " << q->questionName_;
		for (int32_t i=0; i<q->loop_index_values.size(); ++i) {
			error_str << "." << q->loop_index_values[i];
		}
		error_str << ", code: " << code << endl;
		error_str << "... exiting\n";
		cerr << LOG_MESSAGE(error_str.str());
		exit(1);
	}
	pair<int,int> cc = ConvertToCardColumn (column);
	// cerr << " ConvertToCardColumn: card: " << cc.first 
	// 	<< " col: " << cc.second 
	// 	<< endl;
	// cerr	<< "cardVec_.length(): " << cardVec_.size() << endl
	// 	<< "cardVec_[" << cc.first << "].data_.length(): " 
	// 	<< cardVec_[cc.first].data_.size() << endl;
	// cerr << "s.str().c_str()[0]: " << s.str().c_str()[0] << endl;
	//cerr << & (s.str().c_str()[s.str().length()]) << endl;
	//const char * ptr1 = & (s.str().c_str()[0]);  
	//const char * ptr2 = & (s.str().c_str()[s.str().length()]);
	char * buffer = new char[s.str().length()+1];
	strcpy (buffer, s.str().c_str());
	//cout << "[0]: " << *ptr1 << endl;
	vector<char>::iterator it = cardVec_[cc.first].data_.begin() + cc.second;
	std::copy (&buffer[0], &buffer[s.str().length()], it );
	delete[] buffer;
	//std::copy (& s.str()[0], &s.str()[s.str().length()], it);
}

using std::map;
map <int, char> table_of_exceptions;

void init()
{
	qtm_data_file_writer_log.open("qtm_data_file_writer.log", std::ios_base::trunc | std::ios_base::out);
	if (!qtm_data_file_writer_log) {
		cerr << " unable to open qtm_data_file_writer.log for writing ... exiting\n";
		exit(1);
	}
}

void init_exceptions()
{
	for (int code1=1; code1<=9; ++code1) {
		for (int code2=10; code2<=12; ++code2) {
			int index = (code1*100+code2);
			if (code2 == 10) {
				table_of_exceptions[index] = 'R' + code1-1;
			} else if (code2 == 11) {
				table_of_exceptions[index] = 'J' + code1-1;
			} else if (code2 == 12) {
				table_of_exceptions[index] = 'A' + code1-1;
			}
		}
	}

	table_of_exceptions[110] = '/';
	table_of_exceptions[1011] = '}';
	table_of_exceptions[1012] = '{';
	table_of_exceptions[208] = ':';
	table_of_exceptions[308] = '#';
	table_of_exceptions[408] = '@';
	table_of_exceptions[508] = '\'';
	table_of_exceptions[608] = '=';
	table_of_exceptions[708] = '"';



	for (int code1=1; code1<=9; ++code1) {
		for (int code2=10; code2<=11; ++code2) {
			for (int code3=code2+1; code3<=12; ++code3) {
				int index = code1*10000 +code2*100 + code3;
				if (code2 == 10 && code3 == 11) {
					table_of_exceptions[index] = 'r' + code1-1;
				} else if (code2 == 10 && code3 == 12) {
					table_of_exceptions[index] = 'a' + code1-1;
				} else if (code2 == 11 && code3 == 12) {
					table_of_exceptions[index] = 'j' + code1-1;
				}
			}
		}
	}
	table_of_exceptions[11011] = '~';
	table_of_exceptions[10812] = '`';
	table_of_exceptions[20810] = '\\';
	table_of_exceptions[20811] = '!';
	table_of_exceptions[20812] = '|';
	table_of_exceptions[30810] = ',';
	table_of_exceptions[30811] = '$';
	table_of_exceptions[30812] = '.';

	table_of_exceptions[40810] = '%';
	// table_of_exceptions[40811] = '*'
	table_of_exceptions[40812] = '<';

	table_of_exceptions[50810] = '_';
	table_of_exceptions[50811] = ')';
	table_of_exceptions[50812] = '(';

	table_of_exceptions[60810] = '>';
	table_of_exceptions[60811] = ';';
	table_of_exceptions[60812] = '+';
}

char check_for_exceptions(vector<int> & data)
{
	if (data.size() == 2 || data.size() == 3) {
		vector<int> data_copy = data;
		sort(data_copy.begin(), data_copy.end());
		int index = 0;
		if (data_copy.size() == 2) {
			index = data_copy[0]*100+data_copy[1];
		} else if (data_copy.size() == 3) {
			index = data_copy[0]*10000+data_copy[1]*100 + data_copy[2];
		}
		if (table_of_exceptions.find(index) != table_of_exceptions.end()) {
			return table_of_exceptions[index];
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

void QtmDataFile::Initialize()
{
	fileXcha_.Initialize();


}

void QtmFileCharacteristics::Initialize()
{
	cardDataStartAt_ = qtm_datafile_conf_parser_ns::data_start_col;
	cardDataWrapAroundAt_ = qtm_datafile_conf_parser_ns::data_end_col;
	qtmFileMode_ = qtm_datafile_conf_parser_ns::qtm_file_mode;
	cout << "cardDataStartAt_: " << cardDataStartAt_ 
		<< " cardDataWrapAroundAt_: " << cardDataWrapAroundAt_
		<< endl;

	
	if (qtmFileMode_ == READ_EQ_0) {
		multiplier_ = 1;
	} else if (qtmFileMode_ == READ_EQ_1) {
		multiplier_ = 1000;
	} else if (qtmFileMode_ == READ_EQ_2) {
		multiplier_ = 100;
	} else {
		cerr << "error in setting qtmFileMode_ in " 
			<< __PRETTY_FUNCTION__ << ", " 
			<< __FILE__ << ", " 
			<< __LINE__ << endl;
		cerr << "exiting ...\n";
		exit(1);
	}
	if (qtmFileMode_ == READ_EQ_0) {
		// we dont care about 
		// cardDataWrapAroundAt_ or cardDataStartAt_ 
	} else if (qtmFileMode_ == READ_EQ_1) {
		if (cardDataWrapAroundAt_ > 999) {
			cerr    << " cardDataWrapAroundAt_ = " 
				<< cardDataWrapAroundAt_ 
				<< " which is an invalid value for READ_EQ_1 ... exiting" << endl;
			exit(1);
		}
	} else if (qtmFileMode_ == READ_EQ_2) {
		if (cardDataWrapAroundAt_ > 99) {
			cerr << " cardDataWrapAroundAt_ = " 
				<< cardDataWrapAroundAt_ 
				<< " which is an invalid value for READ_EQ_2 ... exiting" << endl;
			exit(1);
		}
	} else {
		cerr << " impossible - the earlier line of code should have terminated the program" << endl;
		cerr  << __FILE__ << ", " 
			<< __LINE__ << ", " 
			<< __PRETTY_FUNCTION__ << endl;
		exit (1);
	}
	if (cardDataStartAt_ < 1) {
		cerr	<< " invalid value for cardDataStartAt_: " << cardDataStartAt_ 
			<< ", " <<  __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
		exit(1);
	}
	currentColumn_ = cardDataStartAt_;
	currentCard_ = 1;
}

}
