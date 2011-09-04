
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <dirent.h>
#include <string>
#include <string>
#include <vector>
using namespace std;

int find_file_in_dir(string filename, const vector<string> & dir_list);
bool find_file_entry_in_directory(string filename, DIR * directory_ptr);

int main()
{
	stringstream path; 
	path << "PATH=" << getenv("PATH");  
	path << ";c:\\usr\\Mingw-foo7\\bin;c:\\usr\\bin;c:\\usr\\lib";
	//cout << "PATH is : " << path.str() << endl
	//	<< "=================" << endl;
	//putenv(path.str().c_str());
	putenv("PATH=c:\\");
	std::cout<<getenv("PATH");  
	system("g++ --help");
	cout	<< "=================" << endl;
	cout << getenv("PATH") << endl;
	stringstream path2; 
	path2 << "PATH=c:\\Mingw-foo7\\bin;c:\\usr\\bin;c:\\usr\\lib";
	putenv(path2.str().c_str());
	cout << getenv("PATH") << endl;
	system("g++ --help");

	vector<string> dir_list;
	dir_list.push_back("c:\\Mingw-foo7\\bin");
	dir_list.push_back("c:\\usr\\bin");
	dir_list.push_back("c:\\usr\\lib");


	int index = find_file_in_dir("pdcurses.dll", dir_list);
	if (index >= 0) {
		cout << "found pdcurses.dll in: " << dir_list[index] << endl;
	} else {
		cout << "did not find pdcurses.dll in given dirs" << endl;
	}
}

int find_file_in_dir(string filename, const vector<string> & dir_list)
{
	cout << "ENTER find_file_in_dir: " << endl;
	for (int i=0; i<dir_list.size(); ++i) {
		DIR * directory_ptr = opendir(dir_list[i].c_str());
		if (!directory_ptr) {
			cerr << "Unable to open directory : " << dir_list[i] << endl
				<< " for reading, skipping entry. Check your provided paths\n";
		} else {
			bool found = find_file_entry_in_directory(filename, directory_ptr);
			if (found == true) {
				return i;
			}
		}
	}
	return -1;
}


bool find_file_entry_in_directory(string filename, DIR * directory_ptr)
{
	struct dirent * directory_entry = readdir(directory_ptr);

	while (directory_entry) {
		string entry_name = directory_entry->d_name;
		if (entry_name == "pdcurses.dll") {
			return true;
		}
		directory_entry = readdir(directory_ptr);
	}
	return false;
}
