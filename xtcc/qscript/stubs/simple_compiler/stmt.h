#ifndef stmt_h
#define stmt_h
#include "xtcc_set.h"
#include "symtab.h"
//#include "common.h"
#include <string>
#include <sstream>
#include "stub_pair.h"
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
	//virtual void eval()=0;
	virtual ~stmt();
};

//#include "named_range.h"
struct named_range;

struct question: public stmt {
	string name;
	string text;
	question_type q_type;
	int no_mpn;
	datatype dt;
	set<int> input_data;
	question(datatype l_type,int l_no, string l_name, string l_text,
		question_type l_q_type, int l_no_mpn, 
		datatype l_dt /*, xtcc_set& l_r_data*/);
	virtual void generate_code(ostringstream & quest_defns, ostringstream& program_code)=0;
	virtual void eval()=0;
	void print_q_type(string &s);
	void print_data_type(string &s);
};

struct range_question: public question {
	xtcc_set * r_data;
	range_question(datatype this_stmt_type, int line_number,
		string l_name, string l_q_text,
		question_type l_q_type, int l_no_mpn, datatype l_dt,
		xtcc_set& l_r_data);

	void generate_code(ostringstream & quest_defns, ostringstream& program_code);
	void eval();
};


class named_stub_question: public question {
	string named_list;
	named_range * nr_ptr;
	vector<stub_pair> * stub_ptr;
	public:
	named_stub_question(datatype this_stmt_type, int line_number, 
		string l_name, string l_q_text,
		question_type l_q_type, int l_no_mpn, datatype l_dt,
		named_range * l_nr_ptr);
	named_stub_question(datatype this_stmt_type, int line_number, 
		string l_name, string l_q_text,
		question_type l_q_type, int l_no_mpn, datatype l_dt,
		vector<stub_pair> * l_stub_ptr);
	//void print_stmt_lst(FILE * & fptr);
	void generate_code(ostringstream & quest_defns, ostringstream& program_code);
	void eval();
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

struct decl_stmt: public stmt{
	struct symtab_ent* symp;
	decl_stmt( datatype dtype, int lline_number):stmt(dtype, lline_number), symp(0) {}
#if 0
	void print_stmt_lst(FILE * & fptr){
		fflush(fptr);
		if(fptr){
			ostringstream code_expr1, code_bef_expr1;
			if( symp->e){
				symp->e->print_expr(code_bef_expr1, code_expr1);
				fprintf(fptr,"%s", code_bef_expr1.str().c_str());
			}
			if(type >= INT8_TYPE && type <=DOUBLE_TYPE){
				fprintf(fptr,"%s %s", noun_list[type].sym, symp->name);
			} else if (type >=INT8_ARR_TYPE && type <=DOUBLE_ARR_TYPE){
				datatype tdt=datatype(INT8_TYPE + type-INT8_ARR_TYPE);
				fprintf(fptr,"%s %s [ %d ]", noun_list[tdt].sym, symp->name, symp->n_elms);
			} else if (type >=INT8_REF_TYPE&& type <=DOUBLE_REF_TYPE){
				datatype tdt=datatype(INT8_TYPE + type-INT8_REF_TYPE);
				fprintf(fptr,"%s & %s", noun_list[tdt].sym, symp->name);
			}
			if( symp->e){
				fprintf(fptr,"=%s", code_expr1.str().c_str());
				//symp->e->print_expr(fptr);
			}
			fprintf(fptr, ";\n");
			if(next) next->print_stmt_lst(fptr);
		}
	}
#endif /* 0 */
	~decl_stmt();
	void generate_code(ostringstream & quest_defns, ostringstream& program_code);
	private:
	decl_stmt& operator=(const decl_stmt&);	
	decl_stmt(const decl_stmt&);	
};


#endif /* stmt_h */
