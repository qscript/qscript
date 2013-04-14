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
#include <cctype>
#include <functional>
#include <algorithm>

//#include <boost/multiprecision/cpp_int.hpp>
//using namespace boost::multiprecision;

#include "util.h"
#include "StringSpectralInfo.h"

using namespace std;
map <string, int> word_freq_count;

	set <string> negative_words_of_interest;
	set <string> positive_words_of_interest, neutral_words_of_interest;
	set <string> other_words_of_interest;
	set <string> emphasizer_words_of_interest;
	set <string> negative_phrase_of_interest;
	set <string> positive_phrase_of_interest;
	set <string> suggestion_phrase_of_interest;
	set <string> neutral_phrase_of_interest;
	set <string> words_indicating_reason;
	set <string> words_having_pwrm_rm_cm;
	set <string> words_indicating_management;
	set <string> words_indicating_call_back_later;
	set <string> words_indicating_suggestions;
	vector <regex_t> regular_expressions_of_interest;
	vector <string> human_readable_regex_pattern;
	set <string> gen_emph_pos_phrases;
	set <string> gen_emph_neg_phrases;
	set <string> gen_pos_phrases;
	set <string> gen_neg_phrases;
	set <string> gen_neg_pos_phrases;



	using namespace std;
void process_file (std::ifstream & data_file)
{
	string a_line;
	while (std::getline(data_file, a_line)) {
		//cout << "got line: " << a_line << endl;
	}
}



// few tweaks to the metric in this function
// we want the prefix of the word to have
// the highest influence on the score
// and the suffix to have the lowest influence
long long compute_string_score (const string & s)
{
	//cout << __PRETTY_FUNCTION__ << " :s:" << s<< endl;
	long long score = 0;
	static map <string, long long> memoized_scores;

	map <string, long long>::iterator it = memoized_scores.find (s);


	if (it == memoized_scores.end()) {
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
				// This wont work until i use boost::multiprecision
				// causes overflow
				//score = (s[i] - 'A' + 10) + score * 36;
				score = (s[i] - 'A' + 10) + i*10;
				//base *= 36;
				//cout << "partial score: " << score << endl;
			}
		}
		memoized_scores[s]=score;
		//cout << "from calc" << endl;
		return score;
	} else {
		//cout << "from cache" << endl;
		return it->second;
	}

}


long long check_for_phrase_of_interest(const set<string> & phrase_of_interest, const string & user_phrase,
		string & addnl_info
		)
{
	long long result = 0;
	const string marker(" | ");
	for (auto it = phrase_of_interest.begin(); it != phrase_of_interest.end();
			++it) {
		const string &  a_phrase_of_interest = *it;
		//cout 	<< "searching: |" << user_phrase << "|"
		//	<< "with: |" << a_phrase_of_interest << "|"<< endl;
		//if (user_phrase.find ("EXTREMELY DISSATISFIED")!= string::npos) {
		//	//cout << "found exact match EXTREMELY DISSATISFIED" << endl;
		//}
		if (user_phrase.find (a_phrase_of_interest)!= string::npos) {
			addnl_info += marker + a_phrase_of_interest + marker;
			// we can memoize here - no?
			long long score =  compute_string_score (a_phrase_of_interest);
			result += score;
			//cout << "found pattern MATCH|" << a_phrase_of_interest << endl;
			//cout << "addnl_info: " << addnl_info << endl;
		}
	}
	//return result * 100;
	return result ;
}


long long check_for_generated_phrases_of_interest(
		const set<string> & modifier_pre_word,
		const set<string> & phrase_of_interest,
		const string & user_phrase,
		string & addnl_info)
{
	long long result = 0;

	for (auto modifier_pre_word_it = modifier_pre_word.begin(); modifier_pre_word_it != modifier_pre_word.end();
				++modifier_pre_word_it) {
		for (auto it = phrase_of_interest.begin(); it != phrase_of_interest.end();
				++it) {
			string  a_phrase_of_interest = *modifier_pre_word_it + string(" ") + *it;
			cout << "checking for gen phrase:" << a_phrase_of_interest << endl;
			if (user_phrase.find (a_phrase_of_interest)!= string::npos) {
				//addnl_info += ": |" + s2 + "| has word of interest: |" + neg_word + "|";
				long long score =  compute_string_score (a_phrase_of_interest);
				result += score;
				addnl_info += "|" + a_phrase_of_interest;
			}
		}
	}
	//return result * 100;
	return result ;
}

long long match_regular_expressions_of_interest (const string & s, string & addnl_info)
{
	//cout << "match_reg"
	//	<< ", " << s << ", regexp"
	//	<< "vector size:" << regular_expressions_of_interest.size()
	//	<< endl;
	long long cumulative_score = 0;
	for (int i=0; i<regular_expressions_of_interest.size(); ++i) {
		regmatch_t p_match[5];
		int n_match=5;
		regex_t a_regex = regular_expressions_of_interest[i];
		int regex_result = regexec (&a_regex, s.c_str(), n_match, p_match, 0);
		if (regex_result == 0) {
			//cout << __PRETTY_FUNCTION__ << " We have a match"
			//	<< endl;
			addnl_info += "matched with regexp";
			//++cumulative_score;
			long long score = compute_string_score(s);
			cumulative_score += score;
		} else {
			//cout << __PRETTY_FUNCTION__ << " no match in vector pattern"
			//	<< endl;
		}
	}
	//cout << "Exit: " << __PRETTY_FUNCTION__ << ", score, "  << cumulative_score << endl;
	return cumulative_score;
}

long long check_for_words_of_interest(const set<string> & words_of_interest, const vector<string> & phrase_in_words,
		string & addnl_info )
{
	long long score = 0;
	for (int i=0; i<phrase_in_words.size(); ++i) {
		const string & a_word = phrase_in_words[i];
		auto found = words_of_interest.find (a_word);
		if (found != words_of_interest.end()) {
			//++score;
			score += compute_string_score(a_word);
			addnl_info += string("|") + (a_word);
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
	//return score * 10000;
	return score ;
}


struct Info
{
	int serial_no;
	int pwrm_no;
	string s5b_verbatim;
	string s6b_verbatim;
	Info (int p_serial_no, int p_pwrm_no, const string & p_s5b_verbatim, const string & p_s6b_verbatim)
		: serial_no (p_serial_no),
		  pwrm_no (p_pwrm_no),
		  s5b_verbatim (p_s5b_verbatim),
		  s6b_verbatim (p_s6b_verbatim)
	{ }
};

struct Info2
{
	int serial_no;
	string verbatim;
	Info2 (int p_serial_no, const string & p_verbatim)
		: serial_no (p_serial_no),
		  verbatim (p_verbatim)
	{ }
};


void generate_phrases_of_interest(const set <string> & prefix
		, const set<string> & suffix
		, set<string> & generated_phrases)
{
	for (auto pre_it = prefix.begin(); pre_it != prefix.end();
				++pre_it) {
		for (auto it = suffix.begin(); it != suffix.end();
				++it) {
			const string & a_phrase_of_interest = *pre_it + string(" ") + *it;
			generated_phrases.insert(a_phrase_of_interest);
		}
	}
}

void analyze_further(string & verbatim, const Info & inf, string  qno)
{
	cout << __PRETTY_FUNCTION__ << endl;
	ofstream phrase_scores("phrase_scores.csv", ios_base::app);
	static bool once = true;
	if (once) {
		phrase_scores
			<< "serial_no" << ","
			<< "pwrm_code" << ","
			<< "any_cls" << ","
			<< "ps_emphr" << ","
			<< "ng_emphr" << ","
			<< "ps_ph" << ","
			<< "ng_ph" << ","
			<< "gen_pos_phrase_score" << ","
			<< "gen_neg_phrase_score" << ","
			<< "ps_wd" << ","
			<< "ng_wd" << ","
			<< "neu_wd" << ","
			<< "oth_wd" << ","
			<< "emph_wd" << ","
			<< "mngmt_wd" << ","
			<< "pwrm_wd" << ","
			<< "reasn_wd " << ","
			<< "regex" << ","
			//<< "n_phr" << ","
			//<< "n_sent" << ","
			<< "positive_match" << ","
			<< "negative_match" << ","
			<< "pos_gen_phr_match" << ","
			<< "neg_gen_phr_match" << ","
			<< "neutral_match" << ","
			<< "other_match" << ","
			<< "emph_match" << ","
			<< "mnmng_match" << ","
			<< "pwrm_match" << ","
			<< "reas_match" << ","
			<< "raw phr" << ","
			<< "raw sent" << ","
			<< endl;
		once = false;
	}
	vector<string> sentences = tokenize_into_sentences(verbatim);
	//cout << "n_sentences: " << sentences.size() << endl;
	for (int i=0; i<sentences.size(); ++i) {
		vector<string> phrases = split_into_phrases (sentences[i]);
		//cout << "phrases: " << endl;
		for (int j=0; j<phrases.size(); ++j) {
			//cout << "        " << phrases[j] << endl;
			vector<string> words = split_into_words(phrases[j]);
			for (int k=0; k<words.size(); ++k) {
				word_freq_count[words[k]]++;
			}
			//long long emphasizer_positive_words_score =  1 * check_for_emphasizer_phrase(emphasizer_words_of_interest, positive_words_of_interest, phrases[j]);
			string pos_emph_word_match = "pos_emph_word_match: ";
			long long emphasizer_positive_words_score =  1 * check_for_generated_phrases_of_interest(emphasizer_words_of_interest, positive_words_of_interest, phrases[j], pos_emph_word_match);
			//long long emphasizer_negative_words_score = -1 * check_for_emphasizer_phrase(emphasizer_words_of_interest, negative_words_of_interest, phrases[j]);
			string neg_emph_word_match = "neg_emph_word_match: ";
			long long emphasizer_negative_words_score =  -1 * check_for_generated_phrases_of_interest(emphasizer_words_of_interest, negative_words_of_interest, phrases[j], neg_emph_word_match);
			string pos_phr_int_match = "pos_phr_int_match: ";
			long long pos_phrase_score =  1 * check_for_phrase_of_interest(positive_phrase_of_interest, phrases[j], pos_phr_int_match);
			string neg_phr_int_match = "neg_phr_int_match: ";
			long long neg_phrase_score = -1 * check_for_phrase_of_interest(negative_phrase_of_interest, phrases[j], neg_phr_int_match);
			string pos_gen_phr_match = "pos_gen_phr_match match: ";
			long long gen_pos_phrase_score =  1 * check_for_generated_phrases_of_interest(positive_words_of_interest, other_words_of_interest, phrases[j], pos_gen_phr_match);
			string neg_gen_phr_match = "neg_gen_phr_match match: ";
			long long gen_neg_phrase_score = -1 * check_for_generated_phrases_of_interest(negative_words_of_interest, other_words_of_interest, phrases[j], neg_gen_phr_match);
			string positive_match = "positive match: ";
			long long pos_score =  10 * check_for_words_of_interest(positive_words_of_interest, words, positive_match);
			string negative_match = "negative match: ";
			long long neg_score = -10 * check_for_words_of_interest(negative_words_of_interest, words, negative_match);
			string neutral_match = "neutral match: ";
			long long neutral_score = -1 * check_for_words_of_interest(neutral_words_of_interest, words, neutral_match);
			string other_match = "other match: ";
			long long other_words_score = 10 * check_for_words_of_interest(other_words_of_interest, words, other_match);
			string emph_match = "emph match: ";
			long long emphasizer_words_score = 1000 * check_for_words_of_interest(emphasizer_words_of_interest, words, emph_match);
			string mnmng_match = "mnmng match: ";
			long long management_words_score = 10000 * check_for_words_of_interest(words_indicating_management, words, mnmng_match);
			string pwrm_match = "pwrm match: ";
			long long pwrm_words_score = 10000 * check_for_words_of_interest(words_having_pwrm_rm_cm, words, pwrm_match);
			string reas_match = "reas match: ";
			long long reason_words_score = 10 * check_for_words_of_interest(words_indicating_reason, words, reas_match);
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
					<< inf.serial_no << ","
					<< inf.pwrm_no << ","
					<< any_cls << ","
					<< emphasizer_positive_words_score  << ","
					<< emphasizer_negative_words_score  << ","
					<< pos_phrase_score << ","
					<< neg_phrase_score << ","
					<< gen_pos_phrase_score << ","
					<< gen_neg_phrase_score << ","
					<< pos_score << ","
					<< neg_score << ","
					<< neutral_score << ","
					<< other_words_score  << ","
					<< emphasizer_words_score  << ","
					<< management_words_score  << ","
					<< pwrm_words_score  << ","
					<< reason_words_score  << ","
					<< regex_score  << ","
					<< phrases.size()   << ","
					<< sentences.size()   << ","
					<< positive_match << ","
					<< negative_match << ","
					<< pos_gen_phr_match << ","
					<< neg_gen_phr_match << ","
					<< neutral_match << ","
					<< other_match << ","
					<< emph_match << ","
					<< mnmng_match << ","
					<< pwrm_match << ","
					<< reas_match << ","
					<< "\"" << phrases[j] << "\"" << ","
					<< "\"" << verbatim   << "\"" << ","
					<< endl;
		}
	}
}

vector <StringSpectralInfo> string_spectral_scores_vec;
void analyze_further2( Info2 & inf, const string &  qno)
{
	string & verbatim = inf.verbatim;
	//ofstream phrase_scores("phrase_scores.csv", ios_base::app);
	static bool once = true;
	if (once) {
#if 0
		phrase_scores
			<< "serial_no" << ","
			<< "any_cls" << ","
			<< "ps_emphr" << ","
			<< "ng_emphr" << ","
			<< "ps_ph" << ","
			<< "ng_ph" << ","
			<< "gen_pos_phrase_score" << ","
			<< "gen_neg_phrase_score" << ","
			<< "ps_wd" << ","
			<< "ng_wd" << ","
			<< "neu_wd" << ","
			<< "oth_wd" << ","
			<< "emph_wd" << ","
			<< "mngmt_wd" << ","
			<< "pwrm_wd" << ","
			<< "reasn_wd " << ","
			<< "cll_bk_ltr_wd" << ","
			<< "regex" << ","
			<< "n_phr" << ","
			<< "n_sent" << ","
			<< "positive_match" << ","
			<< "negative_match" << ","
			<< "pos_phr_int_match" << ","
			<< "neg_phr_int_match" << ","
			<< "pos_gen_phr_match" << ","
			<< "neg_gen_phr_match" << ","
			<< "neutral_match" << ","
			<< "other_match" << ","
			<< "emph_match" << ","
			<< "mnmng_match" << ","
			<< "pwrm_match" << ","
			<< "reas_match" << ","
			<< "call_back_ltr_match" << ","
			<< "raw phr" << ","
			<< "raw sent" << ","
			<< endl;
#endif /* 0 */
		once = false;
	}
	vector<string> sentences = tokenize_into_sentences(verbatim);
	//cout << "n_sentences: " << sentences.size() << endl;
	for (int i=0; i<sentences.size(); ++i) {
		vector<string> phrases = split_into_phrases (sentences[i]);
		//cout << "phrases: " << endl;
		for (int j=0; j<phrases.size(); ++j) {
			//cout << "        " << phrases[j] << endl;
			vector<string> words = split_into_words(phrases[j]);
			for (int k=0; k<words.size(); ++k) {
				word_freq_count[words[k]]++;
			}
			//long long emphasizer_positive_words_score =  1 * check_for_emphasizer_phrase(emphasizer_words_of_interest, positive_words_of_interest, phrases[j]);
			string pos_emph_word_match = "pos_emph_word_match: ";
			pos_emph_word_match.reserve(2048);
			// this is a optimization for speed - which I hope works
			// you will get the same result with the line commented out below
			//long long emphasizer_positive_words_score =  1 * check_for_generated_phrases_of_interest(emphasizer_words_of_interest, positive_words_of_interest, phrases[j], pos_emph_word_match);
			long long emphasizer_positive_words_score =  1 * check_for_phrase_of_interest(gen_emph_pos_phrases, phrases[j], pos_emph_word_match);
			if (pos_emph_word_match == "pos_emph_word_match: ") {
				pos_emph_word_match = "";
			}
			//long long emphasizer_negative_words_score = -1 * check_for_emphasizer_phrase(emphasizer_words_of_interest, negative_words_of_interest, phrases[j]);
			string neg_emph_word_match = "neg_emph_word_match: ";
			neg_emph_word_match.reserve(2048);
			//long long emphasizer_negative_words_score =  1 * check_for_generated_phrases_of_interest(emphasizer_words_of_interest, negative_words_of_interest, phrases[j], neg_emph_word_match);
			long long emphasizer_negative_words_score =  1 * check_for_phrase_of_interest(gen_emph_neg_phrases, phrases[j], neg_emph_word_match);
			//if (emphasizer_negative_words_score > 0)  {
			//	cout << "emphasizer_negative_words_score > 0: "
			//		<< "neg_emph_word_match:" << neg_emph_word_match
			//		<< endl;
			//}
			if (neg_emph_word_match == "neg_emph_word_match: ") {
				neg_emph_word_match = "";
				//cout << "neg_emph_word_match RESET " << endl;
			}
			string pos_phr_int_match = "pos_phr_int_match: ";
			pos_phr_int_match.reserve(2048);
			long long pos_phrase_score =  1 * check_for_phrase_of_interest(positive_phrase_of_interest, phrases[j], pos_phr_int_match);
			if (pos_phr_int_match == "pos_phr_int_match: ") {
				pos_phr_int_match = "";
			}
			string neg_phr_int_match = "neg_phr_int_match: ";
			neg_phr_int_match.reserve(2048);
			long long neg_phrase_score = 1 * check_for_phrase_of_interest(negative_phrase_of_interest, phrases[j], neg_phr_int_match);
			if (neg_phr_int_match == "neg_phr_int_match: ") {
				neg_phr_int_match = "";
			}
			string call_back_ltr_match = "call back ltr match: ";
			long long call_back_ltr_words_score = check_for_phrase_of_interest(words_indicating_call_back_later, phrases[j], call_back_ltr_match);
			if (call_back_ltr_match == "call back ltr match: ") {
				call_back_ltr_match = ""; // reset so you can use ctrl arrow in csv scores file
			}
			string pos_gen_phr_match = "pos_gen_phr_match match: ";
			pos_gen_phr_match.reserve(2048);
			//long long gen_pos_phrase_score =  1 * check_for_generated_phrases_of_interest(positive_words_of_interest, other_words_of_interest, phrases[j], pos_gen_phr_match);
			long long gen_pos_phrase_score =  1 * check_for_phrase_of_interest(gen_pos_phrases, phrases[j], pos_gen_phr_match);
			if (pos_gen_phr_match == "pos_gen_phr_match match: ") {
				pos_gen_phr_match = "";
			}
			string neg_gen_phr_match = "neg_gen_phr_match match: ";
			neg_gen_phr_match.reserve(2048);
			//long long gen_neg_phrase_score = 1 * check_for_generated_phrases_of_interest(negative_words_of_interest, other_words_of_interest, phrases[j], neg_gen_phr_match);
			long long gen_neg_phrase_score =  1 * check_for_phrase_of_interest(gen_neg_phrases, phrases[j], neg_gen_phr_match);
			//gen_neg_phrase_score += 1 * check_for_generated_phrases_of_interest(emphasizer_words_of_interest, negative_words_of_interest, phrases[j], neg_gen_phr_match);
			//gen_neg_phrase_score +=  1 * check_for_phrase_of_interest(gen_neg_phrases, phrases[j], neg_gen_phr_match);
			//string neg_gen_phr_match = "neg_gen_phr_match match: ";
			//gen_neg_phrase_score += 1 * check_for_generated_phrases_of_interest(negative_words_of_interest, positive_words_of_interest, phrases[j], neg_gen_phr_match);
			gen_neg_phrase_score +=  1 * check_for_phrase_of_interest(gen_neg_pos_phrases, phrases[j], neg_gen_phr_match);
			if (neg_gen_phr_match == "neg_gen_phr_match match: ") {
				neg_gen_phr_match = "";
			}
			string positive_match = "positive match: ";
			long long pos_score =  1 * check_for_words_of_interest(positive_words_of_interest, words, positive_match);
			if (positive_match == "positive match: ") {
				positive_match = "";
			}
			string negative_match = "negative match: ";
			long long neg_score = 1 * check_for_words_of_interest(negative_words_of_interest, words, negative_match);
			if (negative_match == "negative match: ") {
				negative_match = "";
			}
			string neutral_match = "neutral match: ";
			long long neutral_score = 1 * check_for_words_of_interest(neutral_words_of_interest, words, neutral_match);
			if (neutral_match == "neutral match: ") {
				neutral_match = "";
			}
			string other_match = "other match: ";
			long long other_words_score = 1 * check_for_words_of_interest(other_words_of_interest, words, other_match);
			if (other_match == "other match: ") {
				other_match = "";
			}
			string emph_match = "emph match: ";
			long long emphasizer_words_score = check_for_words_of_interest(emphasizer_words_of_interest, words, emph_match);
			if (emph_match == "emph match: ") {
				emph_match = "";
			}
			string mnmng_match = "mnmng match: ";
			long long management_words_score = check_for_words_of_interest(words_indicating_management, words, mnmng_match);
			if (mnmng_match == "mnmng match: ") {
				mnmng_match = "";
			}
			string pwrm_match = "pwrm match: ";
			long long pwrm_words_score = check_for_words_of_interest(words_having_pwrm_rm_cm, words, pwrm_match);
			if (pwrm_match == "pwrm match: ") {
				pwrm_match = "";
			}
			string reas_match = "reas match: ";
			long long reason_words_score = check_for_words_of_interest(words_indicating_reason, words, reas_match);
			if (reas_match == "reas match: ") {
				reas_match = "";
			}
			string addnl_info_regex_match = "regex match: ";
			long long regex_score = match_regular_expressions_of_interest (phrases[j], addnl_info_regex_match);
			if (addnl_info_regex_match == "regex match: ") {
				addnl_info_regex_match = "";
			}

			string suggestions_match = "suggestions_match : ";
			long long suggestions_score = check_for_words_of_interest(words_indicating_suggestions, words, suggestions_match);
			if (suggestions_match == "suggestions_match : ") {
				suggestions_match = "";
			}
			long long any_negatives = 1;
			if (emphasizer_negative_words_score || neg_phrase_score || neg_score) {
				any_negatives = -1;
			}
			int any_positives = 1;
			if (emphasizer_positive_words_score || pos_phrase_score || pos_score) {
				any_positives = 1;
			}
			//management_words_score = management_words_score * any_negatives;
			//pwrm_words_score = pwrm_words_score * any_negatives;
			long long  any_cls = emphasizer_positive_words_score + emphasizer_negative_words_score
					+ pos_phrase_score + neg_phrase_score + neg_score + pos_score
					+ other_words_score + emphasizer_words_score + management_words_score
					+ pwrm_words_score + reason_words_score
					+ neutral_score
					;
#if 0
			phrase_scores
					<< inf.serial_no << ","
					<< any_cls << ","
					<< emphasizer_positive_words_score  << ","
					<< emphasizer_negative_words_score  << ","
					<< pos_phrase_score << ","
					<< neg_phrase_score << ","
					<< gen_pos_phrase_score << ","
					<< gen_neg_phrase_score << ","
					<< pos_score << ","
					<< neg_score << ","
					<< neutral_score << ","
					<< other_words_score  << ","
					<< emphasizer_words_score  << ","
					<< management_words_score  << ","
					<< pwrm_words_score  << ","
					<< reason_words_score  << ","
					<< call_back_ltr_words_score  << ","
					<< regex_score  << ","
					<< phrases.size()   << ","
					<< sentences.size()   << ","
					<< positive_match << ","
					<< negative_match << ","
					<< pos_phr_int_match << ","
					<< neg_phr_int_match << ","
					<< pos_gen_phr_match << ","
					<< neg_gen_phr_match << ","
					<< neutral_match << ","
					<< other_match << ","
					<< emph_match << ","
					<< mnmng_match << ","
					<< pwrm_match << ","
					<< reas_match << ","
					<< call_back_ltr_match << ","
					<< "\"" << phrases[j] << "\"" << ","
					<< "\"" << verbatim   << "\"" << ","
					<< endl;
#endif /* 0 */
			StringSpectralInfo ss_inf(
					inf.serial_no,
					pos_emph_word_match,
					emphasizer_positive_words_score,
					neg_emph_word_match,
					emphasizer_negative_words_score,
					pos_phr_int_match,
					pos_phrase_score,
					neg_phr_int_match,
					neg_phrase_score,
					call_back_ltr_match,
					call_back_ltr_words_score,
					pos_gen_phr_match,
					gen_pos_phrase_score,
					neg_gen_phr_match,
					gen_neg_phrase_score,
					positive_match,
					pos_score,
					negative_match,
					neg_score,
					neutral_match,
					neutral_score,
					other_match,
					other_words_score,
					emph_match,
					emphasizer_words_score,
					mnmng_match,
					management_words_score,
					pwrm_match,
					pwrm_words_score,
					reas_match,
					reason_words_score,
					addnl_info_regex_match,
					regex_score,
					suggestions_match,
					suggestions_score,
					phrases[j],
					verbatim
					);
			string_spectral_scores_vec.push_back (ss_inf);
		}
	}
}

void split_verbatim_into_quantum_include (string verbatim, int serial_no)
{
	stringstream s1;
	int first_time = 0;
	for (int i=0; i<verbatim.length(); ++i) {
		char a_char = verbatim[i];
		if (a_char==';') {
			a_char = '.';
		}
		if (s1.str().length() < 30) {
				s1 << a_char;
		} else {
			if (isalpha(a_char)) {
				s1 << a_char;
			} else {
				if (!first_time) {
					cout << "n01: " << s1.str() << ";c=c(a0,a7).eq." << serial_no << endl;
					++first_time;
				} else {
					cout << "n33: " << s1.str() << ";c=c(a0,a7).eq." << serial_no << endl;
				}
				//s1.str().clear();
				s1.str("");
			}
		}
	}
	if (!first_time) {
		cout << "n01: " << s1.str() << ";c=c(a0,a7).eq." << serial_no << endl;
		++first_time;
	} else {
		cout << "n33: " << s1.str() << endl;
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
			int serial_no = atoi (line_split_into_fields[0].c_str());
			int pwrm_code = atoi (line_split_into_fields[1].c_str());
			string s5b_data = line_split_into_fields[3];
			string s6b_data = line_split_into_fields[5];
			Info inf (serial_no, pwrm_code, s5b_data, s6b_data);
			//cout << "S5b data:" << line_split_into_fields[3] << endl;
			//analyze_further(s5b_data, inf, "s5b");
			//cout << "S6b data:" << line_split_into_fields[5] << endl;
			//analyze_further(s6b_data, inf, "s6b");
			split_verbatim_into_quantum_include (s5b_data, serial_no);
			//split_verbatim_into_quantum_include (s6b_data, serial_no);
		}
		//if (count == 1) {
		//	break;
		//}
		++count;
	}
	cout << "finished processing file" << endl;
}

void processInput2 (LineProvider & line_provider)
{
	int count = 0;
	while (1) {
		RValueReadALine res = line_provider.get_a_line();
		if (res.success == false) {
			break;
		}
		//cout << "line_provider: " << res.a_line << endl;
		vector <string> line_split_into_fields = tokenize_csv_components_into_fields(res.a_line);
		const string qno("suggestions");
		if (line_split_into_fields.size() >= 2) {
			int serial_no = atoi (line_split_into_fields[0].c_str());
			string suggestions = line_split_into_fields[1];
			Info2 inf (serial_no, suggestions);
			//cout << "S5b data:" << line_split_into_fields[3] << endl;
			analyze_further2(inf, qno);
			//cout << "S6b data:" << line_split_into_fields[5] << endl;
			//analyze_further(s6b_data, inf, "s6b");
			//split_verbatim_into_quantum_include (s6b_data, serial_no);
		}
		cout << ".";
		//if (count == 1) {
		//	break;
		//}
		++count;
		if (count % 80 == 0) {
			cout << " " << count << endl;
		}
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


}



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

void print_report(const vector<StringSpectralInfo> & string_spectral_scores_vec)
{
	cout << __PRETTY_FUNCTION__ << endl;
	ofstream phrase_scores("phrase_scores.csv", ios_base::app);
	phrase_scores
		<< "serial_no" << ","
		<< "any_cls" << ","
		<< "any_match" << ","
		<< "ps_emphr" << ","
		<< "ng_emphr" << ","
		<< "ps_ph" << ","
		<< "ng_ph" << ","
		<< "gen_pos_phrase_score" << ","
		<< "gen_neg_phrase_score" << ","
		<< "ps_wd" << ","
		<< "ng_wd" << ","
		<< "neu_wd" << ","
		<< "oth_wd" << ","
		<< "emph_wd" << ","
		<< "mngmt_wd" << ","
		<< "pwrm_wd" << ","
		<< "reasn_wd " << ","
		<< "cll_bk_ltr_wd" << ","
		<< "regex" << ","
		//<< "n_phr" << ","
		//<< "n_sent" << ","
		<< "pos_emph_word_match" << ","
		<< "neg_emph_word_match" << ","
		<< "pos_phr_int_match" << ","
		<< "neg_phr_int_match" << ","
		<< "pos_gen_phr_match" << ","
		<< "neg_gen_phr_match" << ","
		<< "positive_match" << ","
		<< "negative_match" << ","
		<< "neutral_match" << ","
		<< "other_match" << ","
		<< "emph_match" << ","
		<< "mnmng_match" << ","
		<< "pwrm_match" << ","
		<< "reas_match" << ","
		<< "call_back_ltr_match" << ","
		<< "suggestions_match" << ","
		<< "raw phr" << ","
		<< "raw sent" << ","
		<< endl;

	for (const StringSpectralInfo & inf : string_spectral_scores_vec) {
		phrase_scores << inf.report();
	}

	phrase_scores << endl;
}

void print_phrases (const set<string> & p_phrases)
{
	for (auto  &it : p_phrases) {
		cout << it << endl;
	}
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
	suggestion_phrase_of_interest =  populate_words_of_interest("suggestion_phrase_of_interest.txt");
	words_indicating_reason =  populate_words_of_interest("words_indicating_reason.txt");
	//populate_words_indicating_management();
	words_indicating_management = populate_words_of_interest("words_indicating_management.txt");
	words_indicating_call_back_later = populate_words_of_interest("words_indicating_call_back_later.txt");
	words_indicating_suggestions = populate_words_of_interest("words_indicating_suggestions.txt");

	populate_regular_expressions_of_interest("negative_regex_patterns.txt");

	//populate_words_having_pwrm_rm_cm();
	words_having_pwrm_rm_cm = populate_words_of_interest("words_having_pwrm_rm_cm.txt");
	neutral_words_of_interest = populate_words_of_interest("neutral_words_of_interest.txt");

	std::ifstream data_file("pwrm_dxb.qdat");
	//process_file (data_file);
	std::ifstream s5b_6b_data_file("s5b-s6b-coding-data-input.csv");
	//process_file (s5b_6b_data_file);
	// This was for S5b/S6b
	//LineProvider s5b_6b_data_file_line_provider("s5b-s6b-coding-data-input.csv");
	//processInput (s5b_6b_data_file_line_provider);

	generate_phrases_of_interest (emphasizer_words_of_interest, positive_words_of_interest, gen_emph_pos_phrases);
	generate_phrases_of_interest (emphasizer_words_of_interest, negative_words_of_interest, gen_emph_neg_phrases);
	generate_phrases_of_interest (positive_words_of_interest, other_words_of_interest, gen_pos_phrases);
	generate_phrases_of_interest (negative_words_of_interest, other_words_of_interest, gen_neg_phrases);
	generate_phrases_of_interest (negative_words_of_interest, positive_words_of_interest, gen_neg_pos_phrases);

	//print_phrases (gen_emph_pos_phrases);
	//print_phrases (gen_emph_neg_phrases);
	//print_phrases (gen_pos_phrases);
	//print_phrases (gen_neg_phrases);
#if 1
	LineProvider suggestions_line_provider("suggestions.csv");
	processInput2 (suggestions_line_provider);
	//RValueReadALine a_poss_line = s5b_6b_data_file_line_provider.get_a_line();
	//if (a_poss_line.success) {
	//	cout << "aline from LineProvider: " << a_poss_line.a_line << endl;
	//}

	print_map(word_freq_count);
	SortStringSpectralInfo sort_strings_on_spectral_scores;
	std::sort (string_spectral_scores_vec.begin()
			, string_spectral_scores_vec.end()
			, sort_strings_on_spectral_scores);

	print_report(string_spectral_scores_vec);
#endif /* 0 */

}
