/home/nxd/Progs/xtcc/xtcc/qscript/stubs/simple_compiler/stubs/gettext>gcc hello.c                                
/home/nxd/Progs/xtcc/xtcc/qscript/stubs/simple_compiler/stubs/gettext> gcc hello-gettext2.c -o hello_gettext2                             
/home/nxd/Progs/xtcc/xtcc/qscript/stubs/simple_compiler/stubs/gettext>xgettext -d hello_gettext2 -s -o hello_gettext2.pot hello_gettext2.c
/home/nxd/Progs/xtcc/xtcc/qscript/stubs/simple_compiler/stubs/gettext>msginit -l hi_IN -o hindi.po -i hello_gettext2.pot                  
root@laptop:/usr/share/locale/hi/LC_MESSAGES# cp /home/nxd/Progs/xtcc/xtcc/qscript/stubs/simple_compiler/stubs/gettext/hello-gettext2.mo .
/home/nxd/Progs/xtcc/xtcc/qscript/stubs/simple_compiler/stubs/gettext>export LANGUAGE=hi_IN:hi
/home/nxd/Progs/xtcc/xtcc/qscript/stubs/simple_compiler/stubs/gettext>./hello_gettext2        
ह
/home/nxd/Progs/xtcc/xtcc/qscript/stubs/simple_compiler/stubs/gettext>




