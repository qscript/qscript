CC=g++ -Weffc++ -c -g -frepo
LIBS=-lreadline

OBJS=lex.yy.o q.tab.o xtcc_set.o stmt.o data_entry.tab.o lex.scan_data.o expr.o symtab.o tree.o utils.o scope.o named_range.o question.o stmt_common.o main.o qscript_parser.o
SOURCES=debug_mem.h
simple_compiler: $(OBJS)
	g++ -g -Weffc++ -o simple_compiler $(OBJS) $(LIBS)

lex.yy.o: lex.yy.c q.tab.h
	$(CC) $<

lex.yy.c: lex.l
	flex $<

q.tab.c q.tab.h: q.y tree.h symtab.h stmt.h expr.h named_attributes.h named_range.h
	bison -v -d $<

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

tree.o: tree.C tree.h debug_mem.h
	$(CC) $<
	
utils.o: utils.C utils.h
	$(CC) $<

scope.o: scope.C scope.h
	$(CC) $<

named_range.o: named_range.C named_range.h
	$(CC) $<

question.o:  question.C question.h
	$(CC) $<

stmt_common.o:  stmt_common.C 
	$(CC) $<

main.o: main.C
	$(CC) $<


.phony: clean
clean:
	rm *.o simple_compiler test_script lex.yy.c  lex.scan_data.c data_entry.tab.h q.tab.c

test_script: inp simple_compiler
	simple_compiler -f inp
	make -f QScriptMakefile
	
qscript_parser.o: qscript_parser.C qscript_parser.h
	$(CC) $<
	
