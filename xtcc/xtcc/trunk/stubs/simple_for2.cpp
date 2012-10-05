/*
 * =====================================================================================
 *
 *       Filename:  simple_for2.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 05 October 2012 04:59:18  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Neil Xavier D'Souza
 *        Company:  
 *
 * =====================================================================================
 */


// compile with: g++ -fpermissive -O2 -ftree-vectorize -msse2 -msse4.2 -ftree-vectorizer-verbose=5 simple_for2.cpp 2> vectorized.txt
// to check vectorization
//
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <sys/types.h>

using namespace std;

int qh1a_arr[4157]  __attribute__ ((aligned(16)))  ;
//          int x __attribute__ ((aligned (16))) = 0;
int8_t c[4157] __attribute__ ((aligned(16))) ;
//extern FILE * runtime_errors ;
int ser_no;


int main ()
{
	for (int i=0; i<4157; ++i) {
		qh1a_arr[i]=0;
	}

	for (int i=0; i<4157; ++i) {
		int a = i;
		a = a%4;
		if (i>=3924 && i < 3984) {
			if (i==3924) {
				c[i] = 2;
			} else if (i==3925) {
				c[i] = 0;
			} else if (i==3926) {
				c[i] = 0;
			} else if (i==3927) {
				c[i] = 0;
			} else {
				if (i%4==0)
					c[i] = i%256;
				else 
					c[i] = 0;
			}
		} else {
			c[i] = 0;
		}
	}
	const int start_col=3924,end_col=3983,width=4;
	if( start_col > end_col) {
		printf("start_col evaluated > end_col -> runtime error");
	}
	if( (end_col-start_col +1) % width!=0 ) {
		printf("expr value:%d", end_col-start_col +1 % width );	
		printf("please check your start_col=%d ,  end_col=%d, width=%d for fld statement-> runtime error\n", start_col, end_col, width);
	}
	for (int i=start_col; i<= end_col+1-width; i+=width) {
		char buff[4];
		for (int s=i,j=0;s<i+width;++s,++j) {
			buff[j]=c[s];
		}
		void * v_ptr = buff;
		int  *i_ptr = static_cast<int *>(v_ptr);
		int tmp=*i_ptr;
		if (tmp>=1 && tmp <=100) {
			++qh1a_arr[tmp];
			++qh1a_arr[0];
		} else if (tmp == 0) {
		} else {
			//fprintf(runtime_errors, " runtime warning: code: %d at variable: qh1a_arr too big to fit in array. ser_no: %d \n", tmp, ser_no);
		}
		printf("tmp: %d\n", tmp);
	}
	const int delta = (end_col + 1 - start_col - width)/width;
	printf("delta = %d\n", delta);

	//for (int i = 0; i<= delta; ++i ) 
	for (int i = 0; i<= 14; ++i ) {
		char buff[4];
		//for (int s=i,j=0;s<i+width;++s,++j) {
		//	cout << "[start_col  + i * width + j]: " << start_col  + i * width + j << endl;
		//	buff[j]=c[start_col  + i * width + j];
		//}
		buff[0]=c[start_col  + i * width + 0];
		buff[1]=c[start_col  + i * width + 1];
		buff[2]=c[start_col  + i * width + 2];
		buff[3]=c[start_col  + i * width + 3];
		//void * v_ptr = buff;
		//int  *i_ptr = static_cast<int *>(v_ptr);
		//int  *i_ptr = reinterpret_cast<int *>(buff);
		int   an_int = * reinterpret_cast<int *>(&buff[0]);

		//int tmp=*i_ptr;
		//if (tmp>=1 && tmp <=100) {
		//	++qh1a_arr[tmp];
		//	++qh1a_arr[0];
		//} else if (tmp == 0) {
		//} else {
		//	//fprintf(runtime_errors, " runtime warning: code: %d at variable: qh1a_arr too big to fit in array. ser_no: %d \n", tmp, ser_no);
		//}
		//printf("2 tmp: %d, an_int: %d\n", /*  tmp, */ an_int);
		//printf(" an_int: %d\n", /*  tmp, */ an_int);
		//(tmp>=1 && tmp <=100) ? ++qh1a_arr[tmp]   : ++qh1a_arr[0];
		(an_int>=1 && an_int <=100) ? ++qh1a_arr[an_int]   : ++qh1a_arr[0];
	}
}
