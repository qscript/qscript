

#include <Wt/WApplication>
#include <Wt/WTextArea>
#include <Wt/WContainerWidget>
#include <string>
#include <sstream>
#include "WCodeMirror.h"

namespace Wt {


WCodeMirrorTextArea::WCodeMirrorTextArea (WContainerWidget * parent) 
		: WContainerWidget (parent)
{

	textArea_ = new WTextArea(this);
	textArea_->setText("var v1;\nfunction f (p1, p2, p3) {\n // does nothing \n};\n");

	WApplication * app = WApplication:: instance();

	//app.require(app.resolveRelativeUrl("codemirror-2.32/lib/codemirror.js"));
	//app.require(app.resolveRelativeUrl("codemirror-2.32/mode/groovy/groovy.js"));
	//true
	//
	app->useStyleSheet(app->resolveRelativeUrl("CodeMirror-2.33/lib/codemirror.css"));
	app->require(app->resolveRelativeUrl("CodeMirror-2.33/lib/codemirror.js"));
	app->require(app->resolveRelativeUrl("CodeMirror-2.33/mode/qscript/clike.js"));
	app->useStyleSheet(app->resolveRelativeUrl("CodeMirror-2.33/doc/docs.css"));

	//TODO:
	//We save the editor state to the text area on each key stroke,
	//it appears to be not a performance issue,
	//however it might very well become one when editing larger fragments of code.
	//A better solution would be to save this state to the text area only when
	//the form is submitted, currently this is not yet possible in Wt???.

	using std::string;
	string js =
	    "var e = " + textArea_->jsRef() + ";" +
	    "var cm = CodeMirror.fromTextArea(e, {" +
	    "    onKeyEvent : function (editor, event) {" +
	    "        editor.save();" +
	    "    }," +
	    "    lineNumbers: true, " +
            "matchBrackets: true,"
	    "mode: \"text/x-qscript\","
	    "    value: \"var v1; function f2 (p1, p2, p3) { var v2; }\" " +
	    "    });" +
	    "var self = " + this->jsRef() + ";" +
	    "self.cm = cm;";
	this->doJavaScript(js);
}


void WCodeMirrorTextArea::setText (std::string text)
{
	textArea_->setText (text);
}

	std::string WCodeMirrorTextArea::getText() 
	{
		return textArea_-> text().toUTF8();
	}

	void WCodeMirrorTextArea::setMarker(int line, std::string htmlMarker) 
	{
		std::stringstream js ;
		js 	<< "var self = " << jsRef() <<  ";" 
			<<  "self.cm.setMarker(" 
			<<  line <<  ", " << jsStringLiteral(htmlMarker + "%N%") 
			<< ");";
		this->doJavaScript(js.str());
	}

	void WCodeMirrorTextArea::clearMarker(int line)
	{
		std::stringstream js ;
		js 	<< "var self = " <<  jsRef() << ";" 
			<< "self.cm.clearMarker(" << line << ");";

		this->doJavaScript(js.str());
	}
}

