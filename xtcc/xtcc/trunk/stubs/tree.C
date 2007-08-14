#include "tree.h"
#include <iostream>
extern int line_no, no_errors;
using namespace std;


struct expr * new_expr(){	
	struct expr * e = ((struct expr * ) malloc (sizeof(struct expr)));
	e->l_op = NULL;
	e->r_op = NULL;
	e->symp = NULL;
	e->prev=e->next=NULL;
	e->text=NULL;
	return e;
}

struct stmt * new_stmt(){	
	struct stmt * s_ptr = ((struct stmt * ) malloc (sizeof(struct stmt)));
	if(s_ptr){
		s_ptr->type=uninit;
		s_ptr->line_number = -1;
		s_ptr->expr = NULL;
		s_ptr->expr2 = NULL;
		s_ptr->next = NULL;
		s_ptr->prev = NULL;
		s_ptr->c_stmt = NULL;
		s_ptr->if_stmt=NULL;
		s_ptr->symp=NULL;
		s_ptr->lsymp=NULL;
		s_ptr->rsymp=NULL;
		s_ptr->f_ptr=NULL;
		s_ptr->sc=NULL;
		s_ptr->c_stmt =NULL;
	}
	return s_ptr;
}


struct if_stmt * new_if_stmt(){	
	struct if_stmt * if_st =  ((struct if_stmt * ) malloc (sizeof(struct if_stmt)));
	if (if_st ){
		if_st->condition = NULL;
		if_st->if_body = NULL;
		if_st->else_body = NULL;
	}
	return if_st;		
}

datatype lcm_type(datatype d1, datatype d2){

	switch(d1){
		case int_type:
			switch(d2){
				case int_type:
					return int_type;
				case char_type:
					return int_type;
				case float_type:
					return float_type;
				default:
					cerr << "Type Error: lineno: " << line_no << "\n";
					++no_errors;
					return error_type;
			}
		case char_type:
			switch(d2){
				case int_type:
					return int_type;
				case char_type:
					return char_type;
				case float_type:
					return float_type;
				default:
					cerr << "Type Error: lineno: " << line_no << "\n";
					++no_errors;
					return error_type;
			}
		case float_type:
			switch(d2){
				case char_type:
				case int_type:
				case float_type:
					return float_type;
				default:	
					cerr << "Type Error: lineno: " << line_no << "\n";
					++no_errors;
					return error_type;
			}
		case int_arr_type:
		case char_arr_type:
		case float_arr_type:
		default:
			cerr << "Type Error: lineno: " << line_no << "\n";
			++no_errors;
			return error_type;
	}

}

datatype arr_deref_type(datatype d1){
	if(d1==int_arr_type) return int_type;
	if(d1==char_arr_type) return char_type;
	cerr << "Type Error: lineno: " << line_no << "\n";
	++no_errors;
	return error_type;
}

void stmt::print_stmt_lst(FILE * &edit_out){ 
	/* I may have to parametrize this later */
	//cout << "ENTER: print_stmt_lst : st"  << st << endl;
	//static FILE * edit_out=NULL;
	//struct stmt* st_ptr=st;
	//printf("Entered func: print_stmt_lst: st: %d\n", st);

	if(edit_out==NULL){
		//edit_out=fopen("edit_out.c", "w+b");
		if(edit_out==NULL){
			printf("could not open edit_out.c for writing\n");
			exit(1);
		}
	//	fprintf(edit_out, "#include <cstdio>\n#include <iostream>\nusing namespace std;\n" );
	}

#if DEBUG
	//fprintf(edit_out,"/* print_stmt_lst: printing type '%c'*/\n", st->type);
#endif /* DEBUG */
	/* New in version 0.2
	   */
	//while( st_ptr){
		switch(type){
		case cmpd_stmt:
			fprintf(edit_out,"{\n");
#if DEBUG
			fprintf(edit_out,"/*printing compound statement*/\n");
#endif /* DEBUG */
			c_stmt->print_stmt_lst(edit_out);
			fprintf(edit_out,"}\n");
			break;
		case expr_stmt:
#if DEBUG
			fprintf(edit_out,"/*printing expr statement*/\n");
#endif /* DEBUG */
			print_expr(edit_out, expr);
			fprintf(edit_out,";\n");
			break;
		case assgn_stmt:
#if DEBUG
			fprintf(edit_out,"/*assignment stmt */\n");
#endif /* DEBUG */
			if(symp) {
				fprintf(edit_out,"%s=", symp->name);
				print_expr(edit_out, expr);
				print_expr(edit_out, expr2);
				fprintf(edit_out,";\n");
			} else {
				// come back here to code
				fprintf(edit_out,"/* DATA CONVERSION */\n");
				fprintf(edit_out,"{int tmp1=");
				print_expr(edit_out, expr);
				fprintf(edit_out,";\nint tmp2=");
				print_expr(edit_out, expr2);
				fprintf(edit_out,";\n");
				if(lsymp->get_type()==float_type) {
					fprintf(edit_out,"if(tmp2-tmp1==sizeof(float)-1){\n");
					fprintf(edit_out,"\tchar buff[sizeof(float)];int i,j;\n");
					fprintf(edit_out,"\tfor(i=tmp1,j=0;i<=tmp2;++i,++j){\n");
					fprintf(edit_out,"\t\tbuff[j]=%s[i];\n", rsymp->name);
					fprintf(edit_out,"\t}\n");
					fprintf(edit_out,"\tvoid * v_ptr = buff;\n");
					fprintf(edit_out,"\tfloat *f_ptr = static_cast<float *>(v_ptr);\n");
					fprintf(edit_out,"\t %s=*f_ptr;\n", lsymp->name);
					fprintf(edit_out,"}else { cerr << \"runtime error: line_no : expr out of bounds\" << %d;}\n}\n", line_no );
				} else if (lsymp->get_type()==int_type){
					fprintf(edit_out,"if(tmp2-tmp1==sizeof(int)-1){\n");
					fprintf(edit_out,"\tchar buff[sizeof(int)];int i,j;\n");
					fprintf(edit_out,"\tfor(i=tmp1,j=0;i<=tmp2;++i,++j){\n");
					fprintf(edit_out,"\t\tbuff[j]=%s[i];\n", rsymp->name);
					fprintf(edit_out,"\t}\n");
					fprintf(edit_out,"\tvoid * v_ptr = buff;\n");
					fprintf(edit_out,"\tint *i_ptr = static_cast<int *>(v_ptr);\n");
					fprintf(edit_out,"\t %s=*i_ptr;\n", lsymp->name);
					fprintf(edit_out,"}else { \n\tcerr << \"runtime error: line_no : expr out of bounds\" << %d;}\n}\n", line_no );
				}
			}

			break;
		case ife_stmt:	{
			fprintf(edit_out, " /* printing ife_stmt: if_stmt %d */\n", if_stmt );
			fflush(edit_out);
			fprintf(edit_out,  "if (");
			print_expr(edit_out, if_stmt->condition);
			fprintf(edit_out,  ")");
			fflush(edit_out);
			if_stmt->if_body->print_stmt_lst(edit_out);
			fflush(edit_out);
			if(if_stmt->else_body){
				fprintf(edit_out,  " else ");
				if_stmt->else_body->print_stmt_lst(edit_out);
			}
		}
		break;
		//case decl_stmt: open_curly
			//fprintf(edit_out,"int %s;\n", symp->name);
	//		switch(type) 
		case char_type: 
			fprintf(edit_out,"char %s;\n", symp->name);
			break;
		case int_type:	
			fprintf(edit_out,"int %s;\n", symp->name);
			break;
		case float_type: 
			fprintf(edit_out,"float %s;\n", symp->name);
			break;
		case char_arr_type:
			if(!symp->text){
				fprintf(edit_out,"char %s [ %d ];\n", symp->name, symp->n_elms);
			} else {
				fprintf(edit_out,"char %s [ %d ]=%s;\n", symp->name, symp->n_elms, symp->text);
			}
			break;
		case int_arr_type:
			fprintf(edit_out,"int %s [ %d ];\n", symp->name, symp->n_elms);
			break;
		case float_arr_type:
			fprintf(edit_out,"float %s [ %d ];\n", symp->name, symp->n_elms);
			break;
					/*
				default:
					fprintf(edit_out, "unhandled decl type: %d\n", type);
					++no_errors;
					*/
	//		close_curly

#if DEBUG
#endif /* DEBUG */
		case func_type:
			f_ptr->print(edit_out);
		break;

		case func_defn:
			//f_ptr->print(edit_out);
			switch(f_ptr->return_type){
			case int_type:	
				fprintf(edit_out,"int ");
			break;	
			case float_type:	
				fprintf(edit_out,"float ");
			break;	
			case void_type:	
				fprintf(edit_out,"void ");
			break;	
			default:
				fprintf(edit_out, "Unxpected type for function\n");
			}
			fprintf(edit_out, "%s\n", f_ptr->fname.c_str());
			struct var_list* v_ptr=f_ptr->param_list;
			fprintf(edit_out, "(");
			v_ptr->print(edit_out);
#if 0
			while (v_ptr->next) v_ptr=v_ptr->next;
			while(v_ptr){
				v_ptr->print(edit_out);
				if(v_ptr->prev)
					fprintf(edit_out, ",");
				else
					fprintf(edit_out, ")");

				v_ptr=v_ptr->prev;
			}
#endif /* 0 */
			fprintf(edit_out, ")");
			f_ptr->func_body->print_stmt_lst(edit_out);
		break;	
		case for_stmt:
			fprintf(edit_out,  "for (");
			print_expr(edit_out, expr);
			fprintf(edit_out,  ";");
			print_expr(edit_out, expr2);
			fprintf(edit_out,  ";");
			print_expr(edit_out, expr3);
			fprintf(edit_out, ")");
			c_stmt->print_stmt_lst(edit_out);
		break;	
		case lista_basic_type_stmt:{
			static int counter_number=0;			   
			FILE * global_vars=fopen("global.C", "a+b");
			FILE * print_list_counts=fopen("print_list_counts.C", "a+b");
			struct symtab_ent* se = list_stmt->se;
			if(!(global_vars&&print_list_counts)){
				cerr << "Unable to open global.C or print_list_counts.C for append... exiting" << endl;
				exit(1);
			}
			if(list_stmt->se){
				datatype dt=se->get_type();
				switch(dt){
				case int_type:{
					fprintf(global_vars, "map<int,int> list%d;\n", counter_number);
					fprintf(edit_out, "list%d [%s]++;\n", counter_number, se->name);
					fprintf(print_list_counts, "print_list_summ(list%d );\n", counter_number);
					} 
				break;		      
				case char_type:{
					fprintf(global_vars, "map<char,int> list%d;\n", counter_number);
					fprintf(edit_out, "list%d [%s]++;\n", counter_number, se->name);
					fprintf(print_list_counts, "print_list_summ(list%d );\n", counter_number);
					}
				break;		      
				case float_type:{
					fprintf(global_vars, "map<float,int> list%d;\n", counter_number);
					fprintf(edit_out, "list%d [%s]++;\n", counter_number, se->name);
					fprintf(print_list_counts, "print_list_summ(list%d );\n", counter_number);
					}
				break;		      
				default:
					++no_errors;
				}
				++counter_number;
			}
			fclose(global_vars);
			fclose(print_list_counts);
		}
		break;
		case lista_basic_arrtype_stmt_1index:{
			static int counter_number=0;			   
			FILE * global_vars=fopen("global.C", "a+b");
			FILE * print_list_counts=fopen("print_list_counts.C", "a+b");
			struct symtab_ent* se = list_stmt->se;
			if(!global_vars){
				cerr << "Unable to open global.C for append" << endl;
			}
			if(list_stmt->se){
				datatype dt=se->get_type();
				switch(dt){
				case int_arr_type:{
					fprintf(global_vars, "map<int,int> list1_%d;\n", counter_number);
					fprintf(edit_out, "list1_%d [%s[%d]]++;\n", counter_number, se->name,
							list_stmt->arr_start);
					fprintf(print_list_counts, "print_list_summ(list1_%d );\n", counter_number);
					} 
				break;		      
				case char_arr_type:{
					fprintf(global_vars, "map<char,int> list1_%d;\n", counter_number);
					fprintf(edit_out, "list1_%d [%s[%d]]++;\n", counter_number, se->name,
							list_stmt->arr_start);
					fprintf(print_list_counts, "print_list_summ(list1_%d );\n", counter_number);
					}
				break;		      
				case float_arr_type:{
					fprintf(global_vars, "map<float,int> list1_%d;\n", counter_number);
					fprintf(edit_out, "list1_%d [%s[%d]]++;\n", counter_number, se->name,
							list_stmt->arr_start);
					fprintf(print_list_counts, "print_list_summ(list1_%d );\n", counter_number);
					}
				break;		      
				default:
					++no_errors;
				}
				++counter_number;
			}
			fclose(global_vars);
			fclose(print_list_counts);
		}
		break;
		case lista_basic_arrtype_stmt_2index:{
			static int counter_number=0;			   
			FILE * global_vars=fopen("global.C", "a+b");
			FILE * print_list_counts=fopen("print_list_counts.C", "a+b");
			struct symtab_ent* se = list_stmt->se;
			if(!global_vars){
				cerr << "Unable to open global.C for append" << endl;
			}
			if(list_stmt->se){
				datatype dt=se->get_type();
				switch(dt){
				case char_arr_type:{
					fprintf(global_vars, "map<char,int> list2_%d;\n", counter_number);
					fprintf(edit_out, "list2_%d [%s[%d]]++;\n", counter_number, se->name,
							list_stmt->arr_start);
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
		break;

		case err_stmt:
			fprintf(edit_out,"error statement \n");
		break;	
			
		default:
			fprintf(edit_out,"/*Unhandled statement type: Report bug to NxD_in@yahoo.com*/\n");
		}
		//if(st_ptr)
		//	st_ptr=prev;
		if(prev) prev-> print_stmt_lst(edit_out);
#if DEBUG
		fprintf(edit_out,"/*stmt printed*/\n");
#endif /* DEBUG */
	//}
}
