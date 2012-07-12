#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include "symtab.h"
#include "scope.h"
#include "stmt.h"
#include "utils.h"
#include "debug_mem.h"
//#include "tree.h"
using std::map;
using std::vector;
using std::ofstream;
extern vector<mem_addr_tab> mem_addr;
namespace Statement{
	struct FunctionInformation;
}
extern vector <Statement::FunctionInformation*> func_info_table;
extern ofstream debug_log_file;
extern int if_line_no;
extern Scope* active_scope;


extern char * work_dir;
extern int no_errors;
extern int line_no;

namespace Statement {
using std::cout;
using std::endl;
using std::cerr;
using std::stringstream;
using std::ostringstream;
//using ::line_no;
//using ::no_errors;
//extern int no_errors;
//extern int line_no;
using Util::print_err;
using Util::void_check;
using Util::lcm_type;
using Util::arr_deref_type;
using Util::search_for_func;

AbstractStatement::~AbstractStatement(){ 
	if (next_ /*
		    && !((type_==FUNC_DEFN)||(type_==FUNC_TYPE))*/ ) {
		delete next_; next_=0;
	} 
	debug_log_file 
	    << "AbstractStatement::~AbstractStatement() base destructor" 
	    << std::endl;
}

ListStatement::~ListStatement(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "ListStatement::~ListStatement setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting ListStatement" << endl;
	//if(next_) delete next_;
	//delete symbolTableEntry_;
}

#include <sstream>
FunctionDeclarationStatement::FunctionDeclarationStatement( DataType dtype
		, int lline_number, char * & name
		, FunctionParameter* & v_list, DataType returnType_)
	: AbstractStatement(dtype, lline_number), funcInfo_(0)
{
	//cout << "load_func_into_symbol_table : " << "name: " << name << endl;
	if ( active_scope->sym_tab.find(name) == active_scope->sym_tab.end() ){
		//cout << "got func_decl" << endl;
		DataType myreturn_type=returnType_;
		FunctionInformation* fi=new FunctionInformation(name
				, v_list, myreturn_type);
		func_info_table.push_back(fi);
		type_=FUNC_TYPE;
		SymbolTableEntry* se=new SymbolTableEntry;
		if(! se) {
			cerr << "memory allocation error: I will eventually crash :-(" 
				<< endl;
		}
		se->name_ = name;
		string s(name);
		active_scope->sym_tab[s] = se;
		se->type_=FUNC_TYPE;
		funcInfo_=fi;
		//free(name);
	} else {
		stringstream s;
		s << "Function  Name : " 
			<< name << " already present in symbol table." << endl;
		print_err(Util::compiler_sem_err, s.str()
				, line_no, __LINE__, __FILE__);
		type_=ERROR_TYPE;
		free(name);
	}
}

void FunctionDeclarationStatement::GenerateCode(FILE * & fptr)
{
	fflush(fptr);
	if(fptr){
		funcInfo_->print(fptr);
		if(next_) next_->GenerateCode(fptr);
	}
}

FunctionDeclarationStatement::~FunctionDeclarationStatement()
{
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file 
				<< "FunctionDeclarationStatement::~FunctionDeclarationStatement setting mem_addr: " 
				<< this<< "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting FunctionDeclarationStatement: name: "  
		<< funcInfo_->funcName_ << endl;
	if (funcInfo_) { delete funcInfo_; funcInfo_=0; }
}

FunctionStatement:: FunctionStatement ( DataType dtype, int lline_number
		, Scope * &scope_, FunctionParameter * & v_list
		, AbstractStatement* & lfunc_body
		, string func_name, DataType lreturn_type
		) 
	: AbstractStatement(dtype, lline_number), funcInfo_(0)
	  , funcBody_(lfunc_body), returnType_(lreturn_type)
{
	int index=search_for_func(func_name);
	if(index==-1){
		cerr << "function defn without decl: " 
			<< func_name << " lline_number: " 
			<< lline_number << endl;
		type_=ERROR_TYPE;
		++no_errors;
	} else if(Util::check_func_decl_with_func_defn(v_list, index, func_name)){
		if(returnType_==func_info_table[index]->returnType_){
			type_=FUNC_DEFN;
			funcInfo_=func_info_table[index];
		} else {
			stringstream s;
			s << "func defn, decl parameter return_types did not match: function name: " << func_name;
			print_err(Util::compiler_sem_err, s.str(), line_no
					, __LINE__, __FILE__);
			type_=ERROR_TYPE;
		}
	} else {
		stringstream s;
		s << "func defn, decl parameter return_types did not match: function name: " << func_name;
		print_err(Util::compiler_sem_err, s.str(), line_no
				, __LINE__, __FILE__);
		++no_errors;
		type_=ERROR_TYPE;
	}
}

void FunctionStatement::GenerateCode(FILE * & fptr)
{
	if(fptr){
		if(funcInfo_->returnType_ >= VOID_TYPE 
				&& funcInfo_->returnType_<=DOUBLE_TYPE){
			fprintf(fptr,"%s ", noun_list[funcInfo_->returnType_].sym);
		} else {
			fprintf(fptr, "Unxpected return type for function: file: %s, line:%d\n",
					__FILE__, __LINE__ );
		}
		
		if(funcInfo_->funcName_==string("printf")){
			fprintf(fptr, "fprintf(xtcc_stdout,");
		} else {
			fprintf(fptr, "%s/* comment */\n"
					, funcInfo_->funcName_.c_str());
			fprintf(fptr, "(");
		}
		FunctionParameter* v_ptr=funcInfo_->paramList_;
		v_ptr->print(fptr);
		fprintf(fptr, ")");
		if(funcBody_) funcBody_->GenerateCode(fptr);
		if(next_) next_->GenerateCode(fptr);
	}
}


FunctionStatement::~FunctionStatement(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "FunctionStatement::~FunctionStatement: setting mem_addr=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting FunctionStatement" << endl;
	if(funcBody_) {
		delete funcBody_;
		funcBody_=0;
	}
}


void ForStatement::GenerateCode(FILE * & fptr)
{
	fflush(fptr);

	if(fptr){
		ostringstream code_bef_expr, code_expr;
		//fprintf(fptr,  "for (");
		code_expr << "for (" ;
		//initializationExpression_->PrintExpressionCode(fptr);
		initializationExpression_->PrintExpressionCode(code_bef_expr, code_expr);
		//fprintf(fptr,  ";");
		code_expr <<   ";";
		testExpression_->PrintExpressionCode(code_bef_expr, code_expr);
		code_expr << ";";
		//incrementExpression_->PrintExpressionCode(fptr);
		incrementExpression_->PrintExpressionCode(code_bef_expr, code_expr);
		code_expr <<  ")";

		fprintf(fptr, "%s \n", code_bef_expr.str().c_str());
		fprintf(fptr, "%s \n", code_expr.str().c_str());
		fflush(fptr);
		forBody_->GenerateCode(fptr);
		if(next_) next_->GenerateCode(fptr);
	}
}

ForStatement:: ~ForStatement(){
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "ForStatement::~ForStatement setting mem_addr:" << this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting ForStatement" << endl;
	//if(next_) { delete next_; }
	if(initializationExpression_) {
		delete initializationExpression_;
		initializationExpression_ =0;
	}
	if(testExpression_) {
		delete testExpression_;
		testExpression_=0;
	}
	if(incrementExpression_) {
		delete incrementExpression_;
		incrementExpression_=0;
	}
	if(forBody_) {
		delete forBody_; forBody_=0;
	}
}

void IfStatement::GenerateCode(FILE * & fptr)
{
	fflush(fptr);

	if(fptr){
		ostringstream code_bef_expr, code_expr;
		//fprintf(fptr,  "if (");
		code_expr << "if (";
		ifCondition_->PrintExpressionCode(code_bef_expr
						  , code_expr);
		//fprintf(fptr,  ")");
		code_expr << ")";
		fprintf(fptr, " %s ", code_bef_expr.str().c_str());
		fprintf(fptr, " %s ", code_expr.str().c_str());
		fflush(fptr);
		ifBody_->GenerateCode(fptr);
		fflush(fptr);
		if(elseBody_){
			fprintf(fptr,  " else ");
			elseBody_->GenerateCode(fptr);
		}
		if(next_) next_->GenerateCode(fptr);
	}
}

IfStatement:: ~IfStatement()
{
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "IfStatement::~IfStatement setting mem_addr:" << this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting IfStatement" << endl;
	//if (next_) delete next_;
	delete ifCondition_;
	delete ifBody_;
	if (elseBody_) delete elseBody_;
}

void ExpressionStatement::GenerateCode(FILE * & fptr)
{
	fflush(fptr);

	if(fptr){
		//PrintExpressionCode(fptr, expr);
		ostringstream code_bef_expr, code_expr;
		expression_->PrintExpressionCode(code_bef_expr, code_expr);
		//fprintf(fptr,";\n");
		fprintf(fptr, "%s\n", code_bef_expr.str().c_str());
		fprintf(fptr, "%s\n", code_expr.str().c_str());
		fprintf(fptr,";\n");
		if(next_) next_->GenerateCode(fptr);
	}
}


void ErrorStatement::GenerateCode(FILE * & fptr)
{
	fflush(fptr);

	if(fptr){
		fprintf(fptr, "error");
		//if(next_) next_->GenerateCode(fptr);
	}
}

ExpressionStatement::~ExpressionStatement() 
{
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "ExpressionStatement::~ExpressionStatement: setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	debug_log_file << "deleting ExpressionStatement" << endl;
	//if(next_ ) delete next_;
	if (expression_) delete expression_;
}

BreakStatement::BreakStatement(DataType dtype, int lline_number, int in_a_loop)
	: AbstractStatement(dtype, lline_number)
{
	if(in_a_loop<=0){
		print_err(Util::compiler_sem_err, "break statement outside a loop: "
			, line_no, __LINE__, __FILE__);
	}
}

void BreakStatement:: GenerateCode(FILE * & fptr)
{
	fflush(fptr);
	if(fptr){
		fprintf(fptr, "break;\n");
		if(next_) next_->GenerateCode(fptr);
	}
}

BreakStatement::~BreakStatement()
{
	cout << "deleting BreakStatement" << endl;
	if (next_) delete next_;
}

ContinueStatement::ContinueStatement(DataType dtype, int lline_number
		, int in_a_loop)
	: AbstractStatement(dtype, lline_number)
{
	if (in_a_loop<=0){
		print_err(Util::compiler_sem_err
				, "continue statement outside a loop: line_no: "
				, line_no, __LINE__, __FILE__);
	}
}

void ContinueStatement::GenerateCode(FILE * & fptr)
{
	fflush(fptr);
	if(fptr){
		fprintf(fptr, "continue;\n");
		if(next_) next_->GenerateCode(fptr);
	}
}

void ListStatement::GenerateCode(FILE * & fptr)
{
	fflush(fptr);
	string my_work_dir=string(work_dir)+string("/");

	if(fptr){
		switch(type_){
		case LISTA_BASIC_TYPE_STMT:{
			static int counter_number=0;			   
			string fname= my_work_dir+ string("global.C");
			FILE * global_vars=fopen(fname.c_str(), "a+b");
			fname=my_work_dir+ string("print_list_counts.C");
			FILE * print_list_counts=fopen(fname.c_str(), "a+b");
			if(!(global_vars&&print_list_counts)){
				cerr << "Unable to open global.C or print_list_counts.C for append... exiting" << endl;
				exit(1);
			}
			if(symbolTableEntry_){
				DataType dt=symbolTableEntry_->get_type();
				if( is_of_noun_type(dt) 
					|| is_of_noun_ref_type(dt)){
					fprintf(global_vars
						, "map<%s,int> list%d;\n", 
						noun_list[dt].sym
						, counter_number);
					fprintf(fptr, "list%d [%s]++;\n"
							, counter_number
							, symbolTableEntry_->name_);
					fprintf(print_list_counts
						, "print_list_summ(list%d, string(\"%s\"), string(%s) );\n"
						, counter_number, symbolTableEntry_->name_
						, list_text.c_str());
				}

				++counter_number;
			}
			fclose(global_vars);
			fclose(print_list_counts);
		}
		break;
		case LISTA_BASIC_ARRTYPE_STMT_1INDEX:{
			static int counter_number=0;			   
			//FILE * global_vars=fopen("xtcc_work/global.C", "a+b");
			//FILE * print_list_counts=fopen("xtcc_work/print_list_counts.C", "a+b");
			string fname= my_work_dir+ string("global.C");
			FILE * global_vars=fopen(fname.c_str(), "a+b");
			fname=my_work_dir+ string("print_list_counts.C");
			FILE * print_list_counts=fopen(fname.c_str(), "a+b");
			if(!global_vars){
				cerr << "Unable to open global.C for append" << endl;
			}
			if(symbolTableEntry_){
				DataType dt=symbolTableEntry_->get_type();
				if(dt>=INT8_ARR_TYPE&& dt<=DOUBLE_ARR_TYPE){
					fprintf(global_vars
						, "map<%s,int> list1_%d;\n"
						, noun_list[dt].sym
						, counter_number);
					fprintf(fptr, "list1_%d [%s["
						, counter_number, symbolTableEntry_->name_);
					ostringstream code_bef_expr1
						, code_expr1;
					//arr_start->PrintExpressionCode(fptr);
					arr_start->PrintExpressionCode(code_bef_expr1
							, code_expr1);
					fprintf(fptr, "%s"
						, code_expr1.str().c_str());
					fprintf(fptr, "]]++;\n");
					fprintf(print_list_counts, "print_list_summ(list1_%d, string(\"%s\"), string(%s) );\n", 
						counter_number, symbolTableEntry_->name_, list_text.c_str());
				}
				++counter_number;
			}
			fclose(global_vars);
			fclose(print_list_counts);
		}
		break;
		case LISTA_BASIC_ARRTYPE_STMT_2INDEX:{
			static int counter_number=0;			   
			//FILE * global_vars=fopen("xtcc_work/global.C", "a+b");
			//FILE * print_list_counts=fopen("xtcc_work/print_list_counts.C", "a+b");
			string fname= my_work_dir+ string("global.C");
			FILE * global_vars=fopen(fname.c_str(), "a+b");
			fname=my_work_dir+ string("print_list_counts.C");
			FILE * print_list_counts=fopen(fname.c_str(), "a+b");
			if(!global_vars){
				cerr << "Unable to open global.C for append" << endl;
			}
			if(symbolTableEntry_){
				DataType dt=symbolTableEntry_->get_type();
				switch(dt){
				case INT8_ARR_TYPE:	
					{
					fprintf(global_vars, "map<%s,int> list2_%d;\n", 
							noun_list[dt].sym, counter_number);
					/*fprintf(fptr, "list2_%d [%s[%d]]++;\n", counter_number, symbolTableEntry_->name,
							arr_start);
					fprintf(print_list_counts, "print_list_summ(list2_%d );\n", counter_number);
					*/
					fprintf(print_list_counts, "printf(\"LISTA_BASIC_ARRTYPE_STMT_2INDEX: to be implemented\");\\n\n");

					}
				break;		      
				default:
					++no_errors;
				}
				++counter_number;
			}
			fclose(print_list_counts);
			fclose(global_vars);
		}
		default:
			fprintf(fptr, "Unhandled lista statement: \n");	
		}
		if(next_) next_->GenerateCode(fptr);

	}
}

void CompoundStatement::GenerateCode(FILE * & fptr)
{
	fflush(fptr);
	if(fptr){
		fprintf(fptr,"{\n");
		if (compoundBody_) compoundBody_->GenerateCode(fptr);
		fprintf(fptr,"}\n");
		if(next_) next_->GenerateCode(fptr);
	}
}

CompoundStatement::~CompoundStatement()
{
	debug_log_file << "deleting CompoundStatement" << endl;
	for (unsigned int i=0; i< mem_addr.size(); ++i){
		if(this==mem_addr[i].mem_ptr){
			mem_addr[i].mem_ptr=0;
			debug_log_file << "basic_count_ax_stmt::~basic_count_ax_stmt setting mem_addr: " << this << "=0" << endl;
			break;
		}
	}
	//if(next_) delete next_;
	if(scope_&&flagIsFunctionBody_<0) {
		delete scope_;
		scope_=0;
	}
	if(compoundBody_ /*&& flagIsFunctionBody_<0*/){
		delete compoundBody_;
		compoundBody_=0;
	}
}


void DeclarationStatement::GenerateCode(FILE * & fptr)
{
	fflush(fptr);
	if(fptr){
		ostringstream code_expr1, code_bef_expr1;
		if( symbolTableEntry_->e){
			symbolTableEntry_->e->PrintExpressionCode(code_bef_expr1, code_expr1);
			fprintf(fptr,"%s", code_bef_expr1.str().c_str());
		}
		if(type_ >= INT8_TYPE && type_ <=DOUBLE_TYPE){
			fprintf(fptr,"%s %s", noun_list[type_].sym, symbolTableEntry_->name_);
		} else if (type_ >=INT8_ARR_TYPE && type_ <=DOUBLE_ARR_TYPE){
			DataType tdt=DataType(INT8_TYPE + type_-INT8_ARR_TYPE);
			fprintf(fptr,"%s %s [ %d ]"
					, noun_list[tdt].sym, symbolTableEntry_->name_
					, symbolTableEntry_->n_elms);
		} else if (type_ >=INT8_REF_TYPE&& type_ <=DOUBLE_REF_TYPE){
			DataType tdt=DataType(INT8_TYPE + type_-INT8_REF_TYPE);
			fprintf(fptr,"%s & %s", noun_list[tdt].sym
					, symbolTableEntry_->name_);
		}
		if( symbolTableEntry_->e){
			fprintf(fptr,"=%s", code_expr1.str().c_str());
			//symbolTableEntry_->e->PrintExpressionCode(fptr);
		}
		fprintf(fptr, ";\n");
		if(next_) next_->GenerateCode(fptr);
	}
}

DeclarationStatement::~DeclarationStatement(){ 
	debug_log_file << "deleting DeclarationStatement" << endl;
	//if(symbolTableEntry_) { delete symbolTableEntry_; symbolTableEntry_=0; }
}

IfStatement::IfStatement( DataType dtype, int lline_number
		, Expression::AbstractExpression * lcondition, AbstractStatement * lif_body
		, AbstractStatement * lelse_body) 
	: AbstractStatement(dtype, lline_number), ifCondition_(lcondition)
	  , ifBody_(lif_body), elseBody_(lelse_body)
{
	if(lcondition->type_==VOID_TYPE || lcondition->type_==ERROR_TYPE){
		print_err(Util::compiler_sem_err
			, "If ifCondition_ expression has Void or Error Type"
			, if_line_no, __LINE__, __FILE__);
	} else {
	}
}


ForStatement::ForStatement(DataType dtype, int lline_number
		, Expression::AbstractExpression* l_init, Expression::AbstractExpression* l_test
		, Expression::AbstractExpression* l_incr
		, AbstractStatement * lfor_body)
	: AbstractStatement(dtype, lline_number)
	, initializationExpression_(l_init)
	, testExpression_(l_test), incrementExpression_(l_incr)
	, forBody_(lfor_body)
{
	if(initializationExpression_->type_==VOID_TYPE
			||testExpression_->type_==VOID_TYPE
			||incrementExpression_->type_==VOID_TYPE ){
		print_err(Util::compiler_sem_err, 
			"For ifCondition_ expression has Void or Error Type"
			, line_no, __LINE__, __FILE__);
		type_=ERROR_TYPE;
	} 
}


ListStatement::ListStatement( DataType dtype, string name,
		string llist_text,
		Expression::AbstractExpression*  l_arr_start, 
		Expression::AbstractExpression* l_arr_end
		):
	AbstractStatement(dtype, line_no)
	, symbolTableEntry_(0), list_text(llist_text)
	, arr_start(l_arr_start), arr_end(l_arr_end)

{
	map<string,SymbolTableEntry*>::iterator sym_it = Util::find_in_symtab(name);
	if(sym_it==active_scope->sym_tab.end() ){
		stringstream s;
		s << "ListStatement:  statement symbol: " << name 
		  << " not found in symbol table" << endl;
		print_err(Util::compiler_sem_err, s.str(), line_no, __LINE__
			  , __FILE__);
	} else {
		symbolTableEntry_=sym_it->second;
		DataType name_type=symbolTableEntry_->type_;
		if( !(is_of_noun_type(name_type)|| is_of_noun_ref_type(name_type))
			){
			stringstream s;
			s << "ListStatement NAME: "<< name 
			  << " should be of basic type or basic reference types: " << line_no << endl;
			print_err(Util::compiler_sem_err, s.str(), line_no
				  , __LINE__, __FILE__);
			type_ = ERROR_TYPE;
		} 
	}
	if(arr_start){
		if(! is_of_int_type( arr_start->type_) ){
			type_=ERROR_TYPE;
			stringstream s;
			s << "ListStatement NAME: "<< name 
			  << " array index should be of INT type: " 
			  << line_no << endl;
			print_err(Util::compiler_sem_err, s.str(), line_no, __LINE__
				  , __FILE__);

		}
	} 
	if(arr_end){
		if(! is_of_int_type( arr_end->type_) ){
			type_=ERROR_TYPE;
			stringstream s;
			s << "ListStatement NAME: "<< name 
			  << " array index 2 should be of INT type: " 
			  << line_no << endl;
			print_err(Util::compiler_sem_err, s.str(), line_no, __LINE__
				  , __FILE__);
		}
	}
}

FieldStatement::FieldStatement(string lhs_name
		, string rhs_name, Expression::AbstractExpression* l_s
		, Expression::AbstractExpression* l_e, int l_w)
	: lhsSymbolTableEntry_(0), rhsSymbolTableEntry_(0)
	  , start_col(l_s), end_col(l_e), width(l_w)
{
	map<string,SymbolTableEntry*>::iterator sym_it1
	    = Util::find_in_symtab(lhs_name);
	map<string,SymbolTableEntry*>::iterator sym_it2 
	    = Util::find_in_symtab(rhs_name);
	if(!(is_of_int_type(start_col->type_)&&
		is_of_int_type(end_col->type_) ) ){
		print_err(Util::compiler_sem_err, "FieldStatement: start col and end col expressions must be of integer type"
			  , line_no, __LINE__, __FILE__);
	} else if(sym_it1==active_scope->sym_tab.end()){
		stringstream s;
		s <<  "Error: could not find:" << lhs_name 
		  <<"  in symbol table: lineno: " << line_no << "\n";
		print_err(Util::compiler_sem_err, s.str(), line_no, __LINE__
			  , __FILE__);
	} else if (sym_it2==active_scope->sym_tab.end()){
		stringstream s;
		s <<  "Error: could not find:" << rhs_name 
		  <<"  in symbol table: lineno: " << line_no << "\n";
		print_err(Util::compiler_sem_err, s.str(), line_no, __LINE__
			  , __FILE__);
	} else {
		lhsSymbolTableEntry_ = sym_it1->second;
		rhsSymbolTableEntry_ = sym_it2->second;
		// first some validation checks
		//DataType type1 = sym_it1->type;
		if( !( 
			(sym_it1->second->type_ == INT32_ARR_TYPE) &&
			(sym_it2->second->type_ >= INT8_ARR_TYPE) &&
			(sym_it2->second->type_ <= INT32_ARR_TYPE)) ) {
			stringstream s;
			s << " lhs name should be an array of type int32_t and rhs name should be an integer array ";
			print_err(Util::compiler_sem_err, s.str(), line_no, __LINE__
				  , __FILE__);

		} else if (!(width==sizeof(INT8_TYPE) 
			     || width==sizeof(INT16_TYPE)
			     ||width==sizeof(INT32_TYPE)) ){
			stringstream s;
			s << "FieldStatement width error: width of field can only be : " 
			  << sizeof(int8_t) << " or " << sizeof(int16_t) 
			  << " or "
			  << sizeof(int32_t) << endl;
			print_err(Util::compiler_sem_err, s.str(), line_no, __LINE__
				  , __FILE__);
		} else {
			//everything is ok
		}
	}
}

void FieldStatement::GenerateCode(FILE * & fptr)
{
	// runtime checks need to be put
	// 1 startcol < endcol
	// endcol-startcol+1 % width == 0
	fprintf(fptr, "/* FieldStatement  code will be generated here */\n");

	fprintf(fptr, "{\n");
	fprintf(fptr, "\tfor (int i=0; i<%d; ++i) %s[i]=0;\n", lhsSymbolTableEntry_->n_elms, lhsSymbolTableEntry_->name_);
	fprintf(fptr, "int start_col=");
	//start_col->PrintExpressionCode(fptr);
	// NOTE: we do not expect operator in to be used in a block initialization
	// I should document this for myself in a more visible place
	ostringstream code_bef_expr1, code_expr1;
	start_col->PrintExpressionCode(code_bef_expr1, code_expr1);
	fprintf(fptr, "%s", code_expr1.str().c_str());
	fprintf(fptr, ",end_col=");
	//end_col->PrintExpressionCode(fptr);
	ostringstream code_bef_expr2, code_expr2;
	end_col->PrintExpressionCode(code_bef_expr2, code_expr2);
	fprintf(fptr, "%s", code_expr2.str().c_str());
	fprintf(fptr, ",width=%d;\n", width);
	fprintf(fptr, "if( start_col > end_col){\n");
	fprintf(fptr, "\tprintf(\"start_col evaluated > end_col -> runtime error\");\n");
	fprintf(fptr, "}\n");
	fprintf(fptr, "if( (end_col-start_col +1) %% width!=0 ){\n");
	fprintf(fptr, "\t\tprintf(\"expr value:%%d\", end_col-start_col +1 %% width );");
	fprintf(fptr, "\tprintf(\"please check your start_col=%%d ,  end_col=%%d, width=%%d for fld statement-> runtime error\\n\", start_col, end_col, width);\n");
	fprintf(fptr, "}\n");
	
	fprintf(fptr, "for (int i=start_col; i<= end_col+1-width; i+=width){\n");
	int lhs_arr_sz;
	if(lhsSymbolTableEntry_->type_==INT8_ARR_TYPE){
		lhs_arr_sz=sizeof(INT8_TYPE);
	} else if (lhsSymbolTableEntry_->type_==INT16_ARR_TYPE){
		lhs_arr_sz=sizeof(INT16_TYPE);
	} else if (lhsSymbolTableEntry_->type_==INT32_ARR_TYPE){
		lhs_arr_sz=sizeof(INT32_TYPE);
	} else {
		fprintf(fptr, "prevent compilation: compiler bug filename:%s, lineNo_: %d\n", __FILE__, __LINE__);
	}
	fprintf(fptr, "\t\tchar buff[%d];\n", lhs_arr_sz);
	fprintf(fptr,"\t\tfor(int s=i,j=0;s<i+width;++s,++j){\n");
	fprintf(fptr,"\t\t\t\tbuff[j]=%s[s];\n", rhsSymbolTableEntry_->name_);
	fprintf(fptr,"\t\t}\n");
	fprintf(fptr,"\tvoid * v_ptr = buff;\n");
	if(lhs_arr_sz==sizeof(char)){
		fprintf(fptr,"\tchar *c_ptr = static_cast<char *>(v_ptr);\n");
		fprintf(fptr,"\tint tmp=*c_ptr;\n");
	} else if (lhs_arr_sz==sizeof(short int)){
		fprintf(fptr,"\tshort int  *si_ptr = static_cast<short int *>(v_ptr);\n");
		fprintf(fptr,"\tint tmp=*si_ptr;\n");
	} else if (lhs_arr_sz==sizeof( int)){
		fprintf(fptr,"\t\tint  *i_ptr = static_cast<int *>(v_ptr);\n");
		fprintf(fptr,"\t\tint tmp=*i_ptr;\n");
	}
	fprintf(fptr,"\t\tif(tmp>=1 && tmp <=%d){\n", lhsSymbolTableEntry_->n_elms);
	fprintf(fptr,"\t\t\t++%s[tmp];\n", lhsSymbolTableEntry_->name_);
	// in arr position 0 incr 1 if this variable has any data.
	// hence position 0 will have a count of how many responses were there
	// this is used in the axes section to tabulate - as a total answering base
	fprintf(fptr,"\t\t\t++%s[0];\n", lhsSymbolTableEntry_->name_);
	fprintf(fptr,"\t\t} else if (tmp == 0) {\n");
	// ignore tmp == 0 for now - later maybe create a blank variable indicator or something
	fprintf(fptr,"\t\t} else {\n");
	fprintf(fptr,"\t\t\tfprintf(runtime_errors, \" runtime warning: code: %%d at variable: %s too big to fit in array. ser_no: %%d \\n\", tmp, ser_no);\n", lhsSymbolTableEntry_->name_);
	// this technique is not used anymore - instead we log an entry into runtime errors
	//fprintf(fptr,"\t\t\t++%s[0];\n", lhsSymbolTableEntry_->name_);
	fprintf(fptr,"\t\t}\n;");
	
	fprintf(fptr, "}} \n");
	if(next_) next_->GenerateCode(fptr);
}


void BlockArrayAssignmentStatement::GenerateCode(FILE * & fptr)
{
	fflush(fptr);

	if(fptr){
		fprintf(fptr,"/* DATA CONVERSION */\n");
		fprintf(fptr,"{int tmp1=");
		//low_indx->PrintExpressionCode(fptr);
		// NOTE: we do not expect operator in to be used in a block initialization
		ostringstream code_expr1, code_bef_expr1;
		low_indx->PrintExpressionCode(code_bef_expr1, code_expr1);
		fprintf(fptr, "%s", code_expr1.str().c_str());
		fprintf(fptr,";\nint tmp2=");
		//high_indx->PrintExpressionCode(fptr);
		ostringstream code_expr2, code_bef_expr2;
		high_indx->PrintExpressionCode(code_bef_expr2, code_expr2);
		fprintf(fptr, "%s", code_expr2.str().c_str());
		fprintf(fptr,";\n");
		if(lhsSymbolTableEntry_->get_type()==FLOAT_TYPE) {
			fprintf(fptr,"if(tmp2-tmp1==sizeof(float)-1){\n");
			fprintf(fptr,"\tchar buff[sizeof(float)];int i,j;\n");
			fprintf(fptr,"\tfor(i=tmp1,j=0;i<=tmp2;++i,++j){\n");
			fprintf(fptr,"\t\tbuff[j]=%s[i];\n", rhsSymbolTableEntry_->name_);
			fprintf(fptr,"\t}\n");
			fprintf(fptr,"\tvoid * v_ptr = buff;\n");
			fprintf(fptr,"\tfloat *f_ptr = static_cast<float *>(v_ptr);\n");
			fprintf(fptr,"\t %s=*f_ptr;\n", lhsSymbolTableEntry_->name_);
			fprintf(fptr,"}else { cerr << \"runtime error: line_no : Expression::AbstractExpression out of bounds\" << %d;}\n}\n", lineNo_ );
		} else if (lhsSymbolTableEntry_->get_type()==INT32_TYPE){
			fprintf(fptr,"if(tmp2-tmp1==sizeof(int)-1){\n");
			fprintf(fptr,"\tchar buff[sizeof(int)];int i,j;\n");
			fprintf(fptr,"\tfor(i=tmp1,j=0;i<=tmp2;++i,++j){\n");
			fprintf(fptr,"\t\tbuff[j]=%s[i];\n", rhsSymbolTableEntry_->name_);
			fprintf(fptr,"\t}\n");
			fprintf(fptr,"\tvoid * v_ptr = buff;\n");
			fprintf(fptr,"\tint *i_ptr = static_cast<int *>(v_ptr);\n");
			fprintf(fptr,"\t %s=*i_ptr;\n", lhsSymbolTableEntry_->name_);
			fprintf(fptr,"}else { \n\tcerr << \"runtime error: line_no : Expression::AbstractExpression out of bounds\" << %d;}\n}\n", lineNo_ );
		}
	}
	if(next_) next_->GenerateCode(fptr);
}


BlockArrayAssignmentStatement::~BlockArrayAssignmentStatement()
{
	//cout << "deleting BlockArrayAssignmentStatement" << endl;
	//if(next_) delete next_;
	delete lhsSymbolTableEntry_; 
	delete rhsSymbolTableEntry_;
	delete low_indx;
	delete	high_indx;
}


FunctionInformation::FunctionInformation(string name, struct FunctionParameter* elist
		, DataType myreturn_type)
	: funcName_(name), paramList_(elist), returnType_(myreturn_type)
	  , funcBody_(0), funcScope_(0)
{
	funcScope_=new Scope();
	struct FunctionParameter* decl_list=elist;
	while(decl_list){
		struct SymbolTableEntry* se=new struct SymbolTableEntry;
		se->name_ = strdup(decl_list->var_name.c_str());
		se->type_=decl_list->var_type;
		funcScope_->sym_tab[decl_list->var_name] = se;
		decl_list=decl_list->next_;
	}
}

void FunctionInformation::print(FILE * fptr)
{
	if(returnType_ >=VOID_TYPE && returnType_ <=DOUBLE_TYPE){
		fprintf(fptr, "%s ", noun_list[returnType_].sym );
	} else {
		fprintf(fptr, "Unexpected return type for function\n");
	}
	fprintf(fptr, "%s(", funcName_.c_str());
	if (paramList_) paramList_->print(fptr);
	fprintf(fptr, ");\n" );
}

FunctionInformation::~FunctionInformation()
{
	if(paramList_) { delete paramList_; paramList_=0; }
	//if(funcBody_) { delete funcBody_; funcBody_=0; }
	// funcScope_ was created by in the constructor - so we delete it
	if(funcScope_) { delete funcScope_; funcScope_=0; }
}
FunctionParameter::FunctionParameter(DataType type, char * name): 
	var_type(type), var_name(name), arr_len(-1), prev_(NULL), next_(NULL){
	if (!( (type>=INT8_TYPE&& type<=DOUBLE_TYPE) ||
		(type>=INT8_REF_TYPE&& type<=DOUBLE_REF_TYPE))){
		stringstream s;
		s << "SEMANTIC error: only INT8_TYPE ... DOUBLE_TYPE is allowed in decl: "  << var_name<< endl;
		print_err(Util::compiler_sem_err, s.str() , line_no, __LINE__, __FILE__);
		cerr << "NEED TO LINK  BACK TO ERROR: FIX ME" << endl;
	}
	//cout << "constructing FunctionParameter: " << var_name << endl;
}
FunctionParameter::~FunctionParameter(){
	debug_log_file << "deleting ~FunctionParameter: var_name:" << var_name << endl;
	if (next_) { delete next_; next_=0; }
	debug_log_file << "end deleting ~FunctionParameter " << endl;
}


void FunctionParameter::print(FILE * edit_out){
	struct FunctionParameter * vl_ptr=this;
	while(vl_ptr){
		if(vl_ptr->var_type>=INT8_TYPE && vl_ptr->var_type<=DOUBLE_TYPE){
			fprintf(edit_out, "%s %s", noun_list[vl_ptr->var_type].sym,vl_ptr->var_name.c_str());
		} else if (vl_ptr->var_type>=INT8_ARR_TYPE&&vl_ptr->var_type<=DOUBLE_ARR_TYPE){
			DataType tdt=DataType(INT8_TYPE + vl_ptr->var_type-INT8_ARR_TYPE);
			fprintf(edit_out, "%s %s[%d]", noun_list[tdt].sym, vl_ptr->var_name.c_str(), arr_len, vl_ptr->var_type);
		} else if (vl_ptr->var_type>=INT8_REF_TYPE&&vl_ptr->var_type<=DOUBLE_REF_TYPE){
			DataType tdt=DataType(INT8_TYPE + vl_ptr->var_type-INT8_REF_TYPE);
			fprintf(edit_out, "%s & %s", noun_list[tdt].sym, vl_ptr->var_name.c_str());
		} else {
			fprintf(edit_out, "INTERNAL ERROR:Unknown data type: file: %s, line: %d\n", __FILE__, __LINE__);
		}
		vl_ptr=vl_ptr->next_;
		if(vl_ptr) {
			fprintf(edit_out, ",");
		}
	}
}

FunctionParameter::FunctionParameter(DataType type, char * name, int len): var_type(type), var_name(name), arr_len(len), prev_(NULL), next_(NULL){
	if(!is_of_arr_type(type)){
		cerr << "SEMANTIC error: only INT8_ARR_TYPE ... DOUBLE_ARR_TYPE array Types are allowed in decl: " << var_name << endl;
		cerr << "NEED TO LINK  BACK TO ERROR: FIX ME" << endl;
	}
	cout << "constructing FunctionParameter: " << var_name << endl;
}

} /* close namespace Statement */
