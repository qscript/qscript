/*
 * =====================================================================================
 *
 *       Filename:  question_logic.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Tuesday 19 February 2013 08:47:50  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <fstream>
#include <signal.h>

#include "AbstractQuestionnaire.h"
#include "question_stdout_runtime.h"

void question_eval_loop2 (
	UserInput p_user_input,
	AbstractQuestion * last_question_visited,
	AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire);

void parse_input_data(vector<int> * data_ptr, int & success);
void callback_ui_input (UserInput p_user_input, AbstractQuestion * q, struct TheQuestionnaire * theQuestionnaire);
// 21-feb-2013 12:53 am
// nxd - modify this function
// remove all GetUserInput calls 
// make it return success or failure
// add error message as a parameter - let the message be registered here
// the decision making about what to do as a result of the success/failure should be handled
// in question_eval_loop2
void eval_single_question_logic_with_input (UserInput p_user_input, AbstractQuestion * q, struct TheQuestionnaire * theQuestionnaire)
{
	cout << "ENTER:" << __PRETTY_FUNCTION__ << endl;
	if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {
		cout << "-reached here" << __PRETTY_FUNCTION__ << ", " << __LINE__ << endl;
		if (p_user_input.questionResponseData_.length() == 0
				&& q->question_attributes.isAllowBlank() == true ) {
			// allow - serve next question
			// note that we do not set the isAnswered_ == true for the blank question
			// so when re-visiting this particular qnre it will automatically
			// stop here for data.
			question_eval_loop2 (p_user_input, /* last_question_visited */ q,
					/*  jump_to_question */ 0, theQuestionnaire);
		} else if (p_user_input.questionResponseData_.length() == 0
				&& q->question_attributes.isAllowBlank() == false ) {
			// do not allow - serve the same question
			GetUserInput (callback_ui_input, q, theQuestionnaire);
		} else {
			cout << "--reached here" << endl;
			// input is not blank
			int success;
			vector <int> input_data;
			parse_input_data (p_user_input.questionResponseData_ 
					/* current_response */, &input_data, success);
			cout << "success: " << success << endl;
			if (success == 0) {
				GetUserInput (callback_ui_input, q, theQuestionnaire);
			} else {
				// =======================
				string err_mesg, re_arranged_buffer;
				int pos_1st_invalid_data;
				if (q->check_and_store_input_data_single_question(err_mesg, re_arranged_buffer, pos_1st_invalid_data,
							input_data)) {
					cout << "Got valid data for : " << q->questionName_ << endl;
					// default direction - chosen by us
					// go for the next question

					// Note - this wont work in Erlang - modifying a variable
					//  - better to create a new UserInput and set it with the
					//  new valyes
					p_user_input.userNavigation_ = NAVIGATE_NEXT;
					p_user_input.theUserResponse_ = user_response::UserEnteredNavigation;
					question_eval_loop2 (p_user_input, q, 0, theQuestionnaire);
				} else {
					//stdout_eval (q, theQuestionnaire, callback_ui_input);
					GetUserInput (callback_ui_input, q, theQuestionnaire);
				}
				// =======================
#if 0
				user_input.userNavigation_ = NAVIGATE_NEXT;
				user_input.inputData_ = input_data;
				callback_ui_input (user_input, q, theQuestionnaire);
				string err_mesg, re_arranged_buffer;
				int pos_1st_invalid_data;
				if (q->check_and_store_input_data_single_question(err_mesg, re_arranged_buffer, pos_1st_invalid_data,
						p_user_input.inputData_)) {
					//serve next question
					question_eval_loop2 ( p_user_input, /* last_question_visited */ q,
							/*  jump_to_question */ 0, theQuestionnaire);
				} else {
					//serve same question
					question_eval_loop2 ( p_user_input, /* last_question_visited */ q,
							/*  jump_to_question */ 0, theQuestionnaire);
				}
#endif /*  0 */
			}
		}
	}
	cout << "EXIT:" << __PRETTY_FUNCTION__ << endl;
}

// these functions below have to be moved to an
// appropriate file - 
// but get them out of the generated code
// as they are static and do not change from
// questionnaire to questionnaire

extern FILE * qscript_stdout;
static void sig_usr(int32_t signo)
{
	if(signo == SIGSEGV)
	{
		printf("received SIGSEGV\n");
	}
	else if(signo == SIGILL)
	{
		printf("received SIGILL\n");
	}
	else if(signo == SIGHUP)
	{
		printf("received, SIGHUP: ignore this signal\n");
		return;
	}
	else
	{
		fprintf(stderr, "received signal : %d\n", signo);
	}
	fflush(qscript_stdout);
	endwin();
	exit(1);
}

extern string output_data_file_name;
extern string output_qtm_data_file_name;
extern string output_xtcc_data_file_name;
bool write_data_file_flag;
bool write_qtm_data_file_flag;
bool write_messages_flag;
bool write_xtcc_data_file_flag;




int process_options(int argc, char * argv[])
{
	//int32_t opterr=1, c;
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	extern int32_t optind, opterr, optopt;
	extern char * optarg;
	int c;
	while ( (c = getopt(argc, argv, "mx::w::q::")) != -1)
	{
		char ch = optopt;
		switch (c)
		{
			case 'w':
			{
				write_data_file_flag = true;
				if (optarg)
				{
					output_data_file_name = optarg;
				}
				else
				{
					output_data_file_name = "datafile.dat";
				}
			}
			break;
			case 'x':
			{
				write_xtcc_data_file_flag = true;
				if (optarg)
				{
					output_xtcc_data_file_name = optarg;
				}
				else
				{
					output_xtcc_data_file_name = "xtcc_datafile.dat";
				}
			}
			break;
			case 'q':
			{
				write_qtm_data_file_flag = true;
				if (optarg)
				{
					output_qtm_data_file_name = optarg;
				}
				else
				{
					output_qtm_data_file_name = "qtm_datafile.dat";
				}
			}
			break;
			case 'm':
			{
				write_messages_flag = true;
			}
			break;
			case '?' :
			{
				cout << " invalid option, optopt:" << optopt << endl;
				exit(1);
			}
			break;
			default:
				cerr << "invalid options: ch: " << ch << ", c: " << c << endl;
		}
	}
	cout << "output_data_file_name: " << output_data_file_name << endl;
	cout << "write_data_file_flag: " << write_data_file_flag << endl;
	cout << "output_qtm_data_file_name: " << output_qtm_data_file_name << endl;
	cout << "write_qtm_data_file_flag: " << write_qtm_data_file_flag << endl;
	//exit(1);
}

void SetupSignalHandler()
{
	if (signal (SIGSEGV, sig_usr) == SIG_ERR)
	{
		fprintf(stderr, "cannot catch SIGSEGV\n");
		exit(1);
	}
	else if (signal (SIGHUP, SIG_IGN) == SIG_ERR)
	{
		fprintf(stderr, "cannot ignore SIGHUP\n");
		exit(1);
	}
	else if (signal (SIGILL, sig_usr) == SIG_ERR)
	{
		fprintf(stderr, "cannot catch SIGILL\n");
		exit(1);
	}
}


void print_map_header(fstream & map_file )
{
	map_file << "Question No			,width,	no responses,	start position,	end position\n";
}
