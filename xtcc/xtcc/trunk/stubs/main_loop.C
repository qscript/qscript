
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include "ax_stmt_type.h"
//#include <sys/mman.h>

using namespace std;
int fread_data(FILE * & inp_data_file , int file_size, int rec_len);

int read_data(int fd, struct stat &file_info_stat, int rec_len);
int mmap_read_data(int fd, struct stat &file_info_stat, int rec_len);
int main(int argc, char * argv[]){
	xtcc_stdout=fopen(xtcc_stdout_fname.c_str(), "w");
	runtime_errors = fopen("runtime_errors.log", "w");
	if(xtcc_stdout==0){
		cerr << "Unable to open " << xtcc_stdout_fname.c_str() << " as stdout exiting" << endl;
		exit(1);
	}
	
	//int fd=open(argv[1], O_RDONLY);
	if(argc !=3) {
		cout << "Usage: " << argv[0] << " <datafile_name> <reclen>"  << endl; 
		exit(1);
	}
	FILE * inp_data_file=fopen(argv[1], "rb");
	if(!inp_data_file){
		cerr << "Unable to open data file : " << argv[1] << endl;
		exit(1);
	}
	int rval=fseek(inp_data_file, 0, SEEK_END);
	long file_size=-1;
	if(!rval){
		file_size=ftell(inp_data_file);
	}

	char * endptr=0;
	int convert_to_base=10;
	int rec_len=strtol(argv[2],&endptr, convert_to_base);
	if(!endptr){
		cerr << "invalid reclen terminating " << endl;
		exit(1);
	} else if (rec_len==0){
		cerr << "reclen was not converted properly terminating" << endl;
		exit(1);
	}
	// assert the the file size is perfectly divisible by the given reclen
	/*
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
	*/
	if (file_size%rec_len!=0){
		cerr << "Filesize should be exactly divisible by reclen" << endl;
		exit(1);
	}
	//fread_data(inp_data_file, file_info_stat, rec_len);
	fread_data(inp_data_file, file_size, rec_len);
	//mmap_read_data (fd, file_info_stat, rec_len);
	print_list_counts();
	tab_summ();

}

#include <sys/types.h>
/*
int read_data(int fd, struct stat &file_info_stat, int rec_len){
	cout << "read_data" << endl;
	//int8_t* buffer=new int8_t[sizeof(int8_t)* rec_len];
	int r_val=0;
		
	while(1){
		//memset(buffer,0, rec_len);
		int n_read=read(fd, c, rec_len); 
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
			//edit_data(buffer);
			edit_data();
			ax_compute();
			tab_compute();
			cout << ".";
		}
	}
	cout << endl;
	//delete [] buffer;
	cout << "END read_data" << endl;
	return r_val;
}

//#if UNIX_H
int mmap_read_data(int fd, struct stat &file_info_stat, int rec_len){
	cout << "mmap_read_data" << endl;
	//int8_t* buffer=new int8_t[sizeof(int8_t)* rec_len];
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
		memcpy(c,src_ptr, rec_len);
		src_ptr+=rec_len;
		cout << ".";
		//edit_data(buffer);
		edit_data();
	}
	cout << endl;
	//delete [] buffer;
	cout << "END mmap_read_data" << endl;
	return r_val;
}
//#endif  UNIX_H 
*/

#include "print_list_counts.C"
/*#include "../stubs/list_summ_template.C"*/
int fread_data(FILE * & inp_data_file , int file_size, int rec_len){
	cout << "read_data" << endl;
	//char* buffer=new char[sizeof(char)* rec_len];
	int seek_res=fseek(inp_data_file, 0, SEEK_SET);
	int r_val=0;
		
	int n_records = 0;
	cout << "Each dot('.') represents 100 records read\n";
	while(1){
		//memset(buffer,0, rec_len);
		int n_read= fread(c ,  sizeof(char), rec_len,  inp_data_file);
		if(n_read==0){
			r_val=0;
			break;
		} else if(n_read<0 || n_read!=rec_len){
			cerr	<< "Error reading file: check record size" 
				<< "n_read: " << n_read
				<< "rec_len: " << rec_len
				<< endl;
			r_val=1;
			break;
		} else{
			//cout << "rec_no: " << ++rec_no << endl;
			edit_data();
			ax_compute();
			tab_compute();
			++n_records;
		}
		if (n_records % 100 == 0) {
			cout << ".";
		}
		if (n_records % 50 == 0) {
			cout << "\n";
		}
	}
	cout << "\nTotal records: " << n_records << endl; 
	cout << endl;
	//delete [] buffer;
	cout << "END read_data" << endl;
	return r_val;
}
