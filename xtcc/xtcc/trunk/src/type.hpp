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
     FOR = 264,
     FLD = 265,
     BIT = 266,
     TEXT = 267,
     NAME = 268,
     DEFINELIST = 269,
     FNUMBER = 270,
     INUMBER = 271,
     CODELIST = 272,
     LISTA = 273,
     IF = 274,
     ELSE = 275,
     IN = 276,
     VOID_T = 277,
     INT8_T = 278,
     INT16_T = 279,
     INT32_T = 280,
     FLOAT_T = 281,
     DOUBLE_T = 282,
     ATTRIBUTE_LIST = 283,
     AXSTART = 284,
     TABSTART = 285,
     ED_START = 286,
     DATA_STRUCT = 287,
     REC_LEN = 288,
     ED_END = 289,
     TAB = 290,
     COND_START = 291,
     CONTINUE = 292,
     BREAK = 293,
     INC = 294,
     LOGOR = 295,
     LOGAND = 296,
     NOEQ = 297,
     ISEQ = 298,
     GEQ = 299,
     LEQ = 300,
     NOT = 301,
     UMINUS = 302,
     FUNC_CALL = 303
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
#line 120 "src/type.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


