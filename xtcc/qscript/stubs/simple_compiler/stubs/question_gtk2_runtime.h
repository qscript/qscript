/*
 * =====================================================================================
 *
 *       Filename:  question_gtk2_runtime.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 15 February 2013 03:14:33  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef QUESTION_GTK2_RUNTIME_H
#define QUESTION_GTK2_RUNTIME_H
#include "question.h"

void setup_ui (int argc, char * argv[], int (* p_return_ser_no) (int));
char get_end_of_question_response();
void print_save_partial_data_message_success ();
int32_t prompt_user_for_serial_no();
void ncurses_eval (AbstractQuestion * q);

#endif /*  QUESTION_GTK2_RUNTIME_H */
