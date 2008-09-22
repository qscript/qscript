#ifndef xtcc_question_h
#define xtcc_question_h

#include "../xtcc/trunk/stmt.h"
#include "range_set.h"
#include <cstdlib>

enum question_type { spn, mpn };

class question: public stmt {
	string name;
	string q_text;
	question_type q_type;
	int no_mpn;
	datatype dt;
	public:
	virtual void print_stmt_lst(FILE * & fptr);
	question(int line_number, datatype this_stmt_type, 
		string l_name, string l_q_text, 
		question_type l_q_type, int l_no_mpn, datatype l_dt):
		stmt(this_stmt_type, line_number), name(l_name), q_text(l_q_text),
		q_type(l_q_type), no_mpn(l_no_mpn), dt(l_dt)
	{}
};


class range_question: public question {
	range_data r_data;
	public:
	range_question(int line_number, datatype this_stmt_type, 
		string l_name, string l_q_text,
		question_type l_q_type, int l_no_mpn, datatype l_dt,
		range_data& l_r_data): question(line_number, this_stmt_type, l_name, l_q_text,
					l_q_type, l_no_mpn, l_dt)
	{
		r_data = l_r_data;
	}
	void print_stmt_lst(FILE * & fptr);

};


class named_stub_question: public question {
	string named_list;
	public:
	named_stub_question(int line_number, datatype this_stmt_type, 
		string l_name, string l_q_text,
		question_type l_q_type, int l_no_mpn, datatype l_dt,
		string & list_name);
	void print_stmt_lst(FILE * & fptr);
};


#endif /* 0 */
