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

#include <iostream>
using namespace std;

#if 0
//char flag_ban1 [] = { 65 };
char flag_ban1 [] = { 1 };
char flag_ban2 [] = { 0, 1 };
//char flag_ban3 [] = { 1, 1, 1, 0 /*  dummy to prevent core dump etc */};
char flag_ban3 [] = { 1, 1, 1, 0 /*  dummy to prevent core dump etc */};
char flag_ban4 [] = { 1, 0, 0, 1 };
char flag_ban5 [] = { 0, 0, 0, 0, 1 };
char flag_ban6 [] = { 0, 0, 0, 0, 0, 1 };
//char flag_side2 [] = { 1, 1 };

char flag_side2 [] __attribute__ ((aligned(16))) = 
	{ 	0, 1, /*  padding */ 
		      0, 0,
		0, 0, 0, 0,	   
		0, 0, 0, 0,	   
		0, 0, 0, 0,	 
	};

char flag_side3 [] = { 1, 1, 1, /*  padding */ 0 };
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
	if (flag_side4[0] && flag_ban2[1])
		++ counter_4_2[0 * cols + 1];
	if (flag_side4[1] && flag_ban2[0])
		++ counter_4_2[1 * cols + 0];
	if (flag_side4[1] && flag_ban2[1])
		++ counter_4_2[1 * cols + 1];

	if (flag_side4[2] && flag_ban2[0])
		++ counter_4_2[2 * cols + 0];
	if (flag_side4[2] && flag_ban2[1])
		++ counter_4_2[2 * cols + 1];
	if (flag_side4[3] && flag_ban2[0])
		++ counter_4_2[3 * cols + 0];
	if (flag_side4[3] && flag_ban2[1])
		++ counter_4_2[3 * cols + 1];

	cout << " simple   counter_4_2: ";
	for (int i=0; i<8; ++i) {
		cout << " " << "|" << (int) counter_4_2[i] << "|" ;
	}
	cout << endl;

}

void tabulate_side4_ban2_parallel ()
{
	cout << __PRETTY_FUNCTION__ << endl;
	char shuffle_mask_ban[] __attribute__ ((aligned(16)))
		//= { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };
		= { 	
			0, 1, 0, 1, 0, 1, 0, 1,
			0, 1, 0, 1, 0, 1, 0, 1
				
			//, 0, 1, 2, 3, 0, 1, 2, 3 
		};
	char shuffle_mask_side[] __attribute__ ((aligned(16)))
		= { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };


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

	cout << " parallel counter_4_2: ";
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

	cout << "simple   counter_4_3: ";
	for (int i=0; i<12; ++i) {
		cout << " " << "|" << (int) counter_4_3[i] << "|" ;
		//if ( (i+1) % cols == 0) {
		//	cout << endl;
		//}
	}
	cout << endl;

}

void tabulate_side4_ban3_parallel ()
{
	char shuffle_mask_ban[] __attribute__ ((aligned(16)))
		//= { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };
		= { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };
	char shuffle_mask_side[] __attribute__ ((aligned(16)))
		= { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };


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


	cout << "parallel counter_4_3: " ;
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

char flag_ban15 [] = { 
	0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0
};

int counter_4_15 [] __attribute__ ((aligned(16))) = { 
	 2,  4,  6,  8,   10,  12,  14,  16,   18,  20,  22,  24,   26,  28,  30, 
	32, 34, 36, 38,   40,  42,  44,  46,   48,  50,  52,  54,   56,  58,  60,
	62, 64, 66, 68,   70,  72,  74,  76,   78,  80,  82,  84,   86,  88,  90, 
	92, 94, 96, 98,  100, 102, 104, 106,  108, 110, 112, 114,  116, 118, 120
};

void tabulate_side4_ban_n_parallel (
			  int n_ban_elements 
			, char * ban_ptr 
			, int   counter [] 
			, int n_side_elements
		)
{
	cout << __PRETTY_FUNCTION__ << endl;
	char shuffle_mask_ban[] __attribute__ ((aligned(16)))
		= { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };
	char shuffle_mask_side[] __attribute__ ((aligned(16)))
		= { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };

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
			= 
			{ 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };
		char shuffle_mask_side[] __attribute__ ((aligned(16)))
			= 
			{ 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };
		//char * my_ban_ptr __attribute__ ((aligned(16))) = flag_ban6;


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

char flag_side1 [] __attribute__ ((aligned(16))) = 
	{ 	1, 
		   /*  padding */ 0, 0, 0,
		0,0,0,0,	   
		0,0,0,0,	   
		0,0,0,0,	 
		
	};

int counter_1_4 [] __attribute__ ((aligned(16))) = { 5, 10, 15, 20 };
 
// ====================================
void tabulate_side1_ban4()
{
	const int cols = 4;
	if (flag_side1[0] && flag_ban4[0]) 
		++ counter_1_4[0 * cols + 0];
	if (flag_side1[0] && flag_ban4[1]) 
		++ counter_1_4[0 * cols + 1];
	if (flag_side1[0] && flag_ban4[2]) 
		++ counter_1_4[0 * cols + 2];
	if (flag_side1[0] && flag_ban4[3]) 
		++ counter_1_4[0 * cols + 3];
}

void tabulate_side1_ban4_parallel()
{
	const int cols = 4;
	//if (flag_side1[0] && flag_ban4[0]) 
	//	++ counter_1_4[0 * cols + 0];
	//if (flag_side1[0] && flag_ban4[1]) 
	//	++ counter_1_4[0 * cols + 1];
	//if (flag_side1[0] && flag_ban4[2]) 
	//	++ counter_1_4[0 * cols + 2];
	//if (flag_side1[0] && flag_ban4[3]) 
	//	++ counter_1_4[0 * cols + 3];
	char shuffle_mask_ban[] __attribute__ ((aligned(16)))
		= { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };
	char shuffle_mask_side[] __attribute__ ((aligned(16)))
		= { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };

	asm (
			"movdqa (%0), %%xmm1\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (shuffle_mask_ban)
			: /*  clobbered */ "xmm1"
	    );

	asm (
			"movdqa (%0), %%xmm2\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (shuffle_mask_side)
			: /*  clobbered */ "xmm2"
	    );

	// the banner conditions in xmm0
	asm (
			"xor %%eax, %%eax\n\t"
			"movl (%0), %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm0\n\t"
			"pshufb %%xmm1, %%xmm0\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (flag_ban4)
			: /*  clobbered */ "rax", "xmm0" 
	    );

	// the side conditions in xmm3
	asm (
			"xor %%eax, %%eax\n\t"
			"movb (%0), %%al\n\t"
			"pinsrb $0, %%eax, %%xmm3\n\t"
			"pshufb %%xmm2, %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (flag_side1)
			: /*  clobbered */ "rax", "xmm3"
	    );

	asm (
			"pand %%xmm3, %%xmm0\n\t"
			: /*  outputs */
			: /*  inputs */ 
			: /*  clobbered */ "xmm0"
	    );

	asm (
			"pextrd $0, %%xmm0, %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm4\n\t"
    			"pmovsxbd %%xmm4, %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ 
			: /*  clobbered */ "rax", "xmm4", "xmm3"
	    );

	// load the 1st 4 counter variables
	int * my_ptr __attribute__ ((aligned(16))) = counter_1_4;
	asm (
			"movdqa (%0), %%xmm5\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (my_ptr)
			: /*  clobbered */ "xmm5"
	    );

	asm (
		"paddd %%xmm3, %%xmm5\n\t"
			: /*  outputs */ 
			: /*  inputs */ 
			: /*  clobbered */ 
				"xmm5"
	    );

	asm (
		"movdqa %%xmm5, %0\n\t"
			: /*  outputs */ "=m" (*my_ptr)
			: /*  inputs */ 
			: /*  clobbered */ 
				"memory"
	    );


	cout << "counter: ";
	for (int i=0; i<4; ++i) {
		cout << " " << "|" << (int) counter_1_4[i] << "|" ;
		if ( (i+1) % 4 == 0) {
			cout << endl;
		}
	}
	cout << endl;
}

/*
char flag_side2 [] __attribute__ ((aligned(16))) = 
	{ 	1, 1, //
		      0, 0,
		0, 0, 0, 0,	   
		0, 0, 0, 0,	   
		0, 0, 0, 0,	 
	};
  */

int counter_2_4 [] __attribute__ ((aligned(16))) = { 
	5 ,  10,  15,  20,
	25,  30,  35,  40 
};

void tabulate_side2_ban4_parallel()
{
	const int cols = 4;
	//if (flag_side1[0] && flag_ban4[0]) 
	//	++ counter_1_4[0 * cols + 0];
	//if (flag_side1[0] && flag_ban4[1]) 
	//	++ counter_1_4[0 * cols + 1];
	//if (flag_side1[0] && flag_ban4[2]) 
	//	++ counter_1_4[0 * cols + 2];
	//if (flag_side1[0] && flag_ban4[3]) 
	//	++ counter_1_4[0 * cols + 3];
	char shuffle_mask_ban[] __attribute__ ((aligned(16)))
		= { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };
	char shuffle_mask_side[] __attribute__ ((aligned(16)))
		= { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };

	asm (
			"movdqa (%0), %%xmm1\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (shuffle_mask_ban)
			: /*  clobbered */ "xmm1"
	    );

	asm (
			"movdqa (%0), %%xmm2\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (shuffle_mask_side)
			: /*  clobbered */ "xmm2"
	    );

	// the banner conditions in xmm0
	asm (
			"xor %%eax, %%eax\n\t"
			"movl (%0), %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm0\n\t"
			"pshufb %%xmm1, %%xmm0\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (flag_ban4)
			: /*  clobbered */ "rax", "xmm0" 
	    );

	// the side conditions in xmm3
	asm (
			"xor %%eax, %%eax\n\t"
			"movw (%0), %%ax\n\t"
			"pinsrw $0, %%eax, %%xmm3\n\t"
			"pshufb %%xmm2, %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (flag_side2)
			: /*  clobbered */ "rax", "xmm3"
	    );

	asm (
			"pand %%xmm3, %%xmm0\n\t"
			: /*  outputs */
			: /*  inputs */ 
			: /*  clobbered */ "xmm0"
	    );

	asm (
			"pextrd $0, %%xmm0, %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm4\n\t"
    			"pmovsxbd %%xmm4, %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ 
			: /*  clobbered */ "rax", "xmm4", "xmm3"
	    );

	// load the 1st 4 counter variables
	int * my_ptr __attribute__ ((aligned(16))) = counter_2_4;
	asm (
			"movdqa (%0), %%xmm5\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (my_ptr)
			: /*  clobbered */ "xmm5"
	    );

	asm (
		"paddd %%xmm3, %%xmm5\n\t"
			: /*  outputs */ 
			: /*  inputs */ 
			: /*  clobbered */ 
				"xmm5"
	    );

	asm (
		"movdqa %%xmm5, %0\n\t"
			: /*  outputs */ "=m" (*my_ptr)
			: /*  inputs */ 
			: /*  clobbered */ 
				"memory"
	    );
	// ==================================

	asm (
			"pextrd $1, %%xmm0, %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm4\n\t"
    			"pmovsxbd %%xmm4, %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ 
			: /*  clobbered */ "rax", "xmm4", "xmm3"
	    );
	my_ptr += 4;
	asm (
			"movdqa (%0), %%xmm5\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (my_ptr)
			: /*  clobbered */ "xmm5"
	    );

	asm (
		"paddd %%xmm3, %%xmm5\n\t"
			: /*  outputs */ 
			: /*  inputs */ 
			: /*  clobbered */ 
				"xmm5"
	    );

	asm (
		"movdqa %%xmm5, %0\n\t"
			: /*  outputs */ "=m" (*my_ptr)
			: /*  inputs */ 
			: /*  clobbered */ 
				"memory"
	    );



	cout << "counter: ";
	for (int i=0; i<8; ++i) {
		cout << " " << "|" << (int) counter_2_4[i] << "|" ;
		if ( (i+1) % 4 == 0) {
			cout << endl;
		}
	}
	cout << endl;
}

int counter_3_4 [] __attribute__ ((aligned(16))) = { 
	5 ,  10,  15,  20,
	25,  30,  35,  40, 
	45,  50,  55,  60 
};


void tabulate_side3_ban4_parallel()
{
	const int cols = 4;
	//if (flag_side1[0] && flag_ban4[0]) 
	//	++ counter_1_4[0 * cols + 0];
	//if (flag_side1[0] && flag_ban4[1]) 
	//	++ counter_1_4[0 * cols + 1];
	//if (flag_side1[0] && flag_ban4[2]) 
	//	++ counter_1_4[0 * cols + 2];
	//if (flag_side1[0] && flag_ban4[3]) 
	//	++ counter_1_4[0 * cols + 3];
	char shuffle_mask_ban[] __attribute__ ((aligned(16)))
		= { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };
	char shuffle_mask_side[] __attribute__ ((aligned(16)))
		= { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };

	asm (
			"movdqa (%0), %%xmm1\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (shuffle_mask_ban)
			: /*  clobbered */ "xmm1"
	    );

	asm (
			"movdqa (%0), %%xmm2\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (shuffle_mask_side)
			: /*  clobbered */ "xmm2"
	    );

	// the banner conditions in xmm0
	asm (
			"xor %%eax, %%eax\n\t"
			"movl (%0), %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm0\n\t"
			"pshufb %%xmm1, %%xmm0\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (flag_ban4)
			: /*  clobbered */ "rax", "xmm0" 
	    );

	// the side conditions in xmm3
	asm (
			"xor %%eax, %%eax\n\t"
			"movl (%0), %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm3\n\t"
			"pshufb %%xmm2, %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (flag_side3)
			: /*  clobbered */ "rax", "xmm3"
	    );

	asm (
			"pand %%xmm3, %%xmm0\n\t"
			: /*  outputs */
			: /*  inputs */ 
			: /*  clobbered */ "xmm0"
	    );
	// ==================================================

	asm (
			"pextrd $0, %%xmm0, %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm4\n\t"
    			"pmovsxbd %%xmm4, %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ 
			: /*  clobbered */ "rax", "xmm4", "xmm3"
	    );

	// load the 1st 4 counter variables
	int * my_ptr __attribute__ ((aligned(16))) = counter_3_4;
	asm (
			"movdqa (%0), %%xmm5\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (my_ptr)
			: /*  clobbered */ "xmm5"
	    );

	asm (
		"paddd %%xmm3, %%xmm5\n\t"
			: /*  outputs */ 
			: /*  inputs */ 
			: /*  clobbered */ 
				"xmm5"
	    );

	asm (
		"movdqa %%xmm5, %0\n\t"
			: /*  outputs */ "=m" (*my_ptr)
			: /*  inputs */ 
			: /*  clobbered */ 
				"memory"
	    );
	// ==================================

	asm (
			"pextrd $1, %%xmm0, %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm4\n\t"
    			"pmovsxbd %%xmm4, %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ 
			: /*  clobbered */ "rax", "xmm4", "xmm3"
	    );
	my_ptr += 4;
	asm (
			"movdqa (%0), %%xmm5\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (my_ptr)
			: /*  clobbered */ "xmm5"
	    );

	asm (
		"paddd %%xmm3, %%xmm5\n\t"
			: /*  outputs */ 
			: /*  inputs */ 
			: /*  clobbered */ 
				"xmm5"
	    );

	asm (
		"movdqa %%xmm5, %0\n\t"
			: /*  outputs */ "=m" (*my_ptr)
			: /*  inputs */ 
			: /*  clobbered */ 
				"memory"
	    );
	// ==================================

	asm (
			"pextrd $2, %%xmm0, %%eax\n\t"
			"pinsrd $0, %%eax, %%xmm4\n\t"
    			"pmovsxbd %%xmm4, %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ 
			: /*  clobbered */ "rax", "xmm4", "xmm3"
	    );
	my_ptr += 4;
	asm (
			"movdqa (%0), %%xmm5\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (my_ptr)
			: /*  clobbered */ "xmm5"
	    );

	asm (
		"paddd %%xmm3, %%xmm5\n\t"
			: /*  outputs */ 
			: /*  inputs */ 
			: /*  clobbered */ 
				"xmm5"
	    );

	asm (
		"movdqa %%xmm5, %0\n\t"
			: /*  outputs */ "=m" (*my_ptr)
			: /*  inputs */ 
			: /*  clobbered */ 
				"memory"
	    );




	cout << "counter: ";
	for (int i=0; i<12; ++i) {
		cout << " " << "|" << (int) counter_3_4[i] << "|" ;
		if ( (i+1) % 4 == 0) {
			cout << endl;
		}
	}
	cout << endl;
}


int counter_15_4 [] __attribute__ ((aligned(16))) = {
	  2,   4,   6,   8,
	 10,  12,  14,  16,
	 18,  20,  22,  24,
	 26,  28,  30,  32,
	 34,  36,  38,  40,
	 42,  44,  46,  48,
	 50,  52,  54,  56,
	 58,  60,  62,  64,
	 66,  68,  70,  72,
	 74,  76,  78,  80,
	 82,  84,  86,  88,
	 90,  92,  94,  96,
	 98, 100, 102, 104,
	106, 108, 110, 112,
	114, 116, 118, 120
}; 

char flag_side15 [] = { 
	1, 1, 1, 1, 
	1, 1, 1, 1, 
	1, 1, 1, 1, 
	1, 1, 1, // padding 
		 1
};

void tabulate_side_n_ban4_parallel (
			  int n_side_elements
			, char * side_ptr 
			, int   counter [] 
		)
{
	const int cols = 4;
	//if (flag_side1[0] && flag_ban4[0]) 
	//	++ counter_1_4[0 * cols + 0];
	//if (flag_side1[0] && flag_ban4[1]) 
	//	++ counter_1_4[0 * cols + 1];
	//if (flag_side1[0] && flag_ban4[2]) 
	//	++ counter_1_4[0 * cols + 2];
	//if (flag_side1[0] && flag_ban4[3]) 
	//	++ counter_1_4[0 * cols + 3];
	char shuffle_mask_ban[] __attribute__ ((aligned(16)))
		= { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };
	char shuffle_mask_side[] __attribute__ ((aligned(16)))
		= { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };

	asm (
			"movdqa (%0), %%xmm1\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (shuffle_mask_ban)
			: /*  clobbered */ "xmm1"
	    );

	asm (
			"movdqa (%0), %%xmm2\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (shuffle_mask_side)
			: /*  clobbered */ "xmm2"
	    );

	// the banner conditions in xmm0
	int l_n_side_elements = n_side_elements;
	int * my_ptr __attribute__ ((aligned(16))) = counter;
	if (l_n_side_elements > 4) {

		while (l_n_side_elements > 4) {

			asm (
					"xor %%eax, %%eax\n\t"
					"movl (%0), %%eax\n\t"
					"pinsrd $0, %%eax, %%xmm0\n\t"
					"pshufb %%xmm1, %%xmm0\n\t"
					: /*  outputs */
					: /*  inputs */ "r" (flag_ban4)
					: /*  clobbered */ "rax", "xmm0" 
			    );

			// the side conditions in xmm3
			asm (
					"xor %%eax, %%eax\n\t"
					"movl (%0), %%eax\n\t"
					"pinsrd $0, %%eax, %%xmm3\n\t"
					"pshufb %%xmm2, %%xmm3\n\t"
					: /*  outputs */
					: /*  inputs */ "r" (side_ptr)
					: /*  clobbered */ "rax", "xmm3"
			    );

			asm (
					"pand %%xmm3, %%xmm0\n\t"
					: /*  outputs */
					: /*  inputs */ 
					: /*  clobbered */ "xmm0"
			    );
			// ==================================================

			asm (
					"pextrd $0, %%xmm0, %%eax\n\t"
					"pinsrd $0, %%eax, %%xmm4\n\t"
					"pmovsxbd %%xmm4, %%xmm3\n\t"
					: /*  outputs */
					: /*  inputs */ 
					: /*  clobbered */ "rax", "xmm4", "xmm3"
			    );

			// load the 1st 4 counter variables
			asm (
					"movdqa (%0), %%xmm5\n\t"
					: /*  outputs */
					: /*  inputs */ "r" (my_ptr)
					: /*  clobbered */ "xmm5"
			    );

			asm (
				"paddd %%xmm3, %%xmm5\n\t"
					: /*  outputs */ 
					: /*  inputs */ 
					: /*  clobbered */ 
						"xmm5"
			    );

			asm (
				"movdqa %%xmm5, %0\n\t"
					: /*  outputs */ "=m" (*my_ptr)
					: /*  inputs */ 
					: /*  clobbered */ 
						"memory"
			    );
			// ==================================

			asm (
					"pextrd $1, %%xmm0, %%eax\n\t"
					"pinsrd $0, %%eax, %%xmm4\n\t"
					"pmovsxbd %%xmm4, %%xmm3\n\t"
					: /*  outputs */
					: /*  inputs */ 
					: /*  clobbered */ "rax", "xmm4", "xmm3"
			    );
			// load the 2nd set of 4 counter variables
			my_ptr += 4;
			asm (
					"movdqa (%0), %%xmm5\n\t"
					: /*  outputs */
					: /*  inputs */ "r" (my_ptr)
					: /*  clobbered */ "xmm5"
			    );

			asm (
				"paddd %%xmm3, %%xmm5\n\t"
					: /*  outputs */ 
					: /*  inputs */ 
					: /*  clobbered */ 
						"xmm5"
			    );

			asm (
				"movdqa %%xmm5, %0\n\t"
					: /*  outputs */ "=m" (*my_ptr)
					: /*  inputs */ 
					: /*  clobbered */ 
						"memory"
			    );
			// ==================================

			asm (
					"pextrd $2, %%xmm0, %%eax\n\t"
					"pinsrd $0, %%eax, %%xmm4\n\t"
					"pmovsxbd %%xmm4, %%xmm3\n\t"
					: /*  outputs */
					: /*  inputs */ 
					: /*  clobbered */ "rax", "xmm4", "xmm3"
			    );
			// load the 3rd set of 4 counter variables
			my_ptr += 4;
			asm (
					"movdqa (%0), %%xmm5\n\t"
					: /*  outputs */
					: /*  inputs */ "r" (my_ptr)
					: /*  clobbered */ "xmm5"
			    );

			asm (
				"paddd %%xmm3, %%xmm5\n\t"
					: /*  outputs */ 
					: /*  inputs */ 
					: /*  clobbered */ 
						"xmm5"
			    );

			asm (
				"movdqa %%xmm5, %0\n\t"
					: /*  outputs */ "=m" (*my_ptr)
					: /*  inputs */ 
					: /*  clobbered */ 
						"memory"
			    );

			// ==================================

			asm (
					"pextrd $3, %%xmm0, %%eax\n\t"
					"pinsrd $0, %%eax, %%xmm4\n\t"
					"pmovsxbd %%xmm4, %%xmm3\n\t"
					: /*  outputs */
					: /*  inputs */ 
					: /*  clobbered */ "rax", "xmm4", "xmm3"
			    );
			// load the 4th set of 4 counter variables
			my_ptr += 4;
			asm (
					"movdqa (%0), %%xmm5\n\t"
					: /*  outputs */
					: /*  inputs */ "r" (my_ptr)
					: /*  clobbered */ "xmm5"
			    );

			asm (
				"paddd %%xmm3, %%xmm5\n\t"
					: /*  outputs */ 
					: /*  inputs */ 
					: /*  clobbered */ 
						"xmm5"
			    );

			asm (
				"movdqa %%xmm5, %0\n\t"
					: /*  outputs */ "=m" (*my_ptr)
					: /*  inputs */ 
					: /*  clobbered */ 
						"memory"
			    );


			l_n_side_elements -= 4;
			side_ptr += 4;
			my_ptr += 4;
		}
	}




	cout << "counter: " << endl;
	for (int i=0; i<n_side_elements * 4; ++i) {
		cout << " " << "|" << (int) counter[i] << "|" ;
		if ( (i+1) % 4 == 0) {
			cout << endl;
		}
	}
	cout << endl;
}

void tabulate_side_n_ban_m_parallel (
			  int n_side_elements
			, char * side_ptr
			, int m_ban_elements
			, char * ban_ptr 
			, int   counter [] 
		)
{
	const int cols = 4;
	//if (flag_side1[0] && flag_ban4[0]) 
	//	++ counter_1_4[0 * cols + 0];
	//if (flag_side1[0] && flag_ban4[1]) 
	//	++ counter_1_4[0 * cols + 1];
	//if (flag_side1[0] && flag_ban4[2]) 
	//	++ counter_1_4[0 * cols + 2];
	//if (flag_side1[0] && flag_ban4[3]) 
	//	++ counter_1_4[0 * cols + 3];
	char shuffle_mask_ban[] __attribute__ ((aligned(16)))
		= { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };
	char shuffle_mask_side[] __attribute__ ((aligned(16)))
		= { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };

	asm (
			"movdqa (%0), %%xmm1\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (shuffle_mask_ban)
			: /*  clobbered */ "xmm1"
	    );

	asm (
			"movdqa (%0), %%xmm2\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (shuffle_mask_side)
			: /*  clobbered */ "xmm2"
	    );

	// the banner conditions in xmm0
	int l_n_side_elements = n_side_elements;
	int * my_ptr __attribute__ ((aligned(16))) = counter;
	if (l_n_side_elements > 4) {

		while (l_n_side_elements > 4) {
			int l_m_ban_elements = m_ban_elements;

			while (l_m_ban_elements > 4) {

				asm (
						"xor %%eax, %%eax\n\t"
						"movl (%0), %%eax\n\t"
						"pinsrd $0, %%eax, %%xmm0\n\t"
						"pshufb %%xmm1, %%xmm0\n\t"
						: /*  outputs */
						: /*  inputs */ "r" (ban_ptr)
						: /*  clobbered */ "rax", "xmm0" 
				    );

				// the side conditions in xmm3
				asm (
						"xor %%eax, %%eax\n\t"
						"movl (%0), %%eax\n\t"
						"pinsrd $0, %%eax, %%xmm3\n\t"
						"pshufb %%xmm2, %%xmm3\n\t"
						: /*  outputs */
						: /*  inputs */ "r" (side_ptr)
						: /*  clobbered */ "rax", "xmm3"
				    );

				asm (
						"pand %%xmm3, %%xmm0\n\t"
						: /*  outputs */
						: /*  inputs */ 
						: /*  clobbered */ "xmm0"
				    );
				// ==================================================

				asm (
						"pextrd $0, %%xmm0, %%eax\n\t"
						"pinsrd $0, %%eax, %%xmm4\n\t"
						"pmovsxbd %%xmm4, %%xmm3\n\t"
						: /*  outputs */
						: /*  inputs */ 
						: /*  clobbered */ "rax", "xmm4", "xmm3"
				    );

				// load the 1st 4 counter variables
				asm (
						"movdqa (%0), %%xmm5\n\t"
						: /*  outputs */
						: /*  inputs */ "r" (my_ptr)
						: /*  clobbered */ "xmm5"
				    );

				asm (
					"paddd %%xmm3, %%xmm5\n\t"
						: /*  outputs */ 
						: /*  inputs */ 
						: /*  clobbered */ 
							"xmm5"
				    );

				asm (
					"movdqa %%xmm5, %0\n\t"
						: /*  outputs */ "=m" (*my_ptr)
						: /*  inputs */ 
						: /*  clobbered */ 
							"memory"
				    );
				// ==================================

				asm (
						"pextrd $1, %%xmm0, %%eax\n\t"
						"pinsrd $0, %%eax, %%xmm4\n\t"
						"pmovsxbd %%xmm4, %%xmm3\n\t"
						: /*  outputs */
						: /*  inputs */ 
						: /*  clobbered */ "rax", "xmm4", "xmm3"
				    );
				// load the 2nd set of 4 counter variables
				my_ptr += 4;
				asm (
						"movdqa (%0), %%xmm5\n\t"
						: /*  outputs */
						: /*  inputs */ "r" (my_ptr)
						: /*  clobbered */ "xmm5"
				    );

				asm (
					"paddd %%xmm3, %%xmm5\n\t"
						: /*  outputs */ 
						: /*  inputs */ 
						: /*  clobbered */ 
							"xmm5"
				    );

				asm (
					"movdqa %%xmm5, %0\n\t"
						: /*  outputs */ "=m" (*my_ptr)
						: /*  inputs */ 
						: /*  clobbered */ 
							"memory"
				    );
				// ==================================

				asm (
						"pextrd $2, %%xmm0, %%eax\n\t"
						"pinsrd $0, %%eax, %%xmm4\n\t"
						"pmovsxbd %%xmm4, %%xmm3\n\t"
						: /*  outputs */
						: /*  inputs */ 
						: /*  clobbered */ "rax", "xmm4", "xmm3"
				    );
				// load the 3rd set of 4 counter variables
				my_ptr += 4;
				asm (
						"movdqa (%0), %%xmm5\n\t"
						: /*  outputs */
						: /*  inputs */ "r" (my_ptr)
						: /*  clobbered */ "xmm5"
				    );

				asm (
					"paddd %%xmm3, %%xmm5\n\t"
						: /*  outputs */ 
						: /*  inputs */ 
						: /*  clobbered */ 
							"xmm5"
				    );

				asm (
					"movdqa %%xmm5, %0\n\t"
						: /*  outputs */ "=m" (*my_ptr)
						: /*  inputs */ 
						: /*  clobbered */ 
							"memory"
				    );

				// ==================================

				asm (
						"pextrd $3, %%xmm0, %%eax\n\t"
						"pinsrd $0, %%eax, %%xmm4\n\t"
						"pmovsxbd %%xmm4, %%xmm3\n\t"
						: /*  outputs */
						: /*  inputs */ 
						: /*  clobbered */ "rax", "xmm4", "xmm3"
				    );
				// load the 3rd set of 4 counter variables
				my_ptr += 4;
				asm (
						"movdqa (%0), %%xmm5\n\t"
						: /*  outputs */
						: /*  inputs */ "r" (my_ptr)
						: /*  clobbered */ "xmm5"
				    );

				asm (
					"paddd %%xmm3, %%xmm5\n\t"
						: /*  outputs */ 
						: /*  inputs */ 
						: /*  clobbered */ 
							"xmm5"
				    );

				asm (
					"movdqa %%xmm5, %0\n\t"
						: /*  outputs */ "=m" (*my_ptr)
						: /*  inputs */ 
						: /*  clobbered */ 
							"memory"
				    );
			}


			l_n_side_elements -= 4;
			side_ptr += 4;
			my_ptr += 4;
		}
	}




	cout << "counter: " << endl;
	for (int i=0; i<n_side_elements * 4; ++i) {
		cout << " " << "|" << (int) counter[i] << "|" ;
		if ( (i+1) % 4 == 0) {
			cout << endl;
		}
	}
	cout << endl;
}
#endif /*  0 */

char shuffle_mask_ban16[] __attribute__ ((aligned(16)))
	= { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
char shuffle_mask_side16[] __attribute__ ((aligned(16)))
	= { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

char shuffle_mask_ban8[] __attribute__ ((aligned(16)))
	= { 	0, 1, 2, 3, 4, 5, 6, 7, 
	 	0, 1, 2, 3, 4, 5, 6, 7
	};
char shuffle_mask_side8[] __attribute__ ((aligned(16)))
	= { 	0, 0, 0, 0, 0, 0, 0, 0, 
		1, 1, 1, 1, 1, 1, 1, 1 
	};

void xfer_data (int src[], int dest[], int arr_sz)
{
	int * s_ptr = src;
	int * d_ptr = dest;
	for (int i=0; i < arr_sz; i += 4) {
		asm (
				"movdqu (%0), %%xmm5\n\t"
				: /*  outputs */
				: /*  inputs */ "r" (s_ptr)
				: /*  clobbered */ "xmm5"
		    );

		asm (
			"movdqu %%xmm5, %0\n\t"
				: /*  outputs */ "=m" (*d_ptr)
				: /*  inputs */ 
				: /*  clobbered */ 
					"memory"
		    );
		s_ptr += 4;
		d_ptr +=4;
	}

}

void test1 (char * side_ptr, char * chk_sid)
{
	asm (
			"movdqa (%0), %%xmm2\n\t"
			: /*  outputs */
			: /*  inputs */ "r" (shuffle_mask_side8)
			: /*  clobbered */ "xmm2"
	    );

	int i = 0;

	asm (
			"xor %%eax, %%eax\n\t"
			"movw (%0), %%ax\n\t"
			"pinsrw $0, %%eax, %%xmm3\n\t"
			"pshufb %%xmm2, %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ "r" ( (side_ptr + i*2) )
			: /*  clobbered */ "rax", "xmm3"
	    );

	asm (
		"movdqa %%xmm3, %0\n\t"
			: /*  outputs */ "=m" (*chk_sid)
			: /*  inputs */ 
			: /*  clobbered */ 
				"memory"
	    );
	i += 1;
	chk_sid += 16;

	asm (
			"xor %%eax, %%eax\n\t"
			"movw (%0), %%ax\n\t"
			"pinsrw $0, %%eax, %%xmm3\n\t"
			"pshufb %%xmm2, %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ "r" ( (side_ptr + i*2) )
			: /*  clobbered */ "rax", "xmm3"
	    );

	asm (
		"movdqa %%xmm3, %0\n\t"
			: /*  outputs */ "=m" (*chk_sid)
			: /*  inputs */ 
			: /*  clobbered */ 
				"memory"
	    );
	i += 1;
	chk_sid += 16;

	asm (
			"xor %%eax, %%eax\n\t"
			"movw (%0), %%ax\n\t"
			"pinsrw $0, %%eax, %%xmm3\n\t"
			"pshufb %%xmm2, %%xmm3\n\t"
			: /*  outputs */
			: /*  inputs */ "r" ( (side_ptr + i*2) )
			: /*  clobbered */ "rax", "xmm3"
	    );

	asm (
		"movdqa %%xmm3, %0\n\t"
			: /*  outputs */ "=m" (*chk_sid)
			: /*  inputs */ 
			: /*  clobbered */ 
				"memory"
	    );
	i += 1;
	chk_sid += 16;



}

void tabulate_side_n_ban_m (
			  int n_side_elements
			, char * side_ptr
			, int m_ban_elements
			, char * ban_ptr
			, int   counter []
			, char * chk_sid
			, char * chk_ban
			, char * chk_xmm1
			, char * chk_xmm2
		)
{
	cout 	<< "n_side_elements: " << n_side_elements << endl
		<< "m_ban_elements:  " << m_ban_elements  << endl
		<< endl;
	int l_n_side_elements = n_side_elements;
	int * my_ptr __attribute__ ((aligned(16))) = counter;
	int i = 0, j = 0;
	if (l_n_side_elements > 0) {
		while (l_n_side_elements > 0) {
			//cout << "1 reached here: " << endl;
			int l_m_ban_elements  = m_ban_elements;
			j = 0;
			char * l_ban_ptr = ban_ptr;

			//if        (l_m_ban_elements > 16) {
			//	while (l_m_ban_elements > 16) {
			//		
			//	}
			//} else 
			if (l_m_ban_elements > 8) {
				// we can process only 1 row at a time

				asm (
						"movdqa (%0), %%xmm1\n\t"
						: /*  outputs */
						: /*  inputs */ "r" (shuffle_mask_ban16)
						: /*  clobbered */ "xmm1"
				    );
				asm (
						"movdqa (%0), %%xmm2\n\t"
						: /*  outputs */
						: /*  inputs */ "r" (shuffle_mask_side16)
						: /*  clobbered */ "xmm2"
				    );

				j = 0;
				while (l_m_ban_elements >= 16) {
					cout << "16 reached here: j == " << j 
						<< "l_m_ban_elements: " << l_m_ban_elements
						<< endl;

					//asm (
					//		"movdqa (%0), %%xmm1\n\t"
					//		: /*  outputs */
					//		: /*  inputs */ "r" (shuffle_mask_ban16)
					//		: /*  clobbered */ "xmm1"
					//    );
					//asm (
					//		"movdqa (%0), %%xmm2\n\t"
					//		: /*  outputs */
					//		: /*  inputs */ "r" (shuffle_mask_side16)
					//		: /*  clobbered */ "xmm2"
					//    );

					asm (
							"movdqu (%0), %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (l_ban_ptr)
							: /*  clobbered */ "xmm0" 
					    );

					//asm (
					//		"pshufb %%xmm1, %%xmm0\n\t"
					//		: /*  outputs */
					//		: /*  inputs */ 
					//		: /*  clobbered */ "xmm0" 
					//    );

					// the side conditions in xmm3
					asm (
							"xor %%eax, %%eax\n\t"
							"movb (%0), %%al\n\t"
							"pinsrb $0, %%eax, %%xmm3\n\t"
							"pshufb %%xmm2, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (side_ptr + i)
							: /*  clobbered */ "rax", "xmm3"
					    );

					asm (
						"movdqa %%xmm0, %0\n\t"
							: /*  outputs */ "=m" (*chk_ban)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );

					asm (
						"movdqa %%xmm3, %0\n\t"
							: /*  outputs */ "=m" (*chk_sid)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );

					asm (
							"pand %%xmm3, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0"
					    );

					asm (
						"movdqa %%xmm1, %0\n\t"
							: /*  outputs */ "=m" (*chk_xmm1)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );

					asm (
						"movdqa %%xmm2, %0\n\t"
							: /*  outputs */ "=m" (*chk_xmm2)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );

					// ==================================================

					asm (
							"pextrd $0, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );

					// load the 1st 4 counter variables
					asm (
							"movdqu (%0), %%xmm5\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (my_ptr)
							: /*  clobbered */ "xmm5"
					    );

					asm (
						"paddd %%xmm3, %%xmm5\n\t"
							: /*  outputs */ 
							: /*  inputs */ 
							: /*  clobbered */ 
								"xmm5"
					    );

					asm (
						"movdqu %%xmm5, %0\n\t"
							: /*  outputs */ "=m" (*my_ptr)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );
					my_ptr += 4;
					// ==================================

					asm (
							"pextrd $1, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );
					asm (
							"movdqu (%0), %%xmm5\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (my_ptr)
							: /*  clobbered */ "xmm5"
					    );

					asm (
						"paddd %%xmm3, %%xmm5\n\t"
							: /*  outputs */ 
							: /*  inputs */ 
							: /*  clobbered */ 
								"xmm5"
					    );

					asm (
						"movdqu %%xmm5, %0\n\t"
							: /*  outputs */ "=m" (*my_ptr)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );
					my_ptr += 4;
					// ==================================

					asm (
							"pextrd $2, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );
					asm (
							"movdqu (%0), %%xmm5\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (my_ptr)
							: /*  clobbered */ "xmm5"
					    );

					asm (
						"paddd %%xmm3, %%xmm5\n\t"
							: /*  outputs */ 
							: /*  inputs */ 
							: /*  clobbered */ 
								"xmm5"
					    );

					asm (
						"movdqu %%xmm5, %0\n\t"
							: /*  outputs */ "=m" (*my_ptr)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );
					my_ptr += 4;

					// ==================================

					asm (
							"pextrd $3, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );
					asm (
							"movdqu (%0), %%xmm5\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (my_ptr)
							: /*  clobbered */ "xmm5"
					    );

					asm (
						"paddd %%xmm3, %%xmm5\n\t"
							: /*  outputs */ 
							: /*  inputs */ 
							: /*  clobbered */ 
								"xmm5"
					    );

					asm (
						"movdqu %%xmm5, %0\n\t"
							: /*  outputs */ "=m" (*my_ptr)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );
					my_ptr += 4;

					l_m_ban_elements -= 16;
					l_ban_ptr  += 16;
					chk_sid  += 16;
					chk_ban  += 16;
					chk_xmm1 += 16;
					chk_xmm2 += 16;
					++j;
				}
				while (l_m_ban_elements >= 8) {
					//cout << "8 reached here: " << endl;
					asm (
							"movq (%0), %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (l_ban_ptr)
							: /*  clobbered */ "xmm0" 
					    );

					//asm (
					//		"pshufb %%xmm1, %%xmm0\n\t"
					//		: /*  outputs */
					//		: /*  inputs */ 
					//		: /*  clobbered */ "xmm0" 
					//    );

					// the side conditions in xmm3
					asm (
							"xor %%eax, %%eax\n\t"
							"movb (%0), %%al\n\t"
							"pinsrb $0, %%eax, %%xmm3\n\t"
							"pshufb %%xmm2, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (side_ptr + i)
							: /*  clobbered */ "rax", "xmm3"
					    );

					asm (
							"pand %%xmm3, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0"
					    );

					// ==================================================

					asm (
							"pextrd $0, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );

					// load the 1st 4 counter variables
					asm (
							"movdqu (%0), %%xmm5\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (my_ptr)
							: /*  clobbered */ "xmm5"
					    );

					asm (
						"paddd %%xmm3, %%xmm5\n\t"
							: /*  outputs */ 
							: /*  inputs */ 
							: /*  clobbered */ 
								"xmm5"
					    );

					asm (
						"movdqu %%xmm5, %0\n\t"
							: /*  outputs */ "=m" (*my_ptr)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );
					my_ptr += 4;
					// ==================================

					asm (
							"pextrd $1, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );
					asm (
							"movdqu (%0), %%xmm5\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (my_ptr)
							: /*  clobbered */ "xmm5"
					    );

					asm (
						"paddd %%xmm3, %%xmm5\n\t"
							: /*  outputs */ 
							: /*  inputs */ 
							: /*  clobbered */ 
								"xmm5"
					    );

					asm (
						"movdqu %%xmm5, %0\n\t"
							: /*  outputs */ "=m" (*my_ptr)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );
					my_ptr += 4;

					l_m_ban_elements -= 8;
					l_ban_ptr += 8;
					++j;

				}
				while (l_m_ban_elements >= 4) {
					//cout << "4 reached here: " << endl;

					asm (
							"movl (%0), %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (l_ban_ptr)
							: /*  clobbered */ "xmm0", "rax" 
					    );

					asm (
							"pshufb %%xmm1, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0" 
					    );

					// the side conditions in xmm3
					asm (
							"xor %%eax, %%eax\n\t"
							"movb (%0), %%al\n\t"
							"pinsrb $0, %%eax, %%xmm3\n\t"
							"pshufb %%xmm2, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (side_ptr + i)
							: /*  clobbered */ "rax", "xmm3"
					    );

					asm (
							"pand %%xmm3, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0"
					    );

					// ==================================================

					asm (
							"pextrd $0, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );

					// load the 1st 4 counter variables
					asm (
							"movdqu (%0), %%xmm5\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (my_ptr)
							: /*  clobbered */ "xmm5"
					    );

					asm (
						"paddd %%xmm3, %%xmm5\n\t"
							: /*  outputs */ 
							: /*  inputs */ 
							: /*  clobbered */ 
								"xmm5"
					    );

					asm (
						"movdqu %%xmm5, %0\n\t"
							: /*  outputs */ "=m" (*my_ptr)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );
					my_ptr += 4;


					l_m_ban_elements -= 4;
					l_ban_ptr += 4;
					++j;

				}
				while (l_m_ban_elements >= 2) {
					//cout << "4 reached here: " << endl;

					asm (
							"xor %%eax, %%eax\n\t"
							"movw (%0), %%ax\n\t"
							"pinsrw $0, %%eax, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (l_ban_ptr)
							: /*  clobbered */ "xmm0", "rax" 
					    );

					asm (
							"pshufb %%xmm1, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0" 
					    );

					// the side conditions in xmm3
					asm (
							"xor %%eax, %%eax\n\t"
							"movb (%0), %%al\n\t"
							"pinsrb $0, %%eax, %%xmm3\n\t"
							"pshufb %%xmm2, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (side_ptr + i)
							: /*  clobbered */ "rax", "xmm3"
					    );

					asm (
							"pand %%xmm3, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0"
					    );

					// ==================================================

					asm (
							"pextrd $0, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );

					// load the 1st 4 counter variables
					asm (
							"movq (%0), %%xmm5\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (my_ptr)
							: /*  clobbered */ "xmm5"
					    );

					asm (
						"paddd %%xmm3, %%xmm5\n\t"
							: /*  outputs */ 
							: /*  inputs */ 
							: /*  clobbered */ 
								"xmm5"
					    );

					asm (
						"movq %%xmm5, %0\n\t"
							: /*  outputs */ "=m" (*my_ptr)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );
					my_ptr += 2;


					l_m_ban_elements -= 2;
					l_ban_ptr += 2;
					++j;

				}
				if (l_m_ban_elements == 1) {
					//cout << "4 reached here: " << endl;
					if (ban_ptr[0] && side_ptr[i]) {
						++ my_ptr[0];
					}

					++my_ptr ;


					--l_m_ban_elements ;
					++l_ban_ptr ;
					++j;
				}

				--l_n_side_elements;
				//++side_ptr;
				//cout << "3 reached here: l_m_ban_elements:" 
				//	<< l_m_ban_elements
				//	<< endl;
				++i;
			} else if (l_m_ban_elements == 8) {
				// we can process 2 rows at a time
				// and 16 banner conditions in 1 go
				//cout << "reached here l_m_ban_elements == 8" << endl;

				asm (
						"movdqa (%0), %%xmm1\n\t"
						: /*  outputs */
						: /*  inputs */ "r" (shuffle_mask_ban8)
						: /*  clobbered */ "xmm1"
				    );
				asm (
						"movdqa (%0), %%xmm2\n\t"
						: /*  outputs */
						: /*  inputs */ "r" (shuffle_mask_side8)
						: /*  clobbered */ "xmm2"
				    );
				if (l_n_side_elements >= 2) {
					//while (l_m_ban_elements != 0) 
					{
						//cout << "looping i:" << i << endl;

						asm (
								"movq (%0), %%xmm0\n\t"
								: /*  outputs */
								: /*  inputs */ "r" (l_ban_ptr)
								: /*  clobbered */ "xmm0" 
						    );

						asm (
								"pshufb %%xmm1, %%xmm0\n\t"
								: /*  outputs */
								: /*  inputs */ 
								: /*  clobbered */ "xmm0" 
						    );

						asm (
								"xor %%eax, %%eax\n\t"
								"movw (%0), %%ax\n\t"
								"pinsrw $0, %%eax, %%xmm3\n\t"
								"pshufb %%xmm2, %%xmm3\n\t"
								: /*  outputs */
								: /*  inputs */ "r" ( (side_ptr + i) )
								: /*  clobbered */ "rax", "xmm3"
						    );

						asm (
							"movdqa %%xmm0, %0\n\t"
								: /*  outputs */ "=m" (*chk_ban)
								: /*  inputs */ 
								: /*  clobbered */ 
									"memory"
						    );

						asm (
							"movdqa %%xmm3, %0\n\t"
								: /*  outputs */ "=m" (*chk_sid)
								: /*  inputs */ 
								: /*  clobbered */ 
									"memory"
						    );

						asm (
								"pand %%xmm3, %%xmm0\n\t"
								: /*  outputs */
								: /*  inputs */ 
								: /*  clobbered */ "xmm0"
						    );

						asm (
							"movdqa %%xmm1, %0\n\t"
								: /*  outputs */ "=m" (*chk_xmm1)
								: /*  inputs */ 
								: /*  clobbered */ 
									"memory"
						    );

						asm (
							"movdqa %%xmm2, %0\n\t"
								: /*  outputs */ "=m" (*chk_xmm2)
								: /*  inputs */ 
								: /*  clobbered */ 
									"memory"
						    );
						// counter 0-7 ==================================================
						asm (
								"pextrd $0, %%xmm0, %%eax\n\t"
								"pinsrd $0, %%eax, %%xmm4\n\t"
								"pmovsxbd %%xmm4, %%xmm3\n\t"
								: /*  outputs */
								: /*  inputs */ 
								: /*  clobbered */ "rax", "xmm4", "xmm3"
						    );
						// load the 1st 4 counter variables
						asm (
								"movdqa (%0), %%xmm5\n\t"
								: /*  outputs */
								: /*  inputs */ "r" (my_ptr)
								: /*  clobbered */ "xmm5"
						    );
						asm (
							"paddd %%xmm3, %%xmm5\n\t"
								: /*  outputs */ 
								: /*  inputs */ 
								: /*  clobbered */ 
									"xmm5"
						    );
						asm (
							"movdqa %%xmm5, %0\n\t"
								: /*  outputs */ "=m" (*my_ptr)
								: /*  inputs */ 
								: /*  clobbered */ 
									"memory"
						    );
						my_ptr += 4;
						// ==================================================
						asm (
								"pextrd $1, %%xmm0, %%eax\n\t"
								"pinsrd $0, %%eax, %%xmm4\n\t"
								"pmovsxbd %%xmm4, %%xmm3\n\t"
								: /*  outputs */
								: /*  inputs */ 
								: /*  clobbered */ "rax", "xmm4", "xmm3"
						    );
						// load the 2nd 4 counter variables
						asm (
								"movdqu (%0), %%xmm5\n\t"
								: /*  outputs */
								: /*  inputs */ "r" (my_ptr)
								: /*  clobbered */ "xmm5"
						    );
						asm (
							"paddd %%xmm3, %%xmm5\n\t"
								: /*  outputs */ 
								: /*  inputs */ 
								: /*  clobbered */ 
									"xmm5"
						    );
						asm (
							"movdqu %%xmm5, %0\n\t"
								: /*  outputs */ "=m" (*my_ptr)
								: /*  inputs */ 
								: /*  clobbered */ 
									"memory"
						    );
						my_ptr += 4;

						// counter 0-7 ==================================================
						asm (
								"pextrd $2, %%xmm0, %%eax\n\t"
								"pinsrd $0, %%eax, %%xmm4\n\t"
								"pmovsxbd %%xmm4, %%xmm3\n\t"
								: /*  outputs */
								: /*  inputs */ 
								: /*  clobbered */ "rax", "xmm4", "xmm3"
						    );
						// load the 1st 4 counter variables - of 2nd row
						asm (
								"movdqu (%0), %%xmm5\n\t"
								: /*  outputs */
								: /*  inputs */ "r" (my_ptr)
								: /*  clobbered */ "xmm5"
						    );
						asm (
							"paddd %%xmm3, %%xmm5\n\t"
								: /*  outputs */ 
								: /*  inputs */ 
								: /*  clobbered */ 
									"xmm5"
						    );
						asm (
							"movdqu %%xmm5, %0\n\t"
								: /*  outputs */ "=m" (*my_ptr)
								: /*  inputs */ 
								: /*  clobbered */ 
									"memory"
						    );
						my_ptr += 4;
						// ==================================================
						asm (
								"pextrd $3, %%xmm0, %%eax\n\t"
								"pinsrd $0, %%eax, %%xmm4\n\t"
								"pmovsxbd %%xmm4, %%xmm3\n\t"
								: /*  outputs */
								: /*  inputs */ 
								: /*  clobbered */ "rax", "xmm4", "xmm3"
						    );
						// load the 2nd 4 counter variables - of second row
						asm (
								"movdqu (%0), %%xmm5\n\t"
								: /*  outputs */
								: /*  inputs */ "r" (my_ptr)
								: /*  clobbered */ "xmm5"
						    );
						asm (
							"paddd %%xmm3, %%xmm5\n\t"
								: /*  outputs */ 
								: /*  inputs */ 
								: /*  clobbered */ 
									"xmm5"
						    );
						asm (
							"movdqu %%xmm5, %0\n\t"
								: /*  outputs */ "=m" (*my_ptr)
								: /*  inputs */ 
								: /*  clobbered */ 
									"memory"
						    );
						my_ptr += 4;
						l_m_ban_elements -= 8;
						l_n_side_elements -= 2;
						i += 2;
						chk_sid  += 16;
						chk_ban  += 16;
					}
				} else if (  l_n_side_elements == 1)  {
					//cout << "l_n_side_elements == 1:" << l_n_side_elements << endl;

					asm (
							"movq (%0), %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (l_ban_ptr)
							: /*  clobbered */ "xmm0" 
					    );

					asm (
							"pshufb %%xmm1, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0" 
					    );

					asm (
							"xor %%eax, %%eax\n\t"
							"movb (%0), %%al\n\t"
							"pinsrb $0, %%eax, %%xmm3\n\t"
							"pshufb %%xmm2, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (side_ptr + i)
							: /*  clobbered */ "rax", "xmm3"
					    );

					asm (
						"movq %%xmm0, %0\n\t"
							: /*  outputs */ "=m" (*chk_ban)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );

					asm (
						"movq %%xmm3, %0\n\t"
							: /*  outputs */ "=m" (*chk_sid)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );

					asm (
							"pand %%xmm3, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0"
					    );
					// counter 0-7 ==================================================
					asm (
							"pextrd $0, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );
					// load the 1st 4 counter variables
					asm (
							"movdqu (%0), %%xmm5\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (my_ptr)
							: /*  clobbered */ "xmm5"
					    );
					asm (
						"paddd %%xmm3, %%xmm5\n\t"
							: /*  outputs */ 
							: /*  inputs */ 
							: /*  clobbered */ 
								"xmm5"
					    );
					asm (
						"movdqu %%xmm5, %0\n\t"
							: /*  outputs */ "=m" (*my_ptr)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );
					my_ptr += 4;
					// ==================================================
					asm (
							"pextrd $1, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );
					// load the 2nd 4 counter variables
					asm (
							"movdqu (%0), %%xmm5\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (my_ptr)
							: /*  clobbered */ "xmm5"
					    );
					asm (
						"paddd %%xmm3, %%xmm5\n\t"
							: /*  outputs */ 
							: /*  inputs */ 
							: /*  clobbered */ 
								"xmm5"
					    );
					asm (
						"movdqu %%xmm5, %0\n\t"
							: /*  outputs */ "=m" (*my_ptr)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );
					my_ptr += 4;
					i += 1;
					l_n_side_elements -= 1;
					chk_sid += 8;
					chk_ban += 8;


				}
			} else if (l_m_ban_elements >= 4 /*  && l_m_ban_elements <=7 */) {
				// we can process 2 rows at a time
				// and between 10 - 14 conditions in 1 go
				cout << "l_m_ban_elements > 4: i == " << i << endl;

				asm (
						"movdqa (%0), %%xmm1\n\t"
						: /*  outputs */
						: /*  inputs */ "r" (shuffle_mask_ban8)
						: /*  clobbered */ "xmm1"
				    );
				asm (
						"movdqa (%0), %%xmm2\n\t"
						: /*  outputs */
						: /*  inputs */ "r" (shuffle_mask_side8)
						: /*  clobbered */ "xmm2"
				    );
				if (l_n_side_elements >= 2) {
					//while (l_m_ban_elements > 4) {
					asm (
							"movq (%0), %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (l_ban_ptr)
							: /*  clobbered */ "xmm0" 
					    );

					asm (
							"pshufb %%xmm1, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0" 
					    );

					asm (
							"xor %%eax, %%eax\n\t"
							"movw (%0), %%ax\n\t"
							"pinsrw $0, %%eax, %%xmm3\n\t"
							"pshufb %%xmm2, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (side_ptr + i)
							: /*  clobbered */ "rax", "xmm3"
					    );

					asm (
						"movdqu %%xmm0, %0\n\t"
							: /*  outputs */ "=m" (*chk_ban)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );

					asm (
						"movdqu %%xmm3, %0\n\t"
							: /*  outputs */ "=m" (*chk_sid)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );

					asm (
							"pand %%xmm3, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0"
					    );

					// ======= Process the 1st Row ======================

					asm (
							"pextrd $0, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );
					// load the 1st 4 counter variables
					asm (
							"movdqu (%0), %%xmm5\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (my_ptr)
							: /*  clobbered */ "xmm5"
					    );

					asm (
						"paddd %%xmm3, %%xmm5\n\t"
							: /*  outputs */ 
							: /*  inputs */ 
							: /*  clobbered */ 
								"xmm5"
					    );

					asm (
						"movdqu %%xmm5, %0\n\t"
							: /*  outputs */ "=m" (*my_ptr)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );
					my_ptr += 4;

					// note l_m_ban_elements < 8 otherwise the above if condition would
					// have trapped it
					char residue = l_m_ban_elements - 4;
					// residue can be 3, 2, 1
					if (residue > 1) {
						// note - although we are extracting the double word
						// we only need the 1st 2 bytes of it.
						asm (
								"pextrd $1, %%xmm0, %%eax\n\t"
								"pinsrd $0, %%eax, %%xmm4\n\t"
								"pmovsxbd %%xmm4, %%xmm3\n\t"
								: /*  outputs */
								: /*  inputs */ 
								: /*  clobbered */ "rax", "xmm4", "xmm3"
						    );
						// load the next 2 counter variables
						asm (
								"movq (%0), %%xmm5\n\t"
								: /*  outputs */
								: /*  inputs */ "r" (my_ptr)
								: /*  clobbered */ "xmm5"
						    );

						asm (
							"paddd %%xmm3, %%xmm5\n\t"
								: /*  outputs */ 
								: /*  inputs */ 
								: /*  clobbered */ 
									"xmm5"
						    );

						asm (
							"movq %%xmm5, %0\n\t"
								: /*  outputs */ "=m" (*my_ptr)
								: /*  inputs */ 
								: /*  clobbered */ 
									"memory"
						    );
						my_ptr += 2;
						residue -= 2;
					}
					if (residue == 1) {
						// let the compiler do this
						// nxd l_ban_ptr[6] will not work for 
						//
						if (side_ptr[i] && l_ban_ptr[6]) {
							++ my_ptr[0];
						}
						++my_ptr;
					}
					// ======= Process the 2nd Row ======================

					asm (
							"pextrd $2, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );
					// load the 1st 4 counter variables
					asm (
							"movdqu (%0), %%xmm5\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (my_ptr)
							: /*  clobbered */ "xmm5"
					    );

					asm (
						"paddd %%xmm3, %%xmm5\n\t"
							: /*  outputs */ 
							: /*  inputs */ 
							: /*  clobbered */ 
								"xmm5"
					    );

					asm (
						"movdqu %%xmm5, %0\n\t"
							: /*  outputs */ "=m" (*my_ptr)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );
					my_ptr += 4;

					// note l_m_ban_elements < 8 otherwise the above if condition would
					// have trapped it
					residue = l_m_ban_elements - 4;
					// residue can be 3, 2, 1
					if (residue > 1) {
						// note - although we are extracting the double word
						// we only need the 1st 2 bytes of it.
						asm (
								"pextrd $3, %%xmm0, %%eax\n\t"
								"pinsrd $0, %%eax, %%xmm4\n\t"
								"pmovsxbd %%xmm4, %%xmm3\n\t"
								: /*  outputs */
								: /*  inputs */ 
								: /*  clobbered */ "rax", "xmm4", "xmm3"
						    );
						// load the next 2 counter variables
						asm (
								"movq (%0), %%xmm5\n\t"
								: /*  outputs */
								: /*  inputs */ "r" (my_ptr)
								: /*  clobbered */ "xmm5"
						    );

						asm (
							"paddd %%xmm3, %%xmm5\n\t"
								: /*  outputs */ 
								: /*  inputs */ 
								: /*  clobbered */ 
									"xmm5"
						    );

						asm (
							"movq %%xmm5, %0\n\t"
								: /*  outputs */ "=m" (*my_ptr)
								: /*  inputs */ 
								: /*  clobbered */ 
									"memory"
						    );
						my_ptr += 2;
						residue -= 2;
					}
					if (residue == 1) {
						// let the compiler do this
						if (side_ptr[i] && l_ban_ptr[6]) {
							++ my_ptr[0];
							++my_ptr;
						}
					}

					i += 2;
					l_n_side_elements -= 2;
					chk_sid  += 16;
					chk_ban  += 16;

					//my_ptr += 4;
				//}
				}
				if (l_n_side_elements == 1) {
					// start programming from here : nxd
					//while (l_m_ban_elements > 4) {
					asm (
							"movq (%0), %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (l_ban_ptr)
							: /*  clobbered */ "xmm0" 
					    );

					asm (
							"pshufb %%xmm1, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0" 
					    );

					asm (
							"xor %%eax, %%eax\n\t"
							"movb (%0), %%al\n\t"
							"pinsrb $0, %%eax, %%xmm3\n\t"
							"pshufb %%xmm2, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (side_ptr + i)
							: /*  clobbered */ "rax", "xmm3"
					    );

					asm (
						"movdqu %%xmm0, %0\n\t"
							: /*  outputs */ "=m" (*chk_ban)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );

					asm (
						"movdqu %%xmm3, %0\n\t"
							: /*  outputs */ "=m" (*chk_sid)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );

					asm (
							"pand %%xmm3, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0"
					    );

					// ======= Process the 1st Row ======================

					asm (
							"pextrd $0, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );
					// load the 1st 4 counter variables
					asm (
							"movdqu (%0), %%xmm5\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (my_ptr)
							: /*  clobbered */ "xmm5"
					    );

					asm (
						"paddd %%xmm3, %%xmm5\n\t"
							: /*  outputs */ 
							: /*  inputs */ 
							: /*  clobbered */ 
								"xmm5"
					    );

					asm (
						"movdqu %%xmm5, %0\n\t"
							: /*  outputs */ "=m" (*my_ptr)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );
					my_ptr += 4;

					// note l_m_ban_elements < 8 otherwise the above if condition would
					// have trapped it
					char residue = l_m_ban_elements - 4;
					// residue can be 3, 2, 1
					if (residue > 1) {
						// note - although we are extracting the double word
						// we only need the 1st 2 bytes of it.
						asm (
								"pextrd $1, %%xmm0, %%eax\n\t"
								"pinsrd $0, %%eax, %%xmm4\n\t"
								"pmovsxbd %%xmm4, %%xmm3\n\t"
								: /*  outputs */
								: /*  inputs */ 
								: /*  clobbered */ "rax", "xmm4", "xmm3"
						    );
						// load the next 2 counter variables
						asm (
								"movq (%0), %%xmm5\n\t"
								: /*  outputs */
								: /*  inputs */ "r" (my_ptr)
								: /*  clobbered */ "xmm5"
						    );

						asm (
							"paddd %%xmm3, %%xmm5\n\t"
								: /*  outputs */ 
								: /*  inputs */ 
								: /*  clobbered */ 
									"xmm5"
						    );

						asm (
							"movq %%xmm5, %0\n\t"
								: /*  outputs */ "=m" (*my_ptr)
								: /*  inputs */ 
								: /*  clobbered */ 
									"memory"
						    );
						my_ptr += 2;
						residue -= 2;
					}
					if (residue == 1) {
						// let the compiler do this
						if (side_ptr[i] && l_ban_ptr[6]) {
							++ my_ptr[0];
						}
						++my_ptr;
					}


					i += 1;
					l_n_side_elements -= 1;
					chk_sid  += 16;
					chk_ban  += 16;

					//my_ptr += 4;
				//}
				}
			} else if (l_m_ban_elements > 2 ) {
				// we can process 4 rows at a time
				while (l_m_ban_elements > 2) {
					
				}
			} else if (l_m_ban_elements == 2) {
				// we can process 8 rows at a time
			} else if (l_m_ban_elements == 1) {
				// we can process 8 rows at a time
			}
			//while (l_m_ban_elements > 4) {
			//	cout << "processing banner elements: "
			//		<< 4 * j
			//		<< " - "
			//		<< 4 * j + 4 - 1
			//		<< endl;
			//	l_m_ban_elements -= 4;
			//	++j;
			//}
			//int ban_residue = l_m_ban_elements % 4;
			//if (ban_residue == 1) {
			//	cout << "processing ban residue: " << ban_residue << endl;
			//} else if (ban_residue == 2) {
			//	cout << "processing ban residue: " << ban_residue << endl;
			//} else if (ban_residue == 3) {
			//	cout << "processing ban residue: " << ban_residue << endl;
			//}
			//
			//l_n_side_elements -= 1;
			// cant do it here (++i)
			// ++i;
			//   4 row (when 2 < l_m_ban_elements <= 4)
			// sometimes we process 
			//   1 row (when l_m_ban_elements > 8)
			//   2 row (when 4 < l_m_ban_elements <= 8)
		}
	}
	//int side_residue = l_n_side_elements % 4;
	//if (side_residue == 1) {
	//	cout << "processing residue: " << side_residue << endl;
	//} else if (side_residue == 2) {
	//	cout << "processing residue: " << side_residue << endl;
	//} else if (side_residue == 3) {
	//	cout << "processing residue: " << side_residue << endl;
	//}
}

#if 0
void tabulate_side_n_ban_m_skeleton (
			  int n_side_elements
			, char * side_ptr
			, int m_ban_elements
			, char * ban_ptr
			, int   counter []
		)
{
	cout 	<< "n_side_elements: " << n_side_elements << endl
		<< "m_ban_elements:  " << m_ban_elements  << endl
		<< endl;
	int l_n_side_elements = n_side_elements;
	int i = 0, j = 0;
	if (l_n_side_elements > 0) {
		while (l_n_side_elements > 0) {
			int l_m_ban_elements  = m_ban_elements;
			j = 0;

			//if        (l_m_ban_elements > 16) {
			//	while (l_m_ban_elements > 16) {
			//		
			//	}
			//} else 
			if (l_m_ban_elements > 8 ) {
				// we can process only 1 row at a time
				char shuffle_mask_ban[] __attribute__ ((aligned(16)))
					= { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
				char shuffle_mask_side[] __attribute__ ((aligned(16)))
					= { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
				asm (
						"movdqa (%0), %%xmm1\n\t"
						: /*  outputs */
						: /*  inputs */ "r" (shuffle_mask_ban)
						: /*  clobbered */ "xmm1"
				    );
				asm (
						"movdqa (%0), %%xmm2\n\t"
						: /*  outputs */
						: /*  inputs */ "r" (shuffle_mask_side)
						: /*  clobbered */ "xmm2"
				    );
				while (l_m_ban_elements > 16) {

					asm (
							"movdqa (%0), %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (ban_ptr)
							: /*  clobbered */ "rax", "xmm0" 
					    );

					// the side conditions in xmm3
					asm (
							"xor %%eax, %%eax\n\t"
							"movb (%0), %%al\n\t"
							"pinsrb $0, %%eax, %%xmm3\n\t"
							"pshufb %%xmm2, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (side_ptr)
							: /*  clobbered */ "rax", "xmm3"
					    );

					asm (
							"pand %%xmm3, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0"
					    );

					asm (
							"pextrd $0, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );

				}
			} else if (l_m_ban_elements > 4 ) {
				// we can process 2 rows at a time
				while (l_m_ban_elements > 4) {
					
				}
			} else if (l_m_ban_elements > 2 ) {
				// we can process 4 rows at a time
				while (l_m_ban_elements > 2) {
					
				}
			} else if (l_m_ban_elements == 2) {
				// we can process 8 rows at a time
			} else if (l_m_ban_elements == 1) {
				// we can process 8 rows at a time
			}
			//while (l_m_ban_elements > 4) {
			//	cout << "processing banner elements: "
			//		<< 4 * j
			//		<< " - "
			//		<< 4 * j + 4 - 1
			//		<< endl;
			//	l_m_ban_elements -= 4;
			//	++j;
			//}
			//int ban_residue = l_m_ban_elements % 4;
			//if (ban_residue == 1) {
			//	cout << "processing ban residue: " << ban_residue << endl;
			//} else if (ban_residue == 2) {
			//	cout << "processing ban residue: " << ban_residue << endl;
			//} else if (ban_residue == 3) {
			//	cout << "processing ban residue: " << ban_residue << endl;
			//}
			//
			//l_n_side_elements -= 1;
			//++i;
		}
	}
	//int side_residue = l_n_side_elements % 4;
	//if (side_residue == 1) {
	//	cout << "processing residue: " << side_residue << endl;
	//} else if (side_residue == 2) {
	//	cout << "processing residue: " << side_residue << endl;
	//} else if (side_residue == 3) {
	//	cout << "processing residue: " << side_residue << endl;
	//}
}
#endif /*  0  */

void print_counter (int counter[], int n_side, int m_ban)
{
	for (int i=0; i < n_side; ++i) {
		for (int j=0; j < m_ban; ++j) {
			cout << " " << counter[i*m_ban + j];
		}
		cout << endl;
	}

}

	//const int m_ban_elements = 32;
	//const int m_ban_elements = 40;
	//const int m_ban_elements = 44;
	//const int m_ban_elements = 47;
	//int counter[7 * m_ban_elements] ;
	//const int m_ban_elements = 8;
	//int counter[7 * m_ban_elements] ;
	const int m_ban_elements = 7;
	int counter[7 * m_ban_elements] ;

int main()
{
	//tabulate_side4_ban1_parallel ();
	//set_counter_4_2();
	//tabulate_side4_ban2();
	//set_counter_4_2();
	//tabulate_side4_ban2_parallel ();
	//set_counter_4_3();
	//tabulate_side4_ban3 ();
	//set_counter_4_3();
	//tabulate_side4_ban3_parallel ();
	//tabulate_side4_ban4_parallel ();
	//tabulate_side4_ban5_parallel ();
	//tabulate_side4_ban6_parallel ();
	//int n_ban_elements = 15;
	//int n_side_elements = 4;
	//tabulate_side4_ban_n_parallel (
	//		  n_ban_elements 
	//		, flag_ban15
	//		, counter_4_15
	//		, n_side_elements
	//	);

	//tabulate_side1_ban4_parallel ();
	//tabulate_side2_ban4_parallel ();
	//tabulate_side3_ban4_parallel ();
	//tabulate_side_n_ban4_parallel (
	//		//5,
	//		15,
	//		flag_side15,
	//		counter_15_4
	//		);
	/* 
	{

		int n_side_elements = 7;
		int m_ban_elements = 19;
		char * side_ptr = 0;
		char * ban_ptr = 0;
		int counter[] = { 1, 2, 3, 4};

		tabulate_side_n_ban_m_skeleton (
				  n_side_elements
				, side_ptr
				, m_ban_elements
				, ban_ptr 
				, counter 
			);
	}
	*/
	/* {

		int n_side_elements = 7;
		//const int m_ban_elements = 44;
		char flag_ban[m_ban_elements] __attribute__ ((aligned(16)));
		char flag_side_7[8]  __attribute__ ((aligned(16)));;
		char * side_ptr __attribute__ ((aligned(16))) = flag_side_7;
		char * ban_ptr   __attribute__ ((aligned(16))) = flag_ban;
		char  chk_sid  [m_ban_elements * 7] __attribute__ ((aligned(16))); 
		char  chk_ban  [m_ban_elements * 7] __attribute__ ((aligned(16))); 
		char  chk_xmm1 [m_ban_elements * 7] __attribute__ ((aligned(16))); 
		char  chk_xmm2 [m_ban_elements * 7] __attribute__ ((aligned(16))); 

		for (int i=0; i < 7; ++i) {
			for (int j=0; j < m_ban_elements; ++j) {
				counter [i*m_ban_elements + j] = j + (i+1)*10;
				chk_sid [i*m_ban_elements + j] = 0;
				chk_ban [i*m_ban_elements + j] = 0;
				chk_xmm1[i*m_ban_elements + j] = 0;
				chk_xmm2[i*m_ban_elements + j] = 0;
			}
			flag_side_7[i] = 1;
			//flag_side_7[i] = i;
		}
		for (int j=0; j < m_ban_elements; ++j) {
			if (j%2==0)
				flag_ban[j] = 1;
			else 
				flag_ban[j] = 0;
			
			//flag_ban[j] = j;
		}
		//flag_side_7[0] = 0;
		flag_side_7[1] = 0;
		//flag_side_7[3] = 0;
		flag_side_7[5] = 0;

		print_counter (counter, 7, m_ban_elements);

		tabulate_side_n_ban_m (
				  n_side_elements
				, side_ptr
				, m_ban_elements
				, ban_ptr 
				, counter 
				, chk_sid
				, chk_ban
				, chk_xmm1
				, chk_xmm2
		);

		print_counter (counter, 7, m_ban_elements);
		for (int i=0; i < 7; ++i) {
			for (int j=0; j < m_ban_elements; ++j) {
				cout << (int) chk_sid[i * m_ban_elements + j] ;
			}
			cout << endl;
			for (int j=0; j < m_ban_elements; ++j) {
				cout << (int) chk_ban[i * m_ban_elements + j] ;
			}
			cout << endl;
			for (int j=0; j < m_ban_elements; ++j) {
				cout << (int) chk_xmm1[i * m_ban_elements + j] ;
			}
			cout << endl;
			for (int j=0; j < m_ban_elements; ++j) {
				cout << (int) chk_xmm2[i * m_ban_elements + j] ;
			}
			cout << endl;
			cout << endl;
		}



	} */
	/* 
	{

		//int n_side_elements = 7;
		int n_side_elements = 7;
		//const int m_ban_elements = 44;
		char flag_ban[m_ban_elements] __attribute__ ((aligned(16)));
		char flag_side_7[8]  __attribute__ ((aligned(16)));;
		char * side_ptr __attribute__ ((aligned(16))) = flag_side_7;
		char * ban_ptr   __attribute__ ((aligned(16))) = flag_ban;
		//char  chk_sid  [m_ban_elements * 7] __attribute__ ((aligned(16))); 
		//char  chk_ban  [m_ban_elements * 7] __attribute__ ((aligned(16))); 
		//char  chk_xmm1 [m_ban_elements * 7] __attribute__ ((aligned(16))); 
		//char  chk_xmm2 [m_ban_elements * 7] __attribute__ ((aligned(16))); 

		char  chk_sid  [2 * m_ban_elements * 7] __attribute__ ((aligned(16))); 
		char  chk_ban  [2 * m_ban_elements * 7] __attribute__ ((aligned(16))); 
		char  chk_xmm1 [2 * m_ban_elements * 7] __attribute__ ((aligned(16))); 
		char  chk_xmm2 [2 * m_ban_elements * 7] __attribute__ ((aligned(16))); 

		for (int i=0; i < 7; ++i) {
			for (int j=0; j < m_ban_elements; ++j) {
				counter [i*m_ban_elements + j] = j + (i+1)*10;
				chk_sid [i*m_ban_elements + j] = 0;
				chk_ban [i*m_ban_elements + j] = 0;
				chk_xmm1[i*m_ban_elements + j] = 0;
				chk_xmm2[i*m_ban_elements + j] = 0;
			}
			//flag_side_7[i] = 21;
			flag_side_7[i] = 1;
			//flag_side_7[i] = i;
		}
		for (int j=0; j < m_ban_elements; ++j) {
			if (j%2==0)
				flag_ban[j] = 1;
			else 
				flag_ban[j] = 0;
			//flag_ban[j] = j*2;
			//flag_ban[j] = 1;
			
			//flag_ban[j] = j;
		}
		//flag_side_7[0] = 0;
		//flag_side_7[1] = 0;
		//flag_side_7[2] = 0;
		//flag_side_7[3] = 0;
		//flag_side_7[4] = 0;
		//flag_side_7[5] = 0;
		//flag_side_7[6] = 0;

		print_counter (counter, 7, m_ban_elements);

		tabulate_side_n_ban_m (
				  n_side_elements
				, side_ptr
				, m_ban_elements
				, ban_ptr 
				, counter 
				, chk_sid
				, chk_ban
				, chk_xmm1
				, chk_xmm2
		);

		print_counter (counter, 7, m_ban_elements);
		//for (int i=0; i < 7; ++i)
		for (int i=0; i < 7; ++i) {
			for (int j=0; j < m_ban_elements; ++j) {
				cout << (int) chk_sid[i * m_ban_elements + j] ;
			}
			cout << endl;
			for (int j=0; j < m_ban_elements; ++j) {
				cout << (int) chk_ban[i * m_ban_elements + j] ;
			}
			cout << endl;
			//for (int j=0; j < m_ban_elements; ++j) {
			//	cout << (int) chk_xmm1[i * m_ban_elements + j] ;
			//}
			//cout << endl;
			//for (int j=0; j < m_ban_elements; ++j) {
			//	cout << (int) chk_xmm2[i * m_ban_elements + j] ;
			//}
			cout << " ================== " << endl;
		}
	} */
	{

		//int n_side_elements = 7;
		int n_side_elements = 6;
		//const int m_ban_elements = 44;
		char flag_ban[m_ban_elements] __attribute__ ((aligned(16)));
		char flag_side_7[8]  __attribute__ ((aligned(16)));;
		char * side_ptr __attribute__ ((aligned(16))) = flag_side_7;
		char * ban_ptr   __attribute__ ((aligned(16))) = flag_ban;
		//char  chk_sid  [m_ban_elements * 7] __attribute__ ((aligned(16))); 
		//char  chk_ban  [m_ban_elements * 7] __attribute__ ((aligned(16))); 
		//char  chk_xmm1 [m_ban_elements * 7] __attribute__ ((aligned(16))); 
		//char  chk_xmm2 [m_ban_elements * 7] __attribute__ ((aligned(16))); 

		char  chk_sid  [2 * m_ban_elements * 7] __attribute__ ((aligned(16))); 
		char  chk_ban  [2 * m_ban_elements * 7] __attribute__ ((aligned(16))); 
		char  chk_xmm1 [2 * m_ban_elements * 7] __attribute__ ((aligned(16))); 
		char  chk_xmm2 [2 * m_ban_elements * 7] __attribute__ ((aligned(16))); 

		for (int i=0; i < 7; ++i) {
			for (int j=0; j < m_ban_elements; ++j) {
				counter [i*m_ban_elements + j] = j + (i+1)*10;
				chk_sid [i*m_ban_elements + j] = 0;
				chk_ban [i*m_ban_elements + j] = 0;
				chk_xmm1[i*m_ban_elements + j] = 0;
				chk_xmm2[i*m_ban_elements + j] = 0;
			}
			//flag_side_7[i] = 21;
			flag_side_7[i] = 1;
			//flag_side_7[i] = i;
		}
		for (int j=0; j < m_ban_elements; ++j) {
			// if (j%2==0)
			// 	flag_ban[j] = 1;
			// else 
			// 	flag_ban[j] = 0;
			//flag_ban[j] = j*2;
			flag_ban[j] = 1;
			
			//flag_ban[j] = j;
		}
		//flag_side_7[0] = 0;
		//flag_side_7[1] = 0;
		//flag_side_7[2] = 0;
		//flag_side_7[3] = 0;
		//flag_side_7[4] = 0;
		//flag_side_7[5] = 0;
		//flag_side_7[6] = 0;

		print_counter (counter, 7, m_ban_elements);

		tabulate_side_n_ban_m (
				  n_side_elements
				, side_ptr
				, m_ban_elements
				, ban_ptr 
				, counter 
				, chk_sid
				, chk_ban
				, chk_xmm1
				, chk_xmm2
		);

		print_counter (counter, 7, m_ban_elements);
		//for (int i=0; i < 7; ++i)
		for (int i=0; i < 7; ++i) {
			for (int j=0; j < 16; ++j) {
				cout << (int) chk_sid[i * 16 + j] ;
			}
			cout << endl;
			for (int j=0; j < 16; ++j) {
				cout << (int) chk_ban[i * 16 + j] ;
			}
			cout << endl;
			//for (int j=0; j < m_ban_elements; ++j) {
			//	cout << (int) chk_xmm1[i * m_ban_elements + j] ;
			//}
			//cout << endl;
			//for (int j=0; j < m_ban_elements; ++j) {
			//	cout << (int) chk_xmm2[i * m_ban_elements + j] ;
			//}
			cout << " ================== " << endl;
		}
	}

	{
		int n_side_elements = 6;
		char flag_side[7] = { 1, 2, 3, 4, 5, 6, 7} 
			;
		char  chk_sid  [16 * 7] __attribute__ ((aligned(16))); 
		for (int i=0; i < 16*7; ++i) {
			chk_sid[i] = 0;
		}
		test1 (flag_side, chk_sid);
		for (int i=0; i < 7; ++i) {
			for (int j =0 ; j < 16; ++j) {
				cout << " "  << (int) chk_sid[i * 16 +j] ;
			}
			cout << endl;
		}
		cout << endl;
		test1 (flag_side, chk_sid);

	}
	/* 
	{
		int src[16] = { 
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 11, 12,
			13, 14, 15, 16
		};
		int dest[16] = { 
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		};
		cout << "before xfer_data: " << endl;
		for (int i=0; i<16; ++i) {
			cout << " " << dest[i];
		}
		cout << endl;
		xfer_data (src, dest, 16);
		cout << "after xfer_data: " << endl;
		for (int i=0; i<16; ++i) {
			cout << " " << dest[i];
		}
		cout << endl;
	}
	*/

}

