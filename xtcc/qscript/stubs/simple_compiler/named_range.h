/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/named_range.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

#ifndef xtcc_named_range_h
#define xtcc_named_range_h
#include "stub_pair.h"
#include "stmt.h"
#include <fstream>

struct named_range: public stmt{
	string name;
	vector <stub_pair> stubs;
	//named_range(): name(""), stubs(){}
	void generate_code(ostringstream & quest_defns, ostringstream& program_code);
	named_range(datatype l_type, int l_line_number, 
		string l_name, vector <stub_pair>& l_stubs ):
		stmt(l_type, l_line_number),
		name(l_name), stubs(l_stubs)
	{
		//cout << "named_range: constructor" << endl;
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
		~named_range();
	};

#endif /* xtcc_named_range_h */
