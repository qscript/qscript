#include <cstdio>
#include <cstdarg>

void eprintf (const char *stemplate, ...) __attribute__ ((format (printf, 1, 2)));

using namespace std;
int main(){
	eprintf("%s%s", "Hello, World", "\n");
	
}


   void
     eprintf (const char *stemplate, ...)
     {
       va_list ap;
       extern char *program_invocation_short_name;

       fprintf (stderr, "%s: ", program_invocation_short_name);
       va_start (ap, stemplate);
       vfprintf (stderr, stemplate, ap);
       va_end (ap);
     }

