#ifndef xtcc_stub_pair_h

#define xtcc_stub_pair_h

#include <string>
using std::string;
struct	stub_pair{
	string stub_text;
	int code;
	stub_pair():stub_text(""), code(-1){}
	stub_pair(string l_txt, int l_code): stub_text(l_txt), code(l_code){}
};

#endif /* xtcc_stub_pair_h */
