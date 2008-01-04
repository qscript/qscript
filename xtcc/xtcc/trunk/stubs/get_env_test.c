#include <stdlib.h>
#include <stdio.h>

int main(){
	char * ptr_HOME = getenv("HOME");
	printf("Home dir is: %s\n", ptr_HOME);
	return 0;
}
