/*
	Copyright : Neil Xavier D'Souza, 2013
	License: GNU GPL2
*/

%{

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
#include "../const_defs.h"
#include "lex_tab.h"
// Why ? - because in the Makefile the generated code is in gen_src/
#include "../TableInfo.h"


	//extern int yylex();
	//extern void yyerror(const char * s);
	using std::cout;
	using std::endl;
	using std::cerr;
	using std::stringstream;
	using std::map;
	using std::string;
	// these are the global accumulators
	// yes bad bad global variables
	//map<string, map <string, int> > qtm_freq_count_map_nq_name_stub_freq;
	//map<string, map <int, int> > qtm_freq_count_map_rq;
	map <string, struct TableInfo *> table_info_map;
	multimap <string, struct TableInfo *> table_info_multimap;
	// these are used while building up the list
	//       this is for named stub questions
	map<string, int> temp_qtm_freq_count_map_nq_stub_codefreq;
	map<int, int>    temp_qtm_freq_count_map_nq_code_codefreq;
	map<string, int>    temp_qtm_freq_count_map_nq_stub_code;
	//       this is for range questions
	map<int, int> temp_qtm_freq_count_map_rq; // will always be code -> freq
	void qtm_table_output_error(const char * s);
	extern string stub_text;

	double global_sigma;
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

	void reset()
	{
		//cout << __PRETTY_FUNCTION__ << endl;

		global_sigma=0.0;
		topbox_perc=0.0;
		topbox_freq=0;
		top2box_perc=0.0;
		top2box_freq=0;
		top3box_perc=0.0;
		top3box_freq=0;
		botbox_perc=0.0;
		botbox_freq=0;
		bot2box_perc=0.0;
		bot2box_freq=0;
		bot3box_perc=0.0;
		bot3box_freq=0;
		mean=0.0;

		has_topbox=false;
		has_top2box=false;
		has_top3box=false;
		has_botbox=false;
		has_bot2box=false;
		has_bot3box=false;
		has_mean=false;
		//cerr << "reset invoked" << endl;

	}
	extern int qtm_line_no;

%}

%union {
	int ival;
	double dval;
	char name[4095];
	char text_buf[4095];
}


%token TABLE
%token PAGE
%token TOTAL
%token <dval> SIGMA
%token MEAN
%token <text_buf> BASE_TEXT
%token <ival> STUB_FREQ
%token <dval> STUB_PERC
%token <ival> STUB_TOPBOX
%token <ival> STUB_TOP2BOX
%token <ival> STUB_TOP3BOX
%token <ival> STUB_BOTBOX
%token <ival> STUB_BOT2BOX
%token <ival> STUB_BOT3BOX
%token <dval> STUB_MEAN
%token <text_buf> STUB_STD_DEV
%token <ival> INUMBER
%token <dval> FNUMBER
%token <name> NAME
%token <text_buf> TEXT
%token <text_buf> TABLE_INFO
%token <text_buf> TABLE_INFO2
%token NEWL
%token COMMA
%token DOT
%token EMPTY_LINE_2_COLS
%token EMPTY_LINE_1_COLS
%token BAN_TOTAL
%token <ival> SIDE_TOTAL

%name-prefix "qtm_table_output_"

%%

axis_qtm_freq_count_list: axis_qtm_freq_count {
		//cout << "parsed axis_qtm_freq_count to axis_qtm_freq_count_list"
		//	<< endl;
	}
	| axis_qtm_freq_count_list axis_qtm_freq_count {
		//cout << "chaining axis_qtm_freq_count with axis_qtm_freq_count_list"
		//	<< endl;
	}
	;

axis_qtm_freq_count: PAGE NEWL TABLE NEWL TEXT NEWL
		   TABLE_INFO NEWL
           text_chain
		   BASE_TEXT NEWL EMPTY_LINE_2_COLS NEWL EMPTY_LINE_1_COLS NEWL
		   BAN_TOTAL NEWL EMPTY_LINE_1_COLS NEWL
		   SIDE_TOTAL NEWL freq_chain /*SIGMA STUB_PERC*/ {
		//qtm_freq_count_map_nq_name_stub_freq[$7] = temp_qtm_freq_count_map_nq_stub_code_qtm_freq_count_map_nq_stub_codefreq;
		cout << "got axis_qtm_freq_count: " << $7 << endl;
		int side_total = $20;
		string title="empty";
		//double sigma = $23;
		double sigma = global_sigma;
		// now in reset() function
		//global_sigma = 0.0;
		string name_ax_info($7);
		int pos_1st_comma = name_ax_info.find (',');
		int pos_2nd_comma = name_ax_info.rfind (',');
		string name = name_ax_info.substr(0, pos_1st_comma);
		string array_base_name = name_ax_info.substr(pos_1st_comma+1, pos_2nd_comma-1-pos_1st_comma);
		string sp_mp_info = name_ax_info.substr(pos_2nd_comma+1,array_base_name.length()-2-(pos_2nd_comma+1));
		cout << "Extracted: name |" << name << "|"
			<< "array_base_name|" << array_base_name << "|"
			<< "sp_mp_info|" << sp_mp_info << "|" << endl;
		int no_mpn = atoi (sp_mp_info.c_str());
		struct TableInfo * table_info_ptr =
			new TableInfo (temp_qtm_freq_count_map_nq_stub_codefreq,
					temp_qtm_freq_count_map_rq, side_total, title, sigma, name, array_base_name
				);
		table_info_map[name] = table_info_ptr;
		table_info_multimap.insert(std::pair<string, TableInfo*> (array_base_name, table_info_ptr));
		temp_qtm_freq_count_map_nq_stub_codefreq.clear();
		reset();
	}

    | PAGE NEWL TABLE NEWL TEXT NEWL
		   TABLE_INFO2 NEWL
           text_chain
		   BASE_TEXT NEWL EMPTY_LINE_2_COLS NEWL EMPTY_LINE_1_COLS NEWL
		   BAN_TOTAL NEWL EMPTY_LINE_1_COLS NEWL
		   SIDE_TOTAL NEWL freq_chain /*SIGMA STUB_PERC*/ {
		//qtm_freq_count_map_nq_name_stub_freq[$7] = temp_qtm_freq_count_map_nq_stub_code_qtm_freq_count_map_nq_stub_codefreq;
		cout << "got axis_qtm_freq_count: " << $7 << endl;
		int side_total = $20;
		string title="empty";
		//double sigma = $23;
		double sigma = global_sigma;
		global_sigma = 0.0;
		string name_ax_info($7);
		int pos_1st_comma = name_ax_info.find (',');
		int pos_2nd_comma = name_ax_info.find (',', pos_1st_comma+1);
		int pos_3rd_comma = name_ax_info.rfind (',');
		string name = name_ax_info.substr(0, pos_1st_comma);
		string array_base_name = name_ax_info.substr(pos_1st_comma+1, pos_2nd_comma-1-pos_1st_comma);
		string sp_mp_info = name_ax_info.substr(pos_2nd_comma+1,pos_3rd_comma-1-(pos_2nd_comma));
		string stub_name = name_ax_info.substr(pos_3rd_comma+1,array_base_name.length()-2-(pos_3rd_comma+1));
		cout 
			<< " pos_1st_comma: " << pos_1st_comma
			<< " pos_2nd_comma: " << pos_2nd_comma
			<< " pos_3rd_comma: " << pos_3rd_comma
			<< endl
			<< "Extracted: name |" << name << "|"
			<< "array_base_name|" << array_base_name << "|"
			<< "sp_mp_info|" << sp_mp_info << "|" 
			<< "stub name|" << stub_name << "|"
			<< endl;
		int no_mpn = atoi (sp_mp_info.c_str());
		struct TableInfo * table_info_ptr =
			new TableInfo (temp_qtm_freq_count_map_nq_stub_codefreq,
					temp_qtm_freq_count_map_rq, side_total, title, sigma, name, array_base_name
				);
		table_info_ptr->stub_name = stub_name;
		table_info_ptr->no_mpn = no_mpn;
		if (has_top2box) {
			table_info_ptr->top2box_freq = top2box_freq;
			table_info_ptr->has_top2box = has_top2box;
		}
		if (has_top3box) {
			table_info_ptr->top3box_freq = top3box_freq;
			table_info_ptr->has_top3box = has_top3box;
		}
		if (has_top3box) {
			table_info_ptr->top3box_freq = top3box_freq;
			table_info_ptr->has_top3box = has_top3box;
		}
		if (has_bot2box) {
			table_info_ptr->bot2box_freq = bot2box_freq;
			table_info_ptr->has_bot2box = has_bot2box;
		}
		if (has_bot3box) {
			table_info_ptr->bot3box_freq = bot3box_freq;
			table_info_ptr->has_bot3box = has_bot3box;
		}
		table_info_map[name] = table_info_ptr;
		temp_qtm_freq_count_map_nq_stub_codefreq.clear();
		reset();
	}

text_chain: TEXT NEWL
	  | text_chain TEXT NEWL
	  ;

freq_chain: a_freq
	  | freq_chain a_freq
	  ;

a_freq 	: 	STUB_FREQ NEWL {
		temp_qtm_freq_count_map_nq_stub_codefreq[stub_text]=$1;
	}
      	|	STUB_PERC NEWL
        |   STUB_MEAN NEWL
        |   STUB_TOP2BOX NEWL { 
		if (has_top2box == false) {
			top2box_freq = $1;
			has_top2box = true;
		} else {
			cerr << "STUB_TOP2BOX is repeated - Auto check will not work for this table: "
				<<  qtm_line_no
				<< endl;
		}
	}
        |   STUB_TOP3BOX NEWL {
		if (has_top3box == false) {
			top3box_freq = $1;
			has_top3box = true;
		} else {
			cerr << "STUB_TOP3BOX is repeated - Auto check will not work for this table: "
				<<  qtm_line_no
				<< endl;
		}
	}
        |   STUB_BOT2BOX NEWL {
		if (has_bot2box == false) {
			bot2box_freq = $1;
			has_bot2box = true;
		} else {
			cerr << "STUB_BOT2BOX is repeated - Auto check will not work for this table: "
				<<  qtm_line_no
				<< endl;
		}
	}
        |   STUB_BOT3BOX NEWL {
		if (has_bot3box == false) {
			bot3box_freq = $1;
			has_bot3box = true;
		} else {
			cerr << "STUB_BOT3BOX is repeated - Auto check will not work for this table: "
				<<  qtm_line_no
				<< endl;
		}
	}
        |   STUB_STD_DEV NEWL
	|   SIGMA NEWL { global_sigma = $1; }
	;


%%

	//extern void qtm_table_output_restart(FILE *input_file);
	extern int yyparse();
	void qtm_table_output_error(const char * s);

//#include "const_defs.h"

/*
// Enable main if you want to test separately
int main()
{
	std::string fname ("T.CSV");
	FILE * yyin = fopen(fname.c_str(), "rb");
	if (!yyin) {
		cerr << " Unable to open: " << fname << " for read ... exiting" << endl;
		exit(1);
	}
	qtm_table_output_restart(yyin);
	//if (!yyparse()) 
	if (!qtm_table_output_parse()) {
		cout << "Input parsed successfully" << endl;
	}
	
}
*/
