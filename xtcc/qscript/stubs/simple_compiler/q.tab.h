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
     CONST = 272,
     LOGOR = 273,
     LOGAND = 274,
     NOEQ = 275,
     ISEQ = 276,
     GEQ = 277,
     LEQ = 278,
     NOT = 279,
     UMINUS = 280,
     COUNT = 281,
     FUNC_CALL = 282,
     IF = 283,
     ELSE = 284,
     STUBS_LIST = 285
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
#define CONST 272
#define LOGOR 273
#define LOGAND 274
#define NOEQ 275
#define ISEQ 276
#define GEQ 277
#define LEQ 278
#define NOT 279
#define UMINUS 280
#define COUNT 281
#define FUNC_CALL 282
#define IF 283
#define ELSE 284
#define STUBS_LIST 285




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 87 "q.y"
{
	type_qualifier type_qual;
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
#line 123 "q.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

