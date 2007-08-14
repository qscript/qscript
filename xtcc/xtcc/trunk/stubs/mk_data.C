#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
using namespace std;

void dump_data(char data[], int rec_no);


int main(){
	char * fname="sample.dat";
	int fd=open("sample.dat", O_WRONLY|O_CREAT|O_TRUNC);
	if(fd==-1){
		cerr << "Error trying to create file sample.dat for writing\n";
		exit(1);
	}
	char buffer[120];
	cout << "sizeof(buffer): " << sizeof(buffer) << endl;

	for(int i=101;i<=20000;++i){
		
		memset(buffer,0, sizeof(buffer));
		dump_data(buffer,i);
		int n_write=write (fd, buffer, sizeof(buffer));
		if(n_write!=sizeof(buffer)){
			cerr << "was not able to write : " << sizeof(buffer)
				<< " bytes to file exiting" << endl;
			exit(1);
		}
	}
	
}

#include <cstring>
void dump_data(char data[], int rec_no){
	char * my_ptr=data;
	// output the serial number	
	void *ptr =&rec_no;
	
	char * c_ptr=static_cast<char*>(ptr);
	for(int i=0; i<sizeof(int); ++i){
		*my_ptr++=*c_ptr++;
	}
	cout << "my_ptr-data=" << my_ptr-data << endl;
	// output 26 letters
	for(char c='A';c<='Z';++c){
		*my_ptr++=c;
	}
	//output 10 digits
	for(char c='0';c<='9';++c){
		*my_ptr++=c;
	}
	//output 10 ints: 40 bytes
	for(int i=1; i<11; ++i){
		int no=i*100;
		ptr=&no;
		c_ptr=static_cast<char*> (ptr);
		for(int j=0; j<sizeof(int); ++j){
			*my_ptr++=*c_ptr++;
		}
	}
	for(int i=1; i<11; ++i){
		float no=i+(static_cast<float>(i)/100);
		ptr=&no;
		c_ptr=static_cast<char*> (ptr);
		for(int j=0; j<sizeof(float); ++j){
			*my_ptr++=*c_ptr++;
		}
	}

	cout << "my_ptr-data=" << my_ptr-data << endl;
}
