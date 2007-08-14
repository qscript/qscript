#include <iostream>

using namespace std;

void func(int i1, int i2);

int main(){
	// no warning: func(1, static_cast<int>(2.1212));
	func(1, 2.1212);
	return 0;
}

void func(int i1, int i2){
	cout << "i2:" << i2 << endl;	
}
