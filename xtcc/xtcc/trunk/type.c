/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

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

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.1"

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
     FNUMBER = 267,
     INUMBER = 268,
     CODELIST = 269,
     LISTA = 270,
     IF = 271,
     ELSE = 272,
     VOID_T = 273,
     INT8_T = 274,
     INT16_T = 275,
     INT32_T = 276,
     FLOAT_T = 277,
     DOUBLE_T = 278,
     AXSTART = 279,
     TABSTART = 280,
     ED_START = 281,
     DATA_STRUCT = 282,
     REC_LEN = 283,
     ED_END = 284,
     TAB = 285,
     COND_START = 286,
     CONTINUE = 287,
     BREAK = 288,
     LOGOR = 289,
     LOGAND = 290,
     NOEQ = 291,
     ISEQ = 292,
     GEQ = 293,
     LEQ = 294,
     NOT = 295,
     UMINUS = 296,
     FUNC_CALL = 297
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
#define FNUMBER 267
#define INUMBER 268
#define CODELIST 269
#define LISTA 270
#define IF 271
#define ELSE 272
#define VOID_T 273
#define INT8_T 274
#define INT16_T 275
#define INT32_T 276
#define FLOAT_T 277
#define DOUBLE_T 278
#define AXSTART 279
#define TABSTART 280
#define ED_START 281
#define DATA_STRUCT 282
#define REC_LEN 283
#define ED_END 284
#define TAB 285
#define COND_START 286
#define CONTINUE 287
#define BREAK 288
#define LOGOR 289
#define LOGAND 290
#define NOEQ 291
#define ISEQ 292
#define GEQ 293
#define LEQ 294
#define NOT 295
#define UMINUS 296
#define FUNC_CALL 297




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

//	struct symtab symtab;
	using namespace std;
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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 101 "type.y"
typedef union YYSTYPE {
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
} YYSTYPE;
/* Line 196 of yacc.c.  */
#line 262 "type.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 219 of yacc.c.  */
#line 274 "type.c"

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T) && (defined (__STDC__) || defined (__cplusplus))
# include <stddef.h> /* INFRINGES ON USER NAME SPACE */
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

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

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if defined (__STDC__) || defined (__cplusplus)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     define YYINCLUDED_STDLIB_H
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2005 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM ((YYSIZE_T) -1)
#  endif
#  ifdef __cplusplus
extern "C" {
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if (! defined (malloc) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if (! defined (free) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifdef __cplusplus
}
#  endif
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
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
      while (0)
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
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   487

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  28
/* YYNRULES -- Number of rules. */
#define YYNRULES  90
/* YYNRULES -- Number of states. */
#define YYNSTATES  216

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    55,    59,     2,
      23,    24,    53,    52,    42,    51,     2,    54,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    60,     5,
      47,    25,    48,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    21,     2,    22,     2,     2,     2,     2,     2,     2,
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
      18,    19,    20,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    43,
      44,    45,    46,    49,    50,    56,    57,    58
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     4,    15,    20,    25,    27,    30,    32,
      34,    36,    38,    40,    42,    44,    46,    47,    55,    59,
      66,    68,    75,    77,    81,    84,    90,    94,    95,    97,
     100,   101,   112,   114,   117,   119,   121,   123,   126,   129,
     131,   134,   139,   147,   157,   163,   171,   184,   188,   190,
     192,   196,   200,   204,   208,   212,   216,   219,   223,   227,
     231,   235,   239,   243,   247,   251,   255,   258,   260,   262,
     264,   269,   276,   281,   283,   287,   289,   292,   297,   305,
     308,   310,   313,   318,   326,   329,   331,   334,   339,   347,
     355
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      62,     0,    -1,    -1,    35,     5,    36,    25,    16,     5,
      63,    34,    64,    37,    -1,    32,     7,    85,     9,    -1,
      33,     7,    83,     9,    -1,    65,    -1,    64,    65,    -1,
      69,    -1,    67,    -1,    26,    -1,    27,    -1,    28,    -1,
      29,    -1,    30,    -1,    31,    -1,    -1,    66,    14,    23,
      71,    24,    68,    79,    -1,    66,    14,     5,    -1,    66,
      14,    21,    16,    22,     5,    -1,    70,    -1,    66,    14,
      23,    71,    24,     5,    -1,    72,    -1,    71,    42,    72,
      -1,    66,    14,    -1,    66,    14,    21,    16,    22,    -1,
      66,    59,    14,    -1,    -1,    74,    -1,    73,    74,    -1,
      -1,    11,    23,    82,     5,    82,     5,    82,    24,    75,
      74,    -1,    77,    -1,    82,     5,    -1,    79,    -1,    69,
      -1,    76,    -1,    41,     5,    -1,    40,     5,    -1,    78,
      -1,     1,     5,    -1,    18,    14,    13,     5,    -1,    18,
      14,    21,    16,    22,    13,     5,    -1,    18,    14,    21,
      16,    42,    16,    22,    13,     5,    -1,    19,    23,    82,
      24,    74,    -1,    19,    23,    82,    24,    74,    20,    74,
      -1,    12,    14,    25,    14,    23,    82,    42,    82,    24,
      60,    16,     5,    -1,    80,    73,     9,    -1,     7,    -1,
      82,    -1,    81,    42,    82,    -1,    82,    52,    82,    -1,
      82,    51,    82,    -1,    82,    53,    82,    -1,    82,    54,
      82,    -1,    82,    55,    82,    -1,    51,    82,    -1,    82,
      47,    82,    -1,    82,    48,    82,    -1,    82,    50,    82,
      -1,    82,    49,    82,    -1,    82,    46,    82,    -1,    82,
      45,    82,    -1,    82,    43,    82,    -1,    82,    44,    82,
      -1,    82,    25,    82,    -1,    56,    82,    -1,    16,    -1,
      15,    -1,    14,    -1,    14,    21,    82,    22,    -1,    14,
      21,    82,    42,    82,    22,    -1,    14,    23,    81,    24,
      -1,    13,    -1,    23,    82,    24,    -1,    84,    -1,    83,
      84,    -1,    38,    14,    14,     5,    -1,    38,    14,    14,
       5,    39,    82,     5,    -1,     1,     5,    -1,    86,    -1,
      85,    86,    -1,     6,    14,     5,    87,    -1,     6,    14,
       5,    39,    82,     5,    87,    -1,     1,     5,    -1,    88,
      -1,    87,    88,    -1,     4,     5,    13,     5,    -1,     4,
       5,    13,     5,    39,    82,     5,    -1,     8,     5,    13,
       5,    39,    82,     5,    -1,    10,     5,    13,     5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   198,   198,   197,   209,   212,   217,   220,   225,   228,
     233,   234,   235,   236,   237,   238,   243,   243,   280,   285,
     300,   306,   320,   324,   331,   339,   349,   359,   365,   373,
     378,   378,   395,   396,   410,   413,   416,   417,   427,   437,
     438,   449,   478,   508,   536,   551,   568,   636,   667,   695,
     696,   701,   708,   715,   722,   729,   743,   754,   761,   768,
     775,   782,   789,   796,   803,   810,   829,   840,   847,   853,
     870,   910,   967,  1006,  1012,  1020,  1025,  1033,  1043,  1052,
    1060,  1062,  1066,  1081,  1095,  1106,  1109,  1114,  1119,  1124,
    1129
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONVERT", "TOT", "';'", "AX", "'{'",
  "CNT", "'}'", "TTL", "FOR", "FLD", "TEXT", "NAME", "FNUMBER", "INUMBER",
  "CODELIST", "LISTA", "IF", "ELSE", "'['", "']'", "'('", "')'", "'='",
  "VOID_T", "INT8_T", "INT16_T", "INT32_T", "FLOAT_T", "DOUBLE_T",
  "AXSTART", "TABSTART", "ED_START", "DATA_STRUCT", "REC_LEN", "ED_END",
  "TAB", "COND_START", "CONTINUE", "BREAK", "','", "LOGOR", "LOGAND",
  "NOEQ", "ISEQ", "'<'", "'>'", "GEQ", "LEQ", "'-'", "'+'", "'*'", "'/'",
  "'%'", "NOT", "UMINUS", "FUNC_CALL", "'&'", "':'", "$accept", "prog",
  "@1", "top_level_item_list", "top_level_item", "xtcc_type", "func_defn",
  "@2", "decl", "func_decl", "decl_comma_list", "var_decl",
  "statement_list", "statement", "@3", "list_stmt", "if_stmt", "fld_stmt",
  "compound_stmt", "open_curly", "expr_list", "expression", "tab_list",
  "tab_defn", "ax_list", "ax_defn", "ax_stmt_list", "ax_stmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,    59,   260,   123,   261,   125,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,    91,    93,    40,    41,    61,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,    44,   289,   290,   291,   292,    60,    62,   293,
     294,    45,    43,    42,    47,    37,   295,   296,   297,    38,
      58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    61,    63,    62,    62,    62,    64,    64,    65,    65,
      66,    66,    66,    66,    66,    66,    68,    67,    69,    69,
      69,    70,    71,    71,    72,    72,    72,    72,    73,    73,
      75,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    76,    76,    76,    77,    77,    78,    79,    80,    81,
      81,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    83,    83,    84,    84,    84,
      85,    85,    86,    86,    86,    87,    87,    88,    88,    88,
      88
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,    10,     4,     4,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     7,     3,     6,
       1,     6,     1,     3,     2,     5,     3,     0,     1,     2,
       0,    10,     1,     2,     1,     1,     1,     2,     2,     1,
       2,     4,     7,     9,     5,     7,    12,     3,     1,     1,
       3,     3,     3,     3,     3,     3,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     1,     1,     1,
       4,     6,     4,     1,     3,     1,     2,     4,     7,     2,
       1,     2,     4,     7,     2,     1,     2,     4,     7,     7,
       4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     1,     0,
       0,     0,    80,     0,     0,     0,    75,     0,    84,     0,
       4,    81,    79,     0,     5,    76,     0,     0,     0,     0,
       0,     0,     0,     0,    82,    85,    77,     2,     0,     0,
       0,    73,    69,    68,    67,     0,     0,     0,     0,    86,
       0,     0,     0,     0,     0,     0,     0,     0,    56,    66,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    87,     0,    90,
       0,     0,    49,    74,    83,    65,    63,    64,    62,    61,
      57,    58,    60,    59,    52,    51,    53,    54,    55,    78,
      10,    11,    12,    13,    14,    15,     0,     6,     0,     9,
       8,    20,     0,     0,    70,     0,    72,     0,     3,     7,
       0,     0,     0,     0,    50,    18,     0,    27,    88,    89,
      71,     0,     0,     0,    22,     0,    24,     0,    16,    27,
      19,     0,    26,    21,     0,    23,     0,    48,    17,     0,
      25,     0,     0,     0,     0,     0,     0,     0,     0,    35,
       0,    28,    36,    32,    39,    34,     0,    40,     0,     0,
       0,     0,    38,    37,     0,    47,    29,    33,     0,     0,
       0,     0,     0,    27,     0,     0,    41,     0,     0,     0,
       0,     0,     0,     0,    44,     0,     0,     0,     0,     0,
       0,     0,     0,    42,     0,    45,    30,     0,     0,     0,
       0,    43,    31,     0,     0,    46
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     4,    51,   106,   107,   158,   109,   144,   159,   111,
     133,   134,   160,   161,   209,   162,   163,   164,   165,   149,
      81,   166,    15,    16,    11,    12,    34,    35
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -92
static const short int yypact[] =
{
     124,    -6,    20,    -1,    65,    61,     4,    74,   -92,   109,
      67,   114,   -92,   116,   105,    10,   -92,   100,   -92,   129,
     -92,   -92,   -92,   115,   -92,   -92,   120,    16,   132,   140,
     142,   150,   155,    -7,   144,   -92,   110,   -92,   148,   149,
     151,   -92,    77,   -92,   -92,    -7,    -7,    -7,   128,   -92,
      -7,   131,   162,   163,   165,    -7,    -7,   337,   -92,   -92,
     144,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,   141,   185,   190,   195,   -92,
     304,     1,   432,   -92,   144,   432,   154,   173,   215,   215,
     224,   224,   224,   224,   178,   178,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   113,   -92,   257,   -92,
     -92,   -92,    -7,    -7,   -92,    -7,   -92,    -7,   -92,   -92,
     103,   192,   205,   354,   432,   -92,   264,   185,   -92,   -92,
     -92,   250,   -12,    69,   -92,   268,   261,   270,   278,   185,
     -92,   271,   -92,   -92,   279,   -92,   263,   -92,   -92,    76,
     -92,   283,   266,   276,   277,   272,   287,   288,   282,   -92,
      45,   -92,   -92,   -92,   -92,   -92,   256,   -92,    -7,   273,
      -3,    -7,   -92,   -92,   107,   -92,   -92,   -92,   269,   313,
     292,   312,   369,   185,    -7,   307,   -92,    28,    76,    89,
     320,    -7,   318,   316,   314,   278,    -7,   417,   328,   315,
      76,   386,    -7,   -92,   322,   -92,   -92,   401,   331,    76,
     280,   -92,   -92,   323,   333,   -92
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
     -92,   -92,   -92,   -92,   235,   -61,   -92,   -92,   -55,   -92,
     159,   204,   -92,   -91,   -92,   -92,   -92,   -92,   200,   -92,
     -92,   -33,   -92,   345,   -92,   366,   335,   -31
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      48,     5,   136,    49,     7,    13,    41,    42,    43,    44,
     180,    13,    57,    58,    59,   108,    45,    75,   181,    24,
      30,   110,    80,    82,    31,   116,    32,     6,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    14,   117,    46,   108,   151,   137,    14,    47,
     192,   110,   147,    49,   175,    33,   152,   153,    41,    42,
      43,    44,     9,   154,   155,     8,   132,    10,    45,   176,
     193,   100,   101,   102,   103,   104,   105,   151,   132,   121,
     122,    19,   123,   147,   124,   156,   157,   152,   153,    41,
      42,    43,    44,   138,   154,   155,    46,   194,    55,    45,
      56,    47,   100,   101,   102,   103,   104,   105,   125,   205,
      17,   139,   125,   195,    18,     9,   156,   157,   212,    23,
      10,    22,   132,    20,   126,    26,   127,    46,   126,    28,
     183,   139,    47,    60,    27,   178,    29,    36,   182,   100,
     101,   102,   103,   104,   105,    37,    99,    38,    30,    50,
     118,   190,    31,    61,    32,    39,     1,     2,   197,     3,
      40,    52,    53,   201,    54,    76,    61,    77,    78,   207,
      79,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,   128,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
     129,   100,   101,   102,   103,   104,   105,    61,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,   112,
      61,    72,    73,    74,   113,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,   177,    66,    67,    68,    69,    70,    71,    72,    73,
      74,   120,   135,   140,   184,    70,    71,    72,    73,    74,
     131,    61,   141,   143,   142,   150,   147,   146,   167,   168,
     169,   170,   172,   173,    61,   171,   174,   186,   179,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,   196,   114,   185,   187,    61,
     191,   198,   199,   203,   200,   208,   211,   204,   215,   214,
     213,   119,   189,   145,   148,    61,   115,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      25,    83,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,   130,    21,     0,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,   188,    61,    84,     0,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
     206,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,   210,    61,     0,     0,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    61,     0,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    61,     0,   202,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,     0,     0,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74
};

static const short int yycheck[] =
{
      33,     7,    14,    34,     5,     1,    13,    14,    15,    16,
      13,     1,    45,    46,    47,    76,    23,    50,    21,     9,
       4,    76,    55,    56,     8,    24,    10,     7,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    38,    42,    51,   106,     1,    59,    38,    56,
      22,   106,     7,    84,     9,    39,    11,    12,    13,    14,
      15,    16,     1,    18,    19,     0,   127,     6,    23,   160,
      42,    26,    27,    28,    29,    30,    31,     1,   139,   112,
     113,    14,   115,     7,   117,    40,    41,    11,    12,    13,
      14,    15,    16,    24,    18,    19,    51,   188,    21,    23,
      23,    56,    26,    27,    28,    29,    30,    31,     5,   200,
      36,    42,     5,    24,     5,     1,    40,    41,   209,    14,
       6,     5,   183,     9,    21,    25,    23,    51,    21,    14,
      23,    42,    56,     5,     5,   168,    16,     5,   171,    26,
      27,    28,    29,    30,    31,     5,     5,     5,     4,    39,
      37,   184,     8,    25,    10,     5,    32,    33,   191,    35,
       5,    13,    13,   196,    13,    34,    25,     5,     5,   202,
       5,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,     5,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
       5,    26,    27,    28,    29,    30,    31,    25,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    39,
      25,    53,    54,    55,    39,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,     5,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    14,    22,     5,     5,    51,    52,    53,    54,    55,
      16,    25,    21,     5,    14,    22,     7,    16,     5,    23,
      14,    14,     5,     5,    25,    23,    14,     5,    25,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,     5,    22,    14,    16,    25,
      23,    13,    16,     5,    20,    13,     5,    22,     5,    16,
      60,   106,   183,   139,   144,    25,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      15,    24,    25,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    22,    11,    -1,    25,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    24,    25,    60,    -1,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      24,    25,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    24,    25,    -1,    -1,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    25,    -1,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    25,    -1,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    -1,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    32,    33,    35,    62,     7,     7,     5,     0,     1,
       6,    85,    86,     1,    38,    83,    84,    36,     5,    14,
       9,    86,     5,    14,     9,    84,    25,     5,    14,    16,
       4,     8,    10,    39,    87,    88,     5,     5,     5,     5,
       5,    13,    14,    15,    16,    23,    51,    56,    82,    88,
      39,    63,    13,    13,    13,    21,    23,    82,    82,    82,
       5,    25,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    82,    34,     5,     5,     5,
      82,    81,    82,    24,    87,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,     5,
      26,    27,    28,    29,    30,    31,    64,    65,    66,    67,
      69,    70,    39,    39,    22,    42,    24,    42,    37,    65,
      14,    82,    82,    82,    82,     5,    21,    23,     5,     5,
      22,    16,    66,    71,    72,    22,    14,    59,    24,    42,
       5,    21,    14,     5,    68,    72,    16,     7,    79,    80,
      22,     1,    11,    12,    18,    19,    40,    41,    66,    69,
      73,    74,    76,    77,    78,    79,    82,     5,    23,    14,
      14,    23,     5,     5,    14,     9,    74,     5,    82,    25,
      13,    21,    82,    23,     5,    14,     5,    16,    24,    71,
      82,    23,    22,    42,    74,    24,     5,    82,    13,    16,
      20,    82,    42,     5,    22,    74,    24,    82,    13,    75,
      24,     5,    74,    60,    16,     5
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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
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
    while (0)
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
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr,					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname[yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

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
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
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
      size_t yyn = 0;
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

#endif /* YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
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
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
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
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()
    ;
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

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

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
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


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
	short int *yyss1 = yyss;
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

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

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

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
#line 198 "type.y"
    {	char * c_arr="c";  
		rec_len=(yyvsp[-1].ival); 
		active_scope->insert(c_arr, INT8_ARR_TYPE, rec_len, 0);
	}
    break;

  case 3:
#line 202 "type.y"
    {
		tree_root = trav_chain((yyvsp[-1].stmt));
		if(tree_root==0){
			cerr << "tree_root =0 : core dump expected" << endl;
		}
		return 0;
	}
    break;

  case 4:
#line 209 "type.y"
    {
		return 0;
	}
    break;

  case 5:
#line 212 "type.y"
    {
		return 0;
	}
    break;

  case 6:
#line 217 "type.y"
    {
		(yyval.stmt)=(yyvsp[0].stmt);
	}
    break;

  case 7:
#line 220 "type.y"
    {
		(yyval.stmt)=link_chain((yyvsp[-1].stmt),(yyvsp[0].stmt));
	}
    break;

  case 8:
#line 225 "type.y"
    {
			(yyval.stmt)=(yyvsp[0].stmt);
	}
    break;

  case 9:
#line 228 "type.y"
    {
		(yyval.stmt)=(yyvsp[0].stmt);
	}
    break;

  case 16:
#line 243 "type.y"
    {
		string func_name_index((yyvsp[-3].name));
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
#line 252 "type.y"
    {
		struct cmpd_stmt* c_stmt= (yyvsp[0].c_stmt);
		if(c_stmt==0){
			cout << "c_stmt==0" << endl;
		} else {
			cout << "func_body: is valid " << endl;
		}
		struct scope *sc=c_stmt->sc;
		struct var_list * v_list=trav_chain((yyvsp[-3].v_list));
		struct stmt* func_body=(yyvsp[0].c_stmt);
		string search_for=(yyvsp[-5].name);
		datatype return_type=(yyvsp[-6].dt);
		/*$$=new func_stmt(FUNC_DEFN, line_no, sc, v_list, cmpd_stmt, search_for, return_type);
			// This gives an error - we have to fool the compiler*/
		(yyval.stmt)=new func_stmt(FUNC_DEFN, line_no, sc, v_list, func_body, search_for, return_type);
		void *ptr=(yyval.stmt);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		// Note that the declaration already has a parameter list
		// the constructor uses the parameter list - name and type to verify everything
		// but doesnt need the parameter list any more - so we should delete it 
		// - took me a while to figure out this memory leak
		delete v_list;
		free((yyvsp[-5].name));
	}
    break;

  case 18:
#line 280 "type.y"
    {
		//cout << "creating simple var of type: " << $1 << endl;
		(yyval.stmt) = active_scope->insert((yyvsp[-1].name), (yyvsp[-2].dt), line_no);
		free((yyvsp[-1].name));
	}
    break;

  case 19:
#line 285 "type.y"
    {
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		//cout << "creating arr var of type: " << $1 << endl;
		datatype dt=datatype(INT8_ARR_TYPE+((yyvsp[-5].dt)-INT8_TYPE));
		(yyval.stmt) = active_scope->insert((yyvsp[-4].name), dt, (yyvsp[-2].ival), line_no);
		free((yyvsp[-4].name));
	}
    break;

  case 20:
#line 300 "type.y"
    {
		(yyval.stmt)=(yyvsp[0].stmt);
	}
    break;

  case 21:
#line 306 "type.y"
    {
		char *name=(yyvsp[-4].name);
		//char *name=strdup($2);
		struct var_list* v_list=trav_chain((yyvsp[-2].v_list));
		datatype return_type=(yyvsp[-5].dt);
		(yyval.stmt)=new func_decl_stmt( FUNC_TYPE, line_no, name,  v_list, return_type);
		void *ptr=(yyval.stmt);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		//free(name);
	}
    break;

  case 22:
#line 320 "type.y"
    {
		 (yyval.v_list)=(yyvsp[0].v_list);
		 //cout << "got decl_comma_list : " << endl;
	}
    break;

  case 23:
#line 324 "type.y"
    {
		(yyval.v_list)=link_chain((yyvsp[-2].v_list),(yyvsp[0].v_list));
		//cout << "chaining var_decl : " << endl;
	}
    break;

  case 24:
#line 331 "type.y"
    {
		//cout << "creating simple var of type: " << $1 << endl;
		(yyval.v_list)=new var_list((yyvsp[-1].dt), (yyvsp[0].name));
		void *ptr=(yyval.v_list);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		free((yyvsp[0].name));
	}
    break;

  case 25:
#line 339 "type.y"
    {
		/* Neil - I need to fix this */
		//cout << "creating arr var of type: " << $1 << endl;
		datatype dt=datatype(INT8_ARR_TYPE+((yyvsp[-4].dt)-INT8_TYPE));
		(yyval.v_list)=new var_list(dt, (yyvsp[-3].name), (yyvsp[-1].ival));
		void *ptr=(yyval.v_list);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		free((yyvsp[-3].name));
	}
    break;

  case 26:
#line 349 "type.y"
    {
		//cout << "creating ref var of type: " << $1 << endl;
		datatype dt=datatype(INT8_REF_TYPE+((yyvsp[-2].dt)-INT8_TYPE));
		(yyval.v_list)=new var_list(dt, (yyvsp[0].name));
		void *ptr=(yyval.v_list);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		free((yyvsp[0].name));
	}
    break;

  case 27:
#line 359 "type.y"
    {
		//$$=new var_list(uninit, "empty");
		(yyval.v_list)=0;
		}
    break;

  case 28:
#line 365 "type.y"
    {
		(yyval.stmt)=(yyvsp[0].stmt); 
		if(flag_next_stmt_start_of_block){
			blk_heads.push_back((yyvsp[0].stmt));
			//start_of_blk=$1;
			flag_next_stmt_start_of_block=false;
		}
	}
    break;

  case 29:
#line 373 "type.y"
    {
		(yyval.stmt)=link_chain((yyvsp[-1].stmt),(yyvsp[0].stmt));
	}
    break;

  case 30:
#line 378 "type.y"
    { ++in_a_loop;}
    break;

  case 31:
#line 378 "type.y"
    {
		   if((yyvsp[-7].expr)->type==VOID_TYPE||(yyvsp[-5].expr)->type==VOID_TYPE||(yyvsp[-3].expr)->type==VOID_TYPE 
			){
			   cerr << "For condition has VOID_TYPE or ERROR_TYPE" << endl;
			   ++ no_errors;
			   (yyval.stmt)=new struct err_stmt(line_no);
			   void *ptr=(yyval.stmt);
			   mem_addr_tab m1(ptr, line_no);
			   mem_addr.push_back(m1);
		   } else{
			   (yyval.stmt) = new struct for_stmt(FOR_STMT, line_no, (yyvsp[-7].expr), (yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[0].stmt));
			   void *ptr=(yyval.stmt);
			   mem_addr_tab m1(ptr, line_no);
			   mem_addr.push_back(m1);
		   }
		   --in_a_loop;
	}
    break;

  case 33:
#line 396 "type.y"
    { 
		if((yyvsp[-1].expr)->isvalid()){
			(yyval.stmt) = new expr_stmt(TEXPR_STMT, line_no, (yyvsp[-1].expr));
			void *ptr=(yyval.stmt);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			(yyval.stmt) = new expr_stmt(ERROR_TYPE, line_no, (yyvsp[-1].expr));
			void *ptr=(yyval.stmt);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		}
		//printf("= %g\n", $1); 
	}
    break;

  case 34:
#line 410 "type.y"
    {
		(yyval.stmt)=(yyvsp[0].c_stmt);
	}
    break;

  case 35:
#line 413 "type.y"
    {
		(yyval.stmt)=(yyvsp[0].stmt);
	}
    break;

  case 37:
#line 417 "type.y"
    {
		(yyval.stmt)=new struct break_stmt(BREAK_STMT, line_no);
		void *ptr=(yyval.stmt);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if (!in_a_loop){
			cerr << "break statement outside a loop: line_no: " << line_no<< endl;
			++no_errors;
		}
	}
    break;

  case 38:
#line 427 "type.y"
    {
		(yyval.stmt)=new struct continue_stmt(CONTINUE_STMT, line_no);
		void *ptr=(yyval.stmt);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if (!in_a_loop){
			cerr << "continue statement outside a loop: line_no: " << line_no<< endl;
			++no_errors;
		}
	}
    break;

  case 40:
#line 438 "type.y"
    {
		cerr << "statement missing ';' around line_no: " << line_no << endl;
		++no_errors;
		(yyval.stmt) = new struct err_stmt(line_no);
		void *ptr=(yyval.stmt);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		yyerrok;
	}
    break;

  case 41:
#line 449 "type.y"
    {
		map<string,symtab_ent*>::iterator sym_it = find_in_symtab((yyvsp[-2].name));
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << (yyvsp[-2].name) << " not found in symbol table" << endl;
			++no_errors;
			(yyval.stmt)=new err_stmt(line_no);
			void *ptr=(yyval.stmt);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->type;
			if( !(name_type>=INT8_TYPE&&name_type<=DOUBLE_TYPE)){
				cerr << "NAME: "<< (yyvsp[-2].name) 
					<< " should be of basic type: " << line_no << endl;
				++no_errors;
				(yyval.stmt)=new struct err_stmt(line_no);
				void *ptr=(yyval.stmt);
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			} else {
				(yyval.stmt)=new list_stmt(LISTA_BASIC_TYPE_STMT, line_no, se);
				void *ptr=(yyval.stmt);
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
		free((yyvsp[-2].name));
	}
    break;

  case 42:
#line 478 "type.y"
    {
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab((yyvsp[-5].name));
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << (yyvsp[-5].name) << " not found in symbol table" << endl;
			++no_errors;
			(yyval.stmt)=new err_stmt(line_no);
			void *ptr=(yyval.stmt);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->type;
			if( !(name_type>=INT8_ARR_TYPE&&name_type<=DOUBLE_ARR_TYPE)){
				cerr << "NAME: "<< (yyvsp[-5].name) 
					<< " is not of array type: line_no:" << line_no << endl;
				++no_errors;
				(yyval.stmt)=new err_stmt(line_no);
				void *ptr=(yyval.stmt);
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			} else {
				(yyval.stmt)=new list_stmt( LISTA_BASIC_ARRTYPE_STMT_1INDEX, line_no, se, (yyvsp[-3].ival), -1, string((yyvsp[-1].text_buf)));
				void *ptr=(yyval.stmt);
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
		free((yyvsp[-5].name));
	}
    break;

  case 43:
#line 508 "type.y"
    {
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab((yyvsp[-7].name));
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << (yyvsp[-7].name) << " not found in symbol table" << endl;
			++no_errors;
			(yyval.stmt)=new err_stmt(line_no);
			void *ptr=(yyval.stmt);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->type;
			if( !(name_type==INT8_ARR_TYPE||name_type==INT8_TYPE)){
				cerr << "NAME: "<< (yyvsp[-7].name) 
					<< " is not of char array type: line_no:" << line_no << endl;
				++no_errors;
			} else {
				(yyval.stmt)=new list_stmt( LISTA_BASIC_ARRTYPE_STMT_2INDEX, line_no, se, (yyvsp[-5].ival), (yyvsp[-3].ival), string((yyvsp[-1].text_buf)));
				void *ptr=(yyval.stmt);
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
		free((yyvsp[-7].name));	
	}
    break;

  case 44:
#line 536 "type.y"
    {
		if((yyvsp[-2].expr)->type==VOID_TYPE || (yyvsp[-2].expr)->type==ERROR_TYPE){
			++no_errors;
			(yyval.stmt)=new err_stmt(line_no);
			void *ptr=(yyval.stmt);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
			cerr << "Error: If condition has void or Error type:" << line_no << endl;
		} else {
			(yyval.stmt)=new if_stmt(IFE_STMT,line_no,(yyvsp[-2].expr),(yyvsp[0].stmt),0);
			void *ptr=(yyval.stmt);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		}
	}
    break;

  case 45:
#line 551 "type.y"
    {
		if((yyvsp[-4].expr)->type==VOID_TYPE || (yyvsp[-4].expr)->type==ERROR_TYPE){
			++no_errors;
			(yyval.stmt)=new err_stmt(line_no);
			void *ptr=(yyval.stmt);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
			cerr << "Error: If condition has void or Error type:" << line_no << endl;
		} else {
			(yyval.stmt)=new if_stmt(IFE_STMT, line_no,(yyvsp[-4].expr),(yyvsp[-2].stmt),(yyvsp[0].stmt));
			void *ptr=(yyval.stmt);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		}
	}
    break;

  case 46:
#line 568 "type.y"
    {
		expr* start_col=(yyvsp[-6].expr);
		expr* end_col=(yyvsp[-4].expr);
		int width=(yyvsp[-1].ival);
		map<string,symtab_ent*>::iterator sym_it1 = find_in_symtab((yyvsp[-10].name));
		map<string,symtab_ent*>::iterator sym_it2 = find_in_symtab((yyvsp[-8].name));
		if(!(	(start_col->type>=INT8_TYPE && start_col->type<=INT32_TYPE)&&
			(end_col->type>=INT8_TYPE && end_col->type<=INT32_TYPE)) ){
			cerr << "start_col, end_col expressions must be of integer type line_no:" 
				<< line_no << endl;
			++no_errors;
			(yyval.stmt)=new err_stmt(line_no);
			void *ptr=(yyval.stmt);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else if(sym_it1==active_scope->sym_tab.end()){
			cerr << "Error: could not find:" << (yyvsp[-10].name)<<"  in symbol table: lineno: " << line_no << "\n";
			++no_errors;
			(yyval.stmt)=new err_stmt(line_no);
			void *ptr=(yyval.stmt);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else if (sym_it2==active_scope->sym_tab.end()){
			cerr << "Error: could not find:" << (yyvsp[-8].name)
				<< " in symbol table: lineno: " << line_no << "\n";
			++no_errors;
			(yyval.stmt)=new err_stmt(line_no);
			void *ptr=(yyval.stmt);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			// first some validation checks
			//datatype type1 = sym_it1->type;
			if( !( 
				(sym_it1->second->type == INT8_ARR_TYPE) &&
				(sym_it2->second->type >= INT8_ARR_TYPE) &&
				(sym_it2->second->type <= INT32_ARR_TYPE)) ) {
				/* add code here */
				++no_errors;
				(yyval.stmt) = new err_stmt(line_no);
				void *ptr=(yyval.stmt);
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			} else if (!(width==sizeof(INT8_TYPE) || width==sizeof(INT16_TYPE)
					||width==sizeof(INT32_TYPE))	){
				cerr << "width of field can only be : " 
					<< sizeof(INT8_TYPE) << " or " << sizeof(INT16_TYPE) << " or "
					<< sizeof(INT32_TYPE) << endl;
				++no_errors;
				(yyval.stmt) = new err_stmt(line_no);
				void *ptr=(yyval.stmt);
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			} else {
				//everything is ok
				// since start_col and end_col can be exprs
				// we have to move some checks to runtime environment
				(yyval.stmt) = new fld_stmt(sym_it1->second, sym_it2->second, 
					start_col, end_col, width);
				void *ptr=(yyval.stmt);
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
	}
    break;

  case 47:
#line 636 "type.y"
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
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else { active_scope = active_scope_list[tmp]; }
		struct stmt* head_of_this_chain=blk_heads.back();
		if(  head_of_this_chain==0){
			cerr << "Error in compiler : cmpd_bdy:  " << __FILE__ << __LINE__ << endl;
			++no_errors;
		} else {
			(yyvsp[-2].c_stmt)->cmpd_bdy = head_of_this_chain;
			blk_heads.pop_back();
		}
		
		(yyval.c_stmt)=(yyvsp[-2].c_stmt);
	}
    break;

  case 48:
#line 667 "type.y"
    {
			cout << "In open_curly: " << endl;
		++nest_lev;
		(yyval.c_stmt) = new cmpd_stmt(CMPD_STMT, line_no, flag_cmpd_stmt_is_a_func_body);
		void *ptr=(yyval.c_stmt);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if(flag_cmpd_stmt_is_a_func_body>=0){
			(yyval.c_stmt)->sc=func_info_table[flag_cmpd_stmt_is_a_func_body]->func_scope;
			// reset the flag
			flag_cmpd_stmt_is_a_func_body=-1;
		} else {
			(yyval.c_stmt)->sc= new scope();
			void *ptr=(yyval.c_stmt);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		}
		flag_next_stmt_start_of_block=true;
		//cout << "open_curly: cmpd_stmt: " << $$ << endl;
		//cout << "pushed active_scope: " << active_scope << endl;
		//active_scope_list.push_back(active_scope);
		active_scope_list.push_back((yyval.c_stmt)->sc);
		active_scope = (yyval.c_stmt)->sc;
		//cout << "active_scope: " << active_scope << endl;
	}
    break;

  case 49:
#line 695 "type.y"
    { (yyval.expr)=(yyvsp[0].expr); }
    break;

  case 50:
#line 696 "type.y"
    {
		(yyval.expr)=link_chain((yyvsp[-2].expr),(yyvsp[0].expr));
	}
    break;

  case 51:
#line 701 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[-2].expr), (yyvsp[0].expr), oper_plus);
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type, (yyval.expr)->type);
	}
    break;

  case 52:
#line 708 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[-2].expr), (yyvsp[0].expr), oper_minus);
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type, (yyval.expr)->type);
	}
    break;

  case 53:
#line 715 "type.y"
    { 
		(yyval.expr)=new bin_expr((yyvsp[-2].expr), (yyvsp[0].expr), oper_mult);
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type, (yyval.expr)->type);
	}
    break;

  case 54:
#line 722 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[-2].expr), (yyvsp[0].expr), oper_div);
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type, (yyval.expr)->type);
	}
    break;

  case 55:
#line 729 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[-2].expr), (yyvsp[0].expr), oper_mod);
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if(!(((yyvsp[-2].expr)->type >= INT8_TYPE && (yyvsp[-2].expr)->type<=INT32_TYPE)
				&&
			((yyvsp[0].expr)->type>=INT8_TYPE && (yyvsp[0].expr)->type<=INT32_TYPE))){
				cerr << " operands of % should be of type int or char only" << endl;
				++no_errors;
				(yyval.expr)->type=ERROR_TYPE;
		}
		void_check((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type, (yyval.expr)->type);
	}
    break;

  case 56:
#line 743 "type.y"
    {
		(yyval.expr) = new un_expr((yyvsp[0].expr), oper_umin);
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if((yyvsp[0].expr)->type==VOID_TYPE){
			cerr << "line_no: " << line_no << " expression of void type: check if you are calling a void function on either side" << endl;
			(yyval.expr)->type=ERROR_TYPE;
			++no_errors;
		}
	}
    break;

  case 57:
#line 754 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[-2].expr), (yyvsp[0].expr), oper_lt);
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type, (yyval.expr)->type);
	}
    break;

  case 58:
#line 761 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[-2].expr), (yyvsp[0].expr), oper_gt);
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type, (yyval.expr)->type);
	}
    break;

  case 59:
#line 768 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[-2].expr), (yyvsp[0].expr), oper_le);
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type, (yyval.expr)->type);
	}
    break;

  case 60:
#line 775 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[-2].expr), (yyvsp[0].expr), oper_ge);
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type, (yyval.expr)->type);
	}
    break;

  case 61:
#line 782 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[-2].expr), (yyvsp[0].expr), oper_iseq);
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type, (yyval.expr)->type);
	}
    break;

  case 62:
#line 789 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[-2].expr), (yyvsp[0].expr), oper_isneq);
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type, (yyval.expr)->type);
	}
    break;

  case 63:
#line 796 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[-2].expr), (yyvsp[0].expr), oper_or);
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type, (yyval.expr)->type);
	}
    break;

  case 64:
#line 803 "type.y"
    {
		(yyval.expr)=new bin_expr((yyvsp[-2].expr), (yyvsp[0].expr), oper_and);
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type, (yyval.expr)->type);
	}
    break;

  case 65:
#line 810 "type.y"
    {
		datatype typ1=(yyvsp[-2].expr)->type;
		datatype typ2=(yyvsp[0].expr)->type;
		cout << " oper_assgn: LHS type" << typ1 << " RHS type: " << typ2 << endl;
		bool b1=check_type_compat(typ1, typ2)&& (yyvsp[-2].expr)->is_lvalue();
		if((yyvsp[-2].expr)->is_lvalue()){
			(yyval.expr) = new bin_expr((yyvsp[-2].expr), (yyvsp[0].expr), oper_assgn);
			void *ptr=(yyval.expr);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			(yyval.expr) = new un2_expr(ERROR_TYPE);
			void *ptr=(yyval.expr);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
			++no_errors;
			cerr << "oper_assgn error on line: " << line_no<< endl;
		}
	}
    break;

  case 66:
#line 829 "type.y"
    {
		(yyval.expr) = new un_expr((yyvsp[0].expr), oper_not);
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if((yyvsp[0].expr)->type==VOID_TYPE){
			cerr << "line_no: " << line_no << " expression of void type: applying operator ! to void expr" << endl;
			(yyval.expr)->type=ERROR_TYPE;
			++no_errors;
		}
	}
    break;

  case 67:
#line 840 "type.y"
    {
		(yyval.expr) = new un2_expr((yyvsp[0].ival));
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		//cerr << "type.y: parsed integer: type" << $$->type << endl;
	}
    break;

  case 68:
#line 847 "type.y"
    {
		(yyval.expr) = new un2_expr((yyvsp[0].dval));
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
	}
    break;

  case 69:
#line 853 "type.y"
    {
		map<string,symtab_ent*>::iterator sym_it = find_in_symtab((yyvsp[0].name));
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "Error: could not find:" << (yyvsp[0].name)<<"  in symbol table: lineno: " << line_no << "\n";
			++no_errors;
			(yyval.expr) = new un2_expr(ERROR_TYPE);
			void *ptr=(yyval.expr);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			(yyval.expr) = new un2_expr(sym_it->second );
			void *ptr=(yyval.expr);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		}
		free((yyvsp[0].name));
	}
    break;

  case 70:
#line 870 "type.y"
    {
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab((yyvsp[-3].name));
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "Error: Array indexing expr could not find:" << (yyvsp[-3].name)<<"  in symbol table: lineno: " << line_no << "\n";
			++no_errors;
			(yyval.expr) = new un2_expr(ERROR_TYPE);
			void *ptr=(yyval.expr);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			symtab_ent* se=sym_it->second;

			datatype e_type=(yyvsp[-1].expr)->type;
			if(e_type>=INT8_TYPE && e_type <=INT32_TYPE){
				datatype nametype =arr_deref_type(se->type);
				if(nametype==ERROR_TYPE) {
					cerr << "ERROR: Variable being indexed not of Array Type : Error: lineno: " << line_no << "\n";
					++no_errors;
					(yyval.expr) = new un2_expr(ERROR_TYPE);
					void *ptr=(yyval.expr);
					mem_addr_tab m1(ptr, line_no);
					mem_addr.push_back(m1);
				} else {
					(yyval.expr) = new un2_expr(oper_arrderef, nametype,  se, (yyvsp[-1].expr));
					void *ptr=(yyval.expr);
					mem_addr_tab m1(ptr, line_no);
					mem_addr.push_back(m1);
				}
			} else {
				cerr << "ERROR: Array index not of Type Int : Error: lineno: " << line_no << "\n";
				++no_errors;
				(yyval.expr) = new un2_expr(ERROR_TYPE);
				void *ptr=(yyval.expr);
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
		free((yyvsp[-3].name));
	}
    break;

  case 71:
#line 910 "type.y"
    {
		symtab_ent* se=0;
		map<string,symtab_ent*>::iterator sym_it1 = find_in_symtab((yyvsp[-5].name));
		if( sym_it1==active_scope->sym_tab.end()) {
			cerr << "Not able to find :" << (yyvsp[-5].name) << " in symbol table: line_no" 
				<< line_no
				<< endl;
			++no_errors;
		} else {
			se=sym_it1->second;
		}
		if( !(se)){
			cerr << "Error: could not find name " << (yyvsp[-5].name) << "  in expr " 
				<< "oper_blk_arr_assgn: " << " line_no: " << line_no;
				++no_errors;
			(yyval.expr) = new un2_expr(ERROR_TYPE);
			void *ptr=(yyval.expr);
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} /*else if(!(lse->type==INT32_TYPE || lse->type==FLOAT_TYPE)){
			cerr << "ERROR: LHS:  " << $1 << ":line_no:" << line_no 
				<< " should be of type float or int"
				<< endl;
			cerr << "lse type: " << lse->type << endl;
			++no_errors;
			$$=new struct err_stmt(line_no);
		}*/ else {
			datatype e_type1=(yyvsp[-3].expr)->type;
			datatype e_type2=(yyvsp[-1].expr)->type;
			if( (e_type1>=INT8_TYPE && e_type1 <=INT32_TYPE) && 
					(e_type2>=INT8_TYPE && e_type2<=INT32_TYPE)){
				datatype d1=arr_deref_type(se->type);
				if(d1==ERROR_TYPE){
					(yyval.expr) = new un2_expr(ERROR_TYPE);
					void *ptr=(yyval.expr);
					mem_addr_tab m1(ptr, line_no);
					mem_addr.push_back(m1);
					cerr << "Type Error:  x: lineno: " << line_no << "\n";
					++no_errors;
				} else {
					(yyval.expr) = new un2_expr(oper_blk_arr_assgn, d1, se,(yyvsp[-3].expr),(yyvsp[-1].expr));
					void *ptr=(yyval.expr);
					mem_addr_tab m1(ptr, line_no);
					mem_addr.push_back(m1);
				}
			} else {
				(yyval.expr) = new un2_expr(ERROR_TYPE);
				void *ptr=(yyval.expr);
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
				cerr << "ERROR: NAME  =NAME[EXPR, EXPR] EXPR should be of type int or char: lineno: " 
					<< line_no << "\n";
				++no_errors;
			}
		}
		//free($1);
	}
    break;

  case 72:
#line 967 "type.y"
    {
		//cout << "parsing Function call: name: " << $1 << endl;
		string search_for=(yyvsp[-3].name);
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
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			datatype my_type=func_info_table[index]->return_type;
			expr* e_ptr=trav_chain((yyvsp[-1].expr));
			var_list* fparam=func_info_table[index]->param_list;
			bool match=false;
			if(skip_type_check==false){
				match=check_parameters(e_ptr, fparam);
			}
			if(match || skip_type_check){
				//$$=new un2_expr(oper_func_call, my_type, $3, index, line_no);
				(yyval.expr)=new un2_expr(oper_func_call, my_type, e_ptr, index, line_no);
				void *ptr=(yyval.expr);
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);

			} else {
				(yyval.expr)=new un2_expr(ERROR_TYPE);
				void *ptr=(yyval.expr);
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
		free((yyvsp[-3].name));
	}
    break;

  case 73:
#line 1006 "type.y"
    {
		(yyval.expr) = new un2_expr(strdup((yyvsp[0].text_buf)));
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
	}
    break;

  case 74:
#line 1012 "type.y"
    { 
		(yyval.expr) = new un_expr((yyvsp[-1].expr), oper_parexp );
		void *ptr=(yyval.expr);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
	}
    break;

  case 75:
#line 1020 "type.y"
    { 
#ifdef DEBUG_GRAM
	printf("got table defn\n"); 
#endif
	}
    break;

  case 76:
#line 1025 "type.y"
    { 
#ifdef DEBUG_GRAM
		printf("recursive tab_defn\n"); 
#endif
	}
    break;

  case 77:
#line 1033 "type.y"
    {
		//printf("got table defn: no filter\n");
		(yyval.tbl)=new table((yyvsp[-2].name),(yyvsp[-1].name), line_no);
		void *ptr=(yyval.tbl);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		// default value for constructor tbl_ptr->filter=NULL;
		table_list.push_back((yyval.tbl));
		//free($2); free($3);
	}
    break;

  case 78:
#line 1043 "type.y"
    {
		//printf("got table defn: with filter\n");
		(yyval.tbl)=new table((yyvsp[-5].name),(yyvsp[-4].name), line_no, (yyvsp[-1].expr));
		void *ptr=(yyval.tbl);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		table_list.push_back((yyval.tbl));
		//free($2); free($3);
	}
    break;

  case 79:
#line 1052 "type.y"
    {
		cerr << "Error in tab section line: " <<
			line_no << endl;
		++ line_no;
		++no_errors;
	}
    break;

  case 80:
#line 1060 "type.y"
    {
	}
    break;

  case 81:
#line 1062 "type.y"
    {
	}
    break;

  case 82:
#line 1066 "type.y"
    {
		basic_ax_stmt* bptr= trav_chain((yyvsp[0].basic_ax_stmt));
		(yyval.ax) = new ax(bptr,no_count_ax_elems, no_tot_ax_elems, 0);
		void *ptr=(yyval.ax);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		
		ax_map[(yyvsp[-2].name)]=(yyval.ax);
#ifdef DEBUG_GRAM
		printf("NAME: $2: %s\n", (yyvsp[-2].name));
#endif
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		free((yyvsp[-2].name));
	}
    break;

  case 83:
#line 1081 "type.y"
    {
		basic_ax_stmt* bptr= trav_chain((yyvsp[0].basic_ax_stmt));
		(yyval.ax) = new ax(bptr,no_count_ax_elems, no_tot_ax_elems, (yyvsp[-2].expr));
		void *ptr=(yyval.ax);
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		ax_map[(yyvsp[-5].name)]=(yyval.ax);
#ifdef DEBUG_GRAM
		printf("NAME: $2: %s\n", (yyvsp[-5].name));
#endif
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		free((yyvsp[-5].name));
	}
    break;

  case 84:
#line 1095 "type.y"
    {
		cerr << "Error in axis section line: " <<
			line_no << endl;
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		++no_errors;
	}
    break;

  case 85:
#line 1106 "type.y"
    {
		(yyval.basic_ax_stmt) = (yyvsp[0].basic_ax_stmt);
	}
    break;

  case 86:
#line 1109 "type.y"
    {
		(yyval.basic_ax_stmt)=link_chain((yyvsp[-1].basic_ax_stmt), (yyvsp[0].basic_ax_stmt));
	}
    break;

  case 87:
#line 1114 "type.y"
    {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.basic_ax_stmt) = new tot_ax_stmt (tot_axstmt,(yyvsp[-1].text_buf), 0);
	}
    break;

  case 88:
#line 1119 "type.y"
    {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.basic_ax_stmt) = new tot_ax_stmt (tot_axstmt,(yyvsp[-4].text_buf), (yyvsp[-1].expr));
	}
    break;

  case 89:
#line 1124 "type.y"
    {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.basic_ax_stmt) = new count_ax_stmt (cnt_axstmt,(yyvsp[-4].text_buf), (yyvsp[-1].expr));
	}
    break;

  case 90:
#line 1129 "type.y"
    {
		(yyval.basic_ax_stmt) = new ttl_ax_stmt (txt_axstmt,(yyvsp[-1].text_buf));
		++no_tot_ax_elems;
	}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 2679 "type.c"

  yyvsp -= yylen;
  yyssp -= yylen;


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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  int yytype = YYTRANSLATE (yychar);
	  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
	  YYSIZE_T yysize = yysize0;
	  YYSIZE_T yysize1;
	  int yysize_overflow = 0;
	  char *yymsg = 0;
#	  define YYERROR_VERBOSE_ARGS_MAXIMUM 5
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;

#if 0
	  /* This is so xgettext sees the translatable formats that are
	     constructed on the fly.  */
	  YY_("syntax error, unexpected %s");
	  YY_("syntax error, unexpected %s, expecting %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
#endif
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
	  int yychecklim = YYLAST - yyn;
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
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + yystrlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow && yysize <= YYSTACK_ALLOC_MAXIMUM)
	    yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg)
	    {
	      /* Avoid sprintf, as that infringes on the user's name space.
		 Don't have undefined behavior even if the translation
		 produced a string with the wrong number of "%s"s.  */
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
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
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    {
	      yyerror (YY_("syntax error"));
	      goto yyexhaustedlab;
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (YY_("syntax error"));
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
	  yydestruct ("Error: discarding", yytoken, &yylval);
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
  if (0)
     goto yyerrorlab;

yyvsp -= yylen;
  yyssp -= yylen;
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


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
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
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK;
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1135 "type.y"


void print_expr(FILE* edit_out, expr * e);

int	compile();
int	run(char * data_file_name, int rec_len);
void print_table_code(FILE * op, FILE *tab_drv_func, FILE * tab_summ_func);
void print_axis_code(FILE * op, FILE * axes_drv_func);
void clean_up();

void	generate_edit_section_code();

extern void yyrestart ( FILE *input_file );

void	print_memory_leaks();
void reset_files();
int main(int argc, char* argv[], char* envp[]){
	if(argc!=3) {
		cout << "Usage: " << argv[0] << " <prog-name> <data-file> " << endl;
		exit(0);
	}
	cout << "SOME DEBUGGING INFO: INT8_TYPE:" << INT8_TYPE 
		<< " INT8_ARR_TYPE:" << INT8_ARR_TYPE
		<< " INT8_REF_TYPE:" << INT8_REF_TYPE 
		<< endl;
	reset_files();
		
		
	active_scope=new scope();
	active_scope_list.push_back(active_scope);
	cout << "tree_root: " << tree_root << endl;
	
	/*
	 * Hand install printf -> something like a library functions
	 */

	char * printf_name="printf";
	var_list* v_list=0;
	datatype myreturn_type=INT8_TYPE;
	func_info* fi=new func_info(printf_name, v_list, myreturn_type);
	func_info_table.push_back(fi);
	
	char *c_arr="c";

	FILE * yyin=fopen(argv[1],"r");
	yyrestart(yyin);
	if(yyparse()){
		cout << "Errors in parsing edit: " << no_errors << endl;
		exit(1);
	} else 
		cout << "edit section parse finished." << endl;

	//yyterminate();
	//print_stmt_lst(tree_root);
	if(!no_errors){
		generate_edit_section_code();
	} else {
		cerr << "Errors in Parse:  Total errors: " << no_errors << endl;
		exit(1);
	}
	FILE * table_op=fopen("xtcc_work/my_table.C", "w");
	FILE * tab_drv_func=fopen("xtcc_work/my_tab_drv_func.C", "w");	
	FILE * tab_summ_func=fopen("xtcc_work/my_tab_summ.C", "w");	
	if(!(table_op&&tab_drv_func&&tab_summ_func)){
		cerr << "Unable to open file for output of table classes" << endl;
		exit(1);
	}
	if(int rval=yyparse()){
		cerr << "parsing tables section failed:" << endl;
		exit(rval);
	}

	FILE * axes_op=fopen("xtcc_work/my_axes.C", "w");	
	FILE * axes_drv_func=fopen("xtcc_work/my_axes_drv_func.C", "w");	
	if(!(axes_op&&axes_drv_func)){
		cerr << "Unable to open file for output of axes classes" << endl;
		exit(1);
	}
	if(yyparse()){
		cerr << "parsing axes section failed:" << endl;
		exit(1);
	} else {
		cout <<  "successfully parsed axes section: " << endl;
	}
	flex_finish();
	print_table_code(table_op, tab_drv_func, tab_summ_func);
	print_axis_code(axes_op, axes_drv_func);
	fclose(yyin); yyin=0;
	fclose(table_op);
	fclose(tab_drv_func);
	fclose(axes_op); 
	fclose(axes_drv_func);
	fclose(tab_summ_func);
	bool my_compile_flag=true;
	if(my_compile_flag&&!compile()){
		char * endptr=0;
		int convert_to_base=10;
		//int rec_len=strtol(argv[3],&endptr, convert_to_base);
		int rval= run(argv[2], rec_len);
		if(tree_root) {
			delete tree_root;
			tree_root=0;
		}
		clean_up();
		// fi was allocated by us - the "hand installed printf function"
		delete fi;
		print_memory_leaks();
		return rval;
	}
	cout << "returning from main with errors"<< endl;
	return no_errors;
}


void	print_memory_leaks(){
	for(int i=0; i< mem_addr.size(); ++i ){
		cout << "addr: " << mem_addr[i].mem_ptr << " line: " << mem_addr[i].line_number << endl;
	}
}

#include <cstdlib>
#include <cstdio>


void clean_up(){
	cout << "Entered function clean_up()" << endl;
	typedef map<string, ax*>::iterator ax_map_iter;
	for(ax_map_iter it=ax_map.begin(); it!=ax_map.end(); ++it){
		delete it->second; it->second=0;
	}
	// we should only delete the 0 index scope as this was manually created by us
	if (active_scope_list[0]) {
		delete active_scope_list[0]; active_scope_list[0]=0;
	}

	for(int i=0; i<table_list.size(); ++i){
		delete table_list[i];
	}
	cout << "Exited function clean_up()" << endl;
			
}


bool check_type_compat(datatype typ1, datatype typ2){
	cout << "check_type_compat: line_no: I have to convert the below code into a function:"  << line_no << endl;
	datatype td1=typ1;
	datatype td2=typ2;
	if(td1>=INT8_REF_TYPE && td1<=DOUBLE_REF_TYPE) td1=datatype(INT8_TYPE + typ1-INT8_REF_TYPE);
	if(td2>=INT8_REF_TYPE && td2<=DOUBLE_REF_TYPE) td2=datatype(INT8_TYPE + typ2-INT8_REF_TYPE);
	if((td1>=INT8_TYPE&&td1<=DOUBLE_TYPE) &&
			td2>=INT8_TYPE&&td2<=DOUBLE_TYPE){
		if(td1>=td2){
			return true;
		}
	} else {
		cerr << "ERROR: Assigning unhandle_able Type to var:  line_no:" << line_no 
			<< " LHS type: " << typ1 << " after converting LHS: " << td1
			<< " RHS type: " << typ2 << " after converting RHS: " << td2
			<< endl;
		++no_errors;
		return false;
	}
}



int check_parameters(expr* e, var_list* v){
	cout << "check_parameters: called" << endl;
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
				cout << "varname: "<< fparam->var_name << " chk_param_counter: " 
				<< chk_param_counter << " passed " << endl;
			}
		} else if ((etype>=INT8_ARR_TYPE&&etype<=DOUBLE_ARR_TYPE)&&
				(fptype>=INT8_ARR_TYPE&&fptype<=DOUBLE_ARR_TYPE)&&
				(etype==fptype)){
			cout << "varname: "<< fparam->var_name << " chk_param_counter: " 
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
		e_ptr=e_ptr->prev;
		fparam=fparam->prev;
		chk_param_counter=chk_param_counter+1;
	}
	if(match==true){
		if(e_ptr==0&& fparam==0){
			cout << "MATCHED" << endl;
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

map<string, symtab_ent*>::iterator find_in_symtab(string id){
	bool found=false;
	int i=active_scope_list.size()-1;
	//cout << "START: find_in_symtab: i=" << i <<endl;

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

/* NxD: I need to write a detailed note about this function's responsibilities
   */
   

	bool skip_func_type_check(const char * fname){
		//cout << "skip_func_type_check: BEGIN" << endl;
		char * skip_func_type_check_list[] = {"printf" };
		for (unsigned int i=0; i<sizeof(skip_func_type_check_list)/sizeof(skip_func_type_check_list[0]); ++i){
			if(!strcmp(fname, skip_func_type_check_list[i])){
				//cout << "skip_func_type_check: returned true: fname: " << fname << endl;
				return true;
			}
		}
		//cout << "skip_func_type_check: returned false: fname: " << fname << endl;
		return false;
	}

		

/*
void	add_func_params_to_cmpd_sc(scope * & sc, var_list * & v_list, string & fname){
	cout << "add_func_params_to_cmpd_sc: ENTER: sc=" << sc << " v_list:" << v_list << endl;
	var_list * v_ptr = v_list;
	while (v_ptr){
		cout << "v_ptr->var_name: " << v_ptr->var_name << endl;
		if(sc->sym_tab.find(v_ptr->var_name)==sc->sym_tab.end()){
			cout << "about to insert : " << v_ptr->var_name << " into cmpd_stmt symbol table" << endl;
			symtab_ent* se=new symtab_ent;
			se->name=strdup( v_ptr->var_name.c_str());
			se->type=v_ptr->var_type;
			sc->sym_tab[fname] = se;
			cout << "Added name: " << fname << " to symbol table" << endl;
		} else {
			cerr << "function parameter: " << v_ptr->var_name << " declared in the "
				<< "body of compound function" << endl;
			cerr << "line: " << line_no << endl;
		}
		//v_ptr=v_ptr->next;
		v_ptr=v_ptr->prev;
	}
}
*/


int search_for_func(string& search_for){
	//cout << "Entered search_for_func: " << endl;
	unsigned int i=0;
	
	for (i=0;i<func_info_table.size();++i){
		if(search_for==func_info_table[i]->fname){
			//cout << "search_for_func(): found: " << search_for << " index: " << i << endl;
			return i;
		}
	}
	cout << "search_for_func():not found function: " <<search_for  << endl;
	return -1;
}

int check_func_decl_with_func_defn(var_list* & v_list, int & index, string func_name){
	//cout << "Entered check_func_decl_with_func_defn: " << func_name << endl;
		
	var_list* defn_ptr=v_list;
	var_list* decl_ptr=func_info_table[index]->param_list;
	cout << "check_func_decl_with_func_defn: after func_info_table[index]->param_list" << endl;

	
	while(defn_ptr&&decl_ptr){
		// I may put a check on the length of the array - but it is not necessary for now I think
		if((defn_ptr->var_type==decl_ptr->var_type)&&
			(defn_ptr->var_name==decl_ptr->var_name)){
			cout << "checking : defn_ptr->var_name: " << defn_ptr->var_name << endl;
		} else {
			cerr << "check_func_decl_with_func_defn: return failure" << endl;
			++no_errors;
			return 0;
		}
		defn_ptr=defn_ptr->prev;
		decl_ptr=decl_ptr->prev;
	}
	if(defn_ptr==decl_ptr && decl_ptr==0){
		cout << "check_func_decl_with_func_defn: return success" << endl;
		return 1;
	}else{
		cout << "check_func_decl_with_func_defn: return failure" << endl;
		return 0;
	}
}

bool 	void_check( datatype & type1, datatype & type2, datatype& result_type){
	if(type1==VOID_TYPE|| type2==VOID_TYPE){
		cerr << "line_no: " << line_no << " either left or rhs of operator - is of void type: check if you are calling a void function on either side" << endl;
		result_type=ERROR_TYPE;
		++no_errors;
		return false;
	} else {
		result_type=type1 > type2? type1: type2;
		return true;
	}
}

template<class T> T* link_chain(T* &elem1, T* &elem2){
	elem2->next=elem1;
	elem1->prev=elem2;
	return elem2;
}

template<class T> T* trav_chain(T* & elem1){
	if(elem1){
		while (elem1->next) elem1=elem1->next;
		return elem1;
		/*
		while (elem1->exists_next()){
			
		}
		*/
	} else return 0;
}

#include <cstdlib>
int compile(){
	int rval;
#if !defined(__WIN32__) && !defined(MAC_TCL) /* GNU/UNIX */
	system("rm xtcc_work/temp.C");
	string cmd1="cat xtcc_work/edit_out.c xtcc_work/my_axes_drv_func.C xtcc_work/my_tab_drv_func.C stubs/main_loop.C > xtcc_work/temp.C";
#endif /* GNU/UNIX */
#if __WIN32__
	system("del xtcc_work\\temp.C");
	string cmd1="type xtcc_work\\edit_out.c xtcc_work\\my_axes_drv_func.C xtcc_work\\my_tab_drv_func.C stubs\\main_loop.C > xtcc_work\\temp.C";
#endif /* __WIN32__ */

	rval=system(cmd1.c_str());
	if(rval){
		cerr << "unable to cat files" << endl;
		return rval;
	}
#if !defined(__WIN32__) && !defined(MAC_TCL) /* GNU/UNIX */
	string cmd2="g++ xtcc_work/temp.C -o xtcc_work/myedit.exe";
#endif /* GNU/UNIX */	
#if __WIN32__
	string cmd2="\\Borland\\BCC55\\Bin\\bcc32 -P -I\\Borland\\BCC55\\Include -L\\Borland\\BCC55\\LIB -extcc_work\\myedit.exe xtcc_work\\temp.C ";
#endif /* __WIN32__ */	

	rval=system(cmd2.c_str());

	return rval;
}

#include <sstream>
int run(char * data_file_name, int rec_len){
	int rval;
	ostringstream cmd1;
#if	__WIN32__
	cmd1 << "xtcc_work\\myedit.exe " << data_file_name  << " " << rec_len;
#endif /* __WIN32__ */
#if !defined(__WIN32__) && !defined(MAC_TCL) /* GNU/UNIX */
	cmd1 << "xtcc_work/myedit.exe " << data_file_name  << " " << rec_len;
#endif /* UNIX */
	rval=system(cmd1.str().c_str());
	return rval;
}

int lookup_func(string func_name_index){
	for(register unsigned int i=0; i<func_info_table.size(); ++i){
		if(func_name_index==func_info_table[i]->fname){
			return i;
		}
	}
	return -1;
}

void print_table_code(FILE * op, FILE * tab_drv_func, FILE * tab_summ_func){
	fprintf(op, "#include <iostream>\n");
	fprintf(op, "#include <fstream>\n");
	fprintf(op, "#include <vector>\nusing namespace std;\n");
	fprintf(tab_drv_func, "#include \"my_table.C\"\n");
	fprintf(tab_drv_func, "void tab_compute(){\n");
	for(int i=0; i<table_list.size(); i++){
		CMAPITER map_iter_s= ax_map.find(table_list[i]->side);
		CMAPITER map_iter_b= ax_map.find(table_list[i]->banner);
		if(map_iter_s==ax_map.end()||map_iter_b==ax_map.end()){
			cerr << "Error: axis name " 
				<< table_list[i]->side << " or " 
				<< table_list[i]->banner << "not pres in axes defn"
				<< " line_no: " << line_no 
				<< endl;
			++ no_errors;
		} else {
			expr* f= table_list[i]->filter;
			cout << "table: " <<
				map_iter_b->first << " by " <<
				map_iter_s->first << endl;
			if ( f ){
				cout << " Filter: " ;
			}
			fprintf(op, "struct table_%s_%s {\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str ());
			fprintf(op, "const int rows, cols;\n");
			fprintf(op, "vector <int> counter;\n");
			fprintf(op, "table_%s_%s():rows(%d), cols(%d),counter(%d*%d){\nfor (int i=0;i<counter.size();++i) counter[i]=0; }\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str (),
					map_iter_s->second->no_count_ax_elems,
					map_iter_b->second->no_count_ax_elems,
					map_iter_s->second->no_count_ax_elems,
					map_iter_b->second->no_count_ax_elems
					);
			fprintf(op, "void compute(){\n");
			fprintf(op, "\tfor(int i=0; i<rows; ++i){\n");
			fprintf(op, "\t\tfor(int j=0; j<cols; ++j){\n");
			fprintf(op, "\t\t\tif(ax_%s.flag[i] && ax_%s.flag[j]){\n", 
				map_iter_s->first.c_str(), map_iter_b->first.c_str());
			fprintf(op, "\t\t\t\t++counter[i*cols+j];\n");
			fprintf(op, "\t\t\t} \n");
			fprintf(op, "\t\t} \n");
			fprintf(op, "\t}\n");
			fprintf(op, "\t} /* compute()*/\n");
			fprintf(op, "\tvoid print(){\n\t\tint rci=0, cci=0; /* row counter index , col ... */\n");
			fprintf(op, "\t\tofstream tab_op(\"tab_.csv\", ios_base::out|ios_base::app);\n");
			fprintf(op, "\t\ttab_op << \"rows: \" << rows << \"cols: \" << cols << endl;\n");
			fprintf(op, "\t\ttab_op << ax_%s.stmt_text[0] << \" x \" << ax_%s.stmt_text[0] << endl;\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str()
					);
			fprintf(op, "\t\ttab_op << \",\";\n");
			fprintf(op, "\t\tfor(int j=0; j<ax_%s.stmt_text.size(); ++j){\n", map_iter_b->first.c_str());
			fprintf(op, "\t\t\tif(ax_%s.is_a_count_text[j]){\n", map_iter_b->first.c_str());
			fprintf(op, "\t\t\t\t tab_op << ax_%s.stmt_text[j] << \",\" ;\n", map_iter_b->first.c_str()); 
			fprintf(op, "\t\t\t}\n");
			fprintf(op, "\t\t}\n");
			fprintf(op, "\t\ttab_op << endl;\n");
			fprintf(op, "\t\t\tfor(int i=1; i<ax_%s.stmt_text.size(); ++i){\n",
					map_iter_s->first.c_str());
			fprintf(op, "\t\t\t\tcci=0;\n");
			fprintf(op, "\t\t\t\ttab_op << ax_%s.stmt_text[i] << \",\";\n", map_iter_s->first.c_str()); 
			fprintf(op, "\t\t\t\tif(ax_%s.is_a_count_text[i]){\n", map_iter_s->first.c_str());
			fprintf(op, "\t\t\t\t\tfor(int j=0; j<ax_%s.stmt_text.size(); ++j){\n",
					map_iter_b->first.c_str());
			fprintf(op, "\t\t\t\t\tif(ax_%s.is_a_count_text[j]){\n", map_iter_b->first.c_str());
			fprintf(op, "\t\t\t\t\t\t//tab_op << \"rci:\" << rci << \"cci:\" << cci << endl;\n");
			fprintf(op, "\t\t\t\t\t\ttab_op << counter[cci+rci*cols]<<\",\";\n");
			fprintf(op, "\t\t\t\t\t\t++cci;\n");
			fprintf(op, "\t\t\t\t\t}\n");
			fprintf(op, "\t\t\t\t}\n");
			fprintf(op, "\t\t\t\t++rci;\n");
			fprintf(op, "\t\t\t}\n");
			fprintf(op, "\t\ttab_op << endl;\n");
			fprintf(op, "\t\t}\n");
			fprintf(op, "\ttab_op.close();\n");
			fprintf(op, "\t}\n");
			fprintf(op, "} tab_%s_%s;\n",
				map_iter_s->first.c_str(), map_iter_b->first.c_str()
				);
			fprintf(tab_drv_func, "\ttab_%s_%s.compute();\n",
				map_iter_s->first.c_str(), map_iter_b->first.c_str()
				);
		}
	}

	fprintf(tab_drv_func, "}\n");

	fprintf(tab_drv_func, "void tab_summ(){\n");
	for(int i=0; i<table_list.size(); i++){
		CMAPITER map_iter_s= ax_map.find(table_list[i]->side);
		CMAPITER map_iter_b= ax_map.find(table_list[i]->banner);
		if(map_iter_s==ax_map.end()||map_iter_b==ax_map.end()){
			cerr << "Error: axis name " 
				<< table_list[i]->side << " or " 
				<< table_list[i]->banner << "not pres in axes defn"
				<< " line_no: " << line_no 
				<< endl;
			++ no_errors;
		} else {
			fprintf(tab_drv_func, "\ttab_%s_%s.print();\n",
			map_iter_s->first.c_str(), map_iter_b->first.c_str()
			);
		}
	}
	fprintf(tab_drv_func, "}\n");

}

void print_axis_code(FILE * op, FILE * axes_drv_func){

	fprintf(op, "#include <bitset>\n" );
	fprintf(op, "#include <string>\n" );
	fprintf(op, "#include <vector>\n" );
	fprintf(op, "using namespace std;\n" );
	fprintf(axes_drv_func, "#include \"my_axes.C\"\n");
	fprintf(axes_drv_func, "void ax_compute(){\n");
	for(CMAPITER it=ax_map.begin(); it!=ax_map.end(); ++it){
		fprintf(op, "struct axis_%s{\n", it->first.c_str() );
		fprintf(op, "\tbitset<%d> flag;\n", it->second->no_count_ax_elems );
		fprintf(op, "\tvector<string> stmt_text;\n");
		fprintf(op, "\tbitset<%d> is_a_count_text;\n", it->second->no_tot_ax_elems);
		fprintf(op, "\taxis_%s():stmt_text(%d){\n", it->first.c_str(), it->second->no_tot_ax_elems);
		int my_counter=0;
		for(basic_ax_stmt* ax_stmt_iter=it->second->ax_stmt_start; ax_stmt_iter; ax_stmt_iter=ax_stmt_iter->prev,
				++my_counter){
			fprintf(op, "\tstmt_text[%d]=%s;\n", my_counter, ax_stmt_iter->ax_text().c_str());
			if(ax_stmt_iter->axtype<=txt_axstmt){
				fprintf(op, "\tis_a_count_text[%d]=false;\n", my_counter);
			} else {
				fprintf(op, "\tis_a_count_text[%d]=true;\n", my_counter);
			}
		}
		fprintf(op, "}\n");
		fprintf(op, "\tvoid compute(){\n\tflag.reset();\n");
		basic_ax_stmt* iter=it->second->ax_stmt_start;
		int counter=0;
		while(iter){
			if(iter->axtype>=tot_axstmt){
				basic_count_ax_stmt * bc=dynamic_cast<basic_count_ax_stmt *> (iter);
					
				if(bc->condn){
					fprintf(op, "\tif (");
					bc->condn->print_expr(op);
					fprintf(op, " ){\n");
					fprintf(op, "\t\tflag[%d]=true;\n", counter);
					fprintf(op, "\t}\n");
				} else {
					fprintf(op, "\tflag[%d]=true;\n", counter);
				}
				++counter;
			}
			iter=iter->prev;
		}
		fprintf(op, "\t} /* close compute func */\n");
		fprintf(op, "} ax_%s;\n", it->first.c_str()) ;
		fprintf(axes_drv_func, "\tax_%s.compute();\n",it->first.c_str());
	}
	fprintf(axes_drv_func, "}\n");
}

void	generate_edit_section_code(){
	FILE * global_vars=fopen("xtcc_work/global.C", "wb");
	fprintf(global_vars, "#ifndef __NxD_GLOB_VARS_H\n#define __NxD_GLOB_VARS_H\n");
	fprintf(global_vars, "#include <sys/types.h>\n");
	fprintf(global_vars, "#include <map>\n using namespace std;\n");
	fprintf(global_vars, "void print_list_counts();\n");
	fprintf(global_vars, "void tab_compute();\n");
	fprintf(global_vars, "void tab_summ();\n");
	fprintf(global_vars, "void ax_compute();\n");
	fclose(global_vars);
	FILE * print_list_counts=fopen("xtcc_work/print_list_counts.C", "wb");
	fprintf(print_list_counts, "template <class T>\nvoid print_list_summ(map<T,int> &m);\n");
	fprintf(print_list_counts, "void print_list_counts(){\n");
	fclose(print_list_counts);
	FILE * edit_out= fopen("xtcc_work/edit_out.c", "w+b");
	if(edit_out==0){
		printf("could not open edit_out.c for writing\n");
		exit(1);
	}
#if __WIN32__
	fprintf(edit_out, "#include \"stubs/iso_types.h\"\n" );
#endif /* __WIN32__ */
	fprintf(edit_out, "#include <cstdio>\n#include <iostream>\nusing namespace std;\n" );
	fprintf(edit_out, "#include <sys/types.h>\n" );
	fprintf(edit_out, "int8_t c[%d];\n", rec_len );
	fprintf(edit_out, "#include \"global.C\"\n" );
	cout << "printing edit:" << endl;
	tree_root->print_stmt_lst(edit_out);
	fclose(edit_out);
	global_vars=fopen("xtcc_work/global.C", "a+");
	if(!global_vars){
		cerr << "cannot open global.C for writing" << endl;
		exit(1);
	}
	fprintf(global_vars, "#endif /* __NxD_GLOB_VARS_H*/\n");
	fclose(global_vars);
	print_list_counts=fopen("xtcc_work/print_list_counts.C", "a+");
	fprintf(print_list_counts, "}\n");
	fclose(print_list_counts);

}

#include <fstream>
void reset_files(){
	ofstream lst_op("lst_.csv", ios_base::out|ios_base::trunc);
	lst_op << endl;
	lst_op.close();
	ofstream tab_op("tab_.csv", ios_base::out|ios_base::trunc);
	tab_op << endl;
	tab_op.close();
}

