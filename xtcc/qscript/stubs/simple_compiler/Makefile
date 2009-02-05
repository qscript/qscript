CC=g++ -c
LIBS=-lreadline

OBJS=lex.yy.o q.tab.o xtcc_set.o stmt.o data_entry.tab.o lex.scan_data.o expr.o symtab.o tree.o utils.o
simple_interpreter: $(OBJS)
	g++ -o simple_interpreter $(OBJS) $(LIBS)

lex.yy.o: lex.yy.c q.tab.h
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

expr.o: expr.C expr.h
	$(CC) $<

symtab.o: symtab.C symtab.h
	$(CC) $<

data_entry.tab.c data_entry.tab.h: data_entry.y	
	bison -d -p scan_data $<
	

lex.scan_data.c: try1.l
	flex $<

lex.scan_data.o: lex.scan_data.c data_entry.tab.h
	$(CC) $<

data_entry.tab.o: data_entry.tab.c
	$(CC) $<

tree.o: tree.C tree.h
	$(CC) $<
	
utils.o: utils.C utils.h
	$(CC) $<
