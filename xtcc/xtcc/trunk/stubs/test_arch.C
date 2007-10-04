#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <float.h>
using namespace std;

#define XTCC_IEEE_FLT_RADIX                   2
#define XTCC_IEEE_FLT_MANT_DIG               24
#define XTCC_IEEE_FLT_DIG                     6
#define XTCC_IEEE_FLT_MIN_EXP              -125
#define XTCC_IEEE_FLT_MIN_10_EXP            -37
#define XTCC_IEEE_FLT_MAX_EXP               128
#define XTCC_IEEE_FLT_MAX_10_EXP            +38
#define XTCC_IEEE_FLT_MIN                 1.17549435E-38F
#define XTCC_IEEE_FLT_MAX                 3.40282347E+38F
#define XTCC_IEEE_FLT_EPSILON             1.19209290E-07F


int main(){
	char * buff="Test";

	void * v_ptr=buff;
	float *f=static_cast<float*>(v_ptr );
	cout << "Test defaults to: " << *f << endl;
	fstream test_dat("test_header.dat", ios_base::out);
	test_dat << *f;
	char new_buff[sizeof(float)];
	void *nvptr=f;
	char *cptr=static_cast<char*>(nvptr);
	for(int i=0; i<sizeof(float); ++i){
		new_buff[i]=*cptr++;
	}
	test_dat.write(new_buff, sizeof(float));
	cout << FLT_RADIX << endl;
	float zero=0.0;
	float vsmall=0.0000000001;
	cout << "zero: " << zero << endl;
	float test_eps=1.19209290E-8F;
	float new_val=zero+test_eps;
	
	test_dat.close();
}

/* Make a header file with data */
/* DATA FILEFORMAT 
   chars 1 to 14: "XTCC DATA FILE"
   chars 15 to 18: Version number of data file

   twenty blank characters
   SCHAR_MIN - 1 bytes
   SCHAR_MAX - 1 bytes
   SHRT_MIN - 2 bytes
   SHRT_MAX - 2 bytes
   INT_MIN - 4 bytes
   INT_MAX - 4 bytes
   IEEE_FLOAT_MIN  - 4 bytes
   IEEE_FLOAT_MAX  - 4 bytes
   IEEE_FLOAT_EPSILON    - 4 bytes
   IEEE_DOUBLE_MIN - 8 bytes
   IEEE_DOUBLE_MAX - 8 bytes
   IEEE_DOUBLE_EPSILON - 8 bytes

*/

   
   
   
