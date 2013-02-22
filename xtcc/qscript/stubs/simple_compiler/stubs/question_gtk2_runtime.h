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
#include "user_navigation.h"
#include "UserResponse.h"
#include "eval_mode.h"

struct TheQuestionnaire;
void setup_ui (int argc, char * argv[], /* int (* p_return_ser_no) (int), */ struct TheQuestionnaire * p_theQuestionnaire);
char get_end_of_question_response();
void print_save_partial_data_message_success ();
int32_t prompt_user_for_serial_no(
		int (* p_return_ser_no) (int, struct TheQuestionnaire *)
	);
void gtk_eval (AbstractQuestion * q);
int callback_get_ser_no_from_ui (int p_ser_no, struct TheQuestionnaire * theQuestionnaire );
/*
struct TheQuestionnaire;

void question_eval_loop (EvalMode qnre_mode,
	UserNavigation qnre_navigation_mode, AbstractQuestion * last_question_visited,
	AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire);
  */

struct UserInput
{
	UserNavigation userNavigation_;
	//string question_response;
	//vector <int> inputData_;
	string questionResponseData_;
	user_response::UserResponseType theUserResponse_;
	UserInput():
		userNavigation_(NOT_SET),
		//inputData_(),
		questionResponseData_(),
		theUserResponse_(user_response::NotSet)
	{}
};
//void stdout_eval (AbstractQuestion * q);
struct TheQuestionnaire;
void stdout_eval (AbstractQuestion * q, struct TheQuestionnaire * theQuestionnaire,
	void (*callback_ui_input) 
		(UserInput p_user_input, AbstractQuestion * q, struct TheQuestionnaire * theQuestionnaire));
void parse_input_data(string input_string, vector<int> * data_ptr, int & success);
void GetUserInput ( 
	void (*callback_ui_input) (UserInput p_user_input, AbstractQuestion * q,
		struct TheQuestionnaire * theQuestionnaire), 
		AbstractQuestion *q, struct TheQuestionnaire * theQuestionnaire);

struct TheQuestionnaire * make_questionnaire ();

#endif /*  QUESTION_GTK2_RUNTIME_H */
