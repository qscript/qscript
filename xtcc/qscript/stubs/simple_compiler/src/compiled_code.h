#ifndef qscript_compiled_code_h
#define qscript_compiled_code_h

#include <sstream>
struct StatementCompiledCode 
{
	std::ostringstream quest_defns, array_quest_init_area, program_code;
	StatementCompiledCode(): quest_defns(), array_quest_init_area(), program_code() {}

};

struct ExpressionCompiledCode 
{
	std::ostringstream code_bef_expr, code_expr;
	ExpressionCompiledCode(): code_bef_expr(), code_expr() {}
};

#endif /* qscript_compiled_code_h */
