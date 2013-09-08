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
#include <sys/types.h>
#include <iosfwd>
//#include <fstream>
#include <iostream>
#include <string>
#include <set>
//#include <Wt/WString>

//#include "stmt.h"
//#include "expr.h"
//#include "compiled_code.h"
//#include "curses_namespace.h"
#include "qscript_debug.h"
#include "display_data.h"
#include "QuestionAttributes.h"
#include "UserResponse.h"
#include "user_navigation.h"
#include "named_attributes.h"
#include "stub_pair.h"
#include "xtcc_set.h"
//#include "active_var_info.h"
#include "question_type.h"

using std::ostringstream;
using std::ofstream;
using std::set;
struct named_range;
struct DummyArrayQuestion;

struct CompoundStatement;

struct Unary2Expression;
struct AbstractExpression;
struct AbstractRuntimeQuestion ;
	struct TextExpression
	{
		enum TextExpressionType {
			simple_text_type, named_attribute_type, question_type
		};
		TextExpressionType teType_;

		string text_;
		Unary2Expression * nameExpr_;
		named_attribute_list* naPtr_;
		int32_t naIndex_;

		AbstractRuntimeQuestion * pipedQuestion_;
		AbstractExpression * questionIndexExpr_;
		int32_t codeIndex_;
		TextExpression(string text);
		TextExpression(Unary2Expression * expr );
		TextExpression(named_attribute_list * na_ptr, int na_index);
		TextExpression(AbstractRuntimeQuestion * q, AbstractExpression * expr);
		TextExpression(AbstractRuntimeQuestion * q, int code_index);
		TextExpression (AbstractRuntimeQuestion * q);
		TextExpression(); // for DummyArrayQuestion
	private:
		TextExpression& operator=(const TextExpression&);
		TextExpression (const TextExpression&);
	};


#if 0
//! The AbstractQuestion pure virtual base class - inherits from AbstractStatement
struct AbstractQuestion: public AbstractStatement
{
	string questionName_;
	//string questionText_;
	vector <TextExpression*> textExprVec_;
	string questionDiskName_;
	QuestionType q_type;
	int32_t no_mpn;
	DataType dt;
	set<int32_t> input_data;
	//AbstractExpression * arr_sz;
	vector<AbstractExpression*> for_bounds_stack;
	vector<int32_t> loop_index_values;
	bool isAnswered_;
	bool isModified_;
	CompoundStatement * enclosingCompoundStatement_;
	vector <ActiveVariableInfo*> activeVarInfo_;
	DummyArrayQuestion * dummyArrayQuestion_;
	//! this variable should never be used in the compile time environment
	string currentResponse_;
	QuestionAttributes question_attributes;
	XtccSet mutexCodeList_;
	int maxCode_;
	bool isStartOfBlock_;
	int questionNoIndex_;
	static int32_t nQuestions_;
	//! this is only called in the compile time environment
	AbstractQuestion(
		DataType l_type,int32_t l_no, string l_name, vector<TextExpression*> text_expr_vec
		, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
		, vector<AbstractExpression*>& l_for_bounds_stack
		, CompoundStatement * l_enclosing_scope
		, vector<ActiveVariableInfo* > l_av_info
		, QuestionAttributes  l_question_attributes
		, const XtccSet & p_mutexCodeList=XtccSet()
		);

	AbstractQuestion(
		DataType l_type,int32_t l_no, string l_name, vector<TextExpression*> text_expr_vec
		, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		);
	//! this is only called in the compile time environment
	AbstractQuestion(
		DataType l_type,int32_t l_no, string l_name, vector<TextExpression*> text_expr_vec
		, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
		, CompoundStatement * l_enclosing_scope
		, vector<ActiveVariableInfo* > l_av_info
		, QuestionAttributes  l_question_attributes
		, const XtccSet & p_mutexCodeList=XtccSet()
		);

	//! this is only called in the runtime environment
	AbstractQuestion(
		DataType l_type,int32_t l_no, string l_name, vector<TextExpression*> text_expr_vec
		, QuestionType l_q_type, int32_t l_no_mpn , DataType l_dt
		, const vector<int32_t>& l_loop_index_values
		, DummyArrayQuestion * l_dummy_array
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		);
	virtual ~AbstractQuestion();
//	virtual void GenerateCode(ostringstream & quest_defns
//			, ostringstream& program_code)=0;
	virtual void GenerateCode(StatementCompiledCode &code)=0;
	virtual void GenerateCodeSingleQuestion(StatementCompiledCode &code, bool array_mode)=0;
	//virtual void Generate_ComputeFlatFileMap(StatementCompiledCode & code);
	//virtual void eval(/*qs_ncurses::*/WINDOW * question_window
	//		  , /*qs_ncurses::*/WINDOW* stub_list_window
	//		  , /*qs_ncurses::*/WINDOW* data_entry_window)=0;
	//virtual bool IsValid(int32_t value)=0;
	void print_q_type(string &s);
	void print_data_type(string &s);
	void init_arr(int32_t n, AbstractQuestion* q);
	virtual void WriteDataToDisk(ofstream & data_file)=0;
	void PrintSetupBackJump(StatementCompiledCode &code);
	void SetupSimpleQuestionSave(StatementCompiledCode &code);
	void SetupSimpleQuestionRestore(StatementCompiledCode &code);
	void SetupArrayQuestionSave(StatementCompiledCode &code);
	void SetupArrayQuestionRestore(StatementCompiledCode &code);
	void PrintEvalArrayQuestion(StatementCompiledCode &code);
	const char * CurrentResponseToCharString();
	//virtual AbstractQuestion * IsAQuestionStatement()=0;
	virtual void GetQuestionNames(vector<string> & question_list
				      , AbstractStatement * endStatement)=0;
	virtual void GetQuestionsInBlock(
		vector<AbstractQuestion*> & question_list
		, AbstractStatement * stop_at);
	void PrintEvalAndNavigateCode(ostringstream & program_code);
	user_response::UserResponseType GetDataFromUser(WINDOW * question_window, WINDOW * stub_list_window, WINDOW * data_entry_window);

	bool VerifyData(string & err_mesg, string & re_arranged_buffer
				, int32_t &pos_1st_invalid_data, vector<int32_t> * data_ptr);
	bool VerifyResponse(user_response::UserResponseType user_resp, UserNavigation user_navigation, string & err_mesg);
	// void PrintArrayDeclarations(ostringstream & quest_defns);
	void PrintArrayDeclarations(StatementCompiledCode & code);
	void PrintQuestionArrayInitialisation(
		StatementCompiledCode & code);
	std::string PrintCodeSaveArrayQuestionNotInTheSameBlock(AbstractQuestion * save_array_quest);
	std::string PrintCodeRestoreArrayQuestionNotInTheSameBlock(AbstractQuestion * restore_array_quest);
	string PrintSaveArrayQuestion(ActiveVariableInfo * av_info);
	string PrintRestoreArrayQuestion(ActiveVariableInfo * av_info);
	void PrintSaveMyPreviousIterationsData(StatementCompiledCode &code);
	void PrintRestoreMyPreviousIterationsData(StatementCompiledCode &code);
	friend bool IsInTheSameScopeAndLevel(AbstractQuestion *q1
					     , AbstractQuestion * q2);
	friend bool NotInTheSameBlock(AbstractQuestion *q1, AbstractQuestion * q2);
	friend bool IsAtAHigherNestLevelInTheSameBlock(AbstractQuestion *q1
						       , AbstractQuestion * q2);
	friend bool IsAtADeeperNestLevelInTheSameBlock(AbstractQuestion *q1
						       , AbstractQuestion * q2);
	bool QuestionIsInMyBlock(AbstractQuestion *q);
	void SaveQuestionsInMyBlockThatAreAfterMe(StatementCompiledCode & code);
	void RestoreQuestionsInMyBlockThatAreAfterMe(StatementCompiledCode & code);
	void PrintUserNavigation(ostringstream & program_code);
	void PrintUserNavigationArrayQuestion(ostringstream & program_code);
	int32_t GetMaxCode();
	bool VerifyQuestionIntegrity();
	//virtual Wt::WString PrintSelectedAnswers()=0;
	//virtual Wt::WString PrintSelectedAnswers(int code_index)=0;
	virtual string PrintSelectedAnswers()=0;
	virtual string PrintSelectedAnswers(int code_index)=0;

	bool check_and_store_input_data_single_question
		(string & err_mesg, string & re_arranged_buffer, int & pos_1st_invalid_data,
		 vector <int> & data);
	private:
		AbstractQuestion& operator=(const AbstractQuestion&);
		AbstractQuestion (const AbstractQuestion&);
};
#endif /* 0 */

struct AbstractRuntimeQuestion
{
	string questionName_;
	//string questionText_;
	vector <TextExpression*> textExprVec_;
	string questionDiskName_;
	QuestionType q_type;
	int32_t no_mpn;
	DataType dt;
	set<int32_t> input_data;
	//AbstractExpression * arr_sz;
	vector<AbstractExpression*> for_bounds_stack;
	vector<int32_t> loop_index_values;
	bool isAnswered_;
	bool isModified_;
	//CompoundStatement * enclosingCompoundStatement_;
	//vector <ActiveVariableInfo*> activeVarInfo_;
	DummyArrayQuestion * dummyArrayQuestion_;
	//! this variable should never be used in the compile time environment
	string currentResponse_;
	QuestionAttributes question_attributes;
	XtccSet mutexCodeList_;
	int maxCode_;
	bool isStartOfBlock_;
	int questionNoIndex_;
	//int baseQuestionNoIndexForArray_;
	static int32_t nQuestions_;
	//! this is only called in the compile time environment
#if 0
	AbstractRuntimeQuestion(
		DataType l_type,int32_t l_no, string l_name, vector<TextExpression*> text_expr_vec
		, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
		, vector<AbstractExpression*>& l_for_bounds_stack
		, CompoundStatement * l_enclosing_scope
		, vector<ActiveVariableInfo* > l_av_info
		, QuestionAttributes  l_question_attributes
		, const XtccSet & p_mutexCodeList=XtccSet()
		);
#endif /* 0 */

	AbstractRuntimeQuestion(
		DataType l_type,int32_t l_no, string l_name, vector<TextExpression*> text_expr_vec
		, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		);

#if 0
	//! this is only called in the compile time environment
	AbstractRuntimeQuestion(
		DataType l_type,int32_t l_no, string l_name, vector<TextExpression*> text_expr_vec
		, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
		, CompoundStatement * l_enclosing_scope
		, vector<ActiveVariableInfo* > l_av_info
		, QuestionAttributes  l_question_attributes
		, const XtccSet & p_mutexCodeList=XtccSet()
		);
#endif /* 0 */

	//! this is only called in the runtime environment
	AbstractRuntimeQuestion(
		DataType l_type,int32_t l_no, string l_name, vector<TextExpression*> text_expr_vec
		, QuestionType l_q_type, int32_t l_no_mpn , DataType l_dt
		, const vector<int32_t>& l_loop_index_values
		, DummyArrayQuestion * l_dummy_array
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		);
	virtual ~AbstractRuntimeQuestion();
//	virtual void GenerateCode(ostringstream & quest_defns
//			, ostringstream& program_code)=0;
	//virtual void GenerateCode(StatementCompiledCode &code)=0;
	//virtual void GenerateCodeSingleQuestion(StatementCompiledCode &code, bool array_mode)=0;
	//virtual void Generate_ComputeFlatFileMap(StatementCompiledCode & code);
	//virtual void eval(/*qs_ncurses::*/WINDOW * question_window
	//		  , /*qs_ncurses::*/WINDOW* stub_list_window
	//		  , /*qs_ncurses::*/WINDOW* data_entry_window)=0;
	virtual bool IsValid(int32_t value)=0;
	void print_q_type(string &s);
	void print_data_type(string &s);
	void init_arr(int32_t n, AbstractRuntimeQuestion* q);
	virtual void WriteDataToDisk(ofstream & data_file)=0;
	//void PrintSetupBackJump(StatementCompiledCode &code);
	//void SetupSimpleQuestionSave(StatementCompiledCode &code);
	//void SetupSimpleQuestionRestore(StatementCompiledCode &code);
	//void SetupArrayQuestionSave(StatementCompiledCode &code);
	//void SetupArrayQuestionRestore(StatementCompiledCode &code);
	//void PrintEvalArrayQuestion(StatementCompiledCode &code);
	const char * CurrentResponseToCharString();
	//virtual AbstractQuestion * IsAQuestionStatement()=0;
	//virtual void GetQuestionNames(vector<string> & question_list
	//			      , AbstractStatement * endStatement)=0;
	//virtual void GetQuestionsInBlock(
	//	vector<AbstractQuestion*> & question_list
	//	, AbstractStatement * stop_at);
	//void PrintEvalAndNavigateCode(ostringstream & program_code);
	//user_response::UserResponseType GetDataFromUser(WINDOW * question_window, WINDOW * stub_list_window, WINDOW * data_entry_window);

	bool VerifyData(string & err_mesg, string & re_arranged_buffer
				, int32_t &pos_1st_invalid_data, vector<int32_t> * data_ptr);
	bool VerifyResponse(user_response::UserResponseType user_resp, UserNavigation user_navigation, string & err_mesg);
	// void PrintArrayDeclarations(ostringstream & quest_defns);
	//void PrintArrayDeclarations(StatementCompiledCode & code);
	//void PrintQuestionArrayInitialisation( StatementCompiledCode & code);
	//std::string PrintCodeSaveArrayQuestionNotInTheSameBlock(AbstractQuestion * save_array_quest);
	//std::string PrintCodeRestoreArrayQuestionNotInTheSameBlock(AbstractQuestion * restore_array_quest);
	//string PrintSaveArrayQuestion(ActiveVariableInfo * av_info);
	//string PrintRestoreArrayQuestion(ActiveVariableInfo * av_info);
	//void PrintSaveMyPreviousIterationsData(StatementCompiledCode &code);
	//void PrintRestoreMyPreviousIterationsData(StatementCompiledCode &code);
	//friend bool IsInTheSameScopeAndLevel(AbstractQuestion *q1
	//				     , AbstractQuestion * q2);
	//friend bool NotInTheSameBlock(AbstractQuestion *q1, AbstractQuestion * q2);
	//friend bool IsAtAHigherNestLevelInTheSameBlock(AbstractQuestion *q1
	//					       , AbstractQuestion * q2);
	//friend bool IsAtADeeperNestLevelInTheSameBlock(AbstractQuestion *q1
	//					       , AbstractQuestion * q2);
	//bool QuestionIsInMyBlock(AbstractQuestion *q);
	//void SaveQuestionsInMyBlockThatAreAfterMe(StatementCompiledCode & code);
	//void RestoreQuestionsInMyBlockThatAreAfterMe(StatementCompiledCode & code);
	//void PrintUserNavigation(ostringstream & program_code);
	//void PrintUserNavigationArrayQuestion(ostringstream & program_code);
	int32_t GetMaxCode();
	bool VerifyQuestionIntegrity();
	//virtual Wt::WString PrintSelectedAnswers()=0;
	//virtual Wt::WString PrintSelectedAnswers(int code_index)=0;
	virtual string PrintSelectedAnswers()=0;
	virtual string PrintSelectedAnswers(int code_index)=0;

	bool check_and_store_input_data_single_question
		(string & err_mesg, string & re_arranged_buffer, int & pos_1st_invalid_data,
		 vector <int> & data);
	private:
		AbstractRuntimeQuestion& operator=(const AbstractRuntimeQuestion&);
		AbstractRuntimeQuestion (const AbstractRuntimeQuestion&);
};



//! RangeQuestion range questions in the qscript language become object instantiations of this class.
/*!
  	Below is an example of a RangeQuestion  - the allowed codes are hard coded
	numbers -> (1,2,5-8)
		q2 "Q2. This is AbstractQuestion 2" mp (5) int32_t (1,2,5-8);
*/
struct RangeQuestion: public AbstractRuntimeQuestion
{
	XtccSet * r_data;
	//vector <int32_t> stack_loop_index_values;
	//set<int32_t> displayData_;
	vector<display_data::DisplayDataUnit> displayData_;
#if 0
	//! this is only called in the compile time environment
	RangeQuestion(
		DataType this_stmt_type, int32_t line_number, string l_name
		, vector<TextExpression*> text_expr_vec, QuestionType l_q_type, int32_t l_no_mpn
		, DataType l_dt, XtccSet& l_r_data
		, vector<AbstractExpression*>& l_for_bounds_stack
		, CompoundStatement * l_enclosing_scope
		, vector<ActiveVariableInfo* > l_av_info
		, QuestionAttributes  l_question_attributes
		, const XtccSet & p_mutexCodeList
		);
#endif /* 0 */
	//! this is only called in the runtime environment
	RangeQuestion(
		DataType this_stmt_type, int32_t line_number, string l_name
		, vector<TextExpression*> text_expr_vec, QuestionType l_q_type, int32_t l_no_mpn
		, DataType l_dt, XtccSet& l_r_data
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		);


#if 0
	//! this is only called in the compile time environment
	RangeQuestion(
		DataType this_stmt_type, int32_t line_number, string l_name
		, vector<TextExpression*> text_expr_vec, QuestionType l_q_type, int32_t l_no_mpn
		, DataType l_dt, XtccSet& l_r_data
		, CompoundStatement * l_enclosing_scope
		, vector<ActiveVariableInfo* > l_av_info
		, QuestionAttributes  l_question_attributes
		, const XtccSet & p_mutexCodeList
		);
#endif /* 0 */

	//! this is only called in the runtime environment
	RangeQuestion(
		DataType this_stmt_type, int32_t line_number, string l_name
		, vector<TextExpression*> text_expr_vec, QuestionType l_q_type, int32_t l_no_mpn
		, DataType l_dt, XtccSet& l_r_data
		, const vector<int32_t> & l_loop_index_values
		, DummyArrayQuestion * l_dummy_array
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		);

	//void GenerateCode(StatementCompiledCode &code);
	//void GenerateCodeSingleQuestion(StatementCompiledCode &code, bool array_mode);
	virtual bool IsValid(int32_t value);
	//void eval();
#if 0
	void eval(/*qs_ncurses::*/WINDOW * question_window
		  , /*qs_ncurses::*/WINDOW* stub_list_window
		  , /*qs_ncurses::*/WINDOW* data_entry_window);
#endif /* 0 */
	void WriteDataToDisk(ofstream& data_file);
	//AbstractQuestion*  IsAQuestionStatement(){
	//	return this;
	//}
#if 0
	void  GetQuestionNames(vector<string> & question_list,
			       AbstractStatement* endStatement)
	{
		if (qscript_debug::DEBUG_RangeQuestion) {
			std::cout << "RangeQuestion::GetQuestionNames"
				  << std::endl;
		}
		if (this==endStatement)
			return;
		if (for_bounds_stack.size() == 0) {
			question_list.push_back(questionName_);
		} else {
			std::stringstream s;
			s << questionName_  << "_list.questionList["
			<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< "]";
			question_list.push_back(s.str());
		}
		if (next_) {
			next_->GetQuestionNames(question_list,endStatement);
		}
	}
#endif /* 0 */

	void MakeDisplaySummaryDataRanges();

	//Wt::WString PrintSelectedAnswers();
	//Wt::WString PrintSelectedAnswers(int code_index);
	string PrintSelectedAnswers();
	string PrintSelectedAnswers(int code_index);
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
class NamedStubQuestion: public AbstractRuntimeQuestion
{
	public:
	string named_list;
	named_range * nr_ptr;
	vector<stub_pair> * stub_ptr;
	vector<display_data::DisplayDataUnit> displayData_;
	int currentPage_;
	int totPages_;
	// this is a stack of indices - start and stop for each page
	vector <pair<int,int> > pageIndices_;
	int stubStartYIndex_;


	//! this is only called in the compile time environment
#if 0
	NamedStubQuestion(
		DataType this_stmt_type, int32_t line_number, string l_name
		, vector<TextExpression*> text_expr_vec, QuestionType l_q_type, int32_t l_no_mpn
		, DataType l_dt, named_range * l_nr_ptr
		, vector<AbstractExpression*>& l_for_bounds_stack
		, CompoundStatement * l_enclosing_scope
		, vector<ActiveVariableInfo* > l_av_info
		, QuestionAttributes  l_question_attributes
		);
	//! this is only called in the compile time environment
	NamedStubQuestion(
		DataType this_stmt_type, int32_t line_number, string l_name
		, vector<TextExpression*> text_expr_vec, QuestionType l_q_type, int32_t l_no_mpn
		, DataType l_dt, named_range * l_nr_ptr
		, CompoundStatement * l_enclosing_scope
		, vector<ActiveVariableInfo* > l_av_info
		, QuestionAttributes  l_question_attributes
		);
#endif /* 0 */

	NamedStubQuestion(
		DataType this_stmt_type, int32_t line_number, string l_name
		, vector<TextExpression*> text_expr_vec, QuestionType l_q_type, int32_t l_no_mpn
		//, DataType l_dt, vector<stub_pair> * l_stub_ptr
		, DataType l_dt, named_range * l_nr_ptr
		, vector<AbstractExpression*>& l_for_bounds_stack
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		);
	NamedStubQuestion(
		DataType this_stmt_type, int32_t line_number
		, string l_name, vector<TextExpression*> text_expr_vec
		, QuestionType l_q_type, int32_t l_no_mpn
		, DataType l_dt, named_range * l_nr_ptr
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		);
	//! only called in the runtime environment
	NamedStubQuestion(
		DataType this_stmt_type, int32_t line_number, string l_name
		, vector<TextExpression*> text_expr_vec, QuestionType l_q_type, int32_t l_no_mpn
		//, DataType l_dt, vector<stub_pair> * l_stub_ptr
		, DataType l_dt, named_range * l_nr_ptr
		, const vector<int32_t> & l_loop_index_values
		, DummyArrayQuestion * l_dummy_array
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		);

	//void GenerateCode(StatementCompiledCode &code);
	//void GenerateCodeSingleQuestion(StatementCompiledCode &code, bool array_mode);
	virtual bool IsValid(int32_t value);
	//void eval();
#if 0
	void eval(/*qs_ncurses::*/WINDOW * question_window
		  , /*qs_ncurses::*/WINDOW* stub_list_window
		  , /*qs_ncurses::*/WINDOW* data_entry_window);
#endif /* 0 */
	void WriteDataToDisk(ofstream& data_file);
	//Wt::WString PrintSelectedAnswers();
	//Wt::WString PrintSelectedAnswers(int code_index);
	string PrintSelectedAnswers();
	string PrintSelectedAnswers(int code_index);
	//AbstractQuestion* IsAQuestionStatement(){
	//	return this;
	//}
#if 0
	void  GetQuestionNames(vector<string> & question_list
			       , AbstractStatement* endStatement)
	{
		if (qscript_debug::DEBUG_NamedStubQuestion) {
			std::cout << "NamedStubQuestion::GetQuestionNames" << std::endl;
		}
		if (this==endStatement)
			return;
		if (for_bounds_stack.size() == 0) {
			question_list.push_back(questionName_);
		} else {
			std::stringstream s;
			s << questionName_  << "_list.questionList["
			<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< "]";
			question_list.push_back(s.str());
		}
		if (next_) {
			next_->GetQuestionNames(question_list, endStatement);
		}
	}
#endif /* 0 */
	void MakeDisplaySummaryDataRanges();

	//void ComputeVisiblePages (/*qs_ncurses::*/WINDOW * question_window
	//		     , /*qs_ncurses::*/WINDOW* stub_list_window
	//		     , /*qs_ncurses::*/WINDOW* data_entry_window
	//		     , WINDOW * error_msg_window);

	//void DisplayStubsPage(/*qs_ncurses::*/WINDOW * question_window
	//		     , /*qs_ncurses::*/WINDOW* stub_list_window
	//		     , /*qs_ncurses::*/WINDOW* data_entry_window
	//		     , WINDOW * error_msg_window);


	private:
		NamedStubQuestion& operator=(const NamedStubQuestion&);
		NamedStubQuestion (const NamedStubQuestion&);
};

class VideoQuestion: public AbstractRuntimeQuestion
{
public:
	string file_path;

	VideoQuestion(
			DataType this_stmt_type, int32_t line_number, string l_name
			, vector<TextExpression*> text_expr_vec
			, QuestionType l_q_type
			//, CompoundStatement * l_enclosing_scope
			//, vector<ActiveVariableInfo* > l_av_info
			, QuestionAttributes  l_question_attributes
			, bool l_isStartOfBlock
			, const string& path_to_media);

	virtual bool IsValid(int32_t value)
	{
		return true;
	}
	void WriteDataToDisk(ofstream& data_file);
	string PrintSelectedAnswers();
	string PrintSelectedAnswers(int code_index);
};



class DummyArrayQuestion: public AbstractRuntimeQuestion
{
	public:
	vector<int32_t> array_bounds;

	DummyArrayQuestion(string l_qno,
			vector<int32_t> l_array_bounds);

	void WriteDataToDisk(ofstream& data_file);
	//void eval(){}
	//void eval(/*qs_ncurses::*/WINDOW * question_window
	//	  , /*qs_ncurses::*/WINDOW* stub_list_window
	//	  , /*qs_ncurses::*/WINDOW* data_entry_window);


	bool IsValid(int32_t value){ return false;}
	//void GenerateCode(StatementCompiledCode &code){}
	//void GenerateCodeSingleQuestion(StatementCompiledCode &code, bool array_mode){}
#if 0
	void GetQuestionNames(vector<string> & question_list
			      , AbstractStatement* endStatement)
	{
		if (this==endStatement)
			return;
		if (next_) {
			next_->GetQuestionNames(question_list, endStatement);
		}
	}
#endif /* 0 */
	//Wt::WString PrintSelectedAnswers();
	//Wt::WString PrintSelectedAnswers(int code_index);
	string PrintSelectedAnswers();
	string PrintSelectedAnswers(int code_index);
	private:
		DummyArrayQuestion& operator=(const DummyArrayQuestion&);
		DummyArrayQuestion (const DummyArrayQuestion&);
};

//void Print_DisplayDataUnitVector(WINDOW * stub_list_window,
//		vector<display_data::DisplayDataUnit> & disp_vec,
//		int &xPos, int &yPos, int maxWinX);


#endif /* qscript_question_h */
