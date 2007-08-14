#include <iostream>

using namespace std;



int func(unsigned int arr[] );
int func2(unsigned int i );
int main(){
	int a[]={1,2,3,4,5};
	
	//func(a);
	int b=-1;
	func2(b);
}

int func(unsigned int arr[] ){
}

int func2(unsigned int i ){
	cout << "func2: " << i << endl;
	cout << " we should have got a warning. We dont get one - not even with -Wall" << endl;
}
