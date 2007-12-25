/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

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

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

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
     U_INT8_T = 274,
     INT8_T = 275,
     U_INT16_T = 276,
     INT16_T = 277,
     U_INT32_T = 278,
     INT32_T = 279,
     FLOAT_T = 280,
     DOUBLE_T = 281,
     AXSTART = 282,
     TABSTART = 283,
     ED_START = 284,
     DATA_STRUCT = 285,
     REC_LEN = 286,
     ED_END = 287,
     TAB = 288,
     COND_START = 289,
     CONTINUE = 290,
     BREAK = 291,
     LOGOR = 292,
     LOGAND = 293,
     NOEQ = 294,
     ISEQ = 295,
     GEQ = 296,
     LEQ = 297,
     NOT = 298,
     UMINUS = 299,
     FUNC_CALL = 300
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
#define U_INT8_T 274
#define INT8_T 275
#define U_INT16_T 276
#define INT16_T 277
#define U_INT32_T 278
#define INT32_T 279
#define FLOAT_T 280
#define DOUBLE_T 281
#define AXSTART 282
#define TABSTART 283
#define ED_START 284
#define DATA_STRUCT 285
#define REC_LEN 286
#define ED_END 287
#define TAB 288
#define COND_START 289
#define CONTINUE 290
#define BREAK 291
#define LOGOR 292
#define LOGAND 293
#define NOEQ 294
#define ISEQ 295
#define GEQ 296
#define LEQ 297
#define NOT 298
#define UMINUS 299
#define FUNC_CALL 300




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 101 "type.y"
typedef union YYSTYPE {
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
} YYSTYPE;
/* Line 1447 of yacc.c.  */
#line 146 "type.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



