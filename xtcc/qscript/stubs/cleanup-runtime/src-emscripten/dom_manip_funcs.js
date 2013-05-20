mergeInto(LibraryManager.library, {

print_to_question_area: function (i)
{
	//alert("print_to_question_area: " + i );
	var v = document.getElementById("question_text_area");
	var html = "";
	html +=
		"<p>"
		+ "some data from the cpp program"
		+ i
		+ "</p>";
	v.innerHTML = html;
},


print_to_stub_area: function (string_pointer)
{
	//alert("print_to_question_area: " + i );
	var v = document.getElementById("question_stub_area");
	var the_stub_data = Pointer_stringify (string_pointer);
	var html = "";
	html +=
		"<p>"
		+ "stub data from the cpp program"
		+ the_stub_data
		+ "</p>";
	v.innerHTML = html;
}

});
