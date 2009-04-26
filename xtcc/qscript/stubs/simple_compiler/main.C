#include <unistd.h>
#include <string>
#include "tree.h"
#include "symtab.h"
#include "stmt.h"
#include "expr.h"
#include "named_attributes.h"
#include "named_range.h"
#include "qscript_parser.h"

	//extern scope* active_scope;
	//extern vector <scope*> active_scope_list;
	extern void yyrestart ( FILE *input_file );
	extern int yyparse();
	extern void generate_code();

int main(int argc, char* argv[]){
	using qscript_parser::active_scope_list;
	using qscript_parser::active_scope;
	using qscript_parser::no_errors;
	int opterr=1, c;
	string fname;
	int fname_flag=0;
	
	while( (c=getopt(argc, argv, "f:"))!=-1 ){
		char ch=optopt;
		switch(c){
		case 'f':
			fname=optarg;
			fname_flag=1;
			break;
		case '?': 
			if(optopt == 'f' ) 
				cerr << " option -'" << optopt << "' requires an argument" << endl;
			else if (isprint(optopt)){
				cerr << " unknown option : '-" << optopt << "'" << endl;
			} else 	
				cerr << " unknown character " << optopt << endl;
			exit(1);
			break;
		default:
			cerr << "usage: " << endl
				<< argv[0] << " -f <input-file>\n" <<   endl ;
			exit(0);
		}
		if(fname_flag==1){
			break;
		}
	}
	if(!fname_flag){
		cout << "usage: " 
			<< endl
			<< argv[0] << " -f <input-file> "  << endl << endl;
		exit(0);
	}
	active_scope=new scope();
	active_scope_list.push_back(active_scope);

	FILE * yyin = fopen(fname.c_str(), "r");
	if(!yyin){
		cerr << " Unable to open: " << fname << " for read ... exiting" << endl;
		exit(1);
	}
	yyrestart(yyin);
	if( !yyparse() && !no_errors){
		cout << "Input parsed sucessfully: generating code" << endl;
		//data_entry_loop();
		qscript_parser::generate_code();
	} else {
		cerr << "There were : " << no_errors << " errors in parse" << endl;
	}
	return no_errors;
}
