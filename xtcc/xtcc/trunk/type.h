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
     TEXT = 265,
     NAME = 266,
     FNUMBER = 267,
     INUMBER = 268,
     CODELIST = 269,
     LISTA = 270,
     IF = 271,
     ELSE = 272,
     VOID_T = 273,
     INT8_T = 274,
     INT16_T = 275,
     INT32_T = 276,
     FLOAT_T = 277,
     DOUBLE_T = 278,
     AXSTART = 279,
     TABSTART = 280,
     ED_START = 281,
     DATA_STRUCT = 282,
     REC_LEN = 283,
     ED_END = 284,
     TAB = 285,
     COND_START = 286,
     CONTINUE = 287,
     BREAK = 288,
     LOGOR = 289,
     LOGAND = 290,
     NOEQ = 291,
     ISEQ = 292,
     GEQ = 293,
     LEQ = 294,
     NOT = 295,
     UMINUS = 296,
     FUNC_CALL = 297
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
#define TEXT 265
#define NAME 266
#define FNUMBER 267
#define INUMBER 268
#define CODELIST 269
#define LISTA 270
#define IF 271
#define ELSE 272
#define VOID_T 273
#define INT8_T 274
#define INT16_T 275
#define INT32_T 276
#define FLOAT_T 277
#define DOUBLE_T 278
#define AXSTART 279
#define TABSTART 280
#define ED_START 281
#define DATA_STRUCT 282
#define REC_LEN 283
#define ED_END 284
#define TAB 285
#define COND_START 286
#define CONTINUE 287
#define BREAK 288
#define LOGOR 289
#define LOGAND 290
#define NOEQ 291
#define ISEQ 292
#define GEQ 293
#define LEQ 294
#define NOT 295
#define UMINUS 296
#define FUNC_CALL 297




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 101 "type.y"
{
	double dval;
	int ival ;
	struct symtab *symp;
	char * name;
	struct expr * expr;
	struct stmt * stmt;
	struct cmpd_stmt * c_stmt;
	int column_no;
	int code_list;
	char text_buf[MY_STR_MAX];
	struct var_list * v_list;
	datatype dt;
	struct ax * ax;
	struct table * tbl;
	class basic_ax_stmt * basic_ax_stmt;
}
/* Line 1489 of yacc.c.  */
#line 151 "type.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

