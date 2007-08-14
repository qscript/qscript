#include <cstdio>
#include <iostream>
using namespace std;
#include "global.C"
char a;
char b;
char d;
int global_val;
int edit_data(char  c[120]);
void func3(float fundc3_a,float func3_b);
int edit_data
(char  c[120]){
int ser_no;
/* DATA CONVERSION */
{int tmp1=0 ;
int tmp2=3 ;
if(tmp2-tmp1==sizeof(int)-1){
	char buff[sizeof(int)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	int *i_ptr = static_cast<int *>(v_ptr);
	 ser_no=*i_ptr;
}else { 
	cerr << "runtime error: line_no : expr out of bounds" << 54;}
}
printf("ser_no:%d\n", ser_no );
char mychar;
mychar =c[4 ];
a =c[4 ];
global_val =c[4 ];
printf("mychar: %c", mychar );
mychar =c[5 ];
b =c[5 ];
printf("mychar: %c", mychar );
mychar =c[6 ];
d =c[7 ];
printf("mychar: %c", mychar );
mychar =c[7 ];
printf("mychar: %c", mychar );
float myfloat;
/* DATA CONVERSION */
{int tmp1=80 ;
int tmp2=83 ;
if(tmp2-tmp1==sizeof(float)-1){
	char buff[sizeof(float)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	float *f_ptr = static_cast<float *>(v_ptr);
	 myfloat=*f_ptr;
}else { cerr << "runtime error: line_no : expr out of bounds" << 54;}
}
list0 [myfloat]++;
printf(":float: %f", myfloat );
func3(1.100000 , 2 );
int i;
for (i =80 ;i  < 120 ;i =i  + 4 ){
float f;
/* DATA CONVERSION */
{int tmp1=i ;
int tmp2=i  + 3 ;
if(tmp2-tmp1==sizeof(float)-1){
	char buff[sizeof(float)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	float *f_ptr = static_cast<float *>(v_ptr);
	 f=*f_ptr;
}else { cerr << "runtime error: line_no : expr out of bounds" << 54;}
}
printf("f=%f", f );
}
 /* printing ife_stmt: if_stmt 5484976 */
if (! i ){
printf("%s", "Hello,World\n");
}
printf("\n");
}
void func3
(float fundc3_a,float func3_b){
printf("called: func3\n");
 /* printing ife_stmt: if_stmt 5488288 */
if (fundc3_a  == 1.100000 ){
printf("fundc3_a==1.1\n");
}
 else {
printf("fundc3_a=%f\n", fundc3_a );
}
}
#include "my_axes.C"
void ax_compute(){
	ax_q1.compute();
	ax_q2.compute();
	ax_q3.compute();
}
#include "my_table.C"
void tab_compute(){
	tab_q1_q2.compute();
	tab_q1_q3.compute();
}
void tab_summ(){
	tab_q1_q2.print();
	tab_q1_q3.print();
}
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <sys/mman.h>

using namespace std;
int read_data(int fd, struct stat &file_info_stat, int rec_len);
int mmap_read_data(int fd, struct stat &file_info_stat, int rec_len);
int main(int argc, char * argv[]){
	
	int fd=open(argv[1], O_RDONLY);
	if(argc !=3) {
		cout << "Usage: " << argv[0] << " <datafile_name> <reclen>"  << endl; 
		exit(1);
	}

	char * endptr=NULL;
	int convert_to_base=10;
	int rec_len=strtol(argv[2],&endptr, convert_to_base);
	if(endptr==NULL){
		cerr << "invalid reclen terminating " << endl;
		exit(1);
	} else if (rec_len==0){
		cerr << "reclen was not converted properly terminating" << endl;
		exit(1);
	}
	// assert the the file size is perfectly divisible by the given reclen
	struct stat file_info_stat;
	if(fstat(fd, &file_info_stat)<0){
		cerr << "fstat error: unable to stat data file: " << argv[1] << endl;
		exit(1);
	} else if(! S_ISREG(file_info_stat.st_mode)){
		cout << argv[1] << " not a regular file" << endl;
	} else {
		cout << " best blk size: " << file_info_stat.st_blksize << endl;
	}
	long int file_size=file_info_stat.st_size;
	cout << argv[1] << " filesize is: " << file_info_stat.st_size << endl;
	if (file_size%rec_len!=0){
		cerr << "Filesize should be exactly divisible by reclen" << endl;
		exit(1);
	}
	read_data(fd, file_info_stat, rec_len);
	//mmap_read_data (fd, file_info_stat, rec_len);
	print_list_counts();
	tab_summ();

}

int read_data(int fd, struct stat &file_info_stat, int rec_len){
	cout << "read_data" << endl;
	char* buffer=new char[sizeof(char)* rec_len];
	int r_val=0;
		
	while(1){
		//memset(buffer,0, rec_len);
		int n_read=read(fd, buffer, rec_len); 
		if(n_read==0){
			r_val=0;
			break;
		} else if(n_read<0 || n_read!=rec_len){
			cerr<< "Error reading file: check record size" 
				<< "n_read: " << n_read
				<< "rec_len: " << rec_len
				<< endl;
			r_val=1;
			break;
		} else{
			//cout << "rec_no: " << ++rec_no << endl;
			edit_data(buffer);
			ax_compute();
			tab_compute();
			cout << ".";
		}
	}
	cout << endl;
	delete [] buffer;
	cout << "END read_data" << endl;
	return r_val;
}

int mmap_read_data(int fd, struct stat &file_info_stat, int rec_len){
	cout << "mmap_read_data" << endl;
	char* buffer=new char[sizeof(char)* rec_len];
	int r_val=0;
	void * src = mmap(0, file_info_stat.st_size, PROT_READ,
			MAP_FILE|MAP_SHARED, fd,0);
	char * char_src=static_cast<char*>(src);
	if(src==MAP_FAILED){
		cerr << "Unable to mmap file" << endl;
		return 0;
	}
	char * src_ptr=char_src;
	while(src_ptr<char_src+file_info_stat.st_size){
		//memset(buffer,0, rec_len);
		//int n_read=read(fd, buffer, rec_len); 
		memcpy(buffer,src_ptr, rec_len);
		src_ptr+=rec_len;
		cout << ".";
		edit_data(buffer);
	}
	cout << endl;
	delete [] buffer;
	cout << "END mmap_read_data" << endl;
	return r_val;
}
#include "print_list_counts.C"
#include "list_summ_template.C"
