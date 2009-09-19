#include "question_disk_data.h"
#include "question.h"
extern vector <AbstractQuestion*> question_list;


void question_disk_data::set_array_data(vector<int> l_array_index_list, vector<int> & l_data)
{
	if(l_array_index_list.size()!=array_bounds.size()){
		cout << "array_index_list.size() != array_bounds.size()" << endl;
	}
	vector<int> v(l_array_index_list.size());
	int index=0;
	for(int i=0; i<l_array_index_list.size(); ++i){
		v[i] += l_array_index_list[i];
		for(int j=i+1; j<array_bounds .size(); ++j){
			v[i]=v[i]*array_bounds[j];
		}
		index+=v[i];
	}
	//cout << "index computes to: " << index << endl;
	cout << "question_list.size(): " << question_list.size() << endl;
	int question_list_index=-1;
	for (int i=0; i< question_list.size(); ++i){
		if(question_list[i]->questionName_==qno){
			question_list_index=i;
			break;
		}
	}
	if(question_list_index!=-1){
		cout << "question_list_index: " << question_list_index << endl;
		AbstractQuestion* q= 	question_list[question_list_index+index+1];
		q->input_data.erase(q->input_data.begin(), q->input_data.end());
		for(int k=0; k<l_data.size(); ++k){
			q->input_data.insert(l_data[k]);
		}
	}
}

