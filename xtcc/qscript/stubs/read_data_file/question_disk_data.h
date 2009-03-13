#ifndef question_disk_data_h
#define question_disk_data_h

#include <string>
#include <vector>
using namespace std;

struct question_disk_data{
	string qno;
	vector <int> data;

	question_disk_data(string & l_qno, vector<int> & l_data):
		qno(l_qno), data(l_data)
	{
		cerr << "question_disk_data::question_disk_data: data.size(): " << data.size()	
			<< ", l_data.size(): " << l_data.size() << endl;							   
	}

	question_disk_data(string & l_qno):
		qno(l_qno)
	{
		cerr << "question_disk_data: (string& l_qno) " << endl;
	}
};

#endif /* question_disk_data_h */
