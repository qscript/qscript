
/*  A Bison parser, made from type.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define	CONVERT	257
#define	TOT	258
#define	AX	259
#define	CNT	260
#define	TTL	261
#define	FOR	262
#define	TEXT	263
#define	NAME	264
#define	FNUMBER	265
#define	INUMBER	266
#define	CODELIST	267
#define	LISTA	268
#define	IF	269
#define	ELSE	270
#define	VOID_T	271
#define	U_INT8_T	272
#define	INT8_T	273
#define	U_INT16_T	274
#define	INT16_T	275
#define	U_INT32_T	276
#define	INT32_T	277
#define	FLOAT_T	278
#define	DOUBLE_T	279
#define	AXSTART	280
#define	TABSTART	281
#define	ED_START	282
#define	DATA_STRUCT	283
#define	REC_LEN	284
#define	ED_END	285
#define	TAB	286
#define	COND_START	287
#define	CONTINUE	288
#define	BREAK	289
#define	LOGOR	290
#define	LOGAND	291
#define	ISEQ	292
#define	NOEQ	293
#define	LEQ	294
#define	GEQ	295
#define	NOT	296
#define	UMINUS	297
#define	FUNC_CALL	298

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
			{	"u_int8_t" ,U_INT8_TYPE},
			{	"int8_t" ,INT8_TYPE},
			{	"u_int16_t",U_INT16_TYPE},
			{	"int16_t" ,INT16_TYPE},
			{	"u_int32_t",U_INT32_TYPE},
			{	"int32_t" ,INT32_TYPE},
			{	"float", FLOAT_TYPE},
			{	"double", DOUBLE_TYPE}
		};
	vector<mem_addr_tab>  mem_addr;

	void flex_finish();


#line 104 "type.y"
typedef union {
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
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		206
#define	YYFLAG		-32768
#define	YYNTBASE	62

#define YYTRANSLATE(x) ((unsigned)(x) <= 298 ? yytranslate[x] : 88)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,    57,    61,     2,    22,
    23,    55,    54,    44,    53,     2,    56,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     6,    51,
    24,    52,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    20,     2,    21,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     8,     2,     9,     2,     2,     2,     2,     2,
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
     2,     2,     2,     2,     2,     1,     3,     4,     5,     7,
    10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
    25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
    35,    36,    37,    38,    39,    40,    41,    42,    43,    45,
    46,    47,    48,    49,    50,    58,    59,    60
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,    12,    17,    22,    24,    27,    29,    31,    33,
    35,    37,    39,    41,    43,    45,    47,    49,    50,    58,
    62,    69,    71,    78,    80,    84,    87,    93,    97,    98,
   100,   103,   104,   115,   117,   120,   122,   124,   126,   129,
   132,   135,   140,   148,   158,   164,   172,   176,   178,   180,
   184,   188,   192,   196,   200,   204,   207,   211,   215,   219,
   223,   227,   231,   235,   239,   243,   246,   248,   250,   252,
   257,   264,   269,   271,   275,   277,   280,   285,   293,   296,
   298,   301,   306,   314,   317,   319,   322,   327,   335,   343
};

static const short yyrhs[] = {    -1,
    37,     6,    38,    24,    15,     6,    63,    36,    64,    39,
     0,    34,     8,    84,     9,     0,    35,     8,    82,     9,
     0,    65,     0,    64,    65,     0,    69,     0,    67,     0,
    25,     0,    26,     0,    27,     0,    28,     0,    29,     0,
    30,     0,    31,     0,    32,     0,    33,     0,     0,    66,
    13,    22,    71,    23,    68,    78,     0,    66,    13,     6,
     0,    66,    13,    20,    15,    21,     6,     0,    70,     0,
    66,    13,    22,    71,    23,     6,     0,    72,     0,    71,
    44,    72,     0,    66,    13,     0,    66,    13,    20,    15,
    21,     0,    66,    61,    13,     0,     0,    74,     0,    73,
    74,     0,     0,    11,    22,    81,     6,    81,     6,    81,
    23,    75,    74,     0,    77,     0,    81,     6,     0,    78,
     0,    69,     0,    76,     0,    43,     6,     0,    42,     6,
     0,     1,     6,     0,    17,    13,    12,     6,     0,    17,
    13,    20,    15,    21,    12,     6,     0,    17,    13,    20,
    15,    44,    15,    21,    12,     6,     0,    18,    22,    81,
    23,    74,     0,    18,    22,    81,    23,    74,    19,    74,
     0,    79,    73,     9,     0,     8,     0,    81,     0,    80,
    44,    81,     0,    81,    54,    81,     0,    81,    53,    81,
     0,    81,    55,    81,     0,    81,    56,    81,     0,    81,
    57,    81,     0,    53,    81,     0,    81,    51,    81,     0,
    81,    52,    81,     0,    81,    49,    81,     0,    81,    50,
    81,     0,    81,    47,    81,     0,    81,    48,    81,     0,
    81,    45,    81,     0,    81,    46,    81,     0,    81,    24,
    81,     0,    58,    81,     0,    15,     0,    14,     0,    13,
     0,    13,    20,    81,    21,     0,    13,    20,    81,    44,
    81,    21,     0,    13,    22,    80,    23,     0,    12,     0,
    22,    81,    23,     0,    83,     0,    82,    83,     0,    40,
    13,    13,     6,     0,    40,    13,    13,     6,    41,    81,
     6,     0,     1,     6,     0,    85,     0,    84,    85,     0,
     5,    13,     6,    86,     0,     5,    13,     6,    41,    81,
     6,    86,     0,     1,     6,     0,    87,     0,    86,    87,
     0,     4,     6,    12,     6,     0,     4,     6,    12,     6,
    41,    81,     6,     0,     7,     6,    12,     6,    41,    81,
     6,     0,    10,     6,    12,     6,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   201,   206,   213,   216,   221,   224,   229,   232,   237,   238,
   239,   240,   241,   242,   243,   244,   245,   249,   259,   287,
   292,   307,   313,   327,   331,   338,   346,   356,   365,   372,
   380,   385,   385,   402,   403,   417,   420,   423,   424,   434,
   444,   455,   484,   514,   542,   557,   575,   606,   634,   635,
   640,   647,   654,   661,   668,   682,   693,   700,   707,   714,
   721,   728,   735,   742,   749,   768,   779,   786,   792,   809,
   849,   906,   945,   951,   959,   964,   971,   982,   991,   999,
  1001,  1005,  1020,  1034,  1044,  1048,  1053,  1058,  1063,  1068
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","CONVERT",
"TOT","AX","';'","CNT","'{'","'}'","TTL","FOR","TEXT","NAME","FNUMBER","INUMBER",
"CODELIST","LISTA","IF","ELSE","'['","']'","'('","')'","'='","VOID_T","U_INT8_T",
"INT8_T","U_INT16_T","INT16_T","U_INT32_T","INT32_T","FLOAT_T","DOUBLE_T","AXSTART",
"TABSTART","ED_START","DATA_STRUCT","REC_LEN","ED_END","TAB","COND_START","CONTINUE",
"BREAK","','","LOGOR","LOGAND","ISEQ","NOEQ","LEQ","GEQ","'<'","'>'","'-'","'+'",
"'*'","'/'","'%'","NOT","UMINUS","FUNC_CALL","'&'","prog","@1","top_level_item_list",
"top_level_item","xtcc_type","func_defn","@2","decl","func_decl","decl_comma_list",
"var_decl","statement_list","statement","@3","list_stmt","if_stmt","compound_stmt",
"open_curly","expr_list","expression","tab_list","tab_defn","ax_list","ax_defn",
"ax_stmt_list","ax_stmt", NULL
};
#endif

static const short yyr1[] = {     0,
    63,    62,    62,    62,    64,    64,    65,    65,    66,    66,
    66,    66,    66,    66,    66,    66,    66,    68,    67,    69,
    69,    69,    70,    71,    71,    72,    72,    72,    72,    73,
    73,    75,    74,    74,    74,    74,    74,    74,    74,    74,
    74,    76,    76,    76,    77,    77,    78,    79,    80,    80,
    81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
    81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
    81,    81,    81,    81,    82,    82,    83,    83,    83,    84,
    84,    85,    85,    85,    86,    86,    87,    87,    87,    87
};

static const short yyr2[] = {     0,
     0,    10,     4,     4,     1,     2,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     0,     7,     3,
     6,     1,     6,     1,     3,     2,     5,     3,     0,     1,
     2,     0,    10,     1,     2,     1,     1,     1,     2,     2,
     2,     4,     7,     9,     5,     7,     3,     1,     1,     3,
     3,     3,     3,     3,     3,     2,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     2,     1,     1,     1,     4,
     6,     4,     1,     3,     1,     2,     4,     7,     2,     1,
     2,     4,     7,     2,     1,     2,     4,     7,     7,     4
};

static const short yydefact[] = {     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
     0,     0,     0,    75,     0,    84,     0,     3,    81,    79,
     0,     4,    76,     0,     0,     0,     0,     0,     0,     0,
     0,    82,    85,    77,     1,     0,     0,     0,    73,    69,
    68,    67,     0,     0,     0,     0,    86,     0,     0,     0,
     0,     0,     0,     0,     0,    56,    66,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    87,     0,    90,     0,     0,    49,
    74,    83,    65,    63,    64,    61,    62,    59,    60,    57,
    58,    52,    51,    53,    54,    55,    78,     9,    10,    11,
    12,    13,    14,    15,    16,    17,     0,     5,     0,     8,
     7,    22,     0,     0,    70,     0,    72,     0,     2,     6,
     0,     0,     0,     0,    50,    20,     0,    29,    88,    89,
    71,     0,     0,     0,    24,     0,    26,     0,    18,    29,
    21,     0,    28,    23,     0,    25,     0,    48,    19,     0,
    27,     0,     0,     0,     0,     0,     0,     0,    37,     0,
    30,    38,    34,    36,     0,    41,     0,     0,     0,    40,
    39,     0,    47,    31,    35,     0,     0,     0,     0,    29,
     0,    42,     0,     0,     0,     0,     0,     0,    45,     0,
     0,     0,     0,     0,     0,    43,     0,    46,    32,     0,
     0,    44,    33,     0,     0,     0
};

static const short yydefgoto[] = {   204,
    49,   107,   108,   158,   110,   145,   159,   112,   134,   135,
   160,   161,   201,   162,   163,   164,   150,    79,   165,    13,
    14,     9,    10,    32,    33
};

static const short yypact[] = {   -16,
    -7,     2,    -3,    15,     3,   -11,    55,    49,   130,-32768,
    82,    76,    70,-32768,    74,-32768,   105,-32768,-32768,-32768,
   101,-32768,-32768,   110,    86,   134,   136,   137,   139,   141,
    54,   122,-32768,    96,-32768,   144,   147,   151,-32768,   108,
-32768,-32768,    54,    54,    54,     0,-32768,    54,   128,   169,
   170,   171,    54,    54,   383,-32768,-32768,   122,    54,    54,
    54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
    54,    54,   155,   286,   148,   149,-32768,   335,   -18,   444,
-32768,   122,   444,   199,   245,   311,   311,   131,   131,   131,
   131,    17,    17,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   202,-32768,   133,-32768,
-32768,-32768,    54,    54,-32768,    54,-32768,    54,-32768,-32768,
    58,   168,   220,   348,   444,-32768,   163,   286,-32768,-32768,
-32768,   159,    -2,    42,-32768,   175,   174,   178,   189,   286,
-32768,   181,-32768,-32768,   191,-32768,   176,-32768,-32768,   140,
-32768,   230,   215,   225,   218,   236,   237,   246,-32768,    91,
-32768,-32768,-32768,-32768,   233,-32768,    54,    -5,    54,-32768,
-32768,    75,-32768,-32768,-32768,   285,   252,   247,   396,   286,
    54,-32768,   -19,   140,    47,   298,   248,   249,   242,   189,
    54,   257,   282,   140,   431,-32768,   293,-32768,-32768,   300,
   140,-32768,-32768,   307,   308,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,   203,   -65,-32768,-32768,   -30,-32768,   143,   180,
-32768,  -100,-32768,-32768,-32768,   179,-32768,-32768,   -31,-32768,
   312,-32768,   317,   263,   -24
};


#define	YYLAST		501


static const short yytable[] = {    46,
     4,   187,     6,    11,   117,    58,   177,    47,   109,     5,
   137,    55,    56,    57,   178,     7,    73,     1,     2,     8,
     3,    78,    80,    59,   188,   118,    15,    83,    84,    85,
    86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
    96,   109,    12,   111,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    47,   138,   174,
    16,    17,   133,   126,   139,    39,    40,    41,    42,   190,
    11,    70,    71,    72,   133,    43,   111,   127,    22,   128,
   126,   122,   123,   189,   124,   140,   125,    20,    21,    28,
   140,   152,    29,   198,   127,    30,   180,    24,   148,   173,
   203,   153,    39,    40,    41,    42,    44,   154,   155,    12,
    25,    45,    43,    26,   133,    98,    99,   100,   101,   102,
   103,   104,   105,   106,    27,    28,    31,    53,    29,    54,
     7,    30,   156,   157,     8,   176,    48,   179,    18,    34,
   152,    35,    36,    44,    37,   121,    38,   148,    45,   186,
   153,    39,    40,    41,    42,    50,   154,   155,    51,   195,
    97,    43,    52,    74,    98,    99,   100,   101,   102,   103,
   104,   105,   106,   129,    75,    76,    77,   132,    59,   136,
   141,   156,   157,    68,    69,    70,    71,    72,   113,   114,
   143,    59,    44,   142,   144,   147,   151,    45,   148,    60,
    61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
    71,    72,    60,    61,    62,    63,    64,    65,    66,    67,
    68,    69,    70,    71,    72,   130,    98,    99,   100,   101,
   102,   103,   104,   105,   106,   166,   167,   168,   175,   169,
   119,   170,   171,    59,    61,    62,    63,    64,    65,    66,
    67,    68,    69,    70,    71,    72,    59,   182,   172,   192,
   194,   183,   196,   193,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    60,    61,    62,
    63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
   181,    62,    63,    64,    65,    66,    67,    68,    69,    70,
    71,    72,   197,   191,   200,   202,   205,   206,    59,   120,
    98,    99,   100,   101,   102,   103,   104,   105,   106,   146,
    82,    59,   185,   149,    23,    19,     0,     0,     0,    60,
    61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
    71,    72,    60,    61,    62,    63,    64,    65,    66,    67,
    68,    69,    70,    71,    72,   115,     0,     0,    59,    64,
    65,    66,    67,    68,    69,    70,    71,    72,   131,     0,
     0,    59,     0,     0,     0,     0,     0,     0,   116,    60,
    61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
    71,    72,    60,    61,    62,    63,    64,    65,    66,    67,
    68,    69,    70,    71,    72,    81,    59,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   184,    59,
     0,     0,     0,     0,     0,     0,     0,    60,    61,    62,
    63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
    60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
    70,    71,    72,   199,    59,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    59,     0,     0,
     0,     0,     0,     0,     0,    60,    61,    62,    63,    64,
    65,    66,    67,    68,    69,    70,    71,    72,    60,    61,
    62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
    72
};

static const short yycheck[] = {    31,
     8,    21,     6,     1,    23,     6,    12,    32,    74,     8,
    13,    43,    44,    45,    20,     1,    48,    34,    35,     5,
    37,    53,    54,    24,    44,    44,    38,    59,    60,    61,
    62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
    72,   107,    40,    74,    45,    46,    47,    48,    49,    50,
    51,    52,    53,    54,    55,    56,    57,    82,    61,   160,
     6,    13,   128,     6,    23,    12,    13,    14,    15,    23,
     1,    55,    56,    57,   140,    22,   107,    20,     9,    22,
     6,   113,   114,   184,   116,    44,   118,     6,    13,     4,
    44,     1,     7,   194,    20,    10,    22,    24,     8,     9,
   201,    11,    12,    13,    14,    15,    53,    17,    18,    40,
     6,    58,    22,    13,   180,    25,    26,    27,    28,    29,
    30,    31,    32,    33,    15,     4,    41,    20,     7,    22,
     1,    10,    42,    43,     5,   167,    41,   169,     9,     6,
     1,     6,     6,    53,     6,    13,     6,     8,    58,   181,
    11,    12,    13,    14,    15,    12,    17,    18,    12,   191,
     6,    22,    12,    36,    25,    26,    27,    28,    29,    30,
    31,    32,    33,     6,     6,     6,     6,    15,    24,    21,
     6,    42,    43,    53,    54,    55,    56,    57,    41,    41,
    13,    24,    53,    20,     6,    15,    21,    58,     8,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    45,    46,    47,    48,    49,    50,    51,    52,
    53,    54,    55,    56,    57,     6,    25,    26,    27,    28,
    29,    30,    31,    32,    33,     6,    22,    13,     6,    22,
    39,     6,     6,    24,    46,    47,    48,    49,    50,    51,
    52,    53,    54,    55,    56,    57,    24,     6,    13,    12,
    19,    15,     6,    15,    45,    46,    47,    48,    49,    50,
    51,    52,    53,    54,    55,    56,    57,    45,    46,    47,
    48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
     6,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    21,     6,    12,     6,     0,     0,    24,   107,
    25,    26,    27,    28,    29,    30,    31,    32,    33,   140,
    58,    24,   180,   145,    13,     9,    -1,    -1,    -1,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    45,    46,    47,    48,    49,    50,    51,    52,
    53,    54,    55,    56,    57,    21,    -1,    -1,    24,    49,
    50,    51,    52,    53,    54,    55,    56,    57,    21,    -1,
    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    45,    46,    47,    48,    49,    50,    51,    52,
    53,    54,    55,    56,    57,    23,    24,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
    48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
    45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
    55,    56,    57,    23,    24,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
    50,    51,    52,    53,    54,    55,    56,    57,    45,    46,
    47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

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

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/local/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 202 "type.y"
{	char * c_arr="c";  
		rec_len=yyvsp[-1].ival; 
		active_scope->insert(c_arr, INT8_ARR_TYPE, rec_len, 0);
	;
    break;}
case 2:
#line 206 "type.y"
{
		tree_root = trav_chain(yyvsp[-1].stmt);
		if(tree_root==0){
			cerr << "tree_root =0 : core dump expected" << endl;
		}
		return 0;
	;
    break;}
case 3:
#line 213 "type.y"
{
		return 0;
	;
    break;}
case 4:
#line 216 "type.y"
{
		return 0;
	;
    break;}
case 5:
#line 221 "type.y"
{
		yyval.stmt=yyvsp[0].stmt;
	;
    break;}
case 6:
#line 224 "type.y"
{
		yyval.stmt=link_chain(yyvsp[-1].stmt,yyvsp[0].stmt);
	;
    break;}
case 7:
#line 229 "type.y"
{
			yyval.stmt=yyvsp[0].stmt;
	;
    break;}
case 8:
#line 232 "type.y"
{
		yyval.stmt=yyvsp[0].stmt;
	;
    break;}
case 18:
#line 250 "type.y"
{
		string func_name_index(yyvsp[-3].name);
		flag_cmpd_stmt_is_a_func_body=lookup_func(func_name_index);
		if(flag_cmpd_stmt_is_a_func_body==-1){
			++ no_errors;
			cerr << "Function name not found in list of declared functions: "
				<< "You will see another error on this same function name: " << func_name_index
				<< "line_no: " << line_no  << endl;
		}
	;
    break;}
case 19:
#line 259 "type.y"
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
		/*$$=new func_stmt(FUNC_DEFN, line_no, sc, v_list, cmpd_stmt, search_for, return_type);
			// This gives an error - we have to fool the compiler*/
		yyval.stmt=new func_stmt(FUNC_DEFN, line_no, sc, v_list, func_body, search_for, return_type);
		void *ptr=yyval.stmt;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		// Note that the declaration already has a parameter list
		// the constructor uses the parameter list - name and type to verify everything
		// but doesnt need the parameter list any more - so we should delete it 
		// - took me a while to figure out this memory leak
		delete v_list;
		free(yyvsp[-5].name);
	;
    break;}
case 20:
#line 287 "type.y"
{
		//cout << "creating simple var of type: " << $1 << endl;
		yyval.stmt = active_scope->insert(yyvsp[-1].name, yyvsp[-2].dt, line_no);
		free(yyvsp[-1].name);
	;
    break;}
case 21:
#line 292 "type.y"
{
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		//cout << "creating arr var of type: " << $1 << endl;
		datatype dt=datatype(U_INT8_ARR_TYPE+(yyvsp[-5].dt-U_INT8_TYPE));
		yyval.stmt = active_scope->insert(yyvsp[-4].name, dt, yyvsp[-2].ival, line_no);
		free(yyvsp[-4].name);
	;
    break;}
case 22:
#line 307 "type.y"
{
		yyval.stmt=yyvsp[0].stmt;
	;
    break;}
case 23:
#line 313 "type.y"
{
		char *name=yyvsp[-4].name;
		//char *name=strdup($2);
		struct var_list* v_list=trav_chain(yyvsp[-2].v_list);
		datatype return_type=yyvsp[-5].dt;
		yyval.stmt=new func_decl_stmt( FUNC_TYPE, line_no, name,  v_list, return_type);
		void *ptr=yyval.stmt;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		//free(name);
	;
    break;}
case 24:
#line 327 "type.y"
{
		 yyval.v_list=yyvsp[0].v_list;
		 //cout << "got decl_comma_list : " << endl;
	;
    break;}
case 25:
#line 331 "type.y"
{
		yyval.v_list=link_chain(yyvsp[-2].v_list,yyvsp[0].v_list);
		//cout << "chaining var_decl : " << endl;
	;
    break;}
case 26:
#line 338 "type.y"
{
		//cout << "creating simple var of type: " << $1 << endl;
		yyval.v_list=new var_list(yyvsp[-1].dt, yyvsp[0].name);
		void *ptr=yyval.v_list;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		free(yyvsp[0].name);
	;
    break;}
case 27:
#line 346 "type.y"
{
		/* Neil - I need to fix this */
		//cout << "creating arr var of type: " << $1 << endl;
		datatype dt=datatype(U_INT8_ARR_TYPE+(yyvsp[-4].dt-U_INT8_TYPE));
		yyval.v_list=new var_list(dt, yyvsp[-3].name, yyvsp[-1].ival);
		void *ptr=yyval.v_list;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		free(yyvsp[-3].name);
	;
    break;}
case 28:
#line 356 "type.y"
{
		//cout << "creating ref var of type: " << $1 << endl;
		datatype dt=datatype(U_INT8_REF_TYPE+(yyvsp[-2].dt-U_INT8_TYPE));
		yyval.v_list=new var_list(dt, yyvsp[0].name);
		void *ptr=yyval.v_list;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		free(yyvsp[0].name);
	;
    break;}
case 29:
#line 366 "type.y"
{
		//$$=new var_list(uninit, "empty");
		yyval.v_list=0;
		;
    break;}
case 30:
#line 372 "type.y"
{
		yyval.stmt=yyvsp[0].stmt; 
		if(flag_next_stmt_start_of_block){
			blk_heads.push_back(yyvsp[0].stmt);
			//start_of_blk=$1;
			flag_next_stmt_start_of_block=false;
		}
	;
    break;}
case 31:
#line 380 "type.y"
{
		yyval.stmt=link_chain(yyvsp[-1].stmt,yyvsp[0].stmt);
	;
    break;}
case 32:
#line 385 "type.y"
{ ++in_a_loop;;
    break;}
case 33:
#line 385 "type.y"
{
		   if(yyvsp[-7].expr->type==VOID_TYPE||yyvsp[-5].expr->type==VOID_TYPE||yyvsp[-3].expr->type==VOID_TYPE 
			){
			   cerr << "For condition has VOID_TYPE or ERROR_TYPE" << endl;
			   ++ no_errors;
			   yyval.stmt=new struct err_stmt(line_no);
			   void *ptr=yyval.stmt;
			   mem_addr_tab m1(ptr, line_no);
			   mem_addr.push_back(m1);
		   } else{
			   yyval.stmt = new struct for_stmt(FOR_STMT, line_no, yyvsp[-7].expr, yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[0].stmt);
			   void *ptr=yyval.stmt;
			   mem_addr_tab m1(ptr, line_no);
			   mem_addr.push_back(m1);
		   }
		   --in_a_loop;
	;
    break;}
case 35:
#line 403 "type.y"
{ 
		if(yyvsp[-1].expr->isvalid()){
			yyval.stmt = new expr_stmt(TEXPR_STMT, line_no, yyvsp[-1].expr);
			void *ptr=yyval.stmt;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			yyval.stmt = new expr_stmt(ERROR_TYPE, line_no, yyvsp[-1].expr);
			void *ptr=yyval.stmt;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		}
		//printf("= %g\n", $1); 
	;
    break;}
case 36:
#line 417 "type.y"
{
		yyval.stmt=yyvsp[0].c_stmt;
	;
    break;}
case 37:
#line 420 "type.y"
{
		yyval.stmt=yyvsp[0].stmt;
	;
    break;}
case 39:
#line 424 "type.y"
{
		yyval.stmt=new struct break_stmt(BREAK_STMT, line_no);
		void *ptr=yyval.stmt;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if (!in_a_loop){
			cerr << "break statement outside a loop: line_no: " << line_no<< endl;
			++no_errors;
		}
	;
    break;}
case 40:
#line 434 "type.y"
{
		yyval.stmt=new struct continue_stmt(CONTINUE_STMT, line_no);
		void *ptr=yyval.stmt;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if (!in_a_loop){
			cerr << "continue statement outside a loop: line_no: " << line_no<< endl;
			++no_errors;
		}
	;
    break;}
case 41:
#line 444 "type.y"
{
		cerr << "statement missing ';' around line_no: " << line_no << endl;
		++no_errors;
		yyval.stmt = new struct err_stmt(line_no);
		void *ptr=yyval.stmt;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		yyerrok;
	;
    break;}
case 42:
#line 455 "type.y"
{
		map<string,symtab_ent*>::iterator sym_it = find_in_symtab(yyvsp[-2].name);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << yyvsp[-2].name << " not found in symbol table" << endl;
			++no_errors;
			yyval.stmt=new err_stmt(line_no);
			void *ptr=yyval.stmt;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->type;
			if( !(name_type>=INT8_TYPE&&name_type<=DOUBLE_TYPE)){
				cerr << "NAME: "<< yyvsp[-2].name 
					<< " should be of basic type: " << line_no << endl;
				++no_errors;
				yyval.stmt=new struct err_stmt(line_no);
				void *ptr=yyval.stmt;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			} else {
				yyval.stmt=new list_stmt(LISTA_BASIC_TYPE_STMT, line_no, se);
				void *ptr=yyval.stmt;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
		free(yyvsp[-2].name);
	;
    break;}
case 43:
#line 484 "type.y"
{
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab(yyvsp[-5].name);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << yyvsp[-5].name << " not found in symbol table" << endl;
			++no_errors;
			yyval.stmt=new err_stmt(line_no);
			void *ptr=yyval.stmt;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->type;
			if( !(name_type>=INT8_ARR_TYPE&&name_type<=DOUBLE_ARR_TYPE)){
				cerr << "NAME: "<< yyvsp[-5].name 
					<< " is not of array type: line_no:" << line_no << endl;
				++no_errors;
				yyval.stmt=new err_stmt(line_no);
				void *ptr=yyval.stmt;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			} else {
				yyval.stmt=new list_stmt( LISTA_BASIC_ARRTYPE_STMT_1INDEX, line_no, se, yyvsp[-3].ival, -1, string(yyvsp[-1].text_buf));
				void *ptr=yyval.stmt;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
		free(yyvsp[-5].name);
	;
    break;}
case 44:
#line 514 "type.y"
{
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab(yyvsp[-7].name);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "symbol: " << yyvsp[-7].name << " not found in symbol table" << endl;
			++no_errors;
			yyval.stmt=new err_stmt(line_no);
			void *ptr=yyval.stmt;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			struct symtab_ent* se=sym_it->second;
			datatype name_type=se->type;
			if( !(name_type==INT8_ARR_TYPE||name_type==U_INT8_TYPE)){
				cerr << "NAME: "<< yyvsp[-7].name 
					<< " is not of char array type: line_no:" << line_no << endl;
				++no_errors;
			} else {
				yyval.stmt=new list_stmt( LISTA_BASIC_ARRTYPE_STMT_2INDEX, line_no, se, yyvsp[-5].ival, yyvsp[-3].ival, string(yyvsp[-1].text_buf));
				void *ptr=yyval.stmt;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
		free(yyvsp[-7].name);	
	;
    break;}
case 45:
#line 542 "type.y"
{
		if(yyvsp[-2].expr->type==VOID_TYPE || yyvsp[-2].expr->type==ERROR_TYPE){
			++no_errors;
			yyval.stmt=new err_stmt(line_no);
			void *ptr=yyval.stmt;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
			cerr << "Error: If condition has void or Error type:" << line_no << endl;
		} else {
			yyval.stmt=new if_stmt(IFE_STMT,line_no,yyvsp[-2].expr,yyvsp[0].stmt,0);
			void *ptr=yyval.stmt;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		}
	;
    break;}
case 46:
#line 557 "type.y"
{
		if(yyvsp[-4].expr->type==VOID_TYPE || yyvsp[-4].expr->type==ERROR_TYPE){
			++no_errors;
			yyval.stmt=new err_stmt(line_no);
			void *ptr=yyval.stmt;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
			cerr << "Error: If condition has void or Error type:" << line_no << endl;
		} else {
			yyval.stmt=new if_stmt(IFE_STMT, line_no,yyvsp[-4].expr,yyvsp[-2].stmt,yyvsp[0].stmt);
			void *ptr=yyval.stmt;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		}
	;
    break;}
case 47:
#line 575 "type.y"
{
		active_scope_list.pop_back();
		int tmp=active_scope_list.size()-1;
		if(tmp==-1) { 
			active_scope = 0;
			cerr << "Error: active_scope = NULL: should not happen: line_no:" << line_no
				<< endl;
			++no_errors;
			yyval.c_stmt=new struct cmpd_stmt(ERROR_TYPE, line_no, 0);
			void *ptr=yyval.c_stmt;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else { active_scope = active_scope_list[tmp]; }
		struct stmt* head_of_this_chain=blk_heads.back();
		if(  head_of_this_chain==0){
			cerr << "Error in compiler : cmpd_bdy:  " << __FILE__ << __LINE__ << endl;
			++no_errors;
		} else {
			yyvsp[-2].c_stmt->cmpd_bdy = head_of_this_chain;
			blk_heads.pop_back();
		}
		
		yyval.c_stmt=yyvsp[-2].c_stmt;
	;
    break;}
case 48:
#line 606 "type.y"
{
			cout << "In open_curly: " << endl;
		++nest_lev;
		yyval.c_stmt = new cmpd_stmt(CMPD_STMT, line_no, flag_cmpd_stmt_is_a_func_body);
		void *ptr=yyval.c_stmt;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if(flag_cmpd_stmt_is_a_func_body>=0){
			yyval.c_stmt->sc=func_info_table[flag_cmpd_stmt_is_a_func_body]->func_scope;
			// reset the flag
			flag_cmpd_stmt_is_a_func_body=-1;
		} else {
			yyval.c_stmt->sc= new scope();
			void *ptr=yyval.c_stmt;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		}
		flag_next_stmt_start_of_block=true;
		//cout << "open_curly: cmpd_stmt: " << $$ << endl;
		//cout << "pushed active_scope: " << active_scope << endl;
		//active_scope_list.push_back(active_scope);
		active_scope_list.push_back(yyval.c_stmt->sc);
		active_scope = yyval.c_stmt->sc;
		//cout << "active_scope: " << active_scope << endl;
	;
    break;}
case 49:
#line 634 "type.y"
{ yyval.expr=yyvsp[0].expr; ;
    break;}
case 50:
#line 635 "type.y"
{
		yyval.expr=link_chain(yyvsp[-2].expr,yyvsp[0].expr);
	;
    break;}
case 51:
#line 640 "type.y"
{
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_plus);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	;
    break;}
case 52:
#line 647 "type.y"
{
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_minus);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	;
    break;}
case 53:
#line 654 "type.y"
{ 
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_mult);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	;
    break;}
case 54:
#line 661 "type.y"
{
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_div);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	;
    break;}
case 55:
#line 668 "type.y"
{
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_mod);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if(!((yyvsp[-2].expr->type >= INT8_TYPE && yyvsp[-2].expr->type<=U_INT32_TYPE)
				&&
			(yyvsp[0].expr->type>=INT8_TYPE && yyvsp[0].expr->type<=U_INT32_TYPE))){
				cerr << " operands of % should be of type int or char only" << endl;
				++no_errors;
				yyval.expr->type=ERROR_TYPE;
		}
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	;
    break;}
case 56:
#line 682 "type.y"
{
		yyval.expr = new un_expr(yyvsp[0].expr, oper_umin);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if(yyvsp[0].expr->type==VOID_TYPE){
			cerr << "line_no: " << line_no << " expression of void type: check if you are calling a void function on either side" << endl;
			yyval.expr->type=ERROR_TYPE;
			++no_errors;
		}
	;
    break;}
case 57:
#line 693 "type.y"
{
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_lt);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	;
    break;}
case 58:
#line 700 "type.y"
{
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_gt);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	;
    break;}
case 59:
#line 707 "type.y"
{
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_le);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	;
    break;}
case 60:
#line 714 "type.y"
{
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_ge);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	;
    break;}
case 61:
#line 721 "type.y"
{
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_iseq);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	;
    break;}
case 62:
#line 728 "type.y"
{
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_isneq);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	;
    break;}
case 63:
#line 735 "type.y"
{
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_or);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	;
    break;}
case 64:
#line 742 "type.y"
{
		yyval.expr=new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_and);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		void_check(yyvsp[-2].expr->type, yyvsp[0].expr->type, yyval.expr->type);
	;
    break;}
case 65:
#line 749 "type.y"
{
		datatype typ1=yyvsp[-2].expr->type;
		datatype typ2=yyvsp[0].expr->type;
		cout << " oper_assgn: LHS type" << typ1 << " RHS type: " << typ2 << endl;
		bool b1=check_type_compat(typ1, typ2)&& yyvsp[-2].expr->is_lvalue();
		if(yyvsp[-2].expr->is_lvalue()){
			yyval.expr = new bin_expr(yyvsp[-2].expr, yyvsp[0].expr, oper_assgn);
			void *ptr=yyval.expr;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			yyval.expr = new un2_expr(ERROR_TYPE);
			void *ptr=yyval.expr;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
			++no_errors;
			cerr << "oper_assgn error on line: " << line_no<< endl;
		}
	;
    break;}
case 66:
#line 768 "type.y"
{
		yyval.expr = new un_expr(yyvsp[0].expr, oper_not);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		if(yyvsp[0].expr->type==VOID_TYPE){
			cerr << "line_no: " << line_no << " expression of void type: applying operator ! to void expr" << endl;
			yyval.expr->type=ERROR_TYPE;
			++no_errors;
		}
	;
    break;}
case 67:
#line 779 "type.y"
{
		yyval.expr = new un2_expr(yyvsp[0].ival);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		//cerr << "type.y: parsed integer: type" << $$->type << endl;
	;
    break;}
case 68:
#line 786 "type.y"
{
		yyval.expr = new un2_expr(yyvsp[0].dval);
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
	;
    break;}
case 69:
#line 792 "type.y"
{
		map<string,symtab_ent*>::iterator sym_it = find_in_symtab(yyvsp[0].name);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "Error: could not find:" << yyvsp[0].name<<"  in symbol table: lineno: " << line_no << "\n";
			++no_errors;
			yyval.expr = new un2_expr(ERROR_TYPE);
			void *ptr=yyval.expr;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			yyval.expr = new un2_expr(sym_it->second );
			void *ptr=yyval.expr;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		}
		free(yyvsp[0].name);
	;
    break;}
case 70:
#line 809 "type.y"
{
		map<string,symtab_ent*>::iterator sym_it = 
				find_in_symtab(yyvsp[-3].name);
		if(sym_it==active_scope->sym_tab.end() ){
			cerr << "Error: Array indexing expr could not find:" << yyvsp[-3].name<<"  in symbol table: lineno: " << line_no << "\n";
			++no_errors;
			yyval.expr = new un2_expr(ERROR_TYPE);
			void *ptr=yyval.expr;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			symtab_ent* se=sym_it->second;

			datatype e_type=yyvsp[-1].expr->type;
			if(e_type>=U_INT8_TYPE && e_type <=INT32_TYPE){
				datatype nametype =arr_deref_type(se->type);
				if(nametype==ERROR_TYPE) {
					cerr << "ERROR: Variable being indexed not of Array Type : Error: lineno: " << line_no << "\n";
					++no_errors;
					yyval.expr = new un2_expr(ERROR_TYPE);
					void *ptr=yyval.expr;
					mem_addr_tab m1(ptr, line_no);
					mem_addr.push_back(m1);
				} else {
					yyval.expr = new un2_expr(oper_arrderef, nametype,  se, yyvsp[-1].expr);
					void *ptr=yyval.expr;
					mem_addr_tab m1(ptr, line_no);
					mem_addr.push_back(m1);
				}
			} else {
				cerr << "ERROR: Array index not of Type Int : Error: lineno: " << line_no << "\n";
				++no_errors;
				yyval.expr = new un2_expr(ERROR_TYPE);
				void *ptr=yyval.expr;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
		free(yyvsp[-3].name);
	;
    break;}
case 71:
#line 849 "type.y"
{
		symtab_ent* se=0;
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
			void *ptr=yyval.expr;
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
			datatype e_type1=yyvsp[-3].expr->type;
			datatype e_type2=yyvsp[-1].expr->type;
			if( (e_type1>=U_INT8_TYPE && e_type1 <=INT32_TYPE) && 
					(e_type2>=U_INT8_TYPE && e_type2<=INT32_TYPE)){
				datatype d1=arr_deref_type(se->type);
				if(d1==ERROR_TYPE){
					yyval.expr = new un2_expr(ERROR_TYPE);
					void *ptr=yyval.expr;
					mem_addr_tab m1(ptr, line_no);
					mem_addr.push_back(m1);
					cerr << "Type Error:  x: lineno: " << line_no << "\n";
					++no_errors;
				} else {
					yyval.expr = new un2_expr(oper_blk_arr_assgn, d1, se,yyvsp[-3].expr,yyvsp[-1].expr);
					void *ptr=yyval.expr;
					mem_addr_tab m1(ptr, line_no);
					mem_addr.push_back(m1);
				}
			} else {
				yyval.expr = new un2_expr(ERROR_TYPE);
				void *ptr=yyval.expr;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
				cerr << "ERROR: NAME  =NAME[EXPR, EXPR] EXPR should be of type int or char: lineno: " 
					<< line_no << "\n";
				++no_errors;
			}
		}
		//free($1);
	;
    break;}
case 72:
#line 906 "type.y"
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
			void *ptr=yyval.expr;
			mem_addr_tab m1(ptr, line_no);
			mem_addr.push_back(m1);
		} else {
			datatype my_type=func_info_table[index]->return_type;
			expr* e_ptr=trav_chain(yyvsp[-1].expr);
			var_list* fparam=func_info_table[index]->param_list;
			bool match=false;
			if(skip_type_check==false){
				match=check_parameters(e_ptr, fparam);
			}
			if(match || skip_type_check){
				//$$=new un2_expr(oper_func_call, my_type, $3, index, line_no);
				yyval.expr=new un2_expr(oper_func_call, my_type, e_ptr, index, line_no);
				void *ptr=yyval.expr;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);

			} else {
				yyval.expr=new un2_expr(ERROR_TYPE);
				void *ptr=yyval.expr;
				mem_addr_tab m1(ptr, line_no);
				mem_addr.push_back(m1);
			}
		}
		free(yyvsp[-3].name);
	;
    break;}
case 73:
#line 945 "type.y"
{
		yyval.expr = new un2_expr(strdup(yyvsp[0].text_buf));
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
	;
    break;}
case 74:
#line 951 "type.y"
{ 
		yyval.expr = new un_expr(yyvsp[-1].expr, oper_parexp );
		void *ptr=yyval.expr;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
	;
    break;}
case 75:
#line 959 "type.y"
{ 
#ifdef DEBUG_GRAM
	printf("got table defn\n"); 
#endif
	;
    break;}
case 76:
#line 964 "type.y"
{ 
#ifdef DEBUG_GRAM
		printf("recursive tab_defn\n"); 
#endif
	;
    break;}
case 77:
#line 972 "type.y"
{
		//printf("got table defn: no filter\n");
		yyval.tbl=new table(yyvsp[-2].name,yyvsp[-1].name, line_no);
		void *ptr=yyval.tbl;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		// default value for constructor tbl_ptr->filter=NULL;
		table_list.push_back(yyval.tbl);
		//free($2); free($3);
	;
    break;}
case 78:
#line 982 "type.y"
{
		//printf("got table defn: with filter\n");
		yyval.tbl=new table(yyvsp[-5].name,yyvsp[-4].name, line_no, yyvsp[-1].expr);
		void *ptr=yyval.tbl;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		table_list.push_back(yyval.tbl);
		//free($2); free($3);
	;
    break;}
case 79:
#line 991 "type.y"
{
		cerr << "Error in tab section line: " <<
			line_no << endl;
		++ line_no;
		++no_errors;
	;
    break;}
case 80:
#line 999 "type.y"
{
	;
    break;}
case 81:
#line 1001 "type.y"
{
	;
    break;}
case 82:
#line 1005 "type.y"
{
		basic_ax_stmt* bptr= trav_chain(yyvsp[0].basic_ax_stmt);
		yyval.ax = new ax(bptr,no_count_ax_elems, no_tot_ax_elems, 0);
		void *ptr=yyval.ax;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		
		ax_map[yyvsp[-2].name]=yyval.ax;
#ifdef DEBUG_GRAM
		printf("NAME: $2: %s\n", yyvsp[-2].name);
#endif
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		free(yyvsp[-2].name);
	;
    break;}
case 83:
#line 1020 "type.y"
{
		basic_ax_stmt* bptr= trav_chain(yyvsp[0].basic_ax_stmt);
		yyval.ax = new ax(bptr,no_count_ax_elems, no_tot_ax_elems, yyvsp[-2].expr);
		void *ptr=yyval.ax;
		mem_addr_tab m1(ptr, line_no);
		mem_addr.push_back(m1);
		ax_map[yyvsp[-5].name]=yyval.ax;
#ifdef DEBUG_GRAM
		printf("NAME: $2: %s\n", yyvsp[-5].name);
#endif
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		free(yyvsp[-5].name);
	;
    break;}
case 84:
#line 1034 "type.y"
{
		cerr << "Error in axis section line: " <<
			line_no << endl;
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		++no_errors;
	;
    break;}
case 85:
#line 1045 "type.y"
{
		yyval.basic_ax_stmt = yyvsp[0].basic_ax_stmt;
	;
    break;}
case 86:
#line 1048 "type.y"
{
		yyval.basic_ax_stmt=link_chain(yyvsp[-1].basic_ax_stmt, yyvsp[0].basic_ax_stmt);
	;
    break;}
case 87:
#line 1053 "type.y"
{
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		yyval.basic_ax_stmt = new tot_ax_stmt (tot_axstmt,yyvsp[-1].text_buf, 0);
	;
    break;}
case 88:
#line 1058 "type.y"
{
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		yyval.basic_ax_stmt = new tot_ax_stmt (tot_axstmt,yyvsp[-4].text_buf, yyvsp[-1].expr);
	;
    break;}
case 89:
#line 1063 "type.y"
{
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		yyval.basic_ax_stmt = new count_ax_stmt (cnt_axstmt,yyvsp[-4].text_buf, yyvsp[-1].expr);
	;
    break;}
case 90:
#line 1068 "type.y"
{
		yyval.basic_ax_stmt = new ttl_ax_stmt (txt_axstmt,yyvsp[-1].text_buf);
		++no_tot_ax_elems;
	;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/local/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 1074 "type.y"


void print_expr(FILE* edit_out, expr * e);

int	compile();
int	run(char * data_file_name, int rec_len);
void print_table_code(FILE * op, FILE *tab_drv_func, FILE * tab_summ_func);
void print_axis_code(FILE * op, FILE * axes_drv_func);
void clean_up();

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
		cout << "yyparse finished : now going to print tree: no_errors: "    
		<< " should be 0 or we have a bug in the compiler"<< endl;

	//yyterminate();
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
		delete fi;
		for(int i=0; i< mem_addr.size(); ++i ){
			cout << "addr: " << mem_addr[i].mem_ptr << " line: " << mem_addr[i].line_number << endl;
		}
		cout << "returning from main"<< endl;
		return rval;
	}
	cout << "returning from main with errors"<< endl;
	/*
	fclose(table_op);
	fclose(tab_drv_func);
	fclose(tab_summ_func);
	fclose(axes_op);
	fclose(axes_drv_func);
	*/

	return no_errors;
}

#include <cstdlib>
#include <cstdio>


void clean_up(){
	cout << "Entered function clean_up()" << endl;
	/*
	if(func_info_table.size()>0){
		// this should be enough as the rest are chained
		delete func_info_table[0];
	}
	for(int i=0; i<func_info_table.size(); ++i){
		func_info * f=func_info_table[i];
			if(f->param_list) {
				delete f->param_list;
			}
			if (f->func_body){
				delete f->func_body;
			}
			if (f->func_scope){
				delete f->func_scope;
			}
		delete f;
	}
			*/
	typedef map<string, ax*>::iterator ax_map_iter;
	for(ax_map_iter it=ax_map.begin(); it!=ax_map.end(); ++it){
		delete it->second; it->second=0;
	}
	// we should only delete the 0 index scope as this was manually created by us
	/*
	for( int  i=0; i<active_scope_list.size(); ++i){
		scope* sc=active_scope_list[i];
		if(sc ) {
			delete sc;
			active_scope_list[i]=0;
		}
	}
	*/
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

