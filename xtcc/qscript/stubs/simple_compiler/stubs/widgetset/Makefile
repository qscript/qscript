CFLAGS = -c -g -Wall -Wno-sign-compare -Weffc++

OBJS = WCodeMirror.o qscript-console2.o

qscript-console2.exe: $(OBJS)
	g++ -g -o $@ $(OBJS) -lwthttp -lwt -lboost_signals

WCodeMirror.o: WCodeMirror.cpp WCodeMirror.h
	g++ $(CFLAGS) -g -c $<

qscript-console2.o: qscript-console2.cpp 
	g++ $(CFLAGS) -g -c $<

