#include <iostream>

#include <string>
// NxD - this program will not work when compiled with emscripten

int main()
{

	using std::string;
	using std::cout;
	using std::cin;
	using std::endl;
	cout << "Hello, What is your age: " << endl;
	int  age;
	cin >> age;
	cout << "Hello, What is your name: " << endl;
	string name;
	//cin >> name;
	getline(cin, name);
	cout << "hello, " << name << endl;
	return 0;
}
