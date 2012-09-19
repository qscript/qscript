/*
 * scope.C
 * The main grammar for the xtcc parser
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
 * the Free Software Foundation version 2
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

#include <sys/types.h>
#include <iostream>
#include <sstream>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "qscript_parser.h"
#include "stmt.h"
#include "expr.h"
#include "scope.h"
#include "question.h"
#include "qscript_debug.h"
#include "named_attributes.h"

//using namespace std;
using std::cerr;
using std::endl;
using std::stringstream;

//extern int32_t line_no;
//extern int32_t no_errors;
//extern ofstream debug_log_file;
//extern vector<mem_addr_tab> mem_addr;

using qscript_parser::line_no;
using qscript_parser::no_errors;
using qscript_parser::debug_log_file;
using qscript_parser::mem_addr;
using qscript_parser::nest_lev;
using qscript_parser::flagIsAForBody_;


AbstractStatement* Scope::insert(const char * name, DataType dt/*, int32_t line_no*/)
{
	// we have to handle a case here where symbol is a function name: - this is not allowed
	DeclarationStatement * st_ptr = new DeclarationStatement(dt, line_no,
			nest_lev, flagIsAForBody_);
	if ( SymbolTable.find(name) == SymbolTable.end() ){
		SymbolTableEntry* se = new SymbolTableEntry(name, dt);
		//se->name = strdup(name.c_str());
		//se->type_ = dt;
		string s(name);
		SymbolTable[s] = se;
		st_ptr->type_ = dt;
		st_ptr->symbolTableEntry_ = se;
	} else {
		//cerr << "ERROR: " << name << " already present in symbol table" << endl;
		print_err (compiler_sem_err, " already present in symbol table"
			  , qscript_parser::line_no, __LINE__, __FILE__);
		st_ptr->type_ = ERROR_TYPE;
		//++no_errors;
	}
	return st_ptr;
}

AbstractStatement* Scope::insert(const char * name, DataType dt
				 , AbstractQuestion * l_q /*, int32_t line_no*/)
{
	stringstream mesg;
	mesg << "we have to handle the case here where symbol is a function name: - this is not allowed"
		     << endl;
	LOG_MAINTAINER_MESSAGE(mesg.str());
	/* - this will now go that the end of main
	if (qscript_debug::MAINTAINER_MESSAGES) {
		cerr << "we have to handle the case here where symbol is a function name: - this is not allowed"
		     << endl;
	}
	*/
	DeclarationStatement * st_ptr = new DeclarationStatement(dt, line_no,
			nest_lev, flagIsAForBody_);
	if (qscript_parser::named_stub_exists (name)) {
		std::stringstream err_mesg;
		err_mesg << "|" << name << " |  is already present as named_stub ";
		print_err (compiler_sem_err, err_mesg.str().c_str()
			  , qscript_parser::line_no, __LINE__, __FILE__);
		st_ptr->type_ = ERROR_TYPE;
	} else if (SymbolTable.find (name) == SymbolTable.end()) {
		SymbolTableEntry* se = new SymbolTableEntry(name, dt, l_q);
		//se->name = strdup(name.c_str());
		//se->type_ = dt;
		string s(name);
		SymbolTable[s] = se;
		st_ptr->type_ = dt;
		st_ptr->symbolTableEntry_ = se;
	} else {
		//cerr << "ERROR: " << name << " already present in symbol table" << endl;
		std::stringstream err_mesg;
		err_mesg << "|" << name << " | NAME already present in symbol table";
		print_err (compiler_sem_err, err_mesg.str()
			  , qscript_parser::line_no, __LINE__, __FILE__);
		st_ptr->type_ = ERROR_TYPE;
		//++no_errors;
	}
	return st_ptr;
}

AbstractStatement* Scope::insert(const char * name, DataType dt
				 , int32_t arr_size	 /*, int32_t line_no*/)
{
	// we have to handle a case here where symbol is a function name: - this is not allowed
	DeclarationStatement * st_ptr = new DeclarationStatement(dt, line_no,
			nest_lev, flagIsAForBody_
			);
	if ( SymbolTable.find(name) == SymbolTable.end() ){
		SymbolTableEntry* se = new SymbolTableEntry(name, dt);
		se->n_elms = arr_size;
		string s(name);
		SymbolTable[s] = se;
		st_ptr->type_ = dt;
		st_ptr->symbolTableEntry_ = se;
	} else {
		//cerr << " array NAME failed:" << line_no << endl;
		//cerr << name << " already present in symbol table" << endl;
		std::stringstream err_mesg;
		err_mesg << "|" << name << " | array NAME already present in symbol table";
		print_err (compiler_sem_err, err_mesg.str().c_str()
			  , qscript_parser::line_no, __LINE__, __FILE__);
		st_ptr->type_ = ERROR_TYPE;
		++no_errors;
	}
	return st_ptr;
}

AbstractStatement* Scope::insert(const char * name, DataType dt
				 , AbstractExpression *e)
{
	// we have to handle a case here where symbol is a function name: - this is not allowed
	DeclarationStatement * st_ptr = new DeclarationStatement(dt, line_no,
			nest_lev, flagIsAForBody_);
	if ( SymbolTable.find(name) == SymbolTable.end()) {
		SymbolTableEntry* se = new SymbolTableEntry(name, dt, e);
		if (is_of_noun_type (e->type_)) {
			if (check_type_compat(dt, e->type_)) {
				string s(name);
				SymbolTable[s] = se;
				st_ptr->type_ = dt;
				st_ptr->symbolTableEntry_ = se;
			} else {
				stringstream s;
				s << "Type of variable: " << name << " = "
					<< human_readable_type(dt)
					<< " in decl cannot handle type of expression on rhs of variable: "
					<< human_readable_type(e->type_) << endl;
				print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
				st_ptr->type_ = ERROR_TYPE;
			}
		} else {
			stringstream s;
			s << "Error in expression on rhs of variable :" << name << endl;
			print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
			st_ptr->type_ = ERROR_TYPE;
		}
	} else {
		stringstream s;
		s << "variable " << name << " already present in symbol table" << endl;
		print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		st_ptr->type_ = ERROR_TYPE;
	}
	return st_ptr;
}


AbstractStatement* Scope::insert(const char * name, DataType dt
				 , AbstractExpression *e, type_qualifier tq)
{
	// we have to handle a case here where symbol is a function name: - this is not allowed
	DeclarationStatement * st_ptr = new DeclarationStatement(dt, line_no,
				nest_lev, flagIsAForBody_);
	if ( SymbolTable.find(name) == SymbolTable.end() ){
		SymbolTableEntry* se = new SymbolTableEntry(name, dt, e, tq);
		if(is_of_noun_type(e->type_)){
			if (check_type_compat(dt, e->type_)){
				string s(name);
				SymbolTable[s] = se;
				st_ptr->type_ = dt;
				st_ptr->symbolTableEntry_ = se;
			} else {
				stringstream s;
				s << "Type of variable: " << name << " = "
					<< human_readable_type(dt)
					<< " in decl cannot handle type of expression on rhs of variable: "
					<< human_readable_type(e->type_) << endl;
				print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
				st_ptr->type_ = ERROR_TYPE;
			}
		} else {
			stringstream s;
			s << "Error in expression on rhs of variable :" << name << endl;
			print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
			st_ptr->type_ = ERROR_TYPE;
		}
	} else {
		stringstream s;
		s << "variable " << name << " already present in symbol table" << endl;
		print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		st_ptr->type_ = ERROR_TYPE;
	}
	return st_ptr;
}

AbstractStatement* Scope::insert(const char * name, DataType dt, int32_t arr_size
				 , /*int32_t line_no, */ char *text)
{
	// we have to handle a case here where symbol is a function name: - this is not allowed
	if(dt != INT8_ARR_TYPE){
		stringstream s;
		s << "only INT8_ARR_TYPE: can be assigned a string expression" << endl;
		print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);

	}
	int32_t text_len = 0;
	if(text){
		text_len = std::strlen(text);
	}
	if(arr_size<text_len-1) {
		cerr << "length of TEXT < array size line_no:" << line_no << endl;
		++no_errors;
	}
	DeclarationStatement * st_ptr = new DeclarationStatement(dt, line_no,
			nest_lev, flagIsAForBody_);
	if ( SymbolTable.find(name) == SymbolTable.end() ){
		SymbolTableEntry* se = new SymbolTableEntry(name, dt, arr_size, text);
		//se->n_elms = arr_size;
		//if(text)
		//	se->text_ = strdup(text);
		string s(name);
		SymbolTable[s] = se;
		st_ptr->type_ = dt;
		st_ptr->symbolTableEntry_ = se;
	} else {
		stringstream s;
		s << " IDENTIFIER: " << name << "  already present in symbol table" << endl;
		print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		st_ptr->type_ = ERROR_TYPE;
		++no_errors;
	}
	return st_ptr;
}

AbstractStatement* Scope::insert(const char * name, DataType dt, XtccSet *lxs)
{
	DeclarationStatement * st_ptr = new DeclarationStatement(dt, line_no,
			nest_lev, flagIsAForBody_);
	if ( SymbolTable.find(name) == SymbolTable.end() ){
		XtccSet * xs = new XtccSet(*lxs);
		SymbolTableEntry* se = new SymbolTableEntry(name, dt, xs);
		string s(name);
		SymbolTable[s] = se;
		st_ptr->type_ = dt;
		st_ptr->symbolTableEntry_ = se;
	} else {
		stringstream s;
		s << " IDENTIFIER: " << name << "  already present in symbol table" << endl;
		print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		st_ptr->type_ = ERROR_TYPE;
	}
	return st_ptr;
}

AbstractStatement* Scope::insert(const char * name, DataType dt, int l_line_no
		, int32_t l_nest_level
		, int32_t l_for_nest_level
		, vector<string> l_vec_named_attribute_list)
{
	named_attribute_list * na = new named_attribute_list
			(NAMED_ATTRIBUTE_TYPE, l_line_no, name
			 , l_nest_level
			 , l_for_nest_level
			 , l_vec_named_attribute_list);
	if ( SymbolTable.find(name) == SymbolTable.end() ){

		SymbolTableEntry* se = new SymbolTableEntry(name, dt, na);
		string s(name);
		SymbolTable[s] = se;
		//na->type_ = dt;
		na->symbolTableEntry_ = se;
	} else {
		stringstream s;
		s << " IDENTIFIER: " << name << "  already present in symbol table" << endl;
		print_err(compiler_sem_err, s.str(), line_no, __LINE__, __FILE__);
		na->type_ = ERROR_TYPE;
	}
	return na;
}
Scope::~Scope()
{
	debug_log_file <<"deleting Scope" << endl;
	typedef map<string,SymbolTableEntry*>::iterator it;
	for(it p = SymbolTable.begin(); p != SymbolTable.end(); ++p){
		delete p->second;
		p->second = 0;
	}
	for (uint32_t i = 0; i< mem_addr.size(); ++i){
		if(this == mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr = 0;
			debug_log_file << "Scope::~Scope setting mem_addr: " << this << " = 0" << endl;
			break;
		}
	}
	debug_log_file << "end deleting Scope" << endl;
}

//string human_readable_type(DataType dt);
void Scope::print_scope(const string & stack_name, vector<string> &push_stack
			, vector<string>& pop_stack)
{
	map<string,SymbolTableEntry*>::iterator it;
	for(it = SymbolTable.begin(); it != SymbolTable.end(); ++it){
		SymbolTableEntry * sym_ptr=  it->second;
		/*
		string s = sym_ptr-> name;
		s += " " + human_readable_type(sym_ptr->type_);
		*/
		string s("NONE");
		sym_ptr->print_push_stack(stack_name, s);
		push_stack.push_back(s);
		sym_ptr->print_pop_stack(stack_name, s);
		pop_stack.push_back(s);
	}
}

void Scope::print_scope(vector<ActiveVariableInfo*> & output_info)
{
	map<string,SymbolTableEntry*>::iterator it;
	for(it = SymbolTable.begin(); it != SymbolTable.end(); ++it){
		SymbolTableEntry * sym_ptr=  it->second;
		output_info.push_back(sym_ptr->GetVarInfo());
	}
}

SymbolTableEntry * Scope::find (string name)
{
	
	map<string,SymbolTableEntry*>::iterator se_entry_iter =  SymbolTable.find (name);
	if (se_entry_iter == SymbolTable.end()) {
		return 0;
	} else {
		return se_entry_iter->second;
	}
}

