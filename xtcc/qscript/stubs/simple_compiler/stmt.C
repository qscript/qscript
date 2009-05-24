/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/stmt.C
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "expr.h"
#include "debug_mem.h"
#include "stmt.h"
#include "question.h"
#include "named_range.h"
#include "qscript_parser.h"


extern vector<mem_addr_tab> mem_addr;
extern int if_line_no;

//extern ofstream debug_log_file;
using qscript_parser::debug_log_file;
using std::cout;
using std::cerr;
using std::endl;
using std::stringstream;
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
	using qscript_parser::mem_addr;
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
	using qscript_parser::mem_addr;
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
			qscript_parser::if_line_no, __LINE__, __FILE__);
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
	using qscript_parser::mem_addr;
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

// There is a reason the scope pointer in the 
// compound statement is initialised to 0
//  - if the cmpd_stmt is part of a function body
// the the variables 

cmpd_stmt::cmpd_stmt(datatype dtype, int lline_number, 
	int l_flag_cmpd_stmt_is_a_func_body,
	int l_flag_cmpd_stmt_is_a_for_body): 
	stmt(dtype, lline_number), 
	cmpd_bdy(0), sc(0), 
	flag_cmpd_stmt_is_a_func_body(l_flag_cmpd_stmt_is_a_func_body),
	flag_cmpd_stmt_is_a_for_body(l_flag_cmpd_stmt_is_a_for_body),
	counter_contains_questions(0)
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
	using qscript_parser::mem_addr;
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

//extern vector <question*> qscript_parser::question_list;
using qscript_parser::question_list;
question* find_in_question_list(string name){
	//using qscript_parser::question_list;

	for(int i=0; i<question_list.size(); ++i){
		if(question_list[i]->name==name){
			return question_list[i];
		}
	}
	return 0;
}


for_stmt::for_stmt( datatype dtype, int lline_number, 
	expr * l_init, expr * l_test, expr* l_incr, cmpd_stmt * l_for_body): 
	stmt(dtype, lline_number),
	init(l_init), test(l_test), incr(l_incr), for_body(l_for_body)
{
	if(init->type==VOID_TYPE||test->type==VOID_TYPE||incr->type==VOID_TYPE ){
		print_err(compiler_sem_err, 
				"For condition expression has Void or Error Type", 
				qscript_parser::line_no, __LINE__, __FILE__);
		type=ERROR_TYPE;
	}
	// NxD - I have to correct here
	// test should be a binary expression and 
	// test->e_type should be <, >, <=, >=, == or !=

	if(for_body->counter_contains_questions){
		/*&& ! (test->is_integral_expr() && test->is_const()))*/
		bin_expr * test_expr = dynamic_cast<bin_expr*>(test);
		if(test_expr==0){
			print_err(compiler_sem_err, 
				" test expr should be a binary expression ",
				qscript_parser::line_no, __LINE__, __FILE__);
		} else if(!(test_expr->r_op->is_integral_expr() 
				&& test_expr->r_op->is_const())) {
			print_err(compiler_sem_err, 
				"If the for loop contains questions, then the counter of the for loop should be an integer and a constant expression"
			, qscript_parser::line_no, __LINE__, __FILE__);
		}
		//cerr << "is integral expr: " << test->is_integral_expr() << endl;
		//cerr << "is const expr: " << test->is_const() << endl;
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
	using qscript_parser::mem_addr;
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


var_list::var_list(datatype type, char * name): 
	var_type(type), var_name(name), arr_len(-1), prev(0), next(0){
	if (!( (type>=INT8_TYPE&& type<=DOUBLE_TYPE) ||
		(type>=INT8_REF_TYPE&& type<=DOUBLE_REF_TYPE))){
		stringstream s;
		s << "SEMANTIC error: only INT8_TYPE ... DOUBLE_TYPE is allowed in decl: "  << var_name<< endl;
		print_err(compiler_sem_err, s.str() , qscript_parser::line_no, __LINE__, __FILE__);
		cerr << "NEED TO LINK  BACK TO ERROR: FIX ME" << endl;
	}
	//cout << "constructing var_list: " << var_name << endl;
}
var_list::~var_list(){
	debug_log_file << "deleting ~var_list: var_name:" << var_name << endl;
	if (next) { delete next; next=0; }
	debug_log_file << "end deleting ~var_list " << endl;
}


void var_list::print(FILE * edit_out){
	struct var_list * vl_ptr=this;
	while(vl_ptr){
		if(vl_ptr->var_type>=INT8_TYPE && vl_ptr->var_type<=DOUBLE_TYPE){
			fprintf(edit_out, "%s %s", noun_list[vl_ptr->var_type].sym,vl_ptr->var_name.c_str());
		} else if (vl_ptr->var_type>=INT8_ARR_TYPE&&vl_ptr->var_type<=DOUBLE_ARR_TYPE){
			datatype tdt=datatype(INT8_TYPE + vl_ptr->var_type-INT8_ARR_TYPE);
			fprintf(edit_out, "%s %s[%d]/* vartype: %d */", noun_list[tdt].sym, vl_ptr->var_name.c_str(), arr_len, vl_ptr->var_type);
		} else if (vl_ptr->var_type>=INT8_REF_TYPE&&vl_ptr->var_type<=DOUBLE_REF_TYPE){
			datatype tdt=datatype(INT8_TYPE + vl_ptr->var_type-INT8_REF_TYPE);
			fprintf(edit_out, "%s & %s", noun_list[tdt].sym, vl_ptr->var_name.c_str());
		} else {
			fprintf(edit_out, "INTERNAL ERROR:Unknown data type: file: %s, line: %d\n", __FILE__, __LINE__);
		}
		vl_ptr=vl_ptr->next;
		if(vl_ptr) {
			fprintf(edit_out, ",");
		}
	}
}

var_list::var_list(datatype type, char * name, int len): var_type(type), var_name(name), arr_len(len), prev(0), next(0){
	if(!is_of_arr_type(type)){
		cerr << "SEMANTIC error: only INT8_ARR_TYPE ... DOUBLE_ARR_TYPE array Types are allowed in decl: " << var_name << endl;
		cerr << "NEED TO LINK  BACK TO ERROR: FIX ME" << endl;
	}
	cout << "constructing var_list: " << var_name << endl;
}


stub_manip::stub_manip( datatype dtype, int lline_number, 
	string l_named_stub, string l_question_name
	): 
	stmt(dtype, lline_number), 
	named_stub(l_named_stub), question_name(l_question_name)
{

}

void stub_manip::generate_code(ostringstream& quest_defns
		, ostringstream& program_code){
	using qscript_parser::question_list;
	program_code << "/*stub_manip::generate_code()" 
		<< question_name << ":" << named_stub << "*/"
		<< endl;
	program_code << "{" << endl;

	program_code << "set<int>::iterator set_iter = " << question_name 
		<< "->input_data.begin();" << endl;
	program_code << "for( ; set_iter!= " 
		<< question_name << "->input_data.end(); ++set_iter){" << endl;
	program_code << "for(int i=0; i< " << named_stub << ".size(); ++i){" << endl;
	program_code << "if(" << named_stub << "[i].code==*set_iter ) {" << endl;
	program_code << named_stub << "[i].mask=false; " << endl;
	program_code << "}" << endl;
	program_code << "}" << endl;

	program_code << endl;

	program_code << "}" << endl;

	/*
	int index=-1;
	for(int i=0; i<question_list.size(); ++i){
		if(question_list[i]->name == question_name){
			index = i;
			break;
		}
	}
	if(index==-1){
		stringstream s;
		s << "Error while generating code - parsed question not found in question list";
		print_err(compiler_code_generation_error, s.str() , 
				qscript_parser::line_no, __LINE__, __FILE__);
	} else {
	}*/
	// Just to print out whats going on after masking something
	program_code << "for(int i=0; i< " << named_stub << ".size(); ++i){" << endl;
	program_code << "cout << " << named_stub << "[i].stub_text << \":\" <<"  << endl 
		<< named_stub << "[i].mask << \":\" <<" << endl 
		<< named_stub << "[i].code  << endl;" << endl 
		<< endl;
	program_code << "}" << endl;
	program_code << "}" << endl;
	if(next) 
		next->generate_code(quest_defns, program_code);
}

stub_manip::~stub_manip(){
}
