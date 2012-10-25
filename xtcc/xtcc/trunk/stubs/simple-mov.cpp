/*
 * =====================================================================================
 *
 *       Filename:  simple-mov.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 11 October 2012 01:14:01  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         URL:  http://www.ibm.com/developerworks/linux/library/l-ia/index.html
 *        Company:  
 *
 * =====================================================================================
 */
int main(void)
{
	int x = 10, y;
	
	asm ("movl %1, %%eax\n\t"
	     "movl %%eax, %0"
		:"=r"(y)	/* y is output operand */
		:"r"(x)		/* x is input operand */
		:"%eax");	/* %eax is clobbered register */
}
