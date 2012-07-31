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
#line 26 "src/type.ypp"

//#include "../../qscript/trunk/named_attributes.h"

#include <cstring>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
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

	using std::stringstream;
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
	int no_inc_ax_elems=0;
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
	vector <double> weight_vec;
	vector <Table::weight_axis_group> wt_axis_group_vec;
	vector <Table::weight_axis> wt_axis_vec;

	noun_list_type noun_list[]= {
			{	"void", VOID_TYPE},
			{	"int8_t", INT8_TYPE},
			{	"int16_t", INT16_TYPE},
			{	"int32_t", INT32_TYPE},
			{	"float", FLOAT_TYPE},
			{	"double", DOUBLE_TYPE}
		};
	vector<mem_addr_tab>  mem_addr;

	void flex_finish();
	using std::cout;
	using std::cerr;
	using std::endl;



/* Line 268 of yacc.c  */
#line 167 "src/type.cpp"

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
     CONVERT = 258,
     TOT = 259,
     AX = 260,
     CNT = 261,
     TTL = 262,
     WT = 263,
     MP = 264,
     FOR = 265,
     FLD = 266,
     BIT = 267,
     TEXT = 268,
     NAME = 269,
     DEFINELIST = 270,
     FNUMBER = 271,
     INUMBER = 272,
     CODELIST = 273,
     LISTA = 274,
     IF = 275,
     ELSE = 276,
     IN = 277,
     VOID_T = 278,
     INT8_T = 279,
     INT16_T = 280,
     INT32_T = 281,
     FLOAT_T = 282,
     DOUBLE_T = 283,
     ATTRIBUTE_LIST = 284,
     AXSTART = 285,
     TABSTART = 286,
     ED_START = 287,
     DATA_STRUCT = 288,
     REC_LEN = 289,
     ED_END = 290,
     TAB = 291,
     COND_START = 292,
     CONTINUE = 293,
     BREAK = 294,
     INC = 295,
     LOGOR = 296,
     LOGAND = 297,
     NOEQ = 298,
     ISEQ = 299,
     GEQ = 300,
     LEQ = 301,
     NOT = 302,
     UMINUS = 303,
     FUNC_CALL = 304
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 121 "src/type.ypp"

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



/* Line 293 of yacc.c  */
#line 274 "src/type.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 286 "src/type.cpp"

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
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   889

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  116
/* YYNRULES -- Number of states.  */
#define YYNSTATES  287

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    62,    66,     2,
      28,    29,    60,    59,    49,    58,     2,    61,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    67,     6,
      54,    30,    55,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    26,     2,    27,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     8,     2,     9,     2,     2,     2,     2,
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
       5,     7,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    50,    51,    52,    53,
      56,    57,    63,    64,    65
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
     345,   351,   360,   374,   379,   382,   383,   390,   393,   397,
     401,   406,   408,   411,   413,   416,   421,   423,   426,   431,
     433,   436,   441,   449,   457,   465,   467
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      69,     0,    -1,    -1,    41,     6,    42,    30,    20,     6,
      70,    40,    71,    43,    -1,    38,     8,    94,     9,    -1,
      39,     8,    92,     9,    -1,    72,    -1,    71,    72,    -1,
      76,    -1,    74,    -1,    31,    -1,    32,    -1,    33,    -1,
      34,    -1,    35,    -1,    36,    -1,    -1,    73,    17,    28,
      78,    29,    75,    86,    -1,    73,    17,     6,    -1,    73,
      17,    30,    89,     6,    -1,    73,    17,    26,    20,    27,
       6,    -1,    18,    17,    30,    90,     6,    -1,    77,    -1,
      73,    17,    28,    78,    29,     6,    -1,    79,    -1,    78,
      49,    79,    -1,    73,    17,    -1,    73,    17,    26,    20,
      27,    -1,    73,    66,    17,    -1,    -1,    81,    -1,    80,
      81,    -1,    96,    -1,    -1,    13,    28,    89,     6,    89,
       6,    89,    29,    82,    81,    -1,    84,    -1,    89,     6,
      -1,    86,    -1,    76,    -1,    83,    -1,    47,     6,    -1,
      46,     6,    -1,    85,    -1,     1,     6,    -1,    22,    17,
      16,     6,    -1,    22,    17,    26,    89,    27,    16,     6,
      -1,    22,    17,    26,    89,    49,    89,    27,    16,     6,
      -1,    23,    28,    89,    29,    81,    -1,    23,    28,    89,
      29,    81,    24,    81,    -1,    14,    17,    30,    17,    28,
      89,    49,    89,    29,    67,    20,     6,    -1,    87,    80,
       9,    -1,     8,    -1,    89,    -1,    88,    49,    89,    -1,
      89,    59,    89,    -1,    89,    58,    89,    -1,    89,    60,
      89,    -1,    89,    61,    89,    -1,    89,    62,    89,    -1,
      58,    89,    -1,    89,    54,    89,    -1,    89,    55,    89,
      -1,    89,    57,    89,    -1,    89,    56,    89,    -1,    89,
      53,    89,    -1,    89,    52,    89,    -1,    89,    50,    89,
      -1,    89,    51,    89,    -1,    89,    30,    89,    -1,    63,
      89,    -1,    20,    -1,    19,    -1,    17,    -1,    17,    26,
      89,    27,    -1,    17,    26,    89,    49,    89,    27,    -1,
      17,    28,    88,    29,    -1,    16,    -1,    28,    89,    29,
      -1,    89,    25,    28,    90,    29,    -1,    91,    -1,    90,
      49,    91,    -1,    20,    58,    20,    -1,    20,    -1,    93,
      -1,    92,    93,    -1,    44,    17,    17,     6,    -1,    44,
      17,    17,     6,    45,    89,     6,    -1,     1,     6,    -1,
      95,    -1,    94,    95,    -1,     5,    17,     6,   103,   105,
      -1,     5,    17,     6,    45,    89,     6,   103,   105,    -1,
       5,    17,     6,    45,    89,     6,    17,    12,    30,    20,
       6,   103,   105,    -1,    11,    17,     6,    99,    -1,     1,
       6,    -1,    -1,    37,    17,    30,    97,    98,     6,    -1,
      16,     6,    -1,    98,    16,     6,    -1,    17,   100,     6,
      -1,    99,    17,   100,     6,    -1,    19,    -1,   100,    19,
      -1,   102,    -1,   101,   102,    -1,    16,    30,    20,     6,
      -1,   104,    -1,   103,   104,    -1,    10,     6,    16,     6,
      -1,   106,    -1,   105,   106,    -1,     4,     6,    16,     6,
      -1,     4,     6,    16,     6,    45,    89,     6,    -1,     7,
       6,    16,     6,    45,    89,     6,    -1,    48,     6,    89,
       6,    45,    89,     6,    -1,   107,    -1,    15,    17,     6,
     101,     6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   237,   237,   236,   248,   251,   256,   259,   264,   267,
     272,   273,   274,   275,   276,   277,   282,   282,   317,   321,
     325,   339,   344,   350,   362,   366,   373,   380,   389,   398,
     403,   413,   416,   421,   421,   425,   426,   439,   442,   445,
     446,   452,   458,   459,   470,   477,   484,   493,   499,   507,
     519,   553,   577,   578,   583,   589,   595,   601,   607,   613,
     619,   625,   631,   637,   643,   649,   655,   661,   667,   673,
     679,   686,   692,   698,   705,   712,   751,   757,   763,   777,
     778,   781,   790,   795,   800,   808,   816,   824,   831,   833,
     837,   859,   883,   909,   913,   922,   922,   946,   950,   956,
     982,   989,   992,   997,   998,  1003,  1012,  1013,  1018,  1028,
    1031,  1036,  1046,  1055,  1064,  1075,  1078
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONVERT", "TOT", "AX", "';'", "CNT",
  "'{'", "'}'", "TTL", "WT", "MP", "FOR", "FLD", "BIT", "TEXT", "NAME",
  "DEFINELIST", "FNUMBER", "INUMBER", "CODELIST", "LISTA", "IF", "ELSE",
  "IN", "'['", "']'", "'('", "')'", "'='", "VOID_T", "INT8_T", "INT16_T",
  "INT32_T", "FLOAT_T", "DOUBLE_T", "ATTRIBUTE_LIST", "AXSTART",
  "TABSTART", "ED_START", "DATA_STRUCT", "REC_LEN", "ED_END", "TAB",
  "COND_START", "CONTINUE", "BREAK", "INC", "','", "LOGOR", "LOGAND",
  "NOEQ", "ISEQ", "'<'", "'>'", "GEQ", "LEQ", "'-'", "'+'", "'*'", "'/'",
  "'%'", "NOT", "UMINUS", "FUNC_CALL", "'&'", "':'", "$accept", "prog",
  "$@1", "top_level_item_list", "top_level_item", "xtcc_type", "func_defn",
  "$@2", "decl", "func_decl", "decl_comma_list", "var_decl",
  "statement_list", "statement", "$@3", "ListStatement", "if_stmt",
  "FieldStatement", "compound_stmt", "open_curly", "expr_list",
  "expression", "range_list", "range", "tab_list", "tab_defn", "ax_list",
  "ax_defn", "attributes", "$@4", "text_list", "axes_and_weights",
  "weights", "stub_list", "stub", "ttl_ax_stmt_list", "ttl_ax_stmt",
  "count_ax_stmt_list", "count_ax_stmt", "bit_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,    59,   261,   123,   125,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,    91,    93,    40,    41,
      61,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,    44,
     296,   297,   298,   299,    60,    62,   300,   301,    45,    43,
      42,    47,    37,   302,   303,   304,    38,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    68,    70,    69,    69,    69,    71,    71,    72,    72,
      73,    73,    73,    73,    73,    73,    75,    74,    76,    76,
      76,    76,    76,    77,    78,    78,    79,    79,    79,    79,
      80,    80,    80,    82,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    83,    83,    83,    84,    84,    85,
      86,    87,    88,    88,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    90,
      90,    91,    91,    92,    92,    93,    93,    93,    94,    94,
      95,    95,    95,    95,    95,    97,    96,    98,    98,    99,
      99,   100,   100,   101,   101,   102,   103,   103,   104,   105,
     105,   106,   106,   106,   106,   106,   107
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
       5,     8,    13,     4,     2,     0,     6,     2,     3,     3,
       4,     1,     2,     1,     2,     4,     1,     2,     4,     1,
       2,     4,     7,     7,     7,     1,     5
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     1,     0,
       0,     0,     0,    88,     0,     0,     0,    83,     0,    94,
       0,     0,     4,    89,    87,     0,     5,    84,     0,     0,
       0,     0,     0,     0,     0,     0,   106,     0,    93,    85,
       2,     0,    76,    72,    71,    70,     0,     0,     0,     0,
       0,     0,     0,     0,   107,    90,   109,   115,   101,     0,
       0,     0,     0,     0,     0,     0,     0,    59,    69,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
      99,   102,     0,     0,     0,   108,     0,     0,    52,    77,
       0,     0,     0,    68,    66,    67,    65,    64,    60,    61,
      63,    62,    55,    54,    56,    57,    58,     0,     0,     0,
       0,   100,    86,     0,    10,    11,    12,    13,    14,    15,
       0,     6,     0,     9,     8,    22,    73,     0,    75,     0,
       0,    91,    82,     0,    79,   111,     0,     0,     0,   103,
       0,     0,     3,     7,     0,     0,    53,     0,     0,    78,
       0,     0,     0,     0,   116,   104,     0,     0,    18,     0,
      29,     0,    74,     0,    81,    80,     0,     0,     0,     0,
       0,     0,     0,     0,    24,     0,     0,   112,   113,   105,
     114,    21,     0,    26,     0,    16,    29,    19,     0,    20,
       0,    28,    23,     0,    25,    92,     0,    51,    17,     0,
      27,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      38,     0,    30,    39,    35,    42,    37,     0,    32,    43,
       0,     0,     0,     0,     0,    41,    40,     0,    50,    31,
      36,     0,     0,     0,     0,     0,    95,    29,     0,     0,
      44,     0,     0,     0,     0,     0,     0,     0,     0,    47,
       0,     0,     0,     0,     0,     0,     0,     0,    97,    96,
       0,     0,     0,    45,     0,    48,    98,    33,     0,     0,
       0,     0,    46,    34,     0,     0,    49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,    62,   130,   131,   219,   133,   203,   220,   135,
     183,   184,   221,   222,   280,   223,   224,   225,   226,   209,
      97,   227,   143,   144,    16,    17,    12,    13,   228,   253,
     261,    38,    59,   148,   149,    35,    36,    55,    56,    57
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -196
static const yytype_int16 yypact[] =
{
     128,     3,    21,     2,    34,   179,     8,    22,  -196,    64,
      50,    56,   232,  -196,    94,    97,     9,  -196,    92,  -196,
     117,   124,  -196,  -196,  -196,   132,  -196,  -196,   130,    15,
     138,   157,   158,   164,     0,   106,  -196,   159,   162,   136,
    -196,   166,  -196,   -21,  -196,  -196,     0,     0,     0,   202,
     180,   181,   172,   185,  -196,    17,  -196,  -196,  -196,    16,
     159,     0,   165,   203,     0,     0,   585,  -196,  -196,   108,
     183,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   197,   207,   219,     0,  -196,
    -196,  -196,    93,   215,   798,  -196,   533,     7,   752,  -196,
     214,   106,   208,   752,   790,   801,   225,   225,   115,   115,
     115,   115,   133,   133,  -196,  -196,  -196,   228,   229,   220,
     272,  -196,  -196,   222,  -196,  -196,  -196,  -196,  -196,  -196,
     846,  -196,   227,  -196,  -196,  -196,  -196,     0,  -196,     0,
     216,    17,   190,    80,  -196,   204,   206,   258,    55,  -196,
     244,   260,  -196,  -196,    60,   598,   752,   274,   275,  -196,
     208,     0,     0,   276,  -196,  -196,     0,   208,  -196,   278,
     273,     0,  -196,   286,  -196,  -196,   285,   342,   287,   355,
      27,   284,   -11,    82,  -196,   412,   289,  -196,  -196,  -196,
    -196,  -196,   294,   277,   295,   307,   273,  -196,   106,  -196,
     281,  -196,  -196,   306,  -196,    17,   290,  -196,  -196,    61,
    -196,   310,   291,   301,   303,   293,   332,   344,   345,   335,
    -196,   125,  -196,  -196,  -196,  -196,  -196,   425,  -196,  -196,
       0,   323,   120,     0,   324,  -196,  -196,    76,  -196,  -196,
    -196,   482,   338,   350,     0,   636,  -196,   273,     0,   329,
    -196,   547,   184,   343,    86,   495,     0,   346,     0,   334,
     354,   146,   307,     0,   650,   357,   688,   184,  -196,  -196,
     358,   701,     0,  -196,   349,  -196,  -196,  -196,   739,   360,
     184,   302,  -196,  -196,   348,   364,  -196
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -196,  -196,  -196,  -196,   241,   -79,  -196,  -196,   -71,  -196,
     126,   178,  -196,  -195,  -196,  -196,  -196,  -196,   173,  -196,
    -196,   -34,   210,   218,  -196,   359,  -196,   367,  -196,  -196,
    -196,  -196,   321,  -196,   234,   -66,   -33,   -97,   -54,  -196
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      49,    89,    54,   101,   141,    64,   193,    65,     7,    14,
      14,     5,    66,    67,    68,   132,    42,    43,    26,    44,
      45,    50,    90,   134,    51,    33,   239,    93,    46,     6,
      96,    98,    52,   191,     8,    91,   138,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   132,    15,    15,   120,   194,   139,   259,    47,   134,
      34,   164,   211,    48,    18,    53,   168,    20,    54,   207,
      19,   147,   275,    21,   212,   213,   160,    42,    43,   123,
      44,    45,   168,   214,   215,   283,   169,    89,   170,    46,
     171,   182,   124,   125,   126,   127,   128,   129,   216,   121,
      24,   205,   169,   155,   247,   156,   171,   217,   218,   159,
      50,   195,    91,    51,    25,   262,    33,   182,    33,    47,
     198,    52,    28,    29,    48,   100,   211,   176,   177,   160,
      30,   196,   179,   207,   238,   196,   243,   185,   212,   213,
      70,    42,    43,   123,    44,    45,   244,   214,   215,    31,
      32,    89,   269,    46,    53,    37,   124,   125,   126,   127,
     128,   129,   270,    39,    40,    54,     1,     2,   182,     3,
      41,   217,   218,    80,    81,    82,    83,    84,    58,    60,
       9,    61,    63,    47,    10,   211,    85,    86,    48,    87,
      11,    88,   207,    82,    83,    84,   241,   212,   213,   245,
      42,    43,   123,    44,    45,    94,   214,   215,    69,    95,
     251,   102,    46,   117,   255,   124,   125,   126,   127,   128,
     129,   122,   264,   118,   266,   119,   140,    70,   142,   271,
     217,   218,    71,     9,   145,   146,   147,    10,   278,   151,
      70,    22,    47,    11,   154,    71,   157,    48,   158,   161,
      70,   162,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,   150,    76,
      77,    78,    79,    80,    81,    82,    83,    84,   163,   166,
     167,   187,   186,   189,   173,   174,   178,    70,   181,    33,
     199,   206,    71,   200,   124,   125,   126,   127,   128,   129,
      70,   192,   201,   202,   207,    71,   229,   210,   231,   230,
     232,   233,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,   188,   234,
     235,   236,   237,   242,   246,   249,   250,   256,   267,   260,
     268,   190,   265,   273,   276,   279,   282,    70,   285,   284,
     286,   153,    71,   254,   204,    27,   208,   180,   175,    23,
      70,    92,   165,     0,     0,    71,     0,     0,     0,     0,
       0,     0,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,   197,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   240,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,    71,     0,     0,     0,     0,     0,     0,     0,
      70,     0,     0,     0,     0,    71,     0,     0,     0,     0,
       0,     0,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,   248,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   263,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,    71,     0,     0,     0,     0,     0,     0,     0,
      70,     0,     0,     0,     0,    71,     0,     0,     0,     0,
       0,     0,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    70,     0,
     136,     0,     0,    71,     0,     0,     0,     0,     0,     0,
       0,     0,    70,     0,   257,     0,     0,    71,     0,     0,
       0,     0,   137,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,   258,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      70,     0,     0,     0,    99,    71,     0,     0,     0,     0,
       0,     0,     0,    70,     0,   172,     0,     0,    71,     0,
       0,     0,     0,     0,     0,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    70,     0,     0,     0,   252,    71,     0,     0,     0,
       0,     0,     0,     0,     0,    70,     0,     0,     0,     0,
      71,     0,     0,     0,     0,     0,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,   272,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    70,     0,   274,     0,     0,    71,     0,
       0,     0,     0,     0,     0,     0,    70,     0,     0,     0,
     277,    71,     0,     0,     0,     0,     0,     0,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    70,     0,     0,     0,   281,    71,
       0,     0,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,    71,     0,     0,     0,     0,     0,     0,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    70,   123,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    70,     0,     0,   124,
     125,   126,   127,   128,   129,     0,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,   123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   124,   125,   126,
     127,   128,   129,     0,     0,     0,     0,     0,     0,   152
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-196))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      34,    55,    35,    69,   101,    26,    17,    28,     6,     1,
       1,     8,    46,    47,    48,    94,    16,    17,     9,    19,
      20,     4,     6,    94,     7,    10,   221,    61,    28,     8,
      64,    65,    15,     6,     0,    19,    29,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,   130,    44,    44,    88,    66,    49,   252,    58,   130,
      45,     6,     1,    63,    42,    48,     6,    17,   101,     8,
       6,    16,   267,    17,    13,    14,    49,    16,    17,    18,
      19,    20,     6,    22,    23,   280,    26,   141,    28,    28,
      30,   170,    31,    32,    33,    34,    35,    36,    37,     6,
       6,   198,    26,   137,    28,   139,    30,    46,    47,    29,
       4,    29,    19,     7,    17,    29,    10,   196,    10,    58,
     186,    15,    30,     6,    63,    17,     1,   161,   162,    49,
       6,    49,   166,     8,     9,    49,    16,   171,    13,    14,
      25,    16,    17,    18,    19,    20,    26,    22,    23,    17,
      20,   205,     6,    28,    48,    17,    31,    32,    33,    34,
      35,    36,    16,     6,     6,   198,    38,    39,   247,    41,
       6,    46,    47,    58,    59,    60,    61,    62,    19,    17,
       1,    45,    16,    58,     5,     1,     6,     6,    63,    17,
      11,     6,     8,    60,    61,    62,   230,    13,    14,   233,
      16,    17,    18,    19,    20,    40,    22,    23,     6,     6,
     244,    28,    28,    16,   248,    31,    32,    33,    34,    35,
      36,     6,   256,    16,   258,     6,    12,    25,    20,   263,
      46,    47,    30,     1,     6,     6,    16,     5,   272,    17,
      25,     9,    58,    11,    17,    30,    30,    63,    58,    45,
      25,    45,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,     6,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    30,    45,
      30,     6,     6,     6,    20,    20,    20,    25,    20,    10,
       6,    20,    30,    26,    31,    32,    33,    34,    35,    36,
      25,    27,    17,     6,     8,    30,     6,    27,    17,    28,
      17,    28,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,     6,    17,
       6,     6,    17,    30,    30,    17,     6,    28,    24,    16,
       6,     6,    16,     6,     6,    16,     6,    25,    20,    67,
       6,   130,    30,   247,   196,    16,   203,   167,   160,    12,
      25,    60,   148,    -1,    -1,    30,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    25,    -1,
      27,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      25,    -1,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    25,    -1,    -1,    -1,    29,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    25,    -1,    27,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,
      29,    30,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    25,    -1,    -1,    -1,    29,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    25,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    43
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    38,    39,    41,    69,     8,     8,     6,     0,     1,
       5,    11,    94,    95,     1,    44,    92,    93,    42,     6,
      17,    17,     9,    95,     6,    17,     9,    93,    30,     6,
       6,    17,    20,    10,    45,   103,   104,    17,    99,     6,
       6,     6,    16,    17,    19,    20,    28,    58,    63,    89,
       4,     7,    15,    48,   104,   105,   106,   107,    19,   100,
      17,    45,    70,    16,    26,    28,    89,    89,    89,     6,
      25,    30,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,     6,     6,    17,     6,   106,
       6,    19,   100,    89,    40,     6,    89,    88,    89,    29,
      17,   103,    28,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    16,    16,     6,
      89,     6,     6,    18,    31,    32,    33,    34,    35,    36,
      71,    72,    73,    74,    76,    77,    27,    49,    29,    49,
      12,   105,    20,    90,    91,     6,     6,    16,   101,   102,
       6,    17,    43,    72,    17,    89,    89,    30,    58,    29,
      49,    45,    45,    30,     6,   102,    45,    30,     6,    26,
      28,    30,    27,    20,    20,    91,    89,    89,    20,    89,
      90,    20,    73,    78,    79,    89,     6,     6,     6,     6,
       6,     6,    27,    17,    66,    29,    49,     6,   103,     6,
      26,    17,     6,    75,    79,   105,    20,     8,    86,    87,
      27,     1,    13,    14,    22,    23,    37,    46,    47,    73,
      76,    80,    81,    83,    84,    85,    86,    89,    96,     6,
      28,    17,    17,    28,    17,     6,     6,    17,     9,    81,
       6,    89,    30,    16,    26,    89,    30,    28,     6,    17,
       6,    89,    29,    97,    78,    89,    28,    27,    49,    81,
      16,    98,    29,     6,    89,    16,    89,    24,     6,     6,
      16,    89,    49,     6,    27,    81,     6,    29,    89,    16,
      82,    29,     6,    81,    67,    20,     6
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
        case 2:

/* Line 1806 of yacc.c  */
#line 237 "src/type.ypp"
    {	const char * c_arr="c";  
		rec_len=(yyvsp[(5) - (6)].ival); 
		active_scope->insert(c_arr, INT8_ARR_TYPE, rec_len, 0);
	}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 241 "src/type.ypp"
    {
		tree_root = trav_chain((yyvsp[(9) - (10)].stmt));
		if(tree_root==0){
			cerr << "tree_root =0 : core dump expected" << endl;
		}
		return 0;
	}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 248 "src/type.ypp"
    {
		return 0;
	}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 251 "src/type.ypp"
    {
		return 0;
	}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 256 "src/type.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 259 "src/type.ypp"
    {
		(yyval.stmt)=link_chain((yyvsp[(1) - (2)].stmt),(yyvsp[(2) - (2)].stmt));
	}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 264 "src/type.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 267 "src/type.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 282 "src/type.ypp"
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

/* Line 1806 of yacc.c  */
#line 291 "src/type.ypp"
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

/* Line 1806 of yacc.c  */
#line 317 "src/type.ypp"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (3)].name), (yyvsp[(1) - (3)].dt)/*, line_no*/, nest_lev);
		free((yyvsp[(2) - (3)].name));
	}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 321 "src/type.ypp"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (5)].name), (yyvsp[(1) - (5)].dt), (yyvsp[(4) - (5)].expr), nest_lev);

	}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 325 "src/type.ypp"
    {
		/* NxD: I have ordered the types in DataType so that this hack is possible I hope */
		DataType dt=DataType(INT8_ARR_TYPE+((yyvsp[(1) - (6)].dt)-INT8_TYPE));
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (6)].name), dt, (yyvsp[(4) - (6)].ival)/*, line_no*/, nest_lev);
		free((yyvsp[(2) - (6)].name));
	}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 339 "src/type.ypp"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (5)].name), RANGE_DECL_STMT, &xs, nest_lev);
		//$$ = new decl_stmt($2, RANGE_DECL_STMT, &xs );
		xs.reset();
	}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 344 "src/type.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 350 "src/type.ypp"
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

/* Line 1806 of yacc.c  */
#line 362 "src/type.ypp"
    {
		 (yyval.v_list)=(yyvsp[(1) - (1)].v_list);
		 //cout << "got decl_comma_list : " << endl;
	}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 366 "src/type.ypp"
    {
		(yyval.v_list)=link_chain((yyvsp[(1) - (3)].v_list),(yyvsp[(3) - (3)].v_list));
		//cout << "chaining var_decl : " << endl;
	}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 373 "src/type.ypp"
    {
		(yyval.v_list)=new Statement::FunctionParameter((yyvsp[(1) - (2)].dt), (yyvsp[(2) - (2)].name));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (2)].name));
	}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 380 "src/type.ypp"
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

/* Line 1806 of yacc.c  */
#line 389 "src/type.ypp"
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

/* Line 1806 of yacc.c  */
#line 398 "src/type.ypp"
    {
		(yyval.v_list)=0;
		}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 403 "src/type.ypp"
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

/* Line 1806 of yacc.c  */
#line 413 "src/type.ypp"
    {
		(yyval.stmt)=link_chain((yyvsp[(1) - (2)].stmt),(yyvsp[(2) - (2)].stmt));
	}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 416 "src/type.ypp"
    {
		(yyval.stmt)=0;
	}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 421 "src/type.ypp"
    { ++in_a_loop;}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 421 "src/type.ypp"
    {
		(yyval.stmt) = new struct Statement::ForStatement(FOR_STMT, line_no, (yyvsp[(3) - (10)].expr), (yyvsp[(5) - (10)].expr), (yyvsp[(7) - (10)].expr), (yyvsp[(10) - (10)].stmt));
		--in_a_loop;
	}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 426 "src/type.ypp"
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

/* Line 1806 of yacc.c  */
#line 439 "src/type.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].c_stmt);
	}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 442 "src/type.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 446 "src/type.ypp"
    {
		(yyval.stmt)=new Statement::BreakStatement(BREAK_STMT, line_no, in_a_loop);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 452 "src/type.ypp"
    {
		(yyval.stmt)=new Statement::ContinueStatement(CONTINUE_STMT, line_no, in_a_loop);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 459 "src/type.ypp"
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

/* Line 1806 of yacc.c  */
#line 470 "src/type.ypp"
    {
		(yyval.stmt)=new Statement::ListStatement(LISTA_BASIC_TYPE_STMT, (yyvsp[(2) - (4)].name), (yyvsp[(3) - (4)].text_buf));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (4)].name));
	}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 477 "src/type.ypp"
    {
		(yyval.stmt)=new Statement::ListStatement( LISTA_BASIC_ARRTYPE_STMT_1INDEX, (yyvsp[(2) - (7)].name), string((yyvsp[(6) - (7)].text_buf)), (yyvsp[(4) - (7)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (7)].name));
	}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 484 "src/type.ypp"
    {
		(yyval.stmt)=new Statement::ListStatement( LISTA_BASIC_ARRTYPE_STMT_1INDEX, (yyvsp[(2) - (9)].name), string((yyvsp[(8) - (9)].text_buf)), (yyvsp[(4) - (9)].expr), (yyvsp[(6) - (9)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (9)].name));	
	}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 493 "src/type.ypp"
    {
		(yyval.stmt)=new Statement::IfStatement(IFE_STMT,if_line_no,(yyvsp[(3) - (5)].expr),(yyvsp[(5) - (5)].stmt),0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 499 "src/type.ypp"
    {
		(yyval.stmt)=new Statement::IfStatement(IFE_STMT, if_line_no,(yyvsp[(3) - (7)].expr),(yyvsp[(5) - (7)].stmt),(yyvsp[(7) - (7)].stmt));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 507 "src/type.ypp"
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

/* Line 1806 of yacc.c  */
#line 519 "src/type.ypp"
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

/* Line 1806 of yacc.c  */
#line 553 "src/type.ypp"
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

/* Line 1806 of yacc.c  */
#line 577 "src/type.ypp"
    { (yyval.expr)=(yyvsp[(1) - (1)].expr); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 578 "src/type.ypp"
    {
		(yyval.expr)=link_chain((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));
	}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 583 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_plus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 589 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_minus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 595 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_mult);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 601 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_div);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 607 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_mod);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 613 "src/type.ypp"
    {
		(yyval.expr) = new Expression::UnaryExpression((yyvsp[(2) - (2)].expr), Expression::oper_umin);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 619 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_lt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 625 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_gt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 631 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_le);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 637 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_ge);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 643 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_iseq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 649 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_isneq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 655 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_or);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 661 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_and);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 667 "src/type.ypp"
    {
		(yyval.expr) = new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_assgn);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 673 "src/type.ypp"
    {
		(yyval.expr) = new Expression::UnaryExpression((yyvsp[(2) - (2)].expr), Expression::oper_not);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 679 "src/type.ypp"
    {
		(yyval.expr) = new Expression::Unary2Expression((yyvsp[(1) - (1)].ival));
		//cout << "got INUMBER: " << $1 << " type : " << $$->type << endl;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 686 "src/type.ypp"
    {
		(yyval.expr) = new Expression::Unary2Expression((yyvsp[(1) - (1)].dval));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 692 "src/type.ypp"
    {
		(yyval.expr) = new Expression::Unary2Expression((yyvsp[(1) - (1)].name), Expression::oper_name );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 698 "src/type.ypp"
    {
		(yyval.expr) = new Expression::Unary2Expression (Expression::oper_arrderef, /*nametype,  se,*/ (yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(1) - (4)].name));
	}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 705 "src/type.ypp"
    {
		(yyval.expr) = new Expression::Unary2Expression(Expression::oper_blk_arr_assgn, (yyvsp[(1) - (6)].name),(yyvsp[(3) - (6)].expr),(yyvsp[(5) - (6)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(1) - (6)].name));
	}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 712 "src/type.ypp"
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

/* Line 1806 of yacc.c  */
#line 751 "src/type.ypp"
    {
		(yyval.expr) = new Expression::Unary2Expression(strdup((yyvsp[(1) - (1)].text_buf)), Expression::oper_text_expr);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 757 "src/type.ypp"
    { 
		(yyval.expr) = new Expression::UnaryExpression((yyvsp[(2) - (3)].expr), Expression::oper_parexp );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 763 "src/type.ypp"
    {
		(yyval.expr) = new Expression::Binary2Expression((yyvsp[(1) - (5)].expr), xs, Expression::oper_in);
		xs.reset();
	}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 781 "src/type.ypp"
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

/* Line 1806 of yacc.c  */
#line 790 "src/type.ypp"
    {
		xs.indiv.insert((yyvsp[(1) - (1)].ival));
	}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 795 "src/type.ypp"
    { 
#ifdef DEBUG_GRAM
	printf("got table defn\n"); 
#endif
	}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 800 "src/type.ypp"
    { 
#ifdef DEBUG_GRAM
		printf("recursive tab_defn\n"); 
#endif
	}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 808 "src/type.ypp"
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

/* Line 1806 of yacc.c  */
#line 816 "src/type.ypp"
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

/* Line 1806 of yacc.c  */
#line 824 "src/type.ypp"
    {
		cerr << "Error in tab section line: " <<
			line_no << endl;
		++no_errors;
	}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 831 "src/type.ypp"
    {
	}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 833 "src/type.ypp"
    {
	}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 837 "src/type.ypp"
    {
		using Table::AbstractPrintableAxisStatement;
		using Table::AbstractCountableAxisStatement;
		Table::AbstractPrintableAxisStatement  * ttl_stmt_ptr= trav_chain((yyvsp[(4) - (5)].print_stmt));
		Table::AbstractCountableAxisStatement * count_stmt_ptr= trav_chain((yyvsp[(5) - (5)].count_stmt));

		(yyval.ax) = new Table::ax(ttl_stmt_ptr, count_stmt_ptr, 
				no_count_ax_elems, 
				no_tot_ax_elems, 
				no_inc_ax_elems,
				0,
				0, string());
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.ax), __LINE__, __FILE__, line_no);
		}
		
		ax_map[(yyvsp[(2) - (5)].name)]=(yyval.ax);
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		no_inc_ax_elems = 0;
		free((yyvsp[(2) - (5)].name));
	}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 860 "src/type.ypp"
    {
		Table::AbstractPrintableAxisStatement * ttl_stmt_ptr= trav_chain((yyvsp[(7) - (8)].print_stmt));
		Table::AbstractCountableAxisStatement * count_stmt_ptr= trav_chain((yyvsp[(8) - (8)].count_stmt));
		(yyval.ax) = new Table::ax(ttl_stmt_ptr, count_stmt_ptr, 
				no_count_ax_elems,
				no_tot_ax_elems,
				no_inc_ax_elems,
				0,
				(yyvsp[(5) - (8)].expr), string());
		
		//std::cout << "got axis: " << $2 
		//	<< "no_tot_ax_elems: " << no_tot_ax_elems 
		//	<< ", no_count_ax_elems: " << no_count_ax_elems
		//	<< endl;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.ax), __LINE__, __FILE__, line_no);
		}
		ax_map[(yyvsp[(2) - (8)].name)]=(yyval.ax);
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		no_inc_ax_elems = 0;
		free((yyvsp[(2) - (8)].name));
	}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 884 "src/type.ypp"
    {
		string stub_hint = (yyvsp[(7) - (13)].name);
		int no_mpn = (yyvsp[(10) - (13)].ival);
		Table::AbstractPrintableAxisStatement * ttl_stmt_ptr= trav_chain((yyvsp[(12) - (13)].print_stmt));
		Table::AbstractCountableAxisStatement * count_stmt_ptr= trav_chain((yyvsp[(13) - (13)].count_stmt));
		(yyval.ax) = new Table::ax(ttl_stmt_ptr, count_stmt_ptr, 
				no_count_ax_elems, 
				no_tot_ax_elems, 
				no_inc_ax_elems,
				no_mpn,
				(yyvsp[(5) - (13)].expr), stub_hint);
		
		//std::cout << "got axis: " << $2 
		//	<< "no_tot_ax_elems: " << no_tot_ax_elems 
		//	<< ", no_count_ax_elems: " << no_count_ax_elems
		//	<< endl;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.ax), __LINE__, __FILE__, line_no);
		}
		ax_map[(yyvsp[(2) - (13)].name)]=(yyval.ax);
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		no_inc_ax_elems = 0;
		free((yyvsp[(2) - (13)].name));
	}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 909 "src/type.ypp"
    {
		Table::weight_axis_group wt_axis_grp ((yyvsp[(2) - (4)].name), wt_axis_vec);
		wt_axis_group_vec .push_back (wt_axis_grp);
	}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 913 "src/type.ypp"
    {
		cerr << "Error in axis section line: " <<
			line_no << endl;
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		++no_errors;
	}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 922 "src/type.ypp"
    {
		attribute_list.resize(0);
		//cout << "resize attribute_list to 0\n";
	}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 925 "src/type.ypp"
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
			SymbolTableEntry* se=new SymbolTableEntry((yyvsp[(2) - (6)].name), NAMED_ATTRIBUTE_TYPE, nest_lev);
			active_scope_list[0]->sym_tab[s] = se;
			n_attr_stmt->symbolTableEntry_ = se;
		}
	}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 946 "src/type.ypp"
    {
		string s1=(yyvsp[(1) - (2)].text_buf);
		attribute_list.push_back(s1);
	}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 950 "src/type.ypp"
    {
		string s1=(yyvsp[(2) - (3)].text_buf);
		attribute_list.push_back(s1);
        }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 956 "src/type.ypp"
    {
		string wt_ax_name((yyvsp[(1) - (3)].name));
		Table::weight_axis wt_ax (wt_ax_name, weight_vec);
		Table::ax * wt_ax_ptr = ax_map[wt_ax_name];
		if (wt_ax_ptr == 0) {
			Util::print_err(Util::compiler_sem_err, "weight axis was not found in the axes parse so far around line_no: ", 
				line_no, __LINE__, __FILE__);
		} else {
			if ( wt_ax_ptr->no_count_ax_elems  != weight_vec.size()) {

				stringstream err_msg;
				err_msg << "no of factors in weight axis |" 
					<< wt_ax_name << "| : "
					<< wt_ax_ptr->no_count_ax_elems 
					<< ",  does not match no of factors in axis, around line_no: " 
					<< weight_vec.size()
					<< endl;
				Util::print_err(Util::compiler_sem_err, err_msg.str(), 
				line_no, __LINE__, __FILE__);
			} else {
				cout << "no of factors in weight axes matched with axes count elements" << endl;
			}
		}
		wt_axis_vec.push_back (wt_ax);
		weight_vec.clear();
	}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 982 "src/type.ypp"
    {
		Table::weight_axis wt_ax ((yyvsp[(2) - (4)].name), weight_vec);
		wt_axis_vec.push_back (wt_ax);
		weight_vec.clear();
	}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 989 "src/type.ypp"
    {
		weight_vec.push_back ((yyvsp[(1) - (1)].dval));
	}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 992 "src/type.ypp"
    {
		weight_vec.push_back ((yyvsp[(2) - (2)].dval));
	}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 998 "src/type.ypp"
    {
		//$$=link_chain($1, $2);
	}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1003 "src/type.ypp"
    {
		using Table::stub;
		(yyval.stub)=new stub((yyvsp[(1) - (4)].text_buf), (yyvsp[(3) - (4)].ival));
		stub_list.push_back((yyval.stub));
		++ no_count_ax_elems;
		++ no_tot_ax_elems;
	}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1012 "src/type.ypp"
    { (yyval.print_stmt)=(yyvsp[(1) - (1)].print_stmt); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1013 "src/type.ypp"
    {
		(yyval.print_stmt)=link_chain((yyvsp[(1) - (2)].print_stmt), (yyvsp[(2) - (2)].print_stmt));
	}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1018 "src/type.ypp"
    {
		using Table::TitleStatement;
		(yyval.print_stmt) = new TitleStatement (Table::txt_axstmt,(yyvsp[(3) - (4)].text_buf));
		++no_tot_ax_elems;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.print_stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1028 "src/type.ypp"
    {
		(yyval.count_stmt) = (yyvsp[(1) - (1)].count_stmt);
	}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1031 "src/type.ypp"
    {
		(yyval.count_stmt)=link_chain((yyvsp[(1) - (2)].count_stmt), (yyvsp[(2) - (2)].count_stmt));
	}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 1036 "src/type.ypp"
    {
		using Table::tot_ax_stmt;
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		int position = no_count_ax_elems-1;
		(yyval.count_stmt) = new tot_ax_stmt (Table::tot_axstmt,(yyvsp[(3) - (4)].text_buf), 0, position);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.count_stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1046 "src/type.ypp"
    {
		using Table::tot_ax_stmt;
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.count_stmt) = new tot_ax_stmt (Table::tot_axstmt,(yyvsp[(3) - (7)].text_buf), (yyvsp[(6) - (7)].expr), no_count_ax_elems);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.count_stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 1055 "src/type.ypp"
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

  case 114:

/* Line 1806 of yacc.c  */
#line 1064 "src/type.ypp"
    {
		if (no_inc_ax_elems > 0) {
			stringstream err_msg;
			err_msg << "Only 1 inc statement is allowed per axis" << endl;
			print_err(Util::compiler_sem_err, err_msg.str(), line_no, __LINE__, __FILE__);
		}
		++no_inc_ax_elems;
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.count_stmt) = new Table::inc_ax_stmt (Table::inc_axstmt, (yyvsp[(3) - (7)].expr), (yyvsp[(6) - (7)].expr));
	}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 1078 "src/type.ypp"
    {
		using Table::fld_ax_stmt;
		//stub * stub_ptr = trav_chain($4);
	 	//$$ = new fld_ax_stmt ($2, stub_ptr);
	 	(yyval.count_stmt) = new fld_ax_stmt (Table::fld_axstmt, (yyvsp[(2) - (5)].name), stub_list);
		stub_list.resize(0);
	}
    break;



/* Line 1806 of yacc.c  */
#line 3228 "src/type.cpp"
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
#line 1087 "src/type.ypp"



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


