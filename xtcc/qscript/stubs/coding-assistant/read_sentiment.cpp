// CopyRight Neil Xavier DSouza
// GNU GPL V2
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include "util.h"

using namespace std;
map <string, int> word_freq_count;

	set <string> negative_words_of_interest;
	set <string> positive_words_of_interest, neutral_words_of_interest;
	set <string> other_words_of_interest;
	set <string> emphasizer_words_of_interest;
	set <string> negative_phrase_of_interest;
	set <string> positive_phrase_of_interest;
	set <string> words_indicating_reason;
	set <string> words_having_pwrm_rm_cm;
	set <string> words_indicating_management;

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

	using namespace std;
void process_file (std::ifstream & data_file)
{
	string a_line;
	while (std::getline(data_file, a_line)) {
		cout << "got line: " << a_line << endl;
	}
}

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

int check_for_phrase_of_interest(const set<string> & phrase_of_interest, string & user_phrase)
{
	int result = 0;
	for (auto it = phrase_of_interest.begin(); it != phrase_of_interest.end();
			++it) {
		string  a_phrase_of_interest = *it;
		if (user_phrase.find (a_phrase_of_interest)!= string::npos) {
			//addnl_info += ": |" + s2 + "| has word of interest: |" + neg_word + "|";
			result = result + 100;
		}
	}
	return result;
}

int check_for_words_of_interest(const set<string> & words_of_interest, vector<string> phrase_in_words)
{
	int score = 0;
	for (int i=0; i<phrase_in_words.size(); ++i) {
		const string & a_word = phrase_in_words[i];
		auto found = words_of_interest.find (a_word);
		if (found != words_of_interest.end()) {
			++score;
		}
	}
	return score;
}

int check_for_emphasizer_phrase(const set<string> & emphasizers, const set<string> & adjectives
		,  const string & phrase)
{
	int score = 0;
	for (auto it1 = emphasizers.begin(); it1 != emphasizers.end(); ++it1) {
		for (auto it2 = adjectives.begin(); it2 != adjectives.end(); ++it2) {
			string a_possible_phrase = *it1 + " " + *it2;
			if (phrase.find(a_possible_phrase) != string::npos) {
				++score;
			}
		}
	}
	return score;
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
			<< "oth_wd" << ","
			<< "emph_wd" << ","
			<< "mngmt_wd" << ","
			<< "pwrm_wd" << ","
			<< "reasn_wd " << ","
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
			int emphasizer_positive_words_score = check_for_emphasizer_phrase(emphasizer_words_of_interest, positive_words_of_interest, phrases[j]);
			int emphasizer_negative_words_score = check_for_emphasizer_phrase(emphasizer_words_of_interest, negative_words_of_interest, phrases[j]);
			int pos_phrase_score = check_for_phrase_of_interest(positive_phrase_of_interest, phrases[j]);
			int neg_phrase_score = check_for_phrase_of_interest(negative_phrase_of_interest, phrases[j]);
			int neg_score = check_for_words_of_interest(negative_words_of_interest, words);
			int pos_score = check_for_words_of_interest(positive_words_of_interest, words);
			int other_words_score = check_for_words_of_interest(other_words_of_interest, words);
			int emphasizer_words_score = check_for_words_of_interest(emphasizer_words_of_interest, words);
			int management_words_score = check_for_words_of_interest(words_indicating_management, words);
			int pwrm_words_score = check_for_words_of_interest(words_having_pwrm_rm_cm, words);
			int reason_words_score = check_for_words_of_interest(words_indicating_reason, words);
			int any_cls = emphasizer_positive_words_score + emphasizer_negative_words_score
					+ pos_phrase_score + neg_phrase_score + neg_score + pos_score
					+ other_words_score + emphasizer_words_score + management_words_score
					+ pwrm_words_score + reason_words_score;
			phrase_scores
					<< any_cls << ","
					<< emphasizer_positive_words_score  << ","
					<< emphasizer_negative_words_score  << ","
					<< pos_phrase_score << ","
					<< neg_phrase_score << ","
					<< pos_score << ","
					<< neg_score << ","
					<< other_words_score  << ","
					<< emphasizer_words_score  << ","
					<< management_words_score  << ","
					<< pwrm_words_score  << ","
					<< reason_words_score  << ","
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

void populate_emphasizer_words_of_interest()
{
	emphasizer_words_of_interest.insert("ALWAYS");
	emphasizer_words_of_interest.insert("NEVER");
	emphasizer_words_of_interest.insert("VERY");
}

void populate_other_words_of_interest()
{
	other_words_of_interest.insert("TIME");
	other_words_of_interest.insert("SERVICE");
	other_words_of_interest.insert("RECOMMEND");
	other_words_of_interest.insert("VALUE");
	other_words_of_interest.insert("RELATIONSHIP");
	other_words_of_interest.insert("SATISFIED");
	other_words_of_interest.insert("FRIENDS");
	other_words_of_interest.insert("AVAILABLE");
	other_words_of_interest.insert("PROBLEM");
	other_words_of_interest.insert("ISSUE");
	other_words_of_interest.insert("TAKE");
	other_words_of_interest.insert("MANY");
	other_words_of_interest.insert("REFER");
	other_words_of_interest.insert("EXPERIENCE");
	other_words_of_interest.insert("INFORM");
	other_words_of_interest.insert("RESPONDS");
	other_words_of_interest.insert("RESOLVED");
	other_words_of_interest.insert("ATTITUDE");
	other_words_of_interest.insert("QUITE");
	other_words_of_interest.insert("DESPITE");
	other_words_of_interest.insert("ADVANTAGE");
	other_words_of_interest.insert("TROUBLE");
	other_words_of_interest.insert("PROACTIVE");
}

void populate_negative_words_of_interest()
{
	negative_words_of_interest.insert("ELUSIVENESS");
	negative_words_of_interest.insert("ENEMIES");
	negative_words_of_interest.insert("NO");
	negative_words_of_interest.insert("NOT");
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
}

void populate_negative_phrase_of_interest()
{
	negative_phrase_of_interest.insert("DOES NOT");
	negative_phrase_of_interest.insert("DO NOT");
	negative_phrase_of_interest.insert("IS NOT");
	negative_phrase_of_interest.insert("NOT BE");
}

void populate_positive_phrase_of_interest()
{
	positive_phrase_of_interest.insert("ALWAYS HELP");
	positive_phrase_of_interest.insert("ALWAYS THERE");
	positive_phrase_of_interest.insert("IS GOOD");
	positive_phrase_of_interest.insert("HELPS ME");
}

void populate_neutral_words_of_interest()
{
	neutral_words_of_interest.insert("OK");
}

void populate_positive_words_of_interest()
{
	positive_words_of_interest.insert("HAPPY");
	positive_words_of_interest.insert("EXPLAINS");
	positive_words_of_interest.insert("TRANSPARENT");
	positive_words_of_interest.insert("KNOWLEDGE");
	positive_words_of_interest.insert("KNOWLEGE");
	positive_words_of_interest.insert("KNOWLEDGE");
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
}

void populate_words_indicating_reason ()
{
	words_indicating_reason.insert("BECAUSE");
	words_indicating_reason.insert("BCOZ");
	words_indicating_reason.insert("REASON");
}

void populate_words_indicating_management()
{
	words_indicating_management.insert("MANAGEMENT");
}

void populate_words_having_pwrm_rm_cm()
{
	words_having_pwrm_rm_cm.insert("RM");
	words_having_pwrm_rm_cm.insert("PWRM");
	words_having_pwrm_rm_cm.insert("CM");
	words_having_pwrm_rm_cm.insert("CUSTOMER");
	words_having_pwrm_rm_cm.insert("BANK");
	words_having_pwrm_rm_cm.insert("HSBC");
}

int main()
{
	populate_positive_words_of_interest();
	populate_negative_words_of_interest();
	populate_other_words_of_interest();
	populate_emphasizer_words_of_interest();
	populate_negative_phrase_of_interest();
	populate_positive_phrase_of_interest();
	populate_words_indicating_reason();
	populate_words_indicating_management();
	populate_words_having_pwrm_rm_cm();

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
