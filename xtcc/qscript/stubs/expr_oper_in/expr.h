#ifndef expr_h
#define expr_h

#include "symtab.h"
#include "range_set.h"
#include <sstream>
using std::ostringstream;

enum e_operator_type { oper_plus, oper_minus, oper_mult, oper_div, oper_and, oper_or, oper_lt, oper_gt,
		oper_le, oper_ge, oper_isneq, oper_iseq, oper_parexp, oper_umin, oper_num,  oper_name, oper_arrderef,
		oper_arr2deref, oper_func_call, oper_text_expr, oper_float, oper_assgn , oper_not, oper_mod,
		oper_blk_arr_assgn, oper_in, oper_q_expr_in, oper_q_expr_arr_in,
		oper_err
	};

struct expr {
	e_operator_type e_type;
	datatype type;
	struct expr * next, *prev;
	expr(e_operator_type le_type):e_type(le_type), type(ERROR_TYPE), next(0), prev(0) { }
	expr(e_operator_type le_type, datatype ldt):e_type(le_type), type(ldt), next(0), prev(0) 
	{}
	virtual void print_expr(/*FILE * edit_out*/ ostringstream& code_bef_expr, ostringstream & code_expr)=0;
	virtual int isvalid();
	virtual bool is_lvalue()=0;
	virtual ~expr();
};


struct bin2_expr: public expr{
	protected:
	string name;
	symtab_ent *l_symp, *r_symp;
	range_data* r_data;
	public:
	//bin2_expr(string lname , string rname, e_operator_type letype);
	bin2_expr(string lname , range_data&  l_rd ,e_operator_type letype);
	bool is_lvalue(){ return false; }
	//void print_oper_assgn(FILE * edit_out);
	void print_expr(/*FILE * edit_out*/ ostringstream& code_bef_expr, ostringstream & code_expr);
	~bin2_expr();
};

struct bin_expr: public expr{
	protected:
	expr *l_op, *r_op;
	public:
	bin_expr(expr* llop, expr* lrop,e_operator_type letype);
	bool is_lvalue(){ return false; }
	void print_oper_assgn(FILE * edit_out);
	void print_expr(/*FILE * edit_out*/ ostringstream& code_bef_expr, ostringstream & code_expr);
	~bin_expr();
};


#endif /* expr_h */
