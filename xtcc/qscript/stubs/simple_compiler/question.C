/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/question.C
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#include "question.h"
#include "named_range.h"

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
void read_data(const char * prompt);
question::question(datatype l_type, int l_no, string l_name, string l_text, 
	question_type l_q_type, int l_no_mpn, datatype l_dt
	/*, xtcc_set& l_r_data */): 
	stmt(l_type, l_no), name(l_name), text(l_text), q_type(l_q_type) , 
	no_mpn(l_no_mpn),
	dt(l_dt)
{
	//r_data = new xtcc_set(l_r_data);
}



range_question::range_question(datatype this_stmt_type, int line_number,
	string l_name, string l_q_text,
	question_type l_q_type, int l_no_mpn, datatype l_dt,
	xtcc_set& l_r_data): 
	question(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt)
{
	r_data = new xtcc_set(l_r_data);
}



#include <sstream>
int scan_datalex();
int scan_dataparse();
extern vector<int> data;
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

	bool invalid_code=false;
	string prompt="before do: Enter Data:";
	do{
		invalid_code=false;
		read_data(prompt.c_str());
		cout << "data.size(): " << data.size() << endl;
		for(int i=0; i<data.size(); ++i){
			cout << "Testing data exists: " << data[i] << endl;
			if (!r_data->exists(data[i])){
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
			for(int i=0; i<data.size(); ++i){
				input_data.insert(data[i]);
				cout << "storing: " << data[i] << " into input_data" << endl;
			}
		}
	} while (invalid_code==true);
	
	data.clear();

	//if(next){
	//	next->eval();
	//}
}

void named_stub_question::eval(){
	cout << name << "." << text << endl << endl;
	vector<stub_pair> vec= *stub_ptr;
	for(int i=0; i< vec.size(); ++i){
		cout << vec[i].stub_text << ": " << vec[i].code << endl;
	}


	bool invalid_code=false;
	string prompt="before do: Enter Data:";
	do{
		invalid_code=true;
		read_data(prompt.c_str());
		cout << "data.size(): " << data.size() << endl;
		for(int i=0; i<data.size(); ++i){
			cout << "Testing data exists: " << data[i] << endl;
			/*
			if (!r_data->exists(data[i])){
				invalid_code=true;
				prompt = "Input contained some invalid data\nRe-enter Data\n";
				data.clear();
				break;
			}
			*/
			for (int j=0; j<vec.size(); ++j){
				if(vec[j].code==data[i]){
					invalid_code=false;
					break;
				}
			}
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
			for(int i=0; i<data.size(); ++i){
				input_data.insert(data[i]);
				cout << "storing: " << data[i] << " into input_data" << endl;
			}
		}
	} while (invalid_code==true);
	
	data.clear();
	
}

void range_question::generate_code(/*FILE * script*/ ostringstream & quest_defns, ostringstream& program_code){
	cerr << "range_question::generate_code invoked: question: " << name << endl;
	/*
	fprintf(script, "cout <<  \"%s.%s\" << endl << endl;\n\n", name.c_str(), text.c_str());
	for(	set<int>::iterator it=r_data->indiv.begin(); it!=r_data->indiv.end(); ++it){
		fprintf(script, "cout << %d << endl;\n", *it );
	}
	for(int i=0; i<r_data->range.size(); ++i){
		for(int j=r_data->range[i].first; j<=r_data->range[i].second;++j){  
			fprintf(script, "cout << %d << endl;\n",j ); 
		}
	}
	*/
	
	static int xtcc_set_counter=0;
	const int BUF_SIZE=100;
	char xtcc_set_name[BUF_SIZE];
	sprintf(xtcc_set_name, "xs_%d", xtcc_set_counter++);
	//fprintf(script, "xtcc_set %s;\n", xtcc_set_name);
	quest_defns  << "xtcc_set " << xtcc_set_name << ";" << endl;
	for(	set<int>::iterator it=r_data->indiv.begin(); it!=r_data->indiv.end(); ++it){
		//fprintf(script, "%s.indiv.insert(%d);\n", xtcc_set_name, *it);
		quest_defns << xtcc_set_name << ".indiv.insert(" << *it << ");" << endl;
	}
	for(int i=0; i<r_data->range.size(); ++i){
		//fprintf(script, "%s.range.push_back(pair<int,int>(%d,%d));\n",
		//	xtcc_set_name, r_data->range[i].first, r_data->range[i].second);
		quest_defns << xtcc_set_name << ".range.push_back(pair<int,int>("
			<< r_data->range[i].first << "," << r_data->range[i].second
			<< "));" << endl;
	}
	string q_type_str;
	print_q_type(q_type_str);

	string datatype_str;
	print_data_type(datatype_str);

	/*
	fprintf(script, "question * %s = new question(%d, \"%s\", \"%s\", %s, %d, %s, %s);\n",
		name.c_str(),
		line_no, name.c_str(), text.c_str(), q_type_str.c_str(), no_mpn, datatype_str.c_str(), xtcc_set_name
		); 
	*/

	quest_defns << "range_question * " << name.c_str() << " = new range_question(QUESTION_TYPE, "
		<< line_no << "," 
		<< "string(\" " << name.c_str() << "\")" << "," 
		<< "string(\" " << text.c_str() << "\")" << ","
		<< q_type_str.c_str() << ","
		<< no_mpn << ","
		<< datatype_str.c_str() << ","
		<< xtcc_set_name << ");\n";

	//fprintf(script, "question_list.push_back(%s);", name.c_str());
	quest_defns << "question_list.push_back(" << name.c_str() << ");\n";

	//fprintf(script, "%s->eval();\n", name.c_str());
	program_code << "\t\t" << name.c_str() << "->eval();\n" ;
	if(next){
		next->generate_code(quest_defns, program_code);
	}

}


void named_stub_question::generate_code( ostringstream & quest_defns, 
		ostringstream& program_code){
	cerr << "named_stub_question::generate_code invoked: question: " << name << endl;
	string q_type_str;
	print_q_type(q_type_str);

	string datatype_str;
	print_data_type(datatype_str);
	quest_defns << "// named_stub_question::generate_code() : to be implemented" << endl;
	quest_defns << "named_stub_question * " << name.c_str() << " = new named_stub_question(QUESTION_TYPE, "
		<< line_no << "," 
		<< "string(\" " << name.c_str() << "\")" << "," 
		<< "string(\" " << text.c_str() << "\")" << ","
		<< q_type_str.c_str() << ","
		<< no_mpn << ","
		<< datatype_str.c_str() << ",&"
		<< nr_ptr->name  << ");\n";
	quest_defns << "question_list.push_back(" << name.c_str() << ");\n";
	program_code << "\t\t" << name.c_str() << "->eval();\n" ;

	if(next){
		next->generate_code(quest_defns, program_code);
	}

}

named_stub_question::named_stub_question(datatype this_stmt_type, int line_number,
	string l_name, string l_q_text,
	question_type l_q_type, int l_no_mpn, datatype l_dt,
	//string& l_named_list): 
	named_range* l_nr_ptr):
	question(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt), 
	//named_list(l_named_list)
	nr_ptr(l_nr_ptr), stub_ptr(0)
{
}


named_stub_question::named_stub_question(datatype this_stmt_type, int line_number,
	string l_name, string l_q_text,
	question_type l_q_type, int l_no_mpn, datatype l_dt,
	vector<stub_pair>* l_stub_ptr):
	question(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt), 
	//named_list(l_named_list)
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

