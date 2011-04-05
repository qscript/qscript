#ifndef QSCRIPT_ASCIIFLATFILEQUESTIONDISKMAP
#define QSCRIPT_ASCIIFLATFILEQUESTIONDISKMAP

#include <set>
#include <sstream>
#include <string>
#include "question.h"

class AsciiFlatFileQuestionDiskMap
{
	public:
		AbstractQuestion *q;
		int32_t start_pos;
		int32_t width;
		int32_t total_length;
		AsciiFlatFileQuestionDiskMap(AbstractQuestion * p_q, int32_t p_start_pos
		/*,
								int32_t p_width, int32_t p_total_length*/
								)						 
			:
		q(p_q), start_pos(p_start_pos)
		/*, width(p_width),
				total_length(p_total_length)*/
		{
			int max_code = q->GetMaxCode();
			if (max_code < 10)
			{
				width = 1;
			}
			else if (max_code < 100)
			{
				width = 2;
			}
			else if (max_code < 1000)
			{
				width = 3;
			}
			else if (max_code < 10000)
			{
				width = 4;
			}
			else if (max_code < 100000)
			{
				width = 5;
			}
			else if (max_code < 1000000)
			{
				width = 6;
			}
			else if (max_code < 10000000)
			{
				width = 7;
			}
			else if (max_code < 100000000)
			{
				width = 8;
			}
			else
			{
				cout << " max_code " << max_code << " for question: " << q->questionName_ << " exceeds max length = 8 we are programmed to handled ... exiting " << __FILE__ << ","  << __LINE__ << ","  << __PRETTY_FUNCTION__ << endl;
				exit(1);
			}
			total_length = width * q->no_mpn;
		}

		int GetTotalLength() { return total_length; }
		void write_data (char * output_buffer)
		{
			char * ptr = output_buffer + start_pos;
			int no_responses_written = 0;
			for (std::set<int>::iterator it = q->input_data.begin();
				it != q->input_data.end(); ++it)
			{
				int code = *it;
				std::stringstream code_str;
				code_str << code;
				cout << "writing code: " << code << " to output_buffer: length: " << code_str.str().length() << "\n";
				if (code_str.str().length() > width)
				{
					cerr << " internal programming error - width of code exceeds width allocated ... exiting\n";
					exit(1);
				}
				// int bytes_written = snprintf(ptr, code_str.str().length(), "%s", code_str.str().c_str());
				// int bytes_written = snprintf(ptr, code_str.str().length(), "%d", code);
				for (int i=0; i<code_str.str().length(); ++i)
				{
					ptr[i] = (code_str.str())[i];
				}
				// ptr[bytes_written] = ' ';
				//if (bytes_written > width) {
				//	cerr << "impossible internal programming error - width of code exceeds width allocated ... exiting\n";
				//	exit(1);
				//}
				ptr += width;
				++no_responses_written;
				if (no_responses_written > q->no_mpn)
				{
					cerr << " no of responses in question : " << q->questionName_ << " exceeds no allocated ... exiting\n";
					exit(1);
				}
			}
		}
		void print_map(fstream & map_file)
		{
			map_file << q->questionName_;
			if (q->loop_index_values.size())
			{
				for (int i=0; i< q->loop_index_values.size(); ++i)
				{
					map_file << "." << q->loop_index_values[i];
				}
			}
			map_file << ",			";
			map_file << width << ",	";
			map_file << q->no_mpn << ",	";
			map_file << start_pos+1 << ",	";
			map_file << start_pos + total_length  << "\n";
		}
};

#endif  /* */
