#include <sys/types.h>
#include <vector>
#include "debug_mem.h"
#include "qscript_parser.h"
using std::vector;
//extern qscript_parser::vector <mem_addr_tab> mem_addr;
void mem_log(void * ptr, int32_t compiler_src_line_no, const char* compiler_src_fname,
	     int32_t input_prog_line_no)
{
	mem_addr_tab m1(ptr, compiler_src_line_no, compiler_src_fname, input_prog_line_no);
	qscript_parser::mem_addr.push_back(m1);
}
