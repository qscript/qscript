/*
 * =====================================================================================
 *
 *       Filename:  AbstractQuestionnaire.cpp
 *
 *    Description:  Extract all common functionality of the questionnaire out
 *    			This should simplify code generation
 *
 *        Version:  1.0
 *        Created:  Friday 15 February 2013 10:04:18  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *        Company:
 *
 * =====================================================================================
 */

#include <iostream>
#include <sstream>
#include <map>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "ArrayQuestion.h"
#include "named_range.h"

#include "question_disk_data.h"
#include "AbstractQuestionnaire.h"

extern char * flat_file_output_buffer ;
extern char * xtcc_datafile_output_buffer ;
extern int32_t len_flat_file_output_buffer  ;
extern int32_t len_xtcc_datafile_output_buffer  ;


std::fstream flat_file;
std::fstream xtcc_datafile;
std::fstream qtm_disk_file;

extern map<string, map<int, int> > freq_count;




extern FILE * qscript_stdout;
//extern vector <AsciiFlatFileQuestionDiskMap*> ascii_flatfile_question_disk_map;
//extern vector <XtccDataFileDiskMap*> xtcc_question_disk_map;
//extern vector <qtm_data_file_ns::QtmDataDiskMap*> qtm_datafile_question_disk_map;






// remove this later
using namespace std;

AbstractQuestionnaire * AbstractQuestionnaire::qnre_ptr = 0;

AbstractQuestionnaire::AbstractQuestionnaire (string p_jno)
		:
		  last_question_answered(0), last_question_visited(0),
		  question_list(),
		  back_jump(false),
		  jno (p_jno),
		  ser_no(0),
		  stopAtNextQuestion(false),
		  questions_start_from_here_index(0),
		  ser_no_pos(0),
		  jumpToQuestion(),
		  jumpToIndex(0),
		  base_text_vec()

{
	AbstractQuestionnaire::qnre_ptr = this;
}


void AbstractQuestionnaire::print_question_messages(AbstractRuntimeQuestion * q)
{
	stringstream question_name;
	question_name << q->questionName_;
	for (int i=0; i< q->loop_index_values.size(); ++i)
	{
		question_name << "_" << q->loop_index_values[i];
	}
	for (int i=0; i< q->textExprVec_.size(); ++i)
	{
		messages << "<message id=\"" << question_name.str()
			<< "_" << i << "\">"
			<< q->textExprVec_[i]->text_
			<< "</message>\n" << endl;
	}
}


#if 0
// Can this be moved into the qtm_data_file.cpp library
void AbstractQuestionnaire::print_summary_axis (vector<qtm_data_file_ns::QtmDataDiskMap*> & v, std::fstream & qtm_qax_file)
{
	AbstractRuntimeQuestion * q = v[0]->q;
	if (q->q_type == spn)
	{
		int n_digits = 0;
		int rat_scale = 0;
		if (NamedStubQuestion * n_q = dynamic_cast<NamedStubQuestion*>(q))
		{
			if (n_q->nr_ptr)
			{
				string & stub_name = n_q->nr_ptr->name;
				int multiplier = 1;
				for (int i=stub_name.length()-1; i>0; --i)
				{
					if ( isdigit(stub_name[i]) )
					{
						int c = stub_name[i] - '0';
						++n_digits;
						rat_scale = rat_scale + c * multiplier;
						multiplier *= 10;
					}
					else
					{
						break;
					}
				}
			}
		}
		if (n_digits > 0)
		{
			string include_file_name;
			string mean_score_include_file;
			if (v[0]->width_ == 1)
			{
				include_file_name = "rat1c.qin";
				mean_score_include_file = "mn1c.qin";
			}
			else if (v[0]->width_ == 2)
			{
				include_file_name = "rat2c.qin";
				mean_score_include_file = "mn2c.qin";
			}
			else if (v[0]->width_ == 3)
			{
				include_file_name = "rat3c.qin";
				mean_score_include_file = "mn3c.qin";
			}
			else
			{
				include_file_name = "unhandled width syntax error";
				mean_score_include_file = "unhandled width syntax error";
			}

			if (rat_scale == 5)
			{

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_top" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 5 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_top2" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 5 << ", " << 4 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_bot" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 1 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_bot2" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 1 << ", " << 2 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_mn" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << mean_score_include_file
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 1 << ":" << 5 << ")"
						<< endl;
				}

			}
			else if (rat_scale == 7)
			{

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_top" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 7 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_top2" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 7 << ", " << 6 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_top3" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 5 << ":" << 7 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_bot" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 1 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_bot2" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 1 << ", " << 2 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_mn" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << mean_score_include_file
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 1 << ":" << 7 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_bot3" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 1 << ":" << 3 << ")"
						<< endl;
				}

			}
			else if (rat_scale == 10)
			{

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_top" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 10 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_top2" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 10 << ", " << 9 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_top3" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 8 << ":" << 10 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_bot" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 1 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_bot2" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 1 << ", " << 2 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_mn" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << mean_score_include_file
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 1 << ":" << 10 << ")"
						<< endl;
				}

				qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
				qtm_qax_file << "l " << q->questionName_ << "_bot3" << endl;
				qtm_qax_file << "ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
				for (int i=0; i<v.size(); ++i)
				{
					qtm_qax_file << "*include " << include_file_name
						<< ";qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1
						<< ";myrange=(" << 1 << ":" << 3 << ")"
						<< endl;
				}

			}
		}
		else
		{
			qtm_qax_file << "/* summary table for: " << v[0]->q->questionName_ << endl;
			qtm_qax_file << "/*l " << q->questionName_ << "_sum" << endl;
			qtm_qax_file << "/*ttl" << q->questionName_ << "." << v[0]->q->textExprVec_[0]->text_ << endl;
			for (int i=0; i<v.size(); ++i)
			{
				qtm_qax_file << "/**include summ.qin;qatt=&at" << i << "t;" << "col(a)=" << v[i]->startPosition_+1 << endl;
			}
		}
	}
	cout << endl;
}
#endif /* 0 */

void AbstractQuestionnaire::write_data_to_disk (const vector<AbstractRuntimeQuestion*>& q_vec
		, string jno
		, int32_t ser_no)
{
	stringstream fname_str;
	fname_str << jno << "_" << ser_no << ".dat";
	//FILE * fptr = fopen(fname_str.str().c_str(), "w+b");

	std::ofstream data_file;
	data_file.exceptions(std::ios::failbit | std::ios::badbit);
	data_file.open(fname_str.str().c_str(), ios_base::ate);

	for(int32_t i = 0; i < question_list.size(); ++i)
	{
		question_list[i]->WriteDataToDisk(data_file);
		/*
		fprintf(fptr, "%s: ", question_list[i]->name.c_str());
		for( set<int32_t>::iterator iter = question_list[i]->input_data.begin();
				iter != question_list[i]->input_data.end(); ++iter){
			fprintf(fptr, "%d ", *iter);
		}
		fprintf(fptr, "
		");
		question_list[i]->input_data.clear();
		*/
	}
	data_file.flush();
	data_file.close();
	//fclose(fptr);
}

AbstractRuntimeQuestion * AbstractQuestionnaire::ComputePreviousQuestion(AbstractRuntimeQuestion * q)
{
	int32_t current_question_index = -1;
	if (q)
	{
		for (int32_t i = questions_start_from_here_index; i < question_list.size(); ++i)
		{
			if (question_list[i] == q)
			{
				current_question_index = i;
				break;
			}
		}
	}
	else
	{
		current_question_index = question_list.size();
	}
	if (current_question_index == -1)
	{
		cerr << "internal compiler error at runtime ... filename: "
			<< __FILE__
			<< "line no: " << __LINE__
			<< endl;
	}
	for (int32_t i = current_question_index-1; i >= 0; --i)
	{
		if (question_list[i]->isAnswered_)
		{
			return question_list[i];
		}
	}
	// If we reach here just return the 1st question and hope for the best
	// This will not work if there is a condition on the 1st question - because of which it should never have been taken
	return question_list[questions_start_from_here_index];
}

int32_t AbstractQuestionnaire::ComputeJumpToIndex(AbstractRuntimeQuestion * q)
{
	//cout << "ENTER ComputeJumpToIndex: index:  ";
	//for (int32_t i = 0; i < q->loop_index_values.size(); ++i) {
	//	cout << q->loop_index_values[i] << " ";
	//}
	//cout << endl;
	int32_t index = 0;
	for (int32_t i = 0; i < q->loop_index_values.size(); ++i)
	{
		int32_t tmp1=q->loop_index_values[i];
		for (int32_t j = i+1; j < q->dummyArrayQuestion_->array_bounds.size(); ++j)
		{
			tmp1 *=q->dummyArrayQuestion_->array_bounds[j];
		}
		index+=tmp1;
	}
	//cout << "EXIT ComputeJumpToIndex: returning : " << index << endl;
	return index;
}

void AbstractQuestionnaire::reset_questionnaire()
{
	for(int32_t i = 0; i< question_list.size(); ++i)
	{
		question_list[i]->isAnswered_ = false;
		question_list[i]->input_data.clear();
	}
}



int read_a_serial_no (DIR * directory_ptr, string jno, struct AbstractQuestionnaire * qnre)
{
	//cout << "ENTER: "  << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
	restart:
	struct dirent *directory_entry = readdir(directory_ptr);
	if (directory_entry == NULL)
	{
		// we have read upto the last record in the directory
		cout << "finished reading all data files ... exiting"
			<< endl;
		return 0;
	}
	string dir_entry_name(directory_entry->d_name);
	int len_entry = dir_entry_name.length();
	if (len_entry > 4 &&
		dir_entry_name[len_entry - 1] == 't' &&
		dir_entry_name[len_entry - 2] == 'a' &&
		dir_entry_name[len_entry - 3] == 'd' &&
		dir_entry_name[len_entry - 4] == '.')
	{
		if (dir_entry_name.length() < jno.length() + 6
			/* "_1.dat" is the shortest possible datafile name for our study */
			)
		{
			// cannot be our data file
			goto restart;
		}
		bool not_our_file = false;
		for (int i = 0; i < jno.length(); ++i)
		{
			if (!(jno[i] == dir_entry_name[i]))
			{
				// cannot be our data file
				not_our_file = true;
				break;
			}
		}
		if (not_our_file)
		{
			//continue;
			goto restart;
		}
		// all our data files are expected
		// to have a ".dat" ending and '_' after job number
		// find the "."
		cout << dir_entry_name << endl;
		if (dir_entry_name[jno.length()] != '_')
		{
			not_our_file = true;
			//continue;
			goto restart;
		}
		stringstream file_ser_no_str;
		for (int i = jno.length() + 1;
			i < dir_entry_name.length(); ++i)
		{
			if (isdigit(dir_entry_name[i]))
			{
				file_ser_no_str << dir_entry_name[i];
			}
			else
			{
				if ((i + 4 == dir_entry_name.length())
					&& dir_entry_name[i] == '.'
					&& dir_entry_name[i + 1] == 'd'
					&& dir_entry_name[i + 2] == 'a'
					&& dir_entry_name[i + 3] == 't')
				{
					//its most probably our file
					// need to check leading digit is not 0
					break;
				}
				else
				{
					// it's not our file
					not_our_file = true;
					goto restart;
				}
			}
		}
		if (not_our_file)
		{
			goto restart;
		}
		if ((file_ser_no_str.str())[0] == '0')
		{
			// the leading digit of our data file
			// can never be zero - so its not our file
			goto restart;
		}
		cout << "got a data file: " << dir_entry_name << endl;
		int file_ser_no = atoi(file_ser_no_str.str().c_str());
		map <string, question_disk_data*>  qdd_map;
		load_data(jno, file_ser_no, &qdd_map);
		merge_disk_data_into_questions2(qscript_stdout,
				qnre->last_question_answered,
				qnre->last_question_visited,
				qnre->question_list, &qdd_map);

		for (map<string, question_disk_data*>:: iterator it
			= qdd_map.begin();
			it != qdd_map.end();
			++it)
		{
			delete it->second;
		}
		return file_ser_no;
	}
	else
	{
		// not our data file
		goto restart;
	}
}

void AbstractQuestionnaire::DisplayActiveQuestions()
{
	for(int32_t i = 0; i<question_list.size(); ++i)
	{
		if (question_list[i]->isAnswered_) {
			cout << question_list[i]->questionName_ << " ";
		}
	}
	cout << endl;
}

#if 0
void AbstractQuestionnaire::write_qtm_data_to_disk()
{
	using qtm_data_file_ns::qtm_data_file_writer_log;
	qtm_data_file_writer_log << "writing serial no: " << ser_no << " to disk \n";
	for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i)
	{
		qtm_datafile_question_disk_map[i]->write_data ();
	}
	qtm_datafile_question_disk_map[0]->qtmDataFile_.write_record_to_disk(qtm_disk_file, ser_no);
	qtm_datafile_question_disk_map[0]->qtmDataFile_.Reset();
	//qtm_datafile_question_disk_map[0]->Reset();
	for (int32_t i = 0; i < qtm_datafile_question_disk_map.size(); ++i)
	{
		qtm_datafile_question_disk_map[i]->Reset();
	}
	do_freq_counts();
}

void AbstractQuestionnaire::write_ascii_data_to_disk()
{
	stringstream temp_ser_no_str;
	temp_ser_no_str << ser_no;
	if (temp_ser_no_str.str().length() > ser_no_pos)
	{
		cerr << "space reserved to hold serial no: "
			<< ser_no_pos << " is not enough"
			<< " to hold this serial no: "
			<< ser_no << endl;
		exit(1);
	}
	else
	{
		//char * ptr = flat_file_output_buffer;
		for (int i=0; i<temp_ser_no_str.str().length(); ++i)
		{
			flat_file_output_buffer[i] = temp_ser_no_str.str()[i];
			//cout << "writing digit " << temp_ser_no_str[i] << " to flat_file_output_buffer" << endl;
		}
	}

	for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i)
	{
		ascii_flatfile_question_disk_map[i]->write_data (flat_file_output_buffer);
	}
	// cout << "output_buffer: " << flat_file_output_buffer;
	flat_file << flat_file_output_buffer << endl;
	memset(flat_file_output_buffer, ' ', len_flat_file_output_buffer-1);
	do_freq_counts();
}

void AbstractQuestionnaire::write_xtcc_data_to_disk()
{
	void * void_ptr = &ser_no;
	char * char_ptr = static_cast<char*>(void_ptr);
	char * my_data_ptr = xtcc_datafile_output_buffer;
	for (int i=0; i<sizeof(int); ++i)
	{
		*my_data_ptr++ = *char_ptr++;
	}

	for (int i=0; i<xtcc_question_disk_map.size(); ++i)
	{
		xtcc_question_disk_map[i]->write_data (xtcc_datafile_output_buffer);
	}
	//cout << "output_buffer: " << xtcc_datafile_output_buffer;
	xtcc_datafile . write(xtcc_datafile_output_buffer, len_xtcc_datafile_output_buffer);
	memset(xtcc_datafile_output_buffer, 0, len_xtcc_datafile_output_buffer-1);
	do_freq_counts();
	cout << "len_xtcc_datafile_output_buffer: " << len_xtcc_datafile_output_buffer << endl;
}
#endif /* 0 */

void AbstractQuestionnaire::do_freq_counts()
{
	for (int32_t i = 0; i < question_list.size(); ++i)
	{
		AbstractRuntimeQuestion * q = question_list[i];
		stringstream question_name_str;
		question_name_str << q->questionName_;
		if (q->loop_index_values.size())
		{
			for (int j=0; j<q->loop_index_values.size(); ++j)
			{
				question_name_str << "." << q->loop_index_values[j];
			}
		}
		map<int , int> q_freq_map = freq_count[question_name_str.str()];
		for (set<int32_t>::iterator it = q->input_data.begin();
			it != q->input_data.end(); ++it)
		{
			q_freq_map[*it] ++;
		}
		freq_count[question_name_str.str()] = q_freq_map;
	}
}

void GetUserResponse(string & qno, int32_t & qindex)
{
	char newl;
	cin >> qno;cin.get(newl);
	qindex = 0;
	cout << "User input qno:" << qno
		<< ", newl: " << newl << endl;
}

AbstractQuestionnaire * AbstractQuestionnaire::getBaseClassPtr()
{
	return this;
}
