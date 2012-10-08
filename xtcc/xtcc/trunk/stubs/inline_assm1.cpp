/*
 * =====================================================================================
 *
 *       Filename:  inline_assm1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Saturday 06 October 2012 12:24:35  IST
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
	int dest[70000];
	char fill_value=12;
	int count = 70000;
	cout << "reached here\n";
	//asm ( 		"cld\n\t"
	//		"rep\n\t"
	//		"stosl\n\t"
	//		: /*  no output regs */
	//		: "c" (count), "a" (fill_value), "D" (dest)
	//		: "%ecx", "%edi");

	// gcc format for inline assembly changed a bit since brennan's guide
//asm ("cld\n\t"
//     "rep\n\t"
//     "stosl\n"
//     : /* no output registers */
//     : "c" (count), "a" (fill_value), "D" (dest)
//     : "%ecx", "%edi" );

asm ("cld\n\t"
     "rep\n\t"
     "stosl\n"
     : "=c"(count)
     : "0"(count), "a"(fill_value), "D"(dest)
     : "memory", "cc" );
	cout << "reached here\n";

	for (int i=0; i<70000; ++i) {
		cout << dest[i] << " ";
		if ( (i+1)%13==0) {
			cout << endl;
		}
	}
	cout << endl;
	 

}


extern inline void * memcpy(void * dest,const void * src, int n)
{
    __asm__ volatile("cld\n\t"
        "rep\n\tmovsb\n\t"
        : "=c" (n), "=S" (src), "=D" (dest)
        : "0" (n), "1" (src), "2" (dest)
        : "memory", "cc");
    return dest;
}
