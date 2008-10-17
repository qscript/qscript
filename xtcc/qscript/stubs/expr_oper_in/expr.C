#include "expr.h"


int expr::isvalid(){
	//cout << "isvalid called" << endl;
	if (type==ERROR_TYPE){
		return 0;
	} else return 1;
}

bin2_expr::bin2_expr( string lname , range_data&  l_rd ,e_operator_type letype): expr(letype),
	name(lname)
{
	r_data = new range_data(l_rd);	
}


expr::~expr(){}

bin2_expr::~bin2_expr(){
	delete r_data;
}

void bin2_expr::print_expr(FILE* fptr){
}

