/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

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
     TEXT = 264,
     NAME = 265,
     FNUMBER = 266,
     INUMBER = 267,
     CODELIST = 268,
     LISTA = 269,
     IF = 270,
     ELSE = 271,
     VOID_T = 272,
     U_INT8_T = 273,
     INT8_T = 274,
     U_INT16_T = 275,
     INT16_T = 276,
     U_INT32_T = 277,
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
#define CONVERT 258
#define TOT 259
#define AX 260
#define CNT 261
#define TTL 262
#define FOR 263
#define TEXT 264
#define NAME 265
#define FNUMBER 266
#define INUMBER 267
#define CODELIST 268
#define LISTA 269
#define IF 270
#define ELSE 271
#define VOID_T 272
#define U_INT8_T 273
#define INT8_T 274
#define U_INT16_T 275
#define INT16_T 276
#define U_INT32_T 277
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
	void	add_func_params_to_cmpd_sc(struct scope * & sc, struct var_list * & v_list, string & fname);
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
			{	"u_int8_t" ,U_INT8_TYPE},
			{	"int8_t" ,INT8_TYPE},
			{	"u_int16_t",U_INT16_TYPE},
			{	"int16_t" ,INT16_TYPE},
			{	"u_int32_t",U_INT32_TYPE},
			{	"int32_t" ,INT32_TYPE},
			{	"float", FLOAT_TYPE},
			{	"double", DOUBLE_TYPE}
		};



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
/* Line 191 of yacc.c.  */
#line 256 "type.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 268 "type.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
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
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   485

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  27
/* YYNRULES -- Number of rules. */
#define YYNRULES  91
/* YYNRULES -- Number of states. */
#define YYNSTATES  206

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    24,     2,     2,     2,    58,    62,     2,
      22,    23,    56,    55,    45,    54,     2,    57,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     5,
      50,    25,    51,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    20,     2,    21,     2,     2,     2,     2,     2,     2,
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
      18,    19,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    46,    47,    48,    49,    52,    53,    59,    60,    61
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,    15,    20,    25,    27,    30,    32,
      34,    36,    38,    40,    42,    44,    46,    48,    50,    52,
      53,    61,    65,    72,    74,    81,    83,    87,    90,    96,
     100,   101,   103,   106,   107,   118,   120,   123,   125,   127,
     129,   132,   135,   138,   143,   151,   161,   167,   175,   179,
     181,   183,   187,   191,   195,   199,   203,   207,   210,   214,
     218,   222,   226,   230,   234,   238,   242,   246,   249,   251,
     253,   255,   260,   267,   272,   274,   278,   280,   283,   288,
     296,   299,   301,   304,   309,   317,   320,   322,   325,   330,
     338,   346
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      64,     0,    -1,    -1,    38,     5,    39,    25,    15,     5,
      65,    37,    66,    40,    -1,    35,     7,    86,     9,    -1,
      36,     7,    84,     9,    -1,    67,    -1,    66,    67,    -1,
      71,    -1,    69,    -1,    26,    -1,    27,    -1,    28,    -1,
      29,    -1,    30,    -1,    31,    -1,    32,    -1,    33,    -1,
      34,    -1,    -1,    68,    13,    22,    73,    23,    70,    80,
      -1,    68,    13,     5,    -1,    68,    13,    20,    15,    21,
       5,    -1,    72,    -1,    68,    13,    22,    73,    23,     5,
      -1,    74,    -1,    73,    45,    74,    -1,    68,    13,    -1,
      68,    13,    20,    15,    21,    -1,    68,    62,    13,    -1,
      -1,    76,    -1,    75,    76,    -1,    -1,    11,    22,    83,
       5,    83,     5,    83,    23,    77,    76,    -1,    79,    -1,
      83,     5,    -1,    80,    -1,    71,    -1,    78,    -1,    44,
       5,    -1,    43,     5,    -1,     1,     5,    -1,    17,    13,
      12,     5,    -1,    17,    13,    20,    15,    21,    12,     5,
      -1,    17,    13,    20,    15,    45,    15,    21,    12,     5,
      -1,    18,    22,    83,    23,    76,    -1,    18,    22,    83,
      23,    76,    19,    76,    -1,    81,    75,     9,    -1,     7,
      -1,    83,    -1,    82,    45,    83,    -1,    83,    55,    83,
      -1,    83,    54,    83,    -1,    83,    56,    83,    -1,    83,
      57,    83,    -1,    83,    58,    83,    -1,    54,    83,    -1,
      83,    50,    83,    -1,    83,    51,    83,    -1,    83,    53,
      83,    -1,    83,    52,    83,    -1,    83,    49,    83,    -1,
      83,    48,    83,    -1,    83,    46,    83,    -1,    83,    47,
      83,    -1,    83,    25,    83,    -1,    59,    83,    -1,    15,
      -1,    14,    -1,    13,    -1,    13,    20,    83,    21,    -1,
      13,    20,    83,    45,    83,    21,    -1,    13,    22,    82,
      23,    -1,    12,    -1,    22,    83,    23,    -1,    85,    -1,
      84,    85,    -1,    41,    13,    13,     5,    -1,    41,    13,
      13,     5,    42,    83,     5,    -1,     1,     5,    -1,    87,
      -1,    86,    87,    -1,     6,    13,     5,    88,    -1,     6,
      13,     5,    42,    83,     5,    88,    -1,     1,     5,    -1,
      89,    -1,    88,    89,    -1,     4,     5,    12,     5,    -1,
       4,     5,    12,     5,    42,    83,     5,    -1,     8,     5,
      12,     5,    42,    83,     5,    -1,    10,     5,    12,     5,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   203,   203,   202,   213,   216,   221,   224,   229,   230,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   246,
     246,   272,   276,   290,   296,   307,   311,   318,   322,   328,
     334,   340,   348,   353,   353,   364,   365,   373,   376,   379,
     380,   387,   394,   402,   421,   441,   462,   471,   483,   509,
     530,   531,   536,   540,   544,   548,   552,   563,   571,   575,
     579,   583,   587,   591,   595,   599,   603,   616,   624,   628,
     631,   642,   669,   713,   740,   743,   748,   753,   761,   767,
     772,   780,   782,   786,   797,   807,   818,   821,   826,   831,
     836,   841
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONVERT", "TOT", "';'", "AX", "'{'", 
  "CNT", "'}'", "TTL", "FOR", "TEXT", "NAME", "FNUMBER", "INUMBER", 
  "CODELIST", "LISTA", "IF", "ELSE", "'['", "']'", "'('", "')'", "'!'", 
  "'='", "VOID_T", "U_INT8_T", "INT8_T", "U_INT16_T", "INT16_T", 
  "U_INT32_T", "INT32_T", "FLOAT_T", "DOUBLE_T", "AXSTART", "TABSTART", 
  "ED_START", "DATA_STRUCT", "REC_LEN", "ED_END", "TAB", "COND_START", 
  "CONTINUE", "BREAK", "','", "LOGOR", "LOGAND", "NOEQ", "ISEQ", "'<'", 
  "'>'", "GEQ", "LEQ", "'-'", "'+'", "'*'", "'/'", "'%'", "NOT", "UMINUS", 
  "FUNC_CALL", "'&'", "$accept", "prog", "@1", "top_level_item_list", 
  "top_level_item", "xtcc_type", "func_defn", "@2", "decl", "func_decl", 
  "decl_comma_list", "var_decl", "statement_list", "statement", "@3", 
  "list_stmt", "if_stmt", "compound_stmt", "open_curly", "expr_list", 
  "expression", "tab_list", "tab_defn", "ax_list", "ax_defn", 
  "ax_stmt_list", "ax_stmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,    59,   260,   123,   261,   125,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
      91,    93,    40,    41,    33,    61,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,    44,   291,   292,   293,   294,
      60,    62,   295,   296,    45,    43,    42,    47,    37,   297,
     298,   299,    38
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    63,    65,    64,    64,    64,    66,    66,    67,    67,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    70,
      69,    71,    71,    71,    72,    73,    73,    74,    74,    74,
      74,    75,    75,    77,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    78,    78,    78,    79,    79,    80,    81,
      82,    82,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    84,    84,    85,    85,
      85,    86,    86,    87,    87,    87,    88,    88,    89,    89,
      89,    89
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,    10,     4,     4,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       7,     3,     6,     1,     6,     1,     3,     2,     5,     3,
       0,     1,     2,     0,    10,     1,     2,     1,     1,     1,
       2,     2,     2,     4,     7,     9,     5,     7,     3,     1,
       1,     3,     3,     3,     3,     3,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     1,     1,
       1,     4,     6,     4,     1,     3,     1,     2,     4,     7,
       2,     1,     2,     4,     7,     2,     1,     2,     4,     7,
       7,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     1,     0,
       0,     0,    81,     0,     0,     0,    76,     0,    85,     0,
       4,    82,    80,     0,     5,    77,     0,     0,     0,     0,
       0,     0,     0,     0,    83,    86,    78,     2,     0,     0,
       0,    74,    70,    69,    68,     0,     0,     0,     0,    87,
       0,     0,     0,     0,     0,     0,     0,     0,    57,    67,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,     0,    91,
       0,     0,    50,    75,    84,    66,    64,    65,    63,    62,
      58,    59,    61,    60,    53,    52,    54,    55,    56,    79,
      10,    11,    12,    13,    14,    15,    16,    17,    18,     0,
       6,     0,     9,     8,    23,     0,     0,    71,     0,    73,
       0,     3,     7,     0,     0,     0,     0,    51,    21,     0,
      30,    89,    90,    72,     0,     0,     0,    25,     0,    27,
       0,    19,    30,    22,     0,    29,    24,     0,    26,     0,
      49,    20,     0,    28,     0,     0,     0,     0,     0,     0,
       0,    38,     0,    31,    39,    35,    37,     0,    42,     0,
       0,     0,    41,    40,     0,    48,    32,    36,     0,     0,
       0,     0,    30,     0,    43,     0,     0,     0,     0,     0,
       0,    46,     0,     0,     0,     0,     0,     0,    44,     0,
      47,    33,     0,     0,    45,    34
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     4,    51,   109,   110,   160,   112,   147,   161,   114,
     136,   137,   162,   163,   203,   164,   165,   166,   152,    81,
     167,    15,    16,    11,    12,    34,    35
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -68
static const short yypact[] =
{
      93,    11,    12,     1,    26,    15,    19,   -37,   -68,    56,
      57,   126,   -68,    64,    60,     2,   -68,    55,   -68,    76,
     -68,   -68,   -68,    79,   -68,   -68,    94,    68,   108,   109,
     120,   121,   125,    52,    85,   -68,    95,   -68,   127,   128,
     130,   -68,    78,   -68,   -68,    52,    52,    52,    -1,   -68,
      52,   106,   141,   143,   156,    52,    52,   345,   -68,   -68,
      85,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,   154,   346,   103,   134,   -68,
     296,   -18,   407,   -68,    85,   407,   373,   418,   427,   427,
     131,   131,   131,   131,   107,   107,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   225,
     -68,   164,   -68,   -68,   -68,    52,    52,   -68,    52,   -68,
      52,   -68,   -68,    66,   170,   188,   309,   407,   -68,   163,
     346,   -68,   -68,   -68,   160,    -3,    39,   -68,   177,   171,
     179,   191,   346,   -68,   183,   -68,   -68,   207,   -68,   194,
     -68,   -68,   140,   -68,   226,   208,   219,   211,   243,   245,
     247,   -68,    90,   -68,   -68,   -68,   -68,   224,   -68,    52,
      -5,    52,   -68,   -68,    74,   -68,   -68,   -68,   242,   256,
     249,   358,   346,    52,   -68,   -20,   140,    45,   258,   250,
     251,   265,   191,    52,   263,   248,   140,   394,   -68,   273,
     -68,   -68,   281,   140,   -68,   -68
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
     -68,   -68,   -68,   -68,   178,   -67,   -68,   -68,   -32,   -68,
     119,   161,   -68,    -6,   -68,   -68,   -68,   155,   -68,   -68,
     -33,   -68,   303,   -68,   308,   260,   -26
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      48,   189,    17,    13,    60,   119,     7,   179,    49,   111,
     139,    24,    57,    58,    59,   180,     9,    75,     5,     6,
      13,    10,    80,    82,    61,   190,     8,   120,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,   111,    14,   113,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    49,   140,
      14,    18,   141,   135,    41,    42,    43,    44,   192,    22,
      19,   128,    30,    23,    45,   135,    31,   113,    32,   128,
      26,    27,   124,   125,   142,   126,   129,   127,   130,    30,
     142,   154,    28,    31,   129,    32,   182,   150,    55,   175,
      56,   155,    41,    42,    43,    44,    46,   156,   157,    29,
      33,    47,    45,    36,    37,   135,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    38,    39,     9,     1,     2,
      40,     3,    10,   158,   159,    20,   178,    50,   181,    52,
      53,   154,    54,    76,    46,   115,    77,   150,    78,    47,
     188,   155,    41,    42,    43,    44,   176,   156,   157,    99,
     197,    79,    45,    72,    73,    74,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   131,   116,   123,   134,    61,
     191,   138,   143,   158,   159,    70,    71,    72,    73,    74,
     200,   144,   145,   132,    46,    61,   146,   205,   149,    47,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    61,   150,   153,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,   177,
     169,   168,   170,   171,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,   183,   172,    61,
     173,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     174,   184,   194,   193,   185,   121,   195,    61,   198,   199,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    61,   196,   202,   204,   122,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,   187,   151,   148,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,   117,    25,    21,
      84,    61,     0,     0,     0,     0,     0,     0,     0,     0,
     133,     0,     0,     0,    61,     0,     0,     0,     0,     0,
       0,   118,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    83,     0,
      61,     0,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   186,     0,    61,     0,     0,     0,     0,     0,     0,
       0,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,   201,     0,    61,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    61,     0,     0,     0,     0,     0,     0,     0,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    66,    67,    68,
      69,    70,    71,    72,    73,    74
};

static const short yycheck[] =
{
      33,    21,    39,     1,     5,    23,     5,    12,    34,    76,
      13,     9,    45,    46,    47,    20,     1,    50,     7,     7,
       1,     6,    55,    56,    25,    45,     0,    45,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,   109,    41,    76,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    84,    62,
      41,     5,    23,   130,    12,    13,    14,    15,    23,     5,
      13,     5,     4,    13,    22,   142,     8,   109,    10,     5,
      25,     5,   115,   116,    45,   118,    20,   120,    22,     4,
      45,     1,    13,     8,    20,    10,    22,     7,    20,     9,
      22,    11,    12,    13,    14,    15,    54,    17,    18,    15,
      42,    59,    22,     5,     5,   182,    26,    27,    28,    29,
      30,    31,    32,    33,    34,     5,     5,     1,    35,    36,
       5,    38,     6,    43,    44,     9,   169,    42,   171,    12,
      12,     1,    12,    37,    54,    42,     5,     7,     5,    59,
     183,    11,    12,    13,    14,    15,   162,    17,    18,     5,
     193,     5,    22,    56,    57,    58,    26,    27,    28,    29,
      30,    31,    32,    33,    34,     5,    42,    13,    15,    25,
     186,    21,     5,    43,    44,    54,    55,    56,    57,    58,
     196,    20,    13,     5,    54,    25,     5,   203,    15,    59,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    25,     7,    21,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,     5,
      22,     5,    13,    22,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,     5,     5,    25,
       5,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      13,     5,    12,     5,    15,    40,    15,    25,     5,    21,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    25,    19,    12,     5,   109,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,   182,   147,   142,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    21,    15,    11,
      60,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    23,    -1,
      25,    -1,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    23,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    23,    -1,    25,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    50,    51,    52,
      53,    54,    55,    56,    57,    58
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    35,    36,    38,    64,     7,     7,     5,     0,     1,
       6,    86,    87,     1,    41,    84,    85,    39,     5,    13,
       9,    87,     5,    13,     9,    85,    25,     5,    13,    15,
       4,     8,    10,    42,    88,    89,     5,     5,     5,     5,
       5,    12,    13,    14,    15,    22,    54,    59,    83,    89,
      42,    65,    12,    12,    12,    20,    22,    83,    83,    83,
       5,    25,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    83,    37,     5,     5,     5,
      83,    82,    83,    23,    88,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,     5,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    66,
      67,    68,    69,    71,    72,    42,    42,    21,    45,    23,
      45,    40,    67,    13,    83,    83,    83,    83,     5,    20,
      22,     5,     5,    21,    15,    68,    73,    74,    21,    13,
      62,    23,    45,     5,    20,    13,     5,    70,    74,    15,
       7,    80,    81,    21,     1,    11,    17,    18,    43,    44,
      68,    71,    75,    76,    78,    79,    80,    83,     5,    22,
      13,    22,     5,     5,    13,     9,    76,     5,    83,    12,
      20,    83,    22,     5,     5,    15,    23,    73,    83,    21,
      45,    76,    23,     5,    12,    15,    19,    83,     5,    21,
      76,    23,    12,    77,     5,    76
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

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
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
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

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
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
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
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
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

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
  register const char *yys = yystr;

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
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



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
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

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
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



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
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
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
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

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
#line 203 "type.y"
    {	char * c_arr="c";  
		rec_len=yyvsp[-1].ival; active_scope->insert(c_arr, INT8_ARR_TYPE, rec_len, 0);
	}
    break;

  case 3:
#line 206 "type.y"
    {
		tree_root = trav_chain(yyvsp[-1].stmt);
		if(tree_root==0){
			cerr << "tree_root =0 : core dump expected" << endl;
		}
		return 0;
	}
    break;

  case 4:
#line 213 "type.y"
    {
		return 0;
	}
    break;

  case 5:
#line 216 "type.y"
    {
		return 0;
	}
    break;

  case 6:
#line 221 "type.y"
    {
		yyval.stmt=yyvsp[0].stmt;
	}
    break;

  case 7:
#line 224 "type.y"
    {
		yyval.stmt=link_chain(yyvsp[-1].stmt,yyvsp[0].stmt);
	}
    break;

  case 19:
#line 246 "type.y"
    {
		string func_name_index(yyvsp[-3].name);
		flag_cmpd_stmt_is_a_func_body=lookup_func(func_name_index);
		if(flag_cmpd_stmt_is_a_func_body==-1){
			++ no_errors;
			cerr << "Function name not found in list of declared functions: "
				<< "You will see another error on this same function name: " << func_name_index
				<< "line_no: " << line_no ;
		}
	}
    break;

  case 20:
#line 255 "type.y"
    {
		struct cmpd_stmt* c_stmt= yyvsp[0].c_stmt;
		if(c_stmt==0){
			cout << "c_stmt==0" << endl;
		} else {
			cout << "func_body: is valid " << endl;
		}
		struct scope *sc=c_stmt->sc;
		struct var_list * v_list=trav_chain(yyvsp[-3].v_list);
		struct stmt* func_body=yyvsp[0].c_stmt;
		string search_for=yyvsp[-5].name;
		datatype return_type=yyvsp[-6].dt;
		yyval.stmt=new func_stmt(FUNC_DEFN, line_no, sc, v_list, func_body, search_for, return_type);
	}
    break;

  case 21:
#line 272 "type.y"
    {
		//cout << "creating simple var of type: " << $1 << endl;
		yyval.stmt = active_scope->insert(yyvsp[-1].name, yyvsp[-2].dt, line_no);
	}
    break;

  case 22:
#line 276 "type.y"
    {
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		//cout << "creating arr var of type: " << $1 << endl;
		datatype dt=datatype(U_INT8_ARR_TYPE+(yyvsp[-5].dt-U_INT8_TYPE));
		yyval.stmt = active_scope->insert(yyvsp[-4].name, dt, yyvsp[-2].ival, line_no);
	}
    break;

  case 23:
#line 290 "type.y"
    {
		yyval.stmt=yyvsp[0].stmt;
	}
    break;

  case 24:
#line 296 "type.y"
    {
		char *name=strdup(yyvsp[-4].name);
		struct var_list* tmp=yyvsp[-2].v_list;
		struct var_list* v_list=trav_chain(yyvsp[-2].v_list);
		tmp=v_list;
		datatype return_type=yyvsp[-5].dt;
		yyval.stmt=new func_decl_stmt( FUNC_TYPE, line_no, name,  v_list, return_type);
	}
    break;

  case 25:
#line 307 "type.y"
    {
		 yyval.v_list=yyvsp[0].v_list;
		 //cout << "got decl_comma_list : " << endl;
	}
    break;

  case 26:
#line 311 "type.y"
    {
		yyval.v_list=link_chain(yyvsp[-2].v_list,yyvsp[0].v_list);
		//cout << "chaining var_decl : " << endl;
	}
    break;

  case 27:
#line 318 "type.y"
    {
		//cout << "creating simple var of type: " << $1 << endl;
		yyval.v_list=new var_list(yyvsp[-1].dt, yyvsp[0].name);
	}
    break;

  case 28:
#line 322 "type.y"
    {
		/* Neil - I need to fix this */
		//cout << "creating arr var of type: " << $1 << endl;
		datatype dt=datatype(U_INT8_ARR_TYPE+(yyvsp[-4].dt-U_INT8_TYPE));
		yyval.v_list=new var_list(dt, yyvsp[-3].name, yyvsp[-1].ival);
	}
    break;

  case 29:
#line 328 "type.y"
    {
		//cout << "creating ref var of type: " << $1 << endl;
		datatype dt=datatype(U_INT8_REF_TYPE+(yyvsp[-2].dt-U_INT8_TYPE));
		yyval.v_list=new var_list(dt, yyvsp[0].name);
	}
    break;

  case 30:
#line 334 "type.y"
    {
		//$$=new var_list(uninit, "empty");
		yyval.v_list=0;
		}
    break;

  case 31:
#line 340 "type.y"
    {
		yyval.stmt=yyvsp[0].stmt; 
		if(flag_next_stmt_start_of_block){
			blk_heads.push_back(yyvsp[0].stmt);
			//start_of_blk=$1;
			flag_next_stmt_start_of_block=false;
		}
	}
    break;

  case 32:
#line 348 "type.y"
    {
		yyval.stmt=link_chain(yyvsp[-1].stmt,yyvsp[0].stmt);
	}
    break;

  case 33:
#line 353 "type.y"
    { ++in_a_loop;}
    break;

  case 34:
#line 353 "type.y"
    {
		   if(yyvsp[-7].expr->type==VOID_TYPE||yyvsp[-5].expr->type==VOID_TYPE||yyvsp[-3].expr->type==VOID_TYPE 
			){
			   cerr << "For condition has VOID_TYPE or ERROR_TYPE" << endl;
			   ++ no_errors;
			   yyval.stmt=new struct err_stmt(line_no);
		   } else{
			   yyval.stmt = new struct for_stmt(FOR_STMT, line_no, yyvsp[-7].expr, yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[0].stmt);
		   }
		   --in_a_loop;
	}
    break;

  case 36:
#line 365 "type.y"
    { 
		if(yyvsp[-1].expr->isvalid()){
			yyval.stmt = new expr_stmt(TEXPR_STMT, line_no, yyvsp[-1].expr);
		} else {
			yyval.stmt = new expr_stmt(ERROR_TYPE, line_no, yyvsp[-1].expr);
		}
		//printf("= %g\n", $1); 
	}
    break;

  case 37:
#line 373 "type.y"
    {
		yyval.stmt=yyvsp[0].c_stmt;
	}
    break;

  case 38:
#line 376 "type.y"
    {
		yyval.stmt=yyvsp[0].stmt;
	}
    break;

  case 40:
#line 380 "type.y"
    {
		yyval.stmt=new struct break_stmt(BREAK_STMT, line_no);
		if (!in_a_loop){
			cerr << "break statement outside a loop: line_no: " << line_no<< endl;
			++no_errors;
		}
	}
    break;

  case 41:
#line 387 "type.y"
    {
		yyval.stmt=new struct continue_stmt(CONTINUE_STMT, line_no);
		if (!in_a_loop){
			cerr << "continue statement outside a loop: line_no: " << line_no<< endl;
			++no_errors;
		}
	}
    break;

  case 42:
#line 394 "type.y"
    {
		cerr << "statement missing ';' around line_no: " << line_no << endl;
		++no_errors;
		yyval.stmt = new struct err_stmt(line_no);
		yyerrok;
	}
    break;

  case 43:
#line 402 "type.y"
    {
		map<string,symtab_ent*>::iterator sym_it = find_in_symtab(yyvsp[-2].name);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << yyvsp[-2].name << " not found in symbol table" << endl;
			++no_errors;
			yyval.stmt=new err_stmt(line_no);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->type;
			if( !(name_type>=INT8_TYPE&&name_type<=DOUBLE_TYPE)){
				cerr << "NAME: "<< yyvsp[-2].name 
					<< " should be of basic type: " << line_no << endl;
				++no_errors;
				yyval.stmt=new struct err_stmt(line_no);
			} else {
				yyval.stmt=new list_stmt(LISTA_BASIC_TYPE_STMT, line_no, se);
			}
		}
	}
    break;

  case 44:
#line 421 "type.y"
    {
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab(yyvsp[-5].name);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << yyvsp[-5].name << " not found in symbol table" << endl;
			++no_errors;
			yyval.stmt=new err_stmt(line_no);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->type;
			if( !(name_type>=INT8_ARR_TYPE&&name_type<=DOUBLE_ARR_TYPE)){
				cerr << "NAME: "<< yyvsp[-5].name 
					<< " is not of array type: line_no:" << line_no << endl;
				++no_errors;
				yyval.stmt=new err_stmt(line_no);
			} else {
				yyval.stmt=new list_stmt( LISTA_BASIC_ARRTYPE_STMT_1INDEX, line_no, se, yyvsp[-3].ival, -1, string(yyvsp[-1].text_buf));
			}
		}
	}
    break;

  case 45:
#line 441 "type.y"
    {
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab(yyvsp[-7].name);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << yyvsp[-7].name << " not found in symbol table" << endl;
			++no_errors;
			yyval.stmt=new err_stmt(line_no);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->type;
			if( !(name_type==INT8_ARR_TYPE||name_type==U_INT8_TYPE)){
				cerr << "NAME: "<< yyvsp[-7].name 
					<< " is not of char array type: line_no:" << line_no << endl;
				++no_errors;
			} else {
				yyval.stmt=new list_stmt( LISTA_BASIC_ARRTYPE_STMT_2INDEX, line_no, se, yyvsp[-5].ival, yyvsp[-3].ival, string(yyvsp[-1].text_buf));
			}
		}
	}
    break;

  case 46:
#line 462 "type.y"
    {
		if(yyvsp[-2].expr->type==VOID_TYPE || yyvsp[-2].expr->type==ERROR_TYPE){
			++no_errors;
			yyval.stmt=new err_stmt(line_no);
			cerr << "Error: If condition has void or Error type:" << line_no << endl;
		} else {
			yyval.stmt=new if_stmt(IFE_STMT,line_no,yyvsp[-2].expr,yyvsp[0].stmt,0);
		}
	}
    break;

  case 47:
#line 471 "type.y"
    {
		if(yyvsp[-4].expr->type==VOID_TYPE || yyvsp[-4].expr->type==ERROR_TYPE){
			++no_errors;
			yyval.stmt=new err_stmt(line_no);
			cerr << "Error: If condition has void or Error type:" << line_no << endl;
		} else {
			yyval.stmt=new if_stmt(IFE_STMT, line_no,yyvsp[-4].expr,yyvsp[-2].stmt,yyvsp[0].stmt);
		}
	}
    break;

  case 48:
#line 483 "type.y"
    {
		//cout << "popping scope: " <<
		//	active_scope_list[active_scope_list.size()-1] << endl;
		active_scope_list.pop_back();
		int tmp=active_scope_list.size()-1;
		if(tmp==-1) { 
			active_scope = 0;
			cerr << "Error: active_scope = NULL: should not happen: line_no:" << line_no
				<< endl;
			++no_errors;
			yyval.c_stmt=new struct cmpd_stmt(ERROR_TYPE, line_no);
		} else { active_scope = active_scope_list[tmp]; }
		//$1->cmpd_bdy = trav_chain($2);
		struct stmt* head_of_this_chain=blk_heads.back();
		if(  head_of_this_chain==0){
			cerr << "Error in compiler : cmpd_bdy:  " << __FILE__ << __LINE__ << endl;
			++no_errors;
		} else {
			yyvsp[-2].c_stmt->cmpd_bdy = head_of_this_chain;
			blk_heads.pop_back();
		}
		
		yyval.c_stmt=yyvsp[-2].c_stmt;
	}
    break;

  case 49:
#line 509 "type.y"
    {
		++nest_lev;
		yyval.c_stmt = new struct cmpd_stmt(CMPD_STMT, line_no);
		if(flag_cmpd_stmt_is_a_func_body>=0){
			yyval.c_stmt->sc=func_info_table[flag_cmpd_stmt_is_a_func_body]->func_scope;
			// reset the flag
			flag_cmpd_stmt_is_a_func_body=-1;
		} else {
			yyval.c_stmt->sc= new scope();
		}
		flag_next_stmt_start_of_block=true;
		//cout << "open_curly: cmpd_stmt: " << $$ << endl;
		//cout << "pushed active_scope: " << active_scope << endl;
		//active_scope_list.push_back(active_scope);
		active_scope_list.push_back(yyval.c_stmt->sc);
		active_scope = yyval.c_stmt->sc;
		//cout << "active_scope: " << active_scope << endl;
	}
    break;

  case 50:
#line 530 "type.y"
    { yyval.expr=yyvsp[0].expr; }
    break;

  case 51:
#line 531 "type.y"
    {
		yyval.expr=link_chain(yyvsp[-2].expr,yyvsp[0].expr);
	}
    break;

  case 52:
#line 536 "type.y"
    {
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_plus);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 53:
#line 540 "type.y"
    {
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_minus);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 54:
#line 544 "type.y"
    { 
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_mult);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 55:
#line 548 "type.y"
    {
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_div);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 56:
#line 552 "type.y"
    {
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_mod);
		if(!((yyvsp[-2].expr->type >= INT8_TYPE && yyvsp[-2].expr->type<=U_INT32_TYPE)
				&&
			(yyvsp[0].expr->type>=INT8_TYPE && yyvsp[0].expr->type<=U_INT32_TYPE))){
				cerr << " operands of % should be of type int or char only" << endl;
				++no_errors;
				yyval.expr->type=ERROR_TYPE;
		}
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 57:
#line 563 "type.y"
    {
		yyval.expr = new un_expr(yyvsp[0].expr, oper_umin);
		if(yyvsp[0].expr->type==VOID_TYPE){
			cerr << "line_no: " << line_no << " expression of void type: check if you are calling a void function on either side" << endl;
			yyval.expr->type=ERROR_TYPE;
			++no_errors;
		}
	}
    break;

  case 58:
#line 571 "type.y"
    {
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_lt);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 59:
#line 575 "type.y"
    {
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_gt);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 60:
#line 579 "type.y"
    {
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_le);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 61:
#line 583 "type.y"
    {
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_ge);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 62:
#line 587 "type.y"
    {
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_iseq);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 63:
#line 591 "type.y"
    {
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_isneq);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 64:
#line 595 "type.y"
    {
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_or);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 65:
#line 599 "type.y"
    {
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_and);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 66:
#line 603 "type.y"
    {
		datatype typ1=yyvsp[-2].expr->type;
		datatype typ2=yyvsp[0].expr->type;
		cout << " oper_assgn: LHS type" << typ1 << " RHS type: " << typ2 << endl;
		bool b1=check_type_compat(typ1, typ2)&& yyvsp[-2].expr->is_lvalue();
		if(yyvsp[-2].expr->is_lvalue()){
			yyval.expr = new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_assgn);
		} else {
			yyval.expr = new un2_expr(ERROR_TYPE);
			++no_errors;
			cerr << "oper_assgn error on line: " << line_no<< endl;
		}
	}
    break;

  case 67:
#line 616 "type.y"
    {
		yyval.expr = new un_expr(yyvsp[0].expr, oper_not);
		if(yyvsp[0].expr->type==VOID_TYPE){
			cerr << "line_no: " << line_no << " expression of void type: applying operator ! to void expr" << endl;
			yyval.expr->type=ERROR_TYPE;
			++no_errors;
		}
	}
    break;

  case 68:
#line 624 "type.y"
    {
		yyval.expr = new un2_expr(yyvsp[0].ival);
		//cerr << "type.y: parsed integer: type" << $$->type << endl;
	}
    break;

  case 69:
#line 628 "type.y"
    {
		yyval.expr = new un2_expr(yyvsp[0].dval);
	}
    break;

  case 70:
#line 631 "type.y"
    {
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab(yyvsp[0].name);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "Error: could not find:" << yyvsp[0].name<<"  in symbol table: lineno: " << line_no << "\n";
			++no_errors;
			yyval.expr = new un2_expr(ERROR_TYPE);
		} else {
			yyval.expr = new un2_expr(sym_it->second );
		}
	}
    break;

  case 71:
#line 642 "type.y"
    {
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab(yyvsp[-3].name);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "Error: Array indexing expr could not find:" << yyvsp[-3].name<<"  in symbol table: lineno: " << line_no << "\n";
			++no_errors;
			yyval.expr = new un2_expr(ERROR_TYPE);
		} else {
			struct symtab_ent* se=sym_it->second;

			datatype e_type=yyvsp[-1].expr->type;
			if(e_type>=U_INT8_TYPE && e_type <=INT32_TYPE){
				datatype nametype =arr_deref_type(se->type);
				if(nametype==ERROR_TYPE) {
					cerr << "ERROR: Variable being indexed not of Array Type : Error: lineno: " << line_no << "\n";
					++no_errors;
					yyval.expr = new un2_expr(ERROR_TYPE);
				} else {
					yyval.expr = new un2_expr(oper_arrderef, nametype,  se, yyvsp[-1].expr);
				}
			} else {
				cerr << "ERROR: Array index not of Type Int : Error: lineno: " << line_no << "\n";
				++no_errors;
				yyval.expr = new un2_expr(ERROR_TYPE);
			}
		}
	}
    break;

  case 72:
#line 669 "type.y"
    {
		struct symtab_ent* se=0;
		map<string,symtab_ent*>::iterator sym_it1 = find_in_symtab(yyvsp[-5].name);
		if( sym_it1==active_scope->sym_tab.end()) {
			cerr << "Not able to find :" << yyvsp[-5].name << " in symbol table: line_no" 
				<< line_no
				<< endl;
			++no_errors;
		} else {
			se=sym_it1->second;
		}
		if( !(se)){
			cerr << "Error: could not find name " << yyvsp[-5].name << "  in expr " 
				<< "oper_blk_arr_assgn: " << " line_no: " << line_no;
				++no_errors;
			yyval.expr = new un2_expr(ERROR_TYPE);
		} /*else if(!(lse->type==INT32_TYPE || lse->type==FLOAT_TYPE)){
			cerr << "ERROR: LHS:  " << $1 << ":line_no:" << line_no 
				<< " should be of type float or int"
				<< endl;
			cerr << "lse type: " << lse->type << endl;
			++no_errors;
			$$=new struct err_stmt(line_no);
		}*/ else {
			datatype e_type1=yyvsp[-3].expr->type;
			datatype e_type2=yyvsp[-1].expr->type;
			if( (e_type1>=U_INT8_TYPE && e_type1 <=INT32_TYPE) && 
					(e_type2>=U_INT8_TYPE && e_type2<=INT32_TYPE)){
				datatype d1=arr_deref_type(se->type);
				if(d1==ERROR_TYPE){
					yyval.expr = new un2_expr(ERROR_TYPE);
					cerr << "Type Error:  x: lineno: " << line_no << "\n";
					++no_errors;
				} else {
					yyval.expr = new un2_expr(oper_blk_arr_assgn, d1, se,yyvsp[-3].expr,yyvsp[-1].expr);
				}
			} else {
				yyval.expr = new un2_expr(ERROR_TYPE);
				cerr << "ERROR: NAME  =NAME[EXPR, EXPR] EXPR should be of type int or char: lineno: " 
					<< line_no << "\n";
				++no_errors;
			}
		}
	}
    break;

  case 73:
#line 713 "type.y"
    {
		//cout << "parsing Function call: name: " << $1 << endl;
		string search_for=yyvsp[-3].name;
		bool found=false;
		int index=search_for_func(search_for);
		if(index!=-1) found=true;
		bool skip_type_check=skip_func_type_check(search_for.c_str());
		if( skip_type_check==false  && found==false ) {
			cerr << "ERROR: function call Error on line_no: " << line_no << endl;
			cerr << "function : " << search_for << " used without decl" << endl;
			++ no_errors;
			yyval.expr=new un2_expr(ERROR_TYPE);
		} else {
			datatype my_type=func_info_table[index]->return_type;
			struct expr* e_ptr=trav_chain(yyvsp[-1].expr);
			struct var_list* fparam=func_info_table[index]->param_list;
			bool match=false;
			if(skip_type_check==false){
				match=check_parameters(e_ptr, fparam);
			}
			if(match || skip_type_check){
				yyval.expr=new un2_expr(oper_func_call, my_type, yyvsp[-1].expr, index);
			} else {
				yyval.expr=new un2_expr(ERROR_TYPE);
			}
		}
	}
    break;

  case 74:
#line 740 "type.y"
    {
		yyval.expr = new un2_expr(strdup(yyvsp[0].text_buf));
	}
    break;

  case 75:
#line 743 "type.y"
    { 
		yyval.expr = new un_expr(yyvsp[-1].expr, oper_parexp );
	}
    break;

  case 76:
#line 748 "type.y"
    { 
#ifdef DEBUG_GRAM
	printf("got table defn\n"); 
#endif
	}
    break;

  case 77:
#line 753 "type.y"
    { 
#ifdef DEBUG_GRAM
		printf("recursive tab_defn\n"); 
#endif
	}
    break;

  case 78:
#line 761 "type.y"
    {
		//printf("got table defn: no filter\n");
		yyval.tbl=new table(yyvsp[-2].name,yyvsp[-1].name, line_no);
		// default value for constructor tbl_ptr->filter=NULL;
		table_list.push_back(yyval.tbl);
	}
    break;

  case 79:
#line 767 "type.y"
    {
		//printf("got table defn: with filter\n");
		yyval.tbl=new table(yyvsp[-5].name,yyvsp[-4].name, line_no, yyvsp[-1].expr);
		table_list.push_back(yyval.tbl);
	}
    break;

  case 80:
#line 772 "type.y"
    {
		cerr << "Error in tab section line: " <<
			line_no << endl;
		++ line_no;
		++no_errors;
	}
    break;

  case 81:
#line 780 "type.y"
    {
	}
    break;

  case 82:
#line 782 "type.y"
    {
	}
    break;

  case 83:
#line 786 "type.y"
    {
		basic_ax_stmt* bptr= trav_chain(yyvsp[0].basic_ax_stmt);
		yyval.ax = new ax(bptr,no_count_ax_elems, no_tot_ax_elems, 0);
		
		ax_map[yyvsp[-2].name]=yyval.ax;
#ifdef DEBUG_GRAM
		printf("NAME: $2: %s\n", yyvsp[-2].name);
#endif
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
	}
    break;

  case 84:
#line 797 "type.y"
    {
		basic_ax_stmt* bptr= trav_chain(yyvsp[0].basic_ax_stmt);
		yyval.ax = new ax(bptr,no_count_ax_elems, no_tot_ax_elems, yyvsp[-2].expr);
		ax_map[yyvsp[-5].name]=yyval.ax;
#ifdef DEBUG_GRAM
		printf("NAME: $2: %s\n", yyvsp[-5].name);
#endif
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
	}
    break;

  case 85:
#line 807 "type.y"
    {
		cerr << "Error in axis section line: " <<
			line_no << endl;
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		++no_errors;
	}
    break;

  case 86:
#line 818 "type.y"
    {
		yyval.basic_ax_stmt = yyvsp[0].basic_ax_stmt;
	}
    break;

  case 87:
#line 821 "type.y"
    {
		yyval.basic_ax_stmt=link_chain(yyvsp[-1].basic_ax_stmt, yyvsp[0].basic_ax_stmt);
	}
    break;

  case 88:
#line 826 "type.y"
    {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		yyval.basic_ax_stmt = new tot_ax_stmt (tot_axstmt,yyvsp[-1].text_buf, 0);
	}
    break;

  case 89:
#line 831 "type.y"
    {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		yyval.basic_ax_stmt = new tot_ax_stmt (tot_axstmt,yyvsp[-4].text_buf, yyvsp[-1].expr);
	}
    break;

  case 90:
#line 836 "type.y"
    {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		yyval.basic_ax_stmt = new count_ax_stmt (cnt_axstmt,yyvsp[-4].text_buf, yyvsp[-1].expr);
	}
    break;

  case 91:
#line 841 "type.y"
    {
		yyval.basic_ax_stmt = new ttl_ax_stmt (txt_axstmt,yyvsp[-1].text_buf);
		++no_tot_ax_elems;
	}
    break;


    }

/* Line 991 of yacc.c.  */
#line 2256 "type.c"

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
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab2;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:

  /* Suppress GCC warning that yyerrlab1 is unused when no action
     invokes YYERROR.  */
#if defined (__GNUC_MINOR__) && 2093 <= (__GNUC__ * 1000 + __GNUC_MINOR__) \
    && !defined __cplusplus
  __attribute__ ((__unused__))
#endif


  goto yyerrlab2;


/*---------------------------------------------------------------.
| yyerrlab2 -- pop states until the error token can be shifted.  |
`---------------------------------------------------------------*/
yyerrlab2:
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 847 "type.y"


//void print_stmt_lst( struct stmt * &st);
void print_expr(FILE* edit_out, struct expr * e);
//void print_if_stmt(FILE* edit_out, struct if_stmt * if_stmt);

int	compile();
int	run(char * data_file_name, int rec_len);
void print_table_code(FILE * op, FILE *tab_drv_func, FILE * tab_summ_func);
void print_axis_code(FILE * op, FILE * axes_drv_func);

extern void yyrestart ( FILE *input_file );
	int main(int argc, char* argv[], char* envp[]){
		if(argc!=3) {
			cout << "Usage: " << argv[0] << " <prog-name> <data-file> " << endl;
			exit(0);
		}
		cout << "SOME DEBUGGING INFO: U_INT8_TYPE:" << U_INT8_TYPE 
			<< " U_INT8_ARR_TYPE:" << U_INT8_ARR_TYPE
			<< " U_INT8_REF_TYPE:" << U_INT8_REF_TYPE 
			<< endl;
			
			
		active_scope=new scope();
		active_scope_list.push_back(active_scope);
		cout << "tree_root: " << tree_root << endl;
		
		char * printf_name="printf";
		struct var_list* v_list=0;
		datatype myreturn_type=INT8_TYPE;
		struct func_info* fi=new func_info(printf_name, v_list, myreturn_type);
		func_info_table.push_back(fi);
		
		char *c_arr="c";
		

		FILE * yyin=fopen(argv[1],"r");
		yyrestart(yyin);
		if(yyparse()){
			cout << "Errors in parsing edit: " << no_errors << endl;
			exit(1);
		} else 
			cout << "yyparse finished : now going to print tree: no_errors: "    
			<< " should be 0 or we have a bug in the compiler"<< endl;
		//print_stmt_lst(tree_root);
		if(!no_errors){
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
			fprintf(edit_out, "#include <cstdio>\n#include <iostream>\nusing namespace std;\n" );
			fprintf(edit_out, "#include <sys/types.h>\n" );
			fprintf(edit_out, "int8_t c[%d];\n", rec_len );
			fprintf(edit_out, "#include \"global.C\"\n" );
			if(edit_out==0){
				printf("could not open edit_out.c for writing\n");
				exit(1);
			}
			cout << "printing edit:" << endl;
			tree_root->print_stmt_lst(edit_out);
			fclose(edit_out);
			global_vars=fopen("xtcc_work/global.C", "a+");
			fprintf(global_vars, "#endif /* __NxD_GLOB_VARS_H*/\n");
			fclose(global_vars);
			if(!global_vars){
				cerr << "cannot open global.C for writing" << endl;
				exit(1);
			}
			print_list_counts=fopen("xtcc_work/print_list_counts.C", "a+");
			fprintf(print_list_counts, "}\n");
			fclose(print_list_counts);
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
		if(yyparse()){
			cerr << "parsing tables section failed:" << endl;
			exit(1);
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
		print_table_code(table_op, tab_drv_func, tab_summ_func);
		print_axis_code(axes_op, axes_drv_func);
		fclose(table_op);fclose(tab_drv_func);
		fclose(axes_op); fclose(axes_drv_func);
		bool my_compile_flag=true;
		if(my_compile_flag&&!compile()){
			char * endptr=0;
			int convert_to_base=10;
			//int rec_len=strtol(argv[3],&endptr, convert_to_base);
			return run(argv[2], rec_len);
		}
		return no_errors;
	}

#include <cstdlib>
#include <cstdio>




bool check_type_compat(datatype typ1, datatype typ2){
	cout << "check_type_compat: line_no: I have to convert the below code into a function:"  << line_no << endl;
	datatype td1=typ1;
	datatype td2=typ2;
	if(td1>=U_INT8_REF_TYPE && td1<=DOUBLE_REF_TYPE) td1=datatype(U_INT8_TYPE + typ1-U_INT8_REF_TYPE);
	if(td2>=U_INT8_REF_TYPE && td2<=DOUBLE_REF_TYPE) td2=datatype(U_INT8_TYPE + typ2-U_INT8_REF_TYPE);
	if((td1>=U_INT8_TYPE&&td1<=DOUBLE_TYPE) &&
			td2>=U_INT8_TYPE&&td2<=DOUBLE_TYPE){
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



int check_parameters(struct expr* e, struct var_list* v){
	cout << "check_parameters: called" << endl;
	struct expr* e_ptr=e;
	struct var_list* fparam=v;
	bool match=true;
	/* Important point to note: I am not allowing references in ordinary variable decl
	   Only in function parameter list - the object is to allow modifying of variables
	   in a function as in C++
	   */

	int chk_param_counter=1;
	while (e_ptr && fparam) {
		//e_ptr->print();
		datatype etype=e_ptr->type, fptype=fparam->var_type; 
		if((etype>=U_INT8_TYPE && etype<=DOUBLE_TYPE) && 
			((fptype>=U_INT8_TYPE && fptype<=DOUBLE_TYPE)||
			 (fptype>=U_INT8_REF_TYPE && fptype<=DOUBLE_REF_TYPE))){
			datatype tdt=fptype;
				/* the code below makes a U_INT8_REF_TYPE -> U_INT8_TYPE
				   			a INT8_REF_TYPE -> INT8_TYPE
				 thats because we dont care much about references -> C++
				 does all the hard work. For checking types they are equivalent to us
				*/			
			if(tdt>=U_INT8_REF_TYPE) tdt=datatype(U_INT8_TYPE+tdt-U_INT8_REF_TYPE);
			if(etype <= tdt) {
				cout << "varname: "<< fparam->var_name << " chk_param_counter: " 
				<< chk_param_counter << " passed " << endl;
			}
		} else if ((etype>=U_INT8_ARR_TYPE&&etype<=DOUBLE_ARR_TYPE)&&
				(fptype>=U_INT8_ARR_TYPE&&fptype<=DOUBLE_ARR_TYPE)&&
				(etype==fptype)){
			cout << "varname: "<< fparam->var_name << " chk_param_counter: " 
					<< chk_param_counter << " passed " << endl;
		}else {
			match=false;
			cerr << "Parameter type mismatch name: " << endl;
			cerr << fparam->var_name << " expected type is " << fparam->var_type
				<< " passed type is " << e_ptr->type 
				<< " line_no: " << line_no << " or currently allowed promotion to: " 
				<< e_ptr->type+U_INT8_REF_TYPE
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

/* NxD: I need to write a detailed note about this function's responisibilities
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

		

void	add_func_params_to_cmpd_sc(struct scope * & sc, struct var_list * & v_list, string & fname){
	cout << "add_func_params_to_cmpd_sc: ENTER: sc=" << sc << " v_list:" << v_list << endl;
	struct var_list * v_ptr = v_list;
	while (v_ptr){
		cout << "v_ptr->var_name: " << v_ptr->var_name << endl;
		if(sc->sym_tab.find(v_ptr->var_name)==sc->sym_tab.end()){
			cout << "about to insert : " << v_ptr->var_name << " into cmpd_stmt symbol table" << endl;
			struct symtab_ent* se=new struct symtab_ent;
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

int check_func_decl_with_func_defn(struct var_list* & v_list, int & index, string func_name){
	//cout << "Entered check_func_decl_with_func_defn: " << func_name << endl;
		
	struct var_list* defn_ptr=v_list;
	struct var_list* decl_ptr=func_info_table[index]->param_list;
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
	} else return 0;
}

#include <cstdlib>
int compile(){
	int rval;
	system("rm xtcc_work/temp.C");
	string cmd1="cat xtcc_work/edit_out.c xtcc_work/my_axes_drv_func.C xtcc_work/my_tab_drv_func.C stubs/main_loop.C > xtcc_work/temp.C";
	rval=system(cmd1.c_str());
	if(rval){
		cerr << "unable to cat files" << endl;
		return rval;
	}
	string cmd2="g++ xtcc_work/temp.C -o xtcc_work/myedit.exe";
	rval=system(cmd2.c_str());

	return rval;
}

#include <sstream>
int run(char * data_file_name, int rec_len){
	int rval;
	ostringstream cmd1;
	
	cmd1 << "xtcc_work/myedit.exe " << data_file_name  << " " << rec_len;
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
			fprintf(op, "table_%s_%s():rows(%d), cols(%d),counter(%d*%d){for (int i=0;i<counter.size();++i) counter[i]=0; }\n",
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
			fprintf(op, "\tcout << \"rows: \" << rows << \"cols: \" << cols << endl;");
			fprintf(op, "\t\tfor(int i=0; i<ax_%s.stmt_text.size(); ++i){\n",
					map_iter_s->first.c_str());
			fprintf(op, "\t\t\tcci=0;\n");
			fprintf(op, "\t\t\tcout << ax_%s.stmt_text[i] << \",\";\n", map_iter_s->first.c_str()); 
			fprintf(op, "\t\t\tif(ax_%s.is_a_count_text[i]){\n", map_iter_s->first.c_str());
			fprintf(op, "\t\t\t\tfor(int j=0; j<ax_%s.stmt_text.size(); ++j){\n",
					map_iter_b->first.c_str());
			fprintf(op, "\t\t\t\t\tif(ax_%s.is_a_count_text[j]){\n", map_iter_b->first.c_str());
			fprintf(op, "\t\t\t\t\t\t//cout << \"rci:\" << rci << \"cci:\" << cci << endl;\n");
			fprintf(op, "\t\t\t\t\t\tcout << counter[cci+rci*cols]<<\",\";\n");
			fprintf(op, "\t\t\t\t\t\t++cci;\n");
			fprintf(op, "\t\t\t\t\t}\n");
			fprintf(op, "\t\t\t\t}\n");
			fprintf(op, "\t\t\t\t++rci;\n");
			fprintf(op, "\t\t\t}\n");
			fprintf(op, "\t\tcout << endl;\n");
			fprintf(op, "\t\t}\n");
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


