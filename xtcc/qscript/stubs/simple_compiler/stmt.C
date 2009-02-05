#include "expr.h"
#include "stmt.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>

extern vector<mem_addr_tab> mem_addr;

extern ofstream debug_log_file;
using std::cout;
using std::endl;
void read_data(const char * prompt);
stmt::~stmt(){ 
	if (next  ) {
		delete next; next=0;
	} 
	debug_log_file << "stmt::~stmt() base destructor" << endl;
}

q_stmt::q_stmt(datatype l_type, int l_no, string l_name, string l_text, question_type l_q_type, int l_no_mpn, datatype l_dt,
	xtcc_set& l_r_data): 
	stmt(l_type, l_no), name(l_name), text(l_text), q_type(l_q_type) , 
	no_mpn(l_no_mpn),
	dt(l_dt)
{
	r_data = new xtcc_set(l_r_data);
}


#include <sstream>
int scan_datalex();
int scan_dataparse();
extern vector<int> data;
/*
void q_stmt::eval(){
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

	if(next){
		next->eval();
	}
}
*/

void q_stmt::generate_code(/*FILE * script*/ ostringstream & quest_defns, ostringstream& program_code){
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
	fprintf(script, "q_stmt * %s = new q_stmt(%d, \"%s\", \"%s\", %s, %d, %s, %s);\n",
		name.c_str(),
		line_no, name.c_str(), text.c_str(), q_type_str.c_str(), no_mpn, datatype_str.c_str(), xtcc_set_name
		); 
	*/
	quest_defns << "q_stmt * " << name.c_str() << " = new q_stmt("
		<< line_no << "," 
		<< "\"" << name.c_str() << "\"" << "," 
		<< "\"" << text.c_str() << "\"" << ","
		<< q_type_str.c_str() << ","
		<< no_mpn << ","
		<< datatype_str.c_str() << ","
		<< xtcc_set_name << ");\n";

	//fprintf(script, "q_list.push_back(%s);", name.c_str());
	quest_defns << "q_list.push_back(" << name.c_str() << ");\n";

	//fprintf(script, "%s->eval();\n", name.c_str());
	program_code << "\t\t" << name.c_str() << "->eval();\n" ;
	if(next){
		next->generate_code(quest_defns, program_code);
	}

}

void q_stmt::print_q_type(string &s){
	const int BUF_SIZE=200;
	char buff[BUF_SIZE];
	if(q_type==spn){
		s="spn";
	} else if(q_type==mpn){
		s="mpn";
	} else {
		sprintf(buff, " internal compiler error: update q_stmt::print_q_type: %d, %s", 
			__LINE__, __FILE__);
		s=buff;
	}
}



void q_stmt::print_data_type(string &s){
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
		sprintf(buff, " internal compiler error: update q_stmt::print_data_type : %d, %s", 
			__LINE__, __FILE__);
		s=buff;
	}
}

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
