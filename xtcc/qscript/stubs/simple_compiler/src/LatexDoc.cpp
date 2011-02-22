//Grzegorz Prusak
// Modified by Neil X Dsouza and integrated into the qscript compiler
//
#include <cstdio>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
//#include "include/qscript_parser.h"
#include "LatexDoc.h"

// int yyparse();
// void yyrestart(FILE *);
// void InitStatement();

#define REP(i,n) for(int i=0; i<(n); ++i)
#define FOR(i,p,k) for(int i=(p); i<=(k); ++i)

#define exc_flags std::ios::failbit | std::ios::badbit

#if 0
void LatexDocument::parse(const std::string &source_file)
{
	FILE *f = fopen(source_file.c_str(),"r"); if(!f) throw "parse: cannot open file \""+source_file+"\""; 
	InitStatement(); qscript_parser::active_scope_list.push_back(new Scope()); yyrestart(f);
	if(yyparse() || qscript_parser::no_errors) throw std::string("parse: errors while yyparse()");
	fclose(f); qv.clear(); visit(qscript_parser::tree_root);
}
#endif /* 0 */

/*
friend std::ostream & operator<<(std::ostream &os, LatexDocument &d)
{
	const char *tex_begin = "\\documentclass[8pt,twocolumn]{article}\n\\begin{document}\n";
	const char *tex_end = "\\end{document}\n";
	os << tex_begin;
	REP(i,d.qv.size()){ int j=i; while(j<d.qv.size() && d.qv[j]->nr_ptr==d.qv[i]->nr_ptr) j++; d.package(os,i,j); i = j-1; }	
	return os << tex_end;
}
*/


void LatexDocument::package(std::ostream &os, int i, int j)
{
	os << "\\parbox{8cm} {\n";
	os << "\\noindent\n\\begin{tabular}{p{0.7cm}p{6cm}}\n";
	//os << "\\noindent\n\\begin{tabular}{p{2cm}p{14cm}}\n";
	FOR(k,i,j-1) os << "\\bfseries{" << safe(qv[k]->questionName_) << "} & \\bfseries{" << safe(qv[k]->questionText_) << "}\\\\\n";
	os << "\\end{tabular}\n"
		"\\newline\n"
		"\\nopagebreak[3]\n"
		"\\noindent\n"
		;
	std::vector<stub_pair> &vsp = qv[i]->nr_ptr->stubs;
	int max_stub_length = 0;
	for (int i=0; i<vsp.size(); ++i) {
		if (max_stub_length < vsp[i].stub_text.length()) {
			max_stub_length = vsp[i].stub_text.length();
		}
	}
	std::cout << "max_stub_length: " << max_stub_length << std::endl;
	int stub_text_col_width = 0;
	if (max_stub_length > 25) {
		stub_text_col_width = 6;
	} else if (max_stub_length > 20) {
		stub_text_col_width = 5;
	} else if (max_stub_length > 15) {
		stub_text_col_width = 4;
	} else if (max_stub_length > 10) {
		stub_text_col_width = 3;
	} else if (max_stub_length > 5) {
		stub_text_col_width = 2;
	} else {
		stub_text_col_width = 1;
	}
	std::cout << "stub_text_col_width: " << stub_text_col_width << std::endl;
	os << "\\begin{tabular}{|p{"  << stub_text_col_width << "cm}|"; 
	int accum_width = stub_text_col_width;
	FOR(k,i,j-1) { 
		os << "p{1cm}|"; 
		accum_width += 1;
	}
	os << "}\n\\hline\n";
	FOR(k,i,j-1) os << " & " << safe(qv[k]->questionName_); os << "\\\\\n\\hline\n";
	REP(x,vsp.size()){ os << safe(vsp[x].stub_text); FOR(k,i,j-1) os << " & " << vsp[x].code; os << " \\\\\n"; }
	os << "\\hline\n\\end{tabular}\\\\\n";
	os << "}\n";
	os << "\\newline\n";
	if (accum_width > 7) {
		os << "\\enlargethispage*{1000pt}\n";
		//os << "\\pagebreak[3]\n";
		os << "\\newpage\n";
		os << "\\cleardoublepage\n";
		os << "\\clearpage\n";
	} else {
		os << "\\pagebreak[0]\n";
	}

}

std::string LatexDocument::safe(const std::string &s)
{
	std::string res; REP(i,s.size()) switch(s[i])
	{ case'~':case'#':case'$':case'%':case'^':case'&':case'_':case'\\':case'{':case'}': res+='\\'; default: res+=s[i]; }
	return res;
}

void LatexDocument::visit(AbstractStatement *stmt)
{
	if(!stmt) return;
	if(AbstractQuestion *q = dynamic_cast<AbstractQuestion*>(stmt))
	{
		if(RangeQuestion *rq = dynamic_cast<RangeQuestion*>(q));
		else if(NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion*>(q))
			qv.push_back(nq);
		else if(DummyArrayQuestion *dq = dynamic_cast<DummyArrayQuestion*>(q))
			throw std::string("parse: DummyArrayQuestion not handled yet");
		else throw std::string("parse: unknown question type");
	}
	else if(CompoundStatement *cs = dynamic_cast<CompoundStatement*>(stmt)) visit(cs->compoundBody_);
	else if(ForStatement *fs = dynamic_cast<ForStatement*>(stmt)) visit(fs->forBody_);
	else if(FunctionStatement *fs = dynamic_cast<FunctionStatement*>(stmt)) visit(fs->functionBody_);
	else if(IfStatement *is = dynamic_cast<IfStatement*>(stmt)){ visit(is->ifBody_); visit(is->elseBody_); }
	visit(stmt->next_);
}

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


std::ostream & operator<<(std::ostream &os, LatexDocument &d)
{
	//const char *tex_begin = "\\documentclass[8pt,twocolumn]{article}\n\\begin{document}\n";
	const char *tex_begin = "\\documentclass[10pt,twocolumn,a4paper]{article}\n"
					"\\usepackage[cm]{fullpage}\n"
					"\\setlength{\\columnsep}{1pt}\n"
					"%two column float page must be 90% full\n"
					"\\renewcommand\\dblfloatpagefraction{.45}\n"
					"%two column top float can cover up to 80% of page\n"
					"\\renewcommand\\dbltopfraction{.45}\n"
					"%float page must be 90% full\n"
					"\\renewcommand\\floatpagefraction{.45}\n"
					"%top float can cover up to 80% of page\n"
					"\\renewcommand\\topfraction{.45}\n"
					"%bottom float can cover up to 80% of page\n"
					"\\renewcommand\\bottomfraction{.45}\n"
					"%at least 10% of a normal page must contain text\n"
					"\\renewcommand\\textfraction{.1}\n"

				//	"\\usepackage[landscape,a4paper]{geometry}\n"
					"\\begin{document}\n"
					;
	const char *tex_end = "\\end{document}\n";
	os << tex_begin;
	REP(i,d.qv.size()){ int j=i; while(j<d.qv.size() && d.qv[j]->nr_ptr==d.qv[i]->nr_ptr) j++; d.package(os,i,j); i = j-1; }	
	return os << tex_end;
}
