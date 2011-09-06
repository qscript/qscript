/*
 * =====================================================================================
 *
 *       Filename:  find_lang_xml.cpp
 *
 *    Description:  find Wt xml files for language and create a drop down box
 *
 *        Version:  1.0
 *        Created:  Wednesday 07 September 2011 12:04:37  IST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Neil Xavier D'Souza
 *
 * =====================================================================================
 */

#include <dirent.h>
#include <string>
#include <cctype>
#include <iostream>

using namespace std;

string jno ("inp_simple_for");

int main()
{
	DIR * directory_ptr = opendir(".");

	struct dirent *directory_entry = readdir(directory_ptr);
	while (directory_entry) {
		string dir_entry_name(directory_entry->d_name);
		int len_entry = dir_entry_name.length();
		if (len_entry > 4 &&
				dir_entry_name[len_entry - 1] == 'l' &&
				dir_entry_name[len_entry - 2] == 'm' &&
				dir_entry_name[len_entry - 3] == 'x' &&
				dir_entry_name[len_entry - 4] == '.' ) {
			// the names we are looking for are of the form
			// jno + "[a-z][a-z].xml"
			bool is_our_file = true;
			if (len_entry != jno.length() + 7) {
				is_our_file = false;
				// the above doesnt matter actually, 
				// continue takes us back to the top
				goto read_another_entry;
			} else {
				// possibly what we are looking for
				//
				for (int i = 0; i < jno.length(); ++i) {
					if (!(jno[i] == dir_entry_name[i])) {
						// cannot be our data file
						is_our_file = false;
						goto read_another_entry;
					}
				}
				char first_letter = dir_entry_name[jno.length() + 1];
				if (! isalpha (first_letter)) {
					is_our_file = false;
					goto read_another_entry;
				}
				char second_letter = dir_entry_name[jno.length() + 2];
				if (! isalpha (second_letter)) {
					is_our_file = false;
					goto read_another_entry;
				}
				cout << "found an language traslation file: " 
					<< dir_entry_name << endl;
			}
		}
read_another_entry:
		directory_entry = readdir(directory_ptr);
	}
}
