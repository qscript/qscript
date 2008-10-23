#include "expr.h"

bin_expr::bin_expr(expr* llop, expr* lrop,e_operator_type letype):expr(letype),
	l_op(llop), r_op(lrop)
{
}


void bin_expr::	print_expr(/*FILE * edit_out*/ ostringstream& code_bef_expr, ostringstream & code_expr){
	switch(e_type){
		case oper_and:	
		l_op->print_expr(code_bef_expr, code_expr);
		//fprintf(edit_out, " && ");
		code_expr << " && ";
		//r_op->print_expr(edit_out);
		r_op->print_expr(code_bef_expr, code_expr);
		break;
		default:
			//fprintf(edit_out, " invalid e_type in print_expr\n");
			code_expr <<  " invalid e_type in print_expr" << endl;
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

/*
bin2_expr::bin2_expr( string lname , range_data&  l_rd ,e_operator_type letype): expr(letype),
	name(lname)
{
	r_data = new range_data(l_rd);	
}
*/

bin2_expr::bin2_expr( string lname , xtcc_set&  l_xs ,e_operator_type letype): expr(letype),
	name(lname)
{
	xs=new xtcc_set(l_xs);
}



expr::~expr(){}

bin2_expr::~bin2_expr(){
	//delete r_data;
	delete xs;
}

string get_temp_name();
//void bin2_expr::print_expr(FILE* fptr)
void bin2_expr::	print_expr(/*FILE * edit_out*/ ostringstream& code_bef_expr, ostringstream & code_expr){
	//fprintf(fptr, "bin2_expr::print_expr()");
	string struct_name = get_temp_name();
	code_bef_expr << "\tstruct " <<  struct_name.c_str() << "{\n" ;
	code_bef_expr << "\t\tconst int size_ran_indiv;\n";
	code_bef_expr << "\t\tconst int size_start_end;\n";
	code_bef_expr << "\t\tvector<int> ran_indiv;\n";
	code_bef_expr << "\t\tvector< pair<int,int> > ran_start_end;\n";
	code_bef_expr << "\t\t" << struct_name.c_str() 
		<< "(): size_ran_indiv(" << xs->indiv.size() //r_data->icount 
		<< "), size_start_end(" <<  xs->range.size() //r_data->rcount << "),\n";
		<< "),\n";								       
	code_bef_expr << "\t\t\tran_indiv(size_ran_indiv), ran_start_end(size_start_end){\n";
	/*
	for(int i=0; i< r_data->rcount; ++i){
		code_bef_expr << "\t\t\tran_start_end[" << i 
			<< "]=pair<int,int>(" 
			<< r_data->ran_start_end[i*2] 
			<< "," << r_data->ran_start_end[i*2+1] << ");\n";
	}
	*/
	for(int i=0; i< xs->range.size() ; ++i){
		code_bef_expr << "\t\t\tran_start_end[" << i 
			<< "]=pair<int,int>(" 
			<< xs->range[i].first 
			<< "," << xs->range[i].second << ");\n";
	}
	/*
	for(int i=0; i< r_data->icount; ++i){
		code_bef_expr << "\t\t\tran_indiv[" 
			<< i << "]=" << r_data->ran_indiv[i] <<";\n";
	}*/
	
	int k=0;
	for(set<int>::iterator iter=xs->indiv.begin(); 
		iter!=xs->indiv.end(); ++iter, ++k){
		code_bef_expr << "\t\t\tran_indiv[" 
			<< k << "]=" << *iter <<";\n";
	}
	code_bef_expr <<  "\t\t}\n";

	code_bef_expr << "\t\tbool exists(int key){\n";
	code_bef_expr << "\t\t\tfor(int i=0; i<size_start_end; ++i){\n";
	code_bef_expr << "\t\t\t\tif(key >=ran_start_end[i].first && key <=ran_start_end[i].second){\n";
	code_bef_expr << "\t\t\t\t\treturn true;\n";
	code_bef_expr << "\t\t\t\t}\n";
	code_bef_expr << "\t\t\t}\n";
	code_bef_expr << "\t\t\tfor(int i=0; i< size_ran_indiv; ++i){\n";
	code_bef_expr << "\t\t\t\tif(key==ran_indiv[i]){\n";
	code_bef_expr << "\t\t\t\t\treturn true;\n";
	code_bef_expr << "\t\t\t\t}\n";
	code_bef_expr << "\t\t\t}\n";
	code_bef_expr << "\t\t\treturn false;\n";
	code_bef_expr << "\t\t}\n";

	string struct_name1 = get_temp_name();
	code_bef_expr << "\t} " <<  struct_name1.c_str() <<";\n";
	string test_bool_var_name=get_temp_name();
	code_bef_expr <<  "bool " <<  test_bool_var_name.c_str()
		<< " = " << struct_name1.c_str()
		<< ".exists(" << name.c_str() << ");\n";
	code_expr << test_bool_var_name.c_str() << " " ;
			  
}

