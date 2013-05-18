#include <cstdio>

extern "C" {

extern void loadScript(const char * s);
extern void loadScriptString(const char * s);
extern void emscripten_run_script(const char * s);

}

int main()
{
	FILE * fptr = fopen("jquery-1.9.1.js","rb");
	fseek (fptr, 0, SEEK_END);
	long length = ftell(fptr);
	char * jquery_1_9_1_js = new char[length+1];
	jquery_1_9_1_js[length]=0;
	fseek (fptr, 0, SEEK_SET);
	long n_read = fread (jquery_1_9_1_js, 1, length, fptr);
	printf ("length: %ld, n_read: %ld\n", length, n_read);
	//loadScript("jquery-1.9.1.js");
	loadScriptString(jquery_1_9_1_js);
	printf("finished call to loadScript jquery-1.9.1.js");
	emscripten_run_script("alert('hi');");
	emscripten_run_script("$(document).ready(function(){ $(\"p\").click(function(){ $(this).hide(); }); });");
	emscripten_run_script("alert('after calling jquery');");
	//printf ("%s\n", jquery_1_9_1_js);
	printf ("finished\n");

}
