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
void print_table_code (FILE * op, FILE * tab_drv_func, FILE * tab_summ_func, vector<Table::table*> & table_list, string tab_fname);
void print_latex_print(FILE* op, int table_index);
void print_axis_code(FILE * op, FILE * axes_drv_func);

#endif /*  XTCC_GENERATE_CODE_H */
