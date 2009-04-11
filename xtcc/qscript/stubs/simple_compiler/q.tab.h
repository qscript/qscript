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
     INUMBER = 258,
     FNUMBER = 259,
     NAME = 260,
     TEXT = 261,
     SP = 262,
     MP = 263,
     VOID_T = 264,
     INT8_T = 265,
     INT16_T = 266,
     INT32_T = 267,
     FLOAT_T = 268,
     DOUBLE_T = 269,
     STRING_T = 270,
     IN = 271,
     LOGOR = 272,
     LOGAND = 273,
     NOEQ = 274,
     ISEQ = 275,
     GEQ = 276,
     LEQ = 277,
     NOT = 278,
     UMINUS = 279,
     COUNT = 280,
     FUNC_CALL = 281,
     IF = 282,
     ELSE = 283,
     STUBS_LIST = 284
   };
#endif
/* Tokens.  */
#define INUMBER 258
#define FNUMBER 259
#define NAME 260
#define TEXT 261
#define SP 262
#define MP 263
#define VOID_T 264
#define INT8_T 265
#define INT16_T 266
#define INT32_T 267
#define FLOAT_T 268
#define DOUBLE_T 269
#define STRING_T 270
#define IN 271
#define LOGOR 272
#define LOGAND 273
#define NOEQ 274
#define ISEQ 275
#define GEQ 276
#define LEQ 277
#define NOT 278
#define UMINUS 279
#define COUNT 280
#define FUNC_CALL 281
#define IF 282
#define ELSE 283
#define STUBS_LIST 284




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 87 "q.y"
{
	int ival;
	double dval;
	char name[MY_STR_MAX];
	char text_buf[MY_STR_MAX];
	datatype dt;
	struct stmt * stmt;
	struct expr * expr;
	//class question* ques;
	struct cmpd_stmt * c_stmt;

}
/* Line 1489 of yacc.c.  */
#line 120 "q.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

