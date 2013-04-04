#ifndef person_info_h
#define person_info_h
#include <string>

struct PersonInfo {

	std::string first_name;
	std::string last_name;
	std::string second_name;
	std::string third_name;
	std::string fourth_name;
	std::string fifth_name;


	std::string first_initial;
	std::string last_initial;
	std::string second_initial;
	std::string third_initial;
	std::string fourth_initial;
	std::string fifth_initial;

	int max_names;
	int rm_code;

	PersonInfo (
		std::string p_first_name,
		std::string p_last_name,
		int p_rm_code
		)
		: first_name(p_first_name),
		  last_name (p_last_name),
		  rm_code (p_rm_code)
	{ }
	friend std::ostream& operator<<(std::ostream& os,const PersonInfo& p_inf)
	{
		os 	<< "fname: " << p_inf.first_name
			<< ", lname: "<< p_inf.last_name
			<<", rm_code "<< p_inf.rm_code
			<<std::endl;
		return os;
	}

};

	struct first_name{};
	struct last_name{};
	struct second_name{};
	struct third_name{};
	struct fourth_name{};
	struct fifth_name{};
	struct rm_code{};

#endif /* person_info_h */
