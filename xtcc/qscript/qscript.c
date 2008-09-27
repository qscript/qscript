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
     STRING_T = 272,
     LOGOR = 273,
     LOGAND = 274,
     NOEQ = 275,
     ISEQ = 276,
     GEQ = 277,
     LEQ = 278,
     NOT = 279,
     UMINUS = 280,
     COUNT = 281,
     IN = 282,
     FUNC_CALL = 283,
     CONTINUE = 284,
     BREAK = 285,
     TEXT = 286,
     ATTRIBUTE_LIST = 287,
     STUBS_LIST = 288
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
#define STRING_T 272
#define LOGOR 273
#define LOGAND 274
#define NOEQ 275
#define ISEQ 276
#define GEQ 277
#define LEQ 278
#define NOT 279
#define UMINUS 280
#define COUNT 281
#define IN 282
#define FUNC_CALL 283
#define CONTINUE 284
#define BREAK 285
#define TEXT 286
#define ATTRIBUTE_LIST 287
#define STUBS_LIST 288




/* Copy the first part of user declarations.  */
#line 25 "qscript.y"

#include <iostream>
#include "const_defs.h"
//#include "qscript_types.h"
#include "../xtcc/trunk/symtab.h"
#include "../xtcc/trunk/expr.h" 
#include "q_expr.h" 
#include "range_set.h"
#include "stub_pair.h"
#include "named_range.h"
#include "question.h"

	question_type q_type;
	int no_mpn=0;
	using std::cout;
	using std::endl;
	vector <scope*> active_scope_list;
	scope* active_scope;
	extern char * yytext;
	int no_errors=0;
	int no_warn=0;
	extern int line_no;
	int yylex();
	void yyerror(char * s);
	const bool XTCC_DEBUG_MEM_USAGE=1;
	bool skip_func_type_check(const char * fname);
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);
	int check_parameters(struct expr* e, struct var_list* v);
	extern int if_line_no;
	int nest_lev=0;
	int flag_cmpd_stmt_is_a_func_body=-1;
	bool flag_next_stmt_start_of_block=false;
	vector<bool> blk_start_flag;
	vector <stmt*> blk_heads;

	char default_work_dir[]="xtcc_work";
	char * work_dir=default_work_dir;
        range_data r_data;
        vector <string> attribute_list;
	vector <named_range> named_stubs_list;
        vector <stub_pair> stub_list;


	noun_list_type noun_list[]= {
			{	"void"	, VOID_TYPE},
			{	"int8_t" ,INT8_TYPE},
			{	"int16_t" ,INT16_TYPE},
			{	"int32_t" ,INT32_TYPE},
			{	"float", FLOAT_TYPE},
			{	"double", DOUBLE_TYPE}
		};
	vector<mem_addr_tab>  mem_addr;
#include <vector>
	using std::vector;
#include <fstream>
#include <map>
	fstream debug_log_file("xtcc_debug.log", ios_base::out|ios_base::trunc);
	map<string, symtab_ent*>::iterator find_in_symtab(string id);
	void print_err(compiler_err_category cmp_err, string err_msg, 
		int line_no, int compiler_line_no, string compiler_file_name);
#include "../xtcc/trunk/stmt.h"
	vector <func_info*> func_info_table;


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
/* Line 187 of yacc.c.  */
#line 239 "qscript.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 252 "qscript.c"

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
#define YYFINAL  43
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   326

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNRULES -- Number of states.  */
#define YYNSTATES  142

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    36,     2,     2,
      20,    21,    34,    33,    23,    32,     2,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    47,
      28,    22,    29,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    18,     2,    19,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,    48,     2,     2,     2,     2,
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
      15,    16,    17,    24,    25,    26,    27,    30,    31,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    15,    21,    29,
      31,    33,    35,    37,    41,    47,    54,    58,    60,    67,
      74,    76,    81,    83,    85,    87,    89,    91,    93,    97,
      99,   103,   107,   109,   113,   117,   121,   125,   129,   132,
     136,   140,   144,   148,   152,   156,   160,   164,   168,   171,
     173,   175,   177,   182,   189,   194,   196,   200,   202,   206,
     213,   218,   220,   224,   227,   231,   232,   239,   240,   247,
     250
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      51,     0,    -1,    52,    -1,    53,    -1,    52,    53,    -1,
      57,    -1,    63,    47,    -1,     3,    20,    63,    21,    53,
      -1,     3,    20,    63,    21,    53,     4,    53,    -1,    55,
      -1,    54,    -1,    69,    -1,    67,    -1,    59,     7,    47,
      -1,    59,     7,    22,    63,    47,    -1,    59,     7,    18,
      63,    19,    47,    -1,    56,    52,    48,    -1,    49,    -1,
       7,    44,    58,    59,    60,    47,    -1,     7,    44,    58,
      59,     7,    47,    -1,     9,    -1,    10,    20,     6,    21,
      -1,    12,    -1,    13,    -1,    14,    -1,    15,    -1,    16,
      -1,    17,    -1,    20,    61,    21,    -1,    62,    -1,    61,
      23,    62,    -1,     6,    32,     6,    -1,     6,    -1,    63,
      33,    63,    -1,    63,    32,    63,    -1,    63,    34,    63,
      -1,    63,    35,    63,    -1,    63,    36,    63,    -1,    32,
      63,    -1,    63,    28,    63,    -1,    63,    29,    63,    -1,
      63,    31,    63,    -1,    63,    30,    63,    -1,    63,    27,
      63,    -1,    63,    26,    63,    -1,    63,    24,    63,    -1,
      63,    25,    63,    -1,    63,    22,    63,    -1,    37,    63,
      -1,     6,    -1,     5,    -1,     7,    -1,     7,    18,    63,
      19,    -1,     7,    18,    63,    23,    63,    19,    -1,     7,
      20,    65,    21,    -1,    44,    -1,    20,    63,    21,    -1,
      64,    -1,     7,    40,    60,    -1,     7,    18,    63,    19,
      40,    60,    -1,    39,    20,     7,    21,    -1,    63,    -1,
      65,    23,    63,    -1,    44,    47,    -1,    66,    44,    47,
      -1,    -1,    45,     7,    22,    68,    66,    47,    -1,    -1,
      46,     7,    70,    22,    71,    47,    -1,    44,     6,    -1,
      71,    44,     6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   157,   157,   160,   171,   176,   177,   190,   196,   202,
     205,   208,   211,   216,   220,   223,   231,   261,   284,   291,
     302,   303,   306,   307,   308,   309,   310,   311,   314,   317,
     318,   321,   338,   350,   356,   362,   368,   374,   380,   386,
     392,   398,   404,   410,   416,   422,   428,   436,   442,   448,
     455,   461,   467,   474,   481,   520,   526,   544,   549,   554,
     559,   565,   566,   571,   575,   582,   582,   592,   592,   605,
     611
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "FNUMBER", "INUMBER",
  "NAME", "QTEXT", "SP", "MP", "VOID_T", "INT8_T", "INT16_T", "INT32_T",
  "FLOAT_T", "DOUBLE_T", "STRING_T", "'['", "']'", "'('", "')'", "'='",
  "','", "LOGOR", "LOGAND", "NOEQ", "ISEQ", "'<'", "'>'", "GEQ", "LEQ",
  "'-'", "'+'", "'*'", "'/'", "'%'", "NOT", "UMINUS", "COUNT", "IN",
  "FUNC_CALL", "CONTINUE", "BREAK", "TEXT", "ATTRIBUTE_LIST", "STUBS_LIST",
  "';'", "'}'", "'{'", "$accept", "prog", "stmt_list", "stmt", "decl_stmt",
  "cmpd_stmt", "open_curly", "ques", "qtype", "datatype",
  "range_allowed_values", "number_range_list", "number_range",
  "expression", "q_expr", "expr_list", "text_list", "attributes", "@1",
  "stubs", "@2", "stub_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,    91,    93,
      40,    41,    61,    44,   273,   274,   275,   276,    60,    62,
     277,   278,    45,    43,    42,    47,    37,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,    59,   125,   123
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    54,    54,    54,    55,    56,    57,    57,
      58,    58,    59,    59,    59,    59,    59,    59,    60,    61,
      61,    62,    62,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    64,    64,
      64,    65,    65,    66,    66,    68,    67,    70,    69,    71,
      71
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     2,     5,     7,     1,
       1,     1,     1,     3,     5,     6,     3,     1,     6,     6,
       1,     4,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     1,     4,     6,     4,     1,     3,     1,     3,     6,
       4,     1,     3,     2,     3,     0,     6,     0,     6,     2,
       3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    50,    49,    51,    22,    23,    24,    25,    26,
      27,     0,     0,     0,     0,    55,     0,     0,    17,     0,
       2,     3,    10,     9,     0,     5,     0,     0,    57,    12,
      11,     0,     0,     0,     0,     0,    51,     0,    38,    48,
       0,     0,    67,     1,     4,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,     0,     0,    61,     0,     0,    58,    20,     0,
       0,    56,     0,    65,     0,    16,     0,     0,    13,    47,
      45,    46,    44,    43,    39,    40,    42,    41,    34,    33,
      35,    36,    37,     0,    52,     0,    54,     0,    32,     0,
      29,     0,     0,    60,     0,     0,     0,     0,     7,     0,
       0,    62,     0,    28,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    14,     0,    59,    53,    31,    30,    21,
      19,    18,    63,     0,    66,    69,     0,    68,    15,     8,
      64,    70
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    70,    26,
      67,    99,   100,    27,    28,    65,   119,    29,   104,    30,
      74,   121
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -94
static const yytype_int16 yypact[] =
{
     123,    -7,   -94,   -94,   -13,   -94,   -94,   -94,   -94,   -94,
     -94,   112,   112,   112,    -3,   -94,    28,    45,   -94,    20,
     123,   -94,   -94,   -94,   123,   -94,    70,    29,   -94,   -94,
     -94,   112,   112,   112,    58,    65,    -8,   227,   -94,   -94,
      73,    62,   -94,   -94,   -94,    76,   -14,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   -94,   243,   175,   258,     3,    80,   -94,   -94,    74,
      85,   -94,    82,   -94,    83,   -94,   112,   112,   -94,   258,
     270,   281,   290,   290,    36,    36,    36,    36,    -6,    -6,
     -94,   -94,   -94,   123,    55,   112,   -94,   112,    75,    13,
     -94,   100,    -1,   -94,    66,    67,   193,   149,   105,    58,
     211,   258,   106,   -94,    80,    93,    69,    84,    86,   -33,
     117,   -29,    87,   -94,   123,   -94,   -94,   -94,   -94,   -94,
     -94,   -94,   -94,    94,   -94,   -94,   121,   -94,   -94,   -94,
     -94,   -94
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -94,   -94,   118,   -20,   -94,   -94,   -94,   -94,   -94,    77,
     -93,   -94,    31,   -10,   -94,   -94,   -94,   -94,   -94,   -94,
     -94,   -94
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      44,    37,    38,    39,    76,    32,   116,    33,    77,   117,
      32,   133,    33,    31,   134,   136,   125,    40,   137,    66,
      43,    62,    63,    64,    96,    44,    97,    34,    58,    59,
      60,    35,    34,    78,   113,    41,   114,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    47,    42,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,   106,   107,    56,    57,
      58,    59,    60,   108,    68,    69,    61,    46,    66,     1,
      72,     2,     3,     4,    73,   110,    98,   111,     5,     6,
       7,     8,     9,    10,   101,   109,    11,     5,     6,     7,
       8,     9,    10,   103,   139,   105,   115,   112,    12,   124,
     118,   120,   127,    13,   129,    14,   130,     2,     3,    36,
      15,    16,    17,   135,    75,    18,     1,   141,     2,     3,
       4,   131,    11,   132,   138,     5,     6,     7,     8,     9,
      10,   140,    45,    11,    12,   128,     0,   102,     0,    13,
       0,    14,     0,     0,     0,    12,    15,     0,     0,     0,
      13,     0,    14,     0,     0,     0,     0,    15,    16,    17,
       0,    47,    18,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,     0,     0,     0,     0,
       0,     0,     0,     0,    94,     0,   123,    47,    95,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,   122,     0,     0,    47,     0,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
     126,     0,     0,    47,     0,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    71,    47,
       0,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    93,    47,     0,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      47,     0,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    52,    53,
      54,    55,    56,    57,    58,    59,    60
};

static const yytype_int8 yycheck[] =
{
      20,    11,    12,    13,    18,    18,     7,    20,    22,   102,
      18,    44,    20,    20,    47,    44,   109,    20,    47,    20,
       0,    31,    32,    33,    21,    45,    23,    40,    34,    35,
      36,    44,    40,    47,    21,     7,    23,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    22,     7,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    76,    77,    32,    33,
      34,    35,    36,    93,     9,    10,    47,     7,    20,     3,
       7,     5,     6,     7,    22,    95,     6,    97,    12,    13,
      14,    15,    16,    17,    20,    40,    20,    12,    13,    14,
      15,    16,    17,    21,   124,    22,     6,    32,    32,     4,
      44,    44,     6,    37,    21,    39,    47,     5,     6,     7,
      44,    45,    46,     6,    48,    49,     3,     6,     5,     6,
       7,    47,    20,    47,    47,    12,    13,    14,    15,    16,
      17,    47,    24,    20,    32,   114,    -1,    70,    -1,    37,
      -1,    39,    -1,    -1,    -1,    32,    44,    -1,    -1,    -1,
      37,    -1,    39,    -1,    -1,    -1,    -1,    44,    45,    46,
      -1,    22,    49,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    -1,    47,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    19,    -1,    -1,    22,    -1,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      19,    -1,    -1,    22,    -1,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    21,    22,
      -1,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    21,    22,    -1,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      22,    -1,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    28,    29,
      30,    31,    32,    33,    34,    35,    36
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,    12,    13,    14,    15,    16,
      17,    20,    32,    37,    39,    44,    45,    46,    49,    51,
      52,    53,    54,    55,    56,    57,    59,    63,    64,    67,
      69,    20,    18,    20,    40,    44,     7,    63,    63,    63,
      20,     7,     7,     0,    53,    52,     7,    22,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    47,    63,    63,    63,    65,    20,    60,     9,    10,
      58,    21,     7,    22,    70,    48,    18,    22,    47,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    21,    19,    23,    21,    23,     6,    61,
      62,    20,    59,    21,    68,    22,    63,    63,    53,    40,
      63,    63,    32,    21,    23,     6,     7,    60,    44,    66,
      44,    71,    19,    47,     4,    60,    19,     6,    62,    21,
      47,    47,    47,    44,    47,     6,    44,    47,    47,    53,
      47,     6
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
        case 3:
#line 160 "qscript.y"
    { 
		   cerr << "chain 1:"  << (yyvsp[(1) - (1)].stmt) << endl; (yyval.stmt)=(yyvsp[(1) - (1)].stmt); 
		   cerr << "after $$=$1;" << endl;
		if(flag_next_stmt_start_of_block){
			blk_heads.push_back((yyvsp[(1) - (1)].stmt));
			//cout << "blk_heads.size(): " << blk_heads.size() << endl;
			//start_of_blk=$1;
			flag_next_stmt_start_of_block=false;
			blk_start_flag.pop_back();
		}
	}
    break;

  case 4:
#line 171 "qscript.y"
    {
		(yyval.stmt)=link_chain((yyvsp[(1) - (2)].stmt), (yyvsp[(2) - (2)].stmt));
	}
    break;

  case 6:
#line 177 "qscript.y"
    { 
		if((yyvsp[(1) - (2)].expr)->isvalid()){
			(yyval.stmt) = new expr_stmt(TEXPR_STMT, line_no, (yyvsp[(1) - (2)].expr));
			if(XTCC_DEBUG_MEM_USAGE){
				mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
			}
		} else {
			(yyval.stmt) = new expr_stmt(ERROR_TYPE, line_no, (yyvsp[(1) - (2)].expr));
			if(XTCC_DEBUG_MEM_USAGE){
				mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
			}
		}
	}
    break;

  case 7:
#line 190 "qscript.y"
    {
		(yyval.stmt)=new if_stmt(IFE_STMT,if_line_no,(yyvsp[(3) - (5)].expr),(yyvsp[(5) - (5)].stmt),0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 8:
#line 196 "qscript.y"
    {
		(yyval.stmt)=new if_stmt(IFE_STMT,if_line_no,(yyvsp[(3) - (7)].expr),(yyvsp[(5) - (7)].stmt),(yyvsp[(7) - (7)].stmt));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 9:
#line 202 "qscript.y"
    { 
		(yyval.stmt)=(yyvsp[(1) - (1)].c_stmt);
	}
    break;

  case 10:
#line 205 "qscript.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 11:
#line 208 "qscript.y"
    {
		(yyval.stmt)=0;
	}
    break;

  case 12:
#line 211 "qscript.y"
    {
		(yyval.stmt)=0;
	}
    break;

  case 13:
#line 216 "qscript.y"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (3)].name), (yyvsp[(1) - (3)].dt)/*, line_no*/);
		//free($2);
	}
    break;

  case 14:
#line 220 "qscript.y"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (5)].name), (yyvsp[(1) - (5)].dt), (yyvsp[(4) - (5)].expr));
	}
    break;

  case 15:
#line 223 "qscript.y"
    {
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		datatype dt=datatype(INT8_ARR_TYPE+((yyvsp[(1) - (6)].dt)-INT8_TYPE));
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (6)].name), dt, (yyvsp[(4) - (6)].expr)/*, line_no*/);
		free((yyvsp[(2) - (6)].name));
	}
    break;

  case 16:
#line 231 "qscript.y"
    {
		active_scope_list.pop_back();
		int tmp=active_scope_list.size()-1;
		if(tmp==-1) { 
			active_scope = 0;
			cerr << "Error: active_scope = NULL: should not happen: line_no:" << line_no
				<< endl;
			++no_errors;
			(yyval.c_stmt)=new struct cmpd_stmt(ERROR_TYPE, line_no, 0);
			void *ptr=(yyval.c_stmt);
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		} else { active_scope = active_scope_list[tmp]; }
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
		
		(yyval.c_stmt)=(yyvsp[(1) - (3)].c_stmt);
	}
    break;

  case 17:
#line 261 "qscript.y"
    {
		++nest_lev;
		(yyval.c_stmt) = new cmpd_stmt(CMPD_STMT, line_no, flag_cmpd_stmt_is_a_func_body);
		void *ptr=(yyval.c_stmt);
		mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
		mem_addr.push_back(m1);
		if(flag_cmpd_stmt_is_a_func_body>=0){
			(yyval.c_stmt)->sc=func_info_table[flag_cmpd_stmt_is_a_func_body]->func_scope;
			// reset the flag
			flag_cmpd_stmt_is_a_func_body=-1;
		} else {
			(yyval.c_stmt)->sc= new scope();
			void *ptr=(yyval.c_stmt);
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		}
		flag_next_stmt_start_of_block=true;
		blk_start_flag.push_back(flag_next_stmt_start_of_block);
		active_scope_list.push_back((yyval.c_stmt)->sc);
		active_scope = (yyval.c_stmt)->sc;
	}
    break;

  case 18:
#line 284 "qscript.y"
    {
	      cout << " got question " << endl;
	      string name=(yyvsp[(1) - (6)].name);
	      string q_txt=(yyvsp[(2) - (6)].text_buf);
	      (yyval.stmt)=new range_question(line_no, QUESTION_TYPE, name, q_txt, q_type, no_mpn, (yyvsp[(4) - (6)].dt), r_data);
	      r_data.reset();
	}
    break;

  case 19:
#line 291 "qscript.y"
    {
		cout << " got named stublist type question" << endl;
	      string name=(yyvsp[(1) - (6)].name);
	      string q_txt=(yyvsp[(2) - (6)].text_buf);
	      string attribute_list_name=(yyvsp[(5) - (6)].name);
	      (yyval.stmt)=new named_stub_question(line_no, QUESTION_TYPE, name, q_txt, q_type, no_mpn, (yyvsp[(4) - (6)].dt), attribute_list_name);
		
	}
    break;

  case 20:
#line 302 "qscript.y"
    { q_type = spn; }
    break;

  case 21:
#line 303 "qscript.y"
    { q_type = mpn; no_mpn = (yyvsp[(3) - (4)].ival); }
    break;

  case 28:
#line 314 "qscript.y"
    { }
    break;

  case 31:
#line 321 "qscript.y"
    {
                if( (yyvsp[(3) - (3)].ival) <=(yyvsp[(1) - (3)].ival) ) {
                        cout << "error on lineno: " << line_no
                                << "2nd number in range <= 1st number"
                                << endl;
                } else {
			if(r_data.rcount<MAX_RANGE_ELEMENTS/2){
				r_data.ran_start_end[r_data.rcount*2  ]=(yyvsp[(1) - (3)].ival);
				r_data.ran_start_end[r_data.rcount*2+1]=(yyvsp[(3) - (3)].ival);
				++r_data.rcount;
			} else {
				cerr << "range_list: ran_start_end rcount : buffer overflow:\n";
				cerr << " I should use vector and get rid of this restriction\n";
			}
			
                }
        }
    break;

  case 32:
#line 338 "qscript.y"
    {
                if(r_data.icount<MAX_RANGE_ELEMENTS){
                        r_data.ran_indiv[r_data.icount]=(yyvsp[(1) - (1)].ival);
			++r_data.icount;
		} else {
                        cerr << "range_list: ran_indiv : buffer overflow:\n";
				cerr << " I should use vector and get rid of this restriction\n";
                }
        }
    break;

  case 33:
#line 350 "qscript.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_plus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 34:
#line 356 "qscript.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_minus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 35:
#line 362 "qscript.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_mult);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 36:
#line 368 "qscript.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_div);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 37:
#line 374 "qscript.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_mod);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 38:
#line 380 "qscript.y"
    {
		(yyval.expr) = new un_expr((yyvsp[(2) - (2)].expr), oper_umin);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 39:
#line 386 "qscript.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_lt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 40:
#line 392 "qscript.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_gt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 41:
#line 398 "qscript.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_le);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 42:
#line 404 "qscript.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_ge);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 43:
#line 410 "qscript.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_iseq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 44:
#line 416 "qscript.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_isneq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 45:
#line 422 "qscript.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_or);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 46:
#line 428 "qscript.y"
    {
		cout << "LOGAND expr: " << endl;
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_and);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		cout << "after LOGAND expr : " << endl;
	}
    break;

  case 47:
#line 436 "qscript.y"
    {
		(yyval.expr) = new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_assgn);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 48:
#line 442 "qscript.y"
    {
		(yyval.expr) = new un_expr((yyvsp[(2) - (2)].expr), oper_not);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 49:
#line 448 "qscript.y"
    {
		(yyval.expr) = new un2_expr((yyvsp[(1) - (1)].ival));
		//cout << "got INUMBER: " << $1 << " type : " << $$->type << endl;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 50:
#line 455 "qscript.y"
    {
		(yyval.expr) = new un2_expr((yyvsp[(1) - (1)].dval));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 51:
#line 461 "qscript.y"
    {
		(yyval.expr) = new un2_expr((yyvsp[(1) - (1)].name), oper_name );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 52:
#line 467 "qscript.y"
    {
		(yyval.expr) = new un2_expr(oper_arrderef, /*nametype,  se,*/ (yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(1) - (4)].name));
	}
    break;

  case 53:
#line 474 "qscript.y"
    {
		(yyval.expr) = new un2_expr(oper_blk_arr_assgn, (yyvsp[(1) - (6)].name),(yyvsp[(3) - (6)].expr),(yyvsp[(5) - (6)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(1) - (6)].name));
	}
    break;

  case 54:
#line 481 "qscript.y"
    {
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
				(yyval.expr)=new un2_expr(oper_func_call, my_type, e_ptr, index, line_no);
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
	}
    break;

  case 55:
#line 520 "qscript.y"
    {
		(yyval.expr) = new un2_expr(strdup((yyvsp[(1) - (1)].text_buf)), oper_text_expr);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 56:
#line 526 "qscript.y"
    { 
		cout << "parenth expression" << endl;
		(yyval.expr) = new un_expr((yyvsp[(2) - (3)].expr), oper_parexp );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 57:
#line 544 "qscript.y"
    {
		(yyval.expr)=(yyvsp[(1) - (1)].expr);
	}
    break;

  case 58:
#line 549 "qscript.y"
    {
		cout << " got NAME IN range_allowed_values " << endl;
		(yyval.expr)=new q_expr((yyvsp[(1) - (3)].name), r_data, oper_q_expr_in);
		r_data.reset();
	}
    break;

  case 59:
#line 554 "qscript.y"
    {
		cout << "NAME '[' expression ']' IN range_allowed_values " << endl;
		(yyval.expr)=new q_expr((yyvsp[(1) - (6)].name), r_data, oper_q_expr_arr_in);
		r_data.reset();
	}
    break;

  case 60:
#line 559 "qscript.y"
    {
		cout << "COUNT '(' NAME ')' " << endl;
		(yyval.expr)=0;
	}
    break;

  case 61:
#line 565 "qscript.y"
    { /*$$=$1;*/ }
    break;

  case 62:
#line 566 "qscript.y"
    {
		//$$=link_chain($1,$3);
	}
    break;

  case 63:
#line 571 "qscript.y"
    {
		string s1=(yyvsp[(1) - (2)].text_buf);
		attribute_list.push_back(s1);
	}
    break;

  case 64:
#line 575 "qscript.y"
    {
		string s1=(yyvsp[(2) - (3)].text_buf);
		attribute_list.push_back(s1);
        }
    break;

  case 65:
#line 582 "qscript.y"
    {
		attribute_list.resize(0);
		//cout << "resize attribute_list to 0\n";
	}
    break;

  case 66:
#line 585 "qscript.y"
    {
		//cout <<"got attribute_list size: " << attribute_list.size() << endl;
		(yyval.stmt)=0;
	}
    break;

  case 67:
#line 592 "qscript.y"
    {
		stub_list.resize(0);
		//cout << "resize attribute_list to 0\n";
	}
    break;

  case 68:
#line 595 "qscript.y"
    {
		//cout <<"got attribute_list size: " << attribute_list.size() << endl;
		string stub_name=(yyvsp[(2) - (6)].name);
		struct named_range nr1(stub_name,stub_list);
		named_stubs_list.push_back(nr1);
		(yyval.stmt)=0;
	}
    break;

  case 69:
#line 605 "qscript.y"
    {
		string s1=(yyvsp[(1) - (2)].text_buf);
		int code=(yyvsp[(2) - (2)].ival);
		struct stub_pair pair1(s1,code);
		stub_list.push_back(pair1);
	}
    break;

  case 70:
#line 611 "qscript.y"
    {
		string s1=(yyvsp[(2) - (3)].text_buf);
		int code=(yyvsp[(3) - (3)].ival);
		struct stub_pair pair1(s1,code);
		stub_list.push_back(pair1);
		//cout << "chaining stublist" << endl;
	}
    break;


/* Line 1267 of yacc.c.  */
#line 2246 "qscript.c"
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


#line 620 "qscript.y"


int main(){
	active_scope=new scope();
	active_scope_list.push_back(active_scope);
	return yyparse(); 
}

#include <string>
#if 0
using std::string;
void print_err(compiler_err_category cmp_err, string err_msg, 
	int line_no, int compiler_line_no, string compiler_file_name){
	++no_errors;
	cerr << "qscript " ;
	switch(cmp_err){
		case compiler_syntax_err: 
			cerr << "syntax error: ";
		break;
		case compiler_sem_err:
			cerr << "semantic error: ";
		break;
		case compiler_internal_error:
			cerr << "compiler internal error: " ;
		break;	
		default:
			cerr << "internal compiler error - error code category missing in switch statement: compiler file: " 
				<< __FILE__ << " compiler src code lineno: " << __LINE__ << endl;
			
	}
	cerr << " line_no: " << line_no << " "<< err_msg << ", compiler line_no: " 
		<< compiler_line_no << ", compiler_file_name: " << compiler_file_name << endl;
}
#endif // 0


#if 0
map<string, symtab_ent*>::iterator find_in_symtab(string id){
	bool found=false;
	int i=active_scope_list.size()-1;

	map<string,symtab_ent*>::iterator sym_it ; 
	for(;i>-1;--i){
		sym_it = active_scope_list[i]->sym_tab.find(id);
		if (sym_it == active_scope_list[i]->sym_tab.end() ){
		} else {
			found = true;
			//cout << "found" << endl;
			break;
		}
	}
	if(found==false){
		return active_scope->sym_tab.end();
	} else {
		return sym_it;
	}
}


bool check_type_compat(datatype typ1, datatype typ2){
	//cout << "check_type_compat: line_no: I have to convert the below code into a function:"  << line_no << endl;
	datatype td1=typ1;
	datatype td2=typ2;
	if(td1>=INT8_REF_TYPE && td1<=DOUBLE_REF_TYPE) td1=datatype(INT8_TYPE + typ1-INT8_REF_TYPE);
	if(td2>=INT8_REF_TYPE && td2<=DOUBLE_REF_TYPE) td2=datatype(INT8_TYPE + typ2-INT8_REF_TYPE);
	if((td1>=INT8_TYPE&&td1<=DOUBLE_TYPE) &&
			td2>=INT8_TYPE&&td2<=DOUBLE_TYPE){
		if(td1>=td2){
			return true;
		} else {
			/*
			cerr << "ERROR: td1< td2 Assigning unhandle_able Type to var:  line_no:" << line_no 
				<< " LHS type: " << typ1 << " after converting LHS: " << td1
				<< " RHS type: " << typ2 << " after converting RHS: " << td2
				<< endl;
			*/	
			return false;
		}
	} else {
		/*
		cerr << "ERROR: Assigning unhandle_able Type to var:  line_no:" << line_no 
			<< " LHS type: " << typ1 << " after converting LHS: " << td1
			<< " RHS type: " << typ2 << " after converting RHS: " << td2
			<< endl;
		*/	
		return false;
	}
}

bool 	void_check( datatype & type1, datatype & type2, datatype& result_type){
	if(type1==VOID_TYPE){
		print_err(compiler_sem_err, " lhs of binary expr is of type void ", 
			line_no, __LINE__, __FILE__);
		result_type=ERROR_TYPE;
		++no_errors;
		return false;
	} 
	if( type2==VOID_TYPE){
		print_err(compiler_sem_err, " rhs of binary expr is of type void ", 
			line_no, __LINE__, __FILE__);
		result_type=ERROR_TYPE;
		++no_errors;
		return false;
	}
	if( !(type1==VOID_TYPE && type2==VOID_TYPE)){
		result_type=type1 > type2? type1: type2;
		return true;
	}
	//return true;
}
#endif //0

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

int check_parameters(expr* e, var_list* v){
	debug_log_file << "check_parameters: called" << endl;
	expr* e_ptr=e;
	var_list* fparam=v;
	bool match=true;
	/* Important point to note: I am not allowing references in ordinary variable decl
	   Only in function parameter list - the object is to allow modifying of variables
	   in a function as in C++
	   */

	int chk_param_counter=1;
	while (e_ptr && fparam) {
		//e_ptr->print();
		datatype etype=e_ptr->type, fptype=fparam->var_type; 
		if((etype>=INT8_TYPE && etype<=DOUBLE_TYPE) && 
			((fptype>=INT8_TYPE && fptype<=DOUBLE_TYPE)||
			 (fptype>=INT8_REF_TYPE && fptype<=DOUBLE_REF_TYPE))){
			datatype tdt=fptype;
				/* the code below makes a INT8_REF_TYPE -> INT8_TYPE
				   			a INT8_REF_TYPE -> INT8_TYPE
				 thats because we dont care much about references -> C++
				 does all the hard work. For checking types they are equivalent to us
				*/			
			if(tdt>=INT8_REF_TYPE) tdt=datatype(INT8_TYPE+tdt-INT8_REF_TYPE);
			if(etype <= tdt) {
				debug_log_file << "varname: "<< fparam->var_name << " chk_param_counter: " 
					<< chk_param_counter << " passed " << endl;
			}
		} else if ((etype>=INT8_ARR_TYPE&&etype<=DOUBLE_ARR_TYPE)&&
				(fptype>=INT8_ARR_TYPE&&fptype<=DOUBLE_ARR_TYPE)&&
				(etype==fptype)){
			debug_log_file << "varname: "<< fparam->var_name << " chk_param_counter: " 
					<< chk_param_counter << " passed " << endl;
		}else {
			match=false;
			cerr << "Parameter type mismatch name: " << endl;
			cerr << fparam->var_name << " expected type is " << fparam->var_type
				<< " passed type is " << e_ptr->type 
				<< " line_no: " << line_no << " or currently allowed promotion to: " 
				<< e_ptr->type+INT8_REF_TYPE
				<< endl;
			++no_errors;
		}
		e_ptr=e_ptr->next;
		fparam=fparam->next;
		chk_param_counter=chk_param_counter+1;
	}
	if(match==true){
		if(e_ptr==0&& fparam==0){
			match=true;
		} else {
			match=false;
			++no_errors;
			cerr << "NOTMATCHED: No of parameters in function call not matching with no of paramters in expr: line_no"
				<< line_no << endl;
		}
	}
	if(!match) {
		cerr << "function parameter type check FAILURE: line_no " << line_no << endl;
	}
	return match;
}


	bool skip_func_type_check(const char * fname){
		const char * skip_func_type_check_list[] = {"printf" };
		for (unsigned int i=0; i<sizeof(skip_func_type_check_list)/sizeof(skip_func_type_check_list[0]); ++i){
			if(!strcmp(fname, skip_func_type_check_list[i])){
				return true;
			}
		}
		return false;
	}

