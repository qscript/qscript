//Grzegorz Prusak
// Modified by Neil X Dsouza and integrated into the qscript compiler
//
#include <cstdio>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "qscript_parser.h"

// int yyparse();
// void yyrestart(FILE *);
// void InitStatement();

#define REP(i,n) for(int i=0; i<(n); ++i)
#define FOR(i,p,k) for(int i=(p); i<=(k); ++i)

#define exc_flags std::ios::failbit | std::ios::badbit

class LatexDocument
{
public:
	void parse(const std::string &source_file);


	//friend std::ostream & operator<<(std::ostream &os, LatexDocument &d);

	LatexDocument(std::string latex_fname): qv(),
		questionProcessedUpto_(0)
	{ 

		latex_file.exceptions(exc_flags); 
		latex_file.open(latex_fname.c_str());
		latex_file << setup_latex();
	}
	~LatexDocument();
	std::ofstream latex_file; 

public:
	//std::vector<NamedStubQuestion*> qv;
	std::vector<AbstractQuestion*> qv;
	void package(std::ostream &os, int i, int j);
	static std::string safe(const std::string &s);
	void visit(AbstractStatement *stmt);
	string setup_latex();
	string finish_latex();
	int questionProcessedUpto_;
	void ProcessQuestions();
};

/*
int main(int argc, char **argv)
{
	if(argc<3){ std::cout << "usage: " << argv[0] << " input_script_file output_TeX_file\n"; exit(EXIT_FAILURE); }
	try { std::ofstream of; of.exceptions(exc_flags); of.open(argv[2]); LatexDocument doc; doc.parse(argv[1]); of << doc; }
	catch(const std::ios::failure &e){ std::cout << "IO error: " << e.what() << "\n"; }
	catch(const std::string &s){ std::cout << "error: " << s; }
	
	return 0;
}
*/
