/*
 * =====================================================================================
 *
 *       Filename:  simd.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Monday 08 October 2012 06:10:41  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 This is a discussion on GCC and SSE multplication within the C Programming forums, part of the General Programming Boards category; 
 I'm trying to get the hand of using SSE instructions through gcc, and I can't get multiplication to work. Here ...*        Company:  
http://cboard.cprogramming.com/c-programming/107195-gcc-sse-multplication.html
Kernel Sanders
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
 
typedef int v4si __attribute__ ((vector_size (16)));
typedef union { int s[4]; v4si v; } v4si_u;
 
 
void usage(char **argv){
  printf("Usage: &#37;s [1|2]\n1: SIMD mode\n2: SISD mode\n", argv[0]);
  exit(1);
}
 
int main(int argc, char **argv){
 
  int aa[4] = { 1, 2, 3, 4 }, 
    bb[4] = { 4, 3, 2, 1 };
  v4si_u a, b;
  int i, j;
 
  if(argc < 2)
    usage(argv);
 
  for(i = 0; i < 4; ++i){
    a.s[i] = aa[i];
    b.s[i] = bb[i];
  }
 
  if(argv[1][0] == '1')
    for(i = 0; i < 0xFFFFFF; ++i)
      a.v = a.v + b.v;
  else if(argv[1][0] == '2')
    for(i = 0; i < 0xFFFFFF; ++i)
      for(j = 0; j < 4; ++j)
    aa[j] = aa[j] + bb[j];
  else
    usage(argv);
 
  return 0;
}
