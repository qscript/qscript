/*
 * =====================================================================================
 *
 *       Filename:  generate_code.hpp
 *
 *    Description:  headers
 *
 *        Version:  1.0
 *        Created:  Saturday 14 July 2012 08:27:58  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Neil Xavier D'Souza
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef XTCC_GENERATE_CODE_H
#define XTCC_GENERATE_CODE_H
#include <time.h>

//void print_table_code(FILE * op, FILE *tab_drv_func, FILE * tab_summ_func, vector<Table::table*> & table_list);
void print_table_code (FILE * table_h, FILE * table_cpp, 
			FILE * tab_drv_func, FILE * tab_summ_func, 
			vector<Table::table*> & table_list, 
			string tab_fname, string session_id);
void print_latex_print(FILE* op, int table_index);
//void print_axis_code(FILE * op, FILE * axes_drv_func);
void print_axis_code (FILE * axes_h, FILE * axes_cpp, FILE * axes_drv_func);

namespace Table{ 

	struct ax;
}

string print_session_makefile (std::string session_id) ;

//string print_constructor_code (string ax_name, Table::ax* axis, FILE * op, FILE * axes_drv_func
//		, stringstream & constructor_header
//		, stringstream & constructor_body
//		);

#endif /*  XTCC_GENERATE_CODE_H */
