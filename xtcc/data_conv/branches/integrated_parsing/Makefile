conv: main.o x86_format.o global.o parse.o
	g++ -L./lib/ -lqscript_runtime -lreadline -lboost_filesystem $^ -o conv

main.o: main.cpp Format.h Type.h RecordMap.h
	g++ -c $< -o $@

global.o: global.cpp Format.h Type.h
	g++ -c $< -o $@

x86_format.o: x86_format.cpp Format.h
	g++ -c $< -o $@

parse.o: parse.cpp
	g++ -c $< -o $@

.PHONY: clean

clean:
	rm -f conv *.o

