#include <algorithm>
#include <iostream>
#include <cstdlib>
#include "question.h"
#include "named_range.h"
#include "utils.h"
#include "UserResponse.h"
#include "expr.h"

using namespace std;

namespace qscript_parser {

	extern int32_t line_no;
}


#if 0
AbstractQuestion::AbstractQuestion(
	DataType l_type, int32_t l_no, string l_name, string l_text
	, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
	, QuestionAttributes  l_question_attributes
	, bool l_isStartOfBlock
	)
	: AbstractStatement(l_type, l_no), questionName_(l_name)
	, questionText_(l_text)
	, questionDiskName_(l_name)
	, q_type(l_q_type)
	, no_mpn(l_no_mpn), dt(l_dt), input_data()
	, for_bounds_stack(0), loop_index_values(0)
	, isAnswered_(false), isModified_(false)
	, enclosingCompoundStatement_(0), activeVarInfo_(0)
	, dummyArrayQuestion_(0), currentResponse_()
	, question_attributes(l_question_attributes)
	  , mutexCodeList_()
	  , maxCode_(0), isStartOfBlock_(l_isStartOfBlock)
{
	//cout << "creating AbstractQuestion: " << questionName_ << endl;
	if(enclosingCompoundStatement_ == 0){
		print_err(compiler_internal_error, " no enclosing CompoundStatement scope for question "
			, qscript_parser::line_no, __LINE__, __FILE__  );
	}
}
#endif /* 0 */

AbstractQuestion::~AbstractQuestion()
{
	for (int i=0; i<activeVarInfo_.size(); ++i) {
		delete activeVarInfo_[i];
		activeVarInfo_[i]=0;
	}
}


int32_t AbstractQuestion::GetMaxCode()
{
	if (maxCode_ == 0) {
		stringstream err_msg;
		err_msg << " maxCode_ == 0 should have been set: questionName_: "
			<< questionName_ << endl;
		print_err(compiler_internal_error, err_msg.str()
				, 0, __LINE__, __FILE__);
		exit(1);
	}
	return maxCode_;
}


void AbstractQuestion::GetQuestionsInBlock(
	vector<AbstractQuestion*> & question_list, AbstractStatement * stop_at)
{
	//std::cerr << "ENTER AbstractQuestion::GetQuestionsInBlock()" << std::endl;
	question_list.push_back(this);
	if(next_ && next_ != stop_at){
		next_->GetQuestionsInBlock(question_list, stop_at);
	}
	//std::cerr << "EXIT AbstractQuestion::GetQuestionsInBlock()" << std::endl;
}


RangeQuestion::~RangeQuestion()
{
	delete r_data ; r_data = 0;
}

DummyArrayQuestion::DummyArrayQuestion(string l_qno, vector<int32_t> l_array_bounds)
	: AbstractQuestion(QUESTION_TYPE, 0, 0, 0, l_qno
			, vector <TextExpression*> () //string(l_qno + "_dummy")
			, spn, 0
			   , INT32_TYPE, QuestionAttributes(true, true), false /* isStartOfBlock_ does not matter i think for DummyArrayQuestion */)
	,  array_bounds(l_array_bounds)
{ 
	TextExpression * t_expr = new TextExpression(l_qno + string("dummy"));
	textExprVec_.push_back (t_expr);
}

void DummyArrayQuestion::eval(/*qs_ncurses::*/WINDOW * question_window
		  , /*qs_ncurses::*/WINDOW* stub_list_window
		  , /*qs_ncurses::*/WINDOW* data_entry_window
		  , WINDOW * error_msg_window)
{ }


bool NamedStubQuestion::IsValid(int32_t value)
{
	//vector<stub_pair> & vec= *stub_ptr;
	vector<stub_pair> & vec= (nr_ptr->stubs);
	for (uint32_t j = 0; j < vec.size(); ++j) {
		if (vec[j].code == value && vec[j].mask) {
			return true;
		}
	}
	return false;
}


bool RangeQuestion::IsValid(int32_t value)
{
	return (r_data->exists(value))? true: false;
}


TextExpression::TextExpression(string text)
	: teType_(TextExpression::simple_text_type), 
	  text_(text), nameExpr_(0),
	  naPtr_(0), naIndex_(-1),
	  pipedQuestion_(0), questionIndexExpr_(0), codeIndex_(-1)
{ }

TextExpression::TextExpression(Unary2Expression * expr)
	: teType_(TextExpression::named_attribute_type), 
	  text_(), nameExpr_(expr),
	  naPtr_(0), naIndex_(-1),
	  pipedQuestion_(0), questionIndexExpr_(0), codeIndex_(-1)
{ }
// for DummyArrayQuestion
TextExpression::TextExpression()
	: teType_(TextExpression::simple_text_type), 
	  text_(), nameExpr_(0),
	  naPtr_(0), naIndex_(0),
	  pipedQuestion_(0), questionIndexExpr_(0), codeIndex_(-1)
{ }

TextExpression::TextExpression(named_attribute_list * na_ptr, int na_index)
	: teType_(TextExpression::named_attribute_type),
	  text_(), nameExpr_(0),
	  naPtr_(na_ptr), naIndex_(na_index),
	  pipedQuestion_(0), questionIndexExpr_(0), codeIndex_(-1)
{ }

TextExpression::TextExpression(AbstractQuestion * q, int code_index)
	: teType_(TextExpression::question_type),
	  text_(), nameExpr_(0),
	  naPtr_(0), naIndex_(0),
	  pipedQuestion_(q), questionIndexExpr_(0), codeIndex_ (code_index)
{ }

TextExpression::TextExpression (AbstractQuestion * q, AbstractExpression * expr)
	: teType_ (TextExpression::question_type), 
	  text_(), nameExpr_(0),
	  naPtr_ (0), naIndex_ (-1),
	  pipedQuestion_ (q), questionIndexExpr_ (expr), codeIndex_ (-1)
{ }

TextExpression::TextExpression (AbstractQuestion * q)
	: teType_ (TextExpression::question_type), 
	  text_(), nameExpr_(0),
	  naPtr_ (0), naIndex_ (-1),
	  pipedQuestion_ (q), questionIndexExpr_ (0), codeIndex_ (-1)
{ }



void DummyArrayQuestion::GetQuestionNames(vector<string> & question_list
			      , AbstractStatement* endStatement)
{
	if (this==endStatement)
		return;
	if (next_) {
		next_->GetQuestionNames(question_list, endStatement);
	}
}

void NamedStubQuestion::GetQuestionNames(vector<string> & question_list
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
		//std::stringstream s;
		//s << questionName_  << "_list.questionList["
		//<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
		//<< "]";
		//question_list.push_back(s.str());
		question_list.push_back(questionName_);
	}
	if (next_) {
		next_->GetQuestionNames(question_list, endStatement);
	}
}


void  RangeQuestion::GetQuestionNames(vector<string> & question_list,
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
		//std::stringstream s;
		//s << questionName_  << "_list.questionList["
		//<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
		//<< "]";
		//question_list.push_back(s.str());
		question_list.push_back(questionName_);
	}
	if (next_) {
		next_->GetQuestionNames(question_list,endStatement);
	}
}


std::string DummyArrayQuestion::PrintSelectedAnswers()
{
	return std::string();
}


std::string DummyArrayQuestion::PrintSelectedAnswers(int code_index)
{
	return std::string();
}

string AbstractQuestion::AxPrepareQuestionTitleSPSS()
{
	stringstream quest_decl;
	for (int i=0; i < textExprVec_.size(); ++i) {
		if (textExprVec_[i]->teType_ == TextExpression::simple_text_type) { 
			quest_decl 
				<< textExprVec_[i]->text_
				;
		} else if (textExprVec_[i]->teType_ == TextExpression::question_type) {
			if (textExprVec_[i]->questionIndexExpr_ ) {
				ExpressionCompiledCode expr_code;
				textExprVec_[i]->questionIndexExpr_->PrintExpressionCode(expr_code);
				quest_decl << "text_expr_vec.push_back( new TextExpression(" 
						<< textExprVec_[i]->pipedQuestion_->questionName_
						<< ", "
						<< expr_code.code_expr.str()
						<< ") ); /*  -NxD- */\n";
			} else {
				quest_decl << "text_expr_vec.push_back( new TextExpression(" 
						<< textExprVec_[i]->pipedQuestion_->questionName_
						<< ") ); /*  -NxD- */\n";
			}
		} else if (textExprVec_[i]->teType_ == TextExpression::named_attribute_type) {
			quest_decl << textExprVec_[i]->naPtr_->attribute[textExprVec_[i]->naIndex_];
		} else {
			ExpressionCompiledCode expr_code;
			textExprVec_[i]->nameExpr_->PrintExpressionCode(expr_code);
			quest_decl << "text_expr_vec.push_back(new TextExpression("
				<< expr_code.code_expr.str()
				<< "));\n";
		}
	}
	return quest_decl.str();
}

string AbstractQuestion::AxPrepareQuestionTitle()
{
	stringstream quest_decl;
	for (int i=0; i < textExprVec_.size(); ++i) {
		if (textExprVec_[i]->teType_ == TextExpression::simple_text_type) { 
			quest_decl 
				<< textExprVec_[i]->text_
				;
		} else if (textExprVec_[i]->teType_ == TextExpression::question_type) {
			//if (textExprVec_[i]->questionIndexExpr_ ) {
			//	ExpressionCompiledCode expr_code;
			//	textExprVec_[i]->questionIndexExpr_->PrintExpressionCode(expr_code);
			//	quest_decl << "text_expr_vec.push_back( new TextExpression(" 
			//			<< textExprVec_[i]->pipedQuestion_->questionName_
			//			<< ", "
			//			<< expr_code.code_expr.str()
			//			<< ") ); /*  -NxD- */\n";
			//} else {
			//	quest_decl << "text_expr_vec.push_back( new TextExpression(" 
			//			<< textExprVec_[i]->pipedQuestion_->questionName_
			//			<< ") ); /*  -NxD- */\n";
			//}
		} else {
			//ExpressionCompiledCode expr_code;
			//textExprVec_[i]->nameExpr_->PrintExpressionCode(expr_code);
			//quest_decl << "text_expr_vec.push_back(new TextExpression("
			//	<< expr_code.code_expr.str()
			//	<< "));\n";
		}
	}
	return quest_decl.str();
}

string AbstractQuestion::PrepareQuestionTitle()
{
	stringstream quest_decl;
	quest_decl << "vector<TextExpression *> text_expr_vec;\n";
	for (int i=0; i < textExprVec_.size(); ++i) {
		if (textExprVec_[i]->teType_ == TextExpression::simple_text_type) { 
			quest_decl << "text_expr_vec.push_back(new TextExpression(string(\""
				<< textExprVec_[i]->text_
				<< "\")));\n";
		} else if (textExprVec_[i]->teType_ == TextExpression::question_type) {
			
			if (textExprVec_[i]->questionIndexExpr_ ) {
				ExpressionCompiledCode expr_code;
				textExprVec_[i]->questionIndexExpr_->PrintExpressionCode(expr_code);
				quest_decl << "text_expr_vec.push_back( new TextExpression(" 
						<< textExprVec_[i]->pipedQuestion_->questionName_
						<< ", "
						<< expr_code.code_expr.str()
						<< ") ); /*  -NxD- */\n";
			} else {
				quest_decl << "text_expr_vec.push_back( new TextExpression(" 
						<< textExprVec_[i]->pipedQuestion_->questionName_
						<< ") ); /*  -NxD- */\n";
			}
		} else {
			ExpressionCompiledCode expr_code;
			textExprVec_[i]->nameExpr_->PrintExpressionCode(expr_code);
			quest_decl << "text_expr_vec.push_back(new TextExpression("
				<< expr_code.code_expr.str()
				<< "));\n";
		}
	}
	return quest_decl.str();
}


#include <cstdlib>

set<int> pick_random_values_from_these_answers (vector<int> valid_answers, int no_mpn, string qno, XtccSet& mutex_code_list)
{
	cout << __PRETTY_FUNCTION__  << "qno: " << qno 
		<< "valid_answers.size(): " << valid_answers.size() 
		<< endl;
	set<int> input_data;
	int n_mutex_codes = mutex_code_list.count();

	if (valid_answers.size() == 1) {
		input_data.insert (valid_answers[0]);
		cout << "setting "  
			<< qno
			<< " input_data with only answer available"
			<< valid_answers[0] << endl;
	} else {
		int n_random_answers = 1;
		if (no_mpn > 1) {
			n_random_answers = rand() % no_mpn;
			// yup - a bias introduced here, sue me
			if (n_random_answers == 0) {
				n_random_answers = 1; 
			}
			// if we dont do this we could have an infinite loop
			if (n_random_answers > valid_answers.size() - n_mutex_codes) {
				n_random_answers = valid_answers.size() - n_mutex_codes;
				cout << "setting n_random_answers to valid_answers.size() : "
					<< valid_answers.size() << " -  n_mutex_codes: "
					<< n_mutex_codes
					<< endl;
			}
			// after this adjustment n_random_answers can still be 1
			// consider this case
			// q1 "q1" mp(3) int32_t (1, 98, 99) mutex (98, 99)
			// above n_random_answers can start at 3
			// but then n_random_answers is set to 3 - 2 = 1
			// if we didnt do the above
			// we could have n_random_answers = 3
			// but preventing mutexes would prevent us from
			// filling up more answers - resulting in an
			// infinite loop
		}
		if (n_random_answers == 1) {
			// see comment above
			int rvi = static_cast<int>  ( rand() % valid_answers.size());
			input_data.insert (valid_answers[rvi]);
		} else if (n_random_answers == no_mpn && no_mpn > 1) {
			for (int i = 0; i < valid_answers.size(); ++i) {
				input_data.insert ( valid_answers[i]);
			}
		} else {
			set<int> already_inserted;
			bool is_first_answer = true;
			for (int i = 0; i < n_random_answers; ++i) {
get_another_random_value:
				int rvi = static_cast<int>  ( rand() % valid_answers.size());
				if        (is_first_answer == true  && mutex_code_list.exists (valid_answers[rvi])) {
					input_data.insert (valid_answers[rvi]);
					break;
				} else if (is_first_answer == false && mutex_code_list.exists (valid_answers[rvi])) {
					cout << "preventing mutex value to be allowed with normal answers as it was not selected as the 1st answer"
						<< endl;
					// we have taken care of inifinite loop prevention
					// by adjusting n_random_answers = valid_answers - n_mutex_codes
					goto get_another_random_value;
				} else {
					// is_first_answer == true  and not a mutex code
					// is_first_answer == false and not a mutex code
					if (already_inserted.find (rvi) == already_inserted.end()) {
						input_data.insert (valid_answers[rvi]);
						already_inserted.insert (rvi);
					} else {
						goto get_another_random_value;
					}
					input_data.insert (valid_answers[rvi]);
					is_first_answer = false;
				}
			}
		}
	}
	return input_data;
}

void RangeQuestion::generateRandomAnswers()
{
	vector<int> valid_answers;
	cout << questionName_ << ": putting into valid_answers : ";
	for (int i = 0; i < r_data->range.size(); ++i) {
		for (int lb = r_data->range[i].first;
				lb <= r_data->range[i].second; ++lb) {
			cout << " " << lb;
			valid_answers.push_back (lb);
		}
	}
	

	cout << " | ";
	for (set<int>::iterator it = r_data->indiv.begin();
			it != r_data->indiv.end(); ++it) {
		cout << " " << *it;
		valid_answers.push_back (*it);
	}

	cout << endl;

#if 0
	if (valid_answers.size() == 1) {
		input_data.insert (valid_answers[0]);
	} else {
		int n_random_answers = rand() % no_mpn;
		if (n_random_answers > valid_answers.size()) {
			n_random_answers = valid_answers.size();
		}
		// yup - a bias introduced here, sue me
		if (n_random_answers == 0) {
			n_random_answers = 1; 
		}
		if (n_random_answers == no_mpn) {
			for (int i = 0; i < valid_answers.size(); ++i) {
				input_data.insert ( valid_answers[i]);
			}
		} else {
			set<int> already_inserted;
			for (int i = 0; i < n_random_answers; ++i) {
get_another_random_value:
				int rvi = static_cast<int>  ( rand() % valid_answers.size());
				if (already_inserted.find (rvi) == already_inserted.end()) {
					input_data.insert (valid_answers[rvi]);
					already_inserted.insert (rvi);
				} else {
					goto get_another_random_value;
				}
			}
		}
	}
#endif /*  0 */
#if 0
		int n_random_answers = rand() % no_mpn;
		if (n_random_answers > valid_answers.size()) {
			n_random_answers = valid_answers.size();
		}
		// yup - a bias introduced here, sue me
		if (n_random_answers == 0) {
			n_random_answers = 1; 
		}
#endif /*  0 */
	input_data = pick_random_values_from_these_answers (valid_answers, no_mpn, questionName_, mutexCodeList_);

}

void NamedStubQuestion::generateRandomAnswers()
{
	vector<int> valid_answers;
	vector<stub_pair> & vec = (nr_ptr->stubs);
	for (uint32_t j = 0; j < vec.size(); ++j) {
		if (vec[j].mask) {
			valid_answers.push_back (vec[j].code);
		}
	}
#if 0
	if (valid_answers.size() == 1) {
		input_data.insert (valid_answers[0]);
	} else {

		int n_random_answers = rand() % no_mpn;
		if (n_random_answers > valid_answers.size()) {
			n_random_answers = valid_answers.size();
		}
		// yup - a bias introduced here, sue me
		if (n_random_answers == 0) {
			n_random_answers = 1; 
		}

	}
#endif
	input_data = pick_random_values_from_these_answers (valid_answers, no_mpn, questionName_, mutexCodeList_);
}

void DummyArrayQuestion::generateRandomAnswers()
{

}
