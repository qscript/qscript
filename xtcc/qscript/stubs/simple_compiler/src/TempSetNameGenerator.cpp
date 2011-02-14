#include "TempSetNameGenerator.h"
#include <sstream>

using std::stringstream;

TempSetNameGenerator::TempSetNameGenerator()
	: count(0)
{ }


std::string TempSetNameGenerator::GetNewTempXtccSetName()
{
	// ok - wtf was I thinking in this code? - this is disgusting
	// did my brain switch off or something - looks like the whole oper_in
	// code is just badddd
	/*
	// about a billion temporaries before we run out
	const int32_t max_temp = 10;
	char buffer[max_temp];
	char op_buf[max_temp];
	int32_t dividend = count;

	buffer[0] = '0'; buffer[1] = '\0';

	int32_t j = 0;
	do {
		int32_t rem = dividend%10;
		dividend = dividend/10;
		buffer[j++] = '0' + rem;
	} while (dividend>0);
	buffer[j] = '\0';
	for(int32_t i = j-1; i >= 0; --i){
		op_buf[j-1-i] = buffer[i];
	}
	op_buf[j] = '\0';
	string s(op_buf);
	*/
	++count;
	//cout << s << endl;
	stringstream s1;
	s1 << "temp_xtcc_set_" << count;
	//string s1 = "temp_xtcc_set_"+s;
	return s1.str();
}

std::string TempSetNameGenerator::GetCurrentTempXtccSetName()
{
	stringstream s1;
	s1 << "temp_xtcc_set_" << count;
	return s1.str();
}
