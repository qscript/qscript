SOURCES= lex.yy.c randomize.tab.c named_range.cpp AbstractStatement.cpp 

randomize: $(SOURCES)
	g++ $(SOURCES) -o $@

randomize.tab.c randomize.tab.h: randomize.y
	bison -d $<

lex.yy.c: lex.l
	flex $<
