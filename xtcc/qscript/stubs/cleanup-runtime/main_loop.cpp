#include <stdio.h>
#include <string.h>
#include <emscripten.h>

void called_from_the_dom (char * data)
{
	//emscripten_pause_main_loop();
	printf ("DOM called\n");
	//printf ("data from the browser dom callback: %s\n", data);
	//emscripten_resume_main_loop();
}

void main_loop()
{
	static int i = 0;
	printf (".");
	++i;
	if (i%80==0) {
		printf (":%d\n", i);
	}
}

int main()
{
	emscripten_set_main_loop (main_loop, 30, 1);
	printf ("finished\n");
}

