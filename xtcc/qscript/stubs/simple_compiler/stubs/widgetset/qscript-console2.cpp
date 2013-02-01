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
#include <Wt/WVBoxLayout>
#include <Wt/WAnchor>
#include <Wt/WFileResource>
#include <Wt/WTabWidget>


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
	void launchXtcc();
	void getTheCode();
	void createRDG();
	void createDataWriter();
	void createQuantumDataAndPrograms();
	void createSPSSDataAndPrograms();
	void createXtccDataAndPrograms();
	void generateRandomData();
	void readFile (std::fstream & file, std::stringstream & data);

	Wt::WServer & server_ ;
	Wt::WContainerWidget * top_ ;
	Wt::WCodeMirrorTextArea * cmta_;
	Wt::WTabWidget * tabWidget_;


	Wt::WContainerWidget * compilerConsole_;
	Wt::WContainerWidget * rdgConsole_;
	Wt::WContainerWidget * dataExportConsole_;
	Wt::WContainerWidget * xtccConsole_;

	Wt::WLineEdit *filename_ ;
	Wt::WLabel *label ;
	std::string launchedProcessNumber_;
	std::string launchedXtccProcessNumber_;
	Wt::WPushButton * pbSaveAndCompile_;

	Wt::WPushButton * pbLaunch_;

	Wt::WPushButton * pbCreateRDGenerator_;
	Wt::WPushButton * pbCreateDataWriter_;

	Wt::WPushButton * pbGenerateRandomData_;

	Wt::WPushButton * pbExportQuantumAxes_;
	Wt::WPushButton * pbExportSPSSScript_;
	Wt::WPushButton * pbExportXtccScript_;

	Wt::WPushButton * pbLaunchXtccWUI_;

	Wt::WVBoxLayout * compilerMessagesLayout_;
	Wt::WContainerWidget * compilerMesgContainer_;
	Wt::WText * compilerMessages_ ;

	Wt::WVBoxLayout * rdgMessagesLayout_;
	Wt::WContainerWidget * rdgMesgContainer_;
	Wt::WText * rdgMessages_ ;
	Wt::WVBoxLayout * dataExportMessagesLayout_;
	Wt::WContainerWidget * dataExportMesgContainer_;
	Wt::WText * dataExportMessages_ ;
	Wt::WText * xtccMessages_ ;




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

void QScriptConsole::createQuantumDataAndPrograms()
{
	using  std::string;
	using  std::stringstream;
	using  std::cout;
	using  std::endl;
	std::string sys_filename = filename_->text().toUTF8();
	std::stringstream cmd;
	cmd <<  "./" << sys_filename << ".exe -q ";
	dataExportMessages_->setText("creating quantum datafile with command: " + cmd.str());
	system (cmd.str().c_str());
	stringstream  zip_file_cmd;
	zip_file_cmd << "zip -r "
		<< sys_filename
		<< "-qtm-setup.zip setup-"
		<< sys_filename << " "
		<< sys_filename << ".qdat " 
		<< sys_filename << ".freq_count.csv ";
	system (zip_file_cmd.str().c_str());
	string zip_file_name = sys_filename + string("-qtm-setup.zip");
	Wt::WFileResource *zipFile = new Wt::WFileResource ("application/zip", zip_file_name);
	zipFile->suggestFileName (zip_file_name);
	Wt::WAnchor *anchor = new Wt::WAnchor (zipFile, zip_file_name + " Quantum Setup + data + frequency counts");
	anchor->setTarget (Wt::TargetNewWindow);
	dataExportMessagesLayout_ -> addWidget (anchor);
}

void QScriptConsole::createSPSSDataAndPrograms()
{
	using  std::string;
	using  std::stringstream;
	using  std::cout;
	using  std::endl;
	std::string sys_filename = filename_->text().toUTF8();
	std::stringstream cmd;
	cmd <<  "./" << sys_filename << ".exe -w ";
	dataExportMessages_->setText("creating spss datafile with command: " + cmd.str());
	system (cmd.str().c_str());
	stringstream  zip_file_cmd;
	zip_file_cmd << "zip -r "
		<< sys_filename
		<< "-spss-setup.zip "
		<< sys_filename << "-flat-ascii.sps "
		<< sys_filename << ".dat " 
		<< sys_filename << ".freq_count.csv ";
	system (zip_file_cmd.str().c_str());
	string zip_file_name = sys_filename + string("-spss-setup.zip");
	Wt::WFileResource *zipFile = new Wt::WFileResource ("application/zip", zip_file_name);
	zipFile->suggestFileName (zip_file_name);
	Wt::WAnchor *anchor = new Wt::WAnchor (zipFile, zip_file_name + " SPSS Setup + data + frequency counts");
	anchor->setTarget (Wt::TargetNewWindow);
	dataExportMessagesLayout_ -> addWidget (anchor);
}

void QScriptConsole::createXtccDataAndPrograms()
{
	using  std::string;
	using  std::stringstream;
	using  std::cout;
	using  std::endl;
	std::string sys_filename = filename_->text().toUTF8();
	std::stringstream cmd;
	cmd <<  "./" << sys_filename << ".exe -x ";
	dataExportMessages_->setText("creating xtcc datafile with command: " + cmd.str());
	system (cmd.str().c_str());
	stringstream  zip_file_cmd;
	zip_file_cmd << "zip -r "
		<< sys_filename
		<< "-xtcc-setup.zip setup-"
		<< sys_filename << " "
		<< sys_filename << ".xdat " 
		<< sys_filename << ".freq_count.csv ";
	system (zip_file_cmd.str().c_str());
	string zip_file_name = sys_filename + string("-xtcc-setup.zip");
	Wt::WFileResource *zipFile = new Wt::WFileResource ("application/zip", zip_file_name);
	zipFile->suggestFileName (zip_file_name);
	Wt::WAnchor *anchor = new Wt::WAnchor (zipFile, zip_file_name + " Xtcc Setup + data + frequency counts");
	anchor->setTarget (Wt::TargetNewWindow);
	dataExportMessagesLayout_ -> addWidget (anchor);
	pbLaunchXtccWUI_->enable();
}

QScriptConsole::QScriptConsole(const Wt::WEnvironment& env, bool embedded
		, Wt::WServer & serv
		)
	: WApplication(env), 
	  server_(serv), 
	  top_ (root()),
	  cmta_ (new Wt::WCodeMirrorTextArea(top_) ),
	  tabWidget_ ( new Wt::WTabWidget (top_) ),
	  compilerConsole_ ( new Wt::WContainerWidget() ), 
	  rdgConsole_ ( new Wt::WContainerWidget() ),
	  dataExportConsole_ ( new Wt::WContainerWidget()),
	  xtccConsole_ ( new Wt::WContainerWidget()),
	  // compilerConsole_ =================
	  label (new Wt::WLabel ("Filename:", compilerConsole_) ),
	  filename_  (new Wt::WLineEdit("vegetable", compilerConsole_)),
	  pbSaveAndCompile_ ( new Wt::WPushButton ("Save & Compile", compilerConsole_)),
	  pbLaunch_ (new Wt::WPushButton ("Launch", compilerConsole_)),
	  compilerMessages_ ( new Wt::WText( compilerConsole_)),
	  compilerMessagesLayout_ ( new Wt::WVBoxLayout ()),
	  compilerMesgContainer_ ( new Wt::WContainerWidget (compilerConsole_)),
	  // rdgConsole_ ==============
	  pbCreateRDGenerator_( new Wt::WPushButton ("Create Random Data Generator", rdgConsole_)),
	  pbGenerateRandomData_ ( new Wt::WPushButton ("Generate Random Data", rdgConsole_)),
	  rdgMessages_ ( new Wt::WText( rdgConsole_)),
	  rdgMessagesLayout_ ( new Wt::WVBoxLayout ()),
	  rdgMesgContainer_ ( new Wt::WContainerWidget (rdgConsole_)),
	  // dataExportConsole_ ==================
	  pbCreateDataWriter_ ( new Wt::WPushButton ("Create Data Writer", dataExportConsole_)),
	  pbExportQuantumAxes_ ( new Wt::WPushButton ("Export Quantum Axes", dataExportConsole_)),
	  pbExportSPSSScript_ ( new Wt::WPushButton ("Export SPSS Script", dataExportConsole_)),
	  pbExportXtccScript_ ( new Wt::WPushButton ("Export Xtcc Script", dataExportConsole_)),
	  dataExportMessages_ ( new Wt::WText (dataExportConsole_)),
	  dataExportMessagesLayout_ ( new Wt::WVBoxLayout ()),
	  dataExportMesgContainer_ ( new Wt::WContainerWidget (dataExportConsole_)),
	  // xtccConsole_ ==================
	  xtccMessages_ ( new Wt::WText (xtccConsole_)),
	  pbLaunchXtccWUI_ (new Wt::WPushButton ("Launch Xtcc", xtccConsole_))
{
	using namespace std;
	//Wt::WContainerWidget *top_ = root();
	//Wt::WContainerWidget * code_mirror_text_editor;
	   
	setTitle("QScript Console");

	//tabWidget_ = new Wt::WTabWidget (top_);


	//Wt::WContainerWidget *w ;
	tabWidget_ -> addTab (compilerConsole_ , "Compiler/Web Launcher Console");
	tabWidget_ -> addTab (rdgConsole_ , "RDG Console");
	tabWidget_ -> addTab (dataExportConsole_, "Data Export Console");
	tabWidget_ -> addTab (xtccConsole_, "Xtcc UI Console");
	Wt::WRegExpValidator * file_name_validator = new Wt::WRegExpValidator("[a-zA-Z0-9_][a-zA-Z0-9._]+");
	label->setBuddy (filename_);
	filename_ -> setValidator (file_name_validator);
	//filename_ = new Wt::WLineEdit("vegetable", compilerConsole_);
	//pbSaveAndCompile_ = new Wt::WPushButton ("Save & Compile", compilerConsole_);
	pbSaveAndCompile_->setMargin(5, Wt::Left);
	pbSaveAndCompile_->clicked().connect(this, &QScriptConsole::getTheCode);
	//pbLaunch_ = new Wt::WPushButton ("Launch", compilerConsole_);
	pbLaunch_->setMargin(5, Wt::Left);
	pbLaunch_->disable();
	pbLaunch_->clicked().connect(this, &QScriptConsole::launch);

	//pbCreateRDGenerator_= new Wt::WPushButton ("Create Random Data Generator", rdgConsole_);
	pbCreateRDGenerator_->setMargin(5, Wt::Left);
	pbCreateRDGenerator_->disable();
	pbCreateRDGenerator_->clicked().connect(this, &QScriptConsole::createRDG);

	//pbGenerateRandomData_ = new Wt::WPushButton ("Generate Random Data", rdgConsole_);
	pbGenerateRandomData_->setMargin(5, Wt::Left);
	pbGenerateRandomData_->disable();
	pbGenerateRandomData_->clicked().connect(this, &QScriptConsole::generateRandomData);

	//pbCreateDataWriter_= new Wt::WPushButton ("Create Data Writer", rdgConsole_);
	pbCreateDataWriter_->setMargin(5, Wt::Left);
	pbCreateDataWriter_->disable();
	pbCreateDataWriter_->clicked().connect(this, &QScriptConsole::createDataWriter);

	//pbExportQuantumAxes_ = new Wt::WPushButton ("Export Quantum Axes", dataExportConsole_);
	pbExportQuantumAxes_->setMargin(5, Wt::Left);
	pbExportQuantumAxes_->disable();
	pbExportQuantumAxes_->clicked().connect(this, &QScriptConsole::createQuantumDataAndPrograms);


	//pbExportSPSSScript_ = new Wt::WPushButton ("Export SPSS Script", dataExportConsole_);
	pbExportSPSSScript_->setMargin(5, Wt::Left);
	pbExportSPSSScript_->disable();
	pbExportSPSSScript_->clicked().connect(this, &QScriptConsole::createSPSSDataAndPrograms);

	//pbExportXtccScript_ = new Wt::WPushButton ("Export Xtcc Script", dataExportConsole_);
	pbExportXtccScript_->setMargin(5, Wt::Left);
	pbExportXtccScript_->disable();
	pbExportXtccScript_->clicked().connect(this, &QScriptConsole::createXtccDataAndPrograms);

	compilerConsole_->addWidget(new Wt::WBreak());
	//compilerMessages_ = new Wt::WText( compilerConsole_);
	//rdgMessages_ = new Wt::WText( rdgConsole_);
	//dataExportMessages_ = new Wt::WText (dataExportConsole_);
	//xtccMessages_ = new Wt::WText (xtccConsole_);
	

	//compilerMessages_->addStyleClass("font-family:monospace;");
	//compilerMessages_->addCssRule (compilerMessages_->jsRef(), "font-family:monospace;");
	// preload the cmta_ with a script
	stringstream sample_code;
	std::fstream fs_sample_code ("vegetable", std::ios::in);
	readFile (fs_sample_code, sample_code);
	cmta_->setText (sample_code.str());

	//compilerMessagesLayout_ = new Wt::WVBoxLayout ();
	//compilerMesgContainer_ = new Wt::WContainerWidget (compilerConsole_);
	compilerMesgContainer_->setLayout (compilerMessagesLayout_);
	compilerMesgContainer_->setOverflow (Wt::WContainerWidget::OverflowAuto);

	rdgMesgContainer_ ->setLayout (rdgMessagesLayout_);
	rdgMesgContainer_ ->setOverflow (Wt::WContainerWidget::OverflowAuto);

	dataExportMesgContainer_->setLayout (dataExportMessagesLayout_);
	dataExportMesgContainer_->setOverflow (Wt::WContainerWidget::OverflowAuto);

	pbLaunchXtccWUI_->setMargin(5, Wt::Left);
	cerr << __LINE__ << ", " << __FILE__ << ", " << __PRETTY_FUNCTION__ << " uncomment after testing"
		<< endl;
	//pbLaunchXtccWUI_->disable();
	pbLaunchXtccWUI_->clicked().connect(this, &QScriptConsole::launchXtcc);

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
	
	dataExportMessages_->setText("compiling generator with command: " + cmd.str());
	system (cmd.str().c_str());
	std::fstream op ("op", std::ios::in);
	stringstream cc_errs;
	readFile (op, cc_errs);
	if (cc_errs.str().find ("Generated executable. You can run it by") != string::npos) {
		pbExportQuantumAxes_->enable();
		pbExportSPSSScript_->enable();
		pbExportXtccScript_->enable();
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
	//rdgMessages_->setText("compiling generator with command: " + cmd.str());
	rdgMessages_ = new Wt::WText("compiling generator with command: " + cmd.str());
	system (cmd.str().c_str());
	std::fstream op ("op", std::ios::in);
	stringstream cc_errs;
	readFile (op, cc_errs);
	if (cc_errs.str().find ("Generated executable. You can run it by") != string::npos) {
		pbGenerateRandomData_->enable();
	}
	rdgMessagesLayout_->addWidget (rdgMessages_);
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
	//rdgMessages_->setText("generating 200 records of random data with cmd: " + cmd.str());
	rdgMessages_ = new Wt::WText ("generating 200 records of random data with cmd: " + cmd.str());
	rdgMessagesLayout_->addWidget (rdgMessages_);
	system (cmd.str().c_str());
	std::fstream op ("op", std::ios::in);
	stringstream cc_errs;
	readFile (op, cc_errs);
	cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
	pbCreateDataWriter_->enable();
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


void QScriptConsole::launchXtcc()
{
	using  std::string;
	using  std::stringstream;
	using  std::cout;
	using  std::endl;
	string sys_filename = filename_->text().toUTF8();
	stringstream cmd;
	//cmd << "./" << sys_filename << ".exe --http-address=127.0.0.1 "
	//cmd << "./" << sys_filename << ".exe --http-address=115.241.206.132 "
	cmd << "cd setup-" << sys_filename
		<< "; xtpp < " << sys_filename << ".xtcc2  > "
		<<  sys_filename << ".xtcc_pp; cd ..;";
	cout << "running command : " << cmd.str() << endl;
	system (cmd.str().c_str());
	cout << "sys_filename: " << sys_filename << endl;

	cmd << "cd setup-" << sys_filename << "; "
		<< "xtcc_wt  --http-address=" << http_address
		<< " --http-port=0 --docroot=. " 
		<< sys_filename << ".xtcc_pp ../" << sys_filename << ".xdat &"
		<< endl;
	std::cerr << "running command : " << cmd.str() << endl;
	system (cmd.str().c_str());
	sleep(1);
	string port_number_fname = string("setup-") + sys_filename + "/" + sys_filename + ".xtcc_pp_xtcc_port_number";
	std::cerr << "port_number_fname: " << port_number_fname << endl;
	std::ifstream port_number_file(port_number_fname.c_str());
	string port_number ;
	port_number_file >> port_number;
	port_number_file >> launchedXtccProcessNumber_;
	stringstream launched_mesg;
	//launched_mesg << "launched at http://115.241.206.132 http://127.0.0.1:" << port_number << endl;
	launched_mesg << "launched at <a href=\"http://"
		<< http_address  << ":"  << port_number 
		<< "\">"
		<< http_address  << ":"  << port_number 
		<< "</a>"
		<< endl;
	cout << launched_mesg.str() << endl;
	cout << "Process number: " << launchedXtccProcessNumber_ << endl;
	xtccMessages_->setText(launched_mesg.str());
	//compilerMessages_->setText(cmd.str());
	xtccMessages_->setTextFormat(Wt::XHTMLText);
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

