/*
 * =====================================================================================
 *
 *       Filename:  paddd.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 12 October 2012 02:32:00  IST
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

	int counter1[] __attribute__ ((aligned(16))) = { 1, 2, 3, 4};
	int counter2[] __attribute__ ((aligned(16))) = { 11, 12, 13, 14};
	int result[] __attribute__ ((aligned(16))) = { 110, 120, 130, 140};

int main()
{
	asm (
		"movdqa (%0), %%xmm1\n\t"
		"movdqa (%1), %%xmm2\n\t"
		: /*  outputs */
		: /*  inputs */ "r" (counter1), "r"(counter2)
		: /*  clobbered */
	);
	asm (
		"paddd  %%xmm1, %%xmm2\n\t"
		"movdqa %%xmm2, %0\n\t"
		: /*  outputs */ "=m" (result)
		: /*  inputs */ 
		: /*  clobbered */
	);

	for (int i=0; i< 4; ++i) {
		cout << " " << result[i];
	}
	cout << endl;

}
