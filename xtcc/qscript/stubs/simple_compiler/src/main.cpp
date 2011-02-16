#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include "symtab.h"
#include "stmt.h"
#include "expr.h"
#include "question.h"
#include "named_attributes.h"
#include "named_range.h"
#include "qscript_parser.h"
#include "scope.h"
#include "qscript_debug.h"


#include <fstream>
using  std::cerr;
using  std::endl;
using  std::cout;

	//extern Scope* active_scope;
	//extern vector <Scope*> active_scope_list;
	extern void yyrestart(FILE *input_file);
	extern int32_t yyparse();
	extern void GenerateCode();
	//extern vector </*Statement::*/FunctionInformation*> func_info_table;
	using qscript_parser::func_info_table;

	void clean_lex();

	void InitStatement();

int32_t main(int32_t argc, char* argv[])
{
	InitStatement();
	using qscript_parser::active_scope_list;
	using qscript_parser::active_scope;
	using qscript_parser::no_errors;
	int32_t opterr = 1, c;
	using qscript_parser::fname;
	int32_t fname_flag = 0;
	bool ncurses_flag = false;
	bool static_binary_flag = false;
	bool exit_flag = false;
	bool compile_to_cpp_only_flag = false;

	while( (c = getopt(argc, argv, "csnf:")) != -1 ){
		char ch = optopt;
		switch(c){
		case 'c':
			compile_to_cpp_only_flag = true;
			break;
		case 'n':
			ncurses_flag = true;
			break;
		case 's':
			static_binary_flag = true;
			break;
		case 'f':
			fname = optarg;
			fname_flag = 1;
			break;
		case '?':
			if (optopt == 'f' )
				cerr << " option -'" << optopt << "' requires an argument" << endl;
			else if (isprint(optopt)){
				cerr << " unknown option : '-" << optopt << "'" << endl;
			} else
				cerr << " unknown character " << optopt << endl;
			exit(1);
			break;
		default:
			cerr << "Usage: "
				<< argv[0] << " -f <input-file>\n" <<   endl;
			exit(0);
		}
		if (fname_flag == 1){
			break;
		}
	}
	char * QSCRIPT_HOME = getenv("QSCRIPT_HOME");
	if (!QSCRIPT_HOME){
		cout << "Please set environment variable QSCRIPT_HOME to the top-level directory that qscript is installed in" << endl
			<< "If qscript was installed in /home/unixuser/qscript/, in UNIX - bash " << endl
			<< "you would do this as (assume $ as shell prompt):" << endl
			<< "$export QSCRIPT_HOME=/home/unix_user/qscript" << endl;
		exit_flag = true;
	}
	if (!qscript_parser::ReadQScriptConfig()){
		exit_flag = true;
	}
	if (exit_flag){
		exit(1);
	}

	if (!fname_flag){
		cout << "Usage: "
			<< argv[0] << " -f <input-file> "  << endl;
		cout << "Options: " << endl;
		cout << " -n            - creates an ncurses executable " << endl;
		cout << " -s            - creates an static executable - for windows only " << endl;
		cout << " -c            - compile to c++ only - dont invoke c++ compiler" << endl;
		exit(0);
	}
	active_scope = new Scope();
	active_scope_list.push_back(active_scope);

	string printf_name = "printf";
	/*Statement:: */FunctionParameter* v_list = 0;
	DataType myreturn_type = INT8_TYPE;
	/*Statement::*/FunctionInformation* fi = new /*Statement::*/FunctionInformation(printf_name, v_list, myreturn_type);
	func_info_table.push_back(fi);


	FILE * yyin = fopen(fname.c_str(), "rb");
	if (!yyin){
		cerr << " Unable to open: " << fname << " for read ... exiting" << endl;
		exit(1);
	}
	yyrestart(yyin);
	qscript_parser::lex_location.SetFileName(qscript_parser::fname);
	qscript_parser::lex_location.ResetLine();
	qscript_parser::lex_location.ResetColumn();
	if (!yyparse() && !no_errors){
		cout << "Input parsed sucessfully: generating code" << endl;
		//data_entry_loop();
		qscript_parser::GenerateCode(fname, ncurses_flag);
		std::stringstream bcpp_command;
		bcpp_command << "bcpp " << fname << ".C" << " > " << fname << "_bcpp.C";
		if (int32_t ret_val = system(bcpp_command.str().c_str())) {
			cout << "error running bcpp - maybe its not installed or not present in the PATH variable" << endl;
		} else {
			// cout << "successfully ran bcpp to generate indented source" << endl;
		}
				
		cout << "code generated " << endl;
		if (compile_to_cpp_only_flag) {
		} else {
			if (static_binary_flag)
				qscript_parser::CompileGeneratedCodeStatic(fname);
			else
				qscript_parser::CompileGeneratedCode(fname);
		}
	} else {
		cerr << "There were : " << no_errors << " errors in parse" << endl;
	}
	{

		using qscript_parser::maintainer_messages;
		cout << "maintainer_messages: " << endl;
		for(map<pair<int32_t, int32_t>, string>::iterator it=maintainer_messages.begin();
				it!=maintainer_messages.end(); ++it) {
			cout << it->second << endl;
		}
	}

////////////////////////////////
	try
	{
		std::ofstream conf;
		conf.exceptions(std::ios::failbit | std::ios::badbit);
		conf.open("a.cfg");

		std::vector<AbstractQuestion*> &qv = qscript_parser::question_list;
		conf << qv.size() << '\n';
		for(int32_t i = 0; i < qv.size(); ++i)
		{
			conf << qv[i]->questionName_ << ' ';
			switch(qv[i]->dt)
			{
				case INT8_TYPE  : conf << "int8"  ; break;
				case INT16_TYPE : conf << "int16" ; break;
				case INT32_TYPE : conf << "int32" ; break;
				case FLOAT_TYPE : conf << "float" ; break;
				case DOUBLE_TYPE: conf << "double"; break;
				default: conf << "Unrecognised type";
			}
			conf << ' ';
			NamedStubQuestion *nsq = dynamic_cast<NamedStubQuestion*>(qv[i]); if (nsq) conf << nsq->nr_ptr->name;
			conf << '\n';
		}

		std::vector<named_range*> &nsl = qscript_parser::named_stubs_list;
		for(int32_t i = 0; i < nsl.size(); ++i)
		{
			conf << nsl[i]->name;
			std::vector<stub_pair> &sv = nsl[i]->stubs;
			for(int32_t i = 0; i < sv.size(); ++i) conf << ' ' << sv[i].code << " \"" << sv[i].stub_text << '\"';
			conf << '\n';
		}
	}
	catch(...){ std::cout << "error while generating configuration file\n"; }
////////////////////////////////
	if (qscript_parser::tree_root) {
		//cerr << "deleting qscript_parser::tree_root" << endl;
		delete qscript_parser::tree_root;
		if (active_scope_list[0]) {
			delete active_scope_list[0]; active_scope_list[0] = 0;
		}
		delete fi; fi = 0;
		//yy_delete_buffer(YY_CURRENT_BUFFER);
		clean_lex();
		for(int i=0; i<qscript_parser::
			    delete_manually_in_cleanup.size(); ++i){
			delete qscript_parser::delete_manually_in_cleanup[i];
			qscript_parser::delete_manually_in_cleanup[i]=0;
		}
	}


	return no_errors;
}
