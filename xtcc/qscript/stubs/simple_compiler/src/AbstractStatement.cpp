#include "AbstractStatement.h"
#include "qscript_parser.h"

using std::vector;
using std::string;

void AbstractStatement::GetQuestionNames(vector<string> &question_list,
					 AbstractStatement * endStatement)
{
	if (this == endStatement)
		return;
	if (next_){
		next_->GetQuestionNames(question_list, endStatement);
	}
}


void AbstractStatement::GetQuestionsInBlock(vector<AbstractQuestion*> & question_list,
					    AbstractStatement * stop_at)
{
	//cerr << "ENTER AbstractStatement::GetQuestionsInBlock: ";
	//cerr << human_readable_type(type_) << endl;
	if (next_ && next_ != stop_at){
		next_->GetQuestionsInBlock(question_list, stop_at);
	}
	//cerr << "Exit AbstractStatement::GetQuestionsInBlock\n";
}


void AbstractStatement::GenerateConsolidatedForLoopIndexes()
{
	//cout << "ENTER AbstractStatement::GenerateConsolidatedForLoopIndexes:" << endl;
	if (next_) {
		next_->GenerateConsolidatedForLoopIndexes();
	}
	//cout << "EXIT AbstractStatement::GenerateConsolidatedForLoopIndexes:" << endl;
}


void AbstractStatement::Generate_ComputeFlatFileMap(StatementCompiledCode & code)
{
	if (next_) {
		next_->Generate_ComputeFlatFileMap(code);
	}
}



AbstractStatement::~AbstractStatement()
{
	using qscript_parser::debug_log_file;
	//std::cerr << "AbstractStatement::~AbstractStatement()\n" << std::endl;
	if (next_  ) {
		delete next_; next_ = 0;
	}
	//debug_log_file << "AbstractStatement::~AbstractStatement() base destructor" << endl;
}

std::string AbstractStatement::PrintIdentity ()
{
	std::stringstream s;
	s << __PRETTY_FUNCTION__ << std::endl;
	return s.str();
}
