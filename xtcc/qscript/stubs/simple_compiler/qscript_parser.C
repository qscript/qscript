#include "qscript_parser.h"

namespace qscript_parser {
	scope* active_scope;
	vector <scope*> active_scope_list;
	int nest_lev=0;
	int flag_cmpd_stmt_is_a_func_body=-1;
	int flag_cmpd_stmt_is_a_for_body=-1;
	bool flag_next_stmt_start_of_block=false;
	vector<bool> blk_start_flag;
	vector <stmt*> blk_heads;
	//const int DEFAULT_STACK_SIZE=20;
	vector<cmpd_stmt*> stack_cmpd_stmt;
	vector<string> stack_of_active_push_vars;
	map<string, vector<string> > map_of_active_vars_for_questions;



	ofstream debug_log_file("xtcc_debug.log", ios_base::out|ios_base::trunc);
	using std::string;
	void print_err(compiler_err_category cmp_err, 
		string err_msg, int line_no, 
		int compiler_line_no, string compiler_file_name);
	extern int line_no;
	extern noun_list_type noun_list[];

	/*
	noun_list_type noun_list[]= {
			{	"void"	, VOID_TYPE},
			{	"int8_t" ,INT8_TYPE},
			{	"int16_t" ,INT16_TYPE},
			{	"int32_t" ,INT32_TYPE},
			{	"float", FLOAT_TYPE},
			{	"double", DOUBLE_TYPE}
		};
	*/	


	question_type q_type;
#include "const_defs.h"
#include "xtcc_set.h"
	int no_mpn=0;
	xtcc_set xs;
	int yylex();
	void yyerror(const char * s);
	int no_errors;

	struct stmt* tree_root=0;
	vector <question*> question_list;
	void generate_code();
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);
	const bool XTCC_DEBUG_MEM_USAGE=true;
	bool skip_func_type_check(const char * fname);
	vector<mem_addr_tab>  mem_addr;
	vector <func_info*> func_info_table;
	int check_parameters(struct expr* e, struct var_list* v);

        vector <string> attribute_list;
	vector <named_range*> named_stubs_list;
	vector <named_attribute_list> named_attributes_list;
        vector <stub_pair> stub_list;
	extern int if_line_no;
	
	int yywrap();

}

namespace qscript_parser{

using std::string;

#include <sstream>

void print_header(FILE* script);
void print_close(FILE* script, ostringstream & program_code);
void generate_code(){
	string script_name("test_script.C");
	FILE * script = fopen(script_name.c_str(), "w");
	if(!script){
		cerr << "unable to open output file to dump script data: " << script_name << endl;
		exit(1);
	}
	ostringstream quest_defns, program_code;
	print_header(script);
	tree_root->generate_code(quest_defns, program_code);
	fprintf(script, "%s\n", quest_defns.str().c_str());
	print_close(script, program_code);
}

void print_header(FILE* script){
	fprintf(script, "#include <iostream>\n");
	fprintf(script, "#include <vector>\n");
	fprintf(script, "#include <string>\n");
	fprintf(script, "#include <sstream>\n");
	fprintf(script, "#include <fstream>\n");
	fprintf(script, "#include <map>\n");
	fprintf(script, "#include \"stmt.h\"\n");
	fprintf(script, "#include \"xtcc_set.h\"\n");
	fprintf(script, "#include \"stub_pair.h\"\n");
	fprintf(script, "#include \"symtab.h\"\n");
	fprintf(script, "#include \"qscript_lib.h\"\n");
	fprintf(script, "#include \"question_disk_data.h\"\n");

	fprintf(script, "#include \"debug_mem.h\"\n");
	fprintf(script, "fstream debug_log_file(\"xtcc_debug.log\", ios_base::out|ios_base::trunc);\n");

	fprintf(script, "using namespace std;\n");
	fprintf(script, "void read_data(const char * prompt);\n");
	fprintf(script, "extern vector<int> data;\n");
	fprintf(script, "vector <question*> question_list;\n");
	fprintf(script, "vector<mem_addr_tab>  mem_addr;\n");
	fprintf(script, "extern vector<question_disk_data*>  qdd_list;\n");
	fprintf(script, "void merge_disk_data_into_questions();\n");


	fprintf(script, "\tnoun_list_type noun_list[]= {\n");
	fprintf(script, "\t\t\t{\t\"void\"\t, VOID_TYPE},\n");
	fprintf(script, "\t\t\t{\t\"int8_t\" ,INT8_TYPE},\n");
	fprintf(script, "\t\t\t{\t\"int16_t\" ,INT16_TYPE},\n");
	fprintf(script, "\t\t\t{\t\"int32_t\" ,INT32_TYPE},\n");
	fprintf(script, "\t\t\t{\t\"float\", FLOAT_TYPE},\n");
	fprintf(script, "\t\t\t{\t\"double\", DOUBLE_TYPE}\n");
	fprintf(script, "\t\t};\n");
	fprintf(script, "\n");
	fprintf(script, "int check_if_reg_file_exists(string jno, int ser_no);\n");
	fprintf(script, "map<string, vector<string> > map_of_active_vars_for_questions;\n");
	fprintf(script, "vector <int8_t> vector_int8_t;\n");
	fprintf(script, "vector <int16_t> vector_int16_t;\n");
	fprintf(script, "vector <int32_t> vector_int32_t;\n");
	fprintf(script, "vector <float> vector_float_t;\n");
	fprintf(script, "vector <double> vector_double_t;\n");
	fprintf(script, "bool back_jump=false;// no need for this but state the intent\n");

	fprintf(script, "int main(){\n");
	/*
	map<string, vector<string> > ::iterator iter;
	for(iter=map_of_active_push_vars_for_questions.begin();
		iter!=map_of_active_push_vars_for_questions.end();
		++iter){
		//fprintf("\t");
		string q_name = iter->first;
		fprintf(script, "vector <string> active_push_vars_%s;\n",
			q_name.c_str());
		vector<string>& v=iter->second;
		for(unsigned int i=0; i<v.size(); ++i){
			fprintf(script, "active_push_vars_%s.push_back(%s);\n",
				q_name.c_str(), v[i].c_str());
		}
		fprintf(script, "map_of_active_push_vars_for_questions[%s] = active_push_vars_%s;\n",
			q_name.c_str(), q_name.c_str());
	}
	*/

}

const char * file_exists_check_code();

void print_close(FILE* script, ostringstream & program_code){

	fprintf(script, "\tint ser_no;\n");
	fprintf(script, "\tcout << \"Enter Serial No (0) to exit: \" << flush;\n");
	fprintf(script, "\tcin >> ser_no;\n");
	fprintf(script, "\tstring jno=\"j_1001\";\n");
	fprintf(script, "\twhile(ser_no!=0){\n");
	fprintf(script, "%s\n", file_exists_check_code());
	fprintf(script, "%s\n", program_code.str().c_str());
	fprintf(script, "\t\t\tstringstream fname_str;\n");
	fprintf(script, "\t\t\tfname_str << jno << \"_\" << ser_no << \".dat\";\n");
	fprintf(script, "\t\t\tFILE * fptr = fopen(fname_str.str().c_str(), \"w+b\");\n");
	fprintf(script, "\tfor (int i=0; i<question_list.size(); ++i){\n");
	fprintf(script, "\t\tfprintf(fptr, \"%%s: \", question_list[i]->name.c_str());\n");
	fprintf(script, "\t\tfor( set<int>::iterator iter=question_list[i]->input_data.begin();\n");
	fprintf(script, "\t\t\t\titer!=question_list[i]->input_data.end(); ++iter){\n");
	fprintf(script, "\t\t\tfprintf(fptr, \"%%d \", *iter);\n");
	fprintf(script, "\t\t}\n");
	fprintf(script, "\t\tfprintf(fptr, \"\\n\");\n");
	fprintf(script, "\t\tquestion_list[i]->input_data.clear();\n");
	fprintf(script, "\t}\n");
	fprintf(script, "\tfclose(fptr);\n");
	fprintf(script, "\n");
	fprintf(script,	"\tcout << \"Enter Serial No (0) to exit: \" << flush;\n");
	fprintf(script, "\tcin >> ser_no;\n");
	fprintf(script, "\n\t} /* close while */\n");
	fprintf(script, "\n} /* close main */\n");
}

/*
template<class T> T* link_chain(T* &elem1, T* &elem2){
	if(elem1 && elem2){
		elem2->prev=elem1;
		elem1->next=elem2;
		return elem2;
	}
	else if(elem1){
		return elem1;
	} else {
		return elem2;
	}
}

template<class T> T* trav_chain(T* & elem1){
	if(elem1){
		while (elem1->prev) elem1=elem1->prev;
		return elem1;
	} else return 0;
}
*/

	bool skip_func_type_check(const char * fname){
		const char * skip_func_type_check_list[] = {"printf" };
		for (unsigned int i=0; i<sizeof(skip_func_type_check_list)/sizeof(skip_func_type_check_list[0]); ++i){
			if(!strcmp(fname, skip_func_type_check_list[i])){
				return true;
			}
		}
		return false;
	}

int check_parameters(expr* e, var_list* v){
	debug_log_file << "check_parameters: called" << endl;
	expr* e_ptr=e;
	var_list* fparam=v;
	bool match=true;
	/* Important point to note: I am not allowing references in ordinary variable decl
	   Only in function parameter list - the object is to allow modifying of variables
	   in a function as in C++
	   */

	int chk_param_counter=1;
	while (e_ptr && fparam) {
		//e_ptr->print();
		datatype etype=e_ptr->type, fptype=fparam->var_type; 
		if((etype>=INT8_TYPE && etype<=DOUBLE_TYPE) && 
			((fptype>=INT8_TYPE && fptype<=DOUBLE_TYPE)||
			 (fptype>=INT8_REF_TYPE && fptype<=DOUBLE_REF_TYPE))){
			datatype tdt=fptype;
				/* the code below makes a INT8_REF_TYPE -> INT8_TYPE
				   			a INT8_REF_TYPE -> INT8_TYPE
				 thats because we dont care much about references -> C++
				 does all the hard work. For checking types they are equivalent to us
				*/			
			if(tdt>=INT8_REF_TYPE) tdt=datatype(INT8_TYPE+tdt-INT8_REF_TYPE);
			if(etype <= tdt) {
				debug_log_file << "varname: "<< fparam->var_name << " chk_param_counter: " 
					<< chk_param_counter << " passed " << endl;
			}
		} else if ((etype>=INT8_ARR_TYPE&&etype<=DOUBLE_ARR_TYPE)&&
				(fptype>=INT8_ARR_TYPE&&fptype<=DOUBLE_ARR_TYPE)&&
				(etype==fptype)){
			debug_log_file << "varname: "<< fparam->var_name << " chk_param_counter: " 
					<< chk_param_counter << " passed " << endl;
		}else {
			match=false;
			cerr << "Parameter type mismatch name: " << endl;
			cerr << fparam->var_name << " expected type is " << fparam->var_type
				<< " passed type is " << e_ptr->type 
				<< " line_no: " << line_no << " or currently allowed promotion to: " 
				<< e_ptr->type+INT8_REF_TYPE
				<< endl;
			++no_errors;
		}
		e_ptr=e_ptr->next;
		fparam=fparam->next;
		chk_param_counter=chk_param_counter+1;
	}
	if(match==true){
		if(e_ptr==0&& fparam==0){
			match=true;
		} else {
			match=false;
			++no_errors;
			cerr << "NOTMATCHED: No of parameters in function call not matching with no of paramters in expr: line_no"
				<< line_no << endl;
		}
	}
	if(!match) {
		cerr << "function parameter type check FAILURE: line_no " << line_no << endl;
	}
	return match;
}


const char * file_exists_check_code(){
	const char * file_check_code =  
	"\tint exists=check_if_reg_file_exists(jno, ser_no);\n"
	"\tif(exists){\n"
	"\t	load_data(jno,ser_no);\n"
	"\t	merge_disk_data_into_questions();\n"
	"\t	for(unsigned int i=0; i< qdd_list.size(); ++i){\n"
	"\t		cout << qdd_list[i]->qno << endl;\n"
	"\t		cout  << \":\" << qdd_list[i]->data.size() << endl;\n"
	"\t		for(int j=0; j<qdd_list[i]->data.size(); ++j){\n"
	"\t			cout << qdd_list[i]->data[j] << \" \";\n"
	"\t		}\n"
	"\t		cout << endl;\n"
	"\t	}\n"
	"\t}\n";
	return file_check_code;
}

}
