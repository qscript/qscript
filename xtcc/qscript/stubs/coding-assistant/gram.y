/* Copyright Neil Xavier D'Souza
*/

%{


#include <inttypes.h>
#include <sys/types.h>
#include <limits.h>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include<boost/tokenizer.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <limits.h>
#include <regex.h>



#include "const_defs.h"
#include "person_info.h"

	extern int yylex();
	extern void yyerror(const char * s);
	using std::cout;
	using std::endl;
	using std::cerr;
	using std::stringstream;
	using std::map;
	using std::string;
	using std::vector;
	using std::set;
	set <string> negative_words_of_interest;
	vector <regex_t> regular_expressions_of_interest;

	std::string trim(const std::string& str,
			 const std::string& whitespace = " \t");

	vector <struct Info> info_vec;
	map <string, int> rm_name_code_map;
	map <string, int> recalled_name_freq;
	//int match_score(const string & s1, const string & s2,
	//	const  set <string> & negative_words_of_interest,
	//	string & addnl_info,
	//	string & verdict, int serial_no
	//	);


	struct Info 
	{
		int serial_no;
		int rm_code;
		string rm_name;
		string cust_ref_no;
		string call_status;
		string survey_agreement;
		string remember_name;
		string recalled_name;
		Info (
			int    p_serial_no,
			int    p_rm_code,
			string p_rm_name,
			string p_cust_ref_no,
			string p_call_status,
			string p_survey_agreement,
			string p_remember_name,
			string p_recalled_name
		):

			serial_no        (p_serial_no)         ,
			rm_code          (p_rm_code   )        ,
			rm_name          (p_rm_name    )       ,
			cust_ref_no      (p_cust_ref_no )      ,
			call_status      (p_call_status  )     ,
			survey_agreement (p_survey_agreement)  ,
			remember_name    (p_remember_name   )  ,
			recalled_name    (p_recalled_name   )
			{}
	};



%}

%union {
	int ival;
	double dval;
	char name[4095];
	char text_buf[4095];
}

%token <ival> INUMBER
%token <text_buf> TEXT
%token NEWL
%token COMMA
%token DOT

%%

chain: a_row
	| chain a_row {
		//cout << "chained a row" << endl;
	}
	;

a_row: INUMBER COMMA INUMBER COMMA 
	TEXT COMMA TEXT COMMA 
	TEXT COMMA TEXT COMMA 
	TEXT COMMA TEXT 
	NEWL {
		//cout << "got a row" << endl;
		//struct Info inf;
		int serial_no = $1;
		int rm_code = $3;
		string rm_name = boost::to_upper_copy(trim(string($5)));
		string cust_ref_no = $7;
		string call_status = $9;
		string survey_agreement = $11;
		string remember_name = $13;
		string recalled_name = boost::to_upper_copy(trim(string($15)));
		struct Info inf (serial_no, rm_code, rm_name, 
			cust_ref_no, call_status, survey_agreement, 
			remember_name, recalled_name);
		info_vec.push_back (inf);
		rm_name_code_map[$5]=$3;
		//if (recalled_name == rm_name) 
		#if 0
		if (recalled_name.length() > 0) {
			string addnl_info;
			string verdict;
			if (int score = match_score (recalled_name, rm_name, 
					negative_words_of_interest, addnl_info,
					verdict) ) {
				cout << verdict << ","
					//<< "ser_no, "
					<< serial_no << ", " 
					//<< ", rm_name, " 
					<< rm_name << ", "
					//<< ", recalled_name, "
					<< "\"" << recalled_name << "\"" << ","
					//<< ", score, " 
					<< score << ","
					<< addnl_info
					<< endl;
			} else {
				cout << "not matched," 
					//<< "  ser_no, "
					<< serial_no  << ", "
					//<< ", rm_name, " 
					<< rm_name <<", "
					//<< ", recalled_name, " 
					<< "\"" << recalled_name << "\"" << ","
					//<< ", score, " 
					<< 0 << ","
					<< addnl_info
					<< endl;
			}
		} else {
			cout << "impossible, "
				<< serial_no  << ", "
				<< rm_name <<", "
				<< "\"" << recalled_name << "\"" << ","
				<< 0 << ","
				<< "recalled_name is of length 0"
				<< endl;
		}
		#endif /* 0 */

	}
	;


%%

	extern void yyrestart(FILE *input_file);
	extern int32_t yyparse();
	int DebugFreqLexer ;


#include<iostream>
#include<boost/tokenizer.hpp>
#include<string>
#include<vector>

/*
struct Info 
{
	int serial_no;
	int rm_code;
	string rm_name;
	string cust_ref_no;
	string call_status;
	string survey_agreement;
	string remember_name;
	string recalled_name;
	Info (
		int    p_serial_no,
		int    p_rm_code,
		string p_rm_name,
		string p_cust_ref_no,
		string p_call_status,
		string p_survey_agreement,
		string p_remember_name,
		string p_recalled_name
	):

		serial_no        (p_serial_no)         ,
		rm_code          (p_rm_code   )        ,
		rm_name          (p_rm_name    )       ,
		cust_ref_no      (p_cust_ref_no )      ,
		call_status      (p_call_status  )     ,
		survey_agreement (p_survey_agreement)  ,
		remember_name    (p_remember_name   )  ,
		recalled_name    (p_recalled_name   )
};
*/

//vector <struct Info> info_vec;
//map <string, int> rm_names;
//map <string, int> recalled_name_freq;
using boost::multi_index_container;
using namespace boost::multi_index;

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

int has_negative_words_of_interest (string s2, const set<string> & negative_words_of_interest, string & addnl_info)
{
	int result = 0;
	//cout << "searching for negative_words_of_interest in " << s2 << endl;
	for (set<string>::iterator it=negative_words_of_interest.begin();
		it != negative_words_of_interest.end(); ++it) {
		string  neg_word = *it;
		if (s2.find (neg_word)!= string::npos) {
			addnl_info += ", |" + s2 + "| has word of interest: |" + neg_word + "|";
			++result ;
		}
	}
	return result;
}

struct regular_expression_scores {
	string human_pattern;
	long long score;
};

int match_regular_expressions_of_interest (const string & s, string & addnl_info)
{
	//cout << "match_reg" 
	//	<< ", " << s << ", regexp"
	//	<< "vector size:" << regular_expressions_of_interest.size()
	//	<< endl;
	int cumulative_score = 0; 
	for (int i=0; i<regular_expressions_of_interest.size(); ++i) {
		regmatch_t p_match[5];
		int n_match=5;
		regex_t a_regex = regular_expressions_of_interest[i];
		int regex_result = regexec (&a_regex, s.c_str(), n_match, p_match, 0);
		if (regex_result == 0) {
			//cout << __PRETTY_FUNCTION__ << " We have a match"
			//	<< endl;
			addnl_info += "matched with regexp";
			++cumulative_score;
		} else {
			//cout << __PRETTY_FUNCTION__ << " no match in vector pattern"
			//	<< endl;
		}
		//regex_t regex_dk;
		//regcomp (&regex_dk, "DON.*T KNOW", REG_ICASE);
		//regex_result = regexec (&regex_dk, s.c_str(), n_match, p_match, 0);
		//if (regex_result == 0) {
		//	cout << __PRETTY_FUNCTION__ << " We have a match AGAINST Hard coded"
		//		<< endl;
		//	++cumulative_score;
		//} else {
		//	cout << __PRETTY_FUNCTION__ << " NO MATCH AGAINST Hard coded: " << s
		//		<< endl;
		//}
	}
	//cout << "Exit: " << __PRETTY_FUNCTION__ << ", score, "  << cumulative_score << endl;
	return cumulative_score;
}

// This code is from stack overflow
// http://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
std::string trim(const std::string& str,
                 const std::string& whitespace /*= " \t"*/)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string reduce(const std::string& str,
                   const std::string& fill = " ",
                   const std::string& whitespace = " \t")
{
    // trim first
    auto result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}

vector <string> split_into_words(string s)
{
	vector <string> result;
	boost::tokenizer<> tok(s);
	for(boost::tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg) {
		result.push_back (*beg);
	}
	return result;
}


int check_for_groups_of_single_word_match_in_same_name(const vector<string> & bank_rm_name_vec, const vector<string> & recalled_name_vec, int serial_no, string & addnl_info)
{
	//cout << "bank_rm_name_vec.size():" << bank_rm_name_vec.size() << endl;
	//cout << "bank_rm_name_vec.size():" << bank_rm_name_vec.size() << endl;
	int score = 0;
	for (int i=0; i<recalled_name_vec.size(); ++i) {
		string recalled_name = recalled_name_vec[i];
		for (int j=0; j< bank_rm_name_vec.size(); ++j) {
			if (recalled_name == bank_rm_name_vec[j]) {
				++score;
				stringstream ss1;
				ss1 << "match:" << recalled_name 
					<< ", " << bank_rm_name_vec[j] 
					<< "," << serial_no;
				addnl_info += ss1.str();
			}
		}
	}
	return score;
}


int check_for_alternate_rm_exact_match (const string & recalled_name, string & addnl_info, int serial_no)
{
	int score = 0;
	//if (serial_no == 1178) {
	//	cout << "serial of interest: strstr should fire" << endl;
	//}
	//if (strstr (recalled_name.c_str(), "MARYAM SHIRAZI")) {
	//	cout << __PRETTY_FUNCTION__ << "target acquired" 
	//		<< ",serial_no," << serial_no
	//		<< endl;
	//}
	map<string, int>::iterator it = rm_name_code_map.find(recalled_name);
	if (it == rm_name_code_map.end()) {
	} else {
		//verdict += ":matched other rm";
		stringstream ss1;
		ss1 << ",other rm name," << it->first 
			<< ",other rm code," << it->second;
		addnl_info += ss1.str();
		score = 1;
	}
	return score;
}

typedef person_info_set::index<first_name>::type person_by_first_name;
typedef person_info_set::index<last_name>::type person_by_last_name;

int  check_for_alternate_rm_word_match (string recalled_name, string & addnl_info,
	int serial_no, const person_info_set & pinf_set)
{
	int score = 0;
	vector <string> recalled_name_split = split_into_words (recalled_name);
	for (int i=0; i<recalled_name_split.size(); ++i) {
		//const string & f_name = name_split[0];
		//const string & l_name = name_split[name_split.size()-1];
		const string & possible_name = recalled_name_split[i];
		person_by_first_name::iterator it_find_fn = pinf_set.get<first_name>().find(possible_name);
		person_by_last_name::iterator  it_find_ln = pinf_set.get<last_name>().find(possible_name);
		if (it_find_fn != pinf_set.get<first_name>().end() ) {
			stringstream ss1;
			ss1 << "check_for_alternate_rm_word_match: got a word match on ,"
				<< "possible_name," << possible_name
				<< "," << it_find_fn->first_name
				<< "," << it_find_fn->last_name
				<< "," << it_find_fn->rm_code
				;
			addnl_info += ss1.str();
			++score;
		}
		if (it_find_ln != pinf_set.get<last_name>().end() ) {
			stringstream ss1;
			ss1 << "check_for_alternate_rm_word_match: got a word match on ,"
				<< "possible_name," << possible_name
				<< "," << it_find_ln->last_name
				<< "," << it_find_ln->last_name
				<< "," << it_find_ln->rm_code
				;
			addnl_info += ss1.str();
			++score;
		}
	}
	return score;
}

// return a score on the match
int match_score(const string & recalled_name, const string & bank_provided_rm_name,
	const  set <string> & negative_words_of_interest,
	string & addnl_info,
	string & verdict,
	int serial_no,
	const person_info_set & pinf_set
	)
{
	
	int score = 0;
	if (recalled_name == bank_provided_rm_name) {
		verdict = "matched";
		score =  INT_MAX;
	} else if (bank_provided_rm_name.find (recalled_name) != string :: npos) {
		verdict = "partial match";
		score =  100;
	} else {
		verdict = "heuristic";
		score += has_negative_words_of_interest (recalled_name, negative_words_of_interest, addnl_info);
		//score += has_negative_words_of_interest (bank_provided_rm_name, negative_words_of_interest, addnl_info);
		int regex_score = 0;
		if (score == 0) {
			regex_score = match_regular_expressions_of_interest (recalled_name, addnl_info);
			if (regex_score) {
				verdict += ":regex";
			}
		}
		score += regex_score;
	}

	// check for single word match of first_name or last_name in the same bank provided rm name
	if (score == 0) {
		vector<string> bank_provided_rm_name_split = split_into_words(bank_provided_rm_name);
		//print_vec (res1);
		vector <string> recalled_name_split = split_into_words (recalled_name);
		int word_match_score = 
			check_for_groups_of_single_word_match_in_same_name(bank_provided_rm_name_split, recalled_name_split, serial_no, addnl_info);
		if (word_match_score > 0) {
			verdict += ":matched same name single word";
			score += word_match_score;
		}
	}

	// check for exact match of alternate rm in 
	if (score == 0) {
		//map<string, int>::iterator it = rm_name_code_map.find(recalled_name);
		//if (it == rm_name_code_map.end()) {
		//} else {
		//	verdict += ":matched other rm";
		//	stringstream ss1;
		//	ss1 << ",other rm name," << it->first 
		//		<< ",other rm code," << it->second;
		//	addnl_info += ss1.str();
		//}
		int alt_rm_score  = check_for_alternate_rm_exact_match (recalled_name, addnl_info, serial_no);
		if (alt_rm_score) {
			verdict += ":matched other rm";
			score += alt_rm_score;
		}
	}

	// check for word match of first_name or last_name in alternate rm name
	if (score == 0) {
		int alt_rm_score  = check_for_alternate_rm_word_match (recalled_name, addnl_info, serial_no, pinf_set);
		if (alt_rm_score) {
			verdict += ":word match other rm";
			score += alt_rm_score;
		}
	}


	return score;
}

using std::set;

// has side effects - bad programming

vector <string> human_readable_regex_pattern;

void populate_regular_expressions_of_interest()
{
	{
		regex_t regex_dk;
		string pattern = "DON.\\{1,6\\}T KNOW";
		human_readable_regex_pattern.push_back(pattern);
		regcomp (&regex_dk, pattern.c_str(), REG_ICASE);
		regular_expressions_of_interest.push_back (regex_dk);
	}
	{
		regex_t regex_dk;
		string pattern = "DON.\\{1,6\\}T RECALL";
		human_readable_regex_pattern.push_back(pattern);
		regcomp (&regex_dk, pattern.c_str(), REG_ICASE);
		regular_expressions_of_interest.push_back (regex_dk);
	}
	{
		regex_t regex_dk;
		string pattern = "DON.\\{1,6\\}T RECALL";
		human_readable_regex_pattern.push_back(pattern);
		regcomp (&regex_dk, pattern.c_str(), REG_ICASE);
		regular_expressions_of_interest.push_back (regex_dk);
	}
	{
		regex_t regex_dk;
		string pattern = "DON.\\{1,6\\}T KNW";
		human_readable_regex_pattern.push_back(pattern);
		regcomp (&regex_dk, pattern.c_str(), REG_ICASE);
		regular_expressions_of_interest.push_back (regex_dk);
	}
	{
		regex_t regex_dk;
		string pattern = "DOESN.\\{1,6\\}T KNOW";
		human_readable_regex_pattern.push_back(pattern);
		regcomp (&regex_dk, pattern.c_str(), REG_ICASE);
		regular_expressions_of_interest.push_back (regex_dk);
	}
	{
		regex_t regex_dk;
		string pattern = "DON.\\{1,6\\}T REMEMBER";
		human_readable_regex_pattern.push_back(pattern);
		regcomp (&regex_dk, pattern.c_str(), REG_ICASE);
		regular_expressions_of_interest.push_back (regex_dk);
	}
	{
		regex_t regex_dk;
		string pattern = "NOT \\+AWARE";
		human_readable_regex_pattern.push_back(pattern);
		regcomp (&regex_dk, pattern.c_str(), REG_ICASE);
		regular_expressions_of_interest.push_back (regex_dk);
	}

}

// has side effects - bad programming
void populate_negative_words_of_interest()
{
	negative_words_of_interest.insert("DON'T KNW");
	negative_words_of_interest.insert("DON'T KNOW");
	negative_words_of_interest.insert("DON'T RECALL");
	negative_words_of_interest.insert("DO NOT REMEMBER");
	negative_words_of_interest.insert("CAN'T REMEMBER");
	negative_words_of_interest.insert("CAN NOT REMEMBER");
	negative_words_of_interest.insert("DON'T REMEMBER");
	negative_words_of_interest.insert("DO NOT KNOW");
	negative_words_of_interest.insert("NOT AWARE");
	negative_words_of_interest.insert("DO NOT RECOLLECT");
	negative_words_of_interest.insert("NO IDEA");
	negative_words_of_interest.insert("CANT REMEMBER");
	negative_words_of_interest.insert("DID NOT KNOW");
	negative_words_of_interest.insert("DOES NOT KNOW");
	negative_words_of_interest.insert("DOESN'T KNOW");
	negative_words_of_interest.insert("NOT SURE");
}

void insert_into_multi_index (person_info_set & pinf_set, vector<string> &name_data, int rm_code)
{
	if (name_data.size()>= 2) {
		pinf_set.insert ( PersonInfo(name_data[0], name_data[name_data.size()-1], rm_code));
	} else {
		cout << "illegal name - should atleast have 1st and last name"
			<< endl;
	}
}

void populate_person_info_set (person_info_set & pinf_set)
{
	for (int i=0; i< info_vec.size(); ++i) {
		const Info &inf = info_vec[i];
		vector <string> name_split = split_into_words(inf.rm_name);
		if (name_split.size() >= 2) {
			const string & f_name = name_split[0];
			const string & l_name = name_split[name_split.size()-1];
			person_by_first_name::iterator it_find_fn = pinf_set.get<first_name>().find(f_name);
			person_by_last_name::iterator it_find_ln = pinf_set.get<last_name>().find(l_name);
			if (it_find_fn == pinf_set.get<first_name>().end() && 
				it_find_ln == pinf_set.get<last_name>().end()
			) {
				insert_into_multi_index (pinf_set, name_split, inf.rm_code);
				cout << "added RM: ,fn," << f_name << ", ln," << l_name 
					<< ",rm_code," << inf.rm_code
					<< endl;
			/*} else if (it_find_fn->last_name !=  l_name) {
				insert_into_multi_index (pinf_set, name_split, inf.rm_code);
				cout << "added RM| same fn different ln," << f_name << ", ln," << l_name
					<< "," << it_find_fn->first_name << "," << it_find_fn->last_name
					<< endl;
				*/
			} else  {
				//person_by_last_name::iterator it_find_ln = pinf_set.get<last_name>().find(l_name);
				//person_by_first_name::iterator it_find_by_rm = pinf_set.get<rm_code>().find(l_name);
				//if (it_find_ln == pinf_set<it_find_ln>().end()) {
				//	cout << "already present RM: fn" << f_name << ", ln" << l_name << endl;
				//}
				//cout << "already present RM: fn," << f_name << ", ln," << l_name << endl;
				//cout << it_find_fn->first_name << "," << it_find_fn->last_name << endl;
				if ( 
					it_find_fn->first_name == f_name && it_find_fn->last_name == l_name
					&& (  it_find_fn->rm_code != inf.rm_code)
				) {
					cout << "PROBLEM: Bank provided rm_code is not consistent:" 
						<< it_find_fn->rm_code << ", " << inf.rm_code
						<< endl
						;
				} else if (
					it_find_ln->first_name == f_name && it_find_ln->last_name == l_name
					&& (  it_find_ln->rm_code != inf.rm_code)
				) {
					cout << "PROBLEM: Bank provided rm_code is not consistent:" 
						<< it_find_fn->rm_code << ", " << inf.rm_code
						<< endl
						;
				} else {
					//cout << "IMPOSSIBLE: this should never happen" << endl;
				}
			}
		}
	}
}

void do_match(const person_info_set & pinf_set)
{
	for (int i=0; i< info_vec.size(); ++i) {
		string recalled_name = info_vec[i].recalled_name;
		string rm_name = info_vec[i].rm_name;
		int serial_no = info_vec[i].serial_no;
		if (recalled_name.length() > 0) {
			string addnl_info;
			string verdict;
			if (int score = match_score (recalled_name, rm_name, 
					negative_words_of_interest, addnl_info,
					verdict, serial_no, pinf_set) ) {
				cout << verdict << ","
					//<< "ser_no, "
					<< serial_no << ", " 
					//<< ", rm_name, " 
					<< rm_name << ", "
					//<< ", recalled_name, "
					<< "\"" << recalled_name << "\"" << ","
					//<< ", score, " 
					<< score << ","
					<< addnl_info
					<< endl;
			} else {
				cout << "not matched," 
					//<< "  ser_no, "
					<< serial_no  << ", "
					//<< ", rm_name, " 
					<< rm_name <<", "
					//<< ", recalled_name, " 
					<< "\"" << recalled_name << "\"" << ","
					//<< ", score, " 
					<< 0 << ","
					<< addnl_info
					<< endl;
			}
		} else {
			cout << "impossible, "
				<< serial_no  << ", "
				<< rm_name <<", "
				<< "\"" << recalled_name << "\"" << ","
				<< 0 << ","
				<< "recalled_name is of length 0"
				<< endl;
		}
	}
}

int main()
{
	string s1 = "  thre is leading space here ";
	string s2 = trim (s1);
	//cout << "trimmed s1" << endl;
	std::string fname ("s2b-data_v4_1.csv");
	DebugFreqLexer = 1;
	FILE * yyin = fopen(fname.c_str(), "rb");
	if (!yyin){
		cerr << " Unable to open: " << fname << " for read ... exiting" << endl;
		exit(1);
	}

	populate_negative_words_of_interest();
	populate_regular_expressions_of_interest();
	yyrestart(yyin);
	cout << "result, serno, rm_name, recalled_name, score" << endl;
	if (!yyparse()) {
		//cout << "Input parsed successfully" << endl;
		person_info_set pinf_set;
		populate_person_info_set(pinf_set);
		do_match(pinf_set);
	} else {
		cout << "Error parsing input" << endl;
	}
	
}

