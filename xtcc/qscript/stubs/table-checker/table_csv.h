/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
     TABLE = 258,
     PAGE = 259,
     TOTAL = 260,
     SIGMA = 261,
     MEAN = 262,
     BASE_TEXT = 263,
     STUB_FREQ = 264,
     STUB_PERC = 265,
     STUB_MEAN = 266,
     STUB_STD_DEV = 267,
     INUMBER = 268,
     FNUMBER = 269,
     NAME = 270,
     TEXT = 271,
     NEWL = 272,
     COMMA = 273,
     DOT = 274,
     EMPTY_LINE_2_COLS = 275,
     EMPTY_LINE_1_COLS = 276,
     BAN_TOTAL = 277,
     SIDE_TOTAL = 278
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 45 "table_csv.y"

	int ival;
	double dval;
	char name[4095];
	char text_buf[4095];



/* Line 2068 of yacc.c  */
#line 82 "table_csv.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE qtm_table_output_lval;


