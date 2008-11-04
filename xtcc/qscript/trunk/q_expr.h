#ifndef xtcc_q_expr_h
#define xtcc_q_expr_h

#include "../../xtcc/trunk/expr.h" 
#include "range_set.h"

struct q_expr: public expr {
	struct symtab_ent * symp;
	expr * index_expr;
	string name; //temp hack for now
	range_data r_data;
	q_expr(string l_name, range_data& l_r_data, e_operator_type le_type): 
		name(l_name), expr(le_type)
	{
		// type=BOOL_TYPE is another hack until we get the symbol table going and
		// then do real validation checks
		type=BOOL_TYPE;
		r_data = l_r_data;
	}
	q_expr(string l_name, expr* arr_index, range_data& l_r_data, e_operator_type le_type):
		name(l_name), index_expr(arr_index), expr(le_type)
	{
		type=BOOL_TYPE;
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
