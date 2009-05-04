/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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
     FOR = 272,
     CONST = 273,
     LOGOR = 274,
     LOGAND = 275,
     NOEQ = 276,
     ISEQ = 277,
     GEQ = 278,
     LEQ = 279,
     NOT = 280,
     UMINUS = 281,
     COUNT = 282,
     FUNC_CALL = 283,
     IF = 284,
     ELSE = 285,
     STUBS_LIST = 286
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
#define FOR 272
#define CONST 273
#define LOGOR 274
#define LOGAND 275
#define NOEQ 276
#define ISEQ 277
#define GEQ 278
#define LEQ 279
#define NOT 280
#define UMINUS 281
#define COUNT 282
#define FUNC_CALL 283
#define IF 284
#define ELSE 285
#define STUBS_LIST 286




/* Copy the first part of user declarations.  */
#line 7 "q.y"


//#include "common.h"

#include <limits.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

//#include "tree.h"
#include "debug_mem.h"
#include "symtab.h"
#include "scope.h"
#include "stmt.h"
#include "expr.h"
#include "named_attributes.h"
#include "named_range.h"

#include "qscript_parser.h"

	//using qscript_parser::yyerror;
	//using qscript_parser::yylex;
	//using qscript_parser::yywrap;
	extern int yylex();
	extern void yyerror(const char * s);
	using std::cout;
	using std::cerr;
	using std::endl;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 40 "q.y"
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
/* Line 187 of yacc.c.  */
#line 204 "q.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 217 "q.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   478

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNRULES -- Number of states.  */
#define YYNSTATES  145

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    37,     2,     2,
      20,    21,    35,    34,    24,    33,     2,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    45,
      29,    22,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    18,     2,    19,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    47,     2,    46,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    23,    25,    26,    27,    28,    31,    32,
      38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    30,    37,    43,    50,    52,    54,
      56,    58,    60,    62,    64,    65,    76,    80,    82,    88,
      96,    99,   106,   113,   117,   121,   125,   129,   133,   136,
     140,   144,   148,   152,   156,   160,   164,   168,   172,   175,
     177,   179,   181,   186,   193,   198,   200,   204,   208,   210,
     214,   216,   221,   225,   227,   231,   235,   237,   238,   245,
     248
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    57,    -1,    54,    -1,    50,    54,    -1,
       9,    -1,    10,    -1,    11,    -1,    12,    -1,    13,    -1,
      14,    -1,    15,    -1,    23,    -1,    51,     5,    45,    -1,
      52,    51,     5,    22,    62,    45,    -1,    51,     5,    22,
      62,    45,    -1,    51,     5,    18,    62,    19,    45,    -1,
      61,    -1,    60,    -1,    53,    -1,    68,    -1,    57,    -1,
      59,    -1,    55,    -1,    -1,    17,    20,    62,    45,    62,
      45,    62,    21,    56,    57,    -1,    58,    50,    46,    -1,
      47,    -1,    42,    20,    62,    21,    54,    -1,    42,    20,
      62,    21,    54,    43,    54,    -1,    62,    45,    -1,     5,
       6,    64,    51,    65,    45,    -1,     5,     6,    64,    51,
       5,    45,    -1,    62,    34,    62,    -1,    62,    33,    62,
      -1,    62,    35,    62,    -1,    62,    36,    62,    -1,    62,
      37,    62,    -1,    33,    62,    -1,    62,    29,    62,    -1,
      62,    30,    62,    -1,    62,    32,    62,    -1,    62,    31,
      62,    -1,    62,    28,    62,    -1,    62,    27,    62,    -1,
      62,    25,    62,    -1,    62,    26,    62,    -1,    62,    22,
      62,    -1,    38,    62,    -1,     3,    -1,     4,    -1,     5,
      -1,     5,    18,    62,    19,    -1,     5,    18,    62,    24,
      62,    19,    -1,     5,    20,    63,    21,    -1,     6,    -1,
      20,    62,    21,    -1,    62,    16,    65,    -1,    62,    -1,
      63,    24,    62,    -1,     7,    -1,     8,    20,     3,    21,
      -1,    20,    66,    21,    -1,    67,    -1,    66,    24,    67,
      -1,     3,    33,     3,    -1,     3,    -1,    -1,    44,     5,
      69,    22,    70,    45,    -1,     6,     3,    -1,    70,     6,
       3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   118,   118,   127,   138,   146,   147,   148,   149,   150,
     151,   152,   155,   160,   165,   167,   171,   182,   183,   184,
     185,   186,   189,   190,   194,   194,   209,   260,   300,   310,
     322,   353,   422,   503,   512,   521,   530,   539,   548,   557,
     566,   575,   584,   593,   602,   611,   620,   631,   640,   649,
     658,   666,   674,   683,   692,   744,   751,   758,   776,   777,
     782,   783,   786,   790,   791,   794,   804,   809,   809,   827,
     834
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INUMBER", "FNUMBER", "NAME", "TEXT",
  "SP", "MP", "VOID_T", "INT8_T", "INT16_T", "INT32_T", "FLOAT_T",
  "DOUBLE_T", "STRING_T", "IN", "FOR", "'['", "']'", "'('", "')'", "'='",
  "CONST", "','", "LOGOR", "LOGAND", "NOEQ", "ISEQ", "'<'", "'>'", "GEQ",
  "LEQ", "'-'", "'+'", "'*'", "'/'", "'%'", "NOT", "UMINUS", "COUNT",
  "FUNC_CALL", "IF", "ELSE", "STUBS_LIST", "';'", "'}'", "'{'", "$accept",
  "prog", "stmt_list", "datatype", "type_qual", "decl_stmt", "stmt",
  "for_loop_stmt", "@1", "cmpd_stmt", "open_curly", "if_stmt", "expr_stmt",
  "question", "expression", "expr_list", "qtype", "range_allowed_values",
  "range_list", "range", "stubs", "@2", "stub_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,    91,    93,
      40,    41,    61,   273,    44,   274,   275,   276,   277,    60,
      62,   278,   279,    45,    43,    42,    47,    37,   280,   281,
     282,   283,   284,   285,   286,    59,   125,   123
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    51,    51,    51,
      51,    51,    52,    53,    53,    53,    53,    54,    54,    54,
      54,    54,    54,    54,    56,    55,    57,    58,    59,    59,
      60,    61,    61,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    63,    63,
      64,    64,    65,    66,    66,    67,    67,    69,    68,    70,
      70
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     6,     5,     6,     1,     1,     1,
       1,     1,     1,     1,     0,    10,     3,     1,     5,     7,
       2,     6,     6,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     1,     4,     6,     4,     1,     3,     3,     1,     3,
       1,     4,     3,     1,     3,     3,     1,     0,     6,     2,
       3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    27,     0,     2,     0,     1,    49,    50,    51,    55,
       5,     6,     7,     8,     9,    10,    11,     0,     0,    12,
       0,     0,     0,     0,     0,     0,     0,    19,     3,    23,
      21,    22,    18,    17,     0,    20,     0,     0,     0,     0,
      51,     0,    38,    48,     0,    67,    26,     4,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    30,    60,     0,     0,     0,
      58,     0,     0,    56,     0,     0,     0,     0,    13,     0,
       0,    57,    47,    45,    46,    44,    43,    39,    40,    42,
      41,    34,    33,    35,    36,    37,     0,     0,    52,     0,
      54,     0,     0,     0,     0,     0,     0,     0,    66,     0,
      63,     0,     0,     0,     0,    59,     0,    28,     0,     0,
       0,    15,     0,     0,    62,     0,    61,    32,    31,    53,
       0,     0,    69,     0,    68,    16,    14,    65,    64,     0,
      29,    70,    24,     0,    25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    24,    25,    26,    27,    28,    29,   143,    30,
       4,    31,    32,    33,    34,    71,    68,    81,   109,   110,
      35,    75,   119
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -41
static const yytype_int16 yypact[] =
{
     -40,   -41,    25,   -41,   111,   -41,   -41,   -41,     6,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,     8,   132,   -41,
     132,   132,     9,    26,    60,    50,   418,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   146,   -41,    11,   132,   132,   132,
      -3,   278,    14,    14,   132,   -41,   -41,   -41,   -13,    52,
      36,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   -41,   -41,    38,   418,   256,
     388,   -10,   168,   -41,   300,    39,   132,   132,   -41,    40,
      65,   -41,   388,   410,   432,   441,   441,    17,    17,    17,
      17,    51,    51,    14,    14,    14,    73,     3,   -41,   132,
     -41,   132,   132,   111,    72,   322,   190,   132,    46,    -8,
     -41,    68,    47,    49,   344,   388,   212,    48,    92,     4,
      54,   -41,   234,    93,   -41,    65,   -41,   -41,   -41,   -41,
     132,   111,   -41,    94,   -41,   -41,   -41,   -41,   -41,   366,
     -41,   -41,   -41,   -40,   -41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -41,   -41,   -41,   -20,   -41,   -41,   -22,   -41,   -41,     0,
     -41,   -41,   -41,   -41,   -17,   -41,   -41,    13,   -41,   -25,
     -41,   -41,   -41
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
       3,    41,    47,    42,    43,    76,    49,     1,   112,    77,
     133,   100,    36,   124,   101,    37,   125,    38,    66,    67,
      69,    70,    72,    80,    37,     5,    38,    74,    39,    44,
      50,    45,    78,    50,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    97,   134,
      60,    61,    62,    63,    64,    48,    80,    79,    96,   105,
     106,   104,   107,     6,     7,     8,     9,    50,   108,    10,
      11,    12,    13,    14,    15,    16,   111,    17,   118,   123,
      18,   117,   114,    19,   115,   116,    62,    63,    64,   126,
     122,   131,   127,    20,   128,   132,   137,   141,    21,   135,
     138,     0,    22,     0,    23,     0,    46,     1,     0,   140,
     113,     0,     0,   139,     6,     7,     8,     9,     0,     0,
      10,    11,    12,    13,    14,    15,    16,     0,    17,     0,
       0,    18,     0,     0,    19,     6,     7,    40,     9,     0,
       0,     0,     0,   144,    20,     0,     0,     0,     0,    21,
       0,     0,    18,    22,     0,    23,     0,     0,     1,     0,
       0,     0,    50,     0,     0,    20,     0,     0,    51,     0,
      21,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    50,     0,     0,     0,     0,     0,
      51,    65,     0,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    50,     0,     0,     0,
       0,     0,    51,   102,     0,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    50,     0,
       0,     0,     0,     0,    51,   121,     0,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      50,     0,     0,     0,     0,     0,    51,   130,     0,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    50,     0,     0,    98,     0,     0,    51,   136,
      99,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    50,     0,     0,     0,     0,    73,
      51,     0,     0,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    50,     0,     0,     0,
       0,   103,    51,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    50,     0,
       0,   120,     0,     0,    51,     0,     0,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      50,     0,     0,   129,     0,     0,    51,     0,     0,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    50,     0,     0,     0,     0,   142,    51,     0,
       0,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    50,     0,     0,     0,     0,     0,
      51,     0,     0,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    50,    10,    11,    12,
      13,    14,    15,    16,     0,     0,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    50,     0,
       0,     0,     0,     0,     0,     0,     0,    50,     0,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      56,    57,    58,    59,    60,    61,    62,    63,    64
};

static const yytype_int16 yycheck[] =
{
       0,    18,    24,    20,    21,    18,    26,    47,     5,    22,
       6,    21,     6,    21,    24,    18,    24,    20,     7,     8,
      37,    38,    39,    20,    18,     0,    20,    44,    20,    20,
      16,     5,    45,    16,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    68,    45,
      33,    34,    35,    36,    37,     5,    20,     5,    20,    76,
      77,    22,    22,     3,     4,     5,     6,    16,     3,     9,
      10,    11,    12,    13,    14,    15,     3,    17,     6,    33,
      20,   103,    99,    23,   101,   102,    35,    36,    37,    21,
     107,    43,    45,    33,    45,     3,     3,     3,    38,    45,
     125,    -1,    42,    -1,    44,    -1,    46,    47,    -1,   131,
      97,    -1,    -1,   130,     3,     4,     5,     6,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,    -1,    17,    -1,
      -1,    20,    -1,    -1,    23,     3,     4,     5,     6,    -1,
      -1,    -1,    -1,   143,    33,    -1,    -1,    -1,    -1,    38,
      -1,    -1,    20,    42,    -1,    44,    -1,    -1,    47,    -1,
      -1,    -1,    16,    -1,    -1,    33,    -1,    -1,    22,    -1,
      38,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    16,    -1,    -1,    -1,    -1,    -1,
      22,    45,    -1,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    16,    -1,    -1,    -1,
      -1,    -1,    22,    45,    -1,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    16,    -1,
      -1,    -1,    -1,    -1,    22,    45,    -1,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      16,    -1,    -1,    -1,    -1,    -1,    22,    45,    -1,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    16,    -1,    -1,    19,    -1,    -1,    22,    45,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    16,    -1,    -1,    -1,    -1,    21,
      22,    -1,    -1,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    16,    -1,    -1,    -1,
      -1,    21,    22,    -1,    -1,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    16,    -1,
      -1,    19,    -1,    -1,    22,    -1,    -1,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      16,    -1,    -1,    19,    -1,    -1,    22,    -1,    -1,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    16,    -1,    -1,    -1,    -1,    21,    22,    -1,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    16,    -1,    -1,    -1,    -1,    -1,
      22,    -1,    -1,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    16,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    16,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      29,    30,    31,    32,    33,    34,    35,    36,    37
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    47,    49,    57,    58,     0,     3,     4,     5,     6,
       9,    10,    11,    12,    13,    14,    15,    17,    20,    23,
      33,    38,    42,    44,    50,    51,    52,    53,    54,    55,
      57,    59,    60,    61,    62,    68,     6,    18,    20,    20,
       5,    62,    62,    62,    20,     5,    46,    54,     5,    51,
      16,    22,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    45,     7,     8,    64,    62,
      62,    63,    62,    21,    62,    69,    18,    22,    45,     5,
      20,    65,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    20,    51,    19,    24,
      21,    24,    45,    21,    22,    62,    62,    22,     3,    66,
      67,     3,     5,    65,    62,    62,    62,    54,     6,    70,
      19,    45,    62,    33,    21,    24,    21,    45,    45,    19,
      45,    43,     3,     6,    45,    45,    45,     3,    67,    62,
      54,     3,    21,    56,    57
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 118 "q.y"
    {
	qscript_parser::tree_root=(yyvsp[(1) - (1)].c_stmt);
		while(qscript_parser::tree_root->prev) {
			cerr << "This should never appear: climbing up the tree" << endl;
			qscript_parser::tree_root=qscript_parser::tree_root->prev;
		}
	;}
    break;

  case 3:
#line 127 "q.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
		if(qscript_parser::flag_next_stmt_start_of_block){
			qscript_parser::blk_heads.push_back((yyvsp[(1) - (1)].stmt));
			//cout << "blk_heads.size(): " << blk_heads.size() << endl;
			//start_of_blk=$1;
			qscript_parser::flag_next_stmt_start_of_block=false;
			qscript_parser::blk_start_flag.pop_back();
		}

	;}
    break;

  case 4:
#line 138 "q.y"
    {
		(yyvsp[(1) - (2)].stmt)->next=(yyvsp[(2) - (2)].stmt);
		(yyvsp[(2) - (2)].stmt)->prev=(yyvsp[(1) - (2)].stmt);
		(yyval.stmt)=(yyvsp[(2) - (2)].stmt);
	;}
    break;

  case 12:
#line 155 "q.y"
    {
		   (yyval.type_qual) = CONST_QUAL;
	;}
    break;

  case 13:
#line 160 "q.y"
    {
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (3)].name), (yyvsp[(1) - (3)].dt)/*, line_no*/);
		//free($2);
		// -- why am i not freeing this?
	;}
    break;

  case 14:
#line 165 "q.y"
    {
	;}
    break;

  case 15:
#line 167 "q.y"
    {
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (5)].name), (yyvsp[(1) - (5)].dt), (yyvsp[(4) - (5)].expr));
		// -- why am i not freeing this?
	;}
    break;

  case 16:
#line 171 "q.y"
    {
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		datatype dt=datatype(INT8_ARR_TYPE+((yyvsp[(1) - (6)].dt)-INT8_TYPE));
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (6)].name), dt, (yyvsp[(4) - (6)].expr)/*, line_no*/);
		free((yyvsp[(2) - (6)].name));
	;}
    break;

  case 21:
#line 186 "q.y"
    {
		(yyval.stmt) = (yyvsp[(1) - (1)].c_stmt);
	;}
    break;

  case 24:
#line 194 "q.y"
    {
		++qscript_parser::flag_cmpd_stmt_is_a_for_body;
		qscript_parser::for_loop_max_counter_stack.push_back((yyvsp[(5) - (8)].expr));
	;}
    break;

  case 25:
#line 197 "q.y"
    {
		using qscript_parser::line_no;
		(yyval.stmt) = new for_stmt(FOR_STMT, line_no, (yyvsp[(3) - (10)].expr), (yyvsp[(5) - (10)].expr), (yyvsp[(7) - (10)].expr), (yyvsp[(10) - (10)].c_stmt));

		--qscript_parser::flag_cmpd_stmt_is_a_for_body;
		qscript_parser::for_loop_max_counter_stack.pop_back();
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 26:
#line 209 "q.y"
    {
		using qscript_parser::active_scope;
		using qscript_parser::active_scope_list;
		using qscript_parser::stack_cmpd_stmt;
		using qscript_parser::blk_start_flag;
		using qscript_parser::blk_heads;
		using qscript_parser::mem_addr;
		using qscript_parser::flag_next_stmt_start_of_block;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;

		active_scope_list.pop_back();
		int tmp=active_scope_list.size()-1;
		if(tmp==-1) { 
			active_scope = 0;
			cerr << "Error: active_scope = NULL: should not happen: line_no:" << line_no
				<< endl;
			++no_errors;
			(yyval.c_stmt)=new struct cmpd_stmt(ERROR_TYPE, line_no, 0, 0);
			void *ptr=(yyval.c_stmt);
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		} else { 
			active_scope = active_scope_list[tmp]; 
		}
		struct stmt* head_of_this_chain=blk_heads.back();
		if(blk_start_flag.size() > 0){
			flag_next_stmt_start_of_block = blk_start_flag[blk_start_flag.size()-1];
		}
		if(  head_of_this_chain==0){
			cerr << "Error in compiler : cmpd_bdy:  " << __FILE__ << __LINE__ << endl;
			++no_errors;
		} else {
			(yyvsp[(1) - (3)].c_stmt)->cmpd_bdy = head_of_this_chain;
			blk_heads.pop_back();
		}

		//! update the counter of enlosing cmpd_stmt with 
		//! the number of questions in this cmpd_stmt being popped of
		//! right now
		if(stack_cmpd_stmt.size()>1){
			cmpd_stmt * popped_off_cmpd_stmt_ptr=stack_cmpd_stmt.back();
			stack_cmpd_stmt.pop_back();
			cmpd_stmt * current  = stack_cmpd_stmt.back();
			current->counter_contains_questions+= 
				(popped_off_cmpd_stmt_ptr->counter_contains_questions);
		} 
		(yyval.c_stmt)=(yyvsp[(1) - (3)].c_stmt);
	;}
    break;

  case 27:
#line 260 "q.y"
    {
		using qscript_parser::active_scope;
		using qscript_parser::active_scope_list;
		using qscript_parser::stack_cmpd_stmt;
		using qscript_parser::blk_start_flag;
		using qscript_parser::blk_heads;
		using qscript_parser::mem_addr;
		using qscript_parser::flag_next_stmt_start_of_block;
		using qscript_parser::flag_cmpd_stmt_is_a_func_body;
		using qscript_parser::flag_cmpd_stmt_is_a_for_body;
		using qscript_parser::func_info_table;
		using qscript_parser::nest_lev;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;

		++nest_lev;
		cmpd_stmt * cmpd_stmt_ptr= new cmpd_stmt(CMPD_STMT, 
				line_no, flag_cmpd_stmt_is_a_func_body,
				flag_cmpd_stmt_is_a_for_body);
		(yyval.c_stmt) = cmpd_stmt_ptr;
		stack_cmpd_stmt.push_back(cmpd_stmt_ptr);
		void *ptr=(yyval.c_stmt);
		mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
		mem_addr.push_back(m1);
		if(flag_cmpd_stmt_is_a_func_body>=0){
			(yyval.c_stmt)->sc=func_info_table[qscript_parser::flag_cmpd_stmt_is_a_func_body]->func_scope;
			// reset the flag
			qscript_parser::flag_cmpd_stmt_is_a_func_body=-1;
		} else {
			(yyval.c_stmt)->sc= new scope();
		}
		qscript_parser::flag_next_stmt_start_of_block=true;
		qscript_parser::blk_start_flag.push_back(flag_next_stmt_start_of_block);
		qscript_parser::active_scope_list.push_back((yyval.c_stmt)->sc);
		qscript_parser::active_scope = (yyval.c_stmt)->sc;
	;}
    break;

  case 28:
#line 300 "q.y"
    {
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		using qscript_parser::XTCC_DEBUG_MEM_USAGE;
		(yyval.stmt)=new if_stmt(IFE_STMT,if_line_no,(yyvsp[(3) - (5)].expr),(yyvsp[(5) - (5)].stmt),0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 29:
#line 310 "q.y"
    {
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.stmt)=new if_stmt(IFE_STMT,qscript_parser::if_line_no,(yyvsp[(3) - (7)].expr),(yyvsp[(5) - (7)].stmt),(yyvsp[(7) - (7)].stmt));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, qscript_parser::line_no);
		}
	;}
    break;

  case 30:
#line 323 "q.y"
    {
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		if((yyvsp[(1) - (2)].expr)->isvalid()){
			(yyval.stmt) = new expr_stmt(TEXPR_STMT, line_no, (yyvsp[(1) - (2)].expr));
			if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
				mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
			}
		} else {
			(yyval.stmt) = new expr_stmt(ERROR_TYPE, line_no, (yyvsp[(1) - (2)].expr));
			if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
				mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
			}
		}
	;}
    break;

  case 31:
#line 353 "q.y"
    {
		using qscript_parser::active_scope;
		using qscript_parser::active_scope_list;
		using qscript_parser::stack_cmpd_stmt;
		using qscript_parser::mem_addr;
		using qscript_parser::map_of_active_vars_for_questions;
		using qscript_parser::question_list;
		using qscript_parser::xs;
		using qscript_parser::q_type;
		using qscript_parser::no_mpn;
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;

		string name((yyvsp[(1) - (6)].name));
		string q_text((yyvsp[(2) - (6)].text_buf));
		datatype dt=(yyvsp[(4) - (6)].dt);
		// This is preparatory work
		// for jumping between questions
		// store
		vector<string> active_push_vars;
		vector<string> active_pop_vars;
		for(unsigned int i=0; i< active_scope_list.size(); ++i){
			scope* sc_ptr= active_scope_list[i];
			sc_ptr->print_scope(active_push_vars, active_pop_vars);
		}
		string q_push_name = name + "_push";
		string q_pop_name = name + "_pop";
		map_of_active_vars_for_questions[q_push_name] = active_push_vars;
		map_of_active_vars_for_questions[q_pop_name] = active_pop_vars;
		
		expr * arr_sz=0;
		range_question * q=0;
		if(qscript_parser::flag_cmpd_stmt_is_a_for_body){
			cout << "flag_cmpd_stmt_is_a_for_body: " 
				<< qscript_parser::flag_cmpd_stmt_is_a_for_body << endl;
			arr_sz = qscript_parser::recurse_for_index(qscript_parser::for_loop_max_counter_stack.size()-1);
			q= new range_question(QUESTION_TYPE, line_no, 
				name, q_text, q_type, no_mpn, dt, xs
				//, arr_sz
				,qscript_parser::for_loop_max_counter_stack
				);
			//ostringstream s1, s2;
			//arr_sz->print_expr(s1, s2);
			//cerr << "s1: " << s1.str() << ", s2: " << s2.str() << endl;
		} else {
			q= new range_question(QUESTION_TYPE, line_no, 
				name, q_text, q_type, no_mpn, dt, xs);
		}
		if(stack_cmpd_stmt.size()==0){
			print_err(compiler_internal_error, "compound statement stack is 0 when parsing a question"
					"... exiting",
					line_no, __LINE__, __FILE__  );
			exit(1);
		}
		cmpd_stmt * cmpd_stmt_ptr=stack_cmpd_stmt.back();
		++(cmpd_stmt_ptr->counter_contains_questions);
		(yyval.stmt)=q;
		question_list.push_back(q);
		xs.reset();
		// questions always get pushed in scope level 0 as they
		// are global variables - no matter what the level of nesting
		active_scope_list[0]->insert((yyvsp[(1) - (6)].name), QUESTION_TYPE);
		// I need to modify the insert in scope to
		// take a 3rd parameter which is a question *
		// and store that into the symbol table
		// I should be able to retrieve that 
		// question* pointer later 
	;}
    break;

  case 32:
#line 422 "q.y"
    {
		using qscript_parser::active_scope;
		using qscript_parser::active_scope_list;
		using qscript_parser::stack_cmpd_stmt;
		using qscript_parser::mem_addr;
		using qscript_parser::map_of_active_vars_for_questions;
		using qscript_parser::named_stubs_list;
		using qscript_parser::question_list;
		using qscript_parser::q_type;
		using qscript_parser::no_mpn;
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		string name=(yyvsp[(1) - (6)].name);
		string q_txt=(yyvsp[(2) - (6)].text_buf);
		datatype dt=(yyvsp[(4) - (6)].dt);
		string attribute_list_name=(yyvsp[(5) - (6)].name);

		// This is preparatory work
		// for jumping between questions
		// store
		vector<string> active_push_vars;
		vector<string> active_pop_vars;
		for(unsigned int i=0; i< active_scope_list.size(); ++i){
			scope* sc_ptr= active_scope_list[i];
			sc_ptr->print_scope(active_push_vars, active_pop_vars);
		}
		string q_push_name = name + "_push";
		string q_pop_name = name + "_pop";
		map_of_active_vars_for_questions[q_push_name] = active_push_vars;
		map_of_active_vars_for_questions[q_pop_name] = active_pop_vars;

		bool found=false;
		struct named_range* nr_ptr = 0;
		for(unsigned int i=0; i<named_stubs_list.size(); ++i){
			nr_ptr = named_stubs_list[i];
			if(nr_ptr->name==attribute_list_name){
				found=true; break;
			}
		}
		if(!found){
			print_err(compiler_sem_err, string("named_stubs_list ") 
				+ attribute_list_name + string(" not found \n"), line_no,
				__LINE__, __FILE__);
		}
		
		expr * arr_sz=0;
		named_stub_question* q=0;
		if(qscript_parser::flag_cmpd_stmt_is_a_for_body){
			cout << "flag_cmpd_stmt_is_a_for_body: " 
				<< qscript_parser::flag_cmpd_stmt_is_a_for_body << endl;
			arr_sz = qscript_parser::recurse_for_index(qscript_parser::for_loop_max_counter_stack.size()-1);
			q=new named_stub_question(QUESTION_TYPE, 
				line_no, name, q_txt, 
				q_type, no_mpn, dt, 
				nr_ptr
				//, arr_sz
				,qscript_parser::for_loop_max_counter_stack
				);
		} else {
			q=new named_stub_question(QUESTION_TYPE, 
				line_no, name, q_txt, 
				q_type, no_mpn, dt, 
				nr_ptr);
		}
		question_list.push_back(q);
		(yyval.stmt)=q;
		active_scope_list[0]->insert((yyvsp[(1) - (6)].name), QUESTION_TYPE);
		if(stack_cmpd_stmt.size()==0){
			print_err(compiler_internal_error, "compound statement stack is 0 when parsing a question"
					"... exiting",
					line_no, __LINE__, __FILE__  );
			exit(1);
		}
		cmpd_stmt * cmpd_stmt_ptr=stack_cmpd_stmt.back();
		++(cmpd_stmt_ptr->counter_contains_questions);
	;}
    break;

  case 33:
#line 503 "q.y"
    {
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		using qscript_parser::mem_addr;
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_plus);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 34:
#line 512 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_minus);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 35:
#line 521 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_mult);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 36:
#line 530 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_div);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 37:
#line 539 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_mod);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 38:
#line 548 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr) = new un_expr((yyvsp[(2) - (2)].expr), oper_umin);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 39:
#line 557 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_lt);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 40:
#line 566 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_gt);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 41:
#line 575 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_le);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 42:
#line 584 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_ge);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 43:
#line 593 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_iseq);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 44:
#line 602 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_isneq);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 45:
#line 611 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_or);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 46:
#line 620 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		cout << "LOGAND expr: " << endl;
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_and);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		cout << "after LOGAND expr : " << endl;
	;}
    break;

  case 47:
#line 631 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr) = new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_assgn);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 48:
#line 640 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr) = new un_expr((yyvsp[(2) - (2)].expr), oper_not);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 49:
#line 649 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr) = new un2_expr((yyvsp[(1) - (1)].ival));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 50:
#line 658 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		(yyval.expr) = new un2_expr((yyvsp[(1) - (1)].dval));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 51:
#line 666 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		(yyval.expr) = new un2_expr((yyvsp[(1) - (1)].name), oper_name );
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 52:
#line 674 "q.y"
    {
		using qscript_parser::line_no;
		using qscript_parser::mem_addr;
		(yyval.expr) = new un2_expr(oper_arrderef, /*nametype,  se,*/ (yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].expr));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(1) - (4)].name));
	;}
    break;

  case 53:
#line 683 "q.y"
    {
		using qscript_parser::line_no;
		using qscript_parser::mem_addr;
		(yyval.expr) = new un2_expr(oper_blk_arr_assgn, (yyvsp[(1) - (6)].name),(yyvsp[(3) - (6)].expr),(yyvsp[(5) - (6)].expr));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(1) - (6)].name));
	;}
    break;

  case 54:
#line 692 "q.y"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::named_stubs_list;
		using qscript_parser::func_info_table;
		using qscript_parser::xs;
		using qscript_parser::q_type;
		using qscript_parser::no_mpn;
		using qscript_parser::trav_chain;
		using qscript_parser::skip_func_type_check;
		using qscript_parser::check_parameters;
		using qscript_parser::link_chain;
		using qscript_parser::stub_list;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		//cout << "parsing Function call: name: " << $1 << endl;
		string search_for=(yyvsp[(1) - (4)].name);
		bool found=false;
		int index=search_for_func(search_for);
		if(index!=-1) found=true;
		bool skip_type_check=skip_func_type_check(search_for.c_str());
		if( skip_type_check==false  && found==false ) {
			cerr << "ERROR: function call Error on line_no: " << line_no << endl;
			cerr << "function : " << search_for << " used without decl" << endl;
			++ no_errors;
			(yyval.expr)=new un2_expr(ERROR_TYPE);
			void *ptr=(yyval.expr);
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		} else {
			datatype my_type=func_info_table[index]->return_type;
			expr* e_ptr=trav_chain((yyvsp[(3) - (4)].expr));
			var_list* fparam=func_info_table[index]->param_list;
			bool match=false;
			if(skip_type_check==false){
				match=check_parameters(e_ptr, fparam);
			}
			if(match || skip_type_check){
				//$$=new un2_expr(oper_func_call, my_type, $3, index, line_no);
				//$$=new un2_expr(oper_func_call, my_type, e_ptr, index, line_no);
				(yyval.expr)=new un2_expr(oper_func_call, my_type, e_ptr, index);
				void *ptr=(yyval.expr);
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);
			} else {
				(yyval.expr)=new un2_expr(ERROR_TYPE);
				void *ptr=(yyval.expr);
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);
			}
		}
		free((yyvsp[(1) - (4)].name));
	;}
    break;

  case 55:
#line 744 "q.y"
    {
		using qscript_parser::line_no;
		(yyval.expr) = new un2_expr(strdup((yyvsp[(1) - (1)].text_buf)), oper_text_expr);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 56:
#line 751 "q.y"
    { 
		using qscript_parser::line_no;
		(yyval.expr) = new un_expr((yyvsp[(2) - (3)].expr), oper_parexp );
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 57:
#line 758 "q.y"
    {
		using qscript_parser::xs;
		using qscript_parser::line_no;
		(yyval.expr) = new bin2_expr((yyvsp[(1) - (3)].expr), xs, oper_in);
		xs.reset();
	;}
    break;

  case 58:
#line 776 "q.y"
    { (yyval.expr)=(yyvsp[(1) - (1)].expr); ;}
    break;

  case 59:
#line 777 "q.y"
    {
		(yyval.expr)=qscript_parser::link_chain((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));
	;}
    break;

  case 60:
#line 782 "q.y"
    { qscript_parser::q_type = spn; ;}
    break;

  case 61:
#line 783 "q.y"
    { qscript_parser::q_type = mpn; qscript_parser::no_mpn = (yyvsp[(3) - (4)].ival); ;}
    break;

  case 62:
#line 786 "q.y"
    { ;}
    break;

  case 65:
#line 794 "q.y"
    {
		using qscript_parser::line_no;
		if((yyvsp[(3) - (3)].ival)<=(yyvsp[(1) - (3)].ival)){
			print_err(compiler_sem_err, "2nd number in range <= 1st number",
					line_no, __LINE__, __FILE__  );

		} else {
			qscript_parser::xs.range.push_back( pair<int,int>((yyvsp[(1) - (3)].ival),(yyvsp[(3) - (3)].ival)));
		}
	;}
    break;

  case 66:
#line 804 "q.y"
    {
		qscript_parser::xs.indiv.insert((yyvsp[(1) - (1)].ival));
	;}
    break;

  case 67:
#line 809 "q.y"
    {
		using qscript_parser:: stub_list;
		using qscript_parser:: named_stubs_list;
		stub_list.resize(0);
	;}
    break;

  case 68:
#line 813 "q.y"
    {
		using qscript_parser::line_no;
		using qscript_parser:: stub_list;
		using qscript_parser:: named_stubs_list;
		//cout <<"got attribute_list size: " << attribute_list.size() << endl;
		string stub_name=(yyvsp[(2) - (6)].name);
		struct named_range* nr_ptr= new named_range(NAMED_RANGE, line_no, stub_name,stub_list);
		named_stubs_list.push_back(nr_ptr);
		//$$=0;
		(yyval.stmt) = nr_ptr;
	;}
    break;

  case 69:
#line 827 "q.y"
    {
		using qscript_parser::stub_list;
		string s1=(yyvsp[(1) - (2)].text_buf);
		int code=(yyvsp[(2) - (2)].ival);
		struct stub_pair pair1(s1,code);
		stub_list.push_back(pair1);
	;}
    break;

  case 70:
#line 834 "q.y"
    {
		using qscript_parser::stub_list;
		string s1=(yyvsp[(2) - (3)].text_buf);
		int code=(yyvsp[(3) - (3)].ival);
		struct stub_pair pair1(s1,code);
		stub_list.push_back(pair1);
		//cout << "chaining stublist" << endl;
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 2458 "q.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 846 "q.y"



#include "utils.h"
#include <unistd.h>
#include <string>

namespace qscript_parser {

template<class T> T* link_chain(T* &elem1, T* &elem2){
	if(elem1 && elem2){
		elem2->prev=elem1;
		elem1->next=elem2;
		return elem2;
	}
	else if(elem1){
		return elem1;
	} else {
		return elem2;
	}
}


template<class T> T* trav_chain(T* & elem1){
	if(elem1){
		while (elem1->prev) elem1=elem1->prev;
		return elem1;
	} else return 0;
}

//! The array size of a question inside a for loop
//! is determined by the nesting level of the question inside the
//! for loop and the maximum bound of the loop index - it is a multiplication
//! of all the maximum counters in the enclosing for loops
expr * recurse_for_index(int stack_index){
	//cerr << "entered: recurse_for_index: stack_index: " << stack_index << endl;
	if(stack_index==0){
		bin_expr * test_expr = dynamic_cast<bin_expr*>(for_loop_max_counter_stack[0]);
		if(test_expr==0){
			print_err(compiler_sem_err, 
				" test expr should be a binary expression ",
				qscript_parser::line_no, __LINE__, __FILE__);
			return 0;
		} else if(test_expr->r_op->is_integral_expr() 
				&& test_expr->r_op->is_const()) {
			return test_expr->r_op;
		} else {
			print_err(compiler_sem_err, 
				" test expr not integer and const",
				qscript_parser::line_no, __LINE__, __FILE__);
			return test_expr->r_op;
		}
	} else {
		bin_expr * test_expr = dynamic_cast<bin_expr*>(for_loop_max_counter_stack[stack_index]);
		if(test_expr==0){
			print_err(compiler_sem_err, 
				" test expr should be a binary expression ",
				qscript_parser::line_no, __LINE__, __FILE__);
			return 0;
		} else if(test_expr->r_op->is_integral_expr() 
				&& test_expr->r_op->is_const()) {
			return new bin_expr(test_expr->r_op,
				recurse_for_index(stack_index-1), oper_mult);
		} else {
			print_err(compiler_sem_err, 
				" test expr not integer and const",
				qscript_parser::line_no, __LINE__, __FILE__);
			return test_expr->r_op;
		}
	}
}

}

