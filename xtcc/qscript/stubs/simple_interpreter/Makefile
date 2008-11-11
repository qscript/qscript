CC=g++ -c

OBJS=lex.yy.o q.tab.o xtcc_set.o stmt.o
simple_interpreter: $(OBJS)
	g++ -o simple_interpreter $(OBJS)

lex.yy.o q.tab.h: lex.yy.c
	$(CC) $<

lex.yy.c: lex.l
	flex $<

q.tab.c q.tab.h: q.y common.h
	bison -d $<

q.tab.o: q.tab.c
	$(CC) $<

xtcc_set.o: xtcc_set.C xtcc_set.h
	$(CC) $<

stmt.o: stmt.C stmt.h
	$(CC) $<
