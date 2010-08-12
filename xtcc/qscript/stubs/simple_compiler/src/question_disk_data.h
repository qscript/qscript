#ifndef question_disk_data_h
#define question_disk_data_h

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct question_disk_data{
	string qno;
	vector <int> data;
	vector <int> array_bounds;

	question_disk_data(string & l_qno, vector<int> & l_bounds, vector<int> & ):
		qno(l_qno), array_bounds(l_bounds)
	{
		//cerr << "question_disk_data::question_disk_data: bounds: " 
		//	<< array_bounds.size()	
		//	<< endl;
	}

	question_disk_data(string & l_qno, vector<int> & l_data):
		qno(l_qno), data(l_data)
	{
		//cerr << "question_disk_data::question_disk_data: data.size(): " << data.size()	
		//	<< ", l_data.size(): " << l_data.size() << endl;
	}

	question_disk_data(string & l_qno):
		qno(l_qno)
	{
		//cerr << "question_disk_data: (string& l_qno) " << endl;
	}

	void set_array_data(vector<int> l_array_index_list, vector<int> & l_data);

};

class QuestionExists
{
	string qno;
	public:
	QuestionExists(string l_qno): qno(l_qno)
	{}
	bool operator() (question_disk_data * q)
	{
		if(qno==q->qno){
			return true;
		} else {
			return false;
		}
	}
};

#endif /* question_disk_data_h */
