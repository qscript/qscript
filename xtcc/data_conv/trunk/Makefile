conv: main.o x86_format.o global.o
	g++ main.o x86_format.o global.o -lboost_filesystem -o conv

main.o: main.cpp Format.h Type.h RecordMap.h
	g++ -c main.cpp -o main.o

global.o: global.cpp Format.h Type.h
	g++ -c global.cpp -o global.o

x86_format.o: x86_format.cpp Format.h
	g++ -c x86_format.cpp -o x86_format.o
	
.PHONY: clean

clean:
	rm conv
	rm *.o

