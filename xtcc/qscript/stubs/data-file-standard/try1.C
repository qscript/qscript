#include <iostream>
using namespace std;

int main(){
	float  f1=2.384185791015625e-7;
	double d1=2.384185791015625e-7;
	cout.precision(18);
	cout << "f1: " << f1 << endl;
	cout.precision(18);
	cout << "d1: " << d1 << endl;

	//float  f2=1234567.891011121314;
	//double d2=1234567.891011121314;
	float  f2=2.384185791015625E36;
	double d2=2.384185791015625E306;
	cout.precision(18);
	cout << f2 << endl;
	cout.precision(18);
	cout << d2 << endl;

	float  f3=1.2345678910E36;
	double d3=1.2345678910E306;
	double z3=1.0E-305;
	cout.precision(18);
	cout << "f3:" << f3 << endl;
	cout.precision(18);
	cout << "d3:" << d3 << endl;
	cout.precision(18);
	cout << "z3: " << z3 << endl;

	float f4=1.0;
	float d4=1.0;
	cout << "-------------f4-------------:" << f4 << endl;
	float fsum=0.0;
	float dsum=0.0;
	for(int i=0; i<22; ++i){
		f4=f4/2.0;
		d4=d4/2.0;
		
		fsum+=f4;
		dsum+=d4;
		cout.precision(18);
		//cout << "f4:" << f4 << endl;
		//cout << "d4:" << d4 << endl;
	}
	cout.precision(18);
	cout << "fsum: " << fsum << endl;
	cout << "dsum: " << dsum << endl;
}

