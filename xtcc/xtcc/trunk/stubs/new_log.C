#include <iostream>
#include <vector>
using namespace std;

struct mem_info{
	void *addr;
	int line_no;
	char* fname;
	mem_info(void* ad, int ln, char* fn):addr(ad), line_no(ln), fname(fn){
	}
};
vector<mem_info> mem_tab;

void new_log(void *ptr, int line_no, char* file_name);
void print_mem_usage();
class c1{
	int a,b;
};

class c2{
	int a,b;
};
int main(){
	c1* c1ptr=0;
	new_log((c1ptr=new c1()), __LINE__, __FILE__);	
	c2* c2ptr=0;
	new_log((c2ptr=new c2), __LINE__, __FILE__);	
	char* ch_ptr=0;
	new_log((ch_ptr=new char), __LINE__, __FILE__);	
	print_mem_usage();
}

void new_log(void *ptr, int line_no, char* file_name){
	mem_info mi(ptr, line_no, file_name);
	mem_tab.push_back(mi);
}

void print_mem_usage(){
	for(int i=0; i<mem_tab.size(); ++i){
		cout << "mem addr: " << mem_tab[i].addr << ","
			<< "line_no: " << mem_tab[i].line_no << ","
			<< "fname: " << mem_tab[i].fname 
			<< endl;
	}
}
