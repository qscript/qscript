#ifndef rest_get_hello_h
#define rest_get_hello_h

#include <Wt/WServer>
#include <Wt/WResource>
#include <Wt/Http/Response>
#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>

using std::cout;
using std::endl;
using std::cerr;

class RestGetHello : public Wt::WResource
{
	public:
	std::string tab_fname;
	RestGetHello (std::string l_tab_fname)
		: tab_fname (l_tab_fname)
	{ }
	virtual ~RestGetHello()
	{
		beingDeleted();
	}
	protected:
	virtual void handleRequest(const Wt::Http::Request &request,
			Wt::Http::Response &response)
	{
		FILE * tab_ = fopen (tab_fname.c_str(), "rb");
		if (!tab_) {
			cout << "Unable to open tab_ for reading";
			return;
		}
		fseek (tab_, 0, SEEK_END);
		long int length = ftell (tab_);
		fseek (tab_, 0, SEEK_SET);
		std::ostringstream size_str;
		response.addHeader ("Content-Type", "binary/octet-stream");
		size_str << "attachment; filename=" << tab_fname
			<< "; size=" 
			<< length;
			//<< 13
			;
		cout << "length: " << length << endl;
		//response.addHeader ("Content-Disposition", size_str.str());
		response.addHeader ("Content-Disposition", size_str.str());
		//response.out() << "HELLO,World!\n";
		int bufsz = 4096;
		char buffer [4096];
		int tot_read = 0;
		bool breakout = false;
		do {
			int n_read = fread (buffer, 1, bufsz, tab_);
			tot_read += n_read;
			if (n_read < bufsz) {
				if ( feof(tab_) ) {
					if (tot_read != length) {
						cout << "we have a problem reading the file: "
							<< "tot_read: " << tot_read
							<< ", length: " << length 
							<< endl;
					} 
					breakout = true;
				}
				if ( ferror(tab_) ) {
					cout << "we have an ERROR reading the file";
					breakout = true;
				}
				breakout = true;
			}
			string s(buffer);
			response.out() << s;
		} while (tot_read < length && !breakout);


		fclose (tab_);
	}
};

#endif /* rest_get_hello_h */
