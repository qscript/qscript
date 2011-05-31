inp_newcard_bcpp.exe: inp_newcard_bcpp.C
	g++ -I ../include -L ../lib inp_newcard_bcpp.C -lqscript_runtime -lpanel -lncurses -o inp_newcard_bcpp.exe -lmicrohttpd
