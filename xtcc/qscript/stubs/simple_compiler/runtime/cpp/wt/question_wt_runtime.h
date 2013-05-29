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
	AbstractRuntimeQuestion * last_question_served;
	AbstractRuntimeQuestion * ptr_last_question_answered;
	AbstractRuntimeQuestion * ptr_last_question_visited;
	Session()
		: start(time(NULL)),
		  theQuestionnaire_(make_questionnaire()),
		  rc(1), last_question_served(0),
		  ptr_last_question_answered(0),
		  ptr_last_question_visited(0)
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


using namespace Wt;
class QuestionnaireApplication: public WApplication
{
public:
	int ser_no;
	Session * this_users_session;
	string sess_id ;
	WContainerWidget * serialPage_;
	std::vector<WText *> languageSelects_;
	WText * wt_debug_;
	WText * wt_questionText_;
	WLineEdit * le_data_;
	WContainerWidget * formContainer_;
	WContainerWidget * currentForm_;
	WText * wt_lastQuestionVisited_;
	WGroupBox * wt_cb_rb_container_;
	WButtonGroup * wt_rb_container_;
	vector<WRadioButton*> vec_rb;
	vector<WCheckBox*> vec_cb;
	bool flagSerialPageRemoved_;
	std::map<int, int> map_cb_code_index;
	QuestionnaireApplication (const WEnvironment &env);
	void (*callback_ui_input) (UserInput p_user_input, AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire, int nest_level);
	void changeLanguage();
	void setLanguage(const std::string lang);
	void ValidateSerialNo();

	void set_callback_ui_input (
		void (*p_callback_ui_input)
				(UserInput p_user_input,
				AbstractRuntimeQuestion * q,
				struct TheQuestionnaire * theQuestionnaire,
				int nest_level)
	);
	void ConstructQuestionForm( AbstractRuntimeQuestion *q );
	void DisplayQuestionTextView (const vector <string> & qno_and_qtxt);
	void setCentralWidget(WContainerWidget * new_question_form);
	void DisplayStubs (AbstractRuntimeQuestion * q);
	void PrepareMultiCodedStubDisplay (NamedStubQuestion * nq);
	void PrepareSingleCodedStubDisplay (NamedStubQuestion * nq);
	void ClearStubsArea();
	void handleDataInput();
	void handleRBDataInput (int nest_level);
	void handleCBDataInput (int nest_level);
	void handleRangeQuestionData (int nest_level);

};



#endif /* question_wt_runtime_h */
