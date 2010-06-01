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

#include <vector>
#include <fstream>
#include <sstream>
#include <climits>
#include <cstdlib>
#include "stmt.h"
#include "expr.h"
#include "scope.h"
#include "named_range.h"
#include "qscript_parser.h"
AbstractQuestion* find_in_question_list(string name);
using std::string;
using std::stringstream;
string get_temp_name();

//extern Scope* active_scope;
//extern ofstream debug_log_file;
//using namespace std;
//
//extern	vector <func_info*> func_info_table;
//extern vector<mem_addr_tab> mem_addr;
//extern vector <named_range*> named_stubs_list;
#include <iostream>
using qscript_parser::debug_log_file;
using qscript_parser::line_no;
using qscript_parser::no_errors;
using std::cout;
using std::cerr;
using std::endl;
AbstractExpression::~AbstractExpression()
{
	debug_log_file << "deleting AbstractExpression::~AbstractExpression(): base destructor for AbstractExpression" << endl;
	if(next_) {delete next_; next_=0; }
}

/*
	DataType AbstractExpression::get_type(){
		if(type_==oper_func_call){
			return func_info_table[index].return_type;
		}
		return type_;
	}
*/

int AbstractExpression::IsValid()
{
	//cout << "IsValid called" << endl;
	if (type_==ERROR_TYPE){
		return 0;
	} else return 1;
}

UnaryExpression::~UnaryExpression()
{
	using qscript_parser::mem_addr;
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "UnaryExpression::~UnaryExpression setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting UnaryExpression: exprOperatorType_" << exprOperatorType_ << endl;
	if (operand_) { delete operand_; operand_=0; }
}

UnaryExpression::UnaryExpression( AbstractExpression * l_operand 
		, ExpressionOperatorType le_type)
	: AbstractExpression(le_type), operand_(l_operand)
{
	if(operand_->exprOperatorType_==oper_blk_arr_assgn){
		print_err(compiler_sem_err, "oper_blk_arr_assgn: cannot be used with unary operators : line_no:",
			line_no, __LINE__, __FILE__);
	} else if(l_operand->type_==VOID_TYPE){
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
				type_ = INT8_TYPE;
			break;
			case oper_parexp:
				type_ = l_operand->type_;
			break;
			default:
				++no_errors;
				print_err(compiler_internal_error, " unknown unary operator applied to AbstractExpression. Internal compiler error ", 
					line_no, __LINE__, __FILE__);
		}
	}
}

bool UnaryExpression::IsIntegralExpression()
{
	return operand_->IsIntegralExpression();
}


//void UnaryExpression::PrintExpressionCode (FILE * edit_out)
void UnaryExpression::PrintExpressionCode (ostringstream& code_bef_expr, ostringstream & code_expr)
{
	code_expr << "/* UnaryExpression::PrintExpressionCode ENTER */" << endl;
	switch(exprOperatorType_){
		case oper_umin:{
			code_expr <<  "- ";
			operand_->PrintExpressionCode(code_bef_expr, code_expr);
		}
		break;

		case oper_not:{
			//fprintf(edit_out, "! ");
			code_expr <<  "! ";
			operand_->PrintExpressionCode(code_bef_expr, code_expr);
		}
		break;

		case oper_parexp:{
			code_expr <<  "(";
			operand_->PrintExpressionCode(code_bef_expr, code_expr);
			code_expr <<  ")";
			}
		break;
		default:
			code_expr <<  " un handled operator\n" ;

	}
	code_expr << "/* UnaryExpression::PrintExpressionCode EXIT */" << endl;
}

bool UnaryExpression::IsConst()
{
	return operand_->IsConst();
}


// will sort this out later
bool BinaryExpression::IsConst(){
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
void BinaryExpression::print_oper_assgn(ostringstream& code_bef_expr
		, ostringstream & code_expr)
{
	if(rightOperand_->exprOperatorType_ == oper_blk_arr_assgn &&
		( leftOperand_->exprOperatorType_==oper_name
		  ||leftOperand_->exprOperatorType_==oper_arrderef)){
		Unary2Expression* blk_e = 
			static_cast<Unary2Expression*> (rightOperand_);
		Unary2Expression* lhs = 
			static_cast<Unary2Expression*> (leftOperand_);
		code_expr << "/* DATA CONVERSION */\n";
		code_expr << "{int tmp1=";
		blk_e->operand_->PrintExpressionCode(code_bef_expr, code_expr);
		code_expr << ";\nint tmp2=";
		blk_e->operand2_->PrintExpressionCode(code_bef_expr, code_expr);
		code_expr << ";\n";
		switch(lhs->get_symp_ptr()->type_){
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
			case BOOL_TYPE:	{	
				if(leftOperand_->type_==FLOAT_TYPE) {
					code_expr << "if(tmp2-tmp1==sizeof(float)-1){\n";
					code_expr << "\tchar buff[sizeof(float)];int i,j;\n";
					code_expr << "\tfor(i=tmp1,j=0;i<=tmp2;++i,++j){\n";
					code_expr << "\t\tbuff[j]=" <<  blk_e->symbolTableEntry_->name_ << "[i];\n";
					code_expr << "\t}\n";
					code_expr << "\tvoid * v_ptr = buff;\n";
					code_expr << "\tfloat *f_ptr = static_cast<float *>(v_ptr);\n";
					
					code_expr << "\t" ;
					lhs->PrintExpressionCode(code_bef_expr, code_expr);
					code_expr << "=*f_ptr;\n";
					code_expr << "}else { cerr << \"runtime error: line_no : AbstractExpression out of bounds\" << " 
						<< line_no  <<";}\n}\n";
				} else if (leftOperand_->type_==INT32_TYPE){
					code_expr << "if(tmp2-tmp1==sizeof(int)-1){\n";
					code_expr << "\tchar buff[sizeof(int)];int i,j;\n";
					code_expr << "\tfor(i=tmp1,j=0;i<=tmp2;++i,++j){\n";
					code_expr << "\t\tbuff[j]=" << blk_e->symbolTableEntry_->name_ << "[i];\n";
					code_expr << "\t}\n";
					code_expr << "\tvoid * v_ptr = buff;\n";
					code_expr << "\tint *i_ptr = static_cast<int *>(v_ptr);\n";
					code_expr << "\t" ;
					lhs->PrintExpressionCode(code_bef_expr, code_expr);
					code_expr << "=*i_ptr;\n" ;
					code_expr << "}else { \n\tcerr << \"runtime error: line_no : AbstractExpression out of bounds\" <<"
						<< line_no << " ;}\n}\n";
				} else {
					std::stringstream s;
					s << "Error in code generation file: ";
					print_err(compiler_internal_error, s.str(), line_no, __LINE__, __FILE__);
					code_expr <<  "error\n";
				}
			}
			break;

			case QUESTION_TYPE:{
				std::stringstream s;
				s << "ASSIGNING to question_type named variable to be programmed  : ";
				print_err(compiler_internal_error, s.str(), line_no, __LINE__, __FILE__);
				code_expr <<  "error\n";
			}
			break;
			default:{
				std::stringstream s;
				s << "Un handled DataType for BinaryExpression";
				print_err(compiler_internal_error, s.str(), line_no, __LINE__, __FILE__);
				code_expr <<  "error\n";
			}
				
		}
	} else if (rightOperand_->exprOperatorType_ == oper_blk_arr_assgn && leftOperand_->exprOperatorType_==oper_blk_arr_assgn){
		std::stringstream s;
		s << "unhandled case LHS. Error in code generation file: ";
		print_err(compiler_internal_error, s.str(), line_no, __LINE__, __FILE__);
		code_expr <<  "error\n";
	}else {
		if(leftOperand_->type_==QUESTION_TYPE){
			Unary2Expression* lhs= 
				static_cast<Unary2Expression*>(leftOperand_);
			const SymbolTableEntry * symp = lhs->get_symp_ptr();
			AbstractQuestion* q = find_in_question_list(symp->name_);
			string cpp_data_type=human_readable_type(q->dt);
			string tmp_name = get_temp_name();
			
			code_expr << cpp_data_type << " " << tmp_name << "=";
			rightOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			code_expr << ";" << endl;
			code_expr << "if ( " 
				<< q->questionName_ << "->IsValid("<<  tmp_name
				<<  ")) {" << endl; 
			code_expr << q->questionName_ 
				<< "->input_data.clear();" << endl;
			code_expr << q->questionName_ << "->input_data.insert(";
			//rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			code_expr << tmp_name ;
			code_expr << ") ; " << endl ;
			code_expr << "} else {";
			code_expr << "cerr << \"runtime error - value assigned to AbstractQuestion: \" << \"" 
				<< q->questionName_ << "\"" << " << \" is not in allowed range: \" <<" << tmp_name << " << endl; " << endl;
			code_expr << "}" << endl;
			cerr << "WARNING : line: " << __LINE__ 
				<< ", file: " << __FILE__
				<< " put range check on allowed codes" 
				<< endl;

		} else {
			leftOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			code_expr << "  = ";
			rightOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
		}
	}
}

bool Unary2Expression::IsConst(){
	switch(exprOperatorType_){
		case oper_num:
		case oper_float:
			//cerr << "Unary2Expression::IsConst() returning true."<< endl ; 
			return true;
		case oper_name:
			if(symbolTableEntry_->type_qual==CONST_QUAL){
				return true;
			} else {
				return false;
			}
		default:
			return false;
	}
}


bool Unary2Expression::IsIntegralExpression(){
	//cerr << "Unary2Expression::IsIntegralExpression(): "
	//		<< exprOperatorType_ << endl;
	//cerr << "oper_num: " << oper_num << endl;
	switch(exprOperatorType_){
		case oper_num:
			//cerr << "Unary2Expression::IsIntegralExpression: returning true" << endl ;
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

void Unary2Expression::PrintExpressionCode(ostringstream& code_bef_expr, ostringstream & code_expr)
{
	//code_expr << "/* Unary2Expression::PrintExpressionCode ENTER */" << endl;
	switch(exprOperatorType_){
		case oper_name:{
			code_expr <<  symbolTableEntry_->name_;
		}
		break;
		case oper_arrderef:{
			code_expr <<   symbolTableEntry_->name_ << "[";
			operand_->PrintExpressionCode(code_expr, code_expr);
			code_expr <<  "]";
			}
		break;

		case oper_num:{
			code_expr <<   intSemanticValue_;
		}
		break;
		case oper_float:{
			code_expr <<   doubleSemanticValue_;
		}
		break;
		case oper_func_call:{
			using qscript_parser::func_info_table;
			//cout << "/* oper_func_call */" << endl;
			//cout << "func_index_in_table: " << func_info_table[e->func_index_in_table]->functionName_ << endl;
			if(func_info_table[func_index_in_table]->functionName_==string("printf")){
				code_expr <<  "fprintf(xtcc_stdout,";
			} else {
				code_expr << func_info_table[func_index_in_table]->functionName_.c_str() << "(";
			}
			struct AbstractExpression* e_ptr=operand_;
			while(e_ptr){
				e_ptr->PrintExpressionCode(code_bef_expr, code_expr);
				if(e_ptr->next_){
					code_expr <<  ", ";
				} 
				e_ptr=e_ptr->next_;
			}
			code_expr <<  ")";
		}
		break;
		case oper_text_expr:{
			code_expr << "\"" <<text << "\"";
		}
		break;
		case oper_blk_arr_assgn: {
			code_expr << "This case should not occur\n";
			print_err(compiler_internal_error, "This case should not occur\n", 
						line_no, __LINE__, __FILE__);
		}
		break;
		default:
			code_expr << "unhandled AbstractExpression operator\n";
			print_err(compiler_internal_error, "unhandled AbstractExpression operator\n", 
						line_no, __LINE__, __FILE__);
	}
	//code_expr << "/* Unary2Expression::PrintExpressionCode EXIT */" << endl;
}

void BinaryExpression::PrintExpressionCode(ostringstream& code_bef_expr, ostringstream & code_expr)
{
	switch(exprOperatorType_){
		char oper_buf[3];
		case oper_plus:{
			sprintf(oper_buf, "%s" , "+");
			leftOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			}
		break;	       
		case oper_minus:{
			sprintf(oper_buf, "%s" , "-");
			leftOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			}
		break;	       
		case oper_mult:{
			sprintf(oper_buf, "%s" , "*");
			leftOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			}
		break;	       
		case oper_div:{
			sprintf(oper_buf, "%s" , "/");
			leftOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			}
		break;	       
		case oper_mod:{
			sprintf(oper_buf, "%s" , "%");
			leftOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			}
		break;	      
		case oper_lt:{
			sprintf(oper_buf, "%s" , "<");
			leftOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			}
		break;	       
		case oper_gt:{
			sprintf(oper_buf, "%s" , ">");
			leftOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			}
		break;	       
		case oper_le:{
			sprintf(oper_buf, "%s" , "<=");
			leftOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			}
		break;	       
		case oper_ge:{
			sprintf(oper_buf, "%s" , ">=");
			leftOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			}
		break;	       
		case oper_iseq:{
			sprintf(oper_buf, "%s" , "==");
			leftOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			}
		break;	       
		case oper_isneq: {
			sprintf(oper_buf, "%s" , "!=");
			leftOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			}
		break;	       
		case oper_assgn:
			//print_oper_assgn(edit_out);		
			print_oper_assgn(code_bef_expr, code_expr);		
		break;
		case oper_or:{
			sprintf(oper_buf, "%s" , "||");
			leftOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			}
		break;
		case oper_and:{
			sprintf(oper_buf, "%s" , "&&");
			leftOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr
					, code_expr);
			}
		break;
		default:
			code_expr << " unhandled operator type_ in AbstractExpression  ";
			print_err(compiler_sem_err
					, " unhandled operator type_ in AbstractExpression  ", 
						line_no, __LINE__, __FILE__);
	}
}

BinaryExpression::~BinaryExpression()
{
	using qscript_parser::mem_addr;
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "BinaryExpression::~BinaryExpression setting mem_addr: " << this  <<"=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting BinaryExpression: exprOperatorType_: " << exprOperatorType_ << endl;
	if(leftOperand_) { delete leftOperand_; leftOperand_=0;}
	if(rightOperand_) { delete rightOperand_; rightOperand_=0;}
}

Unary2Expression::~Unary2Expression()
{
	using qscript_parser::mem_addr;
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			debug_log_file << "Unary2Expression::~Unary2Expression setting mem_addr: " << this << "=0" << endl;
			mem_addr[i].mem_ptr=0;
			break;
		}
	}
	debug_log_file << "deleting Unary2Expression: exprOperatorType_: " << exprOperatorType_ << endl;
	if(exprOperatorType_==oper_func_call){
		//cout << "line_no: " << line_no << endl;
	}
	cerr << "need to check the free later: __FILE__ " << __FILE__ << ", line:" << __LINE__ << endl;
	if(text) { free( text) ; text=0; }
	/*
	if(text) { 
		//free( text) ; text=0; 
		//debug_log_file << "Unary2Expression::~Unary2Expression text:"
		//	<< text << endl;

	}
	*/
	if(operand_) { delete operand_; operand_=0; }
	if(operand2_) { delete operand2_; operand2_=0;}
	//if (text ) { delete text; text=0; }
}

BinaryExpression::BinaryExpression(AbstractExpression* llop
		, AbstractExpression* lrop,ExpressionOperatorType letype)
	: AbstractExpression(letype), leftOperand_(llop), rightOperand_(lrop)
{
	if (exprOperatorType_!=oper_assgn && 
		(leftOperand_->exprOperatorType_==oper_blk_arr_assgn
		 	||rightOperand_->exprOperatorType_==oper_blk_arr_assgn))
	{
		type_=ERROR_TYPE;
		++no_errors;
		print_err(compiler_sem_err, 
			"error: oper_blk_arr_assgn: used in binary AbstractExpression ",
			line_no, __LINE__, __FILE__);
	} else if (exprOperatorType_ ==oper_assgn){
		if( (!leftOperand_->IsLValue()) ){
			type_=ERROR_TYPE;
			++no_errors;
			print_err(compiler_sem_err, 
				"oper_assgn error: lhs of \
				assignment should be lvalue ", 
				line_no, __LINE__, __FILE__);
		}
		DataType typ1=leftOperand_->type_;
		DataType typ2=rightOperand_->type_;
		if(!void_check(leftOperand_->type_, rightOperand_->type_
					, type_)){
			print_err(compiler_sem_err, 
				"oper_assgn error: operand_ data types on \
				lhs and rhs should be of non-VOID type", 
				line_no, __LINE__, __FILE__);
			type_ = ERROR_TYPE;
			++no_errors;
		}
		if(typ1==QUESTION_TYPE){
			Unary2Expression* lhs
				= static_cast<Unary2Expression*>(leftOperand_);
			const SymbolTableEntry * symp = lhs->get_symp_ptr();
			//cerr << "Question questionName_: " << symp->name_ << endl;
			AbstractQuestion* q = find_in_question_list(symp->name_);
			if(!q) {
				stringstream s;
				s << "Question not found in symbol table after parsing input" << endl;
				print_err(compiler_internal_error, s.str(), 
					line_no, __LINE__, __FILE__);
			} else {
				if(q->q_type!=spn){
					stringstream s;
					s << "Direct assignment to AbstractQuestion only allowed for SPN question_type" << endl;
					print_err(compiler_internal_error, s.str(), 
						line_no, __LINE__, __FILE__);
				} 
			}
		} else if(!check_type_compat(typ1, typ2)){
			type_ = ERROR_TYPE;
			stringstream s;
			s << "oper_assgn error: operand_ data types on lhs and rhs should be compatible, ";
			string lhs_hr_type = human_readable_type(typ1);
			string rhs_hr_type = human_readable_type(typ2);
			s << "\tlhs type: " << lhs_hr_type << ", rhs type: " << rhs_hr_type << endl;
			print_err(compiler_sem_err, s.str(), 
				line_no, __LINE__, __FILE__);
		}
	} else 
	switch(exprOperatorType_){
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
			if(void_check(leftOperand_->type_
				, rightOperand_->type_, type_)/*true*/){
				type_=lcm_type(leftOperand_->type_
						, rightOperand_->type_);
			}
			if(exprOperatorType_==oper_mod 
				&& !( is_of_int_type(leftOperand_->type_) 
					&& is_of_int_type(rightOperand_->type_))){
				print_err(compiler_sem_err, 
					" operands of %% should be of type int/char only", line_no, __LINE__, __FILE__);
				//cerr << " operands of %% should be of type int/char only" << endl;
				//++no_errors;
				type_=ERROR_TYPE;
			}
		break;
		default:
			print_err(compiler_internal_error, " INTERNAL ERROR: default case of BinaryExpression", line_no, __LINE__, __FILE__);
			;
	}
}

Unary2Expression::Unary2Expression( struct SymbolTableEntry * lsymp)
	: AbstractExpression(oper_name,lsymp->type_)
	, symbolTableEntry_(lsymp), intSemanticValue_(0)
	, doubleSemanticValue_(0), func_index_in_table(-1)
	, text(0), operand_(0), operand2_(0), column_no(-1) {
}

map<string, SymbolTableEntry*>::iterator find_in_symtab(string id);
Unary2Expression::Unary2Expression(char* ltxt, ExpressionOperatorType le_type)
	: AbstractExpression(le_type, INT8_TYPE), symbolTableEntry_(0)
	, intSemanticValue_(0), doubleSemanticValue_(0)
	, func_index_in_table(-1), text(0), column_no(-1)
	, operand_(0), operand2_(0) 
{
	if(exprOperatorType_==oper_text_expr){
		type_=STRING_TYPE;
		text = ltxt;
	} else if(exprOperatorType_==oper_name){
		map<string,SymbolTableEntry*>::iterator sym_it = 
			find_in_symtab(ltxt);
		using qscript_parser::active_scope;
		if(sym_it==active_scope->SymbolTable.end() ){
			string err_msg = "Error: could not find:" 
				+ string(text) + "  in symbol table  ";
			print_err(compiler_sem_err, err_msg
					, line_no, __LINE__, __FILE__);
			type_=ERROR_TYPE;
		} else {
			symbolTableEntry_ = sym_it->second;
			type_ = symbolTableEntry_->type_;
		}
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
	using qscript_parser::active_scope;
	map<string,SymbolTableEntry*>::iterator sym_it = find_in_symtab(name);
	if(sym_it==active_scope->SymbolTable.end() ){
		std::stringstream s;
		s << "Error: Array indexing AbstractExpression: could not find name: " 
			<< name <<"  in symbol table: lineno: " 
			<< line_no << "\n";
		print_err(compiler_sem_err, s.str()
				, line_no, __LINE__, __FILE__);
	} else {
		SymbolTableEntry* se=sym_it->second;
		symbolTableEntry_ = se;
		DataType l_e_type=arr_index->type_;
		if(is_of_int_type(l_e_type)){
			DataType nametype =arr_deref_type(se->type_);
			if(nametype==ERROR_TYPE) {
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

Unary2Expression::Unary2Expression(ExpressionOperatorType le_type, string name,
		AbstractExpression* arr_index, AbstractExpression* arr_index2)
	: AbstractExpression(le_type, ERROR_TYPE), symbolTableEntry_(0)
	, intSemanticValue_(0), doubleSemanticValue_(0)
	, func_index_in_table(-1), text(0) 
	, column_no(-1), operand_(arr_index), operand2_(arr_index2)
{
	SymbolTableEntry* se=0;
	map<string,SymbolTableEntry*>::iterator sym_it1 = find_in_symtab(name);
	using qscript_parser::active_scope;
	if( sym_it1==active_scope->SymbolTable.end()) {
		std::stringstream s;
		s << "Error: Block Array assignment AbstractExpression: could not find name: " 
			<< name <<"  in symbol table: lineno: " 
			<< line_no << "\n";
		print_err(compiler_sem_err, s.str(), line_no
				, __LINE__, __FILE__);
	} else {
		se=sym_it1->second;
		symbolTableEntry_ = se;
	}
	if( !(se)){
		std::stringstream s;
		s << "Error: Block Array assignment AbstractExpression: could not find name: " 
			<< name <<"  in symbol table: lineno: " 
			<< line_no << "\n";
		print_err(compiler_sem_err, s.str(), line_no
				, __LINE__, __FILE__);
	}  else {
		DataType e_type1=arr_index->type_;
		DataType e_type2=arr_index2->type_;
		if( is_of_int_type (e_type1)&& 
			is_of_int_type(e_type2)	){
			DataType d1=arr_deref_type(se->type_);
			if(d1==ERROR_TYPE){
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
			s <<  "ERROR: NAME  =NAME[EXPR, EXPR] EXPR should be of type int or char: lineno: " 
				<< line_no << "\n";
			print_err(compiler_sem_err, s.str()
					, line_no, __LINE__, __FILE__);
		}
	}
	//free($1);
}

bool Unary2Expression::IsLValue(){ 
	if(exprOperatorType_==oper_name|| exprOperatorType_==oper_arrderef){
		return true;
	} else {
		return false;
	}
}

Unary2Expression::Unary2Expression(int l_isem_value) 
	: AbstractExpression(oper_num), symbolTableEntry_(0)
	  , intSemanticValue_(l_isem_value), doubleSemanticValue_(0), func_index_in_table(-1) 
	, text(0), column_no(-1), operand_(0), operand2_(0)
{
	if( intSemanticValue_ >= SCHAR_MIN && intSemanticValue_<=SCHAR_MAX){
		type_=INT8_TYPE;
	} else if (intSemanticValue_>= SHRT_MIN 
			&& intSemanticValue_ <= SHRT_MAX){
		type_=INT16_TYPE;
	} else if (intSemanticValue_>= INT_MIN && intSemanticValue_ <= INT_MAX){
		type_=INT32_TYPE;
	} else {
		++no_errors;
		cerr << "very  large integer unhandleable type most probably";
		type_ = ERROR_TYPE;
	}
}


Unary2Expression::Unary2Expression(ExpressionOperatorType le_type
		, DataType ldt, AbstractExpression* e_list
		, int lfunc_index_in_table)
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

bool Binary2Expression::IsIntegralExpression(){
	return false;
}

Binary2Expression::Binary2Expression(AbstractExpression* llop
		, XtccSet& l_rd, ExpressionOperatorType letype)
	:AbstractExpression(letype), leftOperand_(0), xs(0)
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
				leftOperand_=0;
				type_ = ERROR_TYPE;
				string err_msg = "Binary2Expression:: lhs operator for oper_in can only be NAME or NAME[INDEX]";
				print_err(compiler_sem_err, err_msg, 
					line_no, __LINE__, __FILE__);
				type_=ERROR_TYPE;
			}
			break;
		default: {
			leftOperand_=0;
			type_ = ERROR_TYPE;
			string err_msg = "Binary2Expression:: operator in exprOperatorType_ can only be oper_in";
			print_err(compiler_sem_err, err_msg
					, line_no, __LINE__, __FILE__);
			type_=ERROR_TYPE;
		}
	}
}



void Binary2Expression::PrintExpressionCode(ostringstream& code_bef_expr
		, ostringstream & code_expr)
{
	string struct_name = get_temp_name();
	code_bef_expr << "\tstruct " <<  struct_name.c_str() << "{\n" ;
	code_bef_expr << "\t\tconst int size_ran_indiv;\n";
	code_bef_expr << "\t\tconst int size_start_end;\n";
	code_bef_expr << "\t\tvector<int> ran_indiv;\n";
	code_bef_expr << "\t\tvector< pair<int,int> > ran_start_end;\n";
	code_bef_expr << "\t\t" << struct_name.c_str() 
		<< "(): size_ran_indiv(" << xs->indiv.size() //r_data->icount 
		<< "), size_start_end(" <<  xs->range.size() //r_data->rcount << "),\n";
		<< "),\n";								       
	code_bef_expr << "\t\t\tran_indiv(size_ran_indiv), ran_start_end(size_start_end){\n";
	//fprintf(stderr, "Binary2Expression::PrintExpressionCode(): printed constructor");
	for(int i=0; i< xs->range.size() ; ++i){
		code_bef_expr << "\t\t\tran_start_end[" << i 
			<< "]=pair<int,int>(" 
			<< xs->range[i].first 
			<< "," << xs->range[i].second << ");\n";
	}
	
	int k=0;
	for(set<int>::iterator iter=xs->indiv.begin(); 
		iter!=xs->indiv.end(); ++iter, ++k){
		code_bef_expr << "\t\t\tran_indiv[" 
			<< k << "]=" << *iter <<";\n";
	}
	code_bef_expr <<  "\t\t}\n";

	code_bef_expr << "\t\tbool exists(int key){\n";
	code_bef_expr << "\t\t\tfor(int i=0; i<size_start_end; ++i){\n";
	code_bef_expr << "\t\t\t\tif(key >=ran_start_end[i].first && key <=ran_start_end[i].second){\n";
	code_bef_expr << "\t\t\t\t\treturn true;\n";
	code_bef_expr << "\t\t\t\t}\n";
	code_bef_expr << "\t\t\t}\n";
	code_bef_expr << "\t\t\tfor(int i=0; i< size_ran_indiv; ++i){\n";
	code_bef_expr << "\t\t\t\tif(key==ran_indiv[i]){\n";
	code_bef_expr << "\t\t\t\t\treturn true;\n";
	code_bef_expr << "\t\t\t\t}\n";
	code_bef_expr << "\t\t\t}\n";
	code_bef_expr << "\t\t\treturn false;\n";
	code_bef_expr << "\t\t}\n";

	code_bef_expr << "\t\tbool contains_subset(set<int> & set_data){\n";
	code_bef_expr << "\t\t\tbool val_exists = false;\n";
	code_bef_expr << "\t\t\tfor(\tset<int>::iterator it=set_data.begin();\n";
	code_bef_expr << "\t\t\t\tit!=set_data.end(); ++it){\n";
	code_bef_expr << "\t\t\t\t\tval_exists=exists(*it);\n";
	code_bef_expr << "\t\t\t\tif(!val_exists){\n";
	code_bef_expr << "\t\t\t\t\treturn false;\n";
	code_bef_expr << "\t\t\t\t}\n";
	code_bef_expr << "\t\t\t}\n";
	code_bef_expr << "\t\t\t/*if(!val_exists){\n";
	code_bef_expr << "\t\t\t\treturn false;\n";
	code_bef_expr << "\t\t\t}*/\n";
	code_bef_expr << "\t\treturn true;\n";
	code_bef_expr << "\t\t}\n";
	string struct_name1 = get_temp_name();
	code_bef_expr << "\t} " <<  struct_name1.c_str() <<";\n";
	
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
			string test_bool_var_name=get_temp_name();
			code_bef_expr <<  "bool " 
				<<  test_bool_var_name.c_str()
				<< " = " << struct_name1.c_str()
				<< ".exists(";
			//<< name.c_str() << ");\n";
			ostringstream code_bef_expr1_discard, code_expr1;
			leftOperand_->PrintExpressionCode(
					code_bef_expr1_discard, code_expr1);
			code_bef_expr << code_expr1.str() << ");\n";
			code_expr << test_bool_var_name.c_str() << " " ;
		}
		break;
		case QUESTION_TYPE:{
			string test_bool_var_name=get_temp_name();
			code_bef_expr <<  "bool " <<  test_bool_var_name.c_str()
				<< " = " << struct_name1.c_str()
				<< ".contains_subset(";
			ostringstream code_bef_expr1_discard, code_expr1;
			leftOperand_->PrintExpressionCode(
					code_bef_expr1_discard, code_expr1);
			code_bef_expr << code_expr1.str() 
				<< "->input_data"
				<< ");\n";
			code_expr << test_bool_var_name.c_str() << " " ;
		}
		break;	
		default: {
			std::stringstream s;
			s << "file: " << __FILE__ 
				<< ", line: " << __LINE__ << endl;
			print_err(compiler_internal_error, s.str()
					, line_no, __LINE__, __FILE__);
		 }
	}
}


Binary2Expression::~Binary2Expression()
{
	using qscript_parser::mem_addr;
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "Binary2Expression::~Binary2Expression setting mem_addr: " << this  <<"=0" << endl;
			break;
		}
	}
	if(leftOperand_){
		delete leftOperand_; leftOperand_=0;
	}
	if(xs){
		delete xs; xs=0;
	}
}


string get_temp_name()
{
	// about a billion temporaries before we run out
	const int max_temp=10;
	static int count=0;
	char buffer[max_temp];
	char op_buf[max_temp];
	int dividend=count;

	buffer[0]='0'; buffer[1]='\0';

	int j=0;
	do {
		int rem = dividend%10;
		dividend=dividend/10;
		buffer[j++]='0' + rem;
	} while(dividend>0);
	/*
	for(int i=0 ; dividend/10>0; dividend=dividend/10,++i,++j){
		//int quot = dividend/10;
		int rem = dividend%10;
		buffer[j]='0' + rem;
	}
	*/
	buffer[j]='\0';
	for(int i=j-1; i>=0; --i){
		op_buf[j-1-i]=buffer[i];
	}
	op_buf[j]='\0';
	string s(op_buf);
	++count;
	//cout << s << endl;
	string s1="temp_"+s;
	return s1;
}

string human_readable_expr_type( ExpressionOperatorType exprOperatorType_)
{
	string s="UNKNOWN EXPR TYPE";
	switch(exprOperatorType_){
		case oper_plus:
			s="oper_plus";
		break;
		case oper_minus:
			s="oper_minus";
		break;
		case oper_mult:
			s="oper_mult";
		break;
		case oper_div:
			s="oper_div";
		break;
		case oper_and:
			s="oper_and";
		break;
		case oper_or:
			s="oper_or";
		break;
		case oper_lt:
			s="oper_lt";
		break;
		case oper_gt:
			s="oper_gt";
		break;
		case oper_le:
			s="oper_le";
		break;
		case oper_ge:
			s="oper_ge";
		break;
		case oper_isneq:
			s="oper_isneq";
		break;
		case oper_iseq:
			s="oper_iseq";
		break;
		case oper_parexp:
			s="oper_parexp";
		break;

		case oper_umin:
			s="oper_umin";
		break;
		case oper_num:
			s="oper_num";
		break;
		case oper_name:
			s="oper_name";
		break;
		case oper_arrderef:
			s="oper_arrderef";
		break;
		case oper_arr2deref:
			s="oper_arr2deref";
		break;
		case oper_func_call:
			s="oper_func_call";
		break;
		case oper_text_expr:
			s="oper_text_expr";
		break;
		case oper_float:
			s="oper_float";
		break;
		case oper_assgn:
			s="oper_assgn";
		break;
		case oper_not:
			s="oper_not";
		break;
		case oper_mod:
			s="oper_mod";
		break;
		case oper_blk_arr_assgn:
			s="oper_blk_arr_assgn";
		break;
		case oper_in:
			s="oper_in";
		break;
		case oper_q_expr_in:
			s="oper_q_expr_in";
		break;
		case oper_q_expr_arr_in:
			s="oper_q_expr_arr_in";
		break;
		case oper_err:
			s="oper_err";
		break;
		default:
		;
	}
	return s;
}
