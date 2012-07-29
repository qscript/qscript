/*
 * =====================================================================================
 *
 *       Filename:  XtccDataFile.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Tuesday 24 July 2012 04:18:45  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Neil Xavier DSouza
 *        Company:  
 *
 * =====================================================================================
 */

#include <fstream>
#include <iostream>
#include "XtccDataFile.h"


using namespace std;

bool is_a_rating_scale_stublist (string & range_name, int & op_rat_scale,
		bool & op_flag_scale_is_reversed)
{
	//string range_name = n_q->nr_ptr->name;
	int rat_scale = 0;
	int factor = 1;
	bool flag_scale_is_reversed = false;
	bool flag_is_a_rating_scale = false;
	if (isdigit(range_name[range_name.size()-1]) /*&& !(range_name[range_name.size()-1]=='0')*/ ) {
		flag_is_a_rating_scale = true;
		int i = range_name.size()-1;
		while (isdigit(range_name[i])) {
			rat_scale += (range_name[i] - '0') * factor;
			factor *=10;
			--i;
		}
		op_rat_scale = rat_scale;
		if (range_name[i] == 'r' && range_name[i-1] == '_') {
			flag_scale_is_reversed = true;
		}
		op_flag_scale_is_reversed = flag_scale_is_reversed;
	}
	return flag_is_a_rating_scale;
}


void print_simple_include_file (NamedStubQuestion *nq, string setup_dir)
{
	string inc_file_name (setup_dir + nq->nr_ptr->name);
	if (nq->no_mpn == 1) {
		inc_file_name += ".sin";
	} else {
		inc_file_name += ".min";
	}
	fstream inc_file (inc_file_name.c_str(), std::ios_base::out | std::ios_base::ate);

	for (int i=0; i<nq->nr_ptr->stubs.size(); ++i) {
		inc_file << "cnt; " << "\""
			<< nq->nr_ptr->stubs[i].stub_text
			<< "\""
			<< "; c=";
		if (nq->no_mpn==1) { 
			inc_file 
				<< " $var1; " 
				<< " == "
				<< nq->nr_ptr->stubs[i].code 
				<< ";" 
				<< endl;
		} else {
			inc_file 
				<< " $var1; " 
				<< "["
				<< nq->nr_ptr->stubs[i].code 
				<< "]"
				<< " > 0"
				<< ";" 
				<< endl;
		}
	}
}

void XtccDataFileDiskMap::print_xtcc_include_file (fstream & xtcc_ax_file, string setup_dir)
{
	static set<string, less<string> > set_include_file;

	if (NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion*>(q_)) {
		string inc_file_name(setup_dir + nq->nr_ptr->name);
		if (nq->no_mpn == 1) {
			inc_file_name += ".sin";
		} else {
			inc_file_name += ".min";
		}
		if (set_include_file.find (inc_file_name) != set_include_file.end()) {
		} else {
			string range_name = nq->nr_ptr->name;
			bool flag_is_a_rating_scale, flag_scale_is_reversed;
			int rat_scale;
			flag_is_a_rating_scale = is_a_rating_scale_stublist ( range_name, 
					rat_scale, flag_scale_is_reversed);
			if (flag_is_a_rating_scale == false) {
				print_simple_include_file (nq, setup_dir);
#if 0
				for (int i=0; i<nq->nr_ptr->stubs.size(); ++i) {
					inc_file << "cnt; " << "\""
						<< nq->nr_ptr->stubs[i].stub_text
						<< "\""
						<< "; c=";
					if (nq->no_mpn==1) { 
						inc_file 
							// << "_data"
							<< " $var1; " 
							<< " == "
							<< nq->nr_ptr->stubs[i].code 
							<< ";" 
							<< endl;
					} else {
						inc_file 
							// << "_arr["
							//<< nq->nr_ptr->stubs[i].code 
							//<< "]"
							<< " $var1; " 
							<< "["
							<< nq->nr_ptr->stubs[i].code 
							<< "]"
							<< " > 0"
							<< ";" 
							<< endl;
					}
				}
#endif /* 0 */
			} else {
				print_simple_include_file (nq, setup_dir);
				fstream inc_file (inc_file_name.c_str(), std::ios_base::out | std::ios_base::app);
				if (rat_scale == 5) {
					inc_file 
						<< "cnt; \"Top 2 Box (Net)\"; c="
						<< " $var1; == 5 || $var1; == 4;"  
						<< endl
						<< "cnt; \"Bottom 2 Box (Net)\"; c="
						<< " $var1; == 1 || $var1; == 2;"  
						<< endl
						<< "inc; $var1; ;c="
						<< " $var1; >= 1 && $var1; <= 5;"
						<< endl;
				} else if (rat_scale == 7) {
					inc_file 
						<< "cnt; \"Top 2 Box (Net)\"; c="
						<< " $var1; == 7 || $var1; == 6;"  
						<< endl
						<< "cnt; \"Top 3 Box (Net)\"; c="
						<< " $var1; == 7 || $var1; == 6 || $var1; == 5;"  
						<< endl
						<< "cnt; \"Bottom 2 Box (Net)\"; c="
						<< " $var1; == 1 || $var1; == 2;"  
						<< endl
						<< "cnt; \"Bottom 3 Box (Net)\"; c="
						<< " $var1; == 1 || $var1; == 2 || $var1; == 3;"  
						<< endl
						<< "inc; $var1; ;c="
						<< " $var1; >= 1 && $var1; <= 7;"
						<< endl;
				} else if (rat_scale == 10) {
					inc_file 
						<< "cnt; \"Top 2 Box (Net)\"; c="
						<< " $var1; == 10 || $var1; == 9;"  
						<< endl
						<< "cnt; \"Top 3 Box (Net)\"; c="
						<< " $var1; == 10 || $var1; == 9 || $var1; == 8;"  
						<< endl
						<< "cnt; \"Bottom 2 Box (Net)\"; c="
						<< " $var1; == 1 || $var1; == 2;"  
						<< endl
						<< "cnt; \"Bottom 3 Box (Net)\"; c="
						<< " $var1; == 1 || $var1; == 2 || $var1; == 3;" 
						<< endl
						<< "inc; $var1; ;c="
						<< " $var1; >= 1 && $var1; <= 10;"
						<< endl;
				}
			}
			set_include_file.insert(inc_file_name);
		}
	}
}


XtccDataFileDiskMap* GetXtccQuestionMapEntry(vector <XtccDataFileDiskMap*> & qtm_datafile_question_disk_map,
string name)
{
	for (int i=0; i < qtm_datafile_question_disk_map.size(); ++i)
	{
		if (qtm_datafile_question_disk_map[i]->q_->questionName_ == name)
		{
			return qtm_datafile_question_disk_map[i];
		}
	}
	return 0;
}


vector <XtccDataFileDiskMap*> GetXtccQuestionMapEntryArrayQ
	(vector <XtccDataFileDiskMap*> & qtm_datafile_question_disk_map,
	string name)
{
	string dummy_output_filename (string("dummy.output"));
	fstream dummy_output_file(dummy_output_filename.c_str(), ios_base::out|ios_base::app);
	dummy_output_file << "searching for : " << name << endl;
	vector <XtccDataFileDiskMap*> result ;
	for (int i=0; i < qtm_datafile_question_disk_map.size(); ++i)
	{
		string s1 = qtm_datafile_question_disk_map[i]->q_->questionName_ ;
		dummy_output_file << "questionName_: " << s1 << endl;
		string s3 = "";
		if (s1.length() > name.length())
		{
			s3 = s1.substr(0, name.length());
		}
		dummy_output_file << s3 << endl;
		if (qtm_datafile_question_disk_map[i]->q_->questionName_ == name)
		{
			result.push_back(qtm_datafile_question_disk_map[i]);
			dummy_output_file << "added to result" << endl;
		}
	}
	return result;
}

string XtccDataFileDiskMap::print_edit_var_defns_str(string setup_dir)
{
	stringstream var_type_str;
	if (q_->dt == INT8_TYPE) {
		var_type_str << "int8_t";
	} else if (q_->dt == INT16_TYPE) {
		var_type_str << "int16_t";
	} else if (q_->dt == INT32_TYPE) {
		var_type_str << "int32_t";
	} else if (q_->dt == FLOAT_TYPE) {
		var_type_str << "float";
	} else if (q_->dt == DOUBLE_TYPE) {
		var_type_str << "double";
	} else {
		var_type_str << "file: " << __FILE__ << ", line: " << __LINE__
			<< ", func: " << __PRETTY_FUNCTION__ 
			<< ", unhandled question data type: else branch " 
			<< endl;
		cerr  << var_type_str.str() << endl;
		exit(1);
	}
	if (q_->no_mpn == 1) {
		var_type_str
			<< " "
			<< q_->questionName_;
		if (q_->loop_index_values.size())
		{
			for (int i=0; i< q_->loop_index_values.size(); ++i)
			{
				var_type_str << "_" << q_->loop_index_values[i];
			}
		}
		var_type_str << "_data;"
			<< endl;
	} else {
		var_type_str
			<< " "
			<< q_->questionName_;
		if (q_->loop_index_values.size())
		{
			for (int i=0; i< q_->loop_index_values.size(); ++i)
			{
				var_type_str << "_" << q_->loop_index_values[i];
			}
		}
		var_type_str << "_arr["
			<< q_->maxCode_+1
			<< "]"
			<< ";" << endl;
	}
	return var_type_str.str();
}

void XtccDataFileDiskMap::print_edit_var_defns(fstream & xtcc_ax_file, string setup_dir)
{
#if 0
	stringstream var_type_str;
	if (q_->dt == INT8_TYPE) {
		var_type_str << "int8_t";
	} else if (q_->dt == INT16_TYPE) {
		var_type_str << "int16_t";
	} else if (q_->dt == INT32_TYPE) {
		var_type_str << "int32_t";
	} else if (q_->dt == FLOAT_TYPE) {
		var_type_str << "float";
	} else if (q_->dt == DOUBLE_TYPE) {
		var_type_str << "double";
	} else {
		var_type_str << "file: " << __FILE__ << ", line: " << __LINE__
			<< ", func: " << __PRETTY_FUNCTION__ 
			<< ", unhandled question data type: else branch " 
			<< endl;
		cerr  << var_type_str.str() << endl;
		exit(1);
	}
	if (q_->no_mpn == 1) {
		xtcc_ax_file 
			<< var_type_str.str()
			<< " "
			<< q_->questionName_;
		if (q_->loop_index_values.size())
		{
			for (int i=0; i< q_->loop_index_values.size(); ++i)
			{
				xtcc_ax_file << "_" << q_->loop_index_values[i];
			}
		}
		xtcc_ax_file << "_data;"
			<< endl;
	} else {
		xtcc_ax_file 
			<< var_type_str.str()
			<< " "
			<< q_->questionName_;
		if (q_->loop_index_values.size())
		{
			for (int i=0; i< q_->loop_index_values.size(); ++i)
			{
				xtcc_ax_file << "_" << q_->loop_index_values[i];
			}
		}
		xtcc_ax_file << "_arr["
			<< q_->maxCode_+1
			<< "]"
			<< ";" << endl;
	}
#endif /* 0 */
	xtcc_ax_file << print_edit_var_defns_str (setup_dir);
}

string print_recode_edit_xtcc_ax (XtccDataFileDiskMap * driver_q, XtccDataFileDiskMap * recode_q, int index)
{
	// One fine day - revisit this and do it right
	// with the axes code normalized - but for now
	// get it to work
#if 0
	stringstream ax;
	extern string jno;
	string setup_dir( string("setup-") + jno + string ("/"));
	NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*> (driver_q->q_);
	if (nq) {
		const int TEXT_LEN_BREAK_AT = 120;
		//vector <string> smaller_ttls = qtm_data_file_ns::split_into_smaller_chunks (recode_q->q_->questionText_, TEXT_LEN_BREAK_AT);
		//stringstream ttl_string;
		//for (int i=0; i<smaller_ttls.size(); ++i) {
		//	ttl_string << smaller_ttls[i];
		//}
		stringstream ttl_string;
		ttl_string << recode_q->q_->questionText_ << endl;
		if (recode_q->q_->loop_index_values.size() > 0) {
			stringstream l_base_text;
			l_base_text << " Fix base text: " << __LINE__ << ", " << __FILE__ << ", " << __PRETTY_FUNCTION__ << endl;
#if 0
			if (recode_q->baseText_.isDynamicBaseText_ == false) {
				l_base_text << recode_q->baseText_.baseText_ ;
			} else {
				l_base_text << qtm_data_file_ns::print_dynamic_base_text (recode_q->q_, recode_q->baseText_);
			}
			l_base_text << " who use : " << nq->nr_ptr->stubs[index].stub_text << endl;
#endif /* 0 */
			if (recode_q->q_->loop_index_values.size()==1) {
				ax << "*include " << "r_" << recode_q->q_->questionName_ 
					<<".qax"
					<<";qlno=" << recode_q->q_->loop_index_values[0] << ";var_name=" << recode_q->q_->questionName_ ;
					for (int i2=0; i2 < recode_q->q_->loop_index_values.size(); ++i2) {
						 ax << "_" << recode_q->q_->loop_index_values[i2];
						}
 				ax << "_" << nq->nr_ptr->stubs[index].stub_text_as_var_name()
					<<";col(a)=" << 1
					<<";qat1t=&a" << recode_q->q_->loop_index_values[0] <<"t;att1t=;qat2t=;att2t=/*;"
					<<"\n+btxt=" << l_base_text.str()
					<< endl
					<< endl;
			} else {
				ax <<"*include r_" << recode_q->q_->questionName_
					<<".qax"
					<<";col(a)=" << recode_q->q_->loop_index_values[0] + 1
					<<";qlno=" << recode_q->q_->loop_index_values[0] <<"_" << recode_q->q_->loop_index_values[1] << ";var_name="  << recode_q->q_->questionName_ << "_" << nq->nr_ptr->stubs[index].stub_text_as_var_name()
					<<";qat1t=&a" << recode_q->q_->loop_index_values[0] <<"t;att1t="
					<<";qat2t=&b" << recode_q->q_->loop_index_values[0] <<"t;att2t=" << endl
					<<"\n+btxt = " << l_base_text.str()
					<< endl
					<< endl;
			}
	
			bool is_1st_iter = true;
			for (int32_t i=0; i<recode_q->q_->loop_index_values.size(); ++i) {
				if (recode_q->q_->loop_index_values[i] != 0) {
					is_1st_iter = false;
					break;
				}
			}
			if (is_1st_iter == true) {
				// make questionName_ . qax file
				stringstream qax_fname;
				qax_fname << setup_dir <<"";
				qax_fname << "r_" << recode_q->q_->questionName_ <<".qax";
				fstream ax(qax_fname.str().c_str(), std::ios_base::out | std::ios_base::trunc);
				ax <<"l " << recode_q->q_->questionName_ <<"_&qlno;c=&var_name(a0";
				if (recode_q->width_>0) {
					ax <<",a" << recode_q->width_-1 ;
				} 
				ax <<") u $ $" << endl;
				ax <<"*include qttl.qin;" 
					<< ttl_string.str() << endl
					<<"*include base.qin" << endl;
	
				if (NamedStubQuestion * n_q = dynamic_cast<NamedStubQuestion*>(recode_q->q_)) {
					//recode_q->print_qin(setup_dir, "&var_name");
					if (n_q->nr_ptr) {
						if (n_q->no_mpn>1) {
							ax <<"*include r_" << n_q->nr_ptr->name <<".min"
							<< endl;
						} else {
							ax <<"*include r_" << n_q->nr_ptr->name <<".sin"
							<< endl;
						}
					}
				} else if (RangeQuestion * r_q = dynamic_cast<RangeQuestion*>(recode_q->q_)) {
					ax <<"*include " << "r_" << recode_q->q_->questionName_ <<".qin"
						<< endl;
					stringstream fname;
					fname << setup_dir << "r_" << recode_q->q_->questionName_ <<".qin";
					fstream qtm_include_file (fname.str().c_str(), 
							std::ios_base::out | std::ios_base::trunc);
					if (recode_q->width_ == 1) {
						qtm_include_file <<"val &var_name(a0);i;" 
							<< endl;
					} else {
						qtm_include_file <<"val &var_name(a0"
							<<"" << recode_q->width_ - 1 <<");i;" 
							<< endl;
					}
				}
					
			}
		} else {
			ax << "ax ";
			ax << recode_q->q_->questionName_ << "_" << nq->nr_ptr->stubs[index].stub_text_as_var_name();
			ax << "; c=" << recode_q->q_->questionName_ << "_" 
				<< nq->nr_ptr->stubs[index].stub_text_as_var_name() 
				<< "_data > 0;\n" 
				//<< recode_q->totalLength_ << ") u $ $\n"
				<< endl;
			ax << "*include qttl.qin;qno=" << recode_q->q_->questionName_ << "_" << nq->nr_ptr->stubs[index].stub_text_as_var_name() << ";";
	
	
			ax << ttl_string.str();
	
			ax << "+q1att=;att1t=/*" << endl;
			ax << "+q2att=;att2t=/*" << endl;

			stringstream l_base_text;
			l_base_text << " Fix base text: " << __LINE__ << ", " << __FILE__ << ", " << __PRETTY_FUNCTION__ << endl;
			ax << l_base_text.str();
	
			//if (recode_q->baseText_.isDynamicBaseText_ == false) {
			//	ax <<"*include base.qin;btxt=" << recode_q->baseText_.baseText_ << " who use : " << nq->nr_ptr->stubs[index].stub_text << endl;
			//} else {
			//	ax <<"*include base.qin;btxt= Unexpected case non-array questions should not have dynamicBaseQuestion_ : 3516, src/qscript_parser.cpp, void qscript_parser::print_recode_edit_qax(FILE*) ";
			//}
	
			if (NamedStubQuestion * n_q = dynamic_cast<NamedStubQuestion*>(recode_q->q_)) {
				//recode_q->print_qin (setup_dir, "&var_name");
				if (n_q->nr_ptr) {
					if (n_q->no_mpn>1) {
						ax <<"*include r_" << n_q->nr_ptr->name <<".min;"
						<<"col(a)=" << 1 << ";var_name=" << recode_q->q_->questionName_ << "_" << nq->nr_ptr->stubs[index].stub_text_as_var_name() << ";"
						<< endl;
					} else {
						ax <<"*include r_" << n_q->nr_ptr->name <<".sin;"
						<<"col(a)=" << 1 << ";var_name=" << recode_q->q_->questionName_ << "_" << nq->nr_ptr->stubs[index].stub_text_as_var_name() << ";"
						<< endl;
					}
				}
			} else if (RangeQuestion * r_q = dynamic_cast<RangeQuestion*>(recode_q->q_)) {
				ax <<"*include r_" << recode_q->q_->questionName_ <<".qin;"
					<<"col(a)=" << 1 << ";var_name=" << recode_q->q_->questionName_ << "_" << nq->nr_ptr->stubs[index].stub_text_as_var_name() << ";"
					<<""
					<< endl;
				stringstream fname;
				fname << setup_dir << "r_" << recode_q->q_->questionName_ <<".qin;";
				fstream qtm_include_file (fname.str().c_str(), 
						std::ios_base::out | std::ios_base::trunc);
				if (recode_q->width_ == 1) {
					qtm_include_file <<"val &var_name(a0);i;" 
						<< endl;
				} else {
					qtm_include_file <<"val &var_name(a0"
						<<"" << recode_q->width_ - 1 <<");i;" 
						<< endl;
				}
			}
	
			ax << endl;
		}
	} else {
		ax << " driver question does not have named stubs, this should be an input file error" << endl;
	}
	return ax.str();
#endif /*  0 */
	stringstream ax;
	//cerr << "index: " << index << endl;

	NamedStubQuestion * nq = dynamic_cast <NamedStubQuestion*> (driver_q->q_);

	ax 	<< "ax "
		<< print_recode_edit_xtcc_combined_ax_name
			(driver_q, recode_q, index)
			<< endl;


	//string combined_ax_data_variable_name = 
	//	print_recode_edit_xtcc_combined_ax_var_name 
	//		(recode_q, driver_q, index);
	//
	stringstream s1;
	s1 << 	print_recode_edit_xtcc_combined_ax_var_name
			(driver_q, recode_q, index);
	string combined_ax_data_variable_name = s1.str();
	if (recode_q->q_->no_mpn == 1) {
		ax << "; c=" 
			<< combined_ax_data_variable_name << " > 0 ;"
			<< endl;
	} else {
		ax << "; c=" 
			<< combined_ax_data_variable_name << "[0]" << " > 0 ;"
			<< endl;
	}

#if 1
	ax
		<< "ttl; " << "\"" << recode_q->q_->questionName_ 
		<< "." 
		<< recode_q->q_->questionText_ 
		<< ":"
		<< nq->nr_ptr->stubs[index].stub_text
		<< "\";" 
		<< endl ;

	if (NamedStubQuestion * r_nq = dynamic_cast<NamedStubQuestion*> (recode_q->q_)) {
		//xtcc_ax_file << "tot; " << "\"" << "Total" << "\";" << endl;
		ax << "#include base.xin;btxt=\"Total\";" << endl;
		//print_xtcc_include_file (xtcc_ax_file, setup_dir);
		named_range * nr_ptr = r_nq->nr_ptr;
		if (r_nq->no_mpn == 1) {
			ax << "#include " << nr_ptr->name << ".sin;" ;
		} else {
			ax << "#include " << nr_ptr->name << ".min;" ;
		}
		/*
		for (int i=0; i<nr_ptr->stubs.size(); ++i) {
		*/

		ax 
			//<< "cnt; " << "\""
			//<< nr_ptr->stubs[i].stub_text
			//<< "\""
			//<< "; c="
			//<< "; c="
			<< " var1=\""
			<< combined_ax_data_variable_name
			<< "\";"
			<< endl;

		/*
		}
		*/
	} else if (RangeQuestion *rq = dynamic_cast<RangeQuestion*>(recode_q->q_)) {
		ax << "tot; " << "\"" << "Total" << "\";" << endl;
		set<int32_t> & indiv = rq->r_data->indiv;
		for (set<int32_t>::iterator it1 = indiv.begin();
				it1 != indiv.end(); ++it1) {
			ax << "cnt; " << "\""
				<< *it1 
				<< "\""
				<< "; c="
				<< recode_q->q_->questionName_;
			if (recode_q->q_->loop_index_values.size())
			{
				for (int i=0; i< recode_q->q_->loop_index_values.size(); ++i)
				{
					ax << "_" << recode_q->q_->loop_index_values[i];
				}
			}
			//ax << "_data == "
			//	<< *it1
			//	<< ";" 
			//	<< endl;
			if (rq->no_mpn==1) { 
				ax << "_data == "
					<< *it1
					<< ";/*  ------------------- */" 
					<< endl;
			} else {
				ax << "_arr["
					<< *it1
					<< "]"
					<< " == "
					<< *it1
					<< "; /*  =================== */" 
					<< endl;
			}
		}
		vector < pair<int32_t,int32_t> > range
			= rq->r_data->range;
		if (rq->no_mpn==1) {
			for (int i=0; i<range.size(); ++i) {
				ax << "cnt; " << "\""
					<< range[i].first 
					<< " - "
					<< range[i].second
					<< "\""
					<< "; c="
					<< recode_q->q_->questionName_;
				if (recode_q->q_->loop_index_values.size())
				{
					for (int i = 0; i< recode_q->q_->loop_index_values.size(); ++i)
					{
						ax << "_" << recode_q->q_->loop_index_values[i];
					}
				}
				ax << "_data >= "
					<< range[i].first
					<< " && "
					<< recode_q->q_->questionName_;
				if (recode_q->q_->loop_index_values.size())
				{
					for (int i=0; i< recode_q->q_->loop_index_values.size(); ++i)
					{
						ax << "_" << recode_q->q_->loop_index_values[i];
					}
				}
				ax << "_data <= "
					<< range[i].second
					<< ";" 
					<< endl;
			}
		} else {
			ax << "cnt; " << "\"all\"; c= all == 1;\n";
			/*

			for (int i=0; i<range.size(); ++i) {
				ax << "cnt; " << "\""
					<< range[i].first 
					<< " - "
					<< range[i].second
					<< "\""
					<< "; c="
					<< q_->questionName_;
				if (q_->loop_index_values.size())
				{
					for (int i=0; i< q_->loop_index_values.size(); ++i)
					{
						ax << "_" << q_->loop_index_values[i];
					}
				}
				ax << "_arr >= "
					<< range[i].first
					<< " && "
					<< q_->questionName_;
				if (q_->loop_index_values.size())
				{
					for (int i=0; i< q_->loop_index_values.size(); ++i)
					{
						ax << "_" << q_->loop_index_values[i];
					}
				}
				ax << "_arr <= "
					<< range[i].second
					<< ";" 
					<< endl;
			}
			*/
		}
	}
#endif /*  0 */
	ax << endl << endl;
	return ax.str();
}

string print_recode_edit_xtcc_combined_name
	(XtccDataFileDiskMap * driver_q,
	 XtccDataFileDiskMap * recode_q, int index)
{
	stringstream defn;

	NamedStubQuestion * nq = dynamic_cast <NamedStubQuestion*> 
					(driver_q->q_);
	//if (recode_q->q_-> no_mpn == 1) {
		//defn << recode_q->q_->questionName_ << " is single coded" << endl;
	defn
		<< recode_q->q_->questionName_;

		//if (recode_q->q_
	for (int i = 0; i < recode_q->q_->loop_index_values.size(); 
			++i) {
		defn << "_" << recode_q->q_->loop_index_values[i];
	}
	defn	
		<< "_"
		<< nq->nr_ptr->stubs[index].stub_text_as_var_name();
		
	//} else {
		//defn << recode_q->q_->questionName_ << " is multi coded" << endl;
		//defn
		//	<< "int32_t " << recode_q->q_->questionName_ << "_"
		//	<< nq->nr_ptr->stubs[index].stub_text_as_var_name() << "_arr["
		//	<< recode_q->q_-> no_mpn << "];"
		//	<< endl;
	//}
#if 0	
	if (recode_q->q_-> no_mpn == 1) {
		defn
			<< "_data;"
			<< endl;
	} else {
		defn
			<< "_arr["
			<< recode_q->q_-> no_mpn << "];"
			<< endl;
	}
#endif /*  0 */
	return defn.str();
}

string print_recode_edit_xtcc_combined_ax_name 
	(XtccDataFileDiskMap * driver_q,
	 XtccDataFileDiskMap * recode_q, int index)
{
	string s;
	s = print_recode_edit_xtcc_combined_name 
		(driver_q, recode_q, index);
	return s;
}

string print_recode_edit_xtcc_combined_ax_var_name 
	(XtccDataFileDiskMap * driver_q,
	 XtccDataFileDiskMap * recode_q, int index)
{

	string s;
	//stringstream var_name;
	s =  print_recode_edit_xtcc_combined_name
		(driver_q, recode_q, index);
	if (recode_q->q_-> no_mpn == 1) {
		s += "_data";
	} else {
		s += "_arr";
	}
	return s;
}

void XtccDataFileDiskMap::print_xtcc_ax2(fstream & xtcc_ax_file, string setup_dir)
{
	xtcc_ax_file 
		<< endl
		<< "ax ";
#if 0
	<< q_->questionName_ ;

	if (q_->loop_index_values.size())
	{
		for (int i=0; i< q_->loop_index_values.size(); ++i) {
			xtcc_ax_file << "_" << q_->loop_index_values[i];
		}
	}
#endif /*  0 */
	xtcc_ax_file << print_xtcc_ax_name();
	string ax_data_variable_name = print_xtcc_ax_data_variable_name();
	if (q_->no_mpn == 1) {
		xtcc_ax_file << "; c=" 
			<< ax_data_variable_name << " > 0 ;"
			<< endl;
	} else {
		xtcc_ax_file << "; c=" 
			<< ax_data_variable_name << "[0]" << " > 0 ;"
			<< endl;
	}

	xtcc_ax_file
		<< "ttl; " << "\"" << q_->questionName_ 
		<< "." 
		<< q_->questionText_ 
		<< "\";" 
		<< endl << endl;
	if (NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion*>(q_)) {
		//xtcc_ax_file << "tot; " << "\"" << "Total" << "\";" << endl;
		xtcc_ax_file << "#include base.xin;btxt=\"Total\";" << endl;
		print_xtcc_include_file (xtcc_ax_file, setup_dir);
		named_range * nr_ptr = nq->nr_ptr;
		if (nq->no_mpn == 1) {
			xtcc_ax_file << "#include " << nr_ptr->name << ".sin;" ;
		} else {
			xtcc_ax_file << "#include " << nr_ptr->name << ".min;" ;
		}
		/*
		for (int i=0; i<nr_ptr->stubs.size(); ++i) {
		*/

		xtcc_ax_file 
			//<< "cnt; " << "\""
			//<< nr_ptr->stubs[i].stub_text
			//<< "\""
			//<< "; c="
			//<< "; c="
			<< " var1=\""
			<< ax_data_variable_name
			<< "\";"
			<< endl;

		/*
		}
		*/
	} else if (RangeQuestion *rq = dynamic_cast<RangeQuestion*>(q_)) {
		xtcc_ax_file << "tot; " << "\"" << "Total" << "\";" << endl;
		set<int32_t> & indiv = rq->r_data->indiv;
		for (set<int32_t>::iterator it1 = indiv.begin();
				it1 != indiv.end(); ++it1) {
			xtcc_ax_file << "cnt; " << "\""
				<< *it1 
				<< "\""
				<< "; c="
				<< q_->questionName_;
			if (q_->loop_index_values.size())
			{
				for (int i=0; i< q_->loop_index_values.size(); ++i)
				{
					xtcc_ax_file << "_" << q_->loop_index_values[i];
				}
			}
			//xtcc_ax_file << "_data == "
			//	<< *it1
			//	<< ";" 
			//	<< endl;
			if (rq->no_mpn==1) { 
				xtcc_ax_file << "_data == "
					<< *it1
					<< ";/*  ------------------- */" 
					<< endl;
			} else {
				xtcc_ax_file << "_arr["
					<< *it1
					<< "]"
					<< " == "
					<< *it1
					<< "; /*  =================== */" 
					<< endl;
			}
		}
		vector < pair<int32_t,int32_t> > range
			= rq->r_data->range;
		if (rq->no_mpn==1) {
			for (int i=0; i<range.size(); ++i) {
				xtcc_ax_file << "cnt; " << "\""
					<< range[i].first 
					<< " - "
					<< range[i].second
					<< "\""
					<< "; c="
					<< q_->questionName_;
				if (q_->loop_index_values.size())
				{
					for (int i=0; i< q_->loop_index_values.size(); ++i)
					{
						xtcc_ax_file << "_" << q_->loop_index_values[i];
					}
				}
				xtcc_ax_file << "_data >= "
					<< range[i].first
					<< " && "
					<< q_->questionName_;
				if (q_->loop_index_values.size())
				{
					for (int i=0; i< q_->loop_index_values.size(); ++i)
					{
						xtcc_ax_file << "_" << q_->loop_index_values[i];
					}
				}
				xtcc_ax_file << "_data <= "
					<< range[i].second
					<< ";" 
					<< endl;
			}
		} else {
			xtcc_ax_file << "cnt; " << "\"all\"; c= all == 1;\n";
			/*

			for (int i=0; i<range.size(); ++i) {
				xtcc_ax_file << "cnt; " << "\""
					<< range[i].first 
					<< " - "
					<< range[i].second
					<< "\""
					<< "; c="
					<< q_->questionName_;
				if (q_->loop_index_values.size())
				{
					for (int i=0; i< q_->loop_index_values.size(); ++i)
					{
						xtcc_ax_file << "_" << q_->loop_index_values[i];
					}
				}
				xtcc_ax_file << "_arr >= "
					<< range[i].first
					<< " && "
					<< q_->questionName_;
				if (q_->loop_index_values.size())
				{
					for (int i=0; i< q_->loop_index_values.size(); ++i)
					{
						xtcc_ax_file << "_" << q_->loop_index_values[i];
					}
				}
				xtcc_ax_file << "_arr <= "
					<< range[i].second
					<< ";" 
					<< endl;
			}
			*/
		}
	}
}

#if 0
string print_recode_edit_xtcc_var_defn_arrayq (XtccDataFileDiskMap * driver_q, XtccDataFileDiskMap *  recode_q_vec, int index)
{
	stringstream var_defn;
	var_defn << "int32_t "
		<< recode_q_vec[0]->q_->questionName_ << endl;

	for (int i2=0; i2 < recode_q_vec.size(); ++i2) {
		var_defn << "_" << recode_q_vec->q_->loop_index_values[i2];
	}

	//<< rec_question_name << "_map_entry[i1]->"
	//<< "q_->loop_index_values.size(); ++i2) {\n"
	//<< "\t\t\t\t\t\t variable_file << \"_\" << "
	//<< rec_question_name << "_map_entry[i1]->q_->"
	//<< "loop_index_values[i2];\n"
	//<< "\t\t\t\t\t}\n"
	
	//<< "\t\t\t\t\tvariable_file << \"_\" << "
	//<< driver_question_name
	//<< "->nr_ptr->stubs[i].stub_text_as_var_name() << \" \" << " 
	//<< rec_question_name << "_map_entry[i1]->totalLength_ " << " << \"s\\n\";\n"
	NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*> (driver_q->q_);
	var_defn 
		<< "_" << nq -> nr_ptr->stubs[index].stub_text_as_var_name()
		<< ";" << endl;

	//<< "\t\t\t\t\trecode_edit_qax_file\n"
	//<< "\t\t\t\t\t\t	<< print_recode_edit_qax (" 
	//<< driver_question_name << "_map_entry, "
	//<< rec_question_name << "_map_entry[i1], i);\n" 
	//<< endl;
	return var_defn.str();
}
#endif /* 0 */

string print_recode_edit_xtcc_var_defn (XtccDataFileDiskMap * driver_q, XtccDataFileDiskMap * recode_q, int index)
{
	stringstream defn;

	NamedStubQuestion * nq = dynamic_cast <NamedStubQuestion*> (driver_q->q_);
	//if (recode_q->q_-> no_mpn == 1) {
		//defn << recode_q->q_->questionName_ << " is single coded" << endl;
		defn
			<< "int32_t " << recode_q->q_->questionName_;

		//if (recode_q->q_
		for (int i = 0; i < recode_q->q_->loop_index_values.size(); 
				++i) {
			defn << "_" << recode_q->q_->loop_index_values[i];
		}
		defn	
			<< "_"
			<< nq->nr_ptr->stubs[index].stub_text_as_var_name();
		
	//} else {
		//defn << recode_q->q_->questionName_ << " is multi coded" << endl;
		//defn
		//	<< "int32_t " << recode_q->q_->questionName_ << "_"
		//	<< nq->nr_ptr->stubs[index].stub_text_as_var_name() << "_arr["
		//	<< recode_q->q_-> no_mpn << "];"
		//	<< endl;
	//}
	if (recode_q->q_-> no_mpn == 1) {
		defn
			<< "_data;"
			<< endl;
	} else {
		defn
			<< "_arr["
			<< recode_q->q_-> no_mpn << "];"
			<< endl;
	}
	return defn.str();
}

string print_recode_edit_xtcc_var_init (XtccDataFileDiskMap * driver_q, XtccDataFileDiskMap * recode_q, int index)
{
	stringstream init_code;
	NamedStubQuestion * nq = dynamic_cast <NamedStubQuestion*> (driver_q->q_);
	if (recode_q->q_->no_mpn == 1) {

		//<< leader_rec_question_name << "_\"" << endl
		//<< "\t\t\t\t\t<< "
		//<< driver_question_name
		//<< "->nr_ptr->stubs[i].stub_text_as_var_name() << \"_data = 0;\\n\" ;" << endl;

		/*
		 * The below block of code should be extracted out into a pure
		 * function : print_combined_variable - and used throughout
		 * wherever the pattern is seen
		 * I am too fatigued out to do it right now
		 */

		init_code 
			<< recode_q->q_->questionName_ ;
		for (int i = 0; i < recode_q->q_->loop_index_values.size(); 
				++i) {
			init_code << "_" << recode_q->q_->loop_index_values[i];
		}

		init_code 
			<< "_" 
			<< nq->nr_ptr->stubs[index].stub_text_as_var_name() 
			<< "_data = 0;"
			<< endl;
	} else {
		init_code 
			<< "{int32_t xtcc_i1=0;"
			<< "for (xtcc_i1=0; xtcc_i1 < "
			<< recode_q->q_->no_mpn 
			<< ";  xtcc_i1 = xtcc_i1 + 1) {\n\t"
			<< recode_q->q_->questionName_ ;

		for (int i = 0; i < recode_q->q_->loop_index_values.size(); 
				++i) {
			init_code << "_" << recode_q->q_->loop_index_values[i];
		}
		init_code
			<< "_" 
			<< nq->nr_ptr->stubs[index].stub_text_as_var_name() 
			<< "_arr[xtcc_i1] = 0;"
			<< "}\n"
			<< "}\n";

	}
	return init_code.str();

}

string print_recode_edit_xtcc_data_xfer (XtccDataFileDiskMap * driver_q, XtccDataFileDiskMap * leader_recode_q, 
		XtccDataFileDiskMap * recode_q, int index)
{
	stringstream data_xfer_recode;
	NamedStubQuestion * nq = dynamic_cast <NamedStubQuestion*> (driver_q->q_);
	if (recode_q->q_->no_mpn == 1) {
		//data_xfer_recode << "single code recode" << endl;
		data_xfer_recode 
			<< "\t"
			<< leader_recode_q->q_->questionName_ ;
		for (int i = 0; i < recode_q->q_->loop_index_values.size(); 
				++i) {
			data_xfer_recode << "_" << recode_q->q_->loop_index_values[i];
		}

		data_xfer_recode
			<< "_" << nq->nr_ptr->stubs[index].stub_text_as_var_name()
			<< "_data"
			<< " = "
			<< recode_q->print_xtcc_ax_data_variable_name()
			<< ";\n";
			//<< recode_q->q_->questionName_ << "_data;\n";
	} else {
		//data_xfer_recode << "multi code recode" << endl;
		data_xfer_recode 
			<< "{"
			<< "int32_t xtcc_i1=0;"
			<< "for (xtcc_i1=0; xtcc_i1 < "
			<< recode_q->q_->no_mpn 
			<< ";  xtcc_i1 = xtcc_i1 + 1) {\n\t"
			<< leader_recode_q->q_->questionName_ 
			<< "_" << nq->nr_ptr->stubs[index].stub_text_as_var_name();
		for (int i = 0; i < recode_q->q_->loop_index_values.size(); 
				++i) {
			data_xfer_recode << "_" << recode_q->q_->loop_index_values[i];
		}
		data_xfer_recode
			<< "_arr[xtcc_i1] = "
			<< recode_q->q_->questionName_ << "_arr[xtcc_i1];\n" 
			<< "}\n"
			<< "}\n";

	}
	return data_xfer_recode.str();

}


void XtccDataFileDiskMap::print_xtcc_ax (fstream & xtcc_ax_file,
		string setup_dir)
{
	xtcc_ax_file 
		<< endl
		<< "ax ";
	
#if 0
	<< q_->questionName_ ;

	if (q_->loop_index_values.size())
	{
		for (int i=0; i< q_->loop_index_values.size(); ++i)
		{
			xtcc_ax_file << "_" << q_->loop_index_values[i];
		}
	}
#endif /* 0 */
	xtcc_ax_file << print_xtcc_ax_name();
	xtcc_ax_file << ";" << endl
		<< "ttl; " << "\"" << q_->questionName_ 
		<< "." 
		<< q_->questionText_ 
		<< "\";" 
		<< endl << endl;
	xtcc_ax_file << "tot; " << "\"" << "Total" << "\";" << endl;
	if (NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion*>(q_)) {
		named_range * nr_ptr = nq->nr_ptr;
		for (int i=0; i<nr_ptr->stubs.size(); ++i) {
			xtcc_ax_file << "cnt; " << "\""
				<< nr_ptr->stubs[i].stub_text
				<< "\""
				<< "; c=";
#if 0
				<< q_->questionName_;
			if (q_->loop_index_values.size())
			{
				for (int i=0; i< q_->loop_index_values.size(); ++i)
				{
					xtcc_ax_file << "_" << q_->loop_index_values[i];
				}
			}
#endif /*  0 */
			xtcc_ax_file << 
				print_xtcc_ax_data_variable_name();
			if (nq->no_mpn==1) { 
				//xtcc_ax_file << "_data == "
				xtcc_ax_file << " == "
					<< nr_ptr->stubs[i].code 
					<< ";" 
					<< endl;
			} else {
				//xtcc_ax_file << "_arr["
				xtcc_ax_file << "["
					<< nr_ptr->stubs[i].code 
					<< "]"
					<< " > 0"
					<< ";" 
					<< endl;
			}
		}
	} else if (RangeQuestion *rq = dynamic_cast<RangeQuestion*>(q_)) {
		set<int32_t> & indiv = rq->r_data->indiv;
		for (set<int32_t>::iterator it1 = indiv.begin();
				it1 != indiv.end(); ++it1) {
			xtcc_ax_file << "cnt; " << "\""
				<< *it1 
				<< "\""
				<< "; c="
				<< q_->questionName_;
			if (q_->loop_index_values.size())
			{
				for (int i=0; i< q_->loop_index_values.size(); ++i)
				{
					xtcc_ax_file << "_" << q_->loop_index_values[i];
				}
			}
			//xtcc_ax_file << "_data == "
			//	<< *it1
			//	<< ";" 
			//	<< endl;
			if (rq->no_mpn==1) { 
				xtcc_ax_file << "_data == "
					<< *it1
					<< ";" 
					<< endl;
			} else {
				xtcc_ax_file << "_arr["
					<< *it1
					<< "]"
					<< " == "
					<< *it1
					<< ";" 
					<< endl;
			}
		}
		vector < pair<int32_t,int32_t> > range
			= rq->r_data->range;
		if (rq->no_mpn==1) {
			for (int i=0; i<range.size(); ++i) {
				xtcc_ax_file << "cnt; " << "\""
					<< range[i].first 
					<< " - "
					<< range[i].second
					<< "\""
					<< "; c="
					<< q_->questionName_;
				if (q_->loop_index_values.size())
				{
					for (int i=0; i< q_->loop_index_values.size(); ++i)
					{
						xtcc_ax_file << "_" << q_->loop_index_values[i];
					}
				}
				xtcc_ax_file << "_data >= "
					<< range[i].first
					<< " && "
					<< q_->questionName_;
				if (q_->loop_index_values.size())
				{
					for (int i=0; i< q_->loop_index_values.size(); ++i)
					{
						xtcc_ax_file << "_" << q_->loop_index_values[i];
					}
				}
				xtcc_ax_file << "_data <= "
					<< range[i].second
					<< ";" 
					<< endl;
			}
		} else {
			xtcc_ax_file << "cnt; " << "\"all\"; c= all == 1;\n";
			/*

			for (int i=0; i<range.size(); ++i) {
				xtcc_ax_file << "cnt; " << "\""
					<< range[i].first 
					<< " - "
					<< range[i].second
					<< "\""
					<< "; c="
					<< q_->questionName_;
				if (q_->loop_index_values.size())
				{
					for (int i=0; i< q_->loop_index_values.size(); ++i)
					{
						xtcc_ax_file << "_" << q_->loop_index_values[i];
					}
				}
				xtcc_ax_file << "_arr >= "
					<< range[i].first
					<< " && "
					<< q_->questionName_;
				if (q_->loop_index_values.size())
				{
					for (int i=0; i< q_->loop_index_values.size(); ++i)
					{
						xtcc_ax_file << "_" << q_->loop_index_values[i];
					}
				}
				xtcc_ax_file << "_arr <= "
					<< range[i].second
					<< ";" 
					<< endl;
			}
			*/
		}
	}
}

string XtccDataFileDiskMap::print_xtcc_ax_name()
{
	stringstream ax_data_variable_name;
	ax_data_variable_name	<< q_->questionName_;
	if (q_->loop_index_values.size()) {
		for (int i = 0; i < q_->loop_index_values.size(); ++i) {
			ax_data_variable_name << "_" << q_->loop_index_values[i];
		}
	}
#if 0
	if (q_->no_mpn==1) { 
		//xtcc_ax_file << "_data == "
		//	<< nr_ptr->stubs[i].code 
		//	<< ";" 
		//	<< endl;
		ax_data_variable_name << "_data" ;
	} else {
		//xtcc_ax_file << "_arr["
		//	<< nr_ptr->stubs[i].code 
		//	<< "]"
		//	<< " > 0"
		//	<< ";" 
		//	<< endl;
		ax_data_variable_name << "_arr";
	}
#endif /* 0 */
	return ax_data_variable_name.str();
}

string XtccDataFileDiskMap::print_xtcc_ax_data_variable_name()
{
	stringstream ax_data_variable_name;
#if 0
	ax_data_variable_name	<< q_->questionName_;
	if (q_->loop_index_values.size()) {
		for (int i=0; i< q_->loop_index_values.size(); ++i)
		{
			ax_data_variable_name << "_" << q_->loop_index_values[i];
		}
	}
#endif /*  0 */

	ax_data_variable_name << print_xtcc_ax_name() ;
	if (q_->no_mpn == 1) { 
		//xtcc_ax_file << "_data == "
		//	<< nr_ptr->stubs[i].code 
		//	<< ";" 
		//	<< endl;
		ax_data_variable_name << "_data" ;
	} else {
		//xtcc_ax_file << "_arr["
		//	<< nr_ptr->stubs[i].code 
		//	<< "]"
		//	<< " > 0"
		//	<< ";" 
		//	<< endl;
		ax_data_variable_name << "_arr";
	}
	return ax_data_variable_name.str();
}
