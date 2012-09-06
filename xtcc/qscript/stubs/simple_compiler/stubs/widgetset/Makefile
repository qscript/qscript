OBJS = WCodeMirror.o qscript-console2.o

qscript-console2.exe: $(OBJS)
	g++ -g -o $@ $(OBJS) -lwthttp -lwt -lboost_signals

WCodeMirror.o: WCodeMirror.cpp WCodeMirror.h
	g++ -c $<

qscript-console2.o: qscript-console2.cpp
	g++ -g -c $<

