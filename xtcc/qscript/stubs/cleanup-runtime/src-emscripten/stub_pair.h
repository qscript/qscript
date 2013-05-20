/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/stub_pair.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#ifndef xtcc_stub_pair_h

#define xtcc_stub_pair_h

#include <sys/types.h>
#include <string>
#include <sstream>
//#include "../rapidjson/prettywriter.h"	// for stringify JSON
//#include "../rapidjson/filestream.h"	// wrapper of C stream for prettywriter as output

using std::string;
struct	stub_pair
{
	string stub_text;
	int32_t code;
	bool mask;
	bool is_mutex;
	stub_pair():stub_text(""), code(-1), mask(false), is_mutex(false) {}
	stub_pair(string l_txt, int32_t l_code)
		: stub_text(l_txt), code(l_code), mask(true),
		  is_mutex(false)
	{}
	stub_pair(string l_txt, int32_t l_code, bool p_mutex)
		: stub_text(l_txt), code(l_code), mask(true),
		  is_mutex(p_mutex)
	{}
	/*

	stub_pair(const stub_pair & p1)
	{
		stub_text = p1.stub_text;
		code = p1.code;
	}
	stub_pair & operator = (const stub_pair & rhs)
	{
		stub_text = rhs.stub_text;
		code = rhs.code;
		return *this;
	}
	*/

	/*
	template <typename Writer>
	void Serialize(Writer& writer) const
	{
		using namespace rapidjson;

		writer.StartObject();
		writer.String("stub_text");
		writer.String(stub_text.c_str(), (SizeType) stub_text.length());
		writer.String("stub_code");
		writer.Int(code);
		writer.String("mask");
		writer.Bool(mask);
		writer.String("is_mutex");
		writer.Bool(is_mutex);
		writer.EndObject();
	}
	*/

	void toString(std::stringstream & s) const
	{
	using std::endl;
		s 	<< "{"
			<< "\"stub_text\":" << "\"" << stub_text << "\"" << ","
			<< "\"stub_code\":" << code << ","
			<< "\"mask\":" << mask << ","
			<< "\"is_mutex\":" << mask
			//<< ","
			<< "}"
			<< endl;

	}
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
