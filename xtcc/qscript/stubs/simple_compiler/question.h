/*! \file
    \brief The "AbstractQuestion" statement classes of the qscript language
           are contained in this file. The AbstractQuestion classes are 
	   required in the runtime as well as compile environment.
	   Hence they have been factored out to speed up compilation
	   and prevent unnecessary code from entering the runtime binary

 *  xtcc/xtcc/qscript/stubs/simple_compiler/AbstractQuestion.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 
 *	Neil Xavier D'Souza
 */
#ifndef qscript_question_h
#define qscript_question_h
#include <iosfwd>
//#include <fstream>
#include "stmt.h"

using std::ostringstream;
using std::ofstream;
struct named_range;
//! The AbstractQuestion pure virtual base class - inherits from AbstractStatement
struct AbstractQuestion: public AbstractStatement 
{
	string questionName_;
	string questionText_;
	QuestionType q_type;
	int no_mpn;
	DataType dt;
	set<int> input_data;
	//AbstractExpression * arr_sz;
	vector<AbstractExpression*> for_bounds_stack;
	vector<int> loop_index_values;
	AbstractQuestion(DataType l_type,int l_no, string l_name, string l_text
		, QuestionType l_q_type, int l_no_mpn, DataType l_dt
		, vector<AbstractExpression*>& l_for_bounds_stack
		);

	AbstractQuestion(DataType l_type,int l_no, string l_name, string l_text
		, QuestionType l_q_type, int l_no_mpn, DataType l_dt 
		);

	AbstractQuestion(DataType l_type,int l_no, string l_name, string l_text
		, QuestionType l_q_type, int l_no_mpn , DataType l_dt
		, const vector<int>& l_loop_index_values
		);
	virtual void GenerateCode(ostringstream & quest_defns
			, ostringstream& program_code)=0;
	virtual void GenerateCodeSingleQuestion(ostringstream & quest_defns
			, ostringstream& program_code)=0;
	virtual void eval()=0;
	virtual bool IsValid(int value)=0;
	void print_q_type(string &s);
	void print_data_type(string &s);
	void init_arr(int n, AbstractQuestion* q);
	virtual void WriteDataToDisk(ofstream & data_file)=0;
	void PrintSetupBackJump(ostringstream & quest_defns
			, ostringstream& program_code);
	void PrintEvalArrayQuestion(ostringstream & quest_defns
			, ostringstream& program_code);
	private:
		AbstractQuestion& operator=(const AbstractQuestion&);
		AbstractQuestion (const AbstractQuestion&);
};



//! RangeQuestion range questions in the qscript language become object instantiations of this class.
/*!
  	Below is an example of a RangeQuestion  - the allowed codes are hard coded
	numbers -> (1,2,5-8)
		q2 "Q2. This is AbstractQuestion 2" mp (5) int32_t (1,2,5-8);
*/
struct RangeQuestion: public AbstractQuestion 
{
	XtccSet * r_data;
	vector <int> stack_loop_index_values;
	RangeQuestion(DataType this_stmt_type, int line_number,
		string l_name, string l_q_text,
		QuestionType l_q_type, int l_no_mpn, DataType l_dt,
		XtccSet& l_r_data
		, vector<AbstractExpression*>& l_for_bounds_stack
		);
	RangeQuestion(DataType this_stmt_type, int line_number,
		string l_name, string l_q_text,
		QuestionType l_q_type, int l_no_mpn, DataType l_dt,
		XtccSet& l_r_data
		);
	RangeQuestion(DataType this_stmt_type, int line_number,
		string l_name, string l_q_text,
		QuestionType l_q_type, int l_no_mpn, DataType l_dt,
		XtccSet& l_r_data, const vector<int> & l_loop_index_values
		);

	void GenerateCode(ostringstream & quest_defns
			, ostringstream& program_code);
	void GenerateCodeSingleQuestion(ostringstream & quest_defns
			, ostringstream& program_code);
	virtual bool IsValid(int value);
	void eval();
	void WriteDataToDisk(ofstream& data_file);
	~RangeQuestion();
	private:
		RangeQuestion& operator=(const RangeQuestion&);
		RangeQuestion (const RangeQuestion&);
};


//! NamedStubQuestion named  questions in the qscript language become object instantiations of this class.
/*!
  	Below is an example of a NamedStubQuestion - the allowed codes are a
	predefined name like "age" below

		q3 "Q3. Respondents age" sp int32_t age; 
*/
class NamedStubQuestion: public AbstractQuestion 
{
	public:
	string named_list;
	named_range * nr_ptr;
	vector<stub_pair> * stub_ptr;
	NamedStubQuestion(DataType this_stmt_type, int line_number, 
		string l_name, string l_q_text,
		QuestionType l_q_type, int l_no_mpn, DataType l_dt,
		named_range * l_nr_ptr 
		, vector<AbstractExpression*>& l_for_bounds_stack
		);
	NamedStubQuestion(DataType this_stmt_type, int line_number, 
		string l_name, string l_q_text,
		QuestionType l_q_type, int l_no_mpn, DataType l_dt,
		named_range * l_nr_ptr 
		);

	NamedStubQuestion(DataType this_stmt_type, int line_number, 
		string l_name, string l_q_text,
		QuestionType l_q_type, int l_no_mpn, DataType l_dt,
		vector<stub_pair> * l_stub_ptr
		, vector<AbstractExpression*>& l_for_bounds_stack
		);
	NamedStubQuestion(DataType this_stmt_type, int line_number, 
		string l_name, string l_q_text,
		QuestionType l_q_type, int l_no_mpn, DataType l_dt,
		vector<stub_pair> * l_stub_ptr
		);
	NamedStubQuestion(DataType this_stmt_type, int line_number
		, string l_name, string l_q_text
		, QuestionType l_q_type, int l_no_mpn, DataType l_dt
		, vector<stub_pair> * l_stub_ptr 
		, const vector<int> & l_loop_index_values
		);

	void GenerateCode(ostringstream & quest_defns
			, ostringstream& program_code);
	void GenerateCodeSingleQuestion(ostringstream & quest_defns
			, ostringstream& program_code);
	virtual bool IsValid(int value);
	void eval();
	void WriteDataToDisk(ofstream& data_file);
	private:
		NamedStubQuestion& operator=(const NamedStubQuestion&);
		NamedStubQuestion (const NamedStubQuestion&);
};

class DummyArrayQuestion: public AbstractQuestion{
	vector<int> array_bounds;
	public:

	DummyArrayQuestion(string l_qno, vector<int> l_array_bounds)
		: AbstractQuestion(QUESTION_TYPE, 0, l_qno, "", spn 
		, 0, INT32_TYPE ),
		  array_bounds(l_array_bounds)
	{ }
	void WriteDataToDisk(ofstream& data_file);
	void eval(){}
	bool IsValid(int value){ return false;}
	void GenerateCode(ostringstream & quest_defns
			, ostringstream& program_code){}
	void GenerateCodeSingleQuestion(ostringstream & quest_defns
			, ostringstream& program_code){}
	private:
		DummyArrayQuestion& operator=(const DummyArrayQuestion&);
		DummyArrayQuestion (const DummyArrayQuestion&);
};


#endif /* qscript_question_h */
