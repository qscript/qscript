#ifndef qscript_user_input
#define qscript_user_input

#include "user_navigation.h"
#include "UserResponse.h"
struct UserInput
{
	UserNavigation userNavigation_;
	//string question_response;
	//vector <int> inputData_;
	vector<string> questionResponseDataVec_;
	user_response::UserResponseType theUserResponse_;
	UserInput():
		userNavigation_(NOT_SET),
		//inputData_(),
		questionResponseDataVec_(),
		theUserResponse_(user_response::NotSet)
	{}
};

#endif /* qscript_user_input */
