#HEADERS = AbstractStatement.h compiled_code.h const_defs.h datatype.h lex_location.h named_range.h randomize.tab.h stub_pair.h
HEADERS = AbstractStatement.h compiled_code.h const_defs.h datatype.h lex_location.h new_named_range.h randomize.tab.h stub_pair.h
SOURCES= lex.yy.c randomize.tab.c named_range.cpp AbstractStatement.cpp new_named_range.cpp

randomize.exe: $(SOURCES) $(HEADERS)
	g++ -fpermissive $(SOURCES) -o $@

randomize.tab.c randomize.tab.h: randomize.y
	bison -v -d $<

lex.yy.c: lex.l
	flex $<

#new_named_range.o: new_named_range.cpp new_named_range.h
#	g++ -fpermissive -c $<
