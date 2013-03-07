
COMMON_FILES = main.cpp
QSCRIPT_FREQ_PARSER_SOURCES = freq_file.y lex.l
QSCRIPT_FREQ_PARSER_GENERATED_SOURCES = freq_file.c freq_file.h lex.yy.c

QTM_SOURCES =  lex_tab.l table_csv.y

QTM_QSCRIPT_FREQ_PARSER_SOURCES = lex_tab.c table_csv.c table_csv.h
QTM_COMPILE_FILES = lex_tab.c table_csv.c

#INCLUDE_DIR=c:\usr\include
#LIB_DIR=c:\usr\lib
#LINK_LIBS=-lregex


table-checker.exe: $(QSCRIPT_FREQ_PARSER_SOURCES) $(QSCRIPT_FREQ_PARSER_GENERATED_SOURCES) $(QTM_SOURCES) $(QTM_COMPILE_FILES) $(COMMON_FILES)
	g++ $(QSCRIPT_FREQ_PARSER_GENERATED_SOURCES) $(QTM_COMPILE_FILES) $(COMMON_FILES) -o $@

qtm-csv-parser.exe: $(QTM_QSCRIPT_FREQ_PARSER_SOURCES)
	g++ $(QTM_COMPILE_FILES) -o $@ $(LINK_LIBS)

lex_tab.c: lex_tab.l
	flex $<

table_csv.c table_csv.h: table_csv.y
	bison -d $< -o table_csv.c

qscript-freq-parser.exe:  $(QSCRIPT_FREQ_PARSER_SOURCES) $(QSCRIPT_FREQ_PARSER_GENERATED_SOURCES)
	g++ $(QSCRIPT_FREQ_PARSER_GENERATED_SOURCES) -o $@

freq_file.c freq_file.h : freq_file.y const_defs.h
	bison -d freq_file.y -o freq_file.c

lex.yy.c: lex.l const_defs.h
	flex $<


