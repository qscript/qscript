OBJS=main_loop.o edit_out.o

SOURCES=main_loop.C edit_out.c

my_edit.exe: $(OBJS)
	g++ $(OBJS) -o $@

main_loop.o: main_loop.C
	g++ -c $<

edit_out.o: edit_out.c
	g++ -c $<
