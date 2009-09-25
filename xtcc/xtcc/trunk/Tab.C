/*
 * Tab.C   
 * The tabulation handling routines for the xtcc compiler
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
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
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

//#include <cstdio>
#include <cstdlib>
#include "Tab.h"
#include "utils.h"

#include "debug_mem.h"
//#include "tree.h"
#include "expr.h"

#include <iostream>
extern std::vector<mem_addr_tab> mem_addr;
extern std::ofstream debug_log_file;
extern int no_errors;
extern int line_no;
extern Scope* active_scope;
namespace Table {
	using ::mem_addr;
	using ::debug_log_file;
	using ::no_errors;
	using ::line_no;
	using Util::find_in_symtab;
	using Util::print_err;
/*
vector<internal_table*> itbl_vec(0);
void print_banner(int side, internal_table* & itbl_ptr, fstream& tab_);
void construct_tables(map<string, ax*>& ax_map, vector<table*>& table_list){
	//cout << "enter construct_tables()\n";
	//typedef map<string, ax*>::const_iterator CMAPITER;
	for(int i=0; i<table_list.size(); i++){
		CMAPITER map_iter_s= ax_map.find(table_list[i]->side);
		CMAPITER map_iter_b= ax_map.find(table_list[i]->banner);
		if(map_iter_s==ax_map.end()||map_iter_b==ax_map.end()){
			cerr << "Error: axis name " <<
				table_list[i]->side << " or " <<
				table_list[i]->banner << "not pres in axes defn"
				<< endl;
		} else {
			//construct_internal_table(ax_map, table_list);
			//cout << "constructing table: " <<
			expr_node* f= table_list[i]->filter;
			cout << "table: " <<
				map_iter_b->first << " by " <<
				map_iter_s->first;
				if ( f ){
					cout << " Filter: " ;
					//f->print(cout);
				}
			internal_table * itbl_ptr = 
				new internal_table(map_iter_s, map_iter_b, f, i);
			itbl_vec.push_back(itbl_ptr);
		}
	}
	//cout << "exit construct_tables()\n";
}
// There probably is a much better way to do this than the dynamic_cast I put into the code
// however this hack works for now
// I'll reassess this code later

internal_table::internal_table(CMAPITER & map_iter_s, CMAPITER & map_iter_b, 
		expr_node* f, int i):
		side_ax(map_iter_s->second), ban_ax(map_iter_b->second),
		filter(f), index(i), base(0)
{
	//cout << "Enter internal_table::internal_table()\n";
	//cout << endl << endl << endl;
	ban_filter = ban_ax->filter;
	side_filter = side_ax->filter;
	basic_ax_stmt * ax_stmt_iter = side_ax->ax_stmt_start;
	while( ax_stmt_iter->next_ax_stmt) 
		ax_stmt_iter = ax_stmt_iter->next_ax_stmt;
	do{
		//cout << "loop: " << endl;
		//ax_stmt * ax_stmt_ptr = new ax_stmt;
		//ax_stmt_ptr= ax_stmt_iter;
		//side.push_back(ax_stmt_ptr);
		if(basic_count_ax_stmt* bcaxs_ptr=
			dynamic_cast<basic_count_ax_stmt*> (ax_stmt_iter) ){
			side.push_back(bcaxs_ptr);
		}
		ax_stmt_iter=ax_stmt_iter->prev_ax_stmt;
	}while (ax_stmt_iter);
	//cout << " finished side : size: " << side.size() << endl;
	cout << " side: " << side.size() ;
	ax_stmt_iter = ban_ax->ax_stmt_start;
	while( ax_stmt_iter->next_ax_stmt) 
		ax_stmt_iter = ax_stmt_iter->next_ax_stmt;
	do{
		
		//ax_stmt * ax_stmt_ptr = new ax_stmt;
		//ax_stmt_ptr= ax_stmt_iter;
		//banner.push_back(ax_stmt_ptr);
		if(basic_count_ax_stmt* bcaxs_ptr=
			dynamic_cast<basic_count_ax_stmt*> (ax_stmt_iter) ){
			banner.push_back(bcaxs_ptr);
		}
		ax_stmt_iter=ax_stmt_iter->prev_ax_stmt;
	} while(ax_stmt_iter);

	//cout << "finished banner : size: "  << banner.size() << endl;
	cout << " banner: "  << banner.size() << endl;
 	tbl_counter.resize(side.size());
	//cout << "resized tbl_counter " << endl;
	for(register unsigned int i=0; i< tbl_counter.size(); i++){
		tbl_counter[i].resize(banner.size());
	}
	//cout << "Exit internal_table::internal_table()\n";
}

void compute_table(vector<string>& data_arr){
	//cout << "Enter compute_table: itbl_vec.size(): " << itbl_vec.size() <<
	//	endl;
	fstream eval_out("EVAL_OUT", ios_base::out | ios_base::ate);
	for(register unsigned int i=0; i<itbl_vec.size(); i++){
		//cout << "loop i:" << i << endl;
		internal_table* itbl_ptr=itbl_vec[i];
		if( (itbl_ptr->filter      && 
			!itbl_ptr->filter->eval(data_arr, eval_out)) ||
		    (itbl_ptr->ban_filter  && 
		     	!itbl_ptr->ban_filter->eval(data_arr, eval_out)) ||
		    (itbl_ptr->side_filter && 
		     !itbl_ptr->side_filter->eval(data_arr, eval_out))  ){
			continue;
		} else {
			itbl_ptr->base++;
		}
		for(register unsigned int j=0; j<itbl_ptr->side.size(); j++){
			//cout << "loop j: " << j << endl;
			for(register unsigned int k=0; k<itbl_ptr->banner.size(); k++){
				//cout << "loop k: " << k << endl;
				//cout << "side AbstractExpression: " << 
				//	itbl_ptr->side[j]->condn;
				//cout << " banner AbstractExpression: " << 
				//	itbl_ptr->banner[k]->condn << endl;
				if( (itbl_ptr->side[j]->condn == NULL ||
				     itbl_ptr->side[j]->condn->eval(data_arr, eval_out)) &&
				    (itbl_ptr->banner[k]->condn == NULL ||
				     itbl_ptr->banner[k]->condn->eval(data_arr, eval_out)) ){
					//cout << "reached heart of compute_table\n";
					itbl_ptr->tbl_counter[j][k]++;
				}
			}
		}
	}
}

// Im now going to modify this function 
// so that the output looks more elegant
// Im going to cheat again 
// Im using the dynamic cast to check for table titles and print them out
// This code will need a review shortly
void print_table(fstream& tab_){
	//tab_ << "Enter print_table():" << endl;
	int test_side=20;
	for(register unsigned int i=0; i<itbl_vec.size(); i++){
		tab_ << "Table No: " << i+1 << endl;
		internal_table* itbl_ptr=itbl_vec[i];
		for(basic_ax_stmt* bs_ptr=itbl_ptr->side_ax->ax_stmt_start; 
				bs_ptr; bs_ptr=bs_ptr->next_ax_stmt){
			ttl_ax_stmt* ttl_ptr = 
				dynamic_cast<ttl_ax_stmt*> (bs_ptr);
			if (ttl_ptr){
				//tab_ << "called ttl_ax_stmt->print()\n";
				ttl_ptr->print(tab_);
			}
		}
		tab_ << "Internal Base: " << itbl_ptr->base << endl << endl;
		// Don't know if this will work
		// shot in the dark
		print_banner(test_side, itbl_ptr, tab_);
		tab_ << endl;
		for(register unsigned int j=0; j<itbl_ptr->side.size(); j++){
			int len =itbl_ptr->side[j]->text.length();
			tab_.setf(ios_base::left, ios_base::adjustfield);
			//tab_.setf(ios_base::right);
			tab_.width(test_side);
			if ( len > test_side ){
				//tab_.setf(ios_base::left, ios_base::adjustfield);
				tab_ << itbl_ptr->side[j]->text.substr(0, test_side) ;
			} else {
				//tab_.setf(ios_base::left, ios_base::adjustfield);
				tab_ << itbl_ptr->side[j]->text;
				//for( int i =0; i<test_side - len; ++i) { tab_ << "-"; }
				//tab_ << " ";
			}
			//if(i==0 && j==0)
			//	tab_.width(test_side);
			int colwid=9;
			for(register unsigned int k=0; k<itbl_ptr->banner.size(); k++){
				//tab_ << itbl_ptr->tbl_counter[j][k] << "\t";
				tab_.width(colwid);
				tab_.setf(ios_base::right, ios_base::adjustfield);
				tab_ << itbl_ptr->tbl_counter[j][k];
			}
			tab_ << endl;
			int left_to_print = len - test_side;int c=0;int i=1;
			while ( left_to_print > 0){
				c = left_to_print - test_side > 0 
					? test_side: left_to_print;
				tab_ << itbl_ptr->side[j]->text.substr(test_side*i, c) << endl;
				left_to_print = left_to_print - c;
				i++;
			}
		}
		tab_ << endl << endl;
	}
	//tab_ << "Exit print_table():" << endl;
}


count_stmt* hc_check_ptr;
int check_tables (vector<table*>& table_list){
	fstream chk_rpt("CHECK.RPT", ios_base::out|ios_base::trunc);
	
	if (!chk_rpt ){
		cerr << "Could not open CHECK.RPT for table checking report\n";
		return 0;
	}
	
	if ( hc_check_ptr == NULL ){
		chk_rpt << "You havent specified a USETHIS in the edit\
			section\n";
		chk_rpt << "I can't check the tables\n";
		return 0;
	}
	for(register unsigned int i=0; i< itbl_vec.size(); i++){
		internal_table* itbl_ptr=itbl_vec[i];
		chk_rpt <<
			"====================================================\n";
		chk_rpt << "Checking axis: " <<
			table_list[itbl_ptr->index]->side <<endl;
		for(register unsigned  int j=0; j<itbl_ptr->side.size(); j++){
			basic_count_ax_stmt* bcaxs_ptr = itbl_ptr->side[j];
			if ( mr_expr* mr_ptr = dynamic_cast<mr_expr*>
					(bcaxs_ptr->condn)){
				check_count(itbl_ptr, mr_ptr, j, chk_rpt);
			}
		}
	}
}

bool check_count(internal_table* itbl_ptr, mr_expr* mr_ptr, int row, 
		fstream& chk_rpt){
	static struct hole_count_container* counts_for_check = hc_check_ptr->h_cont;
	int col = mr_ptr->column_no;
	int punch =mr_ptr-> mask&0xff;
	if (mr_ptr->mask&1<<31==false){
		chk_rpt << "This axstmt is multicoded and cant be checked" <<
			endl;
		return false;
	}
	// below is redundant now
	if ( punch > 255 ){
		cerr << "bug in gram.y mask should not be > 255\n";
		exit(1);
	}
	// There is exactly one punch and we must find it
	// not not take forever
	int tmp=0;
	if ( punch & 0xf ){
		if (punch& 0x3){
			if (punch&0x01){
				tmp = 1;
			} else {
				tmp = 2;
			}
		} else if ( punch & 0xC){
			if(punch & 0x04){
				tmp = 3;
			} else {
				tmp = 4;
			}
		}
	} else if ( punch &0xf0){
		if (punch& 0x30){
			if (punch&0x10){
				tmp = 5;
			} else if (punch&0x20){
				tmp = 6;
			}
		} else if ( punch & 0xC0){
			if(punch & 0x40){
				tmp = 7;
			} else if (punch& 0x80) {
				tmp = 8;
			}
		}
	}
	//chk_rpt << "checking for punch : " << tmp << endl;
	int count = counts_for_check->get_count(col, tmp-1);
	if ( count != -1 ){
		chk_rpt << "c " << col << "'" << tmp << "'";
		if (count == itbl_ptr->tbl_counter[row][0]){
			chk_rpt << ":matched:" << count <<endl;
			return true;
		} else {
			chk_rpt << ":NOT MATCHED: count:" << count 
				<< ":Table:" <<
				itbl_ptr->tbl_counter[row][0] << endl;
			return false;
		}
	}
}

void print_banner(int side, internal_table* & itbl_ptr, fstream& tab_){
	int npoints=itbl_ptr->banner.size();
	// initialization
	vector <int> height;
	vector<int> nleft;
	height.resize(npoints);
	nleft.resize(npoints);
	int colwid=8;
	int max_height=0;
	tab_<<endl;
	for(int i=0; i<npoints; ++i){
		string tmp=itbl_ptr->banner[i]->text;
		int q=tmp.length()/colwid; 
		int r=tmp.length()%colwid; 
		if( r==0){
			height[i]=q;
		} else {
			height[i]=q+1;
		}
		nleft[i]=tmp.length();
		if(i==0) max_height = height[0] ;
		else max_height = (max_height>=height[i])?max_height:height[i];
	}
	tab_ << "Reached Here: max_height:" << max_height << "side: " << side << endl <<endl;
	for(int h=max_height ;h>0; --h ){
		tab_.width(side+1);
		tab_.setf(ios_base::right, ios_base::adjustfield);
		//tab_.width(side*2);
		for(int i=0; i<npoints; ++i){
			if(h<=height[i]){
				int condn=
				(colwid<=nleft[i])?colwid: nleft[i];
				nleft[i]=nleft[i]-condn;
				for(int j=0; j< colwid; ++j){
					if(j<condn){
						string tmp=itbl_ptr->banner[i]->text;
						tab_ <<
						tmp[j+(height[i]-h)*colwid];
					}
					else
						tab_ << "x";
				}
			} else {
				for(int j=0; j< colwid; ++j){
					tab_ << "+";
				}
			}
			tab_ << "&";
		}
		tab_ << endl;
	}
	tab_ << endl;
}
*/


basic_count_ax_stmt::~basic_count_ax_stmt() {
	if (condn) {
		delete condn; condn=0;
	}
	debug_log_file << "deleting ~basic_count_ax_stmt()" << endl;
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "basic_count_ax_stmt::~basic_count_ax_stmt setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	if(next_) {
		delete next_;
		next_=0;
	}
}

ttl_ax_stmt::~ttl_ax_stmt(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "ttl_ax_stmt::~ttl_ax_stmt setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
}

count_ax_stmt::~count_ax_stmt(){
	debug_log_file << "deleting ~count_ax_stmt()" << endl;
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "count_ax_stmt::~count_ax_stmt setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
}

tot_ax_stmt::~tot_ax_stmt(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "tot_ax_stmt::~tot_ax_stmt setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
}

ax::~ax(){
	//basic_ax_stmt* bax_ptr=ax_stmt_start;
	//basic_count_ax_stmt* count_ptr=count_ax_stmt_start;
	//basic_print_ax_stmt* print_ptr=ttl_ax_stmt_start;



	if(count_ax_stmt_start){
		delete count_ax_stmt_start; count_ax_stmt_start=0;
	}
	if(ttl_ax_stmt_start){
		delete ttl_ax_stmt_start; ttl_ax_stmt_start=0;
	}
	if(filter) {
		delete filter; filter=0;
	}
	debug_log_file << "deleting ax" << endl; 
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "ax::~ax setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
}
table::~table(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "table::~table setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	if(filter) {
		delete filter;
		filter=0;
	}
}

stub::stub(string l_text, int l_code):text(l_text), code(l_code), prev_(0), next_(0){ }
#include "utils.h"

extern vector<Scope*> active_scope_list;
extern Scope* active_scope;
//fld_ax_stmt::fld_ax_stmt(string field_name, struct stub * l_stub_list): stub_list(l_stub_list)
fld_ax_stmt::fld_ax_stmt(axstmt_type ltype, string field_name, vector<stub*> l_stub_list): basic_count_ax_stmt(ltype,"",0),
	stub_list(l_stub_list) {
	// NAME Has to be of array type, Int32 
	map<string,SymbolTableEntry*>::iterator sym_it=find_in_symtab(field_name);
	if(sym_it==::active_scope->sym_tab.end()){
		string err_msg = "Error parsing bit statement : could not find array:" + field_name + " in symbol table";
		print_err(Util::compiler_sem_err, err_msg, line_no, __LINE__, __FILE__);
	} else {
		symp = sym_it->second;
		if(!is_of_int32_arr_type(symp->type_)){
			string err_msg = "Error parsing bit statement : array should be of int32 type:" 
				+ field_name + " in symbol table";
			print_err(Util::compiler_sem_err, err_msg, line_no, __LINE__, __FILE__);
		}
	}
	cout << "fld_ax_stmt constructor: verifying copying of vector was correct" << endl;
	cout << "stubs are: " << endl;
	for(unsigned int i=0; i< stub_list.size(); ++i){
		cout << stub_list[i]->text << "," << stub_list[i]->code << endl;
	}
	cout << endl;
}
} /* close namespace Table */
