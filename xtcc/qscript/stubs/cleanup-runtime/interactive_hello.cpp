#include <iostream>

#include <string>

int main()
{

	using std::string;
	using std::cout;
	using std::cin;
	using std::endl;
	cout << "Hello, What is your name: " << endl;
	string name;
	cin >> name;
	cout << "hello, " << name << endl;
	return 0;
}
