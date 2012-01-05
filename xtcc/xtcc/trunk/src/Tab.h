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
#include "ax_stmt_type.h"
//using namespace std;
namespace Table {

using std::string;
using std::map;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

int yyparse();

//enum axstmt_type { ax_uninit, txt_axstmt, tot_axstmt, cnt_axstmt, fld_axstmt, inc_axstmt };

struct table
{
	string side;
	string banner;
	int line_no;
	Expression::AbstractExpression* filter;
	table(string s, string t, int lline_no, Expression::AbstractExpression* f=0) 
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
class AbstractPrintableAxisStatement 
{
	public:
	axstmt_type axtype;
	AbstractPrintableAxisStatement * prev_;
	AbstractPrintableAxisStatement * next_;
	string text;
	AbstractPrintableAxisStatement(axstmt_type ltype ,string s);
	virtual void print(fstream& f)=0;
	virtual string ax_text()=0;
	virtual ~AbstractPrintableAxisStatement();
};

class TitleStatement: public AbstractPrintableAxisStatement
{
	public:
	TitleStatement(axstmt_type ltype,string s);
	void print(fstream& f);
	string ax_text();
	~TitleStatement();
};



class AbstractCountableAxisStatement 
{
	public:
	axstmt_type axtype;
	AbstractCountableAxisStatement * prev_;
	AbstractCountableAxisStatement * next_;
	string text;
	struct Expression::AbstractExpression* condn;
	int count;
	int position_;
	AbstractCountableAxisStatement(axstmt_type ltype,string txt
			, struct Expression::AbstractExpression* c); 
	virtual void print(fstream& f)=0;
	virtual string ax_text()=0;
	virtual void generate_code(FILE * f, std::stringstream & cpp_code_str, unsigned int index)=0;
	virtual void print_axis_constructor_text(FILE *  f, unsigned int start_index)=0;
	virtual bool CustomCountExpression();
	virtual ~AbstractCountableAxisStatement() ;
};

class count_ax_stmt: public AbstractCountableAxisStatement
{
	public:
	count_ax_stmt(axstmt_type ltype,string txt, struct Expression::AbstractExpression* c);
	virtual void print(fstream& f);
	virtual void generate_code(FILE * f, std::stringstream & cpp_code_str, unsigned int index);
	virtual void print_axis_constructor_text(FILE * f
			, unsigned int start_index);
	virtual string ax_text();
	~count_ax_stmt();
};

class tot_ax_stmt: public AbstractCountableAxisStatement
{
	public:
	tot_ax_stmt(axstmt_type ltype, string txt
			, struct Expression::AbstractExpression* c, int l_position);
	
	virtual void print(fstream& f);
	virtual string ax_text();
	virtual void generate_code(FILE * f, std::stringstream & cpp_code_str, unsigned int index);
	virtual void print_axis_constructor_text(FILE * f
			, unsigned int start_index);
	~tot_ax_stmt();
};

class inc_ax_stmt: public AbstractCountableAxisStatement
{
	public:
	Expression::AbstractExpression * incrementExpression_;
	inc_ax_stmt(axstmt_type ltype
			, Expression::AbstractExpression* p_incrementExpression
			, Expression::AbstractExpression* p_condition
			);
		
	virtual void print(fstream& f);
	virtual string ax_text();
	virtual void generate_code(FILE * f, std::stringstream & cpp_code_str, unsigned int index);
	virtual void print_axis_constructor_text(FILE * f
			, unsigned int start_index);
	virtual bool CustomCountExpression();
	void PrintIncrExpression(FILE* op);
	~inc_ax_stmt();
};

struct stub {
	string text;
	int code;
	struct stub* prev_, *next_;
	stub(string l_text, int l_code);
};

#include <string>
using std::string;
class fld_ax_stmt : public AbstractCountableAxisStatement {
	public:
	struct SymbolTableEntry* symp;
	//struct stub* stub_list;
	vector<stub*> stub_list;
	//fld_ax_stmt(string field_name, struct stub * l_stub_list);
	fld_ax_stmt(axstmt_type ltype ,string field_name
			, vector<stub*> l_stub_list);
	virtual void generate_code(FILE * f, std::stringstream & cpp_code_str, unsigned int index);
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
	virtual string ax_text(){
		return text;
	}
	virtual void print(fstream& f){
		f << "FLD: " << text ;
		f << "\n";
		
	}
};


class ax
{
	public:
	//basic_ax_stmt * ax_stmt_start;
	AbstractPrintableAxisStatement * ttl_ax_stmt_start;
	AbstractCountableAxisStatement * count_ax_stmt_start;
	//vector <AbstractCountableAxisStatement*> bas_cnt_ax_stmt_list;
	int no_count_ax_elems;
	int no_tot_ax_elems;
	int no_inc_ax_elems;
	vector <bool> condn_flags;
	Expression::AbstractExpression* filter;
	//fld_ax_stmt * fld_stmt;
	ax (AbstractPrintableAxisStatement * ttl_s
			, AbstractCountableAxisStatement* cnt_ax_s
			, int l_no_count_ax_elems, int l_no_tot_ax_elems
			, int l_no_inc_ax_elems
			, Expression::AbstractExpression* f=0)
		: 
		ttl_ax_stmt_start (ttl_s),  count_ax_stmt_start (cnt_ax_s)
		, no_count_ax_elems (l_no_count_ax_elems)
		, no_tot_ax_elems (l_no_tot_ax_elems)
		, no_inc_ax_elems (l_no_inc_ax_elems)
		, condn_flags(l_no_count_ax_elems), filter(f) 
	{ }

	~ax();
};




int yylex ( void );

void construct_tables(map<string, ax*>& ax_map, vector<table*> & table_list);

typedef map<string, ax*>::const_iterator CMAPITER;

void construct_internal_table(map<string, ax*>& ax_map
		, vector<table*>& table_list);

struct internal_table{
	vector<AbstractCountableAxisStatement*> side;
	vector<AbstractCountableAxisStatement*> banner;
	vector< vector<int> >tbl_counter;
	vector< vector<float> > tbl_perc;
	ax* side_ax, *ban_ax;
	internal_table(CMAPITER &map_iter_s, CMAPITER &map_iter_b, 
			Expression::AbstractExpression* f, int i);
	Expression::AbstractExpression* filter;
	Expression::AbstractExpression* ban_filter;
	Expression::AbstractExpression* side_filter;
	int base;
	int index;
};

struct weight_axis {
	string name;
	vector<double> weights;
	weight_axis (string p_name, vector <double> p_weights);
};

struct weight_axis_group {
	string name;
	vector <weight_axis> weight_axis_vec;
	weight_axis_group (string p_name, vector <weight_axis> p_weight_axis_vec);
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
