

	/* ====== lang  {{{1=======*/

	window.lang = new jquery_lang_js();
	$().ready(function () {
		window.lang.run();
	});


	var btn_chg_lang_en = document.getElementById("btn_chg_lang_en");
	function change_language_en () {
		my_log ("Enter: change_language_en");
		window.lang.change("en");
		my_log ("Exit: change_language_en");
	}
	EventUtil.addHandler (btn_chg_lang_en, "click", change_language_en);

	var btn_chg_lang_hi = document.getElementById("btn_chg_lang_hi");
	function change_language_hi () {
		//alert ("Enter: change_language_hi");
		//window.lang.run();
		if (window.lang) {
			my_log("change_language_hi: has lang");
			window.lang.change("hi");
		} else {
			my_log("change_language_hi: does not have lang");
		}
		my_log ("Exit: change_language_hi");
	}
	EventUtil.addHandler (btn_chg_lang_hi, "click", change_language_hi);
	my_log ("fired all event handlers");
	/* ====== lang  }}}1=======*/
