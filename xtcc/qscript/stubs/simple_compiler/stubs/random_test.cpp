/*
 * =====================================================================================
 *
 *       Filename:  random_test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Wednesday 22 February 2012 10:36:48  GMT
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
using namespace std;
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <time.h>

int main()
{
	srand(time(0));

	printf("%010ld\n", random());
}
