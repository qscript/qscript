/*
 * =====================================================================================
 *
 *       Filename:  fast-loop.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Wednesday 10 October 2012 11:53:34  IST
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

void print(int arr[] , int n) 
{
	for (int i=0; i< n ; ++i) {
		cout << " " << arr[i] ;
		if ( (i+1)% 19==0) {
			cout << endl;
		}
	}
	cout << endl;
}

void do_fast_double_loop(int m, int n, int counter2[]
		, char flag1[], char flag2[]
		)
{
	int i = 0, j=0;
	for (i = 0, j=0; j < (n >> 4); i += (1 << 4), ++j ) {
		if (flag1[i]) {
			counter2[i*9+0] += flag2[0];
			counter2[i*9+1] += flag2[1];
			counter2[i*9+2] += flag2[2];
			counter2[i*9+3] += flag2[3];
			counter2[i*9+4] += flag2[4];
			counter2[i*9+5] += flag2[5];
			counter2[i*9+6] += flag2[6];
			counter2[i*9+7] += flag2[7];
			counter2[i*9+8] += flag2[8];
		}
		if (flag1[i + 1]) {
			counter2[(i+1)*9+0] += flag2[0];
			counter2[(i+1)*9+1] += flag2[1];
			counter2[(i+1)*9+2] += flag2[2];
			counter2[(i+1)*9+3] += flag2[3];
			counter2[(i+1)*9+4] += flag2[4];
			counter2[(i+1)*9+5] += flag2[5];
			counter2[(i+1)*9+6] += flag2[6];
			counter2[(i+1)*9+7] += flag2[7];
			counter2[(i+1)*9+8] += flag2[8];
		}
		if (flag1[i + 2]) {
			counter2[(i+2)*9+0] += flag2[0];
			counter2[(i+2)*9+1] += flag2[1];
			counter2[(i+2)*9+2] += flag2[2];
			counter2[(i+2)*9+3] += flag2[3];
			counter2[(i+2)*9+4] += flag2[4];
			counter2[(i+2)*9+5] += flag2[5];
			counter2[(i+2)*9+6] += flag2[6];
			counter2[(i+2)*9+7] += flag2[7];
			counter2[(i+2)*9+8] += flag2[8];
		}
		if (flag1[i + 3]) {
			counter2[(i+3)*9+0] += flag2[0];
			counter2[(i+3)*9+1] += flag2[1];
			counter2[(i+3)*9+2] += flag2[2];
			counter2[(i+3)*9+3] += flag2[3];
			counter2[(i+3)*9+4] += flag2[4];
			counter2[(i+3)*9+5] += flag2[5];
			counter2[(i+3)*9+6] += flag2[6];
			counter2[(i+3)*9+7] += flag2[7];
			counter2[(i+3)*9+8] += flag2[8];

		}
		
		if (flag1[i + 4]) {
			counter2[(i+4)*9+0] += flag2[0];
			counter2[(i+4)*9+1] += flag2[1];
			counter2[(i+4)*9+2] += flag2[2];
			counter2[(i+4)*9+3] += flag2[3];
			counter2[(i+4)*9+4] += flag2[4];
			counter2[(i+4)*9+5] += flag2[5];
			counter2[(i+4)*9+6] += flag2[6];
			counter2[(i+4)*9+7] += flag2[7];
			counter2[(i+4)*9+8] += flag2[8];

		}
		if (flag1[i + 5]) {
			counter2[(i+5)*9+0] += flag2[0];
			counter2[(i+5)*9+1] += flag2[1];
			counter2[(i+5)*9+2] += flag2[2];
			counter2[(i+5)*9+3] += flag2[3];
			counter2[(i+5)*9+4] += flag2[4];
			counter2[(i+5)*9+5] += flag2[5];
			counter2[(i+5)*9+6] += flag2[6];
			counter2[(i+5)*9+7] += flag2[7];
			counter2[(i+5)*9+8] += flag2[8];

		}
		if (flag1[i + 6]) {
			counter2[(i+6)*9+0] += flag2[0];
			counter2[(i+6)*9+1] += flag2[1];
			counter2[(i+6)*9+2] += flag2[2];
			counter2[(i+6)*9+3] += flag2[3];
			counter2[(i+6)*9+4] += flag2[4];
			counter2[(i+6)*9+5] += flag2[5];
			counter2[(i+6)*9+6] += flag2[6];
			counter2[(i+6)*9+7] += flag2[7];
			counter2[(i+6)*9+8] += flag2[8];

		}
		if (flag1[i + 7]) {

		}
		if (flag1[i+8]) {

		}
		if (flag1[i + 9]) {

		}
		if (flag1[i + 10]) {

		}
		if (flag1[i + 11]) {

		}
		if (flag1[i + 12]) {

		}
		if (flag1[i + 13]) {

		}
		if (flag1[i + 14]) {

		}
		if (flag1[i + 15]) {

		}
	}
}

int main()
{
	int n = 254;
	int i = 0;
	char flag1[107] __attribute__ ((aligned(16))) = 
		{
			1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
			1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
			1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
			1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
			1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
			1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
			1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1
		};
	char flag2[18] __attribute__ ((aligned(16))) = 
		{
			1, 0, 1, 0, 1, 0, 1, 0, 1,
			1, 0, 1, 0, 1, 0, 1, 0, 1

		};
	int counter [9 * 107]__attribute__ ((aligned(16))) ;
	int counter2 [9 * 107]__attribute__ ((aligned(16))) ;
	for (int i=0; i<107; ++i) {
		for (int j=0; j<9; ++j) {
			counter[i*9+j] = 0;
		}
	}
	for (int i=0; i<107; ++i) {
		for (int j=0; j<9; ++j) {
			counter2[i*9+j] = 0;
		}
	}
	print (counter, 107*9);

	// =============== simple case ================
	for (int i=0; i<107; ++i) {
		if (flag1[i]) {
			for (int j=0; j<9; ++j) {
				if (flag2[j]) {
					++counter[i*9+j];
				}
			}
		}
	}

	print (counter, 107*9);

	cout << "n >> 3: " << (n >> 3)
		<< ", 1 << 3:" << (1 << 3)
		<< endl;
	int j = 0;
	//for (j = 0; j < (n >> 4); ++j, i += (1 << 4) ) 
	for (i = 0, j=0; j < (n >> 4); i += (1 << 4), ++j ) {
		cout 
			<< i       << " " << i + 1 << " " << i + 2 << " " << i + 3 << " "
			<< i + 4 << " " << i + 5 << " " << i + 6 << " " << i + 7 << " "
			<< i + 8 << " " << i + 9 << " " << i + 10 << " " << i + 11 << " "
			<< i + 12 << " " << i + 13 << " " << i + 14 << " " << i + 15 << " "
			<< endl;
	}
	cout << " === 16 === : i = " << i << ", j = " << j<< endl;

	// for (; j < (n >> 3); ++j, i += (1 << 3) ) 
	cout << "(A = n >> 3: " << (n >> 3) << ") - (B = (n >> 4): " << (n >> 4)
		<< ") == " << ((n>>3) - (n >> 4))
		<< endl;
	for (j = n>>4; j < ((n >> 3) - (n>>4));  i += (1 << 3), ++j ) {
		cout 
			<< i       << " " << i + 1 << " " << i + 2 << " " << i + 3 << " "
			<< i + 4 << " " << i + 5 << " " << i + 6 << " " << i + 7
			<< endl;
		//cout << " === 8 === : i = " << i << ", j = " << j<< endl;
	}
	cout << "(A = n >> 2: " << (n >> 2) << ") - (B = (n >> 3): " << (n >> 3)
		<< ") == " << ((n>>2) - (n >> 3))
		<< endl;
	cout << " === 8 === : i = " << i << ", j = " << j<< endl;

	// for (; j < (n >> 3); ++j, i += (1 << 3) ) 
	for (j = n>>3; j < ((n >> 2) - (n>>3));  i += (1 << 2), ++j ) {
		cout 
			<< i       << " " << i + 1 << " " << i + 2 << " " << i + 3 << " "
			<< endl;
		//cout << " === 8 === : i = " << i << ", j = " << j<< endl;
	}
	cout << " === 8 === : i = " << i << ", j = " << j<< endl;

	cout << "n: " << n << endl;
	//n -= i ;
	for (; i < n; ++i) {
		cout << " " << i;
	}
	cout << endl;
	// =============== simple case ================
	for (int i=0; i<107; ++i) {
		if (flag1[i]) {
			for (int j=0; j<9; ++j) {
				if (flag2[j]) {
					++counter[i*9+j];
				}
			}
		}
	}
}

void simple_parallel(int m, int n, int counter2[]
		, char flag1[], char flag2[]
		)
{
	char * flags1 __attribute__ ((aligned(16))) = flag1;
	char * flags2 __attribute__ ((aligned(16))) = flag2;

	asm ("movdqa (%0), %%xmm0\n\t"
		: /*  outputs */
		: /*  inputs */ "r" (flags2)
		: /*  clobbered */ "xmm0"
	    );

	asm ("movdqa (%0), %%xmm1\n\t"
		: /*  outputs */
		: /*  inputs */ "r" (flags1)
		: /*  clobbered */ "xmm1"
	    );

	asm ("movdqa (%0), %%xmm2\n\t"
		: /*  outputs */
		: /*  inputs */ "r" (counter2)
		: /*  clobbered */ "xmm2"
	    );


	//if (flag1[0] && flag2[0]) ++counter2[0*18 + 0];
	//if (flag1[0] && flag2[1]) ++counter2[0*18 + 1];
	//if (flag1[0] && flag2[2]) ++counter2[0*18 + 2];
	//if (flag1[0] && flag2[3]) ++counter2[0*18 + 3];
	//asm ("pand xmm0, xmm1" 


	if (flag1[0] && flag2[4]) ++counter2[0*18 + 4];
	if (flag1[0] && flag2[5]) ++counter2[0*18 + 5];
	if (flag1[0] && flag2[6]) ++counter2[0*18 + 6];
	if (flag1[0] && flag2[7]) ++counter2[0*18 + 7];
	if (flag1[0] && flag2[8]) ++counter2[0*18 + 8];
	if (flag1[0] && flag2[9]) ++counter2[0*18 + 9];

	if (flag1[1] && flag2[0]) ++counter2[1*18 + 0];
	if (flag1[1] && flag2[1]) ++counter2[1*18 + 1];
	if (flag1[1] && flag2[2]) ++counter2[1*18 + 2];
	if (flag1[1] && flag2[3]) ++counter2[1*18 + 3];
	if (flag1[1] && flag2[4]) ++counter2[1*18 + 4];
	if (flag1[1] && flag2[5]) ++counter2[1*18 + 5];
	if (flag1[1] && flag2[6]) ++counter2[1*18 + 6];
	if (flag1[1] && flag2[7]) ++counter2[1*18 + 7];
	if (flag1[1] && flag2[8]) ++counter2[1*18 + 8];
	if (flag1[1] && flag2[9]) ++counter2[1*18 + 9];

}
