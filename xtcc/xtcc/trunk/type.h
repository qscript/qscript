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
     FOR = 263,
     FLD = 264,
     BIT = 265,
     TEXT = 266,
     NAME = 267,
     DEFINELIST = 268,
     FNUMBER = 269,
     INUMBER = 270,
     CODELIST = 271,
     LISTA = 272,
     IF = 273,
     ELSE = 274,
     IN = 275,
     VOID_T = 276,
     INT8_T = 277,
     INT16_T = 278,
     INT32_T = 279,
     FLOAT_T = 280,
     DOUBLE_T = 281,
     ATTRIBUTE_LIST = 282,
     AXSTART = 283,
     TABSTART = 284,
     ED_START = 285,
     DATA_STRUCT = 286,
     REC_LEN = 287,
     ED_END = 288,
     TAB = 289,
     COND_START = 290,
     CONTINUE = 291,
     BREAK = 292,
     LOGOR = 293,
     LOGAND = 294,
     NOEQ = 295,
     ISEQ = 296,
     GEQ = 297,
     LEQ = 298,
     NOT = 299,
     UMINUS = 300,
     FUNC_CALL = 301
   };
#endif
/* Tokens.  */
#define CONVERT 258
#define TOT 259
#define AX 260
#define CNT 261
#define TTL 262
#define FOR 263
#define FLD 264
#define BIT 265
#define TEXT 266
#define NAME 267
#define DEFINELIST 268
#define FNUMBER 269
#define INUMBER 270
#define CODELIST 271
#define LISTA 272
#define IF 273
#define ELSE 274
#define IN 275
#define VOID_T 276
#define INT8_T 277
#define INT16_T 278
#define INT32_T 279
#define FLOAT_T 280
#define DOUBLE_T 281
#define ATTRIBUTE_LIST 282
#define AXSTART 283
#define TABSTART 284
#define ED_START 285
#define DATA_STRUCT 286
#define REC_LEN 287
#define ED_END 288
#define TAB 289
#define COND_START 290
#define CONTINUE 291
#define BREAK 292
#define LOGOR 293
#define LOGAND 294
#define NOEQ 295
#define ISEQ 296
#define GEQ 297
#define LEQ 298
#define NOT 299
#define UMINUS 300
#define FUNC_CALL 301




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 111 "type.y"
{
	double dval;
	int ival ;
	struct symtab *symbolTableEntry_;
	char * name;
	struct AbstractExpression * expr;
	struct AbstractStatement * stmt;
	struct CompoundStatement * c_stmt;
	int column_no;
	int code_list;
	char text_buf[MY_STR_MAX];
	struct FunctionParameter * v_list;
	DataType dt;
	struct ax * ax;
	struct stub * stub;
	struct table * tbl;
	class basic_print_ax_stmt * print_stmt;
	class basic_count_ax_stmt * count_stmt;
}
/* Line 1489 of yacc.c.  */
#line 161 "type.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

