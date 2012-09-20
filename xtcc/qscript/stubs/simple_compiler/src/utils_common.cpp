#include <string>
#include <sstream>
#include <iostream>
#include "utils.h"
#include "qscript_parser_common.h"

using std::cerr;
using std::string;
using std::endl;
using std::stringstream;
using qscript_parser::no_errors;

void print_warning(compiler_warning_category cmp_warn, string err_msg,
	int32_t line_no, int32_t compiler_line_no, string compiler_file_name)
{
	++qscript_parser::no_warnings;
	cerr << "xtcc ";
	switch (cmp_warn) {
	case better_coding_style:
		cerr << "better coding style: ";
		break;

	default:
		cerr << "internal compiler error - warning code category missing in switch statement: compiler file: "
		     << __PRETTY_FUNCTION__ << ", "
		     << __FILE__ << " compiler src code lineno: " << __LINE__ << endl
		     ;
	}
	cerr << " line_no: " << line_no << " "<< err_msg << ", compiler line_no: "
		<< compiler_line_no << ", compiler_file_name: " << compiler_file_name << endl;
}

void print_err(compiler_err_category cmp_err, string err_msg,
	int32_t line_no, int32_t compiler_line_no, string compiler_file_name)
{
	++no_errors;
	cerr << "xtcc ";
	switch(cmp_err){
	case compiler_syntax_err:
		cerr << "syntax error: ";
		break;
	case compiler_sem_err:
		cerr << "semantic error: ";
		break;
	case compiler_internal_error:
		cerr << "compiler internal error: ";
		break;
	case compiler_code_generation_error:
		cerr << "compiler code generation error: ";
		break;
	default:
		cerr << "internal compiler error - error code category missing in switch statement: compiler file: "
		     << __FILE__ << " compiler src code lineno: " << __LINE__ << endl;
	}
	cerr << " line_no: " << line_no << " "<< err_msg << ", compiler line_no: "
		<< compiler_line_no << ", compiler_file_name: " << compiler_file_name << endl;
}

/* for those who are reading the source and want to understand the logic
 * the maintainer messages are cluttering up the stdout of the compiler.
 * Im storing them in a map so they will appear only once - less clutter
 * I initially thought of using and sha1 has func but i think that is an overkill
 * and will require an end user to install a crypt library just for maintainer messages.
 * A quick google gave me some web pages and this web page i trust - just blindly
 * Im using 2 hashes - just in case 2 strings hash to the same code. There is still a finite
 * probability that they could be the same for both functions but I think the chance is 
 * much smaller - im willing to risk it */

void log_maintainer_message(int line, string file, string func_name, string mesg)
{
	std::stringstream s;
	s 	<< "line: " << line 
		<< ", file: " << file 
		<< ", func: " << func_name << mesg;
	int sdbm_hash_code = sdbm_hash(s.str().c_str());
	int djb_hash_code = djb_hash(s.str().c_str());
	std::pair<int,int> hashed_pair(sdbm_hash_code, djb_hash_code);
	using qscript_parser::maintainer_messages;
	if (maintainer_messages.find(hashed_pair)==maintainer_messages.end()) {
		maintainer_messages[hashed_pair] = s.str();
	}
}


// http://www.cse.yorku.ca/~oz/hash.html
// hash algo copied from here
unsigned long sdbm_hash(const char *str)
{
	unsigned long hash = 0;
	int c;
	while ((c = *str++))
	    hash = c + (hash << 6) + (hash << 16) - hash;
	return hash;
}

// http://www.cse.yorku.ca/~oz/hash.html
// hash algo copied from here
unsigned long djb_hash(const char *str)
{
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
	    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return hash;
}
