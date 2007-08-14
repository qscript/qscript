#include <cstdio>
#include <iostream>
using namespace std;
#include "global.C"
char c [ 120 ];
int global_val;
int edit_data(char  c[120]);
void func3(float fundc3_a,float func3_b);
int edit_data
(char  c[120]){
int ser_no;
/* DATA CONVERSION */
{int tmp1=0 ;
int tmp2=3 ;
if(tmp2-tmp1==sizeof(int)-1){
	char buff[sizeof(int)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	int *i_ptr = static_cast<int *>(v_ptr);
	 ser_no=*i_ptr;
}else { 
	cerr << "runtime error: line_no : expr out of bounds" << 46;}
}
printf("ser_no:%d\n", ser_no );
char mychar;
mychar =c[4 ];
printf("mychar: %c", mychar );
mychar =c[5 ];
printf("mychar: %c", mychar );
mychar =c[6 ];
printf("mychar: %c", mychar );
mychar =c[7 ];
printf("mychar: %c", mychar );
float myfloat;
/* DATA CONVERSION */
{int tmp1=80 ;
int tmp2=83 ;
if(tmp2-tmp1==sizeof(float)-1){
	char buff[sizeof(float)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	float *f_ptr = static_cast<float *>(v_ptr);
	 myfloat=*f_ptr;
}else { cerr << "runtime error: line_no : expr out of bounds" << 46;}
}
list0 [myfloat]++;
printf(":float: %f", myfloat );
func3(1.100000 , 2 );
int i;
for (i =80 ;i  < 120 ;i =i  + 4 ){
float f;
/* DATA CONVERSION */
{int tmp1=i ;
int tmp2=i  + 3 ;
if(tmp2-tmp1==sizeof(float)-1){
	char buff[sizeof(float)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	float *f_ptr = static_cast<float *>(v_ptr);
	 f=*f_ptr;
}else { cerr << "runtime error: line_no : expr out of bounds" << 46;}
}
printf("f=%f", f );
}
}
void func3
(float fundc3_a,float func3_b){
printf("called: func3\n");
/*Unhandled statement type: Report bug to NxD_in@yahoo.com*/
}
#include "my_axes.C"
void ax_compute(){
	ax_q1.compute();
	ax_q2.compute();
	ax_q3.compute();
}
#include "my_table.C"
void tab_compute(){
	tab_q1_q2.compute();
	tab_q1_q3.compute();
}
