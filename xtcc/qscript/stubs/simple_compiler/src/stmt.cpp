/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/stmt.C
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

#include <inttypes.h>
#include <sys/types.h>
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "expr.h"
#include "debug_mem.h"
#include "stmt.h"
#include "question.h"
#include "named_range.h"
#include "qscript_parser.h"
#include "symtab.h"
#include "qscript_debug.h"
#include "code_gen_utils.h"
#include "utils.h"
#include "log_mesg.h"


//extern vector<mem_addr_tab> mem_addr;
using qscript_parser::mem_addr;
extern int32_t if_line_no;
using qscript_parser:: active_scope;
//extern vector </*Statement::*/FunctionInformation*> func_info_table;
using qscript_parser::func_info_table;
int32_t CompoundStatement::counter_;
using qscript_parser::debug_log_file;
using std::cout;
using std::cerr;
using std::endl;
using std::stringstream;
string PrintConsolidatedForLoopIndex(vector<AbstractExpression*> for_bounds_stack);
void InitStatement()
{
	CompoundStatement::counter_ = 0;
}


//AbstractQuestion* AbstractStatement::IsAQuestionStatement() { return 0; }
#if 0
void AbstractStatement::GetQuestionNames(vector<string> &question_list,
					 AbstractStatement * endStatement)
{
	if (this == endStatement)
		return;
	if (next_){
		next_->GetQuestionNames(question_list, endStatement);
	}
}

void AbstractStatement::GetQuestionsInBlock(vector<AbstractQuestion*> & question_list,
					    AbstractStatement * stop_at)
{
	//cerr << "ENTER AbstractStatement::GetQuestionsInBlock: ";
	//cerr << human_readable_type(type_) << endl;
	if (next_ && next_ != stop_at){
		next_->GetQuestionsInBlock(question_list, stop_at);
	}
	//cerr << "Exit AbstractStatement::GetQuestionsInBlock\n";
}

void AbstractStatement::GenerateConsolidatedForLoopIndexes()
{
	//cout << "ENTER AbstractStatement::GenerateConsolidatedForLoopIndexes:" << endl;
	if (next_) {
		next_->GenerateConsolidatedForLoopIndexes();
	}
	//cout << "EXIT AbstractStatement::GenerateConsolidatedForLoopIndexes:" << endl;
}

void AbstractStatement::Generate_ComputeFlatFileMap(StatementCompiledCode & code)
{
	if (next_) {
		next_->Generate_ComputeFlatFileMap(code);
	}
}
#endif /* 0 */

//extern ofstream debug_log_file;
void read_data(const char * prompt);
void ExpressionStatement::GenerateCode(StatementCompiledCode &code)
{
	code.program_code << "/* ENTER ExpressionStatement::GenerateCode */" << endl;
	ExpressionCompiledCode expr_code;
	expression_->PrintExpressionCode(expr_code);
	code.program_code << expr_code.code_bef_expr.str() << expr_code.code_expr.str() << ";" << endl;
	if (next_){
		code.program_code << "/* EXIT ExpressionStatement::GenerateCode */" << endl;
		next_->GenerateCode(code);
	}
}


ExpressionStatement::~ExpressionStatement()
{
	using qscript_parser::mem_addr;
	for (uint32_t i = 0; i< mem_addr.size(); ++i){
		if (this == mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr = 0;
			debug_log_file << "ExpressionStatement::~ExpressionStatement: setting mem_addr: " << this << " = 0" << endl;
			break;
		}
	}
	debug_log_file << "deleting ExpressionStatement" << endl;
	//if (next_) delete next_;
	if (expression_) delete expression_;
}





void DeclarationStatement::GenerateCode(StatementCompiledCode &code)
{
	if (qscript_debug::DEBUG_DeclarationStatement)
		cout << " // DeclarationStatement::GenerateCode " << endl;
	//ostringstream code_expr1, code_bef_expr1;
	ExpressionCompiledCode expr_code;
	if (symbolTableEntry_->e){
		symbolTableEntry_->e->PrintExpressionCode(expr_code);
		code.program_code << expr_code.code_bef_expr.str();
	}
	if (type_ >= INT8_TYPE && type_  <= DOUBLE_TYPE){
		code.program_code << noun_list[type_].sym
			<< " " << symbolTableEntry_->name_;
	} else if (type_  >= INT8_ARR_TYPE && type_  <= DOUBLE_ARR_TYPE){
		DataType tdt = DataType(INT8_TYPE + type_-INT8_ARR_TYPE);
		code.program_code << noun_list[tdt].sym
			<< symbolTableEntry_->name_ << "["
			<< symbolTableEntry_->n_elms << "]";
	} else if (type_  >= INT8_REF_TYPE&& type_  <= DOUBLE_REF_TYPE){
		DataType tdt = DataType(INT8_TYPE + type_-INT8_REF_TYPE);
		code.program_code << noun_list[tdt].sym
			<< " & " << symbolTableEntry_->name_;
	}
	if (symbolTableEntry_->e){
		code.program_code << " = " << expr_code.code_expr.str();

	}
	code.program_code << ";" << endl;

	if (next_){
		next_->GenerateCode(code);
	}
}



DeclarationStatement::~DeclarationStatement()
{
	using qscript_parser::mem_addr;
	for (uint32_t i = 0; i< mem_addr.size(); ++i){
		if (this == mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr = 0;
			debug_log_file << "DeclarationStatement::~DeclarationStatement: setting mem_addr: " << this << " = 0" << endl;
			break;
		}
	}
	debug_log_file << "deleting DeclarationStatement" << endl;

}

IfStatement::IfStatement(DataType dtype, int32_t lline_number
			 , AbstractExpression * lcondition
			 , AbstractStatement * lif_body
			 , AbstractStatement * lelse_body)
	: AbstractStatement(dtype, lline_number)
	, ifCondition_(lcondition), ifBody_(lif_body), elseBody_(lelse_body)
{
	if (lcondition->type_ == VOID_TYPE || lcondition->type_ == ERROR_TYPE){
		print_err(compiler_sem_err,
			  "If ifCondition_ expression has Void or Error Type",
			  qscript_parser::if_line_no, __LINE__, __FILE__);
	} else {
	}
}

void IfStatement::GetQuestionsInBlock(vector<AbstractQuestion*> & question_list
		,AbstractStatement* stop_at)
{
	if(stop_at==this)
		return;
	ifBody_->GetQuestionsInBlock(question_list, stop_at);
	if( elseBody_)
		elseBody_->GetQuestionsInBlock(question_list, stop_at);
	if (next_ && next_ != stop_at){
		next_->GetQuestionsInBlock(question_list, stop_at);
	}
}

struct IfStatementStackElement
{
	int32_t nestLevel_;
	IfStatement * ifStatementPtr_;
	IfStatementStackElement(int32_t nest_level, IfStatement	* if_stmt_ptr)
		: nestLevel_(nest_level), ifStatementPtr_(if_stmt_ptr)
	{ }
};

void IfStatement::GenerateCode(StatementCompiledCode &code)
{
	//cerr << "ENTER: IfStatement::GenerateCode()" << endl;
	if (qscript_debug::DEBUG_IfStatement) {
		code.array_quest_init_area << "/* ENTER " << __PRETTY_FUNCTION__ << ", "
				<< __FILE__ << ", " << __LINE__
				<< " source lineNo_: " << lineNo_
				<< " */\n";
	}

	static vector<IfStatementStackElement*> ifStatementStack;
	static int32_t if_nest_level =0;
	bool if_nest_level_was_increased = false;
	//++if_nest_level;
	if (ifStatementStack.size()>0) {
		if (this == ifStatementStack[ifStatementStack.size()-1]
				->ifStatementPtr_->elseBody_){
			code.program_code <<
				"// if statement at same level of nesting"
				" as previous if i.e. part of the else if"
				" clause: if_nest_level: "
				<< if_nest_level
				<< endl;
		} else {
			++if_nest_level;
			if_nest_level_was_increased = true;
		}
	} else {
		++if_nest_level;
		if_nest_level_was_increased = true;
	}
	//ostringstream code_bef_expr, code_expr;
	ExpressionCompiledCode expr_code;
	expr_code.code_bef_expr << "/* if_nest_level: " << if_nest_level << " */\n";
	expr_code.code_expr << "if (";
	ifCondition_->PrintExpressionCode(expr_code);
	expr_code.code_expr << ") {";
	code.program_code << expr_code.code_bef_expr.str()
		<< expr_code.code_expr.str();
	vector<string> question_list_else_body;
	code.program_code << "// ifStatementStack.size(): "
		<< ifStatementStack.size() << endl;
	if (ifStatementStack.size() > 0) {
		for(int32_t i = 0; i < ifStatementStack.size(); ++i){
			if (ifStatementStack[i]->nestLevel_ == if_nest_level){
				ifStatementStack[i]->ifStatementPtr_
					->GetQuestionNames
					(question_list_else_body, this);
				break;
			}
		}
	}
	code.program_code << "// question_list_else_body :" ;
	for (int32_t i=0; i<question_list_else_body.size(); ++i) {
		code.program_code << " " << question_list_else_body[i];
	}
	code.program_code << endl;
	if (elseBody_) {
		//elseBody_->GetQuestionNames(question_list_else_body, 0);
		elseBody_->GetQuestionNames(question_list_else_body, next_);
		// this problem has been syntactically handled - the compiler does not allow an empty
		// else block if the "if" block has questions in it
		// stringstream mesg;
		// mesg << "In case else body of question is blank - need to automatically generate a dummy, empty compound block and run GetQuestionNames on it - right now the user has to do this on his own";
		// LOG_MAINTAINER_MESSAGE(mesg.str());
	} else {
		// this problem has been syntactically handled - the compiler does not allow an empty
		// else block if the "if" block has questions in it
		// stringstream mesg;
		// mesg << "In case else body of question is blank - need to automatically generate a dummy, empty compound block and run GetQuestionNames on it - right now the user has to do this on his own";
		// LOG_MAINTAINER_MESSAGE(mesg.str());
	}
	for(int32_t i = 0; i < question_list_else_body.size(); ++i) {
		code.program_code <<  question_list_else_body[i]
			<< "->isAnswered_ = false;"
			<< endl;
	}
	ifBody_->GenerateCode(code);
	code.program_code << " }" << endl;

	// need at this scope level to detect missing else blocks
	vector<string> question_list_if_body;
	if (elseBody_) {
		code.program_code << " else {" << endl;

		IfStatement * elseIfStatement = dynamic_cast<IfStatement*>
						(elseBody_);
		if (elseIfStatement){
			IfStatementStackElement *  stk_el=
				new IfStatementStackElement(if_nest_level,
					this);

			code.program_code <<
				"// pushing onto ifStatementStack \n";

			ifStatementStack.push_back(stk_el);
		}

		//vector<string> question_list_if_body;

		for (int32_t i = 0; i < ifStatementStack.size(); ++i) {
			if (ifStatementStack[i]->nestLevel_ == if_nest_level) {
				ifStatementStack[i]->ifStatementPtr_
					->GetQuestionNames
					(question_list_if_body, this);
				break;
			}
		}
		//ifBody_->GetQuestionNames(question_list_if_body, 0);
		ifBody_->GetQuestionNames(question_list_if_body, next_);

		code.program_code << "// end of ifBody_->GetQuestionNames \n";
		if (elseIfStatement) {
			//elseIfStatement->elseBody_->GetQuestionNames
			//	(question_list_if_body, 0);
			code.program_code << " // elseIfStatement exists \n";
		} else {
			code.program_code << " // elseIfStatement DOES NOT exists \n";
			code.program_code << "/* question_list_if_body.size(): "
				<< question_list_if_body.size() << " */ \n";
			for(int32_t i = 0; i < question_list_if_body.size(); ++i){
				code.program_code <<  question_list_if_body[i]
					<< "->isAnswered_ = false;"
					<< endl;
			}
			code.program_code << "// **************** \n";
		}
		elseBody_->GenerateCode(code);

		if (elseIfStatement) {
			IfStatementStackElement * stk_el =
				ifStatementStack.back();
			delete stk_el;
			ifStatementStack.pop_back();
		}
		code.program_code << "}" << endl;
	}

	if (if_nest_level_was_increased){
		--if_nest_level;
		if_nest_level_was_increased = false;
	}

	if (qscript_debug::DEBUG_IfStatement) {
		code.program_code << " /* finished generating code IfStatement */ " << endl;
		code.array_quest_init_area << "/* EXIT " << __PRETTY_FUNCTION__ << ", "
				<< __FILE__ << ", " << __LINE__ << ", source line no:" << lineNo_ << " */\n";
	}

	if (elseBody_ == 0 ) {
		// cout << LOG_MESSAGE("elseBody_ == 0");
		// this call below is for error detection
		code.program_code << "// elseBody_ == 0 - detecting if ifBody_ has questions: yes => we flag an error" << endl;
		//ifBody_->GetQuestionNames(question_list_if_body, 0);
		ifBody_->GetQuestionNames(question_list_if_body, next_);
		code.program_code << "// question_list_if_body: " ;
		for (int32_t i=0; i<question_list_if_body.size(); ++i) {
			code.program_code << " " << question_list_if_body[i];
		}
		code.program_code << endl;
		if (question_list_if_body.size() > 0 || question_list_else_body.size()>0) {
			stringstream s;
			s << "If block on line number: " << lineNo_ << " has questions but does not have an else block. Please add a dummy else block like this" << endl
				<< " CODE EXAMPLE FOR DUMMY ELSE BLOCK FOLLOWS " << endl
				<< " /* ************************************* */" << endl
				<< " else {\n\t1;\n}\n"
				<< " /* ************************************* */" << endl
				<< " END OF CODE EXAMPLE" << endl
				<< " although the dummy else block seems irrelevant it helps the compiler produce correct code to handle if else statements"
				<< endl;
			print_err(compiler_sem_err, s.str(), lineNo_, __LINE__, __FILE__);
			++qscript_parser::no_errors;
		}
	}
	if (next_)
		next_->GenerateCode(code);
	//cerr << "EXIT: IfStatement::GenerateCode()" << endl;
}

void IfStatement::Generate_ComputeFlatFileMap(StatementCompiledCode & code)
{
	ostringstream base_text;
	ifCondition_->PrintExpressionText(base_text);
	if (qscript_parser::flag_dynamic_base_text == false) {
		code.program_code << "base_text_vec.push_back(BaseText(\"" << base_text.str() << "\"));\n";
	} else {
		code.program_code
			<< "BaseText btxt(\"" << base_text.str() << "\", true,"
			<< qscript_parser::dynamic_base_text_question->questionName_ << " );\n"
			<< "base_text_vec.push_back(btxt);\n";
	}
	qscript_parser::flag_dynamic_base_text = false;
	ifBody_->Generate_ComputeFlatFileMap(code);
	code.program_code << "base_text_vec.pop_back();\n";
	code.program_code << "base_text_vec.push_back(BaseText(\"Not " << base_text.str() << "\"));\n";
	if (elseBody_) {
		elseBody_->Generate_ComputeFlatFileMap(code);
	}
	code.program_code << "base_text_vec.pop_back();\n";
	if (next_) {
		next_->Generate_ComputeFlatFileMap(code);
	}
}

void IfStatement::GenerateConsolidatedForLoopIndexes()
{
	//cout << "ENTER IfStatement::GenerateConsolidatedForLoopIndexes:" << endl;
	if (ifBody_) {
		ifBody_->GenerateConsolidatedForLoopIndexes();
	}
	if (elseBody_) {
		elseBody_->GenerateConsolidatedForLoopIndexes();
	}
	if (next_) {
		next_->GenerateConsolidatedForLoopIndexes();
	}
	//cout << "EXIT IfStatement::GenerateConsolidatedForLoopIndexes:" << endl;
}


IfStatement:: ~IfStatement()
{
	using qscript_parser::mem_addr;
	for (uint32_t i = 0; i< mem_addr.size(); ++i){
		if (this == mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr = 0;
			debug_log_file
				<< "IfStatement::~IfStatement setting mem_addr:"
				<< this << " = 0" << endl;
			break;
		}
	}
	debug_log_file << "deleting IfStatement" << endl;
	delete ifCondition_;
	delete ifBody_;
	if (elseBody_) delete elseBody_;
}

// There is a reason the Scope pointer in the
// compound statement is initialised to 0
//  - if the CompoundStatement is part of a function body
// the the variables

vector<string> consolidated_for_loop_index_stack;

CompoundStatement::CompoundStatement(
	DataType dtype, int32_t lline_number, int32_t l_flag_cmpd_stmt_is_a_func_body
	, int32_t l_flag_cmpd_stmt_is_a_for_body
	, vector<AbstractExpression*>& l_for_bounds_stack
	):
	AbstractStatement(dtype, lline_number)
	, compoundBody_(0), scope_(0)
	, flagIsAFunctionBody_(l_flag_cmpd_stmt_is_a_func_body)
	, flagIsAForBody_(l_flag_cmpd_stmt_is_a_for_body)
	, counterContainsQuestions_(0), compoundStatementNumber_(0)
	, flagGeneratedQuestionDefinitions_(false)
	, for_bounds_stack(l_for_bounds_stack), questionsInBlock_(0)
	, nestedCompoundStatementStack_(0), ConsolidatedForLoopIndexStack_(0)
	, flagIsAIfBody_(0)
{
	compoundStatementNumber_ = CompoundStatement::counter_++;
}

void CompoundStatement::GenerateConsolidatedForLoopIndexes()
{
	//cout << "ENTER CompoundStatement::GenerateConsolidatedForLoopIndexes:" << endl;
	// old code: if (flagIsAForBody_ && counterContainsQuestions_)
	if (flagIsAForBody_ && counterContainsQuestions_ && !flagIsAIfBody_) {
		ostringstream consolidated_loop_counter;
		consolidated_loop_counter << "consolidated_for_loop_index_" << compoundStatementNumber_;
		//cout << "generated " << consolidated_loop_counter.str() << endl;
		consolidated_for_loop_index_stack.push_back(consolidated_loop_counter.str());
	}
	ConsolidatedForLoopIndexStack_ = consolidated_for_loop_index_stack;
	if (compoundBody_) {
		compoundBody_->GenerateConsolidatedForLoopIndexes();
	}
	if (flagIsAForBody_ && counterContainsQuestions_ && !flagIsAIfBody_) {
		//cout << "popping off " << consolidated_for_loop_index_stack.back() << endl;
		consolidated_for_loop_index_stack.pop_back();
	}
	//cout << "EXIT CompoundStatement::GenerateConsolidatedForLoopIndexes:" << endl;
	if (next_) {
		next_->GenerateConsolidatedForLoopIndexes();
	}
}

void CompoundStatement::GetQuestionsInBlock(
	vector<AbstractQuestion*> & question_list
	, AbstractStatement * stop_at)
{
	//cerr << "ENTER: CompoundStatement::GetQuestionsInBlock" << endl;
	if (compoundBody_){
		compoundBody_->GetQuestionsInBlock(question_list, stop_at);
	}
	if (next_ && next_ != stop_at){
		next_->GetQuestionsInBlock(question_list, stop_at);
	}
	//cerr << "EXIT: CompoundStatement::GetQuestionsInBlock" << endl;
}

void CompoundStatement::GenerateQuestionArrayInitLoopOpen(
	StatementCompiledCode &code)
{
	if (qscript_debug::DEBUG_CompoundStatement) {
		code.array_quest_init_area << "// ENTER " << __PRETTY_FUNCTION__
			<< " source line no: " << lineNo_ <<  "\n";
	}
	for(int32_t i = for_bounds_stack.size()-1; i< for_bounds_stack.size(); ++i){
		code.array_quest_init_area << "for(int32_t ";
		BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(for_bounds_stack[i]);
		if (bin_expr_ptr){
			//AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
			AbstractExpression * lhs = bin_expr_ptr->leftOperand_;
			ExpressionCompiledCode expr_code1;
			lhs->PrintExpressionCode(expr_code1);
			code.array_quest_init_area << expr_code1.code_bef_expr.str() << expr_code1.code_expr.str();
			code.array_quest_init_area << " = 0;";
			ExpressionCompiledCode expr_code2;
			for_bounds_stack[i]->PrintExpressionCode(expr_code2);
			code.array_quest_init_area << expr_code2.code_bef_expr.str() << expr_code2.code_expr.str();
			code.array_quest_init_area << "; ++";
			ExpressionCompiledCode expr_code3;
			lhs->PrintExpressionCode(expr_code3);
			code.array_quest_init_area << expr_code3.code_bef_expr.str() << expr_code3.code_expr.str();
			code.array_quest_init_area <<	"){" << endl;
			if (i == 0){
				code.array_quest_init_area << "vector<int32_t> stack_of_loop_indices;\n";
					//<< "(" <<  for_bounds_stack.size() << ");\n";
			}
			code.array_quest_init_area << "stack_of_loop_indices.push_back(";
			//lhs->PrintExpressionCode(array_quest_init_area, array_quest_init_area); // note this is already stored in expr_code3
			code.array_quest_init_area << expr_code3.code_bef_expr.str() << expr_code3.code_expr.str();
			code.array_quest_init_area << ");\n";
		} else {
			ExpressionCompiledCode expr_code;
			for_bounds_stack[i]->PrintExpressionCode(expr_code);
			code.array_quest_init_area << expr_code.code_bef_expr.str() << expr_code.code_expr.str();
			print_err(compiler_sem_err
				, "for loop index condition is not a binary expression"
				, 0, __LINE__, __FILE__);
		}
	}
	if (qscript_debug::DEBUG_CompoundStatement) {
		code.array_quest_init_area << "// EXIT CompoundStatement::GenerateQuestionArrayInitLoopOpen\n";
	}
}

void CompoundStatement::GenerateQuestionArrayInitLoopClose(StatementCompiledCode &code)
{
	for(int32_t i = for_bounds_stack.size()-1; i< for_bounds_stack.size(); ++i){
		code.array_quest_init_area << "\tstack_of_loop_indices.pop_back();\n";
		code.array_quest_init_area << "}" << endl;
	}
}

void ForStatement::GenerateQuestionArrayInitLoopClose(StatementCompiledCode &code)
{
	if (qscript_debug::DEBUG_ForStatement) {
		code.array_quest_init_area << "// ENTER: " << __PRETTY_FUNCTION__ << endl;
	}
	vector<AbstractExpression*> & for_bounds_stack = forBody_->for_bounds_stack;
	for(int32_t i = for_bounds_stack.size()-1; i< for_bounds_stack.size(); ++i){
		code.array_quest_init_area << "\tstack_of_loop_indices.pop_back();\n";
		code.array_quest_init_area << "}" << endl;
	}
	if (qscript_debug::DEBUG_ForStatement) {
		code.array_quest_init_area << "// EXIT: " << __PRETTY_FUNCTION__ << endl;
	}
}

string PrintConsolidatedForLoopIndex(
	vector<AbstractExpression*> for_bounds_stack)
{
	ExpressionCompiledCode * expr_code_arr =
		new ExpressionCompiledCode[for_bounds_stack.size()];
	for(int32_t i = 0; i< for_bounds_stack.size(); ++i){
		BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(for_bounds_stack[i]);
		if (bin_expr_ptr){
			//AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
			AbstractExpression * lhs = bin_expr_ptr->leftOperand_;
			lhs->PrintExpressionCode(expr_code_arr[i]);
			if (i<for_bounds_stack.size()-1) {
				//string_stream_vec[i] << "*";
				expr_code_arr[i].code_expr << "*";
			}
		} else {
			for_bounds_stack[i]->PrintExpressionCode(expr_code_arr[i]);
			print_err(compiler_sem_err
				, "for loop index condition is not a binary expression"
				, 0, __LINE__, __FILE__);
		}
		for(int32_t j = i+1; j < for_bounds_stack.size(); j++){
			// quest_defns is passed twice
			// because we want the AbstractExpression to appear in the for
			// loop in the questions section of the code
			BinaryExpression * bin_expr_ptr2 = dynamic_cast<BinaryExpression*>(for_bounds_stack[j]);
			if (bin_expr_ptr2){
				AbstractExpression * rhs = bin_expr_ptr2->rightOperand_;
				rhs->PrintExpressionCode(expr_code_arr[i]);
				if (j<for_bounds_stack.size()-1) {
					expr_code_arr[i].code_expr << "*";
				}

			} else {
				for_bounds_stack[i]->PrintExpressionCode(expr_code_arr[i]);
				print_err(compiler_sem_err
					, "for loop index condition is not a binary expression. This error should have been caught at compile time"
					, 0, __LINE__, __FILE__);
			}
		}
	}
	ostringstream consolidated_for_loop_index;
	for(uint32_t i = 0; i < for_bounds_stack.size(); ++i) {
		consolidated_for_loop_index << expr_code_arr[i].code_bef_expr.str()
			<< expr_code_arr[i].code_expr.str();
		if (i <for_bounds_stack.size()-1){
			consolidated_for_loop_index << "+";
		}
	}
	delete[] expr_code_arr;
	return consolidated_for_loop_index.str();
}

void CompoundStatement::GenerateCode(StatementCompiledCode &code)
{
	code.quest_defns << "//CompoundStatement::GenerateCode()\n"
		<< "// Generating array declarations"
		<< ": flagGeneratedQuestionDefinitions_: " << flagGeneratedQuestionDefinitions_
		<< ", qscript_parser::for_loop_max_counter_stack.size(): "
		<< 	qscript_parser::for_loop_max_counter_stack.size()
		<< ", counterContainsQuestions_: " << counterContainsQuestions_
		<< ", flagIsAForBody_: " << flagIsAForBody_
		<< ", source lineNo_: " << lineNo_
		<< endl;

	// probably this block of code should go into
	// ForStatement along with flagGeneratedQuestionDefinitions_
	// will git branch and check this idea out
#if 0
	if (flagGeneratedQuestionDefinitions_ == false
	   //&& qscript_parser::for_loop_max_counter_stack.size()>0
	   && flagIsAForBody_
	   && counterContainsQuestions_) {
		if (qscript_debug::DEBUG_CompoundStatement) {
			code.quest_defns << "//CompoundStatement::GenerateCode()\n"
				<< "// Generating array declarations\n";
		}
		if (compoundBody_ && flagIsAForBody_ && !flagIsAIfBody_) {
			if (qscript_debug::DEBUG_CompoundStatement) {
				code.array_quest_init_area << "/* invoking GenerateQuestionArrayInitLoopOpen: "
					<< __LINE__ << ", " << __FILE__ << ", " << __PRETTY_FUNCTION__
					<< " */\n";
			}
			GenerateQuestionArrayInitLoopOpen(code);
			if (qscript_debug::DEBUG_CompoundStatement) {
				code.array_quest_init_area << "/* finished call to GenerateQuestionArrayInitLoopOpen: "
					<< __LINE__ << ", " << __FILE__ << ", " << __PRETTY_FUNCTION__
					<< " */\n";
			}
		}
		flagGeneratedQuestionDefinitions_ = true;
	}
#endif /* 0 */
	code.program_code << "{" << endl;
	/* Warning - duplicated code block - also present in
	 * CompoundStatement::Generate_ComputeFlatFileMap */
	//cout    << "ConsolidatedForLoopIndexStack_.size():"
	//	<< ConsolidatedForLoopIndexStack_.size()
	//	<< endl;
	if (flagIsAForBody_ && counterContainsQuestions_ && !flagIsAIfBody_) {
		code.program_code << "int32_t " << ConsolidatedForLoopIndexStack_.back()
			<< " = ";
		code.program_code << PrintConsolidatedForLoopIndex(for_bounds_stack);
		code.program_code << ";\n";
	}
	/* End of duplicated code block */
	if (compoundBody_) {
		compoundBody_->GetQuestionsInBlock(questionsInBlock_, this);
		code.program_code << "/* compound statement on line no: "
			<< lineNo_ << " questionsInBlock_, size:"
			<< questionsInBlock_.size() << " ";
		for (int i=0; i< questionsInBlock_.size(); ++i) {
			code.program_code << questionsInBlock_[i]->questionName_ << ", ";
		}
		code.program_code << " */\n";
		compoundBody_->GenerateCode(code);
	}
#if 0
	if (compoundBody_ && flagIsAForBody_ && !flagIsAIfBody_){
		GenerateQuestionArrayInitLoopClose(code);
	}
#endif /* 0 */
	if (flagIsAForBody_ && qscript_parser::page_nest_lev == 1) {
		code.program_code << "/* flagIsAForBody_ && page_nest_lev == 1  */"
			<< endl;
		code.program_code
			<< "if (vec_page_" << qscript_parser::globalActivePageName_
			<< "_ret_val.size() == "
			<< qscript_parser::globalActivePageSize_
			<< ") {"
			<< "last_question_visited =  "
			<<  "vec_page_" << qscript_parser::globalActivePageName_ << "_ret_val;"
			<< "return "
			<<  "vec_page_" << qscript_parser::globalActivePageName_ << "_ret_val"
			<< ";" << endl
			<< "}" << endl;
	}
	code.program_code << "}" << endl;
	if (next_)
		next_->GenerateCode(code);
}

void CompoundStatement::Generate_ComputeFlatFileMap(StatementCompiledCode &code)
{
	if (qscript_debug::DEBUG_CompoundStatement) {
		code.program_code << "// " << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
	}

	code.program_code << "{" << endl;
	/* Warning - duplicated code block - also present in
	 * CompoundStatement::GenerateCode */
	if (flagIsAForBody_ && counterContainsQuestions_ && !flagIsAIfBody_) {
		code.program_code << "int32_t " << ConsolidatedForLoopIndexStack_.back()
			<< " = ";
		code.program_code << PrintConsolidatedForLoopIndex(for_bounds_stack);
		code.program_code << ";\n";
	}
	/* End of duplicated code block */
	if (compoundBody_) {
		compoundBody_->Generate_ComputeFlatFileMap(code);
	}
	code.program_code << "}" << endl;
	if (qscript_debug::DEBUG_CompoundStatement) {
		code.program_code << "// EXIT " << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
	}
	if (next_) {
		next_->Generate_ComputeFlatFileMap(code);
	}
}


CompoundStatement::~CompoundStatement()
{
	using qscript_parser::mem_addr;
	debug_log_file << "deleting CompoundStatement" << endl;
	for (uint32_t i = 0; i< mem_addr.size(); ++i){
		if (this == mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr = 0;
			debug_log_file << "basic_count_ax_stmt::~basic_count_ax_stmt setting mem_addr: " << this << " = 0" << endl;
			break;
		}
	}
	if (scope_&&flagIsAFunctionBody_<0) {
		delete scope_;
		scope_ = 0;
	}
	if (compoundBody_ /*&& flagIsAFunctionBody_<0*/){
		delete compoundBody_;
		compoundBody_ = 0;
	}
}

using qscript_parser::question_list;
AbstractQuestion* find_in_question_list(string name)
{

	for(int32_t i = 0; i < question_list.size(); ++i){
		if (question_list[i]->questionName_ == name){
			return question_list[i];
		}
	}
	return 0;
}


ForStatement::ForStatement(DataType dtype, int32_t lline_number
			   , AbstractExpression * l_init
			   , AbstractExpression * l_test
			   , AbstractExpression* l_incr
			   , CompoundStatement * l_for_body)
	: AbstractStatement(dtype, lline_number)
	, initializationExpression_(l_init)
	, testExpression_(l_test), incrementExpression_(l_incr)
	, forBody_(l_for_body)
{
	if (initializationExpression_->type_ == VOID_TYPE
	    || testExpression_->type_ == VOID_TYPE
	    || incrementExpression_->type_ == VOID_TYPE){
		print_err(compiler_sem_err,
			"For ifCondition_ expression has Void or Error Type",
			qscript_parser::line_no, __LINE__, __FILE__);
		type_ = ERROR_TYPE;
	}
	// NxD - I have to correct here
	// testExpression_ should be a binary expression and
	// testExpression_->e_type should be <, >, <=, >=, == or !=

	if (forBody_->counterContainsQuestions_){
		// NxD - put strong checks here on loop initialization, condition and test expression
		DoExtraForLoopChecks();
	}
}

//! This is Called when a for statement contains
//! questions. We then apply stronger checks on the for loop
//! 1. The form of the for loop should be
//!	var = 0; var<const_expression; var = var+1
//! 2. The same variable should not be used in another for loop
//!	in the same nesting hierarchy
//! 3. The variable should be marked as readonly
void ForStatement::DoExtraForLoopChecks()
{
	CheckForIndexUsageConsistency();
	CheckNestedIndexUsage();
}

void ForStatement::CheckNestedIndexUsage()
{
	string init_var_name;
	BinaryExpression * init_expr
		= dynamic_cast<BinaryExpression*>(initializationExpression_);
	if (init_expr == 0){
		print_err(compiler_sem_err,
			"init_expr expr should be a binary expression ",
			qscript_parser::line_no, __LINE__, __FILE__);
	} else {
		Unary2Expression * init_var = dynamic_cast<Unary2Expression*> (
				init_expr->leftOperand_);
		if (init_var == 0){
			print_err(compiler_sem_err,
				"init_expr should be of the form var = 0",
				qscript_parser::line_no, __LINE__, __FILE__);
		} else if (init_var->exprOperatorType_ != oper_name){
			print_err(compiler_sem_err,
				"init_expr should be of the form var = 0",
				qscript_parser::line_no, __LINE__, __FILE__);
		} else  {
			init_var_name = init_var->symbolTableEntry_->name_;
		}
	}
	using qscript_parser::for_loop_max_counter_stack;

	//cout << "CheckNestedIndexUsage: on variable: " << init_var_name << ", "
	//	<< "for_loop_max_counter_stack.size(): "
	//	<< for_loop_max_counter_stack.size()  << endl;
	for(int32_t i = 0; i < for_loop_max_counter_stack.size()-1; ++i){
		BinaryExpression * prev_test_expr = dynamic_cast<BinaryExpression*>(for_loop_max_counter_stack[i]);
		if (prev_test_expr == 0){
			print_err(compiler_sem_err,
				"For loop containing questions should be of the form for(var = 0; var < const_expr; var = var+1)",
				qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			Unary2Expression * prev_init_var = dynamic_cast<Unary2Expression*> (
					prev_test_expr->leftOperand_);
			if (prev_init_var == 0){
				print_err(compiler_sem_err,
					"init_expr should be of the form var = 0",
					qscript_parser::line_no, __LINE__, __FILE__);
			} else if (prev_init_var->exprOperatorType_ != oper_name){
				print_err(compiler_sem_err,
					"init_expr should be of the form var = 0",
					qscript_parser::line_no, __LINE__, __FILE__);
			} else  {
				if (init_var_name  ==  prev_init_var->symbolTableEntry_->name_){
					string err_msg = "for loop variable " + init_var_name + " has been re-used at a deeper nest level";
					print_err(compiler_sem_err,
						err_msg.c_str(),
						qscript_parser::line_no, __LINE__, __FILE__);
				}
			}
		}
	}
}

void ForStatement::CheckForIndexUsageConsistency()
{

	if (initializationExpression_ == 0){
		print_err(compiler_sem_err,
			"initializationExpression_ should not be 0 when the for body contains a question"
		, qscript_parser::line_no, __LINE__, __FILE__);
	}
	if (testExpression_ == 0){
		print_err(compiler_sem_err,
			"testExpression_ should not be 0 when the for body contains a question"
		, qscript_parser::line_no, __LINE__, __FILE__);
	}
	if (incrementExpression_ == 0){
		print_err(compiler_sem_err,
			"incrementExpression_ should not be 0 when the for body contains a question"
		, qscript_parser::line_no, __LINE__, __FILE__);
	}
	if (initializationExpression_ == 0 || testExpression_ == 0
	   || incrementExpression_ == 0){
		return;
	}
	string init_var_name, test_var_name, inc_var_name;
	BinaryExpression * init_expr
		= dynamic_cast<BinaryExpression*>(initializationExpression_);
	if (init_expr == 0){
		print_err(compiler_sem_err,
			"init_expr expr should be a binary expression ",
			qscript_parser::line_no, __LINE__, __FILE__);
	} else {
		Unary2Expression * init_var = dynamic_cast<Unary2Expression*> (
				init_expr->leftOperand_);
		if (init_var == 0){
			print_err(compiler_sem_err,
				"init_expr should be of the form var = 0",
				qscript_parser::line_no, __LINE__, __FILE__);
		} else if (init_var->exprOperatorType_ != oper_name){
			print_err(compiler_sem_err,
				"init_expr should be of the form var = 0",
				qscript_parser::line_no, __LINE__, __FILE__);
		} else  {
			init_var_name = init_var->symbolTableEntry_->name_;
		}
		Unary2Expression * init_value = dynamic_cast<Unary2Expression*> (
				init_expr->rightOperand_);
		if (init_value == 0){
			print_err(compiler_sem_err,
				"init_expr should be of the form var = 0",
				qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			if (is_of_int_type(init_value->type_)){
				if (init_value->intSemanticValue_ == 0){
				} else {
					print_err(compiler_sem_err,
						"init_expr should be of the form var = 0",
						qscript_parser::line_no, __LINE__, __FILE__);
				}
			} else {
				print_err(compiler_sem_err,
					"init_expr should be of the form var = 0",
					qscript_parser::line_no, __LINE__, __FILE__);
			}

		}
	}

	BinaryExpression * inc_expr
		= dynamic_cast<BinaryExpression*>(incrementExpression_);
	if (inc_expr == 0){
		print_err(compiler_sem_err,
			"incrementExpression_ expr should be a binary expression ",
			qscript_parser::line_no, __LINE__, __FILE__);
	} else {
		Unary2Expression * inc_var = dynamic_cast<Unary2Expression*> (
				inc_expr->leftOperand_);
		if (inc_var == 0){
			print_err(compiler_sem_err,
				"init_expr should be of the form var = 0",
				qscript_parser::line_no, __LINE__, __FILE__);
		} else if (inc_var->exprOperatorType_ != oper_name){
			print_err(compiler_sem_err,
				"init_expr should be of the form var = 0",
				qscript_parser::line_no, __LINE__, __FILE__);
		} else  {
			inc_var_name = inc_var->symbolTableEntry_->name_;
		}
		BinaryExpression * rhs_inc_expr = dynamic_cast<BinaryExpression*>
				(inc_expr->rightOperand_);
		if (rhs_inc_expr == 0){
			print_err(compiler_sem_err,
				"inc_expr should be of the form var = var+1",
				qscript_parser::line_no, __LINE__, __FILE__);
		} else if (rhs_inc_expr->exprOperatorType_ != oper_plus) {
			print_err(compiler_sem_err,
				"inc_expr should be of the form var = var+1",
				qscript_parser::line_no, __LINE__, __FILE__);
		} else  {
			Unary2Expression * rhs_inc_expr_left_component =
				dynamic_cast<Unary2Expression*> (rhs_inc_expr->leftOperand_);
			if (rhs_inc_expr_left_component->exprOperatorType_ != oper_name){
				print_err(compiler_sem_err,
					"inc_expr should be of the form var = var+1",
					qscript_parser::line_no, __LINE__, __FILE__);
			}
			if (string(rhs_inc_expr_left_component->symbolTableEntry_->name_)
			   !=inc_var_name){
				print_err(compiler_sem_err,
					"inc_expr does not consistently use inc variable : should be of the form var = var+1",
					qscript_parser::line_no, __LINE__, __FILE__);
			}
			Unary2Expression * rhs_inc_expr_right_component =
				dynamic_cast<Unary2Expression*> (rhs_inc_expr->rightOperand_);
			if (rhs_inc_expr_right_component == 0){
				print_err(compiler_sem_err,
					"inc_expr should be of the form var = var+1",
					qscript_parser::line_no, __LINE__, __FILE__);
			} else if (rhs_inc_expr_right_component->exprOperatorType_ != oper_num){
				print_err(compiler_sem_err,
					"inc_expr should be of the form var = var+1",
					qscript_parser::line_no, __LINE__, __FILE__);
			} else if (rhs_inc_expr_right_component->intSemanticValue_ != 1){
				print_err(compiler_sem_err,
					"inc_expr should be of the form var = var+1",
					qscript_parser::line_no, __LINE__, __FILE__);
			} else {
				// valid inc expression
			}
		}

	}

	BinaryExpression * test_expr
		= dynamic_cast<BinaryExpression*>(testExpression_);
	if (test_expr == 0){
		print_err(compiler_sem_err,
			" testExpression_ expr should be a binary expression ",
			qscript_parser::line_no, __LINE__, __FILE__);
	} else if (!(test_expr->rightOperand_->IsIntegralExpression()
		    && test_expr->rightOperand_->IsConst())) {
		print_err(compiler_sem_err,
			"If the for loop contains questions, then the counter of the for loop should be an integer and a constant expression"
		, qscript_parser::line_no, __LINE__, __FILE__);
	} else if (test_expr->exprOperatorType_ != oper_lt){
			print_err(compiler_sem_err,
				"test_expr should be of the form var< const_integral_expression",
				qscript_parser::line_no, __LINE__, __FILE__);
	} else {
		Unary2Expression * test_var = dynamic_cast<Unary2Expression*> (
				test_expr->leftOperand_);
		if (test_var->exprOperatorType_ != oper_name){
			print_err(compiler_sem_err,
				"test_expr should be of the form var< const_integral_expression",
				qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			test_var_name = test_var->symbolTableEntry_->name_;
		}
	}
	if (!(init_var_name == test_var_name
	     && test_var_name == inc_var_name)){
		print_err(compiler_sem_err,
			"init_var_name should be same as test_var_name should be same as inc_var_name ",
			qscript_parser::line_no, __LINE__, __FILE__);
	}
}

void ForStatement::GenerateCode(StatementCompiledCode &code)
{
	if (qscript_debug::DEBUG_ForStatement) {
		code.array_quest_init_area << "/* " << __PRETTY_FUNCTION__ << ", " << __FILE__ << ", " << __LINE__
			<< "*/\n";
	}

	if (forBody_->counterContainsQuestions_) {
		if (qscript_debug::DEBUG_ForStatement) {
			code.quest_defns << "// " << __PRETTY_FUNCTION__
				<< "// Generating array declarations\n";
			code.array_quest_init_area << "// invoking GenerateQuestionArrayInitLoopOpen: "
					<< __LINE__ << ", " << __FILE__ << ", " << __PRETTY_FUNCTION__
					<< " \n";
		}
		GenerateQuestionArrayInitLoopOpen(code);
		if (qscript_debug::DEBUG_ForStatement) {
			code.array_quest_init_area << "// finished call to GenerateQuestionArrayInitLoopOpen: "
					<< __LINE__ << ", " << __FILE__ << ", " << __PRETTY_FUNCTION__
					<< " \n";
		}
	}

	if (qscript_parser::page_nest_lev > 0) {
		code.program_code << "/* page_nest_lev > 0 */" << endl;
	}

	ExpressionCompiledCode expr_code;
	expr_code.code_expr << "for (";
	initializationExpression_->PrintExpressionCode(expr_code);
	expr_code.code_expr <<   ";";
	testExpression_->PrintExpressionCode(expr_code);
	expr_code.code_expr << ";";
	incrementExpression_->PrintExpressionCode(expr_code);
	expr_code.code_expr <<  ")";

	code.program_code << expr_code.code_bef_expr.str();
	code.program_code << expr_code.code_expr.str();
	forBody_->GenerateCode(code);

	if (forBody_->counterContainsQuestions_) {
		GenerateQuestionArrayInitLoopClose(code);
	}

	if (next_)
		next_->GenerateCode(code);
}

void ForStatement::Generate_ComputeFlatFileMap(StatementCompiledCode &code)
{
	if (qscript_debug::DEBUG_ForStatement) {
		code.program_code << "// ENTER " << __PRETTY_FUNCTION__ << ", " << __FILE__ << ", " << __LINE__
			<< "\n";
	}

	if (forBody_->counterContainsQuestions_) {
		StatementCompiledCode temp_code;
		GenerateQuestionArrayInitLoopOpen(temp_code);
		code.program_code << temp_code.array_quest_init_area.str();
	}

	forBody_->Generate_ComputeFlatFileMap(code);
	if (qscript_debug::DEBUG_ForStatement) {
		code.program_code << "// EXIT " << __PRETTY_FUNCTION__ << ", " << __FILE__ << ", " << __LINE__
			<< "\n";
	}

	if (forBody_->counterContainsQuestions_) {
		StatementCompiledCode temp_code;
		GenerateQuestionArrayInitLoopClose(temp_code);
		code.program_code << temp_code.array_quest_init_area.str();
	}
	if (next_)
		next_->Generate_ComputeFlatFileMap(code);
}

void ForStatement::GenerateConsolidatedForLoopIndexes()
{
	//cout << "ENTER AbstractStatement::GenerateConsolidatedForLoopIndexes:" << endl;
	if (forBody_) {
		forBody_->GenerateConsolidatedForLoopIndexes();
	}
	if (next_) {
		next_->GenerateConsolidatedForLoopIndexes();
	}
	//cout << "EXIT AbstractStatement::GenerateConsolidatedForLoopIndexes:" << endl;
}

void ForStatement::GetQuestionsInBlock(vector<AbstractQuestion*> & question_list
				       , AbstractStatement * stop_at)
{
	//cerr << "ENTER: ForStatement::GetQuestionsInBlock" << endl;
	if (forBody_){
		forBody_->GetQuestionsInBlock(question_list, stop_at);
	}
	if (next_ && next_ != stop_at){
		next_->GetQuestionsInBlock(question_list, stop_at);
	}
	//cerr << "EXIT: ForStatement::GetQuestionsInBlock" << endl;
}


void ForStatement::GenerateQuestionArrayInitLoopOpen(StatementCompiledCode &code)
{
	if (qscript_debug::DEBUG_ForStatement) {
		code.array_quest_init_area << "// " << __PRETTY_FUNCTION__ << ", " << __FILE__ << ", " << __LINE__
			<< " source line no: " << lineNo_ <<  "\n";
	}
	if (forBody_->counterContainsQuestions_) {
		vector<AbstractExpression*> & for_bounds_stack = forBody_->for_bounds_stack;
		for(int32_t i = for_bounds_stack.size()-1; i< for_bounds_stack.size(); ++i){
			code.array_quest_init_area << "for (int32_t ";
			BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(for_bounds_stack[i]);
			if (bin_expr_ptr){
				//AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
				AbstractExpression * lhs = bin_expr_ptr->leftOperand_;
				ExpressionCompiledCode expr_code1;
				lhs->PrintExpressionCode(expr_code1);
				code.array_quest_init_area << expr_code1.code_bef_expr.str() << expr_code1.code_expr.str();
				code.array_quest_init_area << " = 0;";
				ExpressionCompiledCode expr_code2;
				for_bounds_stack[i]->PrintExpressionCode(expr_code2);
				code.array_quest_init_area << expr_code2.code_bef_expr.str() << expr_code2.code_expr.str();
				code.array_quest_init_area << "; ++";
				ExpressionCompiledCode expr_code3;
				lhs->PrintExpressionCode(expr_code3);
				code.array_quest_init_area << expr_code3.code_bef_expr.str() << expr_code3.code_expr.str();
				code.array_quest_init_area <<	") {" << endl;
				if (i == 0){
					code.array_quest_init_area << "vector<int32_t> stack_of_loop_indices;\n";
						//<< "(" <<  for_bounds_stack.size() << ");\n";
				}
				code.array_quest_init_area << "stack_of_loop_indices.push_back(";
				//lhs->PrintExpressionCode(array_quest_init_area, array_quest_init_area); // note this is already stored in expr_code3
				code.array_quest_init_area << expr_code3.code_bef_expr.str() << expr_code3.code_expr.str();
				code.array_quest_init_area << ");\n";
			} else {
				ExpressionCompiledCode expr_code;
				for_bounds_stack[i]->PrintExpressionCode(expr_code);
				code.array_quest_init_area << expr_code.code_bef_expr.str() << expr_code.code_expr.str();
				print_err(compiler_sem_err
					, "for loop index condition is not a binary expression"
					, 0, __LINE__, __FILE__);
			}
		}
	}
	if (qscript_debug::DEBUG_ForStatement) {
		code.array_quest_init_area << "// EXIT "  << __PRETTY_FUNCTION__ << " \n";
	}
}


ForStatement:: ~ForStatement()
{
	using qscript_parser::mem_addr;
	for (uint32_t i = 0; i< mem_addr.size(); ++i){
		if (this == mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr = 0;
			debug_log_file
				<< "ForStatement::~ForStatement setting mem_addr:"
				<< this << " = 0" << endl;
			break;
		}
	}
	debug_log_file << "deleting ForStatement" << endl;
	//if (next_) delete next_;
	delete initializationExpression_; initializationExpression_ = 0;
	delete testExpression_; testExpression_ = 0;
	delete incrementExpression_; incrementExpression_ = 0;
	delete forBody_; forBody_ = 0;
}


VariableList::VariableList(DataType type, char * name)
	: variableType_(type), variableName_(name)
	, arrayLength_(-1), prev_(0), next_(0)
{
	if (!( (type >= INT8_TYPE&& type <= DOUBLE_TYPE) ||
		(type >= INT8_REF_TYPE&& type <= DOUBLE_REF_TYPE))){
		stringstream s;
		s << "SEMANTIC error: only INT8_TYPE ... DOUBLE_TYPE is allowed in decl: "  << variableName_<< endl;
		print_err(compiler_sem_err, s.str() , qscript_parser::line_no, __LINE__, __FILE__);
		cerr << "NEED TO LINK  BACK TO ERROR: FIX ME" << endl;
	}
}

VariableList::~VariableList()
{
	debug_log_file << "deleting ~VariableList: variableName_:"
		<< variableName_ << endl;
	if (next_) { delete next_; next_ = 0; }
	debug_log_file << "end deleting ~VariableList " << endl;
}


void VariableList::print(FILE * edit_out)
{
	struct VariableList * vl_ptr = this;
	while(vl_ptr){
		if (vl_ptr->variableType_ >= INT8_TYPE
		   && vl_ptr->variableType_ <= DOUBLE_TYPE){
			fprintf(edit_out, "%s %s"
					, noun_list[vl_ptr->variableType_].sym
					, vl_ptr->variableName_.c_str());
		} else if (vl_ptr->variableType_ >= INT8_ARR_TYPE
			   && vl_ptr->variableType_ <= DOUBLE_ARR_TYPE){
			DataType tdt = DataType(INT8_TYPE
					+ vl_ptr->variableType_-INT8_ARR_TYPE);
			fprintf(edit_out
					, "%s %s[%d]/* vartype: %d */"
					, noun_list[tdt].sym
					, vl_ptr->variableName_.c_str()
					, arrayLength_
					, vl_ptr->variableType_);
		} else if (vl_ptr->variableType_ >= INT8_REF_TYPE
			   && vl_ptr->variableType_ <= DOUBLE_REF_TYPE){
			DataType tdt = DataType(INT8_TYPE
					+ vl_ptr->variableType_-INT8_REF_TYPE);
			fprintf(edit_out, "%s & %s"
					, noun_list[tdt].sym
					, vl_ptr->variableName_.c_str());
		} else {
			fprintf(edit_out, "INTERNAL ERROR:Unknown data type: file: %s, line: %d\n", __FILE__, __LINE__);
		}
		vl_ptr = vl_ptr->next_;
		if (vl_ptr) {
			fprintf(edit_out, ",");
		}
	}
}

VariableList::VariableList(DataType type, char * name, int32_t len)
	: variableType_(type), variableName_(name)
	, arrayLength_(len), prev_(0), next_(0)
{
	if (!is_of_arr_type(type)){
		cerr << "SEMANTIC error: only INT8_ARR_TYPE ... DOUBLE_ARR_TYPE array Types are allowed in decl: " << variableName_ << endl;
		cerr << "NEED TO LINK  BACK TO ERROR: FIX ME" << endl;
	}
	cout << "constructing VariableList: " << variableName_ << endl;
}


StubManipStatement::StubManipStatement(DataType dtype, int32_t lline_number
				       , named_range * l_named_range
				       , AbstractQuestion * l_question
				       , AbstractExpression * larr_index
	)
	: AbstractStatement(dtype, lline_number)
	  , questionName_(l_question->questionName_), namedStub_(l_named_range->name)
	  , namedRange_(l_named_range), lhs_(0), rhs_(l_question)
	  , xtccSet_(), arrIndex_(larr_index)
{ }

/*
StubManipStatement::StubManipStatement(DataType dtype, int32_t lline_number
				       , named_range * l_named_range
				       , AbstractQuestion * l_question
				       , AbstractExpression * larr_index)
	: AbstractStatement(dtype, lline_number)
	  , questionName_(l_question->questionName_), namedStub_(l_named_range->name)
	  , namedRange_(l_named_range), lhs_(0), rhs_(l_question)
	  , xtccSet_(), arrIndex_(larr_index)
{ }
*/
StubManipStatement::StubManipStatement(DataType dtype, int32_t lline_number
				       , AbstractQuestion * l_question_lhs
				       , AbstractQuestion * l_question_rhs
				       , AbstractExpression * larr_index
	)
	: AbstractStatement(dtype, lline_number)
	  , questionName_(l_question_rhs->questionName_), namedStub_()
	  , namedRange_(0), lhs_(l_question_lhs), rhs_(l_question_rhs)
	  , xtccSet_(), arrIndex_(0)
{ }


StubManipStatement::StubManipStatement(DataType dtype, int32_t lline_number
				       , named_range * l_named_range
				       , XtccSet & xs
	)
	: AbstractStatement(dtype, lline_number)
	  , questionName_(), namedStub_(l_named_range->name)
	  , namedRange_(l_named_range), lhs_(0), rhs_(0)
	  , xtccSet_(xs), arrIndex_(0)
{ }

StubManipStatement::StubManipStatement(DataType dtype, int32_t lline_number
				       , AbstractQuestion * l_question_lhs
				       , XtccSet & xs
	)
	: AbstractStatement(dtype, lline_number)
	  , questionName_(l_question_lhs->questionName_), namedStub_()
	  , namedRange_(0), lhs_(l_question_lhs), rhs_(0)
	  , xtccSet_(xs), arrIndex_(0)
{ }

// This constructor is deprecated and should be deleted at a later stage
#if 0
StubManipStatement::StubManipStatement(DataType dtype, int32_t lline_number
				       , string l_named_stub
				       , string l_question_name
	)
	: AbstractStatement(dtype, lline_number)
	, questionName_(l_question_name), namedStub_(l_named_stub)
	, xtccSet_()
{ }
#endif /* 0 */

StubManipStatement::StubManipStatement(DataType dtype, int32_t lline_number
				       , string l_named_stub)
	: AbstractStatement(dtype, lline_number)
	, questionName_(), namedStub_(l_named_stub)
	, namedRange_(0), lhs_(0), rhs_(0), xtccSet_(), arrIndex_(0)
{ }

void StubManipStatement::GenerateCode(StatementCompiledCode & code)
{
	using qscript_parser::question_list;
	code.program_code << "/*StubManipStatement::GenerateCode() BEGIN "
		<< questionName_ << ":" << namedStub_ << "*/"
		<< endl;
	code.program_code << "{" << endl;


	if (type_ == STUB_MANIP_DEL || type_ == STUB_MANIP_ADD){
		if (namedRange_ && rhs_) {
			code.program_code << "set<int32_t>::iterator set_iter = "
				<< questionName_;
			if (arrIndex_) {
				ExpressionCompiledCode expr_code1;
				arrIndex_->PrintExpressionCode(expr_code1);
				code.program_code << "_list.questionList[" << expr_code1.code_expr.str() << "]";
			}

			code.program_code << "->input_data.begin();" << endl;
			code.program_code << "for( ; set_iter!= "
				<< questionName_;
			if (arrIndex_) {
				ExpressionCompiledCode expr_code1;
				arrIndex_->PrintExpressionCode(expr_code1);
				code.program_code << "_list.questionList[" << expr_code1.code_expr.str() << "]";
			}

			code.program_code << "->input_data.end(); ++set_iter){" << endl;
			code.program_code << "\tfor (int32_t "
				<< qscript_parser::temp_name_generator.GetNewName();
			code.program_code
				<< " = 0; "
				<< qscript_parser::temp_name_generator.GetCurrentName()
				<< " < "
				<< namedStub_ << ".stubs.size(); ++"
				<< qscript_parser::temp_name_generator.GetCurrentName()
				<< ") {" << endl;
			code.program_code << "\t\tif (" << namedStub_
				<< ".stubs["
				<< qscript_parser::temp_name_generator.GetCurrentName()
				<< "].code == *set_iter) {" << endl;
			if (type_ == STUB_MANIP_DEL){
				code.program_code << "\t\t\t"
					<< namedStub_ << ".stubs["
					<< qscript_parser::temp_name_generator.GetCurrentName()
					<< "].mask = false; " << endl;
			} else if (type_ == STUB_MANIP_ADD) {
				code.program_code << "\t\t\t"
					<< namedStub_ << ".stubs["
					<< qscript_parser::temp_name_generator.GetCurrentName()
					<< "].mask = true; " << endl;
			}
			code.program_code << "\t\t}" << endl;
			code.program_code << "\t}" << endl;
			code.program_code << "}" << endl;
		} else if (lhs_ && rhs_) {
			code.program_code << "set<int32_t>::iterator set_iter = "
				<< rhs_->questionName_;

			if (arrIndex_) {
				ExpressionCompiledCode expr_code1;
				arrIndex_->PrintExpressionCode(expr_code1);
				code.program_code << "_list.questionList[" << expr_code1.code_expr.str() << "]";
			}
			code.program_code<< "->input_data.begin();" << endl;
			code.program_code << "for( ; set_iter!= "
				<< rhs_->questionName_;
			if (arrIndex_) {
				ExpressionCompiledCode expr_code1;
				arrIndex_->PrintExpressionCode(expr_code1);
				code.program_code << "_list.questionList[" << expr_code1.code_expr.str() << "]";
			}

			code.program_code << "->input_data.end(); ++set_iter){" << endl;
			code.program_code << lhs_->questionName_ << "->input_data.insert(*set_iter);\n";
			code.program_code << lhs_->questionName_ << "->isAnswered_ = true;\n";
			code.program_code << "\t}" << endl;
		} else if (lhs_ == 0 && rhs_ == 0 && namedRange_) {
			ExpressionCompiledCode expr_code;
			PrintTemporaryXtccSet(expr_code, &xtccSet_);
			code.program_code << expr_code.code_bef_expr.str() << expr_code.code_expr.str();
			code.program_code << "{\n";
			// ===================
			code.program_code << "for (set<int32_t>::iterator xtcc_set_iter1="
				<< qscript_parser::
					temp_set_name_generator.GetCurrentName()
				<< ".indiv.begin()"
				<< "; xtcc_set_iter1 !="
				<< qscript_parser::
					temp_set_name_generator.GetCurrentName()
				<< ".indiv.end(); ++xtcc_set_iter1) {\n"
				<< "\tfor (int32_t xtcc_i2=0; xtcc_i2<" << namedStub_ << ".stubs.size(); ++xtcc_i2) {\n"
				<< "\t\tif ("
				<< "*xtcc_set_iter1  == "
				<< namedStub_
				<< ".stubs[xtcc_i2].code) {\n";

			if (type_ == STUB_MANIP_DEL) {
				code.program_code
					<< "\t\t\t" << namedStub_ << ".stubs[xtcc_i2].mask = false;\n";
			} else if (type_ == STUB_MANIP_ADD) {
				code.program_code
					<< "\t\t\t" << namedStub_ << ".stubs[xtcc_i2].mask = true;\n";
			}

			code.program_code
				<< "\t\t}\n"
				<< "\t}\n"
				<< "}\n"

				<< "for(int32_t xtcc_i1 = 0; xtcc_i1 < "
				<< qscript_parser::
					temp_set_name_generator.GetCurrentName()
				<< ".range.size(); ++xtcc_i1) {\n"
				<< "\tfor(int32_t set_member = "
				<< qscript_parser::
					temp_set_name_generator.GetCurrentName()
				<< ".range[xtcc_i1].first; set_member <= "
				<< qscript_parser::
					temp_set_name_generator.GetCurrentName()
				<< ".range[xtcc_i1].second\n"
				<< "\t\t\t;++set_member) {\n"
				<< "\t\tfor (int32_t xtcc_i2=0; xtcc_i2<"
				<< namedStub_
				<< ".stubs.size(); ++xtcc_i2) {\n"
				<< "\t\t\tif (set_member == "
				<< namedStub_
				<< ".stubs[xtcc_i2].code) {\n"
				<< "\t\t\t\t";
			if (type_ == STUB_MANIP_DEL){
				code.program_code
					<< namedStub_ << ".stubs[xtcc_i2].mask = false;\n";
			} else if (type_ == STUB_MANIP_ADD) {
				code.program_code
					<< namedStub_ << ".stubs[xtcc_i2].mask = true;\n";
			}
			code.program_code
				<< "\t\t\t}\n"
				<< "\t\t}\n"
				<< "\t}\n"
				<< "}\n";
			code.program_code << "}\n";

			// ==================
		} else if (lhs_ && rhs_ == 0 && namedRange_ == 0) {
			//stringstream s;
			//s << "/* not yet programmed : "
			//	<< __FILE__ << ", " << __LINE__ << ", "
			//	<< __PRETTY_FUNCTION__ << " */" << endl;
			//s << "This should cause an ERROR in the generated code: "
			//	<< __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
			//code.program_code << s.str();
			if (xtccSet_ . isEmpty() ) {
				stringstream s;
				s << " In-correct setup of StubManipStatement. xtccSet_ should not be empty. This error should have been caught in the parsing stage.";
				print_err(compiler_internal_error, s.str() , qscript_parser::line_no, __LINE__, __FILE__);
			} else {
				cout << "xtccSet_ is non-empty as expected\n";
				stringstream mesg;
				mesg << "This code has to be revisited. first of all we are not allowing SETADD/SETDEL on array questions. Secondly there is no check on mutex. ";
				LOG_MAINTAINER_MESSAGE(mesg.str());
				for (set<int32_t>::iterator it=xtccSet_.indiv.begin();
						it != xtccSet_.indiv.end();
						++it) {
					if (lhs_->IsValid(*it)) {
						if (type_ == STUB_MANIP_DEL) {
							code.program_code << lhs_->questionName_ << "->input_data.erase("
								<< *it << ");\n";
						} else if (type_ == STUB_MANIP_ADD) {
							code.program_code << lhs_->questionName_ << "->input_data.insert("
								<< *it << ");\n";
						}
						//	lhs->input_data.insert(*it);
					} else {
						stringstream err_msg;
						err_msg << "invalid element: " << *it << " in set_del/set_add. ";
						print_err(compiler_internal_error, err_msg.str() , qscript_parser::line_no, __LINE__, __FILE__);
					}
				}
				for (int32_t xtcc_i1 = 0; xtcc_i1 < xtccSet_.range.size(); ++xtcc_i1) {
					for (int32_t set_member = xtccSet_.range[xtcc_i1].first; set_member <= xtccSet_.range[xtcc_i1].second;
							++set_member) {
						if (type_ == STUB_MANIP_DEL) {
							if (lhs_->IsValid(set_member)) {
								//lhs->input_data.insert(set_member);
								code.program_code << lhs_->questionName_ << "->input_data.insert("
									<< set_member << ");\n";
							} else {
								stringstream err_msg;
								err_msg << "invalid element: " << set_member << " in set_del. ";
								print_err(compiler_internal_error, err_msg.str() , qscript_parser::line_no, __LINE__, __FILE__);
							}
						} else if (type_ == STUB_MANIP_ADD) {
							if (lhs_->IsValid(set_member)) {
								code.program_code << lhs_->questionName_ << "->input_data.erase("
									<< set_member << ");\n";
							} else {
								stringstream err_msg;
								err_msg << "invalid element: " << set_member << " in set_add. ";
								print_err(compiler_internal_error, err_msg.str() , qscript_parser::line_no, __LINE__, __FILE__);
							}
						}

					}
				}
			}
			//print_err(compiler_internal_error, s.str() , qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			stringstream s;
			s << " incorrect setup of StubManipStatement: ";
			print_err(compiler_internal_error, s.str() , qscript_parser::line_no, __LINE__, __FILE__);
		}
	} else if (type_ == STUB_MANIP_UNSET_ALL || type_ == STUB_MANIP_SET_ALL) {
		code.program_code << "for(int32_t "
			<< qscript_parser::temp_name_generator.GetNewName();
		code.program_code
			<< " = 0; "
			<< qscript_parser::temp_name_generator.GetCurrentName()
			<< " < "
			<< namedStub_ << ".stubs.size(); ++"
			<< qscript_parser::temp_name_generator.GetCurrentName()
			<< "){" << endl;
		if (type_ == STUB_MANIP_UNSET_ALL) {
			code.program_code << namedStub_
				<< ".stubs["
				<< qscript_parser::temp_name_generator.GetCurrentName()
				<< "].mask = false; " << endl;
		} else if (type_ == STUB_MANIP_SET_ALL) {
			code.program_code << namedStub_
				<< ".stubs["
				<< qscript_parser::temp_name_generator.GetCurrentName()
				<< "].mask = true; " << endl;
		}
		code.program_code << "}" << endl;
	} else {
		stringstream err_text;
		err_text << "AbstractQuestion: " << questionName_
			<< " , dataype of StubManipStatement statement is not as expected"
			<< endl;
		print_err(compiler_sem_err, err_text.str()
				, lineNo_, __LINE__, __FILE__);
		code.program_code << "ERROR: StubManipStatement: this should fail compilation" << endl;
	}

	code.program_code << endl;

	code.program_code << "}" << endl;
	code.program_code << "/*StubManipStatement::GenerateCode() END "
		<< questionName_ << ":" << namedStub_ << "*/"
		<< endl;

	if (next_)
		next_->GenerateCode(code);
}

StubManipStatement::~StubManipStatement()
{ }



FunctionParameter::FunctionParameter(DataType type, char * name)
	: var_type(type), var_name(name), arr_len(-1), prev_(NULL), next_(NULL)
{
	if (!( (type >= INT8_TYPE&& type <= DOUBLE_TYPE) ||
		(type >= INT8_REF_TYPE&& type <= DOUBLE_REF_TYPE))){
		stringstream s;
		s << "SEMANTIC error: only INT8_TYPE ... DOUBLE_TYPE is allowed in decl: "  << var_name<< endl;
		print_err(/*Util:: */compiler_sem_err, s.str() , qscript_parser::line_no, __LINE__, __FILE__);
		cerr << "NEED TO LINK  BACK TO ERROR: FIX ME" << endl;
	}
	//cout << "constructing FunctionParameter: " << var_name << endl;
}

FunctionParameter::~FunctionParameter()
{
	debug_log_file << "deleting ~FunctionParameter: var_name:" << var_name << endl;
	if (next_) { delete next_; next_ = 0; }
	debug_log_file << "end deleting ~FunctionParameter " << endl;
}


void FunctionParameter::print(ostringstream & program_code)
{
	program_code << " /* FunctionParameter::print */ " << endl;
	cerr << " /* FunctionParameter::print */ " << endl;
	struct FunctionParameter * vl_ptr = this;
	while(vl_ptr){
		if (vl_ptr->var_type >= INT8_TYPE && vl_ptr->var_type <= DOUBLE_TYPE){
			//fprintf(edit_out, "%s %s", noun_list[vl_ptr->var_type].sym,vl_ptr->var_name.c_str());
			program_code << " /* FunctionParameter :: print : NOUN */ ";
			program_code << noun_list[vl_ptr->var_type].sym << " " << vl_ptr->var_name.c_str();
		} else if (vl_ptr->var_type >= INT8_ARR_TYPE&&vl_ptr->var_type <= DOUBLE_ARR_TYPE){
			DataType tdt = DataType(INT8_TYPE + vl_ptr->var_type-INT8_ARR_TYPE);
			//fprintf(edit_out, "%s %s[%d]", noun_list[tdt].sym, vl_ptr->var_name.c_str(), arr_len, vl_ptr->var_type);
			program_code << " /* FunctionParameter :: print : ARRAY TYPE */ ";
			program_code <<  noun_list[tdt].sym <<  " "  <<  vl_ptr->var_name.c_str() << "[" <<  arr_len << "]" <<  vl_ptr->var_type;
		} else if (vl_ptr->var_type >= INT8_REF_TYPE&&vl_ptr->var_type <= DOUBLE_REF_TYPE){
			DataType tdt = DataType(INT8_TYPE + vl_ptr->var_type-INT8_REF_TYPE);
			//fprintf(edit_out, "%s & %s", noun_list[tdt].sym, vl_ptr->var_name.c_str());
			program_code << " /* FunctionParameter :: print : REF TYPE */ ";
			program_code << noun_list[tdt].sym  << " & " << vl_ptr->var_name.c_str();
		} else {
			//fprintf(edit_out, "INTERNAL ERROR:Unknown data type: file: %s, line: %d\n", __FILE__, __LINE__);

			stringstream s;
			s << "INTERNAL ERROR Unknown data type : ";
			print_err(compiler_code_generation_error, s.str()
					, qscript_parser::line_no, __LINE__, __FILE__);
		}
		vl_ptr = vl_ptr->next_;
		if (vl_ptr) {
			//fprintf(edit_out, ",");
			program_code << ", ";
		}
	}
}

FunctionParameter::FunctionParameter(DataType type, char * name, int32_t len): var_type(type), var_name(name), arr_len(len), prev_(NULL), next_(NULL)
{
	if (!is_of_arr_type(type)){
		cerr << "SEMANTIC error: only INT8_ARR_TYPE ... DOUBLE_ARR_TYPE array Types are allowed in decl: " << var_name << endl;
		cerr << "NEED TO LINK  BACK TO ERROR: FIX ME" << endl;
	}
	cout << "constructing FunctionParameter: " << var_name << endl;
}

FunctionDeclarationStatement::FunctionDeclarationStatement(
	DataType dtype, int32_t lline_number, char * & name
	, FunctionParameter* & v_list, DataType returnType_)
	: AbstractStatement(dtype, lline_number), funcInfo_(0)
{
	//cout << "load_func_into_symbol_table : " << "name: " << name << endl;
	if (active_scope->SymbolTable.find(name) == active_scope->SymbolTable.end() ){
		//cout << "got func_decl" << endl;
		DataType myreturn_type = returnType_;
		FunctionInformation* fi = new FunctionInformation(name
				, v_list, myreturn_type);
		func_info_table.push_back(fi);
		type_ = FUNC_TYPE;
		SymbolTableEntry* se = new SymbolTableEntry(name, FUNC_TYPE);
				/*
		if (! se) {
			cerr << "memory allocation error: I will eventually crash :-("
				<< endl;
		}
		*/
		se->name_ = name;
		string s(name);
		active_scope->SymbolTable[s] = se;
		se->type_ = FUNC_TYPE;
		funcInfo_ = fi;
		//free(name);
	} else {
		stringstream s;
		s << "Function  Name : "
			<< name << " already present in symbol table." << endl;
		print_err(compiler_sem_err, s.str()
				, qscript_parser::line_no, __LINE__, __FILE__);
		type_ = ERROR_TYPE;
		free(name);
	}
}

void FunctionDeclarationStatement::GenerateCode(StatementCompiledCode &code)
{
		funcInfo_->print(code.program_code);
		if (next_) next_->GenerateCode(code);
}

FunctionDeclarationStatement::~FunctionDeclarationStatement()
{
	for (uint32_t i = 0; i< mem_addr.size(); ++i){
		if (this == mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr = 0;
			debug_log_file
				<< "FunctionDeclarationStatement::~FunctionDeclarationStatement setting mem_addr: "
				<< this<< " = 0" << endl;
			break;
		}
	}
	debug_log_file << "deleting FunctionDeclarationStatement: name: "
		<< funcInfo_->functionName_ << endl;
	if (funcInfo_) { delete funcInfo_; funcInfo_ = 0; }
}

FunctionStatement:: FunctionStatement(DataType dtype, int32_t lline_number
		, Scope * &scope_, FunctionParameter * & v_list
		, AbstractStatement* & lfunc_body
		, string func_name, DataType lreturn_type
		)
	: AbstractStatement(dtype, lline_number), funcInfo_(0)
	  , functionBody_(lfunc_body), returnType_(lreturn_type)
{
	int32_t index = search_for_func(func_name);
	if (index == -1){
		ostringstream err_msg;
		err_msg << "function defn without decl: "
			<< func_name << " lline_number: "
			<< lline_number << endl;
		print_err(compiler_sem_err, err_msg.str() , qscript_parser::line_no, __LINE__, __FILE__);
		type_ = ERROR_TYPE;
	} else if (/*Util::*/check_func_decl_with_func_defn(v_list, index, func_name)){
		if (returnType_ == func_info_table[index]->returnType_){
			type_ = FUNC_DEFN;
			funcInfo_ = func_info_table[index];
		} else {
			stringstream s;
			s << "func defn, decl parameter return_types did not match: function name: " << func_name;
			print_err(/*Util::*/compiler_sem_err, s.str(), qscript_parser::line_no
					, __LINE__, __FILE__);
			type_ = ERROR_TYPE;
		}
	} else {
		stringstream s;
		s << "func defn, decl parameter return_types did not match: function name: " << func_name;
		print_err(/*Util::*/compiler_sem_err, s.str(), qscript_parser::line_no
				, __LINE__, __FILE__);
		type_ = ERROR_TYPE;
	}
}

void FunctionStatement::GenerateCode(StatementCompiledCode & code)
{
	code.program_code << "//FunctionStatement::GenerateCode()" << endl;
	if (funcInfo_->returnType_ >= VOID_TYPE
	   && funcInfo_->returnType_ <= DOUBLE_TYPE){
		code.program_code << noun_list[funcInfo_->returnType_].sym;
	} else {
		ostringstream err_msg;
		err_msg << " Unxpected return type for function  ";


		print_err(compiler_code_generation_error, err_msg.str().c_str(),
				qscript_parser::line_no, __LINE__, __FILE__);
	}

	if (funcInfo_->functionName_ == string("printf")){
		code.program_code << "/* FunctionStatement::GenerateCode*/ fprintf(qscript_stdout,";
	} else {
		code.program_code << funcInfo_->functionName_.c_str() << "(";
	}
	code.program_code << " /* FunctionStatement::GenerateCode */" << endl;
	FunctionParameter* v_ptr = funcInfo_->parameterList_;
	v_ptr->print(code.program_code);
	code.program_code << ")";
	if (functionBody_) functionBody_->GenerateCode(code);
	if (next_) next_->GenerateCode(code);
}


FunctionStatement::~FunctionStatement()
{
	for (uint32_t i = 0; i< mem_addr.size(); ++i){
		if (this == mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr = 0;
			debug_log_file << "FunctionStatement::~FunctionStatement: setting mem_addr = 0" << endl;
			break;
		}
	}
	debug_log_file << "deleting FunctionStatement" << endl;
	if (functionBody_) {
		delete functionBody_;
		functionBody_ = 0;
	}
}

FunctionInformation::FunctionInformation(string name, struct FunctionParameter* elist
		, DataType myreturn_type)
	: functionName_(name), parameterList_(elist), returnType_(myreturn_type)
	  , functionBody_(0), functionScope_(0)
{
	functionScope_ = new Scope();
	struct FunctionParameter* decl_list = elist;
	while(decl_list){
		struct SymbolTableEntry* se = new struct SymbolTableEntry(strdup(decl_list->var_name.c_str()),
				decl_list->var_type);
		//se->name_ = strdup(decl_list->var_name.c_str());
		//se->type_ = decl_list->var_type;
		functionScope_->SymbolTable[decl_list->var_name] = se;
		decl_list = decl_list->next_;
	}
}

void FunctionInformation::print(ostringstream & program_code)
{
	if (returnType_  >= VOID_TYPE && returnType_  <= DOUBLE_TYPE){
		//fprintf(fptr, "%s ", noun_list[returnType_].sym);
		program_code << noun_list[returnType_].sym;
	} else {
		//fprintf(fptr, "Unexpected return type for function\n");
		ostringstream s;
		s << "Unexpected return type for function\n";
		print_err(/*Util:: */compiler_sem_err, s.str() , qscript_parser::line_no, __LINE__, __FILE__);
	}
	//fprintf(fptr, "%s(", functionName_.c_str());
	program_code << functionName_.c_str() << "(";
	if (parameterList_) parameterList_->print(program_code);
	//fprintf(fptr, ");\n");
	program_code << ");\n";
}

FunctionInformation::~FunctionInformation()
{
	if (parameterList_) { delete parameterList_; parameterList_ = 0; }
	//if (functionBody_) { delete functionBody_; functionBody_ = 0; }
	// functionScope_ was created by in the constructor - so we delete it
	if (functionScope_) { delete functionScope_; functionScope_ = 0; }
}

ErrorStatement::ErrorStatement( int lline_number)
	: AbstractStatement(ERROR_TYPE, lline_number)
{}


void ErrorStatement::GenerateCode(StatementCompiledCode & code)
{
	code.program_code << "error" << endl;
	cerr << __PRETTY_FUNCTION__ << " should never be called\n";
}

GotoStatement::GotoStatement(DataType l_type, int32_t l_line_number
			     , string l_gotoLabel)
	: AbstractStatement(l_type, l_line_number)
	, gotoLabel_(l_gotoLabel)
{
	if (find_in_question_list(gotoLabel_)){
		// I think this check ensures that we never do a forward jump
		// I need to verify this
	} else {
		print_err(compiler_sem_err,
			  "goto target must be a question name",
			  qscript_parser::line_no, __LINE__, __FILE__);
	}
}

void GotoStatement::GenerateCode(StatementCompiledCode & code)
{
	code.program_code << "/*GotoStatement::GenerateCode() */ "
		<< endl;
	code.program_code << "jumpToQuestion = \"" << gotoLabel_ << "\";\n\
			goto start_of_questions;\n";
	if (next_) {
		code.program_code << "/* EXIT GotoStatement::GenerateCode */" << endl;

		next_->GenerateCode(code);
	}
}

ClearStatement::ClearStatement(DataType l_type, int32_t l_line_number,
			const vector <Unary2Expression *> & expr_vec, string err_msg)
	: AbstractStatement(l_type, l_line_number),
	  questionExprVec_ (expr_vec), errorMessage_ (err_msg)
{
	VerifyForClearStatement (questionExprVec_);
}

vector<bool> ClearStatement::VerifyForClearStatement (const vector<Unary2Expression*> expr_vec)
{
	vector <bool> res_vec;
	for (int i = 0; i < expr_vec.size(); ++i) {
		//AbstractExpression * e = expr_vec[i];
		//Unary2Expression * u2e = dynamic_cast <Unary2Expression*> (e);
		Unary2Expression * u2e =  expr_vec[i];
		bool result = true;
		// if (u2e == 0) {
		// 	stringstream err;
		// 	err << " Grammar should not allow any other types than NAME or NAME [ expr ] for clear statement";
		// 	print_err (compiler_internal_error, err.str() , qscript_parser::line_no, __LINE__, __FILE__);
		// 	result = false;
		// } else
		if (u2e -> exprOperatorType_ == oper_name) {
			if (u2e->symbolTableEntry_->type_ != QUESTION_TYPE) {
				stringstream err;
				err << " NAME in clear statement should be a question";
				print_err (compiler_sem_err, err.str() , qscript_parser::line_no, __LINE__, __FILE__);
				result = false;
			}
		} else if (u2e -> exprOperatorType_ == oper_arrderef) {
			if (u2e->symbolTableEntry_->type_ != QUESTION_ARR_TYPE) {
				stringstream err;
				err << " NAME in clear statement should be a question inside a for loop (array question)";
				print_err (compiler_sem_err, err.str() , qscript_parser::line_no, __LINE__, __FILE__);
				result = false;
			}
		}
		res_vec.push_back (result);
	}
	return res_vec;
}



void ClearStatement::GenerateCode(StatementCompiledCode & code)
{
	code.program_code << " /*  Clear statement code */ " 
		<< endl;
	for (int i = 0; i < questionExprVec_.size(); ++i) {
		//ExpressionCompiledCode code1;
		//questionExprVec_[i]->PrintExpressionCode(code1);
		//code.program_code << code1.code_bef_expr.str()
		//		   << code1.code_expr.str();
		//code.program_code << "->isAnswered_ = false;\n";
		Unary2Expression * u2e =  questionExprVec_[i];
		if (u2e -> exprOperatorType_ == oper_name && u2e -> type_ == QUESTION_TYPE) {
			AbstractQuestion * q = u2e->symbolTableEntry_->question_;
			code.program_code << q->questionName_ << "->isAnswered_ = false;\n";
		} else if (u2e -> exprOperatorType_ == oper_arrderef /* && u2e -> type_ == QUESTION_ARR_TYPE */) {
			AbstractQuestion * q = u2e->symbolTableEntry_->question_;
			code.program_code << q->questionName_ << "_list.questionList[";
			ExpressionCompiledCode code1;
			u2e->operand_->PrintExpressionCode(code1);
			code.program_code << code1.code_bef_expr.str()
				<< code1.code_expr.str()
				<< "]->isAnswered_ = false;\n";
		} else {
			code.program_code << "Internal compiler error - this should trigger a compilation failure, "
				<< __LINE__ << ", " << __FILE__ << ", " << __PRETTY_FUNCTION__
				<< endl;
		}
	}

	code.program_code << "stopAtNextQuestion = false;\n"
		<< "error_messages_vec.push_back(\"" << errorMessage_ << "\");\n"
		<< "goto start_of_questions;\n"
		<< endl;

	if (next_) {
		next_->GenerateCode(code);
	}
}


ColumnStatement::ColumnStatement(DataType l_type, int32_t l_line_number,
				AbstractExpression * expr)
	: AbstractStatement(l_type, l_line_number),
	  columnExpression_(expr)
{
	RunColumnExpressionChecks(this);
}

bool RunColumnExpressionChecks(ColumnStatement * col_stmt)
{
	// we want to allow expressions which contain lvalues which are for
	// loop indices
	// but for now just allow plain numbers

	Unary2Expression * un2_expr = dynamic_cast<Unary2Expression*> (col_stmt->columnExpression_);
	if (un2_expr == 0) {
		stringstream s;
		s << " Currently only numbers are allowed as column expressions";
		print_err(compiler_sem_err, s.str(), qscript_parser::line_no, __LINE__, __FILE__);
		return false;
	} else {
		if (! (un2_expr->exprOperatorType_== oper_num)) {
			stringstream s;
			s << " Currently only numbers are allowed as column expressions";
			print_err(compiler_sem_err, s.str(), qscript_parser::line_no, __LINE__, __FILE__);
			return false;
		}
		return true;
		// else all ok
	}

}

bool RunNewCardExpressionChecks(NewCardStatement * newcard_stmt)
{
	// we want to allow expressions which contain lvalues which are for
	// loop indices
	// but for now just allow plain numbers

	Unary2Expression * un2_expr = dynamic_cast<Unary2Expression*> (newcard_stmt->cardExpression_);
	if (un2_expr == 0) {
		stringstream s;
		s << " Currently only numbers are allowed as column expressions";
		print_err(compiler_sem_err, s.str(), qscript_parser::line_no, __LINE__, __FILE__);
		return false;
	} else {
		if (! (un2_expr->exprOperatorType_== oper_num)) {
			stringstream s;
			s << " Currently only numbers are allowed as column expressions";
			print_err(compiler_sem_err, s.str(), qscript_parser::line_no, __LINE__, __FILE__);
			return false;
		}
		return true;
		// else all ok
	}

}

void ColumnStatement::Generate_ComputeFlatFileMap(StatementCompiledCode & code)
{
	ExpressionCompiledCode expr_code;
	columnExpression_->PrintExpressionCode(expr_code);
	code.program_code << "current_map_pos = ";
	code.program_code << expr_code.code_bef_expr.str() << expr_code.code_expr.str()
		<< ";\n";
	if (next_)
		next_->Generate_ComputeFlatFileMap(code);
}

void ColumnStatement::GenerateCode(StatementCompiledCode & code)
{
	if (next_) {
		next_->GenerateCode(code);
	}
}


NewCardStatement::NewCardStatement(DataType l_type, int32_t l_line_number,
				AbstractExpression * expr)
	: AbstractStatement(l_type, l_line_number),
	  cardExpression_(expr)
{
	RunNewCardExpressionChecks(this);
}


void NewCardStatement::Generate_ComputeFlatFileMap(StatementCompiledCode & code)
{
	ExpressionCompiledCode expr_code;
	cardExpression_->PrintExpressionCode(expr_code);
	string tmp_name = qscript_parser::temp_name_generator.GetNewName();
	code.program_code << "for (int32_t " <<  tmp_name << " = 0; " << tmp_name << "<"
		<< expr_code.code_expr.str() << " ; ++ " << tmp_name << " ) {\n"
		<< "qtm_data_file.fileXcha_.NextCard();\n"
		<< "}\n";
	//code.program_code << expr_code.code_bef_expr.str() << expr_code.code_expr.str()
	//	<< ";\n";
	if (next_)
		next_->Generate_ComputeFlatFileMap(code);
}

void NewCardStatement::GenerateCode(StatementCompiledCode & code)
{
	if (next_) {
		next_->GenerateCode(code);
	}
}

PageStatement::PageStatement (DataType dtype, int32_t l_line_no,
		string l_page_name, CompoundStatement * l_page_body,
		int l_page_size)
	: AbstractStatement(dtype, l_line_no),
	  pageName_ (l_page_name), pageBody_ (l_page_body),
	  pageSize_ (l_page_size)
{
	cout
		<< "pageName_: " << pageName_
		<< ", pageSize_: " << pageSize_
		<< endl;
}


void PageStatement::GenerateCode(StatementCompiledCode & code)
{
	qscript_parser::globalActivePageName_ = pageName_;
	qscript_parser::globalActivePageSize_ = pageSize_;
	code.program_code << "/* ENTER " << __PRETTY_FUNCTION__ << " */" << std::endl;
	code.program_code << "vector <AbstractRuntimeQuestion*> vec_page_"
		<< pageName_ << "_ret_val;" << std::endl;
	qscript_parser::page_nest_lev = 1;
	qscript_parser::flag_first_question_in_page = true;
	pageBody_->GenerateCode(code);

	code.program_code
		<< "if (vec_page_" << pageName_ << "_ret_val.size() > 0) {"
		<< " last_question_visited =  vec_page_" << pageName_ << "_ret_val;"
		<< std::endl
		<< " return vec_page_" << pageName_ << "_ret_val;"
		<< std::endl
		<< "}" << endl
		;


	qscript_parser::page_nest_lev = 0;
	code.program_code << "/* EXIT " << __PRETTY_FUNCTION__ << " */" << std::endl;
	if (next_) {
		next_->GenerateCode (code);
	}
}

void PageStatement::GenerateConsolidatedForLoopIndexes()
{
	pageBody_->GenerateConsolidatedForLoopIndexes();
	if (next_) {
		next_->GenerateConsolidatedForLoopIndexes();
	}
}

