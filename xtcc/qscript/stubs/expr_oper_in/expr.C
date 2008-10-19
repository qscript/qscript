#include "expr.h"

bin_expr::bin_expr(expr* llop, expr* lrop,e_operator_type letype):expr(letype),
	l_op(llop), r_op(lrop)
{
}

void bin_expr::print_expr(FILE * edit_out){
	switch(e_type){
		case oper_and:	
		l_op->print_expr(edit_out);
		fprintf(edit_out, " && ");
		r_op->print_expr(edit_out);
		break;
		default:
			fprintf(edit_out, " invalid e_type in print_expr\n");

	}
}

void bin_expr::print_oper_assgn(FILE * edit_out){
}

bin_expr::~bin_expr(){
}

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

string get_temp_name();
void bin2_expr::print_expr(FILE* fptr){
	//fprintf(fptr, "bin2_expr::print_expr()");
	string struct_name = get_temp_name();
	fprintf(fptr, "\tstruct %s{\n", struct_name.c_str());
	fprintf(fptr, "\t\tconst int size_ran_indiv;\n");
	fprintf(fptr, "\t\tconst int size_start_end;\n");
	fprintf(fptr, "\t\tvector<int> ran_indiv;\n");
	fprintf(fptr, "\t\tvector< pair<int,int> > ran_start_end;\n");
	fprintf(fptr, "\t\t%s (): size_ran_indiv(%d), size_start_end(%d),\n", struct_name.c_str(),
		r_data->icount, r_data->rcount);
	fprintf(fptr, "\t\t\tran_indiv(size_ran_indiv), ran_start_end(size_start_end){\n");
	for(int i=0; i< r_data->rcount; ++i){
		fprintf(fptr, "\t\t\tran_start_end[%d]=pair<int,int>(%d, %d);\n", i,
			r_data->ran_start_end[i*2], r_data->ran_start_end[i*2+1]);
	}
	for(int i=0; i< r_data->icount; ++i){
		fprintf(fptr, "\t\t\tran_indiv[%d]=%d;\n", i, r_data->ran_indiv[i]);
	}
	fprintf(fptr, "\t\t}\n");

	fprintf(fptr, "\t\tbool exists(int key){\n");
	fprintf(fptr, "\t\t\tfor(int i=0; i<size_start_end; ++i){\n");
	fprintf(fptr, "\t\t\t\tif(key >=ran_start_end[i].first && key <=ran_start_end[i].second){\n");
	fprintf(fptr, "\t\t\t\t\treturn true;\n");
	fprintf(fptr, "\t\t\t\t}\n");
	fprintf(fptr, "\t\t\t}\n");
	fprintf(fptr, "\t\t\tfor(int i=0; i< size_ran_indiv; ++i){\n");
	fprintf(fptr, "\t\t\t\tif(key==ran_indiv[i]){\n");
	fprintf(fptr, "\t\t\t\t\treturn true;\n");
	fprintf(fptr, "\t\t\t\t}\n");
	fprintf(fptr, "\t\t\t}\n");
	fprintf(fptr, "\t\t\treturn false;\n");
	fprintf(fptr, "\t\t}\n");

	string struct_name1 = get_temp_name();
	fprintf(fptr, "\t} %s;\n", struct_name1.c_str());
	string test_bool_var_name=get_temp_name();
	fprintf(fptr, "bool %s = %s.exists(%s);\n", 
			test_bool_var_name.c_str(), struct_name1.c_str(), name.c_str());
}

