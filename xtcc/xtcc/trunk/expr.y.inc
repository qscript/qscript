
expression: expression '+' expression {
		$$=new Expression::BinaryExpression($1, $3, Expression::oper_plus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '-' expression {
		$$=new Expression::BinaryExpression($1, $3, Expression::oper_minus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '*' expression {
		$$=new Expression::BinaryExpression($1, $3, Expression::oper_mult);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '/' expression {
		$$=new Expression::BinaryExpression($1, $3, Expression::oper_div);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '%' expression {
		$$=new Expression::BinaryExpression($1, $3, Expression::oper_mod);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	'-' expression %prec UMINUS {
		$$ = new Expression::UnaryExpression($2, Expression::oper_umin);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '<' expression {
		$$=new Expression::BinaryExpression($1, $3, Expression::oper_lt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '>' expression {
		$$=new Expression::BinaryExpression($1, $3, Expression::oper_gt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression LEQ expression {
		$$=new Expression::BinaryExpression($1, $3, Expression::oper_le);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression GEQ expression {
		$$=new Expression::BinaryExpression($1, $3, Expression::oper_ge);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression ISEQ expression {
		$$=new Expression::BinaryExpression($1, $3, Expression::oper_iseq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression NOEQ expression {
		$$=new Expression::BinaryExpression($1, $3, Expression::oper_isneq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| expression LOGOR expression {
		$$=new Expression::BinaryExpression($1, $3, Expression::oper_or);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| expression LOGAND expression {
		$$=new Expression::BinaryExpression($1, $3, Expression::oper_and);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| expression '=' expression {
		$$ = new Expression::BinaryExpression($1, $3, Expression::oper_assgn);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	NOT expression {
		$$ = new Expression::UnaryExpression($2, Expression::oper_not);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	INUMBER	{
		$$ = new Expression::Unary2Expression($1);
		//cout << "got INUMBER: " << $1 << " type : " << $$->type << endl;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	FNUMBER {
		$$ = new Expression::Unary2Expression($1);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	NAME	{
		$$ = new Expression::Unary2Expression($1, Expression::oper_name );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| 	NAME '[' expression ']' %prec FUNC_CALL {
		$$ = new Expression::Unary2Expression (Expression::oper_arrderef, /*nametype,  se,*/ $1,$3);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($1);
	}
	| NAME '[' expression ',' expression ']'  %prec FUNC_CALL {
		$$ = new Expression::Unary2Expression(Expression::oper_blk_arr_assgn, $1,$3,$5);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($1);
	}
	| NAME '(' expr_list ')' %prec FUNC_CALL{
		//cout << "parsing Function call: name: " << $1 << endl;
		string search_for=$1;
		bool found=false;
		int index=Util::search_for_func(search_for);
		if(index!=-1) found=true;
		bool skip_type_check=Util::skip_func_type_check(search_for.c_str());
		if( skip_type_check==false  && found==false ) {
			cerr << "ERROR: function call Error on line_no: " << line_no << endl;
			cerr << "function : " << search_for << " used without decl" << endl;
			++ no_errors;
			$$=new Expression::Unary2Expression(ERROR_TYPE);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		} else {
			DataType my_type=func_info_table[index]->returnType_;
			Expression::AbstractExpression* e_ptr=trav_chain($3);
			Statement::FunctionParameter* fparam=func_info_table[index]->paramList_;
			bool match=false;
			if(skip_type_check==false){
				match=Util::check_parameters(e_ptr, fparam);
			}
			if(match || skip_type_check){
				//$$=new Unary2Expression(oper_func_call, my_type, $3, index, line_no);
				$$=new Expression::Unary2Expression(Expression::oper_func_call, my_type, e_ptr, index, line_no);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);

			} else {
				$$=new Expression::Unary2Expression(ERROR_TYPE);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);
			}
		}
		free($1);
	}
	|	TEXT {
		$$ = new Expression::Unary2Expression(strdup($1), Expression::oper_text_expr);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| 	'(' expression ')' %prec UMINUS{ 
		$$ = new Expression::UnaryExpression($2, Expression::oper_parexp );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| expression IN '(' range_list ')' {
		$$ = new Expression::Binary2Expression($1, xs, Expression::oper_in);
	}
	/*
	| NAME IN NAME {
		$$ = new Binary2Expression($1, $3, oper_in);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	*/
	;
