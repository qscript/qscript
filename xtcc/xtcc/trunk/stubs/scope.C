#include "symtab.h"
#include "tree.h"
#include <string>
#include <cstring>
using namespace std;

extern int line_no;
extern int no_errors;

stmt* scope::insert(string name, datatype dt){
	// we have to handle a case here where symbol is a function name: - this is not allowed
	struct stmt * st_ptr=new_stmt();
	if(st_ptr){
	} else {
		cerr << "Memory allocation failed : line_no" << line_no << endl;
		exit(1);
	}
	if ( sym_tab.find(name) == sym_tab.end() ){
		cout << "char decl:start\n";
		struct symtab_ent* se=new struct symtab_ent;
		se->name = strdup(name.c_str());
		se->type=dt;
		//string s(name);
		//sym_tab[s] = se;
		sym_tab[name] = se;
		st_ptr->type=dt;
		st_ptr->symp=se;
	} else {
		cerr << " CHAR NAME failed:" << line_no << endl;
		cerr << name << " already present in symbol table" << endl;
		st_ptr->type=error_type;
		++no_errors;
	}
	return st_ptr;
}


stmt* scope::insert(string name, datatype dt, int arr_size){
	// we have to handle a case here where symbol is a function name: - this is not allowed
	struct stmt * st_ptr=new_stmt();
	if(st_ptr){
	} else {
		cerr << "Memory allocation failed : line_no" << line_no << endl;
		exit(1);
	}
	if ( sym_tab.find(name) == sym_tab.end() ){
		cout << "char decl:start\n";
		struct symtab_ent* se=new struct symtab_ent;
		se->name = strdup(name.c_str());
		se->type=dt;
		se->n_elms=arr_size;
		string s(name);
		sym_tab[s] = se;
		st_ptr->type=dt;
		st_ptr->symp=se;
	} else {
		cerr << " array NAME failed:" << line_no << endl;
		cerr << name << " already present in symbol table" << endl;
		st_ptr->type=error_type;
		++no_errors;
	}
	return st_ptr;
}


stmt* scope::insert(string name, datatype dt, int arr_size, char *text){
	// we have to handle a case here where symbol is a function name: - this is not allowed
	int text_len=strlen(text);
	if(arr_size<text_len-1) {
		cerr << "length of TEXT < array size line_no:" << line_no << endl;
		++no_errors;
	}
	struct stmt * st_ptr=new_stmt();
	if(st_ptr){
	} else {
		cerr << "Memory allocation failed : line_no" << line_no << endl;
		exit(1);
	}
	if ( sym_tab.find(name) == sym_tab.end() ){
		cout << "char decl:start\n";
		struct symtab_ent* se=new struct symtab_ent;
		se->name = strdup(name.c_str());
		se->type=dt;
		se->n_elms=arr_size;
		se->text=strdup(text);
		string s(name);
		sym_tab[s] = se;
		st_ptr->type=dt;
		st_ptr->symp=se;
	} else {
		cerr << " array NAME failed:" << line_no << endl;
		cerr << name << " already present in symbol table" << endl;
		st_ptr->type=error_type;
		++no_errors;
	}
	return st_ptr;
}
