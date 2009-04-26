/*! \file
    \brief The classes for the statements parsed in the input 
            language are contained in this file
 *  xtcc/xtcc/qscript/stubs/simple_compiler/stmt.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#ifndef stmt_h
#define stmt_h
#include "xtcc_set.h"
#include "symtab.h"
//#include "common.h"
#include <string>
#include <sstream>
#include "stub_pair.h"
using std::string;

//!stmt  Pure virtual base class - all statement classes inherit from this class except for class func_info
/*!
  All language statements classes are derived from the stmt class
  the stmt class - contains members (stmt * prev, *next pointers to chain
  to other statements. It also contains line and filename information 
  about the statement being parsed
*/

struct stmt {
	//! chainers to the previous and next statement
	struct stmt * prev, *next;
	//! statement type
	datatype type;
	int line_no;
	//! Constructor - statement type and line number of the statement in the source code
	stmt(datatype l_type, int l_line_no): prev(0), next(0), line_no(l_line_no), type(l_type) 
	{}
	//! generate_code(): Pure virtual functions takes 2 streams which as parameters
	//! code is written to both the streams 
	//! the code in the quest_defns stream appears before the code in 
	//! the program_code stream
	virtual void generate_code(ostringstream& quest_defns, ostringstream& program_code)=0;
	virtual ~stmt();
	private:
		stmt& operator=(const stmt&);
		stmt (const stmt&);
};

//#include "named_range.h"

struct named_range;
#include "question.h"


//!expr_stmt Parsed expressions statements become object instanstiations of this class
/*!
  an example of an expression statement is the assignment statement below: 
  	a=5*10;
  This class contains and expr* pure virutal base class pointer as a member. 
  The expr* expr generates its own
  code through the print_expr(ostringstream& code_bef_expr, ostringstream& code_expr)
  pure virtual function - which is over-ridden in each of the expression classes
*/
struct expr_stmt: public stmt{
	struct expr* expr;
	expr_stmt(datatype l_type, int l_line_number, struct expr* e): stmt(l_type, l_line_number), expr(e) {}
	void generate_code(ostringstream & quest_defns, ostringstream& program_code);
	virtual ~expr_stmt();
	private:
	expr_stmt& operator=(const expr_stmt&);	
	expr_stmt(const expr_stmt&);	
};


//!func_info : parsed function declarations and definitions become object instanstiations of this class
/*!
  Important notes for the func_info class:

  <p>
  When a function declaration is parsed all the variables
  which are function parameters become should available in the scope of this 
  function. 

  On the other hand the function body (which is a compound statement)
  will appear at a later stage, i.e. the declaration of the function. 

  The implementation of compound statements is that each compound statement contains
  a scope variable of its own. Hence to bring the function parameter 
  declarations into the scope of the compound statement the following is done:

  <p>1. func_info has a scope called func_scope - this scope is allocated 
     at the time of declaration of the function. This declaration is then
     stored in the func_info_table vector array
  <p>2. The grammar has a inline rule when detecting a function
  	definition - it sets the variable : flag_cmpd_stmt_is_a_for_body
	to the index of the function in the func_info_table vector array
	or -1 on failure. This grammar rule can be seen 
	by searching for the pattern ^func_info in the "type.y" grammar
	file in the xtcc compiler sources. The simple compiler in qscript
	does not use functions as yet
  <p>3. When a compound body is being parsed (the ^open_curly rule in
  	type.y in the xtcc compiler - it checks if flag_cmpd_stmt_is_a_func_body
	has been set and if so loads the scope from the function declaration
	found in the  func_info_table array - by using the variable 
	flag_cmpd_stmt_is_a_func_body - to index into the func_info_table
  
*/

struct func_info{
	string fname;
	struct var_list * param_list;
	datatype return_type;
	struct stmt * func_body;
	struct scope * func_scope;
	func_info(string name, struct var_list* elist, datatype myreturn_type); 
	void print(FILE * fptr);
	~func_info();
private:
	func_info& operator=(const func_info&);
	func_info(const func_info&);
};

//! decl_stmt  parsed variable declarations become object instanstiations of this class
struct decl_stmt: public stmt{
	struct symtab_ent* symp;
	decl_stmt( datatype dtype, int lline_number):stmt(dtype, lline_number), symp(0) {}
	~decl_stmt();
	void generate_code(ostringstream & quest_defns, ostringstream& program_code);
	private:
	decl_stmt& operator=(const decl_stmt&);	
	decl_stmt(const decl_stmt&);	
};

//! cmpd_stmt parsed compound statements become object instanstiations of this class
/*!
  important notes for this class(cmpd_stmt):
  <p>1. function definitions have a compound statement as the body
     of the class. The compound scope is not allocated in the 
     constructor of the cmpd_stmt initialiser list because 
     we need to determine if this statement is a part
     of a function definition or a normal compound statement.
     If the cmpd_stmt is a part of a func_defn it will get its scope 
     from the declaration of the function which is stored in the
     func_info_table vector array. Otherwise the constructer will
     allocate a scope for the variable
  <p>2. The other case for a compound statement is when it is the body of 
     a for loop. There are certain restrictions on the language because
     the questionnaire is stored on disk. Consider the following .
       
        We need to create a map file of the questionnaire. 
        This means that the map file has to be fixed for each and every single
	questionnaire. Hence if a "for" loop contains questions in the body
	we cannot have a variable number of questions being asked to the respondent.

	for example below is not allowed:
	int v1=v2*v3;
	for(int i=0; i<v1; i++){
		q1 ask "q1" ...
		q2 ask "q2" ...
	}
	This would not allow us to create a fixed map file for the location
	of data on the disk

	on the other hand the following is allowed
	const int n_iters=10;
	for(int i=0; i<n_iters*5; ++i){
		q1 ask "q1" ...
		q2 ask "q2" ...
	}
	as this => that the loop will run 50 times and so
	q1, q2 are arrays of size 50.

	Hence the compound_stmt needs to determine if it contains questions
	and if so set a flag. Then when parsing a for statement - and note that
	a for statement has been forced by the grammar to have only a cmpd_stmt 
	as the body - we check if the cmpd_stmt has questions and run additional
	checks on the test index of the for loop to ensure it is an integral value
	(i.e. countable and determinable)



	When parsing a compound statement the parser it will push the 
	cmpd_stmt_ptr object onto the stack named stack_cmpd_stmt. This is 
	done in the ^open_curly rule in q.y 
	Everytime the parser encounters a question in the body of the cmpd_stmt
	it will increment the counter "counter_contains_questions" cmpd_stmt
	member variable by 1. You can see this happening in the ^question rule
	in q.y 
	This way we can determine if the compound body has a question. Once this has
	been determined we put addition restrictions on the loop index of the for
	statement

*/	

struct cmpd_stmt: public stmt{
	//! pointer to the first chain of statements
	//! in the cmpd_stmt 
	struct stmt* cmpd_bdy;
	//! The scope for the cmpd_stmt will contain all
	//! the variables declared in the body of the 
	//! cmpd_stmt. This variable is set in 2 ways.
	//! 1. If it is the body of a func_defn then
	//     it is assigned to the scope variable in the function
	//     declaration
	//  2. Otherwise a new scope object is allocated
	struct scope * sc;
	//! this flag variable is set in the grammar type.y
	//! in the xtcc compiler sources and not used in 
	//! the qscript compiler as yet.
	//! The rule used to set the variable is ^func_defn
	//! The variable is used in the ^open_curly rule when deciding
	//! if a scope is to be allocated or pulled from the function 
	//! declaration
	int flag_cmpd_stmt_is_a_func_body;
	//! this flag variable is set in the ^for_loop_stmt in 
	//! q.y in an inline action in the grammar
	int flag_cmpd_stmt_is_a_for_body;

	//! this counter variable is set in the ^question rule in 
	//! q.y in an inline action in the grammar
	int counter_contains_questions;
	public:
	cmpd_stmt(datatype dtype, int lline_number
		, int l_flag_cmpd_stmt_is_a_func_body
		, int l_flag_cmpd_stmt_is_a_for_body);
	void generate_code(ostringstream & quest_defns, ostringstream& program_code);
	virtual ~cmpd_stmt();
	private:
	cmpd_stmt& operator=(const cmpd_stmt&);	
	cmpd_stmt(const cmpd_stmt&);	
};

//! for_stmt: A parsed for statement in the language becomes an object instanstiation of this class
/*! Refer to point 2. in the documentation for cmpd_stmt about for loop index
    restrictions when you have a question statement in the body 
    of a for statement
 */
struct for_stmt: public stmt{
	struct expr * init, * test, *incr;
	struct cmpd_stmt * for_body;
	for_stmt(datatype dtype, int lline_number, expr* l_init, expr* l_test, 
			expr* l_incr, cmpd_stmt * lfor_body);
	void generate_code(ostringstream & quest_defns, ostringstream& program_code);
	virtual ~for_stmt();
	private:
	for_stmt& operator=(const for_stmt&);	
	for_stmt(const for_stmt&);	
};

//! if_stmt if statements in the language become object instantiations of this class
struct if_stmt : public stmt{
	protected:
	struct expr * condition;
	struct stmt * if_body;
	struct stmt * else_body;
	public:
	if_stmt( datatype dtype, int lline_number, 
		struct  expr * lcondition, struct  stmt * lif_body, struct stmt * lelse_body=0);
	void generate_code(ostringstream & quest_defns, ostringstream& program_code);
	virtual ~if_stmt();
	private:
	if_stmt& operator=(const if_stmt&);	
	if_stmt(const if_stmt&);	
};


#endif /* stmt_h */
