CC=$(CXX)
AM_CXXFLAGS= -Wall -Weffc++ -frepo -g 
AM_YFLAGS= -d -v
SOURCE_DIR=src
BUILD_DIR=automake-build-dir
bin_PROGRAMS= qscript
qscript_SOURCES= q.ypp lex.l debug_mem.cpp expr.cpp main.cpp named_range.cpp qscript_parser.cpp question.cpp scope.cpp stmt.cpp stmt_common.cpp symtab.cpp utils.cpp xtcc_set.cpp const_defs.h debug_mem.h expr.h named_attributes.h named_range.h qscript_lib.h qscript_parser.h question_disk_data.h question.h scope.h stmt.h stub_pair.h symtab.h utils.h xtcc_set.h data_entry.ypp scan_data.l user_navigation.h

#$(BUILD_DIR)/%.o: %.C
#	$(CC) -$(AM_CXXFLAGS) -c $<

#q.cpp q.h : q.y
#	bison -d q.y -o q.cpp
#	mv q.hpp q.h

q.cpp q.h: q.ypp

lex.cpp: lex.l q.ypp 
	flex -o $@ $<

data_entry.cpp: AM_YFLAGS = -p scan_data -d 
data_entry.cpp data_entry.h: data_entry.ypp
	echo $@
	bison -d -p scan_data $< -o $@
#mv data_entry.hpp data_entry.h

#scan_data.c: scan_data.l
#scan_data.c: data_entry.y scan_data.l

scan_data.cpp: scan_data.l data_entry.ypp
	flex -o $@ $< 


#mv lex.scan_data.c scan_data.c


BUILT_SOURCES=q.h q.cpp lex.cpp scan_data.cpp data_entry.h data_entry.cpp
EXTRA_DIST= inp QScriptMakefile qscript_lib.cpp qscript_lib.h qscript_data.y qscript_data.l
#dist_pkgdata_DATA=stubs/main_loop.C stubs/list_summ_template.C stubs/iso_types.h docs/manual.texi docs/qscript_doc.html
#AUTOMAKE_OPTIONS = dejagnu
#DIST_SUBDIRS=test-inputs testsuite testsuite/config testsuite/qscript.test testsuite/qscript.test/config testsuite/qscript.test/qscript 



qscript_LDADD=@LEXLIB@

#.phony: clean
#clean:
#	rm $(BUILD_DIR)/*.o $(BUILD_DIR)/*.rpo $(BUILD_DIR)/qscript 
