
#ifndef xtcc_named_range_h
#define xtcc_named_range_h
#include "stub_pair.h"
#include <fstream>
	struct named_range{
		string name;
		vector <stub_pair> stubs;
		named_range(): name(""), stubs(){}
		named_range(string l_name, vector <stub_pair>& l_stubs ):
			name(l_name), stubs(l_stubs)
		{
			cout << "named_range: constructor" << endl;
	#if 0
			string fname=name + ".qin";
			ofstream ifile(fname.c_str(), ios_base::out);
			if(!ifile) {
				cerr << "Unable to open include file for outputting stubs" << endl;
				return;
			}
			int scale=name[name.length()-1]-'0';
			cout <<"scale: " << scale << "name[len-1]=" << name[name.length()-1] << endl;

			if(scale==5 && scale==stubs.size()){

				ifile << "net1Bottom 2 BOX(NET);noexport;" << endl << 
					"&myfld" << endl;
				int j=0;
				for(j=0; j<2;++j){
					ifile << 
					"+(" << 
					stubs[j].code << ")" <<
					stubs[j].stub_text << "=" << 
					stubs[j].code << ";%fac=" <<
					stubs[j].code << 
					endl;
				}
				ifile << "netend1" << endl << 
					 "&myfld" << endl <<
					"+(" << 
					stubs[j].code << ")" <<
					stubs[j].stub_text << "=" << 
					stubs[j].code << ";%fac=" <<
					stubs[j].code << endl <<
					"net1Top 2 BOX(NET);noexport" << endl << 
					"&myfld" << endl;
				for(j=3; j<5;++j){
					ifile << "+(" << 
					stubs[j].code << ")" <<
					stubs[j].stub_text << "=" << 
					stubs[j].code << ";%fac=" <<
					stubs[j].code << 
					endl;
				}
				ifile << "netend1" << endl;
				ifile << "n25;inc=c(a0);c=c(a0)'1/" << scale << 
					"';noexport;" <<endl;
				ifile << "#include imean.qin" << endl;
			} else if(scale==7 && scale==stubs.size()){
				ifile << "net1Bottom 3 BOX(NET);noexport" << endl << 
					"&myfld" << endl;
				int j=0;
				for(j=0; j<3;++j){
					ifile << 
					"+(" << 
					stubs[j].code << ")" <<
					stubs[j].stub_text << "=" << 
					stubs[j].code << ";%fac=" <<
					stubs[j].code << 
					endl;
				}
				ifile << "netend1" << endl << 
					 "&myfld" << endl <<
					"+(" << 
					stubs[j].code << ")" <<
					stubs[j].stub_text << "=" << 
					stubs[j].code << ";%fac=" <<
					stubs[j].code << endl <<
					"net1Top 3 BOX(NET);noexport" << endl << 
					"&myfld" << endl;
				for(j=4; j<7;++j){
					ifile << "+(" << 
					stubs[j].code << ")" <<
					stubs[j].stub_text << "=" << 
					stubs[j].code << ";%fac=" <<
					stubs[j].code << 
					endl;
				}
				ifile << "netend1" << endl;
				ifile << "n25;inc=c(a0);c=c(a0)'1/" << scale << 
					"';noexport;" <<
					endl;
				ifile << "#include imean.qin" << endl;
			} else {
				ifile << "&myfld" << endl;
				for(int j=0; j<stubs.size();++j){
					ifile << "+" <<
					stubs[j].stub_text << "=" << 
					stubs[j].code << endl;
				}
			}
#endif /*  0 */
		}
	};

#endif /* xtcc_named_range_h */
