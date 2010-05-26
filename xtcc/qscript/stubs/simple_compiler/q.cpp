
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 7 "q.ypp"


//#include "common.h"

#include <limits.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

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
	int flag_cmpd_stmt_is_a_func_body=-1;
	vector </*Statement::*/FunctionInformation*> func_info_table;




/* Line 189 of yacc.c  */
#line 111 "q.cpp"

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
     STUBS_LIST = 286,
     SETDEL = 287,
     SETADD = 288,
     UNSET = 289,
     SETALL = 290
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
#define SETDEL 287
#define SETADD 288
#define UNSET 289
#define SETALL 290




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 45 "q.ypp"

	type_qualifier type_qual;
	int ival;
	double dval;
	char name[MY_STR_MAX];
	char text_buf[MY_STR_MAX];
	DataType dt;
	struct AbstractStatement * stmt;
	struct AbstractExpression * expr;
	//class AbstractQuestion* ques;
	struct CompoundStatement * c_stmt;
	struct FunctionParameter * v_list;





/* Line 214 of yacc.c  */
#line 235 "q.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 247 "q.cpp"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   534

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNRULES -- Number of states.  */
#define YYNSTATES  188

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    37,    49,     2,
      20,    21,    35,    34,    24,    33,     2,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    50,
      29,    22,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    18,     2,    19,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,    51,     2,     2,     2,     2,
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
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     8,    16,    18,    22,    25,
      31,    35,    36,    38,    41,    43,    45,    47,    49,    51,
      53,    55,    57,    61,    68,    74,    81,    83,    85,    87,
      89,    91,    93,    95,    97,    98,   109,   113,   115,   121,
     129,   132,   139,   146,   150,   154,   158,   162,   166,   169,
     173,   177,   181,   185,   189,   193,   197,   201,   205,   208,
     210,   212,   214,   219,   226,   231,   233,   237,   241,   243,
     247,   249,   254,   258,   260,   264,   268,   270,   271,   278,
     281,   285,   293,   301,   307
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      54,     0,    -1,    66,    -1,    55,    -1,    -1,    60,     5,
      20,    57,    21,    56,    66,    -1,    58,    -1,    57,    24,
      58,    -1,    60,     5,    -1,    60,     5,    18,     3,    19,
      -1,    60,    49,     5,    -1,    -1,    63,    -1,    59,    63,
      -1,     9,    -1,    10,    -1,    11,    -1,    12,    -1,    13,
      -1,    14,    -1,    15,    -1,    23,    -1,    60,     5,    50,
      -1,    61,    60,     5,    22,    71,    50,    -1,    60,     5,
      22,    71,    50,    -1,    60,     5,    18,    71,    19,    50,
      -1,    70,    -1,    69,    -1,    62,    -1,    77,    -1,    66,
      -1,    68,    -1,    64,    -1,    80,    -1,    -1,    17,    20,
      71,    50,    71,    50,    71,    21,    65,    66,    -1,    67,
      59,    51,    -1,    52,    -1,    42,    20,    71,    21,    63,
      -1,    42,    20,    71,    21,    63,    43,    63,    -1,    71,
      50,    -1,     5,     6,    73,    60,    74,    50,    -1,     5,
       6,    73,    60,     5,    50,    -1,    71,    34,    71,    -1,
      71,    33,    71,    -1,    71,    35,    71,    -1,    71,    36,
      71,    -1,    71,    37,    71,    -1,    33,    71,    -1,    71,
      29,    71,    -1,    71,    30,    71,    -1,    71,    32,    71,
      -1,    71,    31,    71,    -1,    71,    28,    71,    -1,    71,
      27,    71,    -1,    71,    25,    71,    -1,    71,    26,    71,
      -1,    71,    22,    71,    -1,    38,    71,    -1,     3,    -1,
       4,    -1,     5,    -1,     5,    18,    71,    19,    -1,     5,
      18,    71,    24,    71,    19,    -1,     5,    20,    72,    21,
      -1,     6,    -1,    20,    71,    21,    -1,    71,    16,    74,
      -1,    71,    -1,    72,    24,    71,    -1,     7,    -1,     8,
      20,     3,    21,    -1,    20,    75,    21,    -1,    76,    -1,
      75,    24,    76,    -1,     3,    33,     3,    -1,     3,    -1,
      -1,    44,     5,    78,    22,    79,    50,    -1,     6,     3,
      -1,    79,     6,     3,    -1,    45,    20,     5,    24,     5,
      21,    50,    -1,    46,    20,     5,    24,     5,    21,    50,
      -1,    47,    20,     5,    21,    50,    -1,    48,    20,     5,
      21,    50,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   133,   133,   140,   146,   146,   179,   183,   189,   196,
     205,   214,   222,   231,   239,   240,   241,   242,   243,   244,
     245,   248,   253,   258,   260,   265,   276,   277,   278,   279,
     280,   283,   284,   285,   289,   289,   304,   309,   317,   327,
     339,   359,   363,   371,   380,   389,   398,   407,   416,   425,
     434,   443,   452,   461,   470,   479,   488,   499,   508,   517,
     526,   534,   542,   551,   560,   616,   623,   630,   648,   649,
     654,   655,   660,   664,   665,   668,   680,   685,   685,   704,
     711,   722,   726,   730,   733
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
  "FUNC_CALL", "IF", "ELSE", "STUBS_LIST", "SETDEL", "SETADD", "UNSET",
  "SETALL", "'&'", "';'", "'}'", "'{'", "$accept", "prog", "func_defn",
  "$@1", "decl_comma_list", "var_decl", "stmt_list", "datatype",
  "type_qual", "decl_stmt", "stmt", "for_loop_stmt", "$@2", "cmpd_stmt",
  "open_curly", "if_stmt", "expr_stmt", "question", "expression",
  "expr_list", "qtype", "range_allowed_values", "range_list", "range",
  "stubs", "$@3", "stub_list", "stub_manip_stmts", 0
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
     282,   283,   284,   285,   286,   287,   288,   289,   290,    38,
      59,   125,   123
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    54,    56,    55,    57,    57,    58,    58,
      58,    58,    59,    59,    60,    60,    60,    60,    60,    60,
      60,    61,    62,    62,    62,    62,    63,    63,    63,    63,
      63,    63,    63,    63,    65,    64,    66,    67,    68,    68,
      69,    70,    70,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    72,    72,
      73,    73,    74,    75,    75,    76,    76,    78,    77,    79,
      79,    80,    80,    80,    80
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     0,     7,     1,     3,     2,     5,
       3,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     6,     5,     6,     1,     1,     1,     1,
       1,     1,     1,     1,     0,    10,     3,     1,     5,     7,
       2,     6,     6,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     1,     4,     6,     4,     1,     3,     3,     1,     3,
       1,     4,     3,     1,     3,     3,     1,     0,     6,     2,
       3,     7,     7,     5,     5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    14,    15,    16,    17,    18,    19,    20,    37,     0,
       3,     0,     2,     0,     1,     0,    59,    60,    61,    65,
       0,     0,    21,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    28,    12,    32,    30,    31,    27,
      26,     0,    29,    33,    11,     0,     0,     0,     0,    61,
       0,    48,    58,     0,    77,     0,     0,     0,     0,    36,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    40,     0,
       6,     0,    70,     0,     0,     0,    68,     0,     0,    66,
       0,     0,     0,     0,     0,     0,     0,     0,    22,     0,
       0,    67,    57,    55,    56,    54,    53,    49,    50,    52,
      51,    44,    43,    45,    46,    47,     4,    11,     8,     0,
       0,     0,    62,     0,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    76,     0,    73,     0,
       7,     0,    10,     0,     0,     0,     0,    69,     0,    38,
       0,     0,     0,     0,    83,    84,     0,    24,     0,     0,
      72,     0,     5,     0,    71,    42,    41,    63,     0,     0,
      79,     0,    78,     0,     0,    25,    23,    75,    74,     9,
       0,    39,    80,    81,    82,    34,     0,    35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,   139,    79,    80,    31,    32,    33,    34,
      35,    36,   186,    37,    13,    38,    39,    40,    41,    87,
      84,   101,   137,   138,    42,    91,   151,    43
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -30
static const yytype_int16 yypact[] =
{
      26,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,    13,
     -30,    14,   -30,   146,   -30,    -4,   -30,   -30,     2,   -30,
      -2,   167,   -30,   167,   167,     9,    29,    23,    40,    52,
      55,    79,    74,    53,   -30,   -30,   -30,   -30,   -30,   -30,
     -30,   181,   -30,   -30,    53,    16,   167,   167,   167,   -13,
     334,    64,    64,   167,   -30,    76,    81,    82,    90,   -30,
     -30,    -8,    92,    80,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   -30,   -12,
     -30,    10,   -30,    84,    53,   312,   444,    49,   207,   -30,
     356,    85,    77,    86,    87,    93,   167,   167,   -30,    89,
     110,   -30,   444,   466,   488,   497,   497,   100,   100,   100,
     100,    -5,    -5,    64,    64,    64,   -30,    53,   101,   113,
     117,     1,   -30,   167,   -30,   167,   167,   146,   116,   123,
     124,    88,    91,   378,   233,   167,    99,    50,   -30,    94,
     -30,   140,   -30,   126,    95,   103,   400,   444,   259,   111,
     141,    11,   143,   144,   -30,   -30,   112,   -30,   285,   164,
     -30,   110,   -30,   149,   -30,   -30,   -30,   -30,   167,   146,
     -30,   171,   -30,   125,   127,   -30,   -30,   -30,   -30,   -30,
     422,   -30,   -30,   -30,   -30,   -30,    94,   -30
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -30,   -30,   -30,   -30,   -30,    59,   -30,    25,   -30,   -30,
     -29,   -30,   -30,     0,   -30,   -30,   -30,   -30,   -20,   -30,
     -30,    57,   -30,    19,   -30,   -30,   -30,   -30
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      12,    50,    60,    51,    52,    46,   144,    47,    45,   116,
      96,    63,   117,    14,    97,   118,    44,   171,    48,    15,
      46,   100,    47,    82,    83,    11,    85,    86,    88,    53,
      75,    76,    77,    90,    54,     1,     2,     3,     4,     5,
       6,     7,    98,    55,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,    62,   119,
      56,   172,     1,     2,     3,     4,     5,     6,     7,    81,
     124,   160,    57,   125,   161,    58,   133,   134,     8,    61,
      63,    92,    16,    17,    18,    19,    93,    94,     1,     2,
       3,     4,     5,     6,     7,    95,    20,    99,   149,    21,
     100,   129,    22,   146,   120,   147,   148,   128,   131,   121,
     130,   135,    23,   136,   132,   158,    63,    24,   142,   141,
     143,    25,   150,    26,    27,    28,    29,    30,   152,   153,
      59,     8,   159,    73,    74,    75,    76,    77,   154,   162,
     181,   155,    81,   163,   170,   165,     8,   164,   180,    16,
      17,    18,    19,   166,   169,     1,     2,     3,     4,     5,
       6,     7,   175,    20,   173,   174,    21,   177,   179,    22,
      16,    17,    49,    19,   182,   183,   140,   184,   145,    23,
     178,     0,     0,     0,    24,     0,   187,    21,    25,     0,
      26,    27,    28,    29,    30,     0,     0,    63,     8,     0,
      23,     0,     0,    64,     0,    24,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,     0,
       0,     0,     0,    63,     0,     0,     0,     0,     0,    64,
       0,    78,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,     0,     0,     0,     0,    63,
       0,     0,     0,     0,     0,    64,     0,   126,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,     0,     0,     0,     0,    63,     0,     0,     0,     0,
       0,    64,     0,   157,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,     0,     0,     0,
       0,    63,     0,     0,     0,     0,     0,    64,     0,   168,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,     0,     0,     0,     0,     0,    63,     0,
       0,   122,     0,     0,    64,   176,   123,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      63,     0,     0,     0,     0,    89,    64,     0,     0,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    63,     0,     0,     0,     0,   127,    64,     0,
       0,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    63,     0,     0,   156,     0,     0,
      64,     0,     0,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    63,     0,     0,   167,
       0,     0,    64,     0,     0,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    63,     0,
       0,     0,     0,   185,    64,     0,     0,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      63,     0,     0,     0,     0,     0,    64,     0,     0,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    63,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    63,     0,     0,     0,     0,     0,
       0,     0,     0,    63,     0,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    69,    70,    71,    72,
      73,    74,    75,    76,    77
};

static const yytype_int16 yycheck[] =
{
       0,    21,    31,    23,    24,    18,     5,    20,     6,    21,
      18,    16,    24,     0,    22,     5,    20,     6,    20,     5,
      18,    20,    20,     7,     8,     0,    46,    47,    48,    20,
      35,    36,    37,    53,     5,     9,    10,    11,    12,    13,
      14,    15,    50,    20,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    33,    49,
      20,    50,     9,    10,    11,    12,    13,    14,    15,    44,
      21,    21,    20,    24,    24,    20,    96,    97,    52,     5,
      16,     5,     3,     4,     5,     6,     5,     5,     9,    10,
      11,    12,    13,    14,    15,     5,    17,     5,   127,    20,
      20,    24,    23,   123,    20,   125,   126,    22,    21,    84,
      24,    22,    33,     3,    21,   135,    16,    38,     5,    18,
       3,    42,     6,    44,    45,    46,    47,    48,     5,     5,
      51,    52,    33,    33,    34,    35,    36,    37,    50,   139,
     169,    50,   117,     3,     3,    50,    52,    21,   168,     3,
       4,     5,     6,    50,    43,     9,    10,    11,    12,    13,
      14,    15,    50,    17,    21,    21,    20,     3,    19,    23,
       3,     4,     5,     6,     3,    50,   117,    50,   121,    33,
     161,    -1,    -1,    -1,    38,    -1,   186,    20,    42,    -1,
      44,    45,    46,    47,    48,    -1,    -1,    16,    52,    -1,
      33,    -1,    -1,    22,    -1,    38,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,    22,
      -1,    50,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    16,
      -1,    -1,    -1,    -1,    -1,    22,    -1,    50,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,    -1,
      -1,    22,    -1,    50,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    16,    -1,    -1,    -1,    -1,    -1,    22,    -1,    50,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    -1,    16,    -1,
      -1,    19,    -1,    -1,    22,    50,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      16,    -1,    -1,    -1,    -1,    21,    22,    -1,    -1,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    16,    -1,    -1,    -1,    -1,    21,    22,    -1,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    16,    -1,    -1,    19,    -1,    -1,
      22,    -1,    -1,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    16,    -1,    -1,    19,
      -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    16,    -1,
      -1,    -1,    -1,    21,    22,    -1,    -1,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      16,    -1,    -1,    -1,    -1,    -1,    22,    -1,    -1,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    16,    -1,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    29,    30,    31,    32,
      33,    34,    35,    36,    37
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    10,    11,    12,    13,    14,    15,    52,    54,
      55,    60,    66,    67,     0,     5,     3,     4,     5,     6,
      17,    20,    23,    33,    38,    42,    44,    45,    46,    47,
      48,    59,    60,    61,    62,    63,    64,    66,    68,    69,
      70,    71,    77,    80,    20,     6,    18,    20,    20,     5,
      71,    71,    71,    20,     5,    20,    20,    20,    20,    51,
      63,     5,    60,    16,    22,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    50,    57,
      58,    60,     7,     8,    73,    71,    71,    72,    71,    21,
      71,    78,     5,     5,     5,     5,    18,    22,    50,     5,
      20,    74,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    21,    24,     5,    49,
      20,    60,    19,    24,    21,    24,    50,    21,    22,    24,
      24,    21,    21,    71,    71,    22,     3,    75,    76,    56,
      58,    18,     5,     3,     5,    74,    71,    71,    71,    63,
       6,    79,     5,     5,    50,    50,    19,    50,    71,    33,
      21,    24,    66,     3,    21,    50,    50,    19,    50,    43,
       3,     6,    50,    21,    21,    50,    50,     3,    76,    19,
      71,    63,     3,    50,    50,    21,    65,    66
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1455 of yacc.c  */
#line 133 "q.ypp"
    {
	qscript_parser::tree_root=(yyvsp[(1) - (1)].c_stmt);
		while(qscript_parser::tree_root->prev_) {
			cerr << "This should never appear: climbing up the tree" << endl;
			qscript_parser::tree_root=qscript_parser::tree_root->prev_;
		}
	}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 140 "q.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 146 "q.ypp"
    {
		string func_name_index((yyvsp[(2) - (5)].name));
		flag_cmpd_stmt_is_a_func_body=lookup_func(func_name_index);
		if(flag_cmpd_stmt_is_a_func_body==-1){
			ostringstream err_mesg;
			err_mesg << "Function name : " << func_name_index <<  "not found in list of declared functions: "
				<< "You will see another error on this same function name: " << func_name_index;
			print_err(compiler_sem_err
					, err_mesg.str().c_str(),
					qscript_parser::line_no, __LINE__, __FILE__  );
		}
	}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 157 "q.ypp"
    {
		struct /* Statement:: */ CompoundStatement* c_stmt= (yyvsp[(7) - (7)].c_stmt);
		if(c_stmt==0){
			cerr << "INTERNAL COMPILER ERROR: c_stmt==0" << endl;
		} else {
			//cout << "funcBody_: is valid " << endl;
		}
		struct Scope *scope_=c_stmt->scope_;
		struct /*Statement::*/ FunctionParameter * v_list=qscript_parser::trav_chain((yyvsp[(4) - (7)].v_list));
		struct /*Statement::*/ AbstractStatement* funcBody_=(yyvsp[(7) - (7)].c_stmt);
		string search_for=(yyvsp[(2) - (7)].name);
		DataType returnType_=(yyvsp[(1) - (7)].dt);
		(yyval.stmt)=new /*Statement::*/ FunctionStatement(FUNC_DEFN, qscript_parser::line_no, scope_, v_list, funcBody_, search_for, returnType_);
		// Note that the declaration already has a parameter list
		// the constructor uses the parameter list - name and type to verify everything
		// but doesnt need the parameter list any more - so we should delete it 
		// - took me a while to figure out this memory leak
		delete v_list;
		free((yyvsp[(2) - (7)].name));
	}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 179 "q.ypp"
    {
		 (yyval.v_list)=(yyvsp[(1) - (1)].v_list);
		 //cout << "got decl_comma_list : " << endl;
	}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 183 "q.ypp"
    {
		(yyval.v_list)=qscript_parser::link_chain((yyvsp[(1) - (3)].v_list),(yyvsp[(3) - (3)].v_list));
		//cout << "chaining var_decl : " << endl;
	}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 189 "q.ypp"
    {
		(yyval.v_list)=new FunctionParameter((yyvsp[(1) - (2)].dt), (yyvsp[(2) - (2)].name));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, qscript_parser::line_no);
		}
		free((yyvsp[(2) - (2)].name));
	}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 196 "q.ypp"
    {
		/* Neil - I need to fix this */
		DataType dt=DataType(INT8_ARR_TYPE+((yyvsp[(1) - (5)].dt)-INT8_TYPE));
		(yyval.v_list)=new FunctionParameter(dt, (yyvsp[(2) - (5)].name), (yyvsp[(4) - (5)].ival));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, qscript_parser::line_no);
		}
		free((yyvsp[(2) - (5)].name));
	}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 205 "q.ypp"
    {
		DataType dt=DataType(INT8_REF_TYPE+((yyvsp[(1) - (3)].dt)-INT8_TYPE));
		(yyval.v_list)=new FunctionParameter(dt, (yyvsp[(3) - (3)].name));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, qscript_parser::line_no);
		}
		free((yyvsp[(3) - (3)].name));
	}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 214 "q.ypp"
    {
		(yyval.v_list)=0;
		}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 222 "q.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
		if(qscript_parser::flag_next_stmt_start_of_block){
			qscript_parser::blk_heads.push_back((yyvsp[(1) - (1)].stmt));
			qscript_parser::flag_next_stmt_start_of_block=false;
			qscript_parser::blk_start_flag.pop_back();
		}

	}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 231 "q.ypp"
    {
		(yyvsp[(1) - (2)].stmt)->next_=(yyvsp[(2) - (2)].stmt);
		(yyvsp[(2) - (2)].stmt)->prev_=(yyvsp[(1) - (2)].stmt);
		(yyval.stmt)=(yyvsp[(2) - (2)].stmt);
	}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 248 "q.ypp"
    {
		   (yyval.type_qual) = CONST_QUAL;
	}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 253 "q.ypp"
    {
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (3)].name), (yyvsp[(1) - (3)].dt)/*, line_no*/);
		//free($2);
		cerr <<  "-- why am i not freeing this?: FILE: " << __FILE__ << ", line:" << __LINE__ << endl;
	}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 258 "q.ypp"
    {
	}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 260 "q.ypp"
    {
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (5)].name), (yyvsp[(1) - (5)].dt), (yyvsp[(4) - (5)].expr));
		//free($2);
		cerr <<  "-- why am i not freeing this?: FILE: " << __FILE__ << ", line:" << __LINE__ << endl;
	}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 265 "q.ypp"
    {
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		DataType dt=DataType(INT8_ARR_TYPE+((yyvsp[(1) - (6)].dt)-INT8_TYPE));
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (6)].name), dt, (yyvsp[(4) - (6)].expr)/*, line_no*/);
		free((yyvsp[(2) - (6)].name));
	}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 280 "q.ypp"
    {
		(yyval.stmt) = (yyvsp[(1) - (1)].c_stmt);
	}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 289 "q.ypp"
    {
		++qscript_parser::flagIsAForBody_;
		qscript_parser::for_loop_max_counter_stack.push_back((yyvsp[(5) - (8)].expr));
	}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 292 "q.ypp"
    {
		using qscript_parser::line_no;
		(yyval.stmt) = new ForStatement(FOR_STMT, line_no, (yyvsp[(3) - (10)].expr), (yyvsp[(5) - (10)].expr), (yyvsp[(7) - (10)].expr), (yyvsp[(10) - (10)].c_stmt));

		--qscript_parser::flagIsAForBody_;
		qscript_parser::for_loop_max_counter_stack.pop_back();
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 304 "q.ypp"
    {
		(yyval.c_stmt) = qscript_parser::ProcessCompoundStatement((yyvsp[(1) - (3)].c_stmt), (yyvsp[(2) - (3)].stmt));
	}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 309 "q.ypp"
    {
		CompoundStatement * cmpdStmt = qscript_parser::ProcessOpenCurly();
		(yyval.c_stmt)=cmpdStmt;
	}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 317 "q.ypp"
    {
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		using qscript_parser::XTCC_DEBUG_MEM_USAGE;
		(yyval.stmt)=new IfStatement(IFE_STMT,if_line_no,(yyvsp[(3) - (5)].expr),(yyvsp[(5) - (5)].stmt),0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 327 "q.ypp"
    {
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.stmt)=new IfStatement(IFE_STMT,qscript_parser::if_line_no,(yyvsp[(3) - (7)].expr),(yyvsp[(5) - (7)].stmt),(yyvsp[(7) - (7)].stmt));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 340 "q.ypp"
    {
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		if((yyvsp[(1) - (2)].expr)->IsValid()){
			(yyval.stmt) = new ExpressionStatement(TEXPR_STMT, line_no, (yyvsp[(1) - (2)].expr));
			if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
				mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
			}
		} else {
			(yyval.stmt) = new ExpressionStatement(ERROR_TYPE, line_no, (yyvsp[(1) - (2)].expr));
			if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
				mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
			}
		}
	}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 359 "q.ypp"
    {
		(yyval.stmt) = qscript_parser::ProcessRangeQuestion((yyvsp[(1) - (6)].name), (yyvsp[(2) - (6)].text_buf), (yyvsp[(4) - (6)].dt));
		cout << "parsed range question : " << (yyvsp[(1) - (6)].name) << endl;
	}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 363 "q.ypp"
    {
		(yyval.stmt) = qscript_parser::ProcessNamedQuestion((yyvsp[(1) - (6)].name), (yyvsp[(2) - (6)].text_buf), (yyvsp[(4) - (6)].dt), (yyvsp[(5) - (6)].name));
		cout << "parsed named question : " << (yyvsp[(1) - (6)].name) << endl;
	}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 371 "q.ypp"
    {
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		using qscript_parser::mem_addr;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_plus);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 380 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_minus);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 389 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_mult);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 398 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_div);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 407 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_mod);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 416 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr) = new UnaryExpression((yyvsp[(2) - (2)].expr), oper_umin);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 425 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_lt);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 434 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_gt);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 443 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_le);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 452 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_ge);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 461 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_iseq);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 470 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_isneq);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 479 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_or);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 488 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		cout << "LOGAND expr: " << endl;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_and);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		cout << "after LOGAND expr : " << endl;
	}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 499 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr) = new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_assgn);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 508 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr) = new UnaryExpression((yyvsp[(2) - (2)].expr), oper_not);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 517 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr) = new Unary2Expression((yyvsp[(1) - (1)].ival));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 526 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		(yyval.expr) = new Unary2Expression((yyvsp[(1) - (1)].dval));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 534 "q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		(yyval.expr) = new Unary2Expression((yyvsp[(1) - (1)].name), oper_name );
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 542 "q.ypp"
    {
		using qscript_parser::line_no;
		using qscript_parser::mem_addr;
		(yyval.expr) = new Unary2Expression(oper_arrderef, /*nametype,  se,*/ (yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].expr));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(1) - (4)].name));
	}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 551 "q.ypp"
    {
		using qscript_parser::line_no;
		using qscript_parser::mem_addr;
		(yyval.expr) = new Unary2Expression(oper_blk_arr_assgn, (yyvsp[(1) - (6)].name),(yyvsp[(3) - (6)].expr),(yyvsp[(5) - (6)].expr));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(1) - (6)].name));
	}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 560 "q.ypp"
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
			cerr << "ERROR: function call Error on line_no: " 
				<< line_no << endl;
			cerr << "function : " << search_for 
				<< " used without decl" << endl;
			++ no_errors;
			(yyval.expr)=new Unary2Expression(ERROR_TYPE);
			void *ptr=(yyval.expr);
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		} else {
			DataType my_type=func_info_table[index]->returnType_;
			AbstractExpression* e_ptr=trav_chain((yyvsp[(3) - (4)].expr));
			FunctionParameter* fparam=
				func_info_table[index]->parameterList_;
			bool match=false;
			if(skip_type_check==false){
				match=check_parameters(e_ptr, fparam);
			}
			if(match || skip_type_check){
				//$$=new Unary2Expression(oper_func_call, my_type, $3, index, line_no);
				//$$=new Unary2Expression(oper_func_call, my_type, e_ptr, index, line_no);
				(yyval.expr)=new Unary2Expression(oper_func_call, my_type, e_ptr, index);
				void *ptr=(yyval.expr);
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);
			} else {
				(yyval.expr)=new Unary2Expression(ERROR_TYPE);
				void *ptr=(yyval.expr);
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);
			}
		}
		cerr << "NxD: need to fix this below - $1 seems to be used somewhere and freeing it kills the program FILE: " << __FILE__ << ", line:" << __LINE__ << endl;
		//free($1);
	}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 616 "q.ypp"
    {
		using qscript_parser::line_no;
		(yyval.expr) = new Unary2Expression(strdup((yyvsp[(1) - (1)].text_buf)), oper_text_expr);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 623 "q.ypp"
    { 
		using qscript_parser::line_no;
		(yyval.expr) = new UnaryExpression((yyvsp[(2) - (3)].expr), oper_parexp );
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 630 "q.ypp"
    {
		using qscript_parser::xs;
		using qscript_parser::line_no;
		(yyval.expr) = new Binary2Expression((yyvsp[(1) - (3)].expr), xs, oper_in);
		xs.reset();
	}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 648 "q.ypp"
    { (yyval.expr)=(yyvsp[(1) - (1)].expr); }
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 649 "q.ypp"
    {
		(yyval.expr)=qscript_parser::link_chain((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));
	}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 654 "q.ypp"
    { qscript_parser::q_type = spn; }
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 655 "q.ypp"
    { qscript_parser::q_type = mpn; 
		qscript_parser::no_mpn = (yyvsp[(3) - (4)].ival); 
	}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 660 "q.ypp"
    { }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 668 "q.ypp"
    {
		using qscript_parser::line_no;
		if((yyvsp[(3) - (3)].ival)<=(yyvsp[(1) - (3)].ival)){
			print_err(compiler_sem_err
					, "2nd number in range <= 1st number",
					line_no, __LINE__, __FILE__  );

		} else {
			qscript_parser::
				xs.range.push_back( pair<int,int>((yyvsp[(1) - (3)].ival),(yyvsp[(3) - (3)].ival)));
		}
	}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 680 "q.ypp"
    {
		qscript_parser::xs.indiv.insert((yyvsp[(1) - (1)].ival));
	}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 685 "q.ypp"
    {
		using qscript_parser:: stub_list;
		using qscript_parser:: named_stubs_list;
		stub_list.resize(0);
	}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 689 "q.ypp"
    {
		using qscript_parser::line_no;
		using qscript_parser:: stub_list;
		using qscript_parser:: named_stubs_list;
		//cout <<"got attribute_list size: " << attribute_list.size() << endl;
		string stub_name=(yyvsp[(2) - (6)].name);
		struct named_range* nr_ptr= new named_range(NAMED_RANGE
				, line_no, stub_name,stub_list);
		named_stubs_list.push_back(nr_ptr);
		//$$=0;
		(yyval.stmt) = nr_ptr;
	}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 704 "q.ypp"
    {
		using qscript_parser::stub_list;
		string s1=(yyvsp[(1) - (2)].text_buf);
		int code=(yyvsp[(2) - (2)].ival);
		struct stub_pair pair1(s1,code);
		stub_list.push_back(pair1);
	}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 711 "q.ypp"
    {
		using qscript_parser::stub_list;
		string s1=(yyvsp[(2) - (3)].text_buf);
		int code=(yyvsp[(3) - (3)].ival);
		struct stub_pair pair1(s1,code);
		stub_list.push_back(pair1);
		//cout << "chaining stublist" << endl;
	}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 722 "q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_DEL
				, (yyvsp[(3) - (7)].name), (yyvsp[(5) - (7)].name));
	}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 726 "q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (7)].name), (yyvsp[(5) - (7)].name));
	}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 730 "q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt_set_unset( STUB_MANIP_UNSET_ALL, (yyvsp[(3) - (5)].name));
	}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 733 "q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt_set_unset( STUB_MANIP_SET_ALL, (yyvsp[(3) - (5)].name));
	}
    break;



/* Line 1455 of yacc.c  */
#line 2586 "q.cpp"
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
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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



/* Line 1675 of yacc.c  */
#line 741 "q.ypp"



#include "utils.h"
#include <unistd.h>
#include <string>

namespace qscript_parser {

template<class T> T* link_chain(T* &elem1, T* &elem2){
	if(elem1 && elem2){
		elem2->prev_=elem1;
		elem1->next_=elem2;
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
		while (elem1->prev_) elem1=elem1->prev_;
		return elem1;
	} else return 0;
}

//! The array size of a question inside a for loop
//! is determined by the nesting level of the question inside the
//! for loop and the maximum bound of the loop index - it is a multiplication
//! of all the maximum counters in the enclosing for loops
AbstractExpression * recurse_for_index(int stack_index){
	//cerr << "entered: recurse_for_index: stack_index: " << stack_index << endl;
	if(stack_index==0){
		BinaryExpression * test_expr = 
			dynamic_cast<BinaryExpression*>(
					for_loop_max_counter_stack[0]);
		if(test_expr==0){
			print_err(compiler_sem_err, 
				" test expr should be a binary expression ",
				qscript_parser::line_no, __LINE__, __FILE__);
			return 0;
		} else if(test_expr->rightOperand_->IsIntegralExpression() 
				&& test_expr->rightOperand_->IsConst()) {
			return test_expr->rightOperand_;
		} else {
			print_err(compiler_sem_err, 
				" test expr not integer and const",
				qscript_parser::line_no, __LINE__, __FILE__);
			return test_expr->rightOperand_;
		}
	} else {
		BinaryExpression * test_expr = 
			dynamic_cast<BinaryExpression*>(
				for_loop_max_counter_stack[stack_index]);
		if(test_expr==0){
			print_err(compiler_sem_err, 
				" test expr should be a binary expression ",
				qscript_parser::line_no, __LINE__, __FILE__);
			return 0;
		} else if(test_expr->rightOperand_->IsIntegralExpression() 
				&& test_expr->rightOperand_->IsConst()) {
			return new BinaryExpression(test_expr->rightOperand_,
				recurse_for_index(stack_index-1), oper_mult);
		} else {
			print_err(compiler_sem_err, 
				" test expr not integer and const",
				qscript_parser::line_no, __LINE__, __FILE__);
			return test_expr->rightOperand_;
		}
	}
}

CompoundStatement* ProcessOpenCurly()
{
	++nest_lev;
	CompoundStatement * cmpdStmt= new CompoundStatement(CMPD_STMT, 
			line_no, flagIsAFunctionBody_,
			flagIsAForBody_);
	stack_cmpd_stmt.push_back(cmpdStmt);
	void *ptr=cmpdStmt;
	mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
	mem_addr.push_back(m1);
	if(flagIsAFunctionBody_>=0){
		cmpdStmt->scope_=func_info_table[
			qscript_parser::flagIsAFunctionBody_]->functionScope_;
		// reset the flag
		qscript_parser::flagIsAFunctionBody_=-1;
	} else {
		cmpdStmt->scope_= new Scope();
	}
	flag_next_stmt_start_of_block=true;
	blk_start_flag.push_back(flag_next_stmt_start_of_block);
	active_scope_list.push_back(cmpdStmt->scope_);
	active_scope = cmpdStmt->scope_;
	return cmpdStmt;
}

CompoundStatement* ProcessCompoundStatement(CompoundStatement* cmpdStmt,
		AbstractStatement *stmt)
{

	active_scope_list.pop_back();
	int tmp=active_scope_list.size()-1;
	if(tmp==-1) { 
		active_scope = 0;
		print_err(compiler_internal_error
			, "Error: active_scope == 0 in ProcessCompoundStatement"
			": should never happen :... exiting",
				line_no, __LINE__, __FILE__  );
		exit(1);
	} else { 
		active_scope = active_scope_list[tmp]; 
	}
	struct AbstractStatement* head_of_this_chain=blk_heads.back();
	if(blk_start_flag.size() > 0){
		flag_next_stmt_start_of_block = blk_start_flag[blk_start_flag.size()-1];
	}
	if(  head_of_this_chain==0){
		//cerr << "Error in compiler : compoundBody_:  " << __FILE__ << __LINE__ << endl;
		//++no_errors;
		print_err(compiler_internal_error
			, "Error: head_of_this_chain == 0 in "
			"ProcessCompoundStatement : should never happen :"
			"... exiting"
			, line_no, __LINE__, __FILE__  );
		exit(1);
	} else {
		cmpdStmt->compoundBody_ = head_of_this_chain;
		blk_heads.pop_back();
	}

	//! update the counter of enlosing CompoundStatement with 
	//! the number of questions in this CompoundStatement being popped of
	//! right now
	if(stack_cmpd_stmt.size()>1){
		CompoundStatement * popped_off_cmpd_stmt_ptr=stack_cmpd_stmt.back();
		stack_cmpd_stmt.pop_back();
		CompoundStatement * current  = stack_cmpd_stmt.back();
		current->counterContainsQuestions_+= 
			(popped_off_cmpd_stmt_ptr->counterContainsQuestions_);
	} 
	//$$=$1;
	return cmpdStmt;
}

AbstractStatement * ProcessRangeQuestion(const string &name
		, const string & q_text, const DataType& dt )
{

	vector<string> active_push_vars;
	vector<string> active_pop_vars;
	for(unsigned int i=0; i< active_scope_list.size(); ++i){
		Scope* sc_ptr= active_scope_list[i];
		sc_ptr->print_scope(name, active_push_vars, active_pop_vars);
	}
	string q_push_name = name + "_push";
	string q_pop_name = name + "_pop";
	map_of_active_vars_for_questions[q_push_name] = active_push_vars;
	map_of_active_vars_for_questions[q_pop_name] = active_pop_vars;
	
	AbstractExpression * arr_sz=0;
	RangeQuestion * q=0;
	if(qscript_parser::flagIsAForBody_){
		cout << "flagIsAForBody_: " 
			<< qscript_parser::flagIsAForBody_ << endl;
		arr_sz = qscript_parser::recurse_for_index(
			qscript_parser::for_loop_max_counter_stack.size()-1);
		q= new RangeQuestion(QUESTION_TYPE, line_no, 
			name, q_text, q_type, no_mpn, dt, xs
			//, arr_sz
			,qscript_parser::for_loop_max_counter_stack
			);
		//ostringstream s1, s2;
		//arr_sz->print_expr(s1, s2);
		//cerr << "s1: " << s1.str() << ", s2: " << s2.str() << endl;
	} else {
		q= new RangeQuestion(QUESTION_TYPE, line_no, 
			name, q_text, q_type, no_mpn, dt, xs);
	}
	if(stack_cmpd_stmt.size()==0){
		print_err(compiler_internal_error
			, "compound statement stack is 0 when parsing"
			"a question... exiting",
				line_no, __LINE__, __FILE__  );
		exit(1);
	}
	CompoundStatement * cmpd_stmt_ptr=stack_cmpd_stmt.back();
	++(cmpd_stmt_ptr->counterContainsQuestions_);
	//$$=q;

	question_list.push_back(q);
	cout << "question_list: questions are " << endl;
	for(int i=0; i<question_list.size(); ++i){
		cout << question_list[i]->questionName_ << endl;
	}
	xs.reset();
	// questions always get pushed in Scope level 0 as they
	// are global variables - no matter what the level of nesting
	active_scope_list[0]->insert(name.c_str(), QUESTION_TYPE);
	// I need to modify the insert in Scope to
	// take a 3rd parameter which is a AbstractQuestion *
	// and store that into the symbol table
	// I should be able to retrieve that 
	// AbstractQuestion* pointer later 
	return q;
}

AbstractStatement * ProcessNamedQuestion(const string &name
			, const string & q_txt , const DataType& dt 
			, const string & attribute_list_name )
{

	// This is preparatory work
	// for jumping between questions
	// store
	vector<string> active_push_vars;
	vector<string> active_pop_vars;
	for(unsigned int i=0; i< active_scope_list.size(); ++i){
		Scope* sc_ptr= active_scope_list[i];
		sc_ptr->print_scope(name, active_push_vars, active_pop_vars);
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
	
	AbstractExpression * arr_sz=0;
	NamedStubQuestion* q=0;
	if(qscript_parser::flagIsAForBody_){
		cout << "flagIsAForBody_: " 
			<< qscript_parser::flagIsAForBody_ << endl;
		arr_sz = qscript_parser::recurse_for_index(
			qscript_parser::for_loop_max_counter_stack.size()-1);
		q=new NamedStubQuestion(QUESTION_TYPE, line_no
				, name, q_txt, q_type, no_mpn, dt , nr_ptr
				,qscript_parser::for_loop_max_counter_stack);
	} else {
		q=new NamedStubQuestion(QUESTION_TYPE, 
			line_no, name, q_txt, q_type, no_mpn, dt, nr_ptr);
	}
	question_list.push_back(q);
	//$$=q;
	active_scope_list[0]->insert(name.c_str(), QUESTION_TYPE);
	if(stack_cmpd_stmt.size()==0){
		print_err(compiler_internal_error, "compound statement stack "
			"is 0 when parsing a AbstractQuestion... exiting"
			, line_no, __LINE__, __FILE__  );
		exit(1);
	}
	CompoundStatement * cmpd_stmt_ptr=stack_cmpd_stmt.back();
	++(cmpd_stmt_ptr->counterContainsQuestions_);
	return q;
}

// Close namespace
}

