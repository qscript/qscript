#ifndef XTCC_SYMTAB_H
#define XTCC_SYMTAB_H
//#include <iostream>
#include <cstring>

	enum DataType {
		VOID_TYPE
		, INT8_TYPE,  INT16_TYPE,  INT32_TYPE, FLOAT_TYPE, DOUBLE_TYPE
		, INT8_ARR_TYPE, INT16_ARR_TYPE, INT32_ARR_TYPE, FLOAT_ARR_TYPE
		, DOUBLE_ARR_TYPE
		, INT8_REF_TYPE, INT16_REF_TYPE, INT32_REF_TYPE, FLOAT_REF_TYPE
		, DOUBLE_REF_TYPE
		, BOOL_TYPE
		, ERROR_TYPE
		, TEXPR_STMT, CMPD_STMT, IFE_STMT, DECL_STMT, FUNC_TYPE
		, FUNC_DEFN, FOR_STMT
		, LISTA_BASIC_TYPE_STMT, LISTA_BASIC_ARRTYPE_STMT_1INDEX
		, LISTA_BASIC_ARRTYPE_STMT_2INDEX
		, BREAK_STMT, CONTINUE_STMT, RANGE_DECL_STMT
		, QUESTION_TYPE, STRING_TYPE, STRING_ARR_TYPE
		, NAMED_ATTRIBUTE_TYPE, UNNAMED_RANGE,
		uninit 
	};
	bool check_type_compat(DataType typ1, DataType typ2);

	bool is_of_int_type(DataType dt);
	bool is_of_noun_type(DataType dt);
	bool is_of_noun_ref_type(DataType dt);
	bool is_of_arr_type(DataType dt);
	bool is_of_int_arr_type(DataType dt);
	bool is_of_int32_arr_type(DataType dt);
	DataType convert_ref_type(DataType dt);
#include <string>
using	std::string ;
	string human_readable_type(DataType dt);

		/*enum decltype { array_decl, pointer_decl };*/


	struct noun_list_type {
		const char * sym;
		enum DataType dt;
	};
namespace Expression {
	struct AbstractExpression;
}
struct XtccSet;
struct SymbolTableEntry {
	char *name_;
	char *text_;
	union {
		double dval;
		int ival;
	};
	DataType type_;
	/*decltype dcl_type;*/
	int n_elms;
	bool created_by_me;
	Expression::AbstractExpression * e;
	XtccSet * xs;
	int nest_level;
	SymbolTableEntry()
		: name_(0), text_(0), dval(0)
		, type_(uninit), n_elms(0), created_by_me(false),e(0), xs(0)
		, nest_level (0)
	{ }
	SymbolTableEntry (const char * lname, DataType ldt, int l_nest_level):
		name_(strdup(lname)), text_(0), dval(0)
		, type_(ldt), n_elms(-1), created_by_me(true), e(0), xs(0)
		, nest_level (l_nest_level)
	{ }
	SymbolTableEntry (const char * lname, DataType ldt
			 , Expression::AbstractExpression* le
			 , int l_nest_level)
		: name_(strdup(lname)), text_(0), dval(0), type_(ldt)
		  , n_elms(-1), created_by_me(true), e(le), xs(0)
		  , nest_level (l_nest_level)
	{ }
	SymbolTableEntry (const char * lname, DataType ldt, XtccSet * xs
			 , int l_nest_level);
	inline DataType get_type(){
		return type_;
	}
	~SymbolTableEntry();
	private:
		SymbolTableEntry& operator= (const SymbolTableEntry&);
		SymbolTableEntry (const SymbolTableEntry&);
};


#endif /* XTCC_SYMTAB_H */
