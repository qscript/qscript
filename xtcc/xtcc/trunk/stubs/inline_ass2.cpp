/*
 * =====================================================================================
 *
 *       Filename:  inline_ass2.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Saturday 06 October 2012 12:44:30  IST
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

int main(void)
{
	int x = 10, y;
	
	asm ("movl %1, %%eax;\n"
	     "movl %%eax, %0;\n"
		:"=r"(y)	/* y is output operand */
		:"r"(x)		/* x is input operand */
		:"%eax");	/* %eax is clobbered register */
	cout << y << endl;
}

