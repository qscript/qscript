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
#include "scope.h"
#include "expr.h"

#include <cstdio>
#include <cstdlib>

	void print_expr(FILE* edit_out, struct expr * e);
	int search_for_func(string& search_for);
	extern scope* active_scope;
	extern int no_errors;
	extern noun_list_type noun_list[];
	extern vector <func_info*> func_info_table;
	int check_func_decl_with_func_defn(struct var_list*& v_list, int & index, string func_name);
// Note : I may have to add file name we are compiling very soon
struct stmt{
	struct stmt * next;
	struct stmt * prev;
	datatype type;
	int line_number;
	virtual void print_stmt_lst(FILE * & fptr)=0;
	stmt(datatype dtype=ERROR_TYPE, int lline_number=0):next(0), prev(0), type(dtype), line_number(lline_number){}
	virtual ~stmt(){}
	private:
		stmt(const stmt&);
		stmt& operator=(const stmt&);
};

struct for_stmt: public stmt{
	struct expr * init, * test, *incr;
	struct stmt * for_body;
	for_stmt(datatype dtype, int lline_number, expr* l_init, expr* l_test, expr* l_incr, stmt * lfor_body):stmt(dtype, lline_number), init(l_init), test(l_test), incr(l_incr),  for_body(lfor_body){}
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
			if(prev) prev->print_stmt_lst(fptr);
		}
	}
	private:
	for_stmt& operator=(const for_stmt&);	
	for_stmt(const for_stmt&);	
};

// Refinement3
struct if_stmt : public stmt{
	struct expr * condition;
	struct stmt * if_body;
	struct stmt * else_body;
	if_stmt( datatype dtype, int lline_number, struct  expr * lcondition, struct  stmt * lif_body, struct stmt * lelse_body=NULL): stmt(dtype, lline_number),
		condition(lcondition), if_body(lif_body), else_body(lelse_body)
	{
	}
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
			if(prev) prev->print_stmt_lst(fptr);
		}
	}
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
			if(prev) prev->print_stmt_lst(fptr);
		}
	}
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
			if(prev) prev->print_stmt_lst(fptr);
		}
	}
	private:
	err_stmt& operator=(const err_stmt&);	
	err_stmt(const err_stmt&);	
};

struct cmpd_stmt: public stmt{
	struct stmt* cmpd_bdy;
	struct scope * sc;
	cmpd_stmt(datatype dtype, int lline_number, struct stmt* s=0): stmt(dtype, lline_number), cmpd_bdy(s), sc(0){}
	void print_stmt_lst(FILE * & fptr){
		fflush(fptr);

		if(fptr){
			fprintf(fptr,"{\n");
			if (cmpd_bdy) cmpd_bdy->print_stmt_lst(fptr);
			fprintf(fptr,"}\n");
			if(prev) prev->print_stmt_lst(fptr);
		}
	}
	private:
	cmpd_stmt& operator=(const cmpd_stmt&);	
	cmpd_stmt(const cmpd_stmt&);	
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
				} else if (lsymp->get_type()==INT32_TYPE
						|| lsymp->get_type()==U_INT32_TYPE){
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
			if(prev) prev->print_stmt_lst(fptr);
		}
	private:
	blk_arr_assgn_stmt& operator=(const blk_arr_assgn_stmt&);	
	blk_arr_assgn_stmt(const blk_arr_assgn_stmt&);	
	};

struct break_stmt: public stmt{
	break_stmt(datatype dtype, int lline_number): stmt(dtype, lline_number){}
	void print_stmt_lst(FILE * & fptr){
		fflush(fptr);
		if(fptr){
			fprintf(fptr, "break;");
			if(prev) prev->print_stmt_lst(fptr);
		}
	}
	private:
	break_stmt& operator=(const break_stmt&);	
	break_stmt(const break_stmt&);	
};
struct continue_stmt: public stmt{
	continue_stmt(datatype dtype, int lline_number): stmt(dtype, lline_number){}
	void print_stmt_lst(FILE * & fptr){
		fflush(fptr);

		if(fptr){
			fprintf(fptr, "continue;");
			if(prev) prev->print_stmt_lst(fptr);
		}
	}
	private:
	continue_stmt& operator=(const continue_stmt&);	
	continue_stmt(const continue_stmt&);	
};

struct func_decl_stmt: public stmt{
	struct func_info * f_ptr;

	func_decl_stmt( datatype dtype, int lline_number, char * & name,  struct var_list* & v_list, datatype return_type):
		stmt(dtype, lline_number), f_ptr(0)
	{
		//cout << "load_func_into_symbol_table : " << "name: " << name << endl;
		if ( active_scope->sym_tab.find(name) == active_scope->sym_tab.end() ){
			//cout << "got func_decl" << endl;
			datatype myreturn_type=return_type;
			struct func_info* fi=new func_info(name, v_list, myreturn_type);
			func_info_table.push_back(fi);
			type=FUNC_TYPE;
			struct symtab_ent* se=new struct symtab_ent;
			if(! se) {
				cerr << "memory allocation error: I will eventually crash :-(" << endl;
			}
			se->name = name;
			string s(name);
			active_scope->sym_tab[s] = se;
			se->type=FUNC_TYPE;
			f_ptr=fi;
		} else {
			cerr << "Symbol : " << name << " already present in symbol table" << endl;
			cout << "line_no: " << lline_number;
			++no_errors;
			type=ERROR_TYPE;
		}
	}
	void print_stmt_lst(FILE * & fptr){
		fflush(fptr);

		if(fptr){
			f_ptr->print(fptr);
			if(prev) prev->print_stmt_lst(fptr);
		}
	}
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
			if(type >= U_INT8_TYPE && type <=DOUBLE_TYPE){
				fprintf(fptr,"%s %s;\n", noun_list[type].sym, symp->name);
			} else if (type >=U_INT8_ARR_TYPE && type <=DOUBLE_ARR_TYPE){
				datatype tdt=datatype(U_INT8_TYPE + type-U_INT8_ARR_TYPE);
				fprintf(fptr,"%s %s [ %d ];\n", noun_list[tdt].sym, symp->name, symp->n_elms);
			} else if (type >=U_INT8_REF_TYPE&& type <=DOUBLE_REF_TYPE){
				datatype tdt=datatype(U_INT8_TYPE + type-U_INT8_REF_TYPE);
				fprintf(fptr,"%s & %s;\n", noun_list[tdt].sym, symp->name);
			}
			if(prev) prev->print_stmt_lst(fptr);
		}

	}
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
		) : stmt(dtype, lline_number), f_ptr(0), func_body(lfunc_body), return_type(lreturn_type){
		int index=search_for_func(func_name);
		if(index==-1){
			cerr << "function defn without decl: " << func_name << " lline_number: " << lline_number << endl;
			type=ERROR_TYPE;
			++no_errors;
		} else if(check_func_decl_with_func_defn(v_list, index, func_name)){
			if(return_type==func_info_table[index]->return_type){
				type=FUNC_DEFN;
				f_ptr=func_info_table[index];
			} else {
				cerr << "func defn, decl parameter return_types did not match: lline_number: " 
				<< lline_number
				<< endl;
				++no_errors;
				type=ERROR_TYPE;
			}
		} else {
			cerr << "func defn, decl parameter lists did not match: lline_number" 
				<< lline_number
				<< endl;
			++no_errors;
			type=ERROR_TYPE;
		}
	}
	void print_stmt_lst(FILE * & fptr){

		if(fptr){
			if(f_ptr->return_type >= VOID_TYPE && f_ptr->return_type<=DOUBLE_TYPE){
				fprintf(fptr,"%s ", noun_list[f_ptr->return_type].sym);
			} else {
				fprintf(fptr, "Unxpected return type for function: file: %s, line:%d\n",
						__FILE__, __LINE__ );
			}
			
			fprintf(fptr, "%s\n", f_ptr->fname.c_str());
			struct var_list* v_ptr=f_ptr->param_list;
			fprintf(fptr, "(");
			v_ptr->print(fptr);
			fprintf(fptr, ")");
			if(func_body) func_body->print_stmt_lst(fptr);
			if(prev) prev->print_stmt_lst(fptr);
		}
	}
	private:
	func_stmt& operator=(const func_stmt&);	
	func_stmt(const func_stmt&);	
};


struct list_stmt: public stmt{
	struct symtab_ent * se;
	int arr_start, arr_end;
	string list_text;
	list_stmt( datatype dtype,
			int lline_number,
			struct symtab_ent * lse, int l_arr_start=-1, int l_arr_end=-1, string llist_text=string("")
		 ): stmt(dtype, lline_number), 
		se(lse), arr_start(l_arr_start), arr_end(l_arr_end), list_text(llist_text)
	{
	}

	void print_stmt_lst(FILE * & fptr){
		fflush(fptr);

		if(fptr){
			switch(type){
			case LISTA_BASIC_TYPE_STMT:{
				static int counter_number=0;			   
				FILE * global_vars=fopen("xtcc_work/global.C", "a+b");
				FILE * print_list_counts=fopen("xtcc_work/print_list_counts.C", "a+b");
				if(!(global_vars&&print_list_counts)){
					cerr << "Unable to open global.C or print_list_counts.C for append... exiting" << endl;
					exit(1);
				}
				if(se){
					datatype dt=se->get_type();
					if(dt>=U_INT8_TYPE && dt<=DOUBLE_TYPE){
						fprintf(global_vars, "map<%s,int> list%d;\n", 
								noun_list[dt].sym, counter_number);
						fprintf(fptr, "list%d [%s]++;\n", counter_number, se->name);
						fprintf(print_list_counts, "print_list_summ(list%d );\n", counter_number);
					}

					++counter_number;
				}
				fclose(global_vars);
				fclose(print_list_counts);
			}
			break;
			case LISTA_BASIC_ARRTYPE_STMT_1INDEX:{
				static int counter_number=0;			   
				FILE * global_vars=fopen("xtcc_work/global.C", "a+b");
				FILE * print_list_counts=fopen("xtcc_work/print_list_counts.C", "a+b");
				if(!global_vars){
					cerr << "Unable to open global.C for append" << endl;
				}
				if(se){
					datatype dt=se->get_type();
					if(dt>=U_INT8_ARR_TYPE&& dt<=DOUBLE_ARR_TYPE){
						fprintf(global_vars, "map<%s,int> list%d;\n", 
								noun_list[dt].sym, counter_number);
						fprintf(fptr, "list1_%d [%s[%d]]++;\n", counter_number, se->name,
								arr_start);
						fprintf(print_list_counts, "print_list_summ(list%d );\n", counter_number);
					}
					++counter_number;
				}
				fclose(global_vars);
				fclose(print_list_counts);
			}
			break;
			case LISTA_BASIC_ARRTYPE_STMT_2INDEX:{
				static int counter_number=0;			   
				FILE * global_vars=fopen("xtcc_work/global.C", "a+b");
				FILE * print_list_counts=fopen("xtcc_work/print_list_counts.C", "a+b");
				if(!global_vars){
					cerr << "Unable to open global.C for append" << endl;
				}
				if(se){
					datatype dt=se->get_type();
					switch(dt){
					case U_INT8_ARR_TYPE:
					case INT8_ARR_TYPE:	
						{
						fprintf(global_vars, "map<%s,int> list2_%d;\n", 
								noun_list[dt].sym, counter_number);
						fprintf(fptr, "list2_%d [%s[%d]]++;\n", counter_number, se->name,
								arr_start);
						fprintf(print_list_counts, "print_list_summ(list2_%d );\n", counter_number);
						}
					break;		      
					default:
						++no_errors;
					}
					++counter_number;
				}
				fclose(print_list_counts);
				fclose(global_vars);
			}
			default:
				fprintf(fptr, "Unhandled lista statement: \n");	
			}
			if(prev) prev->print_stmt_lst(fptr);

		}
	}
	private:
	list_stmt& operator=(const list_stmt&);	
	list_stmt(const list_stmt&);	
};

#endif /* _xtcc_stmt_h */
