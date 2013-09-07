mergeInto(LibraryManager.library, {

print_to_question_area: function (question_text_ptr)
{
	//alert("print_to_question_area: " + i );
	my_log("Enter: print_to_question_area: ");
	var the_question_text = Pointer_stringify (question_text_ptr);
	my_log(" question_text_ptr:" + the_question_text);
	var v = document.getElementById("question_text_area");
	var html = "<span deftext=\"true\" data-deftext=\"true\" id=\"lang_qtxt\" lang=\"en\">" + the_question_text + "</span>";
	if (v !== null) {
		v.innerHTML = html;
	} else {
		my_log ("failed to get html element question_text_area");
	}
	my_log("Exit: print_to_question_area: ");
	//alert(v.innerHTML);
},

print_to_stub_area: function (ptr_question_type, no_mpn, ptr_stub_info, counter, ptr_err_msg)
{
	my_log ("Enter: print_to_stub_area");
	//alert ("print_to_stub_area");
	//alert("print_to_question_area: " + i );
	//var v = document.getElementById("stubs_form_div");
	var question_type = Pointer_stringify (ptr_question_type);
	var stubs_form_div = document.getElementById("stubs_form_div");
	var the_stub_data = Pointer_stringify (ptr_stub_info);
	var err_msg = Pointer_stringify (ptr_err_msg);
	my_log ("err_msg: " + err_msg);

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
						//input.setAttribute("class", "custom");
						input.style.class="custom";
					}
					//input.name  = "stub_response";
					input.name  = "radio-choice";
					input.value = res2.stubs[i].stub_code;
					var id_text = res2.name + res2.stubs[i].stub_code + "_" + counter;
					//alert("id_text: " + id_text);
					input.id  = id_text;
					//alert ("id_text:" + id_text);
					var input_label   = document.createElement("label");
					input_label.innerHTML = res2.stubs[i].stub_text;
					input_label.setAttribute("for", id_text);
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

		} else {
			var input_text = document.createElement("input");
			input_text.type  = "text";
			doc_frag2.appendChild(input_text);
			input_text.setAttribute("data-dojo-type", "dojox/form/TextBox");
			clear_prev_node_sub_child (stubs_form_div);
			stubs_form_div.appendChild(doc_frag2);
		}

		//$( '#stubs_form_div' ).trigger( 'updatelayout' );
		$( '#stubs_form_div' ).trigger( 'create' );
		/*
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
		*/

		if (question_type != "nq" && no_mpn > 1) {
			my_log ("(question_type != \"nq\" && no_mpn > 1): creating verbatim_file_handle");
			var verbatim_response_path = "qscript/" +
					global_survey_related_info.device.uuid +
					"/project_name/interviewer_id/" +
					//global_survey_related_info.questionName_ +
					"q1_1" +
					".project_name_interviewer_id_" +
					global_survey_related_info.serial_no +
					".dat";
			my_log ("verbatim_response_path:" + verbatim_response_path);
			if (fileGetDir) {
				my_log("fileGetDir is present");
			}
			fileGetDir (verbatim_response_path, save_verbatim_data_file_handle,
				    {create: true, exclusive: true},
				    getFileErrorHandler,
				    {create_verbatim_handler: true});
		}
	};

	global_survey_related_info.no_mpn = no_mpn;
	global_survey_related_info.question_type = question_type;
	display_stubs (question_type, the_stub_data);

	window.lang.run();

	my_log ("Exit: print_to_stub_area");
},


/*
get_serial_no_from_dom: function (){
	var serial_no_input = document.getElementById("serial_no_input");
	// for now hardcode a serial no = 1001
	serial_no_input = 1001;
	return serial_no_input;
}
*/

save_qnre_data: function (survey_data_ptr)
{
	my_log ("Enter: save_qnre_data ");
	var the_survey_data = Pointer_stringify (survey_data_ptr);
	// Need to make the fail function the same global function for
	// error handling of files: getFileErrorHandler
	var fail = function (err_msg) {
		console.log(JSON.stringify(err_msg));
		my_log (JSON.stringify(err_msg));
	};

	var gotFileWriter = function (writer) {
		writer.write(the_survey_data);
	};

	//if ( global_current_survey_data_file)
	if (global_survey_related_info.current_survey_data_file ) {
		// global_current_survey_data_file.createWriter (gotFileWriter, fail);
		global_survey_related_info.current_survey_data_file.createWriter (gotFileWriter, fail);
	} else {
		my_log ("global_current_survey_data_file not available from dom_manip_funcs.js");
	}
	my_log ("exit : save_qnre_data");
},

show_end_of_qnre_page: function() {
	var div_serial_no = document.getElementById("div_serial_no");
	div_serial_no.style.display = "none";
	var question_view = document.getElementById("question_view");
	question_view.style.display = "none";
	var thank_you_screen = document.getElementById("thank_you_screen");
	thank_you_screen.style.display = "block";
},

create_question_form: function(question_json_ptr, stubs_json_ptr) {
	my_log ("Entered: create_question_form");
	var question_data = Pointer_stringify (question_json_ptr);
	my_log ("question_data: " + question_data);
	var stubs_data = Pointer_stringify (stubs_json_ptr);
	var stubs_obj_arr , questions_obj_arr;
	my_log ("stub_data: " + stubs_data);
	try {
		questions_obj_arr = JSON.parse(question_data);
		my_log ("parsed question_data");
	} catch (error) {
		my_log("Could not JSON.parse (question_data):" + error.message);
	}
	try {
		stubs_obj_arr = JSON.parse(stubs_data);
		my_log ("parsed stub_data");
	} catch (error) {
		my_log("Could not JSON.parse (stubs_data):" + error.message);
	}
	ui_create_question_form (questions_obj_arr, stubs_obj_arr);
}

});
