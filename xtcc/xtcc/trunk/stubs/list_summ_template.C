#ifndef NxD_print_list_summ
#define NxD_print_list_summ

#include <map>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
template <class T> 
void print_list_summ(map <T,int> &m);
template <class T> 
void print_list_summ(map <T,int> &m, string var_name, string text){
	map <string,int> smap;
	ofstream file("lst_.csv", ios_base::out|ios_base::app);

	typedef typename map<T,int>::const_iterator CI;
	typedef map<string,int>::const_iterator SI;
	file << "===list count===" << " var_name: " << var_name << " : " << text << endl;
	file << "value,frequency" << endl;
	for( CI mi=m.begin(); mi!=m.end(); ++mi){
		file << mi->first << "," <<mi->second << endl;
	}
	file << "===END of list count===" << endl;
	file.close();
}

#endif /* NxD_print_list_summ */
