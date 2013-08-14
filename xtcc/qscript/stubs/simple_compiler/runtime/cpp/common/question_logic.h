#ifndef qscript_question_logic_h
#define qscript_question_logic_h

bool eval_single_question_logic_with_input (UserInput p_user_input,
		const vector<AbstractRuntimeQuestion *> & q_vec,
		struct TheQuestionnaire * theQuestionnaire, int nest_level,
		vector <string> & err_mesg_vec);

#endif /* qscript_question_logic_h */
