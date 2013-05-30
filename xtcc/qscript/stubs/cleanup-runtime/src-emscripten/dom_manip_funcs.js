mergeInto(LibraryManager.library, {

print_to_question_area: function (question_text_ptr)
{
	//alert("print_to_question_area: " + i );
	var the_question_text = Pointer_stringify (question_text_ptr);
	var v = document.getElementById("question_text_area");
	var html = "";
	html +=
		"<p>"
		+ "some data from the cpp program"
		+ the_question_text
		+ "</p>";
	v.innerHTML = html;
},


print_to_stub_area: function (string_pointer, counter)
{
	//alert("print_to_question_area: " + i );
	//var v = document.getElementById("stubs_form_div");
	var stubs_form_div = document.getElementById("stubs_form_div");
	var the_stub_data = Pointer_stringify (string_pointer);
	/*
	var html = "";
	html +=
		"<p>"
		+ "stub data from the cpp program"
		+ the_stub_data
		+ "</p>";
	v.innerHTML = html;
	*/


	var display_stubs = function (json_rep2) {
		var res2 = JSON.parse(json_rep2);
		var doc_frag2 = document.createDocumentFragment();
		//alert (res2.name);
		//alert (res2.stubs);
		// global - counter variable
		for (var i=0; i<res2.stubs.length; ++i) {
			var input   = document.createElement("input");
			input.type  = "radio";
			input.name  = "stub_response";
			input.value = res2.stubs[i].stub_code;
			var id_text = res2.name + res2.stubs[i].stub_code + "_" + counter;
			alert("id_text: " + id_text);
			input.id  = id_text;
			//alert ("id_text:" + id_text);
			var input_label   = document.createElement("label");
			input_label.for =  res2.name + res2.stubs[i].stub_code;
			input_label.innerHTML = res2.stubs[i].stub_text + "_nxd";
			doc_frag2.appendChild( document.createElement("p"));
			doc_frag2.appendChild(input);
			doc_frag2.appendChild(input_label);
		}
		var dojoConfig = {
			parseOnLoad : true,
			async: 1,
		};
		//var stubs_form_div = document.getElementById("stubs_form_div");
		{
			var n_child_nodes = stubs_form_div.childNodes.length;
			alert ( "stubs_form_div.childNodes.length: " + stubs_form_div.childNodes.length);
			alert ("n_child_nodes:" + n_child_nodes);
			for (var i1 = n_child_nodes-1; i1 >= 0; --i1) {
				stubs_form_div.removeChild(stubs_form_div.childNodes[i1]);
			}
		}
		alert("cleared all childNodes of stubs_form_div");
		stubs_form_div.appendChild(doc_frag2);
		require([
		    "dojo/parser",
		    "dijit/form/RadioButton",
		    "dijit/form/Button", // used for example purpose
		    "dojo/domReady!"
		], function(parser, RadioButton){
			    parser.parse();
			    for (var i  = 0; i< res2.stubs.length; ++i ) {
			    var radioOne = new RadioButton({
				checked: false,
				value: res2.stubs[i].stub_code,
				name: "stub_response",
			    }, res2.name + res2.stubs[i].stub_code + "_" + counter);

				alert("id_text: " + id_text + "|" + res2.name + res2.stubs[i].stub_code + "_" + counter);
			}
		});
	};
	display_stubs (the_stub_data);
}


});
