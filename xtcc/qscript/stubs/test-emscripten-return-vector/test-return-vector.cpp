#include <vector>
#include <string>
#include <cstdio>

using std::string;
using std::vector;

struct Question {
	string qName_;
	string qText_;
	Question (string p_qname, string p_qtext):
		qName_ (p_qname), qText_(p_qtext)
	{ }
};

vector <Question *> GetQuestionsForPage ()
{
	vector <Question*> result;
	Question * q1= new Question("q1", "What is your Age?");
	result.push_back(q1);
	Question * q2= new Question("q2", "Please state your Gender");
	result.push_back(q2);
	Question * q3= new Question("q3", "What is your marital status");
	result.push_back(q3);
	return result;
}

void PrintQuestions (vector<Question*> p_vec_questions)
{
	for (int i=0; i<p_vec_questions.size(); ++i) {
		printf ("%s.%s\n", p_vec_questions[i]->qName_.c_str(), p_vec_questions[i]->qText_.c_str());
	}
	printf ("\n");
}

int main()
{
	vector<Question*> questions_for_page = GetQuestionsForPage();
	PrintQuestions (questions_for_page);
}

