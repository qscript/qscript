#INCLUDE_DIR=c:\usr\include
#LIB_DIR=c:\usr\lib
#LINK_LIBS=-lregex

CC=g++ -g
HEADERS =  utils.h
COMMON_FILES = main.cpp
QSCRIPT_FREQ_PARSER_SOURCES = freq_file.y lex.l
QSCRIPT_FREQ_PARSER_GENERATED_SOURCES = gen_src/freq_file.c gen_src/freq_file.h gen_src/lex.yy.c

QTM_SOURCES =  lex_tab.l table_csv.y

QTM_QSCRIPT_FREQ_PARSER_SOURCES = gen_src/lex_tab.c gen_src/table_csv.c gen_src/table_csv.h
QTM_COMPILE_FILES = gen_src/lex_tab.c gen_src/table_csv.c


table-checker.exe: $(QSCRIPT_FREQ_PARSER_SOURCES) $(QSCRIPT_FREQ_PARSER_GENERATED_SOURCES) $(QTM_SOURCES) $(QTM_COMPILE_FILES) $(COMMON_FILES) $(HEADERS)
	$(CC) -o $@ $(QSCRIPT_FREQ_PARSER_GENERATED_SOURCES) $(QTM_COMPILE_FILES) $(COMMON_FILES)

qtm-csv-parser.exe: $(QTM_QSCRIPT_FREQ_PARSER_SOURCES)
	$(CC) $(QTM_COMPILE_FILES) -o $@ $(LINK_LIBS)

gen_src/lex_tab.c: lex_tab.l
	#flex -o$@ $<
	flex $<
	#mv lex_tab.h gen_src
	#mv lex_tab.c gen_src

gen_src/table_csv.c gen_src/table_csv.h: table_csv.y TableInfo.h
	bison -d $< -o table_csv.c
	mv table_csv.c table_csv.h gen_src

qscript-freq-parser.exe:  $(QSCRIPT_FREQ_PARSER_SOURCES) $(QSCRIPT_FREQ_PARSER_GENERATED_SOURCES)
	$(CC) $(QSCRIPT_FREQ_PARSER_GENERATED_SOURCES) -o $@

gen_src/freq_file.c gen_src/freq_file.h : freq_file.y const_defs.h
	bison -d freq_file.y -o freq_file.c
	mv freq_file.c freq_file.h gen_src

gen_src/lex.yy.c: lex.l const_defs.h
	flex -o$@ $<
	#mv lex.yy.c gen_src


