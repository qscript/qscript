OBJS = grid_ex1.o StubViewGridTable.o
#CFLAGS = -c -g -I src -Wall -Wno-sign-compare -Weffc++
CFLAGS = -c -g -Wall -Wno-sign-compare -Weffc++



grid_ex1.exe: $(OBJS)
	g++  `wx-config --cppflags` -o $@ $(OBJS) `wx-config --libs`

%.o:  %.cpp
	$(CC) $(CFLAGS) -o $@ $<


