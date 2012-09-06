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
	/*
        doJavaScript(string("var editor = CodeMirror.fromTextArea(document.getElementById('") 
			+ text_area_id 
			+ string("'), { lineNumbers: true, matchBrackets: true }); alert('success');"));
			*/
	doJavaScript(string("var myCodeMirror = CodeMirror(document.body, { value: \"function f1 () { var v1;}\", mode: \"javascript\" , lineNumbers: true});"));
	//
	//
	/*
	doJavaScript (
	"var myCodeMirror = CodeMirror(document.body, {" \
	 " value: \"vegetable {\\n int32_t i1;\\n stubs yn=	\\\"Yes\\\" 1\\n \\\"No\\\" 2;\\n \\n q1 	\\\"Eat veg?\\\"\\n \\tsp int32_t yn;\\n \\n stubs agree_5 = \\n \\\"agree strongly\\\" 5\\n \\\"agree somewhat\\\" 4\\n \\\"Neutral\\\" 3\\n \\\"Disagree \\\" 2\\n \\\"Disagree strongly\\\" 1;	\\n \\n stubs veg=	\\n \\\"Tomates\\\" 1\\n \\\"Potatoes\\\" 2\\n \\\"Capsicum\\\" 3\\n \\\"Brinjal/Egg plant\\\" 4\\n \\\"Okra/Lady Finger\\\" 5\\n ;\\n named_attribute veg_seg_att = \\\" Vegetables are good for health\\\",\\n \\\" I buy fresh vegetables often\\\",\\n \\\" Greens are good source of dietary fibre\\\",\\n \\\" I would like to be vegetarian some day\\\"\\n ;\\n \\n \\n \\tif (q1==1) {\\n \\t\\tsetall(veg);\\n \\n \\n q2 		\\\"Which veg u r aware of?\\\"\\n\\t\\tmp(5) int32_t veg;\\n \\n\\t\\t unset(veg);\\n \\t\\tsetadd(veg, q2);\\n q3 		\\\"Which veg dou eat?\\\"\\n \\t\\tmp(5) int32_t veg;\\n \\n \\n\\t\\t unset(veg);\\n \\t\\tsetadd(veg, q3);\\n q4 		\\\"Which is ur fav veg?\\\" : q3\\n \\t\\tsp int32_t veg;\\n \\n \\t\\tint32_t sum=0;\\n \\t\\tint32_t iter_no=0;\\n\\t \\tfor (i1=0; i1<5; i1=i1+1) {\\n\\t\\t\\t int32_t code = i1+1;\\n \\n\\t\\t\\t if (code in q3) {\\n q6\\t\\t\\t\\t \\\"In a week what perc of your veggies are : \\\"\\n \\t\\t\\t\\t: q3 . stubs [i1]\\n \\t\\t\\t\\tsp int32_t (0-100);\\n \\t\\t\\t\\tsum=sum+q6[i1];\\n\\t\\t\\t\\t iter_no=i1;\\n\\t\\t\\t } else {\\n \\t\\t\\t\\t1;\\n\\t\\t\\t}\\n\\t\\t }\\n \\t\\tif (sum != 100) {\\n \\t\\t\\tclear (q6[iter_no]);\\n\\t\\t }\\n \\n \\n \\n\\t } else {\\n\\t \\t1;\\n\\t}\\n \\n \\n \\tfor (i1=0; i1<4; i1=i1+1) {\\n q5\\t\\t\\\"Please state your agreement with these statements\\\" : veg_seg_att[i1]\\n\\t\\tsp int32_t agree_5;\\n\\t}\\n \\n }\\n\"," \
	  "mode:  \"javascript\"" \
	"}\");\"" \
	"\"myCodeMirror.id = \\\"code_mirror_text_editor\\\";\"");
	*/
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


