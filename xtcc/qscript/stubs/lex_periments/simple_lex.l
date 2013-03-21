
	 int num_lines = 0, num_chars = 0;
	 enum {
	 NEWL=1,
	 ANOTHER_CHAR
	 };

%%

\n      { ++num_lines; ++num_chars; return NEWL; }
.       { ++num_chars; return ANOTHER_CHAR; }

%%

int  main() {
	while (yylex()) {

	};
	 //yylex();
	 printf( "# of lines = %d, # of chars = %d\n",
		 num_lines, num_chars );
}
