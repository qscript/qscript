#ifndef StringSpectral_info_h
#define StringSpectral_info_h

#include <string>

struct StringSpectralInfo {
	int serial_no;
	std::string pos_emph_word_match;
	long long emphasizer_positive_words_score;
	std::string neg_emph_word_match;
	long long emphasizer_negative_words_score;
	std::string pos_phr_int_match;
	long long pos_phrase_score;
	std::string neg_phr_int_match;
	long long neg_phrase_score;
	std::string call_back_ltr_match;
	long long call_back_ltr_words_score;
	std::string pos_gen_phr_match;
	long long gen_pos_phr_score;
	std::string neg_gen_phr_match;
	long long gen_neg_phr_score;
	std::string positive_match;
	long long pos_score;
	std::string negative_match;
	long long neg_score;
	std::string neutral_match;
	long long neutral_score;
	std::string other_match ;
	long long other_words_score ;
	std::string emph_match ;
	long long emphasizer_words_score ;
	std::string mnmng_match ;
	long long management_words_score ;
	std::string pwrm_match ;
	long long pwrm_words_score ;
	std::string reas_match ;
	long long reason_words_score ;
	std::string addnl_info_regex_match;
	long long regex_score;
	std::string suggestions_match;
	long long suggestions_score;
	double aggregate_score;
	bool is_computed_score;
	std::string raw_phrase;
	std::string raw_verbatim;

	StringSpectralInfo (

		int p_serial_no,
		std::string p_pos_emph_word_match,
		long long p_emphasizer_positive_words_score,
		std::string p_neg_emph_word_match,
		long long p_emphasizer_negative_words_score,
		std::string p_pos_phr_int_match,
		long long p_pos_phrase_score,
		std::string p_neg_phr_int_match,
		long long p_neg_phrase_score,
		std::string p_call_back_ltr_match,
		long long p_call_back_ltr_words_score,
		std::string p_pos_gen_phr_match,
		long long p_gen_pos_phr_score,
		std::string p_neg_gen_phr_match,
		long long p_gen_neg_phr_score,
		std::string p_positive_match,
		long long p_pos_score,
		std::string p_negative_match,
		long long p_neg_score,
		std::string p_neutral_match,
		long long p_neutral_score,
		std::string p_other_match ,
		long long p_other_words_score ,
		std::string p_emph_match ,
		long long p_emphasizer_words_score ,
		std::string p_mnmng_match ,
		long long p_management_words_score ,
		std::string p_pwrm_match ,
		long long p_pwrm_words_score ,
		std::string p_reas_match ,
		long long p_reason_words_score ,
		std::string p_addnl_info_regex_match,
		long long p_regex_score,

		std::string p_suggestions_match,
		long long p_suggestions_score,

		const std::string & p_raw_phrase,
		const std::string & p_raw_verbatim

	):
		serial_no (p_serial_no),
		pos_emph_word_match (p_pos_emph_word_match),
		emphasizer_positive_words_score (p_emphasizer_positive_words_score),
		neg_emph_word_match (p_neg_emph_word_match),
		emphasizer_negative_words_score (p_emphasizer_negative_words_score),
		pos_phr_int_match (p_pos_phr_int_match),
		pos_phrase_score (p_pos_phrase_score),
		neg_phr_int_match (p_neg_phr_int_match),
		neg_phrase_score (p_neg_phrase_score),
		call_back_ltr_match (p_call_back_ltr_match),
		call_back_ltr_words_score (p_call_back_ltr_words_score),
		pos_gen_phr_match (p_pos_gen_phr_match),
		gen_pos_phr_score (p_gen_pos_phr_score),
		neg_gen_phr_match (p_neg_gen_phr_match),
		gen_neg_phr_score (p_gen_neg_phr_score),
		positive_match (p_positive_match),
		pos_score (p_pos_score),
		negative_match (p_negative_match),
		neg_score (p_neg_score),
		neutral_match (p_neutral_match),
		neutral_score (p_neutral_score),
		other_match  (p_other_match ),
		other_words_score  (p_other_words_score ),
		emph_match  (p_emph_match ),
		emphasizer_words_score  (p_emphasizer_words_score ),
		mnmng_match  (p_mnmng_match ),
		management_words_score  (p_management_words_score ),
		pwrm_match  (p_pwrm_match ),
		pwrm_words_score  (p_pwrm_words_score),
		reas_match  (p_reas_match ),
		reason_words_score  (p_reason_words_score ),
		addnl_info_regex_match (p_addnl_info_regex_match),
		regex_score (p_regex_score),
		suggestions_match (p_suggestions_match),
		suggestions_score (p_suggestions_score),
		aggregate_score (0.0),
		is_computed_score(false),
		raw_phrase (p_raw_phrase),
		raw_verbatim (p_raw_verbatim)
	{ compute_aggregate_score(); }

	double compute_aggregate_score ();
	std::string report() const;
};

struct SortStringSpectralInfo
{
	bool operator() (const StringSpectralInfo & inf1,
			const StringSpectralInfo & inf2);
};


#endif /*  std::stringSpectral_info_h */
