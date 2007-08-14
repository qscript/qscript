#include <iostream>
#include <vector>
using namespace std;
struct table_q1_q2 {
const int rows, cols;
vector <int> counter;
table_q1_q2():rows(5), cols(4),counter(5*4){for (int i=0;i<counter.size();++i) counter[i]=0; }
void compute(){
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			if(ax_q1.flag[i] && ax_q2.flag[j]){
				++counter[i*cols+j];
			} 
		} 
	}
	} /* compute()*/
	void print(){
		int rci=0, cci=0; /* row counter index , col ... */
	cout << "rows: " << rows << "cols: " << cols << endl;		for(int i=0; i<ax_q1.stmt_text.size(); ++i){
			cci=0;
			cout << ax_q1.stmt_text[i] << ",";
			if(ax_q1.is_a_count_text[i]){
				for(int j=0; j<ax_q2.stmt_text.size(); ++j){
					if(ax_q2.is_a_count_text[j]){
						//cout << "rci:" << rci << "cci:" << cci << endl;
						cout << counter[cci+rci*cols]<<",";
						++cci;
					}
				}
				++rci;
			}
		cout << endl;
		}
	}
} tab_q1_q2;
struct table_q1_q3 {
const int rows, cols;
vector <int> counter;
table_q1_q3():rows(5), cols(4),counter(5*4){for (int i=0;i<counter.size();++i) counter[i]=0; }
void compute(){
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			if(ax_q1.flag[i] && ax_q3.flag[j]){
				++counter[i*cols+j];
			} 
		} 
	}
	} /* compute()*/
	void print(){
		int rci=0, cci=0; /* row counter index , col ... */
	cout << "rows: " << rows << "cols: " << cols << endl;		for(int i=0; i<ax_q1.stmt_text.size(); ++i){
			cci=0;
			cout << ax_q1.stmt_text[i] << ",";
			if(ax_q1.is_a_count_text[i]){
				for(int j=0; j<ax_q3.stmt_text.size(); ++j){
					if(ax_q3.is_a_count_text[j]){
						//cout << "rci:" << rci << "cci:" << cci << endl;
						cout << counter[cci+rci*cols]<<",";
						++cci;
					}
				}
				++rci;
			}
		cout << endl;
		}
	}
} tab_q1_q3;
