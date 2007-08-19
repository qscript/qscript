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
		} else if (l_op->type==INT32_TYPE || l_op->type==U_INT32_TYPE){
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
