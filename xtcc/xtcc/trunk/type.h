/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

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
     TEXT = 264,
     NAME = 265,
     FNUMBER = 266,
     INUMBER = 267,
     CODELIST = 268,
     LISTA = 269,
     IF = 270,
     ELSE = 271,
     VOID_T = 272,
     U_INT8_T = 273,
     INT8_T = 274,
     U_INT16_T = 275,
     INT16_T = 276,
     U_INT32_T = 277,
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
#define CONVERT 258
#define TOT 259
#define AX 260
#define CNT 261
#define TTL 262
#define FOR 263
#define TEXT 264
#define NAME 265
#define FNUMBER 266
#define INUMBER 267
#define CODELIST 268
#define LISTA 269
#define IF 270
#define ELSE 271
#define VOID_T 272
#define U_INT8_T 273
#define INT8_T 274
#define U_INT16_T 275
#define INT16_T 276
#define U_INT32_T 277
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
/* Line 1249 of yacc.c.  */
#line 142 "type.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



