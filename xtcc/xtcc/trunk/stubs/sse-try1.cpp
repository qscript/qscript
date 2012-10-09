/*
 * =====================================================================================
 *
 *       Filename:  sse-try1.cpp
 *
 *    Description:  SSE Instructions using movdqa and paddd and transfer back to memory
 *
 *        Created:  Monday 08 October 2012 02:15:26  IST
 *       Compiler:  gcc
 *
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

typedef int v4si __attribute__ ((vector_size (16)));
typedef union { int s[4]; v4si v; } v4si_u;


void print_arr(int arr[], int n)
{
	for (int i=0; i<n; ++i) {
		cout << " " << arr[i];
		if ( (i+1)%19 == 0) {
			cout << endl;
		}
	}
	cout << endl;
}

int main ()
{
	int arr [256] __attribute__ ((aligned(16)));
	int bool_condns[256] __attribute__ ((aligned(16))) = {
		5, 10, 15, 20, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0
	};
	for (int i=0; i<256; ++i) {
		arr[i] = i;
	}

	//for (int i=0; i<256; ++i) {
	//	cout << arr[i] << endl;
	//}
	print_arr (arr, 256);
	
	int n = 256;

#if 0
	{
		int * a1 __attribute__ ((aligned(16))) = arr;
		int * b1 __attribute__ ((aligned(16))) = bool_condns;
		for (int i=0; i < 256; i+=4) {
			asm (
				"movdqa     (%0), %%xmm0\n\t"
				"movdqa     (%1), %%xmm1\n\t"
				"paddd      %%xmm0, %%xmm1\n\t"
					: /* outputs */ 
					: /* inputs */ "r" (a1) , "r"(b1)
					: /* clobbered */ "xmm0", "xmm1"
					);
			asm (
				"movdqa     %%xmm0, %0\n\t"
					: /* outputs */ "=m" (a1)
					: /* inputs */ 
					: /* clobbered */  "memory" 
			    );

			a1 += 4; b1+=4;
			cerr << "." ;
		}
		cout << endl;
	}
#endif /*  0 */
#if 1
	{
		int * a1 __attribute__ ((aligned(16))) = arr;
		int * b1 __attribute__ ((aligned(16))) = bool_condns;
		//for (int i=0; i < 256; i+=4) {
			asm volatile ("pxor %xmm0, %xmm0");

			//asm volatile ("movdqa %%xmm0, %0" 
			//	: /*  outputs */ "=m" (*a1) 
			//	: /*  inputs */ 
			//	: /*  clobbered */ "xmm0"
			//	);

#if 1
			asm (
				"movdqa     (%1), %%xmm0\n\t"
				"movdqa     (%2), %%xmm1\n\t"
				"paddd      %%xmm0, %%xmm1\n\t"
				"movdqa     %%xmm1, %0\n\t"
					: /* outputs */ "=m" (*a1)
					: /* inputs */ "r" (a1) , "r"(b1)
					: /* clobbered */ "xmm0", "xmm1"
						//, "memory"
					);
#endif /*  0  */

			//a1 += 4; b1+=4;
			cerr << "." ;
		//}
		cout << endl;
	}
#endif /*  0 */
#if 0
	{
		int * a1 __attribute__ ((aligned(16))) = arr;
		int * b1 __attribute__ ((aligned(16))) = bool_condns;
		for (int i=0; i < 256; i+=4) {
			v4si_u * v1=  static_cast<v4si_u*> (a1);

			//a1 += 4; b1+=4;

			cerr << "." ;
		}
		cout << endl;
	}
#endif /*  0 */

	print_arr (arr, 256);
	//for (int i=0; i<256; ++i) {
	//	cout << arr[i] << endl;
	//}


}
