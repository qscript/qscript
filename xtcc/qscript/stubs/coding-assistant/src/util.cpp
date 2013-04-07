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
	cout << "Word split: " << endl;
	for(Tok::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter) {
		std::cout << "|" << *tok_iter << "| ";
		words.push_back(*tok_iter);
	}
	std::cout << "\n";
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
