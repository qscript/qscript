g++ -g -o vegetable_gtk.exe -I ../include -L ../lib vegetable_gtk.C `pkg-config --libs --cflags gtk+-2.0` -lqscript_runtime -lncurses -lpanel -lwt

