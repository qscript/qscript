pdf_export: main.o
	g++ -L./lib/ -lqscript_compiletime -lreadline $^ -o $@

main.o: main.cpp
	g++ -c $< -o $@

.PHONY: clean

clean:
	rm -f pdf_export *.o

