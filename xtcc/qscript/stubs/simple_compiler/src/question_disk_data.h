#ifndef question_disk_data_h
#define question_disk_data_h

#include <sys/types.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;


struct question_disk_data
{
	string qno;
	vector <int32_t> data;
	vector <int32_t> array_bounds;

	question_disk_data(string & l_qno, vector<int32_t> & l_bounds, vector<int32_t> & ):
		qno(l_qno), data(0), array_bounds(l_bounds)
	{
		//cerr << "question_disk_data::question_disk_data: bounds: " 
		//	<< array_bounds.size()	
		//	<< endl;
	}

	question_disk_data(string & l_qno, vector<int32_t> & l_data):
		qno(l_qno), data(l_data), array_bounds(0)
	{
		//cerr << "question_disk_data::question_disk_data()" <<endl;
		//cerr << "data:";
		//for(int32_t i=0; i<data.size(); ++i){
		//	cerr << " " << data[i] << ",";
		//}
		//cerr << "question_disk_data::question_disk_data: data.size(): " << data.size()	
		//	<< ", l_data.size(): " << l_data.size() << endl;
	}

	question_disk_data(string & l_qno):
		qno(l_qno), data(0), array_bounds(0)
	{
		//cerr << "question_disk_data: (string& l_qno) " << endl;
	}

	void set_array_data(vector<int32_t> l_array_index_list, vector<int32_t> & l_data);

};

struct QuestionDiskDataMap
{
	vector <question_disk_data*> question_list;
	map<string, map<int32_t, vector<int32_t> > > array_question_map;
	void set_array_data(string qno, vector<int32_t> & l_array_index_list, vector<int32_t> & data, vector <int32_t> & array_bounds);
	QuestionDiskDataMap()
		:question_list(), array_question_map()
		{}
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
