
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
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>

// Fix this - global variable
std::string http_address;
class HelloApplication : public Wt::WApplication
{
public:
  //HelloApplication(const Wt::WEnvironment& env, bool embedded);
  HelloApplication(const Wt::WEnvironment& env, bool embedded, Wt::WServer & serv);

private:

  void transferCode();
  void launch();
  Wt::JSignal<std::string> getTheCodeSignal_;
  void getTheCode(std::string p_the_code);
  Wt::JSlot my_js_slot;
  Wt::WLineEdit *filename_ ;
  Wt::WText * compilerMessages_ ;
  Wt::WServer & server_ ;
  std::string launchedProcessNumber_;

};

HelloApplication::HelloApplication(const Wt::WEnvironment& env, bool embedded
		, Wt::WServer & serv
		)
  : WApplication(env), getTheCodeSignal_(this, "getTheCode"), my_js_slot(),
	filename_(0), compilerMessages_(0), server_(serv)
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
  filename_ = new Wt::WLineEdit("vegetable", w);
  filename_->setValidator(file_name_validator);
  label->setBuddy(filename_);
  Wt::WPushButton *b = new Wt::WPushButton ("Save & Compile", top);
  b->setMargin(5, Wt::Left);
  b->clicked().connect(this, &HelloApplication::transferCode);
  b = new Wt::WPushButton ("Launch", top);
  b->setMargin(5, Wt::Left);
  b->clicked().connect(this, &HelloApplication::launch);
  // My initial attempts that failed
  //my_js_slot.setJavaScript("alert('my_js_slot');Wt.emit(Wt, 'getTheCode', myCodeMirror.getValue());");
  //my_js_slot.setJavaScript ("alert('my_js_slot');" + getTheCodeSignal_.createCall ("myCodeMirror.getValue()") );
  //  my_js_slot.setJavaScript (string("function() { alert('my_js_slot');") 
  //	+ string("Wt.emit('") + b->id() + string("','getTheCode',myCodeMirror.getValue()); }"));
  // this one works
  my_js_slot.setJavaScript (string("function () {\n") 
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
  compilerMessages_ = new Wt::WText( top);
}


void HelloApplication::getTheCode (std::string p_the_code)
{
  using namespace std;
  string sys_filename = filename_->text().toUTF8();
  fstream save_file (sys_filename.c_str(), ios::out);
  save_file << p_the_code << endl;
  stringstream cmd;
  cmd << "qscript -o -m -w wt -f " << sys_filename << " 2>&1 >op";
  system (cmd.str().c_str());
  fstream op ("op", ios::in);
  stringstream cc_errs;
  while (!op.eof()) {
	char buffer[4097];
	memset (buffer, 0, 4097);
	op.read (buffer, 4096);
	// why? - because read does put the trailing '\0'
	cc_errs << buffer;
	int n = cc_errs.gcount();
	//buffer[n] = '\0';
  }
  cout << cc_errs.str() << endl;
  string errs = cc_errs.str();
  //{
  //        string::size_type found = errs.find (string(" "));
  //        while (found != string::npos) {
  //      	errs.replace (found, 1, "&nbsp;");
  //      	found = errs.find (string(" "));
  //        }
  //        found = errs.find (string("\n"));
  //        while (found != string::npos) {
  //      	errs.replace (found, 1, "<br />\n");
  //      	found = errs.find (string("\n"), found + 9);
  //        }

  //}
  cout << errs << endl;
  stringstream simple_htmlize;
  simple_htmlize << "<div>" << errs << "</div>" << endl;
  compilerMessages_->setTextFormat (Wt::PlainText);
  compilerMessages_->setText (simple_htmlize.str());
}

void HelloApplication::transferCode()
{
  my_js_slot.exec();
}

void HelloApplication::launch()
{
	using  std::string;
	using  std::stringstream;
	using  std::cout;
	using  std::endl;
	string sys_filename = filename_->text().toUTF8();
	stringstream cmd;
	cmd << "./" << sys_filename << ".exe -m\n";
	system (cmd.str().c_str());
	sleep(1);
	//cmd << "./" << sys_filename << ".exe --http-address=127.0.0.1 "
	//cmd << "./" << sys_filename << ".exe --http-address=115.241.206.132 "
	cmd << "./" << sys_filename << ".exe --http-address " << http_address
			<< " --http-port=0 "
			<< " --docroot=. &" << endl;
	system (cmd.str().c_str());
	sleep(1);
	string port_number_fname = sys_filename + "_port_number";
	cout << "port_number_fname: " << port_number_fname << endl;
	std::ifstream port_number_file(port_number_fname.c_str());
	string port_number ;
	port_number_file >> port_number;
	port_number_file >> launchedProcessNumber_;
	stringstream launched_mesg;
	//launched_mesg << "launched at http://115.241.206.132 http://127.0.0.1:" << port_number << endl;
	launched_mesg << "launched at <a href=\"http://"
		<< http_address  << ":"  << port_number 
		<< "\">"
		<< http_address  << ":"  << port_number 
		<< "</a>"
		<< endl;
	cout << launched_mesg.str() << endl;
	cout << "Process number: " << launchedProcessNumber_ << endl;
	compilerMessages_->setText(launched_mesg.str());
	compilerMessages_->setTextFormat(Wt::XHTMLText);
}

Wt::WServer server;
Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
	using std::cout;
	using std::endl;
  cout << "httpPort: " << server.httpPort() << endl;
  return new HelloApplication(env, false, server);
}

Wt::WApplication *createWidgetSet(const Wt::WEnvironment& env)
{
	using std::cout;
	using std::endl;
  cout << "httpPort: " << server.httpPort() << endl;
  return new HelloApplication(env, true, server);
}

int main(int argc, char **argv)
{
  //Wt::WServer server(argv[0]);
  // Use default server configuration: command line arguments and the
  // wthttpd configuration file.
  for (int i=1; i<argc; ++i) {
	  std::string s1(argv[i]);
	  if (s1=="--http-address") {
		  http_address = argv[i+1];
	  }
  }
  std::cout << "http_address: " << http_address << std::endl;
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
  // std::cout << "httpPort: " << server.httpPort() << std::endl;
  if (server.start()) {
	  std::cout << "server started, port number: " 
		  <<  server.httpPort() << std::endl;
    Wt::WServer::waitForShutdown();

    // Cleanly terminate all sessions
    server.stop();
  }
}

