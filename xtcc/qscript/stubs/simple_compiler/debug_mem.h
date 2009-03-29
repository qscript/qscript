/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/debug_mem.h
 *
 *  memory leak support functions and structures
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#ifndef xtcc_debug_mem_h
#define xtcc_debug_mem_h
struct mem_addr_tab{
	void * mem_ptr;
	int line_number;
	string src_file;
	int src_file_line_no;
	mem_addr_tab(void * ptr, int line): mem_ptr(ptr), line_number(line), src_file(""), src_file_line_no(-1){}
	mem_addr_tab(void * ptr, int line, string l_src_file, int l_src_file_line_no): mem_ptr(ptr), line_number(line), src_file(l_src_file), src_file_line_no(l_src_file_line_no){}

};
void mem_log(void * ptr, int compiler_src_line_no, const char* compiler_src_fname,
                int input_prog_line_no);

#endif /* debug_mem_h */
