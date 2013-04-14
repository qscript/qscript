#ifndef util_h
#define util_h

#include <boost/algorithm/string.hpp>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <set>
#include <fstream>

std::string trim(const std::string& str,
                 const std::string& whitespace = " \t");
std::vector<std::string> split_into_phrases(const std::string &s);
std::vector<std::string> split_into_words(const std::string &s);
std::vector<std::string> tokenize_csv_components_into_fields(std::string &a_csv_line);
std::vector<std::string> tokenize_into_sentences(std::string &s);

struct RValueReadALine
{
	bool success;
	std::string a_line;
	RValueReadALine (): success (false), a_line()
	{ }
};

struct LineProvider
{
	std::ifstream file;
	LineProvider(std::string s);

	RValueReadALine get_a_line();

};

#endif /* util_h */
