#include "cwd-sys.h"		// See tutorial 2.
#include "cwd-debug.h"

int main(void)
{
  Debug( libcw_do.on() );
  Debug( dc::malloc.on() );
  Debug( dc::bfd.on() );

  Debug( list_allocations_on(libcw_do) );
  int* p = new int [100];

  return 0;
}
