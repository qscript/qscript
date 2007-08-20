#ifndef xtcc_expr_h
#define xtcc_expr_h
#include "tree.h"


struct expr {
	e_operator_type e_type;
	datatype type;
	struct expr * prev, *next;
	expr(e_operator_type le_type):e_type(le_type), type(ERROR_TYPE), prev(0), next(0) { }
	expr(e_operator_type le_type, datatype ldt):e_type(le_type), type(ldt), prev(0), next(0) 
	{}
	virtual void print_expr(FILE * edit_out)=0;
	virtual int isvalid();
	virtual bool is_lvalue()=0;
};

extern int no_errors;
extern int line_no;

struct un_expr : public expr{
	expr* operand;
	un_expr( expr * l_operand=0, e_operator_type le_type=oper_err):expr(le_type), operand(l_operand){
		if(operand->e_type==oper_blk_arr_assgn){
			++no_errors;
			cerr << "oper_blk_arr_assgn: cannot be used with unary operators : line_no:" 
				<< line_no << endl;
		} else {
			type=INT8_TYPE;
		}
	}
	bool is_lvalue(){ return false; }
	void print_expr(FILE * edit_out){
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
};

extern vector <func_info*> func_info_table;
struct un2_expr : public expr{
	struct symtab_ent * symp;
	int isem_value;
	double dsem_value;
	int func_index_in_table;
	char * text;
	int column_no;
	expr* operand;
	expr* operand2;
	bool is_lvalue(){ 
		if(e_type==oper_name|| e_type==oper_arrderef){
			return true;
		} else {
			return false;
		}
	}
	un2_expr(e_operator_type le_type, datatype ldt, expr* e_list, int lfunc_index_in_table):
		expr(le_type, ldt),   func_index_in_table(lfunc_index_in_table),operand(e_list), operand2(0){}
	un2_expr(int l_isem_value): 
		expr(oper_num), isem_value(l_isem_value), dsem_value(0), func_index_in_table(-1),
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
	un2_expr(double l_dsem_value): 
		expr(oper_float,FLOAT_TYPE), dsem_value(l_dsem_value) {}
	un2_expr( struct symtab_ent * lsymp): 
		expr(oper_name,lsymp->type), symp(lsymp) {
			//cout << "parsed Name expr: type: " << lsymp->type << " line_no: " << line_no << endl; 
				
		}
	un2_expr(datatype d): 
		expr(oper_err,d){}
	un2_expr(e_operator_type le_type, datatype dt, struct symtab_ent * lsymp, expr* arr_index): 
		expr(le_type, dt), symp(lsymp), operand(arr_index){}
	un2_expr(e_operator_type le_type, datatype dt, struct symtab_ent * lsymp, expr* arr_index, expr* arr_index2): 
		expr(le_type, dt), symp(lsymp), operand(arr_index), operand2(arr_index2){}
	un2_expr(char* ltxt): 
		expr(oper_text_expr, U_INT8_TYPE), text(ltxt){}

	void print_expr(FILE * edit_out){
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
#if 0
				if(edit_out){
					fprintf(edit_out,"/* DATA CONVERSION */\n");
					fprintf(edit_out,"{int tmp1=");
					operand->print_expr(edit_out);
					fprintf(edit_out,";\nint tmp2=");
					operand2->print_expr(edit_out);
					fprintf(edit_out,";\n");
					if(lsymp->get_type()==FLOAT_TYPE) {
						fprintf(edit_out,"if(tmp2-tmp1==sizeof(float)-1){\n");
						fprintf(edit_out,"\tchar buff[sizeof(float)];int i,j;\n");
						fprintf(edit_out,"\tfor(i=tmp1,j=0;i<=tmp2;++i,++j){\n");
						fprintf(edit_out,"\t\tbuff[j]=%s[i];\n", rsymp->name);
						fprintf(edit_out,"\t}\n");
						fprintf(edit_out,"\tvoid * v_ptr = buff;\n");
						fprintf(edit_out,"\tfloat *f_ptr = static_cast<float *>(v_ptr);\n");
						fprintf(edit_out,"\t %s=*f_ptr;\n", lsymp->name);
						fprintf(edit_out,"}else { cerr << \"runtime error: line_no : expr out of bounds\" << %d;}\n}\n", line_number );
					} else if (lsymp->get_type()==INT32_TYPE
							|| lsymp->get_type()==U_INT32_TYPE){
						fprintf(edit_out,"if(tmp2-tmp1==sizeof(int)-1){\n");
						fprintf(edit_out,"\tchar buff[sizeof(int)];int i,j;\n");
						fprintf(edit_out,"\tfor(i=tmp1,j=0;i<=tmp2;++i,++j){\n");
						fprintf(edit_out,"\t\tbuff[j]=%s[i];\n", rsymp->name);
						fprintf(edit_out,"\t}\n");
						fprintf(edit_out,"\tvoid * v_ptr = buff;\n");
						fprintf(edit_out,"\tint *i_ptr = static_cast<int *>(v_ptr);\n");
						fprintf(edit_out,"\t %s=*i_ptr;\n", lsymp->name);
						fprintf(edit_out,"}else { \n\tcerr << \"runtime error: line_no : expr out of bounds\" << %d;}\n}\n", line_number );
					}
				}
#endif /* 0 */
			}
			break;
			default:
				fprintf(edit_out, "unhandled expr operator\n");
		}
	}
};

struct bin_expr: public expr{
	expr *l_op, *r_op;
	bin_expr(expr* llop, expr* lrop,e_operator_type letype):expr(letype), l_op(llop), r_op(lrop){
		if (e_type!=oper_assgn && (l_op->e_type==oper_blk_arr_assgn||r_op->e_type==oper_blk_arr_assgn)){
			type=ERROR_TYPE;
			++no_errors;
			cerr << " oper_blk_arr_assgn: used in binary expr " << line_no << endl;
		} else if (e_type ==oper_assgn && (!l_op->is_lvalue()) ){
			type=ERROR_TYPE;
			++no_errors;
			cerr << "  non lvalue used on LHS of oper_blk_arr_assgn: line_no: " << line_no << endl;
		}
	}
	bool is_lvalue(){ return false; }
	void print_oper_assgn(FILE * edit_out);
	void print_expr(FILE * edit_out){
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
			default:
				fprintf(edit_out, " unhandled operator type in expr  " );
				
			
		}
	}
};

/*
struct expr{
	datatype type;
	struct expr * l_op;
	struct expr * r_op;
	e_operator_type e_operator;
	struct symtab_ent * symp;
	int line_number;
	int isem_value;
	double dsem_value;
	int column_no;
	int column_no_2;
	struct expr * prev, *next;
	int func_index_in_table;
	char * text;
	datatype get_type();
	int isvalid();
	expr( expr* left, expr* right, e_operator_type eop):
		type(uninit), 
		l_op(left), r_op(right), e_operator(eop),
		symp(0), line_number(-1), isem_value(0),dsem_value(0),column_no(-1), column_no_2(-1),
		prev(0), next(0), func_index_in_table(-1), text(0)
	{
		type=lcm_type(l_op->type, r_op->type);
	}
	private:
	expr& operator=(const expr&);	
	expr(const expr&);	
};

void print_expr(FILE* edit_out, struct expr * e){
	if(e) {
		switch(e->e_operator){
			char oper_buf[3];


			default:
				fprintf(edit_out, "Unhandled expression type: %c\n", 
					e->type);
		}
	}
}
*/



#endif /* xtcc_expr_h */
