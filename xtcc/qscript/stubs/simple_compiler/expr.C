/*
 * expr.C  
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
#include "stmt.h"
//#include "tree.h"
#include "expr.h"
#include <climits>
//#include "../../qscript/trunk/named_range.h"
#include "named_range.h"
question* find_in_question_list(string name);
string get_temp_name();

extern scope* active_scope;
extern ofstream debug_log_file;
using namespace std;

extern	vector <func_info*> func_info_table;
extern vector<mem_addr_tab> mem_addr;
extern vector <named_range*> named_stubs_list;
expr::~expr(){
	debug_log_file << "deleting expr::~expr(): base destructor for expr" << endl;
	if(next) {delete next; next=0; }
}

/*
	datatype expr::get_type(){
		if(type==oper_func_call){
			return func_info_table[index].return_type;
		}
		return type;
	}
*/

int expr::isvalid(){
	//cout << "isvalid called" << endl;
	if (type==ERROR_TYPE){
		return 0;
	} else return 1;
}

un_expr::~un_expr(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "un_expr::~un_expr setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting un_expr: e_type" << e_type << endl;
	if (operand) { delete operand; operand=0; }
}

#include "tree.h"
un_expr::un_expr( expr * l_operand, e_operator_type le_type):expr(le_type), operand(l_operand){
	if(operand->e_type==oper_blk_arr_assgn){
		print_err(compiler_sem_err, "oper_blk_arr_assgn: cannot be used with unary operators : line_no:",
			line_no, __LINE__, __FILE__);
	} else if(l_operand->type==VOID_TYPE){
		switch(l_operand->e_type){
			case oper_umin:
			case oper_not:
				cerr << "operator Unary minus(-): ";
				print_err(compiler_sem_err, " unary operator applied to function of type void ", 
				line_no, __LINE__, __FILE__);
			break;
			default: 
				print_err(compiler_sem_err, 
					" unary operator applied to expr of type void. Internal compiler error ", 
				line_no, __LINE__, __FILE__);
		}
	} else {
		switch(e_type){
			case oper_umin:
				type = l_operand->type;
			break;
			case oper_not:
				type = INT8_TYPE;
			break;
			case oper_parexp:
				type = l_operand->type;
			break;
			default:
				++no_errors;
				print_err(compiler_internal_error, " unknown unary operator applied to expr. Internal compiler error ", 
					line_no, __LINE__, __FILE__);

		}

	}
}


//void un_expr::print_expr (FILE * edit_out)
void un_expr::print_expr (ostringstream& code_bef_expr, ostringstream & code_expr){
	switch(e_type){
		case oper_umin:{
			code_expr <<  "- ";
			operand->print_expr(code_bef_expr, code_expr);
		}
		break;

		case oper_not:{
			//fprintf(edit_out, "! ");
			code_expr <<  "! ";
			operand->print_expr(code_bef_expr, code_expr);
		}
		break;

		case oper_parexp:{
			code_expr <<  "(";
			operand->print_expr(code_bef_expr, code_expr);
			code_expr <<  ")";
			}
		break;
		default:
			code_expr <<  " un handled operator\n" ;

	}
}

string human_readable_type(datatype dt);
void bin_expr::print_oper_assgn(ostringstream& code_bef_expr, ostringstream & code_expr){
	if(r_op->e_type == oper_blk_arr_assgn &&
		( l_op->e_type==oper_name||l_op->e_type==oper_arrderef)){
		un2_expr* blk_e = static_cast<un2_expr*> (r_op);
		un2_expr* lhs = static_cast<un2_expr*> (l_op);
		code_expr << "/* DATA CONVERSION */\n";
		code_expr << "{int tmp1=";
		blk_e->operand->print_expr(code_bef_expr, code_expr);
		code_expr << ";\nint tmp2=";
		blk_e->operand2->print_expr(code_bef_expr, code_expr);
		code_expr << ";\n";
		switch(lhs->get_symp_ptr()->type){
			case INT8_TYPE ... DOUBLE_REF_TYPE:
			case BOOL_TYPE:	{	
				if(l_op->type==FLOAT_TYPE) {
					code_expr << "if(tmp2-tmp1==sizeof(float)-1){\n";
					code_expr << "\tchar buff[sizeof(float)];int i,j;\n";
					code_expr << "\tfor(i=tmp1,j=0;i<=tmp2;++i,++j){\n";
					code_expr << "\t\tbuff[j]=" <<  blk_e->symp->name << "[i];\n";
					code_expr << "\t}\n";
					code_expr << "\tvoid * v_ptr = buff;\n";
					code_expr << "\tfloat *f_ptr = static_cast<float *>(v_ptr);\n";
					
					code_expr << "\t" ;
					lhs->print_expr(code_bef_expr, code_expr);
					code_expr << "=*f_ptr;\n";
					code_expr << "}else { cerr << \"runtime error: line_no : expr out of bounds\" << " 
						<< line_no  <<";}\n}\n";
				} else if (l_op->type==INT32_TYPE){
					code_expr << "if(tmp2-tmp1==sizeof(int)-1){\n";
					code_expr << "\tchar buff[sizeof(int)];int i,j;\n";
					code_expr << "\tfor(i=tmp1,j=0;i<=tmp2;++i,++j){\n";
					code_expr << "\t\tbuff[j]=" << blk_e->symp->name << "[i];\n";
					code_expr << "\t}\n";
					code_expr << "\tvoid * v_ptr = buff;\n";
					code_expr << "\tint *i_ptr = static_cast<int *>(v_ptr);\n";
					code_expr << "\t" ;
					lhs->print_expr(code_bef_expr, code_expr);
					code_expr << "=*i_ptr;\n" ;
					code_expr << "}else { \n\tcerr << \"runtime error: line_no : expr out of bounds\" <<"
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
		}
	} else if (r_op->e_type == oper_blk_arr_assgn && l_op->e_type==oper_blk_arr_assgn){
		std::stringstream s;
		s << "unhandled case LHS. Error in code generation file: ";
		print_err(compiler_internal_error, s.str(), line_no, __LINE__, __FILE__);
		code_expr <<  "error\n";
	}else {
		if(l_op->type==QUESTION_TYPE){
			un2_expr* lhs= static_cast<un2_expr*>(l_op);
			const symtab_ent * symp = lhs->get_symp_ptr();
			question* q = find_in_question_list(symp->name);
			string cpp_data_type=human_readable_type(q->dt);
			string tmp_name = get_temp_name();
			
			code_expr << cpp_data_type << " " << tmp_name << "=";
			r_op->print_expr(code_bef_expr, code_expr);
			code_expr << ";" << endl;
			code_expr << "if ( " << q->name << "->is_valid("<<  tmp_name
				<<  ")) {" << endl; 
			code_expr << q->name << "->input_data.clear();" << endl;
			code_expr << q->name << "->input_data.insert(";
			//r_op->print_expr(code_bef_expr, code_expr);
			code_expr << tmp_name ;
			code_expr << ") ; " << endl ;
			code_expr << "}";
			cerr << "WARNING : line: " << __LINE__ 
				<< ", file: " << "__FILE__"
				<< " put range check on allowed codes" 
				<< endl;

		} else {
			l_op->print_expr(code_bef_expr, code_expr);
			code_expr << " /* oper_assgn */ = ";
			r_op->print_expr(code_bef_expr, code_expr);
		}
	}
}


void un2_expr::print_expr(ostringstream& code_bef_expr, ostringstream & code_expr){
	switch(e_type){
		case oper_name:{
			code_expr <<  symp->name;
		}
		break;
		case oper_arrderef:{
			code_expr <<   symp->name << "[";
			operand->print_expr(code_expr, code_expr);
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
			//cout << "/* oper_func_call */" << endl;
			//cout << "func_index_in_table: " << func_info_table[e->func_index_in_table]->fname << endl;
			if(func_info_table[func_index_in_table]->fname==string("printf")){
				code_expr <<  "fprintf(xtcc_stdout,";
			} else {
				code_expr << func_info_table[func_index_in_table]->fname.c_str() << "(";
			}
			struct expr* e_ptr=operand;
			//fprintf(edit_out,  "/*print_expr: oper_func_call:  %s*/", func_info_table[func_index_in_table]->fname.c_str() );
			while(e_ptr){
				e_ptr->print_expr(code_bef_expr, code_expr);
				if(e_ptr->next){
					code_expr <<  ", ";
				} 
				e_ptr=e_ptr->next;
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
			print_err(compiler_internal_error, "This case should not occur\n", 
						line_no, __LINE__, __FILE__);
		}
		break;
		default:
			//fprintf(edit_out, "unhandled expr operator\n");
			code_expr << "unhandled expr operator\n";
			print_err(compiler_internal_error, "unhandled expr operator\n", 
						line_no, __LINE__, __FILE__);
	}
}

//void bin_expr::print_expr(FILE * edit_out)
void bin_expr::print_expr(ostringstream& code_bef_expr, ostringstream & code_expr){
	switch(e_type){
		char oper_buf[3];
		case oper_plus:{
			sprintf(oper_buf, "%s" , "+");
			l_op->print_expr(code_bef_expr, code_expr);
			//fprintf(edit_out, " %s ", oper_buf);
			code_expr << oper_buf;
			r_op->print_expr(code_bef_expr, code_expr);
			}
		break;	       
		case oper_minus:{
			sprintf(oper_buf, "%s" , "-");
			l_op->print_expr(code_bef_expr, code_expr);
			code_expr << oper_buf;
			r_op->print_expr(code_bef_expr, code_expr);
			}
		break;	       
		case oper_mult:{
			sprintf(oper_buf, "%s" , "*");
			l_op->print_expr(code_bef_expr, code_expr);
			code_expr << oper_buf;
			r_op->print_expr(code_bef_expr, code_expr);
			}
		break;	       
		case oper_div:{
			sprintf(oper_buf, "%s" , "/");
			l_op->print_expr(code_bef_expr, code_expr);
			code_expr << oper_buf;
			r_op->print_expr(code_bef_expr, code_expr);
			}
		break;	       
		case oper_mod:{
			sprintf(oper_buf, "%s" , "%");
			l_op->print_expr(code_bef_expr, code_expr);
			code_expr << oper_buf;
			r_op->print_expr(code_bef_expr, code_expr);
			}
		break;	      
		case oper_lt:{
			sprintf(oper_buf, "%s" , "<");
			l_op->print_expr(code_bef_expr, code_expr);
			code_expr << oper_buf;
			r_op->print_expr(code_bef_expr, code_expr);
			}
		break;	       
		case oper_gt:{
			sprintf(oper_buf, "%s" , ">");
			l_op->print_expr(code_bef_expr, code_expr);
			code_expr << oper_buf;
			r_op->print_expr(code_bef_expr, code_expr);
			}
		break;	       
		case oper_le:{
			sprintf(oper_buf, "%s" , "<=");
			l_op->print_expr(code_bef_expr, code_expr);
			code_expr << oper_buf;
			r_op->print_expr(code_bef_expr, code_expr);
			}
		break;	       
		case oper_ge:{
			sprintf(oper_buf, "%s" , ">=");
			l_op->print_expr(code_bef_expr, code_expr);
			code_expr << oper_buf;
			r_op->print_expr(code_bef_expr, code_expr);
			}
		break;	       
		case oper_iseq:{
			sprintf(oper_buf, "%s" , "==");
			l_op->print_expr(code_bef_expr, code_expr);
			code_expr << oper_buf;
			r_op->print_expr(code_bef_expr, code_expr);
			}
		break;	       
		case oper_isneq: {
			sprintf(oper_buf, "%s" , "!=");
			l_op->print_expr(code_bef_expr, code_expr);
			code_expr << oper_buf;
			r_op->print_expr(code_bef_expr, code_expr);
			}
		break;	       
		case oper_assgn:
			//print_oper_assgn(edit_out);		
			print_oper_assgn(code_bef_expr, code_expr);		
		break;
		case oper_or:{
			sprintf(oper_buf, "%s" , "||");
			l_op->print_expr(code_bef_expr, code_expr);
			code_expr << oper_buf;
			r_op->print_expr(code_bef_expr, code_expr);
			}
		break;
		case oper_and:{
			sprintf(oper_buf, "%s" , "&&");
			l_op->print_expr(code_bef_expr, code_expr);
			code_expr << oper_buf;
			r_op->print_expr(code_bef_expr, code_expr);
			}
		break;
		default:
			code_expr << " unhandled operator type in expr  ";
			print_err(compiler_sem_err, " unhandled operator type in expr  ", 
						line_no, __LINE__, __FILE__);
	}
}

bin_expr::~bin_expr(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "bin_expr::~bin_expr setting mem_addr: " << this  <<"=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting bin_expr: e_type: " << e_type << endl;
	if(l_op) { delete l_op; l_op=0;}
	if(r_op) { delete r_op; r_op=0;}
}

un2_expr::~un2_expr(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			debug_log_file << "un2_expr::~un2_expr setting mem_addr: " << this << "=0" << endl;
			mem_addr[i].mem_ptr=0;
			break;
		}
	}
	debug_log_file << "deleting un2_expr: e_type: " << e_type << endl;
	if(e_type==oper_func_call){
		//cout << "line_no: " << line_no << endl;
	}
	if(text) { free( text) ; text=0; }
	if(operand) { delete operand; operand=0; }
	if(operand2) { delete operand2; operand2=0;}
	//if(symp) { delete symp; symp=0; }
}

bin_expr::bin_expr(expr* llop, expr* lrop,e_operator_type letype):
	expr(letype), l_op(llop), r_op(lrop){
	if (e_type!=oper_assgn && 
		(l_op->e_type==oper_blk_arr_assgn
		 	||r_op->e_type==oper_blk_arr_assgn)){
		type=ERROR_TYPE;
		++no_errors;
		print_err(compiler_sem_err, 
			"error: oper_blk_arr_assgn: used in binary expr ",
			line_no, __LINE__, __FILE__);
	} else if (e_type ==oper_assgn){
		if( (!l_op->is_lvalue()) ){
			type=ERROR_TYPE;
			++no_errors;
			print_err(compiler_sem_err, 
				"oper_assgn error: lhs of \
				assignment should be lvalue ", 
				line_no, __LINE__, __FILE__);
		}
		datatype typ1=l_op->type;
		datatype typ2=r_op->type;
		if(!void_check(l_op->type, r_op->type, type)){
			print_err(compiler_sem_err, 
				"oper_assgn error: operand data types on \
				lhs and rhs should be of non-VOID type", 
				line_no, __LINE__, __FILE__);
			type = ERROR_TYPE;
			++no_errors;
		}
		if(typ1==QUESTION_TYPE){
			un2_expr* lhs= static_cast<un2_expr*>(l_op);
			const symtab_ent * symp = lhs->get_symp_ptr();
			//cerr << "Question name: " << symp->name << endl;
			question* q = find_in_question_list(symp->name);
			if(!q) {
				stringstream s;
				s << "Question not found in symbol table after parsing input" << endl;
				print_err(compiler_internal_error, s.str(), 
					line_no, __LINE__, __FILE__);
			} else {
				if(q->q_type!=spn){
					stringstream s;
					s << "Direct assignment to question only allowed for SPN question_type" << endl;
					print_err(compiler_internal_error, s.str(), 
						line_no, __LINE__, __FILE__);
				} 
			}
		} else if(!check_type_compat(typ1, typ2)){
			type = ERROR_TYPE;
			stringstream s;
			s << "oper_assgn error: operand data types on lhs and rhs should be compatible, ";
			string lhs_hr_type = human_readable_type(typ1);
			string rhs_hr_type = human_readable_type(typ2);
			s << "\tlhs type: " << lhs_hr_type << ", rhs type: " << rhs_hr_type << endl;
			print_err(compiler_sem_err, s.str(), 
				line_no, __LINE__, __FILE__);
		}
	} else 
	switch(e_type){
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
			if(void_check(l_op->type, r_op->type, type)/*true*/){
				type=lcm_type(l_op->type, r_op->type);
			}
			if(e_type==oper_mod && !( is_of_int_type(l_op->type) && is_of_int_type(r_op->type))){
				print_err(compiler_sem_err, 
					" operands of %% should be of type int/char only", line_no, __LINE__, __FILE__);
				//cerr << " operands of %% should be of type int/char only" << endl;
				//++no_errors;
				type=ERROR_TYPE;
			}
		break;
		default:
			print_err(compiler_internal_error, " INTERNAL ERROR: default case of bin_expr", line_no, __LINE__, __FILE__);
			;
	}
}
un2_expr::un2_expr( struct symtab_ent * lsymp): 
	expr(oper_name,lsymp->type), symp(lsymp), isem_value(0), dsem_value(0),
	func_index_in_table(-1), text(0), operand(0), operand2(0) {
}

map<string, symtab_ent*>::iterator find_in_symtab(string id);
un2_expr::un2_expr(char* ltxt, e_operator_type le_type): 
	expr(le_type, INT8_TYPE), symp(0), isem_value(0), dsem_value(0), 
	func_index_in_table(-1), text(ltxt), column_no(-1), 
	operand(0), operand2(0) {
	if(e_type==oper_text_expr){
		type=STRING_TYPE;
		//free(ltxt);
	} else if(e_type==oper_name){
		map<string,symtab_ent*>::iterator sym_it = find_in_symtab(ltxt);
		if(sym_it==active_scope->sym_tab.end() ){
			//cerr << "Error: could not find:" << $1<<"  in symbol table: lineno: " << line_no << "\n";
			string err_msg = "Error: could not find:" + string(text) + "  in symbol table  ";
			print_err(compiler_sem_err, err_msg, line_no, __LINE__, __FILE__);
			type=ERROR_TYPE;
		} else {
			symp = sym_it->second;
			type = symp->type;
			/*$$ = new un2_expr(sym_it->second );
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
			*/
		}
	}
}

#include <sstream>
un2_expr::un2_expr(e_operator_type le_type, /*datatype dt, struct symtab_ent * lsymp,*/ string name, expr* arr_index): 
	expr(le_type, ERROR_TYPE), symp(0) /* symp(lsymp)*/, isem_value(0), 
	dsem_value(0), func_index_in_table(-1), text(0),
	column_no(-1), operand(arr_index),  operand2(0)
{
	map<string,symtab_ent*>::iterator sym_it = find_in_symtab(name);
	if(sym_it==active_scope->sym_tab.end() ){
		std::stringstream s;
		s << "Error: Array indexing expr: could not find name: " 
			<< name <<"  in symbol table: lineno: " << line_no << "\n";
		print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
	} else {
		symtab_ent* se=sym_it->second;
		symp = se;
		datatype e_type=arr_index->type;
		if(is_of_int_type(e_type)){
			datatype nametype =arr_deref_type(se->type);
			if(nametype==ERROR_TYPE) {
				std::stringstream s;
				s << "ERROR: Array indexing expr Variable being indexed not of Array Type : Error: lineno: " << line_no << "\n";
				print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
			} else {
				//$$ = new un2_expr(oper_arrderef, nametype,  se, $3);
				type = nametype;
			}
		} else {
			stringstream s;
			s << "ERROR: Array index not of Type Int : Error: lineno: " << line_no << "\n";
			print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		}
	}
}

un2_expr::un2_expr(e_operator_type le_type, /* datatype dt, struct symtab_ent * lsymp,*/ string name,
		expr* arr_index, expr* arr_index2): 
		expr(le_type, ERROR_TYPE), symp(0), isem_value(0), dsem_value(0), func_index_in_table(-1), text(0),
		column_no(-1), operand(arr_index), operand2(arr_index2){
		symtab_ent* se=0;
		map<string,symtab_ent*>::iterator sym_it1 = find_in_symtab(name);
		if( sym_it1==active_scope->sym_tab.end()) {
			std::stringstream s;
			s << "Error: Block Array assignment expr: could not find name: " 
				<< name <<"  in symbol table: lineno: " << line_no << "\n";
			print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		} else {
			se=sym_it1->second;
			symp = se;
		}
		if( !(se)){
			std::stringstream s;
			s << "Error: Block Array assignment expr: could not find name: " 
				<< name <<"  in symbol table: lineno: " << line_no << "\n";
			print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		}  else {
			datatype e_type1=arr_index->type;
			datatype e_type2=arr_index2->type;
			if( is_of_int_type (e_type1)&& 
				is_of_int_type(e_type2)	){
				datatype d1=arr_deref_type(se->type);
				if(d1==ERROR_TYPE){
					std::stringstream s;
					s << "ERROR: Block Array assignment expr Variable: " 
						<< name << " being indexed not of Array Type : Error: lineno: " 
						<< line_no << "\n";
					print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
				} else {

					//$$ = new un2_expr(oper_blk_arr_assgn, d1, se,$3,$5);
					//void *ptr=$$;
					//mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
					//mem_addr.push_back(m1);
					type = d1;
				}
			} else {
				stringstream s;
				s <<  "ERROR: NAME  =NAME[EXPR, EXPR] EXPR should be of type int or char: lineno: " 
					<< line_no << "\n";
				print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
			}
		}
		//free($1);
	}

bool un2_expr::is_lvalue(){ 
	if(e_type==oper_name|| e_type==oper_arrderef){
		return true;
	} else {
		return false;
	}
}

un2_expr::un2_expr(int l_isem_value): 
		expr(oper_num), symp(0), isem_value(l_isem_value), dsem_value(0), func_index_in_table(-1),
		text(0), column_no(-1), operand(0), operand2(0){
		if( isem_value >= SCHAR_MIN && isem_value<=SCHAR_MAX){
			type=INT8_TYPE;
		} else if (isem_value>= SHRT_MIN && isem_value <= SHRT_MAX){
			type=INT16_TYPE;
		} else if (isem_value>= INT_MIN && isem_value <= INT_MAX){
			type=INT32_TYPE;
		} else {
			++no_errors;
			cerr << "very  large integer unhandleable type most probably";
			type = ERROR_TYPE;
		}
		//cout << "parsed integer number: type" << type << endl; 
	}

/*
un2_expr::un2_expr(e_operator_type le_type, datatype ldt, expr* e_list, int lfunc_index_in_table, int lline_no):
	expr(le_type, ldt),  symp(0), 	isem_value(0), dsem_value(0), func_index_in_table(lfunc_index_in_table), 
	text(0), column_no(-1), operand(e_list), operand2(0), line_no(lline_no) {}
*/	

un2_expr::un2_expr(e_operator_type le_type, datatype ldt, expr* e_list, int lfunc_index_in_table):
	expr(le_type, ldt),  symp(0), 	isem_value(0), dsem_value(0), func_index_in_table(lfunc_index_in_table), 
	text(0), column_no(-1), operand(e_list), operand2(0) {}

un2_expr::un2_expr(double l_dsem_value): 
	expr(oper_float,FLOAT_TYPE), symp(0), isem_value(0), dsem_value(l_dsem_value),
	func_index_in_table(-1), text(0), operand(0), operand2(0) {}

un2_expr::un2_expr(datatype d): 
		expr(oper_err,d), symp(0), isem_value(0), dsem_value(0), func_index_in_table(-1), text(0),
		column_no(-1), operand(0), operand2(0)
	{}

#if 0
	xtcc_set::xtcc_set(): range(0){ 
		//range(0), indiv(0){
		//range.reset(0);
		//indiv.resize(0);
		//range.resize(0);
	}

	xtcc_set::xtcc_set(datatype dt, string name, xtcc_set& xs): 
		range(xs.range), indiv(xs.indiv){
	}
	xtcc_set::xtcc_set(xtcc_set& xs1): range(xs1.range), indiv(xs1.indiv){
	}

	xtcc_set& xtcc_set::operator= (const xtcc_set& xs1){
		range=xs1.range;
		indiv = xs1.indiv;
		return *this;
	}

void xtcc_set::reset(){
	range.clear();
	indiv.clear();
}

void xtcc_set::add_range(int n1, int n2){
	range.push_back( pair<int,int>(n1, n2));
}

void xtcc_set::add_indiv(int n1){
	indiv.insert(n1);
}
#endif /* 0 */

bin2_expr::bin2_expr(expr* llop , xtcc_set& l_rd, 
		e_operator_type letype):expr(letype)/*, l_op(llop)*/{
	cerr << "bin2_expr::bin2_expr" << endl;
	switch(e_type){
		case oper_in:
			switch( llop->e_type){
			case oper_name:
			case oper_arrderef:
				type = BOOL_TYPE;
				cerr << "bin2_expr::static_cast" << endl;
				l_op=static_cast<un2_expr*>(llop);
				xs = new xtcc_set(l_rd);
				break;
			default:
				l_op=0;
				type = ERROR_TYPE;
				string err_msg = "bin2_expr:: lhs operator for oper_in can only be NAME or NAME[INDEX]";
				print_err(compiler_sem_err, err_msg, 
					line_no, __LINE__, __FILE__);
				type=ERROR_TYPE;
			}
			break;
		default: {
			l_op=0;
			type = ERROR_TYPE;
			string err_msg = "bin2_expr:: operator in e_type can only be oper_in";
			print_err(compiler_sem_err, err_msg, line_no, __LINE__, __FILE__);
			type=ERROR_TYPE;
		}
	}
}

#if 0
bin2_expr::bin2_expr(string lname , string rname ,e_operator_type letype): expr(letype) {
	switch(e_type){
		case oper_in: {
			datatype  l_type, r_type;

			map<string,symtab_ent*>::iterator sym_it_l = find_in_symtab(lname);
			if( sym_it_l==active_scope->sym_tab.end() ){
				string err_msg = "Error: could not find:" + lname + "  in symbol table  ";
				print_err(compiler_sem_err, err_msg, line_no, __LINE__, __FILE__);
				type=ERROR_TYPE;
			} else {
				l_symp = sym_it_l->second;
				l_type = l_symp->type;
			}

			map<string,symtab_ent*>::iterator sym_it_r = find_in_symtab(rname);
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
			print_err(compiler_internal_error, "unhandled case for bin2_expr::bin2_expr", 
				line_no, __LINE__, __FILE__);
	}
}
#endif /* 0 */

#if 0
void bin2_expr::print_expr (FILE * edit_out){
	switch(e_type){
		case oper_in:
			fprintf(edit_out, "/*printing OPER IN*/");
		default:
			print_err(compiler_internal_error, "ERROR bin2_expr:: was passed oper_in with invalid data ", 
					line_no, __LINE__, __FILE__);
	}
}
#endif /* 0 */

void bin2_expr::print_expr(ostringstream& code_bef_expr, ostringstream & code_expr){

	fprintf(stderr, "bin2_expr::print_expr()\n");
	//fflush(fptr);
	string struct_name = get_temp_name();
	fprintf(stderr, "bin2_expr::print_expr(): after get_temp_name()\n");
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
	fprintf(stderr, "bin2_expr::print_expr(): printed constructor");
	/*
	for(int i=0; i< r_data->rcount; ++i){
		code_bef_expr << "\t\t\tran_start_end[" << i 
			<< "]=pair<int,int>(" 
			<< r_data->ran_start_end[i*2] 
			<< "," << r_data->ran_start_end[i*2+1] << ");\n";
	}
	*/
	for(int i=0; i< xs->range.size() ; ++i){
		code_bef_expr << "\t\t\tran_start_end[" << i 
			<< "]=pair<int,int>(" 
			<< xs->range[i].first 
			<< "," << xs->range[i].second << ");\n";
	}
	/*
	for(int i=0; i< r_data->icount; ++i){
		code_bef_expr << "\t\t\tran_indiv[" 
			<< i << "]=" << r_data->ran_indiv[i] <<";\n";
	}*/
	
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
	code_bef_expr << "\t\t\tif(!val_exists){\n";
	code_bef_expr << "\t\t\t\treturn false;\n";
	code_bef_expr << "\t\t\t}\n";
	code_bef_expr << "\t\t}\n";
	string struct_name1 = get_temp_name();
	code_bef_expr << "\t} " <<  struct_name1.c_str() <<";\n";
	
	switch(l_op->get_symp_ptr()->type){
		case INT8_TYPE ... DOUBLE_REF_TYPE:
		case BOOL_TYPE:{	
			string test_bool_var_name=get_temp_name();
			code_bef_expr <<  "bool " <<  test_bool_var_name.c_str()
				<< " = " << struct_name1.c_str()
				<< ".exists(";
			//<< name.c_str() << ");\n";
			ostringstream code_bef_expr1_discard, code_expr1;
			l_op->print_expr(code_bef_expr1_discard, code_expr1);
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
			l_op->print_expr(code_bef_expr1_discard, code_expr1);
			code_bef_expr << code_expr1.str() 
				<< "->input_data"
				<< ");\n";
			code_expr << test_bool_var_name.c_str() << " " ;
		}
		break;	
		default:	
			std::stringstream s;
			s << "file: " << __FILE__ << ", line: " << __LINE__ << endl;
			print_err(compiler_internal_error, s.str(), line_no, __LINE__, __FILE__);
	}

}


bin2_expr::~bin2_expr(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "bin2_expr::~bin2_expr setting mem_addr: " << this  <<"=0" << endl;
			break;
		}
	}
}


string get_temp_name(){
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

