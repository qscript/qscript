
qscript-console.exe: qscript-console.o
	g++ -o $@ $< -lwthttp -lwt -lboost_signals

qscript-console.o: qscript-console.C
	g++ -c $<
