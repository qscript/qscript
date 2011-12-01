/*
 * =====================================================================================
 *
 *       Filename:  test_named_range_stub.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 01 December 2011 10:20:54  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "new_named_range.h"

int main()
{
	vector <AbstractNamedRange *> nr_vec;

	nr_vec.push_back (new NamedRangeStub("s1", 1));

	NamedRangeGroup grp_1("grp_1");
	grp_1.AddStub( " Kalyanam (Ratia Marg, Snagam Vihar, New Delhi)", 7, 1);
	grp_1.AddStub( " CASP Plan Project (Neem Chowk, Sangam Vihar, New Delhi)", 8, 2);
	grp_1.AddStub( " EFRAH (Aali Vihar, nr. Aali Village, New Delhi)", 9, 3);
	grp_1.AddStub( " Nav Srishti (Village neb Sarai, New Delhi)", 10, 4);
	nr_vec.push_back (&grp_1);
	nr_vec.push_back (new NamedRangeStub("s2", 2));

	for (int32_t i = 0; i< nr_vec.size(); ++i) {
		nr_vec[i]->Print();
	}

}
