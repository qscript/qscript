#ifndef XTCCDATAFILE_H
#define XTCCDATAFILE_H

#include <set>
#include <sstream>
#include <string>
#include "question.h"

class XtccDataFileDiskMap
{
public:

	AbstractQuestion *q_;
	int32_t start_pos;
	int32_t width_;
	int32_t totalLength_;
	XtccDataFileDiskMap(AbstractQuestion * p_q, int32_t p_start_pos)
		: q_(p_q), start_pos(p_start_pos)
	{
		DataType dt1 = q_->dt;
		if (dt1 == INT8_TYPE) {
			width_ = 1; 
		} else if (dt1 == INT16_TYPE) {
			width_ = 2; 
		} else if (dt1 == INT32_TYPE) {
			width_ = 4;
		} else if (dt1 == FLOAT_TYPE) {
			width_ = 4;
		} else if (dt1 == DOUBLE_TYPE) {
			width_ = 8;
		} else {
			cerr << "RUNTIME ERROR unhandled question type: "
				<< __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
				<< endl;
		}
		totalLength_ = q_->no_mpn * width_;
	}
	int GetTotalLength() { return totalLength_; }
	void write_data (char * output_buffer)
	{
		char * ptr = output_buffer + start_pos;
		int no_responses_written = 0;
		void * void_ptr = 0;
		for (std::set<int>::iterator it = q_->input_data.begin();
			it != q_->input_data.end(); ++it)
		{
			int code = *it;
			if (q_->dt == INT8_TYPE) {
				int8_t int8_data = static_cast<int8_t> (code);
				void_ptr = &int8_data;
				char * char_ptr = static_cast<char*>(void_ptr);
				*ptr ++ = * char_ptr ++;
			} else if (q_->dt == INT16_TYPE) {
				int16_t int16_data = static_cast<int16_t> (code);
				void_ptr = &int16_data;
				char * char_ptr = static_cast<char*>(void_ptr);
				*ptr ++ = * char_ptr ++;
				*ptr ++ = * char_ptr ++;
			} else if (q_->dt == INT32_TYPE) {
				void_ptr = &code;
				char * char_ptr = static_cast<char*>(void_ptr);
				*ptr ++ = * char_ptr ++;
				*ptr ++ = * char_ptr ++;
				*ptr ++ = * char_ptr ++;
				*ptr ++ = * char_ptr ++;
			} else if (q_->dt == FLOAT_TYPE) {
				cerr << "file: " << __FILE__ << ", line: " << __LINE__
					<< ", func: " << __PRETTY_FUNCTION__ 
					<< ", unhandled question data type: float" 
					<< endl;
				exit(1);
			} else if (q_->dt == DOUBLE_TYPE) {
				cerr << "file: " << __FILE__ << ", line: " << __LINE__
					<< ", func: " << __PRETTY_FUNCTION__ 
					<< ", unhandled question data type: double" 
					<< endl;
				exit(1);
			} else {
				cerr << "file: " << __FILE__ << ", line: " << __LINE__
					<< ", func: " << __PRETTY_FUNCTION__ 
					<< ", unhandled question data type: else branch " 
					<< endl;
				exit(1);
			}
			++no_responses_written;
			if (no_responses_written > q_->no_mpn)
			{
				cerr << " no of responses in question : " 
					<< q_->questionName_ << " exceeds no allocated ... exiting\n";
				exit(1);
			}
		}
	}
	void print_map(fstream & map_file)
	{
		map_file << q_->questionName_;
		if (q_->loop_index_values.size())
		{
			for (int i=0; i< q_->loop_index_values.size(); ++i)
			{
				map_file << "." << q_->loop_index_values[i];
			}
		}
		map_file << ",			";
		map_file << width_ << ",	";
		map_file << q_->no_mpn << ",	";
		map_file << start_pos+1 << ",	";
		map_file << start_pos + totalLength_  << "\n";
	}

};


#endif /* XTCCDATAFILE_H */
