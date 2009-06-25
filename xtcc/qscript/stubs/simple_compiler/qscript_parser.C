#include "qscript_parser.h"

#include <cstdlib>
#include <sstream>
#include <iostream>
namespace qscript_parser {
	using std::cerr;
	using std::cout;
	using std::endl;
	using std::stringstream;
	vector<AbstractExpression*> for_loop_max_counter_stack;
	Scope* active_scope;
	vector <Scope*> active_scope_list;
	int nest_lev=0;
	int flagIsAFunctionBody_=-1;
	int flagIsAForBody_=0;
	bool flag_next_stmt_start_of_block=false;
	vector<bool> blk_start_flag;
	vector <AbstractStatement*> blk_heads;
	//const int DEFAULT_STACK_SIZE=20;
	vector<CompoundStatement*> stack_cmpd_stmt;
	vector<string> stack_of_active_push_vars;
	map<string, vector<string> > map_of_active_vars_for_questions;

	AbstractExpression * recurse_for_index(int stack_index);


	ofstream debug_log_file("xtcc_debug.log", std::ios_base::out|std::ios_base::trunc);
	using std::string;
	//void print_err(compiler_err_category cmp_err, 
	//	string err_msg, int line_no, 
	//	int compiler_line_no, string compiler_file_name);
	int line_no;
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


	QuestionType q_type;
#include "const_defs.h"
#include "xtcc_set.h"
	int no_mpn=0;
	XtccSet xs;
	int yylex();
	void yyerror(const char * s);
	int no_errors;

	struct AbstractStatement* tree_root=0;
	vector <AbstractQuestion*> question_list;
	void GenerateCode();
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);
	const bool XTCC_DEBUG_MEM_USAGE=true;
	bool skip_func_type_check(const char * fname);
	vector<mem_addr_tab>  mem_addr;
	vector <FunctionInformation*> func_info_table;
	int check_parameters(struct AbstractExpression* e, struct VariableList* v);

        vector <string> attribute_list;
	vector <named_range*> named_stubs_list;
	vector <named_attribute_list> named_attributes_list;
        vector <stub_pair> stub_list;
	int if_line_no=-1;
	
	int yywrap();

}

namespace qscript_parser{

using std::string;

#include <sstream>

void print_header(FILE* script);
void print_close(FILE* script, ostringstream & program_code);
void GenerateCode(){
	string script_name("test_script.C");
	FILE * script = fopen(script_name.c_str(), "w");
	if(!script){
		cerr << "unable to open output file to dump script data: " << script_name << endl;
		exit(1);
	}
	ostringstream quest_defns, program_code;
	print_header(script);
	tree_root->GenerateCode(quest_defns, program_code);
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
	fprintf(script, "#include <cstdlib>\n");
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
	fprintf(script, "vector <AbstractQuestion*> question_list;\n");
	fprintf(script, "vector<mem_addr_tab>  mem_addr;\n");
	fprintf(script, "extern vector<question_disk_data*>  qdd_list;\n");
	fprintf(script, "void merge_disk_data_into_questions();\n");


	//fprintf(script, "\tnoun_list_type noun_list[]= {\n");
	//fprintf(script, "\t\t\t{\t\"void\"\t, VOID_TYPE},\n");
	//fprintf(script, "\t\t\t{\t\"int8_t\" ,INT8_TYPE},\n");
	//fprintf(script, "\t\t\t{\t\"int16_t\" ,INT16_TYPE},\n");
	//fprintf(script, "\t\t\t{\t\"int32_t\" ,INT32_TYPE},\n");
	//fprintf(script, "\t\t\t{\t\"float\", FLOAT_TYPE},\n");
	//fprintf(script, "\t\t\t{\t\"double\", DOUBLE_TYPE}\n");
	//fprintf(script, "\t\t};\n");
	fprintf(script, "\n");
	fprintf(script, "int check_if_reg_file_exists(string jno, int ser_no);\n");
	fprintf(script, "map<string, vector<string> > map_of_active_vars_for_questions;\n");
	fprintf(script, "vector <int8_t> vector_int8_t;\n");
	fprintf(script, "vector <int16_t> vector_int16_t;\n");
	fprintf(script, "vector <int32_t> vector_int32_t;\n");
	fprintf(script, "vector <float> vector_float_t;\n");
	fprintf(script, "vector <double> vector_double_t;\n");
	fprintf(script, "bool back_jump=false;// no need for this but state the intent\n");
	fprintf(script, "void write_data_to_disk(const vector<AbstractQuestion*>& q_vec, string jno, int ser_no);\n");


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
const char * write_data_to_disk_code();

void print_close(FILE* script, ostringstream & program_code){

	fprintf(script, "\tint ser_no;\n");
	fprintf(script, "\tcout << \"Enter Serial No (0) to exit: \" << flush;\n");
	fprintf(script, "\tcin >> ser_no;\n");
	fprintf(script, "\tstring jno=\"j_1001\";\n");
	fprintf(script, "\twhile(ser_no!=0){\n");
	fprintf(script, "%s\n", file_exists_check_code());
	fprintf(script, "%s\n", program_code.str().c_str());
	/*
	fprintf(script, "\t\t\tstringstream fname_str;\n");
	fprintf(script, "\t\t\tfname_str << jno << \"_\" << ser_no << \".dat\";\n");
	fprintf(script, "\t\t\tFILE * fptr = fopen(fname_str.str().c_str(), \"w+b\");\n");
	fprintf(script, "\tfor (int i=0; i<question_list.size(); ++i){\n");
	fprintf(script, "\t\tfprintf(fptr, \"%%s: \", question_list[i]->name_.c_str());\n");
	fprintf(script, "\t\tfor( set<int>::iterator iter=question_list[i]->input_data.begin();\n");
	fprintf(script, "\t\t\t\titer!=question_list[i]->input_data.end(); ++iter){\n");
	fprintf(script, "\t\t\tfprintf(fptr, \"%%d \", *iter);\n");
	fprintf(script, "\t\t}\n");
	fprintf(script, "\t\tfprintf(fptr, \"\\n\");\n");
	fprintf(script, "\t\tquestion_list[i]->input_data.clear();\n");
	fprintf(script, "\t}\n");
	fprintf(script, "\tfclose(fptr);\n");
	fprintf(script, "\n");
	*/
	fprintf(script, "\t\twrite_data_to_disk(question_list, jno, ser_no);\n");

	fprintf(script,	"\tcout << \"Enter Serial No (0) to exit: \" << flush;\n");
	fprintf(script, "\tcin >> ser_no;\n");
	fprintf(script, "\n\t} /* close while */\n");
	fprintf(script, "\n} /* close main */\n");
	fprintf(script, "%s\n", write_data_to_disk_code());
}


	bool skip_func_type_check(const char * fname){
		const char * skip_func_type_check_list[] = {"printf" };
		for (unsigned int i=0; i<sizeof(skip_func_type_check_list)/sizeof(skip_func_type_check_list[0]); ++i){
			if(!strcmp(fname, skip_func_type_check_list[i])){
				return true;
			}
		}
		return false;
	}

int check_parameters(AbstractExpression* e, VariableList* v){
	debug_log_file << "check_parameters: called" << endl;
	AbstractExpression* e_ptr=e;
	VariableList* fparam=v;
	bool match=true;
	/* Important point to note: I am not allowing references in ordinary variable decl
	   Only in function parameter list - the object is to allow modifying of variables
	   in a function as in C++
	   */

	int chk_param_counter=1;
	while (e_ptr && fparam) {
		//e_ptr->print();
		DataType etype=e_ptr->type_, fptype=fparam->variableType_; 
		if((etype>=INT8_TYPE && etype<=DOUBLE_TYPE) && 
			((fptype>=INT8_TYPE && fptype<=DOUBLE_TYPE)||
			 (fptype>=INT8_REF_TYPE && fptype<=DOUBLE_REF_TYPE))){
			DataType tdt=fptype;
				/* the code below makes a INT8_REF_TYPE -> INT8_TYPE
				   			a INT8_REF_TYPE -> INT8_TYPE
				 thats because we dont care much about references -> C++
				 does all the hard work. For checking types they are equivalent to us
				*/			
			if(tdt>=INT8_REF_TYPE) tdt=DataType(INT8_TYPE+tdt-INT8_REF_TYPE);
			if(etype <= tdt) {
				debug_log_file << "varname: "<< fparam->variableName_ << " chk_param_counter: " 
					<< chk_param_counter << " passed " << endl;
			}
		} else if ((etype>=INT8_ARR_TYPE&&etype<=DOUBLE_ARR_TYPE)&&
				(fptype>=INT8_ARR_TYPE&&fptype<=DOUBLE_ARR_TYPE)&&
				(etype==fptype)){
			debug_log_file << "varname: "<< fparam->variableName_ << " chk_param_counter: " 
					<< chk_param_counter << " passed " << endl;
		}else {
			match=false;
			cerr << "Parameter type mismatch name: " << endl;
			cerr << fparam->variableName_ << " expected type is " << fparam->variableType_
				<< " passed type is " << e_ptr->type_ 
				<< " line_no: " << line_no << " or currently allowed promotion to: " 
				<< e_ptr->type_+INT8_REF_TYPE
				<< endl;
			++no_errors;
		}
		e_ptr=e_ptr->next_;
		fparam=fparam->next_;
		chk_param_counter=chk_param_counter+1;
	}
	if(match==true){
		if(e_ptr==0&& fparam==0){
			match=true;
		} else {
			match=false;
			++no_errors;
			cerr << "NOTMATCHED: No of parameters in function call not matching with no of paramters in AbstractExpression: line_no"
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


AbstractStatement* setup_stub_manip_stmt(DataType dt
		, char* stub_list_name , char * question_name
	){
	int index=-1;
	for(int i=0; i<named_stubs_list.size(); ++i){
		named_range * nr_ptr = named_stubs_list[i];
		if(nr_ptr->name==stub_list_name){
			index=i;
			break;
		}
	}
	if(index==-1){
		stringstream err_text;
		err_text << "named stub list does not exist: " << stub_list_name;
		print_err(compiler_sem_err, err_text.str(),
			line_no, __LINE__, __FILE__  );
	} 
	int index_question=-1;
	for(int i=0; i<question_list.size(); ++i){
		if(question_list[i]->questionName_ == question_name){
			index_question=i;
			break;
		}
	}
	if(index_question==-1){
		stringstream err_text;
		err_text << "AbstractQuestion does not exist: " << question_name;
		print_err(compiler_sem_err, err_text.str(),
			line_no, __LINE__, __FILE__  );
	} else {
		if(index_question>=0 && index>=0){
			NamedStubQuestion * q_ptr= 
				dynamic_cast<NamedStubQuestion*> (question_list[index_question]);
			if(q_ptr){
				if(! (q_ptr->nr_ptr->name == stub_list_name) ){
					stringstream err_text;
					err_text << "AbstractQuestion: " << question_name
						<< " named range: " << q_ptr->nr_ptr->name 
						<< " and named stub is : " << stub_list_name 
						<< endl;

					print_err(compiler_sem_err, err_text.str(),
						line_no, __LINE__, __FILE__  );
				}
			} else {
				stringstream err_text;
				err_text << "AbstractQuestion : " << question_name <<
					"is not a named range AbstractQuestion" ;
				print_err(compiler_sem_err, err_text.str(),
					line_no, __LINE__, __FILE__  );
			}
		}
	}
	struct AbstractStatement* st_ptr = new StubManipStatement(dt,
		line_no, stub_list_name, question_name);
	
	return st_ptr;
}


AbstractStatement* setup_stub_manip_stmt_set_unset(DataType dt
		, char* stub_list_name)
{
	int index=-1;
	for(int i=0; i<named_stubs_list.size(); ++i){
		named_range * nr_ptr = named_stubs_list[i];
		if(nr_ptr->name==stub_list_name){
			index=i;
			break;
		}
	}
	if(index==-1){
		stringstream err_text;
		err_text << "named stub list does not exist: " << stub_list_name;
		print_err(compiler_sem_err, err_text.str(),
			line_no, __LINE__, __FILE__  );
	} 
	struct AbstractStatement* st_ptr = new StubManipStatement(dt,
		line_no, stub_list_name);
	
	return st_ptr;
}

const char * write_data_to_disk_code(){
	const char * write_data_disk_code = 
	"\tvoid write_data_to_disk(const vector<AbstractQuestion*>& q_vec\n"
	"\t	, string jno\n"
	"\t	, int ser_no) {\n"
	"\t	stringstream fname_str;\n"
	"\t	fname_str << jno << \"_\" << ser_no << \".dat\";\n"
	"\t	//FILE * fptr = fopen(fname_str.str().c_str(), \"w+b\");\n"
	"\t\n"
	"\t\n"
	"\t	std::ofstream data_file;\n"
	"\t	data_file.exceptions(std::ios::failbit | std::ios::badbit);\n"
	"\t	data_file.open(fname_str.str().c_str());\n"
	"\t\n"
	"\t	for (int i=0; i<question_list.size(); ++i){\n"
	"\t		question_list[i]->WriteDataToDisk(data_file);\n"
	"\t		/*\n"
	"\t		fprintf(fptr, \"%s: \", question_list[i]->name.c_str());\n"
	"\t		for( set<int>::iterator iter=question_list[i]->input_data.begin();\n"
	"\t				iter!=question_list[i]->input_data.end(); ++iter){\n"
	"\t			fprintf(fptr, \"%d \", *iter);\n"
	"\t		}\n"
	"\t		fprintf(fptr, \"\n\");\n"
	"\t		question_list[i]->input_data.clear();\n"
	"\t		*/\n"
	"\t	}\n"
	"\t	//fclose(fptr);\n"
	"\t}\n"
	"\n";
	return write_data_disk_code;
}

/* end of namespace */
}
