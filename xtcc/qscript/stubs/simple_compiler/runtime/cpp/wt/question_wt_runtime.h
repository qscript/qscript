#ifndef question_wt_runtime_h
#define question_wt_runtime_h


#include <Wt/WApplication>
#include <Wt/WServer>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WRadioButton>
#include <Wt/WCheckBox>
#include <Wt/WBreak>
#include <Wt/WButtonGroup>
#include <Wt/WGroupBox>
#include <Wt/WString>
#include <Wt/WStringUtil>
#include "ui_return_value.h"

#include "question.h"
struct TheQuestionnaire;
struct TheQuestionnaire * make_questionnaire ();
struct Session
{
	/**
	* We keep all sessions in a linked list.
	*/
	struct Session *next;
	/**
	* Unique ID for this session.
	*/
	char sid[33];
	/**
	* Reference counter giving the number of connections
	* currently using this session.
	*/
	unsigned int rc;
	/**
	* Time when this session was last active.
	*/
	time_t start;
	struct TheQuestionnaire * theQuestionnaire_;
	char last_question_answered[200];
	char last_question_visited[200];
	char question_response[200];
	char user_navigation[200];
	//AbstractRuntimeQuestion * last_question_served;
	//AbstractRuntimeQuestion * ptr_last_question_answered;
	//AbstractRuntimeQuestion * ptr_last_question_visited;
	Session()
		: start(time(NULL)),
		  theQuestionnaire_(make_questionnaire()),
		  rc(1) //,
		  //last_question_served(0),
		  //ptr_last_question_answered(0),
		  //ptr_last_question_visited(0)
	{
		snprintf (sid,
		    sizeof (sid),
		    "%X%X%X%X",
		    (unsigned int) random (),
		    (unsigned int) random (),
		    (unsigned int) random (),
		    (unsigned int) random ());
		memset(last_question_answered, 0, sizeof(last_question_answered));
		memset(last_question_visited, 0, sizeof(last_question_visited));
	}
	~Session()
	{
		//delete theQuestionnaire_;
		//theQuestionnaire_ = 0;
	}
};

struct QuestionUITemplate
{
	Wt::WContainerWidget * questionContainer_;
	Wt::WText * wt_questionNo_;
	Wt::WText * wt_questionText_;
	Wt::WGroupBox * wt_cb_rb_container_;
	Wt::WButtonGroup * wt_rb_container_;
	Wt::WLineEdit * le_data_;
	vector<Wt::WRadioButton*> vec_rb;
	vector<Wt::WCheckBox*> vec_cb;
	std::map<int, int> map_cb_code_index;
	QuestionUITemplate ()
		: questionContainer_(0), wt_questionNo_(0), wt_questionText_(0),
		  wt_cb_rb_container_(0), wt_rb_container_(0)
	{ }
};


class QuestionnaireApplication: public Wt::WApplication
{
public:
	int ser_no;
	Session * this_users_session;
	string sess_id ;
	Wt::WContainerWidget * serialPage_;
	std::vector<Wt::WText *> languageSelects_;
	Wt::WContainerWidget * formContainer_;
	Wt::WContainerWidget * currentForm_;
	Wt::WText * wt_SerialNo_;
	Wt::WLineEdit * le_SerialNo_;
	Wt::WText * wt_debug_;
	Wt::WText * wt_lastQuestionVisited_;
	Wt::WText * wtxt_err_mesg_;
#if 0
	WText * wt_questionText_;
	WText * wt_questionNo_;
	WLineEdit * le_data_;
	WGroupBox * wt_cb_rb_container_;
	WButtonGroup * wt_rb_container_;
	vector<WRadioButton*> vec_rb;
	vector<WCheckBox*> vec_cb;
	std::map<int, int> map_cb_code_index;
#endif /* 0 */
	vector <QuestionUITemplate *> question_ui_vec;
	bool flagSerialPageRemoved_;
	QuestionnaireApplication (const Wt::WEnvironment &env);
	void (*callback_ui_input) (UserInput p_user_input,
		const vector <AbstractRuntimeQuestion *> & q_vec,
		struct TheQuestionnaire * theQuestionnaire, int nest_level);
	void changeLanguage();
	void setLanguage(const std::string lang);
	void ValidateSerialNo();


	void set_callback_ui_input (
		void (*p_callback_ui_input)
				(UserInput p_user_input,
				const vector <AbstractRuntimeQuestion *> & q_vec,
				struct TheQuestionnaire * theQuestionnaire,
				int nest_level)
	);
	void ConstructQuestionForm(const vector<AbstractRuntimeQuestion *> & q_vec);
	void DisplayQuestionTextView (QuestionUITemplate * p_q_ui_form,
			const vector <string> & qno_and_qtxt);
	void setCentralWidget(Wt::WContainerWidget * new_question_form);
	void DisplayStubs (QuestionUITemplate * p_q_ui_form,
			AbstractRuntimeQuestion * q);
	void PrepareMultiCodedStubDisplay (
		QuestionUITemplate* p_q_ui_form, NamedStubQuestion * nq);
	void PrepareSingleCodedStubDisplay (
		QuestionUITemplate* p_q_ui_form, NamedStubQuestion * nq);
	void ClearStubsArea();
	void handleDataInput();
	void handleSave();
	UIReturnValue handleRBDataInput (int nest_level, int form_index);
	void handleCBDataInput (int nest_level);
	void handleRangeQuestionData (int nest_level);
	void print_ui_error_message (string & err_mesg);

};



#endif /* question_wt_runtime_h */
