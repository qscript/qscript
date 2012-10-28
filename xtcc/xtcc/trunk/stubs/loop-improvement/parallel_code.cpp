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

#ifdef __MMX__
#include <mmintrin.h>
#endif
 
#ifdef __SSE__
#include <xmmintrin.h>
#endif
 
#ifdef __SSE2__
#include <emmintrin.h>
#endif
 
#ifdef __SSE3__
#include <pmmintrin.h>
#endif
 
#ifdef __SSSE3__
#include <tmmintrin.h>
#endif
 
#if defined (__SSE4_2__) || defined (__SSE4_1__)
#include <smmintrin.h>
#endif


//char flag_ban1 [] = { 65 };
char flag_ban1 [] = { 1 };
char flag_ban2 [] = { 0, 1 };
//char flag_ban3 [] = { 1, 1, 1, 0 /*  dummy to prevent core dump etc */};
char flag_ban3 [] = { 1, 0, 1, 0 /*  dummy to prevent core dump etc */};
char flag_ban4 [] = { 1, 1, 1, 1 };
char flag_ban5 [] = { 0, 0, 0, 0, 1 };
char flag_ban6 [] = { 0, 0, 0, 0, 0, 1 };
char flag_side2 [] = { 1, 1 };
char flag_side3 [] = { 1, 1, 1 };
//char flag_side4 [4]  = { 1, 1, 1, 1 };
//char flag_side4 [4]  = { 1, 0, 1, 0 };
//char flag_side4 [4]  = { 0, 1, 0, 1 };
char flag_side4 [4]  = { 1, 1, 1, 1 };
char flag_side5 [] = { 1, 1, 1, 1, 1 };
int counter_4_1 [] __attribute__ ((aligned(16))) = { 1, 2, 3, 4 };

int counter_4_3 [] __attribute__ ((aligned(16))) = { 
	7, 12, 17, 22,
	27, 32, 37, 42,
	47, 52, 57, 62,
};

int counter_4_4 [] __attribute__ ((aligned(16))) = { 
	7, 12, 17, 22,
	27, 32, 37, 42,
	47, 52, 57, 62,
	67, 72, 77, 82,
};

int counter_4_5 [] __attribute__ ((aligned(16))) = { 
	8, 13, 18, 23,
	28, 33, 38, 43,
	48, 53, 58, 63,
	68, 73, 78, 83,
	88, 93, 98, 103,
};

int counter_4_6 [] __attribute__ ((aligned(16))) = { 
	8, 13, 18, 23,
	28, 33, 38, 43,
	48, 53, 58, 63,
	68, 73, 78, 83,
	88, 93, 98, 103,
	108, 113, 118, 123,
};
char flag_ban15 [] = { 
	0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0
};

int counter_4_15 [] __attribute__ ((aligned(16))) = { 

	2, 4, 6, 8, 
	10, 12, 14, 16, 
	18, 20, 22, 24, 
	26, 28, 30, 32, 
	34, 36, 38, 40, 
	42, 44, 46, 48, 
	50, 52, 54, 56, 
	58, 60, 62, 64, 
	66, 68, 70, 72, 
	74, 76, 78, 80, 
	82, 84, 86, 88, 
	90, 92, 94, 96, 
	98, 100, 102, 104, 
	106, 108, 110, 112, 
	114, 116, 118, 120
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


int counter_4_2 [] __attribute__ ((aligned(16))) = { 
	5, 10, 15, 20,
	25, 30, 35, 40
};

void set_counter_4_2()
{
	for (int i=0; i<8; ++i) {
		counter_4_2[i] = (i+1) * 5;
	}
}

void tabulate_side4_ban2 ()
{
	cout << __PRETTY_FUNCTION__ << endl;
	//int counter [] = { 	0, 0, 0, 0, 
	//			0, 0, 0, 0 
	//};

	int cols = 2;

	if (flag_side4[0] && flag_ban2[0])
		++ counter_4_2[0 * cols + 0];
	if (flag_side4[1] && flag_ban2[0])
		++ counter_4_2[0 * cols + 1];
	if (flag_side4[2] && flag_ban2[0])
		++ counter_4_2[1 * cols + 0];
	if (flag_side4[3] && flag_ban2[0])
		++ counter_4_2[1 * cols + 1];

	if (flag_side4[0] && flag_ban2[1])
		++ counter_4_2[2 * cols + 0];
	if (flag_side4[1] && flag_ban2[1])
		++ counter_4_2[2 * cols + 1];
	if (flag_side4[2] && flag_ban2[1])
		++ counter_4_2[3 * cols + 0];
	if (flag_side4[3] && flag_ban2[1])
		++ counter_4_2[3 * cols + 1];

	cout << "counter_4_2: ";
	for (int i=0; i<8; ++i) {
		cout << " " << "|" << (int) counter_4_2[i] << "|" ;
	}
	cout << endl;

}

void tabulate_side4_ban2_parallel ()
{
	cout << __PRETTY_FUNCTION__ << endl;
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

void set_counter_4_3()
{
	for (int i=0; i<12; ++i) {
		counter_4_3[i] = (i+1) * 5 + 2;
	}
}

void tabulate_side4_ban3 ()
{
	//int counter_4_3 [] = { 	
	//			0, 0, 0, 0,
	//			0, 0, 0, 0,
	//			0, 0, 0, 0
	//};

	int cols = 3;

	if (flag_side4[0] && flag_ban3[0])
		++ counter_4_3[0 * cols + 0];
	if (flag_side4[0] && flag_ban3[1])
		++ counter_4_3[0 * cols + 1];
	if (flag_side4[0] && flag_ban3[2])
		++ counter_4_3[0 * cols + 2];

	if (flag_side4[1] && flag_ban3[0])
		++ counter_4_3[1 * cols + 0];
	if (flag_side4[1] && flag_ban3[1])
		++ counter_4_3[1 * cols + 1];
	if (flag_side4[1] && flag_ban3[2])
		++ counter_4_3[1 * cols + 2];

	if (flag_side4[2] && flag_ban3[0])
		++ counter_4_3[2 * cols + 0];
	if (flag_side4[2] && flag_ban3[1])
		++ counter_4_3[2 * cols + 1];
	if (flag_side4[2] && flag_ban3[2])
		++ counter_4_3[2 * cols + 2];

	if (flag_side4[3] && flag_ban3[0])
		++ counter_4_3[3 * cols + 0];
	if (flag_side4[3] && flag_ban3[1])
		++ counter_4_3[3 * cols + 1];
	if (flag_side4[3] && flag_ban3[2])
		++ counter_4_3[3 * cols + 2];

	cout << "counter_4_3: ";
	for (int i=0; i<12; ++i) {
		cout << " " << "|" << (int) counter_4_3[i] << "|" ;
	}
	cout << endl;

}

void tabulate_side4_ban3_parallel ()
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
			"xor %%rax, %%rax\n\t"
			"mov (%0), %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm0\n\t"
			"pshufb %%xmm1, %%xmm0\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (flag_ban3)
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

	// all 12 conditions and'ed in one go, result in xmm0
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
	int * my_ptr __attribute__ ((aligned(16))) = counter_4_3;
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

	// =========================================
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

	// =========================================
	my_ptr+= 4;
	asm (
			"movdqa (%0), %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (my_ptr)
			: /*  clobbered */ "rax", "xmm3"
	    );

	// extract the next 4 results 
	asm (
			"pextrd $2, %%xmm0, %%eax\n\t"
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


	cout << "parallel counter_4_3: ";
	for (int i=0; i<12; ++i) {
		cout << " " << "|" << (int) counter_4_3[i] << "|" ;
	}
	cout << endl;
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

	if (flag_side4[0] && flag_ban4[0])
		++ counter[0];
	if (flag_side4[1] && flag_ban4[0])
		++ counter[1];
	if (flag_side4[2] && flag_ban4[0])
		++ counter[2];
	if (flag_side4[3] && flag_ban4[0])
		++ counter[3];

	if (flag_side4[0] && flag_ban4[1])
		++ counter[1 * cols + 0];
	if (flag_side4[1] && flag_ban4[1])
		++ counter[1 * cols + 1];
	if (flag_side4[2] && flag_ban4[1])
		++ counter[1 * cols + 2];
	if (flag_side4[3] && flag_ban4[1])
		++ counter[1 * cols + 3];

	if (flag_side4[0] && flag_ban4[2])
		++ counter[2 * cols + 0];
	if (flag_side4[1] && flag_ban4[2])
		++ counter[2 * cols + 1];
	if (flag_side4[2] && flag_ban4[2])
		++ counter[2 * cols + 2];
	if (flag_side4[3] && flag_ban4[2])
		++ counter[2 * cols + 3];

	if (flag_side4[0] && flag_ban4[3])
		++ counter[3 * cols + 0];
	if (flag_side4[1] && flag_ban4[3])
		++ counter[3 * cols + 1];
	if (flag_side4[2] && flag_ban4[3])
		++ counter[3 * cols + 2];
	if (flag_side4[3] && flag_ban4[3])
		++ counter[3 * cols + 3];

}


void tabulate_side4_ban4_parallel ()
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
			"xor %%rax, %%rax\n\t"
			"mov (%0), %%eax\n\t"
			"pinsrw $0, %%eax, %%xmm0\n\t"
			"pshufb %%xmm1, %%xmm0\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (flag_ban4)
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

	// all 16 conditions and'ed in one go, result in xmm0
	// extract the results 4 at a time : 0-3
	asm (
			"pextrd $0, %%xmm0, %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm1\n\t"
    			"pmovsxbd %%xmm1, %%xmm2\n\t"
			: /*  outputs */
			: /*  inputs */ 
			: /*  clobbered */ "rax", "xmm2"
	    );

	// load the 1st 4 counter variables
	int * my_ptr __attribute__ ((aligned(16))) = counter_4_4;
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

	// =========================================
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
	// extract the results 4 at a time : 4-7
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

	// =========================================
	my_ptr+= 4;
	asm (
			"movdqa (%0), %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (my_ptr)
			: /*  clobbered */ "rax", "xmm3"
	    );

	// extract the next 4 results 
	// extract the results 4 at a time : 8-11
	asm (
			"pextrd $2, %%xmm0, %%eax\n\t"
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

	// =========================================
	my_ptr+= 4;
	asm (
			"movdqa (%0), %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (my_ptr)
			: /*  clobbered */ "rax", "xmm3"
	    );

	// extract the next 4 results 
	// extract the results 4 at a time : 12-15
	asm (
			"pextrd $3, %%xmm0, %%eax\n\t"
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
	for (int i=0; i<16; ++i) {
		cout << " " << "|" << (int) counter_4_4[i] << "|" ;
	}
	cout << endl;
}


void tabulate_side4_ban5 ()
{
	int cols = 5;

	if (flag_side4[0] && flag_ban5[0])
		++ counter_4_5[0];
	if (flag_side4[1] && flag_ban5[0])
		++ counter_4_5[1];
	if (flag_side4[2] && flag_ban5[0])
		++ counter_4_5[2];
	if (flag_side4[3] && flag_ban5[0])
		++ counter_4_5[3];

	if (flag_side4[0] && flag_ban5[1])
		++ counter_4_5[1 * cols + 0];
	if (flag_side4[1] && flag_ban5[1])
		++ counter_4_5[1 * cols + 1];
	if (flag_side4[2] && flag_ban5[1])
		++ counter_4_5[1 * cols + 2];
	if (flag_side4[3] && flag_ban5[1])
		++ counter_4_5[1 * cols + 3];

	if (flag_side4[0] && flag_ban5[2])
		++ counter_4_5[2 * cols + 0];
	if (flag_side4[1] && flag_ban5[2])
		++ counter_4_5[2 * cols + 1];
	if (flag_side4[2] && flag_ban5[2])
		++ counter_4_5[2 * cols + 2];
	if (flag_side4[3] && flag_ban5[2])
		++ counter_4_5[2 * cols + 3];

	if (flag_side4[0] && flag_ban5[3])
		++ counter_4_5[3 * cols + 0];
	if (flag_side4[1] && flag_ban5[3])
		++ counter_4_5[3 * cols + 1];
	if (flag_side4[2] && flag_ban5[3])
		++ counter_4_5[3 * cols + 2];
	if (flag_side4[3] && flag_ban5[3])
		++ counter_4_5[3 * cols + 3];

	if (flag_side4[0] && flag_ban5[4])
		++ counter_4_5[4 * cols + 0];
	if (flag_side4[1] && flag_ban5[4])
		++ counter_4_5[4 * cols + 1];
	if (flag_side4[2] && flag_ban5[4])
		++ counter_4_5[4 * cols + 2];
	if (flag_side4[3] && flag_ban5[4])
		++ counter_4_5[4 * cols + 3];

}


void tabulate_side4_ban5_parallel ()
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

	char * my_ban_ptr __attribute__ ((aligned(16))) = flag_ban5;
	asm (
			"xor %%rax, %%rax\n\t"
			"movl (%0), %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm0\n\t"
			"pshufb %%xmm1, %%xmm0\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (my_ban_ptr)
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

	// all 16 conditions and'ed in one go, result in xmm0
	// extract the results 4 at a time : 0-3
	asm (
			"pextrd $0, %%xmm0, %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm1\n\t"
    			"pmovsxbd %%xmm1, %%xmm2\n\t"
			: /*  outputs */
			: /*  inputs */ 
			: /*  clobbered */ "rax", "xmm2"
	    );

	// load the 1st 4 counter variables
	int * my_ptr __attribute__ ((aligned(16))) = counter_4_5;
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

	// =========================================
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
	// extract the results 4 at a time : 4-7
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

	// =========================================
	my_ptr+= 4;
	asm (
			"movdqa (%0), %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (my_ptr)
			: /*  clobbered */ "rax", "xmm3"
	    );

	// extract the next 4 results 
	// extract the results 4 at a time : 8-11
	asm (
			"pextrd $2, %%xmm0, %%eax\n\t"
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

	// =========================================
	my_ptr+= 4;
	asm (
			"movdqa (%0), %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (my_ptr)
			: /*  clobbered */ "rax", "xmm3"
	    );

	// extract the next 4 results 
	// extract the results 4 at a time : 12-15
	asm (
			"pextrd $3, %%xmm0, %%eax\n\t"
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




	//cout << "counter: ";
	//for (int i=0; i<16; ++i) {
	//	cout << " " << "|" << (int) counter_4_4[i] << "|" ;
	//}
	//cout << endl;
	{
		//my_ban_ptr += 4;

		//char * my_ban_ptr __attribute__ ((aligned(16))) = flag_ban5;
		//asm (
		//		"xor %%rax, %%rax\n\t"
		//		"movb (%0), %%eax\n\t"
		//		"pinsrd $0, %%eax, %%xmm0\n\t"
		//		"pshufb %%xmm1, %%xmm0\n\t"
		//		: /*  outputs */
		//		: /*  inputs */ "r" (my_ban_ptr)
		//		: /*  clobbered */ "rax", "xmm0", "xmm1"
		//    );
		//// the banner conditions in xmm0
		my_ptr+= 4;

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
				: /*  inputs */ "r" (my_ban_ptr+4)
				: /*  clobbered */ "rax", "xmm0", "rbx"
		    );


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
			: /*  inputs */ "r" (my_ptr)
			: /*  clobbered */
		    );

		asm (
			"paddd %%xmm2, %%xmm4\n\t"
			"movdqa %%xmm4, %0\n\t"
			: /*  outputs */  "=m" (*my_ptr)
			: /*  inputs */
			: /*  clobbered */
		    );

		//cout << "counter: ";
		//for (int i=0; i<4; ++i) {
		//	cout << " " << "|" << (int) counter_4_1[i] << "|" ;
		//}
		//cout << endl;

	}
	cout << "counter: ";
	for (int i=0; i<20; ++i) {
		cout << " " << "|" << (int) counter_4_5[i] << "|" ;
		if ( (i+1) % 5 == 0) {
			cout << endl;
		}
	}
	cout << endl;
}

void tabulate_side4_ban6_parallel ()
{
	char shuffle_mask_ban[] __attribute__ ((aligned(16)))
		= { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };
	char shuffle_mask_side[] __attribute__ ((aligned(16)))
		= { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };
	int * my_ptr __attribute__ ((aligned(16))) = counter_4_6;
	{


		asm (
				"movdqa (%0), %%xmm1\n\t"
				: /*  outputs */
				: /*  inputs */ "r" (shuffle_mask_ban)
				: /*  clobbered */ "xmm1"
		    );

		char * my_ban_ptr __attribute__ ((aligned(16))) = flag_ban6;
		asm (
				"xor %%rax, %%rax\n\t"
				"movl (%0), %%eax\n\t"
				"pinsrd $0, %%eax, %%xmm0\n\t"
				"pshufb %%xmm1, %%xmm0\n\t"
				: /*  outputs */
				: /*  inputs */ "r" (my_ban_ptr)
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

		// all 16 conditions and'ed in one go, result in xmm0
		// extract the results 4 at a time : 0-3
		asm (
				"pextrd $0, %%xmm0, %%eax\n\t"
				"pinsrd $0, %%eax, %%xmm1\n\t"
				"pmovsxbd %%xmm1, %%xmm2\n\t"
				: /*  outputs */
				: /*  inputs */ 
				: /*  clobbered */ "rax", "xmm2"
		    );

		// load the 1st 4 counter variables
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

		// =========================================
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
		// extract the results 4 at a time : 4-7
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

		// =========================================
		my_ptr+= 4;
		asm (
				"movdqa (%0), %%xmm3\n\t"
				: /*  outputs */
				: /*  inputs */ "r" (my_ptr)
				: /*  clobbered */ "rax", "xmm3"
		    );

		// extract the next 4 results 
		// extract the results 4 at a time : 8-11
		asm (
				"pextrd $2, %%xmm0, %%eax\n\t"
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

		// =========================================
		my_ptr+= 4;
		asm (
				"movdqa (%0), %%xmm3\n\t"
				: /*  outputs */
				: /*  inputs */ "r" (my_ptr)
				: /*  clobbered */ "rax", "xmm3"
		    );

		// extract the next 4 results 
		// extract the results 4 at a time : 12-15
		asm (
				"pextrd $3, %%xmm0, %%eax\n\t"
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
	}




	//cout << "counter: ";
	//for (int i=0; i<16; ++i) {
	//	cout << " " << "|" << (int) counter_4_4[i] << "|" ;
	//}
	{
		char shuffle_mask_ban[] __attribute__ ((aligned(16)))
			= { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };
		char shuffle_mask_side[] __attribute__ ((aligned(16)))
			= { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };
		char * my_ban_ptr __attribute__ ((aligned(16))) = flag_ban6;


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
				: /*  inputs */ "r" (my_ban_ptr+4)
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
		my_ptr += 4;
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

	}//cout << endl;
	
	
	cout << "counter: ";
	for (int i=0; i<24; ++i) {
		cout << " " << "|" << (int) counter_4_6[i] << "|" ;
		if ( (i+1) % 6 == 0) {
			cout << endl;
		}
	}
	cout << endl;
}

void tabulate_side4_ban_n_parallel (
			  int n_ban_elements 
			, char * ban_ptr 
			, int   counter [] 
			, int n_side_elements
		)
{
	cout << __PRETTY_FUNCTION__ << endl;
	char shuffle_mask_ban[] __attribute__ ((aligned(16)))
		= { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };
	char shuffle_mask_side[] __attribute__ ((aligned(16)))
		= { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };

	//double *x = __builtin_assume_aligned(a, 16);
	//double *y = __builtin_assume_aligned(b, 16);

	char * my_ban_ptr __attribute__ ((aligned(16))) = ban_ptr;
	int * my_ptr __attribute__ ((aligned(16))) = counter;
	//char * my_ban_ptr = __builtin_assume_aligned (ban_ptr, 16);
	//int * my_ptr      = __builtin_assume_aligned (counter, 16);

	int l_n_ban_elements = n_ban_elements;
	if (l_n_ban_elements > 4) {
		//cout << "l_n_ban_elements > 4: " << l_n_ban_elements << endl;

		while (l_n_ban_elements > 4) {
			//cout << "looping: l_n_ban_elements : " <<  l_n_ban_elements << endl;

			// obviously for perf reasons this
			// will move out of the loop
			// and we should preserve the xmm1 register
			// at some later point
			asm (
					"movdqa (%0), %%xmm1\n\t"
					: /*  outputs */
					: /*  inputs */ "r" (shuffle_mask_ban)
					: /*  clobbered */ "xmm1"
			    );

			asm (
					"xor %%rax, %%rax\n\t"
					"movl (%0), %%eax\n\t"
					"pinsrd $0, %%eax, %%xmm0\n\t"
					"pshufb %%xmm1, %%xmm0\n\t"
					: /*  outputs */
					: /*  inputs */ "r" (my_ban_ptr)
					: /*  clobbered */ "rax", "xmm0", "xmm1"
			    );
			// the banner conditions in xmm0

			// again, for perf reasons this
			// will move out of the loop
			// and we should preserve the xmm2 register
			// at some later point
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

			// all 16 conditions and'ed in one go, result in xmm0
			// extract the results 4 at a time : 0-3
			asm (
					"pextrd $0, %%xmm0, %%eax\n\t"
					"pinsrd $0, %%eax, %%xmm1\n\t"
					"pmovsxbd %%xmm1, %%xmm2\n\t"
					: /*  outputs */
					: /*  inputs */ 
					: /*  clobbered */ "rax", "xmm2"
			    );

			// load the 1st 4 counter variables
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

			// =========================================
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
			// extract the results 4 at a time : 4-7
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

			// =========================================
			my_ptr+= 4;
			asm (
					"movdqa (%0), %%xmm3\n\t"
					: /*  outputs */
					: /*  inputs */ "r" (my_ptr)
					: /*  clobbered */ "rax", "xmm3"
			    );

			// extract the next 4 results 
			// extract the results 4 at a time : 8-11
			asm (
					"pextrd $2, %%xmm0, %%eax\n\t"
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

			// =========================================
			my_ptr+= 4;
			asm (
					"movdqa (%0), %%xmm3\n\t"
					: /*  outputs */
					: /*  inputs */ "r" (my_ptr)
					: /*  clobbered */ "rax", "xmm3"
			    );

			// extract the next 4 results 
			// extract the results 4 at a time : 12-15
			asm (
					"pextrd $3, %%xmm0, %%eax\n\t"
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
			l_n_ban_elements -= 4;
			my_ptr+= 4;
		}

	}
	if (n_ban_elements % 4 == 1) {
		//my_ban_ptr += 4;

		//char * my_ban_ptr __attribute__ ((aligned(16))) = flag_ban5;
		//asm (
		//		"xor %%rax, %%rax\n\t"
		//		"movb (%0), %%eax\n\t"
		//		"pinsrd $0, %%eax, %%xmm0\n\t"
		//		"pshufb %%xmm1, %%xmm0\n\t"
		//		: /*  outputs */
		//		: /*  inputs */ "r" (my_ban_ptr)
		//		: /*  clobbered */ "rax", "xmm0", "xmm1"
		//    );
		//// the banner conditions in xmm0
		my_ptr+= 4;

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
				: /*  inputs */ "r" (my_ban_ptr+4)
				: /*  clobbered */ "rax", "xmm0", "rbx"
		    );


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
			: /*  inputs */ "r" (my_ptr)
			: /*  clobbered */
		    );

		asm (
			"paddd %%xmm2, %%xmm4\n\t"
			"movdqa %%xmm4, %0\n\t"
			: /*  outputs */  "=m" (*my_ptr)
			: /*  inputs */
			: /*  clobbered */
		    );

		//cout << "counter: ";
		//for (int i=0; i<4; ++i) {
		//	cout << " " << "|" << (int) counter_4_1[i] << "|" ;
		//}
		//cout << endl;

	}
	if (n_ban_elements % 4 == 2) {
		char shuffle_mask_ban[] __attribute__ ((aligned(16)))
			= { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };
		char shuffle_mask_side[] __attribute__ ((aligned(16)))
			= { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };
		char * my_ban_ptr __attribute__ ((aligned(16))) = flag_ban6;


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
				: /*  inputs */ "r" (my_ban_ptr+4)
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
		my_ptr += 4;
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

	}
	if (n_ban_elements % 3 ==0 ) {
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
				"xor %%rax, %%rax\n\t"
				"movl (%0), %%eax\n\t"
				"pinsrd $0, %%eax, %%xmm0\n\t"
				"pshufb %%xmm1, %%xmm0\n\t"
				: /*  outputs */
				: /*  inputs */ "r" (my_ban_ptr)
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

		// all 12 conditions and'ed in one go, result in xmm0
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
		//int * my_ptr __attribute__ ((aligned(16))) = counter_4_3;
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

		// =========================================
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

		// =========================================
		my_ptr+= 4;
		asm (
				"movdqa (%0), %%xmm3\n\t"
				: /*  outputs */
				: /*  inputs */ "r" (my_ptr)
				: /*  clobbered */ "rax", "xmm3"
		    );

		// extract the next 4 results 
		asm (
				"pextrd $2, %%xmm0, %%eax\n\t"
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


		//cout << "counter: ";
		//for (int i=0; i<12; ++i) {
		//	cout << " " << "|" << (int) counter_4_3[i] << "|" ;
		//}
		//cout << endl;
	}
	for (int i=0; i < n_side_elements; ++i ) {
		for (int j=0; j < n_ban_elements; ++j) {
			cout << " " << counter[i * n_ban_elements + j];
		}
		cout << endl;
	}

}




int main()
{
	tabulate_side4_ban1_parallel ();
	set_counter_4_2();
	tabulate_side4_ban2();
	set_counter_4_2();
	tabulate_side4_ban2_parallel ();
	set_counter_4_3();
	tabulate_side4_ban3 ();
	set_counter_4_3();
	tabulate_side4_ban3_parallel ();
	tabulate_side4_ban4_parallel ();
	tabulate_side4_ban5_parallel ();
	tabulate_side4_ban6_parallel ();

	int n_ban_elements = 15;
	int n_side_elements = 4;
	tabulate_side4_ban_n_parallel (
			  n_ban_elements 
			, flag_ban15
			, counter_4_15
			, n_side_elements
		);

}

