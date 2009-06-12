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
#include <iosfwd>
//#include <fstream>
#include "stmt.h"

using std::ostringstream;
using std::ofstream;
struct named_range;
//! The question pure virtual base class - inherits from AbstractStatement
struct question: public AbstractStatement {
	string name_;
	string text;
	QuestionType q_type;
	int no_mpn;
	DataType dt;
	set<int> input_data;
	//AbstractExpression * arr_sz;
	vector<AbstractExpression*> for_bounds_stack;
	vector<int> loop_index_values;
	question(DataType l_type,int l_no, string l_name, string l_text
		, QuestionType l_q_type, int l_no_mpn, DataType l_dt
		, vector<AbstractExpression*>& l_for_bounds_stack
		);

	question(DataType l_type,int l_no, string l_name, string l_text
		, QuestionType l_q_type, int l_no_mpn, DataType l_dt 
		);

	question(DataType l_type,int l_no, string l_name, string l_text
		, QuestionType l_q_type, int l_no_mpn , DataType l_dt
		, const vector<int>& l_loop_index_values
		);
	virtual void GenerateCode(ostringstream & quest_defns, ostringstream& program_code)=0;
	virtual void generate_code_single_question(ostringstream & quest_defns, ostringstream& program_code)=0;
	virtual void eval()=0;
	virtual bool is_valid(int value)=0;
	void print_q_type(string &s);
	void print_data_type(string &s);
	void init_arr(int n, question* q);
	virtual void write_data_to_disk(ofstream & data_file)=0;
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
	XtccSet * r_data;
	vector <int> stack_loop_index_values;
	range_question(DataType this_stmt_type, int line_number,
		string l_name, string l_q_text,
		QuestionType l_q_type, int l_no_mpn, DataType l_dt,
		XtccSet& l_r_data
		, vector<AbstractExpression*>& l_for_bounds_stack
		);
	range_question(DataType this_stmt_type, int line_number,
		string l_name, string l_q_text,
		QuestionType l_q_type, int l_no_mpn, DataType l_dt,
		XtccSet& l_r_data
		);
	range_question(DataType this_stmt_type, int line_number,
		string l_name, string l_q_text,
		QuestionType l_q_type, int l_no_mpn, DataType l_dt,
		XtccSet& l_r_data, const vector<int> & l_loop_index_values
		);

	void GenerateCode(ostringstream & quest_defns, ostringstream& program_code);
	void generate_code_single_question(ostringstream & quest_defns, ostringstream& program_code);
	virtual bool is_valid(int value);
	void eval();
	void write_data_to_disk(ofstream& data_file);
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
	public:
	string named_list;
	named_range * nr_ptr;
	vector<stub_pair> * stub_ptr;
	named_stub_question(DataType this_stmt_type, int line_number, 
		string l_name, string l_q_text,
		QuestionType l_q_type, int l_no_mpn, DataType l_dt,
		named_range * l_nr_ptr 
		, vector<AbstractExpression*>& l_for_bounds_stack
		);
	named_stub_question(DataType this_stmt_type, int line_number, 
		string l_name, string l_q_text,
		QuestionType l_q_type, int l_no_mpn, DataType l_dt,
		named_range * l_nr_ptr 
		);

	named_stub_question(DataType this_stmt_type, int line_number, 
		string l_name, string l_q_text,
		QuestionType l_q_type, int l_no_mpn, DataType l_dt,
		vector<stub_pair> * l_stub_ptr
		, vector<AbstractExpression*>& l_for_bounds_stack
		);
	named_stub_question(DataType this_stmt_type, int line_number, 
		string l_name, string l_q_text,
		QuestionType l_q_type, int l_no_mpn, DataType l_dt,
		vector<stub_pair> * l_stub_ptr
		);
	named_stub_question(DataType this_stmt_type, int line_number
		, string l_name, string l_q_text
		, QuestionType l_q_type, int l_no_mpn, DataType l_dt
		, vector<stub_pair> * l_stub_ptr 
		, const vector<int> & l_loop_index_values
		);

	void GenerateCode(ostringstream & quest_defns, ostringstream& program_code);
	void generate_code_single_question(ostringstream & quest_defns, ostringstream& program_code);
	virtual bool is_valid(int value);
	void eval();
	void write_data_to_disk(ofstream& data_file);
	private:
		named_stub_question& operator=(const named_stub_question&);
		named_stub_question (const named_stub_question&);
};


#endif /* qscript_question_h */
