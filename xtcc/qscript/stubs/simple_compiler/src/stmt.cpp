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
	cerr << "ENTER AbstractStatement::GetQuestionsInBlock: ";
	//cerr << human_readable_type(type_) << endl;
	if (next_ && next_ != stop_at){
		next_->GetQuestionsInBlock(question_list, stop_at);
	}
	cerr << "Exit AbstractStatement::GetQuestionsInBlock\n";
}

void AbstractStatement::GenerateConsolidatedForLoopIndexes()
{
	//cout << "ENTER AbstractStatement::GenerateConsolidatedForLoopIndexes:" << endl;
	if (next_){
		next_->GenerateConsolidatedForLoopIndexes();
	}
	//cout << "EXIT AbstractStatement::GenerateConsolidatedForLoopIndexes:" << endl;
}

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
	static vector<IfStatementStackElement*> ifStatementStack;
	static int32_t if_nest_level =0;
	bool if_nest_level_was_increased = false;
	//++if_nest_level;
	if (ifStatementStack.size()>0){
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
	expr_code.code_expr << "if (";
	ifCondition_->PrintExpressionCode(expr_code);
	expr_code.code_expr << ") {";
	code.program_code << expr_code.code_bef_expr.str()
		<< expr_code.code_expr.str();
	vector<string> question_list_else_body;
	code.program_code << "// ifStatementStack.size(): "
		<< ifStatementStack.size() << endl;
	if (ifStatementStack.size() > 0){
		for(int32_t i = 0; i < ifStatementStack.size(); ++i){
			if (ifStatementStack[i]->nestLevel_ == if_nest_level){
				ifStatementStack[i]->ifStatementPtr_
					->GetQuestionNames
					(question_list_else_body, this);
				break;
			}
		}
	}
	if (elseBody_)
		elseBody_->GetQuestionNames(question_list_else_body, 0);
	for(int32_t i = 0; i < question_list_else_body.size(); ++i){
		code.program_code <<  question_list_else_body[i]
			<< "->isAnswered_ = false;"
			<< endl;
	}
	ifBody_->GenerateCode(code);
	code.program_code << " }" << endl;

	if (elseBody_){
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
		vector<string> question_list_if_body;

		for(int32_t i = 0; i < ifStatementStack.size(); ++i){
			if (ifStatementStack[i]->nestLevel_ == if_nest_level){
				ifStatementStack[i]->ifStatementPtr_
					->GetQuestionNames
					(question_list_if_body, this);
				break;
			}
		}
		ifBody_->GetQuestionNames(question_list_if_body, 0);
		code.program_code << "// end of ifBody_->GetQuestionNames \n";
		if (elseIfStatement){
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

		if (elseIfStatement){
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

	code.program_code << " /* finished generating code IfStatement */ " << endl;
	if (next_)
		next_->GenerateCode(code);
	//cerr << "EXIT: IfStatement::GenerateCode()" << endl;
}

void IfStatement::GenerateConsolidatedForLoopIndexes()
{
	//cout << "ENTER IfStatement::GenerateConsolidatedForLoopIndexes:" << endl;
	if (ifBody_){
		ifBody_->GenerateConsolidatedForLoopIndexes();
	}
	if (elseBody_){
		elseBody_->GenerateConsolidatedForLoopIndexes();
	}
	if (next_){
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
{
	compoundStatementNumber_ = CompoundStatement::counter_++;
}

void CompoundStatement::GenerateConsolidatedForLoopIndexes()
{
	//cout << "ENTER CompoundStatement::GenerateConsolidatedForLoopIndexes:" << endl;
	if (flagIsAForBody_ && counterContainsQuestions_){
		ostringstream consolidated_loop_counter;
		consolidated_loop_counter << "consolidated_for_loop_index_" << compoundStatementNumber_;
		//cout << "generated " << consolidated_loop_counter.str() << endl;
		consolidated_for_loop_index_stack.push_back(consolidated_loop_counter.str());
	}
	ConsolidatedForLoopIndexStack_ = consolidated_for_loop_index_stack;
	if (compoundBody_){
		compoundBody_->GenerateConsolidatedForLoopIndexes();
	}
	if (flagIsAForBody_ && counterContainsQuestions_){
		//cout << "popping off " << consolidated_for_loop_index_stack.back() << endl;
		consolidated_for_loop_index_stack.pop_back();
	}
	//cout << "EXIT CompoundStatement::GenerateConsolidatedForLoopIndexes:" << endl;
	if (next_){
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
	code.array_quest_init_area << "/* ENTER CompoundStatement::GenerateQuestionArrayInitLoopOpen */\n";
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
	code.array_quest_init_area << "/* EXIT CompoundStatement::GenerateQuestionArrayInitLoopOpen */\n";
}

void CompoundStatement::GenerateQuestionArrayInitLoopClose(StatementCompiledCode &code)
{
	for(int32_t i = for_bounds_stack.size()-1; i< for_bounds_stack.size(); ++i){
		code.array_quest_init_area << "stack_of_loop_indices.pop_back();\n";
		code.array_quest_init_area << "}" << endl;
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
		<< endl;

	if (flagGeneratedQuestionDefinitions_ == false
	   //&& qscript_parser::for_loop_max_counter_stack.size()>0
	   && flagIsAForBody_
	   && counterContainsQuestions_){
		code.quest_defns << "//CompoundStatement::GenerateCode()\n"
			<< "// Generating array declarations\n";
		if (compoundBody_){
			GenerateQuestionArrayInitLoopOpen(code);
		}
		flagGeneratedQuestionDefinitions_ = true;
	}
	code.program_code << "{" << endl;
	if (flagIsAForBody_ && counterContainsQuestions_){
		code.program_code << "int32_t " << ConsolidatedForLoopIndexStack_.back()
			<< " = ";
		code.program_code << PrintConsolidatedForLoopIndex(for_bounds_stack);
		code.program_code << ";\n";
	}
	if (compoundBody_){
		compoundBody_->GetQuestionsInBlock(questionsInBlock_, this);
		compoundBody_->GenerateCode(code);
	}
	GenerateQuestionArrayInitLoopClose(code);
	code.program_code << "}" << endl;
	if (next_)
		next_->GenerateCode(code);
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
	cout << "CheckNestedIndexUsage: on variable: " << init_var_name << ", "
		<< "for_loop_max_counter_stack.size(): "
		<< for_loop_max_counter_stack.size()  << endl;
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
	if (next_)
		next_->GenerateCode(code);
}

void ForStatement::GenerateConsolidatedForLoopIndexes()
{
	//cout << "ENTER AbstractStatement::GenerateConsolidatedForLoopIndexes:" << endl;
	if (forBody_){
		forBody_->GenerateConsolidatedForLoopIndexes();
	}
	if (next_){
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
	)
	: AbstractStatement(dtype, lline_number)
	  , questionName_(l_question->questionName_), namedStub_(l_named_range->name)
	  , namedRange_(l_named_range), lhs_(0), rhs_(l_question)
{ }

StubManipStatement::StubManipStatement(DataType dtype, int32_t lline_number
				       , AbstractQuestion * l_question_lhs
				       , AbstractQuestion * l_question_rhs
	)
	: AbstractStatement(dtype, lline_number)
	  , questionName_(l_question_rhs->questionName_), namedStub_()
	  , namedRange_(0), lhs_(l_question_lhs), rhs_(l_question_rhs)
{ }

// This constructor is deprecated and should be deleted at a later stage
StubManipStatement::StubManipStatement(DataType dtype, int32_t lline_number
				       , string l_named_stub
				       , string l_question_name
	)
	: AbstractStatement(dtype, lline_number)
	, questionName_(l_question_name), namedStub_(l_named_stub)
{ }

StubManipStatement::StubManipStatement(DataType dtype, int32_t lline_number
				       , string l_named_stub)
	: AbstractStatement(dtype, lline_number)
	, questionName_(), namedStub_(l_named_stub)
{ }

void StubManipStatement::GenerateCode(StatementCompiledCode & code)
{
	using qscript_parser::question_list;
	code.program_code << "/*StubManipStatement::GenerateCode()"
		<< questionName_ << ":" << namedStub_ << "*/"
		<< endl;
	code.program_code << "{" << endl;


	if (type_ == STUB_MANIP_DEL || type_ == STUB_MANIP_ADD){
		if (namedRange_ && rhs_) {
			code.program_code << "set<int32_t>::iterator set_iter = "
				<< questionName_
				<< "->input_data.begin();" << endl;
			code.program_code << "for( ; set_iter!= "
				<< questionName_
				<< "->input_data.end(); ++set_iter){" << endl;
			code.program_code << "\tfor(int32_t i = 0; i< "
				<< namedStub_ << ".size(); ++i){" << endl;
			code.program_code << "\t\tif (" << namedStub_
				<< "[i].code == *set_iter) {" << endl;
			if (type_ == STUB_MANIP_DEL){
				code.program_code << "\t\t\t"
					<< namedStub_ << "[i].mask = false; " << endl;
			} else if (type_ == STUB_MANIP_ADD) {
				code.program_code << "\t\t\t"
					<< namedStub_ << "[i].mask = true; " << endl;
			}
			code.program_code << "\t\t}" << endl;
			code.program_code << "\t}" << endl;
			code.program_code << "}" << endl;
		} else if (lhs_ && rhs_) {
			code.program_code << "set<int32_t>::iterator set_iter = "
				<< rhs_->questionName_
				<< "->input_data.begin();" << endl;
			code.program_code << "for( ; set_iter!= "
				<< rhs_->questionName_
				<< "->input_data.end(); ++set_iter){" << endl;
			code.program_code << lhs_->questionName_ << "->input_data.insert(*set_iter);\n";
			code.program_code << lhs_->questionName_ << "->isAnswered_ = true;\n";
			code.program_code << "\t}" << endl;
		} else {
			stringstream s;
			s << " incorrect setup of StubManipStatement: ";
			print_err(compiler_internal_error, s.str() , qscript_parser::line_no, __LINE__, __FILE__);
		}
	} else if (type_ == STUB_MANIP_UNSET_ALL || type_ == STUB_MANIP_SET_ALL) {
		code.program_code << "for(int32_t i = 0; i< "
			<< namedStub_ << ".size(); ++i){" << endl;
		if (type_ == STUB_MANIP_UNSET_ALL){
			code.program_code << namedStub_
				<< "[i].mask = false; " << endl;
		} else if (type_ == STUB_MANIP_SET_ALL) {
			code.program_code << namedStub_
				<< "[i].mask = true; " << endl;
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
