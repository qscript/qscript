#ifndef XTCC_SYMTAB_H
#define XTCC_SYMTAB_H
#include <iostream>

	enum datatype {
		VOID_TYPE, 
		U_INT8_TYPE, INT8_TYPE, U_INT16_TYPE, INT16_TYPE, U_INT32_TYPE, INT32_TYPE, FLOAT_TYPE, DOUBLE_TYPE,
		U_INT8_ARR_TYPE, INT8_ARR_TYPE, U_INT16_ARR_TYPE, INT16_ARR_TYPE, U_INT32_ARR_TYPE, INT32_ARR_TYPE, FLOAT_ARR_TYPE, DOUBLE_ARR_TYPE,
		U_INT8_REF_TYPE, INT8_REF_TYPE, U_INT16_REF_TYPE, INT16_REF_TYPE, U_INT32_REF_TYPE, INT32_REF_TYPE, FLOAT_REF_TYPE, DOUBLE_REF_TYPE,
		ERROR_TYPE,
		TEXPR_STMT, CMPD_STMT, IFE_STMT, DECL_STMT, FUNC_TYPE, FUNC_DEFN, FOR_STMT,
		LISTA_BASIC_TYPE_STMT, LISTA_BASIC_ARRTYPE_STMT_1INDEX, LISTA_BASIC_ARRTYPE_STMT_2INDEX,
		BREAK_STMT, CONTINUE_STMT,
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
		bool created_by_me;
		symtab_ent():name(0), text(0), dval(0), type(uninit), n_elms(0), created_by_me(false){
		}
		symtab_ent(char * lname, datatype ldt):
			name(strdup(lname)), text(0), dval(0), type(ldt), n_elms(-1), created_by_me(true)
		{ }
		inline datatype get_type(){
			return type;
		}
		~symtab_ent(){
			std::cout << "deleting symtab_ent: name: " << name << std::endl;
			if(name&& created_by_me) { free( name); name=0; }
			if(text) { delete text; text=0; }
			std::cout << "FINISHED deleting symtab_ent" << std::endl;
		}
		private:
			symtab_ent& operator=(const symtab_ent&);
			symtab_ent (const symtab_ent&);
	};


#endif /* XTCC_SYMTAB_H */
