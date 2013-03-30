/*
 * =====================================================================================
 *
 *       Filename:  question_gtk_runtime.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Monday 05 March 2012 03:13:38  GMT
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Neil Xavier D'Souza
 *        Company:
 *
 * =====================================================================================
 */

#include <iostream>
#include <libintl.h>
#include <locale.h>

using namespace std;

#include "question.h"
#include "named_range.h"



enum UI_Mode { NCurses_Mode, Microhttpd_Mode, Wt_Mode, Gtk_Mode};
extern UI_Mode ui_mode;


string NamedStubQuestion::PrintSelectedAnswers()
{
	//return string("hello");
	//stringstream select_answers_text;
	//Wt::WString select_answers_text;
	string select_answers_text;
	bool first_time = true;
	for (set<int32_t>::iterator inp_data_iter = input_data.begin();
			inp_data_iter != input_data.end(); ++inp_data_iter) {
		stringstream mesg_key;
		mesg_key << nr_ptr->name << "_" << *inp_data_iter - 1;
		if (first_time) {
			//select_answers_text << nr_ptr->stubs[*inp_data_iter-1].stub_text;
			cout << "searching for : " << mesg_key.str() << endl;
			//if (ui_mode == Wt_Mode) {
			//	Wt::WString w_str = Wt::WString::tr(mesg_key.str());
			//	select_answers_text += w_str.toUTF8();
			//} else {
				//select_answers_text += gettext(mesg_key.str().c_str());
				select_answers_text += gettext(nr_ptr->stubs[*inp_data_iter - 1].stub_text.c_str());
			//}
			first_time = false;
		} else {
			//select_answers_text << ", " << nr_ptr->stubs[*inp_data_iter-1].stub_text ;
			cout << "searching for : " << mesg_key.str() << endl;
			//if (ui_mode == Wt_Mode) {
			//	select_answers_text += Wt::WString(", ").toUTF8() +  Wt::WString::tr(mesg_key.str()).toUTF8();
			//} else {
				//select_answers_text += gettext(mesg_key.str().c_str());
				select_answers_text += gettext(nr_ptr->stubs[*inp_data_iter - 1].stub_text.c_str());
			//}
		}
	}
	//select_answers_text << nr_ptr->stubs[codeIndex_].stub_text;
	//return select_answers_text.str();
	return select_answers_text;
}

//Wt::WString NamedStubQuestion::PrintSelectedAnswers(int code_index)
string NamedStubQuestion::PrintSelectedAnswers(int code_index)
{
	//return string("hello");
	//Wt::WString select_answers_text;
	bool first_time = true;
	//for (set<int32_t>::iterator inp_data_iter = input_data.begin();
	//		inp_data_iter != input_data.end(); ++inp_data_iter) {
	//	if (first_time) {
	//		select_answers_text << nr_ptr->stubs[*inp_data_iter-1].stub_text;
	//		first_time = false;
	//	} else {
	//		select_answers_text << ", " << nr_ptr->stubs[*inp_data_iter-1].stub_text ;
	//	}
	//}
	stringstream mesg_key;
	mesg_key << nr_ptr->name << "_" << code_index ;
	//select_answers_text << nr_ptr->stubs[code_index].stub_text;
	//select_answers_text << WString::tr(mesg_key.str());
	//return select_answers_text.str();
	//if (ui_mode == Wt_Mode) {
	//	Wt::WString w_str = Wt::WString::tr(mesg_key.str());
	//	return w_str.toUTF8();
	//} else {
		//return string (gettext(mesg_key.str().c_str()));
		return string (gettext( nr_ptr->stubs[code_index].stub_text.c_str() ));
	//}
}
