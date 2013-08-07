mergeInto(LibraryManager.library, {

print_to_question_area: function (question_text_ptr)
{
	//alert("print_to_question_area: " + i );
	var the_question_text = Pointer_stringify (question_text_ptr);
	var v = document.getElementById("question_text_area");
	var html = "";
	html +=
		"<p>"
		+ the_question_text
		+ "</p>";
	v.innerHTML = html;
},

print_to_stub_area: function (ptr_question_type, no_mpn, ptr_stub_info, counter)
{

	//alert("print_to_question_area: " + i );
	//var v = document.getElementById("stubs_form_div");
	var question_type = Pointer_stringify (ptr_question_type);
	var stubs_form_div = document.getElementById("stubs_form_div");
	var the_stub_data = Pointer_stringify (ptr_stub_info);

	var clear_prev_node_sub_child = function (node) {
		var n_child_nodes = node.childNodes.length;
		for (var i1 = n_child_nodes-1; i1 >= 0; --i1) {
			node.removeChild(node.childNodes[i1]);
		}
	};


	var display_stubs = function (question_type, json_rep2) {
		var doc_frag2 = document.createDocumentFragment();
		if (question_type === "nq") {
			var res2 = JSON.parse(json_rep2);
			//alert (res2.name);
			//alert (res2.stubs);
			// global - counter variable
			var my_li = null;
			for (var i=0; i<res2.stubs.length;  ++i) {
				if (res2.stubs[i].mask == 1) {
					var input   = document.createElement("input");
					if (no_mpn == 1) {
						input.type  = "radio";
						//input.setAttribute("data-dojo-type", "dojox/mobile/RadioButton");
						//input.setAttribute("data-dojo-type", "dijit/form/RadioButton");
						input.setAttribute("data-dojo-type", "dojox/mobile/RadioButton");
					} else {
						input.type  = "checkbox";
						//input.setAttribute("data-dojo-type", "dojox/mobile/CheckBox");
						//input.setAttribute("data-dojo-type", "dijit/form/CheckBox");
						input.setAttribute("data-dojo-type", "dojox/mobile/CheckBox");
					}
					input.name  = "stub_response";
					input.value = res2.stubs[i].stub_code;
					var id_text = res2.name + res2.stubs[i].stub_code + "_" + counter;
					//alert("id_text: " + id_text);
					input.id  = id_text;
					//alert ("id_text:" + id_text);
					var input_label   = document.createElement("label");
					//input_label.for =  res2.name + res2.stubs[i].stub_code;
					input_label.innerHTML = res2.stubs[i].stub_text;
					//input_label.for =  id_text;
					input_label.setAttribute("for", id_text);
					//doc_frag2.appendChild( document.createElement("p"));
					//doc_frag2.appendChild(input);
					//doc_frag2.appendChild(input_label);
					my_li = document.createElement("li");
					my_li.appendChild(input);
					my_li.appendChild(input_label);
					my_li.setAttribute("data-dojo-type", "dojox/mobile/ListItem");
					doc_frag2.appendChild(my_li);
				}
			}

			/*
			//var stubs_form_div = document.getElementById("stubs_form_div");
			{
				var n_child_nodes = stubs_form_div.childNodes.length;
				//alert ( "stubs_form_div.childNodes.length: " + stubs_form_div.childNodes.length);
				//alert ("n_child_nodes:" + n_child_nodes);
				for (var i1 = n_child_nodes-1; i1 >= 0; --i1) {
					stubs_form_div.removeChild(stubs_form_div.childNodes[i1]);
				}
			}
			//alert("cleared all childNodes of stubs_form_div");
			*/
			clear_prev_node_sub_child (stubs_form_div);

			stubs_form_div.appendChild(doc_frag2);


			/*
			require([
				"dojox/mobile/parser",
				"dojox/mobile",
				"dojox/mobile/deviceTheme",
				"dojox/mobile/compat",
				"dojo/domReady!"
				],
				function(parser) {
					parser.parse();
				});
			*/
		/*
			require([
			    "dojo/parser",
			    "dojo/dom",
			    "dijit/form/RadioButton",
			    "dijit/form/CheckBox",
			    "dijit/form/TextBox",
			    "dijit/form/Button", // used for example purpose
			    "dojo/domReady!"
			], function(parser, dom){
				parser.parse({
					//rootNode: dom.byId("stubs_form_div")
					rootNode: stubs_form_div
				});
			});
		*/

			require([
			         "dojo/parser",
			         "dojox/mobile/parser",
			         "dojo/dom",
				 "dojox/mobile",
				 "dojox/mobile/deviceTheme",
				 "dojox/mobile/compat",
				 "dojo/domReady!"
			],
			function(parser, dom) {
				parser.parse({
					rootNode: stubs_form_div
				});
			});

		} else {
			var input_text = document.createElement("input");
			input_text.type  = "text";
			doc_frag2.appendChild(input_text);
			input_text.setAttribute("data-dojo-type", "dojox/form/TextBox");
			clear_prev_node_sub_child (stubs_form_div);
			stubs_form_div.appendChild(doc_frag2);
		}
	};

	var make_sencha_form_string = function (json_rep2) {
		var stubs = JSON.parse(json_rep2);
		var sencha_form_string = "{";
		sencha_form_string += "xtype: \"fieldset\"," +
					"title: \"Satisfaction Scale\"," +
					"layout: 'anchor'," +
					"items: [{" +
					"xtype: \"radiogroup\"," +
					"cls: 'x-check-group-alt'," +
					"columns: 1," +
					"items: [" ;
		//{ boxLabel: "Very Satisfied", name: "rb-auto", inputValue: 5},
		for (var i=0; i<stubs.stubs.length; ++i) {
			if (i!=0) {
				sencha_form_string += ","
			}
			sencha_form_string += "{" +
				"boxLabel: \"" + stubs.stubs[i].stub_text +"\"," +
				"name: \"rb-auto\"," +
				"inputValue: " + stubs.stubs[i].stub_code +
				"}";
		}
		sencha_form_string += 		"]" +
					"}]";
		sencha_form_string += "}";
		return sencha_form_string;
	};

	var make_sencha_form_obj = function (json_rep2, no_mpn) {
		var stubs = JSON.parse(json_rep2);
		var sencha_form_obj = {};
		/*
		sencha_form_string += "xtype: \"fieldset\"," +
					"title: \"Satisfaction Scale\"," +
					"layout: 'anchor'," +
					"items: [{" +
					"xtype: \"radiogroup\"," +
					"cls: 'x-check-group-alt'," +
					"columns: 1," +
					"items: [" ;
					*/
		sencha_form_obj.xtype = "fieldset";
		sencha_form_obj.title = "Satisfaction Scale";
		sencha_form_obj.layout = "anchor";
		var items_array = [];
		var items_array_obj = {};
		if (no_mpn == 1) {
			items_array_obj.xtype = "radiogroup";
		} else {
			items_array_obj.xtype = "checkboxgroup";
		}
		items_array_obj.cls = "x-check-group-alt";
		items_array_obj.columns = 1;
		var items_array_obj_array = [];



		//{ boxLabel: "Very Satisfied", name: "rb-auto", inputValue: 5},
		for (var i=0; i<stubs.stubs.length; ++i) {
			/*
			if (i!=0) {
				sencha_form_string += ","
			}
			sencha_form_string += "{" +
				"boxLabel: \"" + stubs.stubs[i].stub_text +"\"," +
				"name: \"rb-auto\"," +
				"inputValue: " + stubs.stubs[i].stub_code +
				"}";
			*/
			var items_array_obj_array_obj = {};
			items_array_obj_array_obj.boxLabel = stubs.stubs[i].stub_text;
			items_array_obj_array_obj.name = "rb-auto";
			items_array_obj_array_obj.inputValue = stubs.stubs[i].stub_code;
			items_array_obj_array.push(items_array_obj_array_obj);
		}
		items_array_obj.items = items_array_obj_array;
		sencha_form_obj.items = [];
		sencha_form_obj.items.push(items_array_obj);
		return sencha_form_obj;

		//sencha_form_string += 		"]" +
		//			"}]";
		//sencha_form_string += "}";
		//return sencha_form_string;

	};

	display_stubs (question_type, the_stub_data);
	/*
	if (question_type === "nq") {
		display_stubs (question_type, the_stub_data);
		//var sencha_form_string = make_sencha_form_string(the_stub_data);
		//var sencha_form_obj = make_sencha_form_obj(the_stub_data, no_mpn);
	} else {
		// display a text box here
		// maybe add validators
	}
	*/
}


});
