

	 /*
      var editor = CodeMirror.fromTextArea(document.getElementById("code"), {
        lineNumbers: true,
        matchBrackets: true
      });
      editor.id = "code_mirror_text_editor";
      */
global_func()
{
	var myCodeMirror = CodeMirror(document.body, {
	  value: "function myScript(){return 100;}\n",
	  mode:  "javascript"
	});
	myCodeMirror.id = "code_mirror_text_editor";
	var get_the_code = document.getElementById("get_the_code");
	get_the_code.onclick = function () {
		var put_code_here = document.getElementById("put_code_here");
		put_code_here.innerHTML =  myCodeMirror.getValue();
	}
}
