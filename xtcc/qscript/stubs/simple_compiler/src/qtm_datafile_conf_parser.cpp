#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "qtm_datafile_conf_parser.h"
#include "log_mesg.h"

using std::stringstream;
using std::cerr;
using std::endl;
int32_t qtm_datafile_conf_parse();
int32_t qtm_datafile_conf_lex();
extern FILE * qtm_datafile_conf_in;


namespace qtm_datafile_conf_parser_ns {
	using std::string;
	int32_t ser_start, ser_end;
	int32_t crd_start, crd_end;
	int32_t line_no;
	int32_t no_errors;

	int32_t load_config_file(std::string jno);
	bool auto_determine_data_start_col = false;
	int32_t data_start_col;
	int32_t data_end_col;
	qtm_data_file_ns::QtmFileMode qtm_file_mode;

	// return 0 on success
	// terminate the program on failure
int32_t load_config_file(string jno)
{
	stringstream conf_file_name;
	conf_file_name << jno << ".qtm_data.conf";
	if (qtm_datafile_conf_in) {
		fclose(qtm_datafile_conf_in);
	}
	qtm_datafile_conf_in = fopen(conf_file_name.str().c_str(), "rb");
	stringstream conf_file_format;
	conf_file_format 
			<< "\tSER_NO_COLS = <start_pos example:1>, <end_pos example: 4>;\n"
			<< "\tCARD_NO_COLS = <start_pos example:5>, <end_pos example:6>;\n";

	if (!qtm_datafile_conf_in) {
		stringstream err_mesg;
		err_mesg << " did not find configuration file: \""
			<< conf_file_name.str() << "\" . Please create one. It should contain, \n"
			<< " at least the following lines \n\n" 
			<< conf_file_format.str()
			<< "\n"
			<< " this tells the data writer in which columns the serial no and card no\n"
			<< "should go\n"
			<< "... exiting\n";
		
		cerr << LOG_MESSAGE(err_mesg.str());
		exit(1);
	}
	if (!qtm_datafile_conf_parse()) {
		// success
		if (ser_start >= ser_end) {
			stringstream err_mesg;
			err_mesg << "ser_start: " << ser_start << " >= ser_end: " 
				<< ser_end << " which does not make sense... exiting\n";
			cerr << LOG_MESSAGE(err_mesg.str());
			exit(1);
		}
		if (crd_start >= crd_end) {
			stringstream err_mesg;
			err_mesg << "crd_start: " << crd_start << " >= crd_end: " 
				<< crd_end << " which does not make sense... exiting\n";
			cerr << LOG_MESSAGE(err_mesg.str());
			exit(1);
		}
		if ( (ser_start <= crd_start && crd_start <= ser_end)
			|| (ser_start <= crd_end && crd_end <= ser_end)) {
			stringstream err_mesg;
			err_mesg << "card no lies between serial no: "
				<< " which does not make sense... exiting\n";
			cerr << LOG_MESSAGE(err_mesg.str());
			exit(1);
		}
		if (qtm_file_mode == 1 || qtm_file_mode == 2) {
			if (crd_start == 0 || crd_end == 0) {
				stringstream err_mesg;
				err_mesg << "please specify card no in data file\n";
				cerr << LOG_MESSAGE(err_mesg.str());
				exit(1);
			}
			if ( (crd_start <= ser_start && ser_start <= crd_end)
				|| (crd_start <= ser_end && ser_end <= crd_end)) {
				stringstream err_mesg;
				err_mesg << "serial no lies between card no: "
					<< " which does not make sense... exiting\n";
				cerr << LOG_MESSAGE(err_mesg.str());
				exit(1);
			}
		}

		if (auto_determine_data_start_col && data_start_col > 0) {
			stringstream err_mesg;
			err_mesg << " Please specify only one of DATA_START_COL_NO = AUTO; or \n"
				<< " DATA_START_COL_NO = <number> ;\n";
			cerr << LOG_MESSAGE(err_mesg.str());
			exit(1);
		}
		if ( ! (qtm_file_mode == 0 || qtm_file_mode == 1 || qtm_file_mode == 2) ) {
			stringstream err_mesg;
			err_mesg << " READ_EQ can only be 0 (=> flat file) or 1 (=> 1000 cols per card )\n"
				<< " or 2 (=> 100 cols per card)\n\n";
			cerr << LOG_MESSAGE(err_mesg.str());
			exit(1);
		}

		if (qtm_file_mode == 0) {
		} else if (qtm_file_mode == 1 && data_end_col > 1000) {
			stringstream err_mesg;
			err_mesg << " READ_EQ 1 mode can have max data column no = 1000\n";
			cerr << LOG_MESSAGE(err_mesg.str());
			exit(1);
		} else if (qtm_file_mode == 2 && data_end_col > 100) {
			stringstream err_mesg;
			err_mesg << " READ_EQ 2 mode can have max data column no = 100\n";
			cerr << LOG_MESSAGE(err_mesg.str());
			exit(1);
		}
		if (crd_start <= ser_end) {
			stringstream err_mesg;
			err_mesg << " expected order is ser no followed by card no in data file\n";
			cerr << LOG_MESSAGE(err_mesg.str());
			exit(1);
		}
		if (ser_start == 0 || ser_end == 0) {
			stringstream err_mesg;
			err_mesg << "please specify ser no in data file\n";
			cerr << LOG_MESSAGE(err_mesg.str());
			exit(1);
		}
		if (auto_determine_data_start_col) {
			data_start_col = crd_end ;
		}
		if (data_end_col <= data_start_col) {
			stringstream err_mesg;
			err_mesg << "It is not possible to fit any data in the given data layout\n";
			cerr << LOG_MESSAGE(err_mesg.str());
			exit(1);
		}
	} else {
		stringstream err_mesg;
		err_mesg << "error in config file: \"" << conf_file_name.str() 
			<< "\"\n"
			<< " it should have this format\n" 
			<< conf_file_format.str() << endl << endl
			<< "... exiting\n";
		cerr << LOG_MESSAGE(err_mesg.str());
		exit(1);
	}
	return 0;
}

}
