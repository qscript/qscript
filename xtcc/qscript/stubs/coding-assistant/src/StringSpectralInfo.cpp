#include <cmath>
#include <sstream>
#include "StringSpectralInfo.h"

bool SortStringSpectralInfo::operator()
	(const StringSpectralInfo & inf1,
			const StringSpectralInfo & inf2)
{
	return inf1.aggregate_score < inf2.aggregate_score;
}

double StringSpectralInfo::compute_aggregate_score ()
{
	if (!is_computed_score) {
		//double d1 = std::isnan(emphasizer_words_score);
		double log_emph_pos = log (emphasizer_positive_words_score  + 1);
		double log_emph_neg = log (emphasizer_negative_words_score  + 1);
		double log_pos_phr_score = log (pos_phrase_score + 1);
		double log_neg_phr_score = log (neg_phrase_score + 1);
		double log_call_back_ltr_words_score = log (call_back_ltr_words_score + 1);
		double log_gen_pos_phr_score = log (gen_pos_phr_score + 1);
		double log_gen_neg_phr_score = log (gen_neg_phr_score + 1);
		double log_pos_score = log (pos_score + 1);
		double log_neg_score = log (neg_score + 1);
		double log_neu_score = log (neutral_score + 1);
		double log_oth_score = log (other_words_score + 1);
		double log_emph_score = log (emphasizer_words_score + 1);
		double log_management_words_score = log (management_words_score + 1);
		double log_pwrm_words_score = log (pwrm_words_score + 1);
		double log_reason_words_score = log (reason_words_score + 1);
		double log_regex_score = log (regex_score + 1);

		aggregate_score =

				+ (-10000  * log_emph_neg)
				+ ( 1000   * log_emph_pos)
				+ (-1000   * log_neg_phr_score)
				+ (100     * log_pos_phr_score)
				+ (-100000 * log_call_back_ltr_words_score)
				+ (-1000   * log_gen_neg_phr_score)
				+ (1000    * log_gen_pos_phr_score)
				+ (-100    * log_neg_score)
				+ (10      * log_pos_score)
				+ (-1      * log_neu_score)
				+ (5       * log_oth_score)
				+ (100     * log_emph_score)
				+ (10000   * log_management_words_score)
				+ (5000    * log_pwrm_words_score)
				+ (2500    * log_reason_words_score)
				+ (-200    * log_regex_score);
		is_computed_score = true;
	}
	return aggregate_score;
}

std::string StringSpectralInfo::report() const
{
	std::stringstream s1;
	s1
			<< serial_no << ","
			<< aggregate_score << ","
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
			<< "\"" << raw_phrase << "\"" << ","
			<< "\"" << raw_verbatim << "\"" << ","
#if 0
#endif /* 0 */
			<< std::endl;
	return s1.str();

}
