#include <cmath>
#include <sstream>
#include <iostream>

#include "StringSpectralInfo.h"

bool SortStringSpectralInfo::operator()
	(const StringSpectralInfo & inf1,
			const StringSpectralInfo & inf2)
{
	return inf1.aggregate_score < inf2.aggregate_score;
}

double StringSpectralInfo::compute_aggregate_score ()
{
	using std::cout;
	using std::endl;
	if (!is_computed_score) {
		//double d1 = std::isnan(emphasizer_words_score);
		double log_emph_pos = log (emphasizer_positive_words_score  + 1);
		if (std::isnan (log_emph_pos)) {
			cout << "emphasizer_positive_words_score: " << emphasizer_positive_words_score << endl;
			std::cout << "isnan serial_no:" << serial_no << std::endl;
			exit(1);
		}
		double log_emph_neg = log (emphasizer_negative_words_score  + 1);
		if (std::isnan (log_emph_neg)) {
			std::cout << "isnan serial_no:" << serial_no << std::endl;
			cout << "emphasizer_negative_words_score: " << emphasizer_negative_words_score << endl;
			exit(1);
		}
		double log_pos_phr_score = log (pos_phrase_score + 1);
		//using std::serial_no;
		if (std::isnan (log_pos_phr_score)) {
			cout << endl;
			cout << "pos_phrase_score: " << pos_phrase_score << endl;
			cout << "nxd: isnan serial_no:" << serial_no << std::endl;
			exit(1);
		}
		double log_neg_phr_score = log (neg_phrase_score + 1);
		if (std::isnan (log_neg_phr_score)) {
			cout << endl;
			cout << "neg_phrase_score: " << neg_phrase_score << endl;
			cout << "nxd: isnan serial_no:" << serial_no << std::endl;
			exit(1);
		}
		double log_call_back_ltr_words_score = log (call_back_ltr_words_score + 1);
		if (std::isnan (log_call_back_ltr_words_score)) {
			cout << endl;
			cout << "call_back_ltr_words_score: " << call_back_ltr_words_score << endl;
			cout << "nxd: isnan serial_no:" << serial_no << std::endl;
			exit(1);
		}
		double log_gen_pos_phr_score = log (gen_pos_phr_score + 1);
		if (std::isnan (log_gen_pos_phr_score)) {
			cout << endl;
			cout << "gen_pos_phr_score: " << gen_pos_phr_score << endl;
			cout << "nxd: isnan serial_no:" << serial_no << std::endl;
			exit(1);
		}
		double log_gen_neg_phr_score = log (gen_neg_phr_score + 1);
		if (std::isnan (log_gen_neg_phr_score)) {
			cout << endl;
			cout << "gen_neg_phr_score: " << gen_neg_phr_score << endl;
			cout << "nxd: isnan serial_no:" << serial_no << std::endl;
			exit(1);
		}
		double log_pos_score = log (pos_score + 1);
		if (std::isnan (log_pos_score)) {
			cout << endl;
			cout << "pos_score: " << pos_score << endl;
			cout << "nxd: isnan serial_no:" << serial_no << std::endl;
			exit(1);
		}
		double log_neg_score = log (neg_score + 1);
		if (std::isnan (log_neg_score)) {
			cout << endl;
			cout << "neg_score: " << neg_score << endl;
			cout << "nxd: isnan serial_no:" << serial_no << std::endl;
			exit(1);
		}
		double log_neu_score = log (neutral_score + 1);
		if (std::isnan (log_neu_score)) {
			cout << endl;
			cout << "neutral_score: " << neutral_score << endl;
			cout << "nxd: isnan serial_no:" << serial_no << std::endl;
			exit(1);
		}
		double log_oth_score = log (other_words_score + 1);
		if (std::isnan (log_oth_score)) {
			cout << endl;
			cout << "other_words_score: " << other_words_score << endl;
			cout << "nxd: isnan serial_no:" << serial_no << std::endl;
			exit(1);
		}
		double log_emph_score = log (emphasizer_words_score + 1);
		if (std::isnan (log_emph_score)) {
			cout << endl;
			cout << "emphasizer_words_score: " << emphasizer_words_score << endl;
			cout << "nxd: isnan serial_no:" << serial_no << std::endl;
			exit(1);
		}
		double log_management_words_score = log (management_words_score + 1);
		if (std::isnan (log_management_words_score)) {
			cout << endl;
			cout << "management_words_score: " << management_words_score << endl;
			cout << "nxd: isnan serial_no:" << serial_no << std::endl;
			exit(1);
		}
		double log_pwrm_words_score = log (pwrm_words_score + 1);
		if (std::isnan (log_pwrm_words_score)) {
			cout << endl;
			cout << "pwrm_words_score: " << pwrm_words_score << endl;
			cout << "nxd: isnan serial_no:" << serial_no << std::endl;
			exit(1);
		}
		double log_reason_words_score = log (reason_words_score + 1);
		if (std::isnan (log_reason_words_score)) {
			cout << endl;
			cout << "reason_words_score: " << reason_words_score << endl;
			cout << "nxd: isnan serial_no:" << serial_no << std::endl;
			exit(1);
		}
		double log_regex_score = log (regex_score + 1);
		if (std::isnan (log_regex_score)) {
			cout << endl;
			cout << "regex_score: " << regex_score << endl;
			cout << "nxd: isnan serial_no:" << serial_no << std::endl;
			exit(1);
		}
		double log_suggestions_score = log (suggestions_score + 1);
		if (std::isnan (log_suggestions_score)) {
			cout << endl;
			cout << "suggestions_score: " << suggestions_score << endl;
			cout << "nxd: isnan serial_no:" << serial_no << std::endl;
			exit(1);
		}
		int any_negatives = 1;
		if (neg_score) {
			any_negatives = -1;
		}
		if (pos_phrase_score > 0 || emphasizer_positive_words_score > 0 || gen_pos_phr_score > 0) {
			any_negatives = 1;
		}
		if (emphasizer_negative_words_score || neg_phrase_score || gen_neg_phr_score
			) {
			any_negatives = -1;
		}

		aggregate_score =
				+ (-100000  * log_emph_neg)
				+ ( 50000   * log_emph_pos)
				+ (-1000   * log_neg_phr_score)
				+ (500     * log_pos_phr_score)
				+ (-100000000 * log_call_back_ltr_words_score)
				+ (-10000   * log_gen_neg_phr_score)
				+ (5000    * log_gen_pos_phr_score)
				+ (-1000    * log_neg_score)
				+ (500      * log_pos_score)
				+ (-1      * log_neu_score)
				+ (5       * log_oth_score)
				+ (10     * log_emph_score)
				+ (500000   * any_negatives * log_management_words_score)
				+ (500000   * any_negatives * log_pwrm_words_score)
				+ (2500    * log_reason_words_score)
				+ (-800    * log_regex_score)
				+ (10000000  *any_negatives * log_suggestions_score)
				;
		is_computed_score = true;
		if (isnan(aggregate_score)) {
			cout << "nxd: isnan aggregate_score serial_no:" << serial_no << std::endl;
			exit(1);
		}
	}
	return aggregate_score;
}

std::string StringSpectralInfo::report() const
{
	using std::cout;
	using std::endl;
	std::stringstream s1;
	if (isnan(aggregate_score)) {
		cout
			<< __PRETTY_FUNCTION__
			<< "nxd: isnan aggregate_score serial_no:" << serial_no << std::endl;
		exit(1);
	}
	std::string any_match =
		  pos_emph_word_match +"|"
		+ neg_emph_word_match +"|"
		+ pos_phr_int_match +"|"
		+ neg_phr_int_match +"|"
		+ pos_gen_phr_match +"|"
		+ neg_gen_phr_match +"|"
		+ positive_match +"|"
		+ negative_match +"|"
		+ neutral_match +"|"
		+ other_match +"|"
		+ emph_match +"|"
		+ mnmng_match +"|"
		+ pwrm_match +"|"
		+ reas_match +"|"
		+ call_back_ltr_match +"|"
		+ suggestions_match;
	s1
		<< serial_no << ","
		<< aggregate_score  << ","
		<< any_match << ","
		<< emphasizer_positive_words_score  << ","
		<< emphasizer_negative_words_score  << ","
		<< pos_phrase_score << ","
		<< neg_phrase_score << ","
		<< gen_pos_phr_score << ","
		<< gen_neg_phr_score << ","
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
		//<< phrases.size()   << ","
		//<< sentences.size()   << ","
		<< pos_emph_word_match << ","
		<< neg_emph_word_match << ","
		<< pos_phr_int_match << ","
		<< neg_phr_int_match << ","
		<< pos_gen_phr_match << ","
		<< neg_gen_phr_match << ","
		<< positive_match << ","
		<< negative_match << ","
		<< neutral_match << ","
		<< other_match << ","
		<< emph_match << ","
		<< mnmng_match << ","
		<< pwrm_match << ","
		<< reas_match << ","
		<< call_back_ltr_match << ","
		<< suggestions_match << ","
		<< "\"" << raw_phrase << "\"" << ","
		<< "\"" << raw_verbatim << "\"" << ","

#if 0
#endif /* 0 */
		<< std::endl;

	return s1.str();

}
