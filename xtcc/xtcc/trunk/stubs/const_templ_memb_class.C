
#include <iostream>

using namespace std;
template <int bound> 
class tobj{
	const int sz;
	int arr[bound];
	public:
	tobj():sz(bound){
	}
	void mysize(){
		cout << "size: " << sz << endl;
	}
};

int main(){
	tobj <5> t1;
	tobj <5> t2;
	t1.mysize();
	t2.mysize();
}
