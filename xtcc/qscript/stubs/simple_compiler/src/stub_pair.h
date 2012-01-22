/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/stub_pair.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#ifndef xtcc_stub_pair_h

#define xtcc_stub_pair_h

#include <sys/types.h>
#include <string>
using std::string;
struct	stub_pair
{
	string stub_text;
	int32_t code;
	bool mask;
	bool is_mutex;
	int index_in_group;
	stub_pair()
		: stub_text(""), code(-1), mask(false), is_mutex(false),
		  index_in_group (-1)
	{ }
	stub_pair(string l_txt, int32_t l_code, int32_t l_index_in_group)
		: stub_text(l_txt), code(l_code), mask(true),
		  is_mutex(false), index_in_group (l_index_in_group)
	{}
	stub_pair(string l_txt, int32_t l_code, bool p_mutex, int32_t l_index_in_group)
		: stub_text(l_txt), code(l_code), mask(true),
		  is_mutex(p_mutex), index_in_group (l_index_in_group)
	{}
	stub_pair(string l_txt, int32_t l_code)
		: stub_text (l_txt), code (l_code), mask (true), is_mutex(false),
		  index_in_group (-1)
	{ }
};

struct stub_pair_order_asc
{
public:
       bool operator() (const stub_pair & p, const stub_pair & q)
       {
               return p.code < q.code;
       }
};


struct stub_pair_order_desc
{
public:
       bool operator() (const stub_pair & p, const stub_pair & q)
       {
               return p.code > q.code;
       }
};


#endif /* xtcc_stub_pair_h */
