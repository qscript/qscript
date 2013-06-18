#HEADERS = AbstractStatement.h compiled_code.h const_defs.h datatype.h lex_location.h named_range.h randomize.tab.h stub_pair.h
HEADERS = AbstractStatement.h compiled_code.h const_defs.h datatype.h lex_location.h new_named_range.h randomize.tab.h stub_pair.h
SOURCES= lex.yy.c randomize.tab.c named_range.cpp AbstractStatement.cpp new_named_range.cpp
OBJS =  lex.yy.o randomize.tab.o AbstractStatement.o new_named_range.o
CPP_FLAGS = -fpermissive

#randomize.exe: $(SOURCES) $(HEADERS)
randomize.exe: $(OBJS) $(HEADERS)
	g++ -fpermissive $(OBJS) -o $@

randomize.tab.c randomize.tab.h: randomize.y
	bison -v -d $<

randomize.tab.o: randomize.tab.c randomize.tab.h
	g++ -c  $(CPP_FLAGS) $<

lex.yy.c: lex.l
	flex $<

lex.yy.o: lex.yy.c
	g++ -c  $(CPP_FLAGS) $<

AbstractStatement.o: AbstractStatement.cpp AbstractStatement.h
	g++ -c  $(CPP_FLAGS) $<

new_named_range.o: new_named_range.cpp new_named_range.h
	g++ -c $(CPP_FLAGS) $<

#new_named_range.o: new_named_range.cpp new_named_range.h
#	g++ -fpermissive -c $<
