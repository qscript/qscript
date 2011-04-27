inp_combined_ncurses.exe: inp_combined_ncurses.C
	g++ -g -I ../include -L ../lib $< -lqscript_runtime -lpanel -lncurses -o $@ -lmicrohttpd

inp_combined_bcpp.exe: inp_combined_bcpp.C 
	g++ -g -I ../include -L ../lib inp_combined_bcpp.C -lqscript_runtime -lpanel -lncurses -o inp_combined_bcpp.exe -lmicrohttpd

