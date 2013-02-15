/*
 * =====================================================================================
 *
 *       Filename:  question_gtk2_runtime.C
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 14 February 2013 10:20:41  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <locale.h>
#include <libintl.h>
#include <gtk/gtk.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "question.h"

// need to fix this later
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
		GtkQuestionnaireApplication (int argc, char * argv[], int (* p_return_ser_no) (int) );
		void SetupGTK (int argc, char * argv[]);
		int (*return_ser_no) (int p_ser_no);
		int rb_selected_code;

		// This may have to be moved to a better location than here
		//  - for example struct TheQuestionnaire
		AbstractQuestion * last_question_visited;
		AbstractQuestion * jump_to_question;
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

		GtkWidget *vbox , *hbox ;
		GtkWidget * entry ;
		//GtkWidget * button ;
		GtkWidget * check ;
		GtkWidget * rb ;
		GtkWidget * next_button ;

		GtkWidget * viewPort_;
		GtkWidget * currentForm_;
		GtkWidget * formContainer_;
		GSList * gtkRadioButtonGroup_;

		GtkWidget * bottomHalfVBox_, * bottomHalfNavigationBox_;

		int ser_no;
		GtkWidget * serialPage_;
		bool flagSerialPageRemoved_;
		Session * this_users_session;
		string sess_id ;

		void display();
		void changeLanguage();
		void setLanguage(const std::string lang);
		void ConstructQuestionForm(
			AbstractQuestion *q, Session * this_users_session);
		void ConstructThankYouPage();
		const char * software_info();
		void CreateBottomHalf();
		void DestroyPreviousWidgets ();
	public:
		void DoQuestionnaire() ;
		void ValidateSerialNo();
		//virtual ~GtkQuestionnaireApplication();
		void get_serial_no_gtk ();
	private:
		GtkQuestionnaireApplication& operator= (const GtkQuestionnaireApplication&);
		GtkQuestionnaireApplication (const GtkQuestionnaireApplication&);
};

void GtkQuestionnaireApplication::DestroyPreviousWidgets ()
{
	cout << __PRETTY_FUNCTION__ << endl;
	if (questionTextLabel_)
	{
		gtk_widget_destroy (questionTextLabel_) ;
		questionTextLabel_ = 0;
	}
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


GtkWidget * CreateTopHalf()
{
	GtkWidget * scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
		GTK_POLICY_AUTOMATIC,
		GTK_POLICY_AUTOMATIC);
	return scrolled_window;
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
	bottomHalfVBox_ = gtk_vbox_new (FALSE, 0);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (bottom_half), bottomHalfVBox_);
	gtk_widget_show (bottomHalfVBox_);
	//insert_text (buffer);
	//gtk_widget_show_all (bottom_half);
	//return scrolled_window;
	bottomHalfNavigationBox_ = gtk_vbox_new (FALSE, 0);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (bottom_half), bottomHalfNavigationBox_);
	gtk_widget_show (bottomHalfNavigationBox_);
}


GtkQuestionnaireApplication::GtkQuestionnaireApplication (int argc, char * argv[], int (* p_return_ser_no) (int))
	:  window(0), top_half(0), bottom_half(0),
	   return_ser_no (p_return_ser_no),
	   last_question_visited (0), jump_to_question (0),
	   wt_debug_(0), wt_questionText_(0), le_data_(0), wt_lastQuestionVisited_(0),
	   wt_cb_rb_container_(0), wt_rb_container_(0), questionTextLabel_(0),
	   vec_rb(), rbData_(), vec_cb(), map_cb_code_index(), languageSelects_(),
	   vbox(0), hbox(0), entry(0), check(0), rb(0), next_button(0),
	   viewPort_(0), currentForm_(0), formContainer_(0), gtkRadioButtonGroup_(0),
	   bottomHalfVBox_(0), bottomHalfNavigationBox_(0), ser_no(-1), serialPage_(0),
	   flagSerialPageRemoved_(false), this_users_session(0), sess_id()

{
	SetupGTK (argc, argv);
}


void GtkQuestionnaireApplication::SetupGTK (int argc, char * argv[])
{
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
	GtkWidget * vpaned = gtk_vpaned_new ();
	gtk_container_add (GTK_CONTAINER (window), vpaned);
	gtk_widget_show (vpaned);
	/* Now create the contents of the two halves of the window */
	/* GtkWidget *  */ top_half = CreateTopHalf ();
	get_serial_no_gtk();
	gtk_paned_add1 (GTK_PANED (vpaned), top_half);
	gtk_widget_show (top_half);
	///*  GtkWidget *   bottom_half =*/ CreateBottomHalf ();
	//gtk_paned_add2 (GTK_PANED (vpaned), bottom_half);
	//gtk_widget_show (bottom_half);
	gtk_widget_show (window);
	// ============================

	// Setup the session
	string sess_id = GenerateSessionId();
	this_users_session = new Session();
	strcpy (this_users_session->sid, sess_id.c_str());
	wt_sessions.push_back(this_users_session);
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
			qapp->return_ser_no(l_ser_no);
		}
	}
}


void line_edit_callback (GtkWidget *widget, GtkQuestionnaireApplication * qapp)
{
	const gchar *entry_text;
	entry_text = gtk_entry_get_text (GTK_ENTRY (widget));
	printf("Entry contents: %s\n", entry_text);

	//theQuestionnaire.eval();
}


void GtkQuestionnaireApplication::get_serial_no_gtk ()
{
	printf ("called: %s\n", __PRETTY_FUNCTION__);
	gint tmp_pos;

	vbox = gtk_vbox_new (FALSE, 0);
	//gtk_container_add (GTK_CONTAINER (top_half), vbox);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (top_half), vbox);
	gtk_widget_show (vbox);

	entry = gtk_entry_new ();
	gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
	g_signal_connect (G_OBJECT (entry), "activate",
		G_CALLBACK (serial_no_enter_callback),
		(gpointer) this);
	gtk_entry_set_text (GTK_ENTRY (entry), "<Enter Serial No Here>");
	tmp_pos = GTK_ENTRY (entry)-> text_length;
	gtk_editable_insert_text (GTK_EDITABLE (entry), "", -1, &tmp_pos);
	gtk_editable_select_region (GTK_EDITABLE (entry),
		0, GTK_ENTRY (entry)-> text_length);
	gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
	gtk_widget_show (entry);

}


#if 0
void GtkQuestionnaireApplication::ValidateSerialNo()
{
	int l_ser_no = -1;
	const gchar * entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
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
			ser_no = l_ser_no;
			//this_users_session->questionnaire->ser_no = l_ser_no;
			int exists = check_if_reg_file_exists (jno, ser_no);
			cout << "checking if serial no : " << ser_no
				<< ", jno: " << jno << " exists: " << exists << endl;

			if(exists == 1)
			{
				map <string, question_disk_data*>  qdd_map;
				load_data(jno, ser_no, &qdd_map);
				merge_disk_data_into_questions2(qscript_stdout,
					this_users_session->questionnaire->last_question_answered,
					this_users_session->questionnaire->last_question_visited,
					this_users_session->questionnaire->question_list,
					&qdd_map);
				for (map<string, question_disk_data*>:: iterator it
					= qdd_map.begin();
					it != qdd_map.end();
					++it)
				{
					delete it->second;
				}
			}

			/*  GtkWidget *   bottom_half =*/ CreateBottomHalf ();
			gtk_paned_add2 (GTK_PANED (vpaned), bottom_half);
			gtk_widget_show (bottom_half);
			// nxd : commented out below - 15-feb-2013
			//DoQuestionnaire();
		}
		else
		{
			//le_data_->setText("You have entered a  negative number");
		}
	}
}
#endif /*  0 */


string GenerateSessionId()
{
	srand(time(0));
	char buffer[50];
	sprintf (buffer, "%010d%010d%010d%010d", rand(), rand(), rand(), rand());
	return string(buffer);
}


#if 1
bool verify_web_data (std::string p_question_data,
UserNavigation p_user_navigation,
user_response::UserResponseType p_the_user_response,
std::vector<int> * data_ptr);

void GtkQuestionnaireApplication::DoQuestionnaire()
{
	//if (!wt_questionText_) {
	//	wt_questionText_ = new WText(root());
	//}
	cout << "Data for ser_no: " << ser_no << endl;
	for(int32_t i = 0; i < this_users_session->questionnaire->question_list.size(); ++i)
	{
		cout << this_users_session->questionnaire->question_list[i]->questionName_;
		for( set<int32_t>::iterator iter = this_users_session->questionnaire->question_list[i]->input_data.begin();
			iter != this_users_session->questionnaire->question_list[i]->input_data.end(); ++iter)
		{
			cout << " " << *iter;
		}
		cout << "\n";
	}
	static int counter = 0;
	stringstream s;
	s << "reached DoQuestionnaire: " << counter++;
	//wt_debug_->setText(s.str());
	UserNavigation qnre_navigation_mode = NAVIGATE_NEXT;
	//string display_text = string("Session Id:") + sess_id;
	//wt_questionText_->setText(display_text);
	// put this code later
	string err_mesg, re_arranged_buffer;
	int32_t pos_1st_invalid_data;
	if (this_users_session->last_question_served)
		s << "last_question_served: " << this_users_session->last_question_served->questionName_ ;
	cout << s.str() << endl;
	//wt_debug_->setText(s.str());
	if (this_users_session->last_question_served)
	{
		if (NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion *>(this_users_session->last_question_served))
		{
			AbstractQuestion * last_question_served = this_users_session->last_question_served;
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
		}
		else
		{

			const gchar *entry_text = gtk_entry_get_text (GTK_ENTRY (le_data_));
			string last_question_served_response (entry_text);
			AbstractQuestion * last_question_served = this_users_session->last_question_served;
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
		}
	}
	{
		TheQuestionnaire * qnre = this_users_session->questionnaire;
		qnre->write_data_to_disk(qnre->question_list, qnre->jno, qnre->ser_no);
	}
	AbstractQuestion * q =
		this_users_session->questionnaire->eval2(
		qnre_navigation_mode, last_question_visited, jump_to_question);
	this_users_session->last_question_served = q;
	if (q)
	{
		ConstructQuestionForm(q, this_users_session);
	}
	else
	{
		//TheQuestionnaire * qnre = this_users_session->questionnaire;
		//qnre->write_data_to_disk(qnre->question_list, qnre->jno, qnre->ser_no);
		//ConstructThankYouPage();
		cout << "End of qnre" << endl;
	}
}



void next_button_callback (GtkWidget *widget, GtkQuestionnaireApplication * qapp)
{
	//g_print ("Next button was pressed", (char *) data);
	qapp->DoQuestionnaire();
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


#endif /*  0 */
void GtkQuestionnaireApplication::ConstructQuestionForm(
AbstractQuestion *q, Session * this_users_session)
{
	map_cb_code_index.clear();
	//WContainerWidget * new_form = new WContainerWidget();
	//vec_rb.clear();				 // memory leak introduced here? no it seems
	//vec_cb.clear();				 // memory leak introduced here? no it seems
	//map_cb_code_index.clear();

	//wt_questionText_ = new WText();
	//wt_questionText_->setText(q->textExprVec_[0]->text_);
	string question_text;
	stringstream part_mesg_id;
	//WString question_text;
	part_mesg_id << q->questionName_;
	for (int i=0; i<q->loop_index_values.size(); ++i)
	{
		part_mesg_id << "_" << q->loop_index_values[i];
	}
	//WText * wt_questionNo_ = new WText(part_mesg_id.str().c_str(), new_form);
	for (int i=0; i<q->textExprVec_.size(); ++i)
	{
		//question_text += "<p>";
		if (q->textExprVec_[i]->teType_ == TextExpression::simple_text_type)
		{
			stringstream mesg_id;
			mesg_id << part_mesg_id.str() << "_" << i;
			//question_text += string (gettext(mesg_id.str().c_str()));
			question_text += string (gettext(q->textExprVec_[0]->text_.c_str()));
		}
		else if (q->textExprVec_[i]->teType_ == TextExpression::named_attribute_type)
		{
			//stringstream named_attribute_key;
			//named_attribute_key << q->textExprVec_[i]->naPtr_->name;
			//named_attribute_key << "_" << q->textExprVec_[i]->naIndex_;
			//question_text += string(gettext(named_attribute_key.str().c_str()));
			question_text += string(" FIXME : BUG that I didnt notice. Need to create a map of <string, named_attribute_list>   to solve this problem, where the first string is the name of the named_attribute_list");
		}
		else if (q->textExprVec_[i]->teType_ == TextExpression::question_type)
		{
			if (q->textExprVec_[i]->codeIndex_ != -1)
			{
				question_text += q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers(q->textExprVec_[i]->codeIndex_);
			}
			else
			{
				question_text += q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers();
			}
		}
		//question_text += "</p>";
	}
	//gtk_widget_hide_all (top_half);
	gtk_widget_hide( entry);

	DestroyPreviousWidgets ();
	questionTextLabel_ = gtk_label_new (question_text.c_str());
	//gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (top_half), questionTextLabel_);
	gtk_box_pack_start (GTK_BOX (vbox), questionTextLabel_, TRUE, TRUE, 0);
	gtk_widget_show(questionTextLabel_);
	gtk_widget_show (top_half);

	if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q))
	{
		//new_form->addWidget(wt_cb_rb_container_ = new WGroupBox());
		if (q->no_mpn==1)
		{
			//wt_rb_container_ = new WButtonGroup(wt_cb_rb_container_);
			rb_selected_code = -1;
			rb = gtk_radio_button_new_with_label (NULL, "Dummy - for default unselected - should never display");
			gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), rb, TRUE, TRUE, 0);
			GtkRadioButtonData * rb_data = new GtkRadioButtonData (0, this);
			rbData_.push_back (rb_data);
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (rb), TRUE);
			gtkRadioButtonGroup_ = gtk_radio_button_get_group (GTK_RADIO_BUTTON (rb));
			//g_signal_connect (G_OBJECT (rb), "toggled",
			//	G_CALLBACK (toggle_rb_button_event), (gpointer) rb_data);
			// purposely dont do a show . Make it default selected
		}
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
	}
	else
	{
		le_data_ = gtk_entry_new ();
		gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
		g_signal_connect (G_OBJECT (le_data_), "activate", G_CALLBACK (line_edit_callback), (gpointer) this);
		gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), le_data_, TRUE, TRUE, 0);
		gtk_widget_show (le_data_);
	}
	next_button = gtk_button_new_with_label ("Next");
	gtk_box_pack_start (GTK_BOX (bottomHalfVBox_), next_button, TRUE, TRUE, 0);
	gtk_widget_show (next_button);

	/* When the button is clicked, we call the "callback" function
	 * with a pointer to "button 1" as its argument */
	g_signal_connect (G_OBJECT (next_button), "clicked",
		G_CALLBACK (next_button_callback), (gpointer) this);
}


// nxd - commented out on 15-feb-2013
//UI_Mode ui_mode = Gtk_Mode ;

#if 0
int main(int argc, char ** argv)
{
	setlocale( LC_ALL, "" );
	bindtextdomain( "vegetable", "/usr/share/locale" );
	textdomain( "vegetable" );
	//process_options(argc, argv);
	if (write_data_file_flag||write_qtm_data_file_flag)
	{
		qtm_data_file_ns::init_exceptions();
		directory_ptr = opendir(".");
		if (! directory_ptr)
		{
			cout << " unable to open . (current directory) for reading\n";
			exit(1);
		}
	}
	//load_languages_available(vec_language);
	bool using_ncurses = true;
	qscript_stdout = fopen(qscript_stdout_fname.c_str(), "w");
	SetupSignalHandler();
	GtkQuestionnaireApplication gtkQuestionnaireApplication (argc, argv);
	//TheQuestionnaire theQuestionnaire;
	//get_serial_no_gtk (theQuestionnaire);
	gtk_main ();

	//return WRun (argc, argv, &createApplication);
}
#endif /* 0 */

GtkQuestionnaireApplication * gtkQuestionnaireApplication = 0;
void setup_ui (int argc, char * argv[], int (* p_return_ser_no) (int))
{
	setlocale( LC_ALL, "" );
	bindtextdomain( "vegetable", "/usr/share/locale" );
	textdomain( "vegetable" );
	//qscript_stdout = fopen(qscript_stdout_fname.c_str(), "w");
	gtkQuestionnaireApplication = new GtkQuestionnaireApplication (argc, argv, p_return_ser_no);
	gtk_main ();
}

static void sig_usr(int32_t signo)
{
	if(signo == SIGSEGV)
	{
		printf("received SIGSEGV\n");
	}
	else if(signo == SIGILL)
	{
		printf("received SIGILL\n");
	}
	else if(signo == SIGHUP)
	{
		printf("received, SIGHUP: ignore this signal\n");
		return;
	}
	else
	{
		fprintf(stderr, "received signal : %d\n", signo);
	}
	fflush(qscript_stdout);
	exit(1);
}


#if 0
void SetupSignalHandler()
{
	if (signal (SIGSEGV, sig_usr) == SIG_ERR)
	{
		fprintf(stderr, "cannot catch SIGSEGV\n");
		exit(1);
	}
	else if (signal (SIGHUP, SIG_IGN) == SIG_ERR)
	{
		fprintf(stderr, "cannot ignore SIGHUP\n");
		exit(1);
	}
	else if (signal (SIGILL, sig_usr) == SIG_ERR)
	{
		fprintf(stderr, "cannot catch SIGILL\n");
		exit(1);
	}
}
#endif /*  0 */

// nxd: commented out 15-feb-2013 
#if 0
void print_map_header(fstream & map_file )
{
	map_file << "Question No			,width,	no responses,	start position,	end position\n";
}
#endif /*  0 */


// ===================== from src/question_gtk_runtime - copied from the gtk branch
//

//enum UI_Mode { NCurses_Mode, Microhttpd_Mode, Wt_Mode, Gtk_Mode};
//extern UI_Mode ui_mode;


#include "named_range.h"
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

char get_end_of_question_response()
{
	// dummy value - this function is not yet done
	return 'A';
}

void ncurses_eval (AbstractQuestion * q)
{
	cout << "Change the name to be Toolkit independent"
		<< endl;
	
	gtkQuestionnaireApplication->ConstructQuestionForm (q, gtkQuestionnaireApplication->this_users_session);
	return;
}


int32_t prompt_user_for_serial_no()
{
	cout << "Not yet implemented"
		<< endl;
	return 100;
}

void print_save_partial_data_message_success ()
{
	cout << " not yet implemented" << endl;
}


#if 0
void question_eval_loop (EvalMode qnre_mode,
	UserNavigation qnre_navigation_mode, AbstractQuestion * last_question_visited,
	AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire)
{

	//while(theQuestionnaire->ser_no != 0 || (write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag))
	//{
	fprintf(qscript_stdout, "reached top of while loop:\n");
	re_eval_from_start:
	AbstractQuestion * q =
		theQuestionnaire->eval2 (
		qnre_navigation_mode, last_question_visited, jump_to_question);
	// Currently lets not worry about the data writing path
	// hence if we are in data writing mode - just exit with a message
	if (!q)
	{
		if (write_data_file_flag)
		{
			theQuestionnaire->write_ascii_data_to_disk();
			cerr << "Not considering data writing path at the moment" << endl;
			exit(1);
		}
		else if (write_qtm_data_file_flag)
		{
			theQuestionnaire->write_qtm_data_to_disk();
			cerr << "Not considering data writing path at the moment" << endl;
			exit(1);
		}
		else
		{
			//cerr << "Not considering What happens when we reach end of qnre at the moment - just lets exit" << endl;
			//exit(1);
			// thanks to the exit above - the code that follow is redundant in this block
			char end_of_question_navigation = get_end_of_question_response();
			if(end_of_question_navigation == 's')
			{
				theQuestionnaire->write_data_to_disk(theQuestionnaire->question_list, theQuestionnaire->jno, theQuestionnaire->ser_no);
				return;
			}
			else if (end_of_question_navigation == 'p')
			{
				AbstractQuestion * target_question = theQuestionnaire->ComputePreviousQuestion(theQuestionnaire->last_question_answered);
				//if(target_question->type_ == QUESTION_ARR_TYPE)
				//{
				//	theQuestionnaire->jumpToIndex = theQuestionnaire->ComputeJumpToIndex(target_question);
				//}
				//theQuestionnaire->jumpToQuestion = target_question->questionName_;
				////if (data_entry_window == 0) cout << "target question: " << jumpToQuestion;
				//theQuestionnaire->back_jump = true;
				//user_navigation = NOT_SET;
				//goto start_of_questions;
				//goto re_eval_from_start;
				question_eval_loop (USER_NAVIGATION,
					NAVIGATE_PREVIOUS, /* last_question_visited */ q,
					/*  jump_to_question */ target_question, theQuestionnaire);
			}
			else if (end_of_question_navigation == 'j')
			{
				theQuestionnaire->DisplayActiveQuestions();
				theQuestionnaire->GetUserResponse(theQuestionnaire->jumpToQuestion, theQuestionnaire->jumpToIndex);
				user_navigation = NOT_SET;
				//goto start_of_questions;
				//goto re_eval_from_start;
			}
			else if (end_of_question_navigation == 'q')
			{
				//change to break again when we remove the exit from above
				//break;
				//endwin();
				//exit(1);
				return;
			}
			else
			{
				//goto label_end_of_qnre_navigation;
			}
			// wclear(data_entry_window);
			// mvwprintw(data_entry_window, 1, 1, "Enter Serial No (0) to exit: ");
			// mvwscanw(data_entry_window, 1, 40, "%d", & ser_no);
			//theQuestionnaire.prompt_user_for_serial_no();
			//if (theQuestionnaire.ser_no ==0) break;
			//change to break again when we remove the exit from above
			//actually this should be un-reachable code
			//break;
			//
			exit(1);
		}
	}
	else
	{
		fprintf(qscript_stdout, "eval2 returned %s\n",
			q->questionName_.c_str());
		re_eval:
		//q->eval(question_window, stub_list_window, data_entry_window);
		ncurses_eval (q);

		if (user_navigation == NAVIGATE_PREVIOUS)
		{
			fprintf(qscript_stdout,
				"user_navigation == NAVIGATE_PREVIOUS\n");
			AbstractQuestion *target_question =
				theQuestionnaire->ComputePreviousQuestion(q);
			if (target_question == 0)
			{
				//goto re_eval;
				//void question_eval_loop (EvalMode qnre_mode,
				//UserNavigation qnre_navigation_mode, AbstractQuestion * last_question_visited,
				//AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire)
				question_eval_loop (USER_NAVIGATION,
					NAVIGATE_PREVIOUS, /* last_question_visited */ q,
					/*  jump_to_question */ q, theQuestionnaire);
			}
			else
			{
				//theQuestionnaire->jumpToQuestion = target_question->questionName_;
				//if (target_question->type_ == QUESTION_ARR_TYPE)
				//{
				//	theQuestionnaire->jumpToIndex =
				//		theQuestionnaire->
				//		ComputeJumpToIndex(target_question);
				//}
				// if (data_entry_window == 0)
				//     cout << "target question: " << jumpToQuestion;
				// if (data_entry_window == 0)
				//     cout << "target question Index: " << theQuestionnaire.jumpToIndex;
				theQuestionnaire->back_jump = true;
				//user_navigation = NOT_SET;
				//goto start_of_questions;
				question_eval_loop (USER_NAVIGATION,
					NAVIGATE_PREVIOUS, /* last_question_visited */ q,
					/*  jump_to_question */ target_question, theQuestionnaire);
				//goto re_eval_from_start;
			}
		}
		else if (user_navigation == NAVIGATE_NEXT)
		{
			//fprintf(qscript_stdout, "user_navigation == NAVIGATE_NEXT\n");
			//if (q->isAnswered_ == false
			//	&& q->question_attributes.isAllowBlank() == false)
			//{
			//	fprintf(qscript_stdout,
			//		"questionName_ %s: going back to re_eval\n",
			//		q->questionName_.c_str());
			//	goto re_eval;
			//}
			//qnre_navigation_mode = NAVIGATE_NEXT;
			// stopAtNextQuestion = true;
			//user_navigation = NOT_SET;
			question_eval_loop (USER_NAVIGATION,
				NAVIGATE_NEXT, /* last_question_visited */ q,
				/*  jump_to_question */ 0, theQuestionnaire);
		}
		else if (user_navigation == JUMP_TO_QUESTION)
		{
			theQuestionnaire->DisplayActiveQuestions();
			theQuestionnaire->GetUserResponse(theQuestionnaire->jumpToQuestion, theQuestionnaire->jumpToIndex);
			user_navigation = NOT_SET;
			//goto start_of_questions;
			goto re_eval_from_start;
		}
		else if (user_navigation == SAVE_DATA)
		{
			theQuestionnaire->write_data_to_disk(theQuestionnaire->question_list, theQuestionnaire->jno,
				theQuestionnaire->ser_no);
			print_save_partial_data_message_success ();
			//if (q->isAnswered_ == false)
			//{
			//	//goto label_eval_q2;
			//	goto re_eval;
			//}
			question_eval_loop (NORMAL_FLOW,
				NAVIGATE_NEXT, /* last_question_visited */ q,
				/*  jump_to_question */ jump_to_question, theQuestionnaire);
		}
		else
		{
			theQuestionnaire->last_question_answered = q;
			question_eval_loop (NORMAL_FLOW,
				NAVIGATE_NEXT, /* last_question_visited */ q,
				/*  jump_to_question */ 0, theQuestionnaire);
		}
	}
	//}						 /* close while */

}
#endif /*  0 */
