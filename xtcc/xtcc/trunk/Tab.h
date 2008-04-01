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
#include "tree.h"
using namespace std;
int yyparse();

enum axstmt_type { ax_uninit,txt_axstmt, tot_axstmt, cnt_axstmt };

struct table{
	string side;
	string banner;
	int line_no;
	expr* filter;
	table(string s, string t, int lline_no, expr* f=0) : side(s), banner(t),line_no(lline_no),filter(f){
	}
	~table();
};


class basic_ax_stmt	{
	public:
	int type;
	//char * text;
	//struct expr * expression;
	axstmt_type axtype;
	basic_ax_stmt * next;
	basic_ax_stmt * prev;
	basic_ax_stmt(axstmt_type ltype=ax_uninit): axtype(ltype),next(0), prev(0) {}

	virtual void print(fstream& f)=0;
	virtual string ax_text()=0;
	virtual ~basic_ax_stmt(){
		if(prev) {
			delete prev;
			prev=0;
		}
	};
};
#include <cstdio>
using namespace std;
class basic_print_ax_stmt: public basic_ax_stmt{
	public:
	string text;
	basic_print_ax_stmt(axstmt_type ltype ,string s): basic_ax_stmt(ltype), text(s){}
	virtual void print(fstream& f){
		f << text << endl ;
	}
	virtual string ax_text(){
		return text;
	}
	virtual ~basic_print_ax_stmt(){}
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



class basic_count_ax_stmt: public basic_ax_stmt{
	public:
	string text;
	int count;
	struct expr* condn;
	basic_count_ax_stmt(axstmt_type ltype,string txt, struct expr* c): basic_ax_stmt(ltype),
		text(txt), condn(c), count(0){}
	virtual void print(fstream& f){
		f << "basic_count_ax_stmt::print(): Should not be called\n";
	}
	virtual string ax_text(){
		return text;
	}
	virtual ~basic_count_ax_stmt() ;
};

class count_ax_stmt: public basic_count_ax_stmt{
	public:
	count_ax_stmt(axstmt_type ltype,string txt, struct expr* c): basic_count_ax_stmt(ltype,txt,c) {}
	virtual void print(fstream& f){
		f << "CNT: " << text ;
		f << "\n";
		
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
	~tot_ax_stmt();
	
};


class ax	{
	public:
	vector <bool> condn_flags;
	basic_ax_stmt * ax_stmt_start;
	//vector <basic_count_ax_stmt*> bas_cnt_ax_stmt_list;
	int no_count_ax_elems;	
	int no_tot_ax_elems;	
	expr* filter;
	ax(basic_ax_stmt* ax_s, int l_no_count_ax_elems, int l_no_tot_ax_elems,
			expr* f=0): ax_stmt_start(ax_s), 
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
