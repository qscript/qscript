
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
#line 1 "randomize.y"

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
	
#include "AbstractStatement.h"
//#include "named_range.h"
#include "new_named_range.h"
#include "const_defs.h"

	using std::vector;
	using std::stringstream;
	using std::string;
	using std::endl;
	using std::cout;
	using std::cerr;

        vector <stub_pair> stub_list;
	//vector <named_range*> named_stubs_list;
	int32_t line_no = 1;
	int32_t no_errors = 0;
	void yyerror(const char * s);
	int32_t yylex();
	int stub_group_nest_level = 0;
	//named_range * active_named_range = 0;
	//vector <named_range*> active_named_range_stack;
	AbstractNamedRange * active_named_range;
	vector <AbstractNamedRange*> active_named_range_stack;
	AbstractStatement * root;
	vector <int> stub_number;


/* Line 189 of yacc.c  */
#line 107 "randomize.tab.c"

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
     STUBS_LIST = 258,
     RANDOMIZE = 259,
     MUTEX = 260,
     STUB_GROUP = 261,
     NAME = 262,
     INUMBER = 263,
     TEXT = 264
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 35 "randomize.y"

	//type_qualifier type_qual;
	int32_t ival;
	//double dval;
	char name[MY_STR_MAX];
	char text_buf[MY_STR_MAX];
	//DataType dt;
	struct AbstractStatement * stmt;
	struct AbstractNamedRange * nr_ptr;



/* Line 214 of yacc.c  */
#line 165 "randomize.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 177 "randomize.tab.c"

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   29

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  15
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  18
/* YYNRULES -- Number of states.  */
#define YYNSTATES  33

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   264

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    12,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    10,
       2,    11,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    13,     2,    14,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    15,    16,    23,
      25,    29,    32,    36,    38,    39,    46,    48,    51
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      16,     0,    -1,    17,    -1,    18,    -1,    17,    18,    -1,
      19,    -1,    26,    10,    -1,    -1,     3,     7,    20,    11,
      25,    10,    -1,    22,    -1,    21,    12,    22,    -1,     9,
       8,    -1,     9,     8,     5,    -1,    21,    -1,    -1,     6,
       7,    24,    13,    25,    14,    -1,    23,    -1,    25,    23,
      -1,     4,     3,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    65,    65,    70,    73,    80,    81,    84,    84,   128,
     129,   132,   139,   148,   154,   154,   209,   210,   245
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "STUBS_LIST", "RANDOMIZE", "MUTEX",
  "STUB_GROUP", "NAME", "INUMBER", "TEXT", "';'", "'='", "','", "'{'",
  "'}'", "$accept", "prog", "stmt_list", "stmt", "stubs", "$@1",
  "simple_stub_list", "simple_stub", "stub", "$@2", "stub_list",
  "randomize_stub_statement", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
      59,    61,    44,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    15,    16,    17,    17,    18,    18,    20,    19,    21,
      21,    22,    22,    23,    24,    23,    25,    25,    26
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     2,     0,     6,     1,
       3,     2,     3,     1,     0,     6,     1,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     2,     3,     5,     0,     7,     0,
       1,     4,     6,     0,    18,     0,     0,     0,    13,     9,
      16,     0,    14,    11,     0,     8,    17,     0,    12,    10,
       0,     0,    15
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    13,    18,    19,    20,    27,
      21,     7
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -22
static const yytype_int8 yypact[] =
{
       9,     0,    11,     3,     9,   -22,   -22,     5,   -22,    10,
     -22,   -22,   -22,     7,   -22,     2,    12,     8,    13,   -22,
     -22,    -4,   -22,    15,    14,   -22,   -22,    16,   -22,   -22,
       2,    -5,   -22
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -22,   -22,   -22,    17,   -22,   -22,   -22,    -2,   -21,   -22,
      -6,   -22
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      26,    16,    16,    10,    17,    17,    25,     8,    16,    32,
      26,    17,     1,     2,     9,    12,    23,    14,    15,    22,
      28,    11,    29,    17,    31,    24,     0,     0,     0,    30
};

static const yytype_int8 yycheck[] =
{
      21,     6,     6,     0,     9,     9,    10,     7,     6,    14,
      31,     9,     3,     4,     3,    10,     8,     7,    11,     7,
       5,     4,    24,     9,    30,    12,    -1,    -1,    -1,    13
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    16,    17,    18,    19,    26,     7,     3,
       0,    18,    10,    20,     7,    11,     6,     9,    21,    22,
      23,    25,     7,     8,    12,    10,    23,    24,     5,    22,
      13,    25,    14
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
#line 65 "randomize.y"
    {
	root = (yyvsp[(1) - (1)].stmt);
	;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 70 "randomize.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 73 "randomize.y"
    {
		(yyvsp[(1) - (2)].stmt)->next_=(yyvsp[(2) - (2)].stmt);
		(yyvsp[(2) - (2)].stmt)->prev_=(yyvsp[(1) - (2)].stmt);
		(yyval.stmt)=(yyvsp[(2) - (2)].stmt);
	;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 84 "randomize.y"
    {
		stub_list.resize(0);
		stub_number.push_back(0);
		//active_named_range = new named_range (NAMED_RANGE, line_no, $2);
	;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 88 "randomize.y"
    {
		//string stub_name=$2;
		//struct named_range* nr_ptr= 
		//	new named_range(NAMED_RANGE, 
		//			line_no, stub_name,stub_list);
		//named_stubs_list.push_back(nr_ptr);
		//$$ = nr_ptr;
		//active_named_range->groupPtr_ = $4;
		//active_named_range = new NamedRangeGroup ($2);
		//active_named_range->groupName_ = $2;
		//active_named_range-
		//$$ = $5;
		NamedRangeGroup * nrg = new NamedRangeGroup ((yyvsp[(2) - (6)].name));
		AbstractNamedRange * nr_ptr = (yyvsp[(5) - (6)].nr_ptr);
		cout << "climbing up the chain" << endl;
		while (nr_ptr->prev_nr) {
			cout << "." ;
			nr_ptr = nr_ptr->prev_nr;
		}
		cout << endl;
		nrg->groupPtr_ = nr_ptr;
		(yyval.stmt) = nrg;

		int highest_stub_number_in_group = stub_number.back() ;
		 
		cout << "stub_number.size(): "  << stub_number.size()
			<< endl;
		stub_number.pop_back(); 
		cout << "highest_stub_number_in_group: " 
			<< (yyvsp[(2) - (6)].name) << ": " 
			<< highest_stub_number_in_group
			<< endl;
		if (stub_number.size() != 0) {
			cerr << "Error in parsing assumptions: stub_number.size should be 0 at this point"
				<< endl;
		}
	;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 132 "randomize.y"
    {
		string s1=(yyvsp[(1) - (2)].text_buf);
		int32_t code=(yyvsp[(2) - (2)].ival);
		++stub_number[stub_number.size()-1];
		struct stub_pair pair1 (s1, code, stub_number.back());
		stub_list.push_back (pair1);
	;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 139 "randomize.y"
    {
		string s1=(yyvsp[(1) - (3)].text_buf);
		int32_t code=(yyvsp[(2) - (3)].ival);
		++stub_number[stub_number.size()-1];
		struct stub_pair pair1 (s1, code, true, stub_number.back());
		stub_list.push_back(pair1);
	;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 148 "randomize.y"
    {
		NamedRangeList * nrl = new NamedRangeList();
		nrl->stubs = stub_list;
		stub_list.clear();
		(yyval.nr_ptr) = nrl;
	;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 154 "randomize.y"
    { ++stub_number[stub_number.size()-1]; stub_number.push_back(0); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 154 "randomize.y"
    {
		/* continue from here:
		   treat this as a named compound statement - just like in the main qscript grammar
		   */
		/*
		if (stub_list.size() > 0) {
			active_named_range.set_stubs(stub_list);
			stub_list.resize(0);
			active_named_range.stubs_come_first = true;
		}
		++stub_group_nest_level;
		active_named_range_stack.push_back (active_named_range);
		active_named_range->sub_group_ptr = new named_range (NAMED_RANGE, line_no, $2);
		active_named_range = active_named_range->sub_group_ptr;
		*/
		AbstractNamedRange * nr_ptr = (yyvsp[(5) - (6)].nr_ptr);
		cout << "climbing up the chain" << endl;
		while (nr_ptr->prev_nr) {
			cout << "." ;
			nr_ptr = nr_ptr->prev_nr;
		}
		cout << endl;

		NamedRangeGroup * nrg = new NamedRangeGroup ((yyvsp[(2) - (6)].name));
		nrg->groupPtr_ = nr_ptr;
		(yyval.nr_ptr) = nrg;
		int highest_stub_number_in_group = stub_number.back() ;
		 
		stub_number.pop_back(); 
		cout << "highest_stub_number_in_group: " 
			<< (yyvsp[(2) - (6)].name) << ": " 
			<< highest_stub_number_in_group
			<< endl
	;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 210 "randomize.y"
    {
		AbstractNamedRange * nr_ptr1=(yyvsp[(1) - (2)].nr_ptr), *nr_ptr2=(yyvsp[(2) - (2)].nr_ptr);
		NamedRangeList * nrl_ptr1 =0, *nrl_ptr2=0;
		NamedRangeGroup *nrg_ptr1 =0, *nrg_ptr2=0;
		/*
		if (	nrl_ptr1 = dynamic_cast<NamedRangeList*> (nr_ptr1) && 
			nrl_ptr2 = dynamic_cast<NamedRangeList*> (nr_ptr2) ) {
			nrl_ptr1->next_nr = nrl_ptr2;
			nrl_ptr2->prev_nr = nrl_ptr1;
			cout << "this case should never be - as the grammar would prevent it. all such cases would fold into simple_stub_list"
				<< endl;
		} else if (	nrg_ptr1 = dynamic_cast<NamedRangeGroup*> (nr_ptr1) &&
				nrl_ptr2 = dynamic_cast<NamedRangeList*> (nr_ptr2) ) {
			nrg_ptr1->groupPtr_ = nrl_ptr2;
			$$ = nrg_ptr1;
		} else if (	nrg_ptr1 = dynamic_cast<NamedRangeGroup*> (nr_ptr1) &&
				nrg_ptr2 = dynamic_cast<NamedRangeGroup*> (nr_ptr2) ) {
			nrg_ptr1->groupPtr_ = nrg_ptr2;
			$$ = nrg_ptr2;
		} else if (	nrg_ptr1 = dynamic_cast<NamedRangeGroup*> (nr_ptr1) &&
				nrl_ptr2 = dynamic_cast<NamedRangeList*>  (nr_ptr2) ) {
			nrg_ptr1->next_nr = nrg_ptr2;
			$$ = nrg_ptr2;
		}
		*/

		(yyvsp[(1) - (2)].nr_ptr)->Print();
		(yyvsp[(2) - (2)].nr_ptr)->Print();
		cout << "connecting: " << endl;
		(yyvsp[(1) - (2)].nr_ptr)->next_nr = (yyvsp[(2) - (2)].nr_ptr);
		(yyvsp[(2) - (2)].nr_ptr)->prev_nr = (yyvsp[(1) - (2)].nr_ptr);
		(yyval.nr_ptr) = (yyvsp[(2) - (2)].nr_ptr);
	;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 245 "randomize.y"
    {
		(yyval.stmt) = 0;
	;}
    break;



/* Line 1455 of yacc.c  */
#line 1599 "randomize.tab.c"
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
#line 250 "randomize.y"

#include <cstdio>
#include <vector>

void yyrestart(FILE *input_file);
int32_t yyparse();
void PrintNamedRange (AbstractNamedRange * nr, vector <string> & group_str, vector <string> & group_list, stringstream & final_answer);
bool compare_structure (AbstractNamedRange * nr1, AbstractNamedRange * nr2);
int main()
{
	FILE * yyin = fopen("random_test2.input", "rb");
	if (!yyin){
		cerr << " Unable to open: random_test.input "  << " for read ... exiting" << endl;
		exit(1);
	}
	yyrestart(yyin);
	if (!yyparse() && !no_errors) {
		cout << "sucessfully parsed" << endl;
		AbstractNamedRange * nr_ptr = dynamic_cast <AbstractNamedRange*> (root);
		if (nr_ptr) {
			nr_ptr->Print();
			vector <string> group_str;
			vector <string> group_list;
			stringstream final_answer;

			if (NamedRangeGroup * ng = dynamic_cast <NamedRangeGroup*> (nr_ptr)) {
				//group_list.push_back ("NamedRangeGroup " + ng->groupName_ + ";\n");
				//group_str.push_back (ng->groupName_);
				PrintNamedRange (nr_ptr, group_str, group_list, final_answer);
			}
			cout 	<< "final_answer: " << endl
				<< "========================" << endl
				<< final_answer.str()
				<< "========================" << endl
				<< endl;
		} else {
			cout << "not a AbstractNamedRange" << endl;
		}
		if (nr_ptr) {
			if (NamedRangeGroup * ng = dynamic_cast <NamedRangeGroup*> (nr_ptr)) {
				cout << "SimplePrint =============== " << endl;
				ng->groupPtr_->SimplePrint();
				cout << "END SimplePrint =============== " << endl;
			}
		}
	}
	{
		// test area
		//=======
		NamedRangeGroup grp_1("grp_1");
		grp_1.AddStub( " Kalyanam (Ratia Marg, Snagam Vihar, New Delhi)", 7, 1);
		grp_1.AddStub( " CASP Plan Project (Neem Chowk, Sangam Vihar, New Delhi)", 8, 2);
		grp_1.AddStub( " EFRAH (Aali Vihar, nr. Aali Village, New Delhi)", 9, 3);
		grp_1.AddStub( " Nav Srishti (Village neb Sarai, New Delhi)", 10, 4);
		cout << "grp_1.groupPtr_->SimplePrint =============== " << endl;
		grp_1.groupPtr_->SimplePrint();
		cout << "END SimplePrint =============== " << endl;

		NamedRangeGroup grp_21("grp_21");
		grp_21.AddStub( " Shape India (R/o block 5c, Sarai Kale Khan, DDA flat)", 13, 1);
		grp_21.AddStub( " Jai Jawan Jai Kisan trust (Cenquin) (Centre for community and child development, Jamia Milia Islamia)", 14, 2);

		NamedRangeGroup grp_22("grp_22");
		grp_22.AddStub( " Adarshila (Greater Kailash 2, New Delhi)", 15, 1);
		grp_22.AddStub( " Katha (A/3 Sarvodaya Enclave, New Delhi)", 16, 2);

		NamedRangeGroup grp_2("grp_2");
		cout << "before: grp_2.AddGroup(grp_21);" << endl;
		grp_2.AddGroup(grp_21);
		cout << "before: grp_2.AddGroup(grp_22);" << endl;
		grp_2.AddGroup(grp_22);
		cout << "grp_2.groupPtr_->SimplePrint =============== " << endl;
		grp_2.groupPtr_->SimplePrint();
		cout << "END SimplePrint =============== " << endl;

		NamedRangeGroup suvidha_kendra("suvidha_kendra");
		suvidha_kendra.AddStub( " CASP (JJ Colony, Madanpur Khadar, New Delhi)", 1, 1);
		suvidha_kendra.AddStub( " Prayatn (Basti Vikas Kendra, Jeevan Jyoti Rajiv Camp, D Block, Okhla PII", 2, 2);
		suvidha_kendra.AddStub( " Jal Shankar Memorial Centre (Jasloa Village, New Delhi) Jal", 3, 3);
		suvidha_kendra.AddStub( " Sakaar Outreach (Tanki Road, Meethapur Badarpur, New Delhi)", 4, 4);
		suvidha_kendra.AddStub( " Mamta health Institute for Mother and Child (JJ Camp, Tigri, New Delhi)", 5, 5);
		suvidha_kendra.AddStub( " New opportunities for Women (NOW) (Nr Shalimar Conema, New park)", 6, 6);
		suvidha_kendra.AddGroup(grp_1);
		suvidha_kendra.AddStub( " Navjyoti Development Society (Tekhand village, Okhla phase I, New Del)", 11, 8);
		suvidha_kendra.AddStub( " Sakaar Outreach (Madangir Ambedkar Nagar, New Delhi)", 12, 9);
		suvidha_kendra.AddGroup(grp_2);
		suvidha_kendra.AddStub( " Kalyanam (41/1407 DDA flats, Madangir, New Delhi)", 17, 11);

		cout << "SimplePrint suvidha_kendra.groupPtr_ =============== " << endl;
		suvidha_kendra.groupPtr_->SimplePrint();
		cout << "END SimplePrint =============== " << endl;
		//cout << "SimplePrint =============== " << endl;
		//suvidha_kendra.SimplePrint();
		//cout << "END SimplePrint =============== " << endl;
		AbstractNamedRange * nr_ptr = dynamic_cast <AbstractNamedRange*> (root);
		if (NamedRangeGroup * ng = dynamic_cast <NamedRangeGroup*> (nr_ptr)) {
			bool compare_result = compare_structure (&suvidha_kendra, ng);
			cout << " compare_result: " << compare_result << endl;
		}

		//=======
		vector <string> group_str;
		vector <string> group_list;
		stringstream final_answer;
		//group_str.push_back("suvidha_kendra");
		//group_list.push_back("suvidha_kendra");

		// uncommenting this one and the PrintNamedRange below should both give the same
		// printed output
		//PrintNamedRange (&suvidha_kendra, group_str, group_list, final_answer);
		NamedRangeGroup * ng = dynamic_cast <NamedRangeGroup*> (nr_ptr);
		PrintNamedRange (ng, group_str, group_list, final_answer);
		cout << "final_answer: "
			<< "=======================" << endl
			<< final_answer.str()
			<< "=======================" << endl
			<< "group_str.size(): " << group_str.size() << endl
			<< "group_list.size(): " << group_list.size() << endl
			<< endl;

		cout << "=========== ng->Print(); ============ " << endl;
		ng->Print();
		ng->Vectorize(ng, ng->stub_grp_vec);
		//cout << "ng->stub_grp_vec.size(): " << ng->stub_grp_vec.size() << endl;
		ng->Randomize();
		ng->VectorizePrint(ng);

	}

}

void PrintNamedRange (AbstractNamedRange * nr, vector <string> & group_str, vector <string> & group_list, stringstream & final_answer)
{
	//cout << "Enter: " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
	//cout << "group_str.size(): " << group_str.size() << endl;
	//cout << "group_list.size(): " << group_list.size() << endl;
	bool added_to_stack = false;
	if (nr) {
		if (NamedRangeGroup * ng = dynamic_cast<NamedRangeGroup*> (nr)) {
			string s (ng->groupName_);
			group_list.push_back ( s);

			cout << "Adding group: " << s 
				<< " onto the stack" << endl;
			if (group_str.size() > 0) {
				//cout << "inside if clause" << __LINE__
				//	<< ": group_str.size(): "
				//	<< group_str.size() << endl;
				//cout << "inside if clause" << __LINE__
				//	<< ": group_list.size(): "
				//	<< group_list.size() << endl;
				group_str[group_str.size() - 1] 
					+=  group_list[group_list.size()-2]
						+ ".AddGroup(" 
						+ s
						+ ");\n";
			}
			//s += " : ";
			group_str.push_back("NamedRangeGroup " + s + "(\"" + s + "\")" +";\n");
			//if (ng->groupPtr_)
			//cout << " before call to PrintNamedRange: " << __LINE__ << endl;
			PrintNamedRange (ng->groupPtr_, group_str, group_list, final_answer);
			added_to_stack = true;
		} else if (NamedRangeList * nl = dynamic_cast<NamedRangeList*> (nr)) {
			//group_str[group_str.size() -1 ] += string("|");
			for (int i = 0; i < nl->stubs.size(); ++i) {
				//group_str[group_str.size() - 1] += string("|") + nl->stubs[i].stub_text;
				stringstream s1;
				s1 << group_list[group_list.size()-1]
					<< string(".AddStub( \"") << nl->stubs[i].stub_text
					<< string("\", ")
					<< nl->stubs[i].code
					<< string(", ") << nl->stubs[i].index_in_group 
					<< string(");\n");
				group_str[group_str.size() - 1] 
					+= s1.str();
			}
		}
		//nr = nr->next_nr;
	}
	//if (group_str.size() > 0) 
	if (added_to_stack) {
		final_answer << group_str.back() << endl;
		group_str.pop_back();
		group_list.pop_back();
	}
	//cout << "before next recursive call nr: " << nr << endl;
	if (nr->next_nr) {
			PrintNamedRange (nr->next_nr, group_str, group_list, final_answer);
	}
}

bool compare_structure (AbstractNamedRange * nr1, AbstractNamedRange * nr2)
{
	NamedRangeList * nl1 = dynamic_cast<NamedRangeList*> (nr1);
	NamedRangeGroup * ng1 = dynamic_cast<NamedRangeGroup*> (nr1);
	NamedRangeList * nl2 = dynamic_cast<NamedRangeList*> (nr2);
	NamedRangeGroup * ng2 = dynamic_cast<NamedRangeGroup*> (nr2);

	if (ng1 && ng1->groupName_ == "grp_21") {
		cout << "ng1 == grp_21" << endl;
		cout << "ng1->groupPtr_: "
			<< ng1->groupPtr_ << endl;
		if (dynamic_cast<NamedRangeGroup*> (ng1->groupPtr_)) {
			cout << "ng1->groupPtr_"
				<< " is a NamedRangeGroup"
				<< endl;
		}
		if (dynamic_cast<NamedRangeList*> (ng1->groupPtr_)) {
			cout << "ng1->groupPtr_"
				<< " is a NamedRangeList"
				<< endl;
		}
		cout << "=============" << endl;
	}
	if (ng2 && ng2->groupName_ == "grp_21") {
		cout << "ng2 == grp_21" << endl;
		cout << "ng2->groupPtr_: "
			<< ng2->groupPtr_ << endl;
		if (dynamic_cast<NamedRangeGroup*> (ng2->groupPtr_)) {
			cout << "ng2->groupPtr_"
				<< " is a NamedRangeGroup"
				<< endl;
		}
		if (dynamic_cast<NamedRangeList*> (ng2->groupPtr_)) {
			cout << "ng2->groupPtr_"
				<< " is a NamedRangeList"
				<< endl;
		}
		cout << "-------------" << endl;
	}

	cout << __PRETTY_FUNCTION__ << endl;

	if (nl1 && nl2) {
		cout <<  "both are lists" << endl;
		if (nl1->stubs.size() != nl2->stubs.size()) {
			cout << "nl1 and nl2 are both lists but stub sizes are different" << endl;
			return false;
		} else {
			for (int i=0; i < nl1->stubs.size(); ++i) {
				if (nl1->stubs[i].stub_text != nl2->stubs[i].stub_text) {
					cout << "nl1 and nl2 differ at i= " << i;
					cout << nl1->stubs[i].stub_text << endl
						 << nl2->stubs[i].stub_text << endl;
				}
			}
			if (nl1->next_nr && nl2->next_nr) {
				return compare_structure (nl1->next_nr, nl2->next_nr);
			} else {
				return true;
			}
		}
	} else if (ng1 && ng2) {
		cout <<  "both are named groups: " 
			<< ng1->groupName_ << ", " 
			<< ng2->groupName_ 
			<< endl;
		if (ng1->groupName_ == ng2->groupName_) {
			
			bool result = compare_structure (ng1->groupPtr_, ng2->groupPtr_);
			if (!result) {
				cout << "group names match but structure doesnt: "
					<< ng1->groupName_
					<< endl;
				return false;
			} else if (ng1->next_nr && ng2->next_nr) {
				return compare_structure (ng1->next_nr, ng2->next_nr);
			} else if (ng1->next_nr == 0 && ng2->next_nr == 0) {
				return true;
			} else {
				cout << "one of the groups does not have a next_nr pointer" << endl;
				if (ng1->next_nr) {
					cout << "ng1->next: " << ng1->next_nr << endl;
				} else {
					cout << "ng1->next == 0" << endl;
				}
				if (ng2->next_nr) {
					cout << "ng2->next: " << ng2->next_nr << endl;
				} else {
					cout << "ng2->next == 0" << endl;
				}
				return false;
			}
		} else {
			cout << "ng1 and ng2 have different names"
				<< endl;
			return false;
		}
	} else {
		cout << "the inputs are of different types" 
			<< endl;
		return false;
	}
}

