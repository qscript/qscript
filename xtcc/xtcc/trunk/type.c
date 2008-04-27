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
     CONVERT = 258,
     TOT = 259,
     AX = 260,
     CNT = 261,
     TTL = 262,
     FOR = 263,
     FLD = 264,
     TEXT = 265,
     NAME = 266,
     DEFINELIST = 267,
     FNUMBER = 268,
     INUMBER = 269,
     CODELIST = 270,
     LISTA = 271,
     IF = 272,
     ELSE = 273,
     IN = 274,
     VOID_T = 275,
     INT8_T = 276,
     INT16_T = 277,
     INT32_T = 278,
     FLOAT_T = 279,
     DOUBLE_T = 280,
     AXSTART = 281,
     TABSTART = 282,
     ED_START = 283,
     DATA_STRUCT = 284,
     REC_LEN = 285,
     ED_END = 286,
     TAB = 287,
     COND_START = 288,
     CONTINUE = 289,
     BREAK = 290,
     LOGOR = 291,
     LOGAND = 292,
     NOEQ = 293,
     ISEQ = 294,
     GEQ = 295,
     LEQ = 296,
     NOT = 297,
     UMINUS = 298,
     FUNC_CALL = 299
   };
#endif
/* Tokens.  */
#define CONVERT 258
#define TOT 259
#define AX 260
#define CNT 261
#define TTL 262
#define FOR 263
#define FLD 264
#define TEXT 265
#define NAME 266
#define DEFINELIST 267
#define FNUMBER 268
#define INUMBER 269
#define CODELIST 270
#define LISTA 271
#define IF 272
#define ELSE 273
#define IN 274
#define VOID_T 275
#define INT8_T 276
#define INT16_T 277
#define INT32_T 278
#define FLOAT_T 279
#define DOUBLE_T 280
#define AXSTART 281
#define TABSTART 282
#define ED_START 283
#define DATA_STRUCT 284
#define REC_LEN 285
#define ED_END 286
#define TAB 287
#define COND_START 288
#define CONTINUE 289
#define BREAK 290
#define LOGOR 291
#define LOGAND 292
#define NOEQ 293
#define ISEQ 294
#define GEQ 295
#define LEQ 296
#define NOT 297
#define UMINUS 298
#define FUNC_CALL 299




/* Copy the first part of user declarations.  */
#line 26 "type.y"

#include "const_defs.h"
#include "symtab.h"
#include "tree.h"
#include "expr.h"
#include "stmt.h"
#include "Tab.h"
#include <cstring>
#include <iostream>
#include <vector>
#include "scope.h"
#include <map>
#include <sys/types.h>
#include <limits.h>

	using namespace std;

	const bool XTCC_DEBUG_MEM_USAGE=1;
	xtcc_set xs;

//	struct symtab symtab;
	extern int if_line_no;
	int no_errors=0;
	int no_warn=0;
	int yylex();
	void yyerror(char * s);
	extern int line_no;
	extern char * yytext;
	bool check_type_compat(datatype typ1, datatype typ2);
	vector <func_info*> func_info_table;
	int check_parameters(struct expr* e, struct var_list* v);
	vector <scope*> active_scope_list;
	scope* active_scope;
	map<string, symtab_ent*>::iterator find_in_symtab(string id);
	//struct stmt * load_func_into_symbol_table( char * & name,  struct var_list* & v_list, datatype int_type);
	bool skip_func_type_check(const char * fname);
	//void	add_func_params_to_cmpd_sc(struct scope * & sc, struct var_list * & v_list, string & fname);
	int search_for_func(string& search_for);
	int check_func_decl_with_func_defn(struct var_list*& v_list, int & index, string func_name);
	struct stmt* make_func_defn_stmt( struct scope *& sc,
		struct var_list * & v_list,
		struct stmt* & func_body,
		string search_for,
		datatype return_type
		);
	struct stmt * tree_root=0;
	bool 	void_check( datatype & type1, datatype & type2, datatype& result_type);
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);

	int flag_cmpd_stmt_is_a_func_body=-1;
	int lookup_func(string func_name_index);
	vector<table*>	table_list;
	map <string, ax*> ax_map;

	int no_count_ax_elems=0;
	int no_tot_ax_elems=0;
	int in_a_loop=0;
	int nest_lev=0;
	int rec_len;
	bool flag_next_stmt_start_of_block=false;
	//struct stmt* start_of_blk=0;
	vector <stmt*> blk_heads;
	vector<bool> blk_start_flag;

	noun_list_type noun_list[]= {
			{	"void"	, VOID_TYPE},
			{	"int8_t" ,INT8_TYPE},
			{	"int16_t" ,INT16_TYPE},
			{	"int32_t" ,INT32_TYPE},
			{	"float", FLOAT_TYPE},
			{	"double", DOUBLE_TYPE}
		};
	vector<mem_addr_tab>  mem_addr;

	void flex_finish();



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
#line 105 "type.y"
{
	double dval;
	int ival ;
	struct symtab *symp;
	char * name;
	struct expr * expr;
	struct stmt * stmt;
	struct cmpd_stmt * c_stmt;
	int column_no;
	int code_list;
	char text_buf[MY_STR_MAX];
	struct var_list * v_list;
	datatype dt;
	struct ax * ax;
	struct table * tbl;
	class basic_ax_stmt * basic_ax_stmt;
}
/* Line 187 of yacc.c.  */
#line 281 "type.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 294 "type.c"

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
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   638

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNRULES -- Number of states.  */
#define YYNSTATES  232

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    57,    61,     2,
      25,    26,    55,    54,    44,    53,     2,    56,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    62,     5,
      49,    27,    50,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    23,     2,    24,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     7,     2,     9,     2,     2,     2,     2,
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
       6,     8,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    45,    46,    47,    48,    51,    52,    58,    59,    60
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,    15,    20,    25,    27,    30,    32,
      34,    36,    38,    40,    42,    44,    46,    47,    55,    59,
      65,    72,    78,    80,    87,    89,    93,    96,   102,   106,
     107,   109,   112,   113,   124,   126,   129,   131,   133,   135,
     138,   141,   143,   146,   151,   159,   169,   175,   183,   196,
     200,   202,   204,   208,   212,   216,   220,   224,   228,   231,
     235,   239,   243,   247,   251,   255,   259,   263,   267,   270,
     272,   274,   276,   281,   288,   293,   295,   299,   303,   305,
     309,   313,   315,   317,   320,   325,   333,   336,   338,   341,
     346,   354,   357,   359,   362,   367,   375,   383
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      64,     0,    -1,    -1,    37,     5,    38,    27,    17,     5,
      65,    36,    66,    39,    -1,    34,     7,    89,     9,    -1,
      35,     7,    87,     9,    -1,    67,    -1,    66,    67,    -1,
      71,    -1,    69,    -1,    28,    -1,    29,    -1,    30,    -1,
      31,    -1,    32,    -1,    33,    -1,    -1,    68,    14,    25,
      73,    26,    70,    81,    -1,    68,    14,     5,    -1,    68,
      14,    27,    84,     5,    -1,    68,    14,    23,    17,    24,
       5,    -1,    15,    14,    27,    85,     5,    -1,    72,    -1,
      68,    14,    25,    73,    26,     5,    -1,    74,    -1,    73,
      44,    74,    -1,    68,    14,    -1,    68,    14,    23,    17,
      24,    -1,    68,    61,    14,    -1,    -1,    76,    -1,    75,
      76,    -1,    -1,    11,    25,    84,     5,    84,     5,    84,
      26,    77,    76,    -1,    79,    -1,    84,     5,    -1,    81,
      -1,    71,    -1,    78,    -1,    43,     5,    -1,    42,     5,
      -1,    80,    -1,     1,     5,    -1,    19,    14,    13,     5,
      -1,    19,    14,    23,    84,    24,    13,     5,    -1,    19,
      14,    23,    84,    44,    84,    24,    13,     5,    -1,    20,
      25,    84,    26,    76,    -1,    20,    25,    84,    26,    76,
      21,    76,    -1,    12,    14,    27,    14,    25,    84,    44,
      84,    26,    62,    17,     5,    -1,    82,    75,     9,    -1,
       7,    -1,    84,    -1,    83,    44,    84,    -1,    84,    54,
      84,    -1,    84,    53,    84,    -1,    84,    55,    84,    -1,
      84,    56,    84,    -1,    84,    57,    84,    -1,    53,    84,
      -1,    84,    49,    84,    -1,    84,    50,    84,    -1,    84,
      52,    84,    -1,    84,    51,    84,    -1,    84,    48,    84,
      -1,    84,    47,    84,    -1,    84,    45,    84,    -1,    84,
      46,    84,    -1,    84,    27,    84,    -1,    58,    84,    -1,
      17,    -1,    16,    -1,    14,    -1,    14,    23,    84,    24,
      -1,    14,    23,    84,    44,    84,    24,    -1,    14,    25,
      83,    26,    -1,    13,    -1,    25,    84,    26,    -1,    14,
      22,    14,    -1,    86,    -1,    85,    44,    86,    -1,    17,
      53,    17,    -1,    17,    -1,    88,    -1,    87,    88,    -1,
      40,    14,    14,     5,    -1,    40,    14,    14,     5,    41,
      84,     5,    -1,     1,     5,    -1,    90,    -1,    89,    90,
      -1,     6,    14,     5,    91,    -1,     6,    14,     5,    41,
      84,     5,    91,    -1,     1,     5,    -1,    92,    -1,    91,
      92,    -1,     4,     5,    13,     5,    -1,     4,     5,    13,
       5,    41,    84,     5,    -1,     8,     5,    13,     5,    41,
      84,     5,    -1,    10,     5,    13,     5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   210,   210,   209,   221,   224,   229,   232,   237,   240,
     245,   246,   247,   248,   249,   250,   255,   255,   290,   294,
     298,   312,   316,   322,   334,   338,   345,   352,   361,   370,
     375,   385,   390,   390,   394,   395,   408,   411,   414,   415,
     421,   427,   428,   439,   446,   453,   462,   468,   476,   488,
     522,   546,   547,   552,   558,   564,   570,   576,   582,   588,
     594,   600,   606,   612,   618,   624,   630,   636,   642,   648,
     655,   661,   667,   674,   681,   720,   726,   732,   740,   741,
     744,   753,   758,   763,   771,   779,   787,   794,   796,   800,
     812,   823,   834,   837,   842,   850,   858,   866
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONVERT", "TOT", "';'", "AX", "'{'",
  "CNT", "'}'", "TTL", "FOR", "FLD", "TEXT", "NAME", "DEFINELIST",
  "FNUMBER", "INUMBER", "CODELIST", "LISTA", "IF", "ELSE", "IN", "'['",
  "']'", "'('", "')'", "'='", "VOID_T", "INT8_T", "INT16_T", "INT32_T",
  "FLOAT_T", "DOUBLE_T", "AXSTART", "TABSTART", "ED_START", "DATA_STRUCT",
  "REC_LEN", "ED_END", "TAB", "COND_START", "CONTINUE", "BREAK", "','",
  "LOGOR", "LOGAND", "NOEQ", "ISEQ", "'<'", "'>'", "GEQ", "LEQ", "'-'",
  "'+'", "'*'", "'/'", "'%'", "NOT", "UMINUS", "FUNC_CALL", "'&'", "':'",
  "$accept", "prog", "@1", "top_level_item_list", "top_level_item",
  "xtcc_type", "func_defn", "@2", "decl", "func_decl", "decl_comma_list",
  "var_decl", "statement_list", "statement", "@3", "list_stmt", "if_stmt",
  "fld_stmt", "compound_stmt", "open_curly", "expr_list", "expression",
  "range_list", "range", "tab_list", "tab_defn", "ax_list", "ax_defn",
  "ax_stmt_list", "ax_stmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,    59,   260,   123,   261,   125,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,    91,    93,    40,    41,    61,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,    44,   291,   292,   293,   294,    60,
      62,   295,   296,    45,    43,    42,    47,    37,   297,   298,
     299,    38,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    63,    65,    64,    64,    64,    66,    66,    67,    67,
      68,    68,    68,    68,    68,    68,    70,    69,    71,    71,
      71,    71,    71,    72,    73,    73,    74,    74,    74,    74,
      75,    75,    77,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    78,    78,    78,    79,    79,    80,    81,
      82,    83,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    85,    85,
      86,    86,    87,    87,    88,    88,    88,    89,    89,    90,
      90,    90,    91,    91,    92,    92,    92,    92
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,    10,     4,     4,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     7,     3,     5,
       6,     5,     1,     6,     1,     3,     2,     5,     3,     0,
       1,     2,     0,    10,     1,     2,     1,     1,     1,     2,
       2,     1,     2,     4,     7,     9,     5,     7,    12,     3,
       1,     1,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     1,     4,     6,     4,     1,     3,     3,     1,     3,
       3,     1,     1,     2,     4,     7,     2,     1,     2,     4,
       7,     2,     1,     2,     4,     7,     7,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     1,     0,
       0,     0,    87,     0,     0,     0,    82,     0,    91,     0,
       4,    88,    86,     0,     5,    83,     0,     0,     0,     0,
       0,     0,     0,     0,    89,    92,    84,     2,     0,     0,
       0,    75,    71,    70,    69,     0,     0,     0,     0,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    58,
      68,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,     0,
      97,    77,     0,     0,    51,    76,    90,    67,    65,    66,
      64,    63,    59,    60,    62,    61,    54,    53,    55,    56,
      57,    85,     0,    10,    11,    12,    13,    14,    15,     0,
       6,     0,     9,     8,    22,     0,     0,    72,     0,    74,
       0,     0,     3,     7,     0,     0,     0,     0,    52,     0,
      18,     0,    29,     0,    95,    96,    73,    81,     0,    78,
       0,     0,     0,    24,     0,     0,    21,     0,     0,    26,
       0,    16,    29,    19,    80,    79,    20,     0,    28,    23,
       0,    25,     0,    50,    17,     0,    27,     0,     0,     0,
       0,     0,     0,     0,     0,    37,     0,    30,    38,    34,
      41,    36,     0,    42,     0,     0,     0,     0,    40,    39,
       0,    49,    31,    35,     0,     0,     0,     0,     0,    29,
       0,     0,    43,     0,     0,     0,     0,     0,     0,     0,
      46,     0,     0,     0,     0,     0,     0,     0,     0,    44,
       0,    47,    32,     0,     0,     0,     0,    45,    33,     0,
       0,    48
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,    51,   109,   110,   174,   112,   160,   175,   114,
     142,   143,   176,   177,   225,   178,   179,   180,   181,   165,
      83,   182,   138,   139,    15,    16,    11,    12,    34,    35
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -133
static const yytype_int16 yypact[] =
{
      -9,    46,    49,    70,    88,    96,    18,    57,  -133,   102,
     104,   143,  -133,   115,   110,     7,  -133,   108,  -133,   132,
    -133,  -133,  -133,   124,  -133,  -133,   125,    95,   142,   148,
     151,   152,   153,    -7,   111,  -133,   107,  -133,   147,   149,
     150,  -133,   109,  -133,  -133,    -7,    -7,    -7,   141,  -133,
      -7,   129,   156,   161,   170,   163,    -7,    -7,   479,  -133,
    -133,   111,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,    -7,   154,   264,   137,   139,
    -133,  -133,   386,   -23,   581,  -133,   111,   581,   255,   167,
     189,   189,   116,   116,   116,   116,    14,    14,  -133,  -133,
    -133,  -133,   168,  -133,  -133,  -133,  -133,  -133,  -133,   198,
    -133,   169,  -133,  -133,  -133,    -7,    -7,  -133,    -7,  -133,
      -7,   157,  -133,  -133,    69,   207,   220,   434,   581,   215,
    -133,   216,   252,    -7,  -133,  -133,  -133,   182,    45,  -133,
     212,   -13,   -22,  -133,   273,   231,  -133,   215,   244,   227,
     237,   281,   252,  -133,  -133,  -133,  -133,   270,  -133,  -133,
     282,  -133,   266,  -133,  -133,    97,  -133,   283,   274,   284,
     300,   290,   311,   312,   331,  -133,    48,  -133,  -133,  -133,
    -133,  -133,   286,  -133,    -7,   319,    -8,    -7,  -133,  -133,
     118,  -133,  -133,  -133,   339,   333,   343,    -7,   492,   252,
      -7,   324,  -133,   400,    97,     1,   352,    -7,   337,    -7,
     330,   281,    -7,   568,   347,   447,    97,   524,    -7,  -133,
     340,  -133,  -133,   537,   349,    97,   293,  -133,  -133,   341,
     351,  -133
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -133,  -133,  -133,  -133,   250,   -66,  -133,  -133,   -57,  -133,
     162,   208,  -133,  -132,  -133,  -133,  -133,  -133,   202,  -133,
    -133,   -33,  -133,   217,  -133,   348,  -133,   354,   306,   -32
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      48,   149,    49,   119,   151,   196,    41,    42,    13,    43,
      44,   111,    58,    59,    60,   197,    24,    76,    45,    13,
     113,   120,   152,    82,    84,     1,     2,   211,     3,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   111,   192,   152,    46,    14,   150,   167,
     146,    47,   113,     5,    49,   163,     6,   191,    14,   168,
     169,    41,    42,   102,    43,    44,   141,   170,   171,    73,
      74,    75,   210,    45,   130,     7,   103,   104,   105,   106,
     107,   108,   125,   126,   221,   127,   141,   128,     8,   147,
     172,   173,   131,   228,   132,    17,   133,     9,   167,    30,
     144,    46,    10,    31,   163,    32,    47,    18,   168,   169,
      41,    42,   102,    43,    44,    30,   170,   171,    19,    31,
      22,    32,    45,   130,    23,   103,   104,   105,   106,   107,
     108,    55,    56,   141,    57,    26,    33,    27,    28,   172,
     173,   131,    29,   199,     9,   133,    61,    36,    50,    10,
      46,   194,    20,    37,   198,    47,    38,    39,    40,   101,
      52,    78,    53,    54,   203,    77,    79,   206,    62,    71,
      72,    73,    74,    75,   213,    80,   215,    81,   115,   217,
     116,    62,   121,   124,   129,   223,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,   134,   102,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,   135,   103,   104,   105,   106,
     107,   108,   137,   140,    62,   145,   148,   122,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    62,   154,   156,
     157,   158,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,   153,   102,
     103,   104,   105,   106,   107,   108,   159,   162,   183,   163,
     166,   193,   103,   104,   105,   106,   107,   108,   185,   184,
      62,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    62,   186,   187,   188,   189,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,   200,   190,   195,   201,   202,   207,
     214,   216,   219,   224,   227,   229,   231,   212,   230,   123,
     161,   205,   164,    25,   155,    21,    62,    86,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    62,
       0,     0,     0,     0,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
     117,     0,     0,    62,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   208,     0,     0,    62,     0,     0,
     118,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,   209,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,   136,     0,
       0,    62,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   220,     0,     0,    62,     0,     0,     0,     0,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    85,    62,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   204,    62,
       0,     0,     0,     0,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
     222,    62,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   226,    62,     0,     0,     0,     0,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    62,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    62,     0,
       0,     0,   218,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75
};

static const yytype_int16 yycheck[] =
{
      33,    14,    34,    26,    26,    13,    13,    14,     1,    16,
      17,    77,    45,    46,    47,    23,     9,    50,    25,     1,
      77,    44,    44,    56,    57,    34,    35,    26,    37,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,   109,   176,    44,    53,    40,    61,     1,
       5,    58,   109,     7,    86,     7,     7,     9,    40,    11,
      12,    13,    14,    15,    16,    17,   132,    19,    20,    55,
      56,    57,   204,    25,     5,     5,    28,    29,    30,    31,
      32,    33,   115,   116,   216,   118,   152,   120,     0,    44,
      42,    43,    23,   225,    25,    38,    27,     1,     1,     4,
     133,    53,     6,     8,     7,    10,    58,     5,    11,    12,
      13,    14,    15,    16,    17,     4,    19,    20,    14,     8,
       5,    10,    25,     5,    14,    28,    29,    30,    31,    32,
      33,    22,    23,   199,    25,    27,    41,     5,    14,    42,
      43,    23,    17,    25,     1,    27,     5,     5,    41,     6,
      53,   184,     9,     5,   187,    58,     5,     5,     5,     5,
      13,     5,    13,    13,   197,    36,     5,   200,    27,    53,
      54,    55,    56,    57,   207,     5,   209,    14,    41,   212,
      41,    27,    14,    14,    27,   218,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,     5,    15,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,     5,    28,    29,    30,    31,
      32,    33,    17,    17,    27,    53,    24,    39,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    27,    17,     5,
      23,    14,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,     5,    15,
      28,    29,    30,    31,    32,    33,     5,    17,     5,     7,
      24,     5,    28,    29,    30,    31,    32,    33,    14,    25,
      27,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    27,    14,    25,     5,     5,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,     5,    14,    27,    14,     5,    25,
      13,    21,     5,    13,     5,    62,     5,     5,    17,   109,
     152,   199,   160,    15,   147,    11,    27,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    27,    -1,    -1,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    24,    -1,
      -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    26,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    34,    35,    37,    64,     7,     7,     5,     0,     1,
       6,    89,    90,     1,    40,    87,    88,    38,     5,    14,
       9,    90,     5,    14,     9,    88,    27,     5,    14,    17,
       4,     8,    10,    41,    91,    92,     5,     5,     5,     5,
       5,    13,    14,    16,    17,    25,    53,    58,    84,    92,
      41,    65,    13,    13,    13,    22,    23,    25,    84,    84,
      84,     5,    27,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    84,    36,     5,     5,
       5,    14,    84,    83,    84,    26,    91,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,     5,    15,    28,    29,    30,    31,    32,    33,    66,
      67,    68,    69,    71,    72,    41,    41,    24,    44,    26,
      44,    14,    39,    67,    14,    84,    84,    84,    84,    27,
       5,    23,    25,    27,     5,     5,    24,    17,    85,    86,
      17,    68,    73,    74,    84,    53,     5,    44,    24,    14,
      61,    26,    44,     5,    17,    86,     5,    23,    14,     5,
      70,    74,    17,     7,    81,    82,    24,     1,    11,    12,
      19,    20,    42,    43,    68,    71,    75,    76,    78,    79,
      80,    81,    84,     5,    25,    14,    14,    25,     5,     5,
      14,     9,    76,     5,    84,    27,    13,    23,    84,    25,
       5,    14,     5,    84,    26,    73,    84,    25,    24,    44,
      76,    26,     5,    84,    13,    84,    21,    84,    44,     5,
      24,    76,    26,    84,    13,    77,    26,     5,    76,    62,
      17,     5
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
#line 210 "type.y"
    {	const char * c_arr="c";  
		rec_len=(yyvsp[(5) - (6)].ival); 
		active_scope->insert(c_arr, INT8_ARR_TYPE, rec_len, 0);
	}
    break;

  case 3:
#line 214 "type.y"
    {
		tree_root = trav_chain((yyvsp[(9) - (10)].stmt));
		if(tree_root==0){
			cerr << "tree_root =0 : core dump expected" << endl;
		}
		return 0;
	}
    break;

  case 4:
#line 221 "type.y"
    {
		return 0;
	}
    break;

  case 5:
#line 224 "type.y"
    {
		return 0;
	}
    break;

  case 6:
#line 229 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 7:
#line 232 "type.y"
    {
		(yyval.stmt)=link_chain((yyvsp[(1) - (2)].stmt),(yyvsp[(2) - (2)].stmt));
	}
    break;

  case 8:
#line 237 "type.y"
    {
			(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 9:
#line 240 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 16:
#line 255 "type.y"
    {
		string func_name_index((yyvsp[(2) - (5)].name));
		flag_cmpd_stmt_is_a_func_body=lookup_func(func_name_index);
		if(flag_cmpd_stmt_is_a_func_body==-1){
			++ no_errors;
			cerr << "Function name not found in list of declared functions: "
				<< "You will see another error on this same function name: " << func_name_index
				<< "line_no: " << line_no  << endl;
		}
	}
    break;

  case 17:
#line 264 "type.y"
    {
		struct cmpd_stmt* c_stmt= (yyvsp[(7) - (7)].c_stmt);
		if(c_stmt==0){
			cerr << "INTERNAL COMPILER ERROR: c_stmt==0" << endl;
		} else {
			//cout << "func_body: is valid " << endl;
		}
		struct scope *sc=c_stmt->sc;
		struct var_list * v_list=trav_chain((yyvsp[(4) - (7)].v_list));
		struct stmt* func_body=(yyvsp[(7) - (7)].c_stmt);
		string search_for=(yyvsp[(2) - (7)].name);
		datatype return_type=(yyvsp[(1) - (7)].dt);
		(yyval.stmt)=new func_stmt(FUNC_DEFN, line_no, sc, v_list, func_body, search_for, return_type);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		// Note that the declaration already has a parameter list
		// the constructor uses the parameter list - name and type to verify everything
		// but doesnt need the parameter list any more - so we should delete it 
		// - took me a while to figure out this memory leak
		delete v_list;
		free((yyvsp[(2) - (7)].name));
	}
    break;

  case 18:
#line 290 "type.y"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (3)].name), (yyvsp[(1) - (3)].dt)/*, line_no*/);
		free((yyvsp[(2) - (3)].name));
	}
    break;

  case 19:
#line 294 "type.y"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (5)].name), (yyvsp[(1) - (5)].dt), (yyvsp[(4) - (5)].expr));

	}
    break;

  case 20:
#line 298 "type.y"
    {
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		datatype dt=datatype(INT8_ARR_TYPE+((yyvsp[(1) - (6)].dt)-INT8_TYPE));
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (6)].name), dt, (yyvsp[(4) - (6)].ival)/*, line_no*/);
		free((yyvsp[(2) - (6)].name));
	}
    break;

  case 21:
#line 312 "type.y"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (5)].name), RANGE_DECL_STMT, &xs);
		//$$ = new decl_stmt($2, RANGE_DECL_STMT, &xs );
	}
    break;

  case 22:
#line 316 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 23:
#line 322 "type.y"
    {
		char *name=(yyvsp[(2) - (6)].name);
		struct var_list* v_list=trav_chain((yyvsp[(4) - (6)].v_list));
		datatype return_type=(yyvsp[(1) - (6)].dt);
		(yyval.stmt)=new func_decl_stmt( FUNC_TYPE, line_no, name,  v_list, return_type);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 24:
#line 334 "type.y"
    {
		 (yyval.v_list)=(yyvsp[(1) - (1)].v_list);
		 //cout << "got decl_comma_list : " << endl;
	}
    break;

  case 25:
#line 338 "type.y"
    {
		(yyval.v_list)=link_chain((yyvsp[(1) - (3)].v_list),(yyvsp[(3) - (3)].v_list));
		//cout << "chaining var_decl : " << endl;
	}
    break;

  case 26:
#line 345 "type.y"
    {
		(yyval.v_list)=new var_list((yyvsp[(1) - (2)].dt), (yyvsp[(2) - (2)].name));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (2)].name));
	}
    break;

  case 27:
#line 352 "type.y"
    {
		/* Neil - I need to fix this */
		datatype dt=datatype(INT8_ARR_TYPE+((yyvsp[(1) - (5)].dt)-INT8_TYPE));
		(yyval.v_list)=new var_list(dt, (yyvsp[(2) - (5)].name), (yyvsp[(4) - (5)].ival));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (5)].name));
	}
    break;

  case 28:
#line 361 "type.y"
    {
		datatype dt=datatype(INT8_REF_TYPE+((yyvsp[(1) - (3)].dt)-INT8_TYPE));
		(yyval.v_list)=new var_list(dt, (yyvsp[(3) - (3)].name));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(3) - (3)].name));
	}
    break;

  case 29:
#line 370 "type.y"
    {
		(yyval.v_list)=0;
		}
    break;

  case 30:
#line 375 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt); 
		if(flag_next_stmt_start_of_block){
			blk_heads.push_back((yyvsp[(1) - (1)].stmt));
			//cout << "blk_heads.size(): " << blk_heads.size() << endl;
			//start_of_blk=$1;
			flag_next_stmt_start_of_block=false;
			blk_start_flag.pop_back();
		}
	}
    break;

  case 31:
#line 385 "type.y"
    {
		(yyval.stmt)=link_chain((yyvsp[(1) - (2)].stmt),(yyvsp[(2) - (2)].stmt));
	}
    break;

  case 32:
#line 390 "type.y"
    { ++in_a_loop;}
    break;

  case 33:
#line 390 "type.y"
    {
		(yyval.stmt) = new struct for_stmt(FOR_STMT, line_no, (yyvsp[(3) - (10)].expr), (yyvsp[(5) - (10)].expr), (yyvsp[(7) - (10)].expr), (yyvsp[(10) - (10)].stmt));
		--in_a_loop;
	}
    break;

  case 35:
#line 395 "type.y"
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

  case 36:
#line 408 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].c_stmt);
	}
    break;

  case 37:
#line 411 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 39:
#line 415 "type.y"
    {
		(yyval.stmt)=new break_stmt(BREAK_STMT, line_no, in_a_loop);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 40:
#line 421 "type.y"
    {
		(yyval.stmt)=new continue_stmt(CONTINUE_STMT, line_no, in_a_loop);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 42:
#line 428 "type.y"
    {
		print_err(compiler_sem_err, "statement missing ';' around line_no: ", 
			line_no, __LINE__, __FILE__);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		(yyval.stmt) = new struct err_stmt(line_no);
		yyerrok;
	}
    break;

  case 43:
#line 439 "type.y"
    {
		(yyval.stmt)=new list_stmt(LISTA_BASIC_TYPE_STMT, (yyvsp[(2) - (4)].name), (yyvsp[(3) - (4)].text_buf));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (4)].name));
	}
    break;

  case 44:
#line 446 "type.y"
    {
		(yyval.stmt)=new list_stmt( LISTA_BASIC_ARRTYPE_STMT_1INDEX, (yyvsp[(2) - (7)].name), string((yyvsp[(6) - (7)].text_buf)), (yyvsp[(4) - (7)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (7)].name));
	}
    break;

  case 45:
#line 453 "type.y"
    {
		(yyval.stmt)=new list_stmt( LISTA_BASIC_ARRTYPE_STMT_1INDEX, (yyvsp[(2) - (9)].name), string((yyvsp[(8) - (9)].text_buf)), (yyvsp[(4) - (9)].expr), (yyvsp[(6) - (9)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (9)].name));	
	}
    break;

  case 46:
#line 462 "type.y"
    {
		(yyval.stmt)=new if_stmt(IFE_STMT,if_line_no,(yyvsp[(3) - (5)].expr),(yyvsp[(5) - (5)].stmt),0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 47:
#line 468 "type.y"
    {
		(yyval.stmt)=new if_stmt(IFE_STMT, if_line_no,(yyvsp[(3) - (7)].expr),(yyvsp[(5) - (7)].stmt),(yyvsp[(7) - (7)].stmt));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 48:
#line 476 "type.y"
    {
		expr* start_col=(yyvsp[(6) - (12)].expr);
		expr* end_col=(yyvsp[(8) - (12)].expr);
		int width=(yyvsp[(11) - (12)].ival);
		(yyval.stmt) = new fld_stmt((yyvsp[(2) - (12)].name), (yyvsp[(4) - (12)].name), start_col, end_col, width);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (12)].name)), free((yyvsp[(4) - (12)].name));
	}
    break;

  case 49:
#line 488 "type.y"
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

  case 50:
#line 522 "type.y"
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

  case 51:
#line 546 "type.y"
    { (yyval.expr)=(yyvsp[(1) - (1)].expr); }
    break;

  case 52:
#line 547 "type.y"
    {
		(yyval.expr)=link_chain((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));
	}
    break;

  case 53:
#line 552 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_plus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 54:
#line 558 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_minus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 55:
#line 564 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_mult);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 56:
#line 570 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_div);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 57:
#line 576 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_mod);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 58:
#line 582 "type.y"
    {
		(yyval.expr) = new un_expr((yyvsp[(2) - (2)].expr), oper_umin);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 59:
#line 588 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_lt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 60:
#line 594 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_gt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 61:
#line 600 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_le);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 62:
#line 606 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_ge);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 63:
#line 612 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_iseq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 64:
#line 618 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_isneq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 65:
#line 624 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_or);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 66:
#line 630 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_and);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 67:
#line 636 "type.y"
    {
		(yyval.expr) = new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_assgn);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 68:
#line 642 "type.y"
    {
		(yyval.expr) = new un_expr((yyvsp[(2) - (2)].expr), oper_not);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 69:
#line 648 "type.y"
    {
		(yyval.expr) = new un2_expr((yyvsp[(1) - (1)].ival));
		//cout << "got INUMBER: " << $1 << " type : " << $$->type << endl;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 70:
#line 655 "type.y"
    {
		(yyval.expr) = new un2_expr((yyvsp[(1) - (1)].dval));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 71:
#line 661 "type.y"
    {
		(yyval.expr) = new un2_expr((yyvsp[(1) - (1)].name), oper_name );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 72:
#line 667 "type.y"
    {
		(yyval.expr) = new un2_expr(oper_arrderef, /*nametype,  se,*/ (yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(1) - (4)].name));
	}
    break;

  case 73:
#line 674 "type.y"
    {
		(yyval.expr) = new un2_expr(oper_blk_arr_assgn, (yyvsp[(1) - (6)].name),(yyvsp[(3) - (6)].expr),(yyvsp[(5) - (6)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(1) - (6)].name));
	}
    break;

  case 74:
#line 681 "type.y"
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

  case 75:
#line 720 "type.y"
    {
		(yyval.expr) = new un2_expr(strdup((yyvsp[(1) - (1)].text_buf)), oper_text_expr);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 76:
#line 726 "type.y"
    { 
		(yyval.expr) = new un_expr((yyvsp[(2) - (3)].expr), oper_parexp );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 77:
#line 732 "type.y"
    {
		(yyval.expr) = new bin2_expr((yyvsp[(1) - (3)].name), (yyvsp[(3) - (3)].name), oper_in);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 80:
#line 744 "type.y"
    {
		if((yyvsp[(3) - (3)].ival)<=(yyvsp[(1) - (3)].ival)){
			print_err(compiler_sem_err, "2nd number in range <= 1st number",
					line_no, __LINE__, __FILE__  );

		} else {
			xs.range.push_back( pair<int,int>((yyvsp[(1) - (3)].ival),(yyvsp[(3) - (3)].ival)));
		}
	}
    break;

  case 81:
#line 753 "type.y"
    {
		xs.indiv.insert((yyvsp[(1) - (1)].ival));
	}
    break;

  case 82:
#line 758 "type.y"
    { 
#ifdef DEBUG_GRAM
	printf("got table defn\n"); 
#endif
	}
    break;

  case 83:
#line 763 "type.y"
    { 
#ifdef DEBUG_GRAM
		printf("recursive tab_defn\n"); 
#endif
	}
    break;

  case 84:
#line 771 "type.y"
    {
		(yyval.tbl)=new table((yyvsp[(2) - (4)].name),(yyvsp[(3) - (4)].name), line_no);
		table_list.push_back((yyval.tbl));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.tbl), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (4)].name)); free((yyvsp[(3) - (4)].name));
	}
    break;

  case 85:
#line 779 "type.y"
    {
		(yyval.tbl)=new table((yyvsp[(2) - (7)].name),(yyvsp[(3) - (7)].name), line_no, (yyvsp[(6) - (7)].expr));
		table_list.push_back((yyval.tbl));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.tbl), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (7)].name)); free((yyvsp[(3) - (7)].name));
	}
    break;

  case 86:
#line 787 "type.y"
    {
		cerr << "Error in tab section line: " <<
			line_no << endl;
		++no_errors;
	}
    break;

  case 87:
#line 794 "type.y"
    {
	}
    break;

  case 88:
#line 796 "type.y"
    {
	}
    break;

  case 89:
#line 800 "type.y"
    {
		basic_ax_stmt* bptr= trav_chain((yyvsp[(4) - (4)].basic_ax_stmt));
		(yyval.ax) = new ax(bptr,no_count_ax_elems, no_tot_ax_elems, 0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.ax), __LINE__, __FILE__, line_no);
		}
		
		ax_map[(yyvsp[(2) - (4)].name)]=(yyval.ax);
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		free((yyvsp[(2) - (4)].name));
	}
    break;

  case 90:
#line 812 "type.y"
    {
		basic_ax_stmt* bptr= trav_chain((yyvsp[(7) - (7)].basic_ax_stmt));
		(yyval.ax) = new ax(bptr,no_count_ax_elems, no_tot_ax_elems, (yyvsp[(5) - (7)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.ax), __LINE__, __FILE__, line_no);
		}
		ax_map[(yyvsp[(2) - (7)].name)]=(yyval.ax);
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		free((yyvsp[(2) - (7)].name));
	}
    break;

  case 91:
#line 823 "type.y"
    {
		cerr << "Error in axis section line: " <<
			line_no << endl;
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		++no_errors;
	}
    break;

  case 92:
#line 834 "type.y"
    {
		(yyval.basic_ax_stmt) = (yyvsp[(1) - (1)].basic_ax_stmt);
	}
    break;

  case 93:
#line 837 "type.y"
    {
		(yyval.basic_ax_stmt)=link_chain((yyvsp[(1) - (2)].basic_ax_stmt), (yyvsp[(2) - (2)].basic_ax_stmt));
	}
    break;

  case 94:
#line 842 "type.y"
    {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.basic_ax_stmt) = new tot_ax_stmt (tot_axstmt,(yyvsp[(3) - (4)].text_buf), 0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.basic_ax_stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 95:
#line 850 "type.y"
    {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.basic_ax_stmt) = new tot_ax_stmt (tot_axstmt,(yyvsp[(3) - (7)].text_buf), (yyvsp[(6) - (7)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.basic_ax_stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 96:
#line 858 "type.y"
    {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.basic_ax_stmt) = new count_ax_stmt (cnt_axstmt,(yyvsp[(3) - (7)].text_buf), (yyvsp[(6) - (7)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.basic_ax_stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 97:
#line 866 "type.y"
    {
		(yyval.basic_ax_stmt) = new ttl_ax_stmt (txt_axstmt,(yyvsp[(3) - (4)].text_buf));
		++no_tot_ax_elems;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.basic_ax_stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;


/* Line 1267 of yacc.c.  */
#line 2688 "type.c"
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


#line 875 "type.y"



template<class T> T* link_chain(T* &elem1, T* &elem2){
	elem2->prev=elem1;
	elem1->next=elem2;
	return elem2;
}

template<class T> T* trav_chain(T* & elem1){
	if(elem1){
		while (elem1->prev) elem1=elem1->prev;
		return elem1;
	} else return 0;
}


