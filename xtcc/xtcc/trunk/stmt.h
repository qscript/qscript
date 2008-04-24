/*
 * stmt.h
 *  
 * implementation of statement handling routines in the xtcc grammar
 * Copyright (C) 2003,2004, 2005,2006,2007  Neil Xavier D'Souza <nxd_in@yahoo.com>
 * Postal MAil address
 * Neil Xavier D'Souza
 * 502, Premier Park
 * 1st Tank Lane,
 * Orlem, Malad(W),
 * Mumbai India. 400064.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
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
#ifndef _xtcc_stmt_h
#define _xtcc_stmt_h
using namespace std;
#include "scope.h"
#include "expr.h"

#include <cstdio>
#include <cstdlib>

	void print_expr(FILE* edit_out, struct expr * e);
	int search_for_func(string& search_for);
	extern scope* active_scope;
	extern int no_errors;
	extern noun_list_type noun_list[];

	//extern vector <func_info*> func_info_table;
	int check_func_decl_with_func_defn(struct var_list*& v_list, int & index, string func_name);
// Note : I may have to add file name we are compiling very soon
struct stmt{
	public:
	struct stmt * prev;
	struct stmt * next;
	datatype type;
	int line_number;
	virtual void print_stmt_lst(FILE * & fptr)=0;
	bool exists_next(){
		return prev;
	}
	bool exists_prev(){
		return next;
	}
	stmt* move_next(){
		return prev;
	}
	stmt(datatype dtype=ERROR_TYPE, int lline_number=0):prev(0), next(0), type(dtype), line_number(lline_number){}
	virtual ~stmt();
	private:
		stmt(const stmt&);
		stmt& operator=(const stmt&);
};

struct for_stmt: public stmt{
	struct expr * init, * test, *incr;
	struct stmt * for_body;
	for_stmt(datatype dtype, int lline_number, expr* l_init, expr* l_test, expr* l_incr, stmt * lfor_body);
	void print_stmt_lst(FILE * & fptr){
		fflush(fptr);

		if(fptr){
			fprintf(fptr,  "for (");
			init->print_expr(fptr);
			fprintf(fptr,  ";");
			test->print_expr(fptr);
			fprintf(fptr,  ";");
			incr->print_expr(fptr);
			fprintf(fptr, ")");
			fflush(fptr);
			for_body->print_stmt_lst(fptr);
			if(next) next->print_stmt_lst(fptr);
		}
	}
	virtual ~for_stmt();
	private:
	for_stmt& operator=(const for_stmt&);	
	for_stmt(const for_stmt&);	
};

// Refinement3
struct if_stmt : public stmt{
	protected:
	struct expr * condition;
	struct stmt * if_body;
	struct stmt * else_body;
	public:
	if_stmt( datatype dtype, int lline_number, 
		struct  expr * lcondition, struct  stmt * lif_body, struct stmt * lelse_body=0);
	void print_stmt_lst(FILE * & fptr){
		fflush(fptr);

		if(fptr){
			fprintf(fptr,  "if (");
			condition->print_expr(fptr);
			fprintf(fptr,  ")");
			fflush(fptr);
			if_body->print_stmt_lst(fptr);
			fflush(fptr);
			if(else_body){
				fprintf(fptr,  " else ");
				else_body->print_stmt_lst(fptr);
			}
			if(next) next->print_stmt_lst(fptr);
		}
	}
	virtual ~if_stmt();
	private:
	if_stmt& operator=(const if_stmt&);	
	if_stmt(const if_stmt&);	
};

struct expr_stmt: public stmt{
	struct expr* expr;
	expr_stmt(datatype dtype, int lline_number, struct expr* e): stmt(dtype, lline_number), expr(e) {}
	void print_stmt_lst(FILE * & fptr){
		fflush(fptr);

		if(fptr){
			//print_expr(fptr, expr);
			expr->print_expr(fptr);
			fprintf(fptr,";\n");
			if(next) next->print_stmt_lst(fptr);
		}
	}
	virtual ~expr_stmt();
	private:
	expr_stmt& operator=(const expr_stmt&);	
	expr_stmt(const expr_stmt&);	
};

struct err_stmt: public stmt{
	err_stmt( int lline_number): stmt(ERROR_TYPE, lline_number){}
	void print_stmt_lst(FILE * & fptr){
		fflush(fptr);

		if(fptr){
			fprintf(fptr, "error");
			//if(next) next->print_stmt_lst(fptr);
		}
	}
	private:
	err_stmt& operator=(const err_stmt&);	
	err_stmt(const err_stmt&);	
};

struct cmpd_stmt: public stmt{
	struct stmt* cmpd_bdy;
	struct scope * sc;
	int flag_cmpd_stmt_is_a_func_body;
	public:
	cmpd_stmt(datatype dtype, int lline_number, int l_flag_cmpd_stmt_is_a_func_body): 
		stmt(dtype, lline_number), cmpd_bdy(0), sc(0), flag_cmpd_stmt_is_a_func_body(l_flag_cmpd_stmt_is_a_func_body) {}
	void print_stmt_lst(FILE * & fptr){
		fflush(fptr);
		if(fptr){
			fprintf(fptr,"{\n");
			if (cmpd_bdy) cmpd_bdy->print_stmt_lst(fptr);
			fprintf(fptr,"}\n");
			if(next) next->print_stmt_lst(fptr);
		}
	}
	virtual ~cmpd_stmt();
	private:
	cmpd_stmt& operator=(const cmpd_stmt&);	
	cmpd_stmt(const cmpd_stmt&);	
};

struct fld_stmt: public stmt{
	struct symtab_ent * lsymp, *rsymp;
	expr* start_col, *end_col;
	// I may need to change width also to expression -> in case of passing
	// argument width to a subroutine within the language syntax
	int width;
	fld_stmt(string lhs_name, string rhs_name , expr* l_s, expr* l_e, int l_w);
	void print_stmt_lst(FILE * & fptr){
		// runtime checks need to be put
		// 1 startcol < endcol
		// endcol-startcol+1 % width == 0
		fprintf(fptr, "/* fld stmt code will be generated here */\n");

		fprintf(fptr, "{\n");
		fprintf(fptr, "\tfor (int i=0; i<%d; ++i) %s[i]=0;\n", lsymp->n_elms, lsymp->name);
		fprintf(fptr, "int start_col=");
		start_col->print_expr(fptr);
		fprintf(fptr, ",end_col=");
		end_col->print_expr(fptr);
		fprintf(fptr, ",width=%d;\n", width);
		fprintf(fptr, "if( start_col > end_col){\n");
		fprintf(fptr, "\tprintf(\"start_col evaluated > end_col -> runtime error\");\n");
		fprintf(fptr, "}\n");
		fprintf(fptr, "if( (end_col-start_col +1) %% width!=0 ){\n");
		fprintf(fptr, "\t\tprintf(\"expr value:%%d\", end_col-start_col +1 %% width );");
		fprintf(fptr, "\tprintf(\"please check your start_col=%%d ,  end_col=%%d, width=%%d for fld statement-> runtime error\\n\", start_col, end_col, width);\n");
		fprintf(fptr, "}\n");
		
		fprintf(fptr, "for (int i=start_col; i<= end_col+1-width; i+=width){\n");
		int lhs_arr_sz;
		if(lsymp->type==INT8_ARR_TYPE){
			lhs_arr_sz=sizeof(INT8_TYPE);
		} else if (lsymp->type==INT16_ARR_TYPE){
			lhs_arr_sz=sizeof(INT16_TYPE);
		} else if (lsymp->type==INT32_ARR_TYPE){
			lhs_arr_sz=sizeof(INT32_TYPE);
		} else {
			fprintf(fptr, "prevent compilation: compiler bug filename:%s, line_number: %d\n", __FILE__, __LINE__);
		}
		fprintf(fptr, "\t\tchar buff[%d];\n", lhs_arr_sz);
		fprintf(fptr,"\t\tfor(int s=i,j=0;s<i+width;++s,++j){\n");
		fprintf(fptr,"\t\t\t\tbuff[j]=%s[s];\n", rsymp->name);
		fprintf(fptr,"\t\t}\n");
		fprintf(fptr,"\tvoid * v_ptr = buff;\n");
		if(lhs_arr_sz==sizeof(char)){
			fprintf(fptr,"\tchar *c_ptr = static_cast<char *>(v_ptr);\n");
			fprintf(fptr,"\tint tmp=*c_ptr;\n");
		} else if (lhs_arr_sz==sizeof(short int)){
			fprintf(fptr,"\tshort int  *si_ptr = static_cast<short int *>(v_ptr);\n");
			fprintf(fptr,"\tint tmp=*si_ptr;\n");
		} else if (lhs_arr_sz==sizeof( int)){
			fprintf(fptr,"\t\tint  *i_ptr = static_cast<int *>(v_ptr);\n");
			fprintf(fptr,"\t\tint tmp=*i_ptr;\n");
		}
		fprintf(fptr,"\t\tif(tmp>=1 && tmp <=%d){\n", lsymp->n_elms);
		fprintf(fptr,"\t\t\t++%s[tmp];\n", lsymp->name);
		fprintf(fptr,"\t\t} else {\n");
		fprintf(fptr,"\t\t\tprintf(\" runtime warning: code too big to fit in array\\n\");\n");
		fprintf(fptr,"\t\t}\n;");
		
		fprintf(fptr, "}} \n");
		if(next) next->print_stmt_lst(fptr);
	}
	~fld_stmt(){
	}
};
		 

struct blk_arr_assgn_stmt: public stmt{
	struct symtab_ent * lsymp;
	struct symtab_ent * rsymp;
	expr * low_indx, *high_indx;
	blk_arr_assgn_stmt(datatype dtype, int lline_number, symtab_ent* llsymp, symtab_ent* lrsymp,
			expr * lbd, expr* hbd): stmt(dtype, lline_number), lsymp(llsymp), rsymp(lrsymp),
						low_indx(lbd), high_indx(hbd){}
	void print_stmt_lst(FILE * & fptr){
		fflush(fptr);

		if(fptr){
			fprintf(fptr,"/* DATA CONVERSION */\n");
			fprintf(fptr,"{int tmp1=");
			low_indx->print_expr(fptr);
			fprintf(fptr,";\nint tmp2=");
			high_indx->print_expr(fptr);
			fprintf(fptr,";\n");
			if(lsymp->get_type()==FLOAT_TYPE) {
				fprintf(fptr,"if(tmp2-tmp1==sizeof(float)-1){\n");
				fprintf(fptr,"\tchar buff[sizeof(float)];int i,j;\n");
				fprintf(fptr,"\tfor(i=tmp1,j=0;i<=tmp2;++i,++j){\n");
				fprintf(fptr,"\t\tbuff[j]=%s[i];\n", rsymp->name);
				fprintf(fptr,"\t}\n");
				fprintf(fptr,"\tvoid * v_ptr = buff;\n");
				fprintf(fptr,"\tfloat *f_ptr = static_cast<float *>(v_ptr);\n");
				fprintf(fptr,"\t %s=*f_ptr;\n", lsymp->name);
				fprintf(fptr,"}else { cerr << \"runtime error: line_no : expr out of bounds\" << %d;}\n}\n", line_number );
			} else if (lsymp->get_type()==INT32_TYPE){
				fprintf(fptr,"if(tmp2-tmp1==sizeof(int)-1){\n");
				fprintf(fptr,"\tchar buff[sizeof(int)];int i,j;\n");
				fprintf(fptr,"\tfor(i=tmp1,j=0;i<=tmp2;++i,++j){\n");
				fprintf(fptr,"\t\tbuff[j]=%s[i];\n", rsymp->name);
				fprintf(fptr,"\t}\n");
				fprintf(fptr,"\tvoid * v_ptr = buff;\n");
				fprintf(fptr,"\tint *i_ptr = static_cast<int *>(v_ptr);\n");
				fprintf(fptr,"\t %s=*i_ptr;\n", lsymp->name);
				fprintf(fptr,"}else { \n\tcerr << \"runtime error: line_no : expr out of bounds\" << %d;}\n}\n", line_number );
			}
		}
		if(next) next->print_stmt_lst(fptr);
	}
	~blk_arr_assgn_stmt(){
		//cout << "deleting blk_arr_assgn_stmt" << endl;
		//if(next) delete next;
		delete lsymp; 
		delete rsymp;
		delete low_indx;
		delete	high_indx;
	}
	
	private:
	blk_arr_assgn_stmt& operator=(const blk_arr_assgn_stmt&);	
	blk_arr_assgn_stmt(const blk_arr_assgn_stmt&);	
	};

struct break_stmt: public stmt{
	break_stmt(datatype dtype, int lline_number, int in_a_loop): stmt(dtype, lline_number){
		if(in_a_loop<=0){
			print_err(compiler_sem_err, "break statement outside a loop: ",
				line_no, __LINE__, __FILE__);
		}
	}
	void print_stmt_lst(FILE * & fptr){
		fflush(fptr);
		if(fptr){
			fprintf(fptr, "break;");
			if(next) next->print_stmt_lst(fptr);
		}
	}
	~break_stmt(){
		cout << "deleting break_stmt" << endl;
		if (next) delete next;
	}
	private:
	break_stmt& operator=(const break_stmt&);	
	break_stmt(const break_stmt&);	
};
struct continue_stmt: public stmt{
	continue_stmt(datatype dtype, int lline_number, int in_a_loop): stmt(dtype, lline_number){
		if (!in_a_loop){
			print_err(compiler_sem_err, "continue statement outside a loop: line_no: ",
				line_no, __LINE__, __FILE__);
		}
	}
	void print_stmt_lst(FILE * & fptr){
		fflush(fptr);

		if(fptr){
			fprintf(fptr, "continue;");
			if(next) next->print_stmt_lst(fptr);
		}
	}
	~continue_stmt(){
		//cout << "deleting continue_stmt" << endl;
		if (next) delete next;
	}
	private:
	continue_stmt& operator=(const continue_stmt&);	
	continue_stmt(const continue_stmt&);	
};

struct func_decl_stmt: public stmt{
	struct func_info * f_ptr;

	func_decl_stmt( datatype dtype, int lline_number, char * & name,  struct var_list* & v_list, datatype return_type);
	void print_stmt_lst(FILE * & fptr);
	~func_decl_stmt();
	private:
	func_decl_stmt& operator=(const func_decl_stmt&);	
	func_decl_stmt(const func_decl_stmt&);	
};

struct decl_stmt: public stmt{
	struct symtab_ent* symp;
	decl_stmt( datatype dtype, int lline_number):stmt(dtype, lline_number),symp(0)
	{}
	void print_stmt_lst(FILE * & fptr){
		fflush(fptr);
		if(fptr){
			if(type >= INT8_TYPE && type <=DOUBLE_TYPE){
				fprintf(fptr,"%s %s", noun_list[type].sym, symp->name);
			} else if (type >=INT8_ARR_TYPE && type <=DOUBLE_ARR_TYPE){
				datatype tdt=datatype(INT8_TYPE + type-INT8_ARR_TYPE);
				fprintf(fptr,"%s %s [ %d ]", noun_list[tdt].sym, symp->name, symp->n_elms);
			} else if (type >=INT8_REF_TYPE&& type <=DOUBLE_REF_TYPE){
				datatype tdt=datatype(INT8_TYPE + type-INT8_REF_TYPE);
				fprintf(fptr,"%s & %s", noun_list[tdt].sym, symp->name);
			}
			if( symp->e){
				fprintf(fptr,"=");
				symp->e->print_expr(fptr);
			}
			fprintf(fptr, ";\n");
			if(next) next->print_stmt_lst(fptr);
		}
	}
	~decl_stmt();
	private:
	decl_stmt& operator=(const decl_stmt&);	
	decl_stmt(const decl_stmt&);	
};


struct func_stmt: public stmt{
	struct func_info * f_ptr;
	struct stmt *func_body;
	datatype return_type;

	func_stmt ( datatype dtype, int lline_number, struct scope * &sc,
		struct var_list * & v_list,
		struct stmt* & lfunc_body,
		string func_name,
		datatype lreturn_type
		) ;
	void print_stmt_lst(FILE * & fptr);
	~func_stmt();
	private:
	func_stmt& operator=(const func_stmt&);	
	func_stmt(const func_stmt&);	
};


struct list_stmt: public stmt{
	struct symtab_ent * se;
	string list_text;
	expr * arr_start;
	expr * arr_end;
	list_stmt( datatype dtype, string name,
		string llist_text=string(""),
		expr*  l_arr_start=0, 
		expr* l_arr_end=0
		);
	void print_stmt_lst(FILE * & fptr);

	~list_stmt();

	private:
	list_stmt& operator=(const list_stmt&);	
	list_stmt(const list_stmt&);	
};
#include <map>
using std:: map;
map<string, symtab_ent*>::iterator find_in_symtab(string id);



/*
 * The func_info constructor adds the names of the function parameters into its scope.
 * When a compound statement is parsed : it checks for the flag_cmpd_stmt_is_a_func_body and
 * loads that into the active scope if set.
 * Note that flag_cmpd_stmt_is_a_func_body is initialized to -1 as the 1st function 
 * will be in index 0 of func_info_table vector.
 * Also lookup_func searches the func_info_table for the function name and returns -1 on failure
 * this is naturally compatible with the initial value of flag_cmpd_stmt_is_a_func_body
 * if the flag is not set -> we need to allocate a new scope - else we will crash
 */
#include "scope.h"
struct func_info;
//#include "stmt.h"
struct stmt;
struct func_info{
	string fname;
	struct var_list * param_list;
	datatype return_type;
	struct stmt * func_body;
	struct scope * func_scope;
	func_info(string name, struct var_list* elist, datatype myreturn_type); 
	void print(FILE * fptr);
	~func_info();
private:
	func_info& operator=(const func_info&);
	func_info(const func_info&);
};


#endif /* _xtcc_stmt_h */
