/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/AbstractQuestion.C
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 
 *  Neil Xavier D'Souza
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

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

AbstractQuestion::AbstractQuestion(DataType l_type, int l_no
		, string l_name, string l_text
		, QuestionType l_q_type, int l_no_mpn, DataType l_dt
		, vector<AbstractExpression*> & l_for_bounds_stack
	): 
	AbstractStatement(l_type, l_no)
	, questionName_(l_name), questionText_(l_text), q_type(l_q_type)
	, no_mpn(l_no_mpn), dt(l_dt)
	, for_bounds_stack(l_for_bounds_stack)
	, isAnswered_(false), isModified_(false)
{
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
{
}


AbstractQuestion::AbstractQuestion(DataType l_type, int l_no, string l_name
		, string l_text
		, QuestionType l_q_type, int l_no_mpn, DataType l_dt
		, const vector<int>& l_loop_index_values
	): 
	AbstractStatement(l_type, l_no), questionName_(l_name)
	, questionText_(l_text), q_type(l_q_type) 
	, no_mpn(l_no_mpn), dt(l_dt) , for_bounds_stack(0)
	, loop_index_values(l_loop_index_values)
	, isAnswered_(false), isModified_(false)
{
	//for(int i=0; i<l_loop_index_values.size(); ++i){
	//	cout << "l_loop_index_values " << i << ":" << l_loop_index_values[i] << endl;
	//}
}


void AbstractQuestion::PrintEvalAndNavigateCode(ostringstream & program_code)
{
	program_code << "if (!" 
		<< questionName_.c_str() << "->isAnswered_ ||" << endl
		<< "stopAtNextQuestion ||" << endl
		<< "jumpToQuestion == \"" << questionName_.c_str() << "\" ){ " << endl;
	program_code << "label_eval_" << questionName_.c_str() << ":\n"
		<< "\t\t" 
		<< questionName_.c_str() 
		<< "->eval();\n" ;
	// hard coded for now
	program_code << "if (user_navigation==NAVIGATE_PREVIOUS){\n\
		AbstractQuestion * target_question = ComputePreviousQuestion(" << questionName_.c_str() << ");\n\
		if(target_question==0)\n\
		goto label_eval_" << questionName_.c_str() << ";\n\
		else {\n\
		jumpToQuestion = target_question->questionName_;\n\
		cout << \"target question: \" << jumpToQuestion;\n\
		back_jump=true;\n\
		user_navigation=NOT_SET;\n\
		goto start_of_questions;\n}\n}\n" ;
	program_code << "else if (user_navigation==NAVIGATE_NEXT){\n\
		stopAtNextQuestion=true;\n\
		user_navigation=NOT_SET;\n}\n";
	program_code << "}" << endl;
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
			prompt="Single coded AbstractQuestion - please enter only 1 code:" ;
			invalid_code=true;
			data.clear();
		} else if (q_type==mpn && data.size() > no_mpn){
			prompt="Multi coded AbstractQuestion codes exceed no of max codes:  " ;
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


RangeQuestion::RangeQuestion(DataType this_stmt_type, int line_number,
	string l_name, string l_q_text,
	QuestionType l_q_type, int l_no_mpn, DataType l_dt,
	XtccSet& l_r_data
	, vector<AbstractExpression*> & l_for_bounds_stack
	): 
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text
		, l_q_type, l_no_mpn, l_dt , l_for_bounds_stack
		)
{
	r_data = new XtccSet(l_r_data);
}

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

RangeQuestion::RangeQuestion(DataType this_stmt_type, int line_number,
	string l_name, string l_q_text,
	QuestionType l_q_type, int l_no_mpn, DataType l_dt,
	XtccSet& l_r_data
	, const vector<int> & l_loop_index_values
	): 
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt, l_loop_index_values
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
	/*
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
			prompt="Single coded AbstractQuestion - please enter only 1 code:" ;
			invalid_code=true;
			data.clear();
		} else if (q_type==mpn && data.size() > no_mpn){
			prompt="Multi coded AbstractQuestion codes exceed no of max codes:  " ;
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
	*/
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

	/*
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
			invalid_code=!IsValid(data[i]);
			if(invalid_code==true){
				prompt = "Input contained some invalid data\nRe-enter Data\n";
				data.clear();
				break;
			}
		}
		if(invalid_code)
			continue;
		if(q_type==spn && data.size()>1) {
			prompt="Single coded AbstractQuestion - please enter only 1 code:" ;
			invalid_code=true;
			data.clear();
		} else if (q_type==mpn && data.size() > no_mpn){
			prompt="Multi coded AbstractQuestion codes exceed no of max codes:  " ;
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
	*/
	AbstractQuestion::GetDataFromUser();
	
}

void RangeQuestion::GenerateCodeSingleQuestion( ostringstream & quest_defns
		, ostringstream& program_code)
{
	AbstractQuestion::PrintSetupBackJump(quest_defns, program_code);
	
	static int xtcc_set_counter=0;
	const int BUF_SIZE=100;
	char xtcc_set_name[BUF_SIZE];
	sprintf(xtcc_set_name, "xs_%d", xtcc_set_counter++);
	quest_defns  << "XtccSet " << xtcc_set_name << ";" << endl;
	for(	set<int>::iterator it=r_data->indiv.begin(); 
			it!=r_data->indiv.end(); ++it){
		quest_defns << xtcc_set_name << ".indiv.insert(" << *it 
			<< ");" << endl;
	}
	for(unsigned int i=0; i<r_data->range.size(); ++i){
		quest_defns << xtcc_set_name 
			<< ".range.push_back(pair<int,int>("
			<< r_data->range[i].first << "," 
			<< r_data->range[i].second
			<< "));" << endl;
	}
	string q_type_str;
	print_q_type(q_type_str);

	string datatype_str;
	print_data_type(datatype_str);


	quest_defns << "RangeQuestion * " << questionName_.c_str() 
		<< " = new RangeQuestion(QUESTION_TYPE, "
		<< lineNo_ << "," 
		<< "string( \"" << questionName_.c_str() << "\")" << "," 
		<< "string(\" " << questionText_.c_str() << "\")" << ","
		<< q_type_str.c_str() << ","
		<< no_mpn << ","
		<< datatype_str.c_str() << ","
		<< xtcc_set_name 
		<<  ( (for_bounds_stack.size() > 0 ) ? ", stack_of_loop_indices " : "" )
		<< "/* " << for_bounds_stack.size() << "*/"
		<< ");\n";

	quest_defns << "question_list.push_back(" << questionName_.c_str() 
		<< ");\n";

	if(for_bounds_stack.size()==0){
		AbstractQuestion::PrintEvalAndNavigateCode(program_code);
	}else {
		AbstractQuestion::PrintEvalArrayQuestion(
				quest_defns, program_code);
	}
	/*
	if(next_){
		next_->GenerateCode(quest_defns, program_code);
	}*/

}

void RangeQuestion::GenerateCode( ostringstream & quest_defns
		, ostringstream& program_code)
{
	if(for_bounds_stack.size()==0){
		GenerateCodeSingleQuestion(quest_defns, program_code);
	} else {
		//quest_defns << "vector <AbstractQuestion*> " << questionName_ << "_list;" << endl;
		//----------------------------------------
		string temp_array_bounds_name = "list_" + questionName_ + "_array_bounds";
		quest_defns << "vector<int> " << temp_array_bounds_name 
			<< "(" << for_bounds_stack.size() << ")"
			<< ";" << endl;
		for(int i=0; i< for_bounds_stack.size(); ++i){
			ostringstream array_bounds;
			BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(for_bounds_stack[i]);
			if(bin_expr_ptr){
				AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
				rhs->PrintExpressionCode(array_bounds, array_bounds);
				//int bounds = atoi(array_bounds.str().c_str());
				quest_defns << temp_array_bounds_name 
					<< "[" << i << "]=" << array_bounds.str() << ";\n";
				array_bounds.clear();

			} else {
				for_bounds_stack[i]->PrintExpressionCode(array_bounds, array_bounds);
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
		for(int i=0; i< for_bounds_stack.size(); ++i){
			quest_defns << "for(int ";
			BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(for_bounds_stack[i]);
			if(bin_expr_ptr){
				AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
				AbstractExpression * lhs = bin_expr_ptr->leftOperand_;
				lhs->PrintExpressionCode(quest_defns, quest_defns);
				quest_defns << "=0;";
				for_bounds_stack[i]->PrintExpressionCode(quest_defns, quest_defns);
				quest_defns << "; ++";
				lhs->PrintExpressionCode(quest_defns, quest_defns);
				quest_defns <<	"){" << endl;
				if(i==0){
					quest_defns << "vector<int> stack_of_loop_indices;\n";
						// << "(" << for_bounds_stack.size() << ");\n";
				}
				quest_defns << "stack_of_loop_indices.push_back(";
				lhs->PrintExpressionCode(quest_defns, quest_defns);
				quest_defns << ");\n";
			} else {
				for_bounds_stack[i]->PrintExpressionCode(quest_defns, quest_defns);
				print_err(compiler_sem_err
					, "for loop index condition is not a binary expression" 
					, 0, __LINE__, __FILE__);
			}

			// quest_defns is passed twice
			// becaues we want the AbstractExpression to appear in the for
			// loop in the questions section of the code
		}
		
		GenerateCodeSingleQuestion(quest_defns, program_code);
		quest_defns << questionName_ << "_list"
			<< ".questionList.push_back(" << questionName_ << ");"
			<< endl;
		for(int i=0; i< for_bounds_stack.size(); ++i){
			quest_defns << "stack_of_loop_indices.pop_back();\n";
			quest_defns << "}" << endl;
		}
	}
	if(next_){
		next_->GenerateCode(quest_defns, program_code);
	}
}

//extern vector <scope*> active_scope_list;
void NamedStubQuestion::GenerateCodeSingleQuestion( 
		ostringstream & quest_defns
		, ostringstream& program_code)
{
	AbstractQuestion::PrintSetupBackJump(quest_defns, program_code);

	string q_type_str;
	print_q_type(q_type_str);

	string datatype_str;
	print_data_type(datatype_str);
	quest_defns << "// NamedStubQuestion::GenerateCode() : to be implemented" << endl;
	quest_defns << "NamedStubQuestion * " << questionName_.c_str() << " = new NamedStubQuestion(QUESTION_TYPE, "
		<< lineNo_ << "," 
		<< "string( \"" << questionName_.c_str() << "\")" << "," 
		<< "string(\" " << questionText_.c_str() << "\")" << ","
		<< q_type_str.c_str() << ","
		<< no_mpn << ","
		<< datatype_str.c_str() << ",&"
		<< nr_ptr->name  
		<<  ( (for_bounds_stack.size() > 0 ) ? ", stack_of_loop_indices " : "" )
		<< "/* " << for_bounds_stack.size() << "*/"
		<< ");\n";
	quest_defns << "question_list.push_back(" << questionName_.c_str() << ");\n";
	//program_code << "\t\t" << questionName_.c_str() << "->eval();\n" ;

	if(for_bounds_stack.size()==0){
		AbstractQuestion::PrintEvalAndNavigateCode(program_code);
	}  else {
		AbstractQuestion::PrintEvalArrayQuestion(
				quest_defns, program_code);
	}

}

void NamedStubQuestion::GenerateCode( ostringstream & quest_defns, 
		ostringstream& program_code)
{
	if(for_bounds_stack.size()==0){
		GenerateCodeSingleQuestion(quest_defns, program_code);
	}  else {
		//----------------------------------------
		string temp_array_bounds_name = "list_" + questionName_ + "_array_bounds";
		quest_defns << "vector<int> " << temp_array_bounds_name 
			<< "(" << for_bounds_stack.size() << ")"
			<< ";" << endl;
		for(int i=0; i< for_bounds_stack.size(); ++i){
			ostringstream array_bounds;
			BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(for_bounds_stack[i]);
			if(bin_expr_ptr){
				AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
				rhs->PrintExpressionCode(array_bounds, array_bounds);
				//int bounds = atoi(array_bounds.str().c_str());
				quest_defns << temp_array_bounds_name 
					<< "[" << i << "]=" << array_bounds.str() << ";\n";
				//array_bounds.clear();
			} else {
				for_bounds_stack[i]->PrintExpressionCode(array_bounds, array_bounds);
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
		for(int i=0; i< for_bounds_stack.size(); ++i){
			quest_defns << "for(int ";
			BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(for_bounds_stack[i]);
			if(bin_expr_ptr){
				AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
				AbstractExpression * lhs = bin_expr_ptr->leftOperand_;
				lhs->PrintExpressionCode(quest_defns, quest_defns);
				quest_defns << "=0;";
				for_bounds_stack[i]->PrintExpressionCode(quest_defns, quest_defns);
				quest_defns << "; ++";
				lhs->PrintExpressionCode(quest_defns, quest_defns);
				quest_defns <<	"){" << endl;
				if(i==0){
					quest_defns << "vector<int> stack_of_loop_indices; \n";
						//<< "(" <<  for_bounds_stack.size() << ");\n";
				}
				quest_defns << "stack_of_loop_indices.push_back(";
				lhs->PrintExpressionCode(quest_defns, quest_defns);
				quest_defns << ");\n";
			} else {
				for_bounds_stack[i]->PrintExpressionCode(quest_defns, quest_defns);
				print_err(compiler_sem_err
					, "for loop index condition is not a binary expression" 
					, 0, __LINE__, __FILE__);
			}

			// quest_defns is passed twice
			// becaues we want the AbstractExpression to appear in the for
			// loop in the questions section of the code
		}
		
		GenerateCodeSingleQuestion(quest_defns, program_code);
		quest_defns << questionName_ << "_list.questionList.push_back(" << questionName_ << ");"
			<< endl;
		for(int i=0; i< for_bounds_stack.size(); ++i){
			quest_defns << "stack_of_loop_indices.pop_back();\n";
			quest_defns << "}" << endl;
		}
	}

	if(next_){
		next_->GenerateCode(quest_defns, program_code);
	} 

}

NamedStubQuestion::NamedStubQuestion(DataType this_stmt_type, int line_number,
	string l_name, string l_q_text,
	QuestionType l_q_type, int l_no_mpn, DataType l_dt,
	//string& l_named_list): 
	named_range* l_nr_ptr
	//, AbstractExpression* l_arr_sz
	, vector<AbstractExpression*>& l_for_bounds_stack
	):
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt
		//, l_arr_sz
		, l_for_bounds_stack
		), 
	//named_list(l_named_list)
	nr_ptr(l_nr_ptr), stub_ptr(0)
{
}

NamedStubQuestion::NamedStubQuestion(DataType this_stmt_type, int line_number,
	string l_name, string l_q_text,
	QuestionType l_q_type, int l_no_mpn, DataType l_dt,
	named_range* l_nr_ptr
	):
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt
		), 
	nr_ptr(l_nr_ptr), stub_ptr(0)
{
}

NamedStubQuestion::NamedStubQuestion(DataType this_stmt_type, int line_number,
	string l_name, string l_q_text,
	QuestionType l_q_type, int l_no_mpn, DataType l_dt,
	vector<stub_pair>* l_stub_ptr
	, vector<AbstractExpression*>& l_for_bounds_stack
	):
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt
		, l_for_bounds_stack), 
	nr_ptr(0), stub_ptr(l_stub_ptr)
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

NamedStubQuestion::NamedStubQuestion(DataType this_stmt_type, int line_number
	, string l_name, string l_q_text
	, QuestionType l_q_type, int l_no_mpn, DataType l_dt
	, vector<stub_pair>* l_stub_ptr
	, const vector<int> & l_loop_index_values
	):
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt, l_loop_index_values
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
		sprintf(buff, " internal compiler error: update AbstractQuestion::print_q_type: %d, %s", 
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

void AbstractQuestion::PrintSetupBackJump(ostringstream & quest_defns
		, ostringstream& program_code)
{
	using qscript_parser::map_of_active_vars_for_questions;
	// --- THIS IS NEW CODE
	quest_defns << "map <string,int8_t> " << questionName_ << "_scope_int8_t;\n";
	quest_defns << "map <string,int16_t> " << questionName_ << "_scope_int16_t;\n";
	quest_defns << "map <string,int32_t> " << questionName_ << "_scope_int32_t;\n";
	quest_defns << "map <string,float> " << questionName_ << "_scope_float_t;\n";
	quest_defns << "map <string,double> " << questionName_ << "_scope_double_t;\n";
	// end of THIS IS NEW CODE


	program_code << "lab_" << questionName_ << ":" << endl;

	string q_push_name = questionName_ + "_push";
	string q_pop_name = questionName_ + "_pop";
	vector<string> active_push_vars_for_this_question = 
		map_of_active_vars_for_questions[q_push_name];
	vector<string> active_pop_vars_for_this_question = 
		map_of_active_vars_for_questions[q_pop_name];

	program_code << "if ( back_jump==true  && " << questionName_ <<  "->isAnswered_==true ) {" << endl;
	for(int i=active_pop_vars_for_this_question.size()-1; i>=0; --i){
		program_code << active_pop_vars_for_this_question[i] << endl;
	}
	program_code << "if ( jumpToQuestion == \"" << questionName_ << "\")\n{ back_jump=false;\n}\n";
	program_code << "}" << endl;

	for(unsigned int i=0; i< active_push_vars_for_this_question.size(); ++i)
	{
		program_code << active_push_vars_for_this_question[i] << endl;
	}
}


void AbstractQuestion::PrintEvalArrayQuestion(ostringstream & quest_defns
			, ostringstream& program_code)
{
	program_code << "\t\t" << questionName_.c_str() << "_list.questionList[";
	// ----------------------------------
	ostringstream * string_stream_vec=
		new ostringstream[for_bounds_stack.size()];
	for(int i=0; i< for_bounds_stack.size(); ++i){
		BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(for_bounds_stack[i]);
		if(bin_expr_ptr){
			AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
			AbstractExpression * lhs = bin_expr_ptr->leftOperand_;
			lhs->PrintExpressionCode(string_stream_vec[i], string_stream_vec[i]); 
			if(i<for_bounds_stack.size()-1) {
				string_stream_vec[i] << "*" ;
			}
		} else {
			for_bounds_stack[i]->PrintExpressionCode(string_stream_vec[i], string_stream_vec[i]);
			print_err(compiler_sem_err
				, "for loop index condition is not a binary expression" 
				, 0, __LINE__, __FILE__);
		}
		for(int j=i+1; j<for_bounds_stack.size(); j++){
			// quest_defns is passed twice
			// becaues we want the AbstractExpression to appear in the for
			// loop in the questions section of the code
			BinaryExpression * bin_expr_ptr2 = dynamic_cast<BinaryExpression*>(for_bounds_stack[j]);
			if(bin_expr_ptr2){
				AbstractExpression * rhs = bin_expr_ptr2->rightOperand_;
				rhs->PrintExpressionCode(string_stream_vec[i], string_stream_vec[i]);
				if(j<for_bounds_stack.size()-1) {
					string_stream_vec[i] << "*" ;
				}

			} else {
				for_bounds_stack[i]->PrintExpressionCode(string_stream_vec[i], string_stream_vec[i]);
				print_err(compiler_sem_err
					, "for loop index condition is not a binary expression" 
					, 0, __LINE__, __FILE__);
			}
		}
	}
	for(unsigned int i=0; i<for_bounds_stack.size(); ++i) {
		program_code << string_stream_vec[i].str();
		if(i <for_bounds_stack.size()-1 ){
			program_code << "+";
		}
	}
	delete[] string_stream_vec;
	// ---------------------------------
	program_code << "]->eval();\n" ;
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
