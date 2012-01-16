GENERATED_SOURCE = random_data_order.tab.h random_data_order.tab.c random_data_order_lex.c

OBJS = random_data_order_lex.o random_data_order.tab.o new_named_range.o AbstractStatement.o

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

new_named_range.o: new_named_range.cpp new_named_range.h
	g++ -fpermissive -c $<

AbstractStatement.o: AbstractStatement.cpp AbstractStatement.h
	g++ -c $<

clean:
	rm $(GENERATED_SOURCE)
