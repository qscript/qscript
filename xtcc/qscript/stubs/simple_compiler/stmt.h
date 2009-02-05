#ifndef stmt_h
#define stmt_h
#include "xtcc_set.h"
#include "symtab.h"
//#include "common.h"
#include <string>
#include <sstream>
using std::string;
struct stmt {
	struct stmt * prev, *next;
	datatype type;
	int line_no;
	stmt(datatype l_type, int l_line_no): prev(0), next(0), line_no(l_line_no), type(l_type) 
	{}
	//virtual void eval()=0;
	//virtual void generate_code(FILE * script)=0;
	virtual void generate_code(ostringstream& quest_defns, ostringstream& program_code)=0;
	virtual ~stmt();
};


struct q_stmt: public stmt {
	string name;
	string text;
	question_type q_type;
	int no_mpn;
	datatype dt;
	xtcc_set * r_data;
	set<int> input_data;
	q_stmt(datatype l_type,int l_no, string l_name, string l_text, question_type l_q_type, int l_no_mpn, 
		datatype l_dt, xtcc_set& l_r_data);
	//void eval();
	//void generate_code(FILE* script);
	void generate_code(ostringstream & quest_defns, ostringstream& program_code);
	void print_q_type(string &s);
	void print_data_type(string &s);
};


struct expr_stmt: public stmt{
	struct expr* expr;
	expr_stmt(datatype l_type, int l_line_number, struct expr* e): stmt(l_type, l_line_number), expr(e) {}
	void generate_code(ostringstream & quest_defns, ostringstream& program_code);
	virtual ~expr_stmt();
	private:
	expr_stmt& operator=(const expr_stmt&);	
	expr_stmt(const expr_stmt&);	
};


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


#endif /* stmt_h */
