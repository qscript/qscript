CPPFLAGS = -g
OBJS = qscript_lib.o read_disk_data.o qscript_data.o AbstractStatement.o \
	qscript_debug.o new_named_range.o


qscript_lib_test.exe: $(OBJS)
	g++ $(CPPFLAGS) -o $@ $(OBJS)

qscript_lib.o: qscript_lib.cpp qscript_lib.h qscript_data.hpp
	g++ $(CPPFLAGS) -DTEST_RANDOM_PARSER -c $<

qscript_data.hpp qscript_data.cpp: qscript_data.ypp
	bison -p read_disk_data  -v -d $< -o $(basename $@).cpp


read_disk_data.cpp: read_disk_data.l
	flex -o$@ $<

qscript_data.o: qscript_data.cpp
	g++ $(CPPFLAGS) -c $<
	
read_disk_data.o: read_disk_data.cpp
	g++ $(CPPFLAGS) -c $<

AbstractStatement.o: AbstractStatement.cpp AbstractStatement.h
	g++ $(CPPFLAGS) -c $<

qscript_debug.o: qscript_debug.cpp qscript_debug.h
	g++ $(CPPFLAGS) -c $<

new_named_range.o: new_named_range.cpp new_named_range.h
	g++ $(CPPFLAGS) -c $<

.PHONY: clean 

clean:
	-rm -f *.o
