#ifndef stmt_h
#define stmt_h
#include "xtcc_set.h"
#include "common.h"
#include <string>
using std::string;
struct stmt {
	struct stmt * prev, *next;
	int line_no;
	stmt(int l_no): prev(0), next(0), line_no(l_no)
	{}
	virtual void eval()=0;
	virtual void generate_code(FILE * script)=0;
};


struct q_stmt: public stmt {
	string name;
	string text;
	question_type q_type;
	int no_mpn;
	datatype dt;
	xtcc_set * r_data;
	set<int> input_data;
	q_stmt(int l_no, string l_name, string l_text, question_type l_q_type, int l_no_mpn, 
		datatype l_dt, xtcc_set& l_r_data);
	void eval();
	void generate_code(FILE* script);
	void print_q_type(string &s);
	void print_data_type(string &s);
};

#endif /* stmt_h */
