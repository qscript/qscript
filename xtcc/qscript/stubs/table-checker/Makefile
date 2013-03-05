

GENERATED_SOURCES = freq_file.c freq_file.h lex.yy.c

table-checker.exe: $(GENERATED_SOURCES)
	g++ $(GENERATED_SOURCES) -o $@

freq_file.c freq_file.h : freq_file.y const_defs.h
	bison -d freq_file.y -o freq_file.c

lex.yy.c: lex.l const_defs.h
	flex $<

