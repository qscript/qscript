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
     INC = 263,
     FOR = 264,
     FLD = 265,
     BIT = 266,
     TEXT = 267,
     NAME = 268,
     DEFINELIST = 269,
     FNUMBER = 270,
     INUMBER = 271,
     CODELIST = 272,
     LISTA = 273,
     IF = 274,
     ELSE = 275,
     IN = 276,
     VOID_T = 277,
     INT8_T = 278,
     INT16_T = 279,
     INT32_T = 280,
     FLOAT_T = 281,
     DOUBLE_T = 282,
     ATTRIBUTE_LIST = 283,
     AXSTART = 284,
     TABSTART = 285,
     ED_START = 286,
     DATA_STRUCT = 287,
     REC_LEN = 288,
     ED_END = 289,
     TAB = 290,
     COND_START = 291,
     CONTINUE = 292,
     BREAK = 293,
     LOGOR = 294,
     LOGAND = 295,
     NOEQ = 296,
     ISEQ = 297,
     GEQ = 298,
     LEQ = 299,
     NOT = 300,
     UMINUS = 301,
     FUNC_CALL = 302
   };
#endif
/* Tokens.  */
#define CONVERT 258
#define TOT 259
#define AX 260
#define CNT 261
#define TTL 262
#define INC 263
#define FOR 264
#define FLD 265
#define BIT 266
#define TEXT 267
#define NAME 268
#define DEFINELIST 269
#define FNUMBER 270
#define INUMBER 271
#define CODELIST 272
#define LISTA 273
#define IF 274
#define ELSE 275
#define IN 276
#define VOID_T 277
#define INT8_T 278
#define INT16_T 279
#define INT32_T 280
#define FLOAT_T 281
#define DOUBLE_T 282
#define ATTRIBUTE_LIST 283
#define AXSTART 284
#define TABSTART 285
#define ED_START 286
#define DATA_STRUCT 287
#define REC_LEN 288
#define ED_END 289
#define TAB 290
#define COND_START 291
#define CONTINUE 292
#define BREAK 293
#define LOGOR 294
#define LOGAND 295
#define NOEQ 296
#define ISEQ 297
#define GEQ 298
#define LEQ 299
#define NOT 300
#define UMINUS 301
#define FUNC_CALL 302




/* Copy the first part of user declarations.  */
#line 26 "type.y"

//#include "../../qscript/trunk/named_attributes.h"

#include <cstring>
#include <iostream>
#include <vector>
#include <map>
#include <sys/types.h>
#include <limits.h>
#include "scope.h"
#include "xtcc_set.h"
#include "named_attributes.h"
#include "const_defs.h"
#include "symtab.h"
#include "debug_mem.h"
#include "utils.h"
#include "expr.h"
#include "stmt.h"
#include "Tab.h"


	const bool XTCC_DEBUG_MEM_USAGE=1;
	XtccSet xs;

//	struct symtab symtab;
	extern int if_line_no;
	int no_errors=0;
	int no_warn=0;
	int yylex();
	void yyerror(char * s);
	extern int line_no;
	extern char * yytext;
	bool check_type_compat(DataType typ1, DataType typ2);
	vector <Statement::FunctionInformation*> func_info_table;
	int check_parameters(struct Expression::AbstractExpression* e, struct Statement::FunctionParameter* v);
	vector <Scope*> active_scope_list;
	Scope* active_scope;
	map<string, SymbolTableEntry*>::iterator find_in_symtab(string id);
	//struct stmt * load_func_into_symbol_table( char * & name,  struct FunctionParameter* & v_list, DataType int_type);
	bool skip_func_type_check(const char * fname);
	//void	add_func_params_to_cmpd_sc(struct Scope * & scope_, struct FunctionParameter * & v_list, string & fname);
	int search_for_func(string& search_for);
	int check_func_decl_with_func_defn(struct FunctionParameter*& v_list, int & index, string func_name);
	struct Statement::AbstractStatement* make_func_defn_stmt( struct Scope *& scope_,
		struct FunctionParameter * & v_list,
		struct Statement::AbstractStatement* & funcBody_,
		string search_for,
		DataType returnType_
		);
	struct Statement::AbstractStatement * tree_root=0;
	bool 	void_check( DataType & type1, DataType & type2, DataType& result_type);
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);

	int flag_cmpd_stmt_is_a_func_body=-1;
	//int lookup_func(string func_name_index);
	vector<Table::table*>	table_list;
	map <string, Table::ax*> ax_map;

	int no_count_ax_elems=0;
	int no_tot_ax_elems=0;
	int in_a_loop=0;
	int nest_lev=0;
	int rec_len;
	bool flag_next_stmt_start_of_block=false;
	//struct AbstractStatement* start_of_blk=0;
	vector <Statement::AbstractStatement*> blk_heads;
	using Table::stub;
	vector <stub*> stub_list;
	vector<bool> blk_start_flag;
        vector <string> attribute_list;
	vector <Statement::named_attribute_list> named_attributes_list;

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
	using std::cout;
	using std::cerr;
	using std::endl;



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
#line 116 "type.y"
{
	double dval;
	int ival ;
	struct symtab *symbolTableEntry_;
	char * name;
	struct Expression::AbstractExpression * expr;
	struct Statement::AbstractStatement * stmt;
	struct Statement::CompoundStatement * c_stmt;
	int column_no;
	int code_list;
	char text_buf[MY_STR_MAX];
	struct Statement::FunctionParameter * v_list;
	DataType dt;
	struct Table::ax * ax;
	struct Table::stub * stub;
	struct Table::table * tbl;
	Table::AbstractPrintableAxisStatement * print_stmt;
	Table::AbstractCountableAxisStatement * count_stmt;
}
/* Line 187 of yacc.c.  */
#line 300 "type.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 313 "type.c"

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
#define YYLAST   907

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNRULES -- Number of states.  */
#define YYNSTATES  270

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
       2,     2,     2,     2,     2,     2,     2,    60,    64,     2,
      27,    28,    58,    57,    47,    56,     2,    59,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    65,     5,
      52,    29,    53,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    25,     2,    26,     2,     2,     2,     2,     2,     2,
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
      18,    19,    20,    21,    22,    23,    24,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    48,    49,    50,    51,    54,    55,
      61,    62,    63
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,    15,    20,    25,    27,    30,    32,
      34,    36,    38,    40,    42,    44,    46,    47,    55,    59,
      65,    72,    78,    80,    87,    89,    93,    96,   102,   106,
     107,   109,   112,   114,   115,   126,   128,   131,   133,   135,
     137,   140,   143,   145,   148,   153,   161,   171,   177,   185,
     198,   202,   204,   206,   210,   214,   218,   222,   226,   230,
     233,   237,   241,   245,   249,   253,   257,   261,   265,   269,
     272,   274,   276,   278,   283,   290,   295,   297,   301,   307,
     309,   313,   317,   319,   321,   324,   329,   337,   340,   342,
     345,   351,   360,   363,   364,   371,   374,   378,   380,   383,
     388,   390,   393,   398,   400,   403,   408,   416,   424,   426,
     436
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      67,     0,    -1,    -1,    40,     5,    41,    29,    19,     5,
      68,    39,    69,    42,    -1,    37,     7,    92,     9,    -1,
      38,     7,    90,     9,    -1,    70,    -1,    69,    70,    -1,
      74,    -1,    72,    -1,    30,    -1,    31,    -1,    32,    -1,
      33,    -1,    34,    -1,    35,    -1,    -1,    71,    16,    27,
      76,    28,    73,    84,    -1,    71,    16,     5,    -1,    71,
      16,    29,    87,     5,    -1,    71,    16,    25,    19,    26,
       5,    -1,    17,    16,    29,    88,     5,    -1,    75,    -1,
      71,    16,    27,    76,    28,     5,    -1,    77,    -1,    76,
      47,    77,    -1,    71,    16,    -1,    71,    16,    25,    19,
      26,    -1,    71,    64,    16,    -1,    -1,    79,    -1,    78,
      79,    -1,    94,    -1,    -1,    12,    27,    87,     5,    87,
       5,    87,    28,    80,    79,    -1,    82,    -1,    87,     5,
      -1,    84,    -1,    74,    -1,    81,    -1,    46,     5,    -1,
      45,     5,    -1,    83,    -1,     1,     5,    -1,    21,    16,
      15,     5,    -1,    21,    16,    25,    87,    26,    15,     5,
      -1,    21,    16,    25,    87,    47,    87,    26,    15,     5,
      -1,    22,    27,    87,    28,    79,    -1,    22,    27,    87,
      28,    79,    23,    79,    -1,    13,    16,    29,    16,    27,
      87,    47,    87,    28,    65,    19,     5,    -1,    85,    78,
       9,    -1,     7,    -1,    87,    -1,    86,    47,    87,    -1,
      87,    57,    87,    -1,    87,    56,    87,    -1,    87,    58,
      87,    -1,    87,    59,    87,    -1,    87,    60,    87,    -1,
      56,    87,    -1,    87,    52,    87,    -1,    87,    53,    87,
      -1,    87,    55,    87,    -1,    87,    54,    87,    -1,    87,
      51,    87,    -1,    87,    50,    87,    -1,    87,    48,    87,
      -1,    87,    49,    87,    -1,    87,    29,    87,    -1,    61,
      87,    -1,    19,    -1,    18,    -1,    16,    -1,    16,    25,
      87,    26,    -1,    16,    25,    87,    47,    87,    26,    -1,
      16,    27,    86,    28,    -1,    15,    -1,    27,    87,    28,
      -1,    87,    24,    27,    88,    28,    -1,    89,    -1,    88,
      47,    89,    -1,    19,    56,    19,    -1,    19,    -1,    91,
      -1,    90,    91,    -1,    43,    16,    16,     5,    -1,    43,
      16,    16,     5,    44,    87,     5,    -1,     1,     5,    -1,
      93,    -1,    92,    93,    -1,     6,    16,     5,    99,   101,
      -1,     6,    16,     5,    44,    87,     5,    99,   101,    -1,
       1,     5,    -1,    -1,    36,    16,    29,    95,    96,     5,
      -1,    15,     5,    -1,    96,    15,     5,    -1,    98,    -1,
      97,    98,    -1,    15,    29,    19,     5,    -1,   100,    -1,
      99,   100,    -1,    10,     5,    15,     5,    -1,   102,    -1,
     101,   102,    -1,     4,     5,    15,     5,    -1,     4,     5,
      15,     5,    44,    87,     5,    -1,     8,     5,    15,     5,
      44,    87,     5,    -1,   103,    -1,    11,     5,    15,     5,
      87,     5,    44,    87,     5,    -1,    14,    16,     5,    97,
       5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   232,   232,   231,   243,   246,   251,   254,   259,   262,
     267,   268,   269,   270,   271,   272,   277,   277,   312,   316,
     320,   334,   338,   344,   356,   360,   367,   374,   383,   392,
     397,   407,   410,   415,   415,   419,   420,   433,   436,   439,
     440,   446,   452,   453,   464,   471,   478,   487,   493,   501,
     513,   547,   571,   572,   577,   583,   589,   595,   601,   607,
     613,   619,   625,   631,   637,   643,   649,   655,   661,   667,
     673,   680,   686,   692,   699,   706,   745,   751,   757,   770,
     771,   774,   783,   788,   793,   801,   809,   817,   824,   826,
     830,   846,   858,   867,   867,   891,   895,   901,   902,   907,
     916,   917,   922,   931,   934,   939,   948,   957,   966,   967,
     976
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONVERT", "TOT", "';'", "AX", "'{'",
  "CNT", "'}'", "TTL", "INC", "FOR", "FLD", "BIT", "TEXT", "NAME",
  "DEFINELIST", "FNUMBER", "INUMBER", "CODELIST", "LISTA", "IF", "ELSE",
  "IN", "'['", "']'", "'('", "')'", "'='", "VOID_T", "INT8_T", "INT16_T",
  "INT32_T", "FLOAT_T", "DOUBLE_T", "ATTRIBUTE_LIST", "AXSTART",
  "TABSTART", "ED_START", "DATA_STRUCT", "REC_LEN", "ED_END", "TAB",
  "COND_START", "CONTINUE", "BREAK", "','", "LOGOR", "LOGAND", "NOEQ",
  "ISEQ", "'<'", "'>'", "GEQ", "LEQ", "'-'", "'+'", "'*'", "'/'", "'%'",
  "NOT", "UMINUS", "FUNC_CALL", "'&'", "':'", "$accept", "prog", "@1",
  "top_level_item_list", "top_level_item", "xtcc_type", "func_defn", "@2",
  "decl", "func_decl", "decl_comma_list", "var_decl", "statement_list",
  "statement", "@3", "ListStatement", "if_stmt", "FieldStatement",
  "compound_stmt", "open_curly", "expr_list", "expression", "range_list",
  "range", "tab_list", "tab_defn", "ax_list", "ax_defn", "attributes",
  "@4", "text_list", "stub_list", "stub", "ttl_ax_stmt_list",
  "ttl_ax_stmt", "count_ax_stmt_list", "count_ax_stmt", "bit_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,    59,   260,   123,   261,   125,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,    91,    93,    40,    41,    61,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,    44,   294,   295,
     296,   297,    60,    62,   298,   299,    45,    43,    42,    47,
      37,   300,   301,   302,    38,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    66,    68,    67,    67,    67,    69,    69,    70,    70,
      71,    71,    71,    71,    71,    71,    73,    72,    74,    74,
      74,    74,    74,    75,    76,    76,    77,    77,    77,    77,
      78,    78,    78,    80,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    81,    81,    81,    82,    82,    83,
      84,    85,    86,    86,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    88,
      88,    89,    89,    90,    90,    91,    91,    91,    92,    92,
      93,    93,    93,    95,    94,    96,    96,    97,    97,    98,
      99,    99,   100,   101,   101,   102,   102,   102,   102,   102,
     103
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,    10,     4,     4,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     7,     3,     5,
       6,     5,     1,     6,     1,     3,     2,     5,     3,     0,
       1,     2,     1,     0,    10,     1,     2,     1,     1,     1,
       2,     2,     1,     2,     4,     7,     9,     5,     7,    12,
       3,     1,     1,     3,     3,     3,     3,     3,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       1,     1,     1,     4,     6,     4,     1,     3,     5,     1,
       3,     3,     1,     1,     2,     4,     7,     2,     1,     2,
       5,     8,     2,     0,     6,     2,     3,     1,     2,     4,
       1,     2,     4,     1,     2,     4,     7,     7,     1,     9,
       5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     1,     0,
       0,     0,    88,     0,     0,     0,    83,     0,    92,     0,
       4,    89,    87,     0,     5,    84,     0,     0,     0,     0,
       0,     0,     0,   100,    85,     2,     0,    76,    72,    71,
      70,     0,     0,     0,     0,     0,     0,     0,     0,   101,
      90,   103,   108,     0,     0,     0,     0,     0,     0,    59,
      69,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   104,     0,     0,   102,     0,     0,    52,    77,     0,
       0,    68,    66,    67,    65,    64,    60,    61,    63,    62,
      55,    54,    56,    57,    58,     0,     0,     0,     0,    86,
       0,    10,    11,    12,    13,    14,    15,     0,     6,     0,
       9,     8,    22,    73,     0,    75,     0,    91,    82,     0,
      79,   105,     0,     0,     0,     0,    97,     0,     3,     7,
       0,     0,    53,     0,    78,     0,     0,     0,     0,     0,
     110,    98,     0,    18,     0,    29,     0,    74,    81,    80,
       0,     0,     0,     0,     0,     0,     0,     0,    24,     0,
     106,   107,     0,    99,    21,     0,    26,     0,    16,    29,
      19,     0,    20,     0,    28,    23,     0,    25,   109,     0,
      51,    17,     0,    27,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    38,     0,    30,    39,    35,    42,    37,
       0,    32,    43,     0,     0,     0,     0,     0,    41,    40,
       0,    50,    31,    36,     0,     0,     0,     0,     0,    93,
      29,     0,     0,    44,     0,     0,     0,     0,     0,     0,
       0,     0,    47,     0,     0,     0,     0,     0,     0,     0,
       0,    95,    94,     0,     0,     0,    45,     0,    48,    96,
      33,     0,     0,     0,     0,    46,    34,     0,     0,    49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,    54,   117,   118,   202,   120,   186,   203,   122,
     167,   168,   204,   205,   263,   206,   207,   208,   209,   192,
      86,   210,   129,   130,    15,    16,    11,    12,   211,   236,
     244,   135,   136,    32,    33,    50,    51,    52
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -190
static const yytype_int16 yypact[] =
{
     102,    23,    46,     4,    54,   105,     6,    27,  -190,    65,
      60,   121,  -190,    78,    83,     5,  -190,    76,  -190,   103,
    -190,  -190,  -190,    97,  -190,  -190,   100,     8,   107,   115,
     131,     1,    93,  -190,    82,  -190,   129,  -190,     2,  -190,
    -190,     1,     1,     1,   258,   140,   152,   154,   147,  -190,
     110,  -190,  -190,     1,   125,   160,     1,     1,   635,  -190,
    -190,   163,   148,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,   159,   161,   164,
     173,  -190,   271,   136,  -190,   584,   -24,   799,  -190,    93,
     162,   799,   836,   847,   134,   134,     7,     7,     7,     7,
      96,    96,  -190,  -190,  -190,   175,   178,   179,   180,  -190,
     181,  -190,  -190,  -190,  -190,  -190,  -190,    56,  -190,   182,
    -190,  -190,  -190,  -190,     1,  -190,     1,   110,   143,   -23,
    -190,   157,   158,     1,   174,    64,  -190,   177,  -190,  -190,
      55,   648,   799,   185,  -190,   162,     1,     1,   327,   188,
    -190,  -190,   162,  -190,   190,   259,     1,  -190,  -190,  -190,
     340,   396,   168,   209,     3,   192,   -13,    28,  -190,   409,
    -190,  -190,     1,  -190,  -190,   222,   203,   213,   225,   259,
    -190,   465,  -190,   214,  -190,  -190,   233,  -190,  -190,   206,
    -190,  -190,   116,  -190,   237,   216,   228,   229,   219,   232,
     246,   249,   248,  -190,   204,  -190,  -190,  -190,  -190,  -190,
     478,  -190,  -190,     1,   239,    85,     1,   250,  -190,  -190,
      67,  -190,  -190,  -190,   534,   253,   261,     1,   685,  -190,
     259,     1,   251,  -190,   598,   240,   262,    30,   547,     1,
     265,     1,   260,   276,    66,   225,     1,   699,   279,   736,
     240,  -190,  -190,   283,   749,     1,  -190,   282,  -190,  -190,
    -190,   786,   293,   240,   234,  -190,  -190,   284,   297,  -190
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -190,  -190,  -190,  -190,   187,   -70,  -190,  -190,   -62,  -190,
      75,   155,  -190,  -189,  -190,  -190,  -190,  -190,   149,  -190,
    -190,   -31,   184,   193,  -190,   318,  -190,   326,  -190,  -190,
    -190,  -190,   205,   278,   -30,   252,   -49,  -190
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      44,    81,    49,   176,   125,   144,    13,    13,   174,     7,
      58,    59,    60,   119,    24,   222,    37,    38,    30,    39,
      40,   121,    82,   126,   145,    85,    87,    56,    41,    57,
       5,    62,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   242,   119,    14,    14,
     145,   177,    31,     6,     8,   121,   178,    42,   245,    49,
     153,   258,    43,    72,    73,    74,    75,    76,    17,   150,
      18,   252,   153,   110,   266,   179,    19,   179,    81,   134,
     154,   253,   155,    22,   156,   166,   111,   112,   113,   114,
     115,   116,   154,   141,   230,   142,   156,    45,   138,    23,
     226,    46,   148,    30,    47,    26,     9,    48,    27,   166,
     227,    10,    34,    28,    45,   160,   161,   194,    46,    29,
      35,    47,     9,   190,    48,   169,    53,    10,   195,   196,
      20,    37,    38,   110,    39,    40,    36,   197,   198,     1,
       2,   181,     3,    41,    55,    77,   111,   112,   113,   114,
     115,   116,   199,   110,    74,    75,    76,    78,    62,    79,
     166,   200,   201,    80,    83,    84,   111,   112,   113,   114,
     115,   116,    42,    30,   105,    90,   106,    43,   108,   107,
     131,   128,   224,   132,   133,   228,    68,    69,    70,    71,
      72,    73,    74,    75,    76,   134,   234,   137,   140,   143,
     238,   146,   147,   149,   158,   194,   152,   163,   247,   165,
     249,   190,   172,   221,   173,   254,   195,   196,   175,    37,
      38,   110,    39,    40,   261,   197,   198,   182,   183,   184,
     185,    41,   193,   189,   111,   112,   113,   114,   115,   116,
     190,   194,   212,   213,   214,   215,   216,   190,   217,   200,
     201,   218,   195,   196,   219,    37,    38,   110,    39,    40,
      42,   197,   198,    61,   220,    43,   233,    41,   225,   232,
     111,   112,   113,   114,   115,   116,   109,   243,   239,   229,
     248,   251,    62,   250,   256,   200,   201,    63,   259,   111,
     112,   113,   114,   115,   116,    62,    42,   262,   265,   267,
      63,    43,   269,   268,   139,   237,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,   162,    25,   187,   191,   164,    21,   159,    89,
     151,   127,     0,     0,     0,   170,     0,     0,     0,     0,
       0,    62,     0,     0,     0,     0,    63,     0,     0,     0,
       0,     0,     0,     0,    62,     0,     0,     0,     0,    63,
       0,     0,     0,     0,     0,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,   171,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,     0,     0,     0,     0,     0,
      62,     0,     0,     0,     0,    63,     0,     0,     0,     0,
       0,     0,     0,    62,     0,     0,     0,     0,    63,     0,
       0,     0,     0,     0,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
     188,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   223,     0,     0,     0,     0,     0,    62,
       0,     0,     0,     0,    63,     0,     0,     0,     0,     0,
       0,     0,    62,     0,     0,     0,     0,    63,     0,     0,
       0,     0,     0,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,   231,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   246,     0,     0,     0,     0,     0,    62,     0,
       0,     0,     0,    63,     0,     0,     0,     0,     0,     0,
       0,    62,     0,     0,     0,     0,    63,     0,     0,     0,
       0,     0,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    62,     0,
     123,     0,     0,    63,     0,     0,     0,     0,     0,     0,
       0,     0,    62,     0,   240,     0,     0,    63,     0,     0,
       0,   124,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,   241,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    62,
       0,     0,     0,    88,    63,     0,     0,     0,     0,     0,
       0,     0,    62,     0,   157,     0,     0,    63,     0,     0,
       0,     0,     0,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    62,
       0,     0,     0,   235,    63,     0,     0,     0,     0,     0,
       0,     0,     0,    62,     0,     0,     0,     0,    63,     0,
       0,     0,     0,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,   255,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      62,     0,   257,     0,     0,    63,     0,     0,     0,     0,
       0,     0,     0,    62,     0,     0,     0,   260,    63,     0,
       0,     0,     0,     0,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      62,     0,     0,     0,   264,    63,     0,     0,     0,     0,
       0,     0,     0,    62,     0,     0,     0,     0,    63,     0,
       0,     0,     0,     0,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    62,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76
};

static const yytype_int16 yycheck[] =
{
      31,    50,    32,    16,    28,    28,     1,     1,     5,     5,
      41,    42,    43,    83,     9,   204,    15,    16,    10,    18,
      19,    83,    53,    47,    47,    56,    57,    25,    27,    27,
       7,    24,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,   235,   117,    43,    43,
      47,    64,    44,     7,     0,   117,    28,    56,    28,    89,
       5,   250,    61,    56,    57,    58,    59,    60,    41,     5,
       5,     5,     5,    17,   263,    47,    16,    47,   127,    15,
      25,    15,    27,     5,    29,   155,    30,    31,    32,    33,
      34,    35,    25,   124,    27,   126,    29,     4,    42,    16,
      15,     8,   133,    10,    11,    29,     1,    14,     5,   179,
      25,     6,     5,    16,     4,   146,   147,     1,     8,    19,
       5,    11,     1,     7,    14,   156,    44,     6,    12,    13,
       9,    15,    16,    17,    18,    19,     5,    21,    22,    37,
      38,   172,    40,    27,    15,     5,    30,    31,    32,    33,
      34,    35,    36,    17,    58,    59,    60,     5,    24,     5,
     230,    45,    46,    16,    39,     5,    30,    31,    32,    33,
      34,    35,    56,    10,    15,    27,    15,    61,     5,    15,
       5,    19,   213,     5,     5,   216,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    15,   227,    16,    16,    56,
     231,    44,    44,    29,    19,     1,    29,    19,   239,    19,
     241,     7,    44,     9,     5,   246,    12,    13,    26,    15,
      16,    17,    18,    19,   255,    21,    22,     5,    25,    16,
       5,    27,    26,    19,    30,    31,    32,    33,    34,    35,
       7,     1,     5,    27,    16,    16,    27,     7,    16,    45,
      46,     5,    12,    13,     5,    15,    16,    17,    18,    19,
      56,    21,    22,     5,    16,    61,     5,    27,    29,    16,
      30,    31,    32,    33,    34,    35,     5,    15,    27,    29,
      15,     5,    24,    23,     5,    45,    46,    29,     5,    30,
      31,    32,    33,    34,    35,    24,    56,    15,     5,    65,
      29,    61,     5,    19,   117,   230,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     5,    15,   179,   186,   152,    11,   145,    61,
     135,    89,    -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,     5,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     5,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    24,    -1,
      26,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    26,    -1,    -1,    29,    -1,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    24,
      -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    26,    -1,    -1,    29,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    24,
      -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    -1,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      24,    -1,    26,    -1,    -1,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    28,    29,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      24,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    37,    38,    40,    67,     7,     7,     5,     0,     1,
       6,    92,    93,     1,    43,    90,    91,    41,     5,    16,
       9,    93,     5,    16,     9,    91,    29,     5,    16,    19,
      10,    44,    99,   100,     5,     5,     5,    15,    16,    18,
      19,    27,    56,    61,    87,     4,     8,    11,    14,   100,
     101,   102,   103,    44,    68,    15,    25,    27,    87,    87,
      87,     5,    24,    29,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,     5,     5,     5,
      16,   102,    87,    39,     5,    87,    86,    87,    28,    99,
      27,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    15,    15,    15,     5,     5,
      17,    30,    31,    32,    33,    34,    35,    69,    70,    71,
      72,    74,    75,    26,    47,    28,    47,   101,    19,    88,
      89,     5,     5,     5,    15,    97,    98,    16,    42,    70,
      16,    87,    87,    56,    28,    47,    44,    44,    87,    29,
       5,    98,    29,     5,    25,    27,    29,    26,    19,    89,
      87,    87,     5,    19,    88,    19,    71,    76,    77,    87,
       5,     5,    44,     5,     5,    26,    16,    64,    28,    47,
       5,    87,     5,    25,    16,     5,    73,    77,     5,    19,
       7,    84,    85,    26,     1,    12,    13,    21,    22,    36,
      45,    46,    71,    74,    78,    79,    81,    82,    83,    84,
      87,    94,     5,    27,    16,    16,    27,    16,     5,     5,
      16,     9,    79,     5,    87,    29,    15,    25,    87,    29,
      27,     5,    16,     5,    87,    28,    95,    76,    87,    27,
      26,    47,    79,    15,    96,    28,     5,    87,    15,    87,
      23,     5,     5,    15,    87,    47,     5,    26,    79,     5,
      28,    87,    15,    80,    28,     5,    79,    65,    19,     5
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
#line 232 "type.y"
    {	const char * c_arr="c";  
		rec_len=(yyvsp[(5) - (6)].ival); 
		active_scope->insert(c_arr, INT8_ARR_TYPE, rec_len, 0);
	}
    break;

  case 3:
#line 236 "type.y"
    {
		tree_root = trav_chain((yyvsp[(9) - (10)].stmt));
		if(tree_root==0){
			cerr << "tree_root =0 : core dump expected" << endl;
		}
		return 0;
	}
    break;

  case 4:
#line 243 "type.y"
    {
		return 0;
	}
    break;

  case 5:
#line 246 "type.y"
    {
		return 0;
	}
    break;

  case 6:
#line 251 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 7:
#line 254 "type.y"
    {
		(yyval.stmt)=link_chain((yyvsp[(1) - (2)].stmt),(yyvsp[(2) - (2)].stmt));
	}
    break;

  case 8:
#line 259 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 9:
#line 262 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 16:
#line 277 "type.y"
    {
		string func_name_index((yyvsp[(2) - (5)].name));
		flag_cmpd_stmt_is_a_func_body=Util::lookup_func(func_name_index);
		if(flag_cmpd_stmt_is_a_func_body==-1){
			++ no_errors;
			cerr << "Function name not found in list of declared functions: "
				<< "You will see another error on this same function name: " << func_name_index
				<< "line_no: " << line_no  << endl;
		}
	}
    break;

  case 17:
#line 286 "type.y"
    {
		struct Statement::CompoundStatement* c_stmt= (yyvsp[(7) - (7)].c_stmt);
		if(c_stmt==0){
			cerr << "INTERNAL COMPILER ERROR: c_stmt==0" << endl;
		} else {
			//cout << "funcBody_: is valid " << endl;
		}
		struct Scope *scope_=c_stmt->scope_;
		struct Statement::FunctionParameter * v_list=trav_chain((yyvsp[(4) - (7)].v_list));
		struct Statement::AbstractStatement* funcBody_=(yyvsp[(7) - (7)].c_stmt);
		string search_for=(yyvsp[(2) - (7)].name);
		DataType returnType_=(yyvsp[(1) - (7)].dt);
		(yyval.stmt)=new Statement::FunctionStatement(FUNC_DEFN, line_no, scope_, v_list, funcBody_, search_for, returnType_);
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
#line 312 "type.y"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (3)].name), (yyvsp[(1) - (3)].dt)/*, line_no*/);
		free((yyvsp[(2) - (3)].name));
	}
    break;

  case 19:
#line 316 "type.y"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (5)].name), (yyvsp[(1) - (5)].dt), (yyvsp[(4) - (5)].expr));

	}
    break;

  case 20:
#line 320 "type.y"
    {
		/* NxD: I have ordered the types in DataType so that this hack is possible I hope */
		DataType dt=DataType(INT8_ARR_TYPE+((yyvsp[(1) - (6)].dt)-INT8_TYPE));
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (6)].name), dt, (yyvsp[(4) - (6)].ival)/*, line_no*/);
		free((yyvsp[(2) - (6)].name));
	}
    break;

  case 21:
#line 334 "type.y"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (5)].name), RANGE_DECL_STMT, &xs);
		//$$ = new decl_stmt($2, RANGE_DECL_STMT, &xs );
	}
    break;

  case 22:
#line 338 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 23:
#line 344 "type.y"
    {
		char *name=(yyvsp[(2) - (6)].name);
		struct Statement::FunctionParameter* v_list=trav_chain((yyvsp[(4) - (6)].v_list));
		DataType returnType_=(yyvsp[(1) - (6)].dt);
		(yyval.stmt)=new Statement::FunctionDeclarationStatement( FUNC_TYPE, line_no, name,  v_list, returnType_);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 24:
#line 356 "type.y"
    {
		 (yyval.v_list)=(yyvsp[(1) - (1)].v_list);
		 //cout << "got decl_comma_list : " << endl;
	}
    break;

  case 25:
#line 360 "type.y"
    {
		(yyval.v_list)=link_chain((yyvsp[(1) - (3)].v_list),(yyvsp[(3) - (3)].v_list));
		//cout << "chaining var_decl : " << endl;
	}
    break;

  case 26:
#line 367 "type.y"
    {
		(yyval.v_list)=new Statement::FunctionParameter((yyvsp[(1) - (2)].dt), (yyvsp[(2) - (2)].name));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (2)].name));
	}
    break;

  case 27:
#line 374 "type.y"
    {
		/* Neil - I need to fix this */
		DataType dt=DataType(INT8_ARR_TYPE+((yyvsp[(1) - (5)].dt)-INT8_TYPE));
		(yyval.v_list)=new Statement::FunctionParameter(dt, (yyvsp[(2) - (5)].name), (yyvsp[(4) - (5)].ival));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (5)].name));
	}
    break;

  case 28:
#line 383 "type.y"
    {
		DataType dt=DataType(INT8_REF_TYPE+((yyvsp[(1) - (3)].dt)-INT8_TYPE));
		(yyval.v_list)=new Statement::FunctionParameter(dt, (yyvsp[(3) - (3)].name));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(3) - (3)].name));
	}
    break;

  case 29:
#line 392 "type.y"
    {
		(yyval.v_list)=0;
		}
    break;

  case 30:
#line 397 "type.y"
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
#line 407 "type.y"
    {
		(yyval.stmt)=link_chain((yyvsp[(1) - (2)].stmt),(yyvsp[(2) - (2)].stmt));
	}
    break;

  case 32:
#line 410 "type.y"
    {
		(yyval.stmt)=0;
	}
    break;

  case 33:
#line 415 "type.y"
    { ++in_a_loop;}
    break;

  case 34:
#line 415 "type.y"
    {
		(yyval.stmt) = new struct Statement::ForStatement(FOR_STMT, line_no, (yyvsp[(3) - (10)].expr), (yyvsp[(5) - (10)].expr), (yyvsp[(7) - (10)].expr), (yyvsp[(10) - (10)].stmt));
		--in_a_loop;
	}
    break;

  case 36:
#line 420 "type.y"
    { 
		if((yyvsp[(1) - (2)].expr)->isvalid()){
			(yyval.stmt) = new Statement::ExpressionStatement(TEXPR_STMT, line_no, (yyvsp[(1) - (2)].expr));
			if(XTCC_DEBUG_MEM_USAGE){
				mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
			}
		} else {
			(yyval.stmt) = new Statement::ExpressionStatement(ERROR_TYPE, line_no, (yyvsp[(1) - (2)].expr));
			if(XTCC_DEBUG_MEM_USAGE){
				mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
			}
		}
	}
    break;

  case 37:
#line 433 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].c_stmt);
	}
    break;

  case 38:
#line 436 "type.y"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 40:
#line 440 "type.y"
    {
		(yyval.stmt)=new Statement::BreakStatement(BREAK_STMT, line_no, in_a_loop);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 41:
#line 446 "type.y"
    {
		(yyval.stmt)=new Statement::ContinueStatement(CONTINUE_STMT, line_no, in_a_loop);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 43:
#line 453 "type.y"
    {
		Util::print_err(Util::compiler_sem_err, "statement missing ';' around line_no: ", 
			line_no, __LINE__, __FILE__);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		(yyval.stmt) = new struct Statement::ErrorStatement(line_no);
		yyerrok;
	}
    break;

  case 44:
#line 464 "type.y"
    {
		(yyval.stmt)=new Statement::ListStatement(LISTA_BASIC_TYPE_STMT, (yyvsp[(2) - (4)].name), (yyvsp[(3) - (4)].text_buf));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (4)].name));
	}
    break;

  case 45:
#line 471 "type.y"
    {
		(yyval.stmt)=new Statement::ListStatement( LISTA_BASIC_ARRTYPE_STMT_1INDEX, (yyvsp[(2) - (7)].name), string((yyvsp[(6) - (7)].text_buf)), (yyvsp[(4) - (7)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (7)].name));
	}
    break;

  case 46:
#line 478 "type.y"
    {
		(yyval.stmt)=new Statement::ListStatement( LISTA_BASIC_ARRTYPE_STMT_1INDEX, (yyvsp[(2) - (9)].name), string((yyvsp[(8) - (9)].text_buf)), (yyvsp[(4) - (9)].expr), (yyvsp[(6) - (9)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (9)].name));	
	}
    break;

  case 47:
#line 487 "type.y"
    {
		(yyval.stmt)=new Statement::IfStatement(IFE_STMT,if_line_no,(yyvsp[(3) - (5)].expr),(yyvsp[(5) - (5)].stmt),0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 48:
#line 493 "type.y"
    {
		(yyval.stmt)=new Statement::IfStatement(IFE_STMT, if_line_no,(yyvsp[(3) - (7)].expr),(yyvsp[(5) - (7)].stmt),(yyvsp[(7) - (7)].stmt));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 49:
#line 501 "type.y"
    {
		Expression::AbstractExpression* start_col=(yyvsp[(6) - (12)].expr);
		Expression::AbstractExpression* end_col=(yyvsp[(8) - (12)].expr);
		int width=(yyvsp[(11) - (12)].ival);
		(yyval.stmt) = new Statement::FieldStatement((yyvsp[(2) - (12)].name), (yyvsp[(4) - (12)].name), start_col, end_col, width);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (12)].name)), free((yyvsp[(4) - (12)].name));
	}
    break;

  case 50:
#line 513 "type.y"
    {
		active_scope_list.pop_back();
		int tmp=active_scope_list.size()-1;
		if(tmp==-1) { 
			active_scope = 0;
			cerr << "Error: active_scope = NULL: should not happen: line_no:" << line_no
				<< endl;
			++no_errors;
			(yyval.c_stmt)=new struct Statement::CompoundStatement(ERROR_TYPE, line_no, 0);
			void *ptr=(yyval.c_stmt);
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		} else { active_scope = active_scope_list[tmp]; }
		struct Statement::AbstractStatement* head_of_this_chain=blk_heads.back();
		if(blk_start_flag.size() > 0){
			flag_next_stmt_start_of_block = blk_start_flag[blk_start_flag.size()-1];
		}
		if(  head_of_this_chain==0){
			cerr << "Error in compiler : compoundBody_:  " << __FILE__ << __LINE__ << endl;
			++no_errors;
		} else {
			(yyvsp[(1) - (3)].c_stmt)->compoundBody_ = head_of_this_chain;
			blk_heads.pop_back();
		}
		
		(yyval.c_stmt)=(yyvsp[(1) - (3)].c_stmt);
	}
    break;

  case 51:
#line 547 "type.y"
    {
		++nest_lev;
		(yyval.c_stmt) = new Statement::CompoundStatement(CMPD_STMT, line_no, flag_cmpd_stmt_is_a_func_body);
		void *ptr=(yyval.c_stmt);
		mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
		mem_addr.push_back(m1);
		if(flag_cmpd_stmt_is_a_func_body>=0){
			(yyval.c_stmt)->scope_=func_info_table[flag_cmpd_stmt_is_a_func_body]->funcScope_;
			// reset the flag
			flag_cmpd_stmt_is_a_func_body=-1;
		} else {
			(yyval.c_stmt)->scope_= new Scope();
			void *ptr=(yyval.c_stmt);
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		}
		flag_next_stmt_start_of_block=true;
		blk_start_flag.push_back(flag_next_stmt_start_of_block);
		active_scope_list.push_back((yyval.c_stmt)->scope_);
		active_scope = (yyval.c_stmt)->scope_;
	}
    break;

  case 52:
#line 571 "type.y"
    { (yyval.expr)=(yyvsp[(1) - (1)].expr); }
    break;

  case 53:
#line 572 "type.y"
    {
		(yyval.expr)=link_chain((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));
	}
    break;

  case 54:
#line 577 "type.y"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_plus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 55:
#line 583 "type.y"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_minus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 56:
#line 589 "type.y"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_mult);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 57:
#line 595 "type.y"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_div);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 58:
#line 601 "type.y"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_mod);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 59:
#line 607 "type.y"
    {
		(yyval.expr) = new Expression::UnaryExpression((yyvsp[(2) - (2)].expr), Expression::oper_umin);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 60:
#line 613 "type.y"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_lt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 61:
#line 619 "type.y"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_gt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 62:
#line 625 "type.y"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_le);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 63:
#line 631 "type.y"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_ge);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 64:
#line 637 "type.y"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_iseq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 65:
#line 643 "type.y"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_isneq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 66:
#line 649 "type.y"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_or);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 67:
#line 655 "type.y"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_and);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 68:
#line 661 "type.y"
    {
		(yyval.expr) = new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_assgn);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 69:
#line 667 "type.y"
    {
		(yyval.expr) = new Expression::UnaryExpression((yyvsp[(2) - (2)].expr), Expression::oper_not);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 70:
#line 673 "type.y"
    {
		(yyval.expr) = new Expression::Unary2Expression((yyvsp[(1) - (1)].ival));
		//cout << "got INUMBER: " << $1 << " type : " << $$->type << endl;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 71:
#line 680 "type.y"
    {
		(yyval.expr) = new Expression::Unary2Expression((yyvsp[(1) - (1)].dval));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 72:
#line 686 "type.y"
    {
		(yyval.expr) = new Expression::Unary2Expression((yyvsp[(1) - (1)].name), Expression::oper_name );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 73:
#line 692 "type.y"
    {
		(yyval.expr) = new Expression::Unary2Expression (Expression::oper_arrderef, /*nametype,  se,*/ (yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(1) - (4)].name));
	}
    break;

  case 74:
#line 699 "type.y"
    {
		(yyval.expr) = new Expression::Unary2Expression(Expression::oper_blk_arr_assgn, (yyvsp[(1) - (6)].name),(yyvsp[(3) - (6)].expr),(yyvsp[(5) - (6)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(1) - (6)].name));
	}
    break;

  case 75:
#line 706 "type.y"
    {
		//cout << "parsing Function call: name: " << $1 << endl;
		string search_for=(yyvsp[(1) - (4)].name);
		bool found=false;
		int index=Util::search_for_func(search_for);
		if(index!=-1) found=true;
		bool skip_type_check=Util::skip_func_type_check(search_for.c_str());
		if( skip_type_check==false  && found==false ) {
			cerr << "ERROR: function call Error on line_no: " << line_no << endl;
			cerr << "function : " << search_for << " used without decl" << endl;
			++ no_errors;
			(yyval.expr)=new Expression::Unary2Expression(ERROR_TYPE);
			void *ptr=(yyval.expr);
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		} else {
			DataType my_type=func_info_table[index]->returnType_;
			Expression::AbstractExpression* e_ptr=trav_chain((yyvsp[(3) - (4)].expr));
			Statement::FunctionParameter* fparam=func_info_table[index]->paramList_;
			bool match=false;
			if(skip_type_check==false){
				match=Util::check_parameters(e_ptr, fparam);
			}
			if(match || skip_type_check){
				//$$=new Unary2Expression(oper_func_call, my_type, $3, index, line_no);
				(yyval.expr)=new Expression::Unary2Expression(Expression::oper_func_call, my_type, e_ptr, index, line_no);
				void *ptr=(yyval.expr);
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);

			} else {
				(yyval.expr)=new Expression::Unary2Expression(ERROR_TYPE);
				void *ptr=(yyval.expr);
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);
			}
		}
		free((yyvsp[(1) - (4)].name));
	}
    break;

  case 76:
#line 745 "type.y"
    {
		(yyval.expr) = new Expression::Unary2Expression(strdup((yyvsp[(1) - (1)].text_buf)), Expression::oper_text_expr);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 77:
#line 751 "type.y"
    { 
		(yyval.expr) = new Expression::UnaryExpression((yyvsp[(2) - (3)].expr), Expression::oper_parexp );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 78:
#line 757 "type.y"
    {
		(yyval.expr) = new Expression::Binary2Expression((yyvsp[(1) - (5)].expr), xs, Expression::oper_in);
	}
    break;

  case 81:
#line 774 "type.y"
    {
		if((yyvsp[(3) - (3)].ival)<=(yyvsp[(1) - (3)].ival)){
			print_err(Util::compiler_sem_err, "2nd number in range <= 1st number",
					line_no, __LINE__, __FILE__  );

		} else {
			xs.range.push_back( pair<int,int>((yyvsp[(1) - (3)].ival),(yyvsp[(3) - (3)].ival)));
		}
	}
    break;

  case 82:
#line 783 "type.y"
    {
		xs.indiv.insert((yyvsp[(1) - (1)].ival));
	}
    break;

  case 83:
#line 788 "type.y"
    { 
#ifdef DEBUG_GRAM
	printf("got table defn\n"); 
#endif
	}
    break;

  case 84:
#line 793 "type.y"
    { 
#ifdef DEBUG_GRAM
		printf("recursive tab_defn\n"); 
#endif
	}
    break;

  case 85:
#line 801 "type.y"
    {
		(yyval.tbl)=new Table::table((yyvsp[(2) - (4)].name),(yyvsp[(3) - (4)].name), line_no);
		table_list.push_back((yyval.tbl));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.tbl), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (4)].name)); free((yyvsp[(3) - (4)].name));
	}
    break;

  case 86:
#line 809 "type.y"
    {
		(yyval.tbl)=new Table::table((yyvsp[(2) - (7)].name),(yyvsp[(3) - (7)].name), line_no, (yyvsp[(6) - (7)].expr));
		table_list.push_back((yyval.tbl));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.tbl), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (7)].name)); free((yyvsp[(3) - (7)].name));
	}
    break;

  case 87:
#line 817 "type.y"
    {
		cerr << "Error in tab section line: " <<
			line_no << endl;
		++no_errors;
	}
    break;

  case 88:
#line 824 "type.y"
    {
	}
    break;

  case 89:
#line 826 "type.y"
    {
	}
    break;

  case 90:
#line 830 "type.y"
    {
		using Table::AbstractPrintableAxisStatement;
		using Table::AbstractCountableAxisStatement;
		Table::AbstractPrintableAxisStatement  * ttl_stmt_ptr= trav_chain((yyvsp[(4) - (5)].print_stmt));
		Table::AbstractCountableAxisStatement * count_stmt_ptr= trav_chain((yyvsp[(5) - (5)].count_stmt));

		(yyval.ax) = new Table::ax(ttl_stmt_ptr, count_stmt_ptr, no_count_ax_elems, no_tot_ax_elems, 0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.ax), __LINE__, __FILE__, line_no);
		}
		
		ax_map[(yyvsp[(2) - (5)].name)]=(yyval.ax);
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		free((yyvsp[(2) - (5)].name));
	}
    break;

  case 91:
#line 846 "type.y"
    {
		Table::AbstractPrintableAxisStatement * ttl_stmt_ptr= trav_chain((yyvsp[(7) - (8)].print_stmt));
		Table::AbstractCountableAxisStatement * count_stmt_ptr= trav_chain((yyvsp[(8) - (8)].count_stmt));
		(yyval.ax) = new Table::ax(ttl_stmt_ptr, count_stmt_ptr, no_count_ax_elems, no_tot_ax_elems, (yyvsp[(5) - (8)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.ax), __LINE__, __FILE__, line_no);
		}
		ax_map[(yyvsp[(2) - (8)].name)]=(yyval.ax);
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		free((yyvsp[(2) - (8)].name));
	}
    break;

  case 92:
#line 858 "type.y"
    {
		cerr << "Error in axis section line: " <<
			line_no << endl;
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		++no_errors;
	}
    break;

  case 93:
#line 867 "type.y"
    {
		attribute_list.resize(0);
		//cout << "resize attribute_list to 0\n";
	}
    break;

  case 94:
#line 870 "type.y"
    {
		//cout <<"got attribute_list size: " << attribute_list.size() << endl;
		//$$=0;
		string attr_list_name=(yyvsp[(2) - (6)].name);
		struct Statement::named_attribute_list * n_attr_stmt= new Statement::named_attribute_list(NAMED_ATTRIBUTE_TYPE,
				line_no, attr_list_name, attribute_list);
		(yyval.stmt)=n_attr_stmt;
		if(active_scope_list.size()!=1){
			Util::print_err(Util::compiler_sem_err, " named_attribute_list found on Scope level higher than 0 ", 
						line_no, __LINE__, __FILE__);
		}
		//named_attributes_list.push_back(attr_list);
		if(active_scope_list[0]->sym_tab.find((yyvsp[(2) - (6)].name)) == active_scope_list[0]->sym_tab.end()){
			string s(attr_list_name);
			SymbolTableEntry* se=new SymbolTableEntry((yyvsp[(2) - (6)].name), NAMED_ATTRIBUTE_TYPE);
			active_scope_list[0]->sym_tab[s] = se;
			n_attr_stmt->symbolTableEntry_ = se;
		}
	}
    break;

  case 95:
#line 891 "type.y"
    {
		string s1=(yyvsp[(1) - (2)].text_buf);
		attribute_list.push_back(s1);
	}
    break;

  case 96:
#line 895 "type.y"
    {
		string s1=(yyvsp[(2) - (3)].text_buf);
		attribute_list.push_back(s1);
        }
    break;

  case 98:
#line 902 "type.y"
    {
		//$$=link_chain($1, $2);
	}
    break;

  case 99:
#line 907 "type.y"
    {
		using Table::stub;
		(yyval.stub)=new stub((yyvsp[(1) - (4)].text_buf), (yyvsp[(3) - (4)].ival));
		stub_list.push_back((yyval.stub));
		++ no_count_ax_elems;
		++ no_tot_ax_elems;
	}
    break;

  case 100:
#line 916 "type.y"
    { (yyval.print_stmt)=(yyvsp[(1) - (1)].print_stmt); }
    break;

  case 101:
#line 917 "type.y"
    {
		(yyval.print_stmt)=link_chain((yyvsp[(1) - (2)].print_stmt), (yyvsp[(2) - (2)].print_stmt));
	}
    break;

  case 102:
#line 922 "type.y"
    {
		(yyval.print_stmt) = new Table::TitleStatement (Table::txt_axstmt,(yyvsp[(3) - (4)].text_buf));
		++no_tot_ax_elems;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.print_stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 103:
#line 931 "type.y"
    {
		(yyval.count_stmt) = (yyvsp[(1) - (1)].count_stmt);
	}
    break;

  case 104:
#line 934 "type.y"
    {
		(yyval.count_stmt)=link_chain((yyvsp[(1) - (2)].count_stmt), (yyvsp[(2) - (2)].count_stmt));
	}
    break;

  case 105:
#line 939 "type.y"
    {
		using Table::tot_ax_stmt;
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.count_stmt) = new tot_ax_stmt (Table::tot_axstmt,(yyvsp[(3) - (4)].text_buf), 0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.count_stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 106:
#line 948 "type.y"
    {
		using Table::tot_ax_stmt;
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.count_stmt) = new tot_ax_stmt (Table::tot_axstmt,(yyvsp[(3) - (7)].text_buf), (yyvsp[(6) - (7)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.count_stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 107:
#line 957 "type.y"
    {
		using Table::count_ax_stmt;
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.count_stmt) = new count_ax_stmt (Table::cnt_axstmt,(yyvsp[(3) - (7)].text_buf), (yyvsp[(6) - (7)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.count_stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 109:
#line 967 "type.y"
    {
		// Need to generate the correct code for the statment below
		// hack added so that we can compile
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.count_stmt) = new Table::inc_ax_stmt (Table::inc_axstmt,(yyvsp[(3) - (9)].text_buf), (yyvsp[(8) - (9)].expr), (yyvsp[(5) - (9)].expr));
	}
    break;

  case 110:
#line 976 "type.y"
    {
		using Table::fld_ax_stmt;
		//stub * stub_ptr = trav_chain($4);
	 	//$$ = new fld_ax_stmt ($2, stub_ptr);
	 	(yyval.count_stmt) = new fld_ax_stmt (Table::fld_axstmt, (yyvsp[(2) - (5)].name), stub_list);
		stub_list.resize(0);
	}
    break;


/* Line 1267 of yacc.c.  */
#line 2900 "type.c"
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


#line 985 "type.y"



template<class T> T* link_chain(T* &elem1, T* &elem2)
{
	elem2->prev_=elem1;
	elem1->next_=elem2;
	return elem2;
}

template<class T> T* trav_chain(T* & elem1){
	if(elem1){
		while (elem1->prev_) elem1=elem1->prev_;
		return elem1;
	} else return 0;
}


