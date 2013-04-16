


// These four lines should actually be part of a custom "sys.h" file.  See tutorial 2.
#ifndef _GNU_SOURCE                     // Already defined by g++ 3.0 and higher.
#define _GNU_SOURCE                     // This must be defined before including <libcwd/sys.h>
#endif
#include <libcwd/sys.h>                 // This must be the first header file
// This line should actually be part of a custom "debug.h" file.  See tutorial 2.
#include <libcwd/debug.h>

int main(void)
{
  Debug( dc::notice.on() );             // Turn on the NOTICE Debug Channel.
  Debug( libcw_do.on() );               // Turn on the default Debug Object.

  Dout(dc::notice, "Hello World");

  return 0;
}
