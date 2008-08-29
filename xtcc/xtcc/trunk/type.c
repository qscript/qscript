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
     BIT = 265,
     TEXT = 266,
     NAME = 267,
     DEFINELIST = 268,
     FNUMBER = 269,
     INUMBER = 270,
     CODELIST = 271,
     LISTA = 272,
     IF = 273,
     ELSE = 274,
     IN = 275,
     VOID_T = 276,
     INT8_T = 277,
     INT16_T = 278,
     INT32_T = 279,
     FLOAT_T = 280,
     DOUBLE_T = 281,
     AXSTART = 282,
     TABSTART = 283,
     ED_START = 284,
     DATA_STRUCT = 285,
     REC_LEN = 286,
     ED_END = 287,
     TAB = 288,
     COND_START = 289,
     CONTINUE = 290,
     BREAK = 291,
     LOGOR = 292,
     LOGAND = 293,
     NOEQ = 294,
     ISEQ = 295,
     GEQ = 296,
     LEQ = 297,
     NOT = 298,
     UMINUS = 299,
     FUNC_CALL = 300
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
#define BIT 265
#define TEXT 266
#define NAME 267
#define DEFINELIST 268
#define FNUMBER 269
#define INUMBER 270
#define CODELIST 271
#define LISTA 272
#define IF 273
#define ELSE 274
#define IN 275
#define VOID_T 276
#define INT8_T 277
#define INT16_T 278
#define INT32_T 279
#define FLOAT_T 280
#define DOUBLE_T 281
#define AXSTART 282
#define TABSTART 283
#define ED_START 284
#define DATA_STRUCT 285
#define REC_LEN 286
#define ED_END 287
#define TAB 288
#define COND_START 289
#define CONTINUE 290
#define BREAK 291
#define LOGOR 292
#define LOGAND 293
#define NOEQ 294
#define ISEQ 295
#define GEQ 296
#define LEQ 297
#define NOT 298
#define UMINUS 299
#define FUNC_CALL 300




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
	vector <stub*> stub_list;
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
#line 106 "type.y"
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
	struct stub * stub;
	struct table * tbl;
	class basic_print_ax_stmt * print_stmt;
	class basic_count_ax_stmt * count_stmt;
}
/* Line 187 of yacc.c.  */
#line 286 "type.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 299 "type.c"

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
#define YYLAST   657

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNRULES -- Number of states.  */
#define YYNSTATES  246

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    58,    62,     2,
      26,    27,    56,    55,    45,    54,     2,    57,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    63,     5,
      50,    28,    51,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    24,     2,    25,     2,     2,     2,     2,     2,     2,
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
      18,    19,    20,    21,    22,    23,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    46,    47,    48,    49,    52,    53,    59,    60,
      61
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
     272,   274,   276,   281,   288,   293,   295,   299,   301,   305,
     309,   311,   313,   316,   321,   329,   332,   334,   337,   343,
     352,   355,   357,   360,   365,   367,   370,   375,   377,   380,
     385,   393,   401,   403
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      65,     0,    -1,    -1,    38,     5,    39,    28,    18,     5,
      66,    37,    67,    40,    -1,    35,     7,    90,     9,    -1,
      36,     7,    88,     9,    -1,    68,    -1,    67,    68,    -1,
      72,    -1,    70,    -1,    29,    -1,    30,    -1,    31,    -1,
      32,    -1,    33,    -1,    34,    -1,    -1,    69,    15,    26,
      74,    27,    71,    82,    -1,    69,    15,     5,    -1,    69,
      15,    28,    85,     5,    -1,    69,    15,    24,    18,    25,
       5,    -1,    16,    15,    28,    86,     5,    -1,    73,    -1,
      69,    15,    26,    74,    27,     5,    -1,    75,    -1,    74,
      45,    75,    -1,    69,    15,    -1,    69,    15,    24,    18,
      25,    -1,    69,    62,    15,    -1,    -1,    77,    -1,    76,
      77,    -1,    -1,    11,    26,    85,     5,    85,     5,    85,
      27,    78,    77,    -1,    80,    -1,    85,     5,    -1,    82,
      -1,    72,    -1,    79,    -1,    44,     5,    -1,    43,     5,
      -1,    81,    -1,     1,     5,    -1,    20,    15,    14,     5,
      -1,    20,    15,    24,    85,    25,    14,     5,    -1,    20,
      15,    24,    85,    45,    85,    25,    14,     5,    -1,    21,
      26,    85,    27,    77,    -1,    21,    26,    85,    27,    77,
      22,    77,    -1,    12,    15,    28,    15,    26,    85,    45,
      85,    27,    63,    18,     5,    -1,    83,    76,     9,    -1,
       7,    -1,    85,    -1,    84,    45,    85,    -1,    85,    55,
      85,    -1,    85,    54,    85,    -1,    85,    56,    85,    -1,
      85,    57,    85,    -1,    85,    58,    85,    -1,    54,    85,
      -1,    85,    50,    85,    -1,    85,    51,    85,    -1,    85,
      53,    85,    -1,    85,    52,    85,    -1,    85,    49,    85,
      -1,    85,    48,    85,    -1,    85,    46,    85,    -1,    85,
      47,    85,    -1,    85,    28,    85,    -1,    59,    85,    -1,
      18,    -1,    17,    -1,    15,    -1,    15,    24,    85,    25,
      -1,    15,    24,    85,    45,    85,    25,    -1,    15,    26,
      84,    27,    -1,    14,    -1,    26,    85,    27,    -1,    87,
      -1,    86,    45,    87,    -1,    18,    54,    18,    -1,    18,
      -1,    89,    -1,    88,    89,    -1,    41,    15,    15,     5,
      -1,    41,    15,    15,     5,    42,    85,     5,    -1,     1,
       5,    -1,    91,    -1,    90,    91,    -1,     6,    15,     5,
      94,    96,    -1,     6,    15,     5,    42,    85,     5,    94,
      96,    -1,     1,     5,    -1,    93,    -1,    92,    93,    -1,
      14,    28,    18,     5,    -1,    95,    -1,    94,    95,    -1,
      10,     5,    14,     5,    -1,    97,    -1,    96,    97,    -1,
       4,     5,    14,     5,    -1,     4,     5,    14,     5,    42,
      85,     5,    -1,     8,     5,    14,     5,    42,    85,     5,
      -1,    98,    -1,    13,    15,     5,    92,     5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   219,   219,   218,   230,   233,   238,   241,   246,   249,
     254,   255,   256,   257,   258,   259,   264,   264,   299,   303,
     307,   321,   325,   331,   343,   347,   354,   361,   370,   379,
     384,   394,   399,   399,   403,   404,   417,   420,   423,   424,
     430,   436,   437,   448,   455,   462,   471,   477,   485,   497,
     531,   555,   556,   561,   567,   573,   579,   585,   591,   597,
     603,   609,   615,   621,   627,   633,   639,   645,   651,   657,
     664,   670,   676,   683,   690,   729,   735,   751,   752,   755,
     764,   769,   774,   782,   790,   798,   805,   807,   811,   825,
     837,   846,   847,   852,   860,   861,   866,   875,   878,   883,
     891,   899,   907,   910
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONVERT", "TOT", "';'", "AX", "'{'",
  "CNT", "'}'", "TTL", "FOR", "FLD", "BIT", "TEXT", "NAME", "DEFINELIST",
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
  "stub_list", "stub", "ttl_ax_stmt_list", "ttl_ax_stmt",
  "count_ax_stmt_list", "count_ax_stmt", "bit_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,    59,   260,   123,   261,   125,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,    91,    93,    40,    41,    61,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,    44,   292,   293,   294,   295,
      60,    62,   296,   297,    45,    43,    42,    47,    37,   298,
     299,   300,    38,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    64,    66,    65,    65,    65,    67,    67,    68,    68,
      69,    69,    69,    69,    69,    69,    71,    70,    72,    72,
      72,    72,    72,    73,    74,    74,    75,    75,    75,    75,
      76,    76,    78,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    79,    79,    79,    80,    80,    81,    82,
      83,    84,    84,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    86,    86,    87,
      87,    88,    88,    89,    89,    89,    90,    90,    91,    91,
      91,    92,    92,    93,    94,    94,    95,    96,    96,    97,
      97,    97,    97,    98
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
       1,     1,     4,     6,     4,     1,     3,     1,     3,     3,
       1,     1,     2,     4,     7,     2,     1,     2,     5,     8,
       2,     1,     2,     4,     1,     2,     4,     1,     2,     4,
       7,     7,     1,     5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     1,     0,
       0,     0,    86,     0,     0,     0,    81,     0,    90,     0,
       4,    87,    85,     0,     5,    82,     0,     0,     0,     0,
       0,     0,     0,    94,    83,     2,     0,    75,    71,    70,
      69,     0,     0,     0,     0,     0,     0,     0,    95,    88,
      97,   102,     0,     0,     0,     0,     0,     0,    58,    68,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    98,     0,
       0,    96,     0,     0,    51,    76,     0,    67,    65,    66,
      64,    63,    59,    60,    62,    61,    54,    53,    55,    56,
      57,     0,     0,     0,    84,     0,    10,    11,    12,    13,
      14,    15,     0,     6,     0,     9,     8,    22,    72,     0,
      74,     0,    89,    99,     0,     0,     0,    91,     0,     3,
       7,     0,     0,    52,     0,     0,     0,   103,    92,     0,
      18,     0,    29,     0,    73,     0,     0,     0,    80,     0,
      77,     0,     0,     0,    24,     0,   100,   101,    93,     0,
      21,     0,     0,    26,     0,    16,    29,    19,    79,    78,
      20,     0,    28,    23,     0,    25,     0,    50,    17,     0,
      27,     0,     0,     0,     0,     0,     0,     0,     0,    37,
       0,    30,    38,    34,    41,    36,     0,    42,     0,     0,
       0,     0,    40,    39,     0,    49,    31,    35,     0,     0,
       0,     0,     0,    29,     0,     0,    43,     0,     0,     0,
       0,     0,     0,     0,    46,     0,     0,     0,     0,     0,
       0,     0,     0,    44,     0,    47,    32,     0,     0,     0,
       0,    45,    33,     0,     0,    48
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,    53,   112,   113,   188,   115,   174,   189,   117,
     153,   154,   190,   191,   239,   192,   193,   194,   195,   179,
      83,   196,   149,   150,    15,    16,    11,    12,   126,   127,
      32,    33,    49,    50,    51
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -140
static const yytype_int16 yypact[] =
{
     109,    19,    41,    48,    64,    22,    14,    34,  -140,    71,
      63,   142,  -140,    81,    74,     5,  -140,    59,  -140,    87,
    -140,  -140,  -140,    83,  -140,  -140,    84,    17,   103,   104,
     110,   -10,   158,  -140,    77,  -140,   102,  -140,    -6,  -140,
    -140,   -10,   -10,   -10,   156,   120,   126,   127,  -140,    93,
    -140,  -140,   -10,   122,   136,   -10,   -10,   497,  -140,  -140,
     148,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,
     -10,   -10,   -10,   -10,   -10,   149,   150,   164,  -140,   169,
     280,  -140,   404,     2,   599,  -140,   158,   599,   272,   182,
     204,   204,   121,   121,   121,   121,    72,    72,  -140,  -140,
    -140,   167,   168,   171,  -140,   166,  -140,  -140,  -140,  -140,
    -140,  -140,   213,  -140,   172,  -140,  -140,  -140,  -140,   -10,
    -140,   -10,    93,   140,   144,   160,    56,  -140,   161,  -140,
    -140,   128,   452,   599,   -10,   -10,   173,  -140,  -140,   175,
    -140,   176,   268,   -10,  -140,   223,   236,   191,   145,    12,
    -140,   224,   -12,    66,  -140,   290,  -140,  -140,  -140,   180,
    -140,   175,   195,   226,   233,   247,   268,  -140,  -140,  -140,
    -140,   245,  -140,  -140,   258,  -140,   241,  -140,  -140,   106,
    -140,   262,   242,   288,   289,   279,   301,   302,   300,  -140,
      51,  -140,  -140,  -140,  -140,  -140,   303,  -140,   -10,   304,
      -5,   -10,  -140,  -140,   129,  -140,  -140,  -140,   357,   318,
     311,   -10,   510,   268,   -10,   291,  -140,   418,   106,    69,
     370,   -10,   320,   -10,   313,   247,   -10,   586,   358,   465,
     106,   542,   -10,  -140,   350,  -140,  -140,   555,   360,   106,
     305,  -140,  -140,   348,   362,  -140
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -140,  -140,  -140,  -140,   257,   -67,  -140,  -140,   -58,  -140,
     157,   205,  -140,  -139,  -140,  -140,  -140,  -140,   198,  -140,
    -140,   -31,  -140,   212,  -140,   359,  -140,   365,  -140,   251,
     319,   -30,   292,   -48,  -140
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      44,    78,    48,   163,    37,    38,    13,    39,    40,   210,
      57,    58,    59,   114,    24,    13,    41,   160,    55,   211,
      56,    79,   116,     9,    82,    84,     5,    30,    10,   120,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    42,   114,    14,   121,     6,    43,
     164,   206,   181,     7,   116,    14,    48,   161,   177,    31,
     205,   137,   182,   183,     8,    37,    38,   105,    39,    40,
     125,   184,   185,    17,    78,   152,    18,    41,    19,   224,
     106,   107,   108,   109,   110,   111,    22,    26,   132,    23,
     133,   235,    27,   165,   186,   187,   225,    45,    28,   152,
     242,    46,    29,   145,   146,    42,    47,   181,    34,    35,
      43,   166,   155,   177,   166,    36,    54,   182,   183,    52,
      37,    38,   105,    39,    40,    75,   184,   185,    72,    73,
      74,    76,    41,   140,   140,   106,   107,   108,   109,   110,
     111,    81,    77,     9,     1,     2,   152,     3,    10,   186,
     187,    20,   141,   141,   142,   213,   143,   143,    30,    80,
      42,    60,    45,   101,   102,    43,    46,   208,    30,   103,
     212,    47,   123,   124,   104,    70,    71,    72,    73,    74,
     217,   128,   134,   220,    61,   125,   135,   131,   136,   139,
     227,   147,   229,   148,   151,   231,   158,    61,   168,   159,
     170,   237,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,   156,   105,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,   157,   106,   107,   108,   109,   110,   111,   172,   162,
     171,    61,   173,   129,    66,    67,    68,    69,    70,    71,
      72,    73,    74,   176,    61,   177,   180,   197,   198,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,   167,   105,   106,   107,   108,
     109,   110,   111,   199,   200,   201,   202,   203,   207,   106,
     107,   108,   109,   110,   111,   204,   216,   221,    61,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    61,   209,   215,   228,   230,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,   214,   233,   238,   241,   244,   245,   243,   130,
     219,   175,   178,   169,    25,   226,    21,   138,   122,    86,
       0,     0,     0,     0,     0,    61,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,     0,
       0,     0,     0,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,   118,
       0,     0,    61,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   222,     0,     0,    61,     0,     0,   119,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,   223,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,   144,     0,     0,
      61,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     234,     0,     0,    61,     0,     0,     0,     0,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    85,    61,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   218,    61,     0,
       0,     0,     0,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,   236,
      61,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   240,    61,     0,     0,     0,     0,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    61,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,     0,     0,
       0,   232,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74
};

static const yytype_int16 yycheck[] =
{
      31,    49,    32,    15,    14,    15,     1,    17,    18,    14,
      41,    42,    43,    80,     9,     1,    26,     5,    24,    24,
      26,    52,    80,     1,    55,    56,     7,    10,     6,    27,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    54,   112,    41,    45,     7,    59,
      62,   190,     1,     5,   112,    41,    86,    45,     7,    42,
       9,     5,    11,    12,     0,    14,    15,    16,    17,    18,
      14,    20,    21,    39,   122,   142,     5,    26,    15,   218,
      29,    30,    31,    32,    33,    34,     5,    28,   119,    15,
     121,   230,     5,    27,    43,    44,    27,     4,    15,   166,
     239,     8,    18,   134,   135,    54,    13,     1,     5,     5,
      59,    45,   143,     7,    45,     5,    14,    11,    12,    42,
      14,    15,    16,    17,    18,     5,    20,    21,    56,    57,
      58,     5,    26,     5,     5,    29,    30,    31,    32,    33,
      34,     5,    15,     1,    35,    36,   213,    38,     6,    43,
      44,     9,    24,    24,    26,    26,    28,    28,    10,    37,
      54,     5,     4,    14,    14,    59,     8,   198,    10,     5,
     201,    13,     5,     5,     5,    54,    55,    56,    57,    58,
     211,    15,    42,   214,    28,    14,    42,    15,    28,    28,
     221,    18,   223,    18,    18,   226,     5,    28,    18,    54,
       5,   232,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,     5,    16,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,     5,    29,    30,    31,    32,    33,    34,    15,    25,
      24,    28,     5,    40,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    18,    28,     7,    25,     5,    26,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,     5,    16,    29,    30,    31,
      32,    33,    34,    15,    15,    26,     5,     5,     5,    29,
      30,    31,    32,    33,    34,    15,     5,    26,    28,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    28,    28,    15,    14,    22,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,     5,     5,    14,     5,    18,     5,    63,   112,
     213,   166,   174,   161,    15,     5,    11,   126,    86,    60,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    25,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    28,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    25,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    28,    -1,    -1,    -1,    -1,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    -1,
      -1,    -1,    -1,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    28,    -1,    -1,    -1,    -1,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    35,    36,    38,    65,     7,     7,     5,     0,     1,
       6,    90,    91,     1,    41,    88,    89,    39,     5,    15,
       9,    91,     5,    15,     9,    89,    28,     5,    15,    18,
      10,    42,    94,    95,     5,     5,     5,    14,    15,    17,
      18,    26,    54,    59,    85,     4,     8,    13,    95,    96,
      97,    98,    42,    66,    14,    24,    26,    85,    85,    85,
       5,    28,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,     5,     5,    15,    97,    85,
      37,     5,    85,    84,    85,    27,    94,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    14,    14,     5,     5,    16,    29,    30,    31,    32,
      33,    34,    67,    68,    69,    70,    72,    73,    25,    45,
      27,    45,    96,     5,     5,    14,    92,    93,    15,    40,
      68,    15,    85,    85,    42,    42,    28,     5,    93,    28,
       5,    24,    26,    28,    25,    85,    85,    18,    18,    86,
      87,    18,    69,    74,    75,    85,     5,     5,     5,    54,
       5,    45,    25,    15,    62,    27,    45,     5,    18,    87,
       5,    24,    15,     5,    71,    75,    18,     7,    82,    83,
      25,     1,    11,    12,    20,    21,    43,    44,    69,    72,
      76,    77,    79,    80,    81,    82,    85,     5,    26,    15,
      15,    26,     5,     5,    15,     9,    77,     5,    85,    28,
      14,    24,    85,    26,     5,    15,     5,    85,    27,    74,
      85,    26,    25,    45,    77,    27,     5,    85,    14,    85,
      22,    85,    45,     5,    25,    77,    27,    85,    14,    78,
      27,     5,    77,    63,    18,     5
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
#line 219 "type.y"
    {	const char * c_arr="c";  
		rec_len=(yyvsp[(5) - (6)].ival); 
		active_scope->insert(c_arr, INT8_ARR_TYPE, rec_len, 0);
	}
    break;

  case 3:
#line 223 "type.y"
    {
		tree_root = trav_chain((yyvsp[(9) - (10)].stmt));
		if(tree_root==0){
			cerr << "tree_root =0 : core dump expected" << endl;
		}
		return 0;
	}
    break;

  case 4:
#line 230 "type.y"
    {
		return 0;
	}
    break;

  case 5:
#line 233 "type.y"
    {
		return 0;
	}
    break;

  case 6:
#line 238 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 7:
#line 241 "type.y"
    {
		(yyval.stmt)=link_chain((yyvsp[(1) - (2)].stmt),(yyvsp[(2) - (2)].stmt));
	}
    break;

  case 8:
#line 246 "type.y"
    {
			(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 9:
#line 249 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 16:
#line 264 "type.y"
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
#line 273 "type.y"
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
#line 299 "type.y"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (3)].name), (yyvsp[(1) - (3)].dt)/*, line_no*/);
		free((yyvsp[(2) - (3)].name));
	}
    break;

  case 19:
#line 303 "type.y"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (5)].name), (yyvsp[(1) - (5)].dt), (yyvsp[(4) - (5)].expr));

	}
    break;

  case 20:
#line 307 "type.y"
    {
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		datatype dt=datatype(INT8_ARR_TYPE+((yyvsp[(1) - (6)].dt)-INT8_TYPE));
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (6)].name), dt, (yyvsp[(4) - (6)].ival)/*, line_no*/);
		free((yyvsp[(2) - (6)].name));
	}
    break;

  case 21:
#line 321 "type.y"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (5)].name), RANGE_DECL_STMT, &xs);
		//$$ = new decl_stmt($2, RANGE_DECL_STMT, &xs );
	}
    break;

  case 22:
#line 325 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 23:
#line 331 "type.y"
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
#line 343 "type.y"
    {
		 (yyval.v_list)=(yyvsp[(1) - (1)].v_list);
		 //cout << "got decl_comma_list : " << endl;
	}
    break;

  case 25:
#line 347 "type.y"
    {
		(yyval.v_list)=link_chain((yyvsp[(1) - (3)].v_list),(yyvsp[(3) - (3)].v_list));
		//cout << "chaining var_decl : " << endl;
	}
    break;

  case 26:
#line 354 "type.y"
    {
		(yyval.v_list)=new var_list((yyvsp[(1) - (2)].dt), (yyvsp[(2) - (2)].name));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (2)].name));
	}
    break;

  case 27:
#line 361 "type.y"
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
#line 370 "type.y"
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
#line 379 "type.y"
    {
		(yyval.v_list)=0;
		}
    break;

  case 30:
#line 384 "type.y"
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
#line 394 "type.y"
    {
		(yyval.stmt)=link_chain((yyvsp[(1) - (2)].stmt),(yyvsp[(2) - (2)].stmt));
	}
    break;

  case 32:
#line 399 "type.y"
    { ++in_a_loop;}
    break;

  case 33:
#line 399 "type.y"
    {
		(yyval.stmt) = new struct for_stmt(FOR_STMT, line_no, (yyvsp[(3) - (10)].expr), (yyvsp[(5) - (10)].expr), (yyvsp[(7) - (10)].expr), (yyvsp[(10) - (10)].stmt));
		--in_a_loop;
	}
    break;

  case 35:
#line 404 "type.y"
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
#line 417 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].c_stmt);
	}
    break;

  case 37:
#line 420 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 39:
#line 424 "type.y"
    {
		(yyval.stmt)=new break_stmt(BREAK_STMT, line_no, in_a_loop);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 40:
#line 430 "type.y"
    {
		(yyval.stmt)=new continue_stmt(CONTINUE_STMT, line_no, in_a_loop);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 42:
#line 437 "type.y"
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
#line 448 "type.y"
    {
		(yyval.stmt)=new list_stmt(LISTA_BASIC_TYPE_STMT, (yyvsp[(2) - (4)].name), (yyvsp[(3) - (4)].text_buf));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (4)].name));
	}
    break;

  case 44:
#line 455 "type.y"
    {
		(yyval.stmt)=new list_stmt( LISTA_BASIC_ARRTYPE_STMT_1INDEX, (yyvsp[(2) - (7)].name), string((yyvsp[(6) - (7)].text_buf)), (yyvsp[(4) - (7)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (7)].name));
	}
    break;

  case 45:
#line 462 "type.y"
    {
		(yyval.stmt)=new list_stmt( LISTA_BASIC_ARRTYPE_STMT_1INDEX, (yyvsp[(2) - (9)].name), string((yyvsp[(8) - (9)].text_buf)), (yyvsp[(4) - (9)].expr), (yyvsp[(6) - (9)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (9)].name));	
	}
    break;

  case 46:
#line 471 "type.y"
    {
		(yyval.stmt)=new if_stmt(IFE_STMT,if_line_no,(yyvsp[(3) - (5)].expr),(yyvsp[(5) - (5)].stmt),0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 47:
#line 477 "type.y"
    {
		(yyval.stmt)=new if_stmt(IFE_STMT, if_line_no,(yyvsp[(3) - (7)].expr),(yyvsp[(5) - (7)].stmt),(yyvsp[(7) - (7)].stmt));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 48:
#line 485 "type.y"
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
#line 497 "type.y"
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
#line 531 "type.y"
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
#line 555 "type.y"
    { (yyval.expr)=(yyvsp[(1) - (1)].expr); }
    break;

  case 52:
#line 556 "type.y"
    {
		(yyval.expr)=link_chain((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));
	}
    break;

  case 53:
#line 561 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_plus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 54:
#line 567 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_minus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 55:
#line 573 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_mult);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 56:
#line 579 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_div);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 57:
#line 585 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_mod);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 58:
#line 591 "type.y"
    {
		(yyval.expr) = new un_expr((yyvsp[(2) - (2)].expr), oper_umin);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 59:
#line 597 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_lt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 60:
#line 603 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_gt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 61:
#line 609 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_le);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 62:
#line 615 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_ge);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 63:
#line 621 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_iseq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 64:
#line 627 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_isneq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 65:
#line 633 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_or);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 66:
#line 639 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_and);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 67:
#line 645 "type.y"
    {
		(yyval.expr) = new bin_expr((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_assgn);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 68:
#line 651 "type.y"
    {
		(yyval.expr) = new un_expr((yyvsp[(2) - (2)].expr), oper_not);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 69:
#line 657 "type.y"
    {
		(yyval.expr) = new un2_expr((yyvsp[(1) - (1)].ival));
		//cout << "got INUMBER: " << $1 << " type : " << $$->type << endl;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 70:
#line 664 "type.y"
    {
		(yyval.expr) = new un2_expr((yyvsp[(1) - (1)].dval));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 71:
#line 670 "type.y"
    {
		(yyval.expr) = new un2_expr((yyvsp[(1) - (1)].name), oper_name );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 72:
#line 676 "type.y"
    {
		(yyval.expr) = new un2_expr(oper_arrderef, /*nametype,  se,*/ (yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(1) - (4)].name));
	}
    break;

  case 73:
#line 683 "type.y"
    {
		(yyval.expr) = new un2_expr(oper_blk_arr_assgn, (yyvsp[(1) - (6)].name),(yyvsp[(3) - (6)].expr),(yyvsp[(5) - (6)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(1) - (6)].name));
	}
    break;

  case 74:
#line 690 "type.y"
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
#line 729 "type.y"
    {
		(yyval.expr) = new un2_expr(strdup((yyvsp[(1) - (1)].text_buf)), oper_text_expr);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 76:
#line 735 "type.y"
    { 
		(yyval.expr) = new un_expr((yyvsp[(2) - (3)].expr), oper_parexp );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 79:
#line 755 "type.y"
    {
		if((yyvsp[(3) - (3)].ival)<=(yyvsp[(1) - (3)].ival)){
			print_err(compiler_sem_err, "2nd number in range <= 1st number",
					line_no, __LINE__, __FILE__  );

		} else {
			xs.range.push_back( pair<int,int>((yyvsp[(1) - (3)].ival),(yyvsp[(3) - (3)].ival)));
		}
	}
    break;

  case 80:
#line 764 "type.y"
    {
		xs.indiv.insert((yyvsp[(1) - (1)].ival));
	}
    break;

  case 81:
#line 769 "type.y"
    { 
#ifdef DEBUG_GRAM
	printf("got table defn\n"); 
#endif
	}
    break;

  case 82:
#line 774 "type.y"
    { 
#ifdef DEBUG_GRAM
		printf("recursive tab_defn\n"); 
#endif
	}
    break;

  case 83:
#line 782 "type.y"
    {
		(yyval.tbl)=new table((yyvsp[(2) - (4)].name),(yyvsp[(3) - (4)].name), line_no);
		table_list.push_back((yyval.tbl));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.tbl), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (4)].name)); free((yyvsp[(3) - (4)].name));
	}
    break;

  case 84:
#line 790 "type.y"
    {
		(yyval.tbl)=new table((yyvsp[(2) - (7)].name),(yyvsp[(3) - (7)].name), line_no, (yyvsp[(6) - (7)].expr));
		table_list.push_back((yyval.tbl));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.tbl), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (7)].name)); free((yyvsp[(3) - (7)].name));
	}
    break;

  case 85:
#line 798 "type.y"
    {
		cerr << "Error in tab section line: " <<
			line_no << endl;
		++no_errors;
	}
    break;

  case 86:
#line 805 "type.y"
    {
	}
    break;

  case 87:
#line 807 "type.y"
    {
	}
    break;

  case 88:
#line 811 "type.y"
    {
		basic_print_ax_stmt  * ttl_stmt_ptr= trav_chain((yyvsp[(4) - (5)].print_stmt));
		basic_count_ax_stmt * count_stmt_ptr= trav_chain((yyvsp[(5) - (5)].count_stmt));

		(yyval.ax) = new ax(ttl_stmt_ptr, count_stmt_ptr, no_count_ax_elems, no_tot_ax_elems, 0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.ax), __LINE__, __FILE__, line_no);
		}
		
		ax_map[(yyvsp[(2) - (5)].name)]=(yyval.ax);
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		free((yyvsp[(2) - (5)].name));
	}
    break;

  case 89:
#line 825 "type.y"
    {
		basic_print_ax_stmt * ttl_stmt_ptr= trav_chain((yyvsp[(7) - (8)].print_stmt));
		basic_count_ax_stmt * count_stmt_ptr= trav_chain((yyvsp[(8) - (8)].count_stmt));
		(yyval.ax) = new ax(ttl_stmt_ptr, count_stmt_ptr, no_count_ax_elems, no_tot_ax_elems, (yyvsp[(5) - (8)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.ax), __LINE__, __FILE__, line_no);
		}
		ax_map[(yyvsp[(2) - (8)].name)]=(yyval.ax);
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		free((yyvsp[(2) - (8)].name));
	}
    break;

  case 90:
#line 837 "type.y"
    {
		cerr << "Error in axis section line: " <<
			line_no << endl;
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		++no_errors;
	}
    break;

  case 92:
#line 847 "type.y"
    {
		//$$=link_chain($1, $2);
	}
    break;

  case 93:
#line 852 "type.y"
    {
		(yyval.stub)=new stub((yyvsp[(1) - (4)].text_buf), (yyvsp[(3) - (4)].ival));
		stub_list.push_back((yyval.stub));
		++ no_count_ax_elems;
		++ no_tot_ax_elems;
	}
    break;

  case 94:
#line 860 "type.y"
    { (yyval.print_stmt)=(yyvsp[(1) - (1)].print_stmt); }
    break;

  case 95:
#line 861 "type.y"
    {
		(yyval.print_stmt)=link_chain((yyvsp[(1) - (2)].print_stmt), (yyvsp[(2) - (2)].print_stmt));
	}
    break;

  case 96:
#line 866 "type.y"
    {
		(yyval.print_stmt) = new ttl_ax_stmt (txt_axstmt,(yyvsp[(3) - (4)].text_buf));
		++no_tot_ax_elems;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.print_stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 97:
#line 875 "type.y"
    {
		(yyval.count_stmt) = (yyvsp[(1) - (1)].count_stmt);
	}
    break;

  case 98:
#line 878 "type.y"
    {
		(yyval.count_stmt)=link_chain((yyvsp[(1) - (2)].count_stmt), (yyvsp[(2) - (2)].count_stmt));
	}
    break;

  case 99:
#line 883 "type.y"
    {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.count_stmt) = new tot_ax_stmt (tot_axstmt,(yyvsp[(3) - (4)].text_buf), 0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.count_stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 100:
#line 891 "type.y"
    {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.count_stmt) = new tot_ax_stmt (tot_axstmt,(yyvsp[(3) - (7)].text_buf), (yyvsp[(6) - (7)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.count_stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 101:
#line 899 "type.y"
    {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.count_stmt) = new count_ax_stmt (cnt_axstmt,(yyvsp[(3) - (7)].text_buf), (yyvsp[(6) - (7)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.count_stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 103:
#line 910 "type.y"
    {
		//stub * stub_ptr = trav_chain($4);
	 	//$$ = new fld_ax_stmt ($2, stub_ptr);
	 	(yyval.count_stmt) = new fld_ax_stmt (fld_axstmt, (yyvsp[(2) - (5)].name), stub_list);
		stub_list.resize(0);
	  }
    break;


/* Line 1267 of yacc.c.  */
#line 2742 "type.c"
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


#line 918 "type.y"



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


