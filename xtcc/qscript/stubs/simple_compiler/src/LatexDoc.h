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


		friend std::ostream & operator<<(std::ostream &os, LatexDocument &d)
		{
			const char *tex_begin = "\\documentclass[8pt,twocolumn]{article}\n\\begin{document}\n";
			const char *tex_end = "\\end{document}\n";
			os << tex_begin;
			REP(i,d.qv.size()){ int j=i; while(j<d.qv.size() && d.qv[j]->nr_ptr==d.qv[i]->nr_ptr) j++; d.package(os,i,j); i = j-1; }	
			return os << tex_end;
		}
	LatexDocument(): qv()
	{ }

	public:
		std::vector<NamedStubQuestion*> qv;
		
		void package(std::ostream &os, int i, int j);

		static std::string safe(const std::string &s);
		
		void visit(AbstractStatement *stmt);
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
