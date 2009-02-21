#include "stmt.h"
#include "expr.h"
#include "debug_mem.h"
#include "stmt.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include "named_range.h"


extern vector<mem_addr_tab> mem_addr;
extern int if_line_no;

extern ofstream debug_log_file;
using std::cout;
using std::endl;
void read_data(const char * prompt);
stmt::~stmt(){ 
	if (next  ) {
		delete next; next=0;
	} 
	debug_log_file << "stmt::~stmt() base destructor" << endl;
}
