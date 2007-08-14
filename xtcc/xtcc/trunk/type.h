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
     TOT = 258,
     AX = 259,
     CNT = 260,
     TTL = 261,
     FOR = 262,
     TEXT = 263,
     NAME = 264,
     FNUMBER = 265,
     INUMBER = 266,
     CODELIST = 267,
     LISTA = 268,
     IF = 269,
     ELSE = 270,
     VOID_T = 271,
     U_INT8_T = 272,
     INT8_T = 273,
     U_INT16_T = 274,
     INT16_T = 275,
     U_INT32_T = 276,
     INT32_T = 277,
     FLOAT_T = 278,
     DOUBLE_T = 279,
     AXSTART = 280,
     TABSTART = 281,
     ED_START = 282,
     DATA_STRUCT = 283,
     REC_LEN = 284,
     ED_END = 285,
     TAB = 286,
     COND_START = 287,
     CONTINUE = 288,
     BREAK = 289,
     LOGOR = 290,
     LOGAND = 291,
     NOEQ = 292,
     ISEQ = 293,
     GEQ = 294,
     LEQ = 295,
     NOT = 296,
     UMINUS = 297,
     FUNC_CALL = 298
   };
#endif
#define TOT 258
#define AX 259
#define CNT 260
#define TTL 261
#define FOR 262
#define TEXT 263
#define NAME 264
#define FNUMBER 265
#define INUMBER 266
#define CODELIST 267
#define LISTA 268
#define IF 269
#define ELSE 270
#define VOID_T 271
#define U_INT8_T 272
#define INT8_T 273
#define U_INT16_T 274
#define INT16_T 275
#define U_INT32_T 276
#define INT32_T 277
#define FLOAT_T 278
#define DOUBLE_T 279
#define AXSTART 280
#define TABSTART 281
#define ED_START 282
#define DATA_STRUCT 283
#define REC_LEN 284
#define ED_END 285
#define TAB 286
#define COND_START 287
#define CONTINUE 288
#define BREAK 289
#define LOGOR 290
#define LOGAND 291
#define NOEQ 292
#define ISEQ 293
#define GEQ 294
#define LEQ 295
#define NOT 296
#define UMINUS 297
#define FUNC_CALL 298




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 102 "type.y"
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
#line 140 "type.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



