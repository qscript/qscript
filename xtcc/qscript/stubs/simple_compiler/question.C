/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/question.C
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#include "question.h"
#include "named_range.h"
#include "scope.h"

#include <iostream>
#include <sstream>
#include <string>
#include "qscript_parser.h"

using std::cout;
using std::endl;
using std::cerr;
using namespace std;
//extern map<string, vector<string> > map_of_active_vars_for_questions;
void read_data(const char * prompt);

question::question(datatype l_type, int l_no, string l_name, string l_text
	, question_type l_q_type, int l_no_mpn, datatype l_dt
	//, expr* l_arr_sz
	, vector<expr*> & l_for_bounds_stack
	): 
	stmt(l_type, l_no), name(l_name), text(l_text), q_type(l_q_type) , 
	no_mpn(l_no_mpn),
	dt(l_dt)
	//, arr_sz(l_arr_sz)
	, for_bounds_stack(l_for_bounds_stack)
{
	//r_data = new xtcc_set(l_r_data);
}

question::question(datatype l_type, int l_no, string l_name, string l_text
	, question_type l_q_type, int l_no_mpn, datatype l_dt
	): 
	stmt(l_type, l_no), name(l_name), text(l_text), q_type(l_q_type) , 
	no_mpn(l_no_mpn),
	dt(l_dt)
	, for_bounds_stack(0)
{
}



range_question::range_question(datatype this_stmt_type, int line_number,
	string l_name, string l_q_text,
	question_type l_q_type, int l_no_mpn, datatype l_dt,
	xtcc_set& l_r_data
	//, expr* l_arr_sz
	, vector<expr*> & l_for_bounds_stack
	): 
	question(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt
		//, l_arr_sz
		, l_for_bounds_stack
		)
{
	r_data = new xtcc_set(l_r_data);
}

range_question::range_question(datatype this_stmt_type, int line_number,
	string l_name, string l_q_text,
	question_type l_q_type, int l_no_mpn, datatype l_dt,
	xtcc_set& l_r_data
	): 
	question(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt
		)
{
	r_data = new xtcc_set(l_r_data);
}


#include <sstream>
int scan_datalex();
int scan_dataparse();
extern vector<int> data;

bool range_question::is_valid(int value){
	return (r_data->exists(value))? true: false;
}

void range_question::eval(){
	cout << name << "." << text << endl << endl;
	for(	set<int>::iterator it=r_data->indiv.begin(); it!=r_data->indiv.end(); ++it){
		cout << *it << endl;
	}
	for(int i=0; i<r_data->range.size(); ++i){
		for(int j=r_data->range[i].first; j<=r_data->range[i].second;++j){  
			cout << j << endl; 
		}
	}


	if(input_data.begin()!=input_data.end()){
		cout << "Current data values: ";

		for(set<int>::iterator iter=input_data.begin();
			iter!=input_data.end(); ++iter){
			cout << *iter << " ";
		}
		cout << endl;
	}
	bool invalid_code=false;
	string prompt="before do: Enter Data:";
	do{
		invalid_code=false;
		read_data(prompt.c_str());
		cout << "data.size(): " << data.size() << endl;
		for(unsigned int i=0; i<data.size(); ++i){
			cout << "Testing data exists: " << data[i] << endl;
			if (!is_valid(data[i])){
				invalid_code=true;
				prompt = "Input contained some invalid data\nRe-enter Data\n";
				data.clear();
				break;
			}
		}
		if(invalid_code)
			continue;
		if(q_type==spn && data.size()>1) {
			prompt="Single coded question - please enter only 1 code:" ;
			invalid_code=true;
			data.clear();
		} else if (q_type==mpn && data.size() > no_mpn){
			prompt="Multi coded question codes exceed no of max codes:  " ;
			invalid_code=true;
			data.clear();
		} else {
			invalid_code=false;
		}

		if(invalid_code==false){
			input_data.erase(input_data.begin(), input_data.end());
			for(unsigned int i=0; i<data.size(); ++i){
				input_data.insert(data[i]);
				cout << "storing: " << data[i] << " into input_data" << endl;
			}
		}
	} while (invalid_code==true);
	
	data.clear();

}

bool named_stub_question::is_valid(int value){
	vector<stub_pair> vec= *stub_ptr;
	for (unsigned int j=0; j<vec.size(); ++j){
		if(vec[j].code==value){
			return true;
		}
	}
	return false;
}

void named_stub_question::eval(){
	cout << name << "." << text << endl << endl;
	vector<stub_pair> vec= *stub_ptr;
	for(unsigned int i=0; i< vec.size(); ++i){
		if( vec[i].mask)
			cout << vec[i].stub_text << ": " << vec[i].code << endl;
	}


	if(input_data.begin()!=input_data.end()){
		cout << "Current data values: ";
		
		for(set<int>::iterator iter=input_data.begin();
			iter!=input_data.end(); ++iter){
			cout << *iter << " ";
		}
		cout << endl;
	}
	bool invalid_code=false;
	string prompt="before do: Enter Data:";
	do{
		invalid_code=true;
		read_data(prompt.c_str());
		cout << "data.size(): " << data.size() << endl;
		for(unsigned int i=0; i<data.size(); ++i){
			cout << "Testing data exists: " << data[i] << endl;
			invalid_code=!is_valid(data[i]);
			if(invalid_code==true){
				prompt = "Input contained some invalid data\nRe-enter Data\n";
				data.clear();
				break;
			}
		}
		if(invalid_code)
			continue;
		if(q_type==spn && data.size()>1) {
			prompt="Single coded question - please enter only 1 code:" ;
			invalid_code=true;
			data.clear();
		} else if (q_type==mpn && data.size() > no_mpn){
			prompt="Multi coded question codes exceed no of max codes:  " ;
			invalid_code=true;
			data.clear();
		} else {
			invalid_code=false;
		}

		if(invalid_code==false){
			input_data.erase(input_data.begin(), input_data.end());
			for(unsigned int i=0; i<data.size(); ++i){
				input_data.insert(data[i]);
				cout << "storing: " << data[i] << " into input_data" << endl;
			}
		}
	} while (invalid_code==true);
	
	data.clear();
	
}

void range_question::generate_code_single_question( ostringstream & quest_defns, ostringstream& program_code){

	program_code << "lab_" << name << ":" << endl;

	string q_push_name = name + "_push";
	string q_pop_name = name + "_pop";
	using qscript_parser::map_of_active_vars_for_questions;
	vector<string> active_push_vars_for_this_question = map_of_active_vars_for_questions[q_push_name];
	vector<string> active_pop_vars_for_this_question = map_of_active_vars_for_questions[q_pop_name];
	for(unsigned int i=0; i< active_push_vars_for_this_question.size(); ++i){
		program_code << active_push_vars_for_this_question[i] << endl;
	}
	program_code << "if ( back_jump==true ) {" << endl;
	for(int i=active_pop_vars_for_this_question.size()-1; i>=0; --i){
		program_code << active_pop_vars_for_this_question[i] << endl;
	}
	program_code << "}" << endl;

	
	static int xtcc_set_counter=0;
	const int BUF_SIZE=100;
	char xtcc_set_name[BUF_SIZE];
	sprintf(xtcc_set_name, "xs_%d", xtcc_set_counter++);
	quest_defns  << "xtcc_set " << xtcc_set_name << ";" << endl;
	for(	set<int>::iterator it=r_data->indiv.begin(); it!=r_data->indiv.end(); ++it){
		quest_defns << xtcc_set_name << ".indiv.insert(" << *it << ");" << endl;
	}
	for(unsigned int i=0; i<r_data->range.size(); ++i){
		quest_defns << xtcc_set_name << ".range.push_back(pair<int,int>("
			<< r_data->range[i].first << "," << r_data->range[i].second
			<< "));" << endl;
	}
	string q_type_str;
	print_q_type(q_type_str);

	string datatype_str;
	print_data_type(datatype_str);


	quest_defns << "range_question * " << name.c_str() << " = new range_question(QUESTION_TYPE, "
		<< line_no << "," 
		<< "string( \"" << name.c_str() << "\")" << "," 
		<< "string(\" " << text.c_str() << "\")" << ","
		<< q_type_str.c_str() << ","
		<< no_mpn << ","
		<< datatype_str.c_str() << ","
		<< xtcc_set_name << ");\n";

	quest_defns << "question_list.push_back(" << name.c_str() << ");\n";

	if(for_bounds_stack.size()==0){
		program_code << "\t\t" << name.c_str() << "->eval();\n" ;
	} else {



		program_code << "\t\t" << name.c_str() << "_list[";
		/*
		for(int i=0; i<for_bounds_stack.size(); ++i){
			//program_code << 
			for_bounds_stack[i]->print_expr(quest_defns, program_code);
				
		}*/
		// ----------------------------------
		ostringstream * string_stream_vec=new ostringstream[for_bounds_stack.size()];
		for(int i=0; i< for_bounds_stack.size(); ++i){
			bin_expr * bin_expr_ptr = dynamic_cast<bin_expr*>(for_bounds_stack[i]);
			if(bin_expr_ptr){
				expr * rhs = bin_expr_ptr->r_op;
				expr * lhs = bin_expr_ptr->l_op;
				lhs->print_expr(string_stream_vec[i], string_stream_vec[i]); 
				if(i<for_bounds_stack.size()-1) {
					string_stream_vec[i] << "*" ;
				}
			} else {
				for_bounds_stack[i]->print_expr(string_stream_vec[i], string_stream_vec[i]);
				print_err(compiler_sem_err
					, "for loop index condition is not a binary expression" 
					, 0, __LINE__, __FILE__);
			}
			for(int j=i+1; j<for_bounds_stack.size(); j++){
				// quest_defns is passed twice
				// becaues we want the expr to appear in the for
				// loop in the questions section of the code
				bin_expr * bin_expr_ptr2 = dynamic_cast<bin_expr*>(for_bounds_stack[j]);
				if(bin_expr_ptr2){
					expr * rhs = bin_expr_ptr2->r_op;
					rhs->print_expr(string_stream_vec[i], string_stream_vec[i]);
					if(j<for_bounds_stack.size()-1) {
						string_stream_vec[i] << "*" ;
					}

				} else {
					for_bounds_stack[i]->print_expr(string_stream_vec[i], string_stream_vec[i]);
					print_err(compiler_sem_err
						, "for loop index condition is not a binary expression" 
						, 0, __LINE__, __FILE__);
				}
			}
		}
		for(int i=0; i<for_bounds_stack.size(); ++i) {
			//for_bounds_stack[i]->print_expr(quest_defns, program_code);
			program_code << string_stream_vec[i].str();
			if(i <for_bounds_stack.size()-1 ){
				program_code << "+";
			}
		}
		// ---------------------------------
		program_code << "]->eval();\n" ;
	}
	/*
	if(next){
		next->generate_code(quest_defns, program_code);
	}*/

}

void range_question::generate_code( ostringstream & quest_defns, ostringstream& program_code){
	if(for_bounds_stack.size()==0){
		generate_code_single_question(quest_defns, program_code);
	} else {
		quest_defns << "vector <question*> " << name << "_list;" << endl;
		for(int i=0; i< for_bounds_stack.size(); ++i){
			quest_defns << "for(int ";
			bin_expr * bin_expr_ptr = dynamic_cast<bin_expr*>(for_bounds_stack[i]);
			if(bin_expr_ptr){
				expr * rhs = bin_expr_ptr->r_op;
				expr * lhs = bin_expr_ptr->l_op;
				lhs->print_expr(quest_defns, quest_defns);
				quest_defns << "=0;";
				for_bounds_stack[i]->print_expr(quest_defns, quest_defns);
				quest_defns << "; ++";
				lhs->print_expr(quest_defns, quest_defns);
				quest_defns <<	"){" << endl;
			} else {
				for_bounds_stack[i]->print_expr(quest_defns, quest_defns);
				print_err(compiler_sem_err
					, "for loop index condition is not a binary expression" 
					, 0, __LINE__, __FILE__);
			}

			// quest_defns is passed twice
			// becaues we want the expr to appear in the for
			// loop in the questions section of the code
		}
		
		generate_code_single_question(quest_defns, program_code);
		quest_defns << name << "_list.push_back(" << name << ");"
			<< endl;
		for(int i=0; i< for_bounds_stack.size(); ++i){
			quest_defns << "}" << endl;
		}
	}
	if(next){
		next->generate_code(quest_defns, program_code);
	}
}

//extern vector <scope*> active_scope_list;
void named_stub_question::generate_code_single_question( ostringstream & quest_defns, 
		ostringstream& program_code){
	using qscript_parser::map_of_active_vars_for_questions;


	program_code << "lab_" << name << ":" << endl;

	string q_push_name = name + "_push";
	string q_pop_name = name + "_pop";
	vector<string> active_push_vars_for_this_question = map_of_active_vars_for_questions[q_push_name];
	vector<string> active_pop_vars_for_this_question = map_of_active_vars_for_questions[q_pop_name];
	for(unsigned int i=0; i< active_push_vars_for_this_question.size(); ++i){
		program_code << active_push_vars_for_this_question[i] << endl;
	}
	program_code << "if ( back_jump==true ) {" << endl;
	for(int i=active_pop_vars_for_this_question.size()-1; i>=0; --i){
		program_code << active_pop_vars_for_this_question[i] << endl;
	}
	program_code << "}" << endl;

	string q_type_str;
	print_q_type(q_type_str);

	string datatype_str;
	print_data_type(datatype_str);
	quest_defns << "// named_stub_question::generate_code() : to be implemented" << endl;
	quest_defns << "named_stub_question * " << name.c_str() << " = new named_stub_question(QUESTION_TYPE, "
		<< line_no << "," 
		<< "string( \"" << name.c_str() << "\")" << "," 
		<< "string(\" " << text.c_str() << "\")" << ","
		<< q_type_str.c_str() << ","
		<< no_mpn << ","
		<< datatype_str.c_str() << ",&"
		<< nr_ptr->name  << ");\n";
	quest_defns << "question_list.push_back(" << name.c_str() << ");\n";
	program_code << "\t\t" << name.c_str() << "->eval();\n" ;

	/*
	if(next){
		next->generate_code(quest_defns, program_code);
	}
	*/

}

void named_stub_question::generate_code( ostringstream & quest_defns, 
		ostringstream& program_code){
	if(for_bounds_stack.size()==0){
		generate_code_single_question(quest_defns, program_code);
	}  else {
		quest_defns << "vector <question*> " << name << "_list;" << endl;
		for(int i=0; i< for_bounds_stack.size(); ++i){
			quest_defns << "for(int ";
			bin_expr * bin_expr_ptr = dynamic_cast<bin_expr*>(for_bounds_stack[i]);
			if(bin_expr_ptr){
				expr * rhs = bin_expr_ptr->r_op;
				expr * lhs = bin_expr_ptr->l_op;
				lhs->print_expr(quest_defns, quest_defns);
				quest_defns << "=0;";
				for_bounds_stack[i]->print_expr(quest_defns, quest_defns);
				quest_defns << "; ++";
				lhs->print_expr(quest_defns, quest_defns);
				quest_defns <<	"){" << endl;
			} else {
				for_bounds_stack[i]->print_expr(quest_defns, quest_defns);
				print_err(compiler_sem_err
					, "for loop index condition is not a binary expression" 
					, 0, __LINE__, __FILE__);
			}

			// quest_defns is passed twice
			// becaues we want the expr to appear in the for
			// loop in the questions section of the code
		}
		
		generate_code_single_question(quest_defns, program_code);
		quest_defns << name << "_list.push_back(" << name << ");"
			<< endl;
		for(int i=0; i< for_bounds_stack.size(); ++i){
			quest_defns << "}" << endl;
		}
	}

	if(next){
		next->generate_code(quest_defns, program_code);
	} 

}

named_stub_question::named_stub_question(datatype this_stmt_type, int line_number,
	string l_name, string l_q_text,
	question_type l_q_type, int l_no_mpn, datatype l_dt,
	//string& l_named_list): 
	named_range* l_nr_ptr
	//, expr* l_arr_sz
	, vector<expr*>& l_for_bounds_stack
	):
	question(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt
		//, l_arr_sz
		, l_for_bounds_stack
		), 
	//named_list(l_named_list)
	nr_ptr(l_nr_ptr), stub_ptr(0)
{
}

named_stub_question::named_stub_question(datatype this_stmt_type, int line_number,
	string l_name, string l_q_text,
	question_type l_q_type, int l_no_mpn, datatype l_dt,
	named_range* l_nr_ptr
	):
	question(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt
		), 
	nr_ptr(l_nr_ptr), stub_ptr(0)
{
}

named_stub_question::named_stub_question(datatype this_stmt_type, int line_number,
	string l_name, string l_q_text,
	question_type l_q_type, int l_no_mpn, datatype l_dt,
	vector<stub_pair>* l_stub_ptr
	//, expr* l_arr_sz
	, vector<expr*>& l_for_bounds_stack
	):
	question(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt
		//, l_arr_sz
		, l_for_bounds_stack), 
	nr_ptr(0), stub_ptr(l_stub_ptr)
{
}

named_stub_question::named_stub_question(datatype this_stmt_type, int line_number,
	string l_name, string l_q_text,
	question_type l_q_type, int l_no_mpn, datatype l_dt,
	vector<stub_pair>* l_stub_ptr
	//, expr* l_arr_sz
	):
	question(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt
		), 
	nr_ptr(0), stub_ptr(l_stub_ptr)
{
}

void question::print_q_type(string &s){
	const int BUF_SIZE=200;
	char buff[BUF_SIZE];
	if(q_type==spn){
		s="spn";
	} else if(q_type==mpn){
		s="mpn";
	} else {
		sprintf(buff, " internal compiler error: update question::print_q_type: %d, %s", 
			__LINE__, __FILE__);
		s=buff;
	}
}



void question::print_data_type(string &s){
	if(dt==	VOID_TYPE){
		s="VOID_TYPE";
	} else if(dt==INT8_TYPE){
		s="INT8_TYPE";
	} else if(dt== INT16_TYPE) {
		s="INT16_TYPE";
	} else if(dt==  INT32_TYPE){
		s="INT32_TYPE";
	} else if(dt== FLOAT_TYPE){
		s="FLOAT_TYPE";
	} else if (dt== DOUBLE_TYPE){
		s="DOUBLE_TYPE";
	} else if (dt== BOOL_TYPE){
		s="BOOL_TYPE";
	} else if (dt== STRING_TYPE){
		s="STRING_TYPE";
	} else {
		const int BUF_SIZE=200;
		char buff[BUF_SIZE];
		sprintf(buff, " internal compiler error: update question::print_data_type : %d, %s", 
			__LINE__, __FILE__);
		s=buff;
	}
}

