/*
 * =====================================================================================
 *
 *       Filename:  parallel_code.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 25 October 2012 11:20:22  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

//char flag_ban1 [] = { 65 };
char flag_ban1 [] = { 1 };
char flag_ban2 [] = { 1, 1 };
char flag_ban3 [] = { 1, 1, 1 };
char flag_ban4 [] = { 1, 1, 1, 1 };
char flag_ban5 [] = { 1, 1, 1, 1, 1 };
char flag_side2 [] = { 1, 1 };
char flag_side3 [] = { 1, 1, 1 };
//char flag_side4 [4]  = { 1, 0, 1, 0 };
char flag_side4 [4]  = { 1, 1, 1, 1 };
char flag_side5 [] = { 1, 1, 1, 1, 1 };
int counter_4_1 [] __attribute__ ((aligned(16))) = { 1, 2, 3, 4 };

#include <iostream>
using namespace std;

void tabulate_side4_ban1 ()
{
	if (flag_side4[0] && flag_ban1[0])
		++ counter_4_1[0];
	if (flag_side4[1] && flag_ban1[0])
		++ counter_4_1[1];
	if (flag_side4[2] && flag_ban1[0])
		++ counter_4_1[2];
	if (flag_side4[3] && flag_ban1[0])
		++ counter_4_1[3];
}

void tabulate_side4_ban1_parallel ()
{
	//if (flag_side4[0] && flag_ban1[0])
	//	++ counter_4_1[0];
	//if (flag_side4[1] && flag_ban1[0])
	//	++ counter_4_1[1];
	//if (flag_side4[2] && flag_ban1[0])
	//	++ counter_4_1[2];
	//if (flag_side4[3] && flag_ban1[0])
	//	++ counter_4_1[3];

	asm (
			"xor %%eax, %%eax\n\t"
			"xor %%ebx, %%ebx\n\t"
			"mov (%0), %%al\n\t"
			"mov %%al, %%ah\n\t"
			"mov %%ax, %%bx\n\t"
			"shl $16, %%eax\n\t"
			"or %%ebx, %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm0\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (flag_ban1)
			: /*  clobbered */ "rax", "xmm0", "rbx"
	    );

#if 0
	// see above: char flag_ban1 [] = { 65 };
	// use that to test that the flag is correctly replicated in all 4 positions
	char test[] __attribute__ ((aligned(16))) = {
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
	};
	asm (
			"movdqa %%xmm0, %0\n\t"
			: /*  outputs */ "=m" (test)
			: /*  inputs */ 
			: /*  clobbered */ 
	    );
	cout << "test: ";
	for (int i=0; i<16; ++i) {
		cout << " " << "|" << (int) test[i] << "|" ;
	}
	cout << endl;
#endif /*  0 */

	asm (
			"movd (%0), %%xmm1\n\t"
			//"pinsrd $0, %%eax, %%xmm1\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (flag_side4)
			: /*  clobbered */ "xmm1"
	    );

	asm (
    		"pmovsxbd %%xmm0, %%xmm2\n\t"
    		"pmovsxbd %%xmm1, %%xmm3\n\t"
		"pand %%xmm3, %%xmm2\n\t"
			: /*  outputs */
			: /*  inputs */ 
			: /*  clobbered */ "xmm2", "xmm3"
	    );
	asm (
		"movdqa (%0), %%xmm4\n\t"
		: /*  outputs */  
		: /*  inputs */ "r" (counter_4_1)
		: /*  clobbered */
	    );

	asm (
		"paddd %%xmm2, %%xmm4\n\t"
		"movdqa %%xmm4, %0\n\t"
		: /*  outputs */  "=m" (counter_4_1)
		: /*  inputs */
		: /*  clobbered */
	    );

	cout << "counter: ";
	for (int i=0; i<4; ++i) {
		cout << " " << "|" << (int) counter_4_1[i] << "|" ;
	}
	cout << endl;

}

void tabulate_side4_ban2 ()
{
	int counter [] = { 	0, 0, 0, 0, 
				0, 0, 0, 0 
	};

	int cols = 2;

	if (flag_side4[0] && flag_ban2[0])
		++ counter[0];
	if (flag_side4[1] && flag_ban2[0])
		++ counter[1];
	if (flag_side4[2] && flag_ban2[0])
		++ counter[2];
	if (flag_side4[3] && flag_ban2[0])
		++ counter[3];

	if (flag_side4[0] && flag_ban2[1])
		++ counter[1 * cols + 0];
	if (flag_side4[1] && flag_ban2[1])
		++ counter[1 * cols + 1];
	if (flag_side4[2] && flag_ban2[1])
		++ counter[1 * cols + 2];
	if (flag_side4[3] && flag_ban2[1])
		++ counter[1 * cols + 3];

}

void tabulate_side4_ban3 ()
{
	int counter [] = { 	
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0
	};

	int cols = 3;

	if (flag_side4[0] && flag_ban2[0])
		++ counter[0];
	if (flag_side4[1] && flag_ban2[0])
		++ counter[1];
	if (flag_side4[2] && flag_ban2[0])
		++ counter[2];
	if (flag_side4[3] && flag_ban2[0])
		++ counter[3];

	if (flag_side4[0] && flag_ban2[1])
		++ counter[1 * cols + 0];
	if (flag_side4[1] && flag_ban2[1])
		++ counter[1 * cols + 1];
	if (flag_side4[2] && flag_ban2[1])
		++ counter[1 * cols + 2];
	if (flag_side4[3] && flag_ban2[1])
		++ counter[1 * cols + 3];

	if (flag_side4[0] && flag_ban2[2])
		++ counter[2 * cols + 0];
	if (flag_side4[1] && flag_ban2[2])
		++ counter[2 * cols + 1];
	if (flag_side4[2] && flag_ban2[2])
		++ counter[2 * cols + 2];
	if (flag_side4[3] && flag_ban2[2])
		++ counter[2 * cols + 3];

}


void tabulate_side4_ban4 ()
{
	int counter [] = { 	
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0
	};

	int cols = 4;

	if (flag_side4[0] && flag_ban2[0])
		++ counter[0];
	if (flag_side4[1] && flag_ban2[0])
		++ counter[1];
	if (flag_side4[2] && flag_ban2[0])
		++ counter[2];
	if (flag_side4[3] && flag_ban2[0])
		++ counter[3];

	if (flag_side4[0] && flag_ban2[1])
		++ counter[1 * cols + 0];
	if (flag_side4[1] && flag_ban2[1])
		++ counter[1 * cols + 1];
	if (flag_side4[2] && flag_ban2[1])
		++ counter[1 * cols + 2];
	if (flag_side4[3] && flag_ban2[1])
		++ counter[1 * cols + 3];

	if (flag_side4[0] && flag_ban2[2])
		++ counter[2 * cols + 0];
	if (flag_side4[1] && flag_ban2[2])
		++ counter[2 * cols + 1];
	if (flag_side4[2] && flag_ban2[2])
		++ counter[2 * cols + 2];
	if (flag_side4[3] && flag_ban2[2])
		++ counter[2 * cols + 3];

	if (flag_side4[0] && flag_ban2[3])
		++ counter[3 * cols + 0];
	if (flag_side4[1] && flag_ban2[3])
		++ counter[3 * cols + 1];
	if (flag_side4[2] && flag_ban2[3])
		++ counter[3 * cols + 2];
	if (flag_side4[3] && flag_ban2[3])
		++ counter[3 * cols + 3];

}





int main()
{
	tabulate_side4_ban1_parallel ();

}

