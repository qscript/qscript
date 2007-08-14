#ifndef XTCC_SYMTAB_H
#define XTCC_SYMTAB_H
#include <iostream>

	enum datatype {
		VOID_TYPE, 
		U_INT8_TYPE, INT8_TYPE, U_INT16_TYPE, INT16_TYPE, U_INT32_TYPE, INT32_TYPE, FLOAT_TYPE, DOUBLE_TYPE,
		U_INT8_ARR_TYPE, INT8_ARR_TYPE, U_INT16_ARR_TYPE, INT16_ARR_TYPE, U_INT32_ARR_TYPE, INT32_ARR_TYPE, FLOAT_ARR_TYPE, DOUBLE_ARR_TYPE,
		U_INT8_REF_TYPE, INT8_REF_TYPE, U_INT16_REF_TYPE, INT16_REF_TYPE, U_INT32_REF_TYPE, INT32_REF_TYPE, FLOAT_REF_TYPE, DOUBLE_REF_TYPE,
		error_type,
		texpr_stmt, assgn_stmt, cmpd_stmt, ife_stmt, decl_stmt, func_type, func_defn, for_stmt,
		lista_basic_type_stmt, lista_basic_arrtype_stmt_1index, lista_basic_arrtype_stmt_2index,
		break_stmt, continue_stmt,
		uninit 
	};
	/*enum decltype { array_decl, pointer_decl };*/

	struct noun_list_type {
		char * sym;
		enum datatype dt;
	};

	struct symtab_ent {
		char *name;
		char *text;
		union {
			double dval;
			int ival;
		};
		datatype type;
		/*decltype dcl_type;*/
		int n_elms;
		symtab_ent():name(NULL), text(NULL), dval(0), type(uninit), n_elms(0){
		}
		inline datatype get_type(){
			return type;
		}
		private:
			symtab_ent& operator=(const symtab_ent&);
			symtab_ent (const symtab_ent&);
	};


#endif /* XTCC_SYMTAB_H */
