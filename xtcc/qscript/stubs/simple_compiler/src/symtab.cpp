/*
 * symtab.C  
 * The symbol table code for the xtcc compiler
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
#include <sstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include "qscript_parser.h"
#include "symtab.h"
#include "expr.h"
//using namespace std;
using std::stringstream;
using std::cout;
using std::endl;

using qscript_parser::line_no;
//extern int line_no;
//extern ofstream debug_log_file;
using qscript_parser::debug_log_file;
/*
stmt* sym_tab::insert(string name, DataType dt){
	// we have to handle a case here where symbol is a function name: - this is not allowed
	struct stmt * st_ptr=new_stmt();
	if(st_ptr){
	} else {
		cerr << "Memory allocation failed : line_no" << line_no << endl;
		exit(1);
	}
	if ( sym_tab.find(name) == sym_tab.end() ){
		cout << "char decl:start\n";
		struct SymbolTableEntry* se=new struct SymbolTableEntry;
		se->name = name;
		se->type=char_type;
		string s(name);
		active_scope->sym_tab[s] = se;
		st_ptr->type=char_type;
		st_ptr->symp=se;
	} else {
		cerr << " CHAR NAME failed:" << line_no << endl;
		cerr << $2 << " already present in symbol table" << endl;
		st_ptr->type=error_type;
		++no_errors;
	}
	return st_ptr;
}
*/
#include <fstream>
using std::endl;
SymbolTableEntry::~SymbolTableEntry()
{
	debug_log_file<< "deleting SymbolTableEntry: name_: " << name_ << std::endl;
	if(name_&& created_by_me) { 
		debug_log_file << "freeing name_: " << name_  << endl; 
		free( name_); name_=0; 
	}
	if(text_ && created_by_me) { 
		debug_log_file << "freeing text_: " << text_  << endl;
		free( text_); text_=0; 
	}
	if(e) { delete e; e=0; }
	if(xs) { delete xs; xs=0; }
	debug_log_file << "FINISHED deleting SymbolTableEntry" << std::endl;
}


bool is_of_int_type(DataType dt)
{
	return (dt >= INT8_TYPE && dt <=INT32_TYPE);
}

bool is_of_noun_type(DataType dt)
{
	return (dt >= INT8_TYPE && dt <=DOUBLE_TYPE)
		|| (dt==QUESTION_TYPE)
		;
}

bool is_of_noun_ref_type(DataType dt)
{
	return (dt >= INT8_REF_TYPE && dt <=DOUBLE_REF_TYPE);
}

bool is_of_arr_type(DataType dt)
{
	return (dt >= INT8_ARR_TYPE && dt <=DOUBLE_ARR_TYPE);
}

DataType convert_ref_type(DataType dt)
{
	if(dt>=INT8_REF_TYPE && dt<=DOUBLE_REF_TYPE) 
		return DataType(INT8_TYPE + dt-INT8_REF_TYPE);
	else 
		return dt;
}

string human_readable_type(DataType dt)
{
	cout << "ENTER human_readable_type" << endl;
	string s="UNKNOWN TYPE";
	switch(dt){
		case VOID_TYPE:
			s= "void";
		break;	
		case INT8_TYPE:
			s= "int8_t";
		break;	
		case INT16_TYPE:
			s = "int16_t";
		break;
		case INT32_TYPE:
			s = "int32_t";
		break;	
		case FLOAT_TYPE:
			s = "float";
		break;	
		case DOUBLE_TYPE:
			s = "double";
		break;	
		case INT8_ARR_TYPE:
			s = "INT8_ARR_TYPE";
		break;	
		case INT16_ARR_TYPE:
			s= "INT16_ARR_TYPE";
		break;	
		case INT32_ARR_TYPE:	
			s="INT32_ARR_TYPE";
		break;	
		case FLOAT_ARR_TYPE:
			s="FLOAT_ARR_TYPE";
		break;	
		case DOUBLE_ARR_TYPE:
			s="DOUBLE_ARR_TYPE";
		break;	
		case INT8_REF_TYPE:
			s="int8_t &";
		break;	
		case INT16_REF_TYPE:
			s="int16_type &";
		break;	
		case INT32_REF_TYPE:
			s="int32_t &";
		break;	
		case FLOAT_REF_TYPE:
			s="float &";
		break;	
		case DOUBLE_REF_TYPE:
			s="double_t &";
		break;	
		case QUESTION_TYPE:
			s="QUESTION_TYPE";
			break;
		case QUESTION_ARR_TYPE:
			s="QUESTION_ARR_TYPE";
			break;
		case BOOL_TYPE:
			s="BOOL_TYPE";
			break;
		case  ERROR_TYPE:
			s=" ERROR_TYPE";
			break;
		case TEXPR_STMT:
			s="TEXPR_STMT";
			break;
		case  CMPD_STMT:
			s="CMPD_STMT";
			break;
		case  IFE_STMT:
			s="IFE_STMT";
			break;
		case  DECL_STMT:
			s="DECL_STMT";
			break;
		case  FUNC_TYPE:
			s="FUNC_TYPE";
			break;
		case  FUNC_DEFN:
			s="FUNC_DEFN";
			break;
		case  FOR_STMT:
			s="FOR_STMT";
			break;
		case BREAK_STMT:
			s="BREAK_STMT";
			break;
		case  CONTINUE_STMT:
			s="CONTINUE_STMT";
			break;
		case  RANGE_DECL_STMT:
			s="RANGE_DECL_STMT";
			break;
		case STRING_TYPE:
			s="STRING_TYPE";
			break;
		case  STRING_ARR_TYPE:
			s="STRING_ARR_TYPE";
			break;
		case  NAMED_ATTRIBUTE_TYPE:
			s="NAMED_ATTRIBUTE_TYPE";
			break;
		case  NAMED_RANGE:
			s="NAMED_RANGE";
			break;
		case UNNAMED_RANGE:
			s="UNNAMED_RANGE";
			break;
		case  STUB_MANIP_ADD:
			s=" STUB_MANIP_ADD";
			break;
		case  STUB_MANIP_DEL:
			s=" STUB_MANIP_DEL";
			break;
		case  STUB_MANIP_UNSET_ALL:
			s=" STUB_MANIP_UNSET_ALL";
			break;
		case  STUB_MANIP_SET_ALL:
			s=" STUB_MANIP_SET_ALL";
			break;
		default:
			s="fix: human_readable_type: unhandled";
	}
	cout << "EXIT human_readable_type" << endl;
	return s;
}



SymbolTableEntry::SymbolTableEntry(const char * lname, DataType ldt, XtccSet * lxs)
	:name_(strdup(lname)), text_(0), dval(0), ival(0)
	 , type_(ldt), n_elms(-1), created_by_me(true), e(0)
	 , xs ( new XtccSet(*lxs)), type_qual(NO_QUAL), question_(0)
	{ }

			
bool is_of_int_arr_type(DataType dt)
{
	return (dt >= INT8_ARR_TYPE && dt <=INT32_ARR_TYPE);
}

bool is_of_int32_arr_type(DataType dt)
{
	return (dt == INT32_ARR_TYPE);
}

//void SymbolTableEntry::print_push_stack(string & str)
void SymbolTableEntry::print_push_stack(const string &stack_name, string & str)
{
	stringstream s("NONE");
	switch(type_){
	case INT8_TYPE:
		s << stack_name << "_scope_int8_t[\"" << name_ << "\"]=" << name_  << ";\n";
		break;
	case INT16_TYPE:	
		s << stack_name << "_scope_int16_t[\"" << name_ << "\"]=" << name_  << ";\n";
		break;
	case INT32_TYPE:	
		s << stack_name << "_scope_int32_t[\"" << name_ << "\"]=" << name_  << ";\n";
		break;
	case FLOAT_TYPE:
		s << stack_name << "_scope_float_t[\"" << name_ << "\"]=" << name_  << ";\n";
		break;
	case DOUBLE_TYPE:
		s << stack_name << "_scope_double_t[\"" << name_ << "\"]=" << name_  << ";\n";
		break;
	case QUESTION_TYPE:
		s << "" << name_ << "_scope_question_t"<<  "[\"" << stack_name << "\"]=" << name_ << "->input_data;\n" << endl;
		break;
	default: {
			string err_msg = "unhandled type in print_push_stack";
			s << err_msg;
			print_err(compiler_sem_err, err_msg, line_no, __LINE__, __FILE__);
		}
	}
	str = s.str();
}


void SymbolTableEntry::print_pop_stack(const string &stack_name, string & str)
{
	stringstream s("NONE");
	switch(type_){
	case INT8_TYPE:
		s << name_ << "=" << stack_name << "_scope_int8_t[\"" << name_ << "\"];" << endl;
		break;
	case INT16_TYPE:	
		s << name_ << "=" << stack_name << "_scope_int16_t[\"" << name_ << "\"];" << endl;
		break;
	case INT32_TYPE:	
		s << name_ << "=" << stack_name << "_scope_int32_t[\"" << name_ << "\"];" << endl;
		break;
	case FLOAT_TYPE:
		s << name_ << "=" << stack_name << "_scope_float_t[\"" << name_ << "\"];" << endl;
		break;
	case DOUBLE_TYPE:
		s << name_ << "=" << stack_name << "_scope_double_t[\"" << name_ << "\"];" << endl;
		break;
	case QUESTION_TYPE:
		//s << "// QUESTION_TYPE - will think of this later " << endl;
		s << "" << name_ << "->input_data=" << name_ << "_scope_question_t"<<  "[\"" << stack_name << "\"];" << endl;
		break;
	default: {
			string err_msg = "unhandled type in print_pop_stack\"";
			s << err_msg;
			print_err(compiler_sem_err, err_msg, line_no, __LINE__, __FILE__);
		}
	}
	str = s.str();
}

ActiveVariableInfo * SymbolTableEntry::GetVarInfo()
{
	return new ActiveVariableInfo(name_, type_);
}
