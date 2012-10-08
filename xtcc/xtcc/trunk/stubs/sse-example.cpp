/*
 * =====================================================================================
 *
 *       Filename:  sse-example.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Monday 08 October 2012 06:49:03  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 *http://www.rhinocerus.net/forum/lang-asm-x86/255298-how-do-you-do-inline-assembly-vector-types-gcc.html
 *
 * =====================================================================================
 */

#include <stdio.h>
char sse2_array[64] __attribute__((aligned(16)));

int main() {
	unsigned long p;
	sse2_array[0] = 1;
	sse2_array[1] = 2;
	sse2_array[2] = 3;
	sse2_array[3] = 4;
	sse2_array[4] = 5;
	sse2_array[5] = 6;
	sse2_array[6] = 7;
	sse2_array[7] = 8;
	sse2_array[8] = 9;
	sse2_array[9] = 10;
	sse2_array[10] = 11;
	sse2_array[11] = 12;
	sse2_array[12] = 13;
	sse2_array[13] = 14;
	sse2_array[14] = 15;
	sse2_array[15] = 16;
	sse2_array[16] = 17;
	sse2_array[17] = 18;
	sse2_array[18] = 19;
	sse2_array[19] = 20;
	sse2_array[20] = 21;
	sse2_array[21] = 22;
	sse2_array[22] = 23;
	sse2_array[23] = 24;
	sse2_array[24] = 25;
	sse2_array[25] = 26;
	sse2_array[26] = 27;
	sse2_array[27] = 28;
	sse2_array[28] = 29;
	sse2_array[29] = 30;
	sse2_array[30] = 31;
	sse2_array[31] = 32;
	sse2_array[32] = 33;
	sse2_array[33] = 34;
	sse2_array[34] = 35;
	sse2_array[35] = 36;
	sse2_array[36] = 37;
	sse2_array[37] = 38;
	sse2_array[38] = 39;
	sse2_array[39] = 40;
	sse2_array[40] = 41;
	sse2_array[41] = 42;
	sse2_array[42] = 43;
	sse2_array[43] = 44;
	sse2_array[44] = 45;
	sse2_array[45] = 46;
	sse2_array[46] = 47;
	sse2_array[47] = 48;
	sse2_array[48] = 49;
	sse2_array[49] = 50;
	sse2_array[50] = 51;
	sse2_array[51] = 52;
	sse2_array[52] = 53;
	sse2_array[53] = 54;
	sse2_array[54] = 55;
	sse2_array[55] = 56;
	sse2_array[56] = 57;
	sse2_array[57] = 58;
	sse2_array[58] = 59;
	sse2_array[59] = 60;
	sse2_array[60] = 61;
	sse2_array[61] = 62;
	sse2_array[62] = 63;
	sse2_array[63] = 64;
	printf("%d %d\n", sse2_array[0], sse2_array[1]);
	asm volatile ("pxor %xmm0, %xmm0");
	asm volatile ("movdqa %%xmm0, %0" 
			: /*  outputs */ "=m" (sse2_array) 
			: /*  inputs */ 
			: /*  clobbered */ "xmm0"

			);
	// asm("movdqa %xmm0, %0" : : "M" (sse2_array));
	printf("%d %d \n", sse2_array[0], sse2_array[1]);
	for (int i=0; i<64; ++i) {
		printf ("sse2_array[%d] = %d\n",
				i,
				sse2_array[i]);
	}
	return 0;
}
