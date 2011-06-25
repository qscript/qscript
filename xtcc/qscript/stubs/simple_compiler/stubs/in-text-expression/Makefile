
OBJS = lex.o simple_parser.o

test.exe: $(OBJS)
	g++ -o $@ $(OBJS)

lex.cpp: lex.l
	flex  -o $@ $<


simple_parser.cpp simple_parser.hpp: simple_parser.ypp const_defs.h
	bison -v -d $< -o $(basename $@).cpp

lex.o: lex.cpp

simple_parser.o: simple_parser.cpp simple_parser.hpp
	
