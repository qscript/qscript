/*
 * =====================================================================================
 *
 *       Filename:  WCodeMirror.C
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 06 September 2012 01:05:33  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

/*
import eu.webtoolkit.jwt.WApplication;
import eu.webtoolkit.jwt.WContainerWidget;
import eu.webtoolkit.jwt.WTextArea;

public class CodeMirrorTextArea extends WContainerWidget {
    private WTextArea textArea;
    public CodeMirrorTextArea(WContainerWidget parent) {
        super(parent);
       
        textArea = new WTextArea(this);
       
        WApplication app = WApplication.getInstance();
       
        app.require(app.resolveRelativeUrl("codemirror-2.32/lib/codemirror.js"));
        app.require(app.resolveRelativeUrl("codemirror-2.32/mode/groovy/groovy.js"));
       
        //TODO:
        //We save the editor state to the text area on each key stroke,
        //it appears to be not a performance issue,
        //however it might very well become one when editing larger fragments of code.
        //A better solution would be to save this state to the text area only when
        //the form is submitted, currently this is not yet possible in Wt???.
       
        String js =
            "var e = " + textArea.getJsRef() + ";" +
            "var cm = CodeMirror.fromTextArea(e, {" +
            "    onKeyEvent : function (editor, event) {" +
            "        editor.save();" +
            "    }," +
            "    lineNumbers: true" +
            "    });" +
            "var self = " + getJsRef() + ";" +
            "self.cm = cm;";
       
        this.doJavaScript(js);
    }
   
    public CodeMirrorTextArea() {
        this(null);
    }
   
    public void setText(String text) {
        textArea.setText(text);
    }
   
    public String getText() {
        return textArea.getText();
    }
   
    public void setMarker(int line, String htmlMarker) {
        String js =
            "var self = " + getJsRef() + ";" +
            "self.cm.setMarker(" + line + ", " + jsStringLiteral(htmlMarker +
"%N%") + ");";
       
        this.doJavaScript(js);
    }
   
    public void clearMarker(int line) {
        String js =
            "var self = " + getJsRef() + ";" +
            "self.cm.clearMarker(" + line + ");";
       
        this.doJavaScript(js);
    }
}
  */
#ifndef WT_WCodeMirrorTextArea
#define WT_WCodeMirrorTextArea

#include <Wt/WApplication>
#include <Wt/WTextArea>
#include <Wt/WContainerWidget>
#include <string>
#include <sstream>

namespace Wt {

class WCodeMirrorTextArea : public WContainerWidget 
{
public:
	WTextArea * textArea_;
	WCodeMirrorTextArea (WContainerWidget * parent) ;



	void setText(std::string text);

	std::string getText() ;

	void setMarker(int line, std::string htmlMarker);

	void clearMarker(int line);

};

}
#endif /*  WT_WCodeMirrorTextArea */
