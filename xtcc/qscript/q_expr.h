#ifndef xtcc_q_expr_h
#define xtcc_q_expr_h

#include "../xtcc/trunk/expr.h" 
#include "range_set.h"
struct q_expr: public expr {
	struct symtab_ent * symp;
	expr * index_expr;

	range_data r_data;
	q_expr(string name, range_data& l_r_data, e_operator_type le_type): 
		expr(le_type)
	{
		r_data = l_r_data;
	}
	q_expr(string name, expr* arr_index, range_data& l_r_data, e_operator_type le_type):
		expr(le_type)
	{
		r_data = l_r_data;
	}
	bool is_lvalue(){
		return false;
	}
	void print_expr(FILE* edit_out){
		cout << "q_expr print_expr not yet implemented"<< endl;
	}


};

#endif /* xtcc_q_expr_h */
