%{

#include "const_defs.h"
#include "qscript_data.tab.h"
#include <iostream>
	using namespace std;
	void yyerror(const char * s);
	int line_no;
	extern int no_errors;

%}


%%

[0-9]+	{
	yylval.ival = atoi(yytext);
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

[ \t]+	; /* ignore */

[_A-Za-z][A-Za-z0-9_]*	{
	if(yyleng < MY_STR_MAX) {
		strcpy(yylval.name,yytext);
		//cout << "got name" << endl;
		return NAME;
	} else {
		//printf("TEXT TOKEN too long... exiting lexer\n");
		exit(1);
	}
}

%%

	void yyerror(const char * s){
		++no_errors;
	 	printf("%s: line: %d: yytext: %s\n", s, line_no, yytext  );
		printf("no_errors: %d\n", no_errors);
	}

int yywrap(){
	return 1;
}
