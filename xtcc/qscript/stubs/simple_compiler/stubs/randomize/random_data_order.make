GENERATED_SOURCE = random_data_order.tab.h random_data_order.tab.c random_data_order_lex.c

OBJS = random_data_order_lex.o random_data_order.tab.o

random_data_order_reader.exe: $(OBJS) random_data_order.tab.h
	g++ -o $@ $(OBJS)


random_data_order.tab.h random_data_order.tab.c: random_data_order.y
	bison -v -d $<

random_data_order_lex.o: random_data_order_lex.c
	g++ -c $<

random_data_order.tab.o: random_data_order.tab.c random_data_order.tab.h
	g++ -c $<

random_data_order_lex.c: random_data_order.l
	flex -o $@ $<

clean:
	rm $(GENERATED_SOURCE)
