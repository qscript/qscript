#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
using namespace std;

void dump_data(char data[], int rec_no);

char* human_readable_csv_data_name = "human_readable_data.csv";
FILE * human_readable_csv_data=fopen(human_readable_csv_data_name, "wb");
void print_data_headers();

int main(){
	char * fname="sample2.dat";
	int fd=open("sample2.dat", O_WRONLY|O_CREAT|O_TRUNC);
	if(!human_readable_csv_data){
		fprintf(stderr, "unable to open %s for writing", human_readable_csv_data_name);
		exit(1);
	}
	if(fd==-1){
		cerr << "Error trying to create file sample2.dat for writing\n";
		exit(1);
	}
	char buffer[140];
	cout << "sizeof(buffer): " << sizeof(buffer) << endl;

	print_data_headers();
	for(int i=101;i<=400;++i){
		
		memset(buffer,0, sizeof(buffer));
		fprintf(human_readable_csv_data, "%d,", i);
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
void print_data_headers(){
	fprintf(human_readable_csv_data, "SNO,");
	for(char c='A';c<='Z';++c){
		fprintf(human_readable_csv_data, "Letter_%c,", c);
	}
	for(char c='0';c<='9';++c){
		fprintf(human_readable_csv_data, "Digit_%c,", c);
	}
	for(int i=1; i<11; ++i){
		fprintf(human_readable_csv_data, "Integer,");
	}
	for(int i=1; i<11; ++i){
		fprintf(human_readable_csv_data, "Float,");
	}
	for(int i=1; i<=5;  ++i){
		fprintf(human_readable_csv_data, "Integer,");
	}
	fprintf(human_readable_csv_data, "\n");
}
void dump_data(char data[], int rec_no){

	static int first_time=1;

	FILE * fptr=0;
	if (first_time) fptr= fopen("sample2.map", "wb");
	if(first_time){
		fprintf(fptr, "SNO,1,4\n");
	}
	char * my_ptr=data;
	// output the serial number	
	void *ptr =&rec_no;
	
	char * c_ptr=static_cast<char*>(ptr);
	for(int i=0; i<sizeof(int); ++i){
		*my_ptr++=*c_ptr++;
	}
	if(first_time) fprintf(fptr, "char a-z,%d,%d\n", 5, 5+26-1);
	//cout << "my_ptr-data=" << my_ptr-data << endl;
	// output 26 letters
	for(char c='A';c<='Z';++c){
		*my_ptr++=c;
		fprintf(human_readable_csv_data, "%c,", c);
	}

	if(first_time) fprintf(fptr, "char digits 0-9,%d,%d\n", 5+26-1+1, 5+26-1+10);
	//output 10 digits
	for(char c='0';c<='9';++c){
		*my_ptr++=c;
		fprintf(human_readable_csv_data, "%c,", c);
	}
	//output 10 ints: 40 bytes
	if(first_time) fprintf(fptr, "4 byte ints ,%d,%d\n", 5+26-1+10+1, 5+26-1+10+1*10*4);
	for(int i=1; i<11; ++i){
		int no=i*100+rec_no;
		ptr=&no;
		c_ptr=static_cast<char*> (ptr);
		for(int j=0; j<sizeof(int); ++j){
			*my_ptr++=*c_ptr++;
		}
		fprintf(human_readable_csv_data, "%d,", no);
	}
	if(first_time) fprintf(fptr, "4 byte floats ,%d,%d\n",  5+26-1+10+1*10*4+1,5+26-1+10+10*4+10*4);
	for(int i=1; i<11; ++i){
		float no=rec_no+(static_cast<float>(rec_no)/i);
		ptr=&no;
		c_ptr=static_cast<char*> (ptr);
		for(int j=0; j<sizeof(float); ++j){
			*my_ptr++=*c_ptr++;
		}
		fprintf(human_readable_csv_data, "%f,", no);
	}

	// some data for the fld statement
	if(first_time) fprintf(fptr, "4 byte floats ,%d,%d\n",  5+26-1+10+1*10*4+10*4+1,5+26-1+10+10*4+10*4+5*4);
	for(int i=1; i<=5;  ++i){
		int no=(i+rec_no)%20;
		printf( "fld data: %d,", no);
		ptr=&no;
		c_ptr=static_cast<char*> (ptr);
		for(int j=0; j<sizeof(int); ++j){
			*my_ptr++=*c_ptr++;
		}
		fprintf(human_readable_csv_data, "%d,", no);
	}
	printf( "\n");

	//cout << "my_ptr-data=" << my_ptr-data << endl;
	if(first_time) fclose(fptr);
	fprintf(human_readable_csv_data, "\n");
	if(first_time) first_time=0;
}
