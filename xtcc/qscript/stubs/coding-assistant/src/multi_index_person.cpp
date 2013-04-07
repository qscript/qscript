#include <iostream>
#include <string>
#include <vector>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>

#include<boost/tokenizer.hpp>
#include "person_info.h"

using boost::multi_index_container;
using namespace boost::multi_index;

using std::vector;
using std::string;



typedef multi_index_container<
  PersonInfo,
  indexed_by<
    ordered_non_unique<
      tag<first_name>,  BOOST_MULTI_INDEX_MEMBER(PersonInfo,std::string,first_name)>,
    ordered_non_unique<
      tag<last_name>,BOOST_MULTI_INDEX_MEMBER(PersonInfo,std::string,last_name)>,
    ordered_unique<
      tag<rm_code>, BOOST_MULTI_INDEX_MEMBER(PersonInfo,int,rm_code)> >
> person_info_set;


vector <string> split_into_words(string s)
{
	vector <string> result;
	boost::tokenizer<> tok(s);
	for(boost::tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg) {
		result.push_back (*beg);
	}
	return result;
}


template<typename Tag,typename MultiIndexContainer>
void print_out_by(
 const MultiIndexContainer& s,
 Tag* =0 /* fixes a MSVC++ 6.0 bug with implicit template function parms */
)
{
  /* obtain a reference to the index tagged by Tag */

  const typename boost::multi_index::index<MultiIndexContainer,Tag>::type& i=
    get<Tag>(s);

  typedef typename MultiIndexContainer::value_type value_type;

  /* dump the elements of the index to cout */

  std::copy(i.begin(),i.end(),std::ostream_iterator<value_type>(std::cout));
}

	using  std::cout;
	using  std::endl;

void print_vec (const vector<string>& vec)
{
	for (int i=0; i<vec.size(); ++i) {
		cout << "|" << vec[i] << "|" << endl;
	}
}

void insert_into_multi_index (person_info_set & pf_set, vector<string> &name_data)
{
	static int id=0;
	if (name_data.size()>= 2) {
		pf_set.insert ( PersonInfo(name_data[0], name_data[1], ++id));
	} else {
		cout << "illegal name - should atleast have 1st and last name"
			<< endl;
	}
}

int check_for_partial_match_in_same_name(const vector<string> & bank_rm_name_vec, const vector<string> & recalled_name_vec)
{
	cout << "bank_rm_name_vec.size():" << bank_rm_name_vec.size() << endl;
	cout << "bank_rm_name_vec.size():" << bank_rm_name_vec.size() << endl;
	int score = 0;
	for (int i=0; i<recalled_name_vec.size(); ++i) {
		string recalled_name = recalled_name_vec[i];
		for (int j=0; j< bank_rm_name_vec.size(); ++j) {
			if (recalled_name == bank_rm_name_vec[j]) {
				cout << "match:" << recalled_name << ", " << bank_rm_name_vec[j];
				++score;
			}
		}
	}
	return score;
}

int main()
{
	person_info_set pf_set;
	string name1 = "NEIL XAVIER D'SOUZA";
	vector<string> res1 = split_into_words(name1);
	print_vec (res1);
	//pf_set.insert (PersonInfo("Neil", "D'Souza", 1));
	insert_into_multi_index (pf_set, res1);
	string test_data_1 = "NEIL XAVIER D'SOUZA";


	string name2 = "SHIVKUMAR ROHIRA";
	vector<string> res2 = split_into_words(name2);
	print_vec (res2);
	insert_into_multi_index (pf_set, res2);
	string test_data_2 = "SHIV KUMAR ROHIRA";

	string name3 = "SUMEET MISHRA";
	vector<string> res3 = split_into_words(name3);
	string test_data_3 = "SUMITH MISHRA";
	insert_into_multi_index (pf_set, res3);


 	string name4 = "SARA WAHDAN";
	vector<string> res4 = split_into_words(name4);
	insert_into_multi_index (pf_set, res4);
	string test_data_4="SARA WAHDAN JUST TODAY HE MET HER";

	typedef person_info_set::index<first_name>::type person_by_first_name;
	//employee_set_by_name::iterator it=es.get<name>().find("Veronica Cruz");
	//person_by_first_name::iterator it = pf_set.get<first_name>().find("Neil");
	person_by_first_name::iterator it = pf_set.get<first_name>().find("Atul");
	if (it != pf_set.get<first_name>().end()) {
		cout << it->first_name << endl;
	}

	{
		vector <string> test_data_1_res = split_into_words(test_data_1);
		cout << "score:" << check_for_partial_match_in_same_name(res1, test_data_1_res) << endl;
	}
	{
		vector <string> test_data_res = split_into_words(test_data_2);
		cout << "score:" << check_for_partial_match_in_same_name(res2, test_data_res) << endl;
	}
	{
		vector <string> test_data_res = split_into_words(test_data_3);
		cout << "score:" << check_for_partial_match_in_same_name(res3, test_data_res) << endl;
	}
	{
		vector <string> test_data_res = split_into_words(test_data_4);
		cout << "score:" << check_for_partial_match_in_same_name(res4, test_data_res) << endl;
	}
}

