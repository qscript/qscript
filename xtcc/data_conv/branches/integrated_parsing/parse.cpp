//Grzegorz Prusak
#include "RecordMap.h"
#include "Type.h"

#include <cstdio>
#include "include/qscript_parser.h"
void yyrestart(FILE *);
int yyparse();
void InitStatement();

AbstractType * get_type(DataType dt)
{
	//printf("parse.cpp :: get_type(dt=%d)\n",dt);
	switch(dt)
	{
		case INT8_TYPE  : return &INT8  ; case INT16_TYPE : return &INT16;
		case INT32_TYPE : return &INT32 ; case FLOAT_TYPE : return &FLOAT;
		case DOUBLE_TYPE: return &DOUBLE; default: throw std::string("parse: unrecognized type enum");
	}
}

void visit(RecordMap &rm, AbstractStatement *stmt)
{
	if(!stmt) return;
	if(AbstractQuestion *q = dynamic_cast<AbstractQuestion*>(stmt))
	{
		//printf("parse.cpp :: visit() :: q->questionName_ == %s; q->dt == %d\n",q->questionName_.c_str(),q->dt);
		
		//os << question[i]->questionName_ << ' ' << text(question[i]->dt);
		//if(question[i]->q_type==mpn) os << ' ' << question[i]->no_mpn; else os << " 1";
		
		if(RangeQuestion *rq = dynamic_cast<RangeQuestion*>(q))
			rm.add_field(rq->questionName_,get_type(rq->dt),"");
		else if(NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion*>(q))
			rm.add_field(nq->questionName_,get_type(nq->dt),nq->nr_ptr->name);
		else if(DummyArrayQuestion *dq = dynamic_cast<DummyArrayQuestion*>(q))
			throw std::string("parse: DummyArrayQuestion not handled yet");
		else throw std::string("parse: unknown question type");
	}
	else if(named_range *nr = dynamic_cast<named_range*>(stmt))
	{
		std::stringstream ss; 
		REP(j,nr->stubs.size()) ss << ' ' << nr->stubs[j].code << " \"" << nr->stubs[j].stub_text << '\"';
		rm.stubinfo += nr->name + " =" + ss.str() + '\n';
	}
	else if(CompoundStatement *cs = dynamic_cast<CompoundStatement*>(stmt)) visit(rm,cs->compoundBody_);
	else if(ForStatement *fs = dynamic_cast<ForStatement*>(stmt)) visit(rm,fs->forBody_);
	else if(FunctionStatement *fs = dynamic_cast<FunctionStatement*>(stmt)) visit(rm,fs->functionBody_);
	else if(IfStatement *is = dynamic_cast<IfStatement*>(stmt)){ visit(rm,is->ifBody_); visit(rm,is->elseBody_); }
	visit(rm,stmt->next_);
}

//#include <cstdlib>

RecordMap::RecordMap(AbstractFormat &F, const std::string &source_file) : format(F)
{
	FILE *f = fopen(source_file.c_str(),"r"); if(!f) throw "parse: cannot open file \""+source_file+"\""; 
	InitStatement(); qscript_parser::active_scope_list.push_back(new Scope()); yyrestart(f);
	if(yyparse() || qscript_parser::no_errors) throw std::string("parse: errors while yyparse()");
	fclose(f); visit(*this,qscript_parser::tree_root);
	//exit(1); //parse test only
}

