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
void gtk_eval (AbstractQuestion * q);
void question_eval_loop (EvalMode qnre_mode,
	UserNavigation qnre_navigation_mode, AbstractQuestion * last_question_visited,
	AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire);

#endif /*  QUESTION_GTK2_RUNTIME_H */
