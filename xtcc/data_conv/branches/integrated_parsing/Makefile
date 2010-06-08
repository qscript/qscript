conv: main.o x86_format.o global.o parse.o
	g++ -g -L./lib/ -lqscript_compiletime -lboost_filesystem-mt -lreadline $^ -o conv

main.o: main.cpp Format.h Type.h RecordMap.h
	g++ -g -c $< -o $@

global.o: global.cpp Format.h Type.h
	g++ -g -c $< -o $@

x86_format.o: x86_format.cpp Format.h
	g++ -g -c $< -o $@

parse.o: parse.cpp
	g++ -g -c $< -o $@

.PHONY: clean

clean:
	rm -f conv *.o

