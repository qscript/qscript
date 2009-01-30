%{

#include "common.h"
#include "stmt.h"
#include <string>
#include <iostream>
	using std::string;
	void print_err(compiler_err_category cmp_err, 
		string err_msg, int line_no, int compiler_line_no, string compiler_file_name);
	extern int line_no;

	question_type q_type;
#include "const_defs.h"
#include "xtcc_set.h"
	int no_mpn=0;
	xtcc_set xs;
	int yylex();
	void yyerror(const char * s);
	int no_errors;

	struct stmt* tree_root=0;
#include <vector>
	vector <q_stmt*> q_list;
	void generate_code();

%}


%union {
	int ival;
	char name[MY_STR_MAX];
	char text_buf[MY_STR_MAX];
	datatype dt;
	struct stmt * stmt;
	//class question* ques;
};

%token <ival> INUMBER
%token <name> NAME
%token <text_buf> TEXT
%token SP
%token MP
%token <dt> VOID_T
%token <dt> INT8_T
%token <dt> INT16_T
%token <dt> INT32_T
%token <dt> FLOAT_T
%token <dt> DOUBLE_T
%token <dt> STRING_T
%type <dt> datatype
%type <stmt> question
%type <stmt> stmt
%type <stmt> stmt_list



%%


prog: stmt_list {
		tree_root=$1;
		while(tree_root->prev) 
			tree_root=tree_root->prev;
	}
	;

stmt_list: stmt {
		   $$=$1;
	}
	| stmt_list stmt{
		$1->next=$2;
		$2->prev=$1;
		$$=$2;
	}
	;

stmt:	question
	;

	/*
	question_list: question {
		$$=$1;
	}
	| question_list question {
		$1->next=$2;
		$2->prev=$1;
		$$=$2;
	}
	;
	*/

question: NAME TEXT qtype datatype range_allowed_values ';' {
		string name($1);
		string q_text($2);
		datatype dt=$4;
		q_stmt* q= new q_stmt(line_no, name, q_text, q_type, no_mpn, dt, xs);
		$$=q;
		q_list.push_back(q);
	  }
	;

qtype: SP { q_type = spn; }
	| MP '(' INUMBER ')' { q_type = mpn; no_mpn = $3; }
	;

datatype: INT8_T
	|INT16_T
	|INT32_T  	
	|FLOAT_T
	|DOUBLE_T
	|STRING_T
	;

range_allowed_values:  '(' range_list ')' { }
	;


range_list: range
	| range_list ',' range
	;

range: 	INUMBER '-' INUMBER {
		if($3<=$1){
			print_err(compiler_sem_err, "2nd number in range <= 1st number",
					line_no, __LINE__, __FILE__  );

		} else {
			xs.range.push_back( pair<int,int>($1,$3));
		}
	}
	|	INUMBER {
		xs.indiv.insert($1);
	}
	;


%%

#include <unistd.h>
#include <string>
extern void yyrestart ( FILE *input_file );

void data_entry_loop();

using std::string;
int main(int argc, char* argv[]){
	int opterr=1, c;
	string fname;
	int fname_flag=0;
	
	while( (c=getopt(argc, argv, "f:"))!=-1 ){
		char ch=optopt;
		cout << "ch: " << ch << endl;
		switch(c){
		case 'f':
			fname=optarg;
			fname_flag=1;
			cout << " got fname: " << fname << endl;
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
	FILE * yyin = fopen(fname.c_str(), "r");
	if(!yyin){
		cerr << " Unable to open: " << fname << " for read ... exiting" << endl;
		exit(1);
	}
	yyrestart(yyin);
	if( !yyparse()){
		cout << "Input parsed sucessfully: starting interpreter" << endl;
		//data_entry_loop();
		generate_code();
	} else {
		cerr << "There were : " << no_errors << " in parse" << endl;
	}
	return no_errors;
}

#include <string>
using std::string;
void print_err(compiler_err_category cmp_err, string err_msg, 
	int line_no, int compiler_line_no, string compiler_file_name){
	++no_errors;
	cerr << "xtcc " ;
	switch(cmp_err){
		case compiler_syntax_err: 
			cerr << "syntax error: ";
		break;
		case compiler_sem_err:
			cerr << "semantic error: ";
		break;
		case compiler_internal_error:
			cerr << "compiler internal error: " ;
		break;	
		default:
			cerr << "internal compiler error - error code category missing in switch statement: compiler file: " 
				<< __FILE__ << " compiler src code lineno: " << __LINE__ << endl;
			
	}
	cerr << " line_no: " << line_no << " "<< err_msg << ", compiler line_no: " 
		<< compiler_line_no << ", compiler_file_name: " << compiler_file_name << endl;
}

#include <sstream>
void data_entry_loop(){
	int ser_no;
	cout << "Enter Serial No (0) to exit: " << flush;
	cin >> ser_no;
	string jno="j_1001";
	while(ser_no!=0){
		stringstream fname_str;
		fname_str << jno << "_" << ser_no << ".dat";
		FILE * fptr = fopen(fname_str.str().c_str(), "w+b");
		tree_root->eval();
		cout << "Enter Serial No (0) to exit: " << flush;
		cin >> ser_no;
		for (int i=0; i<q_list.size(); ++i){
			fprintf(fptr, "%s: ", q_list[i]->name.c_str());
			for( set<int>::iterator iter=q_list[i]->input_data.begin();
					iter!=q_list[i]->input_data.end(); ++iter){
				fprintf(fptr, "%d ", *iter);
			}
			fprintf(fptr, "\n");
		}
		fclose(fptr);
	} 
}
void print_header(FILE* script);
void print_close(FILE* script);
void generate_code(){
	string script_name("test_script.c");
	FILE * script = fopen(script_name.c_str(), "w");
	if(!script){
		cerr << "unable to open output file to dump script data: " << script_name << endl;
		exit(1);
	}
	print_header(script);
	tree_root->generate_code(script);
	print_close(script);
}

void print_header(FILE* script){
	fprintf(script, "#include <iostream>\n");
	fprintf(script, "#include <vector>\n");
	fprintf(script, "#include <string>\n");
	fprintf(script, "#include <sstream>\n");
	fprintf(script, "#include \"stmt.h\"\n");
	fprintf(script, "#include \"xtcc_set.h\"\n");

	fprintf(script, "using namespace std;\n");
	fprintf(script, "void read_data(const char * prompt);\n");
	fprintf(script, "extern vector<int> data;\n");
	fprintf(script, "int main(){\n");

	fprintf(script, "\tint ser_no;\n");
	fprintf(script, "\t\tcout << \"Enter Serial No (0) to exit: \" << flush;\n");
	fprintf(script, "\t\tcin >> ser_no;\n");
	fprintf(script, "\t\tstring jno=\"j_1001\";\n");
	fprintf(script, "\t\twhile(ser_no!=0){\n");
	fprintf(script, "\t\t\tstringstream fname_str;\n");
	fprintf(script, "\t\t\tfname_str << jno << \"_\" << ser_no << \".dat\";\n");
	fprintf(script, "\t\t\tFILE * fptr = fopen(fname_str.str().c_str(), \"w+b\");\n");

}

void print_close(FILE* script){
	fprintf(script,	"cout << \"Enter Serial No (0) to exit: \" << flush;\n");
	fprintf(script, "cin >> ser_no;\n");
	fprintf(script, "\n} /* close while */\n");
	fprintf(script, "\n} /* close main */\n");
}
