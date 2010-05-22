/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/stmt.C
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

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


extern vector<mem_addr_tab> mem_addr;
extern int if_line_no;

AbstractQuestion* AbstractStatement::IsAQuestionStatement()
{
	return 0;
}

void AbstractStatement::GetQuestionNames(vector<string> &question_list,
		AbstractStatement * endStatement)
{
	if(this==endStatement)
		return;
	if(next_){
		next_->GetQuestionNames(question_list, endStatement);
	}
}

//extern ofstream debug_log_file;
using qscript_parser::debug_log_file;
using std::cout;
using std::cerr;
using std::endl;
using std::stringstream;
void read_data(const char * prompt);
void ExpressionStatement::GenerateCode(ostringstream & quest_defns
		, ostringstream& program_code)
{
	expression_->PrintExpressionCode(quest_defns, program_code);
	program_code << ";" << endl;
	if(next_){
		next_->GenerateCode(quest_defns, program_code);
	}
}


ExpressionStatement::~ExpressionStatement() 
{
	using qscript_parser::mem_addr;
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "ExpressionStatement::~ExpressionStatement: setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting ExpressionStatement" << endl;
	//if(next_ ) delete next_;
	if (expression_) delete expression_;
}





void DeclarationStatement::GenerateCode(ostringstream & quest_defns, 
		ostringstream& program_code)
{
	program_code << " // DeclarationStatement::GenerateCode " << endl;
	ostringstream code_expr1, code_bef_expr1;
	if( symbolTableEntry_->e){
		symbolTableEntry_->e->PrintExpressionCode(code_bef_expr1
				, code_expr1);
		program_code << code_bef_expr1.str().c_str();
	}
	if(type_ >= INT8_TYPE && type_ <=DOUBLE_TYPE){
		program_code << noun_list[type_].sym 
			<< " " << symbolTableEntry_->name_;
	} else if (type_ >=INT8_ARR_TYPE && type_ <=DOUBLE_ARR_TYPE){
		DataType tdt=DataType(INT8_TYPE + type_-INT8_ARR_TYPE);
		program_code << noun_list[tdt].sym 
			<< symbolTableEntry_->name_ << "[" 
			<< symbolTableEntry_->n_elms << "]";
	} else if (type_ >=INT8_REF_TYPE&& type_ <=DOUBLE_REF_TYPE){
		DataType tdt=DataType(INT8_TYPE + type_-INT8_REF_TYPE);
		program_code << noun_list[tdt].sym 
			<< " & " << symbolTableEntry_->name_ ;
	}
	if( symbolTableEntry_->e){
		program_code << "=" << code_expr1.str().c_str();

	}
	program_code << ";" << endl;

	if(next_){
		next_->GenerateCode(quest_defns, program_code);
	}
}



DeclarationStatement::~DeclarationStatement() 
{
	using qscript_parser::mem_addr;
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "DeclarationStatement::~DeclarationStatement: setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting DeclarationStatement" << endl;

}

IfStatement::IfStatement( DataType dtype, int lline_number
		, AbstractExpression * lcondition
		, AbstractStatement * lif_body
		, AbstractStatement * lelse_body)
	: AbstractStatement(dtype, lline_number)
	  , ifCondition_(lcondition), ifBody_(lif_body), elseBody_(lelse_body)
{
	if(lcondition->type_==VOID_TYPE || lcondition->type_==ERROR_TYPE){
		print_err(compiler_sem_err, 
			"If ifCondition_ expression has Void or Error Type", 
			qscript_parser::if_line_no, __LINE__, __FILE__);
	} else {
	}
}

	struct IfStatementStackElement 
	{
		int nestLevel_;
		IfStatement * ifStatementPtr_;
		IfStatementStackElement(int nest_level, IfStatement
				* if_stmt_ptr):
			nestLevel_(nest_level), ifStatementPtr_(if_stmt_ptr)
		{}
	};

void IfStatement::GenerateCode(ostringstream & quest_defns
		, ostringstream& program_code)
{
	cerr << "ENTER: IfStatement::GenerateCode()" << endl;
	static vector<IfStatementStackElement*> ifStatementStack;
	static int if_nest_level =0;
	bool if_nest_level_was_increased=false;
	//++if_nest_level;
	if( ifStatementStack.size()>0){
		if(this==ifStatementStack[ifStatementStack.size()-1]
				->ifStatementPtr_->elseBody_){
			program_code <<
				"// if statement at same level of nesting"
				" as previous if i.e. part of the else if"
				" clause: if_nest_level: " 
				<< if_nest_level
				<< endl;
		} else {
			++if_nest_level;
			if_nest_level_was_increased=true;
			cout << "if at a deeper if_nest_level: " 
				<< if_nest_level << endl;
		}
	} else {
		++if_nest_level;
		if_nest_level_was_increased=true;
	}
	ostringstream code_bef_expr, code_expr;
	code_expr << "if (";
	ifCondition_->PrintExpressionCode(code_bef_expr, code_expr);
	code_expr << ") {";
	//code_expr << ") ";
	//CompoundStatement * if_body_is_a_cmpd_stmt = dynamic_cast<CompoundStatement*> (ifBody_);
	//if( if_body_is_a_cmpd_stmt  ){
	//} else {
	//	code_expr << " { " << endl;
	//}
	program_code << code_bef_expr.str();
	program_code << code_expr.str();
	//ifBody_->GenerateCode(quest_defns, program_code);
	vector<string> question_list_else_body;
	program_code << "// ifStatementStack.size(): "
		<< ifStatementStack.size() << endl;
	if(ifStatementStack.size() > 0 ){
		// one change to be done here
		/*
		ifStatementStack[ifStatementStack.size()-1]->ifStatementPtr_
			->GetQuestionNames
			(question_list_else_body, this);
		*/
		cerr << "IfStatement::GenerateCode(): ifStatementStack.size>0 :Before LOOP" << endl;
		for(int i=0; i<ifStatementStack.size(); ++i){
			if(ifStatementStack[i]->nestLevel_==if_nest_level){
				ifStatementStack[i]->ifStatementPtr_
					->GetQuestionNames
					(question_list_else_body, this);
				break;
			}
		}
		cerr << "IfStatement::GenerateCode(): ifStatementStack.size>0 " << endl;
	}
	if(elseBody_)
		elseBody_->GetQuestionNames(question_list_else_body, 0);
	for(int i=0; i<question_list_else_body.size(); ++i){
		program_code <<  question_list_else_body[i] 
			<< "->isAnswered_=false;"
			<< endl;
	}
	ifBody_->GenerateCode(quest_defns, program_code);
	program_code << " }" << endl;
	//if( if_body_is_a_cmpd_stmt  ){
	//} else {
	//	program_code << " } " << endl;
	//}

	if(elseBody_){
		program_code << " else {" << endl;

		IfStatement * elseIfStatement = dynamic_cast<IfStatement*>
						(elseBody_);
		if(elseIfStatement){
			IfStatementStackElement *  stk_el=
				new IfStatementStackElement (if_nest_level,
					this);

			program_code << 
				"// pushing onto ifStatementStack \n";

			ifStatementStack.push_back(stk_el);
		}
		//elseBody_->GenerateCode(quest_defns, program_code);
		vector<string> question_list_if_body;

		for(int i=0; i<ifStatementStack.size(); ++i){
			if(ifStatementStack[i]->nestLevel_==if_nest_level){
				ifStatementStack[i]->ifStatementPtr_
					->GetQuestionNames
					(question_list_if_body, this);
				break;
			}
		}
		ifBody_->GetQuestionNames(question_list_if_body, 0);
		program_code << "// end of ifBody_->GetQuestionNames \n";
		if(elseIfStatement){
			//elseIfStatement->elseBody_->GetQuestionNames
			//	(question_list_if_body, 0);
			program_code << " // elseIfStatement exists \n";
		} else {
			program_code << " // elseIfStatement DOES NOT exists \n";
			program_code << "/* question_list_if_body.size(): " 
				<< question_list_if_body.size() << " */ \n";
			for(int i=0; i<question_list_if_body.size(); ++i){
				program_code <<  question_list_if_body[i] 
					<< "->isAnswered_=false;"
					<< endl;
			}
			program_code << "// **************** \n";
		}
		elseBody_->GenerateCode(quest_defns, program_code);
		
		if(elseIfStatement){
			IfStatementStackElement * stk_el = 
				ifStatementStack.back();
			delete stk_el;
			ifStatementStack.pop_back();
		}
		program_code << "}" << endl;
		//if( else_body_is_a_cmpd_stmt  ){
		//} else {
		//	program_code << " } " << endl;
		//}
	} 

	if(if_nest_level_was_increased){
		--if_nest_level;
		if_nest_level_was_increased=false;
	}

	program_code << " /* finished generating code IfStatement */ " << endl;
	if(next_) 
		next_->GenerateCode(quest_defns, program_code);
	cerr << "EXIT: IfStatement::GenerateCode()" << endl;
}



IfStatement:: ~IfStatement()
{
	using qscript_parser::mem_addr;
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file 
				<< "IfStatement::~IfStatement setting mem_addr:" 
				<< this << "=0" << endl;
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

CompoundStatement::CompoundStatement(DataType dtype, int lline_number, 
	int l_flag_cmpd_stmt_is_a_func_body,
	int l_flag_cmpd_stmt_is_a_for_body): 
	AbstractStatement(dtype, lline_number), 
	compoundBody_(0), scope_(0), 
	flagIsAFunctionBody_(l_flag_cmpd_stmt_is_a_func_body),
	flagIsAForBody_(l_flag_cmpd_stmt_is_a_for_body),
	counterContainsQuestions_(0)
{}


void CompoundStatement::GenerateCode(ostringstream & quest_defns, 
	ostringstream& program_code)
{
	program_code << "{" << endl;
	if (compoundBody_) 
		compoundBody_->GenerateCode(quest_defns, program_code);
	program_code << "}" << endl;
	if(next_) 
		next_->GenerateCode(quest_defns, program_code);
}


CompoundStatement::~CompoundStatement() 
{
	using qscript_parser::mem_addr;
	debug_log_file << "deleting CompoundStatement" << endl;
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "basic_count_ax_stmt::~basic_count_ax_stmt setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	if(scope_&&flagIsAFunctionBody_<0) {
		delete scope_;
		scope_=0;
	}
	if(compoundBody_ /*&& flagIsAFunctionBody_<0*/){
		delete compoundBody_;
		compoundBody_=0;
	}
}

using qscript_parser::question_list;
AbstractQuestion* find_in_question_list(string name)
{

	for(int i=0; i<question_list.size(); ++i){
		if(question_list[i]->questionName_==name){
			return question_list[i];
		}
	}
	return 0;
}


ForStatement::ForStatement( DataType dtype, int lline_number
		, AbstractExpression * l_init, AbstractExpression * l_test
		, AbstractExpression* l_incr, CompoundStatement * l_for_body)
	: AbstractStatement(dtype, lline_number)
	, initializationExpression_(l_init)
	, testExpression_(l_test), incrementExpression_(l_incr)
	, forBody_(l_for_body)
{
	if(initializationExpression_->type_==VOID_TYPE
			||testExpression_->type_==VOID_TYPE
			||incrementExpression_->type_==VOID_TYPE ){
		print_err(compiler_sem_err, 
			"For ifCondition_ expression has Void or Error Type", 
			qscript_parser::line_no, __LINE__, __FILE__);
		type_=ERROR_TYPE;
	}
	// NxD - I have to correct here
	// testExpression_ should be a binary expression and 
	// testExpression_->e_type should be <, >, <=, >=, == or !=

	if(forBody_->counterContainsQuestions_){
		BinaryExpression * test_expr 
			= dynamic_cast<BinaryExpression*>(testExpression_);
		if(test_expr==0){
			print_err(compiler_sem_err, 
				" testExpression_ expr should be a binary expression ",
				qscript_parser::line_no, __LINE__, __FILE__);
		} else if(!(test_expr->rightOperand_->IsIntegralExpression() 
				&& test_expr->rightOperand_->IsConst())) {
			print_err(compiler_sem_err, 
				"If the for loop contains questions, then the counter of the for loop should be an integer and a constant expression"
			, qscript_parser::line_no, __LINE__, __FILE__);
		}
	}
}

void ForStatement::GenerateCode(ostringstream& quest_defns
		, ostringstream& program_code)
{
	ostringstream code_bef_expr, code_expr;
	code_expr << "for (" ;
	initializationExpression_->PrintExpressionCode(code_bef_expr
			, code_expr);
	code_expr <<   ";";
	testExpression_->PrintExpressionCode(code_bef_expr, code_expr);
	code_expr << ";";
	incrementExpression_->PrintExpressionCode(code_bef_expr, code_expr);
	code_expr <<  ")";

	program_code << code_bef_expr.str();
	program_code << code_expr.str();
	forBody_->GenerateCode(quest_defns, program_code);
	if(next_) 
		next_->GenerateCode(quest_defns, program_code);
}


ForStatement:: ~ForStatement()
{
	using qscript_parser::mem_addr;
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file 
				<< "ForStatement::~ForStatement setting mem_addr:" 
				<< this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting ForStatement" << endl;
	//if (next_) delete next_;
	delete initializationExpression_; initializationExpression_=0;
	delete testExpression_; testExpression_=0;
	delete incrementExpression_; incrementExpression_=0;
	delete forBody_; forBody_=0;
}


VariableList::VariableList(DataType type, char * name) 
	: variableType_(type), variableName_(name)
	  , arrayLength_(-1), prev_(0), next_(0)
{
	if (!( (type>=INT8_TYPE&& type<=DOUBLE_TYPE) ||
		(type>=INT8_REF_TYPE&& type<=DOUBLE_REF_TYPE))){
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
	if (next_) { delete next_; next_=0; }
	debug_log_file << "end deleting ~VariableList " << endl;
}


void VariableList::print(FILE * edit_out)
{
	struct VariableList * vl_ptr=this;
	while(vl_ptr){
		if(vl_ptr->variableType_>=INT8_TYPE 
				&& vl_ptr->variableType_<=DOUBLE_TYPE){
			fprintf(edit_out, "%s %s"
					, noun_list[vl_ptr->variableType_].sym
					, vl_ptr->variableName_.c_str());
		} else if (vl_ptr->variableType_>=INT8_ARR_TYPE
				&&vl_ptr->variableType_<=DOUBLE_ARR_TYPE){
			DataType tdt=DataType(INT8_TYPE 
					+ vl_ptr->variableType_-INT8_ARR_TYPE);
			fprintf(edit_out
					, "%s %s[%d]/* vartype: %d */"
					, noun_list[tdt].sym
					, vl_ptr->variableName_.c_str()
					, arrayLength_
					, vl_ptr->variableType_);
		} else if (vl_ptr->variableType_>=INT8_REF_TYPE
				&&vl_ptr->variableType_<=DOUBLE_REF_TYPE){
			DataType tdt=DataType(INT8_TYPE 
					+ vl_ptr->variableType_-INT8_REF_TYPE);
			fprintf(edit_out, "%s & %s"
					, noun_list[tdt].sym
					, vl_ptr->variableName_.c_str());
		} else {
			fprintf(edit_out, "INTERNAL ERROR:Unknown data type: file: %s, line: %d\n", __FILE__, __LINE__);
		}
		vl_ptr=vl_ptr->next_;
		if(vl_ptr) {
			fprintf(edit_out, ",");
		}
	}
}

VariableList::VariableList(DataType type, char * name, int len)
	: variableType_(type), variableName_(name)
	  , arrayLength_(len), prev_(0), next_(0)
{
	if(!is_of_arr_type(type)){
		cerr << "SEMANTIC error: only INT8_ARR_TYPE ... DOUBLE_ARR_TYPE array Types are allowed in decl: " << variableName_ << endl;
		cerr << "NEED TO LINK  BACK TO ERROR: FIX ME" << endl;
	}
	cout << "constructing VariableList: " << variableName_ << endl;
}


StubManipStatement::StubManipStatement( DataType dtype, int lline_number
		, string l_named_stub, string l_question_name
	)
	: AbstractStatement(dtype, lline_number), 
	namedStub_(l_named_stub), questionName_(l_question_name)
{
}

StubManipStatement::StubManipStatement( DataType dtype, int lline_number
		, string l_named_stub)
	: AbstractStatement(dtype, lline_number), 
	namedStub_(l_named_stub)
{
}

void StubManipStatement::GenerateCode(ostringstream& quest_defns
		, ostringstream& program_code)
{
	using qscript_parser::question_list;
	program_code << "/*StubManipStatement::GenerateCode()" 
		<< questionName_ << ":" << namedStub_ << "*/"
		<< endl;
	program_code << "{" << endl;


	if(type_==STUB_MANIP_DEL || type_==STUB_MANIP_ADD){
		program_code << "set<int>::iterator set_iter = " 
			<< questionName_ 
			<< "->input_data.begin();" << endl;
		program_code << "for( ; set_iter!= " 
			<< questionName_ 
			<< "->input_data.end(); ++set_iter){" << endl;
		program_code << "\tfor(int i=0; i< " 
			<< namedStub_ << ".size(); ++i){" << endl;
		program_code << "\t\tif(" << namedStub_ 
			<< "[i].code==*set_iter ) {" << endl;
		if(type_==STUB_MANIP_DEL){
			program_code << "\t\t\t" 
				<< namedStub_ << "[i].mask=false; " << endl;
		} else if(type_==STUB_MANIP_ADD) {
			program_code << "\t\t\t" 
				<< namedStub_ << "[i].mask=true; " << endl;
		}
		program_code << "\t\t}" << endl;
		program_code << "\t}" << endl;
		program_code << "}" << endl;
	} else if (type_==STUB_MANIP_UNSET_ALL || type_==STUB_MANIP_SET_ALL) {
		program_code << "for(int i=0; i< " 
			<< namedStub_ << ".size(); ++i){" << endl;
		if(type_==STUB_MANIP_UNSET_ALL){
			program_code << namedStub_ 
				<< "[i].mask=false; " << endl;
		} else if(type_==STUB_MANIP_SET_ALL) {
			program_code << namedStub_ 
				<< "[i].mask=true; " << endl;
		} 
		program_code << "}" << endl;
	} else {
		stringstream err_text;
		err_text << "AbstractQuestion: " << questionName_
			<< " , dataype of StubManipStatement statement is not as expected"
			<< endl;
		print_err(compiler_sem_err, err_text.str()
				, lineNo_, __LINE__, __FILE__  );
		program_code << "ERROR: StubManipStatement: this should fail compilation" << endl;
	}

	program_code << endl;

	program_code << "}" << endl;

	if(next_) 
		next_->GenerateCode(quest_defns, program_code);
}

StubManipStatement::~StubManipStatement()
{ }
