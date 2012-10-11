/*
 * =====================================================================================
 *
 *       Filename:  shufb.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 11 October 2012 02:39:59  IST
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

int main()
{

	char values[] __attribute__ ((aligned(16))) = { 10, 20, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	char shuffle_mask[] __attribute__ ((aligned(16))) = { 0, 1, 0, 2, 0, 3, 0, 4, 1, 1, 1, 2, 1, 3, 1, 4 };
	char output[] __attribute__ ((aligned(16))) = 
		{ 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63 };
	asm (
			"movdqa (%1), %%xmm2\n\t"
			"movdqa (%2), %%xmm1\n\t"
			"pshufb %%xmm1, %%xmm2\n\t"
			"movdqa %%xmm2, %0\n\t"
			: /*  outputs */ "=m" (output)
			: /*  inputs */ "r" (values), "r" (shuffle_mask)
			: /*  clobbered */ "xmm1", "xmm2");

	for (int i=0; i<16; ++i) {
		cout << " " << (int) output[i];
	}
	cout << endl;

	//asm (
	//		"movl (%0), %%mm1\n\t"
	//		"movl (%1), %%mm2\n\t"
	//		"pshufb %%mm2, %%mm1\n\t"
	//		: /*  outputs */
	//		: /*  inputs */ "r" (values), "r" (shuffle_mask)
	//		: /*  clobbered */ "mm1", "mm2");

}
