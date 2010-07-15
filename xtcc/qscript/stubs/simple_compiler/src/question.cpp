/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/question.cpp
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 
 *  Neil Xavier D'Souza
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <algorithm>

#include "question.h"
#include "named_range.h"
#include "scope.h"
#include "qscript_parser.h"
#include "user_navigation.h"

#include <sstream>
int scan_datalex();
int scan_dataparse();
extern vector<int> data;
extern UserNavigation user_navigation;

using std::cout;
using std::endl;
using std::cerr;
using namespace std;
//extern map<string, vector<string> > map_of_active_vars_for_questions;
void read_data(const char * prompt);
string PrintConsolidatedForLoopIndex(vector<AbstractExpression*> for_bounds_stack);
extern vector<string> consolidated_for_loop_index_stack;
int GetTempMapKeyNumber();
string GetRestoreVariableName(ActiveVariableInfo * av_info);
string GetRestoreVariableContainerName(ActiveVariableInfo * av_info
				       , string & questionName_);
string GetRestoreVariableContainerNameArray(ActiveVariableInfo * av_info
		, string & questionName_, string map_key);
extern vector<string> consolidated_for_loop_index_stack;

	//! this is only called in the compile time environment
AbstractQuestion::AbstractQuestion(DataType l_type, int l_no
		, string l_name, string l_text
		, QuestionType l_q_type, int l_no_mpn, DataType l_dt
		, vector<AbstractExpression*> & l_for_bounds_stack
		, CompoundStatement * l_enclosing_scope 
		, vector<ActiveVariableInfo* > l_av_info
	): 
	AbstractStatement(l_type, l_no)
	, questionName_(l_name), questionText_(l_text), q_type(l_q_type)
	, no_mpn(l_no_mpn), dt(l_dt)
	, for_bounds_stack(l_for_bounds_stack)
	, isAnswered_(false), isModified_(false)
	, enclosingCompoundStatement_(l_enclosing_scope)
	, activeVarInfo_(l_av_info)
	, dummyArrayQuestion_(0)
{
	if(enclosingCompoundStatement_==0){
		print_err(compiler_internal_error, " no enclosing CompoundStatement scope for question "
			, qscript_parser::line_no, __LINE__, __FILE__  );
	}
}


AbstractQuestion::AbstractQuestion(DataType l_type, int l_no
		, string l_name, string l_text
		, QuestionType l_q_type, int l_no_mpn, DataType l_dt
	): 
	AbstractStatement(l_type, l_no), questionName_(l_name)
	, questionText_(l_text), q_type(l_q_type) 
	, no_mpn(l_no_mpn), dt(l_dt)
	, for_bounds_stack(0)
	, isAnswered_(false), isModified_(false)
	//, enclosingCompoundStatement_(qscript_parser::stack_cmpd_stmt.back())
	, enclosingCompoundStatement_(0)
	, dummyArrayQuestion_(0)
{
	//if(enclosingCompoundStatement_==0){
	//	print_err(compiler_internal_error, " no enclosing CompoundStatement scope for question "
	//		, qscript_parser::line_no, __LINE__, __FILE__  );
	//}
}

	//! this is only called in the compile time environment
AbstractQuestion::AbstractQuestion(DataType l_type, int l_no
		, string l_name, string l_text
		, QuestionType l_q_type, int l_no_mpn, DataType l_dt
		, CompoundStatement * l_enclosing_scope
		, vector<ActiveVariableInfo* > l_av_info
	): 
	AbstractStatement(l_type, l_no), questionName_(l_name)
	, questionText_(l_text), q_type(l_q_type) 
	, no_mpn(l_no_mpn), dt(l_dt)
	, for_bounds_stack(0)
	, isAnswered_(false), isModified_(false)
	, enclosingCompoundStatement_(l_enclosing_scope)
	, activeVarInfo_(l_av_info)
	, dummyArrayQuestion_(0)
{
	if(enclosingCompoundStatement_==0){
		print_err(compiler_internal_error, " no enclosing CompoundStatement scope for question "
			, qscript_parser::line_no, __LINE__, __FILE__  );
	}
}

// this is only called from the runtime
AbstractQuestion::AbstractQuestion(DataType l_type, int l_no, string l_name
		, string l_text
		, QuestionType l_q_type, int l_no_mpn, DataType l_dt
		, const vector<int>& l_loop_index_values
		, DummyArrayQuestion * l_dummy_array
	): 
	AbstractStatement(l_type, l_no), questionName_(l_name)
	, questionText_(l_text), q_type(l_q_type) 
	, no_mpn(l_no_mpn), dt(l_dt) , for_bounds_stack(0)
	, loop_index_values(l_loop_index_values)
	, isAnswered_(false), isModified_(false)
	, enclosingCompoundStatement_(0) // this is only used in the compile time environment
	, dummyArrayQuestion_(l_dummy_array)
{
	//for(int i=0; i<l_loop_index_values.size(); ++i){
	//	cout << "l_loop_index_values " << i << ":" << l_loop_index_values[i] << endl;
	//}
}


void AbstractQuestion::GetQuestionsInBlock(vector<AbstractQuestion*> & question_list,
		AbstractStatement * stop_at)
{
	//std::cerr << "ENTER AbstractQuestion::GetQuestionsInBlock()" << std::endl;
	question_list.push_back(this);
	if(next_ && next_!=stop_at){
		next_->GetQuestionsInBlock(question_list, stop_at);
	}
	//std::cerr << "EXIT AbstractQuestion::GetQuestionsInBlock()" << std::endl;
}

void AbstractQuestion::PrintUserNavigation(ostringstream & program_code)
{
	// hard coded for now
	program_code << "if (user_navigation==NAVIGATE_PREVIOUS){\n\
		AbstractQuestion * target_question = ComputePreviousQuestion(" 
		<< questionName_.c_str() << ");\n\
		if(target_question==0)\n\
		goto label_eval_" << questionName_.c_str() << ";\n\
		else {\n\
		jumpToQuestion = target_question->questionName_;\n\
		if(target_question->type_==QUESTION_ARR_TYPE){\n\
			jumpToIndex = ComputeJumpToIndex(target_question);\n\
		}\n\
		cout << \"target question: \" << jumpToQuestion;\n\
		cout << \"target question Index: \" << jumpToIndex;\n\
		back_jump=true;\n\
		user_navigation=NOT_SET;\n\
		goto start_of_questions;\n}\n}\n" ;
	program_code << "else if (user_navigation==NAVIGATE_NEXT){\n\
		stopAtNextQuestion=true;\n\
		user_navigation=NOT_SET;\n\
		}\n";
	program_code << "else if (user_navigation==JUMP_TO_QUESTION){\n\
		DisplayActiveQuestions();\n\
		GetUserResponse(jumpToQuestion, jumpToIndex);\n\
		user_navigation=NOT_SET;\n\
		goto start_of_questions;\n\
		}\n";
	program_code << "else if (user_navigation==SAVE_DATA){\n\
		write_data_to_disk(question_list, jno, ser_no);\n\
		}";
	program_code << " else { " << endl
		<< "last_question_answered = " << questionName_ << ";\n"
		<< "}\n";
}

void AbstractQuestion::PrintUserNavigationArrayQuestion(ostringstream & program_code)
{
	program_code << "if (user_navigation==NAVIGATE_PREVIOUS){\n\
		AbstractQuestion * target_question = ComputePreviousQuestion(" 
			<< questionName_.c_str()  << "_list.questionList[" 
			<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< "]"
			<< ");\n\
		if(target_question==0)\n\
		goto label_eval_" << questionName_.c_str() << ";\n\
		else {\n\
		jumpToQuestion = target_question->questionName_;\n\
		if(target_question->type_==QUESTION_ARR_TYPE){\n\
			jumpToIndex = ComputeJumpToIndex(target_question);\n\
		}\n\
		cout << \"target question: \" << jumpToQuestion;\n\
		cout << \"target question Index: \" << jumpToIndex;\n\
		back_jump=true;\n\
		user_navigation=NOT_SET;\n\
		goto start_of_questions;\n}\n}\n" ;
	program_code << "else if (user_navigation==NAVIGATE_NEXT){\n\
		stopAtNextQuestion=true;\n\
		user_navigation=NOT_SET;\n}\n";
	program_code << "else if (user_navigation==JUMP_TO_QUESTION){\n\
		DisplayActiveQuestions();\n\
		GetUserResponse(jumpToQuestion, jumpToIndex);\n\
		user_navigation=NOT_SET;\n\
		goto start_of_questions;\n\
		}\n";
	program_code << "else if (user_navigation==SAVE_DATA){\n\
		write_data_to_disk(question_list, jno, ser_no);\n\
		}";
	program_code << " else { " << endl
		<< "last_question_answered = " << questionName_ << "_list.questionList["
		//<< consolidated_for_loop_index_stack[consolidated_for_loop_index_stack.size()-1]
		<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
		<< "]" << ";\n"
		<< "}\n";
}

void AbstractQuestion::PrintEvalAndNavigateCode(ostringstream & program_code)
{
	program_code << "if (!" 
		<< questionName_.c_str() << "->isAnswered_ ||" << endl
		<< "stopAtNextQuestion ||" << endl
		<< "jumpToQuestion == \"" << questionName_.c_str() << "\" ){ " << endl;
	program_code << "if (stopAtNextQuestion ) {\n\tstopAtNextQuestion=false;\n}\n";
	program_code << "label_eval_" << questionName_.c_str() << ":\n"
		<< "\t\t" 
		<< questionName_.c_str() 
		<< "->eval();\n" ;
	PrintUserNavigation(program_code);
	program_code <<  "}\n";
}

void AbstractQuestion::PrintQuestionArrayInitialisation(StatementCompiledCode & code)
{
	for(int i=0; i< for_bounds_stack.size(); ++i){
		code.quest_defns << "for(int ";
		BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(for_bounds_stack[i]);
		if(bin_expr_ptr){
			AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
			AbstractExpression * lhs = bin_expr_ptr->leftOperand_;
			ExpressionCompiledCode expr_code1;
			lhs->PrintExpressionCode(expr_code1);
			code.quest_defns << expr_code1.code_bef_expr.str() << expr_code1.code_expr.str();
			code.quest_defns << "=0;";
			ExpressionCompiledCode expr_code2;
			for_bounds_stack[i]->PrintExpressionCode(expr_code2);
			code.quest_defns << expr_code2.code_bef_expr.str() << expr_code2.code_expr.str();
			code.quest_defns << "; ++";
			ExpressionCompiledCode expr_code3;
			lhs->PrintExpressionCode(expr_code3);
			code.quest_defns << expr_code3.code_bef_expr.str() << expr_code3.code_expr.str();
			code.quest_defns <<	"){" << endl;
			if(i==0){
				code.quest_defns << "vector<int> stack_of_loop_indices;\n";
					//<< "(" <<  for_bounds_stack.size() << ");\n";
			}
			code.quest_defns << "stack_of_loop_indices.push_back(";
			//lhs->PrintExpressionCode(quest_defns, quest_defns); // note this is already stored in expr_code3
			code.quest_defns << expr_code3.code_bef_expr.str() << expr_code3.code_expr.str();
			code.quest_defns << ");\n";
		} else {
			ExpressionCompiledCode expr_code;
			for_bounds_stack[i]->PrintExpressionCode(expr_code);
			code.quest_defns << expr_code.code_bef_expr.str() << expr_code.code_expr.str();
			print_err(compiler_sem_err
				, "for loop index condition is not a binary expression" 
				, 0, __LINE__, __FILE__);
		}
	}
}

void AbstractQuestion::GetDataFromUser()
{

	bool invalid_code=false;
	string prompt="before do: Enter Data:";
	do{
		invalid_code=true;
		read_data(prompt.c_str());
		cout << "data.size(): " << data.size() << endl;
		if(data.size()==0 && 
			(user_navigation == NAVIGATE_PREVIOUS 
			 || user_navigation == NAVIGATE_NEXT
			 || user_navigation == JUMP_TO_QUESTION) ){
			return;
		}

			
		for(unsigned int i=0; i<data.size(); ++i){
			cout << "Testing data exists: " << data[i] << endl;
			invalid_code = !IsValid(data[i]);
			if (invalid_code==true){
				prompt = "Input contained some invalid data\nRe-enter Data\n";
				data.clear();
				break;
			}
		}
		if(invalid_code)
			continue;
		if(q_type==spn && data.size()>1) {
			prompt="Single coded Question - please enter only 1 code:" ;
			invalid_code=true;
			data.clear();
		} else if (q_type==mpn && data.size() > no_mpn){
			prompt="Multi coded Question, no values exceed max allowed:  " ;
			invalid_code=true;
			data.clear();
		} else {
			invalid_code=false;
		}

		if(invalid_code==false){
			input_data.erase(input_data.begin(), input_data.end());
			for(unsigned int i=0; i<data.size(); ++i){
				input_data.insert(data[i]);
				cout << "storing: " << data[i] 
					<< " into input_data" << endl;
			}
			isAnswered_=true;
		}
	} while (invalid_code==true);
	
	data.clear();
}

void AbstractQuestion::PrintArrayDeclarations(ostringstream & quest_defns)
{
	string temp_array_bounds_name = "list_" + questionName_ + "_array_bounds";
	quest_defns << "vector<int> " << temp_array_bounds_name 
		<< "(" << for_bounds_stack.size() << ")"
		<< ";" << endl;
	for(int i=0; i< for_bounds_stack.size(); ++i){
		ostringstream array_bounds;
		BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(for_bounds_stack[i]);
		if(bin_expr_ptr){
			AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
			ExpressionCompiledCode expr_code;
			rhs->PrintExpressionCode(expr_code);
			array_bounds << expr_code.code_bef_expr.str() << expr_code.code_expr.str();
			//int bounds = atoi(array_bounds.str().c_str());
			quest_defns << temp_array_bounds_name 
				<< "[" << i << "]=" << array_bounds.str() << ";\n";
			array_bounds.clear();

		} else {
			ExpressionCompiledCode expr_code;
			for_bounds_stack[i]->PrintExpressionCode(expr_code);
			array_bounds << expr_code.code_bef_expr.str()
				<< expr_code.code_expr.str();
			print_err(compiler_sem_err
				, "for loop index condition is not a binary expression" 
				, 0, __LINE__, __FILE__);
		}
	}
	//----------------------------------------
	quest_defns << "ArrayQuestion " << questionName_ << "_list(" 
		<< temp_array_bounds_name <<");" << endl;
	quest_defns << "DummyArrayQuestion* dum_" << questionName_ 
		<< "= new DummyArrayQuestion(\""  << questionName_ << "\","
		<< temp_array_bounds_name <<");" << endl;
	quest_defns << "question_list.push_back( dum_" << questionName_ << ");" 
		<< endl;
}

//! this is only called in the compile time environment
RangeQuestion::RangeQuestion(DataType this_stmt_type, int line_number,
	string l_name, string l_q_text,
	QuestionType l_q_type, int l_no_mpn, DataType l_dt,
	XtccSet& l_r_data
	, vector<AbstractExpression*> & l_for_bounds_stack
	, CompoundStatement * l_enclosing_scope 
	, vector<ActiveVariableInfo* > l_av_info
	): 
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text
		, l_q_type, l_no_mpn, l_dt , l_for_bounds_stack
		, l_enclosing_scope, l_av_info
		)
{
	r_data = new XtccSet(l_r_data);
}

	//! this is only called in the runtime environment
RangeQuestion::RangeQuestion(DataType this_stmt_type, int line_number
	, string l_name, string l_q_text
	, QuestionType l_q_type, int l_no_mpn
	, DataType l_dt , XtccSet& l_r_data
	): 
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt
		)
{
	r_data = new XtccSet(l_r_data);
}

	//! this is only called in the compile time environment
RangeQuestion::RangeQuestion(DataType this_stmt_type, int line_number
	, string l_name, string l_q_text
	, QuestionType l_q_type, int l_no_mpn
	, DataType l_dt , XtccSet& l_r_data
	, CompoundStatement * l_enclosing_scope
	, vector<ActiveVariableInfo* > l_av_info
	): 
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt, l_enclosing_scope, l_av_info
		)
{
	r_data = new XtccSet(l_r_data);
}

	//! this is only called from the runtime environment
RangeQuestion::RangeQuestion(DataType this_stmt_type, int line_number,
	string l_name, string l_q_text,
	QuestionType l_q_type, int l_no_mpn, DataType l_dt,
	XtccSet& l_r_data
	, const vector<int> & l_loop_index_values
	, DummyArrayQuestion * l_dummy_array
	): 
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt, l_loop_index_values, l_dummy_array
		)
{
	r_data = new XtccSet(l_r_data);
}


bool RangeQuestion::IsValid(int value)
{
	return (r_data->exists(value))? true: false;
}

void RangeQuestion::eval()
{
	cout << questionName_ << "." << questionText_ << endl << endl;
	for(	set<int>::iterator it=r_data->indiv.begin(); 
			it!=r_data->indiv.end(); ++it){
		cout << *it << endl;
	}
	for(int i=0; i<r_data->range.size(); ++i){
		for(int j=r_data->range[i].first; j<=r_data->range[i].second
				;++j){  
			cout << j << endl; 
		}
	}


	if(input_data.begin()!=input_data.end()){
		cout << "Current data values: ";

		for(set<int>::iterator iter=input_data.begin();
			iter!=input_data.end(); ++iter){
			cout << *iter << " ";
		}
		cout << endl;
	}
	AbstractQuestion::GetDataFromUser();
}

void RangeQuestion::WriteDataToDisk(ofstream& data_file)
{
	if(loop_index_values.size()>0){
		data_file << questionName_;
		for(int i=0; i< loop_index_values.size(); ++i){
			data_file << "$" << loop_index_values[i];
		}
	} else {
		data_file << questionName_ ;
	}
	data_file << ":" ;
	for( set<int>::iterator iter=input_data.begin();
			iter!=input_data.end(); ++iter){
		data_file << *iter << " ";
	}
	data_file << endl;
	input_data.clear();
}

bool NamedStubQuestion::IsValid(int value)
{
	vector<stub_pair> & vec= *stub_ptr;
	for (unsigned int j=0; j<vec.size(); ++j){
		if(vec[j].code==value && vec[j].mask){
			return true;
		}
	}
	return false;
}

void NamedStubQuestion::eval()
{
	cout << questionName_ << "." << questionText_ << endl << endl;
	vector<stub_pair> vec= *stub_ptr;
	for(unsigned int i=0; i< vec.size(); ++i){
		if( vec[i].mask)
			cout << vec[i].stub_text << ": " << vec[i].code << endl;
	}


	if(input_data.begin()!=input_data.end()){
		cout << "Current data values: ";
		
		for(set<int>::iterator iter=input_data.begin();
			iter!=input_data.end(); ++iter){
			cout << *iter << " ";
		}
		cout << endl;
	}

	AbstractQuestion::GetDataFromUser();
	
}

void RangeQuestion::GenerateCodeSingleQuestion(StatementCompiledCode & code)
{
	//AbstractQuestion::PrintSetupBackJump(quest_defns, program_code);
	
	static int xtcc_set_counter=0;
	const int BUF_SIZE=100;
	char xtcc_set_name[BUF_SIZE];
	sprintf(xtcc_set_name, "xs_%d", xtcc_set_counter++);
	code.quest_defns  << "XtccSet " << xtcc_set_name << ";" << endl;
	for(	set<int>::iterator it=r_data->indiv.begin(); 
			it!=r_data->indiv.end(); ++it){
		code.quest_defns << xtcc_set_name << ".indiv.insert(" << *it 
			<< ");" << endl;
	}
	for(unsigned int i=0; i<r_data->range.size(); ++i){
		code.quest_defns << xtcc_set_name 
			<< ".range.push_back(pair<int,int>("
			<< r_data->range[i].first << "," 
			<< r_data->range[i].second
			<< "));" << endl;
	}
	string q_type_str;
	print_q_type(q_type_str);

	string datatype_str;
	print_data_type(datatype_str);

	ostringstream quest_decl;
	quest_decl << "RangeQuestion * " << questionName_.c_str() 
		<< " = new RangeQuestion("
		<< (( type_ == QUESTION_TYPE) ?"QUESTION_TYPE, " : "QUESTION_ARR_TYPE, " )
		<< lineNo_ << "," 
		<< "string( \"" << questionName_.c_str() << "\")" << "," 
		<< "string(\" " << questionText_.c_str() << "\")" << ","
		<< q_type_str.c_str() << ","
		<< no_mpn << ","
		<< datatype_str.c_str() << ","
		<< xtcc_set_name;
	if(for_bounds_stack.size() >0 ){
		quest_decl << ", stack_of_loop_indices "
			<< ", dum_" << questionName_;
	}
	quest_decl << ");\n";
	quest_decl << "question_list.push_back(" << questionName_.c_str() 
		<< ");\n";

	if(for_bounds_stack.size()==0){
		code.quest_defns << quest_decl.str();
	} else {
		code.array_quest_init_area << quest_decl.str();
	}

	if(for_bounds_stack.size()==0){
		AbstractQuestion::PrintEvalAndNavigateCode(code.program_code);
	}else {
		AbstractQuestion::PrintEvalArrayQuestion( code);
	}

}



void RangeQuestion::GenerateCode( StatementCompiledCode & code )
{
	if(for_bounds_stack.size()==0){
		AbstractQuestion::PrintSetupBackJump(code);
		GenerateCodeSingleQuestion(code);
	} else {
		AbstractQuestion::PrintSetupBackJump(code);
		PrintArrayDeclarations(code.quest_defns);
		
		GenerateCodeSingleQuestion(code);
		code.array_quest_init_area << questionName_ << "_list.questionList.push_back(" << questionName_ << ");"
			<< endl;
	}
	if(next_){
		next_->GenerateCode(code);
	}
}

//extern vector <scope*> active_scope_list;
void NamedStubQuestion::GenerateCodeSingleQuestion(StatementCompiledCode & code)
{
	//AbstractQuestion::PrintSetupBackJump(quest_defns, program_code);

	string q_type_str;
	print_q_type(q_type_str);

	string datatype_str;
	print_data_type(datatype_str);

	ostringstream quest_decl;
	quest_decl << "NamedStubQuestion * " << questionName_.c_str() 
		<< " = new NamedStubQuestion("
		<< (( type_ == QUESTION_TYPE) ?"QUESTION_TYPE, " : "QUESTION_ARR_TYPE, " )
		<< lineNo_ << "," 
		<< "string( \"" << questionName_.c_str() << "\")" << "," 
		<< "string(\" " << questionText_.c_str() << "\")" << ","
		<< q_type_str.c_str() << ","
		<< no_mpn << ","
		<< datatype_str.c_str() << ",&"
		<< nr_ptr->name ;
	if(for_bounds_stack.size() >0 ){
		quest_decl << ", stack_of_loop_indices "
			<< ", dum_" << questionName_;
	}
	quest_decl << ");\n";
	quest_decl << "question_list.push_back(" << questionName_.c_str() << ");\n";

	if(for_bounds_stack.size()==0){
		code.quest_defns << quest_decl.str();
	} else {
		code.array_quest_init_area << quest_decl.str();
	}
	//program_code << "\t\t" << questionName_.c_str() << "->eval();\n" ;

	if(for_bounds_stack.size()==0){
		AbstractQuestion::PrintEvalAndNavigateCode(code.program_code);
	}  else {
		AbstractQuestion::PrintEvalArrayQuestion(code);
	}

}

void NamedStubQuestion::GenerateCode( StatementCompiledCode &code)
{
	if(for_bounds_stack.size()==0){
		AbstractQuestion::PrintSetupBackJump(code);
		GenerateCodeSingleQuestion(code);
	}  else {
		//----------------------------------------
		AbstractQuestion::PrintSetupBackJump(code);
		PrintArrayDeclarations(code.quest_defns);
		GenerateCodeSingleQuestion(code);
		code.array_quest_init_area << questionName_ << "_list.questionList.push_back(" << questionName_ << ");"
			<< endl;
	}

	if(next_){
		next_->GenerateCode(code);
	} 

}

	//! this is only called in the compile time environment
NamedStubQuestion::NamedStubQuestion(DataType this_stmt_type, int line_number,
	string l_name, string l_q_text,
	QuestionType l_q_type, int l_no_mpn, DataType l_dt,
	//string& l_named_list): 
	named_range* l_nr_ptr
	//, AbstractExpression* l_arr_sz
	, vector<AbstractExpression*>& l_for_bounds_stack
	, CompoundStatement * l_enclosing_scope 
	, vector<ActiveVariableInfo* > l_av_info
	):
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt
		//, l_arr_sz
		, l_for_bounds_stack, l_enclosing_scope, l_av_info
		), 
	//named_list(l_named_list)
	nr_ptr(l_nr_ptr), stub_ptr(0)
{
}

	//! this is only called in the compile time environment
NamedStubQuestion::NamedStubQuestion(DataType this_stmt_type, int line_number,
	string l_name, string l_q_text,
	QuestionType l_q_type, int l_no_mpn, DataType l_dt,
	named_range* l_nr_ptr
	, CompoundStatement * l_enclosing_scope 
	, vector<ActiveVariableInfo* > l_av_info
	):
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt, l_enclosing_scope, l_av_info
		), 
	nr_ptr(l_nr_ptr), stub_ptr(0)
{
}

NamedStubQuestion::NamedStubQuestion(DataType this_stmt_type, int line_number,
	string l_name, string l_q_text,
	QuestionType l_q_type, int l_no_mpn, DataType l_dt,
	vector<stub_pair>* l_stub_ptr
	):
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt
		), 
	nr_ptr(0), stub_ptr(l_stub_ptr)
{
}

//! only called in the runtime environment
NamedStubQuestion::NamedStubQuestion(DataType this_stmt_type, int line_number
	, string l_name, string l_q_text
	, QuestionType l_q_type, int l_no_mpn, DataType l_dt
	, vector<stub_pair>* l_stub_ptr
	, const vector<int> & l_loop_index_values
	, DummyArrayQuestion * l_dummy_array
	):
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt, l_loop_index_values, l_dummy_array
		), 
	nr_ptr(0), stub_ptr(l_stub_ptr)
{
}

void AbstractQuestion::print_q_type(string &s)
{
	const int BUF_SIZE=200;
	char buff[BUF_SIZE];
	if(q_type==spn){
		s="spn";
	} else if(q_type==mpn){
		s="mpn";
	} else {
		sprintf(buff, " internal compiler error: update AbstractQuestion::print_q_type: %d, %s\n", 
			__LINE__, __FILE__);
		s=buff;
	}
}



void AbstractQuestion::print_data_type(string &s)
{	
	if(dt==	VOID_TYPE){
		s="VOID_TYPE";
	} else if(dt==INT8_TYPE){
		s="INT8_TYPE";
	} else if(dt== INT16_TYPE) {
		s="INT16_TYPE";
	} else if(dt==  INT32_TYPE){
		s="INT32_TYPE";
	} else if(dt== FLOAT_TYPE){
		s="FLOAT_TYPE";
	} else if (dt== DOUBLE_TYPE){
		s="DOUBLE_TYPE";
	} else if (dt== BOOL_TYPE){
		s="BOOL_TYPE";
	} else if (dt== STRING_TYPE){
		s="STRING_TYPE";
	} else {
		const int BUF_SIZE=200;
		char buff[BUF_SIZE];
		sprintf(buff, " internal compiler error: update AbstractQuestion::print_data_type : %d, %s", 
			__LINE__, __FILE__);
		s=buff;
	}
}


void NamedStubQuestion::WriteDataToDisk(ofstream& data_file)
{
	if(loop_index_values.size()>0){

		data_file << questionName_;
		for(int i=0; i< loop_index_values.size(); ++i){
			data_file << "$" << loop_index_values[i];
		}
	} else  {
		data_file << questionName_ ;
	}
	data_file << ":" ;
	for( set<int>::iterator iter=input_data.begin();
			iter!=input_data.end(); ++iter){
		data_file << *iter << " ";
	}
	data_file << endl;
	input_data.clear();
}

void AbstractQuestion::PrintSetupBackJump(StatementCompiledCode &code)
{
	using qscript_parser::map_of_active_vars_for_questions;
	code.program_code << "/* ENTER: AbstractQuestion::PrintSetupBackJump() : for_bounds_stack.size():" 
		<< for_bounds_stack.size() << " */\n";
	code.quest_defns << "map <string,int8_t> " << questionName_ << "_scope_int8_t;\n";
	code.quest_defns << "map <string,int16_t> " << questionName_ << "_scope_int16_t;\n";
	code.quest_defns << "map <string,int32_t> " << questionName_ << "_scope_int32_t;\n";
	code.quest_defns << "map <string,float> " << questionName_ << "_scope_float_t;\n";
	code.quest_defns << "map <string,double> " << questionName_ << "_scope_double_t;\n";
	code.quest_defns << "map <string,set<int> > " << questionName_ << "_scope_question_t;\n";


	code.program_code << "lab_" << questionName_ << ":" << endl;


	if(for_bounds_stack.size()==0){
		code.program_code << "if ( back_jump==true  && " << questionName_ <<  "->isAnswered_==true ) {" << endl;
		//for(int i=active_pop_vars_for_this_question.size()-1; i>=0; --i){
		//	code.program_code << active_pop_vars_for_this_question[i] << endl;
		//}
		ostringstream &s(code.program_code);
		// the code below should be extracted to a method: NxD 11-Jun-2010
		SetupSimpleQuestionRestore(code);
		code.program_code << "if ( jumpToQuestion == \"" << questionName_ << "\")\n{ back_jump=false;\n}\n";
		code.program_code << "}" << endl;


		SetupSimpleQuestionSave(code);
	} else {
		// Handle Array Question here

		ostringstream &s(code.program_code);
		s << "if ( back_jump==true  && " << questionName_ 
			<<  "_list.questionList["
			<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< "]->isAnswered_==true ) {" << endl;
		SetupArrayQuestionRestore(code);
		s << "}" << endl;
		SetupArrayQuestionSave(code);
	}
	code.program_code << "/* EXIT: AbstractQuestion::PrintSetupBackJump()  */\n";
}


void AbstractQuestion::PrintEvalArrayQuestion(StatementCompiledCode & code)
{
	// ----------------------------------
	code.program_code << "cout << \"jumpToQuestion = \" << jumpToQuestion << endl;" 
		<< endl;
	code.program_code << "cout << \"jumpToIndex = \" << jumpToIndex << endl;" 
		<< endl;
	code.program_code << "if (!"
			<< questionName_.c_str() << "_list.questionList[";
	string consolidated_for_loop_index=PrintConsolidatedForLoopIndex(for_bounds_stack);
	code.program_code << consolidated_for_loop_index;
	code.program_code << "]->isAnswered_||stopAtNextQuestion||\n" 
		<< "(jumpToQuestion == \"" << questionName_ << "\""
		<< " && " << "jumpToIndex ==  " 
		<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
		<< ") ) {\n";
	code.program_code << "label_eval_" << questionName_ << ":\n";
	code.program_code << "if ( jumpToQuestion == \"" << questionName_ 
		<< "\" && jumpToIndex==" 
		<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
		<< "){\n" 
		<< "back_jump=false;\n" 
		<< "jumpToIndex=-1;\n"
		<< "}\n";

	code.program_code << "\t\t" << questionName_ << "_list.questionList[";
	// ---------------------------------
	code.program_code << consolidated_for_loop_index;
	code.program_code << "]->eval();\n" ;
	PrintUserNavigationArrayQuestion(code.program_code);

	code.program_code << "}\n";
	//code.program_code << "*/\n";
}

RangeQuestion::~RangeQuestion()
{
	delete r_data ; r_data=0;
}


// -----------------------------------------------------
// DummyArrayQuestion


void DummyArrayQuestion::WriteDataToDisk(ofstream& data_file)
{
	data_file << questionName_ << " BOUNDS" ;
	for(int i=0; i<array_bounds.size(); ++i){
		data_file << " "<< array_bounds[i];
	}
	data_file << endl;
}

int GetTempMapKeyNumber()
{
	static int temp_map_key_number;
	return temp_map_key_number++;
}

// ----------------------------------------
void AbstractQuestion::SetupSimpleQuestionRestore(StatementCompiledCode & code)
{
	ostringstream &s(code.program_code);
	s << "/* AbstractQuestion::SetupSimpleQuestionRestore */\n";
	for(int i=0; i<activeVarInfo_.size(); ++i){

		switch(activeVarInfo_[i]->type_){
		case INT8_TYPE:
		case INT16_TYPE:	
		case INT32_TYPE:	
		case FLOAT_TYPE:
		case DOUBLE_TYPE:
		case QUESTION_TYPE:
			s << GetRestoreVariableName(activeVarInfo_[i]) 
				<< "=" 
				<< GetRestoreVariableContainerName(activeVarInfo_[i], questionName_)
				<< ";\n" ;
			break;
		case QUESTION_ARR_TYPE:
			s << PrintRestoreArrayQuestion(activeVarInfo_[i]);
			break;
		default:
			string err_msg = "unhandled type in SetupSimpleQuestionRestore()";
			s << err_msg;
			print_err(compiler_internal_error, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
		}
	}
}

string GetRestoreVariableName(ActiveVariableInfo * av_info)
{
	ostringstream s;
	switch(av_info->type_){
	case INT8_TYPE:
		s << av_info->name_ ;
		break;
	case INT16_TYPE:	
		s << av_info->name_ ;
		break;
	case INT32_TYPE:	
		s << av_info->name_ ;
		break;
	case FLOAT_TYPE:
		s << av_info->name_ ;
		break;
	case DOUBLE_TYPE:
		s << av_info->name_ ;
		break;
	case QUESTION_TYPE:
		s << av_info->name_ << "->input_data";
		break;
	case QUESTION_ARR_TYPE:
		s << "/* GetRestoreVariableName::QUESTION_ARR_TYPE not yet handled */\n";
		break;
	default: {
			string err_msg = "unhandled type in print_pop_stack\"";
			s << err_msg;
			print_err(compiler_sem_err, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
		}
	}
	return s.str();
}

string GetRestoreVariableContainerName(ActiveVariableInfo * av_info, string & questionName_)
{
	ostringstream s;
	switch(av_info->type_){
	case INT8_TYPE:
		s << questionName_ << "_scope_int8_t[\"" << av_info->name_ << "\"]" ;
		break;
	case INT16_TYPE:	
		s << questionName_ << "_scope_int16_t[\"" << av_info->name_ << "\"]";
		break;
	case INT32_TYPE:	
		s << questionName_ << "_scope_int32_t[\"" << av_info->name_ << "\"]";
		break;
	case FLOAT_TYPE:
		s << questionName_ << "_scope_float_t[\"" << av_info->name_ << "\"]";
		break;
	case DOUBLE_TYPE:
		s << questionName_ << "_scope_double_t[\"" << av_info->name_ << "\"]";
		break;
	case QUESTION_TYPE:
		s << av_info->name_ << "_scope_question_t"<<  "[\"" << questionName_ << "\"]" ;
		break;
		/*
	case QUESTION_ARR_TYPE:
		s << av_info->name_ << "_scope_question_t"<<  "[\"" << questionName_ << "\"]" << endl;
		break;
		*/
	default: {
			string err_msg = "unhandled type in GetRestoreVariableContainerName";
			s << err_msg;
			print_err(compiler_sem_err, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
		}
	}
	return s.str();
}

string AbstractQuestion::PrintRestoreArrayQuestion(ActiveVariableInfo * av_info)
{
	ostringstream s;
	s << "/* ENTER AbstractQuestion::PrintRestoreArrayQuestion "
		<< av_info->name_ 
		<< " at location: " << questionName_
		<< " */\n";
	if (enclosingCompoundStatement_){
		vector<AbstractQuestion*> & questions_in_block = 
			enclosingCompoundStatement_->questionsInBlock_;
		s << "/* questionsInBlock_: ";
		for(int i=0; i<questions_in_block.size(); ++i){
			s << questions_in_block[i]->questionName_ << " ";
		}
		s << " */\n"; 
	} else {
		ostringstream err_msg ;
		err_msg << " enclosingCompoundStatement_== 0 ... exiting \n";
		print_err(compiler_internal_error, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
	}

	AbstractQuestion * restore_array_quest = 0;
	for(int i=0; i< qscript_parser::question_list.size(); ++i){
		if( qscript_parser::question_list[i]->questionName_
			== av_info->name_){
			restore_array_quest=qscript_parser::question_list[i];
			break;
		}
	}
	if(restore_array_quest==0){
		string err_msg = "Could not find " + av_info->name_ + " in question list while generating restore array code"
			+ " PrintRestoreArrayQuestion ";
		print_err(compiler_internal_error, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
	}
	if(IsInTheSameScopeAndLevel(this, restore_array_quest)) {
		s << "/*" 
			<< questionName_ << " and "
			<< restore_array_quest->questionName_ 
			<< " :are at the same scope and level */"
			<< endl;
		s << "for(int xtcc_i=0; xtcc_i<";
		s << restore_array_quest->enclosingCompoundStatement_
			->ConsolidatedForLoopIndexStack_.back();
		s << ";++xtcc_i){\n";
		s<< "ostringstream map_key;\n"
			<< "map_key << \"" << questionName_ << "\"" 
			<< " << " 
			<< "\"_\" << xtcc_i << \"$\" << " 
			<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< ";" << endl
			<< restore_array_quest->questionName_ 
			<< "_list.questionList[xtcc_i]->input_data=" 
			<< restore_array_quest->questionName_ << "_scope_question_t["
			<< "map_key.str()" << "];\n"
			<< endl;
		s << "}\n";

	} else if (NotInTheSameBlock(this, restore_array_quest)){
		s << "/*" 
			<< questionName_ << " and "
			<< restore_array_quest->questionName_ 
			<< " :belong to different blocks "
			<< "*/"
			<< endl;

		s << "for(int xtcc_i=0; xtcc_i<";
		for(int i1=0; i1<restore_array_quest->for_bounds_stack.size(); ++i1) {
			BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
					restore_array_quest->for_bounds_stack[i1]);
			if(bin_expr_ptr){
				AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
				ExpressionCompiledCode expr_code;
				rhs->PrintExpressionCode(expr_code); 
				s << expr_code.code_bef_expr.str() /* should be empty */
					<< expr_code.code_expr.str();
				if(i1<restore_array_quest->for_bounds_stack.size()-1) {
					s << "*";
				}
			} else {
				print_err(compiler_code_generation_error
					, "for loop index condition is not a binary expression" 
					, 0, __LINE__, __FILE__);
			}
		}
		s << ";++xtcc_i){\n"
			<< "ostringstream map_key;\n"
			<< "map_key << \"" << questionName_ << "\"" 
			<< " << " 
			<< "\"_\" << xtcc_i << \"$\" << " 
			//<< consolidated_for_loop_index_stack.back()
			<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< ";" << endl
			<< restore_array_quest->questionName_ 
			<< "_list.questionList[xtcc_i]->input_data=" 
			<< restore_array_quest->questionName_ << "_scope_question_t["
			<< "map_key.str()" << "];\n"
			<< endl;
		s << "}\n";
	} else if (IsAtAHigherNestLevelInTheSameBlock(this, restore_array_quest)){
		s << "/*" 
			<< questionName_ 
			<< " is at a higher nest level than "
			<< restore_array_quest->questionName_ 
			<< "*/"
			<< endl;
		s << "/*"
			<< " find where my for_bounds_stack\n"
			<< " and other question for_bounds_stack DONT match\n"
			<< " then from that point on in other question find bounds\n"
			<< " and multiply with current consolidated_for_loop_index\n"
			<< " and save all these to the question scope map\n"
			<< "*/\n"
			<< endl;
		s << "for(int xtcc_i=0; xtcc_i<";
		vector <AbstractExpression * > e_stack;
		int i1=0;
		for(i1=0; i1<restore_array_quest->for_bounds_stack.size()
				&& restore_array_quest->for_bounds_stack[i1]
					== for_bounds_stack[i1]
				; ++i1){
			e_stack.push_back(restore_array_quest->for_bounds_stack[i1]);
		}
		s << PrintConsolidatedForLoopIndex(e_stack) 
			<< "*";
		for(; i1<restore_array_quest->for_bounds_stack.size(); ++i1) {
			BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
					restore_array_quest->for_bounds_stack[i1]);
			if(bin_expr_ptr){
				AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
				ExpressionCompiledCode expr_code;
				rhs->PrintExpressionCode(expr_code); 
				s << expr_code.code_bef_expr.str() /* should be empty */
					<< expr_code.code_expr.str();
				if(i1<restore_array_quest->for_bounds_stack.size()-1) {
					s << "*";
				}
			} else {
				print_err(compiler_code_generation_error
					, "for loop index condition is not a binary expression" 
					, 0, __LINE__, __FILE__);
			}
		}
		s << ";++xtcc_i){\n"
			<< "ostringstream map_key;\n"
			<< "map_key << \"" << questionName_ << "\"" 
			<< " << " 
			<< "\"_\" << xtcc_i << \"$\" << " 
			//<< consolidated_for_loop_index_stack.back()
			<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< ";" << endl
			<< restore_array_quest->questionName_ 
			<< "_list.questionList[xtcc_i]->input_data=" 
			<< restore_array_quest->questionName_ << "_scope_question_t["
			<< "map_key.str()" << "];\n"
			<< endl;
		s << "}\n";
	} else if (IsAtADeeperNestLevelInTheSameBlock(this, restore_array_quest)){
		s << "/*" 
			<< questionName_ 
			<< " is at a deeper nest level than "
			<< restore_array_quest->questionName_ 
			<< "*/"
			<< endl;
		s << "for (int xtcc_i=0; xtcc_i < "
			<< PrintConsolidatedForLoopIndex(restore_array_quest->for_bounds_stack)
			<< "; ++xtcc_i){\n"
			<< "ostringstream map_key;\n"
			<< "map_key << \"" << questionName_ << "\"" 
			<< " << " 
			<< "\"_\" << xtcc_i << \"$\" << " 
			<< restore_array_quest->enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< ";" << endl
			<< restore_array_quest->questionName_ << "_list.questionList[xtcc_i]->input_data=" 
			<< restore_array_quest->questionName_ << "_scope_question_t["
			<< "map_key.str()" << "];\n"
			<< endl;
		s << "}\n";
	} else {
		print_err(compiler_code_generation_error
		, "unhandled case in compiler ... exiting code generation" 
		, 0, __LINE__, __FILE__);
		cerr << "questionName_:" 
			<< questionName_
			<< ", restore_array_quest->questionName_" 
			<< restore_array_quest->questionName_ 
			<< endl;
		{
			vector<AbstractQuestion*> & questions_in_block = 
				enclosingCompoundStatement_->questionsInBlock_;
			cerr << "/* questionsInBlock_: quest_loc "
				<< questionName_ << ":";
			for(int i=0; i<questions_in_block.size(); ++i){
				cerr << questions_in_block[i]->questionName_ << " ";
			}
			cerr << " */\n"; 
		}
		{
			vector<AbstractQuestion*> & questions_in_block = 
				restore_array_quest->enclosingCompoundStatement_->questionsInBlock_;
			cerr << "/* questionsInBlock_: restore_array_quest "
				<< restore_array_quest->questionName_ << ":";
			for(int i=0; i<questions_in_block.size(); ++i){
				cerr << questions_in_block[i]->questionName_ << " ";
			}
			cerr << " */\n"; 
		}
		
		exit(1);
	}

	s << "/* EXIT AbstractQuestion::PrintRestoreArrayQuestion */\n";
	return s.str();
}

string AbstractQuestion::PrintSaveArrayQuestion(ActiveVariableInfo * av_info)
{
	ostringstream s;
	s << "/* ENTER PrintSaveArrayQuestion " 
		<< av_info->name_ 
		<< " at location: " << questionName_
		<< "*/\n";
	if (enclosingCompoundStatement_){
		vector<AbstractQuestion*> & questions_in_block = 
			enclosingCompoundStatement_->questionsInBlock_;
		s << "/* questionsInBlock_: ";
		for(int i=0; i<questions_in_block.size(); ++i){
			s << questions_in_block[i]->questionName_ << " ";
		}
		s << " */\n"; 
	} else {
		ostringstream err_msg ;
		err_msg << " enclosingCompoundStatement_== 0 ... exiting \n";
		print_err(compiler_internal_error, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
	}

	AbstractQuestion * save_array_quest = 0;
	for(int i=0; i< qscript_parser::question_list.size(); ++i){
		if( qscript_parser::question_list[i]->questionName_
			== av_info->name_){
			save_array_quest=qscript_parser::question_list[i];
			break;
		}
	}
	if(save_array_quest==0){
		string err_msg = "Could not find " 
			+ av_info->name_ 
			+ " in question list while generating restore array code"
			+ " PrintSaveArrayQuestion... exiting\n";
		print_err(compiler_internal_error, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
		exit(1);
	}
	if(IsInTheSameScopeAndLevel(this, save_array_quest)){
		s << "/*" 
			<< questionName_ << " and "
			<< save_array_quest->questionName_ 
			<< " :are at the same scope and level */"
			<< endl;
		s << "for(int xtcc_i=0; xtcc_i<";
		s << save_array_quest->enclosingCompoundStatement_
			->ConsolidatedForLoopIndexStack_.back();
		s << ";++xtcc_i){\n";
		s<< "ostringstream map_key;\n"
			<< "map_key << \"" << questionName_ << "\"" 
			<< " << " 
			<< "\"_\" << xtcc_i << \"$\" << " 
			<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< ";" << endl
			<< save_array_quest->questionName_ << "_scope_question_t["
			<< "map_key.str()" << "]="
			<< save_array_quest->questionName_ << "_list.questionList[xtcc_i]->input_data;\n" 
			<< endl;
		s << "}\n";

	} else if (NotInTheSameBlock(this, save_array_quest)){
		s << "/*" 
			<< questionName_ << " and "
			<< save_array_quest->questionName_ 
			<< " :belong to different blocks "
			<< "*/"
			<< endl;
		s << "for(int xtcc_i=0; xtcc_i<";
		for(int i1=0; i1<save_array_quest->for_bounds_stack.size(); ++i1) {
			BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
					save_array_quest->for_bounds_stack[i1]);
			if(bin_expr_ptr){
				AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
				ExpressionCompiledCode expr_code;
				rhs->PrintExpressionCode(expr_code); 
				s << expr_code.code_bef_expr.str() /* should be empty */
					<< expr_code.code_expr.str();
				if(i1<save_array_quest->for_bounds_stack.size()-1) {
					s << "*";
				}
			} else {
				print_err(compiler_code_generation_error
					, "for loop index condition is not a binary expression" 
					, 0, __LINE__, __FILE__);
			}
		}
		s << ";++xtcc_i){\n"
			<< "ostringstream map_key;\n"
			<< "map_key << \"" << questionName_ << "\"" 
			<< " << " 
			<< "\"_\" << xtcc_i << \"$\" << " 
			//<< consolidated_for_loop_index_stack.back()
			<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< ";" << endl
			<< save_array_quest->questionName_ << "_scope_question_t["
			<< "map_key.str()" << "]="
			<< save_array_quest->questionName_ << "_list.questionList[xtcc_i]->input_data;\n" 
			<< endl;
		s << "}\n";
	} else if (IsAtAHigherNestLevelInTheSameBlock(this, save_array_quest)){
		s << "/*" 
			<< questionName_ 
			<< " is at a higher nest level than "
			<< save_array_quest->questionName_ 
			<< "*/"
			<< endl;
		s << "/*"
			<< " find where my for_bounds_stack\n"
			<< " and other question for_bounds_stack DONT match\n"
			<< " then from that point on in other question find bounds\n"
			<< " and multiply with current consolidated_for_loop_index\n"
			<< " and save all these to the question scope map\n"
			<< "*/\n"
			<< endl;
		s << "for(int xtcc_i=0; xtcc_i<";
		vector <AbstractExpression * > e_stack;
		int i1=0;
		for(i1=0; i1<save_array_quest->for_bounds_stack.size()
				&& save_array_quest->for_bounds_stack[i1]
					== for_bounds_stack[i1]
				; ++i1){
			e_stack.push_back(save_array_quest->for_bounds_stack[i1]);
		}
		s << PrintConsolidatedForLoopIndex(e_stack) 
			<< "*";
		for(; i1<save_array_quest->for_bounds_stack.size(); ++i1) {
			BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
					save_array_quest->for_bounds_stack[i1]);
			if(bin_expr_ptr){
				AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
				ExpressionCompiledCode expr_code;
				rhs->PrintExpressionCode(expr_code); 
				s << expr_code.code_bef_expr.str() /* should be empty */
					<< expr_code.code_expr.str();
				if(i1<save_array_quest->for_bounds_stack.size()-1) {
					s << "*";
				}
			} else {
				print_err(compiler_code_generation_error
					, "for loop index condition is not a binary expression" 
					, 0, __LINE__, __FILE__);
			}
		}
		s << ";++xtcc_i){\n"
			<< "ostringstream map_key;\n"
			<< "map_key << \"" << questionName_ << "\"" 
			<< " << " 
			<< "\"_\" << xtcc_i << \"$\" << " 
			//<< consolidated_for_loop_index_stack.back()
			<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< ";" << endl
			<< save_array_quest->questionName_ << "_scope_question_t["
			<< "map_key.str()" << "]="
			<< save_array_quest->questionName_ << "_list.questionList[xtcc_i]->input_data;\n" 
			<< endl;
		s << "}\n";
	} else if (IsAtADeeperNestLevelInTheSameBlock(this, save_array_quest)){
		s << "/*" 
			<< questionName_ 
			<< " is at a deeper nest level than "
			<< save_array_quest->questionName_ 
			<< "*/"
			<< endl;
		s << "for (int xtcc_i=0; xtcc_i < "
			<< PrintConsolidatedForLoopIndex(save_array_quest->for_bounds_stack)
			<< "; ++xtcc_i){\n"
			<< "ostringstream map_key;\n"
			<< "map_key << \"" << questionName_ << "\"" 
			<< " << " 
			<< "\"_\" << xtcc_i << \"$\" << " 
			<< save_array_quest->enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< ";" << endl
			<< save_array_quest->questionName_ << "_scope_question_t["
			<< "map_key.str()" << "]="
			<< save_array_quest->questionName_ << "_list.questionList[xtcc_i]->input_data;\n" 
			<< endl;
		s << "}\n";
	} else {
		print_err(compiler_code_generation_error
		, "unhandled case in compiler ... exiting code generation" 
		, 0, __LINE__, __FILE__);
		cerr << "questionName_:" 
			<< questionName_
			<< ", save_array_quest->questionName_" 
			<< save_array_quest->questionName_ 
			<< endl;
		{
			vector<AbstractQuestion*> & questions_in_block = 
				enclosingCompoundStatement_->questionsInBlock_;
			cerr << "/* questionsInBlock_: quest_loc "
				<< questionName_ << ":";
			for(int i=0; i<questions_in_block.size(); ++i){
				cerr << questions_in_block[i]->questionName_ << " ";
			}
			cerr << " */\n"; 
		}
		{
			vector<AbstractQuestion*> & questions_in_block = 
				save_array_quest->enclosingCompoundStatement_->questionsInBlock_;
			cerr << "/* questionsInBlock_: save_array_quest "
				<< save_array_quest->questionName_ << ":";
			for(int i=0; i<questions_in_block.size(); ++i){
				cerr << questions_in_block[i]->questionName_ << " ";
			}
			cerr << " */\n"; 
		}
		
		exit(1);
	}

	s << "/* EXIT PrintSaveArrayQuestion */\n";
	return s.str();

}

void AbstractQuestion::SetupSimpleQuestionSave(StatementCompiledCode &code)
{
	ostringstream &s(code.program_code);
	s << "/* AbstractQuestion::SetupSimpleQuestionSave */\n";
	for(int i=0; i<activeVarInfo_.size(); ++i){
		switch(activeVarInfo_[i]->type_){
		case INT8_TYPE:
		case INT16_TYPE:	
		case INT32_TYPE:	
		case FLOAT_TYPE:
		case DOUBLE_TYPE:
		case QUESTION_TYPE:
			s << GetRestoreVariableContainerName(activeVarInfo_[i], questionName_)
				<< "=" 
				<< GetRestoreVariableName(activeVarInfo_[i])
				<< ";\n"
				;
			break;
		case QUESTION_ARR_TYPE:
			s << PrintSaveArrayQuestion(activeVarInfo_[i]);
			break;
		default:
			string err_msg = "unhandled type in SetupSimpleQuestionRestore()";
			s << err_msg;
			print_err(compiler_internal_error, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
		}
	}
}


void AbstractQuestion::SetupArrayQuestionRestore(StatementCompiledCode &code)
{
	ostringstream &s(code.program_code);
	s << "/* ENTER AbstractQuestion::SetupArrayQuestionRestore */\n";
	PrintRestoreMyPreviousIterationsData(code);
	int temp_map_key_no=GetTempMapKeyNumber();
	s << "ostringstream map_key_" << temp_map_key_no << ";\n";
	for(int i=0; i<activeVarInfo_.size(); ++i){
		switch(activeVarInfo_[i]->type_){
		case INT8_TYPE:
		case INT16_TYPE:	
		case INT32_TYPE:	
		case FLOAT_TYPE:
		case DOUBLE_TYPE:
		case QUESTION_TYPE:{

				
			ostringstream map_key;
			map_key<< "map_key_" << temp_map_key_no ;
			s << map_key.str() << "<< \"" << activeVarInfo_[i]->name_ << "\" << \"_\" << " 
				<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
				<< ";\n";
			s << GetRestoreVariableName(activeVarInfo_[i]) 
				<< "=" 
				<< GetRestoreVariableContainerNameArray(activeVarInfo_[i]
						, questionName_, map_key.str())
				<< ";\n" ;
			}
			break;
		case QUESTION_ARR_TYPE:
			s << PrintRestoreArrayQuestion(activeVarInfo_[i]);
			break;
		default:
			string err_msg = "unhandled type in SetupArrayQuestionRestore()";
			s << err_msg;
			print_err(compiler_internal_error, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
		}
	}
	RestoreQuestionsInMyBlockThatAreAfterMe(code);
	s << "/* EXIT AbstractQuestion::SetupArrayQuestionRestore */\n";
}

void AbstractQuestion::PrintSaveMyPreviousIterationsData(StatementCompiledCode &code)
{
	ostringstream &s(code.program_code);
	s << "/* ENTER:AbstractQuestion::PrintSaveMyPreviousIterationsData */" << endl;
	s << "for(int xtcc_i=0; xtcc_i<" 
		//<< consolidated_for_loop_index_stack.back() << "-1"
		<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back() << "-1"
		<< ";++xtcc_i){\n";
	s << "ostringstream temp_map_key;\n";
	s << "temp_map_key << \"" << questionName_ << "\" << \"_\" << " 
		<< "xtcc_i" 
		<< " << \"$\" << " 
		//<< consolidated_for_loop_index_stack.back() 
		<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back() 
		<< ";\n"
		<< endl;
	//s << "temp_map_key2 << " << questionName_ << " << \"_\" << " 
	//	<< "xtcc_i" 
	//	<< ";\n";
	s << questionName_ << "_scope_question_t[ temp_map_key.str()"
		<< "]="
		<< questionName_ << "_list.questionList[xtcc_i]->input_data;\n"
		;
	s << "}\n";
		
	s << "/* EXIT:AbstractQuestion::PrintSaveMyPreviousIterationsData */" << endl;
}


void AbstractQuestion::SetupArrayQuestionSave(StatementCompiledCode &code)
{
	ostringstream &s(code.program_code);
	s << "/* ENTER AbstractQuestion::SetupArrayQuestionSave */\n";
	PrintSaveMyPreviousIterationsData(code);
	int temp_map_key_no=GetTempMapKeyNumber();
	s << "ostringstream map_key_" << temp_map_key_no << ";\n";
	for(int i=0; i<activeVarInfo_.size(); ++i){
		switch(activeVarInfo_[i]->type_){
		case INT8_TYPE:
		case INT16_TYPE:	
		case INT32_TYPE:	
		case FLOAT_TYPE:
		case DOUBLE_TYPE:
		case QUESTION_TYPE:{
			ostringstream map_key;
			map_key<< "map_key_" << temp_map_key_no ;
			s << map_key.str() << "<< \"" << activeVarInfo_[i]->name_ << "\" << \"_\" << " 
				<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back() 
				<< ";\n";
			s << GetRestoreVariableContainerNameArray(activeVarInfo_[i], questionName_, map_key.str())
				<< "=" 
				<< GetRestoreVariableName(activeVarInfo_[i])
				<< ";\n"
				;
			}
			break;
		case QUESTION_ARR_TYPE:
			s << PrintSaveArrayQuestion(activeVarInfo_[i]);
			break;
		default:
			string err_msg = "unhandled type in SetupArrayQuestionSave()";
			s << err_msg;
			print_err(compiler_internal_error, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
		}
	}
	SaveQuestionsInMyBlockThatAreAfterMe(code);
	s << "/* EXIT AbstractQuestion::SetupArrayQuestionSave */\n";
}

string GetRestoreVariableContainerNameArray(ActiveVariableInfo * av_info, string & questionName_, string map_key)
{
	ostringstream s;
	switch(av_info->type_){
	case INT8_TYPE:
		s << questionName_ << "_scope_int8_t[" << map_key << ".str()" << "]" ;
		break;
	case INT16_TYPE:	
		s << questionName_ << "_scope_int16_t[" << map_key << ".str()" << "]";
		break;
	case INT32_TYPE:	
		s << questionName_ << "_scope_int32_t[" << map_key << ".str()" << "]";
		break;
	case FLOAT_TYPE:
		s << questionName_ << "_scope_float_t[" << map_key << ".str()" << "]";
		break;
	case DOUBLE_TYPE:
		s << questionName_ << "_scope_double_t[" << map_key << ".str()" << "]";
		break;
	case QUESTION_TYPE:
		s << av_info->name_ << "_scope_question_t"<<  "[" << map_key << ".str()" << "]" ;
		break;
		/*
	case QUESTION_ARR_TYPE:
		s << av_info->name_ << "_scope_question_t"<<  "[\"" << questionName_ << "\"]" << endl;
		break;
		*/
	default: {
			string err_msg = "unhandled type in print_pop_stack";
			s << err_msg;
			print_err(compiler_sem_err, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
		}
	}
	return s.str();
}

bool AbstractQuestion::QuestionIsInMyBlock(AbstractQuestion *q)
{
	vector<AbstractQuestion*> & questions_in_block = 
		enclosingCompoundStatement_->questionsInBlock_;
	for(int i=0; i<questions_in_block.size(); ++i){
		if(q==questions_in_block[i]){
			return true;
		}
	}
	return false;
}

bool IsInTheSameScopeAndLevel(AbstractQuestion *q1, AbstractQuestion * q2)
{
	return q1->QuestionIsInMyBlock(q2) && q2->QuestionIsInMyBlock(q1);
}


bool NotInTheSameBlock(AbstractQuestion *q1, AbstractQuestion * q2)
{
	return (!q1->QuestionIsInMyBlock(q2)) && (!q2->QuestionIsInMyBlock(q1));
}

bool IsAtAHigherNestLevelInTheSameBlock(AbstractQuestion *q1, AbstractQuestion *q2)
{
	return (q1->QuestionIsInMyBlock(q2)) && (!q2->QuestionIsInMyBlock(q1));
}

bool IsAtADeeperNestLevelInTheSameBlock(AbstractQuestion *q1, AbstractQuestion *q2)
{
	//cerr << "IsAtADeeperNestLevelInTheSameBlock(q1=" << q1->questionName_
	//	<< ", q2=" << q2->questionName_ << endl;
	//cerr << "(q1->QuestionIsInMyBlock(q2)):" << (q1->QuestionIsInMyBlock(q2))
	//	<< endl;
	//cerr << "q2->QuestionIsInMyBlock(q1):" << q2->QuestionIsInMyBlock(q1)
	//	<< endl;
	return (!q1->QuestionIsInMyBlock(q2)) && (q2->QuestionIsInMyBlock(q1));
}


void AbstractQuestion::SaveQuestionsInMyBlockThatAreAfterMe(StatementCompiledCode & code)
{
	ostringstream &s(code.program_code);
	s << "/* ENTER AbstractQuestion::SaveQuestionsInMyBlockThatAreAfterMe */" << endl;
	int pos_start_of_for_loop=-1;
	for(int i=0; i<enclosingCompoundStatement_->nestedCompoundStatementStack_.size(); ++i){
		if(enclosingCompoundStatement_->nestedCompoundStatementStack_[i]->flagIsAForBody_){
			pos_start_of_for_loop=i;
			break;
		}
	}

	if(pos_start_of_for_loop==-1){
		ostringstream err_msg;
		err_msg << "Compiler internal error: cant find start of for loop in nestedCompoundStatementStack_";
		print_err(compiler_internal_error, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
	}

	vector<AbstractQuestion*> & questions_in_block=  enclosingCompoundStatement_->
		nestedCompoundStatementStack_[pos_start_of_for_loop]->questionsInBlock_;
	s << "/* questions in my block ("
		<< questionName_ << "):";
	for(int i=0; i<questions_in_block.size(); ++i){
		s << questions_in_block[i]->questionName_ << ",";
	}
	s << "*/" << endl;
	vector<AbstractQuestion*>::iterator my_loc = 
		find(questions_in_block.begin(), questions_in_block.end(), this); 
	if(my_loc==questions_in_block.end()){
		ostringstream err_msg;
		err_msg << "unable to find self in block ... exiting\n";
		print_err(compiler_internal_error, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		exit(1);
	}
	if(my_loc+1==questions_in_block.end()){
		s << "/* I=" << questionName_ << " is the last question in in block "
			<< " nothing to do */"<< endl;
	} else {
		for( vector<AbstractQuestion*>::iterator it = my_loc+1;
				it!=questions_in_block.end(); ++it){
			AbstractQuestion *quest_loc=this, *save_array_quest=*it;

			if(IsInTheSameScopeAndLevel(quest_loc, save_array_quest)){
				s << "/*" 
					<< quest_loc->questionName_ << " and "
					<< save_array_quest->questionName_ 
					<< " :are at the same scope and level */"
					<< endl;
				cerr << "Need to revisit this to check if condition should be "
					<< "xtcc_i\"<=\" or \"<\" and other similar places  " 
					<< __LINE__ << "," << __FILE__ 
					<< endl;
				s << "for(int xtcc_i=0; xtcc_i<";
				s << save_array_quest->enclosingCompoundStatement_
					->ConsolidatedForLoopIndexStack_.back();
				s << ";++xtcc_i){\n";
				s<< "ostringstream map_key;\n"
					<< "map_key << \"" << questionName_ << "\"" 
					<< " << " 
					<< "\"_\" << xtcc_i << \"$\" << " 
					<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
					<< ";" << endl
					<< save_array_quest->questionName_ << "_scope_question_t["
					<< "map_key.str()" << "]="
					<< save_array_quest->questionName_ 
					<< "_list.questionList[xtcc_i]->input_data;\n"
					<< endl;
				s << "}\n";

			} else if (NotInTheSameBlock(quest_loc, save_array_quest)){
				s << "/*" 
					<< quest_loc->questionName_ << " and "
					<< save_array_quest->questionName_ 
					<< " :belong to different blocks "
					<< "*/"
					<< endl;
				s << "for(int xtcc_i=0; xtcc_i<";
				for(int i1=0; i1<save_array_quest->for_bounds_stack.size(); ++i1) {
					BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
							save_array_quest->for_bounds_stack[i1]);
					if(bin_expr_ptr){
						AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
 						ExpressionCompiledCode expr_code;
						rhs->PrintExpressionCode(expr_code); 
						s << expr_code.code_bef_expr.str() /* should be empty */
							<< expr_code.code_expr.str();
						if(i1<save_array_quest->for_bounds_stack.size()-1) {
							s << "*";
						}
					} else {
						print_err(compiler_code_generation_error
							, "for loop index condition is not a binary expression" 
							, 0, __LINE__, __FILE__);
					}
				}
				s << ";++xtcc_i){\n"
					<< "ostringstream map_key;\n"
					<< "map_key << \"" << questionName_ << "\"" 
					<< " << " 
					<< "\"_\" << xtcc_i << \"$\" << " 
					//<< consolidated_for_loop_index_stack.back()
					<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
					<< ";" << endl
					<< save_array_quest->questionName_ << "_scope_question_t["
					<< "map_key.str()" << "]="
					<< save_array_quest->questionName_ 
					<< "_list.questionList[xtcc_i]->input_data;\n"
					<< endl;
				s << "}\n";
			} else if (IsAtAHigherNestLevelInTheSameBlock(quest_loc, save_array_quest)){
				s << "/*" 
					<< quest_loc->questionName_ 
					<< " is at a higher nest level than "
					<< save_array_quest->questionName_ 
					<< "*/"
					<< endl;
				s << "/*"
					<< " find where my for_bounds_stack\n"
					<< " and other question for_bounds_stack DONT match\n"
					<< " then from that point on in other question find bounds\n"
					<< " and multiply with current consolidated_for_loop_index\n"
					<< " and save all these to the question scope map\n"
					<< "*/\n"
					<< endl;
				s << "for(int xtcc_i=0; xtcc_i<";
				vector <AbstractExpression * > e_stack;
				int i1=0;
				for(i1=0; i1<save_array_quest->for_bounds_stack.size()
						&& save_array_quest->for_bounds_stack[i1]
							== for_bounds_stack[i1]
						; ++i1){
					e_stack.push_back(save_array_quest->for_bounds_stack[i1]);
				}
				s 	<< "("
					<< PrintConsolidatedForLoopIndex(e_stack) 
					<< ")"
					<< "*";
				for(; i1<save_array_quest->for_bounds_stack.size(); ++i1) {
					BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
							save_array_quest->for_bounds_stack[i1]);
					if(bin_expr_ptr){
						AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
						ExpressionCompiledCode expr_code;
						rhs->PrintExpressionCode(expr_code); 
						s << expr_code.code_bef_expr.str() /* should be empty */
							<< expr_code.code_expr.str();
						if(i1<save_array_quest->for_bounds_stack.size()-1) {
							s << "*";
						}
					} else {
						print_err(compiler_code_generation_error
							, "for loop index condition is not a binary expression" 
							, 0, __LINE__, __FILE__);
					}
				}
				s << ";++xtcc_i){\n"
					<< "ostringstream map_key;\n"
					<< "map_key << \"" << questionName_ << "\"" 
					<< " << " 
					<< "\"_\" << xtcc_i << \"$\" << " 
					//<< consolidated_for_loop_index_stack.back()
					<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
					<< ";" << endl
					<< save_array_quest->questionName_ << "_scope_question_t["
					<< "map_key.str()" << "]="
					<< save_array_quest->questionName_ 
					<< "_list.questionList[xtcc_i]->input_data;\n"
					<< endl;
				s << "}\n";

			} else if (IsAtADeeperNestLevelInTheSameBlock(quest_loc, save_array_quest)){
				s << "/*" 
					<< quest_loc->questionName_ 
					<< " is at a deeper nest level than "
					<< save_array_quest->questionName_ 
					<< "*/"
					<< endl;
				s << "for(int xtcc_i=0; xtcc_i<";
				s << save_array_quest->enclosingCompoundStatement_
					->ConsolidatedForLoopIndexStack_.back() 
					<< "-1";
				s << ";++xtcc_i){\n";
				s<< "ostringstream map_key;\n"
					<< "map_key << \"" << questionName_ << "\"" 
					<< " << " 
					<< "\"_\" << xtcc_i << \"$\" << " 
					<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
					<< ";" << endl
					<< save_array_quest->questionName_ << "_scope_question_t["
					<< "map_key.str()" << "]="
					<< save_array_quest->questionName_ 
					<< "_list.questionList[xtcc_i]->input_data;\n" 
					<< endl;
				s << "}\n";

			} else {
				print_err(compiler_code_generation_error
				, "unhandled case in compiler ... exiting code generation" 
				, 0, __LINE__, __FILE__);
				cerr << "quest_loc->questionName_:" 
					<< quest_loc->questionName_
					<< ", save_array_quest->questionName_" 
					<< save_array_quest->questionName_ 
					<< endl;
				{
					vector<AbstractQuestion*> & questions_in_block = 
						quest_loc->enclosingCompoundStatement_->questionsInBlock_;
					cerr << "/* questionsInBlock_: quest_loc "
						<< quest_loc->questionName_ << ":";
					for(int i=0; i<questions_in_block.size(); ++i){
						cerr << questions_in_block[i]->questionName_ << " ";
					}
					cerr << " */\n"; 
				}
				{
					vector<AbstractQuestion*> & questions_in_block = 
						save_array_quest->enclosingCompoundStatement_->questionsInBlock_;
					cerr << "/* questionsInBlock_: save_array_quest "
						<< save_array_quest->questionName_ << ":";
					for(int i=0; i<questions_in_block.size(); ++i){
						cerr << questions_in_block[i]->questionName_ << " ";
					}
					cerr << " */\n"; 
				}
				
				exit(1);
			}
		}
	}
	s << "/* EXIT AbstractQuestion::SaveQuestionsInMyBlockThatAreAfterMe */" << endl;
}

void AbstractQuestion::RestoreQuestionsInMyBlockThatAreAfterMe(StatementCompiledCode & code)
{
	ostringstream &s(code.program_code);
	s << "/* ENTER AbstractQuestion::RestoreQuestionsInMyBlockThatAreAfterMe */" << endl;
	int pos_start_of_for_loop=-1;
	for(int i=0; i<enclosingCompoundStatement_->nestedCompoundStatementStack_.size(); ++i){
		if(enclosingCompoundStatement_->nestedCompoundStatementStack_[i]->flagIsAForBody_){
			pos_start_of_for_loop=i;
			break;
		}
	}

	if(pos_start_of_for_loop==-1){
		ostringstream err_msg;
		err_msg << "Compiler internal error: cant find start of for loop in nestedCompoundStatementStack_";
		print_err(compiler_internal_error, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
	}

	vector<AbstractQuestion*> & questions_in_block=  enclosingCompoundStatement_->
		nestedCompoundStatementStack_[pos_start_of_for_loop]->questionsInBlock_;
	s << "/* questions in my block ("
		<< questionName_ << "):";
	for(int i=0; i<questions_in_block.size(); ++i){
		s << questions_in_block[i]->questionName_ << ",";
	}
	s << "*/" << endl;
	vector<AbstractQuestion*>::iterator my_loc = 
		find(questions_in_block.begin(), questions_in_block.end(), this); 
	if(my_loc==questions_in_block.end()){
		ostringstream err_msg;
		err_msg << "unable to find self in block ... exiting\n";
		print_err(compiler_internal_error, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		exit(1);
	}
	if(my_loc+1==questions_in_block.end()){
		s << "/* I=" << questionName_ << " is the last question in in block "
			<< " nothing to do */"<< endl;
	} else {
		for( vector<AbstractQuestion*>::iterator it = my_loc+1;
				it!=questions_in_block.end(); ++it){
			AbstractQuestion *quest_loc=this, *restore_array_quest=*it;
			if(IsInTheSameScopeAndLevel(quest_loc, restore_array_quest)){
				s << "/*" 
					<< quest_loc->questionName_ << " and "
					<< restore_array_quest->questionName_ 
					<< " :are at the same scope and level */"
					<< endl;
				cerr << "Need to revisit this to check if condition should be "
					<< "xtcc_i\"<=\" or \"<\" and other similar places  " 
					<< __LINE__ << "," << __FILE__ 
					<< endl;
				s << "for(int xtcc_i=0; xtcc_i<";
				s << restore_array_quest->enclosingCompoundStatement_
					->ConsolidatedForLoopIndexStack_.back();
				s << ";++xtcc_i){\n";
				s<< "ostringstream map_key;\n"
					<< "map_key << \"" << questionName_ << "\"" 
					<< " << " 
					<< "\"_\" << xtcc_i << \"$\" << " 
					<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
					<< ";" << endl
					<< restore_array_quest->questionName_ 
					<< "_list.questionList[xtcc_i]->input_data="
					<< restore_array_quest->questionName_ << "_scope_question_t["
					<< "map_key.str()" << "];\n"
					<< endl;
				s << "}\n";
			} else if (NotInTheSameBlock(quest_loc, restore_array_quest)){
				s << "/*" 
					<< quest_loc->questionName_ << " and "
					<< restore_array_quest->questionName_ 
					<< " :belong to different blocks "
					<< "*/"
					<< endl;
			} else if (IsAtAHigherNestLevelInTheSameBlock(quest_loc, restore_array_quest)){
				s << "/*" 
					<< quest_loc->questionName_ 
					<< " is at a higher nest level than "
					<< restore_array_quest->questionName_ 
					<< "*/"
					<< endl;
				s << "/*"
					<< " find where my for_bounds_stack\n"
					<< " and other question for_bounds_stack DONT match\n"
					<< " then from that point on in other question find bounds\n"
					<< " and multiply with current consolidated_for_loop_index\n"
					<< " and save all these to the question scope map\n"
					<< "*/\n"
					<< endl;
				s << "for(int xtcc_i=0; xtcc_i<";
				vector <AbstractExpression * > e_stack;
				int i1=0;
				for(i1=0; i1<restore_array_quest->for_bounds_stack.size()
						&& restore_array_quest->for_bounds_stack[i1]
							== for_bounds_stack[i1]
						; ++i1){
					e_stack.push_back(restore_array_quest->for_bounds_stack[i1]);
				}
				s 	<< "("
					<< PrintConsolidatedForLoopIndex(e_stack) 
					<< ")"
					<< "*";
				for(; i1<restore_array_quest->for_bounds_stack.size(); ++i1) {
					BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
							restore_array_quest->for_bounds_stack[i1]);
					if(bin_expr_ptr){
						AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
						ExpressionCompiledCode expr_code;
						rhs->PrintExpressionCode(expr_code); 
						s << expr_code.code_bef_expr.str() /* should be empty */
							<< expr_code.code_expr.str();
						if(i1<restore_array_quest->for_bounds_stack.size()-1) {
							s << "*";
						}
					} else {
						print_err(compiler_code_generation_error
							, "for loop index condition is not a binary expression" 
							, 0, __LINE__, __FILE__);
					}
				}
				s << ";++xtcc_i){\n"
					<< "ostringstream map_key;\n"
					<< "map_key << \"" << questionName_ << "\"" 
					<< " << " 
					<< "\"_\" << xtcc_i << \"$\" << " 
					//<< consolidated_for_loop_index_stack.back()
					<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
					<< ";" << endl
					<< restore_array_quest->questionName_ 
					<< "_list.questionList[xtcc_i]->input_data="
					<< restore_array_quest->questionName_ << "_scope_question_t["
					<< "map_key.str()" << "];\n"
					<< endl;
				s << "}\n";

			} else if (IsAtADeeperNestLevelInTheSameBlock(quest_loc, restore_array_quest)){
				s << "/*" 
					<< quest_loc->questionName_ 
					<< " is at a deeper nest level than "
					<< restore_array_quest->questionName_ 
					<< "*/"
					<< endl;
				s << "for(int xtcc_i=0; xtcc_i<";
				s << restore_array_quest->enclosingCompoundStatement_
					->ConsolidatedForLoopIndexStack_.back() 
					<< "-1";
				s << ";++xtcc_i){\n";
				s<< "ostringstream map_key;\n"
					<< "map_key << \"" << questionName_ << "\"" 
					<< " << " 
					<< "\"_\" << xtcc_i << \"$\" << " 
					<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
					<< ";" << endl
					<< restore_array_quest->questionName_ 
					<< "_list.questionList[xtcc_i]->input_data="
					<< restore_array_quest->questionName_ << "_scope_question_t["
					<< "map_key.str()" << "];\n"
					<< endl;
				s << "}\n";
			} else {
				print_err(compiler_code_generation_error
				, "unhandled case in compiler ... exiting code generation" 
				, 0, __LINE__, __FILE__);
				cerr << "quest_loc->questionName_:" 
					<< quest_loc->questionName_
					<< ", restore_array_quest->questionName_" 
					<< restore_array_quest->questionName_ 
					<< endl;
				{
					vector<AbstractQuestion*> & questions_in_block = 
						quest_loc->enclosingCompoundStatement_->questionsInBlock_;
					cerr << "/* questionsInBlock_: quest_loc "
						<< quest_loc->questionName_ << ":";
					for(int i=0; i<questions_in_block.size(); ++i){
						cerr << questions_in_block[i]->questionName_ << " ";
					}
					cerr << " */\n"; 
				}
				{
					vector<AbstractQuestion*> & questions_in_block = 
						restore_array_quest->enclosingCompoundStatement_->questionsInBlock_;
					cerr << "/* questionsInBlock_: restore_array_quest "
						<< restore_array_quest->questionName_ << ":";
					for(int i=0; i<questions_in_block.size(); ++i){
						cerr << questions_in_block[i]->questionName_ << " ";
					}
					cerr << " */\n"; 
				}
				exit(1);
			}
		}
	}
	s << "/* EXIT AbstractQuestion::RestoreQuestionsInMyBlockThatAreAfterMe */" << endl;
}


void AbstractQuestion::PrintRestoreMyPreviousIterationsData(StatementCompiledCode &code)
{
	ostringstream &s(code.program_code);
	s << "/* ENTER:AbstractQuestion::PrintRestoreMyPreviousIterationsData */" << endl;
	s << "for(int xtcc_i=0; xtcc_i<" 
		//<< consolidated_for_loop_index_stack.back() << "-1"
		<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back() << "-1"
		<< ";++xtcc_i){\n";
	s << "ostringstream temp_map_key;\n";
	s << "temp_map_key << \"" << questionName_ << "\" << \"_\" << " 
		<< "xtcc_i" 
		<< " << \"$\" << " 
		//<< consolidated_for_loop_index_stack.back() 
		<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back() 
		<< ";\n"
		<< endl;
	//s << "temp_map_key2 << \"" << questionName_ << "\" << \"_\" << " 
	//	<< "xtcc_i" 
	//	<< ";\n";
	s << questionName_ << "_list.questionList[xtcc_i]->input_data="
		<< questionName_ << "_scope_question_t[ temp_map_key.str()"
		<< "];\n"
		;
	s << "}\n";
		
	s << "/* EXIT:AbstractQuestion::PrintRestoreMyPreviousIterationsData */" << endl;
}
