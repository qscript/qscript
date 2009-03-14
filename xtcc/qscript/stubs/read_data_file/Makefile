
read_data: qscript_data.y qscript_data.l question_disk_data.h
	flex qscript_data.l
	bison -d -p read_disk_data qscript_data.y
	g++ -o read_data qscript_data.tab.c lex.read_disk_data.c
