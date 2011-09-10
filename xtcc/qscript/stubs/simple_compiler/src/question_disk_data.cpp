#include "question_disk_data.h"
#include "question.h"
//extern vector <AbstractQuestion*> question_list;

#if 0
void question_disk_data::set_array_data(vector<int32_t> l_array_index_list, vector<int32_t> & l_data, vector <AbstractQuestion*> question_list)
{
	if(l_array_index_list.size()!=array_bounds.size()){
		cout << "array_index_list.size() != array_bounds.size()" << endl;
	}
	vector<int32_t> v(l_array_index_list.size());
	int32_t index=0;
	for(int32_t i=0; i<l_array_index_list.size(); ++i){
		v[i] += l_array_index_list[i];
		for(int32_t j=i+1; j<array_bounds .size(); ++j){
			v[i]=v[i]*array_bounds[j];
		}
		index+=v[i];
	}
	//cout << "index computes to: " << index << endl;
	//cout << "question_list.size(): " << question_list.size() << endl;
	int32_t question_list_index=-1;
	for (int32_t i=0; i< question_list.size(); ++i){
		if(question_list[i]->questionName_==qno){
			question_list_index=i;
			break;
		}
	}
	if(question_list_index!=-1){
		//cout << "question_list_index: " << question_list_index << endl;
		AbstractQuestion* q= 	question_list[question_list_index+index+1];
		q->input_data.erase(q->input_data.begin(), q->input_data.end());
		for(int32_t k=0; k<l_data.size(); ++k){
			q->input_data.insert(l_data[k]);
		}
	}
}
#endif /*  0  */

void QuestionDiskDataMap::set_array_data(string qno, vector<int32_t> & l_array_index_list, vector<int32_t> & data, vector <int32_t> & array_bounds)
{
	if(l_array_index_list.size()!=array_bounds.size()){
		cout << "array_index_list.size() != array_bounds.size()" << endl;
	}
	vector<int32_t> v(l_array_index_list.size());
	int32_t index=0;
	for(int32_t i=0; i<l_array_index_list.size(); ++i){
		v[i] += l_array_index_list[i];
		for(int32_t j=i+1; j<array_bounds .size(); ++j){
			v[i]=v[i]*array_bounds[j];
		}
		index+=v[i];
	}
	//vector <int32_t> & array_question_data = array_question_map[qno];
	map<int, vector<int32_t> > & array_question_data = array_question_map[qno];
	array_question_data[index] = data;
	
}
