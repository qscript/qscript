/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/question.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#ifndef qscript_question_h
#define qscript_question_h
#include "stmt.h"

struct named_range;
struct question: public stmt {
	string name;
	string text;
	question_type q_type;
	int no_mpn;
	datatype dt;
	set<int> input_data;
	question(datatype l_type,int l_no, string l_name, string l_text,
		question_type l_q_type, int l_no_mpn, 
		datatype l_dt /*, xtcc_set& l_r_data*/);
	virtual void generate_code(ostringstream & quest_defns, ostringstream& program_code)=0;
	virtual void eval()=0;
	virtual bool is_valid(int value)=0;
	void print_q_type(string &s);
	void print_data_type(string &s);
	private:
		question& operator=(const question&);
		question (const question&);
};



struct range_question: public question {
	xtcc_set * r_data;
	range_question(datatype this_stmt_type, int line_number,
		string l_name, string l_q_text,
		question_type l_q_type, int l_no_mpn, datatype l_dt,
		xtcc_set& l_r_data);

	void generate_code(ostringstream & quest_defns, ostringstream& program_code);
	virtual bool is_valid(int value);
	void eval();
	private:
		range_question& operator=(const range_question&);
		range_question (const range_question&);
};


class named_stub_question: public question {
	string named_list;
	named_range * nr_ptr;
	vector<stub_pair> * stub_ptr;
	public:
	named_stub_question(datatype this_stmt_type, int line_number, 
		string l_name, string l_q_text,
		question_type l_q_type, int l_no_mpn, datatype l_dt,
		named_range * l_nr_ptr);
	named_stub_question(datatype this_stmt_type, int line_number, 
		string l_name, string l_q_text,
		question_type l_q_type, int l_no_mpn, datatype l_dt,
		vector<stub_pair> * l_stub_ptr);
	//void print_stmt_lst(FILE * & fptr);
	void generate_code(ostringstream & quest_defns, ostringstream& program_code);
	virtual bool is_valid(int value);
	void eval();
	private:
		named_stub_question& operator=(const named_stub_question&);
		named_stub_question (const named_stub_question&);
};


#endif /* qscript_question_h */
