xtpp: xtpp.l xtpp.y
	bison -d xtpp.y
	flex xtpp.l
#g++ -o $@ y.tab.c lex.yy.c -ll 
	g++ -o $@ xtpp.tab.c lex.yy.c 
