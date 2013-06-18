#include <iostream>

using namespace std;

struct link 
{
	struct link *next;
	link(): next(0)
	{ }
};

int main()
{
	struct link * alink=0;
	struct link * link_ptr=alink;
	cout << alink << ", " << link_ptr << endl;

	link_ptr = new struct link();


	cout << alink << ", " << link_ptr << endl;
}
