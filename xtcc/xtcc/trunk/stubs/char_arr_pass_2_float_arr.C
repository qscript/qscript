#include <iostream>

using namespace std;
void func(float arr[]);
void func2(float f);
int main(){
	char p[]="This is a test";
	char c=100;

	func(p);	
	func2(c);	
	
}

void func(float arr[]){
	cout << "sizeof(arr): " << sizeof(arr) << endl;
}

void func2(float f){
}
