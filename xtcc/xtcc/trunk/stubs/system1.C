#include <iostream>
#include <cstdlib>

using namespace std;
int compile(string filename);

int main(int argc, char * argv[], char * envp[]){
	compile("temp.C");
}

int compile(string filename){
	system("cat edit_out.c main_loop.C > temp.C");
	string cmd="g++  " + filename + " -o " + filename + ".exe" ;
	int ret_val=system(cmd.c_str());
	if(ret_val){
		cout << "Error compiling file: shell returned: " << ret_val << endl;
	}
}
