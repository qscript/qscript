
expression: expression '+' expression {
		$$=new bin_expr($1, $3, oper_plus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '-' expression {
		$$=new bin_expr($1, $3, oper_minus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '*' expression {
		$$=new bin_expr($1, $3, oper_mult);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '/' expression {
		$$=new bin_expr($1, $3, oper_div);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '%' expression {
		$$=new bin_expr($1, $3, oper_mod);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	'-' expression %prec UMINUS {
		$$ = new un_expr($2, oper_umin);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '<' expression {
		$$=new bin_expr($1, $3, oper_lt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '>' expression {
		$$=new bin_expr($1, $3, oper_gt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression LEQ expression {
		$$=new bin_expr($1, $3, oper_le);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression GEQ expression {
		$$=new bin_expr($1, $3, oper_ge);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression ISEQ expression {
		$$=new bin_expr($1, $3, oper_iseq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression NOEQ expression {
		$$=new bin_expr($1, $3, oper_isneq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}	
	| expression LOGOR expression {
		$$=new bin_expr($1, $3, oper_or);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}	
	| expression LOGAND expression {
		$$=new bin_expr($1, $3, oper_and);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| expression '=' expression {
		$$ = new bin_expr($1, $3, oper_assgn);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	NOT expression {
		$$ = new un_expr($2, oper_not);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	INUMBER	{
		$$ = new un2_expr($1);
		//cout << "got INUMBER: " << $1 << " type : " << $$->type << endl;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	FNUMBER {
		$$ = new un2_expr($1);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	NAME	{
		$$ = new un2_expr($1, oper_name );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| 	NAME '[' expression ']' %prec FUNC_CALL {
		$$ = new un2_expr(oper_arrderef, /*nametype,  se,*/ $1,$3);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($1);
	}
	| NAME '[' expression ',' expression ']'  %prec FUNC_CALL {
		$$ = new un2_expr(oper_blk_arr_assgn, $1,$3,$5);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($1);
	}
	| NAME '(' expr_list ')' %prec FUNC_CALL{
		//cout << "parsing Function call: name: " << $1 << endl;
		string search_for=$1;
		bool found=false;
		int index=search_for_func(search_for);
		if(index!=-1) found=true;
		bool skip_type_check=skip_func_type_check(search_for.c_str());
		if( skip_type_check==false  && found==false ) {
			cerr << "ERROR: function call Error on line_no: " << line_no << endl;
			cerr << "function : " << search_for << " used without decl" << endl;
			++ no_errors;
			$$=new un2_expr(ERROR_TYPE);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		} else {
			datatype my_type=func_info_table[index]->return_type;
			expr* e_ptr=trav_chain($3);
			var_list* fparam=func_info_table[index]->param_list;
			bool match=false;
			if(skip_type_check==false){
				match=check_parameters(e_ptr, fparam);
			}
			if(match || skip_type_check){
				//$$=new un2_expr(oper_func_call, my_type, $3, index, line_no);
				$$=new un2_expr(oper_func_call, my_type, e_ptr, index, line_no);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);

			} else {
				$$=new un2_expr(ERROR_TYPE);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);
			}
		}
		free($1);
	}
	|	TEXT {
		$$ = new un2_expr(strdup($1), oper_text_expr);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| 	'(' expression ')' %prec UMINUS{ 
		$$ = new un_expr($2, oper_parexp );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| NAME IN NAME {
		$$ = new bin2_expr($1, $3, oper_in);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	;
