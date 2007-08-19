#include <iostream>
#include <fstream>
using namespace std;

int main(){
	float f1=2.5;
	ofstream float_file("floatest.dat", ios_base::trunc);

	float_file.write(f1, sizeof(f1));
}
