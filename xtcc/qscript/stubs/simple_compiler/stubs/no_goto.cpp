/*
 * =====================================================================================
 *
 *       Filename:  goto.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 31 January 2013 04:31:28  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <cstdlib>
#include <limits.h>

using namespace std;

void print_vec(vector<int> & v)
{
	for (int i=0; i< v.size(); ++i) {
		cout << " " << v[i];
	}

}

bool VerifyQuestionIntegrity (vector<int> & input_data, set<int> & valid_codes);

struct Question
{
	string q_name;
	string q_text;
	set<int> valid_codes;
	vector<int> input_data;
	bool is_answered;
	int question_no_index;
	Question (const string p_q_name, const string p_q_text, const set<int> & p_valid_codes,
			int l_question_no_index) :
		q_name(p_q_name), q_text(p_q_text), valid_codes(p_valid_codes), 
		is_answered(false), question_no_index(l_question_no_index)
	{ }
	void eval() {
		cout << q_name << "." << q_text << endl;
		if (is_answered) {
			cout << "Current data: " ;
			print_vec (input_data);
		}
	}

	bool VerifyQuestionIntegrity();
};

enum UserNavigation { NAVIGATE_NEXT, NAVIGATE_PREV };
//enum STR2INT_ERROR { SUCCESS, OVERFLOW, UNDERFLOW, INCONVERTIBLE };
//STR2INT_ERROR str2int (int &i, char const *s, int base = 0);
bool str2int (vector<int> &answers, string s);
bool str2int (vector<int> &answers, char const *s);

struct TheQuestionnaire {
	Question * q1;
	Question * q2;
	Question * q3;
	vector <Question*> question_list;


	Question * last_question_visited;

	TheQuestionnaire():
		q1(0), q2(0), q3(0), last_question_visited(0)
	{
		cout << __PRETTY_FUNCTION__ << endl;

		string q1_name = "q1";
		string txt_q1 = "Q1. Gender: 1-> Male, 2->Female";
		set<int> q1_valid_codes; 
		q1_valid_codes.insert(1);
		q1_valid_codes.insert(2);
		q1=new Question(q1_name, txt_q1, q1_valid_codes, 0);
		question_list.push_back (q1);

		string q2_name = "q2";
		string txt_q2 = "Q2. Age: 1-> 15-20, 2->21-30, 3->31-40, 4->41-50";
		set<int> q2_valid_codes; 
		q2_valid_codes.insert(1);
		q2_valid_codes.insert(2);
		q2_valid_codes.insert(3);
		q2_valid_codes.insert(4);
		q2=new Question(q2_name, txt_q2, q2_valid_codes, 1);
		question_list.push_back (q2);

		string q3_name = "q3";
		string txt_q3 = "Q3. Vegetables awareness: 11->Okra, 12->Egg Plant, 13->Potato, 14->French Beans";
		set<int> q3_valid_codes; 
		q3_valid_codes.insert(11);
		q3_valid_codes.insert(12);
		q3_valid_codes.insert(13);
		q3_valid_codes.insert(14);
		q3=new Question(q3_name, txt_q3, q3_valid_codes, 2);
		question_list.push_back (q3);

	}
	Question * evaluate (UserNavigation navg, Question * last_question_visited,
			Question * jump_to_question);
	Question * ComputePreviousQuestion(Question * q)
	{
		int32_t current_question_index = -1;
		int32_t questions_start_from_here_index = 0;
		for (int32_t i = questions_start_from_here_index; i < question_list.size(); ++i)
		{
			if (question_list[i] == q)
			{
				current_question_index = i;
				break;
			}
		}
		if (current_question_index == -1)
		{
			cerr << "internal compiler error at runtime ... filename: "
				<< __FILE__
				<< "line no: " << __LINE__
				<< endl;
		}
		for (int32_t i = current_question_index-1; i >= 0; --i)
		{
			if (question_list[i]->is_answered)
			{
				return question_list[i];
			}
		}
		// If we reach here just return the 1st question and hope for the best
		// This will not work if there is a condition on the 1st question - because of which it should never have been taken
		return question_list[questions_start_from_here_index];
	}



};

bool Question::VerifyQuestionIntegrity()
{
	return ::VerifyQuestionIntegrity (input_data, valid_codes);
}

bool VerifyQuestionIntegrity (vector<int> & input_data, set<int> & valid_codes)
{
	const set<int>::iterator NOT_FOUND_IT = valid_codes.end();
	//cout << __PRETTY_FUNCTION__ << ": input_data.size():" << input_data.size()
	//	<< endl;
	for (int i = 0; i < input_data.size(); ++i) {
		int value = input_data[i];
		if (valid_codes.find (value) == NOT_FOUND_IT) {
			return false;
		}
	}
	return true;

}

Question * TheQuestionnaire::evaluate (UserNavigation p_navg, Question * last_question_visited,
		Question * jump_to_question)
{
	//void * q1_ptr = q1;
	//cout << "*q1: " << (q1_ptr) << endl;
//	cout << "q1->q_name:" << q1->q_name << endl;
//start_of_questions:
	if ( 		q1->is_answered == false 
		|| 	(q1->is_answered && !q1-> VerifyQuestionIntegrity())
		||	(p_navg == NAVIGATE_NEXT  && q1->question_no_index > last_question_visited->question_no_index)
		||	(p_navg == NAVIGATE_PREV  && q1 ==  jump_to_question)
	   ) {
		cout << __PRETTY_FUNCTION__ << " returned q1" << endl;
		return q1;
	}

	if ( 		q2->is_answered == false 
		|| 	(q2->is_answered && !q2-> VerifyQuestionIntegrity())
		||	(p_navg == NAVIGATE_NEXT  && q2->question_no_index > last_question_visited->question_no_index )
		||	(p_navg == NAVIGATE_PREV  && q2 ==  jump_to_question)
	   ) {
		cout << __PRETTY_FUNCTION__ << " returned q2" << endl;
		return q2;
	}

	if ( 		q3->is_answered == false 
		|| 	(q3->is_answered && !q3-> VerifyQuestionIntegrity())
		||	(p_navg == NAVIGATE_NEXT  && q3->question_no_index > last_question_visited->question_no_index )
		||	(p_navg == NAVIGATE_PREV  && q3 ==  jump_to_question)
	   ) {
		cout << __PRETTY_FUNCTION__ << " returned q3" << endl;
		return q3;
	}

	cout << __PRETTY_FUNCTION__ << " returned q3" << endl;
	return 0;
}


enum EvalMode { USER_NAVIGATION, NORMAL_FLOW };
void question_eval_loop (EvalMode qnre_mode, UserNavigation navg, Question * last_question_visited
		, Question * jump_to_question, TheQuestionnaire * qnre);

int main()
{
	TheQuestionnaire * qnre = new TheQuestionnaire();

	UserNavigation navg = NAVIGATE_NEXT;
	Question * last_question_visited = 0;
	Question * jump_to_question = 0;
	EvalMode qnre_mode = NORMAL_FLOW;
	//start:
	question_eval_loop (qnre_mode, navg, last_question_visited, jump_to_question, qnre);
}

void question_eval_loop (EvalMode qnre_mode, UserNavigation navg, Question * last_question_visited
		, Question * jump_to_question, TheQuestionnaire * qnre)
{

	//while (Question * next_q = qnre->evaluate (navg, last_question_visited, jump_to_question)) 
	Question * next_q = qnre->evaluate (navg, last_question_visited, jump_to_question);
	if (next_q) {
	
//ask_again:
		//cout << "processing question: next_q->q_name:" << next_q->q_name << endl;
		next_q->eval();
		//cin.getline (current_response, 50);
		string current_response;
		getline(cin, current_response);
		if (current_response.size() > 0) {
			if (current_response[0] == 'P') {
				navg = NAVIGATE_PREV;
				Question * prev_question = qnre->ComputePreviousQuestion (next_q);
				//qnre->evaluate(NAVIGATE_PREV, last_question_visited, prev_question);
				question_eval_loop (USER_NAVIGATION, NAVIGATE_PREV, 
						last_question_visited, prev_question, qnre);
			} else if (current_response[0] == 'N') {
				navg = NAVIGATE_NEXT;
				question_eval_loop (USER_NAVIGATION, NAVIGATE_NEXT, 
						last_question_visited, 0, qnre);
			} else if (isdigit (current_response[0])) {
				vector <int> answers;
				//str2int (answers, current_response.c_str());
				str2int (answers, current_response);
				cout << "Entered data: " ;
				print_vec(answers);
				cout << endl;
				bool is_valid = VerifyQuestionIntegrity(answers, next_q->valid_codes);
				if (is_valid) {
					next_q->is_answered = true;
					question_eval_loop (NORMAL_FLOW, NAVIGATE_NEXT, 
							next_q, 0, qnre);
				} else {
					cout << "Invalid Entry" << endl;
					question_eval_loop (NORMAL_FLOW, NAVIGATE_NEXT, 
							last_question_visited, 0, qnre);
					//goto ask_again;
				}
				//goto start;
			} else {
				// invalid entries
				cout << "invalid input" << endl;
				question_eval_loop (NORMAL_FLOW, NAVIGATE_NEXT, 
						last_question_visited, 0, qnre);
				//goto ask_again;
			}
		} else {
			//goto ask_again;
			question_eval_loop (NORMAL_FLOW, NAVIGATE_NEXT, 
					last_question_visited, 0, qnre);
		}
	}
}

/*

STR2INT_ERROR str2int (int &i, char const *s, int base )
{
    char *end;
    long  l;
    extern int errno ;
    l = strtol(s, &end, base);
    if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
        return OVERFLOW;
    }
    if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
        return UNDERFLOW;
    }
    if (*s == '\0' || *end != '\0') {
        return INCONVERTIBLE;
    }
    i = l;
    return SUCCESS;
}
*/
// very simple and cannot handle errors etc
bool str2int (vector<int> &answers, string s)
//bool str2int (vector<int> &answers, char const *s)
{
	char              c = -1;
	std::stringstream ss(s);
	cout << "str2int: input s: " << s << endl;
	bool got_1 = false;
	while (1) {
		int i;
		ss >> i;
		//if (ss.fail() || ss.get(c)) {
		//    // not an integer
		//    return false;
		//}
		//
		if (ss.fail()) {
			break;
		} else {
			got_1 = true;
			answers.push_back(i);
		}
		ss.get(c);
		if (isdigit(c)) {
			// this should never occur as it was already parsed as a number
			ss.putback(c);
		} else if (!(c=='\n' || c=='\t' || c==' ')) {
			return false;
		}
	}
	return got_1;
}
