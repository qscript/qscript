hello-gettext.pot: hello-gettext.c
	xgettext -d my_gettext_hello -s -o hello-gettext.pot hello-gettext.c

hello-gettext.exe: hello-gettext.c
	gcc -o $@ -DLOCALEDIR=\"/usr/share/locale\" $<


