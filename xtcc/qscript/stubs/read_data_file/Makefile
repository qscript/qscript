
read_data: qscript_data.y qscript_data.l question_disk_data.h
	flex qscript_data.l
	bison -d qscript_data.y
	g++ -o read_data qscript_data.tab.c lex.yy.c
