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
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>
#include "const_defs.h"
#include "lex_tab.h"

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

extern map<string, map <string, int> > qtm_freq_count_map_nq_name_stub_freq;
extern map<string, map <int, int> >    qtm_freq_count_map_nq_name_code_freq;
extern map<string, map <string, int> > qtm_freq_count_map_nq_name_stub_code;
extern map<string, map <int, int> > qtm_freq_count_map_rq;


void check_tables(
	map<string, map <string, int> > & qtm_freq_count_map_nq_name_stub_freq,
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
		}
	}
	{
		std::string fname ("T.CSV");
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
	check_tables(qtm_freq_count_map_nq_name_stub_freq,
			freq_count_map_nq_name_stub_freq,
			freq_count_map_rq
			);


}

void check_tables(
	map<string, map <string, int> > & qtm_freq_count_map_nq_name_stub_freq,
	map<string, map <string, int> > & freq_count_map_nq_name_stub_freq,
	map<string, map <int, int> > & freq_count_map_rq
		)
{
	map<string, map<string, int> >::iterator qtm_table_it = qtm_freq_count_map_nq_name_stub_freq.begin();
	map<string, map<string, int> >::iterator QTM_TABLE_END = qtm_freq_count_map_nq_name_stub_freq.end();
	map<string, map<string, int> >::iterator QSCRIPT_NQ_START =   freq_count_map_nq_name_stub_freq.begin();
	map<string, map<string, int> >::iterator QSCRIPT_NQ_END =   freq_count_map_nq_name_stub_freq.end();

	map<string, map<int, int> >::iterator QSCRIPT_RQ_START =   freq_count_map_rq.begin();
	map<string, map<int, int> >::iterator QSCRIPT_RQ_END =   freq_count_map_rq.end();

	for (; qtm_table_it!=QTM_TABLE_END; ++qtm_table_it ) {
		string ax_name = qtm_table_it->first;
		cout << "ax_name:" << ax_name << endl;
		map<string, map<string, int> >::iterator fq_nq_it =
			freq_count_map_nq_name_stub_freq.find(ax_name);
		if (fq_nq_it == QSCRIPT_NQ_END) {
			cout << "ax_name: " << ax_name << " NOT FOUND in freq_count_map_nq_name_stub_freq"
				<< endl;
		} else {
			cout << "ax_name: " << ax_name << " WAS FOUND in freq_count_map_nq_name_stub_freq"
				<< endl;
		}
		//for (; fq_nq_it != QSCRIPT_NQ_END; ++fq_nq_it) {
		//	fq_nq_it
		//}
	}
}
