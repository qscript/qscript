#HEADERS = AbstractStatement.h compiled_code.h const_defs.h datatype.h lex_location.h named_range.h randomize.tab.h stub_pair.h
HEADERS = AbstractStatement.h compiled_code.h const_defs.h datatype.h lex_location.h new_named_range.h randomize.tab.h stub_pair.h
SOURCES= lex.yy.c randomize.tab.c named_range.cpp AbstractStatement.cpp 

randomize: $(SOURCES) $(HEADERS)
	g++ $(SOURCES) -o $@

randomize.tab.c randomize.tab.h: randomize.y
	bison -v -d $<

lex.yy.c: lex.l
	flex $<
