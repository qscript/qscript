inp_combined_bcpp.exe: inp_combined_bcpp.C
	g++ -I ../include -L ../lib inp_combined_bcpp.C -lqscript_runtime -lpanel -lncurses -o inp_combined_bcpp.exe -lmicrohttpd
