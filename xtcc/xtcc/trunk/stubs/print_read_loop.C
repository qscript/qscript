
#include <iostream>
using  std::cout;
using  std::endl;
void  print_main_loop();

int main(){
	print_main_loop();
}

void  print_main_loop(){
	cout <<
"#include <cstring>"<< endl << 
"#include <fstream>"<< endl << 
"#include <iostream>"<< endl << 
endl <<
endl <<
"using namespace std;"<< endl << 
endl <<
"int read_data_in_loop(ifstream& ifile, ofstream & ofile);"<< endl << 
"void extract_ser_cd_no(char * buffer);"<< endl << 
endl <<
"int main(int argc, char* argv[]){"<< endl << 
"	if( argc!=3) {"<< endl << 
"		cout << \"Usage: \" << endl"<< endl << 
"			<< argv[0] << \" <input_data_file> <output_data_file>\" << endl;"<< endl << 
"	}"<< endl << 
"	ifstream ifile(argv[1], ios_base::in);"<< endl << 
"	ofstream ofile(argv[2], ios_base::out);"<< endl << 
"	return	read_data_in_loop(ifile, ofile);"<< endl << 
"}"<< endl << 
endl <<
"int read_data_in_loop(ifstream& ifile, ofstream& ofile){"<< endl << 
"	int reclen=70;"<< endl << 
"	char * buffer=new char [reclen];"<< endl << 
"	while (ifile.good()&&!ifile.eof()){"<< endl << 
"		memset(buffer, 0, reclen); "<< endl << 
"		ifile.read(buffer, reclen);"<< endl << 
"		int chars_read=ifile.gcount();"<< endl << 
"		if( chars_read) {"<< endl << 
"			extract_ser_cd_no(buffer);"<< endl << 
"			ofile.write(buffer, chars_read);"<< endl << 
"			cout << chars_read << endl; "<< endl << 
"		}"<< endl << 
"	}"<< endl << 
"	return 0;"<< endl << 
"}"<< endl << 
endl <<
"void extract_ser_cd_no(char * buffer){"<< endl << 
"	int ser_no=0;"<< endl << 
"	for(int i=0; i<4; ++i){"<< endl << 
"		ser_no<<=8;"<< endl << 
"		ser_no|= static_cast<unsigned char>(buffer[i]& 0xff);"<< endl << 
"		int tmp = buffer[i];"<< endl << 
"		cout << \"buffer[\" << i << \"]=\" << tmp << \"\t\";"<< endl << 
"	}"<< endl << 
"	cout << endl;"<< endl << 
"	cout << \"ser_no: \" << ser_no << endl;"<< endl << 
"	int cd_no=0;"<< endl << 
"	for(int i=4; i<8; ++i){"<< endl << 
"		cd_no<<= 8;"<< endl << 
"		cd_no|= (buffer[i]&0xff) ;"<< endl << 
"	}"<< endl << 
"	cout << \"ser_no: \" << ser_no << endl"<< endl << 
"		<< \"cd_no: \" << cd_no << endl;"<< endl << 
"}" << endl;

}
