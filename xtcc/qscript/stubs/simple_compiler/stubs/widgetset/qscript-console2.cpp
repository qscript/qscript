/*
 * =====================================================================================
 *
 *       Filename:  qscript-console2.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 06 September 2012 06:00:29  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

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

#include "WCodeMirror.h"


#include <fstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>

std::string http_address;
struct QScriptConsole : public Wt::WApplication
{
	QScriptConsole(const Wt::WEnvironment& env, bool embedded, Wt::WServer & serv);


	//void transferCode();
	void launch();
	void getTheCode();
	void createRDG();
	void createDataWriter();
	void generateRandomData();
	void readFile (std::fstream & file, std::stringstream & data);

	Wt::WCodeMirrorTextArea * cmta_;
	Wt::WLineEdit *filename_ ;
	Wt::WText * compilerMessages_ ;
	Wt::WServer & server_ ;
	std::string launchedProcessNumber_;
	Wt::WPushButton * pbSaveAndCompile_;

	Wt::WPushButton * pbLaunch_;

	Wt::WPushButton * pbCreateRDGenerator_;
	Wt::WPushButton * pbCreateDataWriter_;

	Wt::WPushButton * pbGenerateRandomData_;

	Wt::WPushButton * pbExportQuantumAxes_;
	Wt::WPushButton * pbExportSPSSScript_;
	Wt::WPushButton * pbExportXtccScript_;

	Wt::WPushButton * pbLaunchXtccWUI_;


};


void QScriptConsole::readFile (std::fstream & file, std::stringstream & data)
{
	while (!file.eof()) {
		char buffer[4097];
		memset (buffer, 0, 4097);
		file.read (buffer, 4096);
		// why? - because read does put the trailing '\0'
		data << buffer;
		//int n = data.gcount();
		//buffer[n] = '\0';
	}
}

QScriptConsole::QScriptConsole(const Wt::WEnvironment& env, bool embedded
		, Wt::WServer & serv
		)
	: WApplication(env), 
	  filename_(0), compilerMessages_(0), server_(serv), cmta_(new Wt::WCodeMirrorTextArea(this->root()))
{
	using namespace std;
	Wt::WContainerWidget *top = root();
	//Wt::WContainerWidget * code_mirror_text_editor;
	   
	setTitle("QScript Console");

	Wt::WContainerWidget *w = new Wt::WContainerWidget(top);
	Wt::WLabel *label = new Wt::WLabel("Filename:", w);
	Wt::WRegExpValidator *file_name_validator = new Wt::WRegExpValidator("[a-zA-Z0-9_][a-zA-Z0-9._]+");
	filename_ = new Wt::WLineEdit("vegetable", w);
	filename_->setValidator(file_name_validator);
	label->setBuddy(filename_);
	pbSaveAndCompile_ = new Wt::WPushButton ("Save & Compile", top);
	pbSaveAndCompile_->setMargin(5, Wt::Left);
	pbSaveAndCompile_->clicked().connect(this, &QScriptConsole::getTheCode);
	pbLaunch_ = new Wt::WPushButton ("Launch", top);
	pbLaunch_->setMargin(5, Wt::Left);
	pbLaunch_->disable();
	pbLaunch_->clicked().connect(this, &QScriptConsole::launch);

	pbCreateRDGenerator_= new Wt::WPushButton ("Create Random Data Generator", top);
	pbCreateRDGenerator_->setMargin(5, Wt::Left);
	pbCreateRDGenerator_->disable();
	pbCreateRDGenerator_->clicked().connect(this, &QScriptConsole::createRDG);

	pbGenerateRandomData_ = new Wt::WPushButton ("Generate Random Data", top);
	pbGenerateRandomData_->setMargin(5, Wt::Left);
	pbGenerateRandomData_->disable();
	pbGenerateRandomData_->clicked().connect(this, &QScriptConsole::generateRandomData);

	pbCreateDataWriter_= new Wt::WPushButton ("Create Random Data Writer", top);
	pbCreateDataWriter_->setMargin(5, Wt::Left);
	pbCreateDataWriter_->disable();
	pbCreateDataWriter_->clicked().connect(this, &QScriptConsole::createDataWriter);

	pbExportQuantumAxes_ = new Wt::WPushButton ("Export Quantum Axes", top);
	pbExportQuantumAxes_->setMargin(5, Wt::Left);
	pbExportQuantumAxes_->disable();

	pbExportSPSSScript_ = new Wt::WPushButton ("Export SPSS Script", top);
	pbExportSPSSScript_->setMargin(5, Wt::Left);
	pbExportSPSSScript_->disable();

	pbExportXtccScript_ = new Wt::WPushButton ("Export Xtcc Script", top);
	pbExportXtccScript_->setMargin(5, Wt::Left);
	pbExportXtccScript_->disable();

	top->addWidget(new Wt::WBreak());
	compilerMessages_ = new Wt::WText( top);
	//compilerMessages_->addStyleClass("font-family:monospace;");
	//compilerMessages_->addCssRule (compilerMessages_->jsRef(), "font-family:monospace;");
	// preload the cmta_ with a script
	stringstream sample_code;
	std::fstream fs_sample_code ("vegetable", std::ios::in);
	readFile (fs_sample_code, sample_code);
	cmta_->setText (sample_code.str());
}

void QScriptConsole::createDataWriter()
{
	using  std::string;
	using  std::stringstream;
	using  std::cout;
	using  std::endl;
	std::string sys_filename = filename_->text().toUTF8();
	std::stringstream cmd;
	cmd << "qscript -o -m -n -f " << sys_filename << " 2>&1 >op";
	compilerMessages_->setText("compiling generator with command: " + cmd.str());
	system (cmd.str().c_str());
	std::fstream op ("op", std::ios::in);
	stringstream cc_errs;
	readFile (op, cc_errs);
	if (cc_errs.str().find ("Generated executable. You can run it by") != string::npos) {
		pbGenerateRandomData_->enable();
	}
}

void QScriptConsole::createRDG()
{
	using  std::string;
	using  std::stringstream;
	using  std::cout;
	using  std::endl;
	std::string sys_filename = filename_->text().toUTF8();
	std::stringstream cmd;
	cmd << "qscript-rdg -o -m -n -f " << sys_filename << " 2>&1 >op";
	compilerMessages_->setText("compiling generator with command: " + cmd.str());
	system (cmd.str().c_str());
	std::fstream op ("op", std::ios::in);
	stringstream cc_errs;
	readFile (op, cc_errs);
	if (cc_errs.str().find ("Generated executable. You can run it by") != string::npos) {
		pbGenerateRandomData_->enable();
	}
}

void QScriptConsole::generateRandomData()
{
	using  std::string;
	using  std::stringstream;
	using  std::cout;
	using  std::endl;
	cout << __PRETTY_FUNCTION__ << endl;
	std::string sys_filename = filename_->text().toUTF8();
	std::stringstream cmd;
	cmd << "./" << sys_filename << "-rdg.exe -r 200 2>&1 >op";
	compilerMessages_->setText("generating 200 records of random data with cmd: " + cmd.str());
	system (cmd.str().c_str());
	std::fstream op ("op", std::ios::in);
	stringstream cc_errs;
	readFile (op, cc_errs);
	cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
}


void QScriptConsole::getTheCode ()
{
	using namespace std;

	std::string p_the_code = cmta_->getText();
	string sys_filename = filename_->text().toUTF8();
	fstream save_file (sys_filename.c_str(), ios::out);
	save_file << p_the_code << endl;
	stringstream cmd;

	cmd << "qscript_wq2 -o -m -w wt -f " << sys_filename << " 2>&1 >op";
	system (cmd.str().c_str());
	fstream op ("op", ios::in);
	stringstream cc_errs;
	readFile (op, cc_errs);
#if 0
	while (!op.eof()) {
		char buffer[4097];
		memset (buffer, 0, 4097);
		op.read (buffer, 4096);
		// why? - because read does put the trailing '\0'
		cc_errs << buffer;
		int n = cc_errs.gcount();
		//buffer[n] = '\0';
	}
#endif /*  0 */
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
	if (errs.find ("Generated executable. You can run it by") != string::npos) {
		pbLaunch_->enable();
		pbCreateRDGenerator_->enable();
	}
}


void QScriptConsole::launch()
{
	using  std::string;
	using  std::stringstream;
	using  std::cout;
	using  std::endl;
	string sys_filename = filename_->text().toUTF8();
	stringstream cmd;
	cmd << "./" << sys_filename << "-wq2.exe -m\n";
	system (cmd.str().c_str());
	sleep(1);
	//cmd << "./" << sys_filename << ".exe --http-address=127.0.0.1 "
	//cmd << "./" << sys_filename << ".exe --http-address=115.241.206.132 "
	cmd << "./" << sys_filename << "-wq2.exe --http-address " << http_address
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
	//compilerMessages_->setText(cmd.str());
	compilerMessages_->setTextFormat(Wt::XHTMLText);
}

Wt::WServer server;
Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
	using std::cout;
	using std::endl;
	cout << "httpPort: " << server.httpPort() << endl;

	Wt::WApplication * app =  new QScriptConsole(env, false, server);
  	app->useStyleSheet("style/custom.css");
	return app;
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

