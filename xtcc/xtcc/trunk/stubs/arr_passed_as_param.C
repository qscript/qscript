
#include <iostream>
using namespace std;

int arr_param_func(int arr[]);
int main(){
	int a[20];
	arr_param_func(a);
}

int arr_param_func(int arr[]){
	cout << sizeof(arr) << endl;
}
