/*
 * AbstractExpression.C
 * expressions in the grammar
 * Copyright (C) 2003,2004, 2005,2006,2007  Neil Xavier D'Souza <nxd_in@yahoo.com>
 * Postal MAil address:
 * Neil Xavier D'Souza
 * 502, Premier Park
 * 1st Tank Lane,
 * Orlem, Malad(W),
 * Mumbai India. 400064.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2,
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * The Free Software Foundation,
 * 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include <sys/types.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "stmt.h"
#include "expr.h"
#include "scope.h"
#include "named_range.h"
#include "qscript_parser.h"
#include "question.h"
#include "qscript_debug.h"
#include "code_gen_utils.h"

AbstractQuestion* find_in_question_list(string name);
using std::string;
using std::stringstream;
// string get_temp_name();


//extern Scope* active_scope;
//extern ofstream debug_log_file;
//using namespace std;
//
//extern	vector <func_info*> func_info_table;
//extern vector<mem_addr_tab> mem_addr;
//extern vector <named_range*> named_stubs_list;
using qscript_parser::debug_log_file;
using qscript_parser::line_no;
using qscript_parser::no_errors;
using std::cout;
using std::cerr;
using std::endl;

AbstractExpression::AbstractExpression(ExpressionOperatorType le_type)
	:exprOperatorType_(le_type), type_(ERROR_TYPE)
	, next_(0), prev_(0)
{ }

AbstractExpression::AbstractExpression(ExpressionOperatorType le_type, DataType ldt)
	:exprOperatorType_(le_type), type_(ldt), next_(0), prev_(0)
{ }

AbstractExpression::~AbstractExpression()
{
	debug_log_file << "deleting AbstractExpression::~AbstractExpression(): base destructor for AbstractExpression" << endl;
	if (next_) {delete next_; next_ = 0; }
}

/*
	DataType AbstractExpression::get_type(){
		if (type_ == oper_func_call){
			return func_info_table[index].return_type;
		}
		return type_;
	}
*/

int32_t AbstractExpression::IsValid()
{
	//cout << "IsValid called" << endl;
	if (type_ == ERROR_TYPE){
		return 0;
	} else return 1;
}

void UnaryExpression::PrintExpressionText(ostringstream & s)
{

	switch(exprOperatorType_){
	case oper_umin:{
		s <<  "Minus ";
		operand_->PrintExpressionText(s);
	}
		break;

	case oper_not:{
		//fprintf(edit_out, "! ");
		s << "Not ";
		operand_->PrintExpressionText(s);
	}
		break;

	case oper_parexp:{
		s <<  "(";
		operand_->PrintExpressionText(s);
		s <<  ")";
	}
		break;
	default:
		s <<  " un handled operator\n";

	}
}

UnaryExpression::~UnaryExpression()
{
	using qscript_parser::mem_addr;
	for (int32_t i = 0; i< mem_addr.size(); ++i){
		if (this == mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr = 0;
			debug_log_file
				<< "UnaryExpression::~UnaryExpression setting mem_addr: "
				<< this << " = 0" << endl;
			break;
		}
	}
	debug_log_file << "deleting UnaryExpression: exprOperatorType_" << exprOperatorType_ << endl;
	if (operand_) { delete operand_; operand_ = 0; }
}

UnaryExpression::UnaryExpression(AbstractExpression * l_operand
				 , ExpressionOperatorType le_type)
	: AbstractExpression(le_type), operand_(l_operand)
{
	if (operand_->exprOperatorType_ == oper_blk_arr_assgn) {
		print_err(compiler_sem_err, "oper_blk_arr_assgn: cannot be used with unary operators : line_no:",
			line_no, __LINE__, __FILE__);
	} else if (l_operand->type_ == VOID_TYPE) {
		switch(l_operand->exprOperatorType_){
		case oper_umin:
		case oper_not:
			cerr << "operator Unary minus(-): ";
			print_err(compiler_sem_err, " unary operator applied to function of type_ void ",
				  line_no, __LINE__, __FILE__);
			break;
		default:
			print_err(compiler_sem_err,
				  " unary operator applied to AbstractExpression of type_ void. Internal compiler error ",
				  line_no, __LINE__, __FILE__);
		}
	} else {
		switch(exprOperatorType_){
		case oper_umin:
			type_ = l_operand->type_;
			break;
		case oper_not:
			//type_ = INT8_TYPE;
			type_ = BOOL_TYPE;
			break;
		case oper_parexp:
			type_ = l_operand->type_;
			break;
		default:
			++no_errors;
			print_err(compiler_internal_error
				  , " unknown unary operator applied to AbstractExpression."
				  "Internal compiler error "
				  ,  line_no, __LINE__, __FILE__);
		}
	}
}

bool UnaryExpression::IsIntegralExpression()
{
	return operand_->IsIntegralExpression();
}


//void UnaryExpression::PrintExpressionCode (FILE * edit_out)
//void UnaryExpression::PrintExpressionCode (ostringstream& code_bef_expr, ostringstream & code_expr)
void UnaryExpression::PrintExpressionCode(ExpressionCompiledCode& code)
{
	if (qscript_debug::DEBUG_UnaryExpression) {
		code.code_expr << "/* UnaryExpression::PrintExpressionCode ENTER */" << endl;
	}
	switch(exprOperatorType_){
	case oper_umin:{
		code.code_expr <<  "- ";
		operand_->PrintExpressionCode(code);
	}
		break;

	case oper_not:{
		//fprintf(edit_out, "! ");
		code.code_expr <<  "! ";
		operand_->PrintExpressionCode(code);
	}
		break;

	case oper_parexp:{
		code.code_expr <<  "(";
		operand_->PrintExpressionCode(code);
		code.code_expr <<  ")";
	}
		break;
	default:
		code.code_expr <<  " un handled operator\n";

	}
	if (qscript_debug::DEBUG_UnaryExpression)
		code.code_expr << "/* UnaryExpression::PrintExpressionCode EXIT */" << endl;
}

bool UnaryExpression::IsConst()
{
	return operand_->IsConst();
}

void BinaryExpression::PrintExpressionText(ostringstream &s)
{

	switch(exprOperatorType_){
	case oper_plus:{
		leftOperand_->PrintExpressionText(s);
		s << " Plus ";
		rightOperand_->PrintExpressionText(s);

	}
		break;
	case oper_minus:{
		leftOperand_->PrintExpressionText(s);
		s << " Minus ";
		rightOperand_->PrintExpressionText(s);
	}
		break;
	case oper_mult:{
		leftOperand_->PrintExpressionText(s);
		s << " Multiplied ";
		rightOperand_->PrintExpressionText(s);
	}
		break;
	case oper_div:{
		leftOperand_->PrintExpressionText(s);
		s << " Divided ";
		rightOperand_->PrintExpressionText(s);
	}
		break;
	case oper_mod:{
		leftOperand_->PrintExpressionText(s);
		s << " Modulus ";
		rightOperand_->PrintExpressionText(s);
	}
		break;
	case oper_lt:{
		leftOperand_->PrintExpressionText(s);
		s << " is Less Than ";
		rightOperand_->PrintExpressionText(s);
	}
		break;
	case oper_gt:{

		leftOperand_->PrintExpressionText(s);
		s << " is Greater than ";
		rightOperand_->PrintExpressionText(s);
	}
		break;
	case oper_le:{

		leftOperand_->PrintExpressionText(s);
		s << " is less than or equal to ";
		rightOperand_->PrintExpressionText(s);
	}
		break;
	case oper_ge:{

		leftOperand_->PrintExpressionText(s);
		s << " is greater than or equal to ";
		rightOperand_->PrintExpressionText(s);
	}
		break;
	case oper_iseq:{

		leftOperand_->PrintExpressionText(s);
		s << " Equals ";
		rightOperand_->PrintExpressionText(s);
	}
		break;
	case oper_isneq: {

		leftOperand_->PrintExpressionText(s);
		s << " is Not Equal to ";
		rightOperand_->PrintExpressionText(s);
	}
		break;
	case oper_assgn:
		s<< " oper_assgn not handled in base text generator";
		break;
	case oper_or:{

		leftOperand_->PrintExpressionText(s);
		s << " Or ";
		rightOperand_->PrintExpressionText(s);
	}
		break;
	case oper_and:{

		leftOperand_->PrintExpressionText(s);
		s << " And ";
		rightOperand_->PrintExpressionText(s);
	}
		break;
	default:
		s << " unhandled operator is base text generator";
		print_err(compiler_sem_err
			  , " unhandled operator type_ in AbstractExpression  ",
			  line_no, __LINE__, __FILE__);
	}
}


// will sort this out later
bool BinaryExpression::IsConst()
{
	//cerr << "BinaryExpression::IsConst(): returning: "
	//	<< (leftOperand_->IsIntegralExpression() && rightOperand_->IsIntegralExpression() )
	//	<< endl;
	return leftOperand_->IsConst() && rightOperand_->IsConst();
}

bool BinaryExpression::IsIntegralExpression()
{
	//cerr << "BinaryExpression::IsIntegralExpression(): returning: "
	//	<< (leftOperand_->IsIntegralExpression() && rightOperand_->IsIntegralExpression())
	//	<< endl;
	return leftOperand_->IsIntegralExpression() && rightOperand_->IsIntegralExpression();
}

string human_readable_type(DataType dt);
void BinaryExpression::print_oper_assgn(ExpressionCompiledCode & code)
{
	if (qscript_debug::DEBUG_BinaryExpression)
		code.code_bef_expr << "/* ENTER BinaryExpression::print_oper_assgn */\n";
	if (leftOperand_->exprOperatorType_ == oper_arrderef
	    && leftOperand_->type_ == QUESTION_TYPE){
		Unary2Expression* lhs=
			static_cast<Unary2Expression*>(leftOperand_);
		const SymbolTableEntry * symp = lhs->get_symp_ptr();
		AbstractQuestion* q = find_in_question_list(symp->name_);
		string cpp_data_type = human_readable_type(q->dt);
		//string tmp_name = get_temp_name();
		string tmp_name = qscript_parser::temp_name_generator.GetNewName();

		code.code_expr << cpp_data_type << " " << tmp_name << " = ";
		rightOperand_->PrintExpressionCode(code);
		code.code_expr << ";" << endl;
		code.code_expr << "if ("
			<< q->questionName_ << "_list.questionList[";
		lhs->operand_->PrintExpressionCode(code);
		code.code_expr	<< "]"
			<< "->IsValid("<<  tmp_name
			<<  ")) {" << endl;
		code.code_expr << q->questionName_ << "_list.questionList[";
		lhs->operand_->PrintExpressionCode(code);
		code.code_expr << "]"
			<< "->input_data.clear();" << endl;
		code.code_expr << q->questionName_  << "_list.questionList[";
		lhs->operand_->PrintExpressionCode(code);
		code.code_expr << "]"

			<< "->input_data.insert(";
		//rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
		code.code_expr << tmp_name;
		code.code_expr << ") ; " << endl;
		code.code_expr << "} else {";
		code.code_expr << "cerr << \"runtime error - value assigned to Question: \" << \""
			<< q->questionName_ << "\"" << " << \" is not in allowed range: \" <<"
			<< tmp_name << " << \" ... exiting \" << endl; " << endl
			<< "exit(1);"  << endl
			<< endl;
		code.code_expr << "}\n" << endl;
		cerr << "INTERNAL COMPILER WARNING : line: " << __LINE__
			<< ", file: " << __FILE__
			<< " put range check on allowed codes"
			<< endl;

	} else if (leftOperand_->exprOperatorType_ == oper_name
		   && leftOperand_->type_ == QUESTION_TYPE){
		Unary2Expression* lhs=
			static_cast<Unary2Expression*>(leftOperand_);
		const SymbolTableEntry * symp = lhs->get_symp_ptr();
		AbstractQuestion* q = find_in_question_list(symp->name_);
		string cpp_data_type = human_readable_type(q->dt);
		//string tmp_name = get_temp_name();
		string tmp_name = qscript_parser::temp_name_generator.GetNewName();

		code.code_expr << cpp_data_type << " " << tmp_name << " = ";
		rightOperand_->PrintExpressionCode(code);
		code.code_expr << ";" << endl;
		code.code_expr << "if ("
			<< q->questionName_ << "->IsValid("<<  tmp_name
			<<  ")) {" << endl;
		code.code_expr << q->questionName_
			<< "->input_data.clear();" << endl;
		code.code_expr << q->questionName_ << "->input_data.insert(";
		//rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
		code.code_expr << tmp_name;
		code.code_expr << ") ; " << endl;
		code.code_expr << "} else {";
		code.code_expr << "cerr << \"runtime error - value assigned to Question: \" << \""
			<< q->questionName_ << "\"" << " << \" is not in allowed range: \" <<"
			<< tmp_name << " << \" ... exiting \" << endl; " << endl
			<< "exit(1);" << endl
			<< endl;
		code.code_expr << "}\n" << endl;
		cerr << "WARNING : line: " << __LINE__
			<< ", file: " << __FILE__
			<< " put range check on allowed codes"
			<< endl;

	} else {
		if (qscript_debug::DEBUG_BinaryExpression)
			code.code_bef_expr << " /* print_oper_assgn lhs is not a (QUESTION_TYPE or QUESTION_ARR_TYPE) */";
		leftOperand_->PrintExpressionCode(code);
		code.code_expr << " = ";
		rightOperand_->PrintExpressionCode(code);
		if (qscript_debug::DEBUG_BinaryExpression)
			code.code_expr << " /* print_oper_assgn END */";
	}
	if (qscript_debug::DEBUG_BinaryExpression)
		code.code_expr << "/* EXIT BinaryExpression::print_oper_assgn */\n";
}

bool Unary2Expression::IsConst()
{
	switch(exprOperatorType_){
		case oper_num:
		case oper_float:
			//cerr << "Unary2Expression::IsConst() returning true."<< endl;
			return true;
		case oper_name:
			if (symbolTableEntry_->type_qual == CONST_QUAL){
				return true;
			} else {
				return false;
			}
		default:
			return false;
	}
}


bool Unary2Expression::IsIntegralExpression()
{
	//cerr << "Unary2Expression::IsIntegralExpression(): "
	//		<< exprOperatorType_ << endl;
	//cerr << "oper_num: " << oper_num << endl;
	switch(exprOperatorType_){
	case oper_num:
		//cerr << "Unary2Expression::IsIntegralExpression: returning true" << endl;
		return true;
	case oper_name:
		switch(symbolTableEntry_->type_){
		case INT8_TYPE:
		case INT16_TYPE:
		case INT32_TYPE:
		case INT8_ARR_TYPE:
		case INT16_ARR_TYPE:
		case INT32_ARR_TYPE:
		case INT8_REF_TYPE:
		case INT16_REF_TYPE:
		case INT32_REF_TYPE:
			return true;
		default:
			return false;
		}
	default:
		return false;
	}
}

void Unary2Expression::PrintExpressionText(ostringstream & s)
{
	switch(exprOperatorType_){
	case oper_name:{
		//code.code_bef_expr << " /* case  oper_name */ \n";
		if (type_ == QUESTION_TYPE){
			AbstractQuestion * q = symbolTableEntry_->question_;
			if (q->type_ == QUESTION_TYPE){
				s << "All who have answered question " << q->questionName_;
			}
		} else {
			s << "All respondents where internal variable " << symbolTableEntry_->name_ << " is true"; 
		}

	}
		break;
	case oper_arrderef:{
		if (type_ == QUESTION_TYPE){
			AbstractQuestion * q = symbolTableEntry_->question_;
			if (q->type_ == QUESTION_ARR_TYPE){
				s << " All who have answered " 
					<< q->questionName_
					<< "[";
				ExpressionCompiledCode code1;
				operand_->PrintExpressionCode(code1);
				s << code1.code_bef_expr.str()
					<< code1.code_expr.str()
					<< "]";
			}
		}
	}
		break;

	case oper_num:{
		s << intSemanticValue_;
	}
		break;
	case oper_float:{
		s << doubleSemanticValue_;
	}
		break;
	case oper_func_call:{

		s << " oper_func_call : unhandled case" ;
	}
		break;
	case oper_text_expr:{
		s << "oper_text_expr: unhandled case  " <<  text;
	}
		break;
	case oper_to_string: {
		// the Constructor takes care that only
		// questions are allowed as paramters for
		// oper_to_string
		s << "oper_to_string: unhandled case ";
	}
		break;
	case oper_blk_arr_assgn: {
		s << "oper_blk_arr_assgn : unhandled case" ;
	}
		break;
	case oper_isanswered: {
		AbstractQuestion * q = symbolTableEntry_->question_;
		s << "All respondents who have answered " << q->questionName_;
	}
		break;
	case oper_count: {
		AbstractQuestion * q = symbolTableEntry_->question_;

		s << "Count of answers at " << q->questionName_ ;
	}
		break;
	default:
		s << "unhandled case" << "," << __FILE__ << ", " << __LINE__<< ", " << __PRETTY_FUNCTION__ << endl;
	}
}

void Unary2Expression::PrintExpressionCode(ExpressionCompiledCode & code)
{
	if (qscript_debug::DEBUG_Unary2Expression)
		code.code_bef_expr <<"/* Unary2Expression::PrintExpressionCode ENTER */" << endl;
	switch(exprOperatorType_){
	case oper_name:{
		//code.code_bef_expr << " /* case  oper_name */ \n";
		if (type_ == QUESTION_TYPE){
			AbstractQuestion * q = symbolTableEntry_->question_;
			if (q->type_ == QUESTION_TYPE){
				code.code_bef_expr
					<< "/*if (!" << q->questionName_
					<< "->isAnswered_) {\n"
					<< "cerr << \"runtime error using unanswered question in expression: \" << \""
					<< q->questionName_
					<< "\" << endl;\n}*/\n";

				// string temp_name = get_temp_name();
				string temp_name = qscript_parser::temp_name_generator.GetNewName();
				code.code_bef_expr << "int32_t " << temp_name
						   << " = *" << symbolTableEntry_->name_ 
						   << "->input_data.begin();\n";
				code.code_expr << temp_name;
			}
		} else {
			code.code_expr << symbolTableEntry_->name_;
		}

	}
		break;
	case oper_arrderef:{
		if (type_ == QUESTION_TYPE){
			AbstractQuestion * q = symbolTableEntry_->question_;
			if (q->type_ == QUESTION_ARR_TYPE){
				code.code_bef_expr
					<< "if (!"
					<< q->questionName_
					<< "_list.questionList[";
				ExpressionCompiledCode code1;
				operand_->PrintExpressionCode(code1);
				code.code_bef_expr << code1.code_bef_expr.str()
						   << code1.code_expr.str();
				code.code_bef_expr
					<< "]->isAnswered_) {\n"
					<< "cerr << \"runtime error using unanswered question in expression: \" << \""
					<< q->questionName_
					<< "\" << endl;\n}\n";
			}
		}
		code.code_expr <<  "*(" << symbolTableEntry_->name_ << "_list.questionList[";
		operand_->PrintExpressionCode(code);
		code.code_expr << "]->input_data.begin())";
	}
		break;

	case oper_num:{
		code.code_expr <<  intSemanticValue_;
	}
		break;
	case oper_float:{
		code.code_expr <<  doubleSemanticValue_;
	}
		break;
	case oper_func_call:{
		using qscript_parser::func_info_table;
		//cout << "/* oper_func_call */" << endl;
		//cout << "func_index_in_table: " << func_info_table[e->func_index_in_table]->functionName_ << endl;
		if (func_info_table[func_index_in_table]->functionName_ == string("printf")){
			code.code_expr << "fprintf(qscript_stdout,";
		} else {
			code.code_expr <<func_info_table[func_index_in_table]->functionName_.c_str() << "(";
		}
		struct AbstractExpression* e_ptr = operand_;
		while(e_ptr){
			e_ptr->PrintExpressionCode(code);
			if (e_ptr->next_){
				code.code_expr << ", ";
			}
			e_ptr = e_ptr->next_;
		}
		code.code_expr << ");fflush(qscript_stdout)";
	}
		break;
	case oper_text_expr:{
		code.code_expr <<"\"" <<text << "\"";
	}
		break;
	case oper_to_string: {
		// the Constructor takes care that only
		// questions are allowed as paramters for
		// oper_to_string
		AbstractQuestion * q = symbolTableEntry_->question_;
		code.code_expr << q->questionName_ << "->CurrentResponseToCharString() ";
	}
		break;
	case oper_blk_arr_assgn: {
		code.code_expr <<"This case should not occur\n";
		print_err(compiler_internal_error, "This case should not occur\n",
			  line_no, __LINE__, __FILE__);
	}
		break;
	case oper_isanswered: {
		AbstractQuestion * q = symbolTableEntry_->question_;
		code.code_expr << " " << q->questionName_ << "->isAnswered_ ";
	}
		break;
	case oper_count: {
		AbstractQuestion * q = symbolTableEntry_->question_;
		string tmp_name = qscript_parser::temp_name_generator.GetNewName();
		code.code_bef_expr << "int32_t " << tmp_name << " = 0;\n";
		code.code_bef_expr << "if (!" << q->questionName_ << "->isAnswered_) {\n"
			<< tmp_name << " = 0;\n"
			<< "} else {\n" << endl;
		code.code_bef_expr << "for (set<int32_t>::iterator it = " << q->questionName_ << "->input_data.begin();"
				<< "it != "
				<< q->questionName_ <<  "->input_data.end(); ++it) {\n"
			<< "++" << tmp_name << ";\n"
			<< "}\n}\n" << endl;
		code.code_expr <<  tmp_name;
	}
		break;
	default:
		code.code_expr <<"unhandled AbstractExpression operator: " << __PRETTY_FUNCTION__;
		print_err(compiler_internal_error, code.code_expr.str().c_str(),
			  line_no, __LINE__, __FILE__);
	}
	if (qscript_debug::DEBUG_Unary2Expression)
		code.code_expr <<"/* Unary2Expression::PrintExpressionCode EXIT */" << endl;
}

//void BinaryExpression::PrintExpressionCode(ostringstream& code_bef_expr, ostringstream & code_expr)
void BinaryExpression::PrintExpressionCode(ExpressionCompiledCode &code)
{
	if (qscript_debug::DEBUG_BinaryExpression)
		code.code_bef_expr << "/* ENTER BinaryExpression::PrintExpressionCode */" << endl;

	char oper_buf[3] = { 0, 0, 0};
	switch(exprOperatorType_){
	case oper_plus:{
		oper_buf[0] = '+';
		leftOperand_->PrintExpressionCode(code);
		code.code_expr << oper_buf;
		rightOperand_->PrintExpressionCode(code);
	}
		break;
	case oper_minus:{
		oper_buf[0] = '-';
		leftOperand_->PrintExpressionCode(code);
		code.code_expr << oper_buf;
		rightOperand_->PrintExpressionCode(code);
	}
		break;
	case oper_mult:{
		code.code_expr << " /* Enter oper_mult */ " << endl;
		oper_buf[0] = '*';
		leftOperand_->PrintExpressionCode(code);
		code.code_expr << oper_buf;
		rightOperand_->PrintExpressionCode(code);
	}
		break;
	case oper_div:{
		oper_buf[0] = '/';
		leftOperand_->PrintExpressionCode(code);
		code.code_expr << oper_buf;
		rightOperand_->PrintExpressionCode(code);
	}
		break;
	case oper_mod:{
		//sprintf(oper_buf, "%s" , "%");
		oper_buf[0] = '%';
		leftOperand_->PrintExpressionCode(code);
		code.code_expr << oper_buf;
		rightOperand_->PrintExpressionCode(code);
	}
		break;
	case oper_lt:{
		oper_buf[0] = '<';
		leftOperand_->PrintExpressionCode(code);
		code.code_expr << oper_buf;
		rightOperand_->PrintExpressionCode(code);
	}
		break;
	case oper_gt:{
		oper_buf[0] = '>';
		leftOperand_->PrintExpressionCode(code);
		code.code_expr << oper_buf;
		rightOperand_->PrintExpressionCode(code);
	}
		break;
	case oper_le:{
		oper_buf[0] = '<'; oper_buf[1] = '=';
		leftOperand_->PrintExpressionCode(code);
		code.code_expr << oper_buf;
		rightOperand_->PrintExpressionCode(code);
	}
		break;
	case oper_ge:{
		oper_buf[0] = '>'; oper_buf[1] = '=';
		leftOperand_->PrintExpressionCode(code);
		code.code_expr << oper_buf;
		rightOperand_->PrintExpressionCode(code);
	}
		break;
	case oper_iseq:{
		oper_buf[0] = '='; oper_buf[1] = '=';
		leftOperand_->PrintExpressionCode(code);
		code.code_expr << oper_buf;
		rightOperand_->PrintExpressionCode(code);
	}
		break;
	case oper_isneq: {
		oper_buf[0] = '!'; oper_buf[1] = '=';
		leftOperand_->PrintExpressionCode(code);
		code.code_expr << oper_buf;
		rightOperand_->PrintExpressionCode(code);
	}
		break;
	case oper_assgn:
		print_oper_assgn(code);
		break;
	case oper_or:{
		oper_buf[0] = '|'; oper_buf[1] = '|';
		leftOperand_->PrintExpressionCode(code);
		code.code_expr << oper_buf;
		rightOperand_->PrintExpressionCode(code);
	}
		break;
	case oper_and:{
		oper_buf[0] = '&'; oper_buf[1] = '&';
		leftOperand_->PrintExpressionCode(code);
		code.code_expr << oper_buf;
		rightOperand_->PrintExpressionCode(code);
	}
		break;
	default:
		code.code_expr << " unhandled operator type_ in AbstractExpression  ";
		print_err(compiler_sem_err
			  , " unhandled operator type_ in AbstractExpression  ",
			  line_no, __LINE__, __FILE__);
	}
	if (qscript_debug::DEBUG_BinaryExpression)
		code.code_expr << "/* EXIT BinaryExpression::PrintExpressionCode */" << endl;
}

BinaryExpression::~BinaryExpression()
{
	using qscript_parser::mem_addr;
	for (int32_t i = 0; i< mem_addr.size(); ++i){
		if (this == mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr = 0;
			debug_log_file << "BinaryExpression::~BinaryExpression setting mem_addr: " << this  <<" = 0" << endl;
			break;
		}
	}
	debug_log_file << "deleting BinaryExpression: exprOperatorType_: " << exprOperatorType_ << endl;
	if (leftOperand_) { delete leftOperand_; leftOperand_ = 0;}
	if (rightOperand_) { delete rightOperand_; rightOperand_ = 0;}
}

Unary2Expression::~Unary2Expression()
{
	using qscript_parser::mem_addr;
	for (int32_t i = 0; i< mem_addr.size(); ++i){
		if (this == mem_addr[i].mem_ptr){
			debug_log_file << "Unary2Expression::~Unary2Expression setting mem_addr: " << this << " = 0" << endl;
			mem_addr[i].mem_ptr = 0;
			break;
		}
	}
	debug_log_file << "deleting Unary2Expression: exprOperatorType_: " << exprOperatorType_ << endl;
	if (exprOperatorType_ == oper_func_call){
		//cout << "line_no: " << line_no << endl;
	}
	//if (text) { free( text) ; text = 0; }
	if (text) {
		free(text) ; text = 0;
		debug_log_file << "Unary2Expression::~Unary2Expression text:"
			<< text << endl;

	}
	if (operand_) { delete operand_; operand_ = 0; }
	if (operand2_) { delete operand2_; operand2_ = 0;}
}

BinaryExpression::BinaryExpression(AbstractExpression* llop
				   , AbstractExpression* lrop
				   , ExpressionOperatorType letype)
	: AbstractExpression(letype), leftOperand_(llop), rightOperand_(lrop)
{
	//cerr << "ENTER BinaryExpression::BinaryExpression: " << endl;
	if (exprOperatorType_ != oper_assgn &&
	    (leftOperand_->exprOperatorType_ == oper_blk_arr_assgn
	     ||rightOperand_->exprOperatorType_ == oper_blk_arr_assgn))
	{
		type_ = ERROR_TYPE;
		++no_errors;
		print_err(compiler_sem_err,
			"error: oper_blk_arr_assgn: used in binary AbstractExpression ",
			line_no, __LINE__, __FILE__);
	} else if (exprOperatorType_  == oper_assgn) {
		if ( (!leftOperand_->IsLValue()) ) {
			type_ = ERROR_TYPE;
			++no_errors;
			print_err(compiler_sem_err,
				"oper_assgn error: lhs of "
				"assignment should be lvalue ",
				line_no, __LINE__, __FILE__);
		}
		DataType typ1 = leftOperand_->type_;
		DataType typ2 = rightOperand_->type_;
		if (!void_check(leftOperand_->type_, rightOperand_->type_
			       , type_)){
			print_err(compiler_sem_err,
				"oper_assgn error: operand_ data types on "
				"lhs and rhs should be of non-VOID type",
				line_no, __LINE__, __FILE__);
			type_ = ERROR_TYPE;
			++no_errors;
		}
		if (typ1 == QUESTION_TYPE){
			//cerr << " lhs is of QUESTION_TYPE " << endl;
			Unary2Expression* lhs
				= static_cast<Unary2Expression*>(leftOperand_);
			const SymbolTableEntry * symp = lhs->get_symp_ptr();
			//cerr << "Question questionName_: " << symp->name_ << endl;
			AbstractQuestion* q = find_in_question_list(symp->name_);
			if (!q) {
				stringstream s;
				s << "Question not found in symbol table after parsing input" << endl;
				print_err(compiler_internal_error, s.str(),
					  line_no, __LINE__, __FILE__);
			} else {
				if (q->q_type != spn){
					stringstream s;
					s << "Direct assignment to AbstractQuestion only allowed for SPN question_type" << endl;
					print_err(compiler_internal_error, s.str(),
						line_no, __LINE__, __FILE__);
				}
			}
		} else if (!check_type_compat(typ1, typ2)){
			type_ = ERROR_TYPE;
			stringstream s;
			s << "oper_assgn error: operand_ data types on lhs and rhs should be compatible, ";
			string lhs_hr_type = human_readable_type(typ1);
			string rhs_hr_type = human_readable_type(typ2);
			s << "\tlhs type: " << lhs_hr_type
			  << ", rhs type: " << rhs_hr_type << endl;
			print_err(compiler_sem_err, s.str(),
				  line_no, __LINE__, __FILE__);
		}
	} else
		switch(exprOperatorType_) {
		case oper_plus:
		case oper_minus:
		case oper_mult:
		case oper_div:
		case oper_mod:
		case oper_le:
		case oper_lt:
		case oper_ge :
		case oper_gt :
		case oper_isneq :
		case oper_iseq :
		case oper_or :
		case oper_and :
			if (void_check(leftOperand_->type_
				       , rightOperand_->type_, type_)/*true*/) {
				DataType l_op_type = leftOperand_->type_;
				if ( (leftOperand_->exprOperatorType_ == oper_name
				      || leftOperand_->exprOperatorType_ == oper_arrderef)
				     && leftOperand_->type_ == QUESTION_TYPE) {
					Unary2Expression * un2expr = dynamic_cast<Unary2Expression*>
						(leftOperand_);
					l_op_type = un2expr->symbolTableEntry_->question_->dt;
				}
				DataType r_op_type = rightOperand_->type_;
				if ( (rightOperand_->exprOperatorType_ == oper_name
				      || rightOperand_->exprOperatorType_ == oper_arrderef)
				     && rightOperand_->type_ == QUESTION_TYPE) {
					Unary2Expression * un2expr = dynamic_cast<Unary2Expression*>
						(rightOperand_);
					r_op_type = un2expr->symbolTableEntry_->question_->dt;
				}
				if ( 	exprOperatorType_ == oper_le ||
					exprOperatorType_ == oper_lt ||
					exprOperatorType_ == oper_ge ||
					exprOperatorType_ == oper_gt ||
					exprOperatorType_ == oper_isneq ||
					exprOperatorType_ == oper_iseq ||
					exprOperatorType_ == oper_or ||
					exprOperatorType_ == oper_and) {
					type_ = BOOL_TYPE;
				} else {
					type_ = lcm_type(l_op_type, r_op_type);
				}
			}
			if (exprOperatorType_ == oper_mod
			    && !( (is_of_int_type(leftOperand_->type_)
				    || (leftOperand_->type_ == QUESTION_TYPE))
				 && is_of_int_type(rightOperand_->type_))) {
				print_err(compiler_sem_err,
					  " operands of % should be of type int32_t/char only", line_no, __LINE__, __FILE__);
				cerr << "leftOperand_ type: is " << leftOperand_->type_ << endl;
				//++no_errors;
				type_ = ERROR_TYPE;
			}
			break;
		default:
			print_err(compiler_internal_error, " INTERNAL ERROR: default case of BinaryExpression", line_no, __LINE__, __FILE__);
		}
	//cerr << "EXIT BinaryExpression::BinaryExpression: " << endl;
}

Unary2Expression::Unary2Expression(struct SymbolTableEntry * lsymp)
	: AbstractExpression(oper_name,lsymp->type_)
	, symbolTableEntry_(lsymp), intSemanticValue_(0)
	, doubleSemanticValue_(0), func_index_in_table(-1)
	, text(0), column_no(-1), operand_(0), operand2_(0)
{ }

map<string, SymbolTableEntry*>::iterator find_in_symtab(string id);
Unary2Expression::Unary2Expression(char* ltxt, ExpressionOperatorType le_type)
	: AbstractExpression(le_type, INT8_TYPE), symbolTableEntry_(0)
	, intSemanticValue_(0), doubleSemanticValue_(0)
	, func_index_in_table(-1), text(0), column_no(-1)
	, operand_(0), operand2_(0)
{
	if(qscript_debug::DEBUG_Unary2Expression)
		cerr << __PRETTY_FUNCTION__ << endl;
	if (exprOperatorType_ == oper_text_expr){
		type_ = STRING_TYPE;
		text = ltxt;
	} else if (exprOperatorType_ == oper_name
		  || exprOperatorType_  ==  oper_to_string) {
		map<string,SymbolTableEntry*>::iterator sym_it =
			find_in_symtab(ltxt);
		using qscript_parser::active_scope;
		if (sym_it == active_scope->SymbolTable.end()){
			string err_msg = "Error: could not find:"
				+ string(ltxt) + "  in symbol table  ";
			print_err(compiler_sem_err, err_msg
					, line_no, __LINE__, __FILE__);
			type_ = ERROR_TYPE;
		} else {
			symbolTableEntry_ = sym_it->second;
			type_ = symbolTableEntry_->type_;
			if (exprOperatorType_ == oper_name &&
			   (type_ == QUESTION_TYPE
			    || type_ == QUESTION_ARR_TYPE)){
				if (symbolTableEntry_->question_->q_type != spn){
					stringstream s;
					s << "Usage of Questions in Expressions only allowed for SPN question_type" << endl;
					print_err(compiler_sem_err, s.str(),
						line_no, __LINE__, __FILE__);
				} else {
					type_ = symbolTableEntry_->type_;
				}
			} else if (exprOperatorType_  ==  oper_name) {
				// a normal named variable which is not a question
				type_ = symbolTableEntry_->type_;
			}  else if (exprOperatorType_ == oper_to_string){
				if (type_ == QUESTION_TYPE
				   || type_ == QUESTION_ARR_TYPE){
					type_ = STRING_TYPE;
				} else {
					stringstream s;
					s << "Currently oper_to_string is only allowed for question variables" << endl;
					print_err(compiler_sem_err, s.str(),
						line_no, __LINE__, __FILE__);
					type_ = ERROR_TYPE;
				}
			} else {
				stringstream s;
				s << "Unhandled case in FILE: " << __FILE__
					<< " LINE: " << __LINE__
					<< " function: " << __PRETTY_FUNCTION__
					<< endl;
				print_err(compiler_sem_err, s.str(),
					line_no, __LINE__, __FILE__);
			}
		}
	} else if (exprOperatorType_ == oper_isanswered) {
		map<string,SymbolTableEntry*>::iterator sym_it =
			find_in_symtab(ltxt);
		DataType symbol_type = sym_it->second->type_;
		using qscript_parser::active_scope;
		if (sym_it == active_scope->SymbolTable.end()) {
			string err_msg = "Error: could not find:"
				+ string(ltxt) + "  in symbol table  ";
			print_err(compiler_sem_err, err_msg
					, line_no, __LINE__, __FILE__);
			type_ = ERROR_TYPE;
		} else {
			symbolTableEntry_ = sym_it->second;
			if (symbol_type == QUESTION_TYPE
			    || symbol_type == QUESTION_ARR_TYPE) {
				type_ = BOOL_TYPE;
			} else {
				string err_msg = "Error: isanswered Can only be called for question types ";
				print_err(compiler_sem_err, err_msg
						, line_no, __LINE__, __FILE__);
				type_ = ERROR_TYPE;
			}
		}
	} else if (exprOperatorType_ == oper_count) {
		map<string,SymbolTableEntry*>::iterator sym_it =
			find_in_symtab(ltxt);
		DataType symbol_type = sym_it->second->type_;
		using qscript_parser::active_scope;
		if (sym_it == active_scope->SymbolTable.end()) {
			string err_msg = "Error: could not find:"
				+ string(ltxt) + "  in symbol table  ";
			print_err(compiler_sem_err, err_msg
					, line_no, __LINE__, __FILE__);
			type_ = ERROR_TYPE;
		} else {
			symbolTableEntry_ = sym_it->second;
			if ( symbol_type == QUESTION_TYPE
			    || symbol_type == QUESTION_ARR_TYPE) {
				type_ = INT32_TYPE;
			} else {
				string err_msg = "Error: count Can only be called for question types ";
				print_err(compiler_sem_err, err_msg
						, line_no, __LINE__, __FILE__);
				type_ = ERROR_TYPE;
			}
		}
	} else {
		stringstream err_mesg;
		err_mesg << "Constructor Unary2Expression(char* ltxt, ExpressionOperatorType le_type)"
			"in FILE: " << __FILE__ << ", LINE: " << __LINE__
			<< " only handles exprOperatorType_: oper_text_expr, oper_name, oper_to_string"
			<< " ... if it is supposed to handle other exprOperatorType_(s) please fix this";
		print_err(compiler_sem_err, err_mesg.str(), line_no, __LINE__, __FILE__);
	}
}

#include <sstream>
Unary2Expression::Unary2Expression(ExpressionOperatorType le_type, string name
				   , AbstractExpression* arr_index)
	: AbstractExpression(le_type, ERROR_TYPE), symbolTableEntry_(0)
	, intSemanticValue_(0)
	, doubleSemanticValue_(0), func_index_in_table(-1), text(0)
	, column_no(-1), operand_(arr_index),  operand2_(0)
{
	//cerr << "ENTER Unary2Expression::Unary2Expression :name" << name
	//	<< " with arr_index" << endl;

	//if (le_type == oper_arrderef){
	//	cerr << " arr_deref_type " << endl;
	//}
	using qscript_parser::active_scope;
	map<string,SymbolTableEntry*>::iterator sym_it = find_in_symtab(name);
	if (sym_it == active_scope->SymbolTable.end()){
		std::stringstream s;
		s << "Error: Array indexing AbstractExpression: could not find name: "
			<< name <<"  in symbol table: lineno: "
			<< line_no << "\n";
		print_err(compiler_sem_err, s.str()
				, line_no, __LINE__, __FILE__);
	} else {
		SymbolTableEntry* se = sym_it->second;
		symbolTableEntry_ = se;
		if (symbolTableEntry_->question_) {
			if (symbolTableEntry_->question_->q_type != spn) {
				std::stringstream s;
				s << "Multi-coded question cannot be used in a array expression" << "\n";
				print_err(compiler_sem_err, s.str()
						, line_no, __LINE__, __FILE__);
			}
		}
		DataType l_e_type = arr_index->type_;
		if (is_of_int_type(l_e_type)){
			DataType nametype =arr_deref_type(se->type_);
			if (nametype == ERROR_TYPE) {
				std::stringstream s;
				s << "ERROR: Array indexing AbstractExpression Variable being indexed not of Array Type : Error: lineno: " << line_no << "\n";
				print_err(compiler_sem_err, s.str()
						, line_no, __LINE__, __FILE__);
			} else {
				type_ = nametype;
			}
		} else {
			stringstream s;
			s << "ERROR: Array index not of Type Int : Error: lineno: " << line_no << "\n";
			print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		}
	}
}

Unary2Expression::Unary2Expression(ExpressionOperatorType le_type, string name
				   , AbstractExpression* arr_index
				   , AbstractExpression* arr_index2)
	: AbstractExpression(le_type, ERROR_TYPE), symbolTableEntry_(0)
	, intSemanticValue_(0), doubleSemanticValue_(0)
	, func_index_in_table(-1), text(0)
	, column_no(-1), operand_(arr_index), operand2_(arr_index2)
{
	SymbolTableEntry* se = 0;
	map<string,SymbolTableEntry*>::iterator sym_it1 = find_in_symtab(name);
	using qscript_parser::active_scope;
	if (sym_it1 == active_scope->SymbolTable.end()) {
		std::stringstream s;
		s << "Error: Block Array assignment AbstractExpression: could not find name: "
			<< name <<"  in symbol table: lineno: "
			<< line_no << "\n";
		print_err(compiler_sem_err, s.str(), line_no
				, __LINE__, __FILE__);
	} else {
		se = sym_it1->second;
		symbolTableEntry_ = se;
	}
	if (!(se)){
		std::stringstream s;
		s << "Error: Block Array assignment AbstractExpression: could not find name: "
			<< name <<"  in symbol table: lineno: "
			<< line_no << "\n";
		print_err(compiler_sem_err, s.str(), line_no
				, __LINE__, __FILE__);
	}  else {
		DataType e_type1 = arr_index->type_;
		DataType e_type2 = arr_index2->type_;
		if (is_of_int_type (e_type1)&&
			is_of_int_type(e_type2)	){
			DataType d1 = arr_deref_type(se->type_);
			if (d1 == ERROR_TYPE){
				std::stringstream s;
				s << "ERROR: Block Array assignment AbstractExpression Variable: "
					<< name << " being indexed not of Array Type : Error: lineno: "
					<< line_no << "\n";
				print_err(compiler_sem_err, s.str()
						, line_no, __LINE__, __FILE__);
			} else {
				type_ = d1;
			}
		} else {
			stringstream s;
			s <<  "ERROR: NAME  =NAME[EXPR, EXPR] EXPR should be of type int32_t or char: lineno: "
				<< line_no << "\n";
			print_err(compiler_sem_err, s.str()
					, line_no, __LINE__, __FILE__);
		}
	}
	//free($1);
}

bool Unary2Expression::IsLValue()
{
	if (exprOperatorType_ == oper_name|| exprOperatorType_ == oper_arrderef){
		return true;
	} else {
		return false;
	}
}

Unary2Expression::Unary2Expression(int32_t l_isem_value)
	: AbstractExpression(oper_num), symbolTableEntry_(0)
	, intSemanticValue_(l_isem_value), doubleSemanticValue_(0), func_index_in_table(-1)
	, text(0), column_no(-1), operand_(0), operand2_(0)
{
	if (intSemanticValue_ >= SCHAR_MIN && intSemanticValue_ <= SCHAR_MAX){
		type_ = INT8_TYPE;
	} else if (intSemanticValue_ >=  SHRT_MIN
		   && intSemanticValue_ <= SHRT_MAX){
		type_ = INT16_TYPE;
	} else if (intSemanticValue_ >=  INT_MIN && intSemanticValue_ <= INT_MAX){
		type_ = INT32_TYPE;
	} else {
		++no_errors;
		cerr << "very  large integer unhandleable type most probably";
		type_ = ERROR_TYPE;
	}
}


Unary2Expression::Unary2Expression(ExpressionOperatorType le_type
				   , DataType ldt, AbstractExpression* e_list
				   , int32_t lfunc_index_in_table)
	: AbstractExpression(le_type, ldt),  symbolTableEntry_(0)
	, intSemanticValue_(0), doubleSemanticValue_(0)
	, func_index_in_table(lfunc_index_in_table)
	, text(0), column_no(-1), operand_(e_list), operand2_(0)
{}

Unary2Expression::Unary2Expression(double l_dsem_value)
	: AbstractExpression(oper_float,FLOAT_TYPE), symbolTableEntry_(0)
	, intSemanticValue_(0), doubleSemanticValue_(l_dsem_value)
	, func_index_in_table(-1), text(0), column_no(-1)
	, operand_(0), operand2_(0)
{}

Unary2Expression::Unary2Expression(DataType d)
	: AbstractExpression(oper_err,d), symbolTableEntry_(0)
	, intSemanticValue_(0), doubleSemanticValue_(0)
	, func_index_in_table(-1), text(0)
	, column_no(-1), operand_(0), operand2_(0)
{}


bool Binary2Expression::IsConst()
{
	return false;
}

bool Binary2Expression::IsIntegralExpression()
{
	return false;
}

Binary2Expression::Binary2Expression(AbstractExpression* llop
				     , string name
				     , ExpressionOperatorType letype)
	: AbstractExpression(letype), leftOperand_(0), leftOperand2_(0)
	  , xs(0), rhsQuestion_(0)
{
	switch(exprOperatorType_){
		case oper_in: {
			leftOperand2_=llop;
			AbstractQuestion* q = find_in_question_list(name);
			if (q == 0) {
				stringstream err_msg ;
				err_msg <<  "could not find NAME: " << name << " in the question symbol table";
				print_err(compiler_sem_err, err_msg.str(),
					line_no, __LINE__, __FILE__);
				type_ = ERROR_TYPE;
			}  else {
				rhsQuestion_ = q;
			}


			type_ = BOOL_TYPE;
		}
		break;
		default: {
			leftOperand_ = 0;
			type_ = ERROR_TYPE;
			string err_msg = "Binary2Expression:: operator in exprOperatorType_ can only be oper_in";
			print_err(compiler_sem_err, err_msg
					, line_no, __LINE__, __FILE__);
			type_ = ERROR_TYPE;
		}
	}
}

Binary2Expression::Binary2Expression(AbstractExpression* llop
				     , XtccSet& l_rd
				     , ExpressionOperatorType letype)
	:AbstractExpression(letype), leftOperand_(0), leftOperand2_(0)
	 		, xs(0), rhsQuestion_(0)
{
	//cerr << "Binary2Expression::Binary2Expression" << endl;
	switch(exprOperatorType_){
		case oper_in:
			switch( llop->exprOperatorType_){
			case oper_name:
			case oper_arrderef:
				type_ = BOOL_TYPE;
				//cerr << "Binary2Expression::static_cast" << endl;
				leftOperand_=
					static_cast<Unary2Expression*>(llop);
				xs = new XtccSet(l_rd);
				break;
			default:
				leftOperand_ = 0;
				type_ = ERROR_TYPE;
				string err_msg = "Binary2Expression:: lhs operator for oper_in can only be NAME or NAME[INDEX]";
				print_err(compiler_sem_err, err_msg,
					line_no, __LINE__, __FILE__);
				type_ = ERROR_TYPE;
			}
			break;
		default: {
			leftOperand_ = 0;
			type_ = ERROR_TYPE;
			string err_msg = "Binary2Expression:: operator in exprOperatorType_ can only be oper_in";
			print_err(compiler_sem_err, err_msg
					, line_no, __LINE__, __FILE__);
			type_ = ERROR_TYPE;
		}
	}
}

void Binary2Expression::PrintTemporaryStruct(ExpressionCompiledCode &code)
{
	stringstream mesg;
	mesg << " shouldnt i be using an XtccSet here directly - it looks like im doing the same work 2ice and if i used the set the generated code would be smaller\n";
	cerr << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ 
		<< " " << mesg.str();
	if (qscript_debug::DEBUG_Binary2Expression)
		code.code_bef_expr << " /* ENTER Binary2Expression::PrintTemporaryStruct */ " << endl;
	//string struct_name = get_temp_name();
	string struct_name = qscript_parser::temp_name_generator.GetNewName();
	code.code_bef_expr << "\tstruct " <<  struct_name.c_str() << "{\n";
	code.code_bef_expr << "\t\tconst int32_t size_ran_indiv;\n";
	code.code_bef_expr << "\t\tconst int32_t size_start_end;\n";
	code.code_bef_expr << "\t\tvector<int32_t> ran_indiv;\n";
	code.code_bef_expr << "\t\tvector< pair<int32_t,int32_t> > ran_start_end;\n";
	code.code_bef_expr << "\t\t" << struct_name.c_str()
		<< "(): size_ran_indiv(" << xs->indiv.size() //r_data->icount
		<< "), size_start_end(" <<  xs->range.size() //r_data->rcount << "),\n";
		<< "),\n";
	code.code_bef_expr << "\t\t\tran_indiv(size_ran_indiv), ran_start_end(size_start_end){\n";
	//fprintf(stderr, "Binary2Expression::PrintExpressionCode(): printed constructor");
	for(int32_t i = 0; i< xs->range.size() ; ++i){
		code.code_bef_expr << "\t\t\tran_start_end[" << i
			<< "] = pair<int32_t,int32_t>("
			<< xs->range[i].first
			<< "," << xs->range[i].second << ");\n";
	}

	int32_t k = 0;
	for(set<int32_t>::iterator iter = xs->indiv.begin();
		iter != xs->indiv.end(); ++iter, ++k){
		code.code_bef_expr << "\t\t\tran_indiv["
			<< k << "] = " << *iter <<";\n";
	}
	code.code_bef_expr <<  "\t\t}\n";

	code.code_bef_expr << "\t\tbool exists(int32_t key){\n";
	code.code_bef_expr << "\t\t\tfor(int32_t i = 0; i<size_start_end; ++i){\n";
	code.code_bef_expr << "\t\t\t\tif (key  >= ran_start_end[i].first && key  <= ran_start_end[i].second){\n";
	code.code_bef_expr << "\t\t\t\t\treturn true;\n";
	code.code_bef_expr << "\t\t\t\t}\n";
	code.code_bef_expr << "\t\t\t}\n";
	code.code_bef_expr << "\t\t\tfor(int32_t i = 0; i< size_ran_indiv; ++i){\n";
	code.code_bef_expr << "\t\t\t\tif (key == ran_indiv[i]){\n";
	code.code_bef_expr << "\t\t\t\t\treturn true;\n";
	code.code_bef_expr << "\t\t\t\t}\n";
	code.code_bef_expr << "\t\t\t}\n";
	code.code_bef_expr << "\t\t\treturn false;\n";
	code.code_bef_expr << "\t\t}\n";

	code.code_bef_expr << "\t\tbool contains_subset(set<int32_t> & set_data){\n";
	code.code_bef_expr << "\t\t\tbool val_exists = false;\n";
	code.code_bef_expr << "\t\t\tfor(\tset<int32_t>::iterator it = set_data.begin();\n";
	code.code_bef_expr << "\t\t\t\tit != set_data.end(); ++it){\n";
	code.code_bef_expr << "\t\t\t\t\tval_exists = exists(*it);\n";
	code.code_bef_expr << "\t\t\t\tif (!val_exists){\n";
	code.code_bef_expr << "\t\t\t\t\treturn false;\n";
	code.code_bef_expr << "\t\t\t\t}\n";
	code.code_bef_expr << "\t\t\t}\n";
	code.code_bef_expr << "\t\t\t/*if (!val_exists){\n";
	code.code_bef_expr << "\t\t\t\treturn false;\n";
	code.code_bef_expr << "\t\t\t}*/\n";
	code.code_bef_expr << "\t\treturn true;\n";
	code.code_bef_expr << "\t\t}\n";

	code.code_bef_expr << "\t} ";

	if (qscript_debug::DEBUG_Binary2Expression)
		code.code_bef_expr << " /* EXIT Binary2Expression::PrintTemporaryStruct */ " << endl;
}

#if 0
void PrintTemporaryXtccSet(ExpressionCompiledCode &code, XtccSet * & xs)
{
	stringstream temp_code;
	string set_name = qscript_parser::temp_set_name_generator.GetNewName();
	temp_code << "XtccSet " << set_name << ";\n";

	//fprintf(stderr, "Binary2Expression::PrintExpressionCode(): printed constructor");
	for(int32_t i = 0; i< xs->range.size() ; ++i){
		temp_code << set_name << ".add_range("
			<< xs->range[i].first
			<< ", " << xs->range[i].second << ");\n";
	}

	{
		int32_t k = 0;
		for(set<int32_t>::iterator iter = xs->indiv.begin();
			iter != xs->indiv.end(); ++iter, ++k){
			temp_code << set_name << ".add_indiv(" 
				 << *iter << ");\n";
		}
	}
	code.code_bef_expr << temp_code.str();

}
#endif /* 0 */

void Binary2Expression::PrintExpressionText(ostringstream & s)
{

	if (leftOperand_ != 0) {
		//PrintTemporaryStruct(code);
		//code.code_bef_expr << "\t} "
		//string struct_name1 = get_temp_name();
		//code.code_bef_expr <<  struct_name1 <<";\n";
		//PrintTemporaryXtccSet(code, xs);
		// use xs in creating base text statement
		switch(leftOperand_->get_symp_ptr()->type_){
		case INT8_TYPE:
		case INT16_TYPE:
		case INT32_TYPE:
		case FLOAT_TYPE:
		case DOUBLE_TYPE:
		case INT8_ARR_TYPE:
		case INT16_ARR_TYPE:
		case INT32_ARR_TYPE:
		case FLOAT_ARR_TYPE:
		case DOUBLE_ARR_TYPE:
		case INT8_REF_TYPE:
		case INT16_REF_TYPE:
		case INT32_REF_TYPE:
		case FLOAT_REF_TYPE:
		case DOUBLE_REF_TYPE:
		case BOOL_TYPE:{


			s << "unhandled case" << __LINE__ << ", " << __FILE__ << ", " << __PRETTY_FUNCTION__ ;
		}
			break;
		case QUESTION_TYPE:{

			const SymbolTableEntry * se = leftOperand_->get_symp_ptr();
			AbstractQuestion * q= se->question_;

			NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q);

			s << "All those respondents who have selected: ";
			if (nq) {
				s << " certain values in nq";
			} else {
				s << " certain values in rq";
			}
		}
			break;
		case QUESTION_ARR_TYPE:{

			s << "QUESTION_ARR_TYPE not yet handled" << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__;
		}
		break;
		default: {
			std::stringstream s;
			s << "file: " << __FILE__
			  << ", line: " << __LINE__ << endl;
			print_err(compiler_internal_error, s.str()
				  , line_no, __LINE__, __FILE__);
		} // note this closes the default label
		}
	} else /* if leftOperand2_ !=0 */{

		ExpressionCompiledCode expr2_code;
		leftOperand2_->PrintExpressionCode(expr2_code);
		
		NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*> (rhsQuestion_);
		if (Unary2Expression * un2expr = dynamic_cast<Unary2Expression*> (leftOperand2_)) {
			if (un2expr->exprOperatorType_ == oper_num ) {
				s << " All Respondents who have coded \\\"" << un2expr->intSemanticValue_ << "\\\" i.e. ";
				if (nq) {
					vector<stub_pair> & vec= (nq->nr_ptr->stubs);
					for (int i=0; i<vec.size(); ++i) {
						if (vec[i].code == un2expr->intSemanticValue_) {
							s << vec[i].stub_text;
							break;
						}
					}
				}
				s << " at " << rhsQuestion_->questionName_;
			} else if (un2expr->exprOperatorType_ == oper_name) {
				s << rhsQuestion_->questionName_ << " oper_in unhandled case leftOperand2_ is oper_name " << __LINE__ << ", " << __FILE__ << ", " << __PRETTY_FUNCTION__ ;
				qscript_parser::dynamic_base_text_question = rhsQuestion_;
				qscript_parser::flag_dynamic_base_text = true;

			} else {
				s << rhsQuestion_->questionName_ << " oper_in unhandled case " << __LINE__ << ", " << __FILE__ << ", " << __PRETTY_FUNCTION__ ;
			}
		} else {
			s << rhsQuestion_->questionName_ << " oper_in unhandled case " << __LINE__ << ", " << __FILE__ << ", " << __PRETTY_FUNCTION__ ;
		}
	}
}

void Binary2Expression::PrintExpressionCode(ExpressionCompiledCode &code)
{
	if (qscript_debug::DEBUG_Binary2Expression)
		code.code_bef_expr << "/* ENTER Binary2Expression::PrintExpressionCode */" << endl;

	if (leftOperand_ != 0) {
		//PrintTemporaryStruct(code);
		//code.code_bef_expr << "\t} "
		//string struct_name1 = get_temp_name();
		//code.code_bef_expr <<  struct_name1 <<";\n";
		PrintTemporaryXtccSet(code, xs);
		switch(leftOperand_->get_symp_ptr()->type_){
		case INT8_TYPE:
		case INT16_TYPE:
		case INT32_TYPE:
		case FLOAT_TYPE:
		case DOUBLE_TYPE:
		case INT8_ARR_TYPE:
		case INT16_ARR_TYPE:
		case INT32_ARR_TYPE:
		case FLOAT_ARR_TYPE:
		case DOUBLE_ARR_TYPE:
		case INT8_REF_TYPE:
		case INT16_REF_TYPE:
		case INT32_REF_TYPE:
		case FLOAT_REF_TYPE:
		case DOUBLE_REF_TYPE:
		case BOOL_TYPE:{
				/*
			string test_bool_var_name = get_temp_name();
			code.code_bef_expr <<  "bool "
					   <<  test_bool_var_name
					   << " = " << struct_name1
					   << ".exists(";
			//<< name.c_str() << ");\n";
			//ostringstream code_bef_expr1_discard, code_expr1;
			ExpressionCompiledCode expr1_code;
			leftOperand_->PrintExpressionCode(
				expr1_code);
			code.code_bef_expr << expr1_code.code_expr.str() << ");\n";
			code.code_expr << test_bool_var_name.c_str() << " ";
				*/


			// string test_bool_var_name1 = get_temp_name();
			string test_bool_var_name1 = qscript_parser::temp_name_generator.GetNewName();
			code.code_bef_expr <<  "bool " <<  test_bool_var_name1
				<< " = " << qscript_parser::
					temp_set_name_generator.GetCurrentName()
				<< ".exists(";
			ExpressionCompiledCode expr2_code;
			leftOperand_->PrintExpressionCode(expr2_code);
			code.code_bef_expr << expr2_code.code_expr.str() << ");\n";
			code.code_expr << test_bool_var_name1 << " ";
		}
			break;
		case QUESTION_TYPE:{

			//string test_bool_var_name2 = get_temp_name();
			string test_bool_var_name2 = qscript_parser::temp_name_generator.GetNewName();
			code.code_bef_expr <<  "bool " <<  test_bool_var_name2.c_str()
					   << " = " << qscript_parser::
					   	temp_set_name_generator.GetCurrentName()
					   << ".contains_subset(";
			//ostringstream code_bef_expr1_discard, code_expr1;
			//ExpressionCompiledCode expr1_code;
			//leftOperand_->PrintExpressionCode(expr1_code);
			code.code_bef_expr
				//<< expr1_code.code_bef_expr.str()
				//<< expr1_code.code_expr.str()
				<< leftOperand_->get_symp_ptr()->name_
				<< "->input_data"
				<< ");\n";
			code.code_expr << test_bool_var_name2.c_str() << " ";


		}
			break;
		case QUESTION_ARR_TYPE:{

			//string test_bool_var_name2 = get_temp_name();
			string test_bool_var_name2 = qscript_parser::temp_name_generator.GetNewName();
			code.code_bef_expr <<  "bool " <<  test_bool_var_name2.c_str()
					   << " = " << qscript_parser::
					   	temp_set_name_generator.GetCurrentName()
					   << ".contains_value(";
			ostringstream code_bef_expr1_discard, code_expr1;
			ExpressionCompiledCode expr1_code;
			leftOperand_->PrintExpressionCode(expr1_code);
			code.code_bef_expr
				//<< expr1_code.code_bef_expr.str()
				<< expr1_code.code_expr.str()
				//<< leftOperand_->get_symp_ptr()->name_ << "_list.questionList["
				<< ");\n";
			code.code_expr << test_bool_var_name2.c_str() << " ";
			//std::stringstream s;
			//s << "Purposely Failing compilation here file: " << __FILE__
			//  << ", line: " << __LINE__ << endl;
			//code.code_expr << "/* " << s.str() << " */\n";
			//print_err(compiler_internal_error, s.str()
			//	  , line_no, __LINE__, __FILE__);


		}
		break;
		default: {
			std::stringstream s;
			s << "file: " << __FILE__
			  << ", line: " << __LINE__ << endl;
			print_err(compiler_internal_error, s.str()
				  , line_no, __LINE__, __FILE__);
		} // note this closes the default label
		}
	} else /* if leftOperand2_ !=0 */{
		code.code_expr  << "/* " << __PRETTY_FUNCTION__ 
			<< ", " << __LINE__ 
			<< ", " << __FILE__ 
			<< "   ";
		code.code_expr << " */" << endl;
		code.code_expr << rhsQuestion_->questionName_ << "->input_data.find(";
		leftOperand2_->PrintExpressionCode(code);
		code.code_expr << ") != " << rhsQuestion_->questionName_ << "->input_data.end()";
	}
	if (qscript_debug::DEBUG_Binary2Expression)
		code.code_expr << "/* EXIT Binary2Expression::PrintExpressionCode */" << endl;
}


Binary2Expression::~Binary2Expression()
{
	using qscript_parser::mem_addr;
	for (int32_t i = 0; i< mem_addr.size(); ++i){
		if (this == mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr = 0;
			debug_log_file << "Binary2Expression::~Binary2Expression setting mem_addr: " << this  <<" = 0" << endl;
			break;
		}
	}
	if (leftOperand_){
		delete leftOperand_; leftOperand_ = 0;
	}
	if (xs){
		delete xs; xs = 0;
	}
}

#if 0
string get_temp_name()
{
	// about a billion temporaries before we run out
	const int32_t max_temp = 10;
	static int32_t count = 0;
	char buffer[max_temp];
	char op_buf[max_temp];
	int32_t dividend = count;

	buffer[0] = '0'; buffer[1] = '\0';

	int32_t j = 0;
	do {
		int32_t rem = dividend%10;
		dividend = dividend/10;
		buffer[j++] = '0' + rem;
	} while (dividend>0);
	/*
	for(int32_t i = 0 ; dividend/10>0; dividend = dividend/10,++i,++j){
		//int32_t quot = dividend/10;
		int32_t rem = dividend%10;
		buffer[j] = '0' + rem;
	}
	*/
	buffer[j] = '\0';
	for(int32_t i = j-1; i >= 0; --i){
		op_buf[j-1-i] = buffer[i];
	}
	op_buf[j] = '\0';
	string s(op_buf);
	++count;
	//cout << s << endl;
	string s1 = "temp_"+s;
	return s1;
}
#endif /* 0 */


string human_readable_expr_type(ExpressionOperatorType exprOperatorType_)
{
	string s = "UNKNOWN EXPR TYPE";
	switch(exprOperatorType_){
	case oper_plus:
		s = "oper_plus";
		break;
	case oper_minus:
		s = "oper_minus";
		break;
	case oper_mult:
		s = "oper_mult";
		break;
	case oper_div:
		s = "oper_div";
		break;
	case oper_and:
		s = "oper_and";
		break;
	case oper_or:
		s = "oper_or";
		break;
	case oper_lt:
		s = "oper_lt";
		break;
	case oper_gt:
		s = "oper_gt";
		break;
	case oper_le:
		s = "oper_le";
		break;
	case oper_ge:
		s = "oper_ge";
		break;
	case oper_isneq:
		s = "oper_isneq";
		break;
	case oper_iseq:
		s = "oper_iseq";
		break;
	case oper_parexp:
		s = "oper_parexp";
		break;

	case oper_umin:
		s = "oper_umin";
		break;
	case oper_num:
		s = "oper_num";
		break;
	case oper_name:
		s = "oper_name";
		break;
	case oper_arrderef:
		s = "oper_arrderef";
		break;
	case oper_arr2deref:
		s = "oper_arr2deref";
		break;
	case oper_func_call:
		s = "oper_func_call";
		break;
	case oper_text_expr:
		s = "oper_text_expr";
		break;
	case oper_float:
		s = "oper_float";
		break;
	case oper_assgn:
		s = "oper_assgn";
		break;
	case oper_not:
		s = "oper_not";
		break;
	case oper_mod:
		s = "oper_mod";
		break;
	case oper_blk_arr_assgn:
		s = "oper_blk_arr_assgn";
		break;
	case oper_in:
		s = "oper_in";
		break;
	case oper_q_expr_in:
		s = "oper_q_expr_in";
		break;
	case oper_q_expr_arr_in:
		s = "oper_q_expr_arr_in";
		break;
	case oper_err:
		s = "oper_err";
		break;
	default:
		;
	}
	return s;
}
