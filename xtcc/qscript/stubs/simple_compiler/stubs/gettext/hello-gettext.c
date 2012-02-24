
#include <stdio.h>
#include <libintl.h>
#include <locale.h>
#define _(String) gettext (String)
#define gettext_noop(String) String
#define N_(String) gettext_noop (String)


int main()
{
	setlocale (LC_ALL, "");
	bindtextdomain ("my_gettext_hello", LOCALEDIR);
	textdomain("my_gettext_hello");
	return printf (gettext("Hello, World%s\n"), "neil");
}
