#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
using namespace std;

void dump_data(char data[], int rec_no);


int main(){
	char * fname="sample2.dat";
	int fd=open("sample2.dat", O_WRONLY|O_CREAT|O_TRUNC);
	if(fd==-1){
		cerr << "Error trying to create file sample2.dat for writing\n";
		exit(1);
	}
	char buffer[120];
	cout << "sizeof(buffer): " << sizeof(buffer) << endl;

	for(int i=101;i<=400;++i){
		
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
#include <cstdio>
void dump_data(char data[], int rec_no){

	static int first_time=0;

	FILE * fptr=0;
	if (!first_time) fptr= fopen("sample2.map", "wb");
	if(!first_time){
		fprintf(fptr, "SNO,1,4\n");
	}
	char * my_ptr=data;
	// output the serial number	
	void *ptr =&rec_no;
	
	char * c_ptr=static_cast<char*>(ptr);
	for(int i=0; i<sizeof(int); ++i){
		*my_ptr++=*c_ptr++;
	}
	if(!first_time) fprintf(fptr, "char a-z,%d,%d\n", 5, 5+26);
	//cout << "my_ptr-data=" << my_ptr-data << endl;
	// output 26 letters
	for(char c='A';c<='Z';++c){
		*my_ptr++=c;
	}

	if(!first_time) fprintf(fptr, "char digits 0-9,%d,%d\n", 5+26+1, 5+26+10);
	//output 10 digits
	for(char c='0';c<='9';++c){
		*my_ptr++=c;
	}
	//output 10 ints: 40 bytes
	if(!first_time) fprintf(fptr, "4 byte ints ,%d,%d\n", 5+26+10+1, 5+26+10+1*10*4);
	for(int i=1; i<11; ++i){
		int no=i*100+rec_no;
		ptr=&no;
		c_ptr=static_cast<char*> (ptr);
		for(int j=0; j<sizeof(int); ++j){
			*my_ptr++=*c_ptr++;
		}
	}
	if(!first_time) fprintf(fptr, "4 byte floats ,%d,%d\n",  5+26+10+1*10*4+1,5+26+10+10*4+10*4);
	for(int i=1; i<11; ++i){
		float no=rec_no+(static_cast<float>(rec_no)/i);
		ptr=&no;
		c_ptr=static_cast<char*> (ptr);
		for(int j=0; j<sizeof(float); ++j){
			*my_ptr++=*c_ptr++;
		}
	}

	//cout << "my_ptr-data=" << my_ptr-data << endl;
	if(!first_time) fclose(fptr);
	++first_time;
}
