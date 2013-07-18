/*
 * =====================================================================================
 *
 *       Filename:  question_wt_runtime.cpp
 *
 *    Description:  wx Widgets GUI display for qscript runtime
 *
 *        Version:  1.0
 *        Created:  27-may-2013
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Neil Xavier D'Souza
 *        Company:
 *
 * =====================================================================================
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <locale.h>
#include <libintl.h>
#include <map>
#include <vector>
#include <dirent.h>
#include <signal.h>

#include "question_gtk2_runtime.h"
#include "question.h"
#include "named_range.h"
#include "question_disk_data.h"
#include "qscript_data.hpp"
#include "qscript_lib.h"
#include "AbstractQuestionnaire.h"
#include "question_wt_runtime.h"

extern string jno;

using std::vector;
using std::string;
vector <string> vec_language;

#if 0

static struct Session *sessions;
using namespace Wt;

class QuestionnaireApplication: public WApplication
{
public:
	QuestionnaireApplication(const WEnvironment &env);
private:
	WText * wt_debug_;
	WText * wt_questionText_;
	WLineEdit * le_data_;
	WText * wt_lastQuestionVisited_;
	WGroupBox * wt_cb_rb_container_;
	WButtonGroup * wt_rb_container_;
	vector<WRadioButton*> vec_rb;
	vector<WCheckBox*> vec_cb;
	std::map<int, int> map_cb_code_index;
	std::vector<WText *> languageSelects_;

	WContainerWidget viewPort_;
	//WWidget * currentForm_;
		WContainerWidget * currentForm_;
	WContainerWidget * formContainer_;
	int ser_no;
		WContainerWidget * serialPage_;
		bool flagSerialPageRemoved_;
		Session * this_users_session;
		string sess_id ;

	void display();
	void DoQuestionnaire() ;
	//void setCentralWidget(WWidget * new_question_form);
	void setCentralWidget(WContainerWidget * new_question_form);
	void changeLanguage();
	void setLanguage(const std::string lang);
	void ConstructQuestionForm(
		AbstractQuestion *q, Session * this_users_session);
	void ValidateSerialNo();
 	void ConstructThankYouPage();
 	const char * software_info();
		virtual ~QuestionnaireApplication();
};

QuestionnaireApplication::~QuestionnaireApplication()
{
	delete this_users_session; 	this_users_session=0;
	delete serialPage_; 		serialPage_ = 0;
	if (currentForm_) {
		delete currentForm_; 	currentForm_ = 0;
	}
	cout << __PRETTY_FUNCTION__ << endl;
}

void QuestionnaireApplication::ValidateSerialNo()
{
	int l_ser_no = -1;
	if (le_data_ ) {
		WString serno_text = le_data_->text();
		string narrow_text = serno_text.narrow();
		if (narrow_text.length() == 0 || narrow_text.length()>7) {
			le_data_->setText("You have entered a very long serial number");
		} else {
			l_ser_no = strtol (narrow_text.c_str(), 0, 10);
			if (l_ser_no > 0) {
				ser_no = l_ser_no;
				//this_users_session->theQuestionnaire_->ser_no = l_ser_no;
				int exists = check_if_reg_file_exists(jno, ser_no);
				cout << "checking if serial no : " << ser_no
					<< ", jno: " << jno << " exists: " << exists << endl;

				if(exists == 1){
 					map <string, question_disk_data*>  qdd_map;
					load_data(jno, ser_no, &qdd_map);
					//merge_disk_data_into_questions(qscript_stdout, last_question_answered, last_question_visited);
					merge_disk_data_into_questions2(qscript_stdout,
							this_users_session->theQuestionnaire_->last_question_answered,
							this_users_session->theQuestionnaire_->last_question_visited,
							this_users_session->theQuestionnaire_->question_list,
							&qdd_map);
					for (map<string, question_disk_data*>:: iterator it
							= qdd_map.begin();
							it != qdd_map.end();
							++it) {
						delete it->second;
					}
				}
				DoQuestionnaire();
			} else {
				le_data_->setText("You have entered a  negative number");
			}
		}
	}
}

bool verify_web_data (std::string p_question_data,
		UserNavigation p_user_navigation,
		user_response::UserResponseType p_the_user_response,
		std::vector<int> * data_ptr);


void QuestionnaireApplication::DoQuestionnaire()
{
	//if (!wt_questionText_) {
	//	wt_questionText_ = new WText(root());
	//}
	cout << "Data for ser_no: " << ser_no;
	for(int32_t i = 0; i < this_users_session->theQuestionnaire_->question_list.size(); ++i)
	{
		cout << this_users_session->theQuestionnaire_->question_list[i]->questionName_;
		for( set<int32_t>::iterator iter = this_users_session->theQuestionnaire_->question_list[i]->input_data.begin();
				iter != this_users_session->theQuestionnaire_->question_list[i]->input_data.end(); ++iter){
			cout << " " << *iter;
		}
		cout << "\n";
	}
	static int counter = 0;
	stringstream s;
	s << "reached DoQuestionnaire: " << counter++;
	wt_debug_->setText(s.str());
	UserNavigation qnre_navigation_mode = NAVIGATE_NEXT;
	string display_text = string("Session Id:") + sess_id;
	wt_questionText_->setText(display_text);
	// put this code later
	string err_mesg, re_arranged_buffer;
	int32_t pos_1st_invalid_data;
	s << "last_question_served: " << this_users_session->last_question_served;
	wt_debug_->setText(s.str());
	if (this_users_session->last_question_served)
	{
		if (NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion *>(this_users_session->last_question_served)) {
			AbstractQuestion * last_question_served = this_users_session->last_question_served;
			vector<int32_t> data;
			bool isAnswered = false;
 			cout << "returned back data from question: " << nq->questionName_ << endl;
			if (last_question_served->no_mpn == 1) {
				if ( wt_rb_container_->selectedButtonIndex() != -1) {
					isAnswered = true;
					int code = wt_rb_container_->checkedId();
					cout << "no_mpn == 1, code: " << code << endl;
					data.push_back(code);
				} else {
					isAnswered = false;
				}
			} else {
 				cout << " vec_cb.size(): " << vec_cb.size() << "no_mpn > 1" << endl;
				for (int i = 0; i < vec_cb.size(); ++i) {
					if (vec_cb[i]->checkState() == Wt::Checked) {
						int code = map_cb_code_index[i];
						data.push_back(code);
						cout << "vec_cb[" << i << "] is checked,   code: " << code << endl;
						isAnswered = true;
					}
				}
			}
			if (isAnswered) {
				bool invalid_code = last_question_served->VerifyData(err_mesg, re_arranged_buffer, pos_1st_invalid_data,
					&data);
				if (invalid_code == false)
				{
					//last_question_served->input_data.erase
					//	(last_question_served->input_data.begin(),
					//	last_question_served->input_data.end());
				last_question_served->input_data.clear();
					for(uint32_t i = 0; i < data.size(); ++i)
					{
						last_question_served->input_data.insert(data[i]);
						cout << "storing: " << data[i]
							<< " into input_data" << endl;
					}
					last_question_served->isAnswered_ = true;
					data.clear();
				}
			}
			// do something with isAnswered_ == false here and resend the
			// qnre to the respondent
		} else {

			string last_question_visited_str = wt_lastQuestionVisited_->text().narrow();
			string current_question_response = le_data_->text().narrow();
			AbstractQuestion * last_question_served = this_users_session->last_question_served;
			if (last_question_visited_str != "" && current_question_response != "" && last_question_served->no_mpn==1)
			{
				UserNavigation user_nav=NOT_SET;
				user_response::UserResponseType user_resp=user_response::NotSet;
				vector<int32_t> data;
				bool parse_success = verify_web_data (current_question_response, user_nav, user_resp, &data);
				if (parse_success)
				{
					cout << "successfully parsed data = ";
					for (int i=0; i<data.size(); ++i)
					{
						cout << data[i] << ", ";
					}
					cout << endl;
				}
				// the call below will be required at some later stage
				//bool valid_input = AbstractQuestion::VerifyResponse(user_resp);
				// right now we go along with the happy path
				bool invalid_code = last_question_served->VerifyData(err_mesg, re_arranged_buffer, pos_1st_invalid_data,
					&data);
				if (invalid_code == false)
				{
					last_question_served->input_data.erase
						(last_question_served->input_data.begin(),
						last_question_served->input_data.end());
					for(uint32_t i = 0; i < data.size(); ++i)
					{
						last_question_served->input_data.insert(data[i]);
						//cout << "storing: " << data[i]
						//	<< " into input_data" << endl;
					}
					last_question_served->isAnswered_ = true;
					data.clear();
				}
				else {
					ConstructQuestionForm(last_question_served, this_users_session);
					return;
				}
			}
			else if (last_question_visited_str != "" && current_question_response != "" && last_question_served->no_mpn > 1)
			{
				string utf8_response = le_data_->text().toUTF8();
				if (utf8_response != "")
				{
					stringstream file_name_str;
					file_name_str << last_question_served->questionName_ << "."
						<< jno << "_" << ser_no << ".dat";

					fstream open_end_resp(file_name_str.str().c_str(), ios_base::out|ios_base::ate);
					open_end_resp << utf8_response << endl;
					last_question_served->input_data.insert(96);
					last_question_served->isAnswered_ = true;
				}
				else
				{
					ConstructQuestionForm(last_question_served, this_users_session);
					return;
				}
			}
		}
	}
	{
 		TheQuestionnaire * qnre = this_users_session->theQuestionnaire_;
		qnre->write_data_to_disk(qnre->question_list, qnre->jno, qnre->ser_no);
	}
	AbstractQuestion * q =
		this_users_session->theQuestionnaire_->eval2(
		qnre_navigation_mode, this_users_session->last_question_served, 0 /*jump to index dummy*/);
	this_users_session->last_question_served = q;
if (q) {
	ConstructQuestionForm(q, this_users_session);
} else {
 	TheQuestionnaire * qnre = this_users_session->theQuestionnaire_;
	qnre->write_data_to_disk(qnre->question_list, qnre->jno, qnre->ser_no);
 	ConstructThankYouPage();
}
}

void QuestionnaireApplication::ConstructThankYouPage()
{
	WContainerWidget * new_form = new WContainerWidget();
	WText * txt = new WText(WString::tr("thank_you"), new_form);
 	WText * survey_code = new WText(WString::tr("vege_source_code"), new_form);
	setCentralWidget(new_form);
	cout << "ConstructThankYouPage\n";
}

void QuestionnaireApplication::ConstructQuestionForm(
	AbstractQuestion *q, Session * this_users_session)
{

	WContainerWidget * new_form = new WContainerWidget();
	vec_rb.clear();			 // memory leak introduced here? no it seems
	vec_cb.clear();			 // memory leak introduced here? no it seems
	map_cb_code_index.clear();

	wt_questionText_ = new WText();
	//wt_questionText_->setText(q->textExprVec_[0]->text_);
	//stringstream question_text;
	stringstream part_mesg_id;
	WString question_text;
	part_mesg_id << q->questionName_;
	for (int i=0; i<q->loop_index_values.size(); ++i)
	{
		part_mesg_id << "_" << q->loop_index_values[i];
	}
	WText * wt_questionNo_ = new WText(part_mesg_id.str().c_str(), new_form);
	for (int i=0; i<q->textExprVec_.size(); ++i)
	{
		question_text += "<p>";
		if (q->textExprVec_[i]->teType_ == TextExpression::simple_text_type)
		{
			stringstream mesg_id;
			mesg_id << part_mesg_id.str() << "_" << i;
			question_text += WString::tr(mesg_id.str().c_str());
		}
		else if (q->textExprVec_[i]->teType_ == TextExpression::named_attribute_type)
		{
			stringstream named_attribute_key;
			named_attribute_key << q->textExprVec_[i]->naPtr_->name;
			named_attribute_key << "_" << q->textExprVec_[i]->naIndex_;
			question_text += WString::tr(named_attribute_key.str().c_str());
		}
		else if (q->textExprVec_[i]->teType_ == TextExpression::question_type)
		{
			if (q->textExprVec_[i]->codeIndex_ != -1) {
				question_text += q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers(q->textExprVec_[i]->codeIndex_);
			} else {
				question_text += q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers();
			}
		}
		question_text += "</p>";
	}
	wt_questionText_->setText(question_text);

	new_form->addWidget(wt_questionText_);
	if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q))
	{
		new_form->addWidget(wt_cb_rb_container_ = new WGroupBox());
		if (q->no_mpn==1)
		{
			wt_rb_container_ = new WButtonGroup(wt_cb_rb_container_);
		}
		vector<stub_pair> & vec= (nq->nr_ptr->stubs);
		for (int i=0; i<vec.size(); ++i)
		{
			stringstream named_range_key;
			named_range_key << nq->nr_ptr->name << "_" << i;
			if (q->no_mpn==1 && vec[i].mask)
			{
				//WRadioButton * wt_rb = new WRadioButton( vec[i].stub_text, wt_cb_rb_container_);
				WRadioButton * wt_rb = new WRadioButton(WString::tr(named_range_key.str().c_str()), wt_cb_rb_container_);
				wt_rb_container_->addButton(wt_rb, vec[i].code);
				new WBreak(wt_cb_rb_container_);
				vec_rb.push_back(wt_rb);
			}
			else if (q->no_mpn>1 && vec[i].mask)
			{
				//WCheckBox * wt_cb = new WCheckBox ( vec[i].stub_text, wt_cb_rb_container_);
				WCheckBox * wt_cb = new WCheckBox (WString::tr(named_range_key.str().c_str()), wt_cb_rb_container_);
				vec_cb.push_back(wt_cb);
				cout << " adding code: " << vec[i].code << " to map_cb_code_index" ;
				map_cb_code_index[vec_cb.size()-1] = vec[i].code;
			}
		}
		new_form->addWidget(wt_cb_rb_container_);
	}
	else
	{
		le_data_ = new WLineEdit();
		new_form->addWidget(le_data_);
	}

	wt_lastQuestionVisited_ = new WText();
	if (this_users_session->last_question_answered)
		wt_lastQuestionVisited_->setText(q->questionName_);
	new_form->addWidget(wt_lastQuestionVisited_);

							 // create a button
	WPushButton *b = new WPushButton("Next");
	b->clicked().connect(this, &QuestionnaireApplication::DoQuestionnaire);
	new_form->addWidget(b);

	setCentralWidget(new_form);
}


void QuestionnaireApplication::changeLanguage()
{
	WText *t = (WText *)sender();
	setLanguage(narrow(t->text().value()));
}


extern string jno;
QuestionnaireApplication::QuestionnaireApplication(const WEnvironment &env)
	: WApplication(env), wt_questionText_(0), currentForm_(0), flagSerialPageRemoved_(false)
{
	messageResourceBundle().use(WApplication::appRoot() + jno);
	serialPage_ = new WContainerWidget(0);
	setTitle("QuestionnaireApplication");
	/*
	WPushButton *b = new WPushButton("Click to start survey", root()); // create a button
	b->setMargin(5, Left);                                 // add 5 pixels margin

	root()->addWidget(new WBreak());                       // insert a line break

	wt_questionText_ = new WText(root());                         // empty text

	b->clicked().connect(this, &QuestionnaireApplication::DoQuestionnaire);
	*/

	WCssDecorationStyle langStyle;
	langStyle.font().setSize(WFont::Smaller);
	langStyle.setCursor(PointingHandCursor);
	langStyle.setForegroundColor(blue);
	langStyle.setTextDecoration(WCssDecorationStyle::Underline);
	this->styleSheet().addRule(".lang", langStyle);

	langStyle.setCursor(ArrowCursor);
	langStyle.font().setWeight(WFont::Bold);
	this->styleSheet().addRule(".langcurrent", langStyle);

	langStyle.setForegroundColor(WColor(100, 0, 200, 100));
	langStyle.setCursor(IBeamCursor);
	langStyle.font().setWeight(WFont::Bold);
	langStyle.font().setSize(WFont::XLarge);
	this->styleSheet().addRule(".langtitle", langStyle);

	// warning the statement below modifies the global variable
	//load_languages_available(vec_language);
	WContainerWidget *langLayout = new WContainerWidget();
	langLayout->setContentAlignment(AlignRight);

	WText * lang_title = new WText(WString::tr("language"), langLayout);
	lang_title->setStyleClass(L"langtitle");


	for (int i = 0; i < vec_language.size(); ++i) {
		WText *t = new WText(widen(vec_language[i]), langLayout);
		t->setMargin(5);
		t->clicked().connect(this, &QuestionnaireApplication::changeLanguage);
		languageSelects_.push_back(t);
	}

	/*
	* Start with the reported locale, if available
	*/
	//setLanguage(wApp->locale());
	setLanguage("hn");

	WText * txt_software_info = new WText(WString::tr("qscript_info"), serialPage_);
	WPushButton *b = new WPushButton("Click to start survey", serialPage_); // create a button
	b->setMargin(5, Left);                                 // add 5 pixels margin
	serialPage_->addWidget(new WBreak());                       // insert a line break
	//b->clicked().connect(this, &QuestionnaireApplication::DoQuestionnaire);
	b->clicked().connect(this, &QuestionnaireApplication::ValidateSerialNo);
	wt_questionText_ = new WText(serialPage_);
	wt_questionText_->setText("Serial No: ");
	wt_lastQuestionVisited_ = new WText(serialPage_);
	le_data_ = new WLineEdit(serialPage_);

	wt_debug_ = new WText(serialPage_);
	formContainer_ = new WContainerWidget(root());
	formContainer_->addWidget(serialPage_);
	formContainer_->addWidget(langLayout);
	string sess_id = sessionId();
	this_users_session = new Session();
	strcpy(this_users_session->sid, sess_id.c_str());
	wt_sessions.push_back(this_users_session);
}

int main(int argc, char ** argv)
{
	//process_options(argc, argv);
	cout << __PRETTY_FUNCTION__ << ", " << __FILE__
		<< ", "
		<< __LINE__ << endl;
	cout << "searching for -m option" << endl;
       for (int i=0; i<argc; ++i) { if (string(argv[i]) == "-m") { write_messages_flag = 1; break;} }
	if (write_messages_flag) {
		TheQuestionnaire theQuestionnaire("dummy");
		exit(0);
	}

	load_languages_available(vec_language);
	bool using_ncurses = true;
	qscript_stdout = fopen(qscript_stdout_fname.c_str(), "w");
	SetupSignalHandler();

	//return WRun (argc, argv, &createApplication);
	{
	try
	{
		// use argv[0] as the application name to match a suitable entry
		// in the Wt configuration file, and use the default configuration
		// file (which defaults to /etc/wt/wt_config.xml unless the environment
		// variable WT_CONFIG_XML is set)
		// WServer server(argv[0]);

		// WTHTTP_CONFIGURATION is e.g. "/etc/wt/wthttpd"
		server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);

		// add a single entry point, at the default location (as determined
		// by the server configuration's deploy-path)
		server.addEntryPoint(Wt::Application, createApplication);
		if (server.start()) {
			std::string port_number_fname = jno + string("_port_number");
			std::fstream port_number(port_number_fname.c_str(), ios_base::out);
			port_number << server.httpPort();
			port_number << ' ' << getpid() << std::endl;
			std::cout << server.httpPort() << std::endl;
			port_number.flush();
			int sig = WServer::waitForShutdown(argv[0]);
			std::cerr << "Shutdown (signal = " << sig << ")" << std::endl;
			server.stop();
			if (sig == SIGHUP)
			WServer::restart(argc, argv, environ);
		}
	} catch (WServer::Exception& e) {
	    std::cerr << e.what() << std::endl;
	    return 1;
	  } catch (std::exception& e) {
	    std::cerr << "exception: " << e.what() << std::endl;
	    return 1;
	  }
	}
}

const char * QuestionnaireApplication::software_info()
{
	const char * info = "Welcome to the qscript demo survey page. This survey is not a demo of qscript web capabilities, but rather a demo of the pen and paper module. For web capable qscript we need to implement the following features <ul><li>Piping of answers</li><li>Unicode capture of other responses</li><li>Randomization of stub lists - groups, subgroups, holding an attribute, holding a group, etc</li><li>Randomization of attributes</li><li>question numbers are displayed at the top like this \"q1\". Looped question numbers will be displayed like this \"q1_0\". Note that the 1st iteration starts at 0.</li><li>The qscript project page is <a href=\"http://qscript.in\">http://qscript.in</a></li><li>The Download page is <a href=\"http://sourceforge.net/projects/xtcc\">http://sourceforge.net/projects/xtcc</a></li><li>Enter a serial number below. It can be upto 7 digits long. You can finish the survey later, by entering the same serial number. It will start exactly where you left off. We have no control over what serial numbers people enter. To make up a number somewhat unique - try using your mobile number, mixed with your date of birth, mixed with your spouse's date of birth.</li></ul>";
 	return info;
}
#endif /* 0 */

struct TheQuestionnaire * make_questionnaire ();
vector <Session*> wt_sessions;

void QuestionnaireApplication::setLanguage(const std::string lang)
{
	bool haveLang = false;

	for (unsigned i = 0; i < languageSelects_.size(); ++i) {
		WText *t = languageSelects_[i];

		// prefix match, e.g. en matches en-us.
		bool isLang = lang.find(narrow(t->text().value())) == 0;
		t->setStyleClass(isLang ? L"langcurrent" : L"lang");

		haveLang = haveLang || isLang;
	}

	if (!haveLang) {
		languageSelects_[0]->setStyleClass(L"langcurrent");
		WApplication::instance()
			->setLocale(narrow(languageSelects_[0]->text().value()));
	} else
		WApplication::instance()->setLocale(lang);
}


void QuestionnaireApplication::changeLanguage()
{
	WText *t = (WText *)sender();
	setLanguage(narrow(t->text().value()));
}


QuestionnaireApplication::QuestionnaireApplication (const WEnvironment &env)
	: WApplication(env), wt_questionText_(0), currentForm_(0), flagSerialPageRemoved_(false)
		//, wt_questionText_(0), currentForm_(0), flagSerialPageRemoved_(false)
{
	messageResourceBundle().use(WApplication::appRoot() + jno);
	useStyleSheet(string(jno + string("-qscript.css")).c_str());

	serialPage_ = new WContainerWidget(0);
	setTitle("QuestionnaireApplication");
	WCssDecorationStyle langStyle;
	langStyle.font().setSize(WFont::Smaller);
	langStyle.setCursor(PointingHandCursor);
	langStyle.setForegroundColor(blue);
	langStyle.setTextDecoration(WCssDecorationStyle::Underline);
	this->styleSheet().addRule(".lang", langStyle);
	langStyle.setCursor(ArrowCursor);
	langStyle.font().setWeight(WFont::Bold);
	this->styleSheet().addRule(".langcurrent", langStyle);
	langStyle.setForegroundColor(WColor(100, 0, 200, 100));
	langStyle.setCursor(IBeamCursor);
	langStyle.font().setWeight(WFont::Bold);
	langStyle.font().setSize(WFont::XLarge);
	this->styleSheet().addRule(".langtitle", langStyle);
	// warning the statement below modifies the global variable
	//load_languages_available(vec_language);
	WContainerWidget *langLayout = new WContainerWidget();
	langLayout->setStyleClass("qscript-header");
	langLayout->setContentAlignment(AlignRight);
	WText * lang_title = new WText(WString::tr("language"), langLayout);
	lang_title->setStyleClass(L"langtitle");
	for (int i = 0; i < vec_language.size(); ++i) {
		WText *t = new WText(widen(vec_language[i]), langLayout);
		t->setMargin(5);
		t->clicked().connect(this, &QuestionnaireApplication::changeLanguage);
		languageSelects_.push_back(t);
	}
	setLanguage("hn");
	WText * txt_software_info = new WText(WString::tr("qscript_info"), serialPage_);
	WPushButton *b = new WPushButton("Click to start survey", serialPage_); // create a button
	b->setMargin(5, Left);                                 // add 5 pixels margin
	serialPage_->addWidget(new WBreak());                       // insert a line break
	//b->clicked().connect(this, &QuestionnaireApplication::ValidateSerialNo);
	b->clicked().connect(this, &QuestionnaireApplication::ValidateSerialNo);

	wt_questionText_ = new WText(serialPage_);
	wt_questionText_->setText("Serial No: ");
	wt_lastQuestionVisited_ = new WText(serialPage_);
	le_data_ = new WLineEdit(serialPage_);

	wt_debug_ = new WText(serialPage_);
	formContainer_ = new WContainerWidget(root());
	formContainer_->addWidget(serialPage_);
	formContainer_->addWidget(langLayout);
	string sess_id = sessionId();
	this_users_session = new Session();
	strcpy(this_users_session->sid, sess_id.c_str());
	wt_sessions.push_back(this_users_session);
}

Wt::WServer server;
Wt::WApplication * createApplication(const Wt::WEnvironment &env)
{
	//return new QuestionnaireApplication (env);
	Wt::WApplication * ptr =  new QuestionnaireApplication (env);
	//cout << "Sizeof (WApplication): " << sizeof (*ptr) << endl;
	return ptr;
}

// warning modifies the input variable
void load_languages_available(vector<string> & vec_language)
{
	cout
		<< "Enter: "
		<< __PRETTY_FUNCTION__ << ": vec_language.size(): " << vec_language.size()
		<< endl;
	DIR * directory_ptr = opendir(".");
	vec_language.push_back("en");
	struct dirent *directory_entry = readdir(directory_ptr);
	while (directory_entry) {
		string dir_entry_name(directory_entry->d_name);
		int len_entry = dir_entry_name.length();
		if (len_entry > 4 &&
				dir_entry_name[len_entry - 1] == 'l' &&
				dir_entry_name[len_entry - 2] == 'm' &&
				dir_entry_name[len_entry - 3] == 'x' &&
				dir_entry_name[len_entry - 4] == '.' ) {
			// the names we are looking for are of the form
			// jno + "[a-z][a-z].xml"
			bool is_our_file = true;
			if (len_entry != jno.length() + 7) {
				is_our_file = false;
				// the above doesnt matter actually,
				// continue takes us back to the top
				goto read_another_entry;
			} else {
				// possibly what we are looking for
				//
				for (int i = 0; i < jno.length(); ++i) {
					if (!(jno[i] == dir_entry_name[i])) {
						// cannot be our data file
						is_our_file = false;
						goto read_another_entry;
					}
				}
				char first_letter = dir_entry_name[jno.length() + 1];
				if (! isalpha (first_letter)) {
					is_our_file = false;
					goto read_another_entry;
				}
				char second_letter = dir_entry_name[jno.length() + 2];
				if (! isalpha (second_letter)) {
					is_our_file = false;
					goto read_another_entry;
				}
				string a_language;
				a_language.push_back(first_letter);
				a_language.push_back(second_letter);
				vec_language.push_back(a_language);
				cout << "found an language traslation file: "
					<< dir_entry_name << endl;
			}
		}
read_another_entry:
		directory_entry = readdir(directory_ptr);
	}
	closedir(directory_ptr);
	cout
		<< "EXIT: "
		<< __PRETTY_FUNCTION__ << ": vec_language.size(): " << vec_language.size()
		<< endl;
}



extern bool write_messages_flag;

extern string qscript_stdout_fname;
extern FILE * qscript_stdout;

void write_messages();
int main(int argc, char ** argv)
{
	//process_options(argc, argv);
	for (int i=0; i<argc; ++i) { if (string(argv[i]) == "-m") { write_messages_flag = 1; break;} }
	if (write_messages_flag) {
		//TheQuestionnaire theQuestionnaire("dummy");
		write_messages();
		exit(0);
	}
#if 0
	if (write_messages_flag) {
		TheQuestionnaire theQuestionnaire("dummy");
		exit(0);
	}
#endif /* 0 */

	load_languages_available(vec_language);
	qscript_stdout = fopen(qscript_stdout_fname.c_str(), "w");
	//SetupSignalHandler();

	//return WRun (argc, argv, &createApplication);
	{
		try
		{
			// use argv[0] as the application name to match a suitable entry
			// in the Wt configuration file, and use the default configuration
			// file (which defaults to /etc/wt/wt_config.xml unless the environment
			// variable WT_CONFIG_XML is set)
			// WServer server(argv[0]);

			// WTHTTP_CONFIGURATION is e.g. "/etc/wt/wthttpd"
			server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);

			// add a single entry point, at the default location (as determined
			// by the server configuration's deploy-path)
			server.addEntryPoint(Wt::Application, createApplication);
			if (server.start()) {
				std::string port_number_fname = jno + string("_port_number");
				std::fstream port_number(port_number_fname.c_str(), ios_base::out);
				port_number << server.httpPort();
				port_number << ' ' << getpid() << std::endl;
				std::cout << server.httpPort() << std::endl;
				port_number.flush();
				int sig = WServer::waitForShutdown(argv[0]);
				std::cerr << "Shutdown (signal = " << sig << ")" << std::endl;
				server.stop();
				if (sig == SIGHUP)
				WServer::restart(argc, argv, environ);
			}
		} catch (WServer::Exception& e) {
			std::cerr << e.what() << std::endl;
			return 1;
		} catch (std::exception& e) {
			std::cerr << "exception: " << e.what() << std::endl;
			return 1;
		}
	}
}


void GetUserInput (
	void (*callback_ui_input) (UserInput p_user_input, AbstractRuntimeQuestion * q,
		struct TheQuestionnaire * theQuestionnaire, int nest_level),
		AbstractRuntimeQuestion *q, struct TheQuestionnaire * theQuestionnaire, int nest_level)
{
	static int count = 0;
	cout << __PRETTY_FUNCTION__ << ++count << endl;
	if (q->no_mpn == 1) {
		cout << " Question is single answer, please enter only 1 response." << endl;
	} else {
		cout << " Question accepts multiple answers." << endl;
	}
	string current_response;
	cout << "Enter Data>" << endl;
	if (count < 4) {
		//getline(cin, current_response);
	} else {
		return;
	}
	UserInput user_input;
	if (current_response.size() > 0) {
		if (current_response[0] == 'P') {
			user_input.userNavigation_ = NAVIGATE_PREVIOUS;
			user_input.theUserResponse_ = user_response::UserEnteredNavigation;
		} else if (current_response[0] == 'N') {
			user_input.userNavigation_ = NAVIGATE_NEXT;
			user_input.theUserResponse_ = user_response::UserEnteredNavigation;
		} else if (current_response[0] == 'S') {
			user_input.userNavigation_ = SAVE_DATA;
			user_input.theUserResponse_ = user_response::UserSavedData;
			cout << "Got SAVE_DATA from user" << endl;
		} else  {
			user_input.theUserResponse_ = user_response::UserEnteredData;
			user_input.questionResponseData_ = current_response;
		}

		cout << "reached here" << endl;
		string err_mesg;
		bool valid_input = q->VerifyResponse(user_input.theUserResponse_, user_input.userNavigation_, err_mesg);
		// if VerifyResponse fails it is the UI's job to get valid input from the user
		// It is not the UI's job to parse the data and validate the answer against the question

		/* moved to VerifyResponse - but seems redundant - it was already there
		if (q->isAnswered_ == false && user_input.userNavigation_ == NAVIGATE_PREVIOUS
				&& user_input.theUserResponse_ == user_response::UserEnteredNavigation) {
			// allow this behaviour - they can go back to the
			// previous question without answering anything -
			// no harm done
			callback_ui_input (user_input, q, theQuestionnaire);
		} else */
		/* moved this into VerifyResponse - final else clause
		 * where all error messages can be reported
		if (q->isAnswered_ == false && user_input.userNavigation_ == NAVIGATE_NEXT
				&& user_input.theUserResponse_ == user_response::UserEnteredNavigation
				&& q->question_attributes.isAllowBlank() == false) {
			// nxd: 18-feb-2013 - note this error message should be passed
			// back as a parameter  - so it can be reported
			err_mesg = "cannot navigate to next question unless this is answered";
			valid_input = false;
		}
		*/

		cout << "reached here: valid_input :" << valid_input <<  endl;

		if (valid_input) {

			if (user_input.theUserResponse_ == user_response::UserSavedData) {
				cout << "invoking callback_ui_input with UserSavedData" << endl;
				// this call will return really fast
				//  (if you consider io fast)
				//  but what I mean is we wont add much to the call stack
				callback_ui_input (user_input, q, theQuestionnaire, nest_level + 1);
				GetUserInput (callback_ui_input, q, theQuestionnaire,  nest_level + 1);
				cout << "callback_ui_input has returned after UserSavedData" << endl;
			} else {
				cout << "reached here: "
					<< __PRETTY_FUNCTION__ << endl;
				callback_ui_input (user_input, q, theQuestionnaire, nest_level + 1);
				cout << "callback_ui_input has returned"
					<< __PRETTY_FUNCTION__ << endl;
			}
			// move all this into callback_ui_input
			// case UserEnteredData
#if 0

			int success;
			vector <int> input_data;
			parse_input_data (current_response, &input_data, success);
			if (success == 0) {
				GetUserInput (callback_ui_input, q, theQuestionnaire);
			} else {
				// default direction - chosen by us
				user_input.userNavigation_ = NAVIGATE_NEXT;
				user_input.inputData_ = input_data;
				callback_ui_input (user_input, q, theQuestionnaire);
			}
#endif /*  0 */
		} else {
			// we should be passing an error message too
			GetUserInput (callback_ui_input, q, theQuestionnaire, nest_level + 1);
		}
		/*
		else {
			// invalid entries
			cout << "invalid input" << endl;
			question_eval_loop (NORMAL_FLOW, NAVIGATE_NEXT,
					last_question_visited, 0, qnre);
			//goto ask_again;
		} */
	} else {
		// nxd: 19-feb-2013
		// I have to change this
		GetUserInput (callback_ui_input, q, theQuestionnaire, nest_level + 1);
	}
}


vector<string>  PrepareQuestionText (AbstractRuntimeQuestion *q)
{
	using std::string;
	using std::stringstream;
	stringstream part_mesg_id;
	part_mesg_id << q->questionName_;
	for (int i=0; i<q->loop_index_values.size(); ++i)
	{
		part_mesg_id << "_" << q->loop_index_values[i];
	}
	vector <string> result;
	stringstream question_no;
	//mvwprintw(question_window, 1, 1, "%s.", questionName_.c_str());
	question_no << q->questionName_;
	//int len_qno = questionName_.length()+2;
	if (q->loop_index_values.size() > 0) {
		for (uint32_t i = 0; i < q->loop_index_values.size(); ++i) {
			//cout << loop_index_values[i]+1 << ".";
			//mvwprintw(question_window, 1, len_qno, "%d.", loop_index_values[i]+1);
			//if (loop_index_values[i]+1<10) {
			//	len_qno += 1;
			//} else if (loop_index_values[i]+1<100) {
			//	len_qno += 2;
			//} else if (loop_index_values[i]+1<1000) {
			//	len_qno += 3;
			//} else if (loop_index_values[i]+1<10000) {
			//	len_qno += 4;
			//}
			//len_qno += 1; // for the "."
			question_no << q->loop_index_values[i] << ".";
		}
	}
	result.push_back (question_no.str());
		//mvwprintw(question_window,1,1, "%s. %s", questionName_.c_str(), questionText_.c_str() );
		//wrefresh(question_window);
		//mvwprintw(question_window, 1, len_qno+1, " %s", questionText_.c_str() );
	//mvwprintw(question_window, 1, len_qno+1, " %s", textExprVec_[0]->text_.c_str() );
	stringstream question_text;
	//question_text << q->textExprVec_[0]->text_;
	//result.push_back (question_text.str());
	//for (int i=1; i<q->textExprVec_.size(); ++i) {
	//	//mvwprintw(question_window, 2+i, 1, " %s", textExprVec_[i]->text_.c_str() );
	//	result.push_back (q->textExprVec_[i]->text_);
	//}
	//WString question_text_str;
	for (int i=0; i<q->textExprVec_.size(); ++i)
        {
        	question_text << "<p>";
		//question_text_str += "<p>";
        	if (q->textExprVec_[i]->teType_ == TextExpression::simple_text_type)
        	{
        		//stringstream mesg_id;
        		//mesg_id << part_mesg_id.str() << "_" << i;
        		//question_text += WString::tr(mesg_id.str().c_str());
			question_text << q->textExprVec_[i]->text_;
			{
			stringstream mesg_id;
			mesg_id << part_mesg_id.str() << "_" << i;
			//question_text_str += WString::tr(mesg_id.str().c_str());
			}
        	}
        	else if (q->textExprVec_[i]->teType_ == TextExpression::named_attribute_type)
        	{
			{
        		stringstream named_attribute_key;
        		named_attribute_key << q->textExprVec_[i]->naPtr_->name;
        		named_attribute_key << "_" << q->textExprVec_[i]->naIndex_;
        		//question_text_str += WString::tr(named_attribute_key.str().c_str());
			}
			question_text << q->textExprVec_[i]->naPtr_->attribute[q->textExprVec_[i]->naIndex_];
        	}
        	else if (q->textExprVec_[i]->teType_ == TextExpression::question_type)
        	{
        		if (q->textExprVec_[i]->codeIndex_ != -1) {
        			question_text << q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers(q->textExprVec_[i]->codeIndex_);
				//question_text_str += q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers(q->textExprVec_[i]->codeIndex_);
        		} else {
        			question_text << q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers();
				//question_text_str += q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers();
        		}
			//question_text << "pipedQuestion_" << endl;
        	}
        	question_text << "</p>";
        	//question_text_str += "</p>";
        }
	result.push_back (question_text.str());
	return result;

}

void DisplayQuestionTextView (const vector <string> & qno_and_qtxt)
{
	string start_marker("===================== QUESTION TEXT =============================");
	string end_marker  ("================= END OF QUESTION TEXT ==========================");
	if (qno_and_qtxt.size() > 1) {
		cout << start_marker << endl;
		cout << qno_and_qtxt[0] << "." << qno_and_qtxt[1];
		for (int i = 2; i < qno_and_qtxt.size(); ++i) {
			cout <<  qno_and_qtxt[i].c_str();
		}
		cout << endl;

		cout << end_marker << endl;
	}
	cout << endl;
}


void ClearPreviousView ()
{
	cout << __PRETTY_FUNCTION__ << endl;
}

void PrepareStubs (AbstractRuntimeQuestion *q)
{

}

void DisplayStubs (AbstractRuntimeQuestion *q)
{
	string marker_start ("------------------------------- STUBS ------------------------------------");
	string marker_end   ("----------------------------- STUBS END ----------------------------------");
	cout << marker_start << endl;
	if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*> (q) ) {
		vector<stub_pair> & vec= (nq->nr_ptr->stubs);
		for (int i=0; i<vec.size(); ++i) {
			cout 	<< vec[i].code << " : " << vec[i].stub_text
				<< endl;
		}
	} else if (RangeQuestion * rq = dynamic_cast<RangeQuestion*> (q) ) {
		rq->MakeDisplaySummaryDataRanges();
		for(	vector<display_data::DisplayDataUnit>::iterator it = rq->displayData_.begin();
				it != rq->displayData_.end(); ++it) {
			//cout << *it << endl;
			if ( (*it).displayDataType_ == display_data::single_element) {
				cout << "  " << (*it).startOfRangeOrSingle_ << " ";
			} else if ( (*it).displayDataType_ == display_data::range_element) {
				cout << "  " << (*it).startOfRangeOrSingle_ << " - " << (*it).endOfRange_;
			}
		}
		cout << endl;
	} else {
		cerr << "Unhandled exception" << endl;
		exit(1);
	}
	cout << marker_end << endl;
}


void DisplayCurrentAnswers (AbstractRuntimeQuestion * q)
{
	if (q->input_data.begin() != q->input_data.end()) {
		cout << "Current Answers values: ";

		for (set<int32_t>::iterator iter = q->input_data.begin();
			iter != q->input_data.end(); ++iter){
			cout << *iter << " ";
		}
		cout << endl;
	}
	string end_marker("----------------- END OF ANSWERS -----------------------");
	cout << end_marker << endl;
}




void stdout_eval (AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire,
	void (*callback_ui_input) (UserInput p_user_input, AbstractRuntimeQuestion * q,
		struct TheQuestionnaire * theQuestionnaire, int nest_level), int nest_level)
{
	cout << "Enter: " << __PRETTY_FUNCTION__ << "nest_level: " << nest_level << endl;
	ClearPreviousView ();
	vector <string> qno_and_qtxt = PrepareQuestionText (q);
	DisplayQuestionTextView (qno_and_qtxt);
	PrepareStubs (q);
	DisplayStubs (q);
	DisplayCurrentAnswers (q);
	//GetUserInput (callback_ui_input, q, theQuestionnaire);
	QuestionnaireApplication * qapp_ptr =  static_cast<QuestionnaireApplication*> (WApplication::instance());
	// nxd implement: wxGUI->set_callback_ui_input (callback_ui_input);
	qapp_ptr->set_callback_ui_input(callback_ui_input);
	//gtkQuestionnaireApplication->ConstructQuestionForm (q
	//		//, gtkQuestionnaireApplication->this_users_session
	//		);

	// nxd implement: wxGUI->ConstructQuestionForm( q );
	qapp_ptr->ConstructQuestionForm( q );
	//GetUserInput (callback_ui_input, q, theQuestionnaire);
	cout << "EXIT:"
		<< __PRETTY_FUNCTION__
		<< ", nest_level:" << nest_level
		<< endl;
}


void QuestionnaireApplication::PrepareMultiCodedStubDisplay (NamedStubQuestion * nq)
{
	cout << __PRETTY_FUNCTION__ << endl;
	ClearStubsArea();
	wt_cb_rb_container_ = new WGroupBox();
	wt_cb_rb_container_->setStyleClass("qscript-rb-cb-container");
	vector<stub_pair> & vec= (nq->nr_ptr->stubs);
	unsigned long count = vec.size();
	for (int i=0; i<vec.size(); ++i) {
		stringstream named_range_key;
		named_range_key << nq->nr_ptr->name << "_" << i;
#if 0
		if (/*q->no_mpn==1 && */ vec[i].mask) {
			//WRadioButton * wt_rb = new WRadioButton( vec[i].stub_text, wt_cb_rb_container_);
			WRadioButton * wt_rb = new WRadioButton(WString::tr(named_range_key.str().c_str()), wt_cb_rb_container_);
			wt_rb_container_->addButton(wt_rb, vec[i].code);
			new WBreak(wt_cb_rb_container_);
			vec_rb.push_back(wt_rb);
		}
		else
#endif /* 0 */
		if (/*q->no_mpn>1 && */ vec[i].mask)
		{
			//WCheckBox * wt_cb = new WCheckBox ( vec[i].stub_text, wt_cb_rb_container_);
			WCheckBox * wt_cb = new WCheckBox (WString::tr(named_range_key.str().c_str()), wt_cb_rb_container_);
			wt_cb->setInline(false);
			//wt_cb->setStyleClass("qscript-check-box");
			wt_cb->setStyleClass("qscript-span-checkbox");
			vec_cb.push_back(wt_cb);
			cout << " adding code: " << vec[i].code << " to map_cb_code_index" ;
			map_cb_code_index[vec_cb.size()-1] = vec[i].code;
		}
	}

	/*
	static const unsigned int DEFAULT_N_MAJOR_DIM = 2;
	unsigned long nmajorDim = DEFAULT_N_MAJOR_DIM;
	wxString *items = new wxString[count];

	rbQnreCodeMap_.clear();
	int actual_count = 0;
	for ( size_t i = 0; i < count; ++i ) {
		if (vec[i].mask) {
			stringstream s1;
			s1 << vec[i].code << ": " << vec[i].stub_text;
			//items[i] = wxString::FromUTF8(vec[i].stub_text.c_str());
			items[actual_count] = wxString::FromUTF8 (s1.str().c_str());
			rbQnreCodeMap_[actual_count] = vec[i].code;
			//items[i] = wxString::Format (_T("%d: %s"),
			//		vec[i].stub_text.c_str(),
			//		vec[i].code);
			++actual_count;
		}
	}


	int flags = 0;
	m_pListBox = new wxCheckListBox
		(
		 panel,               // parent
		 MultiAnswerCheckListBox,       // control id
		 wxDefaultPosition, //wxPoint(10, 10),       // listbox poistion
		 //wxDefaultSize,
		 wxSize(500, 350),      // listbox size
		 actual_count, // WXSIZEOF(aszChoices),  // number of strings
		 items, //astrChoices,           // array of strings
		 flags
		);

	delete [] items;

    // set grey background for every second entry
    //for ( ui = 0; ui < WXSIZEOF(aszChoices); ui += 2 ) {
    //    AdjustColour(ui);
    //}

	//m_pListBox->Check(2);
	//m_pListBox->Select(3);
	//check_box_sizer->Add (rboxWindow_);
	check_box_sizer->Add (m_pListBox);
	//stubsRowSizer_->Add(rboxWindow_, 1, wxGROW);
	fgs->Layout();
	panel_sizer->Layout();
	*/

}


void QuestionnaireApplication::PrepareSingleCodedStubDisplay (NamedStubQuestion * nq)
{
	cout << __PRETTY_FUNCTION__ << endl;
	//ClearRadio();
	ClearStubsArea();
	wt_cb_rb_container_ = new WGroupBox();
	wt_cb_rb_container_->setStyleClass("qscript-rb-cb-container");
	wt_rb_container_ = new WButtonGroup(wt_cb_rb_container_);
	vector<stub_pair> & vec= (nq->nr_ptr->stubs);
	unsigned long count = vec.size();
	for (int i=0; i<vec.size(); ++i) {
		stringstream named_range_key;
		named_range_key << nq->nr_ptr->name << "_" << i;
		if (/*q->no_mpn==1 && */ vec[i].mask) {
			//WRadioButton * wt_rb = new WRadioButton( vec[i].stub_text, wt_cb_rb_container_);
			WRadioButton * wt_rb = new WRadioButton(WString::tr(named_range_key.str().c_str()), wt_cb_rb_container_);
			wt_rb->setStyleClass("qscript-span-radio");
			wt_rb_container_->addButton(wt_rb, vec[i].code);
			new WBreak(wt_cb_rb_container_);
			vec_rb.push_back(wt_rb);
		}
#if 0
		if (/*q->no_mpn>1 && */ vec[i].mask) {
			//WCheckBox * wt_cb = new WCheckBox ( vec[i].stub_text, wt_cb_rb_container_);
			WCheckBox * wt_cb = new WCheckBox (WString::tr(named_range_key.str().c_str()), wt_cb_rb_container_);
			vec_cb.push_back(wt_cb);
			cout << " adding code: " << vec[i].code << " to map_cb_code_index" ;
			map_cb_code_index[vec_cb.size()-1] = vec[i].code;
		}
#endif /* 0 */
	}



	// no of radio buttons
#if 0
	vector<stub_pair> & vec= (nq->nr_ptr->stubs);
	unsigned long count = vec.size();
	static const unsigned int DEFAULT_N_MAJOR_DIM = 2;
	unsigned long nmajorDim = DEFAULT_N_MAJOR_DIM;

	wxString *items = new wxString[count];

	rbQnreCodeMap_.clear();
	int actual_count = 0;
	for ( size_t i = 0; i < count; ++i ) {
		if (vec[i].mask) {
			stringstream s1;
			s1 << vec[i].code << ": " << vec[i].stub_text;
			//items[i] = wxString::FromUTF8(vec[i].stub_text.c_str());
			items[actual_count] = wxString::FromUTF8 (s1.str().c_str());
			rbQnreCodeMap_[actual_count] = vec[i].code;
			//items[i] = wxString::Format (_T("%d: %s"),
			//		vec[i].stub_text.c_str(),
			//		vec[i].code);
			++actual_count;
		}
	}
	int flags = wxLB_SINGLE;
	m_rListBox = new wxListBox
		(
		 panel,               // parent
		 SingleAnswerRadioBox,       // control id
		 wxDefaultPosition, //wxPoint(10, 10),       // listbox poistion
		 //wxDefaultSize,
		 wxSize(500, 350),      // listbox size
		 actual_count, // WXSIZEOF(aszChoices),  // number of strings
		 items, //astrChoices,           // array of strings
		 flags
		);
	delete [] items;

	the_stubs->SetLabel(wxT("New Stubs Text - should be visible now"));
	cout << "Updated New stubs text" << endl;
	//stubsRowSizer_->Add(m_radio, 1, wxGROW);
	//stubsRowSizer_->Add(rboxWindow_, 1, wxGROW);
	//radio_box_sizer->Add(rboxWindow_);
	radio_box_sizer->Add(m_rListBox, 1, wxGROW);
	fgs->Layout();
	panel_sizer->Layout();
#endif /*  0 */
}


void QuestionnaireApplication::DisplayStubs (AbstractRuntimeQuestion * q)
{
	cout << __PRETTY_FUNCTION__ << endl;
	if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q))
	{
		// nxd: move both the below functions to a clear() api which we call from here
		//rbData_ = -1; // clear the data basically
		//cbData_.clear();
		if (q->no_mpn==1)
		{
			PrepareSingleCodedStubDisplay(nq);
		} else {
			PrepareMultiCodedStubDisplay (nq);
		}
	} else {
		cout << "=== Implement Display Range Question" << endl;
	}
}

void QuestionnaireApplication::set_callback_ui_input (
			void (*p_callback_ui_input) (UserInput p_user_input, AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire, int nest_level)
			)
{
	callback_ui_input = p_callback_ui_input;
}

void QuestionnaireApplication::DisplayQuestionTextView (const vector <string> & qno_and_qtxt)
{

	wt_questionText_ = new WText();
	wt_questionNo_ = new WText();
	std::stringstream question_text;
	for (int i=1; i < qno_and_qtxt.size(); ++i) {
		question_text << qno_and_qtxt[i];
	}
	wt_questionText_->setText(question_text.str());
	wt_questionText_->setStyleClass("qscript-qtext");
	wt_questionNo_->setText(qno_and_qtxt[0]);
	wt_questionNo_->setStyleClass("qscript-qno");
}

void QuestionnaireApplication::ConstructQuestionForm( AbstractRuntimeQuestion *q )
{
	WContainerWidget * new_form = new WContainerWidget();
	new_form->setStyleClass("qscript-container");
	vec_rb.clear();			 // memory leak introduced here? no it seems
	vec_cb.clear();			 // memory leak introduced here? no it seems

	vector <string> question_text_vec = PrepareQuestionText (q);
	//the_question = new wxStaticText(panel, -1, wxT("Question No and Question Text"));
	DisplayQuestionTextView (question_text_vec);
	new_form->addWidget(wt_questionNo_);
	new_form->addWidget(wt_questionText_);
	// Hack to Display Radio Buttons
	if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q)) {
		DisplayStubs (q);
		wt_cb_rb_container_->setStyleClass("qscript-rb-cb-container");
		new_form->addWidget(wt_cb_rb_container_);
	} else {
		le_data_ = new WLineEdit();
		le_data_->setStyleClass("qscript-open-end-textbox");
		new_form->addWidget(le_data_);
	}
	this_users_session -> ptr_last_question_visited = q;
	WPushButton *b = new WPushButton("Next");
	b->clicked().connect(this, &QuestionnaireApplication::handleDataInput);
	WPushButton *b = new WPushButton("Previous");
	WPushButton *b = new WPushButton("Save");
	new_form->addWidget(b);
	setCentralWidget(new_form);

}


void QuestionnaireApplication::setCentralWidget (WContainerWidget * new_question_form)
{
	if (!flagSerialPageRemoved_) {
		formContainer_->removeWidget (serialPage_);
		flagSerialPageRemoved_ = true;
	}
	if (currentForm_) {
		delete currentForm_;
	}
	currentForm_ = new_question_form;
	formContainer_->addWidget (currentForm_);
}


void QuestionnaireApplication::ClearStubsArea()
{
	//ClearCheckList();
	//ClearRadio();
}

void QuestionnaireApplication::handleRBDataInput (int nest_level)
{
	vector<int32_t> data;
	stringstream s1;
	bool isAnswered = false;
	if ( wt_rb_container_->selectedButtonIndex() != -1) {
		isAnswered = true;
		int code = wt_rb_container_->checkedId();
		cout << "no_mpn == 1, code: " << code << endl;
		data.push_back(code);
		s1 << code;
	} else {
		isAnswered = false;
	}
	string err_mesg;
	UserInput user_input;
	user_input.theUserResponse_ = user_response::UserEnteredData;
	user_input.questionResponseData_ = s1.str();
	AbstractRuntimeQuestion * q = this_users_session -> ptr_last_question_visited ;
	bool valid_input = q->VerifyResponse(user_input.theUserResponse_, user_input.userNavigation_, err_mesg);
	if (valid_input) {
		if (user_input.theUserResponse_ == user_response::UserSavedData) {
			cerr  << "NOT YET DONE"
				<< __FILE__ << "," << __LINE__ << "," << __PRETTY_FUNCTION__
				<< endl
				<< "invoking callback_ui_input with UserSavedData" << endl;
			// this call will return really fast
			//  (if you consider io fast)
			//  but what I mean is we wont add much to the call stack
			callback_ui_input (user_input, q, this_users_session -> theQuestionnaire_, nest_level + 1);
			//GetUserInput (callback_ui_input, q, theQuestionnaire);
			cout << "callback_ui_input has returned after UserSavedData" << endl;
		} else {
			cout << "reached here: "
				<< __PRETTY_FUNCTION__ << endl;
			callback_ui_input (user_input, q, this_users_session ->theQuestionnaire_, nest_level + 1);
			cout << "callback_ui_input has returned"
				<< __PRETTY_FUNCTION__ << endl;
		}
		// move all this into callback_ui_input
		// case UserEnteredData
	} else {
		// we should be passing an error message too
		//GetUserInput (callback_ui_input, q, theQuestionnaire);
		// do nothing - the callback just continues to wait for data
	}

}

void QuestionnaireApplication::handleCBDataInput (int nest_level)
{
	vector<int32_t> data;
	bool isAnswered = false;

	stringstream s1;

#if 0
	for (set<int32_t>::iterator it = cbData_.begin(); it != cbData_.end(); ++it) {
		//cout << " " << *it;
		data.push_back (*it);
		s1 << " " << (*it);
	}
	cout << " vec_cb.size(): " << vec_cb.size() << "no_mpn > 1" << endl;
#endif

	for (int i = 0; i < vec_cb.size(); ++i) {
		if (vec_cb[i]->checkState() == Wt::Checked) {
			int code = map_cb_code_index[i];
			data.push_back(code);
			cout << "vec_cb[" << i << "] is checked,   code: " << code << endl;
			isAnswered = true;
			s1 << " " << code;
		}
	}
	UserInput user_input;
	user_input.questionResponseData_ = s1.str();
	user_input.theUserResponse_ = user_response::UserEnteredData;
	AbstractRuntimeQuestion * q = this_users_session -> ptr_last_question_visited ;
	string err_mesg;
	bool valid_input = q->VerifyResponse(user_input.theUserResponse_, user_input.userNavigation_, err_mesg);
	if (valid_input) {
		if (user_input.theUserResponse_ == user_response::UserSavedData) {
			cerr  << "NOT YET DONE"
				<< __FILE__ << "," << __LINE__ << "," << __PRETTY_FUNCTION__
				<< endl
				<< "invoking callback_ui_input with UserSavedData" << endl;
			// this call will return really fast
			//  (if you consider io fast)
			//  but what I mean is we wont add much to the call stack
			callback_ui_input (user_input, q, this_users_session -> theQuestionnaire_, nest_level + 1);
			//GetUserInput (callback_ui_input, q, theQuestionnaire);
			cout << "callback_ui_input has returned after UserSavedData" << endl;
		} else {
			cout << "reached here: "
				<< __PRETTY_FUNCTION__ << endl;
			callback_ui_input (user_input, q, this_users_session -> theQuestionnaire_, nest_level + 1);
			cout << "callback_ui_input has returned"
				<< __PRETTY_FUNCTION__ << endl;
		}
		// move all this into callback_ui_input
		// case UserEnteredData
	} else {
		// we should be passing an error message too
		//GetUserInput (callback_ui_input, q, theQuestionnaire);
		// do nothing - the callback just continues to wait for data
	}

}

void QuestionnaireApplication::handleRangeQuestionData(int nest_level)
{
	cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
	string current_question_response = le_data_->text().narrow();
	AbstractRuntimeQuestion * last_question_served = this_users_session-> ptr_last_question_visited;
	if (last_question_served->no_mpn==1) {
#if 0
		UserNavigation user_nav=NOT_SET;
		user_response::UserResponseType user_resp=user_response::NotSet;
		vector<int32_t> data;
		bool parse_success = verify_web_data (current_question_response, user_nav, user_resp, &data);
		if (parse_success)
		{
			cout << "successfully parsed data = ";
			for (int i=0; i<data.size(); ++i)
			{
				cout << data[i] << ", ";
			}
			cout << endl;
		}
		// the call below will be required at some later stage
		//bool valid_input = AbstractQuestion::VerifyResponse(user_resp);
		// right now we go along with the happy path
		bool invalid_code = last_question_served->VerifyData(err_mesg, re_arranged_buffer, pos_1st_invalid_data,
			&data);
		if (invalid_code == false)
		{
			last_question_served->input_data.erase
				(last_question_served->input_data.begin(),
				last_question_served->input_data.end());
			for(uint32_t i = 0; i < data.size(); ++i)
			{
				last_question_served->input_data.insert(data[i]);
				//cout << "storing: " << data[i]
				//	<< " into input_data" << endl;
			}
			last_question_served->isAnswered_ = true;
			data.clear();
			callback_ui_input (user_input, q, this_users_session -> theQuestionnaire_, nest_level + 1);
		}
		else {
			//ConstructQuestionForm(last_question_served, this_users_session);
			//return;
		}
#endif /* 0 */

		UserInput user_input;
		user_input.questionResponseData_ = current_question_response ;
		user_input.theUserResponse_ = user_response::UserEnteredData;
		AbstractRuntimeQuestion * q = this_users_session -> ptr_last_question_visited ;
		string err_mesg;
		bool valid_input = q->VerifyResponse(user_input.theUserResponse_, user_input.userNavigation_, err_mesg);
		if (valid_input) {
			if (user_input.theUserResponse_ == user_response::UserSavedData) {
				cerr  << "NOT YET DONE"
					<< __FILE__ << "," << __LINE__ << "," << __PRETTY_FUNCTION__
					<< endl
					<< "invoking callback_ui_input with UserSavedData" << endl;
				// this call will return really fast
				//  (if you consider io fast)
				//  but what I mean is we wont add much to the call stack
				callback_ui_input (user_input, q, this_users_session -> theQuestionnaire_, nest_level + 1);
				//GetUserInput (callback_ui_input, q, theQuestionnaire);
				cout << "callback_ui_input has returned after UserSavedData" << endl;
			} else {
				cout << "reached here: "
					<< __PRETTY_FUNCTION__ << endl;
				callback_ui_input (user_input, q, this_users_session -> theQuestionnaire_, nest_level + 1);
				cout << "callback_ui_input has returned"
					<< __PRETTY_FUNCTION__ << endl;
			}
			// move all this into callback_ui_input
			// case UserEnteredData
		} else {
			// do nothing
		}
	} else if (last_question_served->no_mpn > 1) {
		string utf8_response = le_data_->text().toUTF8();
		if (utf8_response != "")
		{
			stringstream file_name_str;
			file_name_str << last_question_served->questionName_ << "."
				<< jno << "_" << ser_no << ".dat";
			fstream open_end_resp(file_name_str.str().c_str(), ios_base::out|ios_base::ate);
			open_end_resp << utf8_response << endl;
			//last_question_served->input_data.insert(96);
			//last_question_served->isAnswered_ = true;
			stringstream ss1 ;
			ss1 << 96;
			UserInput user_input;
			user_input.questionResponseData_ = ss1.str();
			user_input.theUserResponse_ = user_response::UserEnteredData;
			AbstractRuntimeQuestion * q = this_users_session -> ptr_last_question_visited ;
			string err_mesg;
			bool valid_input = q->VerifyResponse(user_input.theUserResponse_, user_input.userNavigation_, err_mesg);
			if (valid_input) {
				callback_ui_input (user_input, q, this_users_session -> theQuestionnaire_, nest_level + 1);
			}
#if 0
#endif /* 0 */
		}
		else
		{
			// Do nothing - but we should print a default error message on the screen
		}
	}

	cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
}

/*
void QuestionnaireApplication::ConstructThankYouPage()
{
	WContainerWidget * new_form = new WContainerWidget();
	WText * txt = new WText(WString::tr("thank_you"), new_form);
	WText * survey_code = new WText(WString::tr("vege_source_code"), new_form);
	setCentralWidget(new_form);
	cout << "ConstructThankYouPage\n";
}
*/

void QuestionnaireApplication::handleDataInput()
{
	cout << __PRETTY_FUNCTION__ << endl;
	if (NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion *>(this_users_session -> ptr_last_question_visited )) {
		AbstractRuntimeQuestion * last_question_served = this_users_session -> ptr_last_question_visited ;
		vector<int32_t> data;
		bool isAnswered = false;
		cout << "returned back data from question: " << nq->questionName_ << endl;
		if (last_question_served->no_mpn == 1) {
			handleRBDataInput(1);
		} else {
			cout << "Reached NamedStubQuestion and currently doing nothing" << endl;
			handleCBDataInput(1);
		}

	} else {

		string current_question_response = le_data_->text().narrow();
		if (current_question_response !="") {
			handleRangeQuestionData(1);
		}

	}

}
