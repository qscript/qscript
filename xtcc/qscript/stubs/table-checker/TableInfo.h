/*
	Copyright : Neil Xavier D'Souza, 2013
	License: GNU GPLv2
*/

#ifndef TableInfo_h
#define TableInfo_h

#include <map>
#include <string>
#include "utils.h"

//using namespace std;



struct TableInfo
{

	//std::map<std::string, std::map <std::string, int> > qtm_freq_count_map_nq_name_stub_freq_;
	std::map <std::string, int> qtm_freq_count_map_nq_name_stub_freq_;
	//std::map<std::string, std::map <int, int> > qtm_freq_count_map_rq_;
	std::map <int, int> qtm_freq_count_map_rq_;
	int total_;
	std::string title_;
	double sigma_;
	std::string name_;
	std::string array_base_name_;
	std::map <int, std::string> stub_order_;
	std::string stub_name_;
	int no_mpn_;

	double topbox_perc;
	int    topbox_freq;
	double top2box_perc;
	int    top2box_freq;
	double top3box_perc;
	int    top3box_freq;
	double botbox_perc;
	int    botbox_freq;
	double bot2box_perc;
	int    bot2box_freq;
	double bot3box_perc;
	int    bot3box_freq;
	double mean;


	bool has_topbox;
	bool has_top2box;
	bool has_top3box;
	bool has_botbox;
	bool has_bot2box;
	bool has_bot3box;
	bool has_mean;
	RatingScaleInfo rat_scale_inf_;


	TableInfo (
		std::map <std::string, int>  p_qtm_freq_count_map_nq_name_stub_freq,
		std::map <int, int>  p_qtm_freq_count_map_rq,
		int p_total,
		std::string p_title,
		double p_sigma,
		std::string p_name,
		std::string p_array_base_name,
		std::map<int, std::string> p_stub_order,
		std::string p_stub_name,
		int p_no_mpn
		)
		: qtm_freq_count_map_nq_name_stub_freq_(p_qtm_freq_count_map_nq_name_stub_freq),
		  qtm_freq_count_map_rq_(p_qtm_freq_count_map_rq),
		  total_(p_total), title_(p_title), sigma_(p_sigma), name_(p_name),
		  array_base_name_(p_array_base_name),
		  stub_order_ (p_stub_order),
		  stub_name_(p_stub_name),
		  no_mpn_ (p_no_mpn),
		topbox_perc(),
		topbox_freq(),
		top2box_perc(),
		top2box_freq(),
		top3box_perc(),
		top3box_freq(),
		botbox_perc(),
		botbox_freq(),
		bot2box_perc(),
		bot2box_freq(),
		bot3box_perc(),
		bot3box_freq(),
		mean(),
		has_topbox(),
		has_top2box(),
		has_top3box(),
		has_botbox(),
		has_bot2box(),
		has_bot3box(),
		has_mean()
	{
		if (stub_name_.length()) {
			rat_scale_inf_ = extract_rating_scale (stub_name_);
		}
	}


	int get_freq_counts_for_top_box (
			//TableInfo & table_info
			)
	{
		std::cout << "Enter: " << __PRETTY_FUNCTION__ << ", "
			<< "getting freq counts for table: " << name_
			<< " and stub_name: " << stub_name_
			<< std::endl;
		if (!rat_scale_inf_.isRatingScale_) {
			std::cerr << __FILE__ << ", " << __LINE__
				<< ", " << __PRETTY_FUNCTION__
				<< " this function should never have been called"
				<<std::endl;
		} else {
			std::map<std::string, int>::iterator check_against_table_it = qtm_freq_count_map_nq_name_stub_freq_.begin();
			for (; check_against_table_it != qtm_freq_count_map_nq_name_stub_freq_.end(); ++check_against_table_it) {
				ExtractNumberInfo no_inf = extract_number(check_against_table_it->first);
				if (no_inf.gotANumber_ && no_inf.numberValue_ == rat_scale_inf_.ratingScaleEnd_) {
					std::cout << "found ratingScaleEnd_: " << rat_scale_inf_.ratingScaleEnd_
						<< " return value is: " << check_against_table_it->second
						<< std::endl;
					return check_against_table_it->second;
				}
			}
		}
		return -1;
	}

};


#endif /* TableInfo_h */
