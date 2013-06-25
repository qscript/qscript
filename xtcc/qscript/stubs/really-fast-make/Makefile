
really-fast-make.exe: gram.c lex.yy.c gram.h
	g++ gram.c lex.yy.c -o $@ -lfl 

gram.c gram.h: gram.y
	bison -d $< -o gram.c

lex.yy.c: lex.l gram.h
	flex $<
