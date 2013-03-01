/*
 * =====================================================================================
 *
 *       Filename:  make-concept-section.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 28 February 2013 10:34:55  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

struct named_attributes
{
	string name;
	vector <string> n_att_vec;
	named_attributes (string p_name)
		: name (p_name), n_att_vec()
	{ }
};



struct question
{
	string qno;
	string q_text;
	string stubs;
	int no_of_codes;
	struct named_attributes * n_att;

	question (string p_qno,
		string p_q_text,
		string p_stubs,
		int p_no_of_codes,
		struct named_attributes * p_n_att)
		: qno (p_qno), q_text (p_q_text),
		  stubs (p_stubs), no_of_codes (p_no_of_codes),
		  n_att( p_n_att)
	{

	}
};

void print_single_concept (int start_q_no, vector <struct question *> q_vec );

int main()
{
	named_attributes conc_batt (string("conc_batt_atts"));


	conc_batt.n_att_vec.push_back("The concept is very rewarding");
	conc_batt.n_att_vec.push_back("The concept is very attractive");
	conc_batt.n_att_vec.push_back("This is the program I always wanted the bank to offer me");
	conc_batt.n_att_vec.push_back("This concept will motivate me to spend more on credit card to get bigger rewards");
	conc_batt.n_att_vec.push_back("The concept is shariah complaint");

	struct vector <question*> vec_conc_question;

	//struct question ekhlas_conc[] =
	//{
	question * q1 = new question	(
			string("Q27"),
			string("Please tell me how you would rate your likeability for <MENTION CONCEPT # 1> loyalty concept on 5 point rating scale to express your opinion where 5 means ‘liked it a lot’ and 1 means ‘disliked it a lot’."),
			string ("like_5"),
			1,
			0
		); //,
	//question q2 = 	
	question * q2 =  new 	question (
			string("Q28"),
			string("What you liked about <MENTION CONCEPT #1> loyalty program?"),
			string ("(1-500)"),
			5,
			0
			);//,
	question * q3 = new question (
			string ("Q29"),
			string ("What you disliked about <MENTION CONCEPT #1> loyalty program?"),
			string ("(1-500)"),
			5,
			0
			); //,
	question * q4 = new question (
			string ("Q30"),
			string ("Do you have any suggestion to make <MENTION CONCEPT #1> loyalty program more attractive?"),
			string ("(1-500)"),
			5,
			0
			);//,
	question * q5 = new question (
			string ("Q31"),
			string("Now I am going to read out a series of statements which customers like you relate to such loyalty programs. Please tell me to what extent you agree or disagree with each statement in context of <MENTION CONCEPT #1>? (SA)"),
			string ("agree_5"),
			1,
			&conc_batt
			);
	
	vec_conc_question.push_back(q1);
	vec_conc_question.push_back(q2);
	vec_conc_question.push_back(q3);
	vec_conc_question.push_back(q4);
	vec_conc_question.push_back(q5);

	//};

	print_single_concept (27, vec_conc_question);
	print_single_concept (32, vec_conc_question);
	print_single_concept (37, vec_conc_question);
	print_single_concept (42, vec_conc_question);
	print_single_concept (47, vec_conc_question);
	print_single_concept (52, vec_conc_question);
	print_single_concept (57, vec_conc_question);


}

void print_single_concept (int start_q_no, vector< question *> q_vec)
{
	for (int i=0; i < q_vec.size(); ++i ) {
		stringstream my_qno;
		my_qno << "q" << i + start_q_no;
		struct question * q_ptr = q_vec[i];

		if (q_ptr->n_att) {
			vector <string> & n_att= q_ptr->n_att->n_att_vec;
			cout << "named_attributes\t" << q_ptr->n_att->name << " = " << endl;
			for (int i1=0; i1<n_att.size(); ++i1) {
				if (i1 == n_att.size()-1) {
					cout << "\t" << "\"" << n_att[i1] << "\"" << endl;
				} else {
					cout << "\t" << "\"" << n_att[i1] << "\"," << endl;
				}
			}
			cout << ";" << endl << endl;
		}

		if (q_ptr->n_att == 0) {
			cout 	
				//<< q_ptr->qno 
				<< my_qno.str()
				<< "\t"
				<< "\"" <<q_ptr->q_text << "\"" << endl << "\t";
			if (q_ptr->no_of_codes == 1) {
				cout << "sp int32_t ";
			} else {
				cout << "mp(" << q_ptr->no_of_codes << ") int32_t " ;
			}
			cout 	<< q_ptr->stubs << ";"  << endl << endl;
		} else {
			stringstream s1;
			s1 << "i_" << q_ptr->qno;
			string i_name (s1.str());
			cout 	<< endl
				<<"\tint32_t " << i_name << " = 0;" << endl;
			cout << "\tfor (" << i_name << " = 0; " 
					<< i_name <<" < " << q_ptr->n_att->n_att_vec.size() << ";"
					<< " ++" << i_name << ") {" 
					<< endl << endl;
			cout 	
				<< my_qno.str() << "\t\t"
				<< "\"" << q_ptr->q_text << "\"" << endl
				<< "\t\t:" << q_ptr->n_att->name 
				<< "[" << i_name << "]"
				<< endl << "\t\t";
			if (q_ptr->no_of_codes == 1) {
				cout << "sp int32_t ";
			} else {
				cout << "mp(" << q_ptr->no_of_codes << ") int32_t " ;
			}
			cout 	<< q_ptr->stubs << ";"  << endl << endl;


			cout << "\t}" << endl << endl;
		}
	}
}
