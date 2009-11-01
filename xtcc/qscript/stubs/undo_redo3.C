#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

void TheQuestionnaire();

struct Question {
	string questionNo_;
	string questionText_;
	int response_;
	bool isAnswered_;
	bool isModified_;
	Question(string p_qno, string p_qtxt)
		: questionNo_(p_qno), questionText_(p_qtxt), isAnswered_(false)
		  , isModified_(false)
	{
	}

	void ask(){
		cout << questionNo_ << ". " << questionText_ << endl;
		cin >> response_;
		isAnswered_=true;
		char my_endl=0;
		cin.get(my_endl);
		cout << "got my_endl: |" << static_cast<int>(my_endl) << "|" << endl;
	}

	void display(){
		cout << questionNo_ << ". " << questionText_ << endl;
		cout << "Current Response:" << response_ << endl;
	}
	int getData(){
		int c;
		char my_endl;
		while ( (c=cin.get()) && c!=EOF && isspace(c))
			;
		//cin >> response_;
		if(c=='p' || c== 'n'){
			cin.get(my_endl);
			cout << "got my_endl: |" << my_endl << "|" << endl;
			return c;
		} else {
			cin.putback(c);
			cin >> response_ ;
			isModified_=true;
			return 0;
		}
	}
};

enum QuestionMode { COLLECTDATA, REVIEWDATA, WRITEDATA };
void TheQuestionnaire()
{

	Question q1("1", "Q1");
	Question q2("2", "Q2");

lab_q1:
	QuestionMode mode;
	if(q1.isAnswered_){
		mode=REVIEWDATA;
	} else {
		mode=COLLECTDATA;
	}
	int a = 1;
	if(!q1.isAnswered_){
		//mode=COLLECTDATA;
		q1.ask();
	}
	
	/*
	if(mode==COLLECTDATA){
		q1.ask();
	}
	*/
	if(mode==REVIEWDATA){
		cout << "mode==REVIEWDATA" << endl;
		q1.display();
		int resp=q1.getData();
		if(resp=='p'){
			goto lab_q1;
		} 

	}

lab_q2:
	a=2;
	if(q2.isAnswered_){
		mode=REVIEWDATA;
	} else {
		mode=COLLECTDATA;
	}

	if(!q2.isAnswered_){
		if(q1.response_==1)
			q2.ask();
	}
	if(mode==REVIEWDATA){
		if(q1.response_==1){
			q2.display();
			int resp=q2.getData();
			if(resp=='p'){
				goto lab_q2;
			}
		}
	}

	cout << "Review data? (y/n): " << endl;
	//int resp = cin.get();
	int resp ;
	while ( (resp=cin.get()) && resp!=EOF && isspace(resp))
		;
	//int resp;
	//cin >> resp;
	int cr = '\r';
	int newl = '\n';
	cout << "got resp: " << resp  
		<< ", cr: " << cr 
		<< ", newl: " << newl
		<< endl;
	cout << "reached here " << endl;
	if( resp=='y'){
		goto lab_q1;
	}

}

int main()
{
	TheQuestionnaire();
}


