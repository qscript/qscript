/*
 * =====================================================================================
 *
 *       Filename:  pmovsxbw.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Tuesday 09 October 2012 11:46:52  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
/* I am planning to use the intel sse instructions in a code generation 
 * feature I have planned. One of the instructions I need to use is "pmovsxbd" in the sse4.1
 * instruction set.
 *
 * I also tested the pmovsxbw instruction and the behaviour is as I expected.
 *
 *
 *
 * PMOVSXBD xmm1, xmm2/m32 :
 * Sign extend 4 packed signed 8-bit integers in
 * the low 4 bytes of xmm2/m32 to 4 packed
 * signed 32-bit integers in xmm1.
 *
 *
 * 
 */
    
    #include <sys/types.h>
    #include <iostream>
    using namespace std;
    	int8_t arr8_t[] __attribute__ ((aligned(16))) = { 	1, 12, 3, 14, 
    								5, 6, 7, 8,  
    								1, 0, 1, 0,
    								1, 0, 1, 0,  
    							};
    	int16_t arr16_t[] __attribute__ ((aligned(16))) = { 100, 100, 100, 100, 100, 100, 100, 100 };
    	int32_t arr32_t[] __attribute__ ((aligned(16))) = { 200, 200, 200, 200, 200, 200, 200, 200 };
    
    
    int main()
    {
    
    	cout << "arr8_t: ";
    	for (int i=0; i<16; ++i) {
    		cout << " " << (int)arr8_t[i] ;
    	}
    	cout << endl;
    
    	cout << "arr16_t: ";
    	for (int i=0; i<8; ++i) {
    		cout << " " << arr16_t[i] ;
    	}
    	cout << endl;
    
    	cout << "arr32_t: ";
    	for (int i=0; i<8; ++i) {
    		cout << " " << arr32_t[i] ;
    	}
    	cout << endl;
    
    	asm ( 	"movdqa (%0), %%xmm2\n\t"
    		: /*  outputs */
    		: /*  inputs */ "r" (arr8_t)
    		: /*  clobbered */ "xmm2"
    	    );
    	asm ( 	"movdqa (%0), %%xmm3\n\t"
    		: /*  outputs */
    		: /*  inputs */ "r" (arr8_t)
    		: /*  clobbered */ "xmm3"
    	    );
    
    	asm ( 	"paddd      %%xmm2, %%xmm3\n\t"
    		: /*  outputs */
    		: /*  inputs */ 
    		: /*  clobbered */ "xmm3"
    	    );
    	
    
    	asm ( 	"movdqa %%xmm3, %0\n\t"
    		: /*  outputs */ "=m" (arr8_t)
    		: /*  inputs */ 
    		: /*  clobbered */ 
    	    );
    
    	cout << "arr8_t: ";
    	for (int i=0; i<16; ++i) {
    		cout << " " << (int)arr8_t[i] ;
    	}
    	cout << endl;
    
    	asm ( 	"movdqa (%1), %%xmm2\n\t"
    		"pmovsxbw %%xmm2, %%xmm1\n\t"
    		"movdqa %%xmm1, %0\n\t"
    		: /*  outputs */ "=m" (arr16_t)
    		: /*  inputs */ "r" (arr8_t)
    		: /*  clobbered */ "xmm1", "xmm2"
    	    );
    
    	cout << "arr16_t: ";
    	for (int i=0; i<8; ++i) {
    		cout << " " << arr16_t[i] ;
    	}
    	cout << endl;
    
    	asm ( 	
    		//"movdqa (%1), %%xmm2\n\t"
    		//"pxor %%xmm1, %%xmm1\n\t"
    		//"punpcklbw %%xmm1, %%xmm2\n\t"
    		"pmovsxbd %%xmm2, %%xmm1\n\t"
    		"movdqa %%xmm1, %0\n\t"
    		: /*  outputs */ "=m" (arr32_t)
    		: /*  inputs */ "r" (arr8_t)
    		: /*  clobbered */ "xmm1", "xmm2"
    	    );
    
    	cout << "arr32_t: ";
    	for (int i=0; i<8; ++i) {
    		cout << " " << arr32_t[i] ;
    	}
    	
    	//my_base_ptr v4si_dummy.my_v4si = __builtin_ia32_pmovsxbd128(
    	cout << endl;
    
    }
