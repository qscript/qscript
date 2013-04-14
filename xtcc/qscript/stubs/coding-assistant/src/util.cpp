#include <regex.h>
#include "util.h"
using namespace std;

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
	//cout << "Word split: " << endl;
	for(Tok::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter) {
		//std::cout << "|" << *tok_iter << "| ";
		words.push_back(*tok_iter);
	}
	//std::cout << "\n";
	return words;
	//return EXIT_SUCCESS;
}

LineProvider::LineProvider(std::string s): file(s.c_str())
{
	//cout << "got file to open: " << s << endl;
	if (file) {
		//std::string a_line;
		//bool could_read = getline(file, a_line);
		//cout << "read: " << a_line << endl;
	} else {
		cerr <<  "Unable to open file: " << s << " ... exiting" << endl;
		exit(1);
	}
}


RValueReadALine LineProvider::get_a_line()
{
	RValueReadALine r_value;
	std::string a_line;
	if (std::getline(file,a_line)) {
		r_value.success = true;
		r_value.a_line = boost::to_upper_copy(trim(a_line));
	} else {
		//cout << "could_read false" << endl;
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


vector<string> tokenize_into_sentences(string &s)
{
	//boost::char_separator<char> sep("-;|");
	//
	vector<string> sentences;
	int found = s.find ("A/C");
	// some regular expression patterns to prevent splitting
	vector <regex_t> sentence_reg_exp_of_interest;
	string regex_patt_1("\\(CALL\\|CALL AT\\)\\{1\\} [0-9]\\{1,2\\}\\(\\.\\|/\\)[0-9]\\{1,2\\}");
	//string a_regex     ("CALL [0-9]\\{1,2\\}\\.[0-9]\\{1,2\\}");
	static regex_t regex_pattern;
	bool first_time = true;
	if (first_time) {
		// yup - a memory leak - but we allocate only once
		regcomp (&regex_pattern, regex_patt_1.c_str(), REG_ICASE);
		first_time = false;
	}
	regmatch_t p_match[5];
	int n_match=5;
	int regex_result = regexec (&regex_pattern, s.c_str(), n_match, p_match, 0);
	//if (s.find("call ")) {
	//	cout << "sentence had word call:" << s << endl;
	//}

	if (regex_result == 0) {
		cerr << "Found REGEX in sentence split"
			<< "|" << s
			<< endl;
		for (int i=0; i<n_match; ++i) {
			if (p_match[i].rm_so != -1) {
				int pos = s.find (".");
				if (pos != string::npos && pos < p_match[i].rm_eo) {
					cout << "old s:" << s << endl;
					s.replace(s.begin()+pos       , s.begin()+pos+1       , 1, ':');
                               //nxd_str1.replace(nxd_str1.begin()+pos, nxd_str1.begin()+pos+1, 1, ':' );
					cout << "new s:" << s << endl;
					cout << "dot = . present at : " << pos << endl;
				}

				int pos2 = s.find ("/");
				if (pos2 != string::npos && pos2 < p_match[i].rm_eo) {
					cout << "old s:" << s << endl;
					s.replace(s.begin()+pos2       , s.begin()+pos2+1       , 1, '-');
                               //nxd_str1.replace(nxd_str1.begin()+pos, nxd_str1.begin()+pos+1, 1, ':' );
					cout << "new s:" << s << endl;
					cout << "dot = . present at : " << pos << endl;
				}
				int pos3 = s.find ("CALL ");
				if (pos3 != string::npos && pos3 < p_match[i].rm_eo) {
					const string replace_text("CALL BACK");
					cout << "old s:" << s << endl;
					s.replace(s.begin()+pos3, s.begin()+pos3+5, replace_text.begin(), replace_text.end());
					cout << "new s:" << s << endl;
				}

			}
		}
	}

	if (found == string::npos) {
		boost::char_separator<char> sep("./");
		tokenizer tokens(s, sep);
		for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter) {
			//std::cout << "<" << *tok_iter << "> ";
			sentences.push_back(*tok_iter);
		}
	}  else {
		boost::char_separator<char> sep(".");
		tokenizer tokens(s, sep);
		for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter) {
			//std::cout << "<" << *tok_iter << "> ";
			sentences.push_back(*tok_iter);
		}
	}
	return sentences;
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
