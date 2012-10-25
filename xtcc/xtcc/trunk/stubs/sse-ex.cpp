/*
 * =====================================================================================
 *
 *       Filename:  sse-ex.cpp
 *
 *    Description:  SSE Programming example  slight modification which compiles with g++ :
 *    URL       : http://www.rhinocerus.net/forum/lang-asm-x86/255298-how-do-you-do-inline-assembly-vector-types-gcc.html
 *        Created:  Tuesday 09 October 2012 11:50:19  IST
 *       Compiler:  gcc version 4.6.3 (Ubuntu/Linaro 4.6.3-1ubuntu5) 
 *
 *
 * =====================================================================================
 */

#include <stdio.h>
char sse2_array[16] __attribute__((aligned(16)));

int main() {
	unsigned long p;
	sse2_array[0] = 1;
	sse2_array[2] = 2;
	printf("%d %d\n", sse2_array[0], sse2_array[1]);
	asm volatile ("pxor %xmm0, %xmm0");
	asm volatile ("movdqa %%xmm0, %0" 
			: /*  outputs */ "=m" (sse2_array) 
			: /*  inputs */ 
			: /*  clobbered */ "xmm0"
			);
	printf("%d %d \n", sse2_array[0], sse2_array[1]);
	return 0;
}
