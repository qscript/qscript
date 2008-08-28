/* Tab.h
 *
 * Tablulation section header file - classes for constructing and printing
 * tables.
 * 
 * Copyright (C) 2003,2004, 2005,2006,2007  Neil Xavier D'Souza <nxd_in@yahoo.com>
 * Postal MAil address
 * Neil Xavier D'Souza
 * 502, Premier Park
 * 1st Tank Lane,
 * Orlem, Malad(W),
 * Mumbai India. 400064.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * The Free Software Foundation, 
 * 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __TAB_H
#define __TAB_H
#include <map>
#include <fstream>
#include <vector>
#include "expr.h"
#include "tree.h"
using namespace std;
int yyparse();

enum axstmt_type { ax_uninit,txt_axstmt, tot_axstmt, cnt_axstmt, fld_axstmt };

struct table{
	string side;
	string banner;
	int line_no;
	expr* filter;
	table(string s, string t, int lline_no, expr* f=0) : side(s), banner(t),line_no(lline_no),filter(f){
	}
	~table();
};


/*
class basic_ax_stmt	{
	public:
	int type;
	axstmt_type axtype;
	basic_ax_stmt * prev;
	basic_ax_stmt * next;
	basic_ax_stmt(axstmt_type ltype=ax_uninit): axtype(ltype),prev(0), next(0) {}

	virtual void print(fstream& f)=0;
	virtual string ax_text()=0;
	virtual ~basic_ax_stmt(){
		if(next) {
			delete next;
			next=0;
		}
	}
};
*/

#include <cstdio>
using namespace std;
class basic_print_ax_stmt {
	public:
	axstmt_type axtype;
	basic_print_ax_stmt * prev;
	basic_print_ax_stmt * next;
	string text;
	basic_print_ax_stmt(axstmt_type ltype ,string s): 
		axtype(ltype), 
		prev(0), next(0),
		text(s){}
	virtual void print(fstream& f){
		f << text << endl ;
	}
	virtual string ax_text(){
		return text;
	}
	virtual ~basic_print_ax_stmt(){
		if(next) {
			delete next;
			next=0;
		}
	}
};

class ttl_ax_stmt: public basic_print_ax_stmt{
	public:
	ttl_ax_stmt(axstmt_type ltype,string s): basic_print_ax_stmt(ltype,s) {}
	void print(fstream& f){
		basic_print_ax_stmt::print(f);
	}
	string ax_text(){
		return text;
	}
	~ttl_ax_stmt();
};



class basic_count_ax_stmt {
	public:
	axstmt_type axtype;
	basic_count_ax_stmt * prev;
	basic_count_ax_stmt * next;
	string text;
	struct expr* condn;
	int count;
	basic_count_ax_stmt(axstmt_type ltype,string txt, struct expr* c): 
		axtype(ltype),
		prev(0), next(0),
		text(txt), condn(c), count(0){}
	virtual void print(fstream& f){
		f << "basic_count_ax_stmt::print(): Should not be called\n";
	}
	virtual string ax_text(){
		return text;
	}
	virtual void generate_code(FILE * f, unsigned int index)=0;
	virtual void print_axis_constructor_text(FILE *  f, unsigned int start_index)=0;
	virtual ~basic_count_ax_stmt() ;
};

class count_ax_stmt: public basic_count_ax_stmt{
	public:
	count_ax_stmt(axstmt_type ltype,string txt, struct expr* c): basic_count_ax_stmt(ltype,txt,c) {}
	virtual void print(fstream& f){
		f << "CNT: " << text ;
		f << "\n";
		
	}
	virtual void generate_code(FILE * f, unsigned int index){
		//fprintf(f, "count_ax_stmt :: generate_code() not yet implemented\n");
		fprintf(f, "\tif (");
		condn->print_expr(f);
		fprintf(f, " ){\n");
		fprintf(f, "\t\tflag[%d]=true;\n", index);
		fprintf(f, "\t}\n");

	}
	virtual void print_axis_constructor_text(FILE * f, unsigned int start_index){
		fprintf(f, "\t\tcount_stmt_text[%d]=%s;\n", start_index, ax_text().c_str());
	}
	~count_ax_stmt();
};

class tot_ax_stmt: public basic_count_ax_stmt{
	public:
	tot_ax_stmt(axstmt_type ltype, string txt, struct expr* c): basic_count_ax_stmt(ltype,txt,c) {}
	virtual void print(fstream& f){
		f << "TOT: " << text;
		f << "\n";
	}
	virtual void generate_code(FILE * f, unsigned int index){
		//fprintf(f, "tot_ax_stmt :: generate_code() not yet implemented\n");
		fprintf(f, "\tif (");
		condn->print_expr(f);
		fprintf(f, " ){\n");
		fprintf(f, "\t\tflag[%d]=true;\n", index);
		fprintf(f, "\t}\n");
	}
	virtual void print_axis_constructor_text(FILE * f, unsigned int start_index){
		fprintf(f, "\t\tcount_stmt_text[%d]=%s;\n", start_index, ax_text().c_str());
	}
	~tot_ax_stmt();
};

struct stub {
	string text;
	int code;
	struct stub* prev, *next;
	stub(string l_text, int l_code);
};

#include <string>
using std::string;
class fld_ax_stmt : public basic_count_ax_stmt {
	public:
	struct symtab_ent* symp;
	//struct stub* stub_list;
	vector<stub*> stub_list;
	//fld_ax_stmt(string field_name, struct stub * l_stub_list);
	fld_ax_stmt(axstmt_type ltype ,string field_name, vector<stub*> l_stub_list);
	virtual void generate_code(FILE * f, unsigned int index){
		//f << "fld_ax_stmt :: generate_code() not yet implemented" << endl;
		//fprintf(f, "fld_ax_stmt :: generate_code() not yet implemented\n");
		for(unsigned int i=0; i< stub_list.size(); ++i){
			fprintf(f, "\t\tif (%s[%d]){\n", symp->name, stub_list[i]->code-1);
			fprintf(f, "\t\t\t flag[%d]=true;\n\t\t}\n", index+stub_list[i]->code-1);
		}
	}
	virtual void print_axis_constructor_text(FILE * f, unsigned int start_index){
		cout << "came to print_axis_constructor_text in fld_ax_stmt" << endl;
		for(int i=0; i<stub_list.size(); ++i) {
			fprintf(f, "\t\tcount_stmt_text[%d]=%s;\n", i+start_index, 
				stub_list[i]->text.c_str()
				);
		}
		cout << "exited print_axis_constructor_text in fld_ax_stmt" << endl;
	}
};


class ax	{
	public:
	//basic_ax_stmt * ax_stmt_start;
	basic_print_ax_stmt * ttl_ax_stmt_start;
	basic_count_ax_stmt * count_ax_stmt_start;
	//vector <basic_count_ax_stmt*> bas_cnt_ax_stmt_list;
	int no_count_ax_elems;	
	int no_tot_ax_elems;	
	vector <bool> condn_flags;
	expr* filter;
	//fld_ax_stmt * fld_stmt;
	/*
	ax( expr * f, fld_ax_stmt * l_ax_stmt): ax_stmt_start(0),
			no_count_ax_elems(l_ax_stmt->stub_list.size()), no_tot_ax_elems(0), 
			condn_flags(0), filter(f), fld_stmt(l_ax_stmt)
		{
			cout << "fld_stmt constructor: verifying vector was copied correctly" << endl;
		}
	ax(basic_ax_stmt* ax_s, int l_no_count_ax_elems, int l_no_tot_ax_elems,
			expr* f=0): ax_stmt_start(ax_s), 
		no_count_ax_elems(l_no_count_ax_elems), no_tot_ax_elems(l_no_tot_ax_elems),
			condn_flags(l_no_count_ax_elems),
		filter(f), fld_stmt(0) {}
	*/
	ax(basic_print_ax_stmt * ttl_s,	basic_count_ax_stmt* cnt_ax_s, int l_no_count_ax_elems, int l_no_tot_ax_elems,
			expr* f=0): ttl_ax_stmt_start(ttl_s),  count_ax_stmt_start(cnt_ax_s), 
		no_count_ax_elems(l_no_count_ax_elems), no_tot_ax_elems(l_no_tot_ax_elems),
			condn_flags(l_no_count_ax_elems),
		filter(f) {}

	~ax();
};




int yylex ( void );

void construct_tables(map<string, ax*>& ax_map, vector<table*> & table_list);

typedef map<string, ax*>::const_iterator CMAPITER;

void construct_internal_table(map<string, ax*>& ax_map, vector<table*>& table_list);

struct internal_table{
	vector<basic_count_ax_stmt*> side;
	vector<basic_count_ax_stmt*> banner;
	vector< vector<int> >tbl_counter;
	vector< vector<float> > tbl_perc;
	ax* side_ax, *ban_ax;
	internal_table(CMAPITER &map_iter_s, CMAPITER &map_iter_b, 
			expr* f, int i);
	expr* filter;
	expr* ban_filter;
	expr* side_filter;
	int base;
	int index;
};

/*
void compute_table(vector<string>& data_arr);
void print_table(fstream& tab_ );
bool check_count(internal_table* itbl_ptr, mr_expr* mr_ptr, int row, 
		fstream& chk_rpt);
int check_tables (vector<table*>& table_list);
*/
#endif /* __TAB_H */
