/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/stmt.C
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#include "expr.h"
#include "debug_mem.h"
#include "stmt.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include "named_range.h"

extern vector<mem_addr_tab> mem_addr;
extern int if_line_no;

extern ofstream debug_log_file;
using std::cout;
using std::endl;
void read_data(const char * prompt);
#if 0
stmt::~stmt(){ 
	if (next  ) {
		delete next; next=0;
	} 
	debug_log_file << "stmt::~stmt() base destructor" << endl;
}
#endif /* 0 */
void expr_stmt::generate_code(ostringstream & quest_defns, ostringstream& program_code){
	expr->print_expr(quest_defns, program_code);
	program_code << ";" << endl;
	if(next){
		next->generate_code(quest_defns, program_code);
	}
}


expr_stmt::~expr_stmt() {
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "expr_stmt::~expr_stmt: setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting expr_stmt" << endl;
	//if(next ) delete next;
	if (expr) delete expr;
}


//decl_stmt::decl_stmt( datatype dtype, int lline_number):stmt(dtype, lline_number), symp(0) {}



void decl_stmt::generate_code(ostringstream & quest_defns, ostringstream& program_code){
	//expr->print_expr(quest_defns, program_code);
	program_code << " // decl_stmt::generate_code " << endl;
	ostringstream code_expr1, code_bef_expr1;
	if( symp->e){
		symp->e->print_expr(code_bef_expr1, code_expr1);
		//fprintf(fptr,"%s", code_bef_expr1.str().c_str());
		program_code << code_bef_expr1.str().c_str();
	}
	if(type >= INT8_TYPE && type <=DOUBLE_TYPE){
		//fprintf(fptr,"%s %s", noun_list[type].sym, symp->name);
		program_code << noun_list[type].sym << " " << symp->name;
	} else if (type >=INT8_ARR_TYPE && type <=DOUBLE_ARR_TYPE){
		datatype tdt=datatype(INT8_TYPE + type-INT8_ARR_TYPE);
		//fprintf(fptr,"%s %s [ %d ]", noun_list[tdt].sym, symp->name, symp->n_elms);
		program_code << noun_list[tdt].sym << symp->name << "[" << symp->n_elms << "]";
	} else if (type >=INT8_REF_TYPE&& type <=DOUBLE_REF_TYPE){
		datatype tdt=datatype(INT8_TYPE + type-INT8_REF_TYPE);
		//fprintf(fptr,"%s & %s", noun_list[tdt].sym, symp->name);
		program_code << noun_list[tdt].sym << " & " << symp->name ;
	}
	if( symp->e){
		//fprintf(fptr,"=%s", code_expr1.str().c_str());
		program_code << "=" << code_expr1.str().c_str();

	}
	//fprintf(fptr, ";\n");
	program_code << ";" << endl;

	if(next){
		next->generate_code(quest_defns, program_code);
	}
}



decl_stmt::~decl_stmt() {
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "decl_stmt::~decl_stmt: setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting decl_stmt" << endl;
	//if(symp) { delete symp; symp=0; }

}

if_stmt::if_stmt( datatype dtype, int lline_number, 
	struct  expr * lcondition, struct  stmt * lif_body, struct stmt * lelse_body): 
	stmt(dtype, lline_number),
	condition(lcondition), if_body(lif_body), else_body(lelse_body)
{
	if(lcondition->type==VOID_TYPE || lcondition->type==ERROR_TYPE){
		print_err(compiler_sem_err, 
			"If condition expression has Void or Error Type", 
			if_line_no, __LINE__, __FILE__);
	} else {
	}
}


void if_stmt::generate_code(ostringstream & quest_defns, ostringstream& program_code){
	ostringstream code_bef_expr, code_expr;
	code_expr << "if (";
	condition->print_expr(code_bef_expr, code_expr);
	code_expr << ")";
	//fprintf(fptr, " %s ", code_bef_expr.str().c_str());
	//fprintf(fptr, " %s ", code_expr.str().c_str());
	program_code << code_bef_expr.str();
	program_code << code_expr.str();
	//fflush(fptr);
	//if_body->print_stmt_lst(fptr);
	if_body->generate_code(quest_defns, program_code);
	//fflush(fptr);
	if(else_body){
		//fprintf(fptr,  " else ");
		program_code << " else " << endl;
		//else_body->print_stmt_lst(fptr);
		else_body->generate_code(quest_defns, program_code);
	}
	if(next) 
		next->generate_code(quest_defns, program_code);
}


if_stmt:: ~if_stmt(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file 
				<< "if_stmt::~if_stmt setting mem_addr:" 
				<< this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting if_stmt" << endl;
	//if (next) delete next;
	delete condition;
	delete if_body;
	if (else_body) delete else_body;
}

cmpd_stmt::cmpd_stmt(datatype dtype, int lline_number, int l_flag_cmpd_stmt_is_a_func_body): 
	stmt(dtype, lline_number), 
	cmpd_bdy(0), sc(0), 
	flag_cmpd_stmt_is_a_func_body(l_flag_cmpd_stmt_is_a_func_body) 
{}


void cmpd_stmt::generate_code(ostringstream & quest_defns, 
	ostringstream& program_code){
	program_code << "{" << endl;
	if (cmpd_bdy) 
		cmpd_bdy->generate_code(quest_defns, program_code);
	program_code << "}" << endl;
	if(next) 
		next->generate_code(quest_defns, program_code);
}


cmpd_stmt::~cmpd_stmt() {
	debug_log_file << "deleting cmpd_stmt" << endl;
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "basic_count_ax_stmt::~basic_count_ax_stmt setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	//if(next) delete next;
	if(sc&&flag_cmpd_stmt_is_a_func_body<0) {
		delete sc;
		sc=0;
	}
	if(cmpd_bdy /*&& flag_cmpd_stmt_is_a_func_body<0*/){
		delete cmpd_bdy;
		cmpd_bdy=0;
	}
}

question* find_in_question_list(string name);
extern vector <question*> question_list;
question* find_in_question_list(string name){
	for(int i=0; i<question_list.size(); ++i){
		if(question_list[i]->name==name){
			return question_list[i];
		}
	}
	return 0;
}


for_stmt::for_stmt( datatype dtype, int lline_number, 
	expr * l_init, expr * l_test, expr* l_incr, stmt * l_for_body): 
	stmt(dtype, lline_number),
	init(l_init), test(l_test), incr(l_incr), for_body(l_for_body)
{
	if(init->type==VOID_TYPE||test->type==VOID_TYPE||incr->type==VOID_TYPE ){
		print_err(compiler_sem_err, 
				"For condition expression has Void or Error Type", 
				line_no, __LINE__, __FILE__);
		type=ERROR_TYPE;
	} 
}

void for_stmt::generate_code(ostringstream& quest_defns, ostringstream& program_code){
	ostringstream code_bef_expr, code_expr;
	code_expr << "for (" ;
	init->print_expr(code_bef_expr, code_expr);
	code_expr <<   ";";
	test->print_expr(code_bef_expr, code_expr);
	code_expr << ";";
	incr->print_expr(code_bef_expr, code_expr);
	code_expr <<  ")";

	program_code << code_bef_expr.str();
	program_code << code_expr.str();
	for_body->generate_code(quest_defns, program_code);
	if(next) 
		next->generate_code(quest_defns, program_code);
}


for_stmt:: ~for_stmt(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file 
				<< "for_stmt::~for_stmt setting mem_addr:" 
				<< this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting for_stmt" << endl;
	//if (next) delete next;
	delete init; init=0;
	delete test; test=0;
	delete incr; incr=0;
	delete for_body; for_body=0;
}
