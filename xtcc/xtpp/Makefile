preproc: xtpp.l xtpp.y
	bison -d xtpp.y
	flex xtpp.l
#g++ -o $@ y.tab.c lex.yy.c -ll 
	g++ -o $@ y.tab.c lex.yy.c 
