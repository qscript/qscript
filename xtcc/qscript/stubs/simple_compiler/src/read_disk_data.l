%{

#include "const_defs.h"
#include "qscript_data.hpp"
#include "question_disk_data.h"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>

	using namespace std;
	//void read_disk_dataerror(const char * s);
	//int line_no;
	//extern int no_errors;
	int read_disk_dataparse(yyscan_t yyscanner, 
		std::map <string, question_disk_data*>* qdd_map_ptr,
		std::vector<int>* data_ptr,
		vector<int>* array_index_list_ptr);
	int read_disk_datalex (YYSTYPE * yylval_param, yyscan_t yyscanner);

%}
%option never-interactive
%option noyywrap
%option prefix="read_disk_data"
%option reentrant 
%option bison-bridge
%option header-file="read_disk_data_flex_prototypes.h"
%option nounput


%%

[0-9]+	{
	//read_disk_datalval.ival = atoi(read_disk_datatext);
	yylval_param->ival = atoi(yytext);
	//cout << "got INUMBER" << endl; 
	return INUMBER;
}

\n {
	//cout << "got NEWL" << endl;
	return NEWL;
}

":"	{
	//cout << "got COLON" << endl;
	return COLON;
}

"$" 	{
	return DOLLAR;
}

[ \t]+	; /* ignore */

BOUNDS {
	return BOUNDS;
}

[_A-Za-z][A-Za-z0-9_]*	{
	//if(read_disk_dataleng < MY_STR_MAX) 
	if(yyleng < MY_STR_MAX) {
		//strcpy(read_disk_datalval.name,read_disk_datatext);
		strcpy(yylval_param->name, yytext);
		//cout << "got name" << endl;
		return NAME;
	} else {
		//printf("TEXT TOKEN too long... exiting lexer\n");
		exit(1);
	}
}

%%

	void read_disk_dataerror (yyscan_t scanner, 
		map <string, question_disk_data*>* qdd_map_ptr,
		vector<int>* data_ptr,
		vector<int>* array_index_list_ptr,
		const char * s)
	{
		//++no_errors;
	 	//printf("%s: line: %d: read_disk_datatext: %s\n", s, line_no, read_disk_datatext  );
		//printf("no_errors: %d\n", no_errors);
	}

#if 0
int read_disk_datawrap(){
	return 1;
}
#endif 
