#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main(){

	struct temp_0 {
		const int size_ran_indiv;
		const int size_start_end;
		vector<int> ran_indiv;
		vector< pair<int,int> > ran_start_end;

		temp_0(): size_ran_indiv(3), size_start_end(0), 
			ran_indiv(size_ran_indiv), ran_start_end(size_start_end)
		{
			ran_indiv[0]=1;
			ran_indiv[1]=2;
			ran_indiv[2]=3;
		}
		bool exists(int key){
			for(int i=0; i<size_start_end; ++i){
				if(key >=ran_start_end[i].first && key <=ran_start_end[i].second){
					return true;
				}
			}
			for(int i=0; i< size_ran_indiv; ++i){
				if(key==ran_indiv[i]){
					return true;
				}
			}
			return false;
		}
	} temp_1;
	int name=2;
	bool temp_2 = temp_1.exists(name);

}
