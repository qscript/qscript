#include <cstring>
#include <fstream>
#include <iostream>


using namespace std;

int read_data_in_loop(ifstream& ifile, ofstream & ofile);
void extract_ser_cd_no(char * buffer);

int main(int argc, char* argv[]){
	if( argc!=3) {
		cout << "Usage: " << endl
			<< argv[0] << " <input_data_file> <output_data_file>" << endl;
	}
	ifstream ifile(argv[1], ios_base::in);
	ofstream ofile(argv[2], ios_base::out);
	return	read_data_in_loop(ifile, ofile);
}

int read_data_in_loop(ifstream& ifile, ofstream& ofile){
	int reclen=70;
	char * buffer=new char [reclen];
	while (ifile.good()&&!ifile.eof()){
		memset(buffer, 0, reclen); 
		ifile.read(buffer, reclen);
		int chars_read=ifile.gcount();
		if( chars_read) {
			extract_ser_cd_no(buffer);
			ofile.write(buffer, chars_read);
			cout << chars_read << endl; 
		}
	}
	return 0;
}

void extract_ser_cd_no(char * buffer){
	int ser_no=0;
	for(int i=0; i<4; ++i){
		ser_no<<=8;
		ser_no|= static_cast<unsigned char>(buffer[i]& 0xff);
		int tmp = buffer[i];
		cout << "buffer[" << i << "]=" << tmp << "	";
	}
	cout << endl;
	cout << "ser_no: " << ser_no << endl;
	int cd_no=0;
	for(int i=4; i<8; ++i){
		cd_no<<= 8;
		cd_no|= (buffer[i]&0xff) ;
	}
	cout << "ser_no: " << ser_no << endl
		<< "cd_no: " << cd_no << endl;
}
