/*
 * =====================================================================================
 *
 *       Filename:  chunked_for.cpp
 *
 *    Description:  return fixed size chunks in for loop
 *
 *        Version:  1.0
 *        Created:  Thursday 22 August 2013 11:34:33  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::cout;
using std::endl;
using std::string;

struct Question {
	string questionName_;
	bool isAnswered_;
	Question (string  q_name):
		questionName_ (q_name),
		isAnswered_ (false)
	{ }
};

vector <Question*> do_chunked_for (int for_loop_max, int chunk_size, vector<Question*> & q_list)
{
	vector <Question*> result;
	for (int i=0; i<for_loop_max; ++i) {
		if (q_list[i]->isAnswered_ == false) {
			result.push_back (q_list[i]);
		}
		if (result.size() == chunk_size) {
			return  result;
		}
	}
	return result;
}

void eval_qnre (vector<Question*> q_list)
{
	vector <Question*> res = do_chunked_for  (q_list.size(), 5, q_list);
	while (res.size() != 0) {
		for (int i=0; i < res.size(); ++i) {
			cout << " " << res[i]->questionName_;
			res[i]->isAnswered_ = true;
		}
		cout << endl;
		res = do_chunked_for  (q_list.size(), 5, q_list);
	}
}

int main ()
{
	Question * q1_0 =  new Question(string("q1_0"));
	Question * q1_1 =  new Question(string("q1_1"));
	Question * q1_2 =  new Question(string("q1_2"));
	Question * q1_3 =  new Question(string("q1_3"));
	Question * q1_4 =  new Question(string("q1_4"));
	Question * q1_5 =  new Question(string("q1_5"));
	Question * q1_6 =  new Question(string("q1_6"));
	Question * q1_7 =  new Question(string("q1_7"));
	Question * q1_8 =  new Question(string("q1_8"));
	Question * q1_9 =  new Question(string("q1_9"));
	Question * q1_10 = new Question(string("q1_10"));
	Question * q1_11 = new Question(string("q1_11"));
	Question * q1_12 = new Question(string("q1_12"));
	Question * q1_13 = new Question(string("q1_13"));
	Question * q1_14 = new Question(string("q1_14"));
	Question * q1_15 = new Question(string("q1_15"));
	Question * q1_16 = new Question(string("q1_16"));
	Question * q1_17 = new Question(string("q1_17"));

	vector <Question*> q_list;
	q_list.push_back (q1_0);
	q_list.push_back (q1_1);
	q_list.push_back (q1_2);
	q_list.push_back (q1_3);
	q_list.push_back (q1_4);
	q_list.push_back (q1_5);
	q_list.push_back (q1_6);
	q_list.push_back (q1_7);
	q_list.push_back (q1_8);
	q_list.push_back (q1_9);
	q_list.push_back (q1_10);
	q_list.push_back (q1_11);
	q_list.push_back (q1_12);
	q_list.push_back (q1_13);
	q_list.push_back (q1_14);
	q_list.push_back (q1_15);
	q_list.push_back (q1_16);
	q_list.push_back (q1_17);
	eval_qnre(q_list);

}
