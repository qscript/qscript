#ifndef TableInfo_h
#define TableInfo_h

#include <map>
#include <string>

using namespace std;

struct TableInfo
{

	//map<string, map <string, int> > qtm_freq_count_map_nq_name_stub_freq_;
	map <string, int> qtm_freq_count_map_nq_name_stub_freq_;
	//map<string, map <int, int> > qtm_freq_count_map_rq_;
	map <int, int> qtm_freq_count_map_rq_;
	int total_;
	string title_;
	double sigma_;
	string name_;
	string array_base_name_;
	map <int, string> stub_order_;
	string stub_name;
	int no_mpn;

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


	TableInfo (
		map <string, int>  p_qtm_freq_count_map_nq_name_stub_freq,
		map <int, int>  p_qtm_freq_count_map_rq,
		int p_total,
		string p_title,
		double p_sigma,
		string p_name,
		string p_array_base_name,
		map<int, string> p_stub_order
		)
		: qtm_freq_count_map_nq_name_stub_freq_(p_qtm_freq_count_map_nq_name_stub_freq),
		  qtm_freq_count_map_rq_(p_qtm_freq_count_map_rq),
		  total_(p_total), title_(p_title), sigma_(p_sigma), name_(p_name),
		  array_base_name_(p_array_base_name),
		  stub_order_ (p_stub_order),
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
	{ }


};


#endif /* TableInfo_h */
