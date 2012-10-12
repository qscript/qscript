/*
 * =====================================================================================
 *
 *       Filename:  pinsrb.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 12 October 2012 10:18:11  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

	char first_bool_condns[] __attribute__ ((aligned(16))) = 
		//{ 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1};
		{ 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 } ;
	char second_bool_condns[] __attribute__ ((aligned(16))) = 
		//{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
		{ 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 } ;
	char result_bool_condns[] __attribute__ ((aligned(16))) =
		{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	char first_mask []  __attribute__ ((aligned(16))) = { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};
	char second_mask [] __attribute__ ((aligned(16))) = { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};
	char first_bool_condns_stage1[] __attribute__ ((aligned(16))) = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 } ;
	char first_bool_condns_stage2[] __attribute__ ((aligned(16))) = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 } ;
	char first_bool_condns_stage2_again[] __attribute__ ((aligned(16))) = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 } ;


int main(void)
{

	// xmm4 <- first_mask
	// xmm5 <- second_mask
	// xmm1 <- first 16 bool conditions 
	// xmm2 <- second 16 bool conditions 

	asm (
		"movdqa (%0), %%xmm4\n\t"
		"movdqa (%1), %%xmm5\n\t"
		"movdqa (%2), %%xmm1\n\t"
		"movdqa (%3), %%xmm2\n\t"
		: /*  outputs */ 
		: /*  inputs */ "r" (first_mask),
				"r" (second_mask),
				"r" (first_bool_condns),
				"r" (second_bool_condns)
		: /*  clobbered */
			"xmm4", "xmm5",
			"xmm1", "xmm2"
	    );

	char double_word[4]  = { 100, 100, 100, 100 };
	asm (
		"movdqa %%xmm1, %%xmm6\n\t"
		"pshufb %%xmm4, %%xmm6\n\t"
		"movdqa %%xmm6, %0\n\t"
		"movdqa %%xmm2, %%xmm7\n\t"
		"pshufb %%xmm5, %%xmm7\n\t"
		"movdqa %%xmm7, %1\n\t"
		"movdqa %%xmm7, %2\n\t"
		"pextrb $0, %%xmm7, %3\n\t"
		"pextrb $1, %%xmm7, %4\n\t"
		: /*  outputs */ "=m" (first_bool_condns_stage1), "=m" (first_bool_condns_stage2)
				, "=m" (first_bool_condns_stage2_again)
				, "=m" (double_word)
				, "=m" (*(double_word+1))
		: /*  inputs */
		: /*  clobbered */
			"xmm6", "xmm7"
	    );

	//cout << "double_word: " ;
	//for (int i=0; i< 4; ++i) {
	//	cout << " " << (int) double_word[i];
	//}
	//cout << endl;

	//cout << "first_bool_condns_stage1: " ;
	//for (int i=0; i< 16; ++i) {
	//	cout << " " << (int) first_bool_condns_stage1[i];
	//}
	//cout << endl;

	//cout << "first_bool_condns_stage2: " ;
	//for (int i=0; i< 16; ++i) {
	//	cout << " " << (int) first_bool_condns_stage2[i];
	//}
	//cout << endl;

	//cout << "first_bool_condns_stage2_again: " ;
	//for (int i=0; i< 16; ++i) {
	//	cout << " " << (int) first_bool_condns_stage2_again[i];
	//}
	//cout << endl;

	// Note: if you interleave with cout statements like above
	// then xmm7 gets clobbered. I can only guess that cout
	// does use the xmm7 register

	// This was put here to check clobbering
	//asm (
	//	"movdqa %%xmm7, %0\n\t"
	//	: /* outputs */  "=m" (first_bool_condns_stage2_again)
	//	: /* inputs */ 
	//	: /* clobbered */ 
	//    );

	//cout << "first_bool_condns_stage2_again: " ;
	//for (int i=0; i< 16; ++i) {
	//	cout << " " << (int) first_bool_condns_stage2_again[i];
	//}
	//cout << endl;

	//// works fine
	//asm (
	//	"pextrb $0, %%xmm7, %0\n\t"
	//	"pextrb $1, %%xmm7, %1\n\t"
	//	: /* outputs */ "=m" (double_word), "=m" (*(double_word+1))
	//	: /* inputs */ 
	//	: /* clobbered */ 
	//    );

	//// works fine
	//asm (
	//	"pextrd $0, %%xmm7, %0\n\t"
	//	: /* outputs */ "=m" (double_word)
	//	: /* inputs */ 
	//	: /* clobbered */ 
	//    );
	int first_bool_condns_stage3[] __attribute__ ((aligned(16))) = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 } ;
	int second_bool_condns_stage3[] __attribute__ ((aligned(16))) = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 } ;
	int counter [] __attribute__ ((aligned(16))) = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 } ;
	//int *p_counter __attribute__ ((aligned(16))) = counter;
	asm (
		"pextrd $0, %%xmm6, %%eax\n\t"
		"movq %%rax, %%xmm8\n\t"
		"pmovsxbd %%xmm8, %%xmm10\n\t"
		"movdqa %%xmm10, %0\n\t"
		"pextrd $0, %%xmm7, %%eax\n\t"
		"movq %%rax, %%xmm9\n\t"
		"pmovsxbd %%xmm9, %%xmm11\n\t"
		"movdqa %%xmm11, %1\n\t"

		: /* outputs */   "=m" (first_bool_condns_stage3)
				, "=m" (second_bool_condns_stage3)
		: /* inputs */ 		
				 	
		: /* clobbered */ "eax"
	    );

	int and_result [] __attribute__ ((aligned(16))) = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 } ;
	asm (
		"pand %%xmm9, %%xmm11\n\t"
		"movdqa %%xmm11, %0\n\t"
		"movdqa (%1), %%xmm12\n\t"
		: /*  outputs */ "=m" (and_result) 
		: /*  inputs */ "r" (counter)
		: /*  clobbered */
	    );
	asm (
		"paddd %%xmm11, %%xmm12\n\t"
		"movdqa %%xmm12, %0\n\t"
		: /*  outputs */  "=m" (counter)
		: /*  inputs */
		: /*  clobbered */
	    );

	cout << "double_word: " ;
	for (int i=0; i< 4; ++i) {
		cout << " " << (int) double_word[i];
	}
	cout << endl;

	cout << "first_bool_condns_stage3: " ;
	for (int i=0; i< 4; ++i) {
		cout << " " << (int) first_bool_condns_stage3[i];
	}
	cout << endl;

	cout << "second_bool_condns_stage3: " ;
	for (int i=0; i< 4; ++i) {
		cout << " " << (int) second_bool_condns_stage3[i];
	}
	cout << endl;

	cout << "and_result: " ;
	for (int i=0; i< 4; ++i) {
		cout << " " << (int) and_result[i];
	}
	cout << endl;

	cout << "counter: " ;
	for (int i=0; i< 4; ++i) {
		cout << " " << (int) counter[i];
	}
	cout << endl;

}
