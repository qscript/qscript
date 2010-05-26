CC=$(CXX)
AM_CXXFLAGS= -Wall -Weffc++ -frepo -g
AM_YFLAGS= -d -v
bin_PROGRAMS=qscript
qscript_SOURCES= q.ypp lex.l  debug_mem.C expr.C main.C named_range.C qscript_parser.C question.C scope.C stmt.C stmt_common.C symtab.C utils.C xtcc_set.C const_defs.h debug_mem.h expr.h named_attributes.h named_range.h qscript_lib.h qscript_parser.h question_disk_data.h question.h scope.h stmt.h stub_pair.h symtab.h utils.h xtcc_set.h data_entry.ypp scan_data.l user_navigation.h

#q.cpp q.h : q.y
#	bison -d q.y -o q.cpp
#	mv q.hpp q.h

lex.cpp: q.y
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


BUILT_SOURCES=q.h q.cpp lex.c scan_data.cpp data_entry.h data_entry.cpp
EXTRA_DIST= inp QScriptMakefile qscript_lib.C qscript_lib.h qscript_data.y qscript_data.l
#dist_pkgdata_DATA=stubs/main_loop.C stubs/list_summ_template.C stubs/iso_types.h docs/manual.texi docs/qscript_doc.html
#AUTOMAKE_OPTIONS = dejagnu
#DIST_SUBDIRS=test-inputs testsuite testsuite/config testsuite/qscript.test testsuite/qscript.test/config testsuite/qscript.test/qscript 

qscript_LDADD=@LEXLIB@

.phony: clean
clean:
	rm *.o *.rpo
