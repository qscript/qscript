BUILT_SOURCES=read_data.c gram.c gram.h

CODE_ASSISTANT_SOURCES = util.cpp read_sentiment.cpp



code_assistant.exe: $(CODE_ASSISTANT_SOURCES)
	g++ --std=c++0x -o $@ $(CODE_ASSISTANT_SOURCES)

analyzer.exe: $(BUILT_SOURCES)
	g++ -std=c++0x -o $@  $(BUILT_SOURCES)



read_data.c: read_data.l gram.h
	flex -o$@ $<

gram.h gram.c: gram.y
	bison -d gram.y  -o gram.c



