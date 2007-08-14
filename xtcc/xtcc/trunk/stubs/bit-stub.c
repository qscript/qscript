#include <stdio.h>

int main(){
	int i;
	for (i=0; i<8; i++){
		printf("%x,", 1<<i);
		printf("%d\n", 1<<i);
	}
}
