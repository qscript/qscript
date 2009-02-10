#include "named_range.h"
#include <iostream>

named_range::~named_range(){
}

void named_range::generate_code (ostringstream & quest_defns, ostringstream& program_code){
	//std::cout << "named_range:: generate_code()" << endl;

	quest_defns << "vector <stub_pair> " << name 
		//<< "(" << stubs.size() << ");"  
		<< ";" << endl << endl;

	for(int i=0; i<stubs.size(); ++i){
		//quest_defns << name << ";//named_range " << endl;
		quest_defns << name << ".push_back( stub_pair(\"" << stubs[i].stub_text 
			<< "\", " << stubs[i].code << "));" 
			<< endl;
	}
	//quest_defns << "};" << endl;
	if(next){
		next->generate_code(quest_defns, program_code);
	}
}

