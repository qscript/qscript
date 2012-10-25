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
//char flag_side4 [4]  = { 1, 1, 1, 1 };
//char flag_side4 [4]  = { 1, 0, 1, 0 };
//char flag_side4 [4]  = { 0, 1, 0, 1 };
char flag_side4 [4]  = { 0, 1, 1, 0 };
char flag_side5 [] = { 1, 1, 1, 1, 1 };
int counter_4_1 [] __attribute__ ((aligned(16))) = { 1, 2, 3, 4 };
int counter_4_2 [] __attribute__ ((aligned(16))) = { 
	1, 2, 3, 4,
	5, 6, 7, 8
};

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
			"movb (%0), %%al\n\t"
			"movb %%al, %%ah\n\t"
			"movw %%ax, %%bx\n\t"
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

void tabulate_side4_ban2_parallel ()
{
	char shuffle_mask_ban[] __attribute__ ((aligned(16)))
		= { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };
	char shuffle_mask_side[] __attribute__ ((aligned(16)))
		= { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };


	asm (
			"movdqa (%0), %%xmm1\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (shuffle_mask_ban)
			: /*  clobbered */ "xmm1"
	    );

	asm (
			"xor %%eax, %%eax\n\t"
			"movw (%0), %%ax\n\t"
			"pinsrw $0, %%eax, %%xmm0\n\t"
			"pshufb %%xmm1, %%xmm0\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (flag_ban2)
			: /*  clobbered */ "rax", "xmm0", "xmm1"
	    );
	// the banner conditions in xmm0

	asm (
			"movdqa (%0), %%xmm2\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (shuffle_mask_side)
			: /*  clobbered */ "xmm2"
	    );

	asm (
			"movd (%0), %%xmm3\n\t"
			"pshufb %%xmm2, %%xmm3\n\t"
			//"pinsrd $0, %%eax, %%xmm1\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (flag_side4)
			: /*  clobbered */ "xmm3"
	    );

	// side conditions in xmm3

	asm (
			"pand %%xmm3, %%xmm0\n\t"
			: /*  outputs */
			: /*  inputs */ 
			: /*  clobbered */ "xmm0"
	    );

	// all 8 conditions and'ed in one go, result in xmm0
	// extract the results 4 at a time
	asm (
			"pextrd $0, %%xmm0, %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm1\n\t"
    			"pmovsxbd %%xmm1, %%xmm2\n\t"
			: /*  outputs */
			: /*  inputs */ 
			: /*  clobbered */ "rax", "xmm2"
	    );

	// load the 1st 4 counter variables
	int * my_ptr __attribute__ ((aligned(16))) = counter_4_2;
	asm (
			"movdqa (%0), %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (my_ptr)
			: /*  clobbered */ "rax", "xmm3"
	    );

	asm (
		"paddd %%xmm2, %%xmm3\n\t"
			: /*  outputs */ 
			: /*  inputs */ 
			: /*  clobbered */ 
				"xmm3"
	    );

	asm (
		"movdqa %%xmm3, %0\n\t"
			: /*  outputs */ "=m" (*my_ptr)
			: /*  inputs */ 
			: /*  clobbered */ 
				"memory"
	    );
	// load the next 4 counter variables
	//++my_ptr; // or should it be ptr += 4?
	my_ptr+= 4;
	asm (
			"movdqa (%0), %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (my_ptr)
			: /*  clobbered */ "rax", "xmm3"
	    );

	// extract the next 4 results 
	asm (
			"pextrd $1, %%xmm0, %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm1\n\t"
    			"pmovsxbd %%xmm1, %%xmm2\n\t"
			: /*  outputs */
			: /*  inputs */ 
			: /*  clobbered */ "rax", "xmm1",
				"xmm2"
	    );

	asm (
		"paddd %%xmm2, %%xmm3\n\t"
		"movdqa %%xmm3, %0\n\t"
			: /*  outputs */ "=m" (*my_ptr)
			: /*  inputs */ 
			: /*  clobbered */ 
				"xmm3", "memory"
	    );

	cout << "counter: ";
	for (int i=0; i<8; ++i) {
		cout << " " << "|" << (int) counter_4_2[i] << "|" ;
	}
	cout << endl;


	

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
	tabulate_side4_ban2_parallel ();

}

