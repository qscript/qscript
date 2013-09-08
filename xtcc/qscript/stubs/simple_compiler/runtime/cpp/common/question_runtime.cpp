#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
//#include <Wt/WString>
#include "question.h"
#include "named_range.h"
//#include "qscript_readline.h"
#include "user_navigation.h"
#include "utils.h"

using namespace std;
//extern vector<int32_t> data;
extern UserNavigation user_navigation;

//void Print_DisplayDataUnitVector (WINDOW * stub_list_window,
//		vector<display_data::DisplayDataUnit> & disp_vec,
//		int &xPos, int &yPos, int maxWinX);

	//! this is only called in the runtime environment
RangeQuestion::RangeQuestion(
	DataType this_stmt_type, int32_t line_number
	, string l_name, vector<TextExpression*> text_expr_vec, QuestionType l_q_type, int32_t l_no_mpn
	, DataType l_dt , XtccSet& l_r_data
	, QuestionAttributes  l_question_attributes
	, bool l_isStartOfBlock
	)
	: AbstractRuntimeQuestion(this_stmt_type, line_number, l_name, text_expr_vec
			   , l_q_type, l_no_mpn, l_dt, l_question_attributes
			   , l_isStartOfBlock)
	, r_data(new XtccSet(l_r_data)), displayData_()
{
	maxCode_ = r_data->GetMax();
}


#if 0
AbstractRuntimeQuestion::AbstractRuntimeQuestion(
	DataType l_type, int32_t l_no, string l_name, string l_text
	, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
	, QuestionAttributes  l_question_attributes
	)
	: //AbstractStatement(l_type, l_no), questionName_(l_name) ,
	  questionText_(l_text), q_type(l_q_type)
	, no_mpn(l_no_mpn), dt(l_dt), input_data()
	, for_bounds_stack(0), loop_index_values(0)
	, isAnswered_(false), isModified_(false)
	//, enclosingCompoundStatement_(0), activeVarInfo_(0)
	, dummyArrayQuestion_(0), currentResponse_()
	, question_attributes(l_question_attributes)
	  , maxCode_(0)
{
	//if(enclosingCompoundStatement_ == 0){
	//	print_err(compiler_internal_error, " no enclosing CompoundStatement scope for question "
	//		, qscript_parser::line_no, __LINE__, __FILE__  );
	//}
}
#endif /* 0 */

	//! this is only called from the runtime environment
RangeQuestion::RangeQuestion(
	DataType this_stmt_type, int32_t line_number
	, string l_name, vector<TextExpression*> text_expr_vec, QuestionType l_q_type
	, int32_t l_no_mpn, DataType l_dt,	XtccSet& l_r_data
	, const vector<int32_t> & l_loop_index_values
	, DummyArrayQuestion * l_dummy_array
	, QuestionAttributes  l_question_attributes
	, bool l_isStartOfBlock
	):
	AbstractRuntimeQuestion(this_stmt_type, line_number, l_name, text_expr_vec,
		l_q_type, l_no_mpn, l_dt, l_loop_index_values, l_dummy_array
		, l_question_attributes, l_isStartOfBlock
		)
	, r_data(new XtccSet(l_r_data)), displayData_()
{
	maxCode_ = r_data->GetMax();
}




// this is only called from the runtime
AbstractRuntimeQuestion::AbstractRuntimeQuestion(
	DataType l_type, int32_t l_no, string l_name
	//, string l_text
	, vector<TextExpression*> text_expr_vec
	, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
	, const vector<int32_t>& l_loop_index_values
	, DummyArrayQuestion * l_dummy_array
	, QuestionAttributes  l_question_attributes
	, bool l_isStartOfBlock
	)
	: //AbstractStatement(l_type, l_no),
	  questionName_(l_name)
	, textExprVec_(text_expr_vec), q_type(l_q_type)
	, no_mpn(l_no_mpn), dt(l_dt), input_data()
	, for_bounds_stack(0)
	, loop_index_values(l_loop_index_values)
	, isAnswered_(false), isModified_(false)
	//, enclosingCompoundStatement_(0) // this is only used in the compile time environment
	//, activeVarInfo_(0)
	, dummyArrayQuestion_(l_dummy_array), currentResponse_()
	, question_attributes(l_question_attributes)
	, mutexCodeList_()
	, maxCode_(0)
	, isStartOfBlock_(l_isStartOfBlock)
	, questionNoIndex_(0)
	//, baseQuestionNoIndexForArray_ (1)
{
	//for(int32_t i = 0; i < l_loop_index_values.size(); ++i){
	//	cout << "l_loop_index_values " << i << ":" << l_loop_index_values[i] << endl;
	//}
	cout << __PRETTY_FUNCTION__ << endl
		<< ", questionName_: " << questionName_
		<< ", questionNoIndex_: " << questionNoIndex_
		<< ", dummyArrayQuestion_->questionNoIndex_: " << dummyArrayQuestion_->questionNoIndex_
		<< ", This code Has to be revisited - probably wont work for 2 level nested loops - needs to be fixed"
		<< ", FIXME"
		<< endl;
	stringstream s;
	s << questionName_;
	int temp = 0;
	for (int i=0; i<loop_index_values.size(); ++i) {
		s << "$" << loop_index_values[i];
		//baseQuestionNoIndexForArray_ *= 100;
		temp += temp +
			loop_index_values[i]
			;
		temp *= dummyArrayQuestion_->array_bounds[i];
	}

	questionNoIndex_ = dummyArrayQuestion_->questionNoIndex_ + temp;
	cout << "questionNoIndex_: " << questionNoIndex_ << endl;
	questionDiskName_ = s.str();
	cout << "questionDiskName_: " << questionDiskName_  << endl;
	cout << "EXIT : " << __PRETTY_FUNCTION__ << endl;
}


//! only called in the runtime environment
NamedStubQuestion::NamedStubQuestion(
	DataType this_stmt_type, int32_t line_number
	, string l_name, vector<TextExpression*> text_expr_vec
	, QuestionType l_q_type, int32_t l_no_mpn
	// , DataType l_dt , vector<stub_pair>* l_stub_ptr
	, DataType l_dt, named_range * l_nr_ptr
	, const vector<int32_t> & l_loop_index_values
	, DummyArrayQuestion * l_dummy_array
	, QuestionAttributes  l_question_attributes
	, bool l_isStartOfBlock
	):
	AbstractRuntimeQuestion(this_stmt_type, line_number, l_name, text_expr_vec,
		l_q_type, l_no_mpn, l_dt, l_loop_index_values, l_dummy_array, l_question_attributes, l_isStartOfBlock
		)
	, named_list()
	, nr_ptr(l_nr_ptr), stub_ptr(0), displayData_(), currentPage_(0)
	, totPages_ (0), pageIndices_ (), stubStartYIndex_ (0)

{
#if 0
	vector <stub_pair> & v= *stub_ptr;
	for (int i=0; i<v.size(); ++i) {
		if (maxCode_ < v[i].code) {
			maxCode_ = v[i].code;
		}
	}
#endif /* 0 */
	for(int i=0; i<nr_ptr->stubs.size(); ++i) {
		if (nr_ptr->stubs[i].is_mutex) {
			mutexCodeList_.add_indiv(nr_ptr->stubs[i].code);
		}
		if (maxCode_ < nr_ptr->stubs[i].code) {
			maxCode_ = nr_ptr->stubs[i].code;
		}
	}
}


#if 0
user_response::UserResponseType AbstractRuntimeQuestion::GetDataFromUser(WINDOW * question_window, WINDOW * stub_list_window, WINDOW * data_entry_window)
{
	// cout << __PRETTY_FUNCTION__ << ", " << __LINE__ << ", " << __FILE__ << endl;
	string err_mesg, re_arranged_buffer;
	int32_t pos_1st_invalid_data;
	if (data_entry_window == 0) {
		bool invalid_code = false;
		string prompt = "Enter Data:";
		vector <int> data;
		do {
ask_again:
			user_response::UserResponseType user_resp = read_data(prompt.c_str(), &data);
			string err_mesg;
			bool valid_response = AbstractRuntimeQuestion::VerifyResponse(user_resp, user_navigation, err_mesg);
			if (!valid_response) {
				goto ask_again;
			}
			// NxD: 16-Feb-2011
			// handle User Data response here - blank as well as valid data
			if (user_resp == user_response::UserClearedData) {
				input_data.erase(input_data.begin(), input_data.end());
				isAnswered_ = false;
				goto ask_again;
			}
			invalid_code = VerifyData(err_mesg, re_arranged_buffer, pos_1st_invalid_data, &data);
			prompt = err_mesg;

			if(invalid_code == false){
				input_data.erase(input_data.begin(), input_data.end());
				for(uint32_t i = 0; i < data.size(); ++i){
					input_data.insert(data[i]);
					//cout 	<< "storing: " << data[i]
					//	<< " into input_data" << endl;
				}
				isAnswered_ = true;
			}
		} while (invalid_code == true);
		stringstream mesg;
		mesg << "is it necessary to clear data here - we are doing it at top of read_data";
		LOG_MAINTAINER_MESSAGE(mesg.str());
		data.clear();
		return user_response::UserEnteredData;
	} else {
		bool invalid_code = false;
		stringstream current_data_str;
		for (set<int32_t>::iterator inp_data_iter = input_data.begin();
				inp_data_iter != input_data.end(); ++inp_data_iter) {
			current_data_str << *inp_data_iter << " ";
		}
		re_arranged_buffer = current_data_str.str();
		pos_1st_invalid_data = re_arranged_buffer.length() - 1;
		vector <int> data;
		do {
label_ask_again:
			user_response::UserResponseType user_resp
				= read_data_from_window(
						question_window, stub_list_window,
						data_entry_window, err_mesg.c_str()
					      //, (!invalid_code), re_arranged_buffer
					      , false, re_arranged_buffer
					      , pos_1st_invalid_data, this, &data);
			// if (user_resp == user_response::UserEnteredNavigation) {
			// 	return user_resp;
			// }
			string err_mesg;
			bool valid_input = AbstractRuntimeQuestion::VerifyResponse(user_resp, user_navigation, err_mesg);
			// nxd: 17-feb-2013 23:51 - add the cases below to VerifyResponse
			// then delete them from here and take a decision on:
			// 	if valid_input == true else false
			if (isAnswered_ == false && user_navigation == NAVIGATE_PREVIOUS
					&& user_resp == user_response::UserEnteredNavigation) {
				// allow this behaviour - they can go back to the
				// previous question without answering anything -
				// no harm done
				return user_resp;
			} else if (isAnswered_ == false && user_navigation == NAVIGATE_NEXT
					&& user_resp == user_response::UserEnteredNavigation
					&& question_attributes.isAllowBlank() == false) {
				err_mesg = "cannot navigate to next question unless this is answered";
				mvwprintw(data_entry_window, 3, 1, err_mesg.c_str());
				wmove(data_entry_window, 1, 1);
				goto label_ask_again;
			}
			if (!valid_input) {
				goto label_ask_again;
			}

			invalid_code = VerifyData(err_mesg, re_arranged_buffer, pos_1st_invalid_data, &data);


			if (invalid_code == false) {
				input_data.erase(input_data.begin(), input_data.end());
				for(uint32_t i = 0; i < data.size(); ++i){
					input_data.insert(data[i]);
					//cout << "storing: " << data[i]
					//	<< " into input_data" << endl;
				}
				isAnswered_ = true;
			}
		} while (invalid_code == true);
		stringstream mesg;
		mesg << "is it necessary to clear data here - we are doing it at top of read_data";
		LOG_MAINTAINER_MESSAGE(mesg.str());
		data.clear();
		//wclear (error_msg_window);
		return user_response::UserEnteredData;
	}
}
#endif /* 0 */


bool AbstractRuntimeQuestion::VerifyResponse(user_response::UserResponseType user_resp, UserNavigation user_navigation, string & err_mesg)
{
	stringstream mesg; mesg << "user_resp: " << user_resp;
	// cout << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
	// 	<< mesg.str() << endl;
	if (user_resp == user_response::UserClearedData && question_attributes.isAllowBlank()) {
		// valid response if blanks are allowed but dont do isAnswered_ = true
		// because otherwise when visiting the questionnaire it will skip this
		// question and data entry will have an off by 1 error everytime they
		// are reviewing this question - since blank is a valid answer
		return true;
	} else if (user_resp == user_response::UserEnteredData) {
		return true;
	} 	// clause moved here from GetUserInput - but seems redundant
		//	as the next clause is already handling this
		else if (isAnswered_ == false && user_navigation == NAVIGATE_PREVIOUS
				&& user_resp == user_response::UserEnteredNavigation) {
		return true;
	} else if (user_resp == user_response::UserEnteredNavigation
			&& user_navigation == NAVIGATE_PREVIOUS) {
		return true;
	} else if (user_resp == user_response::UserEnteredNavigation
			&& user_navigation == NAVIGATE_NEXT
			&& question_attributes.isAllowBlank() == false
			&& isAnswered_ == true) {
		return true;
	} else if (user_resp == user_response::UserEnteredNavigation
			&& user_navigation == NAVIGATE_NEXT
			&& question_attributes.isAllowBlank() == true) {
		return true;
	} else if (user_resp == user_response::UserSavedData && user_navigation == SAVE_DATA) {
		return true;
	} else {
		if (isAnswered_ == false && user_navigation == NAVIGATE_NEXT
				&& user_resp == user_response::UserEnteredNavigation
				&& question_attributes.isAllowBlank() == false) {
			// nxd: 18-feb-2013 - note this error message should be passed
			// back as a parameter  - so it can be reported
			err_mesg = "cannot navigate to next question unless this is answered";
		} else {
			err_mesg = "failed VerifyResponse for unknown reason";
		}
		return false;
	}
}


// re_arranged_buffer will contain the data like this: valid_data invalid_data
bool AbstractRuntimeQuestion::VerifyData(
	string & err_mesg, string & re_arranged_buffer
	, int32_t & pos_1st_invalid_data, vector<int32_t>* data_ptr)
{
	vector <int> & data = * data_ptr;
	bool invalid_code=false, has_invalid_data_flag = false;
	stringstream valid_data, invalid_data;
	for(uint32_t i = 0; i < data.size(); ++i){
		//cout << "Testing data exists: " << data[i] << endl;
		invalid_code = !IsValid(data[i]);
		if(invalid_code == true){
			if(!has_invalid_data_flag)
				has_invalid_data_flag = true;
			invalid_data << data[i] << " ";
		} else {
			valid_data << data[i] << " ";
		}
	}

	if (data.size() == 0 && question_attributes.isAllowBlank() == false) {
		err_mesg = " question cannot be blank";
		invalid_code = true;
		goto end;
	}

	if(has_invalid_data_flag) {
		err_mesg = "Input contained some invalid data.. " + invalid_data.str() +  " Re-enter Data\n";
		pos_1st_invalid_data = valid_data.str().length(); // it already has a space appended to it
		re_arranged_buffer = valid_data.str() + invalid_data.str();
		invalid_code = true;
		goto end;
	}
	if(q_type == spn && data.size()>1) {
		err_mesg = "Single coded Question - please enter only 1 code:";
		invalid_code = true;
		data.clear();
	} else if (q_type == mpn) {
		//cout << "reached here: " << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
		if (data.size() > no_mpn){
			err_mesg = "Multi coded Question, no values exceed max allowed:  ";
			invalid_code = true;
			cerr << "should I clear this? - the DE operator has done hard work entering this data"
				<< __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
			data.clear();
		}
		int count_mutex_data = 0;
		for(int i=0; i<data.size(); ++i) {
			if (mutexCodeList_.exists(data[i])){
				// cout << "mutexCodeList_ contains: " << data[i];
				++count_mutex_data;
			}
		}
		if (data.size()>1 && count_mutex_data >= 1) {
			err_mesg = "Mutex code entered with other codes";
			invalid_code = true;
			cerr << "should I clear this? - the DE operator has done hard work entering this data"
				<< __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
			data.clear();
		}
	} else {
		invalid_code = false;
	}
end:
	// cout << __PRETTY_FUNCTION__ << " returned invalid_code: |" << invalid_code
	// 	<< "|" << endl;
	return invalid_code;
}


//void AbstractRuntimeQuestion::Generate_ComputeFlatFileMap(StatementCompiledCode & code)
//{ }

//void RangeQuestion::GenerateCode(StatementCompiledCode & code )
//{ }

//void NamedStubQuestion::GenerateCode(StatementCompiledCode &code)
//{ }

//void NamedStubQuestion::GenerateCodeSingleQuestion(StatementCompiledCode & code, bool array_mode)
//{ }

//void RangeQuestion::GenerateCodeSingleQuestion(StatementCompiledCode & code, bool array_mode)
//{ }

void NamedStubQuestion::WriteDataToDisk(ofstream& data_file)
{
	if(loop_index_values.size()>0){

		data_file << questionName_;
		for(int32_t i = 0; i< loop_index_values.size(); ++i){
			data_file << "$" << loop_index_values[i];
		}
	} else  {
		data_file << questionName_;
	}
	data_file << ":";
	if (isAnswered_) {
		for( set<int32_t>::iterator iter = input_data.begin();
				iter != input_data.end(); ++iter){
			data_file << *iter << " ";
		}
	}
	data_file << endl;
	stringstream mesg;
	//mesg << "I think this is the wrong place to clear - should be done at the end of main while loop in generated code, when user loads a new serial number";
	//LOG_MAINTAINER_MESSAGE(mesg.str());
	//input_data.clear();
}

void DummyArrayQuestion::WriteDataToDisk(ofstream& data_file)
{
	data_file << questionName_ << " BOUNDS";
	for(int32_t i = 0; i < array_bounds.size(); ++i){
		data_file << " "<< array_bounds[i];
	}
	data_file << endl;
}

void RangeQuestion::WriteDataToDisk(ofstream& data_file)
{
	if(loop_index_values.size()>0){
		data_file << questionName_;
		for(int32_t i = 0; i< loop_index_values.size(); ++i){
			data_file << "$" << loop_index_values[i];
		}
	} else {
		data_file << questionName_;
	}
	data_file << ":";
	if (isAnswered_) {
		for( set<int32_t>::iterator iter = input_data.begin();
				iter != input_data.end(); ++iter){
			data_file << *iter << " ";
		}
	}
	data_file << endl;
	stringstream mesg;

	//mesg << "I think this is the wrong place to clear - should be done at the end of main while loop in generated code, when user loads a new serial number"
	//	<< " right now if the user presses 's' 2ice - we lose data" << endl;
	//LOG_MAINTAINER_MESSAGE(mesg.str());
	//input_data.clear();
}


NamedStubQuestion::NamedStubQuestion(
	DataType this_stmt_type, int32_t line_number
	, string l_name, vector<TextExpression*> text_expr_vec
	, QuestionType l_q_type, int32_t l_no_mpn
	, DataType l_dt, named_range * l_nr_ptr
	, QuestionAttributes  l_question_attributes
	, bool l_isStartOfBlock
	):
	AbstractRuntimeQuestion(this_stmt_type, line_number, l_name, text_expr_vec
			 ,l_q_type, l_no_mpn, l_dt, l_question_attributes
			 , l_isStartOfBlock)
	, named_list()
	, nr_ptr(l_nr_ptr), stub_ptr(0), displayData_(), currentPage_(0)
{
#if 0
	vector <stub_pair> & v= *stub_ptr;
	for (int i=0; i<v.size(); ++i) {
		if (maxCode_ < v[i].code) {
			maxCode_ = v[i].code;
		}
	}
#endif /* 0 */
	for(int i=0; i<nr_ptr->stubs.size(); ++i) {
		if (nr_ptr->stubs[i].is_mutex) {
			mutexCodeList_.add_indiv(nr_ptr->stubs[i].code);
		}
		if (maxCode_ < nr_ptr->stubs[i].code) {
			maxCode_ = nr_ptr->stubs[i].code;
		}
	}
}

// a question can lose integrity because of modification to a previous question

bool AbstractRuntimeQuestion::VerifyQuestionIntegrity()
{
	bool has_integrity = true;

	for (set<int32_t>::iterator inp_data_iter = input_data.begin();
			inp_data_iter != input_data.end(); ++inp_data_iter) {
		bool invalid_code = !IsValid(*inp_data_iter);
		if (invalid_code) {
			has_integrity = false;
			break;
		}
	}
	return has_integrity;
}
#if 0
Wt::WString NamedStubQuestion::PrintSelectedAnswers()
{
	//return string("hello");
	//stringstream select_answers_text;
	Wt::WString select_answers_text;
	bool first_time = true;
	for (set<int32_t>::iterator inp_data_iter = input_data.begin();
			inp_data_iter != input_data.end(); ++inp_data_iter) {
		stringstream mesg_key;
		mesg_key << nr_ptr->name << "_" << *inp_data_iter - 1;
		if (first_time) {
			//select_answers_text << nr_ptr->stubs[*inp_data_iter-1].stub_text;
			cout << "searching for : " << mesg_key.str() << endl;
			select_answers_text += Wt::WString::tr(mesg_key.str());
			first_time = false;
		} else {
			//select_answers_text << ", " << nr_ptr->stubs[*inp_data_iter-1].stub_text ;
			cout << "searching for : " << mesg_key.str() << endl;
			select_answers_text += Wt::WString(", ") +  Wt::WString::tr(mesg_key.str());
		}
	}
	//select_answers_text << nr_ptr->stubs[codeIndex_].stub_text;
	//return select_answers_text.str();
	return select_answers_text;
}


Wt::WString NamedStubQuestion::PrintSelectedAnswers(int code_index)
{
	//return string("hello");
	Wt::WString select_answers_text;
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
	return Wt::WString::tr(mesg_key.str());
}
#endif /*  0 */


//Wt::WString RangeQuestion::PrintSelectedAnswers()
string RangeQuestion::PrintSelectedAnswers()
{
	//return Wt::WString("hello");
	return string("hello");
}


//Wt::WString RangeQuestion::PrintSelectedAnswers (int code_index)
string RangeQuestion::PrintSelectedAnswers (int code_index)
{
	//return Wt::WString("hello");
	return string("hello");
}

void NamedStubQuestion::MakeDisplaySummaryDataRanges()
{
	//fprintf (qscript_stdout, "displayData_.begin == displayData_.end \n");
	vector<stub_pair> & vec= (nr_ptr->stubs);
	if (vec.size() == 0) {
		cerr << "runtime error: Impossible !!! stubs with no codes: "
			<< __LINE__ << ", " << __FILE__ << __PRETTY_FUNCTION__
			<< " question name: " << questionName_ << endl;
		exit(1);
	}
	int start_code = vec[0].code;
	int previous_code = start_code;
	int current_code = start_code;
	// so what's with start_code, previous_code and current_code ?
	// start_code -> start of interval
	// previous_code -> last code we visited in stubs
	// current_code -> the current code we are visiting in stubs
	for (int32_t i=0; i<vec.size(); ++i) {
		current_code = vec[i].code;
		//fprintf (qscript_stdout, "current_code: %d, previous_code: %d\n", current_code, previous_code);
		if (current_code - previous_code == 0) {
			// 1st iteration thru the loop
			// cant make any decision yet
		} else if (current_code - previous_code == 1) {
			// continuous range - just keep going along we are in an interval
		} else if (current_code - previous_code > 1) {
			if (start_code < previous_code) {
				displayData_.push_back(display_data::DisplayDataUnit(start_code, previous_code));
				//fprintf (qscript_stdout, "> 1 pushed back pair: %d - %d\n", start_code, previous_code);
				start_code = current_code;
				previous_code = current_code;
			} else {
				displayData_.push_back(display_data::DisplayDataUnit(start_code));
				//fprintf (qscript_stdout, "> 1 pushed back singleteon: %d\n", start_code);
				start_code = current_code;
				previous_code = current_code;
			}
		} else {
			// current_code - previous_code < 0
			if (start_code < previous_code) {
				displayData_.push_back(display_data::DisplayDataUnit(start_code, previous_code));
				//fprintf (qscript_stdout, "< 0 pushed back pair: %d - %d\n", start_code, previous_code);
				start_code = current_code;
				previous_code = current_code;
			} else if (start_code == previous_code) {
				displayData_.push_back(display_data::DisplayDataUnit(start_code));
				//fprintf (qscript_stdout, "< 0 pushed back singleteon: %d\n", start_code);
				start_code = current_code;
				previous_code = current_code;
			}
		}
		if (i > 0) {
			previous_code = current_code;
		}
		//displayData_.push_back(display_data::DisplayDataUnit(vec[i].code));
	}
	if (start_code < previous_code) {
		displayData_.push_back(display_data::DisplayDataUnit(start_code, previous_code));
		//fprintf (qscript_stdout, "pushed back pair: %d - %d\n", start_code, previous_code);
		start_code = current_code;
		previous_code = current_code;
	} else {
		displayData_.push_back(display_data::DisplayDataUnit(start_code));
		//fprintf (qscript_stdout, "pushed back singleteon: %d\n", start_code);
		start_code = current_code;
		previous_code = current_code;
	}
}


void RangeQuestion::MakeDisplaySummaryDataRanges()
{
	if (displayData_.begin() == displayData_.end()) {
		for(	set<int32_t>::iterator it = r_data->indiv.begin();
				it != r_data->indiv.end(); ++it){
			//displayData_.insert(*it);
			displayData_.push_back(display_data::DisplayDataUnit(*it));
		}
		for(int32_t i = 0; i < r_data->range.size(); ++i){
			/*
			for(int32_t j = r_data->range[i].first; j <= r_data->range[i].second
					;++j){
				displayData_.insert(j);
			}
			*/
			displayData_.push_back(display_data::DisplayDataUnit(r_data->range[i].first, r_data->range[i].second));
		}
		std::sort(displayData_.begin(), displayData_.end(), display_data::DisplayDataUnitOrder());
	}
}

#if 0
void NamedStubQuestion::ComputeVisiblePages (/*qs_ncurses::*/WINDOW * question_window
			     , /*qs_ncurses::*/WINDOW* stub_list_window
			     , /*qs_ncurses::*/WINDOW* data_entry_window
			     , WINDOW * error_msg_window)
{
	pageIndices_.clear();
	vector<stub_pair> & vec= (nr_ptr->stubs);
	int32_t maxWinX, maxWinY;
	getmaxyx(stub_list_window, maxWinY, maxWinX);
	//if (totPages_ == 0) {
		int start_page_index = 0, end_page_index = 0;
		//stubStartYIndex_ = currYpos;
		int y_pos_tracker = stubStartYIndex_;
		for (uint32_t i = 0; i < vec.size(); ++i) {
			if (vec[i].mask) {
				++ y_pos_tracker;
				if (y_pos_tracker == maxWinY - 1) {
					pageIndices_.push_back ( pair <int, int> (start_page_index, i) );
					start_page_index = i + 1;
					y_pos_tracker = stubStartYIndex_;
				}
			}
		}
		if (start_page_index < vec.size())
			pageIndices_.push_back ( pair <int, int> (start_page_index, vec.size()-1) );
		//cout << "n Pages: " << pageIndices_.size() << endl;
		//for (int i=0; i < pageIndices_.size(); ++i) {
		//	cout << pageIndices_[i].first << ", "
		//		<< pageIndices_[i].second
		//		<< endl;
		//}
	//}
}
#endif /* 0 */

bool AbstractRuntimeQuestion::check_and_store_input_data_single_question
	(string & err_mesg, string & re_arranged_buffer, int & pos_1st_invalid_data,
	 vector <int> & data)
{
	cout << "ENTER: " << __PRETTY_FUNCTION__ << endl;
	//string err_mesg, re_arranged_buffer; int pos_1st_invalid_data;
	bool r_value = false;
	bool invalid_code = VerifyData (err_mesg, re_arranged_buffer, pos_1st_invalid_data, &data);
	if (invalid_code == false) {
		input_data.erase (input_data.begin(), input_data.end());
		for (uint32_t i = 0; i < data.size(); ++i) {
			input_data.insert (data[i]);
			//cout << "storing: " << data[i]
			//	<< " into input_data" << endl;
		}
		isAnswered_ = true;
		r_value = true;
		//return true;
	} else {
		err_mesg += " Data contained some invalid codes";
		//return false;
		r_value = false;
	}
	cout << "exit: "
		<< __PRETTY_FUNCTION__
		<< "return value: (true == success) (false = FAILURE)" <<  r_value
		<< ", re_arranged_buffer:" << re_arranged_buffer
		<< ", pos_1st_invalid_data: " << pos_1st_invalid_data
		<< ", err_mesg: " << err_mesg
		<< endl;
	cout << "data: " ;
	for (int i=0; i<data.size(); ++i) {
		cout << " " << data[i];
	}
	cout << endl;
	return r_value;
}


/*
int32_t AbstractRuntimeQuestion::GetMaxCode()
{
	if (maxCode_ == 0) {
		stringstream err_msg;
		err_msg << " maxCode_ == 0 should have been set: questionName_: "
			<< questionName_ << endl;
		print_err(compiler_internal_error, err_msg.str()
				, 0, __LINE__, __FILE__);
		exit(1);
	}
	return maxCode_;
}
*/


VideoQuestion::VideoQuestion(
		DataType this_stmt_type, int32_t line_number, string l_name
		, vector<TextExpression*> text_expr_vec
		, QuestionType l_q_type
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		, const string& path_to_media)
	: AbstractRuntimeQuestion(this_stmt_type, line_number, l_name, text_expr_vec
			 , l_q_type, 1, INT32_TYPE
			 , l_question_attributes
			 , l_isStartOfBlock),
		file_path (path_to_media)
{

}


void VideoQuestion::WriteDataToDisk(ofstream& data_file)
{
}

string VideoQuestion::PrintSelectedAnswers()
{
	//return Wt::WString("hello");
	return string("hello");
}


//Wt::WString RangeQuestion::PrintSelectedAnswers (int code_index)
string VideoQuestion::PrintSelectedAnswers (int code_index)
{
	//return Wt::WString("hello");
	return string("hello");
}

