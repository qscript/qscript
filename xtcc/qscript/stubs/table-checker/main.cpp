/*
	Copyright : Neil Xavier D'Souza, 2013
	License: GNU GPL2
*/

#include <inttypes.h>
#include <sys/types.h>
#include <limits.h>
#include <string>
#include <iostream>
#include <fstream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <getopt.h>
#include "const_defs.h"
#include "gen_src/lex_tab.h"
#include "TableInfo.h"

	using std::cout;
	using std::endl;
	using std::cerr;
	using std::stringstream;
	using std::map;
	using std::string;
	using std::vector;


namespace program_options_ns {
	std::string table_file_name;
	bool table_file_name_flag;
	std::string count_file_name;
	bool count_file_name_flag;

}

extern void yyrestart(FILE *input_file);
extern int32_t yyparse();
extern int32_t qtm_table_output_parse();
extern int yylex();
extern void yyerror(const char * s);

extern map<string, map <string, int> > freq_count_map_nq_name_stub_freq;
extern map<string, map <int, int> > freq_count_map_nq_name_code_freq;
extern map<string, map <string, int> > freq_count_map_nq_name_stub_code;
extern map<string, map <int, string> > freq_count_map_nq_name_code_stub;
extern map<string, map <int, int> > freq_count_map_rq;

extern map <string, struct TableInfo *> table_info_map;
extern multimap <string, struct TableInfo *> table_info_multimap;
//extern map<string, map <string, int> > qtm_freq_count_map_nq_name_stub_freq;
//extern map<string, map <int, int> >    qtm_freq_count_map_nq_name_code_freq;
//extern map<string, map <string, int> > qtm_freq_count_map_nq_name_stub_code;
//extern map<string, map <int, int> > qtm_freq_count_map_rq;
//

struct ErrorReport
{
	int nStubErrors_;
	int nStubWarnings_;
	int nStubs_;
	vector<string>  stubErrorReasons_;
	int nTitleErrors_;
	int nTitleWarnings_;
	vector<string>  titleErrorReasons_;
	int nBaseTextErrors_;
	int nBaseTextWarnings_;
	vector<string>  baseTextErrorReasons_;
	int nMatched_;
	ErrorReport ()
		:  nStubErrors_(0), nStubWarnings_(0), nStubs_(0),
		   stubErrorReasons_(),
		   nTitleErrors_(0), nTitleWarnings_(0),
		   baseTextErrorReasons_(),
		   nMatched_(0)
	{ }


};


void check_tables(
	//map<string, map <string, int> > & qtm_freq_count_map_nq_name_stub_freq,
	map <string, struct TableInfo *> table_info_map,
	map<string, map <string, int> > & freq_count_map_nq_name_stub_freq,
	map<string, map <int, int> > & freq_count_map_rq
		);

void usage (char * argv[])
{
	cerr << "Usage: "
		<< argv[0] << " -c <count-file-name> -t <table file name>\n" <<   endl;
	exit(1);
}

int main(int argc, char *  argv[])
{

	int c;
	while ( (c = getopt(argc, argv, "c:t:")) != -1 ) {
		char ch = optopt;
		switch(c){

		case 't':
			program_options_ns::table_file_name = optarg;
			program_options_ns::table_file_name_flag = true;
			break;
		case 'c':
			program_options_ns::count_file_name = optarg;
			program_options_ns::count_file_name_flag = true;
			break;

		default:
			usage(argv);
		}
	}
	if (!(program_options_ns::table_file_name_flag && program_options_ns::count_file_name_flag)) {
		cerr << "please pass table filename as option to -t "
			<< " and count filename as option to -c" << endl;
		usage(argv);
	}

	{
		//std::string fname ("cmb_decision_maker.freq_count.csv");
		//FILE * qscript_freq_file = fopen(fname.c_str(), "rb");
		FILE * qscript_freq_file = fopen(program_options_ns::count_file_name.c_str(), "rb");
		if (!qscript_freq_file){
			cerr << " Unable to open: " << program_options_ns::count_file_name << " for read ... exiting" << endl;
			exit(1);
		}
		yyrestart(qscript_freq_file);
		if (!yyparse()) {
			cout << "Input parsed successfully" << endl;
		} else {
			cerr << "Error parsing freq_count file:" << program_options_ns::count_file_name << endl
				<< "exiting ..." << endl;
			exit(1);


		}
	}
	{
		//std::string fname ("T.CSV");
		//std::string fname ("t2.csv");
		FILE * qtm_csv_file = fopen(program_options_ns::table_file_name.c_str(), "rb");
		if (!qtm_csv_file) {
			cerr << " Unable to open: " << program_options_ns::table_file_name << " for read ... exiting" << endl;
			exit(1);
		}
		qtm_table_output_restart(qtm_csv_file);
		//if (!yyparse())
		if (!qtm_table_output_parse()) {
			cout << "Input parsed successfully" << endl;
		} else {
			cerr << "Error parsing tables file:" << program_options_ns::table_file_name << endl
				<< "exiting ..." << endl;
			exit(1);
		}

	}
	check_tables(table_info_map,
			freq_count_map_nq_name_stub_freq,
			freq_count_map_rq
			);


}

// from simple_compiler/src/utils.{h,cpp}
struct RatingScaleInfo
{
	bool isRatingScale_;
	bool isReversed_;
	int ratingScaleStart_;
	int ratingScaleEnd_;
	RatingScaleInfo ()
		: isRatingScale_ (false), isReversed_(false),
		  ratingScaleStart_(0), ratingScaleEnd_(0)
	{ }
};

struct RatingScaleInfo extract_rating_scale (string s)
{
	RatingScaleInfo rat_scale_inf;
	//rat_scale_inf.isReversed_ = false;
	int rat_scale = 0;
	if (isdigit(s[s.size()-1]) /*&& !(range_name[range_name.size()-1]=='0')*/ ) {
		rat_scale_inf.isRatingScale_ = true;
		int i = s.size()-1;
		int factor = 1;
		while (isdigit(s[i])) {
			rat_scale += (s[i] - '0') * factor;
			factor *=10;
			--i;
		}
		rat_scale_inf.ratingScaleEnd_ = rat_scale;
		if (s[i] == 'r' && s[i-1] == '_') {
			rat_scale_inf.isReversed_ = true;
		}
	} else {
		rat_scale_inf.isRatingScale_ = false;
	}
	cout	<< __FILE__ << ", "
		<< __LINE__ << ","
		<< __PRETTY_FUNCTION__ << ","
		<< "input parameter:" << s
		<< ", RatingScaleInfo: "
		<< ", isRatingScale_: " << rat_scale_inf.isRatingScale_
		<< ", isReversed_: " << rat_scale_inf.isReversed_
		<< ", ratingScaleEnd_: " << rat_scale_inf.ratingScaleEnd_
		<< endl;
	return rat_scale_inf;
}

template <class t1, class t2>
void print_map (const map<t1, t2> & the_map)
{
	for (typename map<t1, t2>::const_iterator map_it = the_map.begin();
			map_it != the_map.end(); ++map_it) {
		cout	<< "key: |" << map_it->first <<  "|"
			<< ", value: |" << map_it->second << "|"
			<< endl;
	}
	cout << endl;
}

bool does_top_2_box_match (
	TableInfo  & the_table_info,
	map<string, int> & the_freq_counts,
	RatingScaleInfo rat_scale_inf,
	map <int, string> & table_code_stub_map,
	struct ErrorReport & p_error_report
	)
{
	bool result = true;
	cout << __PRETTY_FUNCTION__
		<< endl
		<< "table name: " << the_table_info.name_
		<< "array_base_name_ : " << the_table_info.array_base_name_
		<< endl;
	static bool not_printed = true;
	if (not_printed) {
		cerr << "put check - some scales start at 0 instead of 1 - modify this function"
			<< endl;
		not_printed = false;
	}
	map <int, string> ::const_iterator END = table_code_stub_map.end();
	map <int, string> ::const_iterator highest = table_code_stub_map.find (rat_scale_inf.ratingScaleEnd_);
	map <int, string> ::const_iterator second_highest = table_code_stub_map.find (rat_scale_inf.ratingScaleEnd_ - 1);
	map <int, string> ::const_iterator third_highest = table_code_stub_map.find (rat_scale_inf.ratingScaleEnd_ - 2);

	map <int, string> ::const_iterator lowest = table_code_stub_map.find (1);
	map <int, string> ::const_iterator second_lowest = table_code_stub_map.find (2);
	map <int, string> ::const_iterator third_lowest = table_code_stub_map.find (3);
	int sum_top2 = 0,
	    sum_top3 = 0,
	    sum_bot2 = 0,
	    sum_bot3 = 0
	    ;

	if (highest != END) {
		map <string, int> :: const_iterator fq_nq_it = the_freq_counts.find (highest->second);
		if (fq_nq_it != the_freq_counts.end()) {
			sum_top2 += fq_nq_it->second;
			sum_top3 += fq_nq_it->second;
		}
	}
	if (second_highest != END) {
		map <string, int> :: const_iterator fq_nq_it = the_freq_counts.find (second_highest->second);
		if (fq_nq_it != the_freq_counts.end()) {
			sum_top2 += fq_nq_it->second;
			sum_top3 += fq_nq_it->second;
		}
	}
	if (third_highest != END) {
		map <string, int> :: const_iterator fq_nq_it = the_freq_counts.find (third_highest->second);
		if (fq_nq_it != the_freq_counts.end()) {
			sum_top3 += fq_nq_it->second;
		}
	}

	if (lowest != END) {
		map <string, int> :: const_iterator fq_nq_it = the_freq_counts.find (lowest->second);
		if (fq_nq_it != the_freq_counts.end()) {
			sum_bot2 += fq_nq_it->second;
			sum_bot3 += fq_nq_it->second;
		}
	}
	if (second_lowest != END) {
		map <string, int> :: const_iterator fq_nq_it = the_freq_counts.find (second_lowest->second);
		if (fq_nq_it != the_freq_counts.end()) {
			sum_bot2 += fq_nq_it->second;
			sum_bot3 += fq_nq_it->second;
		}
	}
	if (third_lowest != END) {
		map <string, int> :: const_iterator fq_nq_it = the_freq_counts.find (third_lowest->second);
		if (fq_nq_it != the_freq_counts.end()) {
			sum_bot3 += fq_nq_it->second;
		}
	}

	cout	<< "sum_top2: |" << sum_top2 << "|"
		<< ", table TOP 2 BOX NET: |" << the_table_info.top2box_freq << "|"
		<< endl;

	if (the_table_info.has_top2box && sum_top2 != the_table_info.top2box_freq) {
		stringstream reasons_str;
		reasons_str << "top2box_freq did not match:"
			<< "table shows:" << the_table_info.top2box_freq
			<< ", I expect it to be: "
			<< sum_top2;
		p_error_report.stubErrorReasons_.push_back (reasons_str.str());
		result = false;
	}

	if (the_table_info.has_top3box && sum_top3 != the_table_info.top3box_freq) {
		stringstream reasons_str;
		reasons_str << "top3box_freq did not match:"
			<< "table shows:" << the_table_info.top3box_freq
			<< ", I expect it to be: "
			<< sum_top3;
		p_error_report.stubErrorReasons_.push_back (reasons_str.str());
		result = false;
	}

	if (the_table_info.has_bot2box && sum_bot2 != the_table_info.bot2box_freq) {
		stringstream reasons_str;
		reasons_str << "bot2box_freq did not match:"
			<< "table shows:" << the_table_info.bot2box_freq
			<< ", I expect it to be: "
			<< sum_bot2;
		p_error_report.stubErrorReasons_.push_back (reasons_str.str());
		result = false;
	}

	if (the_table_info.has_bot3box && sum_bot3 != the_table_info.bot3box_freq) {
		stringstream reasons_str;
		reasons_str << "bot3box_freq did not match:"
			<< "table shows:" << the_table_info.bot3box_freq
			<< ", I expect it to be: "
			<< sum_bot3;
		p_error_report.stubErrorReasons_.push_back (reasons_str.str());
		result = false;
	}

	return result;
}

bool passed_summary_table_checks (
	TableInfo  & the_table_info,
	map<string, int> & the_freq_counts,
	struct ErrorReport & p_error_report
		)
{
	cout << __PRETTY_FUNCTION__ << endl;
	RatingScaleInfo rat_scale_inf = extract_rating_scale (the_table_info.stub_name);
	if (rat_scale_inf.isRatingScale_) {
		if (rat_scale_inf.isReversed_) {
			cerr << __PRETTY_FUNCTION__ << "unhandled case: rat_scale_inf.isReversed_"
				<< endl;
			return false;
		} else {
			//cerr << __PRETTY_FUNCTION__ << "unhandled case: !rat_scale_inf.isReversed_"
			//	<< endl;
			int scale_end = rat_scale_inf.ratingScaleEnd_;
			map <string, int> & table_stub_code_map
				= freq_count_map_nq_name_stub_code[the_table_info.name_];
			map <int, string> & table_code_stub_map
				= freq_count_map_nq_name_code_stub[the_table_info.name_];
			print_map (table_stub_code_map);
			print_map (table_code_stub_map);
			return does_top_2_box_match  (the_table_info, the_freq_counts,
					rat_scale_inf, table_code_stub_map, p_error_report);
		}
	} else {
		cerr << __PRETTY_FUNCTION__ << "summary checks are not possible for table : this should not have occurred "
			<< endl;
		return false;
	}
}

enum SummaryTableType {
	TOPBOX,
	TOP2BOX,
	TOP3BOX,
	BOTBOX,
	BOT2BOX,
	BOT3BOX
};

bool check_summary_table (enum SummaryTableType,
		map <string, TableInfo * >::iterator qtm_table_it,
		struct ErrorReport & p_error_report
		)
{

	cout << __PRETTY_FUNCTION__
		<< endl
		<< ", TableInfo->array_base_name_: " << qtm_table_it->second->array_base_name_
		<< ", TableInfo->name_: " << qtm_table_it->second->name_
		<< endl;

	std::pair <std::multimap<string,TableInfo*>::iterator, std::multimap<string,TableInfo*>::iterator> ret
		= table_info_multimap.equal_range (qtm_table_it->second->array_base_name_);
	for (std::multimap<string, TableInfo*>::iterator it = ret.first; it != ret.second; ++it) {
		cout << " I will be checking against: " << it->second->name_
			<< endl;
	}
	return false;
}


bool check_table_against_nq_freq_counts(
		map <string, TableInfo * >::iterator qtm_table_it,
		map<string, map<string, int> >::iterator fq_nq_it,
		//string & reasons
		struct ErrorReport & p_error_report
		)
{
	cout << "ENTER: check_table_against_nq_freq_counts: "
		//<< __PRETTY_FUNCTION__ << ", "
		<< qtm_table_it->first << endl;
	TableInfo  & the_table_info = *(qtm_table_it->second);
	map <string, int> & the_table = the_table_info.qtm_freq_count_map_nq_name_stub_freq_;
	map<string, int>::iterator TABLE_END = the_table.end();
	map<string, int>::iterator table_it = the_table.begin();
	map<string, int> & the_freq_counts = fq_nq_it->second;
	map<string, int>::iterator FREQ_END = the_freq_counts.end();

	bool counts_matched = true;
	cout << qtm_table_it->second->name_
		<< "Total: " << qtm_table_it->second->total_
		<< "Sigma: " << qtm_table_it->second->sigma_
		<< endl;

	for (; table_it!= TABLE_END; ++table_it) {
		stringstream reasons_str;
		cout << "searching for table stub:" << table_it->first
			<< endl
			;
		++ p_error_report.nStubs_;
		if (strstr (table_it->first.c_str(), "Sigma")==0) {
			map<string, int>::iterator freq_count_it = the_freq_counts.find (table_it->first);
			//{
			//	for (map<string, int>::iterator tmp_it = the_freq_counts.begin();
			//			tmp_it != the_freq_counts.end(); ++tmp_it) {
			//		cout << "stubs stub is |" << tmp_it->first << "|"
			//			<< ", count is |" << tmp_it->second << "|"
			//			<< endl;
			//	}
			//}

			if (freq_count_it != FREQ_END) {
				//cout << "found stub:" << table_it->first << " in fq_nq_it"
				//	<< endl;
				if (freq_count_it->second != table_it->second) {
					cout << "ERROR: the counts for stub|" << table_it->first << "| DID NOT MATCH"
						<< "table counts:"
						<< table_it->second
						<< "freq file counts:" << freq_count_it->second
						<< endl;
					reasons_str << "|" << " ERROR: the counts for stub:"
						<< table_it->first << " DID NOT MATCH"
						<< "table counts:"
						<< table_it->second
						<< "freq file counts:" << freq_count_it->second
						<< endl;
					p_error_report.stubErrorReasons_.push_back (reasons_str.str());
					++p_error_report.nStubErrors_;
					counts_matched = false;
				} else {
					cout << "I found the stub in the_freq_counts file."
						<< " The counts are:" << table_it->second
						<< endl;
					++p_error_report.nMatched_;
				}
			} else {
				//cout << "DID NOT FIND stub:" << table_it->first << " in fq_nq_it"
				//	<< endl;
				if (table_it->second == 0) {

				} else {
					cout << "ERROR: the counts for stub:"
						<< table_it->first
						<< " DID NOT MATCH: counts are not 0"
						<< endl;
					reasons_str << "|" << "ERROR: I Could not check the counts for stub:"
						<< table_it->first
						<< " because I DID NOT FIND IT in the frequency file AND count is not 0. It is "
						<< table_it->second;
					p_error_report.stubErrorReasons_.push_back (reasons_str.str());
					++p_error_report.nStubErrors_;
					counts_matched = false;
				}
			}
		} else {
			// this is the Sigma line - check for 100%
			//
			//if (table_it->second < 100) {
			//	counts_matched = false;
			//	cout << "ERROR: SIGMA < 100 - most probably filter condition missing:"
			//		<< "SIGMA is " << table_it->second
			//		<< endl;
			//}
		}
	}
	//p_error_report.stubErrorReasons_ = reasons_str.str();
	cout << "Sigma:" << qtm_table_it->second->sigma_ << endl;
	cout << "EXIT: " << __PRETTY_FUNCTION__ << endl;
	if (the_table_info.has_top2box) {
		cout << the_table_info.name_ << " has a top2box: value is: "
			<< the_table_info.top2box_freq
			<< ", invoking summary table checks"
			<< endl;
		if (!passed_summary_table_checks (the_table_info, the_freq_counts, p_error_report) ) {
			p_error_report.stubErrorReasons_.push_back ("did not pass summary table checks: " + the_table_info.stub_name);
			++p_error_report.nStubErrors_;
			counts_matched = false;
		} else {
			cout << " top2box matched" << endl;
		}
	}
	//reasons = reasons_str.str();
	return counts_matched;
}

void print_report_for_table(
		struct ErrorReport & p_error_report,
		std::ofstream & table_check_report
		)
{
	struct ErrorReport & error_report = p_error_report;

	table_check_report
		//<< endl
		<< "N M"
		<< "," << error_report.nStubs_
		<< "," << error_report.nStubErrors_
		<< "," << error_report.nStubWarnings_
		<< "," << error_report.nMatched_
		<< endl
		<< ",,,,,,Detailed report"
		<< endl;
		;
	for (int32_t i = 0; i < error_report.stubErrorReasons_.size();
			++i) {
		table_check_report << ",,,,,,"
			<< error_report.stubErrorReasons_[i] << endl;
	}
}

void check_tables(
	//map<string, map <string, int> > & qtm_freq_count_map_nq_name_stub_freq,
	map <string, struct TableInfo *> table_info_map,
	map<string, map <string, int> > & freq_count_map_nq_name_stub_freq,
	map<string, map <int, int> > & freq_count_map_rq
		)
{
	std::ofstream table_check_report ("table_check_report.csv");
	if (!table_check_report) {
		cerr << "Unable to open table_check_report.csv for writing ... exiting" << endl;
		exit(1);
	}
	cout << "============TABLE CHECKING OUTPUT STARTS HERE============" << endl;
	map<string, TableInfo * >::iterator qtm_table_it = table_info_map.begin();
	map<string, TableInfo * >::iterator QTM_TABLE_END = table_info_map.end();
	map<string, map<string, int> >::iterator QSCRIPT_NQ_START =   freq_count_map_nq_name_stub_freq.begin();
	map<string, map<string, int> >::iterator QSCRIPT_NQ_END =   freq_count_map_nq_name_stub_freq.end();

	map<string, map<int, int> >::iterator QSCRIPT_RQ_START =   freq_count_map_rq.begin();
	map<string, map<int, int> >::iterator QSCRIPT_RQ_END =   freq_count_map_rq.end();
	vector <ErrorReport> error_report_vec;

	table_check_report << "ax_name, Result, T S, E S, W S, M, Detailed Errors " << endl;
	for (; qtm_table_it!=QTM_TABLE_END; ++qtm_table_it ) {
		string ax_name = qtm_table_it->first;
		cout << "checking ax_name:" << ax_name << endl;
		table_check_report
			//<< "checking ax_name:, "
			<< ax_name << ",";
		map<string, map<string, int> >::iterator fq_nq_it =
			freq_count_map_nq_name_stub_freq.find(ax_name);
		ErrorReport error_report;
		if (fq_nq_it != QSCRIPT_NQ_END) {
			//cout << "ax_name: " << ax_name << " FOUND in freq_count_map_nq_name_stub_freq"
			//	<< endl;
			string reasons;
			if (check_table_against_nq_freq_counts(qtm_table_it, fq_nq_it, /*reasons*/ error_report)) {
				cout << "counts for table: " << qtm_table_it -> first
					<< "matched" << endl;
				table_check_report << "matched";
			} else {
				cout << "counts for table: " << qtm_table_it -> first
					<< "DID NOT MATCH" << endl;

				/*
				table_check_report << "DID NOT MATCH,"
					<< reasons;
				table_check_report << ",,"
					<< "Total stubs: " << error_report.nStubs_
					<< ",Error stubs: " << error_report.nStubErrors_
					<< ",Warning stubs: " << error_report.nStubWarnings_
					<< error_report.nStubErrors_
					<< endl
					<< ",,Detailed report"
					<< endl;
					;
				for (int32_t i = 0; i < error_report.stubErrorReasons_.size();
						++i) {
					table_check_report << ",,"
						<< error_report.stubErrorReasons_[i] << endl;
				}
				*/

				print_report_for_table(error_report, table_check_report);
			}
			error_report_vec.push_back(error_report);
		} else {
			// check if it's a summary table
			if ( (ax_name.length() > 4) &&
				(
				 ax_name[ax_name.length()-1] == 'p' &&
				 ax_name[ax_name.length()-2] == 'o' &&
				 ax_name[ax_name.length()-3] == 't' &&
				 ax_name[ax_name.length()-4] == '_'
				)
			   ) {
				table_check_report << "summary table check not yet implemented "
					<< endl;
				check_summary_table (TOPBOX, qtm_table_it, error_report);
			} else {
				cout << "ax_name: " << ax_name << " NOT FOUND in freq_count_map_nq_name_stub_freq and not a summary table"
					<< endl;
				table_check_report << "could_not_check,"
					<< ",,,,as not found in freq_count_map_nq_name_stub_freq";
			}
		}
		table_check_report << endl;
		//for (; fq_nq_it != QSCRIPT_NQ_END; ++fq_nq_it) {
		//	fq_nq_it
		//}
	}
}
