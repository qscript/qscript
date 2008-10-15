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
#include "../../qscript/named_range.h"

extern scope* active_scope;
extern ofstream debug_log_file;
using namespace std;

extern	vector <func_info*> func_info_table;
extern vector<mem_addr_tab> mem_addr;
extern vector <named_range> named_stubs_list;
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


void un_expr::print_expr (FILE * edit_out){
	switch(e_type){
		case oper_umin:{
			fprintf(edit_out, "- ");
			operand->print_expr(edit_out);
		}
		break;

		case oper_not:{
			fprintf(edit_out, "! ");
			operand->print_expr(edit_out);
		}
		break;

		case oper_parexp:{
			fprintf(edit_out, "(");
			operand->print_expr(edit_out);
			fprintf(edit_out, ")");
			}
		break;
		default:
			fprintf(edit_out, " un handled operator\n" );

	}
}

void bin_expr::print_oper_assgn(FILE * edit_out){
	//fprintf(edit_out, "/*oper_assgn*/ %s =", symp->name);
	if(r_op->e_type == oper_blk_arr_assgn &&
		( l_op->e_type==oper_name||l_op->e_type==oper_arrderef)){
		un2_expr* blk_e = static_cast<un2_expr*> (r_op);
		un2_expr* lhs = static_cast<un2_expr*> (l_op);
		fprintf(edit_out,"/* DATA CONVERSION */\n");
		fprintf(edit_out,"{int tmp1=");
		blk_e->operand->print_expr(edit_out);
		fprintf(edit_out,";\nint tmp2=");
		blk_e->operand2->print_expr(edit_out);
		fprintf(edit_out,";\n");
		if(l_op->type==FLOAT_TYPE) {
			fprintf(edit_out,"if(tmp2-tmp1==sizeof(float)-1){\n");
			fprintf(edit_out,"\tchar buff[sizeof(float)];int i,j;\n");
			fprintf(edit_out,"\tfor(i=tmp1,j=0;i<=tmp2;++i,++j){\n");
			fprintf(edit_out,"\t\tbuff[j]=%s[i];\n", blk_e->symp->name);
			fprintf(edit_out,"\t}\n");
			fprintf(edit_out,"\tvoid * v_ptr = buff;\n");
			fprintf(edit_out,"\tfloat *f_ptr = static_cast<float *>(v_ptr);\n");
			
			//fprintf(edit_out,"\t %s=*f_ptr;\n", lsymp->name);
			fprintf(edit_out,"\t" );
			lhs->print_expr(edit_out);
			fprintf(edit_out,"=*f_ptr;\n");
			fprintf(edit_out,"}else { cerr << \"runtime error: line_no : expr out of bounds\" << %d;}\n}\n", line_no );
		} else if (l_op->type==INT32_TYPE){
			fprintf(edit_out,"if(tmp2-tmp1==sizeof(int)-1){\n");
			fprintf(edit_out,"\tchar buff[sizeof(int)];int i,j;\n");
			fprintf(edit_out,"\tfor(i=tmp1,j=0;i<=tmp2;++i,++j){\n");
			fprintf(edit_out,"\t\tbuff[j]=%s[i];\n", blk_e->symp->name);
			fprintf(edit_out,"\t}\n");
			fprintf(edit_out,"\tvoid * v_ptr = buff;\n");
			fprintf(edit_out,"\tint *i_ptr = static_cast<int *>(v_ptr);\n");
			//fprintf(edit_out,"\t %s=*i_ptr;\n", lsymp->name);
			fprintf(edit_out,"\t" );
			lhs->print_expr(edit_out);
			fprintf(edit_out,"=*i_ptr;\n" );
			fprintf(edit_out,"}else { \n\tcerr << \"runtime error: line_no : expr out of bounds\" << %d;}\n}\n", line_no );
		} else {
			fprintf(edit_out, "error\n");
			cerr << "Error in code generation" << endl;
		}
	} else if (r_op->e_type == oper_blk_arr_assgn && l_op->e_type==oper_blk_arr_assgn){
		fprintf(edit_out," unhandled case LHS ==");
	}else {
		l_op->print_expr(edit_out);
		fprintf(edit_out, "/*oper_assgn*/  = ");
		r_op->print_expr(edit_out);
	}
}


void un2_expr::print_expr(FILE * edit_out){
	switch(e_type){
		case oper_name:{
			fprintf(edit_out, "%s ", symp->name);
		}
		break;
		case oper_arrderef:{
			fprintf(edit_out, "%s[", symp->name);
			operand->print_expr(edit_out);
			fprintf(edit_out, "]");
			}
		break;

		case oper_num:{
			fprintf(edit_out, "%d ", isem_value);
		}
		break;
		case oper_float:{
			fprintf(edit_out, "%f ", dsem_value);
		}
		break;
		case oper_func_call:{
			//cout << "/* oper_func_call */" << endl;
			//cout << "func_index_in_table: " << func_info_table[e->func_index_in_table]->fname << endl;
			if(func_info_table[func_index_in_table]->fname==string("printf")){
				fprintf(edit_out, "fprintf(xtcc_stdout,");
			} else {
				fprintf(edit_out, "%s(", func_info_table[func_index_in_table]->fname.c_str());
			}
			struct expr* e_ptr=operand;
			//fprintf(edit_out,  "/*print_expr: oper_func_call:  %s*/", func_info_table[func_index_in_table]->fname.c_str() );
			while(e_ptr){
				e_ptr->print_expr(edit_out);
				if(e_ptr->next){
					fprintf(edit_out, ", ");
				} 
				e_ptr=e_ptr->next;
			}
			fprintf(edit_out, ")");
		}
		break;
		case oper_text_expr:{
			fprintf(edit_out, "%s", text);
		}
		break;
		case oper_blk_arr_assgn: {
			fprintf(edit_out,"This case should not occur\n");
		}
		break;
		default:
			fprintf(edit_out, "unhandled expr operator\n");
	}
}

void bin_expr::print_expr(FILE * edit_out){
	switch(e_type){
		char oper_buf[3];
		case oper_plus:{
			sprintf(oper_buf, "%s" , "+");
			l_op->print_expr(edit_out);
			fprintf(edit_out, " %s ", oper_buf);
			r_op->print_expr(edit_out);
			}
		break;	       
		case oper_minus:{
			sprintf(oper_buf, "%s" , "-");
			l_op->print_expr(edit_out);
			fprintf(edit_out, " %s ", oper_buf);
			r_op->print_expr(edit_out);
			}
		break;	       
		case oper_mult:{
			sprintf(oper_buf, "%s" , "*");
			l_op->print_expr(edit_out);
			fprintf(edit_out, " %s ", oper_buf);
			r_op->print_expr(edit_out);
			}
		break;	       
		case oper_div:{
			sprintf(oper_buf, "%s" , "/");
			l_op->print_expr(edit_out);
			fprintf(edit_out, " %s ", oper_buf);
			r_op->print_expr(edit_out);
			}
		break;	       
		case oper_mod:{
			sprintf(oper_buf, "%s" , "%");
			l_op->print_expr(edit_out);
			fprintf(edit_out, " %s ", oper_buf);
			r_op->print_expr(edit_out);
			}
		break;	      
		case oper_lt:{
			sprintf(oper_buf, "%s" , "<");
			l_op->print_expr(edit_out);
			fprintf(edit_out, " %s ", oper_buf);
			r_op->print_expr(edit_out);
			}
		break;	       
		case oper_gt:{
			sprintf(oper_buf, "%s" , ">");
			l_op->print_expr(edit_out);
			fprintf(edit_out, " %s ", oper_buf);
			r_op->print_expr(edit_out);
			}
		break;	       
		case oper_le:{
			sprintf(oper_buf, "%s" , "<=");
			l_op->print_expr(edit_out);
			fprintf(edit_out, " %s ", oper_buf);
			r_op->print_expr(edit_out);
			}
		break;	       
		case oper_ge:{
			sprintf(oper_buf, "%s" , ">=");
			l_op->print_expr(edit_out);
			fprintf(edit_out, " %s ", oper_buf);
			r_op->print_expr(edit_out);
			}
		break;	       
		case oper_iseq:{
			sprintf(oper_buf, "%s" , "==");
			l_op->print_expr(edit_out);
			fprintf(edit_out, " %s ", oper_buf);
			r_op->print_expr(edit_out);
			}
		break;	       
		case oper_isneq: {
			sprintf(oper_buf, "%s" , "!=");
			l_op->print_expr(edit_out);
			fprintf(edit_out, " %s ", oper_buf);
			r_op->print_expr(edit_out);
			}
		break;	       
		case oper_assgn:
			print_oper_assgn(edit_out);		
		break;
		case oper_or:{
			sprintf(oper_buf, "%s" , "||");
			l_op->print_expr(edit_out);
			fprintf(edit_out, " %s ", oper_buf);
			r_op->print_expr(edit_out);
			}
		break;
		case oper_and:{
			sprintf(oper_buf, "%s" , "&&");
			l_op->print_expr(edit_out);
			fprintf(edit_out, " %s ", oper_buf);
			r_op->print_expr(edit_out);
			}
		break;
		default:
			fprintf(edit_out, " unhandled operator type in expr  " );
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

bin_expr::bin_expr(expr* llop, expr* lrop,e_operator_type letype):expr(letype), l_op(llop), r_op(lrop){

	if (e_type!=oper_assgn && (l_op->e_type==oper_blk_arr_assgn||r_op->e_type==oper_blk_arr_assgn)){
		type=ERROR_TYPE;
		++no_errors;
		print_err(compiler_sem_err, "error: oper_blk_arr_assgn: used in binary expr ",
				line_no, __LINE__, __FILE__);
	} else if (e_type ==oper_assgn){
		if( (!l_op->is_lvalue()) ){
			type=ERROR_TYPE;
			++no_errors;
			print_err(compiler_sem_err, "oper_assgn error: lhs of assignment should be lvalue ", 
				line_no, __LINE__, __FILE__);
		}
		datatype typ1=l_op->type;
		datatype typ2=r_op->type;
		if(!void_check(l_op->type, r_op->type, type)){
			print_err(compiler_sem_err, "oper_assgn error: operand data types on lhs and rhs should be of non-VOID type", 
				line_no, __LINE__, __FILE__);
			type = ERROR_TYPE;
			++no_errors;
		}
		if(!check_type_compat(typ1, typ2)){
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
	expr(le_type, INT8_TYPE), symp(0), isem_value(0), dsem_value(0), func_index_in_table(-1), 
	text(ltxt), column_no(-1), operand(0), operand2(0) {
	if(e_type==oper_text_expr){
		type=STRING_TYPE;
		//free(ltxt);
	} else if(e_type==oper_name){
		map<string,symtab_ent*>::iterator sym_it = find_in_symtab(ltxt);
		if(sym_it==active_scope->sym_tab.end() ){
			//cerr << "Error: could not find:" << $1<<"  in symbol table: lineno: " << line_no << "\n";
			string err_msg = "Error: could not find:" + string(ltxt) + "  in symbol table  ";
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
					s << "ERROR: Block Array assignment expr Variable: " << name << " being indexed not of Array Type : Error: lineno: " << line_no << "\n";
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

un2_expr::un2_expr(e_operator_type le_type, datatype ldt, expr* e_list, int lfunc_index_in_table, int lline_no):
	expr(le_type, ldt),  symp(0), 	isem_value(0), dsem_value(0), func_index_in_table(lfunc_index_in_table), 
	text(0), column_no(-1), operand(e_list), operand2(0), line_no(lline_no) {}

un2_expr::un2_expr(double l_dsem_value): 
	expr(oper_float,FLOAT_TYPE), symp(0), isem_value(0), dsem_value(l_dsem_value),
	func_index_in_table(-1), text(0), operand(0), operand2(0) {}

un2_expr::un2_expr(datatype d): 
		expr(oper_err,d), symp(0), isem_value(0), dsem_value(0), func_index_in_table(-1), text(0),
		column_no(-1), operand(0), operand2(0)
	{}

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

void bin2_expr::print_expr (FILE * edit_out){
	switch(e_type){
		case oper_in:
			fprintf(edit_out, "/*printing OPER IN*/");
		default:
			print_err(compiler_internal_error, "ERROR bin2_expr:: was passed oper_in with invalid data ", 
					line_no, __LINE__, __FILE__);
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
