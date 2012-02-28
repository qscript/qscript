#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	setlocale( LC_ALL, "" );
	bindtextdomain( "hello_gettext2", "/usr/share/locale" );
	textdomain( "hello_gettext2" );
	printf( gettext( "Hello, world!\n" ) );
	exit(0);
}
