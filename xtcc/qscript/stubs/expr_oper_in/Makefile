expr_oper_in: expr.tab.c expr.tab.h lex.yy.c range_set.h expr.o stmt.o xtcc_set.o
	g++ -o expr_oper_in expr.tab.c lex.yy.c  expr.o stmt.o xtcc_set.o

expr.tab.c expr.tab.h: expr.y
	bison -d expr.y

lex.yy.c: lex.l
	flex lex.l

expr.o: expr.h expr.C
	g++ -c expr.C

stmt.o: stmt.h stmt.C
	g++ -c stmt.C

xtcc_set.o: xtcc_set.C
	g++ -c xtcc_set.C
