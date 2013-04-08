// CopyRight Neil Xavier DSouza
// GNU GPL V2
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <regex.h>
#include "util.h"

using namespace std;
map <string, int> word_freq_count;

	set <string> negative_words_of_interest;
	set <string> positive_words_of_interest, neutral_words_of_interest;
	set <string> other_words_of_interest;
	set <string> emphasizer_words_of_interest;
	set <string> negative_phrase_of_interest;
	set <string> positive_phrase_of_interest;
	set <string> neutral_phrase_of_interest;
	set <string> words_indicating_reason;
	set <string> words_having_pwrm_rm_cm;
	set <string> words_indicating_management;
	vector <regex_t> regular_expressions_of_interest;
	vector <string> human_readable_regex_pattern;

	/*
struct RValueReadALine
{
	bool success;
	string a_line;
	RValueReadALine (): success (false), a_line()
	{ }
};

struct LineProvider
{
	ifstream file;
	LineProvider(string s): file(s.c_str())
	{
		cout << "got file to open: " << s << endl;
		if (file) {
			//string a_line;
			//bool could_read = getline(file, a_line);
			//cout << "read: " << a_line << endl;
		} else {
			cerr <<  "Unable to open file: " << s << " ... exiting" << endl;
			exit(1);
		}
	}
	RValueReadALine get_a_line()
	{
		RValueReadALine r_value;
		string a_line;
		if (std::getline(file,a_line)) {
			r_value.success = true;
			r_value.a_line = boost::to_upper_copy(trim(a_line));
		} else {
			cout << "could_read false" << endl;
		}
		//if (file) {
		//	bool could_read = getline(file, a_line);
		//}
		//if (could_read) {
		//	r_value.success = true;
		//	r_value.a_line = a_line;
		//} else {
		//	cout << "could_read false" << endl;
		//}
		return r_value;
	}
};
*/

	using namespace std;
void process_file (std::ifstream & data_file)
{
	string a_line;
	while (std::getline(data_file, a_line)) {
		cout << "got line: " << a_line << endl;
	}
}

/*
 typedef boost::tokenizer<boost::char_separator<char> >
	tokenizer;
vector<string> tokenize_csv_components_into_fields(string &a_csv_line)
{
	using namespace boost;
	boost::tokenizer<escaped_list_separator<char> > tok(a_csv_line);
	vector<string> res;
	for(boost::tokenizer<escaped_list_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg){
		//cout << *beg << "\n";
		res.push_back(*beg);
	}
	return res;
}

vector<string> tokenize_into_sentences(const string &s)
{
	//boost::char_separator<char> sep("-;|");
	//
	vector<string> sentences;
	boost::char_separator<char> sep("./");
	tokenizer tokens(s, sep);
	for (tokenizer::iterator tok_iter = tokens.begin();
		tok_iter != tokens.end(); ++tok_iter) {
		//std::cout << "<" << *tok_iter << "> ";
		sentences.push_back(*tok_iter);
	}
	return sentences;
}


vector<string> split_into_words(const string &s)
{
	vector<string> words;
	typedef boost::tokenizer<boost::char_separator<char> > Tok;
	boost::char_separator<char> sep; // default constructed
	Tok tok(s, sep);
	cout << "Word split: " << endl;
	for(Tok::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter) {
		std::cout << "|" << *tok_iter << "| ";
		words.push_back(*tok_iter);
	}
	std::cout << "\n";
	return words;
	//return EXIT_SUCCESS;
}

vector<string> split_into_phrases(const string &s)
{
	boost::char_separator<char> sep(",");
	vector<string> phrases;
	tokenizer tokens(s, sep);
	for (tokenizer::iterator tok_iter = tokens.begin();
		tok_iter != tokens.end(); ++tok_iter) {
		//std::cout << "<" << *tok_iter << "> ";
		phrases.push_back(*tok_iter);
	}
	return phrases;
}

*/

int check_for_phrase_of_interest(const set<string> & phrase_of_interest, string & user_phrase)
{
	int result = 0;
	for (auto it = phrase_of_interest.begin(); it != phrase_of_interest.end();
			++it) {
		string  a_phrase_of_interest = *it;
		if (user_phrase.find (a_phrase_of_interest)!= string::npos) {
			//addnl_info += ": |" + s2 + "| has word of interest: |" + neg_word + "|";
			++result;
		}
	}
	return result * 100;
}

// few tweaks to the metric in this function
// we want the prefix of the word to have
// the highest influence on the score
// and the suffix to have the lowest influence
long long compute_string_score (const string & s)
{
	cout << __PRETTY_FUNCTION__ << " :s:" << s<< endl;
	long long score = 0;
	//for (int i=0; i<s.size(); ++i)
	//
	//long long base =  1;
	//for (int i=s.size()-1; i >= 0; --i)
	for (int i=0; i<s.size(); ++i) {
		if ((s[i] >= 'A') && (s[i] <= 'Z')) {
			// The highest score for a letter is 26
			// add to that digits from 0 to 9 and we have 36
			//cout << "letter :" << s[i] << ", score:" << (s[i] - 'A' +10)
				//<< "base: " << base
				//<< endl;
			//if (i==0) {
			//	score += (s[i] - 'A' + 10) + 0;
			//} else {
			//	score += (s[i] - 'A' + 10) * base;
			//}
			score = (s[i] - 'A' + 10) + score * 36;
			//base *= 36;
			//cout << "partial score: " << score << endl;
		}
	}
	return score;
}


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

long long check_for_words_of_interest(const set<string> & words_of_interest, vector<string> phrase_in_words)
{
	long long score = 0;
	for (int i=0; i<phrase_in_words.size(); ++i) {
		const string & a_word = phrase_in_words[i];
		auto found = words_of_interest.find (a_word);
		if (found != words_of_interest.end()) {
			//++score;
			score += compute_string_score(a_word);
		}
	}
	return score * 1;
}

long long check_for_emphasizer_phrase(const set<string> & emphasizers, const set<string> & adjectives
		,  const string & phrase)
{
	long long score = 0;
	for (auto it1 = emphasizers.begin(); it1 != emphasizers.end(); ++it1) {
		for (auto it2 = adjectives.begin(); it2 != adjectives.end(); ++it2) {
			string a_possible_phrase = *it1 + " " + *it2;
			if (phrase.find(a_possible_phrase) != string::npos) {
				//++score;
				score += compute_string_score(phrase);
			}
		}
	}
	return score * 10000;
}

void analyze_further(const string & verbatim)
{
	ofstream phrase_scores("phrase_scores.csv", ios_base::app);
	static bool once = true;
	if (once) {
		phrase_scores
			<< "any_cls" << ","
			<< "ps_emphr" << ","
			<< "ng_emphr" << ","
			<< "ps_ph" << ","
			<< "ng_ph" << ","
			<< "ps_wd" << ","
			<< "ng_wd" << ","
			<< "neu_wd" << ","
			<< "oth_wd" << ","
			<< "emph_wd" << ","
			<< "mngmt_wd" << ","
			<< "pwrm_wd" << ","
			<< "reasn_wd " << ","
			<< "regex" << ","
			<< "raw phr "
			<< endl;
		once = false;
	}
	vector<string> sentences = tokenize_into_sentences(verbatim);
	cout << "n_sentences: " << sentences.size() << endl;
	for (int i=0; i<sentences.size(); ++i) {
		vector<string> phrases = split_into_phrases (sentences[i]);
		cout << "phrases: " << endl;
		for (int j=0; j<phrases.size(); ++j) {
			cout << "        " << phrases[j] << endl;
			vector<string> words = split_into_words(phrases[j]);
			for (int k=0; k<words.size(); ++k) {
				word_freq_count[words[k]]++;
			}
			long long emphasizer_positive_words_score =  1 * check_for_emphasizer_phrase(emphasizer_words_of_interest, positive_words_of_interest, phrases[j]);
			long long emphasizer_negative_words_score = -1 * check_for_emphasizer_phrase(emphasizer_words_of_interest, negative_words_of_interest, phrases[j]);
			long long pos_phrase_score =  1 * check_for_phrase_of_interest(positive_phrase_of_interest, phrases[j]);
			long long neg_phrase_score = -1 * check_for_phrase_of_interest(negative_phrase_of_interest, phrases[j]);
			long long pos_score =  10 * check_for_words_of_interest(positive_words_of_interest, words);
			long long neg_score = -10 * check_for_words_of_interest(negative_words_of_interest, words);
			long long neutral_score = -1 * check_for_words_of_interest(neutral_words_of_interest, words);
			long long other_words_score = 10 * check_for_words_of_interest(other_words_of_interest, words);
			long long emphasizer_words_score = 1000 * check_for_words_of_interest(emphasizer_words_of_interest, words);
			long long management_words_score = 10000 * check_for_words_of_interest(words_indicating_management, words);
			long long pwrm_words_score = 10000 * check_for_words_of_interest(words_having_pwrm_rm_cm, words);
			long long reason_words_score = 10 * check_for_words_of_interest(words_indicating_reason, words);
			string addnl_info_regex_match;
			long long regex_score = match_regular_expressions_of_interest (phrases[j], addnl_info_regex_match);

			long long any_negatives = 1;
			if (emphasizer_negative_words_score || neg_phrase_score || neg_score) {
				any_negatives = -1;
			}
			int any_positives = 1;
			if (emphasizer_positive_words_score || pos_phrase_score || pos_score) {
				any_positives = 1;
			}
			management_words_score = management_words_score * any_negatives;
			pwrm_words_score = pwrm_words_score * any_negatives;

			long long  any_cls = emphasizer_positive_words_score + emphasizer_negative_words_score
					+ pos_phrase_score + neg_phrase_score + neg_score + pos_score
					+ other_words_score + emphasizer_words_score + management_words_score
					+ pwrm_words_score + reason_words_score
					+ neutral_score
					;
			phrase_scores
					<< any_cls << ","
					<< emphasizer_positive_words_score  << ","
					<< emphasizer_negative_words_score  << ","
					<< pos_phrase_score << ","
					<< neg_phrase_score << ","
					<< pos_score << ","
					<< neg_score << ","
					<< neutral_score << ","
					<< other_words_score  << ","
					<< emphasizer_words_score  << ","
					<< management_words_score  << ","
					<< pwrm_words_score  << ","
					<< reason_words_score  << ","
					<< regex_score  << ","
					<< "\"" << phrases[j] << "\"" << endl;
		}
	}
}

void processInput (LineProvider & line_provider)
{
	int count = 0;
	while (1) {
		RValueReadALine res = line_provider.get_a_line();
		if (res.success == false) {
			break;
		}
		//cout << "line_provider: " << res.a_line << endl;
		vector <string> line_split_into_fields = tokenize_csv_components_into_fields(res.a_line);
		if (line_split_into_fields.size() >= 6) {
			string s5b_data = line_split_into_fields[3];
			string s6b_data = line_split_into_fields[5];
			cout << "S5b data:" << line_split_into_fields[3] << endl;
			analyze_further(s5b_data);
			cout << "S6b data:" << line_split_into_fields[5] << endl;
			analyze_further(s6b_data);
		}
		//if (count == 1) {
		//	break;
		//}
		++count;
	}
	cout << "finished processing file" << endl;
}

void print_map( map <string,int> & word_freq_count)
{
	ofstream word_freq("word_freq.csv");
	for (auto map_it = word_freq_count.begin(); map_it != word_freq_count.end();
			++map_it) {
		word_freq << "word, " << map_it->first << ", freq, " << map_it->second << endl;
	}
}

/*
void populate_emphasizer_words_of_interest()
{
	emphasizer_words_of_interest.insert("ALWAYS");
	emphasizer_words_of_interest.insert("NEVER");
	emphasizer_words_of_interest.insert("VERY");
	emphasizer_words_of_interest.insert("TOO");
	emphasizer_words_of_interest.insert("HIGHLY");
}

void populate_other_words_of_interest()
{
	other_words_of_interest.insert("INVESTMENT");
	other_words_of_interest.insert("EARLY");
	other_words_of_interest.insert("TIME");
	other_words_of_interest.insert("SERVICE");
	other_words_of_interest.insert("RECOMMEND");
	other_words_of_interest.insert("VALUE");
	other_words_of_interest.insert("RELATIONSHIP");
	other_words_of_interest.insert("FRIENDS");
	other_words_of_interest.insert("AVAILABLE");
	other_words_of_interest.insert("ISSUE");
	other_words_of_interest.insert("TAKE");
	other_words_of_interest.insert("MANY");
	other_words_of_interest.insert("REFER");
	other_words_of_interest.insert("EXPERIENCE");
	other_words_of_interest.insert("INFORM");
	other_words_of_interest.insert("RESPONDS");
	other_words_of_interest.insert("RESOLVED");
	other_words_of_interest.insert("RESOLVE");
	other_words_of_interest.insert("RESOLVES");
	other_words_of_interest.insert("ATTITUDE");
	other_words_of_interest.insert("QUITE");
	other_words_of_interest.insert("DESPITE");
	other_words_of_interest.insert("TROUBLE");
	other_words_of_interest.insert("NEED");
	other_words_of_interest.insert("EXPECT");
	other_words_of_interest.insert("EXPECTS");
	other_words_of_interest.insert("EXPECTED");
	other_words_of_interest.insert("NEEDS");
}

void populate_negative_words_of_interest()
{
	negative_words_of_interest.insert("DISAPPEARED");
	negative_words_of_interest.insert("ANNOY");
	negative_words_of_interest.insert("ANNOYS");
	negative_words_of_interest.insert("NEVER");
	negative_words_of_interest.insert("DIDNT");
	negative_words_of_interest.insert("DISCONNECT");
	negative_words_of_interest.insert("LAIDBACK");
	negative_words_of_interest.insert("REGULAR");
	negative_words_of_interest.insert("REQULARLY");
	negative_words_of_interest.insert("CLOSE");
	negative_words_of_interest.insert("REFUSED");
	negative_words_of_interest.insert("BUSY");
	negative_words_of_interest.insert("KICK");
	negative_words_of_interest.insert("PROBLEM");
	negative_words_of_interest.insert("ELUSIVENESS");
	negative_words_of_interest.insert("ENEMIES");
	negative_words_of_interest.insert("NO");
	negative_words_of_interest.insert("NOT");
	negative_words_of_interest.insert("CANNOT");
	negative_words_of_interest.insert("CHANGING");
	negative_words_of_interest.insert("BAD");
	negative_words_of_interest.insert("FINALLY");
	negative_words_of_interest.insert("WORKS");
	negative_words_of_interest.insert("USELESS");
	negative_words_of_interest.insert("WORST");
	negative_words_of_interest.insert("WASTE");
	negative_words_of_interest.insert("MISSED");
	negative_words_of_interest.insert("LOUSY");
	negative_words_of_interest.insert("RUDE");
	negative_words_of_interest.insert("THREATENING");
	negative_words_of_interest.insert("SUPERFICIAL");
	negative_words_of_interest.insert("SELFISH");
	negative_words_of_interest.insert("CHASE");
}

void populate_negative_phrase_of_interest()
{
	negative_phrase_of_interest.insert("HAVEN'T");
	negative_phrase_of_interest.insert("SWITCH BACK");
	negative_phrase_of_interest.insert("DOES NOT");
	negative_phrase_of_interest.insert("DO NOT");
	negative_phrase_of_interest.insert("IS NOT");
	negative_phrase_of_interest.insert("NOT BE");
	negative_phrase_of_interest.insert("ONLY FOR");
	negative_phrase_of_interest.insert("I HAVE TO");
}

void populate_positive_phrase_of_interest()
{
	//positive_phrase_of_interest.insert("HUMBLE");
	positive_phrase_of_interest.insert("ADDS VALUE");
	positive_phrase_of_interest.insert("THINGS ARE DONE");
	positive_phrase_of_interest.insert("RIGHT ANSWERS");
	positive_phrase_of_interest.insert("ALWAYS HELP");
	positive_phrase_of_interest.insert("ALWAYS THERE");
	positive_phrase_of_interest.insert("IS GOOD");
	positive_phrase_of_interest.insert("HELPS ME");
	positive_phrase_of_interest.insert("FOLLOWS UP");
	positive_phrase_of_interest.insert("INFORMED ME");
	positive_phrase_of_interest.insert("KNOWS HIS JOB");
}

void populate_neutral_words_of_interest()
{
	neutral_words_of_interest.insert("OK");
	neutral_words_of_interest.insert("OKAY");
}
*/

void populate_regular_expressions_of_interest(string  file_name)
{
	//LineProvider words_of_interest_provider("words_of_interest.txt");
	LineProvider words_of_interest_provider(file_name.c_str());
	set <string>  words_of_interest;
	int count = 0;
	while (1) {
		RValueReadALine res = words_of_interest_provider.get_a_line();
		if (res.success == false) {
			break;
		}
		++count;
		//words_of_interest.insert(res.a_line);
		human_readable_regex_pattern.push_back(res.a_line);
		regex_t regex_pattern;
		regcomp (&regex_pattern, res.a_line.c_str(), REG_ICASE);
		regular_expressions_of_interest.push_back (regex_pattern);
	}
	cout << "read : " << count << " regex patterns from file" << endl;

	//return words_of_interest;
}

set <string>  populate_words_of_interest(string  file_name)
{
	//LineProvider words_of_interest_provider("words_of_interest.txt");
	LineProvider words_of_interest_provider(file_name.c_str());
	set <string>  words_of_interest;
	int count = 0;
	while (1) {
		RValueReadALine res = words_of_interest_provider.get_a_line();
		if (res.success == false) {
			break;
		}
		++count;
		words_of_interest.insert(res.a_line);
	}
	cout << "read : " << count << " words from file" << endl;

	return words_of_interest;

#if 0
	positive_words_of_interest.insert("BENEFIT");
	positive_words_of_interest.insert("ASSISTED");
	positive_words_of_interest.insert("ASSIST");
	positive_words_of_interest.insert("DOES");
	positive_words_of_interest.insert("EFFECTIVE");
	positive_words_of_interest.insert("DELIVERS");
	positive_words_of_interest.insert("SINCER");
	positive_words_of_interest.insert("SINCERE");
	positive_words_of_interest.insert("SPEEDY");
	positive_words_of_interest.insert("TRUST");
	positive_words_of_interest.insert("ANNOY");
	positive_words_of_interest.insert("INTERESTED");
	positive_words_of_interest.insert("INTEREST");
	positive_words_of_interest.insert("CALLS");
	positive_words_of_interest.insert("PROMPT");
	positive_words_of_interest.insert("PROMT");
	positive_words_of_interest.insert("PROVIDES");
	positive_words_of_interest.insert("PROVIDE");
	positive_words_of_interest.insert("ABLE");
	positive_words_of_interest.insert("ADVISE");
	positive_words_of_interest.insert("BEST");
	positive_words_of_interest.insert("ASSISTANCE");
	positive_words_of_interest.insert("FAMILY");
	positive_words_of_interest.insert("PERFECTION");
	positive_words_of_interest.insert("PERFECT");
	positive_words_of_interest.insert("SURELY");
	positive_words_of_interest.insert("YES");
	positive_words_of_interest.insert("QUALIFIED");
	positive_words_of_interest.insert("PROFITS");
	positive_words_of_interest.insert("PROFIT");
	positive_words_of_interest.insert("PROFESSIONAL");
	positive_words_of_interest.insert("EMPATHETIC");
	positive_words_of_interest.insert("DECENT");
	positive_words_of_interest.insert("NICE");
	positive_words_of_interest.insert("NICELY");
	positive_words_of_interest.insert("ADDED");
	positive_words_of_interest.insert("ARMY");
	positive_words_of_interest.insert("WARM");
	positive_words_of_interest.insert("EASY");
	positive_words_of_interest.insert("DEDICATED");
	positive_words_of_interest.insert("KEENESS");
	positive_words_of_interest.insert("KEEN");
	positive_words_of_interest.insert("FIXED");
	positive_words_of_interest.insert("PATEINT");
	positive_words_of_interest.insert("RELIABLE");
	positive_words_of_interest.insert("SUPER");
	positive_words_of_interest.insert("HELPUL");
	positive_words_of_interest.insert("ENTHUSIASTICK");
	positive_words_of_interest.insert("OWNERSHIP");
	positive_words_of_interest.insert("CORRECT");
	positive_words_of_interest.insert("IMMEDIATE");
	positive_words_of_interest.insert("IMMEDIATELY");
	positive_words_of_interest.insert("INFORM");
	positive_words_of_interest.insert("ADVANTAGE");
	positive_words_of_interest.insert("PROACTIVE");
	positive_words_of_interest.insert("SATISFIED");
	positive_words_of_interest.insert("HAPPY");
	positive_words_of_interest.insert("EXPLAINS");
	positive_words_of_interest.insert("SOLUTIONS");
	positive_words_of_interest.insert("SOLUTION");
	positive_words_of_interest.insert("RESOLUTION");
	positive_words_of_interest.insert("RESOLUTIONS");
	positive_words_of_interest.insert("TRANSPARENT");
	positive_words_of_interest.insert("KNOWLEDGE");
	positive_words_of_interest.insert("KNOWLEGE");
	positive_words_of_interest.insert("KNOWLEDGE");
	positive_words_of_interest.insert("KNOWLEDGABLE");
	positive_words_of_interest.insert("HELPS");
	positive_words_of_interest.insert("UNDESTANDS");
	positive_words_of_interest.insert("UNDERSTAND");
	positive_words_of_interest.insert("UNDERSTANDS");
	positive_words_of_interest.insert("UNDERTSANDING");
	positive_words_of_interest.insert("UNDERSTANGING");
	positive_words_of_interest.insert("UNDERSTANDING");
	positive_words_of_interest.insert("CONSIDERATE");
	positive_words_of_interest.insert("BRILLIANT");
	positive_words_of_interest.insert("COMMITTED");
	positive_words_of_interest.insert("POLITE");
	positive_words_of_interest.insert("GOOD");
	positive_words_of_interest.insert("CARE");
	positive_words_of_interest.insert("CARING");
	positive_words_of_interest.insert("HELPFUL");
	positive_words_of_interest.insert("ASSIST");
	positive_words_of_interest.insert("BETTER");
	positive_words_of_interest.insert("FRIENDLY");
	positive_words_of_interest.insert("COMFORTABLE");
	positive_words_of_interest.insert("HONEST");
	positive_words_of_interest.insert("MODEST");
	positive_words_of_interest.insert("HELPED");
	positive_words_of_interest.insert("HELP");
	positive_words_of_interest.insert("WILLING");
	positive_words_of_interest.insert("GREAT");
	positive_words_of_interest.insert("EXPERIENCED");
	positive_words_of_interest.insert("PROACTIVELY");
	positive_words_of_interest.insert("EXCELLENT");
	positive_words_of_interest.insert("EFFICIENT");
	positive_words_of_interest.insert("DIFFERENCE");
	positive_words_of_interest.insert("CREDIT");
	positive_words_of_interest.insert("LISTENS");
	positive_words_of_interest.insert("INTERACTIVE");
	positive_words_of_interest.insert("VALUABLE");
	positive_words_of_interest.insert("TIMELY");
	positive_words_of_interest.insert("RECOMMENDING");
	positive_words_of_interest.insert("RECOMMENDED");
	positive_words_of_interest.insert("PROMPTLY");
	positive_words_of_interest.insert("SAFE");
	positive_words_of_interest.insert("COMFORT");
	positive_words_of_interest.insert("PATIENT");
	positive_words_of_interest.insert("PARTICULAR");
	positive_words_of_interest.insert("INSTEAD");
	positive_words_of_interest.insert("INFORMATIVE");
	positive_words_of_interest.insert("FRIEND");
	positive_words_of_interest.insert("COMPLETELY");
	positive_words_of_interest.insert("CAPABLE");
	positive_words_of_interest.insert("APPROACHABLE");
	positive_words_of_interest.insert("AGREE");
	positive_words_of_interest.insert("YOUNG");
	positive_words_of_interest.insert("PREFER");
	positive_words_of_interest.insert("POSITIVE");
	positive_words_of_interest.insert("PLEASE");
	positive_words_of_interest.insert("PLEASANT");
	positive_words_of_interest.insert("USEFUL");
	positive_words_of_interest.insert("SUPPORTIVE");
	positive_words_of_interest.insert("SMART");
	positive_words_of_interest.insert("SATIFIED");
	positive_words_of_interest.insert("PRACTICAL");
	positive_words_of_interest.insert("GAINED");
	positive_words_of_interest.insert("EXPERTISE");
	positive_words_of_interest.insert("RESPONSIBLE");
	positive_words_of_interest.insert("RESPONSIVE");
	positive_words_of_interest.insert("RELENTLESSLY");
	positive_words_of_interest.insert("PUNCTUAL");
	positive_words_of_interest.insert("PSOITIVE");
	positive_words_of_interest.insert("SATISFY");
	positive_words_of_interest.insert("SATISFILED");
	positive_words_of_interest.insert("SATISFACTION");
	positive_words_of_interest.insert("SATIFISFIED");
	positive_words_of_interest.insert("RELEVANT");
	positive_words_of_interest.insert("PROFIT");
#endif /* 0 */

}

/*
void populate_words_indicating_reason ()
{
	words_indicating_reason.insert("BECAUSE");
	words_indicating_reason.insert("BCOZ");
	words_indicating_reason.insert("REASON");
	words_indicating_reason.insert("RESONS");
}

void populate_words_indicating_management()
{
	words_indicating_management.insert("MANAGEMENT");
	words_indicating_management.insert("MANAGER");
}

void populate_words_having_pwrm_rm_cm()
{
	words_having_pwrm_rm_cm.insert("RM");
	words_having_pwrm_rm_cm.insert("RMS");
	words_having_pwrm_rm_cm.insert("PWRM");
	words_having_pwrm_rm_cm.insert("WPRM");
	words_having_pwrm_rm_cm.insert("CM");
	words_having_pwrm_rm_cm.insert("CUSTOMER");
	words_having_pwrm_rm_cm.insert("CUSTOMERS");
	words_having_pwrm_rm_cm.insert("CUST");
	words_having_pwrm_rm_cm.insert("BANK");
	words_having_pwrm_rm_cm.insert("BANKS");
	words_having_pwrm_rm_cm.insert("HSBC");
}
*/

// found from google : opposite of strtol (which i thought wouldnt work but gave me perl code)
//http://www.perlmonks.org/?node_id=773397
string ltostr (long long number, int base)
{
	//my ($num, $base) = @_;
	std::stringstream r_val;
	if (base < 2 || base > 36) {
		r_val << "wont_work for base <2 or > 36";
	} else {
		int sign = number < 0 ? -1 : 1;
		if (number < 0) {
			//r_val.push_back('-');
			r_val << '-';
		}
		long long whats_left =  sign *  number ;
		int counter = 0;
		do {
			//cout << "whats_left:" << whats_left << endl;
			long long remainder =  whats_left % base;
			//cout << "remainder:" << remainder << endl;
			whats_left =  whats_left / base;
			if (remainder < 10) {
			    //r_val.push_back(('0' + remainder));
			    char ch = ('0' + remainder);
			    r_val << ch;
			} else {
			    //r_val.push_back('A' + remainder-10);
			    char ch = ('A' + remainder - 10);
			    r_val << ch;
			}
			//cout << "looping: " << endl;
			if (counter > 10) {
				break;
			}
			++ counter;
		} while (whats_left);
	}
	// this can be done better no - like a reverse function?
	// but im too tired
	string new_str;
	string old_str = r_val.str();
	for (int i=old_str.size()-1; i>=0; --i) {
		new_str.push_back(old_str[i]);
	}
	return new_str;

		/*
	my $neg = $num < 0;
	$num = -$num if $neg;
	my $str = '';
	do {
	$str = ( '0'..'9', 'a'..'z' )[ $num % $base ] . $str;
	$num = int( $num / $base );
	} while $num;
	$str = "-$str" if $neg;
	return $str;
	*/
}



int main()
{
	//long long v4 = compute_string_score(string("AB")) ;
	//long long v3 = compute_string_score(string("ABCDEFG")) ;
	//long long v5 = compute_string_score(string("ABCDEFGHIJ")) ;
	//long long v1 = compute_string_score(string("COMPUTE")) ;
	//long long v2 = compute_string_score(string("COMUTE")) ;
	//cout << "v1: " << v1 << "," << ltostr(v1, 36) << endl;
	//cout << "v2: " << v2 << "," << ltostr(v2, 36) << endl;
	//v2 = v2*36;
	//cout << "v2: " << v2 << "," << ltostr(v2, 36) << endl;
	//cout << "v3: " << v3 << "," << ltostr(v3, 36) << endl;
	//cout << "v4: " << v4 << "," << ltostr(v4, 36) << endl;
	//cout << "v5: " << v5 << "," << ltostr(v5, 36) << endl;
	//exit(1);
	positive_words_of_interest =  populate_words_of_interest("positive_words_of_interest.txt");
	negative_words_of_interest =  populate_words_of_interest("negative_words_of_interest.txt");
	other_words_of_interest =  populate_words_of_interest("other_words_of_interest.txt");
	//populate_negative_words_of_interest();
	//populate_other_words_of_interest();
	//populate_emphasizer_words_of_interest();
	emphasizer_words_of_interest =  populate_words_of_interest("emphasizer_words_of_interest.txt");
	//populate_negative_phrase_of_interest();
	negative_phrase_of_interest =  populate_words_of_interest("negative_phrase_of_interest.txt");
	//populate_positive_phrase_of_interest();
	positive_phrase_of_interest =  populate_words_of_interest("positive_phrase_of_interest.txt");
	//populate_words_indicating_reason();
	words_indicating_reason =  populate_words_of_interest("words_indicating_reason.txt");
	//populate_words_indicating_management();
	words_indicating_management = populate_words_of_interest("words_indicating_management.txt");

	populate_regular_expressions_of_interest("negative_regex_patterns.txt");

	//populate_words_having_pwrm_rm_cm();
	words_having_pwrm_rm_cm = populate_words_of_interest("words_having_pwrm_rm_cm.txt");
	neutral_words_of_interest = populate_words_of_interest("neutral_words_of_interest.txt");

	std::ifstream data_file("pwrm_dxb.qdat");
	//process_file (data_file);
	std::ifstream s5b_6b_data_file("s5b-s6b-coding-data-input.csv");
	//process_file (s5b_6b_data_file);
	LineProvider s5b_6b_data_file_line_provider("s5b-s6b-coding-data-input.csv");
	processInput (s5b_6b_data_file_line_provider);
	//RValueReadALine a_poss_line = s5b_6b_data_file_line_provider.get_a_line();
	//if (a_poss_line.success) {
	//	cout << "aline from LineProvider: " << a_poss_line.a_line << endl;
	//}

	print_map(word_freq_count);
}
