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


extern YYSTYPE yylval;
