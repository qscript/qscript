/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CONVERT = 258,
     TOT = 259,
     AX = 260,
     CNT = 261,
     TTL = 262,
     WT = 263,
     MP = 264,
     FOR = 265,
     FLD = 266,
     BIT = 267,
     TEXT = 268,
     NAME = 269,
     DEFINELIST = 270,
     FNUMBER = 271,
     INUMBER = 272,
     CODELIST = 273,
     LISTA = 274,
     IF = 275,
     ELSE = 276,
     IN = 277,
     VOID_T = 278,
     INT8_T = 279,
     INT16_T = 280,
     INT32_T = 281,
     FLOAT_T = 282,
     DOUBLE_T = 283,
     ATTRIBUTE_LIST = 284,
     AXSTART = 285,
     TABSTART = 286,
     ED_START = 287,
     DATA_STRUCT = 288,
     REC_LEN = 289,
     ED_END = 290,
     TAB = 291,
     COND_START = 292,
     CONTINUE = 293,
     BREAK = 294,
     INC = 295,
     LOGOR = 296,
     LOGAND = 297,
     NOEQ = 298,
     ISEQ = 299,
     GEQ = 300,
     LEQ = 301,
     NOT = 302,
     UMINUS = 303,
     FUNC_CALL = 304
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 121 "src/type.ypp"

	double dval;
	int ival ;
	struct symtab *symbolTableEntry_;
	char * name;
	struct Expression::AbstractExpression * expr;
	struct Statement::AbstractStatement * stmt;
	struct Statement::CompoundStatement * c_stmt;
	int column_no;
	int code_list;
	char text_buf[MY_STR_MAX];
	struct Statement::FunctionParameter * v_list;
	DataType dt;
	struct Table::ax * ax;
	struct Table::stub * stub;
	struct Table::table * tbl;
	Table::AbstractPrintableAxisStatement * print_stmt;
	Table::AbstractCountableAxisStatement * count_stmt;



/* Line 2068 of yacc.c  */
#line 121 "src/type.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


