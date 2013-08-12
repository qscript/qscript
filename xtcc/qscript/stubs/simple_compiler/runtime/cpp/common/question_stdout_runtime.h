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
#ifndef QUESTION_STDOUT_RUNTIME_H
#define QUESTION_STDOUT_RUNTIME_H
#include "question.h"
#include "user_navigation.h"
#include "UserResponse.h"
#include "eval_mode.h"
#include "user_input.h"

struct TheQuestionnaire;
void setup_ui (int argc, char * argv[]);
char get_end_of_question_response();
void print_save_partial_data_message_success ();
int32_t prompt_user_for_serial_no(int (* p_return_ser_no) (int, int), int nest_level);
/*
struct TheQuestionnaire;

void question_eval_loop (EvalMode qnre_mode,
	UserNavigation qnre_navigation_mode, AbstractRuntimeQuestion * last_question_visited,
	AbstractRuntimeQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire);
  */

#if 0
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
#endif /* 0 */


//void stdout_eval (AbstractRuntimeQuestion * q);
struct TheQuestionnaire;

void callback_ui_input (UserInput p_user_input,
		const vector<AbstractRuntimeQuestion *> & q_vec,
		struct TheQuestionnaire * theQuestionnaire, int nest_level);
void stdout_eval (const vector <AbstractRuntimeQuestion *> & q_vec, struct TheQuestionnaire * theQuestionnaire,
	void (*callback_ui_input)
		(UserInput p_user_input, const vector<AbstractRuntimeQuestion *> & q_vec,
		 struct TheQuestionnaire * theQuestionnaire, int nest_level),
		 int nest_level
		);

void question_eval_loop2 (
	UserInput p_user_input,
	const vector<AbstractRuntimeQuestion *> & last_question_visited,
	AbstractRuntimeQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire, int nest_level);
void parse_input_data(string input_string, vector<int> * data_ptr, int & success);
void GetUserInput (
	void (*callback_ui_input)
		(UserInput p_user_input, const vector<AbstractRuntimeQuestion *> & q_vec,
		 struct TheQuestionnaire * theQuestionnaire, int nest_level),
	 const vector<AbstractRuntimeQuestion *> & q_vec,
	 struct TheQuestionnaire * theQuestionnaire, int nest_level);


#endif /*  QUESTION_STDOUT_RUNTIME_H */
