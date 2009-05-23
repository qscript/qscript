CC=$(CXX)
AM_CXXFLAGS= -Wall -Weffc++ -frepo 
AM_YFLAGS= -d -v
bin_PROGRAMS=qscript
qscript_SOURCES= q.y lex.l  debug_mem.C expr.C main.C named_range.C qscript_parser.C question.C scope.C stmt.C stmt_common.C symtab.C utils.C xtcc_set.C const_defs.h debug_mem.h expr.h named_attributes.h named_range.h qscript_lib.h qscript_parser.h question_disk_data.h question.h scope.h stmt.h stub_pair.h symtab.h utils.h xtcc_set.h data_entry.y scan_data.c

lex.c: q.y
#data_entry.c data_entry.h: data_entry.y 
#	bison -d -p scan_data $<
#	mv data_entry.tab.h data_entry.h
#	mv data_entry.tab.c data_entry.c

#scan_data.c: scan_data.l

scan_data.c: scan_data.l data_entry.y
	flex $<
	mv lex.scan_data.c scan_data.c
	flex $<


BUILT_SOURCES=q.h q.c lex.c
EXTRA_DIST= inp
#dist_pkgdata_DATA=stubs/main_loop.C stubs/list_summ_template.C stubs/iso_types.h docs/manual.texi docs/qscript_doc.html
#AUTOMAKE_OPTIONS = dejagnu
#DIST_SUBDIRS=test-inputs testsuite testsuite/config testsuite/qscript.test testsuite/qscript.test/config testsuite/qscript.test/qscript 

qscript_LDADD=@LEXLIB@

.phony: clean
clean:
	rm *.o *.rpo
