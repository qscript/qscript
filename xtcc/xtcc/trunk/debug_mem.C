#include "debug_mem.h"
#include <vector>
using std::vector;
extern vector <mem_addr_tab> mem_addr;
void mem_log(void * ptr, int compiler_src_line_no, const char* compiler_src_fname,
                int input_prog_line_no){
        mem_addr_tab m1(ptr, compiler_src_line_no, compiler_src_fname, input_prog_line_no);
	mem_addr.push_back(m1);
}
