#ifndef NxD_print_list_summ
#define NxD_print_list_summ

#include <map>
#include <iostream>
#include <string>
using namespace std;
template <class T> 
void print_list_summ(map <T,int> &m);
template <class T> 
void print_list_summ(map <T,int> &m){
	map <string,int> smap;

	typedef typename map<T,int>::const_iterator CI;
	typedef map<string,int>::const_iterator SI;
	cout << "============list count===========" << endl;
	for( CI mi=m.begin(); mi!=m.end(); ++mi){
		cout << mi->first << "," <<mi->second << endl;
	}
	cout << "=========== END of list count ========" << endl;
}

#endif /* NxD_print_list_summ */
