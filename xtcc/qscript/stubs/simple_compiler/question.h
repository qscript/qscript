/*! \file
    \brief The "question" statement classes of the qscript language
           are contained in this file. The question classes are 
	   required in the runtime as well as compile environment.
	   Hence they have been factored out to speed up compilation
	   and prevent unnecessary code from entering the runtime binary

 *  xtcc/xtcc/qscript/stubs/simple_compiler/question.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#ifndef qscript_question_h
#define qscript_question_h
#include "stmt.h"

struct named_range;
//! The question pure virtual base class - inherits from stmt
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



//! range_question range questions in the qscript language become object instantiations of this class.
/*!
  	Below is an example of a range question - the allowed codes are hard coded
	numbers -> (1,2,5-8)
		q2 "Q2. This is question 2" mp (5) int32_t (1,2,5-8);
*/
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


//! named_stub_question named  questions in the qscript language become object instantiations of this class.
/*!
  	Below is an example of a named_stub_question - the allowed codes are a
	predefined name like "age" below

		q3 "Q3. Respondents age" sp int32_t age; 
*/
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
