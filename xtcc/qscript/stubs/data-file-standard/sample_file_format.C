#include <iostream>
#include <fstream>

using std::cout;
using std::cerr;
using std::endl;

void print_xtcc_file_format();
int main(){
		
	print_xtcc_file_format();
}


void print_xtcc_file_format()
{

	try {
		
		void* ptr=0;
		char* c_ptr=0;
		const int MY_BUF_SIZE=2048;
		char out_buf[MY_BUF_SIZE];
		char* curr_pos = out_buf;
		std::ofstream sample_data_file;
		sample_data_file.exceptions(std::ios::failbit | std::ios::badbit);
		sample_data_file.open("sample_job.xtdat");

		int count = sprintf(curr_pos, "%s\n", "xtcc");
		curr_pos+=count;
		count=sprintf(curr_pos, "0.0.0.0\n");
		curr_pos+=count;
		// 4 chars
		count=sprintf(curr_pos, "xtcc\n");
		curr_pos+=count;
		// 1 short int 
		short int s_int = 0x4142;
		ptr = &s_int;
		c_ptr=static_cast<char*> (ptr);
		*curr_pos++=*c_ptr++; // 1 byte of short int
		*curr_pos++=*c_ptr++; // 2nd byte of short int
		*curr_pos++='\n';

		long int int32_int = 0x43444546;
		ptr= &int32_int;
		c_ptr=static_cast<char*> (ptr);
		*curr_pos++=*c_ptr++; // 1st byte of long int
		*curr_pos++=*c_ptr++; // 2nd byte of long int
		*curr_pos++=*c_ptr++; // 3rd byte of long int
		*curr_pos++=*c_ptr++; // 4th byte of long int
		*curr_pos++='\n';
		
		float f32=3297809.75;
		ptr= &f32;
		c_ptr=static_cast<char*> (ptr);
		/*
		*c_ptr++='G'; 
		*c_ptr++='H'; 
		*c_ptr++='I'; 
		*c_ptr++='J'; 
		*/
		c_ptr=static_cast<char*> (ptr);
		*curr_pos++=*c_ptr++; // 1st byte of float
		*curr_pos++=*c_ptr++; // 2nd byte of float
		*curr_pos++=*c_ptr++; // 3rd byte of float
		*curr_pos++=*c_ptr++; // 4th byte of float
		*curr_pos++='\n';
		cout.precision(18);
		cout << "f32: " << f32 << endl;




		double d64= 7.10524632318153195520e20;
		ptr= &d64;
		c_ptr=static_cast<char*> (ptr);
		/*
		*c_ptr++='G'; 
		*c_ptr++='H'; 
		*c_ptr++='I'; 
		*c_ptr++='J'; 
		*c_ptr++='A'; 
		*c_ptr++='B'; 
		*c_ptr++='C'; 
		*c_ptr++='D'; 
		*/


		c_ptr=static_cast<char*> (ptr);
		*curr_pos++=*c_ptr++; // 1st byte of double
		*curr_pos++=*c_ptr++; // 2nd byte of double
		*curr_pos++=*c_ptr++; // 3rd byte of double
		*curr_pos++=*c_ptr++; // 4th byte of double
		*curr_pos++=*c_ptr++; // 5th byte of double
		*curr_pos++=*c_ptr++; // 6th byte of double
		*curr_pos++=*c_ptr++; // 7th byte of double
		*curr_pos++=*c_ptr++; // 8th byte of double

		*curr_pos++='\n';

		cout.precision(60);
		cout << "d64: " << d64 << endl;

		count = sprintf(curr_pos, "%s\n", "STUBINFORMATION");
		curr_pos+=count;

		count=sprintf(curr_pos, "age = \"15 to 21\" 1 \"22 to 30\" 2 \"31 to 40\" 3 \"41 to 59\" 4;\n");
		curr_pos+=count;

		count=sprintf(curr_pos, "csd_brand_list = \"Goqe\" 1 \"Bebzi\" 2 \"Oogla\" 3 \"Zingmoo\" 4 \"Thunder\" 5 \"Zoinks\" 6;\n");
		curr_pos+=count;

		count=sprintf(curr_pos, "qscript_q1_codelist=1-4;\n");
		curr_pos+=count;

		count=sprintf(curr_pos, "qscript_q2_codelist=1-2,5-8;\n");
		curr_pos+=count;

		count=sprintf(curr_pos, "qscript_ser_no=1-500,601-800;\n");
		curr_pos+=count;


		count = sprintf(curr_pos, "%s\n", "ENDSTUBINFORMATION");
		curr_pos+=count;


		// Forget about the blank space for now
		// here is the map.
		count = sprintf(curr_pos, "ser_no,sp,int32_t,1,4,qscript_ser_no;\n");
		curr_pos+=count;
		count = sprintf(curr_pos, "q1,sp,int32_t,5,8,qscript_q1_codelist;\n" );
		curr_pos+=count;
		count = sprintf(curr_pos, "q2,sp,int32_t,9,12,qscript_q2_codelist;\n" );
		curr_pos+=count;
		count = sprintf(curr_pos, "q3,sp,int32_t,13,16,age;\n" );
		curr_pos+=count;
		count = sprintf(curr_pos, "q4,sp,int32_t,17,20,csd_brand_list;\n" );
		curr_pos+=count;
		// For the mp question type I have dropped the number of codes
		// since it can be determined by 
		//((last_position-first_position)+1)/sizeof(question_type)
		count = sprintf(curr_pos, "q4_2,mp,int32_t,21,36,csd_brand_list;\n" );
		curr_pos+=count;
		*curr_pos++='\0';
		// I should be writing the raw data here - but 
		// from here on it should be easy for you to figure 
		// it out - we should be writing out chunks of
		// recormap.size() just like in your program
		sample_data_file.write(out_buf, curr_pos-out_buf); //pompon: second arg was "curr_pos-out_buf+1" so 1B of unused space was being written to the file

	}
	catch(...){ std::cerr << "error while trying to open  sample_job.xtdat file\n"; }
	
}
