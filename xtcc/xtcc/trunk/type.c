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
     TOT = 258,
     AX = 259,
     CNT = 260,
     TTL = 261,
     FOR = 262,
     TEXT = 263,
     NAME = 264,
     FNUMBER = 265,
     INUMBER = 266,
     CODELIST = 267,
     LISTA = 268,
     IF = 269,
     ELSE = 270,
     VOID_T = 271,
     U_INT8_T = 272,
     INT8_T = 273,
     U_INT16_T = 274,
     INT16_T = 275,
     U_INT32_T = 276,
     INT32_T = 277,
     FLOAT_T = 278,
     DOUBLE_T = 279,
     AXSTART = 280,
     TABSTART = 281,
     ED_START = 282,
     DATA_STRUCT = 283,
     REC_LEN = 284,
     ED_END = 285,
     TAB = 286,
     COND_START = 287,
     CONTINUE = 288,
     BREAK = 289,
     LOGOR = 290,
     LOGAND = 291,
     NOEQ = 292,
     ISEQ = 293,
     GEQ = 294,
     LEQ = 295,
     NOT = 296,
     UMINUS = 297,
     FUNC_CALL = 298
   };
#endif
#define TOT 258
#define AX 259
#define CNT 260
#define TTL 261
#define FOR 262
#define TEXT 263
#define NAME 264
#define FNUMBER 265
#define INUMBER 266
#define CODELIST 267
#define LISTA 268
#define IF 269
#define ELSE 270
#define VOID_T 271
#define U_INT8_T 272
#define INT8_T 273
#define U_INT16_T 274
#define INT16_T 275
#define U_INT32_T 276
#define INT32_T 277
#define FLOAT_T 278
#define DOUBLE_T 279
#define AXSTART 280
#define TABSTART 281
#define ED_START 282
#define DATA_STRUCT 283
#define REC_LEN 284
#define ED_END 285
#define TAB 286
#define COND_START 287
#define CONTINUE 288
#define BREAK 289
#define LOGOR 290
#define LOGAND 291
#define NOEQ 292
#define ISEQ 293
#define GEQ 294
#define LEQ 295
#define NOT 296
#define UMINUS 297
#define FUNC_CALL 298




/* Copy the first part of user declarations.  */
#line 26 "type.y"

#include "const_defs.h"
#include "symtab.h"
#include "tree.h"
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
	struct stmt * tree_root=NULL;
	bool 	void_check( datatype & type1, datatype & type2, datatype& result_type);
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);

	int flag_cmpd_stmt_is_a_func_body=-1;
//	scope * tmp_storage=NULL;
//int	load_func_param_into_scope(tmp_storage, v_list);
	int lookup_func(string func_name_index);
	//extern vector<table*>	table_list;
	//extern map <string, ax*> ax_map;
	vector<table*>	table_list;
	map <string, ax*> ax_map;

	int no_count_ax_elems=0;
	int no_tot_ax_elems=0;
	int in_a_loop=0;
	int nest_lev=0;
	int rec_len;


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
#line 102 "type.y"
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
#line 255 "type.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 267 "type.c"

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
#define YYLAST   468

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  27
/* YYNRULES -- Number of rules. */
#define YYNRULES  91
/* YYNRULES -- Number of states. */
#define YYNSTATES  212

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    23,     2,     2,     2,    57,    61,     2,
      21,    22,    55,    54,    43,    53,     2,    56,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     4,
      49,    44,    50,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    19,     2,    20,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     6,     2,     8,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     5,
       7,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      45,    46,    47,    48,    51,    52,    58,    59,    60
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,    15,    20,    25,    27,    30,    32,
      34,    36,    38,    40,    42,    44,    46,    48,    50,    52,
      53,    61,    65,    72,    74,    81,    83,    87,    90,    96,
     100,   101,   103,   106,   107,   118,   120,   123,   133,   135,
     137,   139,   142,   145,   148,   153,   161,   171,   177,   185,
     189,   191,   193,   197,   201,   205,   209,   213,   217,   220,
     224,   228,   232,   236,   240,   244,   248,   252,   255,   257,
     259,   261,   266,   271,   273,   277,   281,   283,   286,   291,
     299,   302,   304,   307,   312,   320,   323,   325,   328,   333,
     341,   349
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      63,     0,    -1,    -1,    36,     4,    37,    44,    14,     4,
      64,    35,    65,    38,    -1,    33,     6,    85,     8,    -1,
      34,     6,    83,     8,    -1,    66,    -1,    65,    66,    -1,
      70,    -1,    68,    -1,    24,    -1,    25,    -1,    26,    -1,
      27,    -1,    28,    -1,    29,    -1,    30,    -1,    31,    -1,
      32,    -1,    -1,    67,    12,    21,    72,    22,    69,    79,
      -1,    67,    12,     4,    -1,    67,    12,    19,    14,    20,
       4,    -1,    71,    -1,    67,    12,    21,    72,    22,     4,
      -1,    73,    -1,    72,    43,    73,    -1,    67,    12,    -1,
      67,    12,    19,    14,    20,    -1,    67,    61,    12,    -1,
      -1,    75,    -1,    74,    75,    -1,    -1,    10,    21,    82,
       4,    82,     4,    82,    22,    76,    75,    -1,    78,    -1,
      82,     4,    -1,    12,    44,    12,    19,    82,    43,    82,
      20,     4,    -1,    79,    -1,    70,    -1,    77,    -1,    42,
       4,    -1,    41,     4,    -1,     1,     4,    -1,    16,    12,
      11,     4,    -1,    16,    12,    19,    14,    20,    11,     4,
      -1,    16,    12,    19,    14,    43,    14,    20,    11,     4,
      -1,    17,    21,    82,    22,    75,    -1,    17,    21,    82,
      22,    75,    18,    75,    -1,    80,    74,     8,    -1,     6,
      -1,    82,    -1,    81,    43,    82,    -1,    82,    54,    82,
      -1,    82,    53,    82,    -1,    82,    55,    82,    -1,    82,
      56,    82,    -1,    82,    57,    82,    -1,    53,    82,    -1,
      82,    49,    82,    -1,    82,    50,    82,    -1,    82,    52,
      82,    -1,    82,    51,    82,    -1,    82,    48,    82,    -1,
      82,    47,    82,    -1,    82,    45,    82,    -1,    82,    46,
      82,    -1,    58,    82,    -1,    14,    -1,    13,    -1,    12,
      -1,    12,    19,    82,    20,    -1,    12,    21,    81,    22,
      -1,    11,    -1,    12,    44,    82,    -1,    21,    82,    22,
      -1,    84,    -1,    83,    84,    -1,    39,    12,    12,     4,
      -1,    39,    12,    12,     4,    40,    82,     4,    -1,     1,
       4,    -1,    86,    -1,    85,    86,    -1,     5,    12,     4,
      87,    -1,     5,    12,     4,    40,    82,     4,    87,    -1,
       1,     4,    -1,    88,    -1,    87,    88,    -1,     3,     4,
      11,     4,    -1,     3,     4,    11,     4,    40,    82,     4,
      -1,     7,     4,    11,     4,    40,    82,     4,    -1,     9,
       4,    11,     4,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   201,   201,   201,   209,   215,   223,   226,   231,   232,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   247,
     247,   270,   274,   288,   294,   313,   317,   324,   328,   334,
     340,   346,   347,   352,   352,   357,   358,   366,   429,   432,
     435,   436,   443,   450,   458,   477,   497,   518,   521,   527,
     544,   564,   565,   570,   574,   578,   582,   586,   596,   607,
     611,   615,   619,   623,   627,   631,   635,   639,   650,   667,
     674,   690,   728,   763,   769,   803,   811,   816,   824,   830,
     835,   843,   846,   853,   866,   879,   890,   893,   901,   910,
     919,   928
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOT", "';'", "AX", "'{'", "CNT", "'}'", 
  "TTL", "FOR", "TEXT", "NAME", "FNUMBER", "INUMBER", "CODELIST", "LISTA", 
  "IF", "ELSE", "'['", "']'", "'('", "')'", "'!'", "VOID_T", "U_INT8_T", 
  "INT8_T", "U_INT16_T", "INT16_T", "U_INT32_T", "INT32_T", "FLOAT_T", 
  "DOUBLE_T", "AXSTART", "TABSTART", "ED_START", "DATA_STRUCT", "REC_LEN", 
  "ED_END", "TAB", "COND_START", "CONTINUE", "BREAK", "','", "'='", 
  "LOGOR", "LOGAND", "NOEQ", "ISEQ", "'<'", "'>'", "GEQ", "LEQ", "'-'", 
  "'+'", "'*'", "'/'", "'%'", "NOT", "UMINUS", "FUNC_CALL", "'&'", 
  "$accept", "prog", "@1", "top_level_item_list", "top_level_item", 
  "xtcc_type", "func_defn", "@2", "decl", "func_decl", "decl_comma_list", 
  "var_decl", "statement_list", "statement", "@3", "list_stmt", "if_stmt", 
  "compound_stmt", "open_curly", "expr_list", "expression", "tab_list", 
  "tab_defn", "ax_list", "ax_defn", "ax_stmt_list", "ax_stmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,    59,   259,   123,   260,   125,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,    91,
      93,    40,    41,    33,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,    44,    61,   290,   291,   292,   293,    60,
      62,   294,   295,    45,    43,    42,    47,    37,   296,   297,
     298,    38
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    62,    64,    63,    63,    63,    65,    65,    66,    66,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    69,
      68,    70,    70,    70,    71,    72,    72,    73,    73,    73,
      73,    74,    74,    76,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    77,    77,    77,    78,    78,    79,
      80,    81,    81,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    83,    83,    84,    84,
      84,    85,    85,    86,    86,    86,    87,    87,    88,    88,
      88,    88
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,    10,     4,     4,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       7,     3,     6,     1,     6,     1,     3,     2,     5,     3,
       0,     1,     2,     0,    10,     1,     2,     9,     1,     1,
       1,     2,     2,     2,     4,     7,     9,     5,     7,     3,
       1,     1,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     1,     1,
       1,     4,     4,     1,     3,     3,     1,     2,     4,     7,
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
       0,    73,    70,    69,    68,     0,     0,     0,     0,    87,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    58,
      67,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,     0,    91,
       0,     0,    51,    74,    75,    84,    65,    66,    64,    63,
      59,    60,    62,    61,    54,    53,    55,    56,    57,    79,
      10,    11,    12,    13,    14,    15,    16,    17,    18,     0,
       6,     0,     9,     8,    23,     0,     0,    71,    72,     0,
       3,     7,     0,     0,     0,    52,    21,     0,    30,    89,
      90,     0,     0,     0,    25,     0,    27,     0,    19,    30,
      22,     0,    29,    24,     0,    26,     0,    50,    20,     0,
      28,     0,     0,    70,     0,     0,     0,     0,     0,    39,
       0,    31,    40,    35,    38,     0,    43,     0,     0,     0,
       0,    42,    41,     0,    49,    32,    36,     0,    70,     0,
       0,     0,    30,     0,     0,    44,     0,     0,     0,     0,
       0,     0,     0,    47,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,    48,    33,     0,     0,     0,    37,
      46,    34
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     4,    51,   109,   110,   158,   112,   144,   159,   114,
     133,   134,   160,   161,   208,   162,   163,   164,   149,    81,
     165,    15,    16,    11,    12,    34,    35
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -103
static const short yypact[] =
{
      34,    -5,     1,    11,    16,     5,    24,    25,  -103,    62,
      66,   118,  -103,   123,   113,   102,  -103,    78,  -103,   134,
    -103,  -103,  -103,   127,  -103,  -103,   133,   139,   148,   154,
     162,   173,   174,     7,   121,  -103,   141,  -103,   184,   186,
     187,  -103,    88,  -103,  -103,     7,     7,     7,    -2,  -103,
       7,   164,   179,   196,   212,     7,     7,     7,   317,  -103,
    -103,   121,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,   157,   222,   204,   215,  -103,
     225,    59,   379,   379,  -103,   121,   391,   402,   252,   252,
     137,   137,   137,   137,   131,   131,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,   352,
    -103,   271,  -103,  -103,  -103,     7,     7,  -103,  -103,     7,
    -103,  -103,   110,   172,   185,   379,  -103,   283,   222,  -103,
    -103,   278,    -4,    74,  -103,   295,   319,   328,   337,   222,
    -103,   329,  -103,  -103,   336,  -103,   324,  -103,  -103,   143,
    -103,   341,   325,    92,   335,   327,   381,   382,   375,  -103,
      63,  -103,  -103,  -103,  -103,   211,  -103,     7,    87,    -8,
       7,  -103,  -103,   161,  -103,  -103,  -103,   239,    99,   385,
     377,   353,   222,     7,     7,  -103,   -16,   143,    90,   265,
     280,   383,   378,   442,   337,     7,     7,   389,   376,   143,
     366,   304,  -103,   384,  -103,  -103,   393,   457,   143,  -103,
    -103,  -103
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -103,  -103,  -103,  -103,   354,   -67,  -103,  -103,   -50,  -103,
     282,   323,  -103,  -102,  -103,  -103,  -103,   321,  -103,  -103,
     -33,  -103,   451,  -103,   456,   407,   -29
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      48,     5,    61,   179,   191,    49,     9,     6,   136,   111,
      10,   180,    58,    59,    60,     7,     8,    75,    41,    42,
      43,    44,    80,    82,    83,    13,   113,   192,    45,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,   111,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    49,   137,   175,   113,
      46,   132,    17,    14,   151,    47,    18,     1,     2,   147,
       3,   174,   132,   152,    41,   153,    43,    44,    19,   154,
     155,   118,   123,   124,    45,   193,   125,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   138,   204,    41,   178,
      43,    44,   119,    13,   156,   157,   211,    55,    45,    56,
      24,    55,   194,    56,   126,   132,    46,   139,   184,     9,
      56,    47,    26,    10,    30,    23,    20,    22,    31,   127,
      32,   128,    57,   139,   177,    83,   168,   181,    27,    28,
      46,    14,    30,    57,   151,    47,    31,    29,    32,   147,
     189,   190,    36,   152,    41,   153,    43,    44,    37,   154,
     155,    99,   200,   201,    45,   126,    38,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   129,    39,    40,    33,
     127,    50,   182,    77,   156,   157,    72,    73,    74,   130,
      70,    71,    72,    73,    74,    52,    46,    53,    54,    76,
      78,    47,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,   176,    79,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,   183,   115,   117,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   116,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,   195,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,   122,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,   131,   135,   140,
     117,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,   196,   206,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,   141,    84,
     142,   143,   147,   146,   150,   166,   167,   169,   170,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,   187,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   171,   172,   173,   205,   185,
     120,   186,   198,   202,   197,   207,   203,   209,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
     199,   210,   145,   121,   188,   148,    25,    21,    85
};

static const unsigned char yycheck[] =
{
      33,     6,     4,    11,    20,    34,     1,     6,    12,    76,
       5,    19,    45,    46,    47,     4,     0,    50,    11,    12,
      13,    14,    55,    56,    57,     1,    76,    43,    21,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,   109,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    85,    61,   160,   109,
      53,   128,    37,    39,     1,    58,     4,    33,    34,     6,
      36,     8,   139,    10,    11,    12,    13,    14,    12,    16,
      17,    22,   115,   116,    21,   187,   119,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    22,   199,    11,    12,
      13,    14,    43,     1,    41,    42,   208,    19,    21,    21,
       8,    19,    22,    21,     4,   182,    53,    43,    19,     1,
      21,    58,    44,     5,     3,    12,     8,     4,     7,    19,
       9,    21,    44,    43,   167,   168,    44,   170,     4,    12,
      53,    39,     3,    44,     1,    58,     7,    14,     9,     6,
     183,   184,     4,    10,    11,    12,    13,    14,     4,    16,
      17,     4,   195,   196,    21,     4,     4,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     4,     4,     4,    40,
      19,    40,    21,     4,    41,    42,    55,    56,    57,     4,
      53,    54,    55,    56,    57,    11,    53,    11,    11,    35,
       4,    58,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,     4,     4,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,     4,    40,    20,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    40,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,     4,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    12,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    14,    20,     4,
      20,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    43,    20,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    19,    22,
      12,     4,     6,    14,    20,     4,    21,    12,    21,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    22,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     4,     4,    12,    22,     4,
      38,    14,    14,     4,    11,    11,    20,     4,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      18,     4,   139,   109,   182,   144,    15,    11,    61
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    33,    34,    36,    63,     6,     6,     4,     0,     1,
       5,    85,    86,     1,    39,    83,    84,    37,     4,    12,
       8,    86,     4,    12,     8,    84,    44,     4,    12,    14,
       3,     7,     9,    40,    87,    88,     4,     4,     4,     4,
       4,    11,    12,    13,    14,    21,    53,    58,    82,    88,
      40,    64,    11,    11,    11,    19,    21,    44,    82,    82,
      82,     4,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    82,    35,     4,     4,     4,
      82,    81,    82,    82,    22,    87,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,     4,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    65,
      66,    67,    68,    70,    71,    40,    40,    20,    22,    43,
      38,    66,    12,    82,    82,    82,     4,    19,    21,     4,
       4,    14,    67,    72,    73,    20,    12,    61,    22,    43,
       4,    19,    12,     4,    69,    73,    14,     6,    79,    80,
      20,     1,    10,    12,    16,    17,    41,    42,    67,    70,
      74,    75,    77,    78,    79,    82,     4,    21,    44,    12,
      21,     4,     4,    12,     8,    75,     4,    82,    12,    11,
      19,    82,    21,     4,    19,     4,    14,    22,    72,    82,
      82,    20,    43,    75,    22,     4,    43,    11,    14,    18,
      82,    82,     4,    20,    75,    22,    20,    11,    76,     4,
       4,    75
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
#line 201 "type.y"
    {	char * c_arr="c";  rec_len=yyvsp[-1].ival; active_scope->insert(c_arr, INT8_ARR_TYPE, rec_len, 0);}
    break;

  case 3:
#line 201 "type.y"
    {


	//while ( st_ptr->next) st_ptr=st_ptr->next;
	//while ( $1->next) $1=$1->next;
	tree_root = trav_chain(yyvsp[-1].stmt);
	return 0;
}
    break;

  case 4:
#line 209 "type.y"
    {
#if DEBUG_GRAM
		cout << "got axes\n";
#endif /* DEBUG_GRAM */
		return 0;
	}
    break;

  case 5:
#line 215 "type.y"
    {
#if DEBUG_GRAM
		printf("got TABSTART\n");
#endif /* DEBUG_GRAM */
		return 0;
	}
    break;

  case 6:
#line 223 "type.y"
    {
		yyval.stmt=yyvsp[0].stmt;
	}
    break;

  case 7:
#line 226 "type.y"
    {
		yyval.stmt=link_chain(yyvsp[-1].stmt,yyvsp[0].stmt);
	}
    break;

  case 19:
#line 247 "type.y"
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
#line 256 "type.y"
    {
		cout << "parsed to INT function defn" << endl;
		//struct cmpd_stmt* c_stmt=dynamic_cast <struct cmpd_stmt*> ($7);
		struct cmpd_stmt* c_stmt= yyvsp[0].c_stmt;
		struct scope *sc=c_stmt->sc;
		struct var_list * v_list=trav_chain(yyvsp[-3].v_list);
		struct stmt* func_body=yyvsp[0].c_stmt;
		string search_for=yyvsp[-5].name;
		datatype return_type=yyvsp[-6].dt;
		yyval.stmt=new func_stmt(func_defn, line_no, sc, v_list, func_body, search_for, return_type);
	}
    break;

  case 21:
#line 270 "type.y"
    {
		//cout << "creating simple var of type: " << $1 << endl;
		yyval.stmt = active_scope->insert(yyvsp[-1].name, yyvsp[-2].dt, line_no);
	}
    break;

  case 22:
#line 274 "type.y"
    {
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		//cout << "creating arr var of type: " << $1 << endl;
		datatype dt=datatype(U_INT8_ARR_TYPE+(yyvsp[-5].dt-U_INT8_TYPE));
		yyval.stmt = active_scope->insert(yyvsp[-4].name, dt, yyvsp[-2].ival, line_no);
	}
    break;

  case 23:
#line 288 "type.y"
    {
		yyval.stmt=yyvsp[0].stmt;
	}
    break;

  case 24:
#line 294 "type.y"
    {
		char *name=strdup(yyvsp[-4].name);
		struct var_list* tmp=yyvsp[-2].v_list;
		while(tmp ) {
			//cout << "func_decl: traversing param list: " << tmp->var_name << endl;
			tmp=tmp->next;
		}
		struct var_list* v_list=trav_chain(yyvsp[-2].v_list);
		tmp=v_list;
		while(tmp ) {
			//cout << "func_decl after reversing chain: traversing param list: " << tmp->var_name << endl;
			tmp=tmp->prev;
		}
		datatype return_type=yyvsp[-5].dt;
		yyval.stmt=new func_decl_stmt( func_type, line_no, name,  v_list, return_type);
	}
    break;

  case 25:
#line 313 "type.y"
    {
		 yyval.v_list=yyvsp[0].v_list;
		 cout << "got decl_comma_list : " << endl;
	}
    break;

  case 26:
#line 317 "type.y"
    {
		yyval.v_list=link_chain(yyvsp[-2].v_list,yyvsp[0].v_list);
		//cout << "chaining var_decl : " << endl;
	}
    break;

  case 27:
#line 324 "type.y"
    {
		//cout << "creating simple var of type: " << $1 << endl;
		yyval.v_list=new var_list(yyvsp[-1].dt, yyvsp[0].name);
	}
    break;

  case 28:
#line 328 "type.y"
    {
		/* Neil - I need to fix this */
		//cout << "creating arr var of type: " << $1 << endl;
		datatype dt=datatype(U_INT8_ARR_TYPE+(yyvsp[-4].dt-U_INT8_TYPE));
		yyval.v_list=new var_list(dt, yyvsp[-3].name, yyvsp[-1].ival);
	}
    break;

  case 29:
#line 334 "type.y"
    {
		//cout << "creating ref var of type: " << $1 << endl;
		datatype dt=datatype(U_INT8_REF_TYPE+(yyvsp[-2].dt-U_INT8_TYPE));
		yyval.v_list=new var_list(dt, yyvsp[0].name);
	}
    break;

  case 30:
#line 340 "type.y"
    {
		//$$=new var_list(uninit, "empty");
		yyval.v_list=0;
		}
    break;

  case 31:
#line 346 "type.y"
    {yyval.stmt=yyvsp[0].stmt; }
    break;

  case 32:
#line 347 "type.y"
    {
		yyval.stmt=link_chain(yyvsp[-1].stmt,yyvsp[0].stmt);
	}
    break;

  case 33:
#line 352 "type.y"
    { ++in_a_loop;}
    break;

  case 34:
#line 352 "type.y"
    {
		   yyval.stmt = new struct for_stmt(for_stmt, line_no, yyvsp[-7].expr, yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[0].stmt);
		   cout << "finished parsing FOR" << endl;
		   --in_a_loop;
	   }
    break;

  case 36:
#line 358 "type.y"
    { 
		if(yyvsp[-1].expr->isvalid()){
			yyval.stmt = new expr_stmt(texpr_stmt, line_no, yyvsp[-1].expr);
		} else {
			yyval.stmt = new expr_stmt(error_type, line_no, yyvsp[-1].expr);
		}
		//printf("= %g\n", $1); 
	}
    break;

  case 37:
#line 366 "type.y"
    {
		struct symtab_ent* lse=NULL;
		struct symtab_ent* se=NULL;
		map<string,symtab_ent*>::iterator sym_it1 = find_in_symtab(yyvsp[-8].name);
		map<string,symtab_ent*>::iterator sym_it2 = find_in_symtab(yyvsp[-6].name);
		if( sym_it1==active_scope->sym_tab.end()) {
			cerr << "Not able to find :" << yyvsp[-8].name << " in symbol table: line_no" 
				<< line_no
				<< endl;
			++no_errors;
		} else {
			lse=sym_it1->second;
		}
		if( sym_it2==active_scope->sym_tab.end()) {
			cerr << "Not able to find :" << yyvsp[-6].name << " in symbol table: line_no:" 
				<< line_no
				<< endl;
			++no_errors;
		} else {
			se=sym_it2->second;
		}
		if( !(se&&lse)){
			cerr << "Error: could not find " <<endl;
			if(!se){
				cerr << "RHS: " << yyvsp[-6].name ;
				++no_errors;
			}
			if(!lse ){
				cerr << "LHS: " << yyvsp[-8].name;
				++no_errors;
			}
			if (!(se&&lse)) 
				cerr << "  in symbol table: lineno: " << line_no << endl;
			yyval.stmt=new struct err_stmt(line_no);
		} else if(!(lse->get_type()==INT32_TYPE || lse->get_type()==FLOAT_TYPE)){
			cerr << "ERROR: LHS:  " << yyvsp[-8].name << ":line_no:" << line_no 
				<< " should be of type float or int"
				<< endl;
			cerr << "lse type: " << lse->get_type() << endl;
			++no_errors;
			yyval.stmt=new struct err_stmt(line_no);
		} else {
			
			datatype e_type1=yyvsp[-4].expr->get_type();
			datatype e_type2=yyvsp[-2].expr->get_type();
			if( (e_type1>=U_INT8_TYPE && e_type1 <=INT32_TYPE) && 
					(e_type2>=U_INT8_TYPE && e_type2<=INT32_TYPE)){
				datatype d1=arr_deref_type(se->get_type());
				if(d1==INT8_TYPE){
					yyval.stmt = new blk_arr_assgn_stmt(assgn_stmt, line_no, lse, se,yyvsp[-4].expr,yyvsp[-2].expr);
				} else {
					yyval.stmt=new struct err_stmt(line_no);
					cerr << "Type Error:  x: lineno: " << line_no << "\n";
					++no_errors;
				}
			} else {
				yyval.stmt=new struct err_stmt(line_no);
				cerr << "ERROR: NAME  =NAME[EXPR, EXPR] EXPR should be of type int or char: lineno: " 
					<< line_no << "\n";
				++no_errors;
			}
		}
	}
    break;

  case 38:
#line 429 "type.y"
    {
		yyval.stmt=yyvsp[0].c_stmt;
	}
    break;

  case 39:
#line 432 "type.y"
    {
		yyval.stmt=yyvsp[0].stmt;
	}
    break;

  case 41:
#line 436 "type.y"
    {
		yyval.stmt=new struct break_stmt(break_stmt, line_no);
		if (!in_a_loop){
			cerr << "break statement outside a loop: line_no: " << line_no<< endl;
			++no_errors;
		}
	}
    break;

  case 42:
#line 443 "type.y"
    {
		yyval.stmt=new struct continue_stmt(continue_stmt, line_no);
		if (!in_a_loop){
			cerr << "continue statement outside a loop: line_no: " << line_no<< endl;
			++no_errors;
		}
	}
    break;

  case 43:
#line 450 "type.y"
    {
		cerr << "statement missing ';' around line_no: " << line_no << endl;
		++no_errors;
		yyval.stmt = new struct err_stmt(line_no);
		yyerrok;
	}
    break;

  case 44:
#line 458 "type.y"
    {
		map<string,symtab_ent*>::iterator sym_it = find_in_symtab(yyvsp[-2].name);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << yyvsp[-2].name << " not found in symbol table" << endl;
			++no_errors;
			yyval.stmt=new err_stmt(line_no);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->get_type();
			if( !(name_type>=INT8_TYPE&&name_type<=DOUBLE_TYPE)){
				cerr << "NAME: "<< yyvsp[-2].name 
					<< " should be of basic type: " << line_no << endl;
				++no_errors;
				yyval.stmt=new struct err_stmt(line_no);
			} else {
				yyval.stmt=new list_stmt(lista_basic_type_stmt, line_no, se);
			}
		}
	}
    break;

  case 45:
#line 477 "type.y"
    {
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab(yyvsp[-5].name);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << yyvsp[-5].name << " not found in symbol table" << endl;
			++no_errors;
			yyval.stmt=new err_stmt(line_no);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->get_type();
			if( !(name_type>=INT8_ARR_TYPE&&name_type<=DOUBLE_ARR_TYPE)){
				cerr << "NAME: "<< yyvsp[-5].name 
					<< " is not of array type: line_no:" << line_no << endl;
				++no_errors;
				yyval.stmt=new err_stmt(line_no);
			} else {
				yyval.stmt=new list_stmt( lista_basic_arrtype_stmt_1index, line_no, se, yyvsp[-3].ival, -1, string(yyvsp[-1].text_buf));
			}
		}
	}
    break;

  case 46:
#line 497 "type.y"
    {
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab(yyvsp[-7].name);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << yyvsp[-7].name << " not found in symbol table" << endl;
			++no_errors;
			yyval.stmt=new err_stmt(line_no);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->get_type();
			if( !(name_type==INT8_ARR_TYPE||name_type==U_INT8_TYPE)){
				cerr << "NAME: "<< yyvsp[-7].name 
					<< " is not of char array type: line_no:" << line_no << endl;
				++no_errors;
			} else {
				yyval.stmt=new list_stmt( lista_basic_arrtype_stmt_2index, line_no, se, yyvsp[-5].ival, yyvsp[-3].ival, string(yyvsp[-1].text_buf));
			}
		}
	}
    break;

  case 47:
#line 518 "type.y"
    {
		yyval.stmt=new if_stmt(ife_stmt,line_no,yyvsp[-2].expr,yyvsp[0].stmt,0);
	}
    break;

  case 48:
#line 521 "type.y"
    {
		yyval.stmt=new if_stmt(ife_stmt, line_no,yyvsp[-4].expr,yyvsp[-2].stmt,yyvsp[0].stmt);
	}
    break;

  case 49:
#line 527 "type.y"
    {
		cout << "popping scope: " <<
			active_scope_list[active_scope_list.size()-1] << endl;
		active_scope_list.pop_back();
		int tmp=active_scope_list.size()-1;
		if(tmp==-1) { 
			active_scope = NULL;
			cerr << "Error: active_scope = NULL: should not happen: line_no:" << line_no
				<< endl;
			++no_errors;
			yyval.c_stmt=new struct cmpd_stmt(error_type, line_no);
		} else { active_scope = active_scope_list[tmp]; }
		yyvsp[-2].c_stmt->cmpd_bdy = trav_chain(yyvsp[-1].stmt);
		yyval.c_stmt=yyvsp[-2].c_stmt;
	}
    break;

  case 50:
#line 544 "type.y"
    {
		++nest_lev;
		yyval.c_stmt = new struct cmpd_stmt(cmpd_stmt, line_no);
		if(flag_cmpd_stmt_is_a_func_body>=0){
			yyval.c_stmt->sc=func_info_table[flag_cmpd_stmt_is_a_func_body]->func_scope;
			// reset the flag
			flag_cmpd_stmt_is_a_func_body=-1;
		} else {
			yyval.c_stmt->sc= new scope();
		}
		//cout << "open_curly: cmpd_stmt: " << $$ << endl;
		//cout << "pushed active_scope: " << active_scope << endl;
		//active_scope_list.push_back(active_scope);
		active_scope_list.push_back(yyval.c_stmt->sc);
		active_scope = yyval.c_stmt->sc;
		//cout << "active_scope: " << active_scope << endl;
	}
    break;

  case 51:
#line 564 "type.y"
    { yyval.expr=yyvsp[0].expr; }
    break;

  case 52:
#line 565 "type.y"
    {
		yyval.expr=link_chain(yyvsp[-2].expr,yyvsp[0].expr);
	}
    break;

  case 53:
#line 570 "type.y"
    {
		yyval.expr=new expr(yyvsp[-2].expr, yyvsp[0].expr, oper_plus);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 54:
#line 574 "type.y"
    {
		yyval.expr=new expr(yyvsp[-2].expr, yyvsp[0].expr, oper_minus);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 55:
#line 578 "type.y"
    { 
		yyval.expr=new expr(yyvsp[-2].expr, yyvsp[0].expr, oper_mult);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 56:
#line 582 "type.y"
    {
		yyval.expr=new expr(yyvsp[-2].expr, yyvsp[0].expr, oper_div);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 57:
#line 586 "type.y"
    {
		if(!((yyvsp[-2].expr->get_type() >= INT8_TYPE && yyvsp[-2].expr->get_type()<=U_INT32_TYPE)
				&&
			(yyvsp[0].expr->get_type()>=INT8_TYPE && yyvsp[0].expr->get_type()<=U_INT32_TYPE))){
				cerr << " operands of % should be of type int or char only" << endl;
				++no_errors;
		}
		yyval.expr=new expr(yyvsp[-2].expr, yyvsp[0].expr, oper_mod);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 58:
#line 596 "type.y"
    {
		yyval.expr = new_expr();
		yyval.expr->l_op = yyvsp[0].expr;
		yyval.expr->type = yyvsp[0].expr->get_type();
		yyval.expr->e_operator = oper_umin;
		if(yyvsp[0].expr->type==VOID_TYPE){
			cerr << "line_no: " << line_no << " expression of void type: check if you are calling a void function on either side" << endl;
			yyval.expr->type=error_type;
			++no_errors;
		}
	}
    break;

  case 59:
#line 607 "type.y"
    {
		yyval.expr=new expr(yyvsp[-2].expr, yyvsp[0].expr, oper_lt);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 60:
#line 611 "type.y"
    {
		yyval.expr=new expr(yyvsp[-2].expr, yyvsp[0].expr, oper_gt);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 61:
#line 615 "type.y"
    {
		yyval.expr=new expr(yyvsp[-2].expr, yyvsp[0].expr, oper_le);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 62:
#line 619 "type.y"
    {
		yyval.expr=new expr(yyvsp[-2].expr, yyvsp[0].expr, oper_ge);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 63:
#line 623 "type.y"
    {
		yyval.expr=new expr(yyvsp[-2].expr, yyvsp[0].expr, oper_iseq);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 64:
#line 627 "type.y"
    {
		yyval.expr=new expr(yyvsp[-2].expr, yyvsp[0].expr, oper_isneq);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 65:
#line 631 "type.y"
    {
		yyval.expr=new expr(yyvsp[-2].expr, yyvsp[0].expr, oper_or);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 66:
#line 635 "type.y"
    {
		yyval.expr=new expr(yyvsp[-2].expr, yyvsp[0].expr, oper_and);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	}
    break;

  case 67:
#line 639 "type.y"
    {
		yyval.expr = new_expr();
		yyval.expr->l_op = yyvsp[0].expr;
		yyval.expr->type = yyvsp[0].expr->get_type();
		yyval.expr->e_operator = oper_not;
		if(yyvsp[0].expr->type==VOID_TYPE){
			cerr << "line_no: " << line_no << " expression of void type: applying operator ! to void expr" << endl;
			yyval.expr->type=error_type;
			++no_errors;
		}
	}
    break;

  case 68:
#line 650 "type.y"
    {
		yyval.expr = new_expr();
		yyval.expr->l_op = NULL;
		yyval.expr->isem_value = yyvsp[0].ival;
		if( yyvsp[0].ival > SCHAR_MIN && yyvsp[0].ival<SCHAR_MAX){
			yyval.expr->type=INT8_TYPE;
		} else if (yyvsp[0].ival> SHRT_MIN && yyvsp[0].ival < SHRT_MAX){
			yyval.expr->type=INT16_TYPE;
		} else if (yyvsp[0].ival> INT_MIN && yyvsp[0].ival < INT_MAX){
			yyval.expr->type=INT32_TYPE;
		} else {
			++no_errors;
			cerr << "very  integer unhandleable type most probably";
			yyval.expr->type = error_type;
		}
		yyval.expr->e_operator = oper_num;
	}
    break;

  case 69:
#line 667 "type.y"
    {
		yyval.expr = new_expr();
		yyval.expr->l_op = NULL;
		yyval.expr->dsem_value = yyvsp[0].dval;
		yyval.expr->type = FLOAT_TYPE;
		yyval.expr->e_operator = oper_float;
	}
    break;

  case 70:
#line 674 "type.y"
    {
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab(yyvsp[0].name);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "Error: could not find:" << yyvsp[0].name<<"  in symbol table: lineno: " << line_no << "\n";
			++no_errors;
			yyval.expr = new_expr();
			yyval.expr->type=error_type;
			yyval.expr->e_operator = oper_name;
		} else {
			yyval.expr = new_expr();
			yyval.expr->symp=sym_it->second;
			yyval.expr->type = sym_it->second->get_type();
			yyval.expr->e_operator = oper_name;
		}
	}
    break;

  case 71:
#line 690 "type.y"
    {
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab(yyvsp[-3].name);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "Error: could not find:" << yyvsp[-3].name<<"  in symbol table: lineno: " << line_no << "\n";
			++no_errors;
			yyval.expr = new_expr();
			yyval.expr->type=error_type;
			//$$->type='R';
			yyval.expr->e_operator = oper_arrderef;
		} else {
			struct symtab_ent* se=sym_it->second;
			yyval.expr = new_expr();
			yyval.expr->symp=se;
			yyval.expr->l_op=yyvsp[-1].expr;
			cout << "$1: name : " << yyvsp[-3].name << " $1:type " << se->get_type() << endl;
			datatype name_type=se->get_type();
			if( !(name_type>=INT8_ARR_TYPE&&name_type<=DOUBLE_ARR_TYPE)){
				cerr << "NAME: "<< yyvsp[-3].name 
					<< " is not of array type: line_no:" << line_no << endl;
				++no_errors;
			}
			datatype e_type=yyvsp[-1].expr->get_type();
			cout << "NAME [expression ]:e_type:" << e_type << endl;
			if(e_type>=U_INT8_TYPE && e_type <=INT32_TYPE){
				yyval.expr->type =arr_deref_type(se->get_type());
				if(yyval.expr->type==error_type) {
					cerr << "ERROR: Variable being indexed not of Array Type : Error: lineno: " << line_no << "\n";
					++no_errors;
				}
			} else {
				yyval.expr->type=error_type;
				cerr << "ERROR: Array index not of Type Int : Error: lineno: " << line_no << "\n";
				++no_errors;
			}
			yyval.expr->e_operator = oper_arrderef;
		}
	}
    break;

  case 72:
#line 728 "type.y"
    {
		cout << "parsing Function call: name: " << yyvsp[-3].name << endl;
		string search_for=yyvsp[-3].name;
		bool found=false;
		int index=search_for_func(search_for);
		if(index!=-1) found=true;
		bool skip_type_check=skip_func_type_check(search_for.c_str());
		if( skip_type_check==false  && found==false ) {
			cerr << "ERROR: function call Error on line_no: " << line_no << endl;
			cerr << "function : " << search_for << " used without decl" << endl;
			++ no_errors;
			yyval.expr=new_expr();
			yyval.expr->type=error_type;
		} else {
			datatype my_type=func_info_table[index]->return_type;
			struct expr* e_ptr=trav_chain(yyvsp[-1].expr);
			struct var_list* fparam=func_info_table[index]->param_list;
			bool match=false;
			if(skip_type_check==false){
				match=check_parameters(e_ptr, fparam);
			}
			if(match || skip_type_check){
				yyval.expr=new_expr();
				yyval.expr->type=my_type;
				yyval.expr->e_operator=oper_func_call;
				yyval.expr->func_index_in_table=index;
				yyval.expr->l_op = yyvsp[-1].expr;
			} else {
				yyval.expr=new_expr();
				yyval.expr->type=error_type;
				yyval.expr->e_operator=oper_func_call;
				yyval.expr->func_index_in_table=index;
			}
		}
	}
    break;

  case 73:
#line 763 "type.y"
    {
		yyval.expr=new_expr();
		yyval.expr->type=INT8_ARR_TYPE;
		yyval.expr->text=strdup(yyvsp[0].text_buf);
		yyval.expr->e_operator=oper_text_expr;
	}
    break;

  case 74:
#line 769 "type.y"
    {
		cout << "BEGIN parse oper_assgn: line_no: "<<  line_no << endl;
		map<string,symtab_ent*>::iterator sym_it = find_in_symtab(yyvsp[-2].name);
		yyval.expr = new_expr();
		struct symtab_ent* se= NULL;
		cout << "CAME HERE1 parse oper_assgn: line_no: "<<  line_no << endl;
		if( sym_it==active_scope->sym_tab.end()) {
			cerr << "Error: could not find name in symbol table NAME:" << yyvsp[-2].name << endl;
			++no_errors;
			yyval.expr->type=error_type;
		} else if( yyvsp[0].expr->isvalid()){
			cout << "CAME HERE2 parse oper_assgn: line_no: "<<  line_no << endl;
			se= sym_it->second;
			yyval.expr->symp=se;
			yyval.expr->type = uninit;
			yyval.expr->e_operator=oper_assgn;
			yyval.expr->r_op= yyvsp[0].expr;
			datatype typ1=se->get_type();
			datatype typ2=yyvsp[0].expr->type;
			bool b1=check_type_compat(typ1, typ2);
			if(!b1) {
				cerr << "Error : assigning incompatible types line_no" << line_no << endl;
				++no_errors;
			}
			cout << "parsed oper_assgn: line_no: "<<  line_no << endl;
			//Finish the test HERE
		} else {
			yyval.expr->symp=se;
			yyval.expr->type=error_type;
			yyval.expr->r_op=yyvsp[0].expr;
			++no_errors;
			cerr << "Propagating type error to oper_assgn: line_no: " << line_no << endl;
		}
	}
    break;

  case 75:
#line 803 "type.y"
    { 
		yyval.expr = new_expr();
		yyval.expr->l_op = yyvsp[-1].expr;
		yyval.expr->type = yyvsp[-1].expr->type;
		yyval.expr->e_operator = oper_parexp;
	}
    break;

  case 76:
#line 811 "type.y"
    { 
#ifdef DEBUG_GRAM
	printf("got table defn\n"); 
#endif
	}
    break;

  case 77:
#line 816 "type.y"
    { 
#ifdef DEBUG_GRAM
		printf("recursive tab_defn\n"); 
#endif
	}
    break;

  case 78:
#line 824 "type.y"
    {
		//printf("got table defn: no filter\n");
		yyval.tbl=new table(yyvsp[-2].name,yyvsp[-1].name, line_no);
		// default value for constructor tbl_ptr->filter=NULL;
		table_list.push_back(yyval.tbl);
	}
    break;

  case 79:
#line 830 "type.y"
    {
		//printf("got table defn: with filter\n");
		yyval.tbl=new table(yyvsp[-5].name,yyvsp[-4].name, line_no, yyvsp[-1].expr);
		table_list.push_back(yyval.tbl);
	}
    break;

  case 80:
#line 835 "type.y"
    {
		cerr << "Error in tab section line: " <<
			line_no << endl;
		++ line_no;
		++no_errors;
	}
    break;

  case 81:
#line 843 "type.y"
    {
		//$$ = $1;
	}
    break;

  case 82:
#line 846 "type.y"
    {
		//$2->next_ax = $1;
		//$1->prev_ax = $2;
		//$$ = $2;
	}
    break;

  case 83:
#line 853 "type.y"
    {
		basic_ax_stmt* bptr= trav_chain(yyvsp[0].basic_ax_stmt);
		yyval.ax = new ax(bptr,no_count_ax_elems, no_tot_ax_elems, NULL);
		
		//$$->ax_stmt_start = $4;
		//$$->ax_name = $2;
		ax_map[yyvsp[-2].name]=yyval.ax;
#ifdef DEBUG_GRAM
		printf("NAME: $2: %s\n", yyvsp[-2].name);
#endif
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
	}
    break;

  case 84:
#line 866 "type.y"
    {
		basic_ax_stmt* bptr= trav_chain(yyvsp[0].basic_ax_stmt);
		yyval.ax = new ax(bptr,no_count_ax_elems, no_tot_ax_elems, yyvsp[-2].expr);
		//$$->filter = $5;
		//$$->ax_stmt_start = $7;
		//$$->ax_name = $2;
		ax_map[yyvsp[-5].name]=yyval.ax;
#ifdef DEBUG_GRAM
		printf("NAME: $2: %s\n", yyvsp[-5].name);
#endif
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
	}
    break;

  case 85:
#line 879 "type.y"
    {
		cerr << "Error in axis section line: " <<
			line_no << endl;
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		++no_errors;
	}
    break;

  case 86:
#line 890 "type.y"
    {
		yyval.basic_ax_stmt = yyvsp[0].basic_ax_stmt;
	}
    break;

  case 87:
#line 893 "type.y"
    {
		//$2->next = $1;
		//$1->prev = $2;
		//$$ = $2;
		yyval.basic_ax_stmt=link_chain(yyvsp[-1].basic_ax_stmt, yyvsp[0].basic_ax_stmt);
	}
    break;

  case 88:
#line 901 "type.y"
    {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		yyval.basic_ax_stmt = new tot_ax_stmt (tot_axstmt,yyvsp[-1].text_buf, NULL);
		if (yyval.basic_ax_stmt == NULL){
			cout << "Failed to allocate memory\n";
			exit(1);
		}
	}
    break;

  case 89:
#line 910 "type.y"
    {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		yyval.basic_ax_stmt = new tot_ax_stmt (tot_axstmt,yyvsp[-4].text_buf, yyvsp[-1].expr);
		if (yyval.basic_ax_stmt == NULL){
			cout << "Failed to allocate memory\n";
			exit(1);
		}
	}
    break;

  case 90:
#line 919 "type.y"
    {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		yyval.basic_ax_stmt = new count_ax_stmt (cnt_axstmt,yyvsp[-4].text_buf, yyvsp[-1].expr);
		if (yyval.basic_ax_stmt == NULL){
			cout << "Failed to allocate memory\n";
			exit(1);
		}
	}
    break;

  case 91:
#line 928 "type.y"
    {
		yyval.basic_ax_stmt = new ttl_ax_stmt (txt_axstmt,yyvsp[-1].text_buf);
		++no_tot_ax_elems;
	}
    break;


    }

/* Line 991 of yacc.c.  */
#line 2344 "type.c"

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


#line 934 "type.y"


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
		struct var_list* v_list=NULL;
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
			if(edit_out==NULL){
				printf("could not open edit_out.c for writing\n");
				exit(1);
			}
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
			char * endptr=NULL;
			int convert_to_base=10;
			//int rec_len=strtol(argv[3],&endptr, convert_to_base);
			return run(argv[2], rec_len);
		}
		return no_errors;
	}

#include <cstdlib>
#include <cstdio>


void print_expr(FILE* edit_out, struct expr * e){
	if(e) {
		switch(e->e_operator){
			char oper_buf[3];

			case oper_plus:{
				fprintf(edit_out, "/* oper_plus */");	       
				sprintf(oper_buf, "%s" , "+");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_minus:{
				sprintf(oper_buf, "%s" , "-");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_mult:{
				sprintf(oper_buf, "%s" , "*");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_div:{
				sprintf(oper_buf, "%s" , "/");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_mod:{
				sprintf(oper_buf, "%s" , "%");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	      
			case oper_lt:{
				sprintf(oper_buf, "%s" , "<");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_gt:{
				sprintf(oper_buf, "%s" , ">");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_le:{
				sprintf(oper_buf, "%s" , "<=");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_ge:{
				sprintf(oper_buf, "%s" , ">=");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_iseq:{
				sprintf(oper_buf, "%s" , "==");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			case oper_isneq: {
				sprintf(oper_buf, "%s" , "!=");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, " %s ", oper_buf);
				print_expr(edit_out, e->r_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;	       
			

			case oper_parexp:{
				fprintf(edit_out, "(");
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, ")");
				//fprintf(edit_out, "/* %d */\n", e->type);
				}
			break;

			case oper_num:{
				fprintf(edit_out, "%d ", e->isem_value);
				//fprintf(edit_out, "/* %d */\n", e->type);
				      }
			break;
			case oper_float:{
				fprintf(edit_out, "%f ", e->dsem_value);
				//fprintf(edit_out, "/* %d */\n", e->type);
				      }
			break;

			case oper_name:{
				fprintf(edit_out, "%s ", e->symp->name);
				//fprintf(edit_out, "/* %d */\n", e->type);
				       }
			break;

			case oper_umin:{
				fprintf(edit_out, "- ");
				print_expr(edit_out, e->l_op);
				//fprintf(edit_out, "/* %d */\n", e->type);
				       }
			break;

			case oper_arrderef:{
				fprintf(edit_out, "%s[", e->symp->name);
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, "]");
				//fprintf(edit_out, "/* %d */\n", e->type);
					   }
			break;
			case oper_arr2deref:{
				fprintf(edit_out, "%s[", e->symp->name);
				print_expr(edit_out, e->l_op);
				fprintf(edit_out, ",");
				print_expr(edit_out, e->r_op);
				fprintf(edit_out, "]");
				//fprintf(edit_out, "/* %d */\n", e->type);
				// Note : flag runtime error if r_op-l_op>=3
					    }
			break;
			case oper_func_call:{
				//cout << "func_index_in_table: " << e->func_index_in_table << endl;
				cout << "func_index_in_table: " << func_info_table[e->func_index_in_table]->fname << endl;
				fprintf(edit_out, "%s(", func_info_table[e->func_index_in_table]->fname.c_str());
				struct expr* e_ptr=e->l_op;
				fprintf(edit_out,  "/*print_expr: oper_func_call:  %s*/", func_info_table[e->func_index_in_table]->fname.c_str() );
				while(e_ptr){
					print_expr(edit_out, e_ptr);
					if(e_ptr->prev){
						fprintf(edit_out, ", ");
					} 
					e_ptr=e_ptr->prev;
				}
				fprintf(edit_out, ")");
			}
			break;
			case oper_text_expr:{
				fprintf(edit_out, "%s", e->text);
			}
			break;
			case oper_assgn:{
				fprintf(edit_out, "/*oper_assgn*/ %s =", e->symp->name);
				print_expr(edit_out, e->r_op);
			}
			break;
			case oper_not:{
				fprintf(edit_out, "! ");
				print_expr(edit_out, e->l_op);
			}
			break;
					


			default:
				fprintf(edit_out, "Unhandled expression type: %c\n", 
					e->type);
		}
	}
}



bool check_type_compat(datatype typ1, datatype typ2){
	cout << "check_type_compat: line_no: I have to convert the below code into a function"  << line_no << endl;
	datatype td1=typ1;
	datatype td2=typ2;
	if(td1>=U_INT8_REF_TYPE && td1<=DOUBLE_REF_TYPE) td1=datatype(U_INT8_TYPE + typ1-U_INT8_REF_TYPE);
	if(td2>=U_INT8_REF_TYPE && td2<=DOUBLE_REF_TYPE) td2=datatype(U_INT8_TYPE + typ2-U_INT8_REF_TYPE);
	if((td1>=U_INT8_TYPE&&td1<=DOUBLE_TYPE) &&
			td2>=U_INT8_TYPE&&td2<=DOUBLE_TYPE){
		if(td1>=td2){
			return true;
		}
	}
	cerr << "ERROR: Assigning unhandle_able Type to var:  line_no" << line_no 
		<< " LHS type: " << typ1 
		<< " RHS type: " << typ2 
		<< endl;
	++no_errors;
	return false;
}



int check_parameters(struct expr* e, struct var_list* v){
	cout << "check_parameters: called" << endl;
	struct expr* e_ptr=e;
	struct var_list* fparam=v;
	bool match=true;
	int count=0;
	struct expr* tmp_e=e;
	// No need to reverse chain any more: start here NxD: 22-jun-2007
	while (tmp_e) { 
		//e_ptr->print();
		count=count+1; 
		//cout << "count: " << count << endl;
		if(tmp_e->prev) tmp_e=tmp_e->prev; 
		else break;
	}
	int pcount=0;
	struct var_list* tmp_v=fparam ;
	while (tmp_v) { 
		//cout << "fparam->var_name: " << fparam->var_name << " ";
		pcount=pcount+1; 
		//cout << "pcount: " << pcount << endl;
		if(tmp_v->prev) tmp_v=tmp_v->prev; 
		else break;
	}
	if(count!=pcount) {
		cerr << "Number of parameters used in func call: " << count 
			<< " does not match number of parameters in function: = " << pcount 
			<< " line_no: " << line_no
			<< endl;
		++no_errors;
		match=false;
	}
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
			if(tdt>U_INT8_REF_TYPE) tdt=datatype(U_INT8_TYPE+tdt-U_INT8_REF_TYPE);
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
				<< " line_no: " << line_no << " or currently allowed promotion to: " << e_ptr->type+U_INT8_REF_TYPE
				<< endl;
			++no_errors;
		}
		e_ptr=e_ptr->prev;
		fparam=fparam->prev;
		chk_param_counter=chk_param_counter+1;
	}
	if(match==true){
		if(e_ptr==NULL&& fparam==NULL){
			match=true;
			//cout << "e_ptr && fparam are both NULL" << endl;
		}
		else 
			match=false;
	}
	if(match) {
		cout << "function passed parameter type check: n_params:" << chk_param_counter << endl;
	} else {
		cerr << "function parameter type check FAILURE: line_no " << line_no << endl;
	}
	return match;
}

map<string, symtab_ent*>::iterator find_in_symtab(string id){
	bool found=false;
	int i=active_scope_list.size()-1;
	cout << "START: find_in_symtab: i=" << i <<endl;

	map<string,symtab_ent*>::iterator sym_it ; 
	for(;i>-1;--i){
		sym_it = active_scope_list[i]->sym_tab.find(id);
		if (sym_it == active_scope_list[i]->sym_tab.end() ){
		} else {
			found = true;
			cout << "found" << endl;
			break;
		}
	}
	if(found==false){
		cout << "ID:" << id <<
			": not found in any scope\n";
		int j=active_scope_list.size()-1;
		map<string,symtab_ent*>::iterator it;
		for(; j>-1; --j){
			cout <<"searching in: " << 
				active_scope_list[j];
			cout << "j=" << j << endl;
			for(it=active_scope_list[j]->sym_tab.begin();
				it!=active_scope_list[j]->sym_tab.end();
				++it){
				cout << it->first << ",";
			}
		}
		return active_scope->sym_tab.end();
	} else {
		cout << "ID:" << id <<
			": found at scope level:" <<
			i << endl;
		return sym_it;
	}
}

/* NxD: I need to write a detailed note about this function's responisibilities
   */
   

	bool skip_func_type_check(const char * fname){
		cout << "skip_func_type_check: BEGIN" << endl;
		char * skip_func_type_check_list[] = {"printf" };
		for (unsigned int i=0; i<sizeof(skip_func_type_check_list)/sizeof(skip_func_type_check_list[0]); ++i){
			if(!strcmp(fname, skip_func_type_check_list[i])){
				cout << "skip_func_type_check: returned true: fname: " << fname << endl;
				return true;
			}
		}
		cout << "skip_func_type_check: returned false: fname: " << fname << endl;
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
	cout << "Entered search_for_func: " << endl;
	unsigned int i=0;
	
	for (i=0;i<func_info_table.size();++i){
		if(search_for==func_info_table[i]->fname){
			cout << "search_for_func(): found: " << search_for 
				<< " index: " << i
				<< endl;
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
	if(defn_ptr==decl_ptr && decl_ptr==NULL){
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
		result_type=error_type;
		++no_errors;
		return false;
	} else {
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
			//construct_internal_table(ax_map, table_list);
			//cout << "constructing table: " <<
			expr* f= table_list[i]->filter;
			cout << "table: " <<
				map_iter_b->first << " by " <<
				map_iter_s->first << endl;
			if ( f ){
				cout << " Filter: " ;
			}
				/*
			internal_table * itbl_ptr = 
				new internal_table(map_iter_s, map_iter_b, f, i);
			itbl_vec.push_back(itbl_ptr);
			*/
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
					print_expr(op, bc->condn);
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


