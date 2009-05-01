#include "debug_mem.h"
#include "qscript_parser.h"
#include <vector>
using std::vector;
//extern qscript_parser::vector <mem_addr_tab> mem_addr;
void mem_log(void * ptr, int compiler_src_line_no, const char* compiler_src_fname,
                int input_prog_line_no){
        mem_addr_tab m1(ptr, compiler_src_line_no, compiler_src_fname, input_prog_line_no);
	qscript_parser::mem_addr.push_back(m1);
}
