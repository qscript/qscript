/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.5"

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

/* Line 268 of yacc.c  */
#line 4 "gram.y"



#include <inttypes.h>
#include <sys/types.h>
#include <limits.h>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include<boost/tokenizer.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <limits.h>
#include <regex.h>



#include "const_defs.h"
#include "person_info.h"

	extern int yylex();
	extern void yyerror(const char * s);
	using std::cout;
	using std::endl;
	using std::cerr;
	using std::stringstream;
	using std::map;
	using std::string;
	using std::vector;
	using std::set;
	set <string> negative_words_of_interest;
	vector <regex_t> regular_expressions_of_interest;

	std::string trim(const std::string& str,
			 const std::string& whitespace = " \t");

	vector <struct Info> info_vec;
	map <string, int> rm_name_code_map;
	map <string, int> recalled_name_freq;
	//int match_score(const string & s1, const string & s2,
	//	const  set <string> & negative_words_of_interest,
	//	string & addnl_info,
	//	string & verdict, int serial_no
	//	);


	struct Info 
	{
		int serial_no;
		int rm_code;
		string rm_name;
		string cust_ref_no;
		string call_status;
		string survey_agreement;
		string remember_name;
		string recalled_name;
		Info (
			int    p_serial_no,
			int    p_rm_code,
			string p_rm_name,
			string p_cust_ref_no,
			string p_call_status,
			string p_survey_agreement,
			string p_remember_name,
			string p_recalled_name
		):

			serial_no        (p_serial_no)         ,
			rm_code          (p_rm_code   )        ,
			rm_name          (p_rm_name    )       ,
			cust_ref_no      (p_cust_ref_no )      ,
			call_status      (p_call_status  )     ,
			survey_agreement (p_survey_agreement)  ,
			remember_name    (p_remember_name   )  ,
			recalled_name    (p_recalled_name   )
			{}
	};





/* Line 268 of yacc.c  */
#line 162 "gram.c"

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
     TEXT = 259,
     NEWL = 260,
     COMMA = 261,
     DOT = 262
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 94 "gram.y"

	int ival;
	double dval;
	char name[4095];
	char text_buf[4095];



/* Line 293 of yacc.c  */
#line 214 "gram.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 226 "gram.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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

# define YYCOPY_NEEDED 1

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

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   19

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  8
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  3
/* YYNRULES -- Number of rules.  */
#define YYNRULES  4
/* YYNRULES -- Number of states.  */
#define YYNSTATES  21

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   262

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       5,     6,     7
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
       9,     0,    -1,    10,    -1,     9,    10,    -1,     3,     6,
       3,     6,     4,     6,     4,     6,     4,     6,     4,     6,
       4,     6,     4,     5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   109,   109,   110,   115
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INUMBER", "TEXT", "NEWL", "COMMA",
  "DOT", "$accept", "chain", "a_row", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,     8,     9,     9,    10
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,    16
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,     1,     3,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       4
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -5
static const yytype_int8 yypact[] =
{
      -2,    -4,     0,    -5,     1,    -5,    -5,    -1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -5
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
      -5,    -5,    17
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
       5,     1,     4,     1,     7,     8,     9,     0,    11,    10,
      13,    12,    15,    14,    17,    16,    19,    18,    20,     6
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-5))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       0,     3,     6,     3,     3,     6,     4,    -1,     4,     6,
       4,     6,     4,     6,     4,     6,     4,     6,     5,     2
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     9,    10,     6,     0,    10,     3,     6,     4,
       6,     4,     6,     4,     6,     4,     6,     4,     6,     4,
       5
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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
  if (yypact_value_is_default (yyn))
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
      if (yytable_value_is_error (yyn))
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
        case 3:

/* Line 1806 of yacc.c  */
#line 110 "gram.y"
    {
		//cout << "chained a row" << endl;
	}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 119 "gram.y"
    {
		//cout << "got a row" << endl;
		//struct Info inf;
		int serial_no = (yyvsp[(1) - (16)].ival);
		int rm_code = (yyvsp[(3) - (16)].ival);
		string rm_name = boost::to_upper_copy(trim(string((yyvsp[(5) - (16)].text_buf))));
		string cust_ref_no = (yyvsp[(7) - (16)].text_buf);
		string call_status = (yyvsp[(9) - (16)].text_buf);
		string survey_agreement = (yyvsp[(11) - (16)].text_buf);
		string remember_name = (yyvsp[(13) - (16)].text_buf);
		string recalled_name = boost::to_upper_copy(trim(string((yyvsp[(15) - (16)].text_buf))));
		struct Info inf (serial_no, rm_code, rm_name, 
			cust_ref_no, call_status, survey_agreement, 
			remember_name, recalled_name);
		info_vec.push_back (inf);
		rm_name_code_map[(yyvsp[(5) - (16)].text_buf)]=(yyvsp[(3) - (16)].ival);
		//if (recalled_name == rm_name) 
		#if 0
		if (recalled_name.length() > 0) {
			string addnl_info;
			string verdict;
			if (int score = match_score (recalled_name, rm_name, 
					negative_words_of_interest, addnl_info,
					verdict) ) {
				cout << verdict << ","
					//<< "ser_no, "
					<< serial_no << ", " 
					//<< ", rm_name, " 
					<< rm_name << ", "
					//<< ", recalled_name, "
					<< "\"" << recalled_name << "\"" << ","
					//<< ", score, " 
					<< score << ","
					<< addnl_info
					<< endl;
			} else {
				cout << "not matched," 
					//<< "  ser_no, "
					<< serial_no  << ", "
					//<< ", rm_name, " 
					<< rm_name <<", "
					//<< ", recalled_name, " 
					<< "\"" << recalled_name << "\"" << ","
					//<< ", score, " 
					<< 0 << ","
					<< addnl_info
					<< endl;
			}
		} else {
			cout << "impossible, "
				<< serial_no  << ", "
				<< rm_name <<", "
				<< "\"" << recalled_name << "\"" << ","
				<< 0 << ","
				<< "recalled_name is of length 0"
				<< endl;
		}
		#endif /* 0 */

	}
    break;



/* Line 1806 of yacc.c  */
#line 1521 "gram.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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
      if (!yypact_value_is_default (yyn))
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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



/* Line 2067 of yacc.c  */
#line 182 "gram.y"


	extern void yyrestart(FILE *input_file);
	extern int32_t yyparse();
	int DebugFreqLexer ;


#include<iostream>
#include<boost/tokenizer.hpp>
#include<string>
#include<vector>

/*
struct Info 
{
	int serial_no;
	int rm_code;
	string rm_name;
	string cust_ref_no;
	string call_status;
	string survey_agreement;
	string remember_name;
	string recalled_name;
	Info (
		int    p_serial_no,
		int    p_rm_code,
		string p_rm_name,
		string p_cust_ref_no,
		string p_call_status,
		string p_survey_agreement,
		string p_remember_name,
		string p_recalled_name
	):

		serial_no        (p_serial_no)         ,
		rm_code          (p_rm_code   )        ,
		rm_name          (p_rm_name    )       ,
		cust_ref_no      (p_cust_ref_no )      ,
		call_status      (p_call_status  )     ,
		survey_agreement (p_survey_agreement)  ,
		remember_name    (p_remember_name   )  ,
		recalled_name    (p_recalled_name   )
};
*/

//vector <struct Info> info_vec;
//map <string, int> rm_names;
//map <string, int> recalled_name_freq;
using boost::multi_index_container;
using namespace boost::multi_index;

typedef multi_index_container<
  PersonInfo,
  indexed_by<
    ordered_non_unique<
      tag<first_name>,  BOOST_MULTI_INDEX_MEMBER(PersonInfo,std::string,first_name)>,
    ordered_non_unique<
      tag<last_name>,BOOST_MULTI_INDEX_MEMBER(PersonInfo,std::string,last_name)>,
    ordered_unique<
      tag<rm_code>, BOOST_MULTI_INDEX_MEMBER(PersonInfo,int,rm_code)> >
> person_info_set;

int has_negative_words_of_interest (string s2, const set<string> & negative_words_of_interest, string & addnl_info)
{
	int result = 0;
	//cout << "searching for negative_words_of_interest in " << s2 << endl;
	for (set<string>::iterator it=negative_words_of_interest.begin();
		it != negative_words_of_interest.end(); ++it) {
		string  neg_word = *it;
		if (s2.find (neg_word)!= string::npos) {
			addnl_info += ": |" + s2 + "| has word of interest: |" + neg_word + "|";
			++result ;
		}
	}
	return result;
}

struct regular_expression_scores {
	string human_pattern;
	long long score;
};

int match_regular_expressions_of_interest (const string & s, string & addnl_info)
{
	//cout << "match_reg" 
	//	<< ", " << s << ", regexp"
	//	<< "vector size:" << regular_expressions_of_interest.size()
	//	<< endl;
	int cumulative_score = 0; 
	for (int i=0; i<regular_expressions_of_interest.size(); ++i) {
		regmatch_t p_match[5];
		int n_match=5;
		regex_t a_regex = regular_expressions_of_interest[i];
		int regex_result = regexec (&a_regex, s.c_str(), n_match, p_match, 0);
		if (regex_result == 0) {
			//cout << __PRETTY_FUNCTION__ << " We have a match"
			//	<< endl;
			addnl_info += "matched with regexp";
			++cumulative_score;
		} else {
			//cout << __PRETTY_FUNCTION__ << " no match in vector pattern"
			//	<< endl;
		}
		//regex_t regex_dk;
		//regcomp (&regex_dk, "DON.*T KNOW", REG_ICASE);
		//regex_result = regexec (&regex_dk, s.c_str(), n_match, p_match, 0);
		//if (regex_result == 0) {
		//	cout << __PRETTY_FUNCTION__ << " We have a match AGAINST Hard coded"
		//		<< endl;
		//	++cumulative_score;
		//} else {
		//	cout << __PRETTY_FUNCTION__ << " NO MATCH AGAINST Hard coded: " << s
		//		<< endl;
		//}
	}
	//cout << "Exit: " << __PRETTY_FUNCTION__ << ", score, "  << cumulative_score << endl;
	return cumulative_score;
}

// This code is from stack overflow
// http://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
std::string trim(const std::string& str,
                 const std::string& whitespace /*= " \t"*/)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string reduce(const std::string& str,
                   const std::string& fill = " ",
                   const std::string& whitespace = " \t")
{
    // trim first
    auto result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}

vector <string> split_into_words(string s)
{
	vector <string> result;
	boost::tokenizer<> tok(s);
	for(boost::tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg) {
		result.push_back (*beg);
	}
	return result;
}


int check_for_groups_of_single_word_match_in_same_name(const vector<string> & bank_rm_name_vec, const vector<string> & recalled_name_vec, int serial_no, string & addnl_info)
{
	//cout << "bank_rm_name_vec.size():" << bank_rm_name_vec.size() << endl;
	//cout << "bank_rm_name_vec.size():" << bank_rm_name_vec.size() << endl;
	int score = 0;
	for (int i=0; i<recalled_name_vec.size(); ++i) {
		string recalled_name = recalled_name_vec[i];
		for (int j=0; j< bank_rm_name_vec.size(); ++j) {
			if (recalled_name == bank_rm_name_vec[j]) {
				++score;
				stringstream ss1;
				ss1 << "match: recalled_name |" << recalled_name 
					<< ": bank_rm_name_vec |" << bank_rm_name_vec[j] 
					<< ": serial_no|" << serial_no;
				addnl_info += ss1.str();
			}
		}
	}
	return score;
}


int check_for_alternate_rm_exact_match (const string & recalled_name, string & addnl_info, int serial_no
	, int & other_rm_code, string & other_rm_name
)
{
	int score = 0;
	//if (serial_no == 1178) {
	//	cout << "serial of interest: strstr should fire" << endl;
	//}
	//if (strstr (recalled_name.c_str(), "MARYAM SHIRAZI")) {
	//	cout << __PRETTY_FUNCTION__ << "target acquired" 
	//		<< ",serial_no," << serial_no
	//		<< endl;
	//}
	map<string, int>::iterator it = rm_name_code_map.find(recalled_name);
	if (it == rm_name_code_map.end()) {
	} else {
		//verdict += ":matched other rm";
		stringstream ss1;
		ss1 << ",other rm name," << it->first 
			<< ",other rm code," << it->second;
		addnl_info += ss1.str();
		score = 1;
		other_rm_code = it->second;
		other_rm_name = it->first;
	}
	return score;
}

typedef person_info_set::index<first_name>::type person_by_first_name;
typedef person_info_set::index<last_name>::type person_by_last_name;

int  check_for_alternate_rm_word_match (string recalled_name, string & addnl_info,
	int serial_no, const person_info_set & pinf_set,
	int & other_rm_code, string & other_rm_name
	)
{
	int score = 0;
	vector <string> recalled_name_split = split_into_words (recalled_name);
	for (int i=0; i<recalled_name_split.size(); ++i) {
		//const string & f_name = name_split[0];
		//const string & l_name = name_split[name_split.size()-1];
		const string & possible_name = recalled_name_split[i];
		person_by_first_name::iterator it_find_fn = pinf_set.get<first_name>().find(possible_name);
		person_by_last_name::iterator  it_find_ln = pinf_set.get<last_name>().find(possible_name);
		if (it_find_fn != pinf_set.get<first_name>().end() ) {
			stringstream ss1;
			ss1 << "check_for_alternate_rm_word_match: got a word match on "
				<< "possible_name|" << possible_name
				<< "| so full name is |" << it_find_fn->first_name
				<< "|" << it_find_fn->last_name
				<< "|" << it_find_fn->rm_code
				;
			other_rm_name += it_find_fn->first_name;
			other_rm_name += string(" ") + it_find_fn->last_name;
			other_rm_code = it_find_fn->rm_code;
			addnl_info += ss1.str();
			++score;
		}
		if (it_find_ln != pinf_set.get<last_name>().end() ) {
			stringstream ss1;
			ss1 << "check_for_alternate_rm_word_match: got a word match on |"
				<< "possible_name|" << possible_name
				<< "| so full name is |" << it_find_ln->last_name
				<< "|" << it_find_ln->last_name
				<< "|" << it_find_ln->rm_code
				;
			other_rm_name += it_find_ln->first_name;
			other_rm_name += string("|") + it_find_ln->last_name;
			other_rm_code = it_find_ln->rm_code;
			addnl_info += ss1.str();
			++score;
		}
	}
	return score;
}

// return a score on the match
int match_score(const string & recalled_name, const string & bank_provided_rm_name,
	const  set <string> & negative_words_of_interest,
	string & addnl_info,
	string & verdict,
	int serial_no,
	const person_info_set & pinf_set,
	int & other_rm_code,
	string & other_rm_name
	)
{
	
	int score = 0;
	if (recalled_name == bank_provided_rm_name) {
		verdict = "exact match,proposed rm name,N/A";
		score =  INT_MAX;
		stringstream ss1;
		ss1 << ",," << "N/A";
		addnl_info += ss1.str();
	} else if (bank_provided_rm_name.find (recalled_name) != string :: npos) {
		verdict = "partial match,proposed rm name,dbl check:negative recall";
		stringstream ss1;
		ss1 << ",," << "N/A";
		addnl_info += ss1.str();
		score =  100;
	} 
	
	if (score==0) {
		int score_negative_word_of_interest = has_negative_words_of_interest (recalled_name, negative_words_of_interest, addnl_info);
		if (score_negative_word_of_interest > 0) {
			verdict = "heuristic,negative_words_of_interest,exact match";
			score += score_negative_word_of_interest;
		}
		//score += has_negative_words_of_interest (bank_provided_rm_name, negative_words_of_interest, addnl_info);
	}
	if (score == 0) {
		int regex_score = match_regular_expressions_of_interest (recalled_name, addnl_info);
		if (regex_score) {
			verdict += "heuristic,negative_words_of_interest,pattern";
			score += regex_score;
		}
	}

	// check for single word match of first_name or last_name in the same bank provided rm name
	if (score == 0) {
		vector<string> bank_provided_rm_name_split = split_into_words(bank_provided_rm_name);
		//print_vec (res1);
		vector <string> recalled_name_split = split_into_words (recalled_name);
		int word_match_score = 
			check_for_groups_of_single_word_match_in_same_name(bank_provided_rm_name_split, recalled_name_split, serial_no, addnl_info);
		if (word_match_score > 0) {
			verdict = "heuristic,proposed name single word,pattern";
			score += word_match_score;
		}
	}

	// check for exact match of alternate rm in 
	if (score == 0) {
		//map<string, int>::iterator it = rm_name_code_map.find(recalled_name);
		//if (it == rm_name_code_map.end()) {
		//} else {
		//	verdict += ":matched other rm";
		//	stringstream ss1;
		//	ss1 << ",other rm name," << it->first 
		//		<< ",other rm code," << it->second;
		//	addnl_info += ss1.str();
		//}
		int alt_rm_score  = check_for_alternate_rm_exact_match (recalled_name, addnl_info,
				serial_no, other_rm_code, other_rm_name);
		if (alt_rm_score > 0) {
			verdict = "exact,matched other rm,N/A";
			score += alt_rm_score;
		}
	}

	// check for word match of first_name or last_name in alternate rm name
	if (score == 0) {
		int alt_rm_score  = check_for_alternate_rm_word_match (recalled_name, addnl_info, serial_no, pinf_set,
			other_rm_code, other_rm_name);
		if (alt_rm_score > 0) {
			verdict = "heuristic,word match other rm,pattern";
			score += alt_rm_score;
		}
	}


	return score;
}

using std::set;

// has side effects - bad programming

vector <string> human_readable_regex_pattern;

void populate_regular_expressions_of_interest()
{
	{
		regex_t regex_dk;
		string pattern = "DON.\\{1,6\\}T KNOW";
		human_readable_regex_pattern.push_back(pattern);
		regcomp (&regex_dk, pattern.c_str(), REG_ICASE);
		regular_expressions_of_interest.push_back (regex_dk);
	}
	{
		regex_t regex_dk;
		string pattern = "DON.\\{1,6\\}T RECALL";
		human_readable_regex_pattern.push_back(pattern);
		regcomp (&regex_dk, pattern.c_str(), REG_ICASE);
		regular_expressions_of_interest.push_back (regex_dk);
	}
	{
		regex_t regex_dk;
		string pattern = "DON.\\{1,6\\}T RECALL";
		human_readable_regex_pattern.push_back(pattern);
		regcomp (&regex_dk, pattern.c_str(), REG_ICASE);
		regular_expressions_of_interest.push_back (regex_dk);
	}
	{
		regex_t regex_dk;
		string pattern = "DON.\\{1,6\\}T KNW";
		human_readable_regex_pattern.push_back(pattern);
		regcomp (&regex_dk, pattern.c_str(), REG_ICASE);
		regular_expressions_of_interest.push_back (regex_dk);
	}
	{
		regex_t regex_dk;
		string pattern = "DOESN.\\{1,6\\}T KNOW";
		human_readable_regex_pattern.push_back(pattern);
		regcomp (&regex_dk, pattern.c_str(), REG_ICASE);
		regular_expressions_of_interest.push_back (regex_dk);
	}
	{
		regex_t regex_dk;
		string pattern = "DON.\\{1,6\\}T REMEMBER";
		human_readable_regex_pattern.push_back(pattern);
		regcomp (&regex_dk, pattern.c_str(), REG_ICASE);
		regular_expressions_of_interest.push_back (regex_dk);
	}
	{
		regex_t regex_dk;
		string pattern = "NOT \\+AWARE";
		human_readable_regex_pattern.push_back(pattern);
		regcomp (&regex_dk, pattern.c_str(), REG_ICASE);
		regular_expressions_of_interest.push_back (regex_dk);
	}

}

// has side effects - bad programming
void populate_negative_words_of_interest()
{
	negative_words_of_interest.insert("DON'T KNW");
	negative_words_of_interest.insert("DON'T KNOW");
	negative_words_of_interest.insert("DON'T RECALL");
	negative_words_of_interest.insert("DO NOT REMEMBER");
	negative_words_of_interest.insert("CAN'T REMEMBER");
	negative_words_of_interest.insert("CAN NOT REMEMBER");
	negative_words_of_interest.insert("DON'T REMEMBER");
	negative_words_of_interest.insert("DO NOT KNOW");
	negative_words_of_interest.insert("NOT AWARE");
	negative_words_of_interest.insert("DO NOT RECOLLECT");
	negative_words_of_interest.insert("NO IDEA");
	negative_words_of_interest.insert("CANT REMEMBER");
	negative_words_of_interest.insert("DID NOT KNOW");
	negative_words_of_interest.insert("DOES NOT KNOW");
	negative_words_of_interest.insert("DOESN'T KNOW");
	negative_words_of_interest.insert("NOT SURE");
	negative_words_of_interest.insert("DO NOT THINK");
}

void insert_into_multi_index (person_info_set & pinf_set, vector<string> &name_data, int rm_code)
{
	if (name_data.size()>= 2) {
		pinf_set.insert ( PersonInfo(name_data[0], name_data[name_data.size()-1], rm_code));
	} else {
		cout << "illegal name - should atleast have 1st and last name"
			<< endl;
	}
}

void populate_person_info_set (person_info_set & pinf_set)
{
	for (int i=0; i< info_vec.size(); ++i) {
		const Info &inf = info_vec[i];
		vector <string> name_split = split_into_words(inf.rm_name);
		if (name_split.size() >= 2) {
			const string & f_name = name_split[0];
			const string & l_name = name_split[name_split.size()-1];
			person_by_first_name::iterator it_find_fn = pinf_set.get<first_name>().find(f_name);
			person_by_last_name::iterator it_find_ln = pinf_set.get<last_name>().find(l_name);
			if (it_find_fn == pinf_set.get<first_name>().end() && 
				it_find_ln == pinf_set.get<last_name>().end()
			) {
				insert_into_multi_index (pinf_set, name_split, inf.rm_code);
				//cout << "added RM: ,fn," << f_name << ", ln," << l_name 
				//	<< ",rm_code," << inf.rm_code
				//	<< endl;
			/*} else if (it_find_fn->last_name !=  l_name) {
				insert_into_multi_index (pinf_set, name_split, inf.rm_code);
				cout << "added RM| same fn different ln," << f_name << ", ln," << l_name
					<< "," << it_find_fn->first_name << "," << it_find_fn->last_name
					<< endl;
				*/
			} else  {
				//person_by_last_name::iterator it_find_ln = pinf_set.get<last_name>().find(l_name);
				//person_by_first_name::iterator it_find_by_rm = pinf_set.get<rm_code>().find(l_name);
				//if (it_find_ln == pinf_set<it_find_ln>().end()) {
				//	cout << "already present RM: fn" << f_name << ", ln" << l_name << endl;
				//}
				//cout << "already present RM: fn," << f_name << ", ln," << l_name << endl;
				//cout << it_find_fn->first_name << "," << it_find_fn->last_name << endl;
				if ( 
					it_find_fn->first_name == f_name && it_find_fn->last_name == l_name
					&& (  it_find_fn->rm_code != inf.rm_code)
				) {
					cout << "PROBLEM: Bank provided rm_code is not consistent:" 
						<< it_find_fn->rm_code << ", " << inf.rm_code
						<< endl
						;
				} else if (
					it_find_ln->first_name == f_name && it_find_ln->last_name == l_name
					&& (  it_find_ln->rm_code != inf.rm_code)
				) {
					cout << "PROBLEM: Bank provided rm_code is not consistent:" 
						<< it_find_fn->rm_code << ", " << inf.rm_code
						<< endl
						;
				} else {
					//cout << "IMPOSSIBLE: this should never happen" << endl;
				}
			}
		}
	}
}

void print_result(const Info & inf, const string & verdict, const string addnl_info, int score,
	const int & other_rm_code, const string & other_rm_name
	)
{
	cout << verdict 
		//<< "ser_no, "
		<< "," << inf.serial_no 
		//<< ", rm_name, bank_rm_code"
		<< ",\""<< inf.rm_name << "\""
		<< ", " << inf.rm_code;

	if (verdict == "exact match,proposed rm name,N/A") {
		cout
			//<< ", proposed_recalled_name, proposed_recall_code"
			<< ",\"N/A\",\"N/A\""
			//<< ", match_quality"
			<< ", perfect"
			//<< ", reason1, reason2"
			<< ",,"
			//<<", score"
			<< "," << score
			//<<", raw_recalled_text"
			<< "," << "\"" << inf.recalled_name << "\""
			<< "," << addnl_info
			<< endl;
	} else if (verdict == "partial match,proposed rm name,dbl check:negative recall") {
		cout
			//<< ", proposed_recalled_name, proposed_recall_code"
			<< ",\"N/A\",\"N/A\""
			//<< ", match_quality"
			<< ", very high"
			//<< ", reason1, reason2"
			<< ",,"
			//<<", score"
			<< "," << score
			//<<", raw_recalled_text"
			<< "," << "\"" << inf.recalled_name << "\""
			<< "," << addnl_info
			<< endl;
	} else if (verdict == "heuristic,negative_words_of_interest,exact match") {
		cout
			//<< ", proposed_recalled_name, proposed_recall_code"
			<< ",\"N/A\",\"N/A\""
			//<< ", match_quality"
			<< ", high"
			//<< ", reason1, reason2"
			<< ",,"
			//<<", score"
			<< "," << score
			//<<", raw_recalled_text"
			<< "," << "\"" << inf.recalled_name << "\""
			<< "," << addnl_info
			<< endl;
	} else if (verdict == "heuristic,negative_words_of_interest,pattern") {
		cout
			//<< ", proposed_recalled_name, proposed_recall_code"
			<< ",\"N/A\",\"N/A\""
			//<< ", match_quality"
			<< ", high"
			//<< ", reason1, reason2"
			<< ",,"
			//<<", score"
			<< "," << score
			//<<", raw_recalled_text"
			<< "," << "\"" << inf.recalled_name << "\""
			<< "," << addnl_info
			<< endl;
	} else if (verdict == "exact,matched other rm,N/A") {
		cout
			//<< ", proposed_recalled_name, proposed_recall_code"
			//<< ",\"N/A\",\"N/A\""
			<< "," << other_rm_name << "," << other_rm_code 
			//<< ", match_quality"
			<< ", perfect"
			//<< ", reason1, reason2"
			<< ",,"
			//<<", score"
			<< "," << score
			//<<", raw_recalled_text"
			<< "," << "\"" << inf.recalled_name << "\""
			<< "," << addnl_info
			<< endl;
	} else if (verdict == "heuristic,word match other rm,pattern") {
		cout
			//<< ", proposed_recalled_name, proposed_recall_code"
			//<< ",\"N/A\",\"N/A\""
			<< "," << other_rm_name << "," << other_rm_code 
			//<< ", match_quality"
			<< ", ok:check visually"
			//<< ", reason1, reason2"
			<< ",,"
			//<<", score"
			<< "," << score
			//<<", raw_recalled_text"
			<< "," << "\"" << inf.recalled_name << "\""
			<< "," << addnl_info
			<< endl;
	} else if (verdict == "heuristic,proposed name single word,pattern") {
		cout
			//<< ", proposed_recalled_name, proposed_recall_code"
			<< ",\"N/A\",\"N/A\""
			//<< "," << other_rm_name << "," << other_rm_code 
			//<< ", match_quality"
			<< ", good:check visually"
			//<< ", reason1, reason2"
			<< ",,"
			//<<", score"
			<< "," << score
			//<<", raw_recalled_text"
			<< "," << "\"" << inf.recalled_name << "\""
			<< "," << addnl_info
			<< endl;
	} else {
		cout << "NOT YET DONE FIX PROGRAM" << endl;
	}

}

void do_match(const person_info_set & pinf_set)
{
	for (int i=0; i< info_vec.size(); ++i) {
		string recalled_name = info_vec[i].recalled_name;
		string rm_name = info_vec[i].rm_name;
		int serial_no = info_vec[i].serial_no;
		int rm_code = info_vec[i].rm_code;
		if (recalled_name.length() > 0) {
			string addnl_info;
			string verdict;
			int other_rm_code=-1;
			string other_rm_name;
			if (int score = match_score (recalled_name, rm_name, 
					negative_words_of_interest, addnl_info,
					verdict, serial_no, pinf_set,
					other_rm_code, other_rm_name) ) {
				print_result(info_vec[i], verdict, addnl_info, score,
					other_rm_code, other_rm_name);
				//cout << verdict << ","
				//	//<< "ser_no, "
				//	<< serial_no << ", " 
				//	//<< ", rm_name, " 
				//	<< rm_name << ", "
				//	<< rm_code << ", "
				//	//<< ", recalled_name, "
				//	<< "\"" << recalled_name << "\"" << ","
				//	//<< ", score, " 
				//	<< score << ","
				//	<< addnl_info
				//	<< endl;
			} else {
				//cout << "FIX ME," << endl;
				//cout << "not matched," 
				//	//<< "  ser_no, "
				//	<< serial_no  << ", "
				//	//<< ", rm_name, " 
				//	<< rm_name <<", "
				//	//<< ", recalled_name, " 
				//	<< "\"" << recalled_name << "\"" << ","
				//	//<< ", score, " 
				//	<< 0 << ","
				//	<< addnl_info
				//	<< endl;
				cout << "not matched,,"
					<< "," << info_vec[i].serial_no
				<< ",\""<< info_vec[i].rm_name << "\""
				<< ", " << info_vec[i].rm_code
				//<< ", proposed_recalled_name, proposed_recall_code"
				<< ",\"N/A\",\"N/A\""
				//<< ", match_quality"
				<< ", N/A"
				//<< ", reason1, reason2"
				<< ",not matched any criteria,"
				//<<", score"
				<< "," << 0
				//<<", raw_recalled_text"
				<< "," << "\"" << info_vec[i].recalled_name << "\""
				//<< "," << addnl_info
				<< "," 
				<< endl;
			}
		} else {
			//cout << "FIX ME," << endl;
			cout << "impossible,,"
				<< "," << info_vec[i].serial_no
			<< ",\""<< info_vec[i].rm_name << "\""
			<< ", " << info_vec[i].rm_code
			//<< ", proposed_recalled_name, proposed_recall_code"
			<< ",\"N/A\",\"N/A\""
			//<< ", match_quality"
			<< ", impossible"
			//<< ", reason1, reason2"
			<< ",recall text empty,"
			//<<", score"
			<< "," << 0
			//<<", raw_recalled_text"
			<< "," << "\"" << info_vec[i].recalled_name << "\""
			//<< "," << addnl_info
			<< "," 
			<< endl;
		}
	}
}

int main()
{
	string s1 = "  thre is leading space here ";
	string s2 = trim (s1);
	//cout << "trimmed s1" << endl;
	std::string fname ("s2b-data_v4_1.csv");
	DebugFreqLexer = 1;
	FILE * yyin = fopen(fname.c_str(), "rb");
	if (!yyin){
		cerr << " Unable to open: " << fname << " for read ... exiting" << endl;
		exit(1);
	}

	populate_negative_words_of_interest();
	populate_regular_expressions_of_interest();
	yyrestart(yyin);
	//cout << endl;
 	cout << "match_lvl_1,match_lvl_2,match_lvl_3"
		<< ", serno, rm_name, bank_rm_code"
		<< ", proposed_recalled_name, proposed_recall_code"
		<< ", match_quality"
		<< ", reason1, reason2, score, raw_recalled_text"
		<< ", addnl_info"
		<< endl;
	if (!yyparse()) {
		//cout << "Input parsed successfully" << endl;
		person_info_set pinf_set;
		populate_person_info_set(pinf_set);
		do_match(pinf_set);
	} else {
		cout << "Error parsing input" << endl;
	}
	
}


