#ifndef qscript_ui_return_value_h
#define qscript_ui_return_value_h

struct UIReturnValue {
	bool answered_;
	string textData_;
	UIReturnValue () :
		answered_(false), textData_()
	{ }
};

#endif /* qscript_ui_return_value_h */
