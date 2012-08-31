/*
 * =====================================================================================
 *
 *       Filename:  my_wt_codemirror.C
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 31 August 2012 05:49:05  IST
 *       Revision:  none
 *       Compiler:  c++
 *
 *         Author: Neil Xavier D'Souza
 *
 * =====================================================================================
 */


#include <iostream>
#include <string>

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WEnvironment>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WServer>
#include <Wt/WText>
#include <Wt/WTemplate>
#include <Wt/WTextArea>

class MyWtCodeMirror : public Wt::WApplication
{
	public:
		MyWtCodeMirror (const Wt::WEnvironment& env);
	Wt::WContainerWidget *top;
	Wt::WTextArea * textCodeEditor_;
};

MyWtCodeMirror::MyWtCodeMirror (const Wt::WEnvironment& env)
	: Wt::WApplication (env), top (0), textCodeEditor_ (0)
{
	using std::cout;
	using std::cerr;
	using std::endl;
	using std::string;
	top = root();
	bool success = require ("code-mirror/codemirror.js");
	if (success) {
		cout << "loaded codemirror.js" << endl;
	}
	success = require ("code-mirror/mode/javascript/javascript.js");
	if (success) {
		cout << "loaded javascript.js" << endl;
	}

	Wt::WTemplate * t = new Wt::WTemplate(root());
	//t->setTemplateText ("<div><textarea id=\"code\" name=\"code\"> Some text in the text area</textarea> </div>");
	t->setTemplateText ("<div> I contain a WTextArea called code: ${code} </div>");
	t->bindWidget ("code", textCodeEditor_ = new Wt::WTextArea (top));
	textCodeEditor_->setId("code");
	std::string text_area_id = textCodeEditor_->id();
	cout << "textCodeEditor_ id(): " << text_area_id << endl;
	//Wt::WWidget  * found =  findWidget 	("code");
	//if (found) {
	//	cout << "found the code widget" << endl;
	//} else {
	//	cout << "DID NOT FIND the \"code\" widget" << endl;
	//}
	//string text_area_id = "code";
        doJavaScript(string("var editor = CodeMirror.fromTextArea(document.getElementById('") 
			+ text_area_id 
			+ string("'), { lineNumbers: true, matchBrackets: true }); alert('success');"));
	//doJavaScript(string("var myCodeMirror = CodeMirror(document.body);"));


}


Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
  /*
   * You could read information from the environment to decide whether
   * the user has permission to start a new application
   */
  return new MyWtCodeMirror(env);
}


int main(int argc, char **argv)
{
  return Wt::WRun(argc, argv, &createApplication);
}


