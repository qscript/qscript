/*
 *  AbstractStatement.h
 *  Copyright (C) 2011 Neil Xavier D'Souza
 */

#ifndef QSCRIPT_ABSTRACT_STATEMENT_H
#define QSCRIPT_ABSTRACT_STATEMENT_H

#include <sys/types.h>
#include <vector>
#include <string>
#include "datatype.h"
#include "compiled_code.h"

struct AbstractQuestion;

//!AbstractStatement  Pure virtual base class - all statement classes inherit from this class except for class FunctionInformation
/*!
  All language statements classes are derived from the AbstractStatement class
  the AbstractStatement class - contains members (
  AbstractStatement * prev_, *next_ pointers to chain other statements).
  It also contains line and filename information
  about the statement being parsed
*/
struct AbstractStatement
{
	//! chainers to the previous and next_ statement
	struct AbstractStatement * prev_, *next_;
	//! statement type
	DataType type_;
	int32_t lineNo_;
	int32_t nestLevel_;
	int32_t forNestLevel_;
	//! Constructor - statement type and line number of the statement in the source code
	AbstractStatement(DataType l_type, int32_t l_line_no, 
			  int32_t l_nest_level, int32_t l_for_nest_level)
	: prev_(0), next_(0), type_(l_type), 
	  lineNo_(l_line_no), nestLevel_(l_nest_level), forNestLevel_(l_for_nest_level)
	{ }
	//! GenerateConsolidatedForLoopIndexes() - has to be called before GenerateCode
	//! sets up the loop indices in various compound bodies for later use
	//! by GenerateCode
	virtual void GenerateConsolidatedForLoopIndexes();
	//! GenerateCode(): Pure virtual functions takes 2 streams as parameters.
	//! Compiler generated code is written to both the streams.
	//! The code to the quest_defns stream appears before code written to
	//! the program_code stream in the generated compiled code
	//virtual void GenerateCode(ostringstream& quest_defns
	//		, ostringstream& program_code)=0;
	virtual void GenerateCode(StatementCompiledCode & code)=0;
	virtual ~AbstractStatement();
	//virtual AbstractQuestion* IsAQuestionStatement();
	virtual void GetQuestionNames(std::vector<std::string> & question_list,
				      AbstractStatement * endStatement);
	virtual void GetQuestionsInBlock(std::vector<AbstractQuestion*> & question_list
					 , AbstractStatement * stop_at);
	virtual void Generate_ComputeFlatFileMap(StatementCompiledCode & code);
	virtual std::string PrintIdentity ();
	private:
		AbstractStatement& operator=(const AbstractStatement&);
		AbstractStatement (const AbstractStatement&);
};

#endif /* QSCRIPT_ABSTRACT_STATEMENT_H */
