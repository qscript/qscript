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

#include "tree.h"
#include "expr.h"
#include <vector>
using namespace std;

extern	vector <func_info*> func_info_table;
extern vector<mem_addr_tab> mem_addr;

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
			cout << "un_expr::~un2_expr: setting mem_addr=0" << endl;
			break;
		}
	}
	cout << "deleting un_expr: e_type" << e_type << endl;
	if (operand) { delete operand; operand=0; }
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
				fprintf(edit_out, "%s(", func_info_table[func_index_in_table]->fname.c_str());
				struct expr* e_ptr=operand;
				//fprintf(edit_out,  "/*print_expr: oper_func_call:  %s*/", func_info_table[func_index_in_table]->fname.c_str() );
				while(e_ptr){
					e_ptr->print_expr(edit_out);
					if(e_ptr->prev){
						fprintf(edit_out, ", ");
					} 
					e_ptr=e_ptr->prev;
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
			cout << "bin_expr::~bin_expr: setting mem_addr=0" << endl;
			break;
		}
	}
	cout << "deleting bin_expr: e_type: " << e_type << endl;
	if(l_op) { delete l_op; l_op=0;}
	if(r_op) { delete r_op; r_op=0;}
}

un2_expr::~un2_expr(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			cout << "un2_expr::~un2_expr: setting mem_addr=0" << endl;
			mem_addr[i].mem_ptr=0;
			break;
		}
	}
	cout << "deleting un2_expr: e_type: " << e_type << endl;
	if(e_type==oper_func_call){
		cout << "line_no: " << line_no << endl;
	}
	if(text) { free( text) ; text=0; }
	if(operand) { delete operand; operand=0; }
	if(operand2) { delete operand2; operand2=0;}
	//if(symp) { delete symp; symp=0; }
}
