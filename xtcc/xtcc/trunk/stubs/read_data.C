#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
using namespace std;

void print_rec(char * data);

int main(unsigned int argc, char * argv[]){
	int fd=open(argv[1], O_RDONLY);
	if(fd==-1){
		cerr << "Error opening file sample.dat for reading\n";
		exit(1);
	}
	char buffer[120];
	int r_val=1;
	int rec_no=0;
	while(1){
		memset(buffer,0, sizeof(buffer));
		int n_read=read(fd, buffer, sizeof(buffer)); 
		if(n_read==0){
			r_val=0;
			break;
		} else if(n_read<0 || n_read!=sizeof(buffer)){
			cerr<< "Error reading file: check record size" 
				<< "n_read: " << n_read
				<< "sizeof(buffer): " << buffer
				<< endl;
			r_val=1;
			break;
		} else{
			cout << "rec_no: " << ++rec_no << endl;
			print_rec(buffer);
			/*
			r_val=1;
			cout << "Error: should not happen: n_read: " << n_read
				<< " sizeof(buffer): " << sizeof(buffer)
				<<endl;
			break;
			*/
		}
	}
}

void print_rec(char * data){
	char buff[4];

	void *ptr=data;
	int * i_ptr;
	float * f_ptr;
	for(int i=0; i<sizeof(int);++i){
		buff[i]=data[i];
	}
	ptr=buff;
	i_ptr=static_cast<int*>(ptr);
	int ser_no=*i_ptr;
	cout << "converted ser_no: " << ser_no << endl;
	char * c_ptr=data+sizeof(int);
	for( int i=0; i<26; ++i){
		char c=c_ptr[i];
		cout << "c=" << c << endl;
	}
	c_ptr+=26;
	for( int i=0; i<10; ++i){
		char c=c_ptr[i];
		cout << "c=" << c << endl;
	}
	c_ptr+=10;
	for( int j=1; j<11; ++j){
		for(int i=0; i<sizeof(int);++i){
			buff[i]=c_ptr[i];
		}
		ptr=buff;
		i_ptr=static_cast<int*>(ptr);
		int i_data=*i_ptr;
		cout << "i_data: " << i_data << endl;
		c_ptr+=sizeof(int);
	}
	for( int j=1; j<11; ++j){
		for(int i=0; i<sizeof(float);++i){
			buff[i]=c_ptr[i];
		}
		ptr=buff;
		float* f_ptr=static_cast<float*>(ptr);
		float f_data=*f_ptr;
		cout << "f_data: " << f_data << endl;
		c_ptr+=sizeof(int);
	}
}
