scan_data.exe: scan_data.l data_entry.ypp
	flex --bison-bridge  scan_data.l
	bison -p scan_data data_entry.ypp
	g++ -g data_entry.tab.cpp lex.scan_data.c  qscript_readline.cpp  -lncurses -lpanel -o $@
