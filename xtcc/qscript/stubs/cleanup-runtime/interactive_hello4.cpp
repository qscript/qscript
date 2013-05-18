#include <iostream>
#include <cstdio>

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
	//cin >> age;
	char line_buf[250];
	line_buf[249]=0;
	fgets (line_buf, 249, stdin);
	sscanf (line_buf, "%d", &age);
	cout << "Hello, What is your name: " << endl;
	fgets (line_buf, 249, stdin);
	string name(line_buf);
	//cin >> name;
	//getline(cin, name);
	//cin.get(line_buf, 249);
	//cin.getline (line_buf, 249);
	cout << "hello, " << name << endl;
	return 0;
}
