/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     INC = 263,
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
     LOGOR = 294,
     LOGAND = 295,
     NOEQ = 296,
     ISEQ = 297,
     GEQ = 298,
     LEQ = 299,
     NOT = 300,
     UMINUS = 301,
     FUNC_CALL = 302
   };
#endif
/* Tokens.  */
#define CONVERT 258
#define TOT 259
#define AX 260
#define CNT 261
#define TTL 262
#define INC 263
#define FOR 264
#define FLD 265
#define BIT 266
#define TEXT 267
#define NAME 268
#define DEFINELIST 269
#define FNUMBER 270
#define INUMBER 271
#define CODELIST 272
#define LISTA 273
#define IF 274
#define ELSE 275
#define IN 276
#define VOID_T 277
#define INT8_T 278
#define INT16_T 279
#define INT32_T 280
#define FLOAT_T 281
#define DOUBLE_T 282
#define ATTRIBUTE_LIST 283
#define AXSTART 284
#define TABSTART 285
#define ED_START 286
#define DATA_STRUCT 287
#define REC_LEN 288
#define ED_END 289
#define TAB 290
#define COND_START 291
#define CONTINUE 292
#define BREAK 293
#define LOGOR 294
#define LOGAND 295
#define NOEQ 296
#define ISEQ 297
#define GEQ 298
#define LEQ 299
#define NOT 300
#define UMINUS 301
#define FUNC_CALL 302




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 116 "type.y"
{
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
}
/* Line 1489 of yacc.c.  */
#line 163 "type.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

