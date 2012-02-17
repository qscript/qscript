
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
#line 7 "src/q.ypp"


//#include "common.h"

#include <inttypes.h>
#include <sys/types.h>
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
#include "expr.h"
#include "stmt.h"
#include "named_attributes.h"
//#include "named_range.h"
#include "new_named_range.h"
#include "question.h"
#include "QuestionAttributes.h"

#include "qscript_parser.h"

	//using qscript_parser::yyerror;
	//using qscript_parser::yylex;
	//using qscript_parser::yywrap;
	extern int32_t yylex();
	extern void yyerror(const char * s);
	using std::cout;
	using std::cerr;
	using std::endl;
	int32_t flag_cmpd_stmt_is_a_func_body=-1;
	vector </*Statement::*/FunctionInformation*> func_info_table;
	QuestionAttributes question_attributes;
	vector<TextExpression*> text_expr_vec;
	vector<string> vec_named_attribute_list;
	//bool check_duplicate_stub_entry (string  stub_text, int code);
	//bool check_duplicate_code_entry (int code);
	vector <int> stub_number;




/* Line 189 of yacc.c  */
#line 122 "src/q.cpp"

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
     TOSTRING = 261,
     TEXT = 262,
     SINGLE_CODED = 263,
     MP = 264,
     VOID_T = 265,
     INT8_T = 266,
     INT16_T = 267,
     INT32_T = 268,
     FLOAT_T = 269,
     DOUBLE_T = 270,
     STRING_T = 271,
     IN = 272,
     FOR = 273,
     GOTO = 274,
     HIDDEN = 275,
     ALLOW_BLANK = 276,
     MUTEX = 277,
     CLEAR = 278,
     COLUMN = 279,
     ISANSWERED = 280,
     NEWCARD = 281,
     RANDOMIZE = 282,
     CONST = 283,
     LOGOR = 284,
     LOGAND = 285,
     NOEQ = 286,
     ISEQ = 287,
     GEQ = 288,
     LEQ = 289,
     NOT = 290,
     UMINUS = 291,
     COUNT = 292,
     FUNC_CALL = 293,
     IF = 294,
     ELSE = 295,
     STUBS_LIST = 296,
     STUB_GROUP = 297,
     NAMED_ATTRIBUTES = 298,
     SETDEL = 299,
     SETADD = 300,
     UNSET = 301,
     SETALL = 302
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 56 "src/q.ypp"

	type_qualifier type_qual;
	int32_t ival;
	double dval;
	char name[MY_STR_MAX];
	char text_buf[MY_STR_MAX];
	DataType dt;
	struct AbstractStatement * stmt;
	struct AbstractExpression * expr;
	//class AbstractQuestion* ques;
	struct CompoundStatement * c_stmt;
	struct FunctionParameter * v_list;
	struct AbstractNamedRange * nr_ptr;




/* Line 214 of yacc.c  */
#line 223 "src/q.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 235 "src/q.cpp"

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
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   742

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  132
/* YYNRULES -- Number of states.  */
#define YYNSTATES  303

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    47,    61,     2,
      30,    31,    45,    44,    34,    43,    66,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    65,    62,
      39,    32,    40,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    28,     2,    29,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    64,     2,    63,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    33,    35,    36,    37,    38,    41,    42,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,     9,    17,    19,    23,    26,
      32,    36,    37,    39,    42,    44,    46,    48,    50,    52,
      54,    56,    58,    62,    69,    75,    82,    84,    86,    88,
      90,    92,    94,    96,    98,   100,   102,   104,   106,   108,
     110,   113,   114,   125,   129,   131,   137,   145,   148,   152,
     158,   167,   173,   179,   184,   192,   201,   209,   211,   215,
     217,   222,   229,   231,   232,   235,   237,   240,   242,   244,
     248,   252,   256,   260,   264,   267,   271,   275,   279,   283,
     287,   291,   295,   299,   303,   306,   308,   310,   312,   317,
     322,   324,   328,   332,   337,   341,   346,   351,   353,   357,
     359,   364,   369,   371,   375,   379,   381,   385,   387,   391,
     395,   397,   398,   405,   411,   413,   417,   419,   423,   426,
     430,   432,   433,   440,   442,   445,   453,   464,   472,   483,
     491,   499,   505
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      68,     0,    -1,     5,    80,    -1,    69,    -1,    -1,    74,
       5,    30,    71,    31,    70,    80,    -1,    72,    -1,    71,
      34,    72,    -1,    74,     5,    -1,    74,     5,    28,     3,
      29,    -1,    74,    61,     5,    -1,    -1,    77,    -1,    73,
      77,    -1,    10,    -1,    11,    -1,    12,    -1,    13,    -1,
      14,    -1,    15,    -1,    16,    -1,    33,    -1,    74,     5,
      62,    -1,    75,    74,     5,    32,    95,    62,    -1,    74,
       5,    32,    95,    62,    -1,    74,     5,    28,    95,    29,
      62,    -1,    89,    -1,    83,    -1,    76,    -1,   103,    -1,
     105,    -1,    80,    -1,    82,    -1,    78,    -1,   112,    -1,
      84,    -1,    85,    -1,    86,    -1,    87,    -1,    88,    -1,
       1,    62,    -1,    -1,    18,    30,    95,    62,    95,    62,
      95,    31,    79,    80,    -1,    81,    73,    63,    -1,    64,
      -1,    52,    30,    95,    31,    77,    -1,    52,    30,    95,
      31,    77,    53,    77,    -1,    95,    62,    -1,    19,     5,
      62,    -1,    23,    30,     5,    31,    62,    -1,    23,    30,
       5,    28,    95,    29,    31,    62,    -1,    24,    30,    95,
      31,    62,    -1,    26,    30,    95,    31,    62,    -1,    27,
      54,     5,    62,    -1,     5,    90,    97,    74,   100,    92,
      62,    -1,     5,    90,    97,    74,   100,    98,    92,    62,
      -1,     5,    90,    97,    74,     5,    92,    62,    -1,    91,
      -1,    90,    65,    91,    -1,     7,    -1,     5,    28,    95,
      29,    -1,     5,    66,    54,    28,    95,    29,    -1,     5,
      -1,    -1,    65,    93,    -1,    94,    -1,    93,    94,    -1,
      20,    -1,    21,    -1,    95,    44,    95,    -1,    95,    43,
      95,    -1,    95,    45,    95,    -1,    95,    46,    95,    -1,
      95,    47,    95,    -1,    43,    95,    -1,    95,    39,    95,
      -1,    95,    40,    95,    -1,    95,    42,    95,    -1,    95,
      41,    95,    -1,    95,    38,    95,    -1,    95,    37,    95,
      -1,    95,    35,    95,    -1,    95,    36,    95,    -1,    95,
      32,    95,    -1,    48,    95,    -1,     3,    -1,     4,    -1,
       5,    -1,     5,    28,    95,    29,    -1,     5,    30,    96,
      31,    -1,     7,    -1,    30,    95,    31,    -1,    95,    17,
     100,    -1,     6,    30,     5,    31,    -1,    95,    17,     5,
      -1,    25,    30,     5,    31,    -1,    50,    30,     5,    31,
      -1,    95,    -1,    96,    34,    95,    -1,     8,    -1,     9,
      30,     3,    31,    -1,    22,    30,    99,    31,    -1,    98,
      -1,    99,    34,    98,    -1,     3,    43,     3,    -1,     3,
      -1,    30,   101,    31,    -1,   102,    -1,   101,    34,   102,
      -1,     3,    43,     3,    -1,     3,    -1,    -1,    54,     5,
     104,    32,   111,    62,    -1,    56,     5,    32,   106,    62,
      -1,     7,    -1,   106,    34,     7,    -1,   108,    -1,   107,
      34,   108,    -1,     7,     3,    -1,     7,     3,    22,    -1,
     107,    -1,    -1,    55,     5,   110,    64,   111,    63,    -1,
     109,    -1,   111,   109,    -1,    57,    30,     5,    34,     5,
      31,    62,    -1,    57,    30,     5,    34,     5,    28,    95,
      29,    31,    62,    -1,    58,    30,     5,    34,     5,    31,
      62,    -1,    58,    30,     5,    34,     5,    28,    95,    29,
      31,    62,    -1,    58,    30,     5,    34,   100,    31,    62,
      -1,    57,    30,     5,    34,   100,    31,    62,    -1,    59,
      30,     5,    31,    62,    -1,    60,    30,     5,    31,    62,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   166,   166,   174,   180,   180,   213,   217,   223,   230,
     239,   248,   256,   265,   273,   274,   275,   276,   277,   278,
     279,   282,   287,   290,   292,   295,   305,   306,   307,   308,
     309,   310,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   338,   338,   353,   358,   368,   383,   411,   430,   435,
     439,   445,   450,   455,   460,   474,   487,   499,   500,   503,
     506,   525,   548,   572,   573,   577,   578,   581,   584,   590,
     599,   608,   617,   626,   635,   644,   653,   662,   671,   680,
     689,   698,   707,   716,   725,   734,   743,   751,   759,   767,
     821,   828,   835,   844,   850,   856,   862,   880,   881,   886,
     892,   897,   902,   903,   907,   918,   924,   928,   929,   932,
     944,   950,   950,   996,  1005,  1008,  1013,  1014,  1018,  1056,
    1093,  1099,  1099,  1137,  1138,  1146,  1150,  1154,  1158,  1162,
    1168,  1175,  1178
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INUMBER", "FNUMBER", "NAME", "TOSTRING",
  "TEXT", "SINGLE_CODED", "MP", "VOID_T", "INT8_T", "INT16_T", "INT32_T",
  "FLOAT_T", "DOUBLE_T", "STRING_T", "IN", "FOR", "GOTO", "HIDDEN",
  "ALLOW_BLANK", "MUTEX", "CLEAR", "COLUMN", "ISANSWERED", "NEWCARD",
  "RANDOMIZE", "'['", "']'", "'('", "')'", "'='", "CONST", "','", "LOGOR",
  "LOGAND", "NOEQ", "ISEQ", "'<'", "'>'", "GEQ", "LEQ", "'-'", "'+'",
  "'*'", "'/'", "'%'", "NOT", "UMINUS", "COUNT", "FUNC_CALL", "IF", "ELSE",
  "STUBS_LIST", "STUB_GROUP", "NAMED_ATTRIBUTES", "SETDEL", "SETADD",
  "UNSET", "SETALL", "'&'", "';'", "'}'", "'{'", "':'", "'.'", "$accept",
  "prog", "func_defn", "$@1", "decl_comma_list", "var_decl", "stmt_list",
  "datatype", "type_qual", "decl_stmt", "stmt", "for_loop_stmt", "$@2",
  "cmpd_stmt", "open_curly", "if_stmt", "expr_stmt", "goto_stmt",
  "clear_stmt", "column_stmt", "newcard_stmt", "randomize_stmt",
  "question", "text_expr_list", "text_expr", "attribute_list",
  "attributes", "attribute", "expression", "expr_list", "qtype",
  "mutex_range", "mutex_range_list", "range_allowed_values", "range_list",
  "range", "stubs", "$@3", "named_attributes", "named_attribute_list",
  "simple_stub_list", "simple_stub", "stub", "$@4", "stub_list",
  "stub_manip_stmts", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    91,    93,
      40,    41,    61,   283,    44,   284,   285,   286,   287,    60,
      62,   288,   289,    45,    43,    42,    47,    37,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,    38,    59,   125,   123,    58,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    67,    68,    68,    70,    69,    71,    71,    72,    72,
      72,    72,    73,    73,    74,    74,    74,    74,    74,    74,
      74,    75,    76,    76,    76,    76,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    79,    78,    80,    81,    82,    82,    83,    84,    85,
      85,    86,    87,    88,    89,    89,    89,    90,    90,    91,
      91,    91,    91,    92,    92,    93,    93,    94,    94,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    96,    96,    97,
      97,    98,    99,    99,    98,    98,   100,   101,   101,   102,
     102,   104,   103,   105,   106,   106,   107,   107,   108,   108,
     109,   110,   109,   111,   111,   112,   112,   112,   112,   112,
     112,   112,   112
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     0,     7,     1,     3,     2,     5,
       3,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     6,     5,     6,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     0,    10,     3,     1,     5,     7,     2,     3,     5,
       8,     5,     5,     4,     7,     8,     7,     1,     3,     1,
       4,     6,     1,     0,     2,     1,     2,     1,     1,     3,
       3,     3,     3,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     1,     1,     1,     4,     4,
       1,     3,     3,     4,     3,     4,     4,     1,     3,     1,
       4,     4,     1,     3,     3,     1,     3,     1,     3,     3,
       1,     0,     6,     5,     1,     3,     1,     3,     2,     3,
       1,     0,     6,     1,     2,     7,    10,     7,    10,     7,
       7,     5,     5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    14,    15,    16,    17,    18,    19,    20,     0,
       3,     0,    44,     2,     0,     1,     0,     0,    85,    86,
      87,     0,    90,     0,     0,     0,     0,     0,     0,     0,
       0,    21,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    28,    12,    33,    31,    32,
      27,    35,    36,    37,    38,    39,    26,     0,    29,    30,
      34,    11,    40,    62,    59,     0,     0,     0,    57,     0,
       0,     0,     0,     0,     0,     0,     0,    87,     0,    74,
      84,     0,     0,   111,     0,     0,     0,     0,     0,    43,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    47,     0,
       6,     0,     0,     0,     0,    97,     0,    99,     0,     0,
       0,     0,     0,    48,     0,     0,     0,     0,     0,    91,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      22,     0,    94,     0,    92,    83,    81,    82,    80,    79,
      75,    76,    78,    77,    70,    69,    71,    72,    73,     4,
      11,     8,     0,     0,     0,    88,    89,     0,     0,    58,
       0,    93,     0,     0,     0,     0,    95,     0,    53,    96,
       0,     0,   114,     0,     0,     0,     0,     0,     0,     0,
       0,   110,     0,   107,     0,     7,     0,    10,    60,     0,
      98,     0,    63,    63,     0,     0,    49,    51,    52,    45,
       0,     0,   120,   116,   123,     0,     0,   113,     0,     0,
       0,     0,   131,   132,     0,    24,     0,     0,   106,     0,
       5,     0,     0,   100,     0,     0,   105,     0,     0,    63,
       0,     0,     0,   118,   121,     0,   112,   124,   115,     0,
       0,     0,     0,     0,     0,    25,    23,   109,   108,     9,
      61,    67,    68,    64,    65,    56,     0,     0,    54,     0,
       0,     0,    46,   119,     0,   117,     0,   125,   130,     0,
     127,   129,    66,   104,   102,     0,    55,    41,    50,     0,
       0,     0,   101,     0,     0,     0,     0,     0,   103,    42,
     122,   126,   128
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,   194,   109,   110,    42,    43,    44,    45,
      46,    47,   294,    48,    14,    49,    50,    51,    52,    53,
      54,    55,    56,    67,    68,   235,   263,   264,    57,   116,
     120,   239,   285,   144,   192,   193,    58,   132,    59,   183,
     212,   213,   214,   274,   215,    60
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -251
static const yytype_int16 yypact[] =
{
      91,   -46,  -251,  -251,  -251,  -251,  -251,  -251,  -251,    26,
    -251,    27,  -251,  -251,   271,  -251,    31,   -32,  -251,  -251,
      24,    81,  -251,    82,   129,   105,   106,   111,   128,   115,
      83,  -251,    83,    83,   130,   143,   154,   169,   171,   173,
     175,   182,   203,   219,   184,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,   110,  -251,  -251,
    -251,   184,  -251,   -18,  -251,    83,    83,    14,  -251,   220,
      83,   170,   230,    83,   232,    83,   233,   -14,   145,   222,
     222,   235,    83,  -251,   209,   237,   238,   239,   240,  -251,
    -251,   -17,   242,     8,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,  -251,    -7,
    -251,    20,    83,   194,   425,   695,    60,  -251,   224,   123,
     184,   218,   301,  -251,    69,   442,   221,   459,   188,  -251,
     225,   476,   226,   257,   231,   234,   248,   249,    83,    83,
    -251,   241,  -251,   266,  -251,   695,    78,   315,   373,   373,
     120,   120,   120,   120,     4,     4,   222,   222,   222,  -251,
     184,   243,   265,   507,   260,  -251,  -251,    83,   288,  -251,
      28,  -251,    83,    83,   244,   245,  -251,   246,  -251,  -251,
     271,     2,  -251,   -22,    29,    30,   247,   250,   538,   332,
      83,   256,    98,  -251,   -46,  -251,   289,  -251,  -251,    83,
     695,   269,   251,    17,   363,   569,  -251,  -251,  -251,   252,
     299,   298,   276,  -251,  -251,     0,   304,  -251,   140,   282,
     147,   284,  -251,  -251,   255,  -251,   394,   317,  -251,   266,
    -251,   293,   600,  -251,    72,   262,   283,   320,   272,   251,
      83,   334,   271,   329,  -251,   359,  -251,  -251,  -251,    83,
     319,   321,    83,   322,   323,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,    72,  -251,  -251,   379,    25,  -251,   324,
     617,   325,  -251,  -251,   327,  -251,   648,  -251,  -251,   679,
    -251,  -251,  -251,  -251,  -251,   200,  -251,  -251,  -251,     2,
     357,   358,  -251,    25,   -46,     1,   330,   331,  -251,  -251,
    -251,  -251,  -251
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -251,  -251,  -251,  -251,  -251,   236,  -251,    19,  -251,  -251,
     -40,  -251,  -251,    -1,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,   278,  -197,  -251,   158,   -29,  -251,
    -251,  -250,  -251,   -86,  -251,   193,  -251,  -251,  -251,  -251,
    -251,   178,  -210,  -251,   135,  -251
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      13,    78,    90,    79,    80,   247,   238,   210,   210,   210,
     112,   138,   216,   142,    65,   139,    66,   284,    12,    11,
     236,    93,   117,   118,   159,   161,    15,   160,   236,    63,
      62,    64,    16,   202,   218,   220,   114,   115,   143,   237,
     217,   122,   269,   298,   125,   140,   127,   237,   113,   105,
     106,   107,    65,   131,    66,   211,   211,   211,   143,   143,
     143,    61,   246,    92,   300,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   119,
     111,   162,   234,   163,   203,   247,    18,    19,    77,    21,
      22,   166,   261,   262,   167,    93,     1,   173,   219,   221,
     174,     2,     3,     4,     5,     6,     7,     8,    27,   188,
     189,    69,    70,    30,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,    32,    93,    63,   228,
      64,    33,   229,    34,    71,    72,    73,    93,   200,   170,
     209,    74,    94,   204,   205,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,    75,    83,
      81,   226,    93,   103,   104,   105,   106,   107,   249,    76,
     232,   250,   108,    82,    84,   252,   129,    94,   253,   111,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   230,     2,     3,     4,     5,     6,     7,
       8,    85,   272,    86,    17,    87,    18,    19,    20,    21,
      22,   270,    88,     2,     3,     4,     5,     6,     7,     8,
     276,    23,    24,   279,    91,   121,    25,    26,    27,    28,
      29,   292,   123,    30,   293,   124,    31,   126,   128,    93,
     130,   133,   134,   135,   136,   137,    32,   141,   164,   171,
     178,    33,   176,    34,   168,    35,   179,    36,   181,    37,
      38,    39,    40,    41,   182,   184,    89,    12,   185,   191,
     197,   196,    17,   190,    18,    19,    20,    21,    22,   186,
     187,     2,     3,     4,     5,     6,     7,     8,   199,    23,
      24,   201,   231,   299,    25,    26,    27,    28,    29,   227,
     233,    30,   243,   244,    31,   242,   206,   207,   208,   222,
     245,   248,   223,   251,    32,   254,   234,   255,    93,    33,
     257,    34,   259,    35,   265,    36,   266,    37,    38,    39,
      40,    41,    93,    94,   268,    12,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,    93,
     267,   273,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   172,    94,   271,   210,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
      93,   277,   283,   278,   280,   281,   286,   288,   296,   297,
      93,   289,   301,   302,   225,    94,   195,   169,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,    93,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   282,   258,   275,   295,   240,    94,     0,     0,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   165,     0,   256,    94,     0,    93,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   175,    94,     0,    93,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     177,    94,     0,    93,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   180,    94,     0,
       0,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   198,     0,     0,    94,
       0,     0,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,    93,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   224,     0,     0,
      94,     0,     0,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   241,     0,
       0,    94,     0,     0,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,    93,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   260,
       0,     0,    94,     0,    93,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   287,    94,
       0,     0,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,    93,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   290,     0,     0,
      94,     0,     0,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   291,     0,
       0,    94,    93,     0,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,    94,     0,     0,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107
};

static const yytype_int16 yycheck[] =
{
       1,    30,    42,    32,    33,   215,   203,     7,     7,     7,
      28,    28,    34,     5,    28,    32,    30,   267,    64,     0,
       3,    17,     8,     9,    31,     5,     0,    34,     3,     5,
      62,     7,     5,     5,     5,     5,    65,    66,    30,    22,
      62,    70,   239,   293,    73,    62,    75,    22,    66,    45,
      46,    47,    28,    82,    30,    55,    55,    55,    30,    30,
      30,    30,    62,    44,    63,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,    65,
      61,    61,    65,   112,   170,   295,     3,     4,     5,     6,
       7,    31,    20,    21,    34,    17,     5,    28,   184,   185,
      31,    10,    11,    12,    13,    14,    15,    16,    25,   138,
     139,    30,    30,    30,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    43,    17,     5,    31,
       7,    48,    34,    50,     5,    30,    30,    17,   167,   120,
     180,    30,    32,   172,   173,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    30,     5,
      30,   190,    17,    43,    44,    45,    46,    47,    28,    54,
     199,    31,    62,    30,     5,    28,    31,    32,    31,   160,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,   194,    10,    11,    12,    13,    14,    15,
      16,    30,   242,    30,     1,    30,     3,     4,     5,     6,
       7,   240,    30,    10,    11,    12,    13,    14,    15,    16,
     249,    18,    19,   252,     5,     5,    23,    24,    25,    26,
      27,    31,    62,    30,    34,     5,    33,     5,     5,    17,
       5,    32,     5,     5,     5,     5,    43,     5,    54,    31,
      62,    48,    31,    50,    30,    52,    31,    54,    32,    56,
      57,    58,    59,    60,     7,    34,    63,    64,    34,     3,
       5,    28,     1,    32,     3,     4,     5,     6,     7,    31,
      31,    10,    11,    12,    13,    14,    15,    16,    28,    18,
      19,     3,     3,   294,    23,    24,    25,    26,    27,    43,
      31,    30,     3,     5,    33,    53,    62,    62,    62,    62,
      34,     7,    62,    31,    43,    31,    65,    62,    17,    48,
       3,    50,    29,    52,    62,    54,    43,    56,    57,    58,
      59,    60,    17,    32,    62,    64,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    17,
      30,    22,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    62,    32,    31,     7,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      17,    62,     3,    62,    62,    62,    62,    62,    31,    31,
      17,    64,    62,    62,    62,    32,   160,   119,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    17,    39,    40,    41,    42,    43,    44,    45,    46,
      47,   263,   229,   245,   289,    62,    32,    -1,    -1,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    62,    32,    -1,    17,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    31,    32,    -1,    17,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      31,    32,    -1,    17,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    31,    32,    -1,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    32,
      -1,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      32,    -1,    -1,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,
      -1,    32,    -1,    -1,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    -1,    32,    -1,    17,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    31,    32,
      -1,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      32,    -1,    -1,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,
      -1,    32,    17,    -1,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    32,    -1,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,    10,    11,    12,    13,    14,    15,    16,    68,
      69,    74,    64,    80,    81,     0,     5,     1,     3,     4,
       5,     6,     7,    18,    19,    23,    24,    25,    26,    27,
      30,    33,    43,    48,    50,    52,    54,    56,    57,    58,
      59,    60,    73,    74,    75,    76,    77,    78,    80,    82,
      83,    84,    85,    86,    87,    88,    89,    95,   103,   105,
     112,    30,    62,     5,     7,    28,    30,    90,    91,    30,
      30,     5,    30,    30,    30,    30,    54,     5,    95,    95,
      95,    30,    30,     5,     5,    30,    30,    30,    30,    63,
      77,     5,    74,    17,    32,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    62,    71,
      72,    74,    28,    66,    95,    95,    96,     8,     9,    65,
      97,     5,    95,    62,     5,    95,     5,    95,     5,    31,
       5,    95,   104,    32,     5,     5,     5,     5,    28,    32,
      62,     5,     5,    30,   100,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    31,
      34,     5,    61,    95,    54,    29,    31,    34,    30,    91,
      74,    31,    62,    28,    31,    31,    31,    31,    62,    31,
      31,    32,     7,   106,    34,    34,    31,    31,    95,    95,
      32,     3,   101,   102,    70,    72,    28,     5,    29,    28,
      95,     3,     5,   100,    95,    95,    62,    62,    62,    77,
       7,    55,   107,   108,   109,   111,    34,    62,     5,   100,
       5,   100,    62,    62,    29,    62,    95,    43,    31,    34,
      80,     3,    95,    31,    65,    92,     3,    22,    92,    98,
      62,    29,    53,     3,     5,    34,    62,   109,     7,    28,
      31,    31,    28,    31,    31,    62,    62,     3,   102,    29,
      29,    20,    21,    93,    94,    62,    43,    30,    62,    92,
      95,    31,    77,    22,   110,   108,    95,    62,    62,    95,
      62,    62,    94,     3,    98,    99,    62,    31,    62,    64,
      29,    29,    31,    34,    79,   111,    31,    31,    98,    80,
      63,    62,    62
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
#line 166 "src/q.ypp"
    {
		qscript_parser::project_name = (yyvsp[(1) - (2)].name);
		qscript_parser::tree_root=(yyvsp[(2) - (2)].c_stmt);
		while(qscript_parser::tree_root->prev_) {
			cerr << "This should never appear: climbing up the tree" << endl;
			qscript_parser::tree_root=qscript_parser::tree_root->prev_;
		}
	;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 174 "src/q.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 180 "src/q.ypp"
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
	;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 191 "src/q.ypp"
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
	;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 213 "src/q.ypp"
    {
		 (yyval.v_list)=(yyvsp[(1) - (1)].v_list);
		 //cout << "got decl_comma_list : " << endl;
	;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 217 "src/q.ypp"
    {
		(yyval.v_list)=qscript_parser::link_chain((yyvsp[(1) - (3)].v_list),(yyvsp[(3) - (3)].v_list));
		//cout << "chaining var_decl : " << endl;
	;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 223 "src/q.ypp"
    {
		(yyval.v_list)=new FunctionParameter((yyvsp[(1) - (2)].dt), (yyvsp[(2) - (2)].name));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, qscript_parser::line_no);
		}
		free((yyvsp[(2) - (2)].name));
	;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 230 "src/q.ypp"
    {
		/* Neil - I need to fix this */
		DataType dt=DataType(INT8_ARR_TYPE+((yyvsp[(1) - (5)].dt)-INT8_TYPE));
		(yyval.v_list)=new FunctionParameter(dt, (yyvsp[(2) - (5)].name), (yyvsp[(4) - (5)].ival));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, qscript_parser::line_no);
		}
		free((yyvsp[(2) - (5)].name));
	;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 239 "src/q.ypp"
    {
		DataType dt=DataType(INT8_REF_TYPE+((yyvsp[(1) - (3)].dt)-INT8_TYPE));
		(yyval.v_list)=new FunctionParameter(dt, (yyvsp[(3) - (3)].name));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, qscript_parser::line_no);
		}
		free((yyvsp[(3) - (3)].name));
	;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 248 "src/q.ypp"
    {
		(yyval.v_list)=0;
		;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 256 "src/q.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
		if(qscript_parser::flag_next_stmt_start_of_block){
			qscript_parser::blk_heads.push_back((yyvsp[(1) - (1)].stmt));
			qscript_parser::flag_next_stmt_start_of_block=false;
			qscript_parser::blk_start_flag.pop_back();
		}

	;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 265 "src/q.ypp"
    {
		(yyvsp[(1) - (2)].stmt)->next_=(yyvsp[(2) - (2)].stmt);
		(yyvsp[(2) - (2)].stmt)->prev_=(yyvsp[(1) - (2)].stmt);
		(yyval.stmt)=(yyvsp[(2) - (2)].stmt);
	;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 282 "src/q.ypp"
    {
		   (yyval.type_qual) = CONST_QUAL;
	;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 287 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (3)].name), (yyvsp[(1) - (3)].dt)/*, line_no*/);
	;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 290 "src/q.ypp"
    {
	;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 292 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (5)].name), (yyvsp[(1) - (5)].dt), (yyvsp[(4) - (5)].expr));
	;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 295 "src/q.ypp"
    {
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		DataType dt=DataType(INT8_ARR_TYPE+((yyvsp[(1) - (6)].dt)-INT8_TYPE));
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (6)].name), dt, (yyvsp[(4) - (6)].expr)/*, line_no*/);
	;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 310 "src/q.ypp"
    {
		(yyval.stmt) = (yyvsp[(1) - (1)].c_stmt);
	;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 321 "src/q.ypp"
    {
		fprintf (stderr, "continuing parse with errors around line_no: %d\n", qscript_parser::line_no);
		std::stringstream err_msg;
		err_msg << "continuing parsing"
			<< " file: " << qscript_parser::lex_location.fileName_
			<< " with errors around"
			<< " line: " << qscript_parser::lex_location.lineNo_
			<< " column: " << qscript_parser::lex_location.columnNo_ << std::endl;
		print_err(compiler_syntax_err
			, err_msg.str()
			, qscript_parser::lex_location.lineNo_, __LINE__, __FILE__);
		yyerrok;
		(yyval.stmt) = new ErrorStatement(qscript_parser::line_no);
	;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 338 "src/q.ypp"
    {
		++qscript_parser::flagIsAForBody_;
		qscript_parser::for_loop_max_counter_stack.push_back((yyvsp[(5) - (8)].expr));
	;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 341 "src/q.ypp"
    {
		using qscript_parser::line_no;
		(yyval.stmt) = new ForStatement(FOR_STMT, line_no, (yyvsp[(3) - (10)].expr), (yyvsp[(5) - (10)].expr), (yyvsp[(7) - (10)].expr), (yyvsp[(10) - (10)].c_stmt));

		--qscript_parser::flagIsAForBody_;
		qscript_parser::for_loop_max_counter_stack.pop_back();
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 353 "src/q.ypp"
    {
		(yyval.c_stmt) = qscript_parser::ProcessCompoundStatement((yyvsp[(1) - (3)].c_stmt), (yyvsp[(2) - (3)].stmt));
	;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 358 "src/q.ypp"
    {
		CompoundStatement * cmpdStmt = qscript_parser::ProcessOpenCurly();
		//qscript_parser::compound_body_stack.push_back(cmpdStmt);
		//cmpdStmt->nestedCompoundStatementStack_=qscript_parser::compound_body_stack;
		(yyval.c_stmt)=cmpdStmt;
	;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 368 "src/q.ypp"
    {
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		using qscript_parser::XTCC_DEBUG_MEM_USAGE;
		CompoundStatement * cmpd_stmt = dynamic_cast<CompoundStatement*>((yyvsp[(5) - (5)].stmt));
		if (cmpd_stmt!=0) {
			cmpd_stmt->flagIsAIfBody_ = 1;
			(yyval.stmt)=new IfStatement(IFE_STMT,if_line_no,(yyvsp[(3) - (5)].expr),cmpd_stmt,0);
		} else 
			(yyval.stmt)=new IfStatement(IFE_STMT,if_line_no,(yyvsp[(3) - (5)].expr),(yyvsp[(5) - (5)].stmt),0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 383 "src/q.ypp"
    {
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		CompoundStatement * cmpd_stmt_if_body = dynamic_cast<CompoundStatement*>((yyvsp[(5) - (7)].stmt));
		if (cmpd_stmt_if_body) {
			cmpd_stmt_if_body->flagIsAIfBody_ = 1;
		}
		CompoundStatement * cmpd_stmt_else_body = dynamic_cast<CompoundStatement*>((yyvsp[(7) - (7)].stmt));
		if (cmpd_stmt_else_body) {
			cmpd_stmt_else_body->flagIsAIfBody_ = 1;
		}
		if (cmpd_stmt_if_body==0 && cmpd_stmt_else_body==0)
			(yyval.stmt)=new IfStatement(IFE_STMT,qscript_parser::if_line_no,(yyvsp[(3) - (7)].expr),(yyvsp[(5) - (7)].stmt),(yyvsp[(7) - (7)].stmt));
		else if (cmpd_stmt_if_body != 0 && cmpd_stmt_else_body !=0 ) 
			(yyval.stmt)=new IfStatement(IFE_STMT,qscript_parser::if_line_no,(yyvsp[(3) - (7)].expr),cmpd_stmt_if_body,cmpd_stmt_else_body);
		else if (cmpd_stmt_else_body !=0 && cmpd_stmt_if_body==0) 
			(yyval.stmt)=new IfStatement(IFE_STMT,qscript_parser::if_line_no,(yyvsp[(3) - (7)].expr),(yyvsp[(5) - (7)].stmt),cmpd_stmt_else_body);
		else 
			(yyval.stmt)=new IfStatement(IFE_STMT,qscript_parser::if_line_no,(yyvsp[(3) - (7)].expr),cmpd_stmt_if_body,(yyvsp[(7) - (7)].stmt));

		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, qscript_parser::line_no);
		}
	;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 412 "src/q.ypp"
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
	;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 430 "src/q.ypp"
    {
		(yyval.stmt) = new GotoStatement(GOTO_STMT, qscript_parser::line_no, (yyvsp[(2) - (3)].name));
		// free($2); ? is this required here
	;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 435 "src/q.ypp"
    {
		// free($3); ? is this required here
		(yyval.stmt) = new ClearStatement(CLEAR_STMT, qscript_parser::line_no, (yyvsp[(3) - (5)].name));
	;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 439 "src/q.ypp"
    {
		(yyval.stmt) = new ClearStatement(CLEAR_STMT, qscript_parser::line_no, (yyvsp[(3) - (8)].name), (yyvsp[(5) - (8)].expr));
		// free($3); ? is this required here
	;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 445 "src/q.ypp"
    {
		(yyval.stmt) = new ColumnStatement(COLUMN_STMT, qscript_parser::line_no, (yyvsp[(3) - (5)].expr));
	;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 450 "src/q.ypp"
    {
		(yyval.stmt) = new NewCardStatement(COLUMN_STMT, qscript_parser::line_no, (yyvsp[(3) - (5)].expr));
	;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 455 "src/q.ypp"
    {
               (yyval.stmt) = new RandomizeStatement (RANDOMIZE_STMT, qscript_parser::line_no, string((yyvsp[(3) - (4)].name)));
       ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 460 "src/q.ypp"
    {
		// Warning : xs is a global variable that is used here
		//$$ = qscript_parser::ProcessRangeQuestion($1, $2, $4);
		(yyval.stmt) = qscript_parser::ProcessRangeQuestion((yyvsp[(1) - (7)].name), "dummy question text", (yyvsp[(4) - (7)].dt));
		//cout << "parsed range question : " << $1 << endl;
		question_attributes.Reset();
		using qscript_parser::xs;
		xs.reset();
		std::stringstream mesg;
		mesg << "fix memory leak problem introduced at this point";
		LOG_MAINTAINER_MESSAGE(mesg.str());
		// huge memory leak 
		text_expr_vec.clear();
	;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 474 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::ProcessRangeQuestion((yyvsp[(1) - (8)].name), "dummy question text" , (yyvsp[(4) - (8)].dt));
		//cout << "parsed range question : " << $1 << endl;
		question_attributes.Reset();
		qscript_parser::has_mutex_range = false;
		using qscript_parser::xs;
		xs.reset();
		std::stringstream mesg;
		mesg << "fix memory leak problem introduced at this point";
		LOG_MAINTAINER_MESSAGE(mesg.str());
		// huge memory leak 
		text_expr_vec.clear();
	;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 487 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::ProcessNamedQuestion((yyvsp[(1) - (7)].name), "dummy question text", (yyvsp[(4) - (7)].dt), (yyvsp[(5) - (7)].name));
		//cout << "parsed named question : " << $1 << endl;
		question_attributes.Reset();
		std::stringstream mesg;
		mesg << "fix memory leak problem introduced at this point";
		LOG_MAINTAINER_MESSAGE(mesg.str());
		// huge memory leak 
		text_expr_vec.clear();
	;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 503 "src/q.ypp"
    {
		text_expr_vec.push_back (new TextExpression(string((yyvsp[(1) - (1)].text_buf))));
	;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 506 "src/q.ypp"
    {
		string name ((yyvsp[(1) - (4)].name));
		map<string,SymbolTableEntry*>::iterator sym_it = find_in_symtab(name);

		if ( sym_it  == qscript_parser::active_scope->SymbolTable.end() ){
			std::stringstream err_mesg;
			err_mesg << "symbol: " << name << " not found in symbol table. It should be a named_attribute list";
			print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			SymbolTableEntry * se = sym_it->second;
			if (se->type_ == NAMED_ATTRIBUTE_TYPE) {
				text_expr_vec.push_back (new TextExpression(new Unary2Expression (oper_arrderef, (yyvsp[(1) - (4)].name), (yyvsp[(3) - (4)].expr))));
			} else {
				std::stringstream err_mesg;
				err_mesg << "symbol: " << name << " should be a named_attribute or a question";
				print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
			}
		}
	;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 525 "src/q.ypp"
    {

		string name ((yyvsp[(1) - (6)].name));
		map<string,SymbolTableEntry*>::iterator sym_it = find_in_symtab(name);
		if ( sym_it  == qscript_parser::active_scope->SymbolTable.end() ){
			std::stringstream err_mesg;
			err_mesg << "symbol: " << name << " not found in symbol table. It should be a named_attribute list";
			print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			SymbolTableEntry * se = sym_it->second;
			if (se->type_ == QUESTION_TYPE) {
				text_expr_vec.push_back (new TextExpression(se->question_, (yyvsp[(5) - (6)].expr)) );
				std::stringstream err_mesg;
				//err_mesg << "symbol: " << name << " question - unhandled case";
				//print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
			} else {
				std::stringstream err_mesg;
				err_mesg << "symbol: " << name << " should be a named_attribute or a question";
				print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
			}
		}

	;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 548 "src/q.ypp"
    {

		string name ((yyvsp[(1) - (1)].name));
		map<string,SymbolTableEntry*>::iterator sym_it = find_in_symtab(name);
		if ( sym_it  == qscript_parser::active_scope->SymbolTable.end() ){
			std::stringstream err_mesg;
			err_mesg << "symbol: " << name << " not found in symbol table. It should be a named_attribute list";
			print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			SymbolTableEntry * se = sym_it->second;
			if (se->type_ == QUESTION_TYPE) {
				text_expr_vec.push_back (new TextExpression (se->question_));
				std::stringstream err_mesg;
				//err_mesg << "symbol: " << name << " question - unhandled case";
				//print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
			} else {
				std::stringstream err_mesg;
				err_mesg << "symbol: " << name << " should be a named_attribute or a question";
				print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
			}
		}
	;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 581 "src/q.ypp"
    {
		question_attributes.setHidden();
	;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 584 "src/q.ypp"
    {
		question_attributes.setAllowBlank();
	;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 590 "src/q.ypp"
    {
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		using qscript_parser::mem_addr;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_plus);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 599 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_minus);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 608 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_mult);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 617 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_div);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 626 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_mod);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 635 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr) = new UnaryExpression((yyvsp[(2) - (2)].expr), oper_umin);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 644 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_lt);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 653 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_gt);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 662 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_le);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 671 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_ge);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 680 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_iseq);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 689 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_isneq);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 698 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_or);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 707 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_and);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 716 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr) = new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_assgn);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 725 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr) = new UnaryExpression((yyvsp[(2) - (2)].expr), oper_not);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 734 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr) = new Unary2Expression((yyvsp[(1) - (1)].ival));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 743 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		(yyval.expr) = new Unary2Expression((yyvsp[(1) - (1)].dval));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 751 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		(yyval.expr) = new Unary2Expression((yyvsp[(1) - (1)].name), oper_name );
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 759 "src/q.ypp"
    {
		using qscript_parser::line_no;
		using qscript_parser::mem_addr;
		(yyval.expr) = new Unary2Expression(oper_arrderef, (yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].expr));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 767 "src/q.ypp"
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
		int32_t index=search_for_func(search_for);
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
	;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 821 "src/q.ypp"
    {
		using qscript_parser::line_no;
		(yyval.expr) = new Unary2Expression(strdup((yyvsp[(1) - (1)].text_buf)), oper_text_expr);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 828 "src/q.ypp"
    {
		using qscript_parser::line_no;
		(yyval.expr) = new UnaryExpression((yyvsp[(2) - (3)].expr), oper_parexp );
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 835 "src/q.ypp"
    {
		using qscript_parser::xs;
		using qscript_parser::line_no;
		(yyval.expr) = new Binary2Expression((yyvsp[(1) - (3)].expr), xs, oper_in);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		xs.reset();
	;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 844 "src/q.ypp"
    {
		(yyval.expr) = new Unary2Expression((yyvsp[(3) - (4)].name), oper_to_string);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 850 "src/q.ypp"
    {
		(yyval.expr) = new Binary2Expression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].name), oper_in);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 856 "src/q.ypp"
    {
		(yyval.expr) = new Unary2Expression ((yyvsp[(3) - (4)].name), oper_isanswered);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 862 "src/q.ypp"
    {
		(yyval.expr) = new Unary2Expression ((yyvsp[(3) - (4)].name), oper_count);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 880 "src/q.ypp"
    { (yyval.expr)=(yyvsp[(1) - (1)].expr); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 881 "src/q.ypp"
    {
		(yyval.expr)=qscript_parser::link_chain((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));
	;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 886 "src/q.ypp"
    { 
	       qscript_parser::q_type = spn; 
	       // we need this =1 when generating
	       // code for flat file creation
		qscript_parser::no_mpn = 1;
       ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 892 "src/q.ypp"
    { qscript_parser::q_type = mpn;
		qscript_parser::no_mpn = (yyvsp[(3) - (4)].ival);
	;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 897 "src/q.ypp"
    { 
		     qscript_parser::has_mutex_range = true;
	     ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 907 "src/q.ypp"
    {
		using qscript_parser::line_no;
		if((yyvsp[(3) - (3)].ival)<=(yyvsp[(1) - (3)].ival)){
			print_err(compiler_sem_err
					, "2nd number in range <= 1st number",
					line_no, __LINE__, __FILE__  );

		} else {
			qscript_parser:: mutex_range_set.add_range ( (yyvsp[(1) - (3)].ival),(yyvsp[(3) - (3)].ival));
		}
	;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 918 "src/q.ypp"
    {
		qscript_parser::mutex_range_set.add_indiv((yyvsp[(1) - (1)].ival));
	;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 924 "src/q.ypp"
    { ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 932 "src/q.ypp"
    {
		using qscript_parser::line_no;
		if((yyvsp[(3) - (3)].ival)<=(yyvsp[(1) - (3)].ival)){
			print_err(compiler_sem_err
					, "2nd number in range <= 1st number",
					line_no, __LINE__, __FILE__  );

		} else {
			//qscript_parser:: xs.range.push_back( pair<int32_t,int32_t>($1,$3));
			qscript_parser:: xs.add_range ( (yyvsp[(1) - (3)].ival),(yyvsp[(3) - (3)].ival));
		}
	;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 944 "src/q.ypp"
    {
		//qscript_parser::xs.indiv.insert($1);
		qscript_parser::xs.add_indiv((yyvsp[(1) - (1)].ival));
	;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 950 "src/q.ypp"
    {
		using qscript_parser:: stub_list;
		using qscript_parser:: named_stubs_list;
		stub_list.resize (0);
		stub_number.push_back (0);
		qscript_parser::map_duplicate_stub_entry_check.clear();
		qscript_parser::set_duplicate_stub_entry_check.clear();
	;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 957 "src/q.ypp"
    {
		using qscript_parser::line_no;
		using qscript_parser:: stub_list;
		using qscript_parser:: named_stubs_list;
		//cout <<"got attribute_list size: " << attribute_list.size() << endl;
		string stub_name=(yyvsp[(2) - (6)].name);
		NamedRangeGroup * nrg = new NamedRangeGroup(line_no,
					stub_name, stub_number.back());
		//$$=0;
		//$$ = nr_ptr;

		// ==========
		AbstractNamedRange * nr_ptr = (yyvsp[(5) - (6)].nr_ptr);
		//cout << "climbing up the chain" << endl;
		while (nr_ptr->prev_nr) {
			//cout << "." ;
			nr_ptr = nr_ptr->prev_nr;
		}
		//cout << endl;
		nrg->groupPtr_ = nr_ptr;
		(yyval.stmt) = nrg;

		//int highest_stub_number_in_group = stub_number.back() ;
		 
		//cout << "stub_number.size(): "  << stub_number.size()
		//	<< endl;
		stub_number.pop_back(); 
		//cout << "highest_stub_number_in_group: " 
		//	<< $2 << ": " 
		//	<< highest_stub_number_in_group
		//	<< endl;
		if (stub_number.size() != 0) {
			cerr << "Error in parsing assumptions: stub_number.size should be 0 at this point"
				<< endl;
		}
		named_stubs_list.push_back(nrg);
	;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 996 "src/q.ypp"
    {
		//$$ = new named_attribute_list (NAMED_ATTRIBUTE_TYPE, $2, vec_named_attribute_list);
		//qscript_parser::delete_manually_in_cleanup.push_back(
		(yyval.stmt) = qscript_parser::active_scope_list[0]->insert((yyvsp[(2) - (5)].name), NAMED_ATTRIBUTE_TYPE, qscript_parser::line_no, vec_named_attribute_list);
		//);
		vec_named_attribute_list.clear();
	;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1005 "src/q.ypp"
    {
		vec_named_attribute_list.push_back ((yyvsp[(1) - (1)].text_buf));
	;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1008 "src/q.ypp"
    {
		vec_named_attribute_list.push_back ((yyvsp[(3) - (3)].text_buf));
	;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1018 "src/q.ypp"
    {
		using qscript_parser::stub_list;
		string s1=(yyvsp[(1) - (2)].text_buf);
		int32_t code=(yyvsp[(2) - (2)].ival);
		++stub_number[stub_number.size()-1];
		struct stub_pair pair1 (s1, code, stub_number.back());
		stub_list.push_back (pair1);

		/*
		map <string,int>::iterator map_iter = map_duplicate_stub_entry_check.find(s1);
		//cout << "searching for : " << s1 << " in map" << endl;
		if (map_iter != map_duplicate_stub_entry_check.end()) {
			std::stringstream err_msg;
			err_msg << "the stub text: \"" << s1
				<< "\" with code: " << code
				<< " already exists with a code value of : "
				<< map_iter->second;
			print_err(compiler_syntax_err, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			map_duplicate_stub_entry_check[s1] = code;
		}
		*/
		qscript_parser::check_duplicate_stub_entry (s1, code);

		/*
		set<int>::iterator set_iter = set_duplicate_stub_entry_check.find (code);
		if (set_iter != set_duplicate_stub_entry_check.end()) {
			std::stringstream err_msg;
			err_msg << "the code: " << code
				<< " already exists in the stub list: ";
			print_err(compiler_syntax_err, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			set_duplicate_stub_entry_check.insert(code);
		}
		*/
		qscript_parser::check_duplicate_code_entry (code);

	;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1056 "src/q.ypp"
    {
		using qscript_parser::stub_list;
		string s1=(yyvsp[(1) - (3)].text_buf);
		int32_t code=(yyvsp[(2) - (3)].ival);
		++stub_number[stub_number.size()-1];
		struct stub_pair pair1 (s1, code, true, stub_number.back());
		stub_list.push_back(pair1);

		
		qscript_parser::check_duplicate_stub_entry (s1, code);
		//map <string,int>::iterator map_iter = qscript_parser::map_duplicate_stub_entry_check.find(s1);
		//cout << "searching for : " << s1 << " in map" << endl;
		//if (map_iter != map_duplicate_stub_entry_check.end()) {
		//	std::stringstream err_msg;
		//	err_msg << "the stub text: \"" << s1
		//		<< "\" with code: " << code
		//		<< " already exists with a code value of : "
		//		<< map_iter->second;
		//	print_err(compiler_syntax_err, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		//} else {
		//	map_duplicate_stub_entry_check[s1] = code;
		//}

		qscript_parser::check_duplicate_code_entry (code);
		//set<int>::iterator set_iter = set_duplicate_stub_entry_check.find (code);
		//if (set_iter != set_duplicate_stub_entry_check.end()) {
		//	std::stringstream err_msg;
		//	err_msg << "the code: " << code
		//		<< " already exists in the stub list";
		//	print_err(compiler_syntax_err, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		//} else {
		//	set_duplicate_stub_entry_check.insert(code);
		//}
	;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1093 "src/q.ypp"
    {
		NamedRangeList * nrl = new NamedRangeList (qscript_parser::line_no);
		nrl->stubs = qscript_parser::stub_list;
		qscript_parser::stub_list.clear();
		(yyval.nr_ptr) = nrl;
	;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1099 "src/q.ypp"
    { ++stub_number[stub_number.size()-1]; stub_number.push_back(0); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1099 "src/q.ypp"
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
		//cout << "climbing up the chain" << endl;
		while (nr_ptr->prev_nr) {
			//cout << "." ;
			nr_ptr = nr_ptr->prev_nr;
		}
		//cout << endl;

		NamedRangeGroup * nrg = new NamedRangeGroup (qscript_parser::line_no, (yyvsp[(2) - (6)].name), stub_number[stub_number.size()-2]);
		nrg->groupPtr_ = nr_ptr;
		(yyval.nr_ptr) = nrg;
		//int highest_stub_number_in_group = stub_number.back() ;
		 
		stub_number.pop_back(); 
		//cout << "highest_stub_number_in_group: " 
		//	<< $2 << ": " 
		//	<< highest_stub_number_in_group
		//	<< endl
	;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1138 "src/q.ypp"
    {
		(yyvsp[(1) - (2)].nr_ptr)->next_nr = (yyvsp[(2) - (2)].nr_ptr);
		(yyvsp[(2) - (2)].nr_ptr)->prev_nr = (yyvsp[(1) - (2)].nr_ptr);
		(yyval.nr_ptr) = (yyvsp[(2) - (2)].nr_ptr);
	;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1146 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_DEL
				, (yyvsp[(3) - (7)].name), (yyvsp[(5) - (7)].name));
	;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1150 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_DEL
				, (yyvsp[(3) - (10)].name), (yyvsp[(5) - (10)].name), (yyvsp[(7) - (10)].expr));
	;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1154 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (7)].name), (yyvsp[(5) - (7)].name));
	;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1158 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (10)].name), (yyvsp[(5) - (10)].name), (yyvsp[(7) - (10)].expr));
	;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1162 "src/q.ypp"
    {
		using qscript_parser::xs;
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (7)].name), xs);
		xs.reset();
	;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1168 "src/q.ypp"
    {
		using qscript_parser::xs;
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_DEL
				, (yyvsp[(3) - (7)].name), xs);
		using qscript_parser::xs;
		xs.reset();
	;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1175 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt_set_unset( STUB_MANIP_UNSET_ALL, (yyvsp[(3) - (5)].name));
	;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1178 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt_set_unset( STUB_MANIP_SET_ALL, (yyvsp[(3) - (5)].name));
	;}
    break;



/* Line 1455 of yacc.c  */
#line 3248 "src/q.cpp"
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
#line 1186 "src/q.ypp"



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
AbstractExpression * recurse_for_index(int32_t stack_index){
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
			flagIsAForBody_, for_loop_max_counter_stack);
	stack_cmpd_stmt.push_back(cmpdStmt);
	cmpdStmt->nestedCompoundStatementStack_=stack_cmpd_stmt;
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
	flag_next_question_start_of_block = true;
	blk_start_flag.push_back(flag_next_stmt_start_of_block);
	blk_question_start_flag.push_back(flag_next_question_start_of_block);
	active_scope_list.push_back(cmpdStmt->scope_);
	active_scope = cmpdStmt->scope_;
	return cmpdStmt;
}

CompoundStatement* ProcessCompoundStatement(CompoundStatement* cmpdStmt,
		AbstractStatement *stmt)
{

	active_scope_list.pop_back();
	int32_t tmp=active_scope_list.size()-1;
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
	if(blk_start_flag.size() > 0) {
		flag_next_stmt_start_of_block = blk_start_flag[blk_start_flag.size()-1];
	}
	if (blk_question_start_flag.size()>0) {
		//flag_next_question_start_of_block = blk_question_start_flag[blk_question_start_flag.size()-1];
		blk_question_start_flag.pop_back();
		flag_next_question_start_of_block = blk_question_start_flag.back();
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

// NxD: 10-Jun-2010
// Need to make changes here - create a new struct to store variable name and type
// and dump the entire scope into the map
// later the question::GenerateCode will
// decide by looking if it is an array question or a simple
// question and generate the appropriate save restore scope code
AbstractStatement * ProcessRangeQuestion(const string &name
		, const string & q_text, const DataType& dt )
{

	//vector<string> active_push_vars;
	//vector<string> active_pop_vars;
	//for(unsigned int32_t i=0; i< active_scope_list.size(); ++i){
	//	Scope* sc_ptr= active_scope_list[i];
	//	sc_ptr->print_scope(name, active_push_vars, active_pop_vars);
	//}
	//string q_push_name = name + "_push";
	//string q_pop_name = name + "_pop";
	//map_of_active_vars_for_questions[q_push_name] = active_push_vars;
	//map_of_active_vars_for_questions[q_pop_name] = active_pop_vars;
	vector <ActiveVariableInfo* > av_info;
	PrintActiveVariablesAtScope(active_scope_list, av_info);


	AbstractExpression * arr_sz=0;
	RangeQuestion * q=0;
	if(stack_cmpd_stmt.size()==0){
		print_err(compiler_internal_error
			, "compound statement stack is 0 when parsing"
			"a question... exiting",
				line_no, __LINE__, __FILE__  );
		exit(1);
	}
	CompoundStatement * cmpd_stmt_ptr=stack_cmpd_stmt.back();
	if(qscript_parser::flagIsAForBody_){
		//cout << "flagIsAForBody_: "
		//	<< qscript_parser::flagIsAForBody_ << endl;
		arr_sz = qscript_parser::recurse_for_index(
			qscript_parser::for_loop_max_counter_stack.size()-1);
		q= new RangeQuestion(QUESTION_ARR_TYPE, line_no,
			name, ::text_expr_vec, q_type, no_mpn, dt, xs
			//, arr_sz
			, qscript_parser::for_loop_max_counter_stack
			, cmpd_stmt_ptr, av_info, question_attributes, mutex_range_set
			);
		qscript_parser::delete_manually_in_cleanup.push_back(
			active_scope_list[0]->insert(name.c_str(), QUESTION_ARR_TYPE, q));
		//ostringstream s1, s2;
		//arr_sz->print_expr(s1, s2);
		//cerr << "s1: " << s1.str() << ", s2: " << s2.str() << endl;
	} else {
		q= new RangeQuestion(QUESTION_TYPE, line_no,
			name, ::text_expr_vec, q_type, no_mpn, dt, xs, cmpd_stmt_ptr, av_info
			, question_attributes, mutex_range_set
			);
		qscript_parser::delete_manually_in_cleanup.push_back(
			active_scope_list[0]->insert(name.c_str(), QUESTION_TYPE, q));
	}
	++(cmpd_stmt_ptr->counterContainsQuestions_);
	//$$=q;

	question_list.push_back(q);
	/*
	cout << "question_list: questions are " << endl;
	for(int32_t i=0; i<question_list.size(); ++i){
		cout << question_list[i]->questionName_ << endl;
	}
	*/
	xs.reset();
	mutex_range_set.reset();
	// questions always get pushed in Scope level 0 as they
	// are global variables - no matter what the level of nesting
	// I need to modify the insert in Scope to
	// take a 3rd parameter which is a AbstractQuestion *
	// and store that into the symbol table
	// I should be able to retrieve that
	// AbstractQuestion* pointer later
	if (flag_next_question_start_of_block) {
		q->isStartOfBlock_ = true;
		flag_next_question_start_of_block = false;
		blk_question_start_flag[blk_question_start_flag.size()-1] = false;
		//cout << "blk_question_start_flag.size(): " << blk_question_start_flag.size() << endl;
		//cout << "At question: " << name << ", resetting flag_next_question_start_of_block = false " << endl;
		//cout << " blk_question_start_flag looks like this: " << endl;
		//for (int i=0; i<blk_question_start_flag.size(); ++i) {
		//	cout << " " <<blk_question_start_flag[i] ;
		//}
		//cout << endl;
	}
	
	return q;
}

AbstractStatement * ProcessNamedQuestion(const string &name
			, const string & q_txt , const DataType& dt
			, const string & attribute_list_name )
{

	// This is preparatory work
	// for jumping between questions
	// store
	//vector<string> active_push_vars;
	//vector<string> active_pop_vars;
	//for(unsigned int32_t i=0; i< active_scope_list.size(); ++i){
	//	Scope* sc_ptr= active_scope_list[i];
	//	sc_ptr->print_scope(name, active_push_vars, active_pop_vars);
	//}
	//string q_push_name = name + "_push";
	//string q_pop_name = name + "_pop";
	//map_of_active_vars_for_questions[q_push_name] = active_push_vars;
	//map_of_active_vars_for_questions[q_pop_name] = active_pop_vars;
	vector <ActiveVariableInfo* > av_info;
	PrintActiveVariablesAtScope(active_scope_list, av_info);

	bool found=false;
	struct NamedRangeGroup* nrg_ptr = 0;
	for(uint32_t i=0; i<named_stubs_list.size(); ++i) {
		nrg_ptr = named_stubs_list[i];
		if (nrg_ptr->groupName_ == attribute_list_name) {
			found=true; break;
		}
	}
	if (! found) {
		print_err(compiler_sem_err, string("named_stubs_list ")
			+ attribute_list_name + string(" not found \n"), line_no,
			__LINE__, __FILE__);
	}

	if (stack_cmpd_stmt.size()==0) {
		print_err(compiler_internal_error, "compound statement stack "
			"is 0 when parsing a AbstractQuestion... exiting"
			, line_no, __LINE__, __FILE__  );
		exit(1);
	}
	CompoundStatement * cmpd_stmt_ptr=stack_cmpd_stmt.back();
	AbstractExpression * arr_sz=0;
	NamedStubQuestion* q=0;
	if(qscript_parser::flagIsAForBody_){
		//cout << "flagIsAForBody_: "
		//	<< qscript_parser::flagIsAForBody_ << endl;
		arr_sz = qscript_parser::recurse_for_index(
			qscript_parser::for_loop_max_counter_stack.size()-1);
		q=new NamedStubQuestion(QUESTION_ARR_TYPE, line_no
				, name, ::text_expr_vec, q_type, no_mpn, dt , nrg_ptr
				,qscript_parser::for_loop_max_counter_stack
				, cmpd_stmt_ptr, av_info, question_attributes);
		qscript_parser::delete_manually_in_cleanup.push_back(
			active_scope_list[0]->insert(name.c_str(), QUESTION_ARR_TYPE, q));
	} else {
		q = new NamedStubQuestion(QUESTION_TYPE,
			line_no, name, ::text_expr_vec, q_type, no_mpn, dt, nrg_ptr
			, cmpd_stmt_ptr, av_info, question_attributes);
		qscript_parser::delete_manually_in_cleanup.push_back(
				active_scope_list[0]->insert(name.c_str(), QUESTION_TYPE, q));
	}
	question_list.push_back(q);
	//$$=q;
	++(cmpd_stmt_ptr->counterContainsQuestions_);

	if (flag_next_question_start_of_block) {
		q->isStartOfBlock_ = true;
		flag_next_question_start_of_block = false;
		//blk_question_start_flag[blk_question_start_flag.size()-1] = false;
		//cout << "blk_question_start_flag.size(): " << blk_question_start_flag.size() << endl;
		//cout << "At question: " << name << ", resetting flag_next_question_start_of_block = false " << endl;
		//cout << " blk_question_start_flag looks like this: " << endl;
		//for (int i=0; i<blk_question_start_flag.size(); ++i) {
		//	cout << " " <<blk_question_start_flag[i] ;
		//}
		//cout << endl;
	}

	return q;
}


// Close namespace
}

