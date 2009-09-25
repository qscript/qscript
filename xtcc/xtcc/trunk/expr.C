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
#include "utils.h"
#include "stmt.h"
#include "expr.h"
#include "debug_mem.h"
#include "named_range.h"

extern int no_errors;
extern int line_no;
extern Scope* active_scope;
extern std::ofstream debug_log_file;
extern	std::vector <Statement::FunctionInformation*> func_info_table;
extern std::vector<mem_addr_tab> mem_addr;
extern std::vector <named_range> named_stubs_list;
namespace Expression {
using ::line_no;
using ::no_errors;
using std::ofstream;
using std::cout;
using std::cerr;
using std::endl;
using Util::print_err;
using Util::void_check;
using Util::lcm_type;
using Util::arr_deref_type;

AbstractExpression::~AbstractExpression()
{
	debug_log_file << "deleting AbstractExpression::~AbstractExpression(): base destructor for AbstractExpression" << endl;
	if(next_) {delete next_; next_=0; }
}


int AbstractExpression::isvalid()
{
	if (type_==ERROR_TYPE){
		return 0;
	} else return 1;
}

UnaryExpression::~UnaryExpression()
{
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "UnaryExpression::~UnaryExpression setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting UnaryExpression: exprOperatorType_" 
		<< exprOperatorType_ << endl;
	if (operand_) { delete operand_; operand_=0; }
}

//#include "tree.h"
UnaryExpression::UnaryExpression( AbstractExpression * l_operand
		, ExpressionOperatorType le_type)
	:AbstractExpression(le_type), operand_(l_operand)
{
	if(operand_->exprOperatorType_==oper_blk_arr_assgn){
		Util::print_err(Util::compiler_sem_err
				, "oper_blk_arr_assgn: cannot be used with unary operators : line_no:",
			line_no, __LINE__, __FILE__);
	} else if(l_operand->type_==VOID_TYPE){
		switch(l_operand->exprOperatorType_){
			case oper_umin:
			case oper_not:
				cerr << "operator Unary minus(-): ";
				Util::print_err(Util::compiler_sem_err
						, " unary operator applied to function of type void ", 
						line_no, __LINE__, __FILE__);
			break;
			default: 
				print_err(Util::compiler_sem_err, 
					" unary operator applied to AbstractExpression of type void. Internal compiler error ", 
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
				Util::print_err(Util::compiler_internal_error, " unknown unary operator applied to AbstractExpression. Internal compiler error ", 
					line_no, __LINE__, __FILE__);

		}
	}
}


void UnaryExpression::PrintExpressionCode (ostringstream& code_bef_expr
		, ostringstream & code_expr)
{
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
}

//void BinaryExpression::print_oper_assgn(FILE * edit_out)
void BinaryExpression::print_oper_assgn(ostringstream& code_bef_expr
		, ostringstream & code_expr)
{
	if(rightOperand_->exprOperatorType_ == oper_blk_arr_assgn &&
		( leftOperand_->exprOperatorType_==oper_name
		  ||leftOperand_->exprOperatorType_==oper_arrderef)){
		Unary2Expression* blk_e = 
			static_cast<Unary2Expression*> (rightOperand_);
		Unary2Expression* lhs 
			= static_cast<Unary2Expression*> (leftOperand_);
		code_expr << "/* DATA CONVERSION */\n";
		code_expr << "{int tmp1=";
		blk_e->operand_->PrintExpressionCode(code_bef_expr, code_expr);
		code_expr << ";\nint tmp2=";
		blk_e->operand2_->PrintExpressionCode(code_bef_expr, code_expr);
		code_expr << ";\n";
		if(leftOperand_->type_==FLOAT_TYPE) {
			code_expr << "if(tmp2-tmp1==sizeof(float)-1){\n";
			code_expr << "\tchar buff[sizeof(float)];int i,j;\n";
			code_expr << "\tfor(i=tmp1,j=0;i<=tmp2;++i,++j){\n";
			code_expr << "\t\tbuff[j]=" 
				<<  blk_e->symbolTableEntry_->name_ << "[i];\n";
			code_expr << "\t}\n";
			code_expr << "\tvoid * v_ptr = buff;\n";
			code_expr << "\tfloat *f_ptr = static_cast<float *>(v_ptr);\n";
			
			code_expr << "\t" ;
			lhs->PrintExpressionCode(code_bef_expr, code_expr);
			code_expr << "=*f_ptr;\n";
			code_expr << "}else { cerr << \"runtime error: line_no : AbstractExpression out of bounds\" << " 
				<< ::line_no  <<";}\n}\n";
		} else if (leftOperand_->type_==INT32_TYPE){
			code_expr << "if(tmp2-tmp1==sizeof(int)-1){\n";
			code_expr << "\tchar buff[sizeof(int)];int i,j;\n";
			code_expr << "\tfor(i=tmp1,j=0;i<=tmp2;++i,++j){\n";
			code_expr << "\t\tbuff[j]=" 
				<< blk_e->symbolTableEntry_->name_ << "[i];\n";
			code_expr << "\t}\n";
			code_expr << "\tvoid * v_ptr = buff;\n";
			code_expr << "\tint *i_ptr = static_cast<int *>(v_ptr);\n";
			code_expr << "\t" ;
			lhs->PrintExpressionCode(code_bef_expr, code_expr);
			code_expr << "=*i_ptr;\n" ;
			code_expr << "}else { \n\tcerr << \"runtime error: line_no : AbstractExpression out of bounds\" <<"
				<< line_no << " ;}\n}\n";
		} else {
			code_expr <<  "error\n";
			cerr << "Error in code generation" << endl;
		}
	} else if (rightOperand_->exprOperatorType_ == oper_blk_arr_assgn 
			&& leftOperand_->exprOperatorType_==oper_blk_arr_assgn){
		code_expr << " unhandled case LHS ==";
	}else {
		leftOperand_->PrintExpressionCode(code_bef_expr, code_expr);
		code_expr << " /* oper_assgn */ = ";
		rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
	}
}


void Unary2Expression::PrintExpressionCode(ostringstream& code_bef_expr
		, ostringstream & code_expr)
{
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
			code_expr <<   isem_value;
		}
		break;
		case oper_float:{
			code_expr <<   dsem_value;
		}
		break;
		case oper_func_call:{
			if(func_info_table[func_index_in_table]->funcName_==string("printf")){
				code_expr <<  "fprintf(xtcc_stdout,";
			} else {
				code_expr << func_info_table[func_index_in_table]->funcName_.c_str() << "(";
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
			code_expr << text;
		}
		break;
		case oper_blk_arr_assgn: {
			code_expr << "This case should not occur\n";
			Util::print_err(Util::compiler_internal_error, "This case should not occur\n", 
						line_no, __LINE__, __FILE__);
		}
		break;
		default:
			code_expr << "unhandled AbstractExpression operator\n";
			Util::print_err(Util::compiler_internal_error, "unhandled AbstractExpression operator\n", 
						line_no, __LINE__, __FILE__);
	}
}

void BinaryExpression::PrintExpressionCode(ostringstream& code_bef_expr
		, ostringstream & code_expr){
	switch(exprOperatorType_) {
		char oper_buf[3];
		case oper_plus:{
			sprintf(oper_buf, "%s" , "+");
			leftOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			//fprintf(edit_out, " %s ", oper_buf);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			}
		break;	       
		case oper_minus:{
			sprintf(oper_buf, "%s" , "-");
			leftOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			}
		break;	       
		case oper_mult:{
			sprintf(oper_buf, "%s" , "*");
			leftOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			}
		break;	       
		case oper_div:{
			sprintf(oper_buf, "%s" , "/");
			leftOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			}
		break;	       
		case oper_mod:{
			sprintf(oper_buf, "%s" , "%");
			leftOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			}
		break;	      
		case oper_lt:{
			sprintf(oper_buf, "%s" , "<");
			leftOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			}
		break;	       
		case oper_gt:{
			sprintf(oper_buf, "%s" , ">");
			leftOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			}
		break;	       
		case oper_le:{
			sprintf(oper_buf, "%s" , "<=");
			leftOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			}
		break;	       
		case oper_ge:{
			sprintf(oper_buf, "%s" , ">=");
			leftOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			}
		break;	       
		case oper_iseq:{
			sprintf(oper_buf, "%s" , "==");
			leftOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			}
		break;	       
		case oper_isneq: {
			sprintf(oper_buf, "%s" , "!=");
			leftOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			}
		break;	       
		case oper_assgn:
			print_oper_assgn(code_bef_expr, code_expr);		
		break;
		case oper_or:{
			sprintf(oper_buf, "%s" , "||");
			leftOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			}
		break;
		case oper_and:{
			sprintf(oper_buf, "%s" , "&&");
			leftOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			code_expr << oper_buf;
			rightOperand_->PrintExpressionCode(code_bef_expr, code_expr);
			}
		break;
		default:
			code_expr << " unhandled operator type in AbstractExpression  ";
			Util::print_err(Util::compiler_sem_err
					, " unhandled operator type in AbstractExpression  ", 
						line_no, __LINE__, __FILE__);
	}
}

BinaryExpression::~BinaryExpression(){
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

Unary2Expression::~Unary2Expression(){
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
	if(text) { free( text) ; text=0; }
	if(operand_) { delete operand_; operand_=0; }
	if(operand2_) { delete operand2_; operand2_=0;}
}

BinaryExpression::BinaryExpression(AbstractExpression* llop
		, AbstractExpression* lrop,ExpressionOperatorType letype)
	:AbstractExpression(letype), leftOperand_(llop), rightOperand_(lrop)
{
	if (exprOperatorType_!=oper_assgn 
		&& (leftOperand_->exprOperatorType_==oper_blk_arr_assgn
			||rightOperand_->exprOperatorType_==oper_blk_arr_assgn))
	{
		type_=ERROR_TYPE;
		++no_errors;
		print_err(Util::compiler_sem_err, "error: oper_blk_arr_assgn: used in binary AbstractExpression ",
				line_no, __LINE__, __FILE__);
	} else if (exprOperatorType_ ==oper_assgn){
		if( (!leftOperand_->is_lvalue()) ){
			type_=ERROR_TYPE;
			++no_errors;
			print_err(Util::compiler_sem_err, "oper_assgn error: lhs of assignment should be lvalue ", 
				line_no, __LINE__, __FILE__);
		}
		DataType typ1=leftOperand_->type_;
		DataType typ2=rightOperand_->type_;
		if(!void_check(leftOperand_->type_, rightOperand_->type_, type_)){
			print_err(Util::compiler_sem_err, "oper_assgn error: operand_ data types on lhs and rhs should be of non-VOID type", 
				line_no, __LINE__, __FILE__);
			type_ = ERROR_TYPE;
			++no_errors;
		}
		if(!Util::check_type_compat(typ1, typ2)){
			type_ = ERROR_TYPE;
			stringstream s;
			s << "oper_assgn error: operand_ data types on lhs and rhs should be compatible, ";
			string lhs_hr_type = human_readable_type(typ1);
			string rhs_hr_type = human_readable_type(typ2);
			s << "\tlhs type: " << lhs_hr_type << ", rhs type: " << rhs_hr_type << endl;
			print_err(Util::compiler_sem_err, s.str(), 
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
						, rightOperand_->type_, type_)){
				type_=lcm_type(leftOperand_->type_
						, rightOperand_->type_);
			}
			if(exprOperatorType_==oper_mod 
				&& !( is_of_int_type(leftOperand_->type_) 
					&& is_of_int_type(rightOperand_->type_))){
				print_err(Util::compiler_sem_err, 
					" operands of %% should be of type int/char only", line_no, __LINE__, __FILE__);
				type_=ERROR_TYPE;
			}
		break;
		default:
			print_err(Util::compiler_internal_error, " INTERNAL ERROR: default case of BinaryExpression", line_no, __LINE__, __FILE__);
			;
	}
}
Unary2Expression::Unary2Expression( struct SymbolTableEntry * lsymp)
	: AbstractExpression(oper_name,lsymp->type_), symbolTableEntry_(lsymp)
	, isem_value(0), dsem_value(0)
	, func_index_in_table(-1), text(0), operand_(0), operand2_(0) 
{
}

map<string, SymbolTableEntry*>::iterator find_in_symtab(string id);
Unary2Expression::Unary2Expression(char* ltxt, ExpressionOperatorType le_type)
	: AbstractExpression(le_type, INT8_TYPE), symbolTableEntry_(0)
	, isem_value(0), dsem_value(0), func_index_in_table(-1)
	, text(ltxt), column_no(-1), operand_(0), operand2_(0) 
{
	if(exprOperatorType_==oper_text_expr){
		type_=STRING_TYPE;
	} else if(exprOperatorType_==oper_name){
		map<string,SymbolTableEntry*>::iterator sym_it = 
			Util::find_in_symtab(ltxt);
		if(sym_it==active_scope->sym_tab.end() ){
			string err_msg = "Error: could not find:" 
				+ string(ltxt) + "  in symbol table  ";
			print_err(Util::compiler_sem_err, err_msg, line_no, __LINE__, __FILE__);
			type_=ERROR_TYPE;
		} else {
			symbolTableEntry_ = sym_it->second;
			type_ = symbolTableEntry_->type_;
		}
	}
}

#include <sstream>
Unary2Expression::Unary2Expression(ExpressionOperatorType le_type,  string name
		, AbstractExpression* arr_index)
	: AbstractExpression(le_type, ERROR_TYPE), symbolTableEntry_(0)
	, isem_value(0), dsem_value(0), func_index_in_table(-1)
	, text(0), column_no(-1), operand_(arr_index),  operand2_(0)
{
	map<string,SymbolTableEntry*>::iterator sym_it = Util::find_in_symtab(name);
	if(sym_it==active_scope->sym_tab.end() ){
		std::stringstream s;
		s << "Error: Array indexing AbstractExpression: could not find name: " 
			<< name <<"  in symbol table: lineno: " << line_no << "\n";
		print_err(Util::compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
	} else {
		SymbolTableEntry* se=sym_it->second;
		symbolTableEntry_ = se;
		DataType exprOperatorType_=arr_index->type_;
		if(is_of_int_type(exprOperatorType_)){
			DataType nametype =arr_deref_type(se->type_);
			if(nametype==ERROR_TYPE) {
				std::stringstream s;
				s << "ERROR: Array indexing AbstractExpression Variable being indexed not of Array Type : Error: lineno: " << line_no << "\n";
				print_err(Util::compiler_sem_err
					, s.str(), line_no, __LINE__, __FILE__);
			} else {
				type_ = nametype;
			}
		} else {
			stringstream s;
			s << "ERROR: Array index not of Type Int : Error: lineno: " << line_no << "\n";
			print_err(Util::compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		}
	}
}

Unary2Expression::Unary2Expression(ExpressionOperatorType le_type,  string name
		, AbstractExpression* arr_index, AbstractExpression* arr_index2)
	: AbstractExpression(le_type, ERROR_TYPE)
	, symbolTableEntry_(0), isem_value(0)
	, dsem_value(0), func_index_in_table(-1), text(0)
	, column_no(-1), operand_(arr_index), operand2_(arr_index2)
{
	SymbolTableEntry* se=0;
	map<string,SymbolTableEntry*>::iterator sym_it1 = 
		Util::find_in_symtab(name);
	if( sym_it1==active_scope->sym_tab.end()) {
		std::stringstream s;
		s << "Error: Block Array assignment AbstractExpression: could not find name: " 
			<< name <<"  in symbol table: lineno: " << line_no << "\n";
		print_err(Util::compiler_sem_err, s.str(), line_no
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
		print_err(Util::compiler_sem_err, s.str(), line_no
				, __LINE__, __FILE__);
	}  else {
		DataType e_type1=arr_index->type_;
		DataType e_type2=arr_index2->type_;
		if( is_of_int_type (e_type1)&& 
			is_of_int_type(e_type2)	){
			DataType d1=arr_deref_type(se->type_);
			if(d1==ERROR_TYPE){
				std::stringstream s;
				s << "ERROR: Block Array assignment AbstractExpression Variable: " << name << " being indexed not of Array Type : Error: lineno: " << line_no << "\n";
				print_err(Util::compiler_sem_err, s.str()
					, line_no, __LINE__, __FILE__);
			} else {
				type_ = d1;
			}
		} else {
			stringstream s;
			s <<  "ERROR: NAME  =NAME[EXPR, EXPR] EXPR should be of type int or char: lineno: " 
				<< line_no << "\n";
			print_err(Util::compiler_sem_err, s.str()
					, line_no, __LINE__, __FILE__);
		}
	}
	//free($1);
}

bool Unary2Expression::is_lvalue()
{ 
	if(exprOperatorType_==oper_name|| exprOperatorType_==oper_arrderef){
		return true;
	} else {
		return false;
	}
}

Unary2Expression::Unary2Expression(int l_isem_value)
	: AbstractExpression(oper_num), symbolTableEntry_(0)
	, isem_value(l_isem_value)
	, dsem_value(0), func_index_in_table(-1), text(0), column_no(-1)
	, operand_(0), operand2_(0)
{
	if( isem_value >= SCHAR_MIN && isem_value<=SCHAR_MAX){
		type_=INT8_TYPE;
	} else if (isem_value>= SHRT_MIN && isem_value <= SHRT_MAX){
		type_=INT16_TYPE;
	} else if (isem_value>= INT_MIN && isem_value <= INT_MAX){
		type_=INT32_TYPE;
	} else {
		++no_errors;
		type_ = ERROR_TYPE;
		stringstream s;
		s << "very large integer unhandleable type most probably line_no: "
			<< line_no << "\n";
		print_err(Util::compiler_sem_err, s.str(), line_no
				, __LINE__, __FILE__);
	}
}

Unary2Expression::Unary2Expression(ExpressionOperatorType le_type, DataType ldt
		, AbstractExpression* e_list, int lfunc_index_in_table
		, int lline_no)
	: AbstractExpression(le_type, ldt), symbolTableEntry_(0), isem_value(0)
	, dsem_value(0), func_index_in_table(lfunc_index_in_table)
	, text(0), column_no(-1), operand_(e_list), operand2_(0), 
	line_no(lline_no) 
{}

Unary2Expression::Unary2Expression(double l_dsem_value): 
	AbstractExpression(oper_float,FLOAT_TYPE), symbolTableEntry_(0)
	, isem_value(0), dsem_value(l_dsem_value)
	, func_index_in_table(-1), text(0), operand_(0), operand2_(0) 
{}

Unary2Expression::Unary2Expression(DataType d)
	: AbstractExpression(oper_err,d), symbolTableEntry_(0)
	, isem_value(0), dsem_value(0), func_index_in_table(-1), text(0)
	, column_no(-1), operand_(0), operand2_(0)
	{}

#if 0
XtccSet::XtccSet(): range(0){ 
	//range(0), indiv(0){
	//range.reset(0);
	//indiv.resize(0);
	//range.resize(0);
}

XtccSet::XtccSet(DataType dt, string name, XtccSet& xs): 
	range(xs.range), indiv(xs.indiv){
}
XtccSet::XtccSet(XtccSet& xs1): range(xs1.range), indiv(xs1.indiv){
}

XtccSet& XtccSet::operator= (const XtccSet& xs1){
	range=xs1.range;
	indiv = xs1.indiv;
	return *this;
}

void XtccSet::reset(){
	range.clear();
	indiv.clear();
}

void XtccSet::add_range(int n1, int n2){
	range.push_back( pair<int,int>(n1, n2));
}

void XtccSet::add_indiv(int n1){
	indiv.insert(n1);
}
#endif /* 0 */

Binary2Expression::Binary2Expression(AbstractExpression* llop , XtccSet& l_rd
		, ExpressionOperatorType letype)
	:AbstractExpression(letype), leftOperand_(llop)
{
	switch(exprOperatorType_) {
	case oper_in:
		switch( leftOperand_->exprOperatorType_){
		case oper_name:
		case oper_arrderef:
			type_ = BOOL_TYPE;
			xs = new XtccSet(l_rd);
			break;
		default:
			type_ = ERROR_TYPE;
			string err_msg = "Binary2Expression:: lhs operator for oper_in can only be NAME or NAME[INDEX]";
			print_err(Util::compiler_internal_error, err_msg
					, line_no, __LINE__, __FILE__);
			type_=ERROR_TYPE;
			
		}
		break;


	default: {
			type_ = ERROR_TYPE;
			string err_msg = "Binary2Expression:: operator in exprOperatorType_ can only be oper_in";
			print_err(Util::compiler_internal_error, err_msg
					, line_no, __LINE__, __FILE__);
			type_=ERROR_TYPE;
		}
	}
}

#if 0
Binary2Expression::Binary2Expression(string lname , string rname ,ExpressionOperatorType letype): AbstractExpression(letype) {
	switch(exprOperatorType_){
		case oper_in: {
			DataType  l_type, r_type;

			map<string,SymbolTableEntry*>::iterator sym_it_l = find_in_symtab(lname);
			if( sym_it_l==active_scope->sym_tab.end() ){
				string err_msg = "Error: could not find:" + lname + "  in symbol table  ";
				print_err(compiler_sem_err, err_msg, line_no, __LINE__, __FILE__);
				type=ERROR_TYPE;
			} else {
				l_symp = sym_it_l->second;
				l_type = l_symp->type;
			}

			map<string,SymbolTableEntry*>::iterator sym_it_r = find_in_symtab(rname);
			if( sym_it_r ==active_scope->sym_tab.end() ) {
				string err_msg = "Error: could not find:" + rname + " in symbol table.";
				print_err(compiler_sem_err, err_msg, line_no, __LINE__, __FILE__);
				type=ERROR_TYPE;
			} else {
				r_symp = sym_it_r->second;
				r_type = r_symp->type;
			}
			if(!(type==ERROR_TYPE) ) {
				if(  ((l_symp->type == RANGE_DECL_STMT 
					|| is_of_int_type(l_symp->type))
					|| is_of_int_arr_type(l_symp->type)) 
				&& r_symp->type == RANGE_DECL_STMT ){
					type = BOOL_TYPE;
				} else {
					string err_msg=" LHS of operator IN can only be of type NAME, NAME[ EXPR ] of type int or a RANGE_DECL_STMT";
					print_err(compiler_sem_err, err_msg, line_no, __LINE__, __FILE__);
				}
			}
		}
		default:
			type=ERROR_TYPE;      
			print_err(compiler_internal_error, "unhandled case for Binary2Expression::Binary2Expression", 
				line_no, __LINE__, __FILE__);
	}
}
#endif /* 0 */

#if 0
void Binary2Expression::PrintExpressionCode (FILE * edit_out){
	switch(exprOperatorType_){
		case oper_in:
			fprintf(edit_out, "/*printing OPER IN*/");
		default:
			print_err(compiler_internal_error, "ERROR Binary2Expression:: was passed oper_in with invalid data ", 
					line_no, __LINE__, __FILE__);
	}
}
#endif /* 0 */

string get_temp_name();
void Binary2Expression::PrintExpressionCode(ostringstream& code_bef_expr
		, ostringstream & code_expr)
{
	fprintf(stderr, "Binary2Expression::PrintExpressionCode()\n");
	//fflush(fptr);
	string struct_name = get_temp_name();
	fprintf(stderr, "Binary2Expression::PrintExpressionCode(): after get_temp_name()\n");
	code_bef_expr << "\tstruct " <<  struct_name.c_str() << "{\n" ;
	code_bef_expr << "\t\tconst int size_ran_indiv;\n";
	code_bef_expr << "\t\tconst int size_start_end;\n";
	code_bef_expr << "\t\tvector<int> ran_indiv;\n";
	code_bef_expr << "\t\tvector< pair<int,int> > ran_start_end;\n";
	code_bef_expr << "\t\t" << struct_name.c_str() 
		<< "(): size_ran_indiv(" << xs->indiv.size() 
		<< "), size_start_end(" <<  xs->range.size()
		<< "),\n";								       
	code_bef_expr << "\t\t\tran_indiv(size_ran_indiv), ran_start_end(size_start_end){\n";
	fprintf(stderr, "Binary2Expression::PrintExpressionCode(): printed constructor");
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

	string struct_name1 = get_temp_name();
	code_bef_expr << "\t} " <<  struct_name1.c_str() <<";\n";
	string test_bool_var_name=get_temp_name();
	code_bef_expr <<  "bool " <<  test_bool_var_name.c_str()
		<< " = " << struct_name1.c_str()
		<< ".exists(";
	ostringstream code_bef_expr1_discard, code_expr1;
	leftOperand_->PrintExpressionCode(code_bef_expr1_discard, code_expr1);
	code_bef_expr << code_expr1.str() << ");\n";
	code_expr << test_bool_var_name.c_str() << " " ;
			  
}


Binary2Expression::~Binary2Expression(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "Binary2Expression::~Binary2Expression setting mem_addr: " << this  <<"=0" << endl;
			break;
		}
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

} /* close namespace Expression */
