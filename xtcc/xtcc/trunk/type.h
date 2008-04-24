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
     DEFINELIST = 267,
     FNUMBER = 268,
     INUMBER = 269,
     CODELIST = 270,
     LISTA = 271,
     IF = 272,
     ELSE = 273,
     IN = 274,
     VOID_T = 275,
     INT8_T = 276,
     INT16_T = 277,
     INT32_T = 278,
     FLOAT_T = 279,
     DOUBLE_T = 280,
     AXSTART = 281,
     TABSTART = 282,
     ED_START = 283,
     DATA_STRUCT = 284,
     REC_LEN = 285,
     ED_END = 286,
     TAB = 287,
     COND_START = 288,
     CONTINUE = 289,
     BREAK = 290,
     LOGOR = 291,
     LOGAND = 292,
     NOEQ = 293,
     ISEQ = 294,
     GEQ = 295,
     LEQ = 296,
     NOT = 297,
     UMINUS = 298,
     FUNC_CALL = 299
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
#define DEFINELIST 267
#define FNUMBER 268
#define INUMBER 269
#define CODELIST 270
#define LISTA 271
#define IF 272
#define ELSE 273
#define IN 274
#define VOID_T 275
#define INT8_T 276
#define INT16_T 277
#define INT32_T 278
#define FLOAT_T 279
#define DOUBLE_T 280
#define AXSTART 281
#define TABSTART 282
#define ED_START 283
#define DATA_STRUCT 284
#define REC_LEN 285
#define ED_END 286
#define TAB 287
#define COND_START 288
#define CONTINUE 289
#define BREAK 290
#define LOGOR 291
#define LOGAND 292
#define NOEQ 293
#define ISEQ 294
#define GEQ 295
#define LEQ 296
#define NOT 297
#define UMINUS 298
#define FUNC_CALL 299




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 105 "type.y"
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
#line 155 "type.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

