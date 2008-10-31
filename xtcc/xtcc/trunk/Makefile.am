CC=$(CXX)
AM_CXXFLAGS= -Wall -frepo 
AM_YFLAGS= -d -v
bin_PROGRAMS=xtcc
xtcc_SOURCES= tree.h Tab.h type.y lex.l expr.C tree.C scope.C  stmt.C  symtab.h  stmt.h expr.h scope.h symtab.C Tab.C const_defs.h generate_code.C main.C utils.h utils.C toplev_gram.y.inc expr_prec.y.inc expr.y.inc named_attributes.h named_range.h stub_pair.h
#BUILT_SOURCES=type.h type.c lex.c
EXTRA_DIST=stubs/sample2.map sample2.dat Makefile.borland Makefile.unix Makefile.manual testsuite/mk_data_visual_check.ods stubs/mk_data.C stubs/human_readable_data.csv RELEASE-NOTES ChangeLog
dist_pkgdata_DATA=stubs/main_loop.C stubs/list_summ_template.C stubs/iso_types.h docs/manual.texi docs/xtcc_doc.html
AUTOMAKE_OPTIONS = dejagnu
#DIST_SUBDIRS=test-inputs testsuite testsuite/config testsuite/xtcc.test testsuite/xtcc.test/config testsuite/xtcc.test/xtcc 

xtcc_LDADD=@LEXLIB@
type.y:  toplev_gram.y.inc expr_prec.y.inc expr.y.inc
	m4 toplev_gram.y.inc > type.y
#type.y: const_defs.h symtab.h tree.h stmt.h Tab.h expr.h scope.h
#lex.l: type.h const_defs.h symtab.h
#expr.C: expr.h tree.h
#tree.C: tree.h symtab.h stmt.h
#scope.C: scope.h tree.h stmt.h
#stmt.C: stmt.h tree.h symtab.h
#symtab.C: symtab.h tree.h expr.h
#Tab.C: Tab.h tree.h expr.h
.phony: clean
clean:
	rm *.o y.output y.tab.[hc] lex.yy.c dp a.out op op1 op.ind op.ind2 cscope.out ch3-04.output y.output y.tab.[hc] lex.yy.c err edit_out.c edit_out.ndg ofile hand_compile loop my_edit.exe my_loop temp.C.exe mk_data first Type_checker7.kdev* massif.* gmon.out myedit.exe rd_data Type_checker8.zip temp.C temp1.C op2 op.C op-mmap Type_checker7.tag read_op read_times dp-static tags mmap_op mmap_time Doxyfile global.C print_list_counts.C temp2.C my_axes.C my_axes_drv_func.C my_tab_drv_func.C my_table.C xtcc xtcc.exe *.rpo stubs/a.out xtcc_work/global.C xtcc_work/my_tab_drv_func.C xtcc_work/temp.C xtcc_work/my_axes.C xtcc_work/myedit.exe xtcc_work/my_axes_drv_func.C xtcc_work/.temp.C.swp xtcc_work/my_tab_summ.C xtcc_work/my_table.C xtcc_work/edit_out.c stubs/a.out
RUNTESTDEFAULTFLAGS = --tool xtcc --verbose XTCC=`pwd`/xtcc XTCC_TEST_DATA=`pwd`/sample2.dat --srcdir $$srcdir/testsuite

dist-hook:
	-cp -rp $(srcdir)/test-inputs $(top_distdir)
	-cp -rp $(srcdir)/testsuite $(top_distdir)
	-rm -rf `find $(top_distdir)/testsuite -name ".svn"`
	-rm -rf `find $(top_distdir)/test-inputs -name ".svn"`

