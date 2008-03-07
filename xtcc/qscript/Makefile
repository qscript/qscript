

SOURCES = qscript.tab.c lex.yy.c
qscript.exe: $(SOURCES)
	g++ -o $@ $(SOURCES)


lex.yy.c: lex.l qscript.tab.h const_defs.h qscript_types.h
	flex lex.l

qscript.tab.c: qscript.y const_defs.h qscript_types.h
	bison -d -v qscript.y
	
