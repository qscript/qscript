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
#include "const_defs.h"
#include "lex_tab.h"
#include "TableInfo.h"

	using std::cout;
	using std::endl;
	using std::cerr;
	using std::stringstream;
	using std::map;
	using std::string;

extern void yyrestart(FILE *input_file);
extern int32_t yyparse();
extern int32_t qtm_table_output_parse();
extern int yylex();
extern void yyerror(const char * s);

extern map<string, map <string, int> > freq_count_map_nq_name_stub_freq;
extern map<string, map <int, int> > freq_count_map_nq_name_code_freq;
extern map<string, map <string, int> > freq_count_map_nq_name_stub_code;
extern map<string, map <int, int> > freq_count_map_rq;

extern map <string, struct TableInfo *> table_info_map;
//extern map<string, map <string, int> > qtm_freq_count_map_nq_name_stub_freq;
//extern map<string, map <int, int> >    qtm_freq_count_map_nq_name_code_freq;
//extern map<string, map <string, int> > qtm_freq_count_map_nq_name_stub_code;
//extern map<string, map <int, int> > qtm_freq_count_map_rq;


void check_tables(
	//map<string, map <string, int> > & qtm_freq_count_map_nq_name_stub_freq,
	map <string, struct TableInfo *> table_info_map,
	map<string, map <string, int> > & freq_count_map_nq_name_stub_freq,
	map<string, map <int, int> > & freq_count_map_rq
		);

int main()
{
	{
		std::string fname ("cmb_decision_maker.freq_count.csv");
		FILE * qscript_freq_file = fopen(fname.c_str(), "rb");
		if (!qscript_freq_file){
			cerr << " Unable to open: " << fname << " for read ... exiting" << endl;
			exit(1);
		}
		yyrestart(qscript_freq_file);
		if (!yyparse()) {
			cout << "Input parsed successfully" << endl;
		} else {
			cerr << "Error parsing freq_count file:" << fname << endl
				<< "exiting ..." << endl;
			exit(1);


		}
	}
	{
		//std::string fname ("T.CSV");
		std::string fname ("t2.csv");
		FILE * qtm_csv_file = fopen(fname.c_str(), "rb");
		if (!qtm_csv_file) {
			cerr << " Unable to open: " << fname << " for read ... exiting" << endl;
			exit(1);
		}
		qtm_table_output_restart(qtm_csv_file);
		//if (!yyparse())
		if (!qtm_table_output_parse()) {
			cout << "Input parsed successfully" << endl;
		}

	}
	check_tables(table_info_map,
			freq_count_map_nq_name_stub_freq,
			freq_count_map_rq
			);


}

bool check_table_against_nq_freq_counts(
		map <string, TableInfo * >::iterator qtm_table_it,
		map<string, map<string, int> >::iterator fq_nq_it, string & reasons)
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
	stringstream reasons_str;

	bool counts_matched = true;
	cout << qtm_table_it->second->name_
		<< "Total: " << qtm_table_it->second->total_
		<< "Sigma: " << qtm_table_it->second->sigma_
		<< endl;

	for (; table_it!= TABLE_END; ++table_it) {
		//cout << "searching for table stub:" << table_it->first;
		if (strstr (table_it->first.c_str(), "Sigma")==0) {
			map<string, int>::iterator freq_count_it = the_freq_counts.find (table_it->first);
			if (freq_count_it != FREQ_END) {
				//cout << "found stub:" << table_it->first << " in fq_nq_it"
				//	<< endl;
				if (freq_count_it->second != table_it->second) {
					cout << "ERROR: the counts for stub:" << table_it->first << " DID NOT MATCH"
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
					counts_matched = false;
				}
			} else {
				//cout << "DID NOT FIND stub:" << table_it->first << " in fq_nq_it"
				//	<< endl;
				if (table_it->second == 0) {

				} else {
					cout << "ERROR: the counts for stub:" << table_it->first << " DID NOT MATCH: counts are not 0"
						<< endl;
					reasons_str << "|" << "ERROR: I Could not check the counts for stub:" << table_it->first << " because I DID NOT FIND IT in the frequency file AND count is not 0, it is "
						<< table_it->second;
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
	cout << "Sigma:" << qtm_table_it->second->sigma_ << endl;
	cout << "EXIT: " << __PRETTY_FUNCTION__ << endl;
	reasons = reasons_str.str();
	return counts_matched;
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

	for (; qtm_table_it!=QTM_TABLE_END; ++qtm_table_it ) {
		string ax_name = qtm_table_it->first;
		cout << "checking ax_name:" << ax_name << endl;
		table_check_report << "checking ax_name:, " << ax_name << ",";
		map<string, map<string, int> >::iterator fq_nq_it =
			freq_count_map_nq_name_stub_freq.find(ax_name);
		if (fq_nq_it != QSCRIPT_NQ_END) {
			//cout << "ax_name: " << ax_name << " FOUND in freq_count_map_nq_name_stub_freq"
			//	<< endl;
			string reasons;
			if (check_table_against_nq_freq_counts(qtm_table_it, fq_nq_it, reasons)) {
				cout << "counts for table: " << qtm_table_it -> first
					<< "matched" << endl;
				table_check_report << "matched";
			} else {
				cout << "counts for table: " << qtm_table_it -> first
					<< "DID NOT MATCH" << endl;
				table_check_report << "DID NOT MATCH,"
					<< reasons;
			}
		} else {
			cout << "ax_name: " << ax_name << " NOT FOUND in freq_count_map_nq_name_stub_freq"
				<< endl;
			table_check_report << "could_not_check,"
				<< "as not found in freq_count_map_nq_name_stub_freq";
		}
		table_check_report << endl;
		//for (; fq_nq_it != QSCRIPT_NQ_END; ++fq_nq_it) {
		//	fq_nq_it
		//}
	}
}
