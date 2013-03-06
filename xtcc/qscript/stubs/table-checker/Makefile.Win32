

GENERATED_SOURCES = freq_file.c freq_file.h lex.yy.c

QTM_SOURCES =  lex_tab.l table_csv.y

QTM_GENERATED_SOURCES = lex_tab.c table_csv.c table_csv.h
QTM_COMPILE_FILES = lex_tab.c table_csv.c

INCLUDE_DIR=c:\usr\include
LIB_DIR=c:\usr\lib
LINK_LIBS=-lregex


qtm-csv-parser.exe: $(QTM_GENERATED_SOURCES)
	g++ -I$(INCLUDE_DIR) -L$(LIB_DIR) $(QTM_COMPILE_FILES) -o $@ $(LINK_LIBS)

lex_tab.c: lex_tab.l
	flex -o$@ $<

table_csv.c table_csv.h: table_csv.y
	bison -d $< -o table_csv.c


table-checker.exe: $(GENERATED_SOURCES)
	g++ $(GENERATED_SOURCES) -o $@

freq_file.c freq_file.h : freq_file.y const_defs.h
	bison -d freq_file.y -o freq_file.c

lex.yy.c: lex.l const_defs.h
	flex $<

