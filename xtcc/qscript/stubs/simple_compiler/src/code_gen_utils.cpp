#include <sstream>
#include "qscript_parser.h"

using std::stringstream;
#include "code_gen_utils.h"

void PrintTemporaryXtccSet(ExpressionCompiledCode &code, XtccSet *  xs)
{
	stringstream temp_code;
	string set_name = qscript_parser::temp_set_name_generator.GetNewName();
	temp_code << "XtccSet " << set_name << ";\n";

	//fprintf(stderr, "Binary2Expression::PrintExpressionCode(): printed constructor");
	for(int32_t i = 0; i< xs->range.size() ; ++i){
		temp_code << set_name << ".add_range("
			<< xs->range[i].first
			<< ", " << xs->range[i].second << ");\n";
	}

	{
		int32_t k = 0;
		for(set<int32_t>::iterator iter = xs->indiv.begin();
			iter != xs->indiv.end(); ++iter, ++k){
			temp_code << set_name << ".add_indiv(" 
				 << *iter << ");\n";
		}
	}
	code.code_bef_expr << temp_code.str();

}
