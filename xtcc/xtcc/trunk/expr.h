#ifndef xtcc_expr_h
#define xtcc_expr_h
#include "tree.h"

enum e_operator_type { oper_plus, oper_minus, oper_mult, oper_div, oper_and, oper_or, oper_lt, oper_gt,
		oper_le, oper_ge, oper_isneq, oper_iseq, oper_parexp, oper_umin, oper_num,  oper_name, oper_arrderef,
		oper_arr2deref, oper_func_call, oper_text_expr, oper_float, oper_assgn , oper_not, oper_mod,
		oper_blk_arr_assgn,
		oper_err
	};

struct expr {
	e_operator_type e_type;
	datatype type;
	struct expr * next, *prev;
	expr(e_operator_type le_type):e_type(le_type), type(ERROR_TYPE), next(0), prev(0) { }
	expr(e_operator_type le_type, datatype ldt):e_type(le_type), type(ldt), next(0), prev(0) 
	{}
	virtual void print_expr(FILE * edit_out)=0;
	virtual int isvalid();
	virtual bool is_lvalue()=0;
	virtual ~expr();
};

extern int no_errors;
extern int line_no;

struct un_expr : public expr{
	protected:
	expr* operand;
	public:
	un_expr( expr * l_operand=0, e_operator_type le_type=oper_err);
	bool is_lvalue(){ return false; }
	void print_expr(FILE * edit_out);
	virtual ~un_expr();
};

//extern vector <func_info*> func_info_table;

struct bin_expr: public expr{
	protected:
	expr *l_op, *r_op;
	public:
	bin_expr(expr* llop, expr* lrop,e_operator_type letype);
	bool is_lvalue(){ return false; }
	void print_oper_assgn(FILE * edit_out);
	void print_expr(FILE * edit_out);
	~bin_expr();
};


struct un2_expr : public expr{
	protected:
	struct symtab_ent * symp;
	int isem_value;
	double dsem_value;
	int func_index_in_table;
	char * text;
	int column_no;
	expr* operand;
	expr* operand2;
	public:
	// This is a hack - I have to fix this by putting line number in the base class
	int line_no;
	bool is_lvalue();
	un2_expr(e_operator_type le_type, datatype ldt, expr* e_list, int lfunc_index_in_table, int lline_no);

	un2_expr(int l_isem_value);

	un2_expr(double l_dsem_value);

	un2_expr( struct symtab_ent * lsymp); 
	un2_expr(datatype d);
	un2_expr(e_operator_type le_type, /*datatype dt, struct symtab_ent * lsymp,*/ string name, expr* arr_index);
	un2_expr(e_operator_type le_type, /*datatype dt, struct symtab_ent * lsymp, */ string name,  expr* arr_index, expr* arr_index2);
	un2_expr(char* ltxt, e_operator_type le_type); 
	~un2_expr();
	friend void bin_expr::print_oper_assgn(FILE* edit_out);
	void print_expr(FILE * edit_out);
};



#endif /* xtcc_expr_h */
