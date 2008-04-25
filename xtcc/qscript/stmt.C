#include "../xtcc/trunk/symtab.h"
#include "../xtcc/trunk/stmt.h"
#include "../xtcc/trunk/tree.h"
#include <vector>
using std::vector;
extern vector<mem_addr_tab> mem_addr;
extern vector <func_info*> func_info_table;
extern ofstream debug_log_file;
#include <fstream>
#include <iostream>

extern char * work_dir;
stmt::~stmt(){ 
	if (next /*
		    && !((type==FUNC_DEFN)||(type==FUNC_TYPE))*/ ) {
		delete next; next=0;
	} 
	debug_log_file << "stmt::~stmt() base destructor" << std::endl;
}
decl_stmt::~decl_stmt(){ 
	debug_log_file << "deleting decl_stmt" << endl;
	//if(symp) { delete symp; symp=0; }
}

func_info::func_info(string name, struct var_list* elist, datatype myreturn_type): 
	fname(name), param_list(elist), return_type(myreturn_type), func_body(0), func_scope(0){
	func_scope=new scope();
	struct var_list* decl_list=elist;
	while(decl_list){
		//cout << " constructing func_info decl list names are: " << decl_list->var_name << endl;
		struct symtab_ent* se=new struct symtab_ent;
		se->name = strdup(decl_list->var_name.c_str());
		se->type=decl_list->var_type;
		func_scope->sym_tab[decl_list->var_name] = se;
		decl_list=decl_list->next;
	}
}

void func_info::print(FILE * fptr){
	if(return_type >=VOID_TYPE && return_type <=DOUBLE_TYPE){
		fprintf(fptr, "%s ", noun_list[return_type].sym );
	} else {
		fprintf(fptr, "Unexpected return type for function\n");
	}
	fprintf(fptr, "%s(", fname.c_str());
	if (param_list) param_list->print(fptr);
	fprintf(fptr, ");\n" );
}

func_info::~func_info(){
	if(param_list) { delete param_list; param_list=0; }
	//if(func_body) { delete func_body; func_body=0; }
	// func_scope was created by in the constructor - so we delete it
	if(func_scope) { delete func_scope; func_scope=0; }
}

