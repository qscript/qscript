/*
 * =====================================================================================
 *
 *       Filename:  XtccDataFile.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Tuesday 24 July 2012 04:18:45  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Neil Xavier DSouza
 *        Company:  
 *
 * =====================================================================================
 */

#include <fstream>
#include <iostream>
#include "XtccDataFile.h"


using namespace std;

bool is_a_rating_scale_stublist (string & range_name, int & op_rat_scale,
		bool & op_flag_scale_is_reversed)
{
	//string range_name = n_q->nr_ptr->name;
	int rat_scale = 0;
	int factor = 1;
	bool flag_scale_is_reversed = false;
	bool flag_is_a_rating_scale = false;
	if (isdigit(range_name[range_name.size()-1]) /*&& !(range_name[range_name.size()-1]=='0')*/ ) {
		flag_is_a_rating_scale = true;
		int i = range_name.size()-1;
		while (isdigit(range_name[i])) {
			rat_scale += (range_name[i] - '0') * factor;
			factor *=10;
			--i;
		}
		op_rat_scale = rat_scale;
		if (range_name[i] == 'r' && range_name[i-1] == '_') {
			flag_scale_is_reversed = true;
		}
		op_flag_scale_is_reversed = flag_scale_is_reversed;
	}
	return flag_is_a_rating_scale;
}


void print_simple_include_file (NamedStubQuestion *nq, string setup_dir)
{
	string inc_file_name (setup_dir + nq->nr_ptr->name);
	if (nq->no_mpn == 1) {
		inc_file_name += ".sin";
	} else {
		inc_file_name += ".min";
	}
	fstream inc_file (inc_file_name.c_str(), std::ios_base::out | std::ios_base::ate);

	for (int i=0; i<nq->nr_ptr->stubs.size(); ++i) {
		inc_file << "cnt; " << "\""
			<< nq->nr_ptr->stubs[i].stub_text
			<< "\""
			<< "; c=";
		if (nq->no_mpn==1) { 
			inc_file 
				<< " $var1; " 
				<< " == "
				<< nq->nr_ptr->stubs[i].code 
				<< ";" 
				<< endl;
		} else {
			inc_file 
				<< " $var1; " 
				<< "["
				<< nq->nr_ptr->stubs[i].code 
				<< "]"
				<< " > 0"
				<< ";" 
				<< endl;
		}
	}
}

void XtccDataFileDiskMap::print_xtcc_include_file (fstream & xtcc_ax_file, string setup_dir)
{
	static set<string, less<string> > set_include_file;

	if (NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion*>(q_)) {
		string inc_file_name(setup_dir + nq->nr_ptr->name);
		if (nq->no_mpn == 1) {
			inc_file_name += ".sin";
		} else {
			inc_file_name += ".min";
		}
		if (set_include_file.find (inc_file_name) != set_include_file.end()) {
		} else {
			string range_name = nq->nr_ptr->name;
			bool flag_is_a_rating_scale, flag_scale_is_reversed;
			int rat_scale;
			flag_is_a_rating_scale = is_a_rating_scale_stublist ( range_name, 
					rat_scale, flag_scale_is_reversed);
			if (flag_is_a_rating_scale == false) {
				print_simple_include_file (nq, setup_dir);
#if 0
				for (int i=0; i<nq->nr_ptr->stubs.size(); ++i) {
					inc_file << "cnt; " << "\""
						<< nq->nr_ptr->stubs[i].stub_text
						<< "\""
						<< "; c=";
					if (nq->no_mpn==1) { 
						inc_file 
							// << "_data"
							<< " $var1; " 
							<< " == "
							<< nq->nr_ptr->stubs[i].code 
							<< ";" 
							<< endl;
					} else {
						inc_file 
							// << "_arr["
							//<< nq->nr_ptr->stubs[i].code 
							//<< "]"
							<< " $var1; " 
							<< "["
							<< nq->nr_ptr->stubs[i].code 
							<< "]"
							<< " > 0"
							<< ";" 
							<< endl;
					}
				}
#endif /* 0 */
			} else {
				print_simple_include_file (nq, setup_dir);
				fstream inc_file (inc_file_name.c_str(), std::ios_base::out | std::ios_base::app);
				if (rat_scale == 5) {
					inc_file 
						<< "cnt; \"Top 2 Box (Net)\"; c="
						<< " $var1; == 5 || $var1; == 4;"  
						<< endl
						<< "cnt; \"Bottom 2 Box (Net)\"; c="
						<< " $var1; == 1 || $var1; == 2;"  
						<< endl
						<< "inc; $var1; ;c="
						<< " $var1; >= 1 && $var1; <= 5;"
						<< endl;
				} else if (rat_scale == 7) {
					inc_file 
						<< "cnt; \"Top 2 Box (Net)\"; c="
						<< " $var1; == 7 || $var1; == 6;"  
						<< endl
						<< "cnt; \"Top 3 Box (Net)\"; c="
						<< " $var1; == 7 || $var1; == 6 || $var1; == 5;"  
						<< endl
						<< "cnt; \"Bottom 2 Box (Net)\"; c="
						<< " $var1; == 1 || $var1; == 2;"  
						<< endl
						<< "cnt; \"Bottom 3 Box (Net)\"; c="
						<< " $var1; == 1 || $var1; == 2 || $var1; == 3;"  
						<< endl
						<< "inc; $var1; ;c="
						<< " $var1; >= 1 && $var1; <= 7;"
						<< endl;
				} else if (rat_scale == 10) {
					inc_file 
						<< "cnt; \"Top 2 Box (Net)\"; c="
						<< " $var1; == 10 || $var1; == 9;"  
						<< endl
						<< "cnt; \"Top 3 Box (Net)\"; c="
						<< " $var1; == 10 || $var1; == 9 || $var1; == 8;"  
						<< endl
						<< "cnt; \"Bottom 2 Box (Net)\"; c="
						<< " $var1; == 1 || $var1; == 2;"  
						<< endl
						<< "cnt; \"Bottom 3 Box (Net)\"; c="
						<< " $var1; == 1 || $var1; == 2 || $var1; == 3;" 
						<< endl
						<< "inc; $var1; ;c="
						<< " $var1; >= 1 && $var1; <= 10;"
						<< endl;
				}
			}
			set_include_file.insert(inc_file_name);
		}
	}
}
