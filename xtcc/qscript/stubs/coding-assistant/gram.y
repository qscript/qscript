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
#include <limits.h>
#include <regex.h>

#include "const_defs.h"

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
	int match_score(const string & s1, const string & s2,
		const  set <string> & negative_words_of_interest,
		string & addnl_info,
		string & verdict, int serial_no
		);


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

int check_for_alternate_rm (const string & recalled_name, string & addnl_info, int serial_no)
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


// return a score on the match
int match_score(const string & recalled_name, const string & s2,
	const  set <string> & negative_words_of_interest,
	string & addnl_info,
	string & verdict,
	int serial_no
	)
{
	
	int score = 0;
	if (recalled_name == s2) {
		verdict = "matched";
		score =  INT_MAX;
	} else if (s2.find (recalled_name) != string :: npos) {
		verdict = "partial match";
		score =  100;
	} else {
		verdict = "heuristic";
		score += has_negative_words_of_interest (recalled_name, negative_words_of_interest, addnl_info);
		//score += has_negative_words_of_interest (s2, negative_words_of_interest, addnl_info);
		int regex_score = 0;
		if (score == 0) {
			regex_score = match_regular_expressions_of_interest (recalled_name, addnl_info);
			if (regex_score) {
				verdict += ":regex";
			}
		}
		score += regex_score;
	}

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
		int alt_rm_score  = check_for_alternate_rm (recalled_name, addnl_info, serial_no);
		if (alt_rm_score) {
			verdict += ":matched other rm";
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

void do_match()
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
					verdict, serial_no) ) {
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
	cout << "trimmed s1" << endl;
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
		do_match();
	} else {
		cout << "Error parsing input" << endl;
	}
	
}


