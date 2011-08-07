
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



/* Line 189 of yacc.c  */
#line 166 "src/type.cpp"

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
     ATTRIBUTE_LIST = 282,
     AXSTART = 283,
     TABSTART = 284,
     ED_START = 285,
     DATA_STRUCT = 286,
     REC_LEN = 287,
     ED_END = 288,
     TAB = 289,
     COND_START = 290,
     CONTINUE = 291,
     BREAK = 292,
     INC = 293,
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



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 118 "src/type.ypp"

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



/* Line 214 of yacc.c  */
#line 271 "src/type.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 283 "src/type.cpp"

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
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   837

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNRULES -- Number of states.  */
#define YYNSTATES  268

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
      26,    27,    58,    57,    47,    56,     2,    59,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    65,     6,
      52,    28,    53,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    24,     2,    25,     2,     2,     2,     2,     2,     2,
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
      18,    19,    20,    21,    22,    23,    29,    30,    31,    32,
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
     388,   390,   393,   398,   400,   403,   408,   416,   424,   432,
     434
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      67,     0,    -1,    -1,    39,     6,    40,    28,    18,     6,
      68,    38,    69,    41,    -1,    36,     8,    92,     9,    -1,
      37,     8,    90,     9,    -1,    70,    -1,    69,    70,    -1,
      74,    -1,    72,    -1,    29,    -1,    30,    -1,    31,    -1,
      32,    -1,    33,    -1,    34,    -1,    -1,    71,    15,    26,
      76,    27,    73,    84,    -1,    71,    15,     6,    -1,    71,
      15,    28,    87,     6,    -1,    71,    15,    24,    18,    25,
       6,    -1,    16,    15,    28,    88,     6,    -1,    75,    -1,
      71,    15,    26,    76,    27,     6,    -1,    77,    -1,    76,
      47,    77,    -1,    71,    15,    -1,    71,    15,    24,    18,
      25,    -1,    71,    64,    15,    -1,    -1,    79,    -1,    78,
      79,    -1,    94,    -1,    -1,    11,    26,    87,     6,    87,
       6,    87,    27,    80,    79,    -1,    82,    -1,    87,     6,
      -1,    84,    -1,    74,    -1,    81,    -1,    45,     6,    -1,
      44,     6,    -1,    83,    -1,     1,     6,    -1,    20,    15,
      14,     6,    -1,    20,    15,    24,    87,    25,    14,     6,
      -1,    20,    15,    24,    87,    47,    87,    25,    14,     6,
      -1,    21,    26,    87,    27,    79,    -1,    21,    26,    87,
      27,    79,    22,    79,    -1,    12,    15,    28,    15,    26,
      87,    47,    87,    27,    65,    18,     6,    -1,    85,    78,
       9,    -1,     8,    -1,    87,    -1,    86,    47,    87,    -1,
      87,    57,    87,    -1,    87,    56,    87,    -1,    87,    58,
      87,    -1,    87,    59,    87,    -1,    87,    60,    87,    -1,
      56,    87,    -1,    87,    52,    87,    -1,    87,    53,    87,
      -1,    87,    55,    87,    -1,    87,    54,    87,    -1,    87,
      51,    87,    -1,    87,    50,    87,    -1,    87,    48,    87,
      -1,    87,    49,    87,    -1,    87,    28,    87,    -1,    61,
      87,    -1,    18,    -1,    17,    -1,    15,    -1,    15,    24,
      87,    25,    -1,    15,    24,    87,    47,    87,    25,    -1,
      15,    26,    86,    27,    -1,    14,    -1,    26,    87,    27,
      -1,    87,    23,    26,    88,    27,    -1,    89,    -1,    88,
      47,    89,    -1,    18,    56,    18,    -1,    18,    -1,    91,
      -1,    90,    91,    -1,    42,    15,    15,     6,    -1,    42,
      15,    15,     6,    43,    87,     6,    -1,     1,     6,    -1,
      93,    -1,    92,    93,    -1,     5,    15,     6,    99,   101,
      -1,     5,    15,     6,    43,    87,     6,    99,   101,    -1,
       1,     6,    -1,    -1,    35,    15,    28,    95,    96,     6,
      -1,    14,     6,    -1,    96,    14,     6,    -1,    98,    -1,
      97,    98,    -1,    14,    28,    18,     6,    -1,   100,    -1,
      99,   100,    -1,    10,     6,    14,     6,    -1,   102,    -1,
     101,   102,    -1,     4,     6,    14,     6,    -1,     4,     6,
      14,     6,    43,    87,     6,    -1,     7,     6,    14,     6,
      43,    87,     6,    -1,    46,     6,    87,     6,    43,    87,
       6,    -1,   103,    -1,    13,    15,     6,    97,     6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   234,   234,   233,   245,   248,   253,   256,   261,   264,
     269,   270,   271,   272,   273,   274,   279,   279,   314,   318,
     322,   336,   341,   347,   359,   363,   370,   377,   386,   395,
     400,   410,   413,   418,   418,   422,   423,   436,   439,   442,
     443,   449,   455,   456,   467,   474,   481,   490,   496,   504,
     516,   550,   574,   575,   580,   586,   592,   598,   604,   610,
     616,   622,   628,   634,   640,   646,   652,   658,   664,   670,
     676,   683,   689,   695,   702,   709,   748,   754,   760,   774,
     775,   778,   787,   792,   797,   805,   813,   821,   828,   830,
     834,   854,   877,   886,   886,   910,   914,   920,   921,   926,
     935,   936,   941,   951,   954,   959,   969,   978,   987,   998,
    1001
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONVERT", "TOT", "AX", "';'", "CNT",
  "'{'", "'}'", "TTL", "FOR", "FLD", "BIT", "TEXT", "NAME", "DEFINELIST",
  "FNUMBER", "INUMBER", "CODELIST", "LISTA", "IF", "ELSE", "IN", "'['",
  "']'", "'('", "')'", "'='", "VOID_T", "INT8_T", "INT16_T", "INT32_T",
  "FLOAT_T", "DOUBLE_T", "ATTRIBUTE_LIST", "AXSTART", "TABSTART",
  "ED_START", "DATA_STRUCT", "REC_LEN", "ED_END", "TAB", "COND_START",
  "CONTINUE", "BREAK", "INC", "','", "LOGOR", "LOGAND", "NOEQ", "ISEQ",
  "'<'", "'>'", "GEQ", "LEQ", "'-'", "'+'", "'*'", "'/'", "'%'", "NOT",
  "UMINUS", "FUNC_CALL", "'&'", "':'", "$accept", "prog", "$@1",
  "top_level_item_list", "top_level_item", "xtcc_type", "func_defn", "$@2",
  "decl", "func_decl", "decl_comma_list", "var_decl", "statement_list",
  "statement", "$@3", "ListStatement", "if_stmt", "FieldStatement",
  "compound_stmt", "open_curly", "expr_list", "expression", "range_list",
  "range", "tab_list", "tab_defn", "ax_list", "ax_defn", "attributes",
  "$@4", "text_list", "stub_list", "stub", "ttl_ax_stmt_list",
  "ttl_ax_stmt", "count_ax_stmt_list", "count_ax_stmt", "bit_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,    59,   261,   123,   125,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,    91,    93,    40,    41,    61,   276,
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
       1,     2,     4,     1,     2,     4,     7,     7,     7,     1,
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
      90,   103,   109,     0,     0,     0,     0,     0,     0,    59,
      69,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   104,     0,     0,   102,     0,     0,    52,    77,     0,
       0,    68,    66,    67,    65,    64,    60,    61,    63,    62,
      55,    54,    56,    57,    58,     0,     0,     0,     0,    86,
       0,    10,    11,    12,    13,    14,    15,     0,     6,     0,
       9,     8,    22,    73,     0,    75,     0,    91,    82,     0,
      79,   105,     0,     0,     0,    97,     0,     0,     3,     7,
       0,     0,    53,     0,    78,     0,     0,     0,     0,   110,
      98,     0,     0,    18,     0,    29,     0,    74,    81,    80,
       0,     0,     0,     0,     0,     0,     0,     0,    24,     0,
     106,   107,    99,   108,    21,     0,    26,     0,    16,    29,
      19,    20,     0,    28,    23,     0,    25,     0,    51,    17,
       0,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    38,     0,    30,    39,    35,    42,    37,     0,    32,
      43,     0,     0,     0,     0,     0,    41,    40,     0,    50,
      31,    36,     0,     0,     0,     0,     0,    93,    29,     0,
       0,    44,     0,     0,     0,     0,     0,     0,     0,     0,
      47,     0,     0,     0,     0,     0,     0,     0,     0,    95,
      94,     0,     0,     0,    45,     0,    48,    96,    33,     0,
       0,     0,     0,    46,    34,     0,     0,    49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,    54,   117,   118,   200,   120,   185,   201,   122,
     167,   168,   202,   203,   261,   204,   205,   206,   207,   190,
      86,   208,   129,   130,    15,    16,    11,    12,   209,   234,
     242,   134,   135,    32,    33,    50,    51,    52
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -188
static const yytype_int16 yypact[] =
{
     137,     0,    67,    24,    56,   118,     8,    82,  -188,    88,
      47,    64,  -188,   120,   114,    22,  -188,   112,  -188,   138,
    -188,  -188,  -188,   144,  -188,  -188,   145,    43,   183,   186,
     191,     2,    14,  -188,   132,  -188,   193,  -188,   169,  -188,
    -188,     2,     2,     2,    48,   199,   203,   195,   205,  -188,
      44,  -188,  -188,     2,   174,   218,     2,     2,   563,  -188,
    -188,   215,   201,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,   214,   221,   223,
       2,  -188,   240,   136,  -188,   496,    40,   754,  -188,    14,
     226,   754,   766,   777,   263,   263,    54,    54,    54,    54,
     -53,   -53,  -188,  -188,  -188,   235,   239,   233,   253,  -188,
     217,  -188,  -188,  -188,  -188,  -188,  -188,    50,  -188,   234,
    -188,  -188,  -188,  -188,     2,  -188,     2,    44,   194,    41,
    -188,   219,   227,   229,   148,  -188,   228,   230,  -188,  -188,
     115,   601,   754,   242,  -188,   226,     2,     2,   243,  -188,
    -188,     2,   226,  -188,   246,   187,     2,  -188,  -188,  -188,
     308,   321,   259,   376,    23,   244,   -12,    45,  -188,   389,
    -188,  -188,  -188,  -188,  -188,   266,   249,   260,   268,   187,
    -188,  -188,   261,  -188,  -188,   269,  -188,   255,  -188,  -188,
     116,  -188,   276,   258,   270,   272,   298,   310,   320,   322,
     314,  -188,   170,  -188,  -188,  -188,  -188,  -188,   444,  -188,
    -188,     2,   302,   -10,     2,   304,  -188,  -188,   129,  -188,
    -188,  -188,   457,   318,   328,     2,   614,  -188,   187,     2,
     309,  -188,   550,   222,   323,    91,   512,     2,   324,     2,
     317,   334,   150,   268,     2,   652,   335,   665,   222,  -188,
    -188,   336,   703,     2,  -188,   329,  -188,  -188,  -188,   716,
     339,   222,   281,  -188,  -188,   330,   341,  -188
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -188,  -188,  -188,  -188,   236,   -70,  -188,  -188,   -28,  -188,
     122,   172,  -188,  -187,  -188,  -188,  -188,  -188,   167,  -188,
    -188,   -31,   202,   210,  -188,   368,  -188,   373,  -188,  -188,
    -188,  -188,   251,   325,   -30,   299,   -49,  -188
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      44,    81,    49,   176,   224,    74,    75,    76,     5,    13,
      58,    59,    60,   119,   225,   220,    37,    38,    45,    39,
      40,    46,    82,    13,    30,    85,    87,    47,    41,   174,
       7,    24,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   240,   119,    45,   108,
      14,    46,   177,    30,    61,   121,     8,    47,    42,    49,
      48,   256,    19,    43,    14,     9,   110,   125,   144,    10,
     145,    62,   178,    20,   264,     6,    63,    62,    81,   111,
     112,   113,   114,   115,   116,   166,    31,   126,   145,   121,
      48,   138,   179,   141,    18,   142,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,   166,
      72,    73,    74,    75,    76,   160,   161,   192,   243,     9,
     163,   153,    17,    10,   188,   169,    22,   193,   194,    23,
      37,    38,   110,    39,    40,   153,   195,   196,   179,   154,
      26,   155,    41,   156,    27,   111,   112,   113,   114,   115,
     116,   197,   110,   154,   149,   228,   250,   156,   166,    28,
     198,   199,   133,    29,   251,   111,   112,   113,   114,   115,
     116,   192,    42,     1,     2,    53,     3,    43,   188,   219,
     222,   193,   194,   226,    37,    38,   110,    39,    40,    34,
     195,   196,    35,    56,   232,    57,    41,    36,   236,   111,
     112,   113,   114,   115,   116,    77,   245,    55,   247,    78,
      79,    80,    83,   252,   198,   199,   111,   112,   113,   114,
     115,   116,   259,   192,    84,    30,    42,    90,   105,   107,
     188,    43,   137,   193,   194,   106,    37,    38,   110,    39,
      40,   131,   195,   196,   128,   132,   109,   133,    41,   140,
     143,   111,   112,   113,   114,   115,   116,   148,   152,   136,
     158,   162,   146,    62,   165,   172,   198,   199,    63,   175,
     147,   151,   181,   182,   184,   183,    62,   188,    42,   187,
     191,    63,   210,    43,   211,   212,    62,   213,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,   170,    68,    69,    70,    71,    72,
      73,    74,    75,    76,   214,   215,   216,   171,   217,   218,
     223,    62,   227,   230,   231,   237,    63,   241,   246,   248,
     249,   254,   257,   260,    62,   263,   265,   267,   266,    63,
     235,   186,   189,   139,   164,   159,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,   173,    25,    21,   150,    89,     0,   127,     0,
       0,     0,     0,     0,     0,   180,     0,     0,     0,    62,
       0,     0,     0,     0,    63,     0,     0,     0,     0,     0,
       0,     0,    62,     0,     0,     0,     0,    63,     0,     0,
       0,     0,     0,     0,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
     221,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   229,     0,     0,     0,    62,     0,     0,
       0,     0,    63,     0,     0,     0,     0,     0,     0,     0,
      62,     0,     0,     0,     0,    63,     0,     0,     0,     0,
       0,     0,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,   244,    62,
       0,   123,     0,     0,    63,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    62,     0,     0,     0,     0,
      63,     0,     0,   124,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,     0,     0,     0,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    62,     0,   238,     0,     0,    63,     0,
       0,     0,     0,     0,     0,     0,    62,     0,     0,     0,
      88,    63,     0,     0,     0,     0,     0,   239,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    62,     0,   157,     0,     0,    63,
       0,     0,     0,     0,     0,     0,     0,    62,     0,     0,
       0,   233,    63,     0,     0,     0,     0,     0,     0,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    62,     0,     0,     0,     0,
      63,     0,     0,     0,     0,     0,     0,     0,    62,     0,
     255,     0,     0,    63,     0,     0,     0,     0,     0,   253,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    62,     0,     0,     0,
     258,    63,     0,     0,     0,     0,     0,     0,     0,    62,
       0,     0,     0,   262,    63,     0,     0,     0,     0,     0,
       0,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    62,     0,     0,
       0,     0,    63,     0,     0,     0,     0,     0,     0,    62,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      62,     0,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76
};

static const yytype_int16 yycheck[] =
{
      31,    50,    32,    15,    14,    58,    59,    60,     8,     1,
      41,    42,    43,    83,    24,   202,    14,    15,     4,    17,
      18,     7,    53,     1,    10,    56,    57,    13,    26,     6,
       6,     9,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,   233,   117,     4,    80,
      42,     7,    64,    10,     6,    83,     0,    13,    56,    89,
      46,   248,    15,    61,    42,     1,    16,    27,    27,     5,
      47,    23,    27,     9,   261,     8,    28,    23,   127,    29,
      30,    31,    32,    33,    34,   155,    43,    47,    47,   117,
      46,    41,    47,   124,     6,   126,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,   179,
      56,    57,    58,    59,    60,   146,   147,     1,    27,     1,
     151,     6,    40,     5,     8,   156,     6,    11,    12,    15,
      14,    15,    16,    17,    18,     6,    20,    21,    47,    24,
      28,    26,    26,    28,     6,    29,    30,    31,    32,    33,
      34,    35,    16,    24,     6,    26,     6,    28,   228,    15,
      44,    45,    14,    18,    14,    29,    30,    31,    32,    33,
      34,     1,    56,    36,    37,    43,    39,    61,     8,     9,
     211,    11,    12,   214,    14,    15,    16,    17,    18,     6,
      20,    21,     6,    24,   225,    26,    26,     6,   229,    29,
      30,    31,    32,    33,    34,     6,   237,    14,   239,     6,
      15,     6,    38,   244,    44,    45,    29,    30,    31,    32,
      33,    34,   253,     1,     6,    10,    56,    26,    14,     6,
       8,    61,    15,    11,    12,    14,    14,    15,    16,    17,
      18,     6,    20,    21,    18,     6,     6,    14,    26,    15,
      56,    29,    30,    31,    32,    33,    34,    28,    28,     6,
      18,    18,    43,    23,    18,     6,    44,    45,    28,    25,
      43,    43,     6,    24,     6,    15,    23,     8,    56,    18,
      25,    28,     6,    61,    26,    15,    23,    15,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,     6,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    26,    15,     6,     6,     6,    15,
      28,    23,    28,    15,     6,    26,    28,    14,    14,    22,
       6,     6,     6,    14,    23,     6,    65,     6,    18,    28,
     228,   179,   185,   117,   152,   145,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     6,    15,    11,   134,    61,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,     6,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     6,    23,
      -1,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    23,    -1,    25,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      27,    28,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    23,    -1,    25,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    23,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,
      25,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    23,    -1,    -1,    -1,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    23,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    36,    37,    39,    67,     8,     8,     6,     0,     1,
       5,    92,    93,     1,    42,    90,    91,    40,     6,    15,
       9,    93,     6,    15,     9,    91,    28,     6,    15,    18,
      10,    43,    99,   100,     6,     6,     6,    14,    15,    17,
      18,    26,    56,    61,    87,     4,     7,    13,    46,   100,
     101,   102,   103,    43,    68,    14,    24,    26,    87,    87,
      87,     6,    23,    28,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,     6,     6,    15,
       6,   102,    87,    38,     6,    87,    86,    87,    27,    99,
      26,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    14,    14,     6,    87,     6,
      16,    29,    30,    31,    32,    33,    34,    69,    70,    71,
      72,    74,    75,    25,    47,    27,    47,   101,    18,    88,
      89,     6,     6,    14,    97,    98,     6,    15,    41,    70,
      15,    87,    87,    56,    27,    47,    43,    43,    28,     6,
      98,    43,    28,     6,    24,    26,    28,    25,    18,    89,
      87,    87,    18,    87,    88,    18,    71,    76,    77,    87,
       6,     6,     6,     6,     6,    25,    15,    64,    27,    47,
       6,     6,    24,    15,     6,    73,    77,    18,     8,    84,
      85,    25,     1,    11,    12,    20,    21,    35,    44,    45,
      71,    74,    78,    79,    81,    82,    83,    84,    87,    94,
       6,    26,    15,    15,    26,    15,     6,     6,    15,     9,
      79,     6,    87,    28,    14,    24,    87,    28,    26,     6,
      15,     6,    87,    27,    95,    76,    87,    26,    25,    47,
      79,    14,    96,    27,     6,    87,    14,    87,    22,     6,
       6,    14,    87,    47,     6,    25,    79,     6,    27,    87,
      14,    80,    27,     6,    79,    65,    18,     6
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
#line 234 "src/type.ypp"
    {	const char * c_arr="c";  
		rec_len=(yyvsp[(5) - (6)].ival); 
		active_scope->insert(c_arr, INT8_ARR_TYPE, rec_len, 0);
	;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 238 "src/type.ypp"
    {
		tree_root = trav_chain((yyvsp[(9) - (10)].stmt));
		if(tree_root==0){
			cerr << "tree_root =0 : core dump expected" << endl;
		}
		return 0;
	;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 245 "src/type.ypp"
    {
		return 0;
	;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 248 "src/type.ypp"
    {
		return 0;
	;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 253 "src/type.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 256 "src/type.ypp"
    {
		(yyval.stmt)=link_chain((yyvsp[(1) - (2)].stmt),(yyvsp[(2) - (2)].stmt));
	;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 261 "src/type.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 264 "src/type.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 279 "src/type.ypp"
    {
		string func_name_index((yyvsp[(2) - (5)].name));
		flag_cmpd_stmt_is_a_func_body=Util::lookup_func(func_name_index);
		if(flag_cmpd_stmt_is_a_func_body==-1){
			++ no_errors;
			cerr << "Function name not found in list of declared functions: "
				<< "You will see another error on this same function name: " << func_name_index
				<< "line_no: " << line_no  << endl;
		}
	;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 288 "src/type.ypp"
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
	;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 314 "src/type.ypp"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (3)].name), (yyvsp[(1) - (3)].dt)/*, line_no*/);
		free((yyvsp[(2) - (3)].name));
	;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 318 "src/type.ypp"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (5)].name), (yyvsp[(1) - (5)].dt), (yyvsp[(4) - (5)].expr));

	;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 322 "src/type.ypp"
    {
		/* NxD: I have ordered the types in DataType so that this hack is possible I hope */
		DataType dt=DataType(INT8_ARR_TYPE+((yyvsp[(1) - (6)].dt)-INT8_TYPE));
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (6)].name), dt, (yyvsp[(4) - (6)].ival)/*, line_no*/);
		free((yyvsp[(2) - (6)].name));
	;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 336 "src/type.ypp"
    {
		(yyval.stmt) = active_scope->insert((yyvsp[(2) - (5)].name), RANGE_DECL_STMT, &xs);
		//$$ = new decl_stmt($2, RANGE_DECL_STMT, &xs );
		xs.reset();
	;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 341 "src/type.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 347 "src/type.ypp"
    {
		char *name=(yyvsp[(2) - (6)].name);
		struct Statement::FunctionParameter* v_list=trav_chain((yyvsp[(4) - (6)].v_list));
		DataType returnType_=(yyvsp[(1) - (6)].dt);
		(yyval.stmt)=new Statement::FunctionDeclarationStatement( FUNC_TYPE, line_no, name,  v_list, returnType_);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 359 "src/type.ypp"
    {
		 (yyval.v_list)=(yyvsp[(1) - (1)].v_list);
		 //cout << "got decl_comma_list : " << endl;
	;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 363 "src/type.ypp"
    {
		(yyval.v_list)=link_chain((yyvsp[(1) - (3)].v_list),(yyvsp[(3) - (3)].v_list));
		//cout << "chaining var_decl : " << endl;
	;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 370 "src/type.ypp"
    {
		(yyval.v_list)=new Statement::FunctionParameter((yyvsp[(1) - (2)].dt), (yyvsp[(2) - (2)].name));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (2)].name));
	;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 377 "src/type.ypp"
    {
		/* Neil - I need to fix this */
		DataType dt=DataType(INT8_ARR_TYPE+((yyvsp[(1) - (5)].dt)-INT8_TYPE));
		(yyval.v_list)=new Statement::FunctionParameter(dt, (yyvsp[(2) - (5)].name), (yyvsp[(4) - (5)].ival));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (5)].name));
	;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 386 "src/type.ypp"
    {
		DataType dt=DataType(INT8_REF_TYPE+((yyvsp[(1) - (3)].dt)-INT8_TYPE));
		(yyval.v_list)=new Statement::FunctionParameter(dt, (yyvsp[(3) - (3)].name));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(3) - (3)].name));
	;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 395 "src/type.ypp"
    {
		(yyval.v_list)=0;
		;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 400 "src/type.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt); 
		if(flag_next_stmt_start_of_block){
			blk_heads.push_back((yyvsp[(1) - (1)].stmt));
			//cout << "blk_heads.size(): " << blk_heads.size() << endl;
			//start_of_blk=$1;
			flag_next_stmt_start_of_block=false;
			blk_start_flag.pop_back();
		}
	;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 410 "src/type.ypp"
    {
		(yyval.stmt)=link_chain((yyvsp[(1) - (2)].stmt),(yyvsp[(2) - (2)].stmt));
	;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 413 "src/type.ypp"
    {
		(yyval.stmt)=0;
	;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 418 "src/type.ypp"
    { ++in_a_loop;;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 418 "src/type.ypp"
    {
		(yyval.stmt) = new struct Statement::ForStatement(FOR_STMT, line_no, (yyvsp[(3) - (10)].expr), (yyvsp[(5) - (10)].expr), (yyvsp[(7) - (10)].expr), (yyvsp[(10) - (10)].stmt));
		--in_a_loop;
	;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 423 "src/type.ypp"
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
	;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 436 "src/type.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].c_stmt);
	;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 439 "src/type.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 443 "src/type.ypp"
    {
		(yyval.stmt)=new Statement::BreakStatement(BREAK_STMT, line_no, in_a_loop);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 449 "src/type.ypp"
    {
		(yyval.stmt)=new Statement::ContinueStatement(CONTINUE_STMT, line_no, in_a_loop);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 456 "src/type.ypp"
    {
		Util::print_err(Util::compiler_sem_err, "statement missing ';' around line_no: ", 
			line_no, __LINE__, __FILE__);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		(yyval.stmt) = new struct Statement::ErrorStatement(line_no);
		yyerrok;
	;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 467 "src/type.ypp"
    {
		(yyval.stmt)=new Statement::ListStatement(LISTA_BASIC_TYPE_STMT, (yyvsp[(2) - (4)].name), (yyvsp[(3) - (4)].text_buf));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (4)].name));
	;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 474 "src/type.ypp"
    {
		(yyval.stmt)=new Statement::ListStatement( LISTA_BASIC_ARRTYPE_STMT_1INDEX, (yyvsp[(2) - (7)].name), string((yyvsp[(6) - (7)].text_buf)), (yyvsp[(4) - (7)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (7)].name));
	;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 481 "src/type.ypp"
    {
		(yyval.stmt)=new Statement::ListStatement( LISTA_BASIC_ARRTYPE_STMT_1INDEX, (yyvsp[(2) - (9)].name), string((yyvsp[(8) - (9)].text_buf)), (yyvsp[(4) - (9)].expr), (yyvsp[(6) - (9)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (9)].name));	
	;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 490 "src/type.ypp"
    {
		(yyval.stmt)=new Statement::IfStatement(IFE_STMT,if_line_no,(yyvsp[(3) - (5)].expr),(yyvsp[(5) - (5)].stmt),0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 496 "src/type.ypp"
    {
		(yyval.stmt)=new Statement::IfStatement(IFE_STMT, if_line_no,(yyvsp[(3) - (7)].expr),(yyvsp[(5) - (7)].stmt),(yyvsp[(7) - (7)].stmt));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 504 "src/type.ypp"
    {
		Expression::AbstractExpression* start_col=(yyvsp[(6) - (12)].expr);
		Expression::AbstractExpression* end_col=(yyvsp[(8) - (12)].expr);
		int width=(yyvsp[(11) - (12)].ival);
		(yyval.stmt) = new Statement::FieldStatement((yyvsp[(2) - (12)].name), (yyvsp[(4) - (12)].name), start_col, end_col, width);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (12)].name)), free((yyvsp[(4) - (12)].name));
	;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 516 "src/type.ypp"
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
	;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 550 "src/type.ypp"
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
	;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 574 "src/type.ypp"
    { (yyval.expr)=(yyvsp[(1) - (1)].expr); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 575 "src/type.ypp"
    {
		(yyval.expr)=link_chain((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));
	;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 580 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_plus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 586 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_minus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 592 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_mult);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 598 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_div);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 604 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_mod);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 610 "src/type.ypp"
    {
		(yyval.expr) = new Expression::UnaryExpression((yyvsp[(2) - (2)].expr), Expression::oper_umin);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 616 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_lt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 622 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_gt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 628 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_le);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 634 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_ge);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 640 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_iseq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 646 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_isneq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 652 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_or);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 658 "src/type.ypp"
    {
		(yyval.expr)=new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_and);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 664 "src/type.ypp"
    {
		(yyval.expr) = new Expression::BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), Expression::oper_assgn);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 670 "src/type.ypp"
    {
		(yyval.expr) = new Expression::UnaryExpression((yyvsp[(2) - (2)].expr), Expression::oper_not);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 676 "src/type.ypp"
    {
		(yyval.expr) = new Expression::Unary2Expression((yyvsp[(1) - (1)].ival));
		//cout << "got INUMBER: " << $1 << " type : " << $$->type << endl;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 683 "src/type.ypp"
    {
		(yyval.expr) = new Expression::Unary2Expression((yyvsp[(1) - (1)].dval));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 689 "src/type.ypp"
    {
		(yyval.expr) = new Expression::Unary2Expression((yyvsp[(1) - (1)].name), Expression::oper_name );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 695 "src/type.ypp"
    {
		(yyval.expr) = new Expression::Unary2Expression (Expression::oper_arrderef, /*nametype,  se,*/ (yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(1) - (4)].name));
	;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 702 "src/type.ypp"
    {
		(yyval.expr) = new Expression::Unary2Expression(Expression::oper_blk_arr_assgn, (yyvsp[(1) - (6)].name),(yyvsp[(3) - (6)].expr),(yyvsp[(5) - (6)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(1) - (6)].name));
	;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 709 "src/type.ypp"
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
	;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 748 "src/type.ypp"
    {
		(yyval.expr) = new Expression::Unary2Expression(strdup((yyvsp[(1) - (1)].text_buf)), Expression::oper_text_expr);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 754 "src/type.ypp"
    { 
		(yyval.expr) = new Expression::UnaryExpression((yyvsp[(2) - (3)].expr), Expression::oper_parexp );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 760 "src/type.ypp"
    {
		(yyval.expr) = new Expression::Binary2Expression((yyvsp[(1) - (5)].expr), xs, Expression::oper_in);
		xs.reset();
	;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 778 "src/type.ypp"
    {
		if((yyvsp[(3) - (3)].ival)<=(yyvsp[(1) - (3)].ival)){
			print_err(Util::compiler_sem_err, "2nd number in range <= 1st number",
					line_no, __LINE__, __FILE__  );

		} else {
			xs.range.push_back( pair<int,int>((yyvsp[(1) - (3)].ival),(yyvsp[(3) - (3)].ival)));
		}
	;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 787 "src/type.ypp"
    {
		xs.indiv.insert((yyvsp[(1) - (1)].ival));
	;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 792 "src/type.ypp"
    { 
#ifdef DEBUG_GRAM
	printf("got table defn\n"); 
#endif
	;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 797 "src/type.ypp"
    { 
#ifdef DEBUG_GRAM
		printf("recursive tab_defn\n"); 
#endif
	;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 805 "src/type.ypp"
    {
		(yyval.tbl)=new Table::table((yyvsp[(2) - (4)].name),(yyvsp[(3) - (4)].name), line_no);
		table_list.push_back((yyval.tbl));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.tbl), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (4)].name)); free((yyvsp[(3) - (4)].name));
	;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 813 "src/type.ypp"
    {
		(yyval.tbl)=new Table::table((yyvsp[(2) - (7)].name),(yyvsp[(3) - (7)].name), line_no, (yyvsp[(6) - (7)].expr));
		table_list.push_back((yyval.tbl));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.tbl), __LINE__, __FILE__, line_no);
		}
		free((yyvsp[(2) - (7)].name)); free((yyvsp[(3) - (7)].name));
	;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 821 "src/type.ypp"
    {
		cerr << "Error in tab section line: " <<
			line_no << endl;
		++no_errors;
	;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 828 "src/type.ypp"
    {
	;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 830 "src/type.ypp"
    {
	;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 834 "src/type.ypp"
    {
		using Table::AbstractPrintableAxisStatement;
		using Table::AbstractCountableAxisStatement;
		Table::AbstractPrintableAxisStatement  * ttl_stmt_ptr= trav_chain((yyvsp[(4) - (5)].print_stmt));
		Table::AbstractCountableAxisStatement * count_stmt_ptr= trav_chain((yyvsp[(5) - (5)].count_stmt));

		(yyval.ax) = new Table::ax(ttl_stmt_ptr, count_stmt_ptr, 
				no_count_ax_elems, 
				no_tot_ax_elems, 
				no_inc_ax_elems,
				0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.ax), __LINE__, __FILE__, line_no);
		}
		
		ax_map[(yyvsp[(2) - (5)].name)]=(yyval.ax);
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		free((yyvsp[(2) - (5)].name));
	;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 855 "src/type.ypp"
    {
		Table::AbstractPrintableAxisStatement * ttl_stmt_ptr= trav_chain((yyvsp[(7) - (8)].print_stmt));
		Table::AbstractCountableAxisStatement * count_stmt_ptr= trav_chain((yyvsp[(8) - (8)].count_stmt));
		(yyval.ax) = new Table::ax(ttl_stmt_ptr, count_stmt_ptr, 
				no_count_ax_elems, 
				no_tot_ax_elems, 
				no_inc_ax_elems,
				(yyvsp[(5) - (8)].expr));
		
		std::cout << "got axis: " << (yyvsp[(2) - (8)].name) 
			<< "no_tot_ax_elems: " << no_tot_ax_elems 
			<< ", no_count_ax_elems: " << no_count_ax_elems
			<< endl;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.ax), __LINE__, __FILE__, line_no);
		}
		ax_map[(yyvsp[(2) - (8)].name)]=(yyval.ax);
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		no_inc_ax_elems = 0;
		free((yyvsp[(2) - (8)].name));
	;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 877 "src/type.ypp"
    {
		cerr << "Error in axis section line: " <<
			line_no << endl;
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		++no_errors;
	;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 886 "src/type.ypp"
    {
		attribute_list.resize(0);
		//cout << "resize attribute_list to 0\n";
	;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 889 "src/type.ypp"
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
	;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 910 "src/type.ypp"
    {
		string s1=(yyvsp[(1) - (2)].text_buf);
		attribute_list.push_back(s1);
	;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 914 "src/type.ypp"
    {
		string s1=(yyvsp[(2) - (3)].text_buf);
		attribute_list.push_back(s1);
        ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 921 "src/type.ypp"
    {
		//$$=link_chain($1, $2);
	;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 926 "src/type.ypp"
    {
		using Table::stub;
		(yyval.stub)=new stub((yyvsp[(1) - (4)].text_buf), (yyvsp[(3) - (4)].ival));
		stub_list.push_back((yyval.stub));
		++ no_count_ax_elems;
		++ no_tot_ax_elems;
	;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 935 "src/type.ypp"
    { (yyval.print_stmt)=(yyvsp[(1) - (1)].print_stmt); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 936 "src/type.ypp"
    {
		(yyval.print_stmt)=link_chain((yyvsp[(1) - (2)].print_stmt), (yyvsp[(2) - (2)].print_stmt));
	;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 941 "src/type.ypp"
    {
		using Table::TitleStatement;
		(yyval.print_stmt) = new TitleStatement (Table::txt_axstmt,(yyvsp[(3) - (4)].text_buf));
		++no_tot_ax_elems;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.print_stmt), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 951 "src/type.ypp"
    {
		(yyval.count_stmt) = (yyvsp[(1) - (1)].count_stmt);
	;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 954 "src/type.ypp"
    {
		(yyval.count_stmt)=link_chain((yyvsp[(1) - (2)].count_stmt), (yyvsp[(2) - (2)].count_stmt));
	;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 959 "src/type.ypp"
    {
		using Table::tot_ax_stmt;
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		int position = no_count_ax_elems-1;
		(yyval.count_stmt) = new tot_ax_stmt (Table::tot_axstmt,(yyvsp[(3) - (4)].text_buf), 0, position);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.count_stmt), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 969 "src/type.ypp"
    {
		using Table::tot_ax_stmt;
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.count_stmt) = new tot_ax_stmt (Table::tot_axstmt,(yyvsp[(3) - (7)].text_buf), (yyvsp[(6) - (7)].expr), no_count_ax_elems);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.count_stmt), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 978 "src/type.ypp"
    {
		using Table::count_ax_stmt;
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		(yyval.count_stmt) = new count_ax_stmt (Table::cnt_axstmt,(yyvsp[(3) - (7)].text_buf), (yyvsp[(6) - (7)].expr));
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.count_stmt), __LINE__, __FILE__, line_no);
		}
	;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 987 "src/type.ypp"
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
	;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1001 "src/type.ypp"
    {
		using Table::fld_ax_stmt;
		//stub * stub_ptr = trav_chain($4);
	 	//$$ = new fld_ax_stmt ($2, stub_ptr);
	 	(yyval.count_stmt) = new fld_ax_stmt (Table::fld_axstmt, (yyvsp[(2) - (5)].name), stub_list);
		stub_list.resize(0);
	;}
    break;



/* Line 1455 of yacc.c  */
#line 3067 "src/type.cpp"
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
#line 1010 "src/type.ypp"



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


