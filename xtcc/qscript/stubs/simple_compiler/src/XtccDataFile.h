#ifndef XTCCDATAFILE_H
#define XTCCDATAFILE_H

#include <set>
#include <sstream>
#include <string>
#include "question.h"
#include "named_range.h"

#include <fstream>
#include <cstdlib>

using namespace std;

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
		map_file << start_pos << ",	";
		map_file << start_pos + totalLength_ -1  << "\n";
	}
	void print_xtcc_include_file (fstream & xtcc_ax_file, string setup_dir);



	string print_xtcc_ax_data_variable_name()
	{
		stringstream ax_data_variable_name;

		ax_data_variable_name	<< q_->questionName_;
		if (q_->loop_index_values.size()) {
			for (int i=0; i< q_->loop_index_values.size(); ++i)
			{
				ax_data_variable_name << "_" << q_->loop_index_values[i];
			}
		}
		if (q_->no_mpn==1) { 
			//xtcc_ax_file << "_data == "
			//	<< nr_ptr->stubs[i].code 
			//	<< ";" 
			//	<< endl;
			ax_data_variable_name << "_data" ;
		} else {
			//xtcc_ax_file << "_arr["
			//	<< nr_ptr->stubs[i].code 
			//	<< "]"
			//	<< " > 0"
			//	<< ";" 
			//	<< endl;
			ax_data_variable_name << "_arr";
		}
		return ax_data_variable_name.str();
	}

	void print_xtcc_ax2(fstream & xtcc_ax_file, string setup_dir);
	void print_xtcc_ax(fstream & xtcc_ax_file, string setup_dir);



	void print_xtcc_tab(fstream & xtcc_ax_file, string setup_dir)
	{
		xtcc_ax_file << "tab " << q_->questionName_ ;
		if (q_->loop_index_values.size())
		{
			for (int i=0; i< q_->loop_index_values.size(); ++i)
			{
				xtcc_ax_file << "_" << q_->loop_index_values[i];
			}
		}
		xtcc_ax_file << " " << "tot_ax;" << endl;
	}

	void print_xtcc_edit_load(fstream & xtcc_ax_file, string setup_dir)
	{
		if (q_->no_mpn == 1) {
			xtcc_ax_file << "\t"
				<< q_->questionName_ ;

			if (q_->loop_index_values.size())
			{
				for (int i=0; i< q_->loop_index_values.size(); ++i)
				{
					xtcc_ax_file << "_" << q_->loop_index_values[i];
				}
			}
			xtcc_ax_file 	<< "_data = c [" 
				<< start_pos  << ", " 
				<< start_pos + totalLength_ - 1
				<< "];" <<endl;
		} else {
			xtcc_ax_file << "\t"
				<< "fld " 
				<< q_->questionName_;
			if (q_->loop_index_values.size())
			{
				for (int i=0; i< q_->loop_index_values.size(); ++i)
				{
					xtcc_ax_file << "_" << q_->loop_index_values[i];
				}
			}
			xtcc_ax_file << "_arr = c (" 
				<< start_pos  << ", " 
				<< start_pos + totalLength_ -1
				<< ") : "  << width_ << ";" << endl;
		}
	}

	void print_edit_var_defns(fstream & xtcc_ax_file, string setup_dir);
	string print_edit_var_defns_str(string setup_dir);

};
XtccDataFileDiskMap* GetXtccQuestionMapEntry(vector <XtccDataFileDiskMap*> & qtm_datafile_question_disk_map,
string name);

vector <XtccDataFileDiskMap*> GetXtccQuestionMapEntryArrayQ
	(vector <XtccDataFileDiskMap*> & qtm_datafile_question_disk_map,
	string name);
string print_recode_edit_xtcc_ax (XtccDataFileDiskMap * driver_q, XtccDataFileDiskMap * recode_q, int index);
string print_recode_edit_xtcc_var_defn (XtccDataFileDiskMap * driver_q, XtccDataFileDiskMap * recode_q, int index);
string print_recode_edit_xtcc_var_init (XtccDataFileDiskMap * driver_q, XtccDataFileDiskMap * recode_q, int index);
string print_recode_edit_xtcc_data_xfer (XtccDataFileDiskMap * driver_q, XtccDataFileDiskMap * leader_recode_q, 
		XtccDataFileDiskMap * recode_q, int index);
string print_recode_edit_xtcc_var_defn_arrayq (XtccDataFileDiskMap * driver_q, vector<XtccDataFileDiskMap *> & recode_q_vec, int index);



#endif /* XTCCDATAFILE_H */
