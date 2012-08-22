/*
 * =====================================================================================
 *
 *       Filename:  char_star_array_args.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Tuesday 07 August 2012 02:34:13  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct AStruct {
	vector <string> vec_str;
	AStruct (char * txt_ptrs[])
		/* : vec_str (sizeof(txt_ptrs)/sizeof(txt_ptrs[0])) */
	{
		//cout << "sizeof(txt_ptrs):"  << sizeof(txt_ptrs) << endl;
		//cout << "(sizeof(txt_ptrs)/sizeof(txt_ptrs[0])): "
		//	<< (sizeof(txt_ptrs)/sizeof(txt_ptrs[0]))
		//	<< endl;
		//for (int i=0; i<vec_str.size(); ++i) {
		//	vec_str[i] = string (txt_ptrs[i]);
		//}
		int i=0;
		for (char ** a_ptr = txt_ptrs; *a_ptr != (char *) 0; ++a_ptr, ++i) {
			cerr << "a_ptr: " << a_ptr << endl;
			cerr << i << endl;
			vec_str.push_back (string(*a_ptr));
			cout << *a_ptr << endl;
		}
	}

	void print()
	{
		for (int i=0; i < vec_str.size(); ++i) {
			cout << vec_str[i] << endl;
		}
	}
};

int main()
{
	char * txt_ptrs[] = { "This is some text",
				"This is some more text",
				"Even more text",
				(char *) 0};

	AStruct a_struct(txt_ptrs);
	a_struct.print();
}
