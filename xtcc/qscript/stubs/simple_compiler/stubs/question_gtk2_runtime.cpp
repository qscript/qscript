/*
 * =====================================================================================
 *
 *       Filename:  question_stdout_runtime.C
 *
 *    Description:  Simplest possible runtime
 *    			and I should have built this first
 *    			but I thought that I was too smart
 *
 *        Version:  1.0
 *        Created:  Sunday 17 February 2013 11:42:54  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Neil Xavier D'Souza
 *        Company:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <cstdlib>
#include <locale.h>
#include <libintl.h>
#include <gtk/gtk.h>
#include <map>

#include "question_stdout_runtime.h"
#include "named_range.h"
#include "question_disk_data.h"
#include "qscript_data.hpp"

void parse_input_data(vector<int> * data_ptr, int & success);

void destroy( GtkWidget *widget, gpointer data );
gint delete_event (GtkWidget *widget, GdkEvent *event, gpointer data);

using namespace std;


//#include "inp_jump_test.h"
//string qscript_stdout_fname("qscript_stdout.log");
//FILE * qscript_stdout = 0;
extern FILE * qscript_stdout ;
string GenerateSessionId();
extern string jno;


struct Session
{
	/**
	 * We keep all sessions in a linked list.
	 */
	//struct Session *next;
	/**
	 * Unique ID for this session.
	 */
	char sid[50];
	/**
	 * Reference counter giving the number of connections
	 * currently using this session.
	 */
	unsigned int rc;
	/**
	 * Time when this session was last active.
	 */
	time_t start;

	//struct TheQuestionnaire * questionnaire;
	char last_question_answered[200];
	char last_question_visited[200];
	char question_response[200];
	char user_navigation[200];
	AbstractQuestion * last_question_served;
	AbstractQuestion * ptr_last_question_answered;
	AbstractQuestion * ptr_last_question_visited;
	Session()
		: start(time(NULL)), rc(1)
		//questionnaire(new TheQuestionnaire()),
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
		//delete questionnaire;
		//questionnaire = 0;
	}
	private:
		Session& operator= (const Session&);
		Session (const Session&);
};

static struct Session *sessions;
vector <Session*> wt_sessions;
class GtkQuestionnaireApplication;

struct GtkRadioButtonData
{
	int selectedCode_;
	GtkQuestionnaireApplication * qApp_;
	GtkRadioButtonData (int data, GtkQuestionnaireApplication * p_qapp)
		: selectedCode_ (data), qApp_ (p_qapp)
		{ }
};

class GtkQuestionnaireApplication
{
	public:
		GtkWidget * window , * top_half , * bottom_half ;
		GtkQuestionnaireApplication (int argc, char * argv[] /* , int (* p_return_ser_no) (int) */ );
		void SetupGTK (int argc, char * argv[]);
		int (*return_ser_no) (int p_ser_no);
		int rb_selected_code;

		// This may have to be moved to a better location than here
		//  - for example struct TheQuestionnaire
		AbstractQuestion * last_question_visited;
		AbstractQuestion * jump_to_question;
		void handleDataInput();
	private:
		GtkWidget * wt_debug_;
		GtkWidget * wt_questionText_;
		GtkWidget * le_data_;
		GtkWidget * wt_lastQuestionVisited_;
		GtkWidget * wt_cb_rb_container_;
		GtkWidget * wt_rb_container_;

		GtkWidget * questionTextLabel_;

		vector<GtkWidget*> vec_rb;
		vector<GtkRadioButtonData*> rbData_;
		vector<GtkWidget*> vec_cb;
		std::map<int, int> map_cb_code_index;
		std::vector<GtkWidget *> languageSelects_;

		GtkWidget 
			//*vbox, 
			*hbox ;
		GtkWidget * serialNoEntry_ ;
		//GtkWidget * button ;
		GtkWidget * check ;
		GtkWidget * rb ;
		GtkWidget * next_button ;

		GtkWidget * viewPort_;
		GtkWidget * currentForm_;
		GtkWidget * formContainer_;
		GSList * gtkRadioButtonGroup_;

		GtkWidget * bottomHalfVBox_, * bottomHalfNavigationBox_;
		GtkWidget * topHalfVBox_;

		int ser_no;
		GtkWidget * serialPage_;
		bool flagSerialPageRemoved_;
		Session * this_users_session;
		string sess_id ;

		void display();
		void changeLanguage();
		void setLanguage(const std::string lang);
		void ConstructThankYouPage();
		const char * software_info();
		void CreateBottomHalf();
		void CreateTopHalf();
		void DestroyPreviousWidgets ();
	public:
		void DoQuestionnaire() ;
		void ValidateSerialNo();
		//virtual ~GtkQuestionnaireApplication();
		void get_serial_no_gtk (int (* p_return_ser_no) (int));
		void ConstructQuestionForm(
			AbstractQuestion *q
			//, Session * this_users_session
			);
	void PrepareSingleCodedStubDisplay (NamedStubQuestion * q);
	void PrepareMultiCodedStubDisplay (NamedStubQuestion * q);

	vector<string> PrepareQuestionText(AbstractQuestion *q);
	void DisplayQuestionTextView (const vector <string> & qno_and_qtxt);
	private:
		GtkQuestionnaireApplication& operator= (const GtkQuestionnaireApplication&);
		GtkQuestionnaireApplication (const GtkQuestionnaireApplication&);
};




char get_end_of_question_response()
{
	return 'Z'; // an invalid character
}

void print_save_partial_data_message_success ()
{
	cout << "saved partial data " << endl;
}

GtkQuestionnaireApplication * gtkQuestionnaireApplication = 0;
int32_t prompt_user_for_serial_no(int (* p_return_ser_no) (int))
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "Enter a serial no, 0 to exit" << endl;
#if 0
	int serial_no;
	cin >> serial_no;

	if (serial_no == 0) {
		cout << "exiting ..." << endl;
		exit(0);
	} else {
		p_return_ser_no (serial_no);
	}
	// unreachable code 
#endif /*  0 */
	
	gtkQuestionnaireApplication->get_serial_no_gtk(p_return_ser_no);
	cerr 	<< __PRETTY_FUNCTION__ << ","
		<< __FILE__ << ","
		<< __LINE__ << ","
		<< " fix this return 100 - return the serial no from the UI" 
		<< endl;

	return  100;
}


GtkQuestionnaireApplication::GtkQuestionnaireApplication (int argc, char * argv[]//, int (* p_return_ser_no) (int)
		)
	:  window(0), top_half(0), bottom_half(0),
	   //return_ser_no (p_return_ser_no),
	   last_question_visited (0), jump_to_question (0),
	   wt_debug_(0), wt_questionText_(0), le_data_(0), wt_lastQuestionVisited_(0),
	   wt_cb_rb_container_(0), wt_rb_container_(0), questionTextLabel_(0),
	   vec_rb(), rbData_(), vec_cb(), map_cb_code_index(), languageSelects_(),
	   //vbox(0), 
	   hbox(0), serialNoEntry_(0), check(0), rb(0), next_button(0),
	   viewPort_(0), currentForm_(0), formContainer_(0), gtkRadioButtonGroup_(0),
	   bottomHalfVBox_(0), bottomHalfNavigationBox_(0), topHalfVBox_(0),
	   ser_no(-1), serialPage_(0),
	   flagSerialPageRemoved_(false), this_users_session(0), sess_id()

{
	SetupGTK (argc, argv);
	cout << "exit constructor: " << __PRETTY_FUNCTION__ << endl;
}


void GtkQuestionnaireApplication::CreateBottomHalf()
{
	//GtkWidget *scrolled_window;
	//GtkWidget *view;
	//GtkTextBuffer *buffer;
	//view = gtk_text_view_new ();
	//buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
	bottom_half = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (bottom_half),
		GTK_POLICY_AUTOMATIC,
		GTK_POLICY_AUTOMATIC);
	//gtk_container_add (GTK_CONTAINER (scrolled_window), view);
	//bottomHalfVBox_ = gtk_vbox_new (FALSE, 0);
	//bottomHalfVBox_ = gtk_vbox_new (FALSE, 0);
	bottomHalfVBox_ = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (bottom_half), bottomHalfVBox_);
	gtk_widget_show (bottomHalfVBox_);
	//insert_text (buffer);
	//gtk_widget_show_all (bottom_half);
	//return scrolled_window;
	//bottomHalfNavigationBox_ = gtk_vbox_new (FALSE, 0);
	bottomHalfNavigationBox_ = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (bottom_half), bottomHalfNavigationBox_);
	gtk_widget_show (bottomHalfNavigationBox_);
	gtk_widget_show (bottom_half);
}

void GtkQuestionnaireApplication::CreateTopHalf()
{
	cout << __PRETTY_FUNCTION__ << endl;
	//GtkWidget * scrolled_window = gtk_scrolled_window_new (NULL, NULL);

	/* GtkWidget *  */ top_half = gtk_scrolled_window_new (NULL, NULL);
	cout << "GTK_IS_SCROLLED_WINDOW (top_half) :"<< GTK_IS_SCROLLED_WINDOW (top_half) << endl;
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (top_half),
		GTK_POLICY_AUTOMATIC,
		GTK_POLICY_AUTOMATIC);
	gtk_widget_show (top_half);
	//topHalfVBox_ = gtk_vbox_new (FALSE, 0);
	topHalfVBox_ = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_show (topHalfVBox_);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (top_half), topHalfVBox_);

	GtkWidget * label = gtk_label_new( "Hello, World");
	gtk_widget_show (label);
	
	gtk_box_pack_start (GTK_BOX (topHalfVBox_), label, TRUE, TRUE, 0);
	//return scrolled_window;
}

void GtkQuestionnaireApplication::SetupGTK (int argc, char * argv[])
{
	cout << __PRETTY_FUNCTION__ << endl;
	questionTextLabel_ = 0;
	next_button = 0;
	le_data_ = 0;
	gtk_init (&argc, &argv);
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Paned Windows");
	/* Sets the border width of the window. */
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	gtk_widget_set_size_request (GTK_WIDGET (window), 800, 600);
	g_signal_connect (G_OBJECT (window), "delete_event",
		G_CALLBACK (delete_event), NULL);
	/* Here we connect the "destroy" event to a signal handler.
	 * This event occurs when we call gtk_widget_destroy() on the window,
	 * or if we return FALSE in the "delete_event" callback. */
	g_signal_connect (G_OBJECT (window), "destroy",
		G_CALLBACK (destroy), NULL);
	// ============================
	/* create a vpaned widget and add it to our toplevel window */
	GtkWidget * vpaned = gtk_paned_new (GTK_ORIENTATION_VERTICAL);
	gtk_container_add (GTK_CONTAINER (window), vpaned);
	gtk_widget_show (vpaned);
	/* Now create the contents of the two halves of the window */
	/* GtkWidget *   top_half =*/ CreateTopHalf ();
	gtk_paned_add1 (GTK_PANED (vpaned), top_half);
	/*  GtkWidget *   bottom_half =*/ CreateBottomHalf ();
	gtk_paned_add2 (GTK_PANED (vpaned), bottom_half);
	gtk_widget_show (window);
	// ============================

	// Setup the session
	string sess_id = GenerateSessionId();
	this_users_session = new Session();
	strcpy (this_users_session->sid, sess_id.c_str());
	wt_sessions.push_back(this_users_session);
	cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
}


int callback_get_ser_no_from_ui (int p_ser_no);
void setup_ui (int argc, char * argv[] )
{
	cout 	<< "Gtk: Welcome to the simplest possible qscript runtime"
		<< endl;
	setlocale( LC_ALL, "" );
	bindtextdomain( "vegetable", "/usr/share/locale" );
	textdomain( "vegetable" );
	gtkQuestionnaireApplication = new GtkQuestionnaireApplication (argc, argv /* , p_return_ser_no */);
	prompt_user_for_serial_no (callback_get_ser_no_from_ui);

	gtk_main();
}


vector<string> PrepareQuestionText (AbstractQuestion *q)
{
	using std::string;
	using std::stringstream;
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
	question_text << q->textExprVec_[0]->text_;
	result.push_back (question_text.str());
	for (int i=1; i<q->textExprVec_.size(); ++i) {
		//mvwprintw(question_window, 2+i, 1, " %s", textExprVec_[i]->text_.c_str() );
		result.push_back (q->textExprVec_[i]->text_);
	}
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

void PrepareStubs (AbstractQuestion *q)
{

}

void DisplayStubs (AbstractQuestion *q)
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

/* 
typedef void (*callback_get_user_input_t) (callback_ui_input_t callback_ui_input,
			callback_get_user_input_t callback_get_user_input);

struct UserInputParams
{
void (*callback_ui_input) (UserInput * p_user_input);
}; */


/* 
void GetUserInput (void (*callback_ui_input) (UserInput * p_user_input),
		void (*get_user_input) (
			void (*callback_ui_input) (UserInput * p_user_input),
			void (*get_user_input) (
				void (*callback_ui_input) (UserInput * p_user_input),
				)
		) 
	)
 */
typedef void (*callback_ui_input_t) (UserInput * p_user_input);

// this functions job is to take any user input from the interface
// and pass it to the control flow logic decider.
// Any control flow logic that appears here is a mistake in my programming
// and needs to be fixed
void GetUserInput ( 
	void (*callback_ui_input) (UserInput p_user_input, AbstractQuestion * q,
		struct TheQuestionnaire * theQuestionnaire), 
		AbstractQuestion *q, struct TheQuestionnaire * theQuestionnaire)
{
	cout << __PRETTY_FUNCTION__ << endl;
	if (q->no_mpn == 1) {
		cout << " Question is single answer, please enter only 1 response." << endl;
	} else {
		cout << " Question accepts multiple answers." << endl;
	}
	string current_response;
	cout << "Enter Data>" << endl;
	getline(cin, current_response);
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
				callback_ui_input (user_input, q, theQuestionnaire);
				GetUserInput (callback_ui_input, q, theQuestionnaire);
				cout << "callback_ui_input has returned after UserSavedData" << endl;
			} else {
				cout << "reached here: " 
					<< __PRETTY_FUNCTION__ << endl;
				callback_ui_input (user_input, q, theQuestionnaire);
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
			GetUserInput (callback_ui_input, q, theQuestionnaire);
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
		GetUserInput (callback_ui_input, q, theQuestionnaire);
	}
}

void DisplayCurrentAnswers (AbstractQuestion * q)
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

void stdout_eval (AbstractQuestion * q, struct TheQuestionnaire * theQuestionnaire,
	void (*callback_ui_input) (UserInput p_user_input, AbstractQuestion * q, struct TheQuestionnaire * theQuestionnaire))
{
	cout << __PRETTY_FUNCTION__ << endl;
	ClearPreviousView ();
	vector <string> qno_and_qtxt = PrepareQuestionText (q);
	DisplayQuestionTextView (qno_and_qtxt);
	PrepareStubs (q);
	DisplayStubs (q);
	DisplayCurrentAnswers (q);

	gtkQuestionnaireApplication->ConstructQuestionForm (q 
			//, gtkQuestionnaireApplication->this_users_session
			);

	//GetUserInput (callback_ui_input, q, theQuestionnaire);
}

string GenerateSessionId()
{
	srand(time(0));
	char buffer[50];
	sprintf (buffer, "%010d%010d%010d%010d", rand(), rand(), rand(), rand());
	return string(buffer);
}


gint delete_event (GtkWidget *widget, GdkEvent *event, gpointer data)
{
	/*
	 *
	 *
	 *
	 *
	If you return FALSE in the "delete_event" signal handler,
	GTK will emit the "destroy" signal. Returning TRUE means
	you dont want the window to be destroyed.
	This is useful for popping up are you sure you want to quit?
	type dialogs. */
	g_print ("delete event occurred\n");
	/* Change TRUE to FALSE and the main window will be destroyed with
	 * a "delete_event". */
	return FALSE;
}


/* Anothe callback */
void destroy( GtkWidget *widget, gpointer data )
{
	gtk_main_quit ();
}


void serial_no_enter_callback (GtkWidget *widget, GtkQuestionnaireApplication * qapp)
{
	//const gchar *entry_text;
	//entry_text = gtk_entry_get_text (GTK_ENTRY (widget));

	//qapp->ValidateSerialNo ();
	//theQuestionnaire.eval();
	//
	int l_ser_no = -1;
	const gchar * entry_text = gtk_entry_get_text (GTK_ENTRY (widget));
	printf("Entry contents: %s\n", entry_text);
	string narrow_text (entry_text);
	if (narrow_text.length() == 0 || narrow_text.length() > 7)
	{
		//le_data_->setText("You have entered a very long serial number");
	}
	else
	{
		l_ser_no = strtol (narrow_text.c_str(), 0, 10);
		if (l_ser_no > 0)
		{
			cerr << __PRETTY_FUNCTION__ << " hide serialNoEntry_ later" << endl;
			//gtk_widget_hide (serialNoEntry_);
			qapp->return_ser_no(l_ser_no);
		}
	}
}



void GtkQuestionnaireApplication::get_serial_no_gtk (int (* p_return_ser_no) (int))
{
	cout << __PRETTY_FUNCTION__ << endl;

	// convert below assignment to a setter operation
	return_ser_no =  p_return_ser_no;

	//printf ("called: %s\n", __PRETTY_FUNCTION__);
	gint tmp_pos;

	//vbox = gtk_vbox_new (FALSE, 0);
	//vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);

	//gtk_widget_show (vbox);

	//gtk_container_add (GTK_CONTAINER (top_half), vbox);
	//gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (top_half), vbox);
	//gtk_container_add (GTK_SCROLLED_WINDOW (top_half), vbox);

	if (serialNoEntry_ == 0) {

		serialNoEntry_ = gtk_entry_new ();
		gtk_entry_set_max_length (GTK_ENTRY (serialNoEntry_), 50);
		g_signal_connect (G_OBJECT (serialNoEntry_), "activate",
			G_CALLBACK (serial_no_enter_callback),
			(gpointer) this);
		gtk_entry_set_text (GTK_ENTRY (serialNoEntry_), "<Enter Serial No Here>");
		gtk_box_pack_start (GTK_BOX (topHalfVBox_), serialNoEntry_, TRUE, TRUE, 0);
	}

	/* 
	 * nxd: commented out on 16-feb-2013
	tmp_pos = GTK_ENTRY (serialNoEntry_)-> text_length;
	gtk_editable_insert_text (GTK_EDITABLE (serialNoEntry_), "", -1, &tmp_pos);
	gtk_editable_select_region (GTK_EDITABLE (serialNoEntry_),
		0, GTK_ENTRY (serialNoEntry_)-> text_length);
	*/

	gtk_widget_show (serialNoEntry_);

}


void GtkQuestionnaireApplication::DestroyPreviousWidgets ()
{
	cerr << "Enter: " << __PRETTY_FUNCTION__ << endl;
	if (questionTextLabel_)
	{
		cerr << "destroying questionTextLabel_: " << questionTextLabel_ << endl;
		gtk_widget_destroy (questionTextLabel_) ;
		questionTextLabel_ = 0;
	}
	cerr << "reached here " << endl;
	if (vec_rb.size() > 0)
	{
		// put clear / destroy previous widget code here
		for (int i=0; i<vec_rb.size(); ++i)
		{
			gtk_widget_destroy (vec_rb[i]);
		}
		vec_rb.clear();
	}
	if (vec_cb.size() > 0)
	{
		// put clear / destroy previous widget code here
		for (int i=0; i<vec_cb.size(); ++i)
		{
			gtk_widget_destroy (vec_cb[i]);
		}
		vec_cb.clear();
	}
	if (next_button)
	{
		gtk_widget_destroy (next_button);
		next_button = 0;
	}
	if (le_data_)
	{
		gtk_widget_destroy (le_data_);
		le_data_ = 0;
	}
	cerr << "Exit: " << __PRETTY_FUNCTION__ << endl;
}


void line_edit_callback (GtkWidget *widget, GtkQuestionnaireApplication * qapp)
{
	const gchar *entry_text;
	entry_text = gtk_entry_get_text (GTK_ENTRY (widget));
	printf("Entry contents: %s\n", entry_text);
}

void next_button_callback (GtkWidget *widget, GtkQuestionnaireApplication * qapp)
{
	//g_print ("Next button was pressed", (char *) data);
	// nxd: 16-feb-2013 - comment it out for now 
	//qapp->DoQuestionnaire();
	//question_eval_loop_gtk (qnre_mode,
	//	qnre_navigation_mode, last_question_visited,
	//	jump_to_question, theQuestionnaire);
	//
	//
	qapp->handleDataInput();
}

void toggle_rb_button_event (GtkWidget *widget, GtkRadioButtonData * rb_data)
{
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
	{
		/* If control reaches here, the toggle button is down */
		rb_data->qApp_->rb_selected_code  = rb_data -> selectedCode_;
	}
	else
	{
		/* If control reaches here, the toggle button is up */
	}
	g_print ("Toggle event occured %d",  rb_data -> selectedCode_);
}

void GtkQuestionnaireApplication::ConstructQuestionForm( AbstractQuestion *q )
{
	cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
	map_cb_code_index.clear();
	vector <string> question_text_vec = PrepareQuestionText (q);
	//gtk_widget_hide( entry);

	DestroyPreviousWidgets ();
	this->DisplayQuestionTextView (question_text_vec);


	if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q))
	{
		if (q->no_mpn==1)
		{
			PrepareSingleCodedStubDisplay(nq);
#if 0
			rb_selected_code = -1;
			rb = gtk_radio_button_new_with_label (NULL, "Dummy - for default unselected - should never display");
			gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), rb, TRUE, TRUE, 0);
			GtkRadioButtonData * rb_data = new GtkRadioButtonData (0, this);
			rbData_.push_back (rb_data);
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (rb), TRUE);
			gtkRadioButtonGroup_ = gtk_radio_button_get_group (GTK_RADIO_BUTTON (rb));
#endif /*  0 */
		} else {
			PrepareMultiCodedStubDisplay (nq);
		}
#if 0
		vector<stub_pair> & vec= (nq->nr_ptr->stubs);
		bool rb_group_was_created = false;
		for (int i=0; i<vec.size(); ++i)
		{
			stringstream named_range_key;
			named_range_key << nq->nr_ptr->name << "_" << i;
			if (q->no_mpn == 1 && vec[i].mask)
			{
				//WRadioButton * wt_rb = new WRadioButton( vec[i].stub_text, wt_cb_rb_container_);
				//WRadioButton * wt_rb = new WRadioButton(WString::tr(named_range_key.str().c_str()), wt_cb_rb_container_);
				//wt_rb_container_->addButton(wt_rb, vec[i].code);
				//new WBreak(wt_cb_rb_container_);
				//if (!rb_group_was_created) {
				rb = gtk_radio_button_new_with_label (gtkRadioButtonGroup_, vec[i].stub_text.c_str());
				gtkRadioButtonGroup_ = gtk_radio_button_get_group (GTK_RADIO_BUTTON (rb));
				gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), rb, TRUE, TRUE, 0);
				GtkRadioButtonData * rb_data = new GtkRadioButtonData (vec[i].code, this);
				rbData_.push_back (rb_data);
				g_signal_connect (G_OBJECT (rb), "toggled",
					G_CALLBACK (toggle_rb_button_event), (gpointer) rb_data);
				gtk_widget_show (rb);
				//gtkRadioButtonGroup_ = gtk_radio_button_get_group (GTK_RADIO_BUTTON (rb));
				//rb_group_was_created = true;
				//} else {
				//	rb = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON(vec_rb[vec_rb.size()-1]), vec[i].stub_text.c_str());
				//	GtkRadioButtonData * rb_data = new GtkRadioButtonData (vec[i].code, this);
				//	rbData_.push_back (rb_data);
				//	g_signal_connect (G_OBJECT (rb), "toggled",
				//		G_CALLBACK (toggle_rb_button_event), (gpointer) rb_data);
				//	gtk_widget_show (rb);
				//	gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), rb, TRUE, TRUE, 0);
				//}
				vec_rb.push_back (rb);
			}
			if (q->no_mpn>1 && vec[i].mask)
			{
				//WCheckBox * wt_cb = new WCheckBox ( vec[i].stub_text, wt_cb_rb_container_);
				//WCheckBox * wt_cb = new WCheckBox (WString::tr(named_range_key.str().c_str()), wt_cb_rb_container_);
				//vec_cb.push_back(wt_cb);
				//cout << " adding code: " << vec[i].code << " to map_cb_code_index" ;
				GtkWidget * cb = gtk_check_button_new_with_label (vec[i].stub_text.c_str());
				GtkRadioButtonData * cb_data = new GtkRadioButtonData (vec[i].code, this);
				rbData_.push_back (cb_data);
				g_signal_connect (G_OBJECT (cb), "toggled",
					G_CALLBACK (toggle_rb_button_event), (gpointer) cb_data);
				gtk_widget_show (cb);
				gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), cb, TRUE, TRUE, 0);
				//!! Warning - the 2 statements below have to be in this order
				// and are not interchangeable
				vec_cb.push_back (cb);
				map_cb_code_index[vec_cb.size()-1] = vec[i].code;
			}
		}
		//new_form->addWidget(wt_cb_rb_container_);
#endif /* 0 */
	}
	else
	{
		le_data_ = gtk_entry_new ();
		gtk_entry_set_max_length (GTK_ENTRY (le_data_), 50);
		g_signal_connect (G_OBJECT (le_data_), "activate", G_CALLBACK (line_edit_callback), (gpointer) this);
		gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), le_data_, TRUE, TRUE, 0);
		gtk_widget_show (le_data_);
	}
	next_button = gtk_button_new_with_label ("Next");
	gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), next_button, TRUE, TRUE, 0);
	gtk_widget_show (next_button);

	/* When the button is clicked, we call the "callback" function
	 * with a pointer to "button 1" as its argument */
	last_question_visited = q;
	g_signal_connect (G_OBJECT (next_button), "clicked",
		G_CALLBACK (next_button_callback), (gpointer) this);
}


void GtkQuestionnaireApplication::DisplayQuestionTextView (const vector <string> & qno_and_qtxt)
{
	stringstream question_text;
	for (int i=0; i < qno_and_qtxt.size(); ++i) {
		question_text << qno_and_qtxt[i];
	}
	//question_text << "dummy - to check for core dump";
	questionTextLabel_ = gtk_label_new (question_text.str().c_str());
	//gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (top_half), questionTextLabel_);
	cout << "topHalfVBox_: " << topHalfVBox_ << endl;
	gtk_box_pack_start (GTK_BOX (topHalfVBox_), questionTextLabel_, TRUE, TRUE, 0);
	gtk_widget_show (questionTextLabel_);
	gtk_widget_show (top_half);
}


void GtkQuestionnaireApplication::PrepareSingleCodedStubDisplay (NamedStubQuestion * nq)
{
	rb_selected_code = -1;
	rb = gtk_radio_button_new_with_label (NULL, "Dummy - for default unselected - should never display");
	gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), rb, TRUE, TRUE, 0);
	GtkRadioButtonData * rb_data = new GtkRadioButtonData (0, this);
	rbData_.push_back (rb_data);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (rb), TRUE);
	gtkRadioButtonGroup_ = gtk_radio_button_get_group (GTK_RADIO_BUTTON (rb));
	//g_signal_connect (G_OBJECT (rb), "toggled",
	//
	vector<stub_pair> & vec= (nq->nr_ptr->stubs);
	bool rb_group_was_created = false;
	for (int32_t i = 0; i < vec.size(); ++i) {
		stringstream named_range_key;
		named_range_key << nq->nr_ptr->name << "_" << i;
		if (vec[i].mask) {
			//WRadioButton * wt_rb = new WRadioButton( vec[i].stub_text, wt_cb_rb_container_);
			//WRadioButton * wt_rb = new WRadioButton(WString::tr(named_range_key.str().c_str()), wt_cb_rb_container_);
			//wt_rb_container_->addButton(wt_rb, vec[i].code);
			//new WBreak(wt_cb_rb_container_);
			//if (!rb_group_was_created) {
			rb = gtk_radio_button_new_with_label (gtkRadioButtonGroup_, vec[i].stub_text.c_str());
			gtkRadioButtonGroup_ = gtk_radio_button_get_group (GTK_RADIO_BUTTON (rb));
			gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), rb, TRUE, TRUE, 0);
			GtkRadioButtonData * rb_data = new GtkRadioButtonData (vec[i].code, this);
			rbData_.push_back (rb_data);
			g_signal_connect (G_OBJECT (rb), "toggled",
				G_CALLBACK (toggle_rb_button_event), (gpointer) rb_data);
			gtk_widget_show (rb);
			//gtkRadioButtonGroup_ = gtk_radio_button_get_group (GTK_RADIO_BUTTON (rb));
			//rb_group_was_created = true;
			//} else {
			//	rb = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON(vec_rb[vec_rb.size()-1]), vec[i].stub_text.c_str());
			//	GtkRadioButtonData * rb_data = new GtkRadioButtonData (vec[i].code, this);
			//	rbData_.push_back (rb_data);
			//	g_signal_connect (G_OBJECT (rb), "toggled",
			//		G_CALLBACK (toggle_rb_button_event), (gpointer) rb_data);
			//	gtk_widget_show (rb);
			//	gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), rb, TRUE, TRUE, 0);
			//}
			vec_rb.push_back (rb);
		}
	}
}


void GtkQuestionnaireApplication::PrepareMultiCodedStubDisplay (NamedStubQuestion * nq)
{
	vector<stub_pair> & vec= (nq->nr_ptr->stubs);
	for (int i=0; i<vec.size(); ++i) {
		stringstream named_range_key;
		named_range_key << nq->nr_ptr->name << "_" << i;
		if (vec[i].mask) {
			GtkWidget * cb = gtk_check_button_new_with_label (vec[i].stub_text.c_str());
			GtkRadioButtonData * cb_data = new GtkRadioButtonData (vec[i].code, this);
			rbData_.push_back (cb_data);
			g_signal_connect (G_OBJECT (cb), "toggled",
				G_CALLBACK (toggle_rb_button_event), (gpointer) cb_data);
			gtk_widget_show (cb);
			gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), cb, TRUE, TRUE, 0);
			//!! Warning - the 2 statements below have to be in this order
			// and are not interchangeable
			vec_cb.push_back (cb);
			map_cb_code_index[vec_cb.size()-1] = vec[i].code;
		}
	}
}


vector<string> GtkQuestionnaireApplication::PrepareQuestionText(AbstractQuestion *q)
{
	vector <string> result;
	string question_text;
	stringstream part_mesg_id;
	stringstream question_no;
	question_no << q->questionName_;
	part_mesg_id << q->questionName_;
	for (int i=0; i<q->loop_index_values.size(); ++i)
	{
		part_mesg_id << "_" << q->loop_index_values[i];
		question_no << q->loop_index_values[i] << ".";
	}
	result.push_back (question_no.str());

	//WText * wt_questionNo_ = new WText(part_mesg_id.str().c_str(), new_form);
	for (int i=0; i<q->textExprVec_.size(); ++i)
	{
		//question_text += "<p>";
		if (q->textExprVec_[i]->teType_ == TextExpression::simple_text_type)
		{
			stringstream mesg_id;
			mesg_id << part_mesg_id.str() << "_" << i;
			// prev - commented  out on 16-feb-2013
			// question_text += string (gettext(q->textExprVec_[0]->text_.c_str()));
			result.push_back ( string (gettext(q->textExprVec_[0]->text_.c_str())) );
		}
		else if (q->textExprVec_[i]->teType_ == TextExpression::named_attribute_type)
		{
			//stringstream named_attribute_key;
			//named_attribute_key << q->textExprVec_[i]->naPtr_->name;
			//named_attribute_key << "_" << q->textExprVec_[i]->naIndex_;
			//question_text += string(gettext(named_attribute_key.str().c_str()));
			// prev - commented  out on 16-feb-2013
			// question_text += string(" FIXME : BUG that I didnt notice. Need to create a map of <string, named_attribute_list>   to solve this problem, where the first string is the name of the named_attribute_list");
			result.push_back(string(" FIXME : BUG that I didnt notice. Need to create a map of <string, named_attribute_list>   to solve this problem, where the first string is the name of the named_attribute_list"));

		}
		else if (q->textExprVec_[i]->teType_ == TextExpression::question_type)
		{
			if (q->textExprVec_[i]->codeIndex_ != -1)
			{
				//question_text += q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers(q->textExprVec_[i]->codeIndex_);
				result.push_back (q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers(q->textExprVec_[i]->codeIndex_));
			}
			else
			{
				//question_text +=  q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers();
				result.push_back (q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers());
			}
		}
		//question_text += "</p>";
	}

	return result;
}

void GtkQuestionnaireApplication::handleDataInput()
{
	if (NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion *>(last_question_visited))
	{
#if 0
		AbstractQuestion * last_question_served = last_question_visited;
		vector<int32_t> data;
		bool isAnswered = false;
		cout << "returned back data from question: " << nq->questionName_ << endl;
		if (last_question_served->no_mpn == 1)
		{
			if (rb_selected_code != -1)
			{
				isAnswered = true;
				//int code = wt_rb_container_->checkedId();
				cout << "no_mpn == 1, code: " << rb_selected_code << endl;
				data.push_back(rb_selected_code);
			}
			else
			{
				isAnswered = false;
			}
		}
		else
		{
			cout << " vec_cb.size(): " << vec_cb.size() << "no_mpn > 1" << endl;
			for (int i = 0; i < vec_cb.size(); ++i)
			{
				//if (vec_cb[i]->checkState() == Wt::Checked)
				//{
				//	int code = map_cb_code_index[i];
				//	data.push_back(code);
				//	cout << "vec_cb[" << i << "] is checked,   code: " << code << endl;
				//	isAnswered = true;
				//}
				if (gtk_toggle_button_get_active ((GtkToggleButton *) vec_cb[i]) )
				{
					int code = map_cb_code_index[i];
					data.push_back(code);
					isAnswered = true;
					cout << "button is toggled: " << code << endl;
				}
			}
		}
		if (isAnswered)
		{
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
#endif 
	}
	else
	{

		const gchar *entry_text = gtk_entry_get_text (GTK_ENTRY (le_data_));
		string last_question_served_response (entry_text);
		cout << "RangeQuestion: entry_text: " << entry_text << endl;
#if 0
		AbstractQuestion * last_question_served = last_question_visited;
		if (/* last_question_visited_str != "" &&  */ last_question_served_response != "" && last_question_served->no_mpn==1)
		{
			UserNavigation user_nav=NOT_SET;
			user_response::UserResponseType user_resp=user_response::NotSet;
			vector<int32_t> data;
			bool parse_success = verify_web_data (last_question_served_response, user_nav, user_resp, &data);
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
			else
			{
				ConstructQuestionForm(last_question_served, this_users_session);
				return;
			}
		}
		else if (/* last_question_visited_str != "" &&  */ last_question_served_response != "" && last_question_served->no_mpn > 1)
		{
			//string utf8_response = le_data_->text().toUTF8();
			if (last_question_served_response != "")
			{
				stringstream file_name_str;
				file_name_str << last_question_served->questionName_ << "."
					<< jno << "_" << ser_no << ".dat";

				fstream open_end_resp(file_name_str.str().c_str(), ios_base::out|ios_base::ate);
				open_end_resp << last_question_served_response << endl;
				last_question_served->input_data.insert(96);
				last_question_served->isAnswered_ = true;
			}
			else
			{
				ConstructQuestionForm(last_question_served, this_users_session);
				return;
			}
		}
#endif /*  0 */
	}


}
