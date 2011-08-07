#ifndef CODE_OUTPUT_FILES_H
#define CODE_OUTPUT_FILES_H

#include <cstdio>
//#include <cstdlib>
struct CodeOutputFiles
{
	FILE * editCodeFile_;
	FILE * axisCodeFile_;
	FILE * tableCodeFile_;
	FILE * globalVarsFile_;
	CodeOutputFiles(): 
		editCodeFile_(0),
		axisCodeFile_(0),
		tableCodeFile_(0),
		globalVarsFile_(0)
	{ }
	void SetEditCodeFile(FILE * p_editCodeFile)
	{ editCodeFile_ = p_editCodeFile; }
	void SetAxisCodeFile(FILE * p_axisCodeFile)
	{ axisCodeFile_ = p_axisCodeFile; }
	void SetTableCodeFile(FILE * p_tableCodeFile)
	{ tableCodeFile_ = p_tableCodeFile; }
	void SetGlobalVarsFile(FILE * p_globalVarsFile)
	{ globalVarsFile_ = p_globalVarsFile; }
};

#endif /* CODE_OUTPUT_FILES_H */
