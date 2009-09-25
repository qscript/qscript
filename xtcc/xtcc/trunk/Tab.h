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
#include <sstream>
#include <iostream>
#include "expr.h"
#include "scope.h"
//#include "tree.h"
#include "debug_mem.h"
//using namespace std;
namespace Table {

using std::string;
using std::map;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

int yyparse();

enum axstmt_type { ax_uninit,txt_axstmt, tot_axstmt, cnt_axstmt, fld_axstmt };

struct table{
	string side;
	string banner;
	int line_no;
	AbstractExpression* filter;
	table(string s, string t, int lline_no, AbstractExpression* f=0) 
		: side(s), banner(t),line_no(lline_no),filter(f)
	{ }
	~table();
};


/*
class basic_ax_stmt	{
	public:
	int type;
	axstmt_type axtype;
	basic_ax_stmt * prev_;
	basic_ax_stmt * next_;
	basic_ax_stmt(axstmt_type ltype=ax_uninit): axtype(ltype),prev_(0), next_(0) {}

	virtual void print(fstream& f)=0;
	virtual string ax_text()=0;
	virtual ~basic_ax_stmt(){
		if(next_) {
			delete next_;
			next_=0;
		}
	}
};
*/

#include <cstdio>
using namespace std;
class basic_print_ax_stmt {
	public:
	axstmt_type axtype;
	basic_print_ax_stmt * prev_;
	basic_print_ax_stmt * next_;
	string text;
	basic_print_ax_stmt(axstmt_type ltype ,string s): 
		axtype(ltype), 
		prev_(0), next_(0),
		text(s){}
	virtual void print(fstream& f){
		f << text << endl ;
	}
	virtual string ax_text(){
		return text;
	}
	virtual ~basic_print_ax_stmt(){
		if(next_) {
			delete next_;
			next_=0;
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
	basic_count_ax_stmt * prev_;
	basic_count_ax_stmt * next_;
	string text;
	struct AbstractExpression* condn;
	int count;
	basic_count_ax_stmt(axstmt_type ltype,string txt
			, struct AbstractExpression* c): 
		axtype(ltype),
		prev_(0), next_(0),
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
	count_ax_stmt(axstmt_type ltype,string txt, struct AbstractExpression* c): basic_count_ax_stmt(ltype,txt,c) {}
	virtual void print(fstream& f){
		f << "CNT: " << text ;
		f << "\n";
		
	}
	virtual void generate_code(FILE * f, unsigned int index)
	{
		//fprintf(f, "count_ax_stmt :: generate_code() not yet implemented\n");
		ostringstream code_expr1, code_bef_expr1;
		condn->PrintExpressionCode(code_bef_expr1, code_expr1);
		fprintf(f, "%s", code_bef_expr1.str().c_str());
		fprintf(f, "\tif ( %s", code_expr1.str().c_str());
		//condn->PrintExpressionCode(f);
		fprintf(f, " ){\n");
		fprintf(f, "\t\tflag[%d]=true;\n", index);
		fprintf(f, "\t}\n");

	}
	virtual void print_axis_constructor_text(FILE * f
			, unsigned int start_index)
	{
		fprintf(f, "\t\tcount_stmt_text[%d]=%s;\n"
				, start_index, ax_text().c_str());
	}
	~count_ax_stmt();
};

class tot_ax_stmt: public basic_count_ax_stmt
{
	public:
	tot_ax_stmt(axstmt_type ltype, string txt
			, struct AbstractExpression* c)
		: basic_count_ax_stmt(ltype,txt,c) {}
	virtual void print(fstream& f)
	{
		f << "TOT: " << text;
		f << "\n";
	}
	virtual void generate_code(FILE * f, unsigned int index){
		//fprintf(f, "tot_ax_stmt :: generate_code() not yet implemented\n");
		ostringstream code_expr1, code_bef_expr1;
		condn->PrintExpressionCode(code_bef_expr1, code_expr1);
		fprintf(f, "%s", code_bef_expr1.str().c_str());
		fprintf(f, "\tif ( %s", code_expr1.str().c_str());
		//fprintf(f, "\tif (");
		//condn->PrintExpressionCode(f);
		fprintf(f, " ){\n");
		fprintf(f, "\t\tflag[%d]=true;\n", index);
		fprintf(f, "\t}\n");
	}
	virtual void print_axis_constructor_text(FILE * f
			, unsigned int start_index)
	{
		fprintf(f, "\t\tcount_stmt_text[%d]=%s;\n"
				, start_index, ax_text().c_str());
	}
	~tot_ax_stmt();
};

struct stub {
	string text;
	int code;
	struct stub* prev_, *next_;
	stub(string l_text, int l_code);
};

#include <string>
using std::string;
class fld_ax_stmt : public basic_count_ax_stmt {
	public:
	struct SymbolTableEntry* symp;
	//struct stub* stub_list;
	vector<stub*> stub_list;
	//fld_ax_stmt(string field_name, struct stub * l_stub_list);
	fld_ax_stmt(axstmt_type ltype ,string field_name
			, vector<stub*> l_stub_list);
	virtual void generate_code(FILE * f, unsigned int index)
	{
		for(unsigned int i=0; i< stub_list.size(); ++i){
			fprintf(f, "\t\tif (%s[%d]){\n"
					, symp->name_, stub_list[i]->code-1);
			fprintf(f, "\t\t\t flag[%d]=true;\n\t\t}\n"
					, index+stub_list[i]->code-1);
		}
	}
	virtual void print_axis_constructor_text(FILE * f
			, unsigned int start_index){
		cout << "came to print_axis_constructor_text in fld_ax_stmt" 
			<< endl;
		for(int i=0; i<stub_list.size(); ++i) {
			fprintf(f, "\t\tcount_stmt_text[%d]=%s;\n"
					, i+start_index
					, stub_list[i]->text.c_str());
		}
		cout << "exited print_axis_constructor_text in fld_ax_stmt" 
			<< endl;
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
	AbstractExpression* filter;
	//fld_ax_stmt * fld_stmt;
	ax(basic_print_ax_stmt * ttl_s,	basic_count_ax_stmt* cnt_ax_s
			, int l_no_count_ax_elems, int l_no_tot_ax_elems
			, AbstractExpression* f=0)
		: ttl_ax_stmt_start(ttl_s),  count_ax_stmt_start(cnt_ax_s)
		, no_count_ax_elems(l_no_count_ax_elems)
		, no_tot_ax_elems(l_no_tot_ax_elems)
		, condn_flags(l_no_count_ax_elems), filter(f) {}

	~ax();
};




int yylex ( void );

void construct_tables(map<string, ax*>& ax_map, vector<table*> & table_list);

typedef map<string, ax*>::const_iterator CMAPITER;

void construct_internal_table(map<string, ax*>& ax_map
		, vector<table*>& table_list);

struct internal_table{
	vector<basic_count_ax_stmt*> side;
	vector<basic_count_ax_stmt*> banner;
	vector< vector<int> >tbl_counter;
	vector< vector<float> > tbl_perc;
	ax* side_ax, *ban_ax;
	internal_table(CMAPITER &map_iter_s, CMAPITER &map_iter_b, 
			AbstractExpression* f, int i);
	AbstractExpression* filter;
	AbstractExpression* ban_filter;
	AbstractExpression* side_filter;
	int base;
	int index;
};

} /* Close Namespace Table */

/*
void compute_table(vector<string>& data_arr);
void print_table(fstream& tab_ );
bool check_count(internal_table* itbl_ptr, mr_expr* mr_ptr, int row, 
		fstream& chk_rpt);
int check_tables (vector<table*>& table_list);
*/
#endif /* __TAB_H */
