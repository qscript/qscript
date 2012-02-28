/*
 * =====================================================================================
 *
 *       Filename:  hello.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Monday 27 February 2012 04:51:10  GMT
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <libintl.h>
   #include <locale.h>
   #include <stdio.h>
   #include <stdlib.h>
   int main(void)
   {
     setlocale( LC_ALL, "" );
     bindtextdomain( "hello", "/usr/share/locale" );
     textdomain( "hello" );
      printf( gettext( "Hello, world!\n" ) );
      exit(0);
    }
