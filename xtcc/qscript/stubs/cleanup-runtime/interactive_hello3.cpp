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
	//getline(cin, name);
	char line_buf[250];
	line_buf[249]=0;
	cin.get(line_buf, 249);
	//cin.getline (line_buf, 249);
	cout << "hello, " << name << endl;
	return 0;
}
