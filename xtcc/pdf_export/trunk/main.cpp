//Grzegorz Prusak
#include <cstdio>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "include/qscript_parser.h"

int yyparse();
void yyrestart(FILE *);
void InitStatement();

#define REP(i,n) for(int i=0; i<(n); ++i)

#define exc_flags std::ios::failbit | std::ios::badbit

std::string safe(const std::string &s)
{
	std::string res; REP(i,s.size()) switch(s[i])
	{ case'~':case'#':case'$':case'%':case'^':case'&':case'_':case'\\':case'{':case'}': res+='\\'; default: res+=s[i]; }
	return res;
}

std::ostream & operator<<(std::ostream &os, NamedStubQuestion &nq)
{
	os << "\\noindent\n\\begin{tabular}{p{2cm}p{12cm}}\n\\bfseries{" << safe(nq.questionName_)
		<< "} & \\bfseries{" << safe(nq.questionText_) << "}\\\\\n& \\begin{tabular}{|p{8cm}|p{2cm}|}\n""\\hline\n";
	std::vector<stub_pair> &vsp = nq.nr_ptr->stubs;
	REP(i,vsp.size()){ os << safe(vsp[i].stub_text) << " & " << vsp[i].code << " \\\\\n"; }
	os << "\\hline\n\\end{tabular}\\\\\n\\end{tabular}\\\\\n";
	return os;
}

void visit(std::ostream &os, AbstractStatement *stmt)
{
	if(!stmt) return;
	if(AbstractQuestion *q = dynamic_cast<AbstractQuestion*>(stmt))
	{
		if(RangeQuestion *rq = dynamic_cast<RangeQuestion*>(q))
		{
			
		}	
		else if(NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion*>(q)) os << *nq;
		else if(DummyArrayQuestion *dq = dynamic_cast<DummyArrayQuestion*>(q))
			throw std::string("parse: DummyArrayQuestion not handled yet");
		else throw std::string("parse: unknown question type");
	}
	else if(CompoundStatement *cs = dynamic_cast<CompoundStatement*>(stmt)) visit(os,cs->compoundBody_);
	else if(ForStatement *fs = dynamic_cast<ForStatement*>(stmt)) visit(os,fs->forBody_);
	else if(FunctionStatement *fs = dynamic_cast<FunctionStatement*>(stmt)) visit(os,fs->functionBody_);
	else if(IfStatement *is = dynamic_cast<IfStatement*>(stmt)){ visit(os,is->ifBody_); visit(os,is->elseBody_); }
	visit(os,stmt->next_);
}

const char *tex_begin = "\\documentclass[12pt]{article}\n\\begin{document}\n";
const char *tex_end = "\\end{document}\n";

void tex_document(std::ostream &os, const std::string &source_file)
{
	FILE *f = fopen(source_file.c_str(),"r"); if(!f) throw "parse: cannot open file \""+source_file+"\""; 
	InitStatement(); qscript_parser::active_scope_list.push_back(new Scope()); yyrestart(f);
	if(yyparse() || qscript_parser::no_errors) throw std::string("parse: errors while yyparse()");
	fclose(f);
	os << tex_begin; visit(os,qscript_parser::tree_root); os << tex_end;
}

int main(int argc, char **argv)
{
	if(argc<3){ std::cout << "usage: " << argv[0] << " input_script_file output_TeX_file\n"; exit(EXIT_FAILURE); }
	try { std::ofstream of; of.exceptions(exc_flags); of.open(argv[2]); tex_document(of,argv[1]); }
	catch(const std::ios::failure &e){ std::cout << "IO error: " << e.what() << "\n"; }
	catch(const std::string &s){ std::cout << "error: " << s; }
	
	return 0;
}

