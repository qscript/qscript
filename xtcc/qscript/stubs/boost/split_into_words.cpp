
#include<iostream>
#include<boost/tokenizer.hpp>
#include<string>
#include<vector>

using namespace std;
using namespace boost;
vector <string> split_into_words(string s)
{
	vector <string> result;
	tokenizer<> tok(s);
	for(tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg) {
		result.push_back (*beg);
	}
	return result;
}

void print_vec (const vector<string>& vec)
{
	for (int i=0; i<vec.size(); ++i) {
		cout << "|" << vec[i] << "|" << endl;
	}
}

int main()
{
	string s = "This is,  a test";
	vector<string> res1 = split_into_words (s);
	print_vec (res1);
	std::string str = ";;Hello|world||-foo--bar;yow;baz|";
	vector<string> res2 = split_into_words (str);
	print_vec (res2);
}
