%{

#include "const_defs.h"
#include "qscript_data.hpp"
#include <iostream>
#include <cstdlib>
	using namespace std;
	void read_disk_dataerror(const char * s);
	int line_no;
	extern int no_errors;

%}
%option noyywrap
%option prefix="read_disk_data"


%%

[0-9]+	{
	read_disk_datalval.ival = atoi(read_disk_datatext);
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
	if(read_disk_dataleng < MY_STR_MAX) {
		strcpy(read_disk_datalval.name,read_disk_datatext);
		//cout << "got name" << endl;
		return NAME;
	} else {
		//printf("TEXT TOKEN too long... exiting lexer\n");
		exit(1);
	}
}

%%

	void read_disk_dataerror(const char * s){
		++no_errors;
	 	printf("%s: line: %d: read_disk_datatext: %s\n", s, line_no, read_disk_datatext  );
		printf("no_errors: %d\n", no_errors);
	}

#if 0
int read_disk_datawrap(){
	return 1;
}
#endif 
