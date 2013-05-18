mergeInto(LibraryManager.library, {
  loadScript: function(url) {
	var script  = document.createElement("script");
	script.type = "text/javascript";
	script.src = url;
	document.body.appendChild(script);
  },
  loadScriptString: function(code_pointer) {
	alert("loadScriptString - entered");
	var script  = document.createElement("script");
	script.type = "text/javascript";
	//script.src = Pointer_stringify(code);
	//document.body.appendChild(script);
	var code = Pointer_stringify(code_pointer);
	try {
		script.appendChild(document.createTextNode(code));
	} catch (ex) {
		script.text = code;
	}
	alert(code);
	alert("loadScriptString - finished");
  }

});

