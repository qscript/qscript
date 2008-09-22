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
     IF = 258,
     ELSE = 259,
     FNUMBER = 260,
     INUMBER = 261,
     NAME = 262,
     QTEXT = 263,
     SP = 264,
     MP = 265,
     VOID_T = 266,
     INT8_T = 267,
     INT16_T = 268,
     INT32_T = 269,
     FLOAT_T = 270,
     DOUBLE_T = 271,
     LOGOR = 272,
     LOGAND = 273,
     NOEQ = 274,
     ISEQ = 275,
     GEQ = 276,
     LEQ = 277,
     NOT = 278,
     UMINUS = 279,
     COUNT = 280,
     IN = 281,
     FUNC_CALL = 282,
     CONTINUE = 283,
     BREAK = 284,
     TEXT = 285,
     ATTRIBUTE_LIST = 286,
     STUBS_LIST = 287
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FNUMBER 260
#define INUMBER 261
#define NAME 262
#define QTEXT 263
#define SP 264
#define MP 265
#define VOID_T 266
#define INT8_T 267
#define INT16_T 268
#define INT32_T 269
#define FLOAT_T 270
#define DOUBLE_T 271
#define LOGOR 272
#define LOGAND 273
#define NOEQ 274
#define ISEQ 275
#define GEQ 276
#define LEQ 277
#define NOT 278
#define UMINUS 279
#define COUNT 280
#define IN 281
#define FUNC_CALL 282
#define CONTINUE 283
#define BREAK 284
#define TEXT 285
#define ATTRIBUTE_LIST 286
#define STUBS_LIST 287




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 90 "qscript.y"
{
	double dval;
	int ival ;
	char name[MY_STR_MAX];
	char text_buf[MY_STR_MAX];
	datatype dt;
	struct expr * expr;
	struct stmt * stmt;
	struct cmpd_stmt * c_stmt;
	class question* ques;
}
/* Line 1489 of yacc.c.  */
#line 125 "qscript.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

