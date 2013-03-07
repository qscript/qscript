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

	TableInfo (
		map <string, int>  p_qtm_freq_count_map_nq_name_stub_freq,
		map <int, int>  p_qtm_freq_count_map_rq,
		int p_total,
		string p_title,
		double p_sigma,
		string p_name,
		string p_array_base_name
		)
		: qtm_freq_count_map_nq_name_stub_freq_(p_qtm_freq_count_map_nq_name_stub_freq),
		  qtm_freq_count_map_rq_(p_qtm_freq_count_map_rq),
		  total_(p_total), title_(p_title), sigma_(p_sigma), name_(p_name),
		  array_base_name_(p_array_base_name)
	{ }


};


#endif /* TableInfo_h */
