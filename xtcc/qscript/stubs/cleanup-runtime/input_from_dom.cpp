#include <emscripten.h>
#include<stdlib.h>
//#include <iostream>
#include <cstdio>

using namespace std;



#if 1
extern "C" {
void called_from_the_dom (char * data)
{
	//emscripten_pause_main_loop();
	//emscripten_resume_main_loop();
	//printf ("data from the browser dom callback: %s\n", data);
	printf ("hello called_from_the_dom\n");
	printf ("data: %s\n", data);
}
}

void my_main_loop()
{

	static int i = 0;
	printf (".");
	++i;
	if (i%80==0) {
		printf (":%d\n", i);
	}
}
#endif /* 0 */


void never() {
  int result = 0;
  //REPORT_RESULT();
}

#if 0
int main()
{
	//emscripten_set_main_loop(my_main_loop, 30, 1);
	printf ("finished\n");
	atexit(never); // should never be called - it is wrong to exit the runtime orderly if we have async calls!
	//cout << "finished" << endl;
}
#endif /* 0 */
