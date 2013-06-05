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

// 3-jun-2013. Newly added here
my_createForm: function (the_data)
{
    // combine all that into one huge form
    //alert ("Ext.create:" + Ext.create);
    console.log ("Ext.create: " + Ext.create);
    var fp = Ext.create('Ext.FormPanel', {
	title: 'Check/Radio Groups Example',
	frame: false,
	fieldDefaults: {
	    labelWidth: 110,
	    labelStyle: 'color:green;padding-left:4px'
	},
	width: 600,
	renderTo:'form-ct',
	bodyPadding: 10,
	items: [
	    //agree_5_rg
	    the_data
	],
	buttons: [{
	    text: 'Save',
	    handler: function(){
	       if(fp.getForm().isValid()){
		    Ext.Msg.alert('Submitted Values', 'The following will be sent to the server: <br />'+
			fp.getForm().getValues(true).replace(/&/g,', '));
		}
	    }
	},{
	    text: 'Reset',
	    handler: function(){
		fp.getForm().reset();
	    }
	}]
    });
},

print_to_stub_area: function (ptr_question_type, no_mpn, ptr_stub_info, counter)
{
	/*
	 * Activate this when we restart with sencha
	Ext.require([
	    'Ext.form.*',
	    'Ext.layout.container.Column',
	    'Ext.window.MessageBox',
	    'Ext.fx.target.Element'
	]);
	*/
	//alert("print_to_question_area: " + i );
	//var v = document.getElementById("stubs_form_div");
	var question_type = Pointer_stringify (ptr_question_type);
	var stubs_form_div = document.getElementById("stubs_form_div");
	var the_stub_data = Pointer_stringify (ptr_stub_info);
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
			if (no_mpn == 1) {
				input.type  = "radio";
				input.setAttribute("data-dojo-type", "dojox/mobile/RadioButton");
			} else {
				input.type  = "checkbox";
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
			doc_frag2.appendChild(input);
			doc_frag2.appendChild(input_label);
		}

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
		stubs_form_div.appendChild(doc_frag2);


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
		/*
		var dojoConfig = {
			parseOnLoad : true,
			async: 1,
		};
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

				//alert("id_text: " + id_text + "|" + res2.name + res2.stubs[i].stub_code + "_" + counter);
			}
		});
		*/
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


	/*
	var my_createForm = function (the_data) {
	    // combine all that into one huge form
	    //alert ("Ext.create:" + Ext.create);
	    console.log ("Ext.create: " + Ext.create);
	    var fp = Ext.create('Ext.FormPanel', {
		title: 'Check/Radio Groups Example',
		frame: false,
		fieldDefaults: {
		    labelWidth: 110,
		    labelStyle: 'color:green;padding-left:4px'
		},
		width: 600,
		renderTo:'form-ct',
		bodyPadding: 10,
		items: [
		    //agree_5_rg
		    the_data
		],
		buttons: [{
		    text: 'Save',
		    handler: function(){
		       if(fp.getForm().isValid()){
			    Ext.Msg.alert('Submitted Values', 'The following will be sent to the server: <br />'+
				fp.getForm().getValues(true).replace(/&/g,', '));
			}
		    }
		},{
		    text: 'Reset',
		    handler: function(){
			fp.getForm().reset();
		    }
		}]
	    });
	};
	*/

	if (question_type === "nq") {
		display_stubs (the_stub_data);
		var sencha_form_string = make_sencha_form_string(the_stub_data);
		//console.log(sencha_form_string);
		var sencha_form_obj = make_sencha_form_obj(the_stub_data, no_mpn);

		/*
		var yn = {
				xtype: "fieldset",
				title: "Satisfaction Scale",
				layout: 'anchor',
				items: [{
				xtype: "radiogroup",
				cls: 'x-check-group-alt',
				columns: 1,
				items: [{boxLabel: "Yes",name: "rb-auto",inputValue: 1},
					{boxLabel: "No",name: "rb-auto",inputValue: 2}
				]
			}]
		};
		*/
		//console.log("yn                :" + yn);
		//console.log("sencha_form_string:" + sencha_form_string);
		//var parse_sencha_form_string = JSON.parse(sencha_form_string);
		//console.log("p sn              :" + parse_sencha_form_string);
		//console.log("sencha_form_obj   :" + sencha_form_obj);
		//console.log("yn  toString():" + yn.toString());
		//console.log("obj toString():" + sencha_form_obj.toString());
		//console.log("yn  toString():" + JSON.stringify(yn));
		//console.log("obj toString():" + JSON.stringify(sencha_form_obj));
		//if (sencha_form_obj == yn) {
		//	console.log("sencha_form_obj == yn");
		//} else {
		//	console.log("sencha_form_obj != yn");
		//}

		//Ext.onReady(my_createForm(yn));
		//alert ("sencha_form_string:" + sencha_form_string);
		//var my_createForm = Module.cwrap ('my_createForm', 'void', ['string']);
		//alert ("my_createForm: " + my_createForm);
		//alert ("createForm: " + createForm);
		//console.log (createForm);

		//Ext.onReady(createForm(yn));
		//Ext.EventManager.onDocumentReady(createForm(sencha_form_string));
		// nxd : 4-jun-2013 - this works,
		// deactivate it for now as we are working with dojo
		//Ext.onReady(createForm(sencha_form_obj));

		//Ext.onReady(my_createForm (sencha_form_string));
	} else {
		// display a text box here
		// maybe add validators
	}
}


});
