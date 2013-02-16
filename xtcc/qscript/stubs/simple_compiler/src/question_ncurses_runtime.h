/*
 * =====================================================================================
 *
 *       Filename:  question_ncurses_runtime.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 08 February 2013 08:16:08  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Neil Xavier D'Souza
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef QUESTION_NCURSES_RUNTIME_H
#define QUESTION_NCURSES_RUNTIME_H

#include <curses.h>
#include <panel.h>
#include "a_few_pd_curses_keys.h"
#include "question.h"


WINDOW *create_newwin (int32_t height, int32_t width, int32_t starty, int32_t startx);
/*
void SetupNCurses (	WINDOW * &  question_window,
			WINDOW * &  stub_list_window,
			WINDOW * & data_entry_window,
			WINDOW * & help_window,
			PANEL * &  question_panel,
			PANEL * &  stub_list_panel,
			PANEL * & data_entry_panel,
			PANEL * & help_panel);
*/
void SetupNCurses(WINDOW * &  question_window,
			WINDOW * &  stub_list_window,
			WINDOW * & data_entry_window,
			WINDOW * & help_window,
			PANEL * &  question_panel,
			PANEL * &  stub_list_panel,
			PANEL * & data_entry_panel,
			PANEL * & help_panel);

void define_some_pd_curses_keys();
void ncurses_eval (AbstractQuestion * q);
void setup_ui ();

int32_t prompt_user_for_serial_no();
char get_end_of_question_response();
void print_save_partial_data_message_success ();

#endif /*  QUESTION_NCURSES_RUNTIME_H */
