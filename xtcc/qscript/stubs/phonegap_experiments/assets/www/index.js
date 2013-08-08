/* Professional JavaScript for Web Developers - Nicholas C Zakas. Chpt 12*/
var EventUtil = {
	addHandler: function (element, type, handler) {
		if (element.addEventListener) {
			element.addEventListener (type, handler, false);
		} else if (element.attachEvent) {
			element.attachEvent ("on" + type, handler);
		} else {
			element["on" + type] = handler;
		}
	},
	getEvent: function (event) {
		return event ? event : window.event;
	},
	getTarget: function (event) {
		return event.target || event.srcElement;
	},
	preventDefault: function (event) {
		if (event.preventDefault) {
			event.preventDefault();
		} else {
			event.returnValue = false;
		}
	},
	removeHandler: function (element, type, handler) {
		if (element.removeEventListener) {
			element.removeEventListener (type, handler, false);
		} else if (element.detachEvent) {
			element.detachEvent ("on" + type, handler);
		} else {
			element["on" + type] = null;
		}
	},
	stopPropagation: function (event) {
		if (event.stopPropagation) {
			event.stopPropagation();
		} else {
			event.cancelBubble = true;
		}
	}
};

global_survey_related_info = {};




function my_log (mesg)
{
	var div_console_log = document.getElementById("div_console_log");
	div_console_log.innerHTML += "<p><pre>" + mesg + "</pre></p>";
}
my_log ("test log message");

/* ============== Device Info ================================= */
function get_device_info()
{
	//var div_has_PhoneGap = document.getElementById ("div_has_PhoneGap");
	//if (div_has_PhoneGap) {
	//	div_has_PhoneGap.innerHTML = "PhoneGap library loaded successfully.";
	//}
	//var div_device_properties = document.getElementById ("div_device_properties");
	if (window.device) {
		///
		//div_device_properties.innerHTML =
		//	'Device Name: '     + device.name     + '<br />' +
		//	'Device Cordova: '  + device.cordova + '<br />' +
		//	'Device Platform: ' + device.platform + '<br />' +
		//	'Device UUID: '     + device.uuid     + '<br />' +
		//	'Device Model: '    + device.model     + '<br />' +
		//	'Device Version: '  + device.version  + '<br />';
		///
		//global_survey_related_info.device_name = device.name;
		//global_survey_related_info.device_cordova = device.cordova;
		//global_survey_related_info.device_platform = device.platform;
		//global_survey_related_info.device_uuid = device.uuid;
		//global_survey_related_info.device_model = device.model;
		//global_survey_related_info.device_version = device.version;
		global_survey_related_info.device = device;
		return true;
	} else {
		//div_device_properties.innerHTML = "does not have device property";
		// my_log ("DOES NOT HAVE DEVICE PROPERTY");
		return false;
	}
}
//my_log ("created get_device_info function");
/* ============== End: Device Info ================================= */

/* ===================== FileSystem ========================= */

function onFileSystemSuccess (fileSystem) {
	//fileSystemObject = fileSystem;
	//my_log("assigned fileSystemObject fileSystem.name:" + fileSystem.name);
	//my_log("assigned fileSystemObject fileSystemObject.name:" +  fileSystem.name);
	//my_log("assigned fileSystemObject fileSystemObject.root.name:" +  fileSystem.root.name);
	//my_log("assigned fileSystemObject fileSystemObject.root.fullPath:" +  fileSystem.root.fullPath);
	//my_log("assigned fileSystemObject fileSystemObject.root.isDirectory:" +  fileSystem.root.isDirectory);
	global_survey_related_info.fileSystemObject = fileSystem;
}

function fileFSError(e) {
	//console.log(e.code);
	//try {
	//	my_log ("fileFSError: " + JSON.stringify(e));
	//} catch (err) {}
	my_log ("=== ERROR ====  fileFSError: " + JSON.stringify(e));
}



function getFileSystemObject () {
//my_log("Enter: getFileSystemObject");
window.requestFileSystem(LocalFileSystem.PERSISTENT, 0, onFileSystemSuccess, fileFSError);
}

/* ===================== End FileSystem ========================= */

/* ===================== File api =============== */

	function gotFileEntry(fileEntry) {
		my_log("Enter: gotFileEntry");
		fileEntry.file(gotFile, getFileErrorHandler);
	}

	function readAsText(file) {
		my_log ("Enter: readAsText");
		var reader = new FileReader();
		reader.onloadend = function(evt) {
			my_log("Read as text:");
			my_log(evt.target.result);
			var callback_return_serial = Module.cwrap ('callback_return_serial', 'void', ['int', 'string']);
			my_log ("callback_return_serial:" + callback_return_serial);
			callback_return_serial (56, evt.target.result);
		};
		reader.readAsText(file);
	}


	function gotFile(file){
		my_log("Enter: gotFile");
		//readDataUrl(file);
		readAsText(file);
	}

	function getFileErrorHandler (file_error) {
		var file_err_string =
			" file_error.NOT_FOUND_ERR              "   +  file_error.NOT_FOUND_ERR + "<br />" +
			" file_error.SECURITY_ERR               "   +  file_error.SECURITY_ERR + "<br />" +
			" file_error.ABORT_ERR                  "   +  file_error.ABORT_ERR + "<br />" +
			" file_error.NOT_READABLE_ERR           "   +  file_error.NOT_READABLE_ERR + "<br />" +
			" file_error.ENCODING_ERR               "   +  file_error.ENCODING_ERR + "<br />" +
			" file_error.NO_MODIFICATION_ALLOWED_ERR"   +  file_error.NO_MODIFICATION_ALLOWED_ERR + "<br />" +
			" file_error.INVALID_STATE_ERR          "   +  file_error.INVALID_STATE_ERR + "<br />" +
			" file_error.SYNTAX_ERR                 "   +  file_error.SYNTAX_ERR + "<br />" +
			" file_error.INVALID_MODIFICATION_ERR   "   +  file_error.INVALID_MODIFICATION_ERR + "<br />" +
			" file_error.QUOTA_EXCEEDED_ERR         "   +  file_error.QUOTA_EXCEEDED_ERR + "<br />" +
			" file_error.TYPE_MISMATCH_ERR          "   +  file_error.TYPE_MISMATCH_ERR + "<br />" +
			" file_error.PATH_EXISTS_ERR            "   +  file_error.PATH_EXISTS_ERR + "<br />"
			;
		my_log (file_err_string);
	}


/* ===================== End: File api =============== */


/* ============== Initialization ================== */
function onDeviceReady() {
	//my_log("Enter onDeviceReady");
	var success = false;
	success = get_device_info();
	if (success == false) {
		my_log ("Unable to get device information ... exiting the survey");
		return false;
	}
	//success = get_compass_info();
	//if (success == false) {
	//	my_log ("Unable to get compass information ... exiting the survey");
	//	return false;
	//}
	//success = get_geolocation_info();
	//if (success == false) {
	//	my_log ("Unable to get geolocation information ... exiting the survey");
	//	return false;
	//}
	success = getFileSystemObject();
	if (success == false) {
		my_log ("Unable to get LocalFileSystem ... exiting the survey");
		return false;
	}
	// allow to click on start only after initializing all the things we need
	var return_serial_no_button = document.getElementById("btn_return_serial_no");
	return_serial_no_button.disabled = false;
	my_log("ready to start interview");
	// var our_path = "qscript/uuid/project_name/interviewer_id/project_name_interviewer_id_serial.dat";
	// fileGetDir (our_path, printSuccess);
}
//my_log("created onDeviceReady");
document.addEventListener ("deviceready", onDeviceReady, false);

/* ============== Initialization ================== */

var test_file_read_success = document.getElementById("test_file_read_success");
function test_file_read_success_handler ()
{
	my_log ("Enter: test_file_read_success_handler");
	var our_path = "qscript/" +
					global_survey_related_info.device.uuid +
					"/project_name/interviewer_id/project_name_interviewer_id_56.dat";
					//serial_no +
					//".dat"
					//;
	my_log ("our_path:" + our_path);
	// first try to open the file and see if it exists
	my_log("opening file:" + our_path);
	global_survey_related_info.fileSystemObject.root.getFile(
		our_path, {create: false, exclusive: true}, gotFileEntry, getFileErrorHandler);
}
EventUtil.addHandler (test_file_read_success, "click", test_file_read_success_handler);


var test_file_read_failure = document.getElementById("test_file_read_failure");
function test_file_read_failure_handler ()
{
	my_log ("Enter: test_file_read_failure_handler");
	var our_path = "qscript/" +
					global_survey_related_info.device.uuid +
					"/project_name/interviewer_id/project_name_interviewer_id_does_not_exist.dat";
					//serial_no +
					//".dat"
					//;
	my_log ("our_path:" + our_path);
	// first try to open the file and see if it exists
	my_log("opening file:" + our_path);
	global_survey_related_info.fileSystemObject.root.getFile(
		our_path, {create: false, exclusive: true}, gotFileEntry, getFileErrorHandler);
}
EventUtil.addHandler (test_file_read_failure, "click", test_file_read_failure_handler);


var test_file_read_failure_middle_dir_missing = document.getElementById("test_file_read_failure_middle_dir_missing");
function test_file_read_failure_middle_dir_missing_handler ()
{
	my_log ("Enter: test_file_read_failure_middle_dir_missing_handler");
	var our_path = "qscript/" +
					global_survey_related_info.device.uuid +
					"/project_name_missing/interviewer_id/project_name_interviewer_id_does_not_exist.dat";
					//serial_no +
					//".dat"
					//;
	my_log ("our_path:" + our_path);
	// first try to open the file and see if it exists
	my_log("opening file:" + our_path);
	global_survey_related_info.fileSystemObject.root.getFile(
		our_path, {create: false, exclusive: true}, gotFileEntry, getFileErrorHandler);
}
EventUtil.addHandler (test_file_read_failure_middle_dir_missing, "click", test_file_read_failure_middle_dir_missing_handler);

