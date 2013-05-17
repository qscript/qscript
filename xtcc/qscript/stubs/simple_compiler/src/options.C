/*
 * =====================================================================================
 *
 *       Filename:  options.C
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Tuesday 19 February 2013 07:55:13  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <sys/types.h>
#include <getopt.h>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;


namespace program_options_ns {
	bool ncurses_flag = false;
	bool static_binary_flag = false;
	bool web_server_flag = false;
	bool microhttpd_flag = false;
	bool wt_flag = false;
	int32_t fname_flag = 0;
	bool  no_question_save_restore_optimization;
	bool flag_nice_map;
	bool compile_to_cpp_only_flag = false;
	bool latex_flag = false;
	int stdout_flag = 0;
	string fname;
}

int main (int32_t argc, char* argv[])
{
	int c;
	static struct option long_options[] = 
		{
			{ "nice-map", no_argument, 0, 'm'},
			{ "optimise-no-save-restore", no_argument, 0, 'o'},
			{ "latex-qnre", no_argument, 0, 'l'},
			{ "compile-c++-only", no_argument, 0, 'c'},
			{ "static", no_argument, 0, 's'},
			{ "ncurses-exe", no_argument, 0, 'n'},
			{ "web-exe", required_argument, 0, 'w'},
			{ "filename", required_argument, 0, 'f'},
			{ "stdout", no_argument, &program_options_ns::stdout_flag, 1}
		};
	int option_index = 0;
	while (1) {
		c = getopt_long (argc, argv, "molcsnw:f:", long_options, &option_index);
		if (c == -1) {
			break;
		} else if (c == 0) {
			continue;
		}
		switch (c) {
			case 'c':
				program_options_ns::compile_to_cpp_only_flag = true;
				break;
			case 'n':
				program_options_ns::ncurses_flag = true;
				break;
			case 's':
				program_options_ns::static_binary_flag = true;
				break;
			case 'w': {
					program_options_ns::web_server_flag = true;
					string option_arg(optarg);
					if (option_arg == "microhttpd") {
						program_options_ns::microhttpd_flag = true;
					} else if (option_arg == "wt") {
						program_options_ns::wt_flag = true;
					} else {
						cerr << "invalid parameter: " << option_arg 
							<< " for -w (--web-exe) ... exiting" << endl;
						exit(1);
					}
				}
				break;
			case 'f':
				program_options_ns::fname = optarg;
				program_options_ns::fname_flag = 1;
				break;
			case 'l':
				program_options_ns::latex_flag = true;
				break;
			case 'o':
				program_options_ns::no_question_save_restore_optimization = true;
				break;
			case 'm':
				program_options_ns::flag_nice_map = true;
				break;
			case '?':
				if (optopt == 'f' )
					cerr << " option -'" << optopt << "' requires an argument" << endl;
				else if (optopt == 'w' )
					cerr << " option -'" << optopt << "' requires an argument" << endl;
				else if (isprint(optopt)){
					cerr << " unknown option : '-" << optopt << "'" << endl;
				} else
					cerr << " unknown character " << optopt << endl;
				exit(1);
				break;
			default:
				cerr << "Usage: "
					<< argv[0] << " -f <input-file>\n" <<   endl;
				exit(0);
			}
	}
	if (program_options_ns::microhttpd_flag && program_options_ns::wt_flag) {
		cerr << " -w option can be specified only once" << endl;
		exit (0);
	}
	cout << "program_options_ns::stdout_flag: " << program_options_ns:: stdout_flag << endl;
}
