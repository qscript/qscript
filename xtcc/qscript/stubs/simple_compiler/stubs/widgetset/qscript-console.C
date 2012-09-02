
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WRegExpValidator>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WContainerWidget>
#include <Wt/WEnvironment>
#include <Wt/WPushButton>
#include <Wt/WServer>
#include <Wt/WText>
#include <Wt/WTextEdit>
#include <Wt/WJavaScript>

#include <fstream>

class HelloApplication : public Wt::WApplication
{
public:
  HelloApplication(const Wt::WEnvironment& env, bool embedded);

private:

  void transferCode();
  Wt::JSignal<std::string> getTheCodeSignal_;
  void getTheCode(std::string p_the_code);
  Wt::JSlot my_js_slot;
  Wt::WLineEdit *filename_ ;

};

HelloApplication::HelloApplication(const Wt::WEnvironment& env, bool embedded)
  : WApplication(env), getTheCodeSignal_(this, "getTheCode"), my_js_slot(),
	filename_(0)
{
  using namespace std;
  Wt::WContainerWidget *top;
  //Wt::WContainerWidget * code_mirror_text_editor;
	   
  getTheCodeSignal_.connect(this, &HelloApplication::getTheCode);
  setTitle("Hello world");


  if (!embedded) {
    /*
     * In Application mode, we have the root() is a container
     * corresponding to the entire browser window
     */
    top = root();
	  cout << " I am not embedded" << endl;

  } else {
    /*
     * In WidgetSet mode, we create and bind containers to existing
     * divs in the web page. In this example, we create a single div
     * whose DOM id was passed as a request argument.
     */
	  cout << " I am embedded" << endl;
    top = new Wt::WContainerWidget();
    const std::string *div = env.getParameter("div");
    if (div) {
      setJavaScriptClass(*div);
      bindWidget(top, *div);
      // another red herring - didnt need this at all
      //code_mirror_text_editor = new Wt::WContainerWidget(top);
      ////code_mirror_text_editor->setId("code_mirror_text_editor");
      //bindWidget(code_mirror_text_editor, "code_mirror_text_editor");
      //cout << "code_mirror_text_editor .id:" <<  code_mirror_text_editor->id() << endl;
    } else {
      std::cerr << "Missing: parameter: 'div'" << std::endl;
      return;
    }
  }
 
  Wt::WContainerWidget *w = new Wt::WContainerWidget(top);
  Wt::WLabel *label = new Wt::WLabel("Filename:", w);
  Wt::WRegExpValidator *file_name_validator = new Wt::WRegExpValidator("[a-zA-Z0-9_][a-zA-Z0-9._]+");
  filename_ = new Wt::WLineEdit("<filename>", w);
  filename_->setValidator(file_name_validator);
  label->setBuddy(filename_);
  Wt::WPushButton *b = new Wt::WPushButton("Transfer Code To Server.", top);
  b->setMargin(5, Wt::Left);
  // My initial attempts that failed
  //my_js_slot.setJavaScript("alert('my_js_slot');Wt.emit(Wt, 'getTheCode', myCodeMirror.getValue());");
  //my_js_slot.setJavaScript ("alert('my_js_slot');" + getTheCodeSignal_.createCall ("myCodeMirror.getValue()") );
  //  my_js_slot.setJavaScript (string("function() { alert('my_js_slot');") 
  //	+ string("Wt.emit('") + b->id() + string("','getTheCode',myCodeMirror.getValue()); }"));
  // this one works
  my_js_slot.setJavaScript (string("function () { alert('my_js_slot');") 
		  	+ getTheCodeSignal_.createCall ("myCodeMirror.getValue()") 
			+ string ("}")
			);

  if (!embedded)
    new Wt::WText
      ("<p><emph>Please run this application from within a web page to see the code transfer demo"
       "from within <a href=\"qscript-console.html\">a web page</a>.</emph></p>",
       root());


  top->addWidget(new Wt::WBreak());


  /*
   * Connect signals with slots
   */
  b->clicked().connect(this, &HelloApplication::transferCode);
}


void HelloApplication::getTheCode (std::string p_the_code)
{
  using namespace std;
  fstream save_file (filename_->text().toUTF8().c_str(), ios::out);
  save_file << p_the_code << endl;
}

void HelloApplication::transferCode()
{
  my_js_slot.exec();
}

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
  return new HelloApplication(env, false);
}

Wt::WApplication *createWidgetSet(const Wt::WEnvironment& env)
{
  return new HelloApplication(env, true);
}

int main(int argc, char **argv)
{
  Wt::WServer server(argv[0]);

  // Use default server configuration: command line arguments and the
  // wthttpd configuration file.
  server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);

  // Application entry points. Each entry point binds an URL with an
  // application (with a callback function used to bootstrap a new
  // application).

  // The following is the default entry point. It configures a
  // standalone Wt application at the deploy path configured in the
  // server configuration.
  server.addEntryPoint(Wt::Application, createApplication);

  // The following adds an entry point for a widget set. A widget set
  // must be loaded as a JavaScript from an HTML page.
  server.addEntryPoint(Wt::WidgetSet, createWidgetSet, "/qscript-console.js");

  // Start the server (in the background if there is threading support)
  // and wait for a shutdown signal (e.g. Ctrl C, SIGKILL)
  if (server.start()) {
    Wt::WServer::waitForShutdown();

    // Cleanly terminate all sessions
    server.stop();
  }
}

