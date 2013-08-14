

	/* Next Question Button {{{2 */
	var nextQ = document.getElementById("nextQ");
	EventUtil.addHandler (nextQ, "click", function(event) {
		//event = EventUtil.getEvent (event);
		//EventUtil.preventDefault (event);
		var called_from_the_dom = Module.cwrap ('called_from_the_dom', 'void', ['string']);
		//var data_for_cpp;
		//Module.setValue (data_for_cpp, "hey mr cpp function - how you doing. This is a js func calling from the dom", "i8*");
		//called_from_the_dom(data_for_cpp);
		//called_from_the_dom("hey mr cpp function - how you doing. This is a js func calling from the dom");
		//alert("this is the DOM brother");
		//console.log("submit handler called");
		var returnValue = serialize (question_form);
		//var data_for_cpp;
		//Module.setValue (data_for_cpp, returnValue, "i8*");
		called_from_the_dom(returnValue);
	});
	//my_log ("created submit handler function");
	/* Next Question Button }}}2 */

/* handleStartSurveyButton  {{{2 */
	var return_serial_no_button = document.getElementById("btn_return_serial_no");
	function handleStartSurveyButton (event)
	{
		my_log ("Enter: handleStartSurveyButton");
		var question_view = document.getElementById("question_view");
		//alert("question_view:" + question_view);
		//var attr = document.createAttribute("display");
		//attr.value = "block";
		//question_view.setAttributeNode(attr);
		var txt_serial_no = document.getElementById("txt_serial_no");
		var serial_no = txt_serial_no.value;
		//alert ("serial_no: " + serial_no);
		var re_chk_serial = /\d+/;
		var test_numeric_serial =  re_chk_serial.test(serial_no);
		if (test_numeric_serial === false) {
			alert ("Please enter a valid serial no" );
		}
		// Sanity checks
		var all_systems_go = false;
		//alert ("global_survey_related_info: uuid" + gl)
		//my_log ("global_survey_related_info.uuid: " + global_survey_related_info.device.uuid);
		//my_log ("global_survey_related_info.latitude: " + global_survey_related_info.position.coords.latitude);
		if (
			test_numeric_serial &&
			global_survey_related_info.device && global_survey_related_info.device.uuid &&
			global_survey_related_info.position && global_survey_related_info.position.coords &&
			global_survey_related_info.fileSystemObject)  {
			question_view.style.display = "block";
			var div_serial_no = document.getElementById("div_serial_no");
			div_serial_no.style.display = "none";
			return_serial_no_button.disabled = true;
			my_log ("sanity checks passed");
			var our_path = "qscript/" +
					global_survey_related_info.device.uuid +
					"/project_name/interviewer_id/project_name_interviewer_id_" +
					serial_no +
					".dat";
			//alert ("our_path:" + our_path);
			// first try to open the file and see if it exists
			my_log("opening file:" + our_path);
			global_survey_related_info.open_file_path = our_path;
			global_survey_related_info.fileSystemObject.root.getFile(
				our_path, {create: false, exclusive: true}, gotFileEntry, getFileErrorHandler);
			//global_survey_related_info.fileSystemObject.root.getFile("qscript/uuid/project_name/interviewer_id/project_name_interviewer_id_serial.dat", null, gotFileEntry, getFileErrorHandler);
			// if successful, we need to merge in the survey data into the qnre
			// so that eval correctly returns the next question to be asked
			// otherwise open the path piecewise - constructing intermediate directories on the way
			//fileGetDir (our_path, printSuccess, false, getFileErrorHandler);
			//all_systems_go = true;
		} else {
			my_log ("cordova : sanity checks failed");
			// my_log ("global_survey_related_info.device: " + global_survey_related_info.device);
			// my_log ("global_survey_related_info.position: " + global_survey_related_info.position);
			// my_log ("global_survey_related_info.fileSystemObject: " + global_survey_related_info.fileSystemObject);
		}
		//my_log (" after sanity checks");
		var callback_return_serial = Module.cwrap ('callback_return_serial', 'void', ['int', 'string']);
		if (/*all_systems_go && */ callback_return_serial) {
			//console.log("returning serial no to c++ code");
			// add check on serial no here.
			callback_return_serial (txt_serial_no.value, "");
		} else {
			my_log ("Could not find callback_return_serial in Module.cwrap");
		}
		//var callback_return_serial = Module.cwrap ('callback_return_serial', 'void', ['int', 'string']);
		//callback_return_serial (serial_no);
	}
	EventUtil.addHandler (return_serial_no_button, "click", handleStartSurveyButton);
	//my_log ("created handleStartSurveyButton function");
/* handleStartSurveyButton  }}}2 */
