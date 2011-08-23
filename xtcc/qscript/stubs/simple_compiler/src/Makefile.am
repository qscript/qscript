CC=$(CXX)
AM_CXXFLAGS= -Wall -Weffc++ -frepo -Wno-sign-compare -g 
AM_YFLAGS= -d -v
SOURCE_DIR=src
BUILD_DIR=automake-build-dir
bin_PROGRAMS= qscript
qscript_SOURCES= AbstractStatement.cpp code_gen_utils.cpp config_parser.cpp \
		 debug_mem.cpp expr.cpp LatexDoc.cpp \
		 log_mesg.cpp main.cpp named_attributes.cpp named_range.cpp \
		 qscript_debug.cpp qscript_parser_common.cpp \
		 qscript_parser.cpp qscript_readline.cpp \
		 qtm_datafile_conf_parser.cpp \
		 QuestionAttributes.cpp question_common.cpp \
		 question.cpp scope.cpp stmt.cpp \
		 symtab.cpp TempNameGenerator.cpp utils_common.cpp \
		 utils.cpp xtcc_set.cpp  \
		 data_entry.ypp qscript_conf.ypp \
		 qtm_datafile_conf.ypp q.ypp  \
		 lex.l qscript_conf_lex.l qtm_datafile_conf_lex.l scan_data.l

#$(BUILD_DIR)/%.o: %.C
#	$(CC) -$(AM_CXXFLAGS) -c $<

#q.cpp q.h : q.y
#	bison -d q.y -o q.cpp
#	mv q.hpp q.h

#q.cpp q.h: q.ypp

#lex.cpp: lex.l q.ypp 
#	flex -o $@ $<

%.cpp : %.l
	flex -o$@ $<

%.cpp %.hpp: %.ypp
	echo "building parser from ypp target : $@ YFLAGS: $(YFLAGS)"
	bison $(AM_YFLAGS) -v -d $< -o $(basename $@).cpp

data_entry.cpp: AM_YFLAGS = -p scan_data -d -v
data_entry.hpp: AM_YFLAGS = -p scan_data -d -v
#data_entry.cpp data_entry.h: data_entry.ypp
#	echo $@
#	bison -d -p scan_data $< -o $@

#scan_data.cpp: scan_data.l data_entry.ypp
#	flex -o $@ $< 



qscript_data.cpp: AM_YFLAGS = -p read_disk_data -d -v
qscript_data.hpp: AM_YFLAGS = -p read_disk_data -d -v

qscript_conf.cpp: AM_YFLAGS = -p qscript_conf -d -v
qscript_conf.hpp: AM_YFLAGS = -p qscript_conf -d -v

qtm_datafile_conf.hpp: AM_YFLAGS = -p qtm_datafile_conf_ -d -v
qtm_datafile_conf.cpp: AM_YFLAGS = -p qtm_datafile_conf_ -d -v



BUILT_SOURCES=q.hpp q.cpp lex.cpp scan_data.cpp data_entry.hpp data_entry.cpp qtm_datafile_conf.cpp qtm_datafile_conf.hpp
EXTRA_DIST= inp QScriptMakefile qscript_lib.cpp qscript_lib.h qscript_data.y qscript_data.l
#dist_pkgdata_DATA=stubs/main_loop.C stubs/list_summ_template.C stubs/iso_types.h docs/manual.texi docs/qscript_doc.html
#AUTOMAKE_OPTIONS = dejagnu
#DIST_SUBDIRS=test-inputs testsuite testsuite/config testsuite/qscript.test testsuite/qscript.test/config testsuite/qscript.test/qscript 



qscript_LDADD=@LEXLIB@

#.phony: clean
#clean:
#	rm $(BUILD_DIR)/*.o $(BUILD_DIR)/*.rpo $(BUILD_DIR)/qscript 
