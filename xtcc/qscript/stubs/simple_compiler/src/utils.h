/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/utils.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#ifndef xtcc_utils_h
#define xtcc_utils_h

#include <sys/types.h>
#include <map>
#include <string>
#include "symtab.h"
using std::map;
using std::string;

struct FunctionParameter;
enum compiler_err_category
{	compiler_syntax_err
	, compiler_sem_err
	, compiler_internal_error
	, compiler_code_generation_error
};

enum compiler_warning_category
{
	better_coding_style
};

void print_err(compiler_err_category cmp_err
		, string err_msg
		, int32_t line_no
		, int32_t compiler_line_no
		, string compiler_file_name);

void print_warning (compiler_warning_category cmp_err
		, string err_msg
		, int32_t line_no
		, int32_t compiler_line_no
		, string compiler_file_name);
map<string, SymbolTableEntry*>::iterator find_in_symtab(string id);
int32_t search_for_func(string& search_for);
DataType arr_deref_type(DataType d1);
bool is_of_int_type(DataType dt);
int32_t check_func_decl_with_func_defn(FunctionParameter* & v_list
		, int32_t & index, string func_name);
bool 	void_check( DataType & type1, DataType & type2, DataType& result_type);
DataType lcm_type(DataType d1, DataType d2);
int32_t check_parameters(AbstractExpression* e, FunctionParameter* v);
bool skip_func_type_check(const char * fname);
bool check_type_compat(DataType typ1, DataType typ2);
int32_t lookup_func(string func_name_index);
unsigned long djb_hash(const char *str);
unsigned long sdbm_hash(const char *str);
void log_maintainer_message(int line, string file, string func_name, string mesg);
#define LOG_MAINTAINER_MESSAGE(mesg)	log_maintainer_message(__LINE__, __FILE__, __PRETTY_FUNCTION__, mesg)
struct RatingScaleInfo
{
	bool isRatingScale_;
	bool isReversed_;
	int ratingScaleStart_;
	int ratingScaleEnd_;
	RatingScaleInfo ()
		: isRatingScale_ (false), isReversed_(false),
		  ratingScaleStart_(0), ratingScaleEnd_(0)
	{ }

};

struct RatingScaleInfo extract_rating_scale (string s);

struct ExtractNumberInfo {
	bool gotANumber_;
	int numberValue_;
	ExtractNumberInfo()
		: gotANumber_ (false), numberValue_(0)
	{ }
};

struct ExtractNumberInfo extract_number (string s);


extern noun_list_type noun_list[];
#endif // xtcc_utils_h
